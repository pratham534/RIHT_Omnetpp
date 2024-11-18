/*
 * RIHTRouter.h
 *
 *  Created on: 15-Nov-2024
 *      Author: Pratham
 */

// src/RIHTRouter.h
#ifndef __RIHT_ROUTER_H
#define __RIHT_ROUTER_H

#include <omnetpp.h>
#include "RIHTPacket_m.h"

struct HashTableEntry {
    int mark;
    int UI;
};

class RIHTRouter : public omnetpp::cSimpleModule {
  private:
    int degree;
    int hashTableSize;
    std::vector<HashTableEntry> hashTable;
    int computeMark(RIHTPacket *packet, int upstreamInterface);
    int hashFunction(int mark);
    void logMark(int index, int mark, int UI);

  protected:
    virtual void initialize() override;
    virtual void handleMessage(omnetpp::cMessage *msg) override;
};

#endif
