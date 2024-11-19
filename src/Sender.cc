
#include <omnetpp.h>
#include "RIHTPacket_m.h"

using namespace omnetpp;

class Sender: public omnetpp::cSimpleModule {
    protected:
        virtual void initialize() override;
        virtual void handleMessage(omnetpp::cMessage *msg) override;
};

Define_Module(Sender);

void Sender::initialize()
{
    // TODO - Generated method body
    EV << "Sender initialized\n";
    EV << "Sending packet...\n";
    const char* srcAddress = par("ipv4Address").stringValue();

    RIHTPacket *packet = new RIHTPacket();
    packet->setMark(0);
    packet->setUI(-1);
    packet->setSrcAddress(srcAddress); // Example source address
    packet->setDestAddress("192.168.0.6"); // Example destination address

    sendDelayed(packet, 1, gate("ethg$o", 0));
}

void Sender::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    if (msg->isSelfMessage()) {
        // Handle self messages (timeouts, etc.)
        return;
    }
    EV << "This is sender..\n";
}
