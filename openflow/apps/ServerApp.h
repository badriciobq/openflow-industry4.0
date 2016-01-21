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

#ifndef __OPENFLOW_SERVERAPP_H_
#define __OPENFLOW_SERVERAPP_H_

#include "INETDefs.h"
#include "ILifecycle.h"
#include "LifecycleOperation.h"
#include "GenericAppMsg_m.h"
#include "nodeFactory.h"

#include <set>
#include <map>

/**
 * Generic server application. It serves requests coming in GenericAppMsg
 * request messages. Clients are usually subclassed from TCPAppBase.
 *
 * @see GenericAppMsg, TCPAppBase
 */

typedef struct type_line_of_production{
    int product_inventory = 0;
    int product_demmand = 0;

    std::set<int> production_starts; // Produtos que entraram na linha de produção
    std::set<int> production_done; // Produtos produzidos com sucesso
    std::map<int, int> production_defect; // Produtos com defeito, armazenados em um map onde <id do produto, sensor que detectou o defeito>

} type_line_of_production;


class INET_API ServerApp : public cSimpleModule, public ILifecycle
{
  protected:
    simtime_t delay;
    simtime_t maxMsgDelay;

    long msgsRcvd;
    long msgsSent;
    long bytesRcvd;
    long bytesSent;

    //statistics:
    static simsignal_t rcvdPkSignal;
    static simsignal_t sentPkSignal;

    static simsignal_t prodDoneSignal;
    static simsignal_t prodProblemSignal;
    static simsignal_t prodStartsSignal;

  public:
    virtual bool handleOperationStage(LifecycleOperation *operation, int stage, IDoneCallback *doneCallback)
    { Enter_Method_Silent(); throw cRuntimeError("Unsupported lifecycle operation '%s'", operation->getClassName()); return true; }

    enum sensor_kind{
        SENSOR_PRODUCT = 0,
        SENSOR_WEIGTH,
        SENSOR_SIZE,
        SENSOR_PRODUCT_P0,
        SENSOR_WEIGTH_P0,
        SENSOR_SIZE_P0,
        CLIENT,
        SERVER,
        SUPPLIER
    };

  protected:
    virtual void sendBack(cMessage *msg);
    virtual void sendOrSchedule(cMessage *msg, simtime_t delay);

  protected:
    virtual void initialize(int stage);
    virtual int numInitStages() const { return 4; }
    virtual void handleMessage(cMessage *msg);
    virtual void finish();


  private:
    const int qtde_lines = 2;
    virtual void process_message(GenericAppMsg *msg);
    NodeFactory *Factory;

    // Armazena o estoque da fábrica
    int product_inventory;
    int product_demmand;

    // Armazena os dados de uma linha de produção
    type_line_of_production *lines_of_production;

};

#endif


