// This file generated by libqtelegram-code-generator.
// You can download it from: https://github.com/Aseman-Land/libqtelegram-code-generator
// DO NOT EDIT THIS FILE BY HAND -- YOUR CHANGES WILL BE OVERWRITTEN

#ifndef LQTG_TYPE_INPUTPHOTOCROP_OBJECT
#define LQTG_TYPE_INPUTPHOTOCROP_OBJECT

#include "telegramtypeqobject.h"
#include "telegram/types/inputphotocrop.h"

#include <QPointer>

class LIBQTELEGRAMSHARED_EXPORT InputPhotoCropObject : public TelegramTypeQObject
{
    Q_OBJECT
    Q_ENUMS(InputPhotoCropClassType)
    Q_PROPERTY(qreal cropLeft READ cropLeft WRITE setCropLeft NOTIFY cropLeftChanged)
    Q_PROPERTY(qreal cropTop READ cropTop WRITE setCropTop NOTIFY cropTopChanged)
    Q_PROPERTY(qreal cropWidth READ cropWidth WRITE setCropWidth NOTIFY cropWidthChanged)
    Q_PROPERTY(InputPhotoCrop core READ core WRITE setCore NOTIFY coreChanged)
    Q_PROPERTY(quint32 classType READ classType WRITE setClassType NOTIFY classTypeChanged)

public:
    enum InputPhotoCropClassType {
        TypeInputPhotoCropAuto,
        TypeInputPhotoCrop
    };

    InputPhotoCropObject(const InputPhotoCrop &core, QObject *parent = 0);
    InputPhotoCropObject(QObject *parent = 0);
    virtual ~InputPhotoCropObject();

    void setCropLeft(qreal cropLeft);
    qreal cropLeft() const;

    void setCropTop(qreal cropTop);
    qreal cropTop() const;

    void setCropWidth(qreal cropWidth);
    qreal cropWidth() const;

    void setClassType(quint32 classType);
    quint32 classType() const;

    void setCore(const InputPhotoCrop &core);
    InputPhotoCrop core() const;

    InputPhotoCropObject &operator =(const InputPhotoCrop &b);
    bool operator ==(const InputPhotoCrop &b) const;

Q_SIGNALS:
    void coreChanged();
    void classTypeChanged();
    void cropLeftChanged();
    void cropTopChanged();
    void cropWidthChanged();

private Q_SLOTS:

private:
    InputPhotoCrop m_core;
};

inline InputPhotoCropObject::InputPhotoCropObject(const InputPhotoCrop &core, QObject *parent) :
    TelegramTypeQObject(parent),
    m_core(core)
{
}

inline InputPhotoCropObject::InputPhotoCropObject(QObject *parent) :
    TelegramTypeQObject(parent),
    m_core()
{
}

inline InputPhotoCropObject::~InputPhotoCropObject() {
}

inline void InputPhotoCropObject::setCropLeft(qreal cropLeft) {
    if(m_core.cropLeft() == cropLeft) return;
    m_core.setCropLeft(cropLeft);
    Q_EMIT cropLeftChanged();
    Q_EMIT coreChanged();
}

inline qreal InputPhotoCropObject::cropLeft() const {
    return m_core.cropLeft();
}

inline void InputPhotoCropObject::setCropTop(qreal cropTop) {
    if(m_core.cropTop() == cropTop) return;
    m_core.setCropTop(cropTop);
    Q_EMIT cropTopChanged();
    Q_EMIT coreChanged();
}

inline qreal InputPhotoCropObject::cropTop() const {
    return m_core.cropTop();
}

inline void InputPhotoCropObject::setCropWidth(qreal cropWidth) {
    if(m_core.cropWidth() == cropWidth) return;
    m_core.setCropWidth(cropWidth);
    Q_EMIT cropWidthChanged();
    Q_EMIT coreChanged();
}

inline qreal InputPhotoCropObject::cropWidth() const {
    return m_core.cropWidth();
}

inline InputPhotoCropObject &InputPhotoCropObject::operator =(const InputPhotoCrop &b) {
    if(m_core == b) return *this;
    m_core = b;

    Q_EMIT cropLeftChanged();
    Q_EMIT cropTopChanged();
    Q_EMIT cropWidthChanged();
    Q_EMIT coreChanged();
    return *this;
}

inline bool InputPhotoCropObject::operator ==(const InputPhotoCrop &b) const {
    return m_core == b;
}

inline void InputPhotoCropObject::setClassType(quint32 classType) {
    InputPhotoCrop::InputPhotoCropClassType result;
    switch(classType) {
    case TypeInputPhotoCropAuto:
        result = InputPhotoCrop::typeInputPhotoCropAuto;
        break;
    case TypeInputPhotoCrop:
        result = InputPhotoCrop::typeInputPhotoCrop;
        break;
    default:
        result = InputPhotoCrop::typeInputPhotoCropAuto;
        break;
    }

    if(m_core.classType() == result) return;
    m_core.setClassType(result);
    Q_EMIT classTypeChanged();
    Q_EMIT coreChanged();
}

inline quint32 InputPhotoCropObject::classType() const {
    int result;
    switch(static_cast<qint64>(m_core.classType())) {
    case InputPhotoCrop::typeInputPhotoCropAuto:
        result = TypeInputPhotoCropAuto;
        break;
    case InputPhotoCrop::typeInputPhotoCrop:
        result = TypeInputPhotoCrop;
        break;
    default:
        result = TypeInputPhotoCropAuto;
        break;
    }

    return result;
}

inline void InputPhotoCropObject::setCore(const InputPhotoCrop &core) {
    operator =(core);
}

inline InputPhotoCrop InputPhotoCropObject::core() const {
    return m_core;
}

#endif // LQTG_TYPE_INPUTPHOTOCROP_OBJECT
