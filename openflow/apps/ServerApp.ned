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
        
        // Fabrica 
        @signal[man_inventory](type=int);
        @signal[man_demmand](type=int);
        @statistic[man_inventory](title="manufacture inventory"; source=man_inventory; record=vector,histogram; interpolationmode=none);
        @statistic[man_demmand](title="manufacture demmand"; source=man_demmand; record=vector,histogram; interpolationmode=none);
        
        // Linha de produção zero
        @signal[lin_0_inventory](type=int);
        @signal[lin_0_demmand](type=int);
        
        @statistic[lin_0_inventory](title="linha zero inventory"; source=lin_0_inventory; record=vector,histogram; interpolationmode=none);
        @statistic[lin_0_demmand](title="linha zero demmand"; source=lin_0_demmand; record=vector,histogram; interpolationmode=none);
        
        @signal[lin_0_prodDone](type=GenericAppMsg);
        @signal[lin_0_prodProblem](type=GenericAppMsg);
        @signal[lin_0_prodStarts](type=GenericAppMsg);
        
        @statistic[lin_0_prodDone](title="produtos concluídos"; source=lin_0_prodDone; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        @statistic[lin_0_prodProblem](title="produtos concluídos"; source=lin_0_prodProblem; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        @statistic[lin_0_prodStarts](title="produtos concluídos"; source=lin_0_prodStarts; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        
        // Linha de produção um
        @signal[lin_1_inventory](type=int);
        @signal[lin_1_demmand](type=int);
        
        @statistic[lin_1_inventory](title="linha zero inventory"; source=lin_1_inventory; record=vector,histogram; interpolationmode=none);
        @statistic[lin_1_demmand](title="linha zero demmand"; source=lin_1_demmand; record=vector,histogram; interpolationmode=none);
        
        @signal[lin_1_prodDone](type=GenericAppMsg);
        @signal[lin_1_prodProblem](type=GenericAppMsg);
        @signal[lin_1_prodStarts](type=GenericAppMsg);
        
        @statistic[lin_1_prodDone](title="produtos concluídos"; source=lin_1_prodDone; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        @statistic[lin_1_prodProblem](title="produtos concluídos"; source=lin_1_prodProblem; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        @statistic[lin_1_prodStarts](title="produtos concluídos"; source=lin_1_prodStarts; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        
    gates:
        input tcpIn @labels(TCPCommand/up);
        output tcpOut @labels(TCPCommand/down);
}