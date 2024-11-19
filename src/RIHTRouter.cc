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
        // Handle self messages (timeouts, etc.)
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

    // Print hash table before processing the packet
    EV << "Hash Table Before Processing:\n";
    printHashTable();

    // Step 1: Compute mark_new
    int mark_new = mark * (degree + 1) + upstreamInterface + 1;
    EV<<"new p.mark = "<<mark_new<<"\n";
    // Step 2: Check for 32-bit integer overflow
    const int MAX_8BIT_INT = 255;
    if (mark_new > MAX_8BIT_INT) {
        EV<<"Mark Overflow. Logging....\n";
        int index = hashFunction(mark);
        int probe = 0;

        // Step 3: Quadratic probing
        while (hashTable[index].mark != -1 &&
               !(hashTable[index].mark == mark && hashTable[index].UI == upstreamInterface)) {
            probe++;
            index = (index + 1 * probe + 2 * probe * probe) % hashTableSize;
        }

        // Step 4: Insert or update the hash table entry
        if (hashTable[index].mark == -1) {
            hashTable[index].mark = mark;
            hashTable[index].UI = upstreamInterface;
            EV << "Hash Table After Logging Mark:\n";
            printHashTable();
        }

    // Print hash table after logging the mark

        // Update mark_new based on the index
        mark_new = index * (degree + 1);
    }
    EV<<"final p.mark = "<<mark_new<<"\n";

    // Step 5: Update the packet mark
    packet->setMark(mark_new);


    /*
     * below outgoingInterface logic
     * to be modified ....
     *
     */

    // Compute the outgoing interface (downstream interface)
    int outgoingInterface = (upstreamInterface + 1) % degree;

    EV << "Packet received on interface " << upstreamInterface
       << ", forwarding to interface " << outgoingInterface << "\n";

    // Forward the packet to the selected interface
    simtime_t delay = 2;
    sendDelayed(msg, delay, gate("ethg$o", outgoingInterface));
}

void RIHTRouter::handleReconstructionRequest(RIHTReconstructionPacket *reconPacket) {
    int mark_req = reconPacket->getMarkReq();
    int UI_i = mark_req % (degree + 1) - 1;

    if (UI_i == -1) {
        int index = mark_req / (degree + 1);

        if (index != 0) {
            UI_i = hashTable[index].UI;
            int mark_old = hashTable[index].mark;

            EV << "Sending reconstruction request with mark_old " << mark_old
               << " to upstream router via UI " << UI_i << "\n";

            reconPacket->setMarkReq(mark_old);
            send(reconPacket, gate("ethg$o", UI_i));
        } else {
            EV << "This router is the nearest border router to the attacker\n";
            delete reconPacket;
        }
    } else {
        int mark_old = mark_req / (degree + 1);

        EV << "Sending reconstruction request with mark_old " << mark_old
           << " to upstream router via UI " << UI_i << "\n";

        reconPacket->setMarkReq(mark_old);
        send(reconPacket, gate("ethg$o", UI_i));
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
