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

#include <ccomponenttype.h>
#include <cobjectfactory.h>
#include <cregistrationlist.h>
#include <factory/nodeFactory.h>
#include <regmacros.h>
#include <simutil.h>

#include "DynamicRectableMobility.h"

#define coreEV (ev.isDisabled()||!coreDebug) ? EV : EV << "NodeFactory: "

Define_Module(NodeFactory);


NodeFactory::NodeFactory()
{

}

NodeFactory::~NodeFactory()
{
}


void NodeFactory::initialize(int stage)
{
    nextNodeId = 0;
    intervalTime = par("intervalTime");

    if(stage != 1)
        return;

    timeoutMsg = NULL;
}

void NodeFactory::handleMessage(cMessage *msg)
{
    // TODO - Generated method body

    if(msg->isSelfMessage()){
        // Cria um novo nó a cada intervalo de tempo definido no .ini

        bool cancel = true;
        for(int i=0; i < qtde_lines; ++i)
        {
            if(m_demmand[i] > 0 )
            {
                createNode(i);
                cancel = false;
            }
        }

        if(cancel)
        {
            cancelAndDelete(timeoutMsg);
            timeoutMsg = NULL;
        }
        else
        {
            scheduleAt(simTime() + intervalTime, timeoutMsg);
        }
    }
}

void NodeFactory::createNode(int line)
{

    std::string type = par("nodeType");

    cModule* parentmod = getParentModule();
    if (!parentmod) error("Parent Module not found");

    cModuleType* nodeType = cModuleType::get(type.c_str());
    if (!nodeType) error("Module Type \"%s\" not found", type.c_str());

    int32_t nodeVectorIndex = nextNodeId++;

    char name[20];
    sprintf (name, "productP%d", line);

    cModule* mod = nodeType->create(name, parentmod, nodeVectorIndex, nodeVectorIndex);
    mod->finalizeParameters();
    mod->getDisplayString().parse("i=misc/node;is=vs");
    mod->buildInside();
    mod->scheduleStart(simTime());

    mod->callInitialize();

    nodes[nodeVectorIndex] = mod;

    // Incementa a demanda de produção de nós
    m_demmand[line]--;
}

void NodeFactory::deleteNode(long id)
{
    Enter_Method_Silent();

    cModule *mod = getNode(id);

    if (!mod)
        error("no vehicle with Id \"%d\" found", id);

    //cc->unregisterNic(mod->getSubmodule("nic"));

    nodes.erase(id);
    mod->callFinish();
    mod->deleteModule();
}

cModule *NodeFactory::getNode(long id)
{
    if(nodes.find(id) == nodes.end())
        return 0;

    return nodes[id];
}

void NodeFactory::setDemand(int demmand, int line)
{
    Enter_Method_Silent();

    m_demmand[line] += demmand;

    if(!timeoutMsg)
    {
        timeoutMsg = new cMessage("factory_node_timer");
        scheduleAt(simTime() + intervalTime, timeoutMsg);
    }
}

