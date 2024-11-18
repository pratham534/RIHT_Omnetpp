#include <omnetpp.h>
#include "inet/networklayer/contract/IRoutingTable.h"
#include "inet/networklayer/ipv4/IPv4RoutingTable.h"
#include "RIHTPacket_m.h"

using namespace omnetpp;
using namespace inet;

class MyRoutingProtocol : public cSimpleModule {
  private:
    IRoutingTable *routingTable;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void setupRoutingTable();
    int getOutgoingInterface(RIHTPacket *packet, int upstreamInterface);
};

Define_Module(MyRoutingProtocol);

void MyRoutingProtocol::initialize() {
    routingTable = getModuleFromPar<IRoutingTable>(par("routingTableModule"), this);
    setupRoutingTable();
}

void MyRoutingProtocol::handleMessage(cMessage *msg) {
    RIHTPacket *packet = check_and_cast<RIHTPacket *>(msg);
    int upstreamInterface = packet->getArrivalGate()->getIndex();

    // Determine the outgoing interface based on the packet’s mark or other criteria
    int outgoingInterface = getOutgoingInterface(packet, upstreamInterface);

    EV << "Routing packet from interface " << upstreamInterface
       << " to interface " << outgoingInterface << "\n";

    // Forward the packet to the selected outgoing interface
    send(msg, "lowerLayerOut", outgoingInterface);
}

void MyRoutingProtocol::setupRoutingTable() {
    // Example: Adding static routes (this can be extended with dynamic routing logic)
    IPv4Route *route = new IPv4Route();
    route->setDestination(Ipv4Address("192.168.0.6"));
    route->setNetmask(Ipv4Address::ALLONES_ADDRESS);
    route->setGateway(Ipv4Address("192.168.0.1"));
    route->setInterface(routingTable->getInterfaceByName("eth0"));
    routingTable->addRoute(route);
}

int MyRoutingProtocol::getOutgoingInterface(RIHTPacket *packet, int upstreamInterface) {
    // Example decision based on upstream interface and packet mark
    int mark = packet->getMark();
    return (mark + upstreamInterface) % gateSize("lowerLayerOut");
}
