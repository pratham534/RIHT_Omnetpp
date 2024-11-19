//
// Generated file, do not edit! Created by opp_msgtool 6.1 from RIHTPacket.msg.
//

#ifndef __RIHTPACKET_M_H
#define __RIHTPACKET_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// opp_msgtool version check
#define MSGC_VERSION 0x0601
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgtool: 'make clean' should help.
#endif

class RIHTPacket;
/**
 * Class generated from <tt>RIHTPacket.msg:4</tt> by opp_msgtool.
 * <pre>
 * message RIHTPacket
 * {
 *     int mark;
 *     int UI;
 *     string srcAddress; // Source IP address
 *     string destAddress; // Destination IP address
 * }
 * </pre>
 */
class RIHTPacket : public ::omnetpp::cMessage
{
  protected:
    int mark = 0;
    int UI = 0;
    omnetpp::opp_string srcAddress;
    omnetpp::opp_string destAddress;

  private:
    void copy(const RIHTPacket& other);

  protected:
    bool operator==(const RIHTPacket&) = delete;

  public:
    RIHTPacket(const char *name=nullptr, short kind=0);
    RIHTPacket(const RIHTPacket& other);
    virtual ~RIHTPacket();
    RIHTPacket& operator=(const RIHTPacket& other);
    virtual RIHTPacket *dup() const override {return new RIHTPacket(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual int getMark() const;
    virtual void setMark(int mark);

    virtual int getUI() const;
    virtual void setUI(int UI);

    virtual const char * getSrcAddress() const;
    virtual void setSrcAddress(const char * srcAddress);

    virtual const char * getDestAddress() const;
    virtual void setDestAddress(const char * destAddress);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RIHTPacket& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RIHTPacket& obj) {obj.parsimUnpack(b);}


namespace omnetpp {

template<> inline RIHTPacket *fromAnyPtr(any_ptr ptr) { return check_and_cast<RIHTPacket*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __RIHTPACKET_M_H

