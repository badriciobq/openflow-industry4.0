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

package openflow.apps;

import inet.applications.ITCPApp;


simple ServerApp like ITCPApp
{
    parameters:
        string localAddress = default(""); // local address; may be left empty ("")
        int localPort = default(1000);     // localPort number to listen on
        double replyDelay @unit(s) = default(0s);
        @display("i=block/app");
        
        @signal[sentPk](type=GenericAppMsg);
        @signal[rcvdPk](type=GenericAppMsg);
        @statistic[rcvdPk](title="packets received"; source=rcvdPk; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        @statistic[sentPk](title="packets sent"; source=sentPk; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        @statistic[endToEndDelay](title="end-to-end delay"; source="messageAge(rcvdPk)"; unit=s; record=histogram,vector; interpolationmode=none);
        
        @signal[prodDone](type=GenericAppMsg);
        @signal[prodProblem](type=GenericAppMsg);
        @signal[prodStarts](type=GenericAppMsg);
        @statistic[prodDone](title="produtos concluídos"; source=prodDone; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        @statistic[prodProblem](title="produtos concluídos"; source=prodProblem; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        @statistic[prodStarts](title="produtos concluídos"; source=prodStarts; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        
    gates:
        input tcpIn @labels(TCPCommand/up);
        output tcpOut @labels(TCPCommand/down);
}