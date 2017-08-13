// This file generated by libqtelegram-code-generator.
// You can download it from: https://github.com/Aseman-Land/libqtelegram-code-generator
// DO NOT EDIT THIS FILE BY HAND -- YOUR CHANGES WILL BE OVERWRITTEN

#ifndef LQTG_TYPE_DCOPTION_OBJECT
#define LQTG_TYPE_DCOPTION_OBJECT

#include "telegramtypeqobject.h"
#include "telegram/types/dcoption.h"

#include <QPointer>

class LIBQTELEGRAMSHARED_EXPORT DcOptionObject : public TelegramTypeQObject
{
    Q_OBJECT
    Q_ENUMS(DcOptionClassType)
    Q_PROPERTY(qint32 flags READ flags WRITE setFlags NOTIFY flagsChanged)
    Q_PROPERTY(qint32 id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString ipAddress READ ipAddress WRITE setIpAddress NOTIFY ipAddressChanged)
    Q_PROPERTY(qint32 port READ port WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(DcOption core READ core WRITE setCore NOTIFY coreChanged)
    Q_PROPERTY(quint32 classType READ classType WRITE setClassType NOTIFY classTypeChanged)

public:
    enum DcOptionClassType {
        TypeDcOption
    };

    DcOptionObject(const DcOption &core, QObject *parent = 0);
    DcOptionObject(QObject *parent = 0);
    virtual ~DcOptionObject();

    void setFlags(qint32 flags);
    qint32 flags() const;

    void setId(qint32 id);
    qint32 id() const;

    void setIpAddress(const QString &ipAddress);
    QString ipAddress() const;

    void setPort(qint32 port);
    qint32 port() const;

    void setClassType(quint32 classType);
    quint32 classType() const;

    void setCore(const DcOption &core);
    DcOption core() const;

    DcOptionObject &operator =(const DcOption &b);
    bool operator ==(const DcOption &b) const;

Q_SIGNALS:
    void coreChanged();
    void classTypeChanged();
    void flagsChanged();
    void idChanged();
    void ipAddressChanged();
    void portChanged();

private Q_SLOTS:

private:
    DcOption m_core;
};

inline DcOptionObject::DcOptionObject(const DcOption &core, QObject *parent) :
    TelegramTypeQObject(parent),
    m_core(core)
{
}

inline DcOptionObject::DcOptionObject(QObject *parent) :
    TelegramTypeQObject(parent),
    m_core()
{
}

inline DcOptionObject::~DcOptionObject() {
}

inline void DcOptionObject::setFlags(qint32 flags) {
    if(m_core.flags() == flags) return;
    m_core.setFlags(flags);
    Q_EMIT flagsChanged();
    Q_EMIT coreChanged();
}

inline qint32 DcOptionObject::flags() const {
    return m_core.flags();
}

inline void DcOptionObject::setId(qint32 id) {
    if(m_core.id() == id) return;
    m_core.setId(id);
    Q_EMIT idChanged();
    Q_EMIT coreChanged();
}

inline qint32 DcOptionObject::id() const {
    return m_core.id();
}

inline void DcOptionObject::setIpAddress(const QString &ipAddress) {
    if(m_core.ipAddress() == ipAddress) return;
    m_core.setIpAddress(ipAddress);
    Q_EMIT ipAddressChanged();
    Q_EMIT coreChanged();
}

inline QString DcOptionObject::ipAddress() const {
    return m_core.ipAddress();
}

inline void DcOptionObject::setPort(qint32 port) {
    if(m_core.port() == port) return;
    m_core.setPort(port);
    Q_EMIT portChanged();
    Q_EMIT coreChanged();
}

inline qint32 DcOptionObject::port() const {
    return m_core.port();
}

inline DcOptionObject &DcOptionObject::operator =(const DcOption &b) {
    if(m_core == b) return *this;
    m_core = b;

    Q_EMIT flagsChanged();
    Q_EMIT idChanged();
    Q_EMIT ipAddressChanged();
    Q_EMIT portChanged();
    Q_EMIT coreChanged();
    return *this;
}

inline bool DcOptionObject::operator ==(const DcOption &b) const {
    return m_core == b;
}

inline void DcOptionObject::setClassType(quint32 classType) {
    DcOption::DcOptionClassType result;
    switch(classType) {
    case TypeDcOption:
        result = DcOption::typeDcOption;
        break;
    default:
        result = DcOption::typeDcOption;
        break;
    }

    if(m_core.classType() == result) return;
    m_core.setClassType(result);
    Q_EMIT classTypeChanged();
    Q_EMIT coreChanged();
}

inline quint32 DcOptionObject::classType() const {
    int result;
    switch(static_cast<qint64>(m_core.classType())) {
    case DcOption::typeDcOption:
        result = TypeDcOption;
        break;
    default:
        result = TypeDcOption;
        break;
    }

    return result;
}

inline void DcOptionObject::setCore(const DcOption &core) {
    operator =(core);
}

inline DcOption DcOptionObject::core() const {
    return m_core;
}

#endif // LQTG_TYPE_DCOPTION_OBJECT
