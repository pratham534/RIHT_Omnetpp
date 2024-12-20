//
// Generated file, do not edit! Created by opp_msgtool 6.1 from RIHTPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "RIHTPacket_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

Register_Class(RIHTPacket)

RIHTPacket::RIHTPacket(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

RIHTPacket::RIHTPacket(const RIHTPacket& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

RIHTPacket::~RIHTPacket()
{
}

RIHTPacket& RIHTPacket::operator=(const RIHTPacket& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void RIHTPacket::copy(const RIHTPacket& other)
{
    this->mark = other.mark;
    this->UI = other.UI;
    this->srcAddress = other.srcAddress;
    this->destAddress = other.destAddress;
}

void RIHTPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->mark);
    doParsimPacking(b,this->UI);
    doParsimPacking(b,this->srcAddress);
    doParsimPacking(b,this->destAddress);
}

void RIHTPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->mark);
    doParsimUnpacking(b,this->UI);
    doParsimUnpacking(b,this->srcAddress);
    doParsimUnpacking(b,this->destAddress);
}

int RIHTPacket::getMark() const
{
    return this->mark;
}

void RIHTPacket::setMark(int mark)
{
    this->mark = mark;
}

int RIHTPacket::getUI() const
{
    return this->UI;
}

void RIHTPacket::setUI(int UI)
{
    this->UI = UI;
}

const char * RIHTPacket::getSrcAddress() const
{
    return this->srcAddress.c_str();
}

void RIHTPacket::setSrcAddress(const char * srcAddress)
{
    this->srcAddress = srcAddress;
}

const char * RIHTPacket::getDestAddress() const
{
    return this->destAddress.c_str();
}

void RIHTPacket::setDestAddress(const char * destAddress)
{
    this->destAddress = destAddress;
}

class RIHTPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_mark,
        FIELD_UI,
        FIELD_srcAddress,
        FIELD_destAddress,
    };
  public:
    RIHTPacketDescriptor();
    virtual ~RIHTPacketDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(RIHTPacketDescriptor)

RIHTPacketDescriptor::RIHTPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(RIHTPacket)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

RIHTPacketDescriptor::~RIHTPacketDescriptor()
{
    delete[] propertyNames;
}

bool RIHTPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RIHTPacket *>(obj)!=nullptr;
}

const char **RIHTPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RIHTPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RIHTPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int RIHTPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_mark
        FD_ISEDITABLE,    // FIELD_UI
        FD_ISEDITABLE,    // FIELD_srcAddress
        FD_ISEDITABLE,    // FIELD_destAddress
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *RIHTPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "mark",
        "UI",
        "srcAddress",
        "destAddress",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int RIHTPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "mark") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "UI") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "srcAddress") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "destAddress") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *RIHTPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_mark
        "int",    // FIELD_UI
        "string",    // FIELD_srcAddress
        "string",    // FIELD_destAddress
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **RIHTPacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *RIHTPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int RIHTPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RIHTPacket *pp = omnetpp::fromAnyPtr<RIHTPacket>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RIHTPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RIHTPacket *pp = omnetpp::fromAnyPtr<RIHTPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RIHTPacket'", field);
    }
}

const char *RIHTPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RIHTPacket *pp = omnetpp::fromAnyPtr<RIHTPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RIHTPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RIHTPacket *pp = omnetpp::fromAnyPtr<RIHTPacket>(object); (void)pp;
    switch (field) {
        case FIELD_mark: return long2string(pp->getMark());
        case FIELD_UI: return long2string(pp->getUI());
        case FIELD_srcAddress: return oppstring2string(pp->getSrcAddress());
        case FIELD_destAddress: return oppstring2string(pp->getDestAddress());
        default: return "";
    }
}

void RIHTPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RIHTPacket *pp = omnetpp::fromAnyPtr<RIHTPacket>(object); (void)pp;
    switch (field) {
        case FIELD_mark: pp->setMark(string2long(value)); break;
        case FIELD_UI: pp->setUI(string2long(value)); break;
        case FIELD_srcAddress: pp->setSrcAddress((value)); break;
        case FIELD_destAddress: pp->setDestAddress((value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RIHTPacket'", field);
    }
}

omnetpp::cValue RIHTPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RIHTPacket *pp = omnetpp::fromAnyPtr<RIHTPacket>(object); (void)pp;
    switch (field) {
        case FIELD_mark: return pp->getMark();
        case FIELD_UI: return pp->getUI();
        case FIELD_srcAddress: return pp->getSrcAddress();
        case FIELD_destAddress: return pp->getDestAddress();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RIHTPacket' as cValue -- field index out of range?", field);
    }
}

void RIHTPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RIHTPacket *pp = omnetpp::fromAnyPtr<RIHTPacket>(object); (void)pp;
    switch (field) {
        case FIELD_mark: pp->setMark(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_UI: pp->setUI(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_srcAddress: pp->setSrcAddress(value.stringValue()); break;
        case FIELD_destAddress: pp->setDestAddress(value.stringValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RIHTPacket'", field);
    }
}

const char *RIHTPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr RIHTPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RIHTPacket *pp = omnetpp::fromAnyPtr<RIHTPacket>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RIHTPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RIHTPacket *pp = omnetpp::fromAnyPtr<RIHTPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RIHTPacket'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

