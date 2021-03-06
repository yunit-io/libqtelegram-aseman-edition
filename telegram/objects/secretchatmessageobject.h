// This file generated by libqtelegram-code-generator.
// You can download it from: https://github.com/Aseman-Land/libqtelegram-code-generator
// DO NOT EDIT THIS FILE BY HAND -- YOUR CHANGES WILL BE OVERWRITTEN

#ifndef LQTG_TYPE_SECRETCHATMESSAGE_OBJECT
#define LQTG_TYPE_SECRETCHATMESSAGE_OBJECT

#include "telegramtypeqobject.h"
#include "telegram/types/secretchatmessage.h"

#include <QPointer>
#include "encryptedfileobject.h"
#include "decryptedmessageobject.h"

class LIBQTELEGRAMSHARED_EXPORT SecretChatMessageObject : public TelegramTypeQObject
{
    Q_OBJECT
    Q_ENUMS(SecretChatMessageClassType)
    Q_PROPERTY(EncryptedFileObject* attachment READ attachment WRITE setAttachment NOTIFY attachmentChanged)
    Q_PROPERTY(qint32 chatId READ chatId WRITE setChatId NOTIFY chatIdChanged)
    Q_PROPERTY(qint32 date READ date WRITE setDate NOTIFY dateChanged)
    Q_PROPERTY(DecryptedMessageObject* decryptedMessage READ decryptedMessage WRITE setDecryptedMessage NOTIFY decryptedMessageChanged)
    Q_PROPERTY(qint32 ttl READ ttl WRITE setTtl NOTIFY ttlChanged)
    Q_PROPERTY(SecretChatMessage core READ core WRITE setCore NOTIFY coreChanged)
    Q_PROPERTY(quint32 classType READ classType WRITE setClassType NOTIFY classTypeChanged)

public:
    enum SecretChatMessageClassType {
        TypeSecretChatMessage
    };

    SecretChatMessageObject(const SecretChatMessage &core, QObject *parent = 0);
    SecretChatMessageObject(QObject *parent = 0);
    virtual ~SecretChatMessageObject();

    void setAttachment(EncryptedFileObject* attachment);
    EncryptedFileObject* attachment() const;

    void setChatId(qint32 chatId);
    qint32 chatId() const;

    void setDate(qint32 date);
    qint32 date() const;

    void setDecryptedMessage(DecryptedMessageObject* decryptedMessage);
    DecryptedMessageObject* decryptedMessage() const;

    void setTtl(qint32 ttl);
    qint32 ttl() const;

    void setClassType(quint32 classType);
    quint32 classType() const;

    void setCore(const SecretChatMessage &core);
    SecretChatMessage core() const;

    SecretChatMessageObject &operator =(const SecretChatMessage &b);
    bool operator ==(const SecretChatMessage &b) const;

Q_SIGNALS:
    void coreChanged();
    void classTypeChanged();
    void attachmentChanged();
    void chatIdChanged();
    void dateChanged();
    void decryptedMessageChanged();
    void ttlChanged();

private Q_SLOTS:
    void coreAttachmentChanged();
    void coreDecryptedMessageChanged();

private:
    QPointer<EncryptedFileObject> m_attachment;
    QPointer<DecryptedMessageObject> m_decryptedMessage;
    SecretChatMessage m_core;
};

inline SecretChatMessageObject::SecretChatMessageObject(const SecretChatMessage &core, QObject *parent) :
    TelegramTypeQObject(parent),
    m_attachment(0),
    m_decryptedMessage(0),
    m_core(core)
{
    m_attachment = new EncryptedFileObject(m_core.attachment(), this);
    connect(m_attachment.data(), &EncryptedFileObject::coreChanged, this, &SecretChatMessageObject::coreAttachmentChanged);
    m_decryptedMessage = new DecryptedMessageObject(m_core.decryptedMessage(), this);
    connect(m_decryptedMessage.data(), &DecryptedMessageObject::coreChanged, this, &SecretChatMessageObject::coreDecryptedMessageChanged);
}

inline SecretChatMessageObject::SecretChatMessageObject(QObject *parent) :
    TelegramTypeQObject(parent),
    m_attachment(0),
    m_decryptedMessage(0),
    m_core()
{
    m_attachment = new EncryptedFileObject(m_core.attachment(), this);
    connect(m_attachment.data(), &EncryptedFileObject::coreChanged, this, &SecretChatMessageObject::coreAttachmentChanged);
    m_decryptedMessage = new DecryptedMessageObject(m_core.decryptedMessage(), this);
    connect(m_decryptedMessage.data(), &DecryptedMessageObject::coreChanged, this, &SecretChatMessageObject::coreDecryptedMessageChanged);
}

inline SecretChatMessageObject::~SecretChatMessageObject() {
}

inline void SecretChatMessageObject::setAttachment(EncryptedFileObject* attachment) {
    if(m_attachment == attachment) return;
    if(m_attachment) delete m_attachment;
    m_attachment = attachment;
    if(m_attachment) {
        m_attachment->setParent(this);
        m_core.setAttachment(m_attachment->core());
        connect(m_attachment.data(), &EncryptedFileObject::coreChanged, this, &SecretChatMessageObject::coreAttachmentChanged);
    }
    Q_EMIT attachmentChanged();
    Q_EMIT coreChanged();
}

inline EncryptedFileObject*  SecretChatMessageObject::attachment() const {
    return m_attachment;
}

inline void SecretChatMessageObject::setChatId(qint32 chatId) {
    if(m_core.chatId() == chatId) return;
    m_core.setChatId(chatId);
    Q_EMIT chatIdChanged();
    Q_EMIT coreChanged();
}

inline qint32 SecretChatMessageObject::chatId() const {
    return m_core.chatId();
}

inline void SecretChatMessageObject::setDate(qint32 date) {
    if(m_core.date() == date) return;
    m_core.setDate(date);
    Q_EMIT dateChanged();
    Q_EMIT coreChanged();
}

inline qint32 SecretChatMessageObject::date() const {
    return m_core.date();
}

inline void SecretChatMessageObject::setDecryptedMessage(DecryptedMessageObject* decryptedMessage) {
    if(m_decryptedMessage == decryptedMessage) return;
    if(m_decryptedMessage) delete m_decryptedMessage;
    m_decryptedMessage = decryptedMessage;
    if(m_decryptedMessage) {
        m_decryptedMessage->setParent(this);
        m_core.setDecryptedMessage(m_decryptedMessage->core());
        connect(m_decryptedMessage.data(), &DecryptedMessageObject::coreChanged, this, &SecretChatMessageObject::coreDecryptedMessageChanged);
    }
    Q_EMIT decryptedMessageChanged();
    Q_EMIT coreChanged();
}

inline DecryptedMessageObject*  SecretChatMessageObject::decryptedMessage() const {
    return m_decryptedMessage;
}

inline void SecretChatMessageObject::setTtl(qint32 ttl) {
    if(m_core.ttl() == ttl) return;
    m_core.setTtl(ttl);
    Q_EMIT ttlChanged();
    Q_EMIT coreChanged();
}

inline qint32 SecretChatMessageObject::ttl() const {
    return m_core.ttl();
}

inline SecretChatMessageObject &SecretChatMessageObject::operator =(const SecretChatMessage &b) {
    if(m_core == b) return *this;
    m_core = b;
    m_attachment->setCore(b.attachment());
    m_decryptedMessage->setCore(b.decryptedMessage());

    Q_EMIT attachmentChanged();
    Q_EMIT chatIdChanged();
    Q_EMIT dateChanged();
    Q_EMIT decryptedMessageChanged();
    Q_EMIT ttlChanged();
    Q_EMIT coreChanged();
    return *this;
}

inline bool SecretChatMessageObject::operator ==(const SecretChatMessage &b) const {
    return m_core == b;
}

inline void SecretChatMessageObject::setClassType(quint32 classType) {
    SecretChatMessage::SecretChatMessageClassType result;
    switch(classType) {
    case TypeSecretChatMessage:
        result = SecretChatMessage::typeSecretChatMessage;
        break;
    default:
        result = SecretChatMessage::typeSecretChatMessage;
        break;
    }

    if(m_core.classType() == result) return;
    m_core.setClassType(result);
    Q_EMIT classTypeChanged();
    Q_EMIT coreChanged();
}

inline quint32 SecretChatMessageObject::classType() const {
    int result;
    switch(static_cast<qint64>(m_core.classType())) {
    case SecretChatMessage::typeSecretChatMessage:
        result = TypeSecretChatMessage;
        break;
    default:
        result = TypeSecretChatMessage;
        break;
    }

    return result;
}

inline void SecretChatMessageObject::setCore(const SecretChatMessage &core) {
    operator =(core);
}

inline SecretChatMessage SecretChatMessageObject::core() const {
    return m_core;
}

inline void SecretChatMessageObject::coreAttachmentChanged() {
    if(m_core.attachment() == m_attachment->core()) return;
    m_core.setAttachment(m_attachment->core());
    Q_EMIT attachmentChanged();
    Q_EMIT coreChanged();
}

inline void SecretChatMessageObject::coreDecryptedMessageChanged() {
    if(m_core.decryptedMessage() == m_decryptedMessage->core()) return;
    m_core.setDecryptedMessage(m_decryptedMessage->core());
    Q_EMIT decryptedMessageChanged();
    Q_EMIT coreChanged();
}

#endif // LQTG_TYPE_SECRETCHATMESSAGE_OBJECT
