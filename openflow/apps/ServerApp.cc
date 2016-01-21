//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include <ccomponent.h>
#include <cdisplaystring.h>
#include <cenvir.h>
#include <cexception.h>
#include <clistener.h>
#include <cmessage.h>
#include <cnamedobject.h>
#include <cobjectfactory.h>
#include <cownedobject.h>
#include <cpar.h>
#include <cregistrationlist.h>
#include <csimplemodule.h>
#include <csimulation.h>
#include <cwatch.h>
#include <Compat.h>
#include <IPvXAddress.h>
#include <IPvXAddressResolver.h>
#include <ModuleAccess.h>
#include <NodeStatus.h>
#include <regmacros.h>
#include <simtime.h>
#include <simtime_t.h>
#include <simutil.h>
#include <ServerApp.h>
#include <TCPCommand_m.h>
#include <TCPSocket.h>
#include <__tree>
#include <cstdio>
#include <iostream>
#include <utility>

Define_Module(ServerApp);

simsignal_t ServerApp::rcvdPkSignal = registerSignal("rcvdPk");
simsignal_t ServerApp::sentPkSignal = registerSignal("sentPk");


simsignal_t ServerApp::prodDoneSignal = registerSignal("prodDone");
simsignal_t ServerApp::prodProblemSignal = registerSignal("prodProblem");
simsignal_t ServerApp::prodStartsSignal = registerSignal("prodStarts");

void ServerApp::initialize(int stage)
{
    cSimpleModule::initialize(stage);

    if (stage == 0)
    {
        delay = par("replyDelay");
        maxMsgDelay = 0;
        product_inventory = 0;

        //statistics
        msgsRcvd = msgsSent = bytesRcvd = bytesSent = 0;

        WATCH(msgsRcvd);
        WATCH(msgsSent);
        WATCH(bytesRcvd);
        WATCH(bytesSent);
    }
    else if (stage == 3)
    {
        const char *localAddress = par("localAddress");
        int localPort = par("localPort");
        TCPSocket socket;
        socket.setOutputGate(gate("tcpOut"));
        socket.setDataTransferMode(TCP_TRANSFER_OBJECT);
        socket.bind(localAddress[0] ? IPvXAddressResolver().resolve(localAddress) : IPvXAddress(), localPort);
        socket.listen();

        bool isOperational;
        NodeStatus *nodeStatus = dynamic_cast<NodeStatus *>(findContainingNode(this)->getSubmodule("status"));
        isOperational = (!nodeStatus) || nodeStatus->getState() == NodeStatus::UP;
        if (!isOperational)
            throw cRuntimeError("This module doesn't support starting in node DOWN state");


        // Pega a referência para o factory para mandar destruir os produtos fabricados com sucesso ou que falharem
        cModule *factory = getModuleByPath("industry4.factory");
        Factory = check_and_cast<NodeFactory *>(factory);
    }
}

void ServerApp::sendOrSchedule(cMessage *msg, simtime_t delay)
{
    if (delay==0)
        sendBack(msg);
    else
        scheduleAt(simTime()+delay, msg);
}

void ServerApp::sendBack(cMessage *msg)
{
    GenericAppMsg *appmsg = dynamic_cast<GenericAppMsg*>(msg);

    if (appmsg)
    {
        msgsSent++;
        bytesSent += appmsg->getByteLength();
        emit(sentPkSignal, appmsg);

        EV << "sending \"" << appmsg->getName() << "\" to TCP, " << appmsg->getByteLength() << " bytes\n";
    }
    else
    {
        EV << "sending \"" << msg->getName() << "\" to TCP\n";
    }

    send(msg, "tcpOut");
}

void ServerApp::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage())
    {
        sendBack(msg);
    }
    else if (msg->getKind()==TCP_I_PEER_CLOSED)
    {
        // we'll close too, but only after there's surely no message
        // pending to be sent back in this connection
        msg->setName("close");
        msg->setKind(TCP_C_CLOSE);
        sendOrSchedule(msg, delay+maxMsgDelay);
    }
    else if (msg->getKind()==TCP_I_DATA || msg->getKind()==TCP_I_URGENT_DATA)
    {
        GenericAppMsg *appmsg = dynamic_cast<GenericAppMsg *>(msg);

        if (!appmsg)
            error("Message (%s)%s is not a GenericAppMsg -- "
                  "probably wrong client app, or wrong setting of TCP's "
                  "dataTransferMode parameters "
                  "(try \"object\")",
                  msg->getClassName(), msg->getName());

        process_message(appmsg);

        msgsRcvd++;
        bytesRcvd += appmsg->getByteLength();
        emit(rcvdPkSignal, appmsg);

        long requestedBytes = appmsg->getExpectedReplyLength();

        simtime_t msgDelay = appmsg->getReplyDelay();
        if (msgDelay>maxMsgDelay)
            maxMsgDelay = msgDelay;

        bool doClose = appmsg->getServerClose();
        int connId = check_and_cast<TCPCommand *>(appmsg->getControlInfo())->getConnId();

        if (requestedBytes==0)
        {
            delete msg;
        }
        else
        {
            delete appmsg->removeControlInfo();
            TCPSendCommand *cmd = new TCPSendCommand();
            cmd->setConnId(connId);
            appmsg->setControlInfo(cmd);

            // set length and send it back
            appmsg->setKind(TCP_C_SEND);
            appmsg->setByteLength(requestedBytes);
            sendOrSchedule(appmsg, delay+msgDelay);
        }

        if (doClose)
        {
            cMessage *msg = new cMessage("close");
            msg->setKind(TCP_C_CLOSE);
            TCPCommand *cmd = new TCPCommand();
            cmd->setConnId(connId);
            msg->setControlInfo(cmd);
            sendOrSchedule(msg, delay+maxMsgDelay);
        }
    }
    else
    {
        // some indication -- ignore
        EV << "drop msg: " << msg->getName() << ", kind:"<< msg->getKind() << endl;
        delete msg;
    }

    if (ev.isGUI())
    {
        char buf[64];
        sprintf(buf, "rcvd: %ld pks %ld bytes\nsent: %ld pks %ld bytes", msgsRcvd, bytesRcvd, msgsSent, bytesSent);
        getDisplayString().setTagArg("t", 0, buf);
    }
}

void ServerApp::finish()
{
    EV << getFullPath() << ": sent " << bytesSent << " bytes in " << msgsSent << " packets\n";
    EV << getFullPath() << ": received " << bytesRcvd << " bytes in " << msgsRcvd << " packets\n";
}

void ServerApp::process_message(GenericAppMsg *msg)
{
    // Não excluir a mensagem, ela geralmente é utilizada como resposta pelo server.
    switch (msg->getSensor()) {
        case SENSOR_PRODUCT:
        {
            production_starts.insert(msg->getTag_id());

            emit(prodStartsSignal, msg);

            break;
        }
        case SENSOR_WEIGTH:
        {
            double weigth = msg->getData();

            // Se o peso do produtor for maior do que 0.9, produto considerado com defeito
            if(weigth < 0.1)
            {
                // Insere o elemento entre os elementos com deifeito
                production_defect.insert( std::pair<int, int>(msg->getTag_id(), SENSOR_WEIGTH));

                std::set<int>::iterator it = production_starts.find(msg->getTag_id());
                if(it != production_starts.end())
                    production_starts.erase(msg->getTag_id());

                // Destroy os produtos com defeito de peso
                Factory->deleteNode(msg->getTag_id());
                Factory->setDemand(1, 1);

                emit(prodProblemSignal, msg);
            }
            break;
        }
        case SENSOR_SIZE:
        {
            double size = msg->getData();

            // Se o peso do produtor for maior do que 0.9, produto considerado com defeito
            if(size < 0.1)
            {
                // Insere o elemento entre os elementos com deifeito
                production_defect.insert( std::pair<int, int>(msg->getTag_id(), SENSOR_SIZE));

                std::set<int>::iterator it = production_starts.find(msg->getTag_id());
                if(it != production_starts.end())
                    production_starts.erase(msg->getTag_id());

                // Destroy os produtos com defeito de tamanho
                Factory->deleteNode(msg->getTag_id());
                Factory->setDemand(1, 1);

                emit(prodProblemSignal, msg);

            }
            else
            {
                // Ultimo sensor! fim do processo de produção
                production_done.insert(msg->getTag_id());

                std::set<int>::iterator it = production_starts.find(msg->getTag_id());
                if(it != production_starts.end())
                    production_starts.erase(msg->getTag_id());

                // Destroy os produtos que foram fabriados com sucesso
                Factory->deleteNode(msg->getTag_id());

                emit(prodDoneSignal, msg);
            }

            break;
        }

        case CLIENT:
        {
            int value = msg->getData();
            Factory->setDemand(value, 1);

            std::cout << "Server recebeu uma mensagem de CLIENT" << endl;
            EV << "Server recebeu uma mensagem de CLIENT" << endl;

            /*if(product_inventory >= value)
            {
                Factory->setDemand(value);
            }
            else
            {

            }*/

            break;
        }
        case SUPPLIER:
        {
            std::cout << "Server recebeu uma mensagem de SUPPLIER" << endl;
            EV << "Server recebeu uma mensagem de SUPPLIER" << endl;

            break;
        }
        default:
            EV << "sensor desconhecido: " << msg->getSensor() << endl;
            break;
    }

}
