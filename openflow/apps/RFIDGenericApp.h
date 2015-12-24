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

#ifndef __OPENFLOW_RFIDGENERICAPP_H_
#define __OPENFLOW_RFIDGENERICAPP_H_

#include <omnetpp.h>
#include "TypeMessages.h"
#include "SensorApp.h"

/**
 * TODO - Generated class
 */
class RFIDGenericApp : public cSimpleModule
{
public:
    RFIDGenericApp();
    ~RFIDGenericApp();

  protected:
    virtual int numInitStages() const { return 3; }
    virtual void initialize(int stage);
    virtual void handleMessage(cMessage *msg);
    virtual void scheduleSelfMessage();
    virtual void sendMessageDown(cMessage *msg);

  private:
    // Identificador único do nó
    int id;

    // Referência para os canais
    int lowerLayerOut;
    int lowerLayerIn;

    // Intervalo entre as Timer Messages
    double intervalTimer;

    // Timer Message
    cMessage *s_msg;

    bool isTag = false;

    SensorApp *AppSensor;
};

#endif
