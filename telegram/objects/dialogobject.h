// This file generated by libqtelegram-code-generator.
// You can download it from: https://github.com/Aseman-Land/libqtelegram-code-generator
// DO NOT EDIT THIS FILE BY HAND -- YOUR CHANGES WILL BE OVERWRITTEN

#ifndef LQTG_TYPE_DIALOG_OBJECT
#define LQTG_TYPE_DIALOG_OBJECT

#include "telegramtypeqobject.h"
#include "telegram/types/dialog.h"

#include <QPointer>
#include "peernotifysettingsobject.h"
#include "peerobject.h"

class LIBQTELEGRAMSHARED_EXPORT DialogObject : public TelegramTypeQObject
{
    Q_OBJECT
    Q_ENUMS(DialogClassType)
    Q_PROPERTY(PeerNotifySettingsObject* notifySettings READ notifySettings WRITE setNotifySettings NOTIFY notifySettingsChanged)
    Q_PROPERTY(PeerObject* peer READ peer WRITE setPeer NOTIFY peerChanged)
    Q_PROPERTY(qint32 readInboxMaxId READ readInboxMaxId WRITE setReadInboxMaxId NOTIFY readInboxMaxIdChanged)
    Q_PROPERTY(qint32 topMessage READ topMessage WRITE setTopMessage NOTIFY topMessageChanged)
    Q_PROPERTY(qint32 unreadCount READ unreadCount WRITE setUnreadCount NOTIFY unreadCountChanged)
    Q_PROPERTY(Dialog core READ core WRITE setCore NOTIFY coreChanged)
    Q_PROPERTY(quint32 classType READ classType WRITE setClassType NOTIFY classTypeChanged)

public:
    enum DialogClassType {
        TypeDialog
    };

    DialogObject(const Dialog &core, QObject *parent = 0);
    DialogObject(QObject *parent = 0);
    virtual ~DialogObject();

    void setNotifySettings(PeerNotifySettingsObject* notifySettings);
    PeerNotifySettingsObject* notifySettings() const;

    void setPeer(PeerObject* peer);
    PeerObject* peer() const;

    void setReadInboxMaxId(qint32 readInboxMaxId);
    qint32 readInboxMaxId() const;

    void setTopMessage(qint32 topMessage);
    qint32 topMessage() const;

    void setUnreadCount(qint32 unreadCount);
    qint32 unreadCount() const;

    void setClassType(quint32 classType);
    quint32 classType() const;

    void setCore(const Dialog &core);
    Dialog core() const;

    DialogObject &operator =(const Dialog &b);
    bool operator ==(const Dialog &b) const;

Q_SIGNALS:
    void coreChanged();
    void classTypeChanged();
    void notifySettingsChanged();
    void peerChanged();
    void readInboxMaxIdChanged();
    void topMessageChanged();
    void unreadCountChanged();

private Q_SLOTS:
    void coreNotifySettingsChanged();
    void corePeerChanged();

private:
    QPointer<PeerNotifySettingsObject> m_notifySettings;
    QPointer<PeerObject> m_peer;
    Dialog m_core;
};

inline DialogObject::DialogObject(const Dialog &core, QObject *parent) :
    TelegramTypeQObject(parent),
    m_notifySettings(0),
    m_peer(0),
    m_core(core)
{
    m_notifySettings = new PeerNotifySettingsObject(m_core.notifySettings(), this);
    connect(m_notifySettings.data(), &PeerNotifySettingsObject::coreChanged, this, &DialogObject::coreNotifySettingsChanged);
    m_peer = new PeerObject(m_core.peer(), this);
    connect(m_peer.data(), &PeerObject::coreChanged, this, &DialogObject::corePeerChanged);
}

inline DialogObject::DialogObject(QObject *parent) :
    TelegramTypeQObject(parent),
    m_notifySettings(0),
    m_peer(0),
    m_core()
{
    m_notifySettings = new PeerNotifySettingsObject(m_core.notifySettings(), this);
    connect(m_notifySettings.data(), &PeerNotifySettingsObject::coreChanged, this, &DialogObject::coreNotifySettingsChanged);
    m_peer = new PeerObject(m_core.peer(), this);
    connect(m_peer.data(), &PeerObject::coreChanged, this, &DialogObject::corePeerChanged);
}

inline DialogObject::~DialogObject() {
}

inline void DialogObject::setNotifySettings(PeerNotifySettingsObject* notifySettings) {
    if(m_notifySettings == notifySettings) return;
    if(m_notifySettings) delete m_notifySettings;
    m_notifySettings = notifySettings;
    if(m_notifySettings) {
        m_notifySettings->setParent(this);
        m_core.setNotifySettings(m_notifySettings->core());
        connect(m_notifySettings.data(), &PeerNotifySettingsObject::coreChanged, this, &DialogObject::coreNotifySettingsChanged);
    }
    Q_EMIT notifySettingsChanged();
    Q_EMIT coreChanged();
}

inline PeerNotifySettingsObject*  DialogObject::notifySettings() const {
    return m_notifySettings;
}

inline void DialogObject::setPeer(PeerObject* peer) {
    if(m_peer == peer) return;
    if(m_peer) delete m_peer;
    m_peer = peer;
    if(m_peer) {
        m_peer->setParent(this);
        m_core.setPeer(m_peer->core());
        connect(m_peer.data(), &PeerObject::coreChanged, this, &DialogObject::corePeerChanged);
    }
    Q_EMIT peerChanged();
    Q_EMIT coreChanged();
}

inline PeerObject*  DialogObject::peer() const {
    return m_peer;
}

inline void DialogObject::setReadInboxMaxId(qint32 readInboxMaxId) {
    if(m_core.readInboxMaxId() == readInboxMaxId) return;
    m_core.setReadInboxMaxId(readInboxMaxId);
    Q_EMIT readInboxMaxIdChanged();
    Q_EMIT coreChanged();
}

inline qint32 DialogObject::readInboxMaxId() const {
    return m_core.readInboxMaxId();
}

inline void DialogObject::setTopMessage(qint32 topMessage) {
    if(m_core.topMessage() == topMessage) return;
    m_core.setTopMessage(topMessage);
    Q_EMIT topMessageChanged();
    Q_EMIT coreChanged();
}

inline qint32 DialogObject::topMessage() const {
    return m_core.topMessage();
}

inline void DialogObject::setUnreadCount(qint32 unreadCount) {
    if(m_core.unreadCount() == unreadCount) return;
    m_core.setUnreadCount(unreadCount);
    Q_EMIT unreadCountChanged();
    Q_EMIT coreChanged();
}

inline qint32 DialogObject::unreadCount() const {
    return m_core.unreadCount();
}

inline DialogObject &DialogObject::operator =(const Dialog &b) {
    if(m_core == b) return *this;
    m_core = b;
    m_notifySettings->setCore(b.notifySettings());
    m_peer->setCore(b.peer());

    Q_EMIT notifySettingsChanged();
    Q_EMIT peerChanged();
    Q_EMIT readInboxMaxIdChanged();
    Q_EMIT topMessageChanged();
    Q_EMIT unreadCountChanged();
    Q_EMIT coreChanged();
    return *this;
}

inline bool DialogObject::operator ==(const Dialog &b) const {
    return m_core == b;
}

inline void DialogObject::setClassType(quint32 classType) {
    Dialog::DialogClassType result;
    switch(classType) {
    case TypeDialog:
        result = Dialog::typeDialog;
        break;
    default:
        result = Dialog::typeDialog;
        break;
    }

    if(m_core.classType() == result) return;
    m_core.setClassType(result);
    Q_EMIT classTypeChanged();
    Q_EMIT coreChanged();
}

inline quint32 DialogObject::classType() const {
    int result;
    switch(static_cast<qint64>(m_core.classType())) {
    case Dialog::typeDialog:
        result = TypeDialog;
        break;
    default:
        result = TypeDialog;
        break;
    }

    return result;
}

inline void DialogObject::setCore(const Dialog &core) {
    operator =(core);
}

inline Dialog DialogObject::core() const {
    return m_core;
}

inline void DialogObject::coreNotifySettingsChanged() {
    if(m_core.notifySettings() == m_notifySettings->core()) return;
    m_core.setNotifySettings(m_notifySettings->core());
    Q_EMIT notifySettingsChanged();
    Q_EMIT coreChanged();
}

inline void DialogObject::corePeerChanged() {
    if(m_core.peer() == m_peer->core()) return;
    m_core.setPeer(m_peer->core());
    Q_EMIT peerChanged();
    Q_EMIT coreChanged();
}

#endif // LQTG_TYPE_DIALOG_OBJECT
