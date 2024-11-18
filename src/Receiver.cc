
#include <omnetpp.h>
#include "RIHTPacket_m.h"

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
    if (auto myMsg = dynamic_cast<RIHTPacket *>(msg)) {
        EV << "Received message: Mark-" << myMsg->getMark() << " UI-"<< myMsg->getUI()<< "\n";
    }

}
