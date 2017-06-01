// This file generated by libqtelegram-code-generator.
// You can download it from: https://github.com/Aseman-Land/libqtelegram-code-generator
// DO NOT EDIT THIS FILE BY HAND -- YOUR CHANGES WILL BE OVERWRITTEN

#ifndef LQTG_TYPE_INPUTNOTIFYPEER_OBJECT
#define LQTG_TYPE_INPUTNOTIFYPEER_OBJECT

#include "telegramtypeqobject.h"
#include "telegram/types/inputnotifypeer.h"

#include <QPointer>
#include "inputgeochatobject.h"
#include "inputpeerobject.h"

class LIBQTELEGRAMSHARED_EXPORT InputNotifyPeerObject : public TelegramTypeQObject
{
    Q_OBJECT
    Q_ENUMS(InputNotifyPeerClassType)
    Q_PROPERTY(InputGeoChatObject* peerInputGeoChat READ peerInputGeoChat WRITE setPeerInputGeoChat NOTIFY peerInputGeoChatChanged)
    Q_PROPERTY(InputPeerObject* peerInput READ peerInput WRITE setPeerInput NOTIFY peerInputChanged)
    Q_PROPERTY(InputNotifyPeer core READ core WRITE setCore NOTIFY coreChanged)
    Q_PROPERTY(quint32 classType READ classType WRITE setClassType NOTIFY classTypeChanged)

public:
    enum InputNotifyPeerClassType {
        TypeInputNotifyPeer,
        TypeInputNotifyUsers,
        TypeInputNotifyChats,
        TypeInputNotifyAll,
        TypeInputNotifyGeoChatPeer
    };

    InputNotifyPeerObject(const InputNotifyPeer &core, QObject *parent = 0);
    InputNotifyPeerObject(QObject *parent = 0);
    virtual ~InputNotifyPeerObject();

    void setPeerInputGeoChat(InputGeoChatObject* peerInputGeoChat);
    InputGeoChatObject* peerInputGeoChat() const;

    void setPeerInput(InputPeerObject* peerInput);
    InputPeerObject* peerInput() const;

    void setClassType(quint32 classType);
    quint32 classType() const;

    void setCore(const InputNotifyPeer &core);
    InputNotifyPeer core() const;

    InputNotifyPeerObject &operator =(const InputNotifyPeer &b);
    bool operator ==(const InputNotifyPeer &b) const;

Q_SIGNALS:
    void coreChanged();
    void classTypeChanged();
    void peerInputGeoChatChanged();
    void peerInputChanged();

private Q_SLOTS:
    void corePeerInputGeoChatChanged();
    void corePeerInputChanged();

private:
    QPointer<InputGeoChatObject> m_peerInputGeoChat;
    QPointer<InputPeerObject> m_peerInput;
    InputNotifyPeer m_core;
};

inline InputNotifyPeerObject::InputNotifyPeerObject(const InputNotifyPeer &core, QObject *parent) :
    TelegramTypeQObject(parent),
    m_peerInputGeoChat(0),
    m_peerInput(0),
    m_core(core)
{
    m_peerInputGeoChat = new InputGeoChatObject(m_core.peerInputGeoChat(), this);
    connect(m_peerInputGeoChat.data(), &InputGeoChatObject::coreChanged, this, &InputNotifyPeerObject::corePeerInputGeoChatChanged);
    m_peerInput = new InputPeerObject(m_core.peerInput(), this);
    connect(m_peerInput.data(), &InputPeerObject::coreChanged, this, &InputNotifyPeerObject::corePeerInputChanged);
}

inline InputNotifyPeerObject::InputNotifyPeerObject(QObject *parent) :
    TelegramTypeQObject(parent),
    m_peerInputGeoChat(0),
    m_peerInput(0),
    m_core()
{
    m_peerInputGeoChat = new InputGeoChatObject(m_core.peerInputGeoChat(), this);
    connect(m_peerInputGeoChat.data(), &InputGeoChatObject::coreChanged, this, &InputNotifyPeerObject::corePeerInputGeoChatChanged);
    m_peerInput = new InputPeerObject(m_core.peerInput(), this);
    connect(m_peerInput.data(), &InputPeerObject::coreChanged, this, &InputNotifyPeerObject::corePeerInputChanged);
}

inline InputNotifyPeerObject::~InputNotifyPeerObject() {
}

inline void InputNotifyPeerObject::setPeerInputGeoChat(InputGeoChatObject* peerInputGeoChat) {
    if(m_peerInputGeoChat == peerInputGeoChat) return;
    if(m_peerInputGeoChat) delete m_peerInputGeoChat;
    m_peerInputGeoChat = peerInputGeoChat;
    if(m_peerInputGeoChat) {
        m_peerInputGeoChat->setParent(this);
        m_core.setPeerInputGeoChat(m_peerInputGeoChat->core());
        connect(m_peerInputGeoChat.data(), &InputGeoChatObject::coreChanged, this, &InputNotifyPeerObject::corePeerInputGeoChatChanged);
    }
    Q_EMIT peerInputGeoChatChanged();
    Q_EMIT coreChanged();
}

inline InputGeoChatObject*  InputNotifyPeerObject::peerInputGeoChat() const {
    return m_peerInputGeoChat;
}

inline void InputNotifyPeerObject::setPeerInput(InputPeerObject* peerInput) {
    if(m_peerInput == peerInput) return;
    if(m_peerInput) delete m_peerInput;
    m_peerInput = peerInput;
    if(m_peerInput) {
        m_peerInput->setParent(this);
        m_core.setPeerInput(m_peerInput->core());
        connect(m_peerInput.data(), &InputPeerObject::coreChanged, this, &InputNotifyPeerObject::corePeerInputChanged);
    }
    Q_EMIT peerInputChanged();
    Q_EMIT coreChanged();
}

inline InputPeerObject*  InputNotifyPeerObject::peerInput() const {
    return m_peerInput;
}

inline InputNotifyPeerObject &InputNotifyPeerObject::operator =(const InputNotifyPeer &b) {
    if(m_core == b) return *this;
    m_core = b;
    m_peerInputGeoChat->setCore(b.peerInputGeoChat());
    m_peerInput->setCore(b.peerInput());

    Q_EMIT peerInputGeoChatChanged();
    Q_EMIT peerInputChanged();
    Q_EMIT coreChanged();
    return *this;
}

inline bool InputNotifyPeerObject::operator ==(const InputNotifyPeer &b) const {
    return m_core == b;
}

inline void InputNotifyPeerObject::setClassType(quint32 classType) {
    InputNotifyPeer::InputNotifyPeerClassType result;
    switch(classType) {
    case TypeInputNotifyPeer:
        result = InputNotifyPeer::typeInputNotifyPeer;
        break;
    case TypeInputNotifyUsers:
        result = InputNotifyPeer::typeInputNotifyUsers;
        break;
    case TypeInputNotifyChats:
        result = InputNotifyPeer::typeInputNotifyChats;
        break;
    case TypeInputNotifyAll:
        result = InputNotifyPeer::typeInputNotifyAll;
        break;
    case TypeInputNotifyGeoChatPeer:
        result = InputNotifyPeer::typeInputNotifyGeoChatPeer;
        break;
    default:
        result = InputNotifyPeer::typeInputNotifyPeer;
        break;
    }

    if(m_core.classType() == result) return;
    m_core.setClassType(result);
    Q_EMIT classTypeChanged();
    Q_EMIT coreChanged();
}

inline quint32 InputNotifyPeerObject::classType() const {
    int result;
    switch(static_cast<qint64>(m_core.classType())) {
    case InputNotifyPeer::typeInputNotifyPeer:
        result = TypeInputNotifyPeer;
        break;
    case InputNotifyPeer::typeInputNotifyUsers:
        result = TypeInputNotifyUsers;
        break;
    case InputNotifyPeer::typeInputNotifyChats:
        result = TypeInputNotifyChats;
        break;
    case InputNotifyPeer::typeInputNotifyAll:
        result = TypeInputNotifyAll;
        break;
    case InputNotifyPeer::typeInputNotifyGeoChatPeer:
        result = TypeInputNotifyGeoChatPeer;
        break;
    default:
        result = TypeInputNotifyPeer;
        break;
    }

    return result;
}

inline void InputNotifyPeerObject::setCore(const InputNotifyPeer &core) {
    operator =(core);
}

inline InputNotifyPeer InputNotifyPeerObject::core() const {
    return m_core;
}

inline void InputNotifyPeerObject::corePeerInputGeoChatChanged() {
    if(m_core.peerInputGeoChat() == m_peerInputGeoChat->core()) return;
    m_core.setPeerInputGeoChat(m_peerInputGeoChat->core());
    Q_EMIT peerInputGeoChatChanged();
    Q_EMIT coreChanged();
}

inline void InputNotifyPeerObject::corePeerInputChanged() {
    if(m_core.peerInput() == m_peerInput->core()) return;
    m_core.setPeerInput(m_peerInput->core());
    Q_EMIT peerInputChanged();
    Q_EMIT coreChanged();
}

#endif // LQTG_TYPE_INPUTNOTIFYPEER_OBJECT
