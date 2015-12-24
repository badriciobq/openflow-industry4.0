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

package openflow.nodes;

import inet.base.NotificationBoard;
import inet.linklayer.ieee80211.radio.Ieee80211Radio;
import inet.mobility.contract.IMobility;
import openflow.apps.IRFIDApp;


module RFIDTagNode
{
    parameters:
        string mobilityType = default("RectangleMobility");
        @node;
        @display("i=misc/node2;is=s");

    gates:
        input radio @directIn;

    submodules:
        notificationBoard: NotificationBoard {
            parameters:
                @display("p=31,30;is=s");
        }

		// optional mobility module. Required only if wireless cards are present
        mobility: <mobilityType> like IMobility if mobilityType != "" {
            parameters:
                @display("p=31,84");
        }

        appRFID: <default("RFIDGenericApp")> like IRFIDApp {
            parameters:
                @display("p=154,44");
        }

        phyRFID: Ieee80211Radio {
            parameters:
                @display("p=154,148");
        }

    connections:
        radio --> { @display("m=s"); } --> phyRFID.radioIn;
        phyRFID.upperLayerIn <-- appRFID.lowerLayerOut;
        phyRFID.upperLayerOut --> appRFID.lowerLayerIn;
}
