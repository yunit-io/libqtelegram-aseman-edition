// This file generated by libqtelegram-code-generator.
// You can download it from: https://github.com/Aseman-Land/libqtelegram-code-generator
// DO NOT EDIT THIS FILE BY HAND -- YOUR CHANGES WILL BE OVERWRITTEN

#ifndef LQTG_TYPE_ACCOUNTPASSWORDINPUTSETTINGS_OBJECT
#define LQTG_TYPE_ACCOUNTPASSWORDINPUTSETTINGS_OBJECT

#include "telegramtypeqobject.h"
#include "telegram/types/accountpasswordinputsettings.h"

#include <QPointer>

class LIBQTELEGRAMSHARED_EXPORT AccountPasswordInputSettingsObject : public TelegramTypeQObject
{
    Q_OBJECT
    Q_ENUMS(AccountPasswordInputSettingsClassType)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(qint32 flags READ flags WRITE setFlags NOTIFY flagsChanged)
    Q_PROPERTY(QString hint READ hint WRITE setHint NOTIFY hintChanged)
    Q_PROPERTY(QByteArray newPasswordHash READ newPasswordHash WRITE setNewPasswordHash NOTIFY newPasswordHashChanged)
    Q_PROPERTY(QByteArray newSalt READ newSalt WRITE setNewSalt NOTIFY newSaltChanged)
    Q_PROPERTY(AccountPasswordInputSettings core READ core WRITE setCore NOTIFY coreChanged)
    Q_PROPERTY(quint32 classType READ classType WRITE setClassType NOTIFY classTypeChanged)

public:
    enum AccountPasswordInputSettingsClassType {
        TypeAccountPasswordInputSettings
    };

    AccountPasswordInputSettingsObject(const AccountPasswordInputSettings &core, QObject *parent = 0);
    AccountPasswordInputSettingsObject(QObject *parent = 0);
    virtual ~AccountPasswordInputSettingsObject();

    void setEmail(const QString &email);
    QString email() const;

    void setFlags(qint32 flags);
    qint32 flags() const;

    void setHint(const QString &hint);
    QString hint() const;

    void setNewPasswordHash(const QByteArray &newPasswordHash);
    QByteArray newPasswordHash() const;

    void setNewSalt(const QByteArray &newSalt);
    QByteArray newSalt() const;

    void setClassType(quint32 classType);
    quint32 classType() const;

    void setCore(const AccountPasswordInputSettings &core);
    AccountPasswordInputSettings core() const;

    AccountPasswordInputSettingsObject &operator =(const AccountPasswordInputSettings &b);
    bool operator ==(const AccountPasswordInputSettings &b) const;

Q_SIGNALS:
    void coreChanged();
    void classTypeChanged();
    void emailChanged();
    void flagsChanged();
    void hintChanged();
    void newPasswordHashChanged();
    void newSaltChanged();

private Q_SLOTS:

private:
    AccountPasswordInputSettings m_core;
};

inline AccountPasswordInputSettingsObject::AccountPasswordInputSettingsObject(const AccountPasswordInputSettings &core, QObject *parent) :
    TelegramTypeQObject(parent),
    m_core(core)
{
}

inline AccountPasswordInputSettingsObject::AccountPasswordInputSettingsObject(QObject *parent) :
    TelegramTypeQObject(parent),
    m_core()
{
}

inline AccountPasswordInputSettingsObject::~AccountPasswordInputSettingsObject() {
}

inline void AccountPasswordInputSettingsObject::setEmail(const QString &email) {
    if(m_core.email() == email) return;
    m_core.setEmail(email);
    Q_EMIT emailChanged();
    Q_EMIT coreChanged();
}

inline QString AccountPasswordInputSettingsObject::email() const {
    return m_core.email();
}

inline void AccountPasswordInputSettingsObject::setFlags(qint32 flags) {
    if(m_core.flags() == flags) return;
    m_core.setFlags(flags);
    Q_EMIT flagsChanged();
    Q_EMIT coreChanged();
}

inline qint32 AccountPasswordInputSettingsObject::flags() const {
    return m_core.flags();
}

inline void AccountPasswordInputSettingsObject::setHint(const QString &hint) {
    if(m_core.hint() == hint) return;
    m_core.setHint(hint);
    Q_EMIT hintChanged();
    Q_EMIT coreChanged();
}

inline QString AccountPasswordInputSettingsObject::hint() const {
    return m_core.hint();
}

inline void AccountPasswordInputSettingsObject::setNewPasswordHash(const QByteArray &newPasswordHash) {
    if(m_core.newPasswordHash() == newPasswordHash) return;
    m_core.setNewPasswordHash(newPasswordHash);
    Q_EMIT newPasswordHashChanged();
    Q_EMIT coreChanged();
}

inline QByteArray AccountPasswordInputSettingsObject::newPasswordHash() const {
    return m_core.newPasswordHash();
}

inline void AccountPasswordInputSettingsObject::setNewSalt(const QByteArray &newSalt) {
    if(m_core.newSalt() == newSalt) return;
    m_core.setNewSalt(newSalt);
    Q_EMIT newSaltChanged();
    Q_EMIT coreChanged();
}

inline QByteArray AccountPasswordInputSettingsObject::newSalt() const {
    return m_core.newSalt();
}

inline AccountPasswordInputSettingsObject &AccountPasswordInputSettingsObject::operator =(const AccountPasswordInputSettings &b) {
    if(m_core == b) return *this;
    m_core = b;

    Q_EMIT emailChanged();
    Q_EMIT flagsChanged();
    Q_EMIT hintChanged();
    Q_EMIT newPasswordHashChanged();
    Q_EMIT newSaltChanged();
    Q_EMIT coreChanged();
    return *this;
}

inline bool AccountPasswordInputSettingsObject::operator ==(const AccountPasswordInputSettings &b) const {
    return m_core == b;
}

inline void AccountPasswordInputSettingsObject::setClassType(quint32 classType) {
    AccountPasswordInputSettings::AccountPasswordInputSettingsClassType result;
    switch(classType) {
    case TypeAccountPasswordInputSettings:
        result = AccountPasswordInputSettings::typeAccountPasswordInputSettings;
        break;
    default:
        result = AccountPasswordInputSettings::typeAccountPasswordInputSettings;
        break;
    }

    if(m_core.classType() == result) return;
    m_core.setClassType(result);
    Q_EMIT classTypeChanged();
    Q_EMIT coreChanged();
}

inline quint32 AccountPasswordInputSettingsObject::classType() const {
    int result;
    switch(static_cast<qint64>(m_core.classType())) {
    case AccountPasswordInputSettings::typeAccountPasswordInputSettings:
        result = TypeAccountPasswordInputSettings;
        break;
    default:
        result = TypeAccountPasswordInputSettings;
        break;
    }

    return result;
}

inline void AccountPasswordInputSettingsObject::setCore(const AccountPasswordInputSettings &core) {
    operator =(core);
}

inline AccountPasswordInputSettings AccountPasswordInputSettingsObject::core() const {
    return m_core;
}

#endif // LQTG_TYPE_ACCOUNTPASSWORDINPUTSETTINGS_OBJECT
