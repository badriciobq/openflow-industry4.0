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


/**
 *
 * Maurício <badriciobq@gmail.com>
 *
 * Vale lembrar que existe duas linhas de produção, a 0 e a 1. Cuidado com
 * as linhas de produção pois os nomes dos sensores e o indice das linhas
 * está inconsistente.
 *
 * TODO - Consertar a inconsistencia nos nomes.
 */


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
        product_demmand = 0;

        lines_of_production = new type_line_of_production[qtde_lines];

        //statistics
        msgsRcvd = msgsSent = bytesRcvd = bytesSent = 0;

        WATCH(msgsRcvd);
        WATCH(msgsSent);
        WATCH(bytesRcvd);
        WATCH(bytesSent);

        WATCH(product_demmand);
        WATCH(product_inventory);

        WATCH(lines_of_production[0].product_demmand);
        WATCH(lines_of_production[0].product_inventory);

        WATCH(lines_of_production[1].product_demmand);
        WATCH(lines_of_production[1].product_inventory);

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
        cModule *factory = getModuleByPath("factory");
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


    std::cout << "Fábrica" << endl;
    std::cout << "Demanda: " <<  product_demmand << endl;
    std::cout << "Estoque: " << product_inventory << endl;

    std::cout << endl;
    std::cout << "Linha de produção 0" << endl;
    std::cout << "Demanda: " << lines_of_production[0].product_demmand << endl;
    std::cout << "Estoque: " << lines_of_production[0].product_inventory << endl;

    std::cout << "Iniciados: " << lines_of_production[0].production_starts.size() << endl;
    std::cout << "Defeito: " << lines_of_production[0].production_defect.size() << endl;
    std::cout << "Concluídos: " << lines_of_production[0].production_done.size() << endl;

    std::cout << endl;
    std::cout << "Linha de produção 1" << endl;
    std::cout << "Demanda: " << lines_of_production[1].product_demmand << endl;
    std::cout << "Estoque: " << lines_of_production[1].product_inventory << endl;

    std::cout << "Iniciados: " << lines_of_production[1].production_starts.size() << endl;
    std::cout << "Defeito: " << lines_of_production[1].production_defect.size() << endl;
    std::cout << "Concluídos: " << lines_of_production[1].production_done.size() << endl;



}

void ServerApp::process_message(GenericAppMsg *msg)
{
    // Não excluir a mensagem, ela geralmente é utilizada como resposta pelo server.
    switch (msg->getSensor()) {

    case SENSOR_PRODUCT:
    {
        lines_of_production[1].production_starts.insert(msg->getTag_id());

        // A cada produto que entra em produção eu incremento o estoque de matéria prima
        lines_of_production[1].product_inventory--;

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
            lines_of_production[1].production_defect.insert( std::pair<int, int>(msg->getTag_id(), SENSOR_WEIGTH));

            std::set<int>::iterator it = lines_of_production[1].production_starts.find(msg->getTag_id());
            if(it != lines_of_production[1].production_starts.end())
                lines_of_production[1].production_starts.erase(msg->getTag_id());

            // Destroy os produtos com defeito de peso
            Factory->deleteNode(msg->getTag_id());

            /* A cada produto com defeito, eu decremento o produto da linha de produção atual e
             * mando o produto para ser uma demanda de fábrica, com isso ele pode ser atendido
             * por outra linha de produção ociosa.
             * */
            lines_of_production[1].product_demmand--;
            product_demmand++;

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
            lines_of_production[1].production_defect.insert( std::pair<int, int>(msg->getTag_id(), SENSOR_SIZE));

            std::set<int>::iterator it = lines_of_production[1].production_starts.find(msg->getTag_id());
            if(it != lines_of_production[1].production_starts.end())
                lines_of_production[1].production_starts.erase(msg->getTag_id());

            // Destroy os produtos com defeito de tamanho
            Factory->deleteNode(msg->getTag_id());

            /* A cada produto com defeito, eu decremento o produto da linha de produção atual e
             * mando o produto para ser uma demanda de fábrica, com isso ele pode ser atendido
             * por outra linha de produção ociosa.
             * */
            lines_of_production[1].product_demmand--;
            product_demmand++;

            emit(prodProblemSignal, msg);
        }
        else
        {
            // Último sensor! fim do processo de produção
            lines_of_production[1].production_done.insert(msg->getTag_id());

            std::set<int>::iterator it = lines_of_production[1].production_starts.find(msg->getTag_id());
            if(it != lines_of_production[1].production_starts.end())
                lines_of_production[1].production_starts.erase(msg->getTag_id());

            // Destroy os produtos que foram fabriados com sucesso
            Factory->deleteNode(msg->getTag_id());

            /* A cada produto fabricado com sucesso, é decretado um produto da demanda */
            lines_of_production[1].product_demmand--;

            emit(prodDoneSignal, msg);
        }

        break;
    }

    case SENSOR_PRODUCT_P0:
    {
        lines_of_production[0].production_starts.insert(msg->getTag_id());

        // Incrementa a matéria prima de cada nó que inicia.
        lines_of_production[0].product_inventory--;

        emit(prodStartsSignal, msg);

        break;
    }
    case SENSOR_WEIGTH_P0:
    {
        double weigth = msg->getData();

        // Se o peso do produtor for maior do que 0.9, produto considerado com defeito
        if(weigth < 0.1)
        {
            // Insere o elemento entre os elementos com deifeito
            lines_of_production[0].production_defect.insert( std::pair<int, int>(msg->getTag_id(), SENSOR_WEIGTH));

            std::set<int>::iterator it = lines_of_production[0].production_starts.find(msg->getTag_id());
            if(it != lines_of_production[0].production_starts.end())
                lines_of_production[0].production_starts.erase(msg->getTag_id());

            // Destroy os produtos com defeito de peso
            Factory->deleteNode(msg->getTag_id());

            lines_of_production[0].product_demmand--;
            product_demmand++;

            emit(prodProblemSignal, msg);
        }
        break;
    }
    case SENSOR_SIZE_P0:
    {
        double size = msg->getData();

        // Se o peso do produtor for maior do que 0.9, produto considerado com defeito
        if(size < 0.1)
        {
            // Insere o elemento entre os elementos com deifeito
            lines_of_production[0].production_defect.insert( std::pair<int, int>(msg->getTag_id(), SENSOR_SIZE));

            std::set<int>::iterator it = lines_of_production[0].production_starts.find(msg->getTag_id());
            if(it != lines_of_production[0].production_starts.end())
                lines_of_production[0].production_starts.erase(msg->getTag_id());

            // Destroy os produtos com defeito de tamanho
            Factory->deleteNode(msg->getTag_id());

            lines_of_production[0].product_demmand--;
            product_demmand++;

            emit(prodProblemSignal, msg);

        }
        else
        {
            // Ultimo sensor! fim do processo de produção
            lines_of_production[0].production_done.insert(msg->getTag_id());

            std::set<int>::iterator it = lines_of_production[0].production_starts.find(msg->getTag_id());
            if(it != lines_of_production[0].production_starts.end())
                lines_of_production[0].production_starts.erase(msg->getTag_id());

            // Destroy os produtos que foram fabriados com sucesso
            Factory->deleteNode(msg->getTag_id());

            lines_of_production[0].product_demmand--;

            emit(prodDoneSignal, msg);
        }

        break;
    }

    case CLIENT:
    {
        // Quantidade de nós a produzer. Demanda do cliente.
        int value = msg->getData();

        product_demmand += value;

        if(product_demmand == 0)
            break;

        check_demmmand();
        break;
    }
    case SUPPLIER:
    {
        // Valor -1 indica início de comunicação; Valor diferente indica fornecimento de material
        int value = msg->getData();

        if(value == -1)
        {
            // Solicita do fornecedor matéria prima
            if(product_demmand > product_inventory)
                msg->setData(product_demmand);
        }
        else
        {
            product_inventory += value;
        }

        check_demmmand();

        break;
    }
    default:
        EV << "sensor desconhecido: " << msg->getSensor() << endl;
        break;
    }

}


void ServerApp::check_demmmand()
{

    if(product_demmand == 0)
        return;

    // Se a demanda for maior do que o estoque?
    if(product_demmand > product_inventory)
    {
        if(product_inventory > 0)
        {
            if(lines_of_production[0].product_demmand <= lines_of_production[1].product_demmand)
            {
                Factory->setDemand(product_inventory, 0);
                lines_of_production[0].product_demmand += product_inventory;
                lines_of_production[0].product_inventory += product_inventory;
            }
            else
            {
                Factory->setDemand(product_inventory, 1);
                lines_of_production[1].product_demmand += product_inventory;
                lines_of_production[1].product_inventory += product_inventory;
            }

            product_demmand -= product_inventory;
            product_inventory -= product_inventory;
        }
    }
    else
    {
        if(lines_of_production[0].product_demmand <= lines_of_production[1].product_demmand)
        {
            Factory->setDemand(product_demmand, 0);
            lines_of_production[0].product_demmand += product_demmand;
            lines_of_production[0].product_inventory += product_demmand;
        }
        else
        {
            Factory->setDemand(product_demmand, 1);
            lines_of_production[1].product_demmand += product_demmand;
            lines_of_production[1].product_inventory += product_demmand;
        }
        product_inventory -= product_demmand;
        product_demmand -= product_demmand;
    }
}
