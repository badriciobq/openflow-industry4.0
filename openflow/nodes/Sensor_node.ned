
package openflow.nodes;

import inet.linklayer.ieee80211.radio.Ieee80211Radio;
import inet.nodes.inet.WirelessHost;
import openflow.apps.IRFIDApp;


module SensorNode extends WirelessHost
{
    parameters:
        @display("i=device/accesspoint");
        numRadios = default(0);

    gates:
        input radio @directIn;

    submodules:

        appRFID: <default("RFIDGenericApp")> like IRFIDApp {
            parameters:
                @display("p=686,307");
        }

        phyRFID: Ieee80211Radio {
            parameters:
                @display("p=686,387");
        }

    connections:
        radio --> { @display("m=s"); } --> phyRFID.radioIn;
        phyRFID.upperLayerIn <-- appRFID.lowerLayerOut;
        phyRFID.upperLayerOut --> appRFID.lowerLayerIn;
}
