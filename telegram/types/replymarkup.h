// This file generated by libqtelegram-code-generator.
// You can download it from: https://github.com/Aseman-Land/libqtelegram-code-generator
// DO NOT EDIT THIS FILE BY HAND -- YOUR CHANGES WILL BE OVERWRITTEN

#ifndef LQTG_TYPE_REPLYMARKUP
#define LQTG_TYPE_REPLYMARKUP

#include "telegramtypeobject.h"

#include <QMetaType>
#include <QVariant>
#include "core/inboundpkt.h"
#include "core/outboundpkt.h"
#include "../coretypes.h"

#include <QDataStream>

#include <QtGlobal>
#include <QList>
#include "keyboardbuttonrow.h"

class LIBQTELEGRAMSHARED_EXPORT ReplyMarkup : public TelegramTypeObject
{
public:
    enum ReplyMarkupClassType {
        typeReplyKeyboardHide = 0xa03e5b85,
        typeReplyKeyboardForceReply = 0xf4108aa0,
        typeReplyKeyboardMarkup = 0x3502758c
    };

    ReplyMarkup(ReplyMarkupClassType classType = typeReplyKeyboardHide, InboundPkt *in = 0);
    ReplyMarkup(InboundPkt *in);
    ReplyMarkup(const Null&);
    virtual ~ReplyMarkup();

    void setFlags(qint32 flags);
    qint32 flags() const;

    void setRows(const QList<KeyboardButtonRow> &rows);
    QList<KeyboardButtonRow> rows() const;

    void setClassType(ReplyMarkupClassType classType);
    ReplyMarkupClassType classType() const;

    bool fetch(InboundPkt *in);
    bool push(OutboundPkt *out) const;

    QMap<QString, QVariant> toMap() const;
    static ReplyMarkup fromMap(const QMap<QString, QVariant> &map);

    bool operator ==(const ReplyMarkup &b) const;

    bool operator==(bool stt) const { return isNull() != stt; }
    bool operator!=(bool stt) const { return !operator ==(stt); }

    QByteArray getHash(QCryptographicHash::Algorithm alg = QCryptographicHash::Md5) const;

private:
    qint32 m_flags;
    QList<KeyboardButtonRow> m_rows;
    ReplyMarkupClassType m_classType;
};

Q_DECLARE_METATYPE(ReplyMarkup)

QDataStream LIBQTELEGRAMSHARED_EXPORT &operator<<(QDataStream &stream, const ReplyMarkup &item);
QDataStream LIBQTELEGRAMSHARED_EXPORT &operator>>(QDataStream &stream, ReplyMarkup &item);

inline ReplyMarkup::ReplyMarkup(ReplyMarkupClassType classType, InboundPkt *in) :
    m_flags(0),
    m_classType(classType)
{
    if(in) fetch(in);
}

inline ReplyMarkup::ReplyMarkup(InboundPkt *in) :
    m_flags(0),
    m_classType(typeReplyKeyboardHide)
{
    fetch(in);
}

inline ReplyMarkup::ReplyMarkup(const Null &null) :
    TelegramTypeObject(null),
    m_flags(0),
    m_classType(typeReplyKeyboardHide)
{
}

inline ReplyMarkup::~ReplyMarkup() {
}

inline void ReplyMarkup::setFlags(qint32 flags) {
    m_flags = flags;
}

inline qint32 ReplyMarkup::flags() const {
    return m_flags;
}

inline void ReplyMarkup::setRows(const QList<KeyboardButtonRow> &rows) {
    m_rows = rows;
}

inline QList<KeyboardButtonRow> ReplyMarkup::rows() const {
    return m_rows;
}

inline bool ReplyMarkup::operator ==(const ReplyMarkup &b) const {
    return m_classType == b.m_classType &&
           m_flags == b.m_flags &&
           m_rows == b.m_rows;
}

inline void ReplyMarkup::setClassType(ReplyMarkup::ReplyMarkupClassType classType) {
    m_classType = classType;
}

inline ReplyMarkup::ReplyMarkupClassType ReplyMarkup::classType() const {
    return m_classType;
}

inline bool ReplyMarkup::fetch(InboundPkt *in) {
    LQTG_FETCH_LOG;
    int x = in->fetchInt();
    switch(x) {
    case typeReplyKeyboardHide: {
        m_flags = in->fetchInt();
        m_classType = static_cast<ReplyMarkupClassType>(x);
        return true;
    }
        break;
    
    case typeReplyKeyboardForceReply: {
        m_flags = in->fetchInt();
        m_classType = static_cast<ReplyMarkupClassType>(x);
        return true;
    }
        break;
    
    case typeReplyKeyboardMarkup: {
        m_flags = in->fetchInt();
        if(in->fetchInt() != (qint32)CoreTypes::typeVector) return false;
        qint32 m_rows_length = in->fetchInt();
        m_rows.clear();
        for (qint32 i = 0; i < m_rows_length; i++) {
            KeyboardButtonRow type;
            type.fetch(in);
            m_rows.append(type);
        }
        m_classType = static_cast<ReplyMarkupClassType>(x);
        return true;
    }
        break;
    
    default:
        LQTG_FETCH_ASSERT;
        return false;
    }
}

inline bool ReplyMarkup::push(OutboundPkt *out) const {
    out->appendInt(m_classType);
    switch(m_classType) {
    case typeReplyKeyboardHide: {
        out->appendInt(m_flags);
        return true;
    }
        break;
    
    case typeReplyKeyboardForceReply: {
        out->appendInt(m_flags);
        return true;
    }
        break;
    
    case typeReplyKeyboardMarkup: {
        out->appendInt(m_flags);
        out->appendInt(CoreTypes::typeVector);
        out->appendInt(m_rows.count());
        for (qint32 i = 0; i < m_rows.count(); i++) {
            m_rows[i].push(out);
        }
        return true;
    }
        break;
    
    default:
        return false;
    }
}

inline QMap<QString, QVariant> ReplyMarkup::toMap() const {
    QMap<QString, QVariant> result;
    switch(static_cast<int>(m_classType)) {
    case typeReplyKeyboardHide: {
        result["classType"] = "ReplyMarkup::typeReplyKeyboardHide";
        return result;
    }
        break;
    
    case typeReplyKeyboardForceReply: {
        result["classType"] = "ReplyMarkup::typeReplyKeyboardForceReply";
        return result;
    }
        break;
    
    case typeReplyKeyboardMarkup: {
        result["classType"] = "ReplyMarkup::typeReplyKeyboardMarkup";
        QList<QVariant> _rows;
        Q_FOREACH(const KeyboardButtonRow &m__type, m_rows)
            _rows << m__type.toMap();
        result["rows"] = _rows;
        return result;
    }
        break;
    
    default:
        return result;
    }
}

inline ReplyMarkup ReplyMarkup::fromMap(const QMap<QString, QVariant> &map) {
    ReplyMarkup result;
    if(map.value("classType").toString() == "ReplyMarkup::typeReplyKeyboardHide") {
        result.setClassType(typeReplyKeyboardHide);
        return result;
    }
    if(map.value("classType").toString() == "ReplyMarkup::typeReplyKeyboardForceReply") {
        result.setClassType(typeReplyKeyboardForceReply);
        return result;
    }
    if(map.value("classType").toString() == "ReplyMarkup::typeReplyKeyboardMarkup") {
        result.setClassType(typeReplyKeyboardMarkup);
        QList<QVariant> map_rows = map["rows"].toList();
        QList<KeyboardButtonRow> _rows;
        Q_FOREACH(const QVariant &var, map_rows)
            _rows << KeyboardButtonRow::fromMap(var.toMap());
        result.setRows(_rows);
        return result;
    }
    return result;
}

inline QByteArray ReplyMarkup::getHash(QCryptographicHash::Algorithm alg) const {
    QByteArray data;
    QDataStream str(&data, QIODevice::WriteOnly);
    str << *this;
    return QCryptographicHash::hash(data, alg);
}

inline QDataStream &operator<<(QDataStream &stream, const ReplyMarkup &item) {
    stream << static_cast<uint>(item.classType());
    switch(item.classType()) {
    case ReplyMarkup::typeReplyKeyboardHide:
        stream << item.flags();
        break;
    case ReplyMarkup::typeReplyKeyboardForceReply:
        stream << item.flags();
        break;
    case ReplyMarkup::typeReplyKeyboardMarkup:
        stream << item.flags();
        stream << item.rows();
        break;
    }
    return stream;
}

inline QDataStream &operator>>(QDataStream &stream, ReplyMarkup &item) {
    uint type = 0;
    stream >> type;
    item.setClassType(static_cast<ReplyMarkup::ReplyMarkupClassType>(type));
    switch(type) {
    case ReplyMarkup::typeReplyKeyboardHide: {
        qint32 m_flags;
        stream >> m_flags;
        item.setFlags(m_flags);
    }
        break;
    case ReplyMarkup::typeReplyKeyboardForceReply: {
        qint32 m_flags;
        stream >> m_flags;
        item.setFlags(m_flags);
    }
        break;
    case ReplyMarkup::typeReplyKeyboardMarkup: {
        qint32 m_flags;
        stream >> m_flags;
        item.setFlags(m_flags);
        QList<KeyboardButtonRow> m_rows;
        stream >> m_rows;
        item.setRows(m_rows);
    }
        break;
    }
    return stream;
}


#endif // LQTG_TYPE_REPLYMARKUP
