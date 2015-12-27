#include "SupplierApp.h"

#include "NodeOperations.h"
#include "ModuleAccess.h"
#include "GenericAppMsg_m.h"


Define_Module(SupplierApp);

SupplierApp::SupplierApp()
{

}

SupplierApp::~SupplierApp()
{
    cancelAndDelete(timeOutMess);
}

void SupplierApp::initialize(int stage)
{
    TCPAppBase::initialize(stage);
    if (stage == 0)
    {
        numRequestsToSend = 0;

        earlySend = false;  // TBD make it parameter
        isAnSession = false;

        WATCH(numRequestsToSend);
        WATCH(earlySend);
    }
    else if (stage == 3)
    {
        timeOutMess = NULL;
        nodeStatus = dynamic_cast<NodeStatus *>(findContainingNode(this)->getSubmodule("status"));
    }
}

bool SupplierApp::isNodeUp()
{
    return !nodeStatus || nodeStatus->getState() == NodeStatus::UP;
}

bool SupplierApp::handleOperationStage(LifecycleOperation *operation, int stage, IDoneCallback *doneCallback)
{
    Enter_Method_Silent();
    if (dynamic_cast<NodeStartOperation *>(operation)) {
        if (stage == NodeStartOperation::STAGE_APPLICATION_LAYER) {
            // TODO: Descobrir pra que usar isso
        }
    }
    else if (dynamic_cast<NodeShutdownOperation *>(operation)) {
        if (stage == NodeShutdownOperation::STAGE_APPLICATION_LAYER) {
            if (socket.getState() == TCPSocket::CONNECTED || socket.getState() == TCPSocket::CONNECTING || socket.getState() == TCPSocket::PEER_CLOSED)
                close();
            // TODO: wait until socket is closed
        }
    }
    else if (dynamic_cast<NodeCrashOperation *>(operation)) {
        if (stage == NodeCrashOperation::STAGE_CRASH)
        {
            //TODO: Descobrir o que fazer aqui também
        }

    }
    else throw cRuntimeError("Unsupported lifecycle operation '%s'", operation->getClassName());
    return true;
}

void SupplierApp::sendRequest()
{
     long requestLength = par("requestLength");
     long replyLength = par("replyLength");
     if (requestLength < 1)
         requestLength = 1;
     if (replyLength < 1)
         replyLength = 1;

     if(!isBufferEmpty())
     {
         GenericAppMsg *msg = new GenericAppMsg("data");
         msg->setByteLength(requestLength);
         msg->setExpectedReplyLength(replyLength);
         msg->setServerClose(false);

         int value = popBuffer();
         if(value != -1)
         {
             msg->setTag_id( value );
             msg->setData(uniform(0,1));

             if(strcmp(getParentModule()->getName(), "RFIDProduct") == 0)
             {
                 msg->setSensor(SENSOR_PRODUCT);
             }
             else if (strcmp(getParentModule()->getName(), "RFIDSize") == 0)
             {
                 msg->setSensor(SENSOR_SIZE);
             }
             else if (strcmp(getParentModule()->getName(), "RFIDWeigth") == 0)
             {
                 msg->setSensor(SENSOR_WEIGTH);
             }
         }

         sendPacket(msg);
     }
}

void SupplierApp::handleTimer(cMessage *msg)
{
    switch (msg->getKind())
    {
        case MSGKIND_CONNECT:
        {
            connect(); // active OPEN

            // significance of earlySend: if true, data will be sent already
            // in the ACK of SYN, otherwise only in a separate packet (but still
            // immediately)
            if (earlySend)
                sendRequest();

            break;
        }
        case MSGKIND_SEND:
        {
           sendRequest();
           numRequestsToSend--;
           // no scheduleAt(): next request will be sent when reply to this one
           // arrives (see socketDataArrived())
           break;
        }

        default:
            throw cRuntimeError("Invalid timer msg: kind=%d", msg->getKind());
    }
}

void SupplierApp::socketEstablished(int connId, void *ptr)
{
    TCPAppBase::socketEstablished(connId, ptr);

    isAnSession = true;

    // determine number of requests in this session
    numRequestsToSend = (long) m_buffer.size();
    if (numRequestsToSend < 1)
        numRequestsToSend = 1;

    // perform first request if not already done (next one will be sent when reply arrives)
    if (!earlySend)
        sendRequest();

    numRequestsToSend--;
}

void SupplierApp::rescheduleTimer(simtime_t d, short int msgKind)
{
    if(timeOutMess)
    {
        if(isAnSession)
        {
            cancelEvent(timeOutMess);
            //timeOutMess->setKind(msgKind);
            //scheduleAt(d, timeOutMess);
        }
    }
    else
    {
        timeOutMess = new cMessage("timer");
        timeOutMess->setKind(msgKind);
        scheduleAt(d, timeOutMess);
    }
}

void SupplierApp::socketDataArrived(int connId, void *ptr, cPacket *msg, bool urgent)
{
    GenericAppMsg *appmsg = dynamic_cast<GenericAppMsg *>(msg);

    if(appmsg)
    {
        int value = appmsg->getTag_id();

        if(m_history.find(value) == m_history.end())
        {
            m_history.insert(value);
            for(std::deque<int>::iterator it = m_buffer.begin(); it != m_buffer.end(); it++)
            {
                if(value == (*it))
                {
                    m_buffer.erase(it);
                    break;
                }
            }
        }
    }

    TCPAppBase::socketDataArrived(connId, ptr, msg, urgent);

    if (numRequestsToSend > 0)
    {
        // Enviando outra mensagens do buffer na mesma sessão.
        sendRequest();
    }
    else if (socket.getState() != TCPSocket::LOCALLY_CLOSED)
    {
        close();
    }
}

void SupplierApp::socketClosed(int connId, void *ptr)
{
    TCPAppBase::socketClosed(connId, ptr);


    delete(timeOutMess);
    timeOutMess = NULL;

    isAnSession = false;
}

void SupplierApp::socketFailure(int connId, void *ptr, int code)
{
    TCPAppBase::socketFailure(connId, ptr, code);

    simtime_t delay = uniform(0, 0.01);
    rescheduleTimer(simTime() + delay, MSGKIND_CONNECT);
}


void SupplierApp::pushBuffer(int id)
{
    Enter_Method_Silent("pushBuffer()");

    if( m_history.find(id) == m_history.end() )
    {
        bool insert = true;
        std::deque<int>::iterator it;

        for( it = m_buffer.begin(); it != m_buffer.end(); it++)
        {
            if(id == (*it))
            {
                insert = false;
                continue;
            }
        }

        if(insert)
        {
            m_buffer.push_back(id);
            if(isNodeUp())
            {
                simtime_t delay = uniform(0,0.01);
                rescheduleTimer(simTime() + delay, MSGKIND_CONNECT);
            }
        }
    }
}

int SupplierApp::popBuffer()
{
    if( !isBufferEmpty() )
    {
        int value = m_buffer.front();
        m_buffer.pop_front();

        return value;
    }
    else
    {
        return -1;
    }
}

bool SupplierApp::isBufferEmpty()
{
    return m_buffer.empty();
}







