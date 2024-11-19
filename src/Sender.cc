
#include <omnetpp.h>
#include "RIHTPacket_m.h"

using namespace omnetpp;

class Sender: public omnetpp::cSimpleModule {
private:
    cMessage *sendTimer;
    protected:
        virtual void initialize() override;
        virtual void handleMessage(omnetpp::cMessage *msg) override;
        virtual void sendPacket();
};

Define_Module(Sender);

void Sender::initialize()
{
    EV << "Sender initialized\n";
    EV << "Sending packet...\n";

    std::string senderAddress = par("ipv4Address").stringValue();
    if(senderAddress == "192.168.0.7"){
        sendTimer = new cMessage("sendTimer");
        scheduleAt(simTime() + 0.3, sendTimer);
    }else{
        sendPacket();
    }
}

void Sender::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
//    if (msg->isSelfMessage()) {
//        return;
//    }
    if (msg == sendTimer) {
        sendPacket();
        scheduleAt(simTime() + 0.3, sendTimer);
    } else {
        EV << "This is sender: " << par("ipv4Address").stringValue() << "\n";
        delete msg;
    }
}

void Sender::sendPacket()
{
    EV << "Sending packet...\n";

    const char* srcAddress = par("ipv4Address").stringValue();

    RIHTPacket *packet = new RIHTPacket();
    packet->setMark(0);
    packet->setUI(-1);
    packet->setSrcAddress(srcAddress);
    packet->setDestAddress("192.168.0.6");

    send(packet, gate("ethg$o", 0));
}
