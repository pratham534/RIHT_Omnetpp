#include <omnetpp.h>
#include <map>
#include "RIHTPacket_m.h"
#include "RIHTReconstructionPacket_m.h"

using namespace omnetpp;

class Receiver : public cSimpleModule
{
  private:
    std::map<std::string, int> packetCount;
    simtime_t lastCheckTime;
    int attackThreshold;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

    void checkForDDoS(RIHTPacket *packet);
};

Define_Module(Receiver);

void Receiver::initialize()
{
    EV << "Receiver Initialized!" << "\n";
    attackThreshold = par("attackThreshold");
    lastCheckTime = simTime();
}

void Receiver::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage()) {
        return;
    }

    RIHTPacket *packet = check_and_cast<RIHTPacket *>(msg);
    std::string srcAddress = packet->getSrcAddress();
    packetCount[srcAddress]++;

    EV << "Packet Received from src: " << srcAddress << "\n";
    EV << "Received message: Mark-" << packet->getMark() << " UI-" << packet->getUI() << "\n";


    checkForDDoS(packet);

//    RIHTReconstructionPacket *repacket = new RIHTReconstructionPacket();
//    repacket->setMarkReq(packet->getMark());
//    int UI = packet->getArrivalGate()->getIndex();
//    sendDelayed(repacket, 4, gate("ethg$o", UI));

    delete packet;
}

void Receiver::checkForDDoS(RIHTPacket *packet)
{
    simtime_t now = simTime();
    if (now - lastCheckTime >= 1)
    {
        lastCheckTime = now;

        for (auto it = packetCount.begin(); it != packetCount.end(); ++it) {
            if (it->second > attackThreshold) {
                EV << "DDoS detected from source: " << it->first << " with "
                   << it->second << " packets in last second.\n";

                RIHTReconstructionPacket *repacket = new RIHTReconstructionPacket();
                repacket->setMarkReq(packet->getMark());
                int UI = packet->getArrivalGate()->getIndex();
                sendDelayed(repacket, 1, gate("ethg$o", UI));
            }
        }

        packetCount.clear();
    }
}

