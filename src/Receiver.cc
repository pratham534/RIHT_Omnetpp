
#include <omnetpp.h>
#include "RIHTPacket_m.h"
#include "RIHTReconstructionPacket_m.h"

using namespace omnetpp;

class Receiver : public omnetpp::cSimpleModule
{
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Receiver);

void Receiver::initialize()
{
    // TODO - Generated method body
    EV << "Receiver Initialized!" << "\n";
}

void Receiver::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    if (msg->isSelfMessage()) {
        // Handle self messages (timeouts, etc.)
        return;
    }
    RIHTPacket *packet = check_and_cast<RIHTPacket *>(msg);
    EV << "Packet Received from src: " << packet->getSrcAddress() << "\n";
    EV << "Received message: Mark-" << packet->getMark() << " UI-"<< packet->getUI()<< "\n";

    int UI = packet->getArrivalGate()->getIndex();
    RIHTReconstructionPacket *repacket = new RIHTReconstructionPacket();
    repacket->setMarkReq(packet->getMark());

    sendDelayed(repacket, 4, gate("ethg$o", UI));

}
