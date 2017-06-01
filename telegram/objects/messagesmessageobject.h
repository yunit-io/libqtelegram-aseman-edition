// This file generated by libqtelegram-code-generator.
// You can download it from: https://github.com/Aseman-Land/libqtelegram-code-generator
// DO NOT EDIT THIS FILE BY HAND -- YOUR CHANGES WILL BE OVERWRITTEN

#ifndef LQTG_TYPE_MESSAGESMESSAGE_OBJECT
#define LQTG_TYPE_MESSAGESMESSAGE_OBJECT

#include "telegramtypeqobject.h"
#include "telegram/types/messagesmessage.h"

#include <QPointer>

class LIBQTELEGRAMSHARED_EXPORT MessagesMessageObject : public TelegramTypeQObject
{
    Q_OBJECT
    Q_ENUMS(MessagesMessageClassType)
    Q_PROPERTY(MessagesMessage core READ core WRITE setCore NOTIFY coreChanged)
    Q_PROPERTY(quint32 classType READ classType WRITE setClassType NOTIFY classTypeChanged)

public:
    enum MessagesMessageClassType {
        TypeMessagesMessageEmpty
    };

    MessagesMessageObject(const MessagesMessage &core, QObject *parent = 0);
    MessagesMessageObject(QObject *parent = 0);
    virtual ~MessagesMessageObject();

    void setClassType(quint32 classType);
    quint32 classType() const;

    void setCore(const MessagesMessage &core);
    MessagesMessage core() const;

    MessagesMessageObject &operator =(const MessagesMessage &b);
    bool operator ==(const MessagesMessage &b) const;

Q_SIGNALS:
    void coreChanged();
    void classTypeChanged();

private Q_SLOTS:

private:
    MessagesMessage m_core;
};

inline MessagesMessageObject::MessagesMessageObject(const MessagesMessage &core, QObject *parent) :
    TelegramTypeQObject(parent),
    m_core(core)
{
}

inline MessagesMessageObject::MessagesMessageObject(QObject *parent) :
    TelegramTypeQObject(parent),
    m_core()
{
}

inline MessagesMessageObject::~MessagesMessageObject() {
}

inline MessagesMessageObject &MessagesMessageObject::operator =(const MessagesMessage &b) {
    if(m_core == b) return *this;
    m_core = b;

    Q_EMIT coreChanged();
    return *this;
}

inline bool MessagesMessageObject::operator ==(const MessagesMessage &b) const {
    return m_core == b;
}

inline void MessagesMessageObject::setClassType(quint32 classType) {
    MessagesMessage::MessagesMessageClassType result;
    switch(classType) {
    case TypeMessagesMessageEmpty:
        result = MessagesMessage::typeMessagesMessageEmpty;
        break;
    default:
        result = MessagesMessage::typeMessagesMessageEmpty;
        break;
    }

    if(m_core.classType() == result) return;
    m_core.setClassType(result);
    Q_EMIT classTypeChanged();
    Q_EMIT coreChanged();
}

inline quint32 MessagesMessageObject::classType() const {
    int result;
    switch(static_cast<qint64>(m_core.classType())) {
    case MessagesMessage::typeMessagesMessageEmpty:
        result = TypeMessagesMessageEmpty;
        break;
    default:
        result = TypeMessagesMessageEmpty;
        break;
    }

    return result;
}

inline void MessagesMessageObject::setCore(const MessagesMessage &core) {
    operator =(core);
}

inline MessagesMessage MessagesMessageObject::core() const {
    return m_core;
}

#endif // LQTG_TYPE_MESSAGESMESSAGE_OBJECT
