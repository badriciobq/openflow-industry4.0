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

package openflow.scenarios;


import inet.networklayer.autorouting.ipv4.FlatNetworkConfigurator;
import inet.nodes.inet.StandardHost;
import inet.util.ThruputMeteringChannel;
import inet.world.radio.ChannelControl;
import openflow.nodes.Open_Flow_Controller;
import openflow.nodes.Open_Flow_Switch;
import openflow.nodes.RFIDTagNode;
import openflow.nodes.SensorNode;


network teste
{
    types:
        channel ethernetWire extends ThruputMeteringChannel
        {
            delay = 1us;
            datarate = 100Mbps;
            thruputDisplayFormat = "u";
        }

    submodules:
        channelControl: ChannelControl {
            parameters:
                @display("p=52,26");
        }

	
        configurator: FlatNetworkConfigurator {
            parameters:
                @display("p=52,86");
        }
        
        product1: RFIDTagNode {
            @display("p=125,205");
        }

        product2: RFIDTagNode {
            @display("p=193,181");
        }
        

}
