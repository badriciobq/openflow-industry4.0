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

#ifndef __OPENFLOW_NODEFACTORY_H_
#define __OPENFLOW_NODEFACTORY_H_

#include <omnetpp.h>
#include <string>
#include <map>

/**
 * TODO - Generated class
 */
class NodeFactory : public cSimpleModule
{
  public:
    NodeFactory();
    ~NodeFactory();
    virtual int numInitStages() const { return 2; } ;
    virtual void initialize(int stage);
    virtual void handleMessage(cMessage *msg);
    void createNode();
    void deleteNode(long);
    cModule *getNode(long);
    void setDemand(int demmand);

  private:
    int nextNodeId;
    int m_demmand;
    double intervalTime;
    cMessage *timeoutMsg;
    std::map<long, cModule*> nodes;
};

#endif
