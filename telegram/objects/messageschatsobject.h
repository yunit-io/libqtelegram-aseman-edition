// This file generated by libqtelegram-code-generator.
// You can download it from: https://github.com/Aseman-Land/libqtelegram-code-generator
// DO NOT EDIT THIS FILE BY HAND -- YOUR CHANGES WILL BE OVERWRITTEN

#ifndef LQTG_TYPE_MESSAGESCHATS_OBJECT
#define LQTG_TYPE_MESSAGESCHATS_OBJECT

#include "telegramtypeqobject.h"
#include "telegram/types/messageschats.h"

#include <QPointer>

class LIBQTELEGRAMSHARED_EXPORT MessagesChatsObject : public TelegramTypeQObject
{
    Q_OBJECT
    Q_ENUMS(MessagesChatsClassType)
    Q_PROPERTY(QList<Chat> chats READ chats WRITE setChats NOTIFY chatsChanged)
    Q_PROPERTY(MessagesChats core READ core WRITE setCore NOTIFY coreChanged)
    Q_PROPERTY(quint32 classType READ classType WRITE setClassType NOTIFY classTypeChanged)

public:
    enum MessagesChatsClassType {
        TypeMessagesChats
    };

    MessagesChatsObject(const MessagesChats &core, QObject *parent = 0);
    MessagesChatsObject(QObject *parent = 0);
    virtual ~MessagesChatsObject();

    void setChats(const QList<Chat> &chats);
    QList<Chat> chats() const;

    void setClassType(quint32 classType);
    quint32 classType() const;

    void setCore(const MessagesChats &core);
    MessagesChats core() const;

    MessagesChatsObject &operator =(const MessagesChats &b);
    bool operator ==(const MessagesChats &b) const;

Q_SIGNALS:
    void coreChanged();
    void classTypeChanged();
    void chatsChanged();

private Q_SLOTS:

private:
    MessagesChats m_core;
};

inline MessagesChatsObject::MessagesChatsObject(const MessagesChats &core, QObject *parent) :
    TelegramTypeQObject(parent),
    m_core(core)
{
}

inline MessagesChatsObject::MessagesChatsObject(QObject *parent) :
    TelegramTypeQObject(parent),
    m_core()
{
}

inline MessagesChatsObject::~MessagesChatsObject() {
}

inline void MessagesChatsObject::setChats(const QList<Chat> &chats) {
    if(m_core.chats() == chats) return;
    m_core.setChats(chats);
    Q_EMIT chatsChanged();
    Q_EMIT coreChanged();
}

inline QList<Chat> MessagesChatsObject::chats() const {
    return m_core.chats();
}

inline MessagesChatsObject &MessagesChatsObject::operator =(const MessagesChats &b) {
    if(m_core == b) return *this;
    m_core = b;

    Q_EMIT chatsChanged();
    Q_EMIT coreChanged();
    return *this;
}

inline bool MessagesChatsObject::operator ==(const MessagesChats &b) const {
    return m_core == b;
}

inline void MessagesChatsObject::setClassType(quint32 classType) {
    MessagesChats::MessagesChatsClassType result;
    switch(classType) {
    case TypeMessagesChats:
        result = MessagesChats::typeMessagesChats;
        break;
    default:
        result = MessagesChats::typeMessagesChats;
        break;
    }

    if(m_core.classType() == result) return;
    m_core.setClassType(result);
    Q_EMIT classTypeChanged();
    Q_EMIT coreChanged();
}

inline quint32 MessagesChatsObject::classType() const {
    int result;
    switch(static_cast<qint64>(m_core.classType())) {
    case MessagesChats::typeMessagesChats:
        result = TypeMessagesChats;
        break;
    default:
        result = TypeMessagesChats;
        break;
    }

    return result;
}

inline void MessagesChatsObject::setCore(const MessagesChats &core) {
    operator =(core);
}

inline MessagesChats MessagesChatsObject::core() const {
    return m_core;
}

#endif // LQTG_TYPE_MESSAGESCHATS_OBJECT
