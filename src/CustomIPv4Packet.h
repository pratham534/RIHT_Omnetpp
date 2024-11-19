#ifndef CUSTOM_IPV4_PACKET_H
#define CUSTOM_IPV4_PACKET_H

#include <omnetpp.h>
#include "Ipv4Header_m.h"
#include "Ipv4Address.h"

class CustomIPv4Packet : public cPacket
{
  private:
    Ipv4Header header;  // IPv4 Header to encapsulate IPv4 fields
    uint32_t markingField;  // Custom 32-bit marking field

  public:
    // Constructor
    CustomIPv4Packet(const char *name = nullptr);

    // Set the custom marking field (32-bit value)
    void setMarkingField(uint32_t marking);

    // Get the custom marking field (32-bit value)
    uint32_t getMarkingField() const;

    // Set the destination address (IPv4Address)
    void setDestinationAddress(const Ipv4Address& destAddr);

    // Get the destination address (IPv4Address)
    Ipv4Address getDestinationAddress() const;

    // Set the source address (IPv4Address)
    void setSourceAddress(const Ipv4Address& srcAddr);

    // Get the source address (IPv4Address)
    Ipv4Address getSourceAddress() const;

    // Accessor for the IPv4Header
    const Ipv4Header& getHeader() const;
    void setHeader(const Ipv4Header& newHeader);

    // Serialization function (used when sending/receiving packets)
    virtual void parsimPack(cCommBuffer *b) const override;

    // Deserialization function (used when receiving packets)
    virtual void parsimUnpack(cCommBuffer *b) override;
};

#endif // CUSTOM_IPV4_PACKET_H
