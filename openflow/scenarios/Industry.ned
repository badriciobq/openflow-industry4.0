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
import openflow.factory.NodeFactory;
import openflow.nodes.Open_Flow_Controller;
import openflow.nodes.Open_Flow_Switch;
import openflow.nodes.RFIDTagNode;
import openflow.nodes.SensorNode;


network industry4
{
    types:
        channel ethernetWire extends ThruputMeteringChannel
        {
            delay = 1us;
            datarate = 100Mbps;
            //thruputDisplayFormat = "u";
        }

    submodules:

        factory: NodeFactory {
            parameters:
                @display("p=52,154;i=misc/globe;is=s");
        }

        channelControl: ChannelControl {
            parameters:
                @display("p=52,26");
        }

        configurator: FlatNetworkConfigurator {
            parameters:
                @display("p=52,86");
        }

        client: StandardHost {
            @display("p=867,28;i=abstract/people2");
        }

        supplier: StandardHost {
            @display("p=875,117;i=misc/town2");
        }

        gateway: Open_Flow_Switch {
            @display("p=752,86;i=device/router");
        }

		// Linha de produção 2
        RFIDWeigth: SensorNode {
            parameters:
                @display("p=667,334;i=rfid_tag;is=vs");
        }

        RFIDSize: SensorNode {
            parameters:
                @display("p=556,334;i=rfid_tag;is=vs");
        }

        RFIDProduct: SensorNode {
            parameters:
                @display("p=563,240;i=rfid_tag;is=vs");
        }

        switch2: Open_Flow_Switch {
            @display("p=649,162");
        }

        // Linha de produção 2

        RFIDWeigthP0: SensorNode {
            parameters:
                @display("p=180,334;i=rfid_tag;is=vs");
        }

        RFIDSizeP0: SensorNode {
            parameters:
                @display("p=95,334;i=rfid_tag;is=vs");
        }

        RFIDProductP0: SensorNode {
            parameters:
                @display("p=110,240;i=rfid_tag;is=vs");
        }

        switch3: Open_Flow_Switch {
            @display("p=325,162");
        }

        controller: Open_Flow_Controller {
            @display("p=556,29");
        }

        server: StandardHost {
            @display("p=276,50");
        }


    connections allowunconnected:
        // Sensores
        RFIDWeigth.ethg++ <--> ethernetWire <--> switch2.ethg++;
        RFIDSize.ethg++ <--> ethernetWire <--> switch2.ethg++;
        RFIDProduct.ethg++ <--> ethernetWire <--> switch2.ethg++;

        RFIDWeigthP0.ethg++ <--> ethernetWire <--> switch3.ethg++;
        RFIDSizeP0.ethg++ <--> ethernetWire <--> switch3.ethg++;
        RFIDProductP0.ethg++ <--> ethernetWire <--> switch3.ethg++;


        // Controller
        controller.ethg++ <--> ethernetWire <--> switch2.gate_controller++;
        controller.ethg++ <--> ethernetWire <--> gateway.gate_controller++;
        controller.ethg++ <--> ethernetWire <--> switch3.gate_controller++;

        gateway.ethg++ <--> ethernetWire <--> switch2.ethg++;
        gateway.ethg++ <--> ethernetWire <--> supplier.ethg++;
        gateway.ethg++ <--> ethernetWire <--> client.ethg++;
        //client.ethg++ <--> ethernetWire <--> switch2.ethg++;

		// Server que será o controler da fábrica
        server.ethg++ <--> ethernetWire <--> switch2.ethg++;
        switch3.ethg++ <--> ethernetWire <--> switch2.ethg++;
}
