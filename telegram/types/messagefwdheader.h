// This file generated by libqtelegram-code-generator.
// You can download it from: https://github.com/Aseman-Land/libqtelegram-code-generator
// DO NOT EDIT THIS FILE BY HAND -- YOUR CHANGES WILL BE OVERWRITTEN

#ifndef LQTG_TYPE_MESSAGEFWDHEADER
#define LQTG_TYPE_MESSAGEFWDHEADER

#include "telegramtypeobject.h"

#include <QMetaType>
#include <QVariant>
#include "core/inboundpkt.h"
#include "core/outboundpkt.h"
#include "../coretypes.h"

#include <QDataStream>

#include <QtGlobal>

class LIBQTELEGRAMSHARED_EXPORT MessageFwdHeader : public TelegramTypeObject
{
public:
    enum MessageFwdHeaderClassType {
        typeMessageFwdHeader = 0xc786ddcb
    };

    MessageFwdHeader(MessageFwdHeaderClassType classType = typeMessageFwdHeader, InboundPkt *in = 0);
    MessageFwdHeader(InboundPkt *in);
    MessageFwdHeader(const Null&);
    virtual ~MessageFwdHeader();

    void setChannelId(qint32 channelId);
    qint32 channelId() const;

    void setChannelPost(qint32 channelPost);
    qint32 channelPost() const;

    void setDate(qint32 date);
    qint32 date() const;

    void setFlags(qint32 flags);
    qint32 flags() const;

    void setFromId(qint32 fromId);
    qint32 fromId() const;

    void setClassType(MessageFwdHeaderClassType classType);
    MessageFwdHeaderClassType classType() const;

    bool fetch(InboundPkt *in);
    bool push(OutboundPkt *out) const;

    QMap<QString, QVariant> toMap() const;
    static MessageFwdHeader fromMap(const QMap<QString, QVariant> &map);

    bool operator ==(const MessageFwdHeader &b) const;

    bool operator==(bool stt) const { return isNull() != stt; }
    bool operator!=(bool stt) const { return !operator ==(stt); }

    QByteArray getHash(QCryptographicHash::Algorithm alg = QCryptographicHash::Md5) const;

private:
    qint32 m_channelId;
    qint32 m_channelPost;
    qint32 m_date;
    qint32 m_flags;
    qint32 m_fromId;
    MessageFwdHeaderClassType m_classType;
};

Q_DECLARE_METATYPE(MessageFwdHeader)

QDataStream LIBQTELEGRAMSHARED_EXPORT &operator<<(QDataStream &stream, const MessageFwdHeader &item);
QDataStream LIBQTELEGRAMSHARED_EXPORT &operator>>(QDataStream &stream, MessageFwdHeader &item);

inline MessageFwdHeader::MessageFwdHeader(MessageFwdHeaderClassType classType, InboundPkt *in) :
    m_channelId(0),
    m_channelPost(0),
    m_date(0),
    m_flags(0),
    m_fromId(0),
    m_classType(classType)
{
    if(in) fetch(in);
}

inline MessageFwdHeader::MessageFwdHeader(InboundPkt *in) :
    m_channelId(0),
    m_channelPost(0),
    m_date(0),
    m_flags(0),
    m_fromId(0),
    m_classType(typeMessageFwdHeader)
{
    fetch(in);
}

inline MessageFwdHeader::MessageFwdHeader(const Null &null) :
    TelegramTypeObject(null),
    m_channelId(0),
    m_channelPost(0),
    m_date(0),
    m_flags(0),
    m_fromId(0),
    m_classType(typeMessageFwdHeader)
{
}

inline MessageFwdHeader::~MessageFwdHeader() {
}

inline void MessageFwdHeader::setChannelId(qint32 channelId) {
    m_channelId = channelId;
}

inline qint32 MessageFwdHeader::channelId() const {
    return m_channelId;
}

inline void MessageFwdHeader::setChannelPost(qint32 channelPost) {
    m_channelPost = channelPost;
}

inline qint32 MessageFwdHeader::channelPost() const {
    return m_channelPost;
}

inline void MessageFwdHeader::setDate(qint32 date) {
    m_date = date;
}

inline qint32 MessageFwdHeader::date() const {
    return m_date;
}

inline void MessageFwdHeader::setFlags(qint32 flags) {
    m_flags = flags;
}

inline qint32 MessageFwdHeader::flags() const {
    return m_flags;
}

inline void MessageFwdHeader::setFromId(qint32 fromId) {
    m_fromId = fromId;
}

inline qint32 MessageFwdHeader::fromId() const {
    return m_fromId;
}

inline bool MessageFwdHeader::operator ==(const MessageFwdHeader &b) const {
    return m_classType == b.m_classType &&
           m_channelId == b.m_channelId &&
           m_channelPost == b.m_channelPost &&
           m_date == b.m_date &&
           m_flags == b.m_flags &&
           m_fromId == b.m_fromId;
}

inline void MessageFwdHeader::setClassType(MessageFwdHeader::MessageFwdHeaderClassType classType) {
    m_classType = classType;
}

inline MessageFwdHeader::MessageFwdHeaderClassType MessageFwdHeader::classType() const {
    return m_classType;
}

inline bool MessageFwdHeader::fetch(InboundPkt *in) {
    LQTG_FETCH_LOG;
    int x = in->fetchInt();
    switch(x) {
    case typeMessageFwdHeader: {
        m_flags = in->fetchInt();
        if(m_flags & 1<<0) {
            m_fromId = in->fetchInt();
        }
        m_date = in->fetchInt();
        if(m_flags & 1<<1) {
            m_channelId = in->fetchInt();
        }
        if(m_flags & 1<<2) {
            m_channelPost = in->fetchInt();
        }
        m_classType = static_cast<MessageFwdHeaderClassType>(x);
        return true;
    }
        break;
    
    default:
        LQTG_FETCH_ASSERT;
        return false;
    }
}

inline bool MessageFwdHeader::push(OutboundPkt *out) const {
    out->appendInt(m_classType);
    switch(m_classType) {
    case typeMessageFwdHeader: {
        out->appendInt(m_flags);
        out->appendInt(m_fromId);
        out->appendInt(m_date);
        out->appendInt(m_channelId);
        out->appendInt(m_channelPost);
        return true;
    }
        break;
    
    default:
        return false;
    }
}

inline QMap<QString, QVariant> MessageFwdHeader::toMap() const {
    QMap<QString, QVariant> result;
    switch(static_cast<int>(m_classType)) {
    case typeMessageFwdHeader: {
        result["classType"] = "MessageFwdHeader::typeMessageFwdHeader";
        result["fromId"] = QVariant::fromValue<qint32>(fromId());
        result["date"] = QVariant::fromValue<qint32>(date());
        result["channelId"] = QVariant::fromValue<qint32>(channelId());
        result["channelPost"] = QVariant::fromValue<qint32>(channelPost());
        return result;
    }
        break;
    
    default:
        return result;
    }
}

inline MessageFwdHeader MessageFwdHeader::fromMap(const QMap<QString, QVariant> &map) {
    MessageFwdHeader result;
    if(map.value("classType").toString() == "MessageFwdHeader::typeMessageFwdHeader") {
        result.setClassType(typeMessageFwdHeader);
        result.setFromId( map.value("fromId").value<qint32>() );
        result.setDate( map.value("date").value<qint32>() );
        result.setChannelId( map.value("channelId").value<qint32>() );
        result.setChannelPost( map.value("channelPost").value<qint32>() );
        return result;
    }
    return result;
}

inline QByteArray MessageFwdHeader::getHash(QCryptographicHash::Algorithm alg) const {
    QByteArray data;
    QDataStream str(&data, QIODevice::WriteOnly);
    str << *this;
    return QCryptographicHash::hash(data, alg);
}

inline QDataStream &operator<<(QDataStream &stream, const MessageFwdHeader &item) {
    stream << static_cast<uint>(item.classType());
    switch(item.classType()) {
    case MessageFwdHeader::typeMessageFwdHeader:
        stream << item.flags();
        stream << item.fromId();
        stream << item.date();
        stream << item.channelId();
        stream << item.channelPost();
        break;
    }
    return stream;
}

inline QDataStream &operator>>(QDataStream &stream, MessageFwdHeader &item) {
    uint type = 0;
    stream >> type;
    item.setClassType(static_cast<MessageFwdHeader::MessageFwdHeaderClassType>(type));
    switch(type) {
    case MessageFwdHeader::typeMessageFwdHeader: {
        qint32 m_flags;
        stream >> m_flags;
        item.setFlags(m_flags);
        qint32 m_from_id;
        stream >> m_from_id;
        item.setFromId(m_from_id);
        qint32 m_date;
        stream >> m_date;
        item.setDate(m_date);
        qint32 m_channel_id;
        stream >> m_channel_id;
        item.setChannelId(m_channel_id);
        qint32 m_channel_post;
        stream >> m_channel_post;
        item.setChannelPost(m_channel_post);
    }
        break;
    }
    return stream;
}


#endif // LQTG_TYPE_MESSAGEFWDHEADER
