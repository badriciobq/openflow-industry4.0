#
# OMNeT++/OMNEST Makefile for openflow
#
# This file was generated with the command:
#  opp_makemake -f --deep -O out -I/Users/mauriciosilva/Documents/workspace/omnetpp/inet/src/transport/tcp/queues -I/Users/mauriciosilva/Documents/workspace/omnetpp/inet/src/transport/tcp_common -I/Users/mauriciosilva/Documents/workspace/omnetpp/inet/src/base -I/Users/mauriciosilva/Documents/workspace/omnetpp/inet/src/util -I/Users/mauriciosilva/Documents/workspace/omnetpp/inet/src/transport/udp -I/Users/mauriciosilva/Documents/workspace/omnetpp/inet/src/transport/tcp -I/Users/mauriciosilva/Documents/workspace/omnetpp/inet/src/util/headerserializers -I/Users/mauriciosilva/Documents/workspace/omnetpp/inet/src/status -I/Users/mauriciosilva/Documents/workspace/omnetpp/inet/src/transport/sctp -I/Users/mauriciosilva/Documents/workspace/omnetpp/inet/src/networklayer/icmpv6 -I/Users/mauriciosilva/Documents/workspace/omnetpp/inet/src/transport/contract -I/Users/mauriciosilva/Documents/workspace/omnetpp/inet/src/mobility/static -I/Users/mauriciosilva/Documents/workspace/omnetpp/inet/src/networklayer/ipv6tunneling -I/Users/mauriciosilva/Documents/workspace/omnetpp/inet/src/linklayer/contract -I/Users/mauriciosilva/Documents/workspace/omnetpp/inet/src/util/headerserializers/udp -I/Users/mauriciosilva/Documents/workspace/omnetpp/inet/src/util/headerserializers/tcp -I/Users/mauriciosilva/Documents/workspace/omnetpp/inet/src/networklayer/common -I/Users/mauriciosilva/Documents/workspace/omnetpp/inet/src/linklayer/ethernet -I/Users/mauriciosilva/Documents/workspace/omnetpp/inet/src/networklayer/ipv6 -I/Users/mauriciosilva/Documents/workspace/omnetpp/inet/src/networklayer/arp -I/Users/mauriciosilva/Documents/workspace/omnetpp/inet/src/networklayer/contract -I/Users/mauriciosilva/Documents/workspace/omnetpp/inet/src -I/Users/mauriciosilva/Documents/workspace/omnetpp/inet/src/networklayer/xmipv6 -I/Users/mauriciosilva/Documents/workspace/omnetpp/inet/src/util/headerserializers/sctp -I/Users/mauriciosilva/Documents/workspace/omnetpp/inet/src/mobility/common -I/Users/mauriciosilva/Documents/workspace/omnetpp/inet/src/util/headerserializers/ipv6 -I/Users/mauriciosilva/Documents/workspace/omnetpp/inet/src/applications/tcpapp -I/Users/mauriciosilva/Documents/workspace/omnetpp/inet/src/networklayer/autorouting/ipv4 -I/Users/mauriciosilva/Documents/workspace/omnetpp/inet/src/networklayer/ipv4 -I/Users/mauriciosilva/Documents/workspace/omnetpp/inet/src/applications/pingapp -I/Users/mauriciosilva/Documents/workspace/omnetpp/inet/src/mobility/contract -I/Users/mauriciosilva/Documents/workspace/omnetpp/inet/src/linklayer/common -I/Users/mauriciosilva/Documents/workspace/omnetpp/inet/src/util/headerserializers/ipv4 -I/Users/mauriciosilva/Documents/workspace/omnetpp/inet/src/mobility/single -L/Users/mauriciosilva/Documents/workspace/omnetpp/inet/out/$$\(CONFIGNAME\)/src -linet -DINET_IMPORT -KINET_PROJ=/Users/mauriciosilva/Documents/workspace/omnetpp/inet
#

# Name of target to be created (-o option)
TARGET = openflow$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I$(INET_PROJ)/src/transport/tcp/queues \
    -I$(INET_PROJ)/src/transport/tcp_common \
    -I$(INET_PROJ)/src/base \
    -I$(INET_PROJ)/src/util \
    -I$(INET_PROJ)/src/transport/udp \
    -I$(INET_PROJ)/src/transport/tcp \
    -I$(INET_PROJ)/src/util/headerserializers \
    -I$(INET_PROJ)/src/status \
    -I$(INET_PROJ)/src/transport/sctp \
    -I$(INET_PROJ)/src/networklayer/icmpv6 \
    -I$(INET_PROJ)/src/transport/contract \
    -I$(INET_PROJ)/src/mobility/static \
    -I$(INET_PROJ)/src/networklayer/ipv6tunneling \
    -I$(INET_PROJ)/src/linklayer/contract \
    -I$(INET_PROJ)/src/util/headerserializers/udp \
    -I$(INET_PROJ)/src/util/headerserializers/tcp \
    -I$(INET_PROJ)/src/networklayer/common \
    -I$(INET_PROJ)/src/linklayer/ethernet \
    -I$(INET_PROJ)/src/networklayer/ipv6 \
    -I$(INET_PROJ)/src/networklayer/arp \
    -I$(INET_PROJ)/src/networklayer/contract \
    -I$(INET_PROJ)/src \
    -I$(INET_PROJ)/src/networklayer/xmipv6 \
    -I$(INET_PROJ)/src/util/headerserializers/sctp \
    -I$(INET_PROJ)/src/mobility/common \
    -I$(INET_PROJ)/src/util/headerserializers/ipv6 \
    -I$(INET_PROJ)/src/applications/tcpapp \
    -I$(INET_PROJ)/src/networklayer/autorouting/ipv4 \
    -I$(INET_PROJ)/src/networklayer/ipv4 \
    -I$(INET_PROJ)/src/applications/pingapp \
    -I$(INET_PROJ)/src/mobility/contract \
    -I$(INET_PROJ)/src/linklayer/common \
    -I$(INET_PROJ)/src/util/headerserializers/ipv4 \
    -I$(INET_PROJ)/src/mobility/single \
    -I. \
    -Iapps \
    -IctrlApps \
    -Ifactory \
    -Iimages \
    -Imessages \
    -Imobility \
    -Inodes \
    -Iscenarios \
    -Iscenarios/results \
    -Iscenarios/results/Industry.ini \
    -Iutility

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = -L$(INET_PROJ)/out/$(CONFIGNAME)/src  -linet
LIBS += -Wl,-rpath,`abspath $(INET_PROJ)/out/$(CONFIGNAME)/src`

# Output directory
PROJECT_OUTPUT_DIR = out
PROJECTRELATIVE_PATH =
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/Buffer.o \
    $O/Flow_Table.o \
    $O/OF_Wrapper.o \
    $O/OFA_controller.o \
    $O/OFA_switch.o \
    $O/Open_Flow_Processing.o \
    $O/apps/ClientApp.o \
    $O/apps/PingAppRandom.o \
    $O/apps/RFIDGenericApp.o \
    $O/apps/SensorApp.o \
    $O/apps/ServerApp.o \
    $O/apps/SupplierApp.o \
    $O/ctrlApps/Forwarding.o \
    $O/ctrlApps/Hub.o \
    $O/ctrlApps/Switch.o \
    $O/factory/nodeFactory.o \
    $O/mobility/DynamicRectableMobility.o \
    $O/utility/kPartitionNetwork.o \
    $O/utility/placeController.o \
    $O/utility/SpanningTree.o \
    $O/messages/OFP_Features_Reply_m.o \
    $O/messages/OFP_Features_Request_m.o \
    $O/messages/OFP_Flow_Mod_m.o \
    $O/messages/OFP_Packet_In_m.o \
    $O/messages/OFP_Packet_Out_m.o \
    $O/messages/Open_Flow_Message_m.o \
    $O/messages/RFID_Message_m.o

# Message files
MSGFILES = \
    messages/OFP_Features_Reply.msg \
    messages/OFP_Features_Request.msg \
    messages/OFP_Flow_Mod.msg \
    messages/OFP_Packet_In.msg \
    messages/OFP_Packet_Out.msg \
    messages/Open_Flow_Message.msg \
    messages/RFID_Message.msg

# Other makefile variables (-K)
INET_PROJ=/Users/mauriciosilva/Documents/workspace/omnetpp/inet

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS) -DINET_IMPORT $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $O/$(TARGET)
	$(Q)$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	@echo Creating executable: $@
	$(Q)$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY: all clean cleanall depend msgheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f openflow openflow.exe libopenflow.so libopenflow.a libopenflow.dll libopenflow.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h
	$(Q)-rm -f apps/*_m.cc apps/*_m.h
	$(Q)-rm -f ctrlApps/*_m.cc ctrlApps/*_m.h
	$(Q)-rm -f factory/*_m.cc factory/*_m.h
	$(Q)-rm -f images/*_m.cc images/*_m.h
	$(Q)-rm -f messages/*_m.cc messages/*_m.h
	$(Q)-rm -f mobility/*_m.cc mobility/*_m.h
	$(Q)-rm -f nodes/*_m.cc nodes/*_m.h
	$(Q)-rm -f scenarios/*_m.cc scenarios/*_m.h
	$(Q)-rm -f scenarios/results/*_m.cc scenarios/results/*_m.h
	$(Q)-rm -f scenarios/results/Industry.ini/*_m.cc scenarios/results/Industry.ini/*_m.h
	$(Q)-rm -f utility/*_m.cc utility/*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc apps/*.cc ctrlApps/*.cc factory/*.cc images/*.cc messages/*.cc mobility/*.cc nodes/*.cc scenarios/*.cc scenarios/results/*.cc scenarios/results/Industry.ini/*.cc utility/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/Buffer.o: Buffer.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	Buffer.h \
	openflow.h
$O/Flow_Table.o: Flow_Table.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/arp/ARPPacket_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	Flow_Table.h \
	openflow.h
$O/OFA_controller.o: OFA_controller.cc \
	$(INET_PROJ)/src/applications/tcpapp/GenericAppMsg_m.h \
	$(INET_PROJ)/src/base/ByteArray.h \
	$(INET_PROJ)/src/base/ByteArray_m.h \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/ILifecycle.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/INotifiable.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/base/NotificationBoard.h \
	$(INET_PROJ)/src/base/NotifierConsts.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/autorouting/ipv4/FlatNetworkConfigurator.h \
	$(INET_PROJ)/src/networklayer/common/IInterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPv4Route.h \
	$(INET_PROJ)/src/networklayer/ipv4/IRoutingTable.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	$(INET_PROJ)/src/transport/tcp/TCP.h \
	$(INET_PROJ)/src/transport/tcp/TCPConnection.h \
	$(INET_PROJ)/src/transport/tcp_common/TCPSegment.h \
	$(INET_PROJ)/src/transport/tcp_common/TCPSegment_m.h \
	OFA_controller.h \
	OF_Wrapper.h \
	ctrlApps/Forwarding.h \
	ctrlApps/Hub.h \
	ctrlApps/Switch.h \
	messages/OFP_Features_Reply_m.h \
	messages/OFP_Features_Request_m.h \
	messages/OFP_Flow_Mod_m.h \
	messages/OFP_Packet_In_m.h \
	messages/OFP_Packet_Out_m.h \
	messages/Open_Flow_Message_m.h \
	openflow.h
$O/OFA_switch.o: OFA_switch.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/INotifiable.h \
	$(INET_PROJ)/src/base/NotifierConsts.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/arp/ARPPacket_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPProtocolId_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddressResolver.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPv4Datagram.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPv4Datagram_m.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	Buffer.h \
	Flow_Table.h \
	OFA_switch.h \
	OF_Wrapper.h \
	Open_Flow_Processing.h \
	messages/OFP_Features_Reply_m.h \
	messages/OFP_Flow_Mod_m.h \
	messages/OFP_Packet_In_m.h \
	messages/OFP_Packet_Out_m.h \
	messages/Open_Flow_Message_m.h \
	openflow.h
$O/OF_Wrapper.o: OF_Wrapper.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	OF_Wrapper.h \
	messages/Open_Flow_Message_m.h \
	openflow.h
$O/Open_Flow_Processing.o: Open_Flow_Processing.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/INotifiable.h \
	$(INET_PROJ)/src/base/NotifierConsts.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/arp/ARPPacket_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPProtocolId_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPv4Datagram.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPv4Datagram_m.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	Buffer.h \
	Flow_Table.h \
	OF_Wrapper.h \
	Open_Flow_Processing.h \
	messages/Open_Flow_Message_m.h \
	openflow.h
$O/apps/ClientApp.o: apps/ClientApp.cc \
	$(INET_PROJ)/src/applications/tcpapp/GenericAppMsg_m.h \
	$(INET_PROJ)/src/applications/tcpapp/TCPAppBase.h \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/ILifecycle.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/LifecycleOperation.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/base/NodeOperations.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/status/NodeStatus.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	apps/ClientApp.h \
	apps/TypeMessages.h \
	messages/RFID_Message_m.h
$O/apps/PingAppRandom.o: apps/PingAppRandom.cc \
	$(INET_PROJ)/src/applications/pingapp/PingPayload_m.h \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPProtocolId_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4ControlInfo.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4ControlInfo_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6ControlInfo.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6ControlInfo_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddressResolver.h \
	apps/PingAppRandom.h
$O/apps/RFIDGenericApp.o: apps/RFIDGenericApp.cc \
	$(INET_PROJ)/src/applications/tcpapp/TCPAppBase.h \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/ILifecycle.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/status/NodeStatus.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	apps/RFIDGenericApp.h \
	apps/SensorApp.h \
	apps/TypeMessages.h \
	messages/RFID_Message_m.h
$O/apps/SensorApp.o: apps/SensorApp.cc \
	$(INET_PROJ)/src/applications/tcpapp/GenericAppMsg_m.h \
	$(INET_PROJ)/src/applications/tcpapp/TCPAppBase.h \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/ILifecycle.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/LifecycleOperation.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/base/NodeOperations.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/status/NodeStatus.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	apps/SensorApp.h \
	apps/TypeMessages.h \
	messages/RFID_Message_m.h
$O/apps/ServerApp.o: apps/ServerApp.cc \
	$(INET_PROJ)/src/applications/tcpapp/GenericAppMsg_m.h \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/ILifecycle.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/LifecycleOperation.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddressResolver.h \
	$(INET_PROJ)/src/status/NodeStatus.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	apps/ServerApp.h \
	factory/nodeFactory.h
$O/apps/SupplierApp.o: apps/SupplierApp.cc \
	$(INET_PROJ)/src/applications/tcpapp/GenericAppMsg_m.h \
	$(INET_PROJ)/src/applications/tcpapp/TCPAppBase.h \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/ILifecycle.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/LifecycleOperation.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/base/NodeOperations.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/status/NodeStatus.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	apps/SupplierApp.h \
	apps/TypeMessages.h \
	messages/RFID_Message_m.h
$O/ctrlApps/Forwarding.o: ctrlApps/Forwarding.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/ILifecycle.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/INotifiable.h \
	$(INET_PROJ)/src/base/IPassiveQueue.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/base/NotificationBoard.h \
	$(INET_PROJ)/src/base/NotifierConsts.h \
	$(INET_PROJ)/src/linklayer/common/MACBase.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherMAC.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherMACBase.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/arp/ARPPacket_m.h \
	$(INET_PROJ)/src/networklayer/autorouting/ipv4/FlatNetworkConfigurator.h \
	$(INET_PROJ)/src/networklayer/common/IInterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/networklayer/contract/IPProtocolId_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddressResolver.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPv4Datagram.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPv4Datagram_m.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPv4Route.h \
	$(INET_PROJ)/src/networklayer/ipv4/IRoutingTable.h \
	$(INET_PROJ)/src/status/NodeStatus.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	OFA_controller.h \
	OF_Wrapper.h \
	ctrlApps/Forwarding.h \
	messages/OFP_Packet_In_m.h \
	messages/Open_Flow_Message_m.h \
	openflow.h
$O/ctrlApps/Hub.o: ctrlApps/Hub.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	OFA_controller.h \
	OF_Wrapper.h \
	ctrlApps/Hub.h \
	messages/OFP_Packet_In_m.h \
	messages/Open_Flow_Message_m.h \
	openflow.h
$O/ctrlApps/Switch.o: ctrlApps/Switch.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	OFA_controller.h \
	OF_Wrapper.h \
	ctrlApps/Switch.h \
	messages/OFP_Packet_In_m.h \
	messages/Open_Flow_Message_m.h \
	openflow.h
$O/factory/nodeFactory.o: factory/nodeFactory.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/mobility/common/MobilityBase.h \
	$(INET_PROJ)/src/mobility/common/MovingMobilityBase.h \
	$(INET_PROJ)/src/mobility/contract/IMobility.h \
	$(INET_PROJ)/src/mobility/single/RectangleMobility.h \
	$(INET_PROJ)/src/util/FWMath.h \
	factory/nodeFactory.h \
	mobility/DynamicRectableMobility.h
$O/messages/OFP_Features_Reply_m.o: messages/OFP_Features_Reply_m.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	messages/OFP_Features_Reply_m.h \
	messages/Open_Flow_Message_m.h \
	openflow.h
$O/messages/OFP_Features_Request_m.o: messages/OFP_Features_Request_m.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	messages/OFP_Features_Request_m.h \
	messages/Open_Flow_Message_m.h \
	openflow.h
$O/messages/OFP_Flow_Mod_m.o: messages/OFP_Flow_Mod_m.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	messages/OFP_Flow_Mod_m.h \
	messages/Open_Flow_Message_m.h \
	openflow.h
$O/messages/OFP_Packet_In_m.o: messages/OFP_Packet_In_m.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	messages/OFP_Packet_In_m.h \
	messages/Open_Flow_Message_m.h \
	openflow.h
$O/messages/OFP_Packet_Out_m.o: messages/OFP_Packet_Out_m.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	messages/OFP_Packet_Out_m.h \
	messages/Open_Flow_Message_m.h \
	openflow.h
$O/messages/Open_Flow_Message_m.o: messages/Open_Flow_Message_m.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	messages/Open_Flow_Message_m.h \
	openflow.h
$O/messages/RFID_Message_m.o: messages/RFID_Message_m.cc \
	messages/RFID_Message_m.h
$O/mobility/DynamicRectableMobility.o: mobility/DynamicRectableMobility.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/mobility/common/MobilityBase.h \
	$(INET_PROJ)/src/mobility/common/MovingMobilityBase.h \
	$(INET_PROJ)/src/mobility/contract/IMobility.h \
	$(INET_PROJ)/src/mobility/single/RectangleMobility.h \
	$(INET_PROJ)/src/util/FWMath.h \
	mobility/DynamicRectableMobility.h
$O/utility/SpanningTree.o: utility/SpanningTree.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/INotifiable.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/arp/ARPPacket_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPProtocolId_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPv4Datagram.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPv4Datagram_m.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	Buffer.h \
	Flow_Table.h \
	OF_Wrapper.h \
	Open_Flow_Processing.h \
	messages/Open_Flow_Message_m.h \
	openflow.h \
	utility/SpanningTree.h
$O/utility/kPartitionNetwork.o: utility/kPartitionNetwork.cc \
	utility/kPartitionNetwork.h
$O/utility/placeController.o: utility/placeController.cc \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/INotifiable.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/networklayer/arp/ARPPacket_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPProtocolId_m.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPv4Datagram.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPv4Datagram_m.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	Buffer.h \
	Flow_Table.h \
	OF_Wrapper.h \
	Open_Flow_Processing.h \
	messages/Open_Flow_Message_m.h \
	openflow.h \
	utility/placeController.h

