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

#ifndef __OPENFLOW_SENSORAPP_H_
#define __OPENFLOW_SENSORAPP_H_

#include "INETDefs.h"

#include "TCPAppBase.h"
#include "NodeStatus.h"
#include "ILifecycle.h"

#include "TypeMessages.h"
#include "RFID_Message_m.h"

#include <deque>
#include <set>

/**An example request-reply based client application.
 */
class INET_API SensorApp : public TCPAppBase, public ILifecycle
{
  protected:
    bool isAnSession;
    cMessage *timeOutMess;
    NodeStatus *nodeStatus;
    bool earlySend;  // if true, don't wait with sendRequest() until established()
    int numRequestsToSend; // requests to send in this session
    simtime_t startTime;
    simtime_t stopTime;

    /** Utility: sends a request to the server */
    virtual void sendRequest();

    /** Utility: cancel msgTimer and if d is smaller than stopTime, then schedule it to d,
     * otherwise delete msgTimer */
    virtual void rescheduleTimer(simtime_t d, short int msgKind);

  public:
    SensorApp();
    virtual ~SensorApp();
    virtual bool handleOperationStage(LifecycleOperation *operation, int stage, IDoneCallback *doneCallback);
    virtual void pushBuffer(int id);
    virtual int popBuffer();
    virtual bool isBufferEmpty();

    enum sensor_kind{
        SENSOR_PRODUCT = 0,
        SENSOR_WEIGTH,
        SENSOR_SIZE,
    };

  protected:
    virtual int numInitStages() const { return 4; }

    /** Redefined . */
    virtual void initialize(int stage);

    /** Redefined. */
    virtual void handleTimer(cMessage *msg);

    /** Redefined. */
    virtual void socketEstablished(int connId, void *yourPtr);

    /** Redefined. */
    virtual void socketDataArrived(int connId, void *yourPtr, cPacket *msg, bool urgent);

    /** Redefined to start another session after a delay. */
    virtual void socketClosed(int connId, void *yourPtr);

    /** Redefined to reconnect after a delay. */
    virtual void socketFailure(int connId, void *yourPtr, int code);

    virtual bool isNodeUp();

  private:
    std::deque<int> m_buffer;
    std::set<int> m_history;

};


#endif

