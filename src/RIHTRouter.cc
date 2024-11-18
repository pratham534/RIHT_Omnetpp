///*
// * RIHTRouter.cc
// *
// *  Created on: 15-Nov-2024
// *      Author: Pratham
// */
//
// src/RIHTRouter.cc
#include <omnetpp.h>
#include "RIHTPacket_m.h"

using namespace omnetpp;

struct HashTableEntry {
    int mark;
    int UI;
};

class RIHTRouter : public omnetpp::cSimpleModule {
  private:
    int degree;
    int hashTableSize;
//    int port;
    std::vector<HashTableEntry> hashTable;
    int computeMark(RIHTPacket *packet, int upstreamInterface);
    int hashFunction(int mark);
    void logMark(int index, int mark, int UI);

  protected:
    virtual void initialize() override;
    virtual void handleMessage(omnetpp::cMessage *msg) override;
};

Define_Module(RIHTRouter);

void RIHTRouter::initialize() {
    degree = par("degree");
    hashTableSize = par("hashTableSize");
    hashTable.resize(hashTableSize, {-1, -1});
    EV << "Router Initialized \n";
//    this->port = 0;
}

void RIHTRouter::handleMessage(omnetpp::cMessage *msg) {
    if (msg->isSelfMessage()) {
        // Handle self messages (timeouts, etc.)
        return;
    }

    RIHTPacket *packet = check_and_cast<RIHTPacket *>(msg);
    int mark = packet->getMark();
    int upstreamInterface = packet->getArrivalGate()->getIndex();

    // Compute the outgoing interface (downstream interface) based on the mark and upstream interface
    int outgoingInterface = (upstreamInterface + 1) % degree;  // Simple decision rule

    // Log the mark in the hash table (for RIHT traceback)
    int index = hashFunction(mark);
    logMark(index, mark, upstreamInterface);

    EV << "Packet received on interface " << upstreamInterface
       << ", forwarding to interface " << outgoingInterface << "\n";

    // Forward the packet to the selected interface
    simtime_t delay = 1;
    sendDelayed(msg, delay, gate("ethg$o", outgoingInterface));
}



int RIHTRouter::computeMark(RIHTPacket *packet, int upstreamInterface) {
    int oldMark = packet->getMark();
    return oldMark * (degree + 1) + upstreamInterface + 1;
}

int RIHTRouter::hashFunction(int mark) {
    return mark % hashTableSize;
}

void RIHTRouter::logMark(int index, int mark, int UI) {
    hashTable[index].mark = mark;
    hashTable[index].UI = UI;
}
