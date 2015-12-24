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

#ifndef __OPENFLOW_DYNAMICRECTABLEMOBILITY_H_
#define __OPENFLOW_DYNAMICRECTABLEMOBILITY_H_

#include "INETDefs.h"

#include <RectangleMobility.h>
#include <simtime_t.h>
#include <map>

/**
 * TODO - Generated class
 */
class INET_API DynamicRectableMobility : public RectangleMobility
{
  public:
    bool registerNode(long id);
    bool unregisterNode(long id);


  protected:
    virtual int numInitStages() const { return 3; }
    virtual void initialize(int stage);
    virtual void move();

  private:
    std::map<long, double> initial_times;

};

#endif
