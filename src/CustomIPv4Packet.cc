#include "CustomIPv4Packet.h"

// Constructor
CustomIPv4Packet::CustomIPv4Packet(const char *name) : cPacket(name), markingField(0) {}

// Set the custom marking field (32-bit value)
void CustomIPv4Packet::setMarkingField(uint32_t marking)
{
    markingField = marking;

    // Decompose marking field into identification, flags, and fragment offset
    int identification = (markingField >> 16) & 0xFFFF;  // Extract 16-bit identification
    int flags = (markingField >> 13) & 0x7;  // Extract 3-bit flags
    int fragmentOffset = markingField & 0x1FFF;  // Extract 13-bit fragment offset

    // Set the corresponding fields in the IPv4 header
    header.setIdentification(identification);
    header.setFlags(flags);
    header.setFragmentOffset(fragmentOffset);
}

// Get the custom marking field (32-bit value) by combining identification, flags, and fragment offset
uint32_t CustomIPv4Packet::getMarkingField() const
{
    int identification = header.getIdentification();
    int flags = header.getFlags();
    int fragmentOffset = header.getFragmentOffset();

    // Combine fields into a single 32-bit marking field
    return (identification << 16) | (flags << 13) | fragmentOffset;
}

// Set the destination address (IPv4Address)
void CustomIPv4Packet::setDestinationAddress(const Ipv4Address& destAddr)
{
    header.setDestAddress(destAddr);
}

// Get the destination address (IPv4Address)
Ipv4Address CustomIPv4Packet::getDestinationAddress() const
{
    return header.getDestAddress();
}

// Set the source address (IPv4Address)
void CustomIPv4Packet::setSourceAddress(const Ipv4Address& srcAddr)
{
    header.setSrcAddress(srcAddr);
}

// Get the source address (IPv4Address)
Ipv4Address CustomIPv4Packet::getSourceAddress() const
{
    return header.getSrcAddress();
}

// Accessor for the IPv4Header
const Ipv4Header& CustomIPv4Packet::getHeader() const
{
    return header;
}

// Mutator for the IPv4Header
void CustomIPv4Packet::setHeader(const Ipv4Header& newHeader)
{
    header = newHeader;
}

// Serialization function (used when sending/receiving packets)
void CustomIPv4Packet::parsimPack(cCommBuffer *b) const
{
    cPacket::parsimPack(b);
    b->pack(markingField);
    b->pack(header);
}

// Deserialization function (used when receiving packets)
void CustomIPv4Packet::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    b->unpack(markingField);
    b->unpack(header);
}
