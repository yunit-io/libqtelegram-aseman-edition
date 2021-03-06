// This file generated by libqtelegram-code-generator.
// You can download it from: https://github.com/Aseman-Land/libqtelegram-code-generator
// DO NOT EDIT THIS FILE BY HAND -- YOUR CHANGES WILL BE OVERWRITTEN

#ifndef LQTG_TYPE_CHANNELSCHANNELPARTICIPANT
#define LQTG_TYPE_CHANNELSCHANNELPARTICIPANT

#include "telegramtypeobject.h"

#include <QMetaType>
#include <QVariant>
#include "core/inboundpkt.h"
#include "core/outboundpkt.h"
#include "../coretypes.h"

#include <QDataStream>

#include "channelparticipant.h"
#include <QList>
#include "user.h"

class LIBQTELEGRAMSHARED_EXPORT ChannelsChannelParticipant : public TelegramTypeObject
{
public:
    enum ChannelsChannelParticipantClassType {
        typeChannelsChannelParticipant = 0xd0d9b163
    };

    ChannelsChannelParticipant(ChannelsChannelParticipantClassType classType = typeChannelsChannelParticipant, InboundPkt *in = 0);
    ChannelsChannelParticipant(InboundPkt *in);
    ChannelsChannelParticipant(const Null&);
    virtual ~ChannelsChannelParticipant();

    void setParticipant(const ChannelParticipant &participant);
    ChannelParticipant participant() const;

    void setUsers(const QList<User> &users);
    QList<User> users() const;

    void setClassType(ChannelsChannelParticipantClassType classType);
    ChannelsChannelParticipantClassType classType() const;

    bool fetch(InboundPkt *in);
    bool push(OutboundPkt *out) const;

    QMap<QString, QVariant> toMap() const;
    static ChannelsChannelParticipant fromMap(const QMap<QString, QVariant> &map);

    bool operator ==(const ChannelsChannelParticipant &b) const;

    bool operator==(bool stt) const { return isNull() != stt; }
    bool operator!=(bool stt) const { return !operator ==(stt); }

    QByteArray getHash(QCryptographicHash::Algorithm alg = QCryptographicHash::Md5) const;

private:
    ChannelParticipant m_participant;
    QList<User> m_users;
    ChannelsChannelParticipantClassType m_classType;
};

Q_DECLARE_METATYPE(ChannelsChannelParticipant)

QDataStream LIBQTELEGRAMSHARED_EXPORT &operator<<(QDataStream &stream, const ChannelsChannelParticipant &item);
QDataStream LIBQTELEGRAMSHARED_EXPORT &operator>>(QDataStream &stream, ChannelsChannelParticipant &item);

inline ChannelsChannelParticipant::ChannelsChannelParticipant(ChannelsChannelParticipantClassType classType, InboundPkt *in) :
    m_classType(classType)
{
    if(in) fetch(in);
}

inline ChannelsChannelParticipant::ChannelsChannelParticipant(InboundPkt *in) :
    m_classType(typeChannelsChannelParticipant)
{
    fetch(in);
}

inline ChannelsChannelParticipant::ChannelsChannelParticipant(const Null &null) :
    TelegramTypeObject(null),
    m_classType(typeChannelsChannelParticipant)
{
}

inline ChannelsChannelParticipant::~ChannelsChannelParticipant() {
}

inline void ChannelsChannelParticipant::setParticipant(const ChannelParticipant &participant) {
    m_participant = participant;
}

inline ChannelParticipant ChannelsChannelParticipant::participant() const {
    return m_participant;
}

inline void ChannelsChannelParticipant::setUsers(const QList<User> &users) {
    m_users = users;
}

inline QList<User> ChannelsChannelParticipant::users() const {
    return m_users;
}

inline bool ChannelsChannelParticipant::operator ==(const ChannelsChannelParticipant &b) const {
    return m_classType == b.m_classType &&
           m_participant == b.m_participant &&
           m_users == b.m_users;
}

inline void ChannelsChannelParticipant::setClassType(ChannelsChannelParticipant::ChannelsChannelParticipantClassType classType) {
    m_classType = classType;
}

inline ChannelsChannelParticipant::ChannelsChannelParticipantClassType ChannelsChannelParticipant::classType() const {
    return m_classType;
}

inline bool ChannelsChannelParticipant::fetch(InboundPkt *in) {
    LQTG_FETCH_LOG;
    int x = in->fetchInt();
    switch(x) {
    case typeChannelsChannelParticipant: {
        m_participant.fetch(in);
        if(in->fetchInt() != (qint32)CoreTypes::typeVector) return false;
        qint32 m_users_length = in->fetchInt();
        m_users.clear();
        for (qint32 i = 0; i < m_users_length; i++) {
            User type;
            type.fetch(in);
            m_users.append(type);
        }
        m_classType = static_cast<ChannelsChannelParticipantClassType>(x);
        return true;
    }
        break;
    
    default:
        LQTG_FETCH_ASSERT;
        return false;
    }
}

inline bool ChannelsChannelParticipant::push(OutboundPkt *out) const {
    out->appendInt(m_classType);
    switch(m_classType) {
    case typeChannelsChannelParticipant: {
        m_participant.push(out);
        out->appendInt(CoreTypes::typeVector);
        out->appendInt(m_users.count());
        for (qint32 i = 0; i < m_users.count(); i++) {
            m_users[i].push(out);
        }
        return true;
    }
        break;
    
    default:
        return false;
    }
}

inline QMap<QString, QVariant> ChannelsChannelParticipant::toMap() const {
    QMap<QString, QVariant> result;
    switch(static_cast<int>(m_classType)) {
    case typeChannelsChannelParticipant: {
        result["classType"] = "ChannelsChannelParticipant::typeChannelsChannelParticipant";
        result["participant"] = m_participant.toMap();
        QList<QVariant> _users;
        Q_FOREACH(const User &m__type, m_users)
            _users << m__type.toMap();
        result["users"] = _users;
        return result;
    }
        break;
    
    default:
        return result;
    }
}

inline ChannelsChannelParticipant ChannelsChannelParticipant::fromMap(const QMap<QString, QVariant> &map) {
    ChannelsChannelParticipant result;
    if(map.value("classType").toString() == "ChannelsChannelParticipant::typeChannelsChannelParticipant") {
        result.setClassType(typeChannelsChannelParticipant);
        result.setParticipant( ChannelParticipant::fromMap(map.value("participant").toMap()) );
        QList<QVariant> map_users = map["users"].toList();
        QList<User> _users;
        Q_FOREACH(const QVariant &var, map_users)
            _users << User::fromMap(var.toMap());
        result.setUsers(_users);
        return result;
    }
    return result;
}

inline QByteArray ChannelsChannelParticipant::getHash(QCryptographicHash::Algorithm alg) const {
    QByteArray data;
    QDataStream str(&data, QIODevice::WriteOnly);
    str << *this;
    return QCryptographicHash::hash(data, alg);
}

inline QDataStream &operator<<(QDataStream &stream, const ChannelsChannelParticipant &item) {
    stream << static_cast<uint>(item.classType());
    switch(item.classType()) {
    case ChannelsChannelParticipant::typeChannelsChannelParticipant:
        stream << item.participant();
        stream << item.users();
        break;
    }
    return stream;
}

inline QDataStream &operator>>(QDataStream &stream, ChannelsChannelParticipant &item) {
    uint type = 0;
    stream >> type;
    item.setClassType(static_cast<ChannelsChannelParticipant::ChannelsChannelParticipantClassType>(type));
    switch(type) {
    case ChannelsChannelParticipant::typeChannelsChannelParticipant: {
        ChannelParticipant m_participant;
        stream >> m_participant;
        item.setParticipant(m_participant);
        QList<User> m_users;
        stream >> m_users;
        item.setUsers(m_users);
    }
        break;
    }
    return stream;
}


#endif // LQTG_TYPE_CHANNELSCHANNELPARTICIPANT
