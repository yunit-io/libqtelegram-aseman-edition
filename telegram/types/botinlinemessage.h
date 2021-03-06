// This file generated by libqtelegram-code-generator.
// You can download it from: https://github.com/Aseman-Land/libqtelegram-code-generator
// DO NOT EDIT THIS FILE BY HAND -- YOUR CHANGES WILL BE OVERWRITTEN

#ifndef LQTG_TYPE_BOTINLINEMESSAGE
#define LQTG_TYPE_BOTINLINEMESSAGE

#include "telegramtypeobject.h"

#include <QMetaType>
#include <QVariant>
#include "core/inboundpkt.h"
#include "core/outboundpkt.h"
#include "../coretypes.h"

#include <QDataStream>

#include <QString>
#include <QList>
#include "messageentity.h"
#include <QtGlobal>
#include "geopoint.h"
#include "replymarkup.h"

class LIBQTELEGRAMSHARED_EXPORT BotInlineMessage : public TelegramTypeObject
{
public:
    enum BotInlineMessageClassType {
        typeBotInlineMessageMediaAuto = 0xa74b15b,
        typeBotInlineMessageText = 0x8c7f65e2,
        typeBotInlineMessageMediaGeo = 0x3a8fd8b8,
        typeBotInlineMessageMediaVenue = 0x4366232e,
        typeBotInlineMessageMediaContact = 0x35edb4d4
    };

    BotInlineMessage(BotInlineMessageClassType classType = typeBotInlineMessageMediaAuto, InboundPkt *in = 0);
    BotInlineMessage(InboundPkt *in);
    BotInlineMessage(const Null&);
    virtual ~BotInlineMessage();

    void setAddress(const QString &address);
    QString address() const;

    void setCaption(const QString &caption);
    QString caption() const;

    void setEntities(const QList<MessageEntity> &entities);
    QList<MessageEntity> entities() const;

    void setFirstName(const QString &firstName);
    QString firstName() const;

    void setFlags(qint32 flags);
    qint32 flags() const;

    void setGeo(const GeoPoint &geo);
    GeoPoint geo() const;

    void setLastName(const QString &lastName);
    QString lastName() const;

    void setMessage(const QString &message);
    QString message() const;

    void setNoWebpage(bool noWebpage);
    bool noWebpage() const;

    void setPhoneNumber(const QString &phoneNumber);
    QString phoneNumber() const;

    void setProvider(const QString &provider);
    QString provider() const;

    void setReplyMarkup(const ReplyMarkup &replyMarkup);
    ReplyMarkup replyMarkup() const;

    void setTitle(const QString &title);
    QString title() const;

    void setVenueId(const QString &venueId);
    QString venueId() const;

    void setClassType(BotInlineMessageClassType classType);
    BotInlineMessageClassType classType() const;

    bool fetch(InboundPkt *in);
    bool push(OutboundPkt *out) const;

    QMap<QString, QVariant> toMap() const;
    static BotInlineMessage fromMap(const QMap<QString, QVariant> &map);

    bool operator ==(const BotInlineMessage &b) const;

    bool operator==(bool stt) const { return isNull() != stt; }
    bool operator!=(bool stt) const { return !operator ==(stt); }

    QByteArray getHash(QCryptographicHash::Algorithm alg = QCryptographicHash::Md5) const;

private:
    QString m_address;
    QString m_caption;
    QList<MessageEntity> m_entities;
    QString m_firstName;
    qint32 m_flags;
    GeoPoint m_geo;
    QString m_lastName;
    QString m_message;
    QString m_phoneNumber;
    QString m_provider;
    ReplyMarkup m_replyMarkup;
    QString m_title;
    QString m_venueId;
    BotInlineMessageClassType m_classType;
};

Q_DECLARE_METATYPE(BotInlineMessage)

QDataStream LIBQTELEGRAMSHARED_EXPORT &operator<<(QDataStream &stream, const BotInlineMessage &item);
QDataStream LIBQTELEGRAMSHARED_EXPORT &operator>>(QDataStream &stream, BotInlineMessage &item);

inline BotInlineMessage::BotInlineMessage(BotInlineMessageClassType classType, InboundPkt *in) :
    m_flags(0),
    m_classType(classType)
{
    if(in) fetch(in);
}

inline BotInlineMessage::BotInlineMessage(InboundPkt *in) :
    m_flags(0),
    m_classType(typeBotInlineMessageMediaAuto)
{
    fetch(in);
}

inline BotInlineMessage::BotInlineMessage(const Null &null) :
    TelegramTypeObject(null),
    m_flags(0),
    m_classType(typeBotInlineMessageMediaAuto)
{
}

inline BotInlineMessage::~BotInlineMessage() {
}

inline void BotInlineMessage::setAddress(const QString &address) {
    m_address = address;
}

inline QString BotInlineMessage::address() const {
    return m_address;
}

inline void BotInlineMessage::setCaption(const QString &caption) {
    m_caption = caption;
}

inline QString BotInlineMessage::caption() const {
    return m_caption;
}

inline void BotInlineMessage::setEntities(const QList<MessageEntity> &entities) {
    m_entities = entities;
}

inline QList<MessageEntity> BotInlineMessage::entities() const {
    return m_entities;
}

inline void BotInlineMessage::setFirstName(const QString &firstName) {
    m_firstName = firstName;
}

inline QString BotInlineMessage::firstName() const {
    return m_firstName;
}

inline void BotInlineMessage::setFlags(qint32 flags) {
    m_flags = flags;
}

inline qint32 BotInlineMessage::flags() const {
    return m_flags;
}

inline void BotInlineMessage::setGeo(const GeoPoint &geo) {
    m_geo = geo;
}

inline GeoPoint BotInlineMessage::geo() const {
    return m_geo;
}

inline void BotInlineMessage::setLastName(const QString &lastName) {
    m_lastName = lastName;
}

inline QString BotInlineMessage::lastName() const {
    return m_lastName;
}

inline void BotInlineMessage::setMessage(const QString &message) {
    m_message = message;
}

inline QString BotInlineMessage::message() const {
    return m_message;
}

inline void BotInlineMessage::setNoWebpage(bool noWebpage) {
    if(noWebpage) m_flags = (m_flags | (1<<0));
    else m_flags = (m_flags & ~(1<<0));
}

inline bool BotInlineMessage::noWebpage() const {
    return (m_flags & 1<<0);
}

inline void BotInlineMessage::setPhoneNumber(const QString &phoneNumber) {
    m_phoneNumber = phoneNumber;
}

inline QString BotInlineMessage::phoneNumber() const {
    return m_phoneNumber;
}

inline void BotInlineMessage::setProvider(const QString &provider) {
    m_provider = provider;
}

inline QString BotInlineMessage::provider() const {
    return m_provider;
}

inline void BotInlineMessage::setReplyMarkup(const ReplyMarkup &replyMarkup) {
    m_replyMarkup = replyMarkup;
}

inline ReplyMarkup BotInlineMessage::replyMarkup() const {
    return m_replyMarkup;
}

inline void BotInlineMessage::setTitle(const QString &title) {
    m_title = title;
}

inline QString BotInlineMessage::title() const {
    return m_title;
}

inline void BotInlineMessage::setVenueId(const QString &venueId) {
    m_venueId = venueId;
}

inline QString BotInlineMessage::venueId() const {
    return m_venueId;
}

inline bool BotInlineMessage::operator ==(const BotInlineMessage &b) const {
    return m_classType == b.m_classType &&
           m_address == b.m_address &&
           m_caption == b.m_caption &&
           m_entities == b.m_entities &&
           m_firstName == b.m_firstName &&
           m_flags == b.m_flags &&
           m_geo == b.m_geo &&
           m_lastName == b.m_lastName &&
           m_message == b.m_message &&
           m_phoneNumber == b.m_phoneNumber &&
           m_provider == b.m_provider &&
           m_replyMarkup == b.m_replyMarkup &&
           m_title == b.m_title &&
           m_venueId == b.m_venueId;
}

inline void BotInlineMessage::setClassType(BotInlineMessage::BotInlineMessageClassType classType) {
    m_classType = classType;
}

inline BotInlineMessage::BotInlineMessageClassType BotInlineMessage::classType() const {
    return m_classType;
}

inline bool BotInlineMessage::fetch(InboundPkt *in) {
    LQTG_FETCH_LOG;
    int x = in->fetchInt();
    switch(x) {
    case typeBotInlineMessageMediaAuto: {
        m_flags = in->fetchInt();
        m_caption = in->fetchQString();
        if(m_flags & 1<<2) {
            m_replyMarkup.fetch(in);
        }
        m_classType = static_cast<BotInlineMessageClassType>(x);
        return true;
    }
        break;
    
    case typeBotInlineMessageText: {
        m_flags = in->fetchInt();
        m_message = in->fetchQString();
        if(m_flags & 1<<1) {
            if(in->fetchInt() != (qint32)CoreTypes::typeVector) return false;
            qint32 m_entities_length = in->fetchInt();
            m_entities.clear();
            for (qint32 i = 0; i < m_entities_length; i++) {
                MessageEntity type;
                if(m_flags & 1<<1) {
                type.fetch(in);
            }
                m_entities.append(type);
            }
        }
        if(m_flags & 1<<2) {
            m_replyMarkup.fetch(in);
        }
        m_classType = static_cast<BotInlineMessageClassType>(x);
        return true;
    }
        break;
    
    case typeBotInlineMessageMediaGeo: {
        m_flags = in->fetchInt();
        m_geo.fetch(in);
        if(m_flags & 1<<2) {
            m_replyMarkup.fetch(in);
        }
        m_classType = static_cast<BotInlineMessageClassType>(x);
        return true;
    }
        break;
    
    case typeBotInlineMessageMediaVenue: {
        m_flags = in->fetchInt();
        m_geo.fetch(in);
        m_title = in->fetchQString();
        m_address = in->fetchQString();
        m_provider = in->fetchQString();
        m_venueId = in->fetchQString();
        if(m_flags & 1<<2) {
            m_replyMarkup.fetch(in);
        }
        m_classType = static_cast<BotInlineMessageClassType>(x);
        return true;
    }
        break;
    
    case typeBotInlineMessageMediaContact: {
        m_flags = in->fetchInt();
        m_phoneNumber = in->fetchQString();
        m_firstName = in->fetchQString();
        m_lastName = in->fetchQString();
        if(m_flags & 1<<2) {
            m_replyMarkup.fetch(in);
        }
        m_classType = static_cast<BotInlineMessageClassType>(x);
        return true;
    }
        break;
    
    default:
        LQTG_FETCH_ASSERT;
        return false;
    }
}

inline bool BotInlineMessage::push(OutboundPkt *out) const {
    out->appendInt(m_classType);
    switch(m_classType) {
    case typeBotInlineMessageMediaAuto: {
        out->appendInt(m_flags);
        out->appendQString(m_caption);
        m_replyMarkup.push(out);
        return true;
    }
        break;
    
    case typeBotInlineMessageText: {
        out->appendInt(m_flags);
        out->appendQString(m_message);
        out->appendInt(CoreTypes::typeVector);
        out->appendInt(m_entities.count());
        for (qint32 i = 0; i < m_entities.count(); i++) {
            m_entities[i].push(out);
        }
        m_replyMarkup.push(out);
        return true;
    }
        break;
    
    case typeBotInlineMessageMediaGeo: {
        out->appendInt(m_flags);
        m_geo.push(out);
        m_replyMarkup.push(out);
        return true;
    }
        break;
    
    case typeBotInlineMessageMediaVenue: {
        out->appendInt(m_flags);
        m_geo.push(out);
        out->appendQString(m_title);
        out->appendQString(m_address);
        out->appendQString(m_provider);
        out->appendQString(m_venueId);
        m_replyMarkup.push(out);
        return true;
    }
        break;
    
    case typeBotInlineMessageMediaContact: {
        out->appendInt(m_flags);
        out->appendQString(m_phoneNumber);
        out->appendQString(m_firstName);
        out->appendQString(m_lastName);
        m_replyMarkup.push(out);
        return true;
    }
        break;
    
    default:
        return false;
    }
}

inline QMap<QString, QVariant> BotInlineMessage::toMap() const {
    QMap<QString, QVariant> result;
    switch(static_cast<int>(m_classType)) {
    case typeBotInlineMessageMediaAuto: {
        result["classType"] = "BotInlineMessage::typeBotInlineMessageMediaAuto";
        result["caption"] = QVariant::fromValue<QString>(caption());
        result["replyMarkup"] = m_replyMarkup.toMap();
        return result;
    }
        break;
    
    case typeBotInlineMessageText: {
        result["classType"] = "BotInlineMessage::typeBotInlineMessageText";
        result["noWebpage"] = QVariant::fromValue<bool>(noWebpage());
        result["message"] = QVariant::fromValue<QString>(message());
        QList<QVariant> _entities;
        Q_FOREACH(const MessageEntity &m__type, m_entities)
            _entities << m__type.toMap();
        result["entities"] = _entities;
        result["replyMarkup"] = m_replyMarkup.toMap();
        return result;
    }
        break;
    
    case typeBotInlineMessageMediaGeo: {
        result["classType"] = "BotInlineMessage::typeBotInlineMessageMediaGeo";
        result["geo"] = m_geo.toMap();
        result["replyMarkup"] = m_replyMarkup.toMap();
        return result;
    }
        break;
    
    case typeBotInlineMessageMediaVenue: {
        result["classType"] = "BotInlineMessage::typeBotInlineMessageMediaVenue";
        result["geo"] = m_geo.toMap();
        result["title"] = QVariant::fromValue<QString>(title());
        result["address"] = QVariant::fromValue<QString>(address());
        result["provider"] = QVariant::fromValue<QString>(provider());
        result["venueId"] = QVariant::fromValue<QString>(venueId());
        result["replyMarkup"] = m_replyMarkup.toMap();
        return result;
    }
        break;
    
    case typeBotInlineMessageMediaContact: {
        result["classType"] = "BotInlineMessage::typeBotInlineMessageMediaContact";
        result["phoneNumber"] = QVariant::fromValue<QString>(phoneNumber());
        result["firstName"] = QVariant::fromValue<QString>(firstName());
        result["lastName"] = QVariant::fromValue<QString>(lastName());
        result["replyMarkup"] = m_replyMarkup.toMap();
        return result;
    }
        break;
    
    default:
        return result;
    }
}

inline BotInlineMessage BotInlineMessage::fromMap(const QMap<QString, QVariant> &map) {
    BotInlineMessage result;
    if(map.value("classType").toString() == "BotInlineMessage::typeBotInlineMessageMediaAuto") {
        result.setClassType(typeBotInlineMessageMediaAuto);
        result.setCaption( map.value("caption").value<QString>() );
        result.setReplyMarkup( ReplyMarkup::fromMap(map.value("replyMarkup").toMap()) );
        return result;
    }
    if(map.value("classType").toString() == "BotInlineMessage::typeBotInlineMessageText") {
        result.setClassType(typeBotInlineMessageText);
        result.setNoWebpage( map.value("noWebpage").value<bool>() );
        result.setMessage( map.value("message").value<QString>() );
        QList<QVariant> map_entities = map["entities"].toList();
        QList<MessageEntity> _entities;
        Q_FOREACH(const QVariant &var, map_entities)
            _entities << MessageEntity::fromMap(var.toMap());
        result.setEntities(_entities);
        result.setReplyMarkup( ReplyMarkup::fromMap(map.value("replyMarkup").toMap()) );
        return result;
    }
    if(map.value("classType").toString() == "BotInlineMessage::typeBotInlineMessageMediaGeo") {
        result.setClassType(typeBotInlineMessageMediaGeo);
        result.setGeo( GeoPoint::fromMap(map.value("geo").toMap()) );
        result.setReplyMarkup( ReplyMarkup::fromMap(map.value("replyMarkup").toMap()) );
        return result;
    }
    if(map.value("classType").toString() == "BotInlineMessage::typeBotInlineMessageMediaVenue") {
        result.setClassType(typeBotInlineMessageMediaVenue);
        result.setGeo( GeoPoint::fromMap(map.value("geo").toMap()) );
        result.setTitle( map.value("title").value<QString>() );
        result.setAddress( map.value("address").value<QString>() );
        result.setProvider( map.value("provider").value<QString>() );
        result.setVenueId( map.value("venueId").value<QString>() );
        result.setReplyMarkup( ReplyMarkup::fromMap(map.value("replyMarkup").toMap()) );
        return result;
    }
    if(map.value("classType").toString() == "BotInlineMessage::typeBotInlineMessageMediaContact") {
        result.setClassType(typeBotInlineMessageMediaContact);
        result.setPhoneNumber( map.value("phoneNumber").value<QString>() );
        result.setFirstName( map.value("firstName").value<QString>() );
        result.setLastName( map.value("lastName").value<QString>() );
        result.setReplyMarkup( ReplyMarkup::fromMap(map.value("replyMarkup").toMap()) );
        return result;
    }
    return result;
}

inline QByteArray BotInlineMessage::getHash(QCryptographicHash::Algorithm alg) const {
    QByteArray data;
    QDataStream str(&data, QIODevice::WriteOnly);
    str << *this;
    return QCryptographicHash::hash(data, alg);
}

inline QDataStream &operator<<(QDataStream &stream, const BotInlineMessage &item) {
    stream << static_cast<uint>(item.classType());
    switch(item.classType()) {
    case BotInlineMessage::typeBotInlineMessageMediaAuto:
        stream << item.flags();
        stream << item.caption();
        stream << item.replyMarkup();
        break;
    case BotInlineMessage::typeBotInlineMessageText:
        stream << item.flags();
        stream << item.message();
        stream << item.entities();
        stream << item.replyMarkup();
        break;
    case BotInlineMessage::typeBotInlineMessageMediaGeo:
        stream << item.flags();
        stream << item.geo();
        stream << item.replyMarkup();
        break;
    case BotInlineMessage::typeBotInlineMessageMediaVenue:
        stream << item.flags();
        stream << item.geo();
        stream << item.title();
        stream << item.address();
        stream << item.provider();
        stream << item.venueId();
        stream << item.replyMarkup();
        break;
    case BotInlineMessage::typeBotInlineMessageMediaContact:
        stream << item.flags();
        stream << item.phoneNumber();
        stream << item.firstName();
        stream << item.lastName();
        stream << item.replyMarkup();
        break;
    }
    return stream;
}

inline QDataStream &operator>>(QDataStream &stream, BotInlineMessage &item) {
    uint type = 0;
    stream >> type;
    item.setClassType(static_cast<BotInlineMessage::BotInlineMessageClassType>(type));
    switch(type) {
    case BotInlineMessage::typeBotInlineMessageMediaAuto: {
        qint32 m_flags;
        stream >> m_flags;
        item.setFlags(m_flags);
        QString m_caption;
        stream >> m_caption;
        item.setCaption(m_caption);
        ReplyMarkup m_reply_markup;
        stream >> m_reply_markup;
        item.setReplyMarkup(m_reply_markup);
    }
        break;
    case BotInlineMessage::typeBotInlineMessageText: {
        qint32 m_flags;
        stream >> m_flags;
        item.setFlags(m_flags);
        QString m_message;
        stream >> m_message;
        item.setMessage(m_message);
        QList<MessageEntity> m_entities;
        stream >> m_entities;
        item.setEntities(m_entities);
        ReplyMarkup m_reply_markup;
        stream >> m_reply_markup;
        item.setReplyMarkup(m_reply_markup);
    }
        break;
    case BotInlineMessage::typeBotInlineMessageMediaGeo: {
        qint32 m_flags;
        stream >> m_flags;
        item.setFlags(m_flags);
        GeoPoint m_geo;
        stream >> m_geo;
        item.setGeo(m_geo);
        ReplyMarkup m_reply_markup;
        stream >> m_reply_markup;
        item.setReplyMarkup(m_reply_markup);
    }
        break;
    case BotInlineMessage::typeBotInlineMessageMediaVenue: {
        qint32 m_flags;
        stream >> m_flags;
        item.setFlags(m_flags);
        GeoPoint m_geo;
        stream >> m_geo;
        item.setGeo(m_geo);
        QString m_title;
        stream >> m_title;
        item.setTitle(m_title);
        QString m_address;
        stream >> m_address;
        item.setAddress(m_address);
        QString m_provider;
        stream >> m_provider;
        item.setProvider(m_provider);
        QString m_venue_id;
        stream >> m_venue_id;
        item.setVenueId(m_venue_id);
        ReplyMarkup m_reply_markup;
        stream >> m_reply_markup;
        item.setReplyMarkup(m_reply_markup);
    }
        break;
    case BotInlineMessage::typeBotInlineMessageMediaContact: {
        qint32 m_flags;
        stream >> m_flags;
        item.setFlags(m_flags);
        QString m_phone_number;
        stream >> m_phone_number;
        item.setPhoneNumber(m_phone_number);
        QString m_first_name;
        stream >> m_first_name;
        item.setFirstName(m_first_name);
        QString m_last_name;
        stream >> m_last_name;
        item.setLastName(m_last_name);
        ReplyMarkup m_reply_markup;
        stream >> m_reply_markup;
        item.setReplyMarkup(m_reply_markup);
    }
        break;
    }
    return stream;
}


#endif // LQTG_TYPE_BOTINLINEMESSAGE
