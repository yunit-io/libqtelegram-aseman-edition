// This file generated by libqtelegram-code-generator.
// You can download it from: https://github.com/Aseman-Land/libqtelegram-code-generator
// DO NOT EDIT THIS FILE BY HAND -- YOUR CHANGES WILL BE OVERWRITTEN

#ifndef LQTG_TYPE_NOTIFYPEER_OBJECT
#define LQTG_TYPE_NOTIFYPEER_OBJECT

#include "telegramtypeqobject.h"
#include "telegram/types/notifypeer.h"

#include <QPointer>
#include "peerobject.h"

class LIBQTELEGRAMSHARED_EXPORT NotifyPeerObject : public TelegramTypeQObject
{
    Q_OBJECT
    Q_ENUMS(NotifyPeerClassType)
    Q_PROPERTY(PeerObject* peer READ peer WRITE setPeer NOTIFY peerChanged)
    Q_PROPERTY(NotifyPeer core READ core WRITE setCore NOTIFY coreChanged)
    Q_PROPERTY(quint32 classType READ classType WRITE setClassType NOTIFY classTypeChanged)

public:
    enum NotifyPeerClassType {
        TypeNotifyAll,
        TypeNotifyChats,
        TypeNotifyPeer,
        TypeNotifyUsers
    };

    NotifyPeerObject(const NotifyPeer &core, QObject *parent = 0);
    NotifyPeerObject(QObject *parent = 0);
    virtual ~NotifyPeerObject();

    void setPeer(PeerObject* peer);
    PeerObject* peer() const;

    void setClassType(quint32 classType);
    quint32 classType() const;

    void setCore(const NotifyPeer &core);
    NotifyPeer core() const;

    NotifyPeerObject &operator =(const NotifyPeer &b);
    bool operator ==(const NotifyPeer &b) const;

Q_SIGNALS:
    void coreChanged();
    void classTypeChanged();
    void peerChanged();

private Q_SLOTS:
    void corePeerChanged();

private:
    QPointer<PeerObject> m_peer;
    NotifyPeer m_core;
};

inline NotifyPeerObject::NotifyPeerObject(const NotifyPeer &core, QObject *parent) :
    TelegramTypeQObject(parent),
    m_peer(0),
    m_core(core)
{
    m_peer = new PeerObject(m_core.peer(), this);
    connect(m_peer.data(), &PeerObject::coreChanged, this, &NotifyPeerObject::corePeerChanged);
}

inline NotifyPeerObject::NotifyPeerObject(QObject *parent) :
    TelegramTypeQObject(parent),
    m_peer(0),
    m_core()
{
    m_peer = new PeerObject(m_core.peer(), this);
    connect(m_peer.data(), &PeerObject::coreChanged, this, &NotifyPeerObject::corePeerChanged);
}

inline NotifyPeerObject::~NotifyPeerObject() {
}

inline void NotifyPeerObject::setPeer(PeerObject* peer) {
    if(m_peer == peer) return;
    if(m_peer) delete m_peer;
    m_peer = peer;
    if(m_peer) {
        m_peer->setParent(this);
        m_core.setPeer(m_peer->core());
        connect(m_peer.data(), &PeerObject::coreChanged, this, &NotifyPeerObject::corePeerChanged);
    }
    Q_EMIT peerChanged();
    Q_EMIT coreChanged();
}

inline PeerObject*  NotifyPeerObject::peer() const {
    return m_peer;
}

inline NotifyPeerObject &NotifyPeerObject::operator =(const NotifyPeer &b) {
    if(m_core == b) return *this;
    m_core = b;
    m_peer->setCore(b.peer());

    Q_EMIT peerChanged();
    Q_EMIT coreChanged();
    return *this;
}

inline bool NotifyPeerObject::operator ==(const NotifyPeer &b) const {
    return m_core == b;
}

inline void NotifyPeerObject::setClassType(quint32 classType) {
    NotifyPeer::NotifyPeerClassType result;
    switch(classType) {
    case TypeNotifyAll:
        result = NotifyPeer::typeNotifyAll;
        break;
    case TypeNotifyChats:
        result = NotifyPeer::typeNotifyChats;
        break;
    case TypeNotifyPeer:
        result = NotifyPeer::typeNotifyPeer;
        break;
    case TypeNotifyUsers:
        result = NotifyPeer::typeNotifyUsers;
        break;
    default:
        result = NotifyPeer::typeNotifyAll;
        break;
    }

    if(m_core.classType() == result) return;
    m_core.setClassType(result);
    Q_EMIT classTypeChanged();
    Q_EMIT coreChanged();
}

inline quint32 NotifyPeerObject::classType() const {
    int result;
    switch(static_cast<qint64>(m_core.classType())) {
    case NotifyPeer::typeNotifyAll:
        result = TypeNotifyAll;
        break;
    case NotifyPeer::typeNotifyChats:
        result = TypeNotifyChats;
        break;
    case NotifyPeer::typeNotifyPeer:
        result = TypeNotifyPeer;
        break;
    case NotifyPeer::typeNotifyUsers:
        result = TypeNotifyUsers;
        break;
    default:
        result = TypeNotifyAll;
        break;
    }

    return result;
}

inline void NotifyPeerObject::setCore(const NotifyPeer &core) {
    operator =(core);
}

inline NotifyPeer NotifyPeerObject::core() const {
    return m_core;
}

inline void NotifyPeerObject::corePeerChanged() {
    if(m_core.peer() == m_peer->core()) return;
    m_core.setPeer(m_peer->core());
    Q_EMIT peerChanged();
    Q_EMIT coreChanged();
}

#endif // LQTG_TYPE_NOTIFYPEER_OBJECT
