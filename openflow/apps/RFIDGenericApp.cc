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

#include "RFIDGenericApp.h"
#include "RFID_Message_m.h"

Define_Module(RFIDGenericApp);


RFIDGenericApp::RFIDGenericApp()
{
    s_msg = new cMessage("rfid_timer", RFID_TIMER);

    // Pegando referências dos canais
    lowerLayerOut = findGate("lowerLayerOut");
    lowerLayerIn = findGate("lowerLayerIn");

    AppSensor = NULL;
}

RFIDGenericApp::~RFIDGenericApp()
{
    cancelAndDelete(s_msg);
}


void RFIDGenericApp::initialize(int stage)
{
    if(stage != 2)
        return;

    intervalTimer = par("intervalTimer");
    isTag = par("isTag");

    // Tag do nó é sua  posição no vetor de index do factory
    id = getParentModule()->getIndex();


    if(getParentModule()->findSubmodule("tcpApp",0) != -1)
    {
        cSimpleModule *AppTCP = static_cast< cSimpleModule *>(getParentModule()->getSubmodule("tcpApp",0));
        AppSensor = check_and_cast<SensorApp *>(AppTCP);
    }

    // Agenda uma mensagem para evento interno (se TAG)
    scheduleSelfMessage();
}

void RFIDGenericApp::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage())
    {
        if(msg->getKind() == RFID_TIMER)
        {
            if(isTag)
            {
                // Envia o id para a camada de baixo
                RFID_Message *msg = new RFID_Message("RFID_INFO", RFID_INFO);
                msg->setTag_id(id);

                // Envia mensagem para a camada de baixo.
                sendMessageDown(msg);
            }

            // Agenda um evento para enviar uma nova mensagem
            scheduleSelfMessage();
        }
    }
    else
    {
        RFID_Message *rfid_msg = static_cast<RFID_Message *>(msg);
        if(rfid_msg->getKind() == RFID_INFO)
        {

            if(AppSensor != NULL && AppSensor->isSimple())
            {
                // Envia o ID direto para o server
                AppSensor->pushBuffer(rfid_msg->getTag_id());
            }
        }
    }
}


void RFIDGenericApp::scheduleSelfMessage()
{
    if(isTag)
    {
        scheduleAt(simTime() + intervalTimer, s_msg);
    }
}


void RFIDGenericApp::sendMessageDown(cMessage *msg)
{
    EV << "RFID [" << id << "]: Send My ID."<< endl;
    simtime_t delay_timer;
    delay_timer = uniform(0, 0.01);
    sendDelayed(msg, delay_timer, "lowerLayerOut");
}

