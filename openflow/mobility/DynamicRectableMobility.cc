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

#include "DynamicRectableMobility.h"

Define_Module(DynamicRectableMobility);

void DynamicRectableMobility::initialize(int stage)
{
    RectangleMobility::initialize(stage);

    EV_TRACE << "initializing DynamicRectableMobility stage " << stage << endl;
}

bool DynamicRectableMobility::registerNode(long id)
{
    if(initial_times.find(id) == initial_times.end())
        return false;

    EV << "BAD: ELEMENTO REGISTRADO" << endl << endl;

    initial_times[id] = simTime().dbl();
    return true;
}

bool DynamicRectableMobility::unregisterNode(long id)
{
    if(initial_times.find(id) == initial_times.end())
        return false;

    initial_times.erase(initial_times.find(id));
    return true;
}


void DynamicRectableMobility::move()
{
    double elapsedTime = 0;//(simTime() - lastUpdate).dbl()  - initial_times.find(id)->second;
    d += speed * elapsedTime;

    while (d < 0)
        d += corner4;

    while (d >= corner4)
        d -= corner4;

    if (d < corner1)
    {
        // top side
        lastPosition.x = constraintAreaMin.x + d;
        lastPosition.y = constraintAreaMin.y;
    }
    else if (d < corner2)
    {
        // right side
        lastPosition.x = constraintAreaMax.x;
        lastPosition.y = constraintAreaMin.y + d - corner1;
    }
    else if (d < corner3)
    {
        // bottom side
        lastPosition.x = constraintAreaMax.x - d + corner2;
        lastPosition.y = constraintAreaMax.y;
    }
    else
    {
        // left side
        lastPosition.x = constraintAreaMin.x;
        lastPosition.y = constraintAreaMax.y - d + corner3;
    }
}
