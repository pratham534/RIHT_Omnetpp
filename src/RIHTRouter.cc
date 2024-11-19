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
#include "RIHTReconstructionPacket_m.h"

using namespace omnetpp;

struct HashTableEntry {
    int mark;
    int UI;
};

class RIHTRouter : public omnetpp::cSimpleModule {
  private:
    int degree;
    int hashTableSize;
    std::vector<HashTableEntry> hashTable;
    int hashFunction(int mark);
    void printHashTable();

  protected:
    virtual void initialize() override;
    virtual void handleMessage(omnetpp::cMessage *msg) override;
    void handleReconstructionRequest(RIHTReconstructionPacket *reconPacket);
};

Define_Module(RIHTRouter);

void RIHTRouter::initialize() {
    degree = par("degree");
    hashTableSize = par("hashTableSize");
    hashTable.resize(hashTableSize, {-1, -1});
    EV << "Router Initialized \n";
}

void RIHTRouter::handleMessage(omnetpp::cMessage *msg) {
    if (msg->isSelfMessage()) {
        return;
    }

    if (RIHTReconstructionPacket *reconPacket = dynamic_cast<RIHTReconstructionPacket *>(msg)) {
        handleReconstructionRequest(reconPacket);
        return;
    }
    RIHTPacket *packet = check_and_cast<RIHTPacket *>(msg);

    int mark = packet->getMark();
    int upstreamInterface = packet->getArrivalGate()->getIndex();
    EV<<"p.mark = "<<mark<<" UI = "<<upstreamInterface<<"\n";

    EV << "Hash Table Before Processing:\n";
    printHashTable();

    int mark_new = mark * (degree + 1) + upstreamInterface + 1;
    EV<<"new p.mark = "<<mark_new<<"\n";

    const int MAX_8BIT_INT = 255;
    if (mark_new > MAX_8BIT_INT) {
        EV<<"Mark Overflow. Logging....\n";
        int index = hashFunction(mark);
        int probe = 0;

        while (hashTable[index].mark != -1 &&
               !(hashTable[index].mark == mark && hashTable[index].UI == upstreamInterface)) {
            probe++;
            index = (index + 1 * probe + 2 * probe * probe) % hashTableSize;
        }

        if (hashTable[index].mark == -1) {
            hashTable[index].mark = mark;
            hashTable[index].UI = upstreamInterface;
            EV << "Hash Table After Logging Mark:\n";
            printHashTable();
        }
        mark_new = index * (degree + 1);
    }
    EV<<"final p.mark = "<<mark_new<<"\n";
    packet->setMark(mark_new);

    int outgoingInterface = (upstreamInterface + 1) % degree;
    std::string destAddress = packet->getDestAddress();
    if (destAddress == "192.168.0.6") {
        outgoingInterface = 1;
    }

    EV << "Packet received on interface " << upstreamInterface << ", forwarding to interface " << outgoingInterface << "\n";

    sendDelayed(msg, 2, gate("ethg$o", outgoingInterface));
}

void RIHTRouter::handleReconstructionRequest(RIHTReconstructionPacket *reconPacket) {
    int mark_req = reconPacket->getMarkReq();
    int UI = mark_req % (degree + 1) - 1;
    EV << "marking field: " << mark_req << "\tUI: " << UI << "\n";

    if (UI == -1) {
        EV << "Searching HashTable for the Upstream Router\n";
        int index = mark_req / (degree + 1);

        if (index != 0) {
            UI = hashTable[index].UI;
            int mark_old = hashTable[index].mark;

            EV << "Sending reconstruction request with mark_old " << mark_old
               << " to upstream router via UI " << UI << "\n";

            reconPacket->setMarkReq(mark_old);
            send(reconPacket, gate("ethg$o", UI));
        } else {
            EV << "This router is the nearest border router to the attacker\n";
            delete reconPacket;
        }
    } else {
        int mark_old = mark_req / (degree + 1);

        EV << "Sending reconstruction request with mark_old " << mark_old
           << " to upstream router via UI " << UI << "\n";

        reconPacket->setMarkReq(mark_old);
        send(reconPacket, gate("ethg$o", UI));
    }
}

void RIHTRouter::printHashTable() {
    EV << "Index\tMark\tUI\n";
    for (int i = 0; i < hashTableSize; i++) {
        EV << i << "\t" << hashTable[i].mark << "\t" << hashTable[i].UI << "\n";
    }
}

int RIHTRouter::hashFunction(int mark) {
    return mark % hashTableSize;
}
