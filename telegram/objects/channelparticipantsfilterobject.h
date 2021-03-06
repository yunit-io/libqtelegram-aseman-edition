// This file generated by libqtelegram-code-generator.
// You can download it from: https://github.com/Aseman-Land/libqtelegram-code-generator
// DO NOT EDIT THIS FILE BY HAND -- YOUR CHANGES WILL BE OVERWRITTEN

#ifndef LQTG_TYPE_CHANNELPARTICIPANTSFILTER_OBJECT
#define LQTG_TYPE_CHANNELPARTICIPANTSFILTER_OBJECT

#include "telegramtypeqobject.h"
#include "telegram/types/channelparticipantsfilter.h"

#include <QPointer>

class LIBQTELEGRAMSHARED_EXPORT ChannelParticipantsFilterObject : public TelegramTypeQObject
{
    Q_OBJECT
    Q_ENUMS(ChannelParticipantsFilterClassType)
    Q_PROPERTY(ChannelParticipantsFilter core READ core WRITE setCore NOTIFY coreChanged)
    Q_PROPERTY(quint32 classType READ classType WRITE setClassType NOTIFY classTypeChanged)

public:
    enum ChannelParticipantsFilterClassType {
        TypeChannelParticipantsRecent,
        TypeChannelParticipantsAdmins,
        TypeChannelParticipantsKicked,
        TypeChannelParticipantsBots
    };

    ChannelParticipantsFilterObject(const ChannelParticipantsFilter &core, QObject *parent = 0);
    ChannelParticipantsFilterObject(QObject *parent = 0);
    virtual ~ChannelParticipantsFilterObject();

    void setClassType(quint32 classType);
    quint32 classType() const;

    void setCore(const ChannelParticipantsFilter &core);
    ChannelParticipantsFilter core() const;

    ChannelParticipantsFilterObject &operator =(const ChannelParticipantsFilter &b);
    bool operator ==(const ChannelParticipantsFilter &b) const;

Q_SIGNALS:
    void coreChanged();
    void classTypeChanged();

private Q_SLOTS:

private:
    ChannelParticipantsFilter m_core;
};

inline ChannelParticipantsFilterObject::ChannelParticipantsFilterObject(const ChannelParticipantsFilter &core, QObject *parent) :
    TelegramTypeQObject(parent),
    m_core(core)
{
}

inline ChannelParticipantsFilterObject::ChannelParticipantsFilterObject(QObject *parent) :
    TelegramTypeQObject(parent),
    m_core()
{
}

inline ChannelParticipantsFilterObject::~ChannelParticipantsFilterObject() {
}

inline ChannelParticipantsFilterObject &ChannelParticipantsFilterObject::operator =(const ChannelParticipantsFilter &b) {
    if(m_core == b) return *this;
    m_core = b;

    Q_EMIT coreChanged();
    return *this;
}

inline bool ChannelParticipantsFilterObject::operator ==(const ChannelParticipantsFilter &b) const {
    return m_core == b;
}

inline void ChannelParticipantsFilterObject::setClassType(quint32 classType) {
    ChannelParticipantsFilter::ChannelParticipantsFilterClassType result;
    switch(classType) {
    case TypeChannelParticipantsRecent:
        result = ChannelParticipantsFilter::typeChannelParticipantsRecent;
        break;
    case TypeChannelParticipantsAdmins:
        result = ChannelParticipantsFilter::typeChannelParticipantsAdmins;
        break;
    case TypeChannelParticipantsKicked:
        result = ChannelParticipantsFilter::typeChannelParticipantsKicked;
        break;
    case TypeChannelParticipantsBots:
        result = ChannelParticipantsFilter::typeChannelParticipantsBots;
        break;
    default:
        result = ChannelParticipantsFilter::typeChannelParticipantsRecent;
        break;
    }

    if(m_core.classType() == result) return;
    m_core.setClassType(result);
    Q_EMIT classTypeChanged();
    Q_EMIT coreChanged();
}

inline quint32 ChannelParticipantsFilterObject::classType() const {
    int result;
    switch(static_cast<qint64>(m_core.classType())) {
    case ChannelParticipantsFilter::typeChannelParticipantsRecent:
        result = TypeChannelParticipantsRecent;
        break;
    case ChannelParticipantsFilter::typeChannelParticipantsAdmins:
        result = TypeChannelParticipantsAdmins;
        break;
    case ChannelParticipantsFilter::typeChannelParticipantsKicked:
        result = TypeChannelParticipantsKicked;
        break;
    case ChannelParticipantsFilter::typeChannelParticipantsBots:
        result = TypeChannelParticipantsBots;
        break;
    default:
        result = TypeChannelParticipantsRecent;
        break;
    }

    return result;
}

inline void ChannelParticipantsFilterObject::setCore(const ChannelParticipantsFilter &core) {
    operator =(core);
}

inline ChannelParticipantsFilter ChannelParticipantsFilterObject::core() const {
    return m_core;
}

#endif // LQTG_TYPE_CHANNELPARTICIPANTSFILTER_OBJECT
