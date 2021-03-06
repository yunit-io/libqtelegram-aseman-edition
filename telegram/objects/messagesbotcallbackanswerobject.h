// This file generated by libqtelegram-code-generator.
// You can download it from: https://github.com/Aseman-Land/libqtelegram-code-generator
// DO NOT EDIT THIS FILE BY HAND -- YOUR CHANGES WILL BE OVERWRITTEN

#ifndef LQTG_TYPE_MESSAGESBOTCALLBACKANSWER_OBJECT
#define LQTG_TYPE_MESSAGESBOTCALLBACKANSWER_OBJECT

#include "telegramtypeqobject.h"
#include "telegram/types/messagesbotcallbackanswer.h"

#include <QPointer>

class LIBQTELEGRAMSHARED_EXPORT MessagesBotCallbackAnswerObject : public TelegramTypeQObject
{
    Q_OBJECT
    Q_ENUMS(MessagesBotCallbackAnswerClassType)
    Q_PROPERTY(bool alert READ alert WRITE setAlert NOTIFY alertChanged)
    Q_PROPERTY(qint32 flags READ flags WRITE setFlags NOTIFY flagsChanged)
    Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged)
    Q_PROPERTY(MessagesBotCallbackAnswer core READ core WRITE setCore NOTIFY coreChanged)
    Q_PROPERTY(quint32 classType READ classType WRITE setClassType NOTIFY classTypeChanged)

public:
    enum MessagesBotCallbackAnswerClassType {
        TypeMessagesBotCallbackAnswer
    };

    MessagesBotCallbackAnswerObject(const MessagesBotCallbackAnswer &core, QObject *parent = 0);
    MessagesBotCallbackAnswerObject(QObject *parent = 0);
    virtual ~MessagesBotCallbackAnswerObject();

    void setAlert(bool alert);
    bool alert() const;

    void setFlags(qint32 flags);
    qint32 flags() const;

    void setMessage(const QString &message);
    QString message() const;

    void setClassType(quint32 classType);
    quint32 classType() const;

    void setCore(const MessagesBotCallbackAnswer &core);
    MessagesBotCallbackAnswer core() const;

    MessagesBotCallbackAnswerObject &operator =(const MessagesBotCallbackAnswer &b);
    bool operator ==(const MessagesBotCallbackAnswer &b) const;

Q_SIGNALS:
    void coreChanged();
    void classTypeChanged();
    void alertChanged();
    void flagsChanged();
    void messageChanged();

private Q_SLOTS:

private:
    MessagesBotCallbackAnswer m_core;
};

inline MessagesBotCallbackAnswerObject::MessagesBotCallbackAnswerObject(const MessagesBotCallbackAnswer &core, QObject *parent) :
    TelegramTypeQObject(parent),
    m_core(core)
{
}

inline MessagesBotCallbackAnswerObject::MessagesBotCallbackAnswerObject(QObject *parent) :
    TelegramTypeQObject(parent),
    m_core()
{
}

inline MessagesBotCallbackAnswerObject::~MessagesBotCallbackAnswerObject() {
}

inline void MessagesBotCallbackAnswerObject::setAlert(bool alert) {
    if(m_core.alert() == alert) return;
    m_core.setAlert(alert);
    Q_EMIT alertChanged();
    Q_EMIT coreChanged();
}

inline bool MessagesBotCallbackAnswerObject::alert() const {
    return m_core.alert();
}

inline void MessagesBotCallbackAnswerObject::setFlags(qint32 flags) {
    if(m_core.flags() == flags) return;
    m_core.setFlags(flags);
    Q_EMIT flagsChanged();
    Q_EMIT coreChanged();
}

inline qint32 MessagesBotCallbackAnswerObject::flags() const {
    return m_core.flags();
}

inline void MessagesBotCallbackAnswerObject::setMessage(const QString &message) {
    if(m_core.message() == message) return;
    m_core.setMessage(message);
    Q_EMIT messageChanged();
    Q_EMIT coreChanged();
}

inline QString MessagesBotCallbackAnswerObject::message() const {
    return m_core.message();
}

inline MessagesBotCallbackAnswerObject &MessagesBotCallbackAnswerObject::operator =(const MessagesBotCallbackAnswer &b) {
    if(m_core == b) return *this;
    m_core = b;

    Q_EMIT alertChanged();
    Q_EMIT flagsChanged();
    Q_EMIT messageChanged();
    Q_EMIT coreChanged();
    return *this;
}

inline bool MessagesBotCallbackAnswerObject::operator ==(const MessagesBotCallbackAnswer &b) const {
    return m_core == b;
}

inline void MessagesBotCallbackAnswerObject::setClassType(quint32 classType) {
    MessagesBotCallbackAnswer::MessagesBotCallbackAnswerClassType result;
    switch(classType) {
    case TypeMessagesBotCallbackAnswer:
        result = MessagesBotCallbackAnswer::typeMessagesBotCallbackAnswer;
        break;
    default:
        result = MessagesBotCallbackAnswer::typeMessagesBotCallbackAnswer;
        break;
    }

    if(m_core.classType() == result) return;
    m_core.setClassType(result);
    Q_EMIT classTypeChanged();
    Q_EMIT coreChanged();
}

inline quint32 MessagesBotCallbackAnswerObject::classType() const {
    int result;
    switch(static_cast<qint64>(m_core.classType())) {
    case MessagesBotCallbackAnswer::typeMessagesBotCallbackAnswer:
        result = TypeMessagesBotCallbackAnswer;
        break;
    default:
        result = TypeMessagesBotCallbackAnswer;
        break;
    }

    return result;
}

inline void MessagesBotCallbackAnswerObject::setCore(const MessagesBotCallbackAnswer &core) {
    operator =(core);
}

inline MessagesBotCallbackAnswer MessagesBotCallbackAnswerObject::core() const {
    return m_core;
}

#endif // LQTG_TYPE_MESSAGESBOTCALLBACKANSWER_OBJECT
