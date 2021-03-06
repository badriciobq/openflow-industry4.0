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

        simtime_t delay = uniform(0, 0.01);
        rescheduleTimer(simTime() + delay, MSGKIND_CONNECT);
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

void SupplierApp::sendRequest(double data)
{
    long requestLength = par("requestLength");
    long replyLength = par("replyLength");
    if (requestLength < 1)
        requestLength = 1;
    if (replyLength < 1)
        replyLength = 1;

    GenericAppMsg *msg = new GenericAppMsg("data");
    msg->setByteLength(requestLength);
    msg->setExpectedReplyLength(replyLength);
    msg->setServerClose(false);
    msg->setSensor(SUPPLIER);
    msg->setData(data);

    sendPacket(msg);
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
            sendRequest(-1);

        break;
    }
    case MSGKIND_SEND:
    {
        sendRequest(-1);
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
    numRequestsToSend = 2;

    if (numRequestsToSend < 1)
        numRequestsToSend = 1;

    // perform first request if not already done (next one will be sent when reply arrives)
    if (!earlySend)
        sendRequest(-1);

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
        else
        {
            timeOutMess->setKind(msgKind);
            scheduleAt(d, timeOutMess);
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
    if (numRequestsToSend > 0)
    {
        GenericAppMsg *appmsg = dynamic_cast<GenericAppMsg *>(msg);
        if(appmsg)
        {
            int value = appmsg->getData();

            if(value > 0 )
                sendRequest(value*1.1);
        }
    }

    numRequestsToSend--;

    TCPAppBase::socketDataArrived(connId, ptr, msg, urgent);

    if (numRequestsToSend > 0)
    {
        // Enviando outra mensagens do buffer na mesma sessão.
        sendRequest(-1);
    }
    else if (socket.getState() != TCPSocket::LOCALLY_CLOSED)
    {
        close();
    }
}

void SupplierApp::socketClosed(int connId, void *ptr)
{
    TCPAppBase::socketClosed(connId, ptr);

    isAnSession = false;

    if (timeOutMess)
    {
        simtime_t d = uniform(1,1.1);
        rescheduleTimer(simTime() + d, MSGKIND_CONNECT);
    }
}

void SupplierApp::socketFailure(int connId, void *ptr, int code)
{
    TCPAppBase::socketFailure(connId, ptr, code);

    simtime_t delay = uniform(0, 0.01);
    rescheduleTimer(simTime() + delay, MSGKIND_CONNECT);
}







