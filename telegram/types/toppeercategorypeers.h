// This file generated by libqtelegram-code-generator.
// You can download it from: https://github.com/Aseman-Land/libqtelegram-code-generator
// DO NOT EDIT THIS FILE BY HAND -- YOUR CHANGES WILL BE OVERWRITTEN

#ifndef LQTG_TYPE_TOPPEERCATEGORYPEERS
#define LQTG_TYPE_TOPPEERCATEGORYPEERS

#include "telegramtypeobject.h"

#include <QMetaType>
#include <QVariant>
#include "core/inboundpkt.h"
#include "core/outboundpkt.h"
#include "../coretypes.h"

#include <QDataStream>

#include "toppeercategory.h"
#include <QtGlobal>
#include <QList>
#include "toppeer.h"

class LIBQTELEGRAMSHARED_EXPORT TopPeerCategoryPeers : public TelegramTypeObject
{
public:
    enum TopPeerCategoryPeersClassType {
        typeTopPeerCategoryPeers = 0xfb834291
    };

    TopPeerCategoryPeers(TopPeerCategoryPeersClassType classType = typeTopPeerCategoryPeers, InboundPkt *in = 0);
    TopPeerCategoryPeers(InboundPkt *in);
    TopPeerCategoryPeers(const Null&);
    virtual ~TopPeerCategoryPeers();

    void setCategory(const TopPeerCategory &category);
    TopPeerCategory category() const;

    void setCount(qint32 count);
    qint32 count() const;

    void setPeers(const QList<TopPeer> &peers);
    QList<TopPeer> peers() const;

    void setClassType(TopPeerCategoryPeersClassType classType);
    TopPeerCategoryPeersClassType classType() const;

    bool fetch(InboundPkt *in);
    bool push(OutboundPkt *out) const;

    QMap<QString, QVariant> toMap() const;
    static TopPeerCategoryPeers fromMap(const QMap<QString, QVariant> &map);

    bool operator ==(const TopPeerCategoryPeers &b) const;

    bool operator==(bool stt) const { return isNull() != stt; }
    bool operator!=(bool stt) const { return !operator ==(stt); }

    QByteArray getHash(QCryptographicHash::Algorithm alg = QCryptographicHash::Md5) const;

private:
    TopPeerCategory m_category;
    qint32 m_count;
    QList<TopPeer> m_peers;
    TopPeerCategoryPeersClassType m_classType;
};

Q_DECLARE_METATYPE(TopPeerCategoryPeers)

QDataStream LIBQTELEGRAMSHARED_EXPORT &operator<<(QDataStream &stream, const TopPeerCategoryPeers &item);
QDataStream LIBQTELEGRAMSHARED_EXPORT &operator>>(QDataStream &stream, TopPeerCategoryPeers &item);

inline TopPeerCategoryPeers::TopPeerCategoryPeers(TopPeerCategoryPeersClassType classType, InboundPkt *in) :
    m_count(0),
    m_classType(classType)
{
    if(in) fetch(in);
}

inline TopPeerCategoryPeers::TopPeerCategoryPeers(InboundPkt *in) :
    m_count(0),
    m_classType(typeTopPeerCategoryPeers)
{
    fetch(in);
}

inline TopPeerCategoryPeers::TopPeerCategoryPeers(const Null &null) :
    TelegramTypeObject(null),
    m_count(0),
    m_classType(typeTopPeerCategoryPeers)
{
}

inline TopPeerCategoryPeers::~TopPeerCategoryPeers() {
}

inline void TopPeerCategoryPeers::setCategory(const TopPeerCategory &category) {
    m_category = category;
}

inline TopPeerCategory TopPeerCategoryPeers::category() const {
    return m_category;
}

inline void TopPeerCategoryPeers::setCount(qint32 count) {
    m_count = count;
}

inline qint32 TopPeerCategoryPeers::count() const {
    return m_count;
}

inline void TopPeerCategoryPeers::setPeers(const QList<TopPeer> &peers) {
    m_peers = peers;
}

inline QList<TopPeer> TopPeerCategoryPeers::peers() const {
    return m_peers;
}

inline bool TopPeerCategoryPeers::operator ==(const TopPeerCategoryPeers &b) const {
    return m_classType == b.m_classType &&
           m_category == b.m_category &&
           m_count == b.m_count &&
           m_peers == b.m_peers;
}

inline void TopPeerCategoryPeers::setClassType(TopPeerCategoryPeers::TopPeerCategoryPeersClassType classType) {
    m_classType = classType;
}

inline TopPeerCategoryPeers::TopPeerCategoryPeersClassType TopPeerCategoryPeers::classType() const {
    return m_classType;
}

inline bool TopPeerCategoryPeers::fetch(InboundPkt *in) {
    LQTG_FETCH_LOG;
    int x = in->fetchInt();
    switch(x) {
    case typeTopPeerCategoryPeers: {
        m_category.fetch(in);
        m_count = in->fetchInt();
        if(in->fetchInt() != (qint32)CoreTypes::typeVector) return false;
        qint32 m_peers_length = in->fetchInt();
        m_peers.clear();
        for (qint32 i = 0; i < m_peers_length; i++) {
            TopPeer type;
            type.fetch(in);
            m_peers.append(type);
        }
        m_classType = static_cast<TopPeerCategoryPeersClassType>(x);
        return true;
    }
        break;
    
    default:
        LQTG_FETCH_ASSERT;
        return false;
    }
}

inline bool TopPeerCategoryPeers::push(OutboundPkt *out) const {
    out->appendInt(m_classType);
    switch(m_classType) {
    case typeTopPeerCategoryPeers: {
        m_category.push(out);
        out->appendInt(m_count);
        out->appendInt(CoreTypes::typeVector);
        out->appendInt(m_peers.count());
        for (qint32 i = 0; i < m_peers.count(); i++) {
            m_peers[i].push(out);
        }
        return true;
    }
        break;
    
    default:
        return false;
    }
}

inline QMap<QString, QVariant> TopPeerCategoryPeers::toMap() const {
    QMap<QString, QVariant> result;
    switch(static_cast<int>(m_classType)) {
    case typeTopPeerCategoryPeers: {
        result["classType"] = "TopPeerCategoryPeers::typeTopPeerCategoryPeers";
        result["category"] = m_category.toMap();
        result["count"] = QVariant::fromValue<qint32>(count());
        QList<QVariant> _peers;
        Q_FOREACH(const TopPeer &m__type, m_peers)
            _peers << m__type.toMap();
        result["peers"] = _peers;
        return result;
    }
        break;
    
    default:
        return result;
    }
}

inline TopPeerCategoryPeers TopPeerCategoryPeers::fromMap(const QMap<QString, QVariant> &map) {
    TopPeerCategoryPeers result;
    if(map.value("classType").toString() == "TopPeerCategoryPeers::typeTopPeerCategoryPeers") {
        result.setClassType(typeTopPeerCategoryPeers);
        result.setCategory( TopPeerCategory::fromMap(map.value("category").toMap()) );
        result.setCount( map.value("count").value<qint32>() );
        QList<QVariant> map_peers = map["peers"].toList();
        QList<TopPeer> _peers;
        Q_FOREACH(const QVariant &var, map_peers)
            _peers << TopPeer::fromMap(var.toMap());
        result.setPeers(_peers);
        return result;
    }
    return result;
}

inline QByteArray TopPeerCategoryPeers::getHash(QCryptographicHash::Algorithm alg) const {
    QByteArray data;
    QDataStream str(&data, QIODevice::WriteOnly);
    str << *this;
    return QCryptographicHash::hash(data, alg);
}

inline QDataStream &operator<<(QDataStream &stream, const TopPeerCategoryPeers &item) {
    stream << static_cast<uint>(item.classType());
    switch(item.classType()) {
    case TopPeerCategoryPeers::typeTopPeerCategoryPeers:
        stream << item.category();
        stream << item.count();
        stream << item.peers();
        break;
    }
    return stream;
}

inline QDataStream &operator>>(QDataStream &stream, TopPeerCategoryPeers &item) {
    uint type = 0;
    stream >> type;
    item.setClassType(static_cast<TopPeerCategoryPeers::TopPeerCategoryPeersClassType>(type));
    switch(type) {
    case TopPeerCategoryPeers::typeTopPeerCategoryPeers: {
        TopPeerCategory m_category;
        stream >> m_category;
        item.setCategory(m_category);
        qint32 m_count;
        stream >> m_count;
        item.setCount(m_count);
        QList<TopPeer> m_peers;
        stream >> m_peers;
        item.setPeers(m_peers);
    }
        break;
    }
    return stream;
}


#endif // LQTG_TYPE_TOPPEERCATEGORYPEERS
