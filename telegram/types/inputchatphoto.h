// This file generated by libqtelegram-code-generator.
// You can download it from: https://github.com/Aseman-Land/libqtelegram-code-generator
// DO NOT EDIT THIS FILE BY HAND -- YOUR CHANGES WILL BE OVERWRITTEN

#ifndef LQTG_TYPE_INPUTCHATPHOTO
#define LQTG_TYPE_INPUTCHATPHOTO

#include "telegramtypeobject.h"

#include <QMetaType>
#include <QVariant>
#include "core/inboundpkt.h"
#include "core/outboundpkt.h"
#include "../coretypes.h"

#include <QDataStream>

#include "inputphotocrop.h"
#include "inputfile.h"
#include "inputphoto.h"

class LIBQTELEGRAMSHARED_EXPORT InputChatPhoto : public TelegramTypeObject
{
public:
    enum InputChatPhotoClassType {
        typeInputChatPhotoEmpty = 0x1ca48f57,
        typeInputChatUploadedPhoto = 0x94254732,
        typeInputChatPhoto = 0xb2e1bf08
    };

    InputChatPhoto(InputChatPhotoClassType classType = typeInputChatPhotoEmpty, InboundPkt *in = 0);
    InputChatPhoto(InboundPkt *in);
    InputChatPhoto(const Null&);
    virtual ~InputChatPhoto();

    void setCrop(const InputPhotoCrop &crop);
    InputPhotoCrop crop() const;

    void setFile(const InputFile &file);
    InputFile file() const;

    void setId(const InputPhoto &id);
    InputPhoto id() const;

    void setClassType(InputChatPhotoClassType classType);
    InputChatPhotoClassType classType() const;

    bool fetch(InboundPkt *in);
    bool push(OutboundPkt *out) const;

    QMap<QString, QVariant> toMap() const;
    static InputChatPhoto fromMap(const QMap<QString, QVariant> &map);

    bool operator ==(const InputChatPhoto &b) const;

    bool operator==(bool stt) const { return isNull() != stt; }
    bool operator!=(bool stt) const { return !operator ==(stt); }

    QByteArray getHash(QCryptographicHash::Algorithm alg = QCryptographicHash::Md5) const;

private:
    InputPhotoCrop m_crop;
    InputFile m_file;
    InputPhoto m_id;
    InputChatPhotoClassType m_classType;
};

Q_DECLARE_METATYPE(InputChatPhoto)

QDataStream LIBQTELEGRAMSHARED_EXPORT &operator<<(QDataStream &stream, const InputChatPhoto &item);
QDataStream LIBQTELEGRAMSHARED_EXPORT &operator>>(QDataStream &stream, InputChatPhoto &item);

inline InputChatPhoto::InputChatPhoto(InputChatPhotoClassType classType, InboundPkt *in) :
    m_classType(classType)
{
    if(in) fetch(in);
}

inline InputChatPhoto::InputChatPhoto(InboundPkt *in) :
    m_classType(typeInputChatPhotoEmpty)
{
    fetch(in);
}

inline InputChatPhoto::InputChatPhoto(const Null &null) :
    TelegramTypeObject(null),
    m_classType(typeInputChatPhotoEmpty)
{
}

inline InputChatPhoto::~InputChatPhoto() {
}

inline void InputChatPhoto::setCrop(const InputPhotoCrop &crop) {
    m_crop = crop;
}

inline InputPhotoCrop InputChatPhoto::crop() const {
    return m_crop;
}

inline void InputChatPhoto::setFile(const InputFile &file) {
    m_file = file;
}

inline InputFile InputChatPhoto::file() const {
    return m_file;
}

inline void InputChatPhoto::setId(const InputPhoto &id) {
    m_id = id;
}

inline InputPhoto InputChatPhoto::id() const {
    return m_id;
}

inline bool InputChatPhoto::operator ==(const InputChatPhoto &b) const {
    return m_classType == b.m_classType &&
           m_crop == b.m_crop &&
           m_file == b.m_file &&
           m_id == b.m_id;
}

inline void InputChatPhoto::setClassType(InputChatPhoto::InputChatPhotoClassType classType) {
    m_classType = classType;
}

inline InputChatPhoto::InputChatPhotoClassType InputChatPhoto::classType() const {
    return m_classType;
}

inline bool InputChatPhoto::fetch(InboundPkt *in) {
    LQTG_FETCH_LOG;
    int x = in->fetchInt();
    switch(x) {
    case typeInputChatPhotoEmpty: {
        m_classType = static_cast<InputChatPhotoClassType>(x);
        return true;
    }
        break;
    
    case typeInputChatUploadedPhoto: {
        m_file.fetch(in);
        m_crop.fetch(in);
        m_classType = static_cast<InputChatPhotoClassType>(x);
        return true;
    }
        break;
    
    case typeInputChatPhoto: {
        m_id.fetch(in);
        m_crop.fetch(in);
        m_classType = static_cast<InputChatPhotoClassType>(x);
        return true;
    }
        break;
    
    default:
        LQTG_FETCH_ASSERT;
        return false;
    }
}

inline bool InputChatPhoto::push(OutboundPkt *out) const {
    out->appendInt(m_classType);
    switch(m_classType) {
    case typeInputChatPhotoEmpty: {
        return true;
    }
        break;
    
    case typeInputChatUploadedPhoto: {
        m_file.push(out);
        m_crop.push(out);
        return true;
    }
        break;
    
    case typeInputChatPhoto: {
        m_id.push(out);
        m_crop.push(out);
        return true;
    }
        break;
    
    default:
        return false;
    }
}

inline QMap<QString, QVariant> InputChatPhoto::toMap() const {
    QMap<QString, QVariant> result;
    switch(static_cast<int>(m_classType)) {
    case typeInputChatPhotoEmpty: {
        result["classType"] = "InputChatPhoto::typeInputChatPhotoEmpty";
        return result;
    }
        break;
    
    case typeInputChatUploadedPhoto: {
        result["classType"] = "InputChatPhoto::typeInputChatUploadedPhoto";
        result["file"] = m_file.toMap();
        result["crop"] = m_crop.toMap();
        return result;
    }
        break;
    
    case typeInputChatPhoto: {
        result["classType"] = "InputChatPhoto::typeInputChatPhoto";
        result["id"] = m_id.toMap();
        result["crop"] = m_crop.toMap();
        return result;
    }
        break;
    
    default:
        return result;
    }
}

inline InputChatPhoto InputChatPhoto::fromMap(const QMap<QString, QVariant> &map) {
    InputChatPhoto result;
    if(map.value("classType").toString() == "InputChatPhoto::typeInputChatPhotoEmpty") {
        result.setClassType(typeInputChatPhotoEmpty);
        return result;
    }
    if(map.value("classType").toString() == "InputChatPhoto::typeInputChatUploadedPhoto") {
        result.setClassType(typeInputChatUploadedPhoto);
        result.setFile( InputFile::fromMap(map.value("file").toMap()) );
        result.setCrop( InputPhotoCrop::fromMap(map.value("crop").toMap()) );
        return result;
    }
    if(map.value("classType").toString() == "InputChatPhoto::typeInputChatPhoto") {
        result.setClassType(typeInputChatPhoto);
        result.setId( InputPhoto::fromMap(map.value("id").toMap()) );
        result.setCrop( InputPhotoCrop::fromMap(map.value("crop").toMap()) );
        return result;
    }
    return result;
}

inline QByteArray InputChatPhoto::getHash(QCryptographicHash::Algorithm alg) const {
    QByteArray data;
    QDataStream str(&data, QIODevice::WriteOnly);
    str << *this;
    return QCryptographicHash::hash(data, alg);
}

inline QDataStream &operator<<(QDataStream &stream, const InputChatPhoto &item) {
    stream << static_cast<uint>(item.classType());
    switch(item.classType()) {
    case InputChatPhoto::typeInputChatPhotoEmpty:
        
        break;
    case InputChatPhoto::typeInputChatUploadedPhoto:
        stream << item.file();
        stream << item.crop();
        break;
    case InputChatPhoto::typeInputChatPhoto:
        stream << item.id();
        stream << item.crop();
        break;
    }
    return stream;
}

inline QDataStream &operator>>(QDataStream &stream, InputChatPhoto &item) {
    uint type = 0;
    stream >> type;
    item.setClassType(static_cast<InputChatPhoto::InputChatPhotoClassType>(type));
    switch(type) {
    case InputChatPhoto::typeInputChatPhotoEmpty: {
        
    }
        break;
    case InputChatPhoto::typeInputChatUploadedPhoto: {
        InputFile m_file;
        stream >> m_file;
        item.setFile(m_file);
        InputPhotoCrop m_crop;
        stream >> m_crop;
        item.setCrop(m_crop);
    }
        break;
    case InputChatPhoto::typeInputChatPhoto: {
        InputPhoto m_id;
        stream >> m_id;
        item.setId(m_id);
        InputPhotoCrop m_crop;
        stream >> m_crop;
        item.setCrop(m_crop);
    }
        break;
    }
    return stream;
}


#endif // LQTG_TYPE_INPUTCHATPHOTO
