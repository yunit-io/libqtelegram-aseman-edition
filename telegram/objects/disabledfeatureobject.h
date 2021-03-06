// This file generated by libqtelegram-code-generator.
// You can download it from: https://github.com/Aseman-Land/libqtelegram-code-generator
// DO NOT EDIT THIS FILE BY HAND -- YOUR CHANGES WILL BE OVERWRITTEN

#ifndef LQTG_TYPE_DISABLEDFEATURE_OBJECT
#define LQTG_TYPE_DISABLEDFEATURE_OBJECT

#include "telegramtypeqobject.h"
#include "telegram/types/disabledfeature.h"

#include <QPointer>

class LIBQTELEGRAMSHARED_EXPORT DisabledFeatureObject : public TelegramTypeQObject
{
    Q_OBJECT
    Q_ENUMS(DisabledFeatureClassType)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(QString feature READ feature WRITE setFeature NOTIFY featureChanged)
    Q_PROPERTY(DisabledFeature core READ core WRITE setCore NOTIFY coreChanged)
    Q_PROPERTY(quint32 classType READ classType WRITE setClassType NOTIFY classTypeChanged)

public:
    enum DisabledFeatureClassType {
        TypeDisabledFeature
    };

    DisabledFeatureObject(const DisabledFeature &core, QObject *parent = 0);
    DisabledFeatureObject(QObject *parent = 0);
    virtual ~DisabledFeatureObject();

    void setDescription(const QString &description);
    QString description() const;

    void setFeature(const QString &feature);
    QString feature() const;

    void setClassType(quint32 classType);
    quint32 classType() const;

    void setCore(const DisabledFeature &core);
    DisabledFeature core() const;

    DisabledFeatureObject &operator =(const DisabledFeature &b);
    bool operator ==(const DisabledFeature &b) const;

Q_SIGNALS:
    void coreChanged();
    void classTypeChanged();
    void descriptionChanged();
    void featureChanged();

private Q_SLOTS:

private:
    DisabledFeature m_core;
};

inline DisabledFeatureObject::DisabledFeatureObject(const DisabledFeature &core, QObject *parent) :
    TelegramTypeQObject(parent),
    m_core(core)
{
}

inline DisabledFeatureObject::DisabledFeatureObject(QObject *parent) :
    TelegramTypeQObject(parent),
    m_core()
{
}

inline DisabledFeatureObject::~DisabledFeatureObject() {
}

inline void DisabledFeatureObject::setDescription(const QString &description) {
    if(m_core.description() == description) return;
    m_core.setDescription(description);
    Q_EMIT descriptionChanged();
    Q_EMIT coreChanged();
}

inline QString DisabledFeatureObject::description() const {
    return m_core.description();
}

inline void DisabledFeatureObject::setFeature(const QString &feature) {
    if(m_core.feature() == feature) return;
    m_core.setFeature(feature);
    Q_EMIT featureChanged();
    Q_EMIT coreChanged();
}

inline QString DisabledFeatureObject::feature() const {
    return m_core.feature();
}

inline DisabledFeatureObject &DisabledFeatureObject::operator =(const DisabledFeature &b) {
    if(m_core == b) return *this;
    m_core = b;

    Q_EMIT descriptionChanged();
    Q_EMIT featureChanged();
    Q_EMIT coreChanged();
    return *this;
}

inline bool DisabledFeatureObject::operator ==(const DisabledFeature &b) const {
    return m_core == b;
}

inline void DisabledFeatureObject::setClassType(quint32 classType) {
    DisabledFeature::DisabledFeatureClassType result;
    switch(classType) {
    case TypeDisabledFeature:
        result = DisabledFeature::typeDisabledFeature;
        break;
    default:
        result = DisabledFeature::typeDisabledFeature;
        break;
    }

    if(m_core.classType() == result) return;
    m_core.setClassType(result);
    Q_EMIT classTypeChanged();
    Q_EMIT coreChanged();
}

inline quint32 DisabledFeatureObject::classType() const {
    int result;
    switch(static_cast<qint64>(m_core.classType())) {
    case DisabledFeature::typeDisabledFeature:
        result = TypeDisabledFeature;
        break;
    default:
        result = TypeDisabledFeature;
        break;
    }

    return result;
}

inline void DisabledFeatureObject::setCore(const DisabledFeature &core) {
    operator =(core);
}

inline DisabledFeature DisabledFeatureObject::core() const {
    return m_core;
}

#endif // LQTG_TYPE_DISABLEDFEATURE_OBJECT
