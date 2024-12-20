//
// Generated file, do not edit! Created by opp_msgtool 6.1 from RIHTReconstructionPacket.msg.
//

#ifndef __RIHTRECONSTRUCTIONPACKET_M_H
#define __RIHTRECONSTRUCTIONPACKET_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// opp_msgtool version check
#define MSGC_VERSION 0x0601
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgtool: 'make clean' should help.
#endif

class RIHTReconstructionPacket;
/**
 * Class generated from <tt>RIHTReconstructionPacket.msg:3</tt> by opp_msgtool.
 * <pre>
 * message RIHTReconstructionPacket
 * {
 *     int markReq;
 * }
 * </pre>
 */
class RIHTReconstructionPacket : public ::omnetpp::cMessage
{
  protected:
    int markReq = 0;

  private:
    void copy(const RIHTReconstructionPacket& other);

  protected:
    bool operator==(const RIHTReconstructionPacket&) = delete;

  public:
    RIHTReconstructionPacket(const char *name=nullptr, short kind=0);
    RIHTReconstructionPacket(const RIHTReconstructionPacket& other);
    virtual ~RIHTReconstructionPacket();
    RIHTReconstructionPacket& operator=(const RIHTReconstructionPacket& other);
    virtual RIHTReconstructionPacket *dup() const override {return new RIHTReconstructionPacket(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual int getMarkReq() const;
    virtual void setMarkReq(int markReq);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RIHTReconstructionPacket& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RIHTReconstructionPacket& obj) {obj.parsimUnpack(b);}


namespace omnetpp {

template<> inline RIHTReconstructionPacket *fromAnyPtr(any_ptr ptr) { return check_and_cast<RIHTReconstructionPacket*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __RIHTRECONSTRUCTIONPACKET_M_H

