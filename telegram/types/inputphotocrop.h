// This file generated by libqtelegram-code-generator.
// You can download it from: https://github.com/Aseman-Land/libqtelegram-code-generator
// DO NOT EDIT THIS FILE BY HAND -- YOUR CHANGES WILL BE OVERWRITTEN

#ifndef LQTG_TYPE_INPUTPHOTOCROP
#define LQTG_TYPE_INPUTPHOTOCROP

#include "telegramtypeobject.h"

#include <QMetaType>
#include <QVariant>
#include "core/inboundpkt.h"
#include "core/outboundpkt.h"
#include "../coretypes.h"

#include <QDataStream>

#include <QtGlobal>

class LIBQTELEGRAMSHARED_EXPORT InputPhotoCrop : public TelegramTypeObject
{
public:
    enum InputPhotoCropClassType {
        typeInputPhotoCropAuto = 0xade6b004,
        typeInputPhotoCrop = 0xd9915325
    };

    InputPhotoCrop(InputPhotoCropClassType classType = typeInputPhotoCropAuto, InboundPkt *in = 0);
    InputPhotoCrop(InboundPkt *in);
    InputPhotoCrop(const Null&);
    virtual ~InputPhotoCrop();

    void setCropLeft(qreal cropLeft);
    qreal cropLeft() const;

    void setCropTop(qreal cropTop);
    qreal cropTop() const;

    void setCropWidth(qreal cropWidth);
    qreal cropWidth() const;

    void setClassType(InputPhotoCropClassType classType);
    InputPhotoCropClassType classType() const;

    bool fetch(InboundPkt *in);
    bool push(OutboundPkt *out) const;

    QMap<QString, QVariant> toMap() const;
    static InputPhotoCrop fromMap(const QMap<QString, QVariant> &map);

    bool operator ==(const InputPhotoCrop &b) const;

    bool operator==(bool stt) const { return isNull() != stt; }
    bool operator!=(bool stt) const { return !operator ==(stt); }

    QByteArray getHash(QCryptographicHash::Algorithm alg = QCryptographicHash::Md5) const;

private:
    qreal m_cropLeft;
    qreal m_cropTop;
    qreal m_cropWidth;
    InputPhotoCropClassType m_classType;
};

Q_DECLARE_METATYPE(InputPhotoCrop)

QDataStream LIBQTELEGRAMSHARED_EXPORT &operator<<(QDataStream &stream, const InputPhotoCrop &item);
QDataStream LIBQTELEGRAMSHARED_EXPORT &operator>>(QDataStream &stream, InputPhotoCrop &item);

inline InputPhotoCrop::InputPhotoCrop(InputPhotoCropClassType classType, InboundPkt *in) :
    m_cropLeft(0),
    m_cropTop(0),
    m_cropWidth(0),
    m_classType(classType)
{
    if(in) fetch(in);
}

inline InputPhotoCrop::InputPhotoCrop(InboundPkt *in) :
    m_cropLeft(0),
    m_cropTop(0),
    m_cropWidth(0),
    m_classType(typeInputPhotoCropAuto)
{
    fetch(in);
}

inline InputPhotoCrop::InputPhotoCrop(const Null &null) :
    TelegramTypeObject(null),
    m_cropLeft(0),
    m_cropTop(0),
    m_cropWidth(0),
    m_classType(typeInputPhotoCropAuto)
{
}

inline InputPhotoCrop::~InputPhotoCrop() {
}

inline void InputPhotoCrop::setCropLeft(qreal cropLeft) {
    m_cropLeft = cropLeft;
}

inline qreal InputPhotoCrop::cropLeft() const {
    return m_cropLeft;
}

inline void InputPhotoCrop::setCropTop(qreal cropTop) {
    m_cropTop = cropTop;
}

inline qreal InputPhotoCrop::cropTop() const {
    return m_cropTop;
}

inline void InputPhotoCrop::setCropWidth(qreal cropWidth) {
    m_cropWidth = cropWidth;
}

inline qreal InputPhotoCrop::cropWidth() const {
    return m_cropWidth;
}

inline bool InputPhotoCrop::operator ==(const InputPhotoCrop &b) const {
    return m_classType == b.m_classType &&
           m_cropLeft == b.m_cropLeft &&
           m_cropTop == b.m_cropTop &&
           m_cropWidth == b.m_cropWidth;
}

inline void InputPhotoCrop::setClassType(InputPhotoCrop::InputPhotoCropClassType classType) {
    m_classType = classType;
}

inline InputPhotoCrop::InputPhotoCropClassType InputPhotoCrop::classType() const {
    return m_classType;
}

inline bool InputPhotoCrop::fetch(InboundPkt *in) {
    LQTG_FETCH_LOG;
    int x = in->fetchInt();
    switch(x) {
    case typeInputPhotoCropAuto: {
        m_classType = static_cast<InputPhotoCropClassType>(x);
        return true;
    }
        break;
    
    case typeInputPhotoCrop: {
        m_cropLeft = in->fetchDouble();
        m_cropTop = in->fetchDouble();
        m_cropWidth = in->fetchDouble();
        m_classType = static_cast<InputPhotoCropClassType>(x);
        return true;
    }
        break;
    
    default:
        LQTG_FETCH_ASSERT;
        return false;
    }
}

inline bool InputPhotoCrop::push(OutboundPkt *out) const {
    out->appendInt(m_classType);
    switch(m_classType) {
    case typeInputPhotoCropAuto: {
        return true;
    }
        break;
    
    case typeInputPhotoCrop: {
        out->appendDouble(m_cropLeft);
        out->appendDouble(m_cropTop);
        out->appendDouble(m_cropWidth);
        return true;
    }
        break;
    
    default:
        return false;
    }
}

inline QMap<QString, QVariant> InputPhotoCrop::toMap() const {
    QMap<QString, QVariant> result;
    switch(static_cast<int>(m_classType)) {
    case typeInputPhotoCropAuto: {
        result["classType"] = "InputPhotoCrop::typeInputPhotoCropAuto";
        return result;
    }
        break;
    
    case typeInputPhotoCrop: {
        result["classType"] = "InputPhotoCrop::typeInputPhotoCrop";
        result["cropLeft"] = QVariant::fromValue<qreal>(cropLeft());
        result["cropTop"] = QVariant::fromValue<qreal>(cropTop());
        result["cropWidth"] = QVariant::fromValue<qreal>(cropWidth());
        return result;
    }
        break;
    
    default:
        return result;
    }
}

inline InputPhotoCrop InputPhotoCrop::fromMap(const QMap<QString, QVariant> &map) {
    InputPhotoCrop result;
    if(map.value("classType").toString() == "InputPhotoCrop::typeInputPhotoCropAuto") {
        result.setClassType(typeInputPhotoCropAuto);
        return result;
    }
    if(map.value("classType").toString() == "InputPhotoCrop::typeInputPhotoCrop") {
        result.setClassType(typeInputPhotoCrop);
        result.setCropLeft( map.value("cropLeft").value<qreal>() );
        result.setCropTop( map.value("cropTop").value<qreal>() );
        result.setCropWidth( map.value("cropWidth").value<qreal>() );
        return result;
    }
    return result;
}

inline QByteArray InputPhotoCrop::getHash(QCryptographicHash::Algorithm alg) const {
    QByteArray data;
    QDataStream str(&data, QIODevice::WriteOnly);
    str << *this;
    return QCryptographicHash::hash(data, alg);
}

inline QDataStream &operator<<(QDataStream &stream, const InputPhotoCrop &item) {
    stream << static_cast<uint>(item.classType());
    switch(item.classType()) {
    case InputPhotoCrop::typeInputPhotoCropAuto:
        
        break;
    case InputPhotoCrop::typeInputPhotoCrop:
        stream << item.cropLeft();
        stream << item.cropTop();
        stream << item.cropWidth();
        break;
    }
    return stream;
}

inline QDataStream &operator>>(QDataStream &stream, InputPhotoCrop &item) {
    uint type = 0;
    stream >> type;
    item.setClassType(static_cast<InputPhotoCrop::InputPhotoCropClassType>(type));
    switch(type) {
    case InputPhotoCrop::typeInputPhotoCropAuto: {
        
    }
        break;
    case InputPhotoCrop::typeInputPhotoCrop: {
        qreal m_crop_left;
        stream >> m_crop_left;
        item.setCropLeft(m_crop_left);
        qreal m_crop_top;
        stream >> m_crop_top;
        item.setCropTop(m_crop_top);
        qreal m_crop_width;
        stream >> m_crop_width;
        item.setCropWidth(m_crop_width);
    }
        break;
    }
    return stream;
}


#endif // LQTG_TYPE_INPUTPHOTOCROP
