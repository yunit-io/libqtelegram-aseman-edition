// This file generated by libqtelegram-code-generator.
// You can download it from: https://github.com/Aseman-Land/libqtelegram-code-generator
// DO NOT EDIT THIS FILE BY HAND -- YOUR CHANGES WILL BE OVERWRITTEN

#ifndef LQTG_TYPE_INPUTDOCUMENT
#define LQTG_TYPE_INPUTDOCUMENT

#include "telegramtypeobject.h"

#include <QMetaType>
#include <QVariant>
#include "core/inboundpkt.h"
#include "core/outboundpkt.h"
#include "../coretypes.h"

#include <QDataStream>

#include <QtGlobal>

class LIBQTELEGRAMSHARED_EXPORT InputDocument : public TelegramTypeObject
{
public:
    enum InputDocumentClassType {
        typeInputDocumentEmpty = 0x72f0eaae,
        typeInputDocument = 0x18798952
    };

    InputDocument(InputDocumentClassType classType = typeInputDocumentEmpty, InboundPkt *in = 0);
    InputDocument(InboundPkt *in);
    InputDocument(const Null&);
    virtual ~InputDocument();

    void setAccessHash(qint64 accessHash);
    qint64 accessHash() const;

    void setId(qint64 id);
    qint64 id() const;

    void setClassType(InputDocumentClassType classType);
    InputDocumentClassType classType() const;

    bool fetch(InboundPkt *in);
    bool push(OutboundPkt *out) const;

    QMap<QString, QVariant> toMap() const;
    static InputDocument fromMap(const QMap<QString, QVariant> &map);

    bool operator ==(const InputDocument &b) const;

    bool operator==(bool stt) const { return isNull() != stt; }
    bool operator!=(bool stt) const { return !operator ==(stt); }

    QByteArray getHash(QCryptographicHash::Algorithm alg = QCryptographicHash::Md5) const;

private:
    qint64 m_accessHash;
    qint64 m_id;
    InputDocumentClassType m_classType;
};

Q_DECLARE_METATYPE(InputDocument)

QDataStream LIBQTELEGRAMSHARED_EXPORT &operator<<(QDataStream &stream, const InputDocument &item);
QDataStream LIBQTELEGRAMSHARED_EXPORT &operator>>(QDataStream &stream, InputDocument &item);

inline InputDocument::InputDocument(InputDocumentClassType classType, InboundPkt *in) :
    m_accessHash(0),
    m_id(0),
    m_classType(classType)
{
    if(in) fetch(in);
}

inline InputDocument::InputDocument(InboundPkt *in) :
    m_accessHash(0),
    m_id(0),
    m_classType(typeInputDocumentEmpty)
{
    fetch(in);
}

inline InputDocument::InputDocument(const Null &null) :
    TelegramTypeObject(null),
    m_accessHash(0),
    m_id(0),
    m_classType(typeInputDocumentEmpty)
{
}

inline InputDocument::~InputDocument() {
}

inline void InputDocument::setAccessHash(qint64 accessHash) {
    m_accessHash = accessHash;
}

inline qint64 InputDocument::accessHash() const {
    return m_accessHash;
}

inline void InputDocument::setId(qint64 id) {
    m_id = id;
}

inline qint64 InputDocument::id() const {
    return m_id;
}

inline bool InputDocument::operator ==(const InputDocument &b) const {
    return m_classType == b.m_classType &&
           m_accessHash == b.m_accessHash &&
           m_id == b.m_id;
}

inline void InputDocument::setClassType(InputDocument::InputDocumentClassType classType) {
    m_classType = classType;
}

inline InputDocument::InputDocumentClassType InputDocument::classType() const {
    return m_classType;
}

inline bool InputDocument::fetch(InboundPkt *in) {
    LQTG_FETCH_LOG;
    int x = in->fetchInt();
    switch(x) {
    case typeInputDocumentEmpty: {
        m_classType = static_cast<InputDocumentClassType>(x);
        return true;
    }
        break;
    
    case typeInputDocument: {
        m_id = in->fetchLong();
        m_accessHash = in->fetchLong();
        m_classType = static_cast<InputDocumentClassType>(x);
        return true;
    }
        break;
    
    default:
        LQTG_FETCH_ASSERT;
        return false;
    }
}

inline bool InputDocument::push(OutboundPkt *out) const {
    out->appendInt(m_classType);
    switch(m_classType) {
    case typeInputDocumentEmpty: {
        return true;
    }
        break;
    
    case typeInputDocument: {
        out->appendLong(m_id);
        out->appendLong(m_accessHash);
        return true;
    }
        break;
    
    default:
        return false;
    }
}

inline QMap<QString, QVariant> InputDocument::toMap() const {
    QMap<QString, QVariant> result;
    switch(static_cast<int>(m_classType)) {
    case typeInputDocumentEmpty: {
        result["classType"] = "InputDocument::typeInputDocumentEmpty";
        return result;
    }
        break;
    
    case typeInputDocument: {
        result["classType"] = "InputDocument::typeInputDocument";
        result["id"] = QVariant::fromValue<qint64>(id());
        result["accessHash"] = QVariant::fromValue<qint64>(accessHash());
        return result;
    }
        break;
    
    default:
        return result;
    }
}

inline InputDocument InputDocument::fromMap(const QMap<QString, QVariant> &map) {
    InputDocument result;
    if(map.value("classType").toString() == "InputDocument::typeInputDocumentEmpty") {
        result.setClassType(typeInputDocumentEmpty);
        return result;
    }
    if(map.value("classType").toString() == "InputDocument::typeInputDocument") {
        result.setClassType(typeInputDocument);
        result.setId( map.value("id").value<qint64>() );
        result.setAccessHash( map.value("accessHash").value<qint64>() );
        return result;
    }
    return result;
}

inline QByteArray InputDocument::getHash(QCryptographicHash::Algorithm alg) const {
    QByteArray data;
    QDataStream str(&data, QIODevice::WriteOnly);
    str << *this;
    return QCryptographicHash::hash(data, alg);
}

inline QDataStream &operator<<(QDataStream &stream, const InputDocument &item) {
    stream << static_cast<uint>(item.classType());
    switch(item.classType()) {
    case InputDocument::typeInputDocumentEmpty:
        
        break;
    case InputDocument::typeInputDocument:
        stream << item.id();
        stream << item.accessHash();
        break;
    }
    return stream;
}

inline QDataStream &operator>>(QDataStream &stream, InputDocument &item) {
    uint type = 0;
    stream >> type;
    item.setClassType(static_cast<InputDocument::InputDocumentClassType>(type));
    switch(type) {
    case InputDocument::typeInputDocumentEmpty: {
        
    }
        break;
    case InputDocument::typeInputDocument: {
        qint64 m_id;
        stream >> m_id;
        item.setId(m_id);
        qint64 m_access_hash;
        stream >> m_access_hash;
        item.setAccessHash(m_access_hash);
    }
        break;
    }
    return stream;
}


#endif // LQTG_TYPE_INPUTDOCUMENT
