// This file generated by libqtelegram-code-generator.
// You can download it from: https://github.com/Aseman-Land/libqtelegram-code-generator
// DO NOT EDIT THIS FILE BY HAND -- YOUR CHANGES WILL BE OVERWRITTEN

#ifndef LQTG_TYPE_CHAT_OBJECT
#define LQTG_TYPE_CHAT_OBJECT

#include "telegramtypeqobject.h"
#include "telegram/types/chat.h"

#include <QPointer>
#include "geopointobject.h"
#include "chatphotoobject.h"

class LIBQTELEGRAMSHARED_EXPORT ChatObject : public TelegramTypeQObject
{
    Q_OBJECT
    Q_ENUMS(ChatClassType)
    Q_PROPERTY(qint64 accessHash READ accessHash WRITE setAccessHash NOTIFY accessHashChanged)
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(bool checkedIn READ checkedIn WRITE setCheckedIn NOTIFY checkedInChanged)
    Q_PROPERTY(qint32 date READ date WRITE setDate NOTIFY dateChanged)
    Q_PROPERTY(GeoPointObject* geo READ geo WRITE setGeo NOTIFY geoChanged)
    Q_PROPERTY(qint32 id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(bool left READ left WRITE setLeft NOTIFY leftChanged)
    Q_PROPERTY(qint32 participantsCount READ participantsCount WRITE setParticipantsCount NOTIFY participantsCountChanged)
    Q_PROPERTY(ChatPhotoObject* photo READ photo WRITE setPhoto NOTIFY photoChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString venue READ venue WRITE setVenue NOTIFY venueChanged)
    Q_PROPERTY(qint32 version READ version WRITE setVersion NOTIFY versionChanged)
    Q_PROPERTY(Chat core READ core WRITE setCore NOTIFY coreChanged)
    Q_PROPERTY(quint32 classType READ classType WRITE setClassType NOTIFY classTypeChanged)

public:
    enum ChatClassType {
        TypeChatEmpty,
        TypeChat,
        TypeChatForbidden,
        TypeGeoChat
    };

    ChatObject(const Chat &core, QObject *parent = 0);
    ChatObject(QObject *parent = 0);
    virtual ~ChatObject();

    void setAccessHash(qint64 accessHash);
    qint64 accessHash() const;

    void setAddress(const QString &address);
    QString address() const;

    void setCheckedIn(bool checkedIn);
    bool checkedIn() const;

    void setDate(qint32 date);
    qint32 date() const;

    void setGeo(GeoPointObject* geo);
    GeoPointObject* geo() const;

    void setId(qint32 id);
    qint32 id() const;

    void setLeft(bool left);
    bool left() const;

    void setParticipantsCount(qint32 participantsCount);
    qint32 participantsCount() const;

    void setPhoto(ChatPhotoObject* photo);
    ChatPhotoObject* photo() const;

    void setTitle(const QString &title);
    QString title() const;

    void setVenue(const QString &venue);
    QString venue() const;

    void setVersion(qint32 version);
    qint32 version() const;

    void setClassType(quint32 classType);
    quint32 classType() const;

    void setCore(const Chat &core);
    Chat core() const;

    ChatObject &operator =(const Chat &b);
    bool operator ==(const Chat &b) const;

Q_SIGNALS:
    void coreChanged();
    void classTypeChanged();
    void accessHashChanged();
    void addressChanged();
    void checkedInChanged();
    void dateChanged();
    void geoChanged();
    void idChanged();
    void leftChanged();
    void participantsCountChanged();
    void photoChanged();
    void titleChanged();
    void venueChanged();
    void versionChanged();

private Q_SLOTS:
    void coreGeoChanged();
    void corePhotoChanged();

private:
    QPointer<GeoPointObject> m_geo;
    QPointer<ChatPhotoObject> m_photo;
    Chat m_core;
};

inline ChatObject::ChatObject(const Chat &core, QObject *parent) :
    TelegramTypeQObject(parent),
    m_geo(0),
    m_photo(0),
    m_core(core)
{
    m_geo = new GeoPointObject(m_core.geo(), this);
    connect(m_geo.data(), &GeoPointObject::coreChanged, this, &ChatObject::coreGeoChanged);
    m_photo = new ChatPhotoObject(m_core.photo(), this);
    connect(m_photo.data(), &ChatPhotoObject::coreChanged, this, &ChatObject::corePhotoChanged);
}

inline ChatObject::ChatObject(QObject *parent) :
    TelegramTypeQObject(parent),
    m_geo(0),
    m_photo(0),
    m_core()
{
    m_geo = new GeoPointObject(m_core.geo(), this);
    connect(m_geo.data(), &GeoPointObject::coreChanged, this, &ChatObject::coreGeoChanged);
    m_photo = new ChatPhotoObject(m_core.photo(), this);
    connect(m_photo.data(), &ChatPhotoObject::coreChanged, this, &ChatObject::corePhotoChanged);
}

inline ChatObject::~ChatObject() {
}

inline void ChatObject::setAccessHash(qint64 accessHash) {
    if(m_core.accessHash() == accessHash) return;
    m_core.setAccessHash(accessHash);
    Q_EMIT accessHashChanged();
    Q_EMIT coreChanged();
}

inline qint64 ChatObject::accessHash() const {
    return m_core.accessHash();
}

inline void ChatObject::setAddress(const QString &address) {
    if(m_core.address() == address) return;
    m_core.setAddress(address);
    Q_EMIT addressChanged();
    Q_EMIT coreChanged();
}

inline QString ChatObject::address() const {
    return m_core.address();
}

inline void ChatObject::setCheckedIn(bool checkedIn) {
    if(m_core.checkedIn() == checkedIn) return;
    m_core.setCheckedIn(checkedIn);
    Q_EMIT checkedInChanged();
    Q_EMIT coreChanged();
}

inline bool ChatObject::checkedIn() const {
    return m_core.checkedIn();
}

inline void ChatObject::setDate(qint32 date) {
    if(m_core.date() == date) return;
    m_core.setDate(date);
    Q_EMIT dateChanged();
    Q_EMIT coreChanged();
}

inline qint32 ChatObject::date() const {
    return m_core.date();
}

inline void ChatObject::setGeo(GeoPointObject* geo) {
    if(m_geo == geo) return;
    if(m_geo) delete m_geo;
    m_geo = geo;
    if(m_geo) {
        m_geo->setParent(this);
        m_core.setGeo(m_geo->core());
        connect(m_geo.data(), &GeoPointObject::coreChanged, this, &ChatObject::coreGeoChanged);
    }
    Q_EMIT geoChanged();
    Q_EMIT coreChanged();
}

inline GeoPointObject*  ChatObject::geo() const {
    return m_geo;
}

inline void ChatObject::setId(qint32 id) {
    if(m_core.id() == id) return;
    m_core.setId(id);
    Q_EMIT idChanged();
    Q_EMIT coreChanged();
}

inline qint32 ChatObject::id() const {
    return m_core.id();
}

inline void ChatObject::setLeft(bool left) {
    if(m_core.left() == left) return;
    m_core.setLeft(left);
    Q_EMIT leftChanged();
    Q_EMIT coreChanged();
}

inline bool ChatObject::left() const {
    return m_core.left();
}

inline void ChatObject::setParticipantsCount(qint32 participantsCount) {
    if(m_core.participantsCount() == participantsCount) return;
    m_core.setParticipantsCount(participantsCount);
    Q_EMIT participantsCountChanged();
    Q_EMIT coreChanged();
}

inline qint32 ChatObject::participantsCount() const {
    return m_core.participantsCount();
}

inline void ChatObject::setPhoto(ChatPhotoObject* photo) {
    if(m_photo == photo) return;
    if(m_photo) delete m_photo;
    m_photo = photo;
    if(m_photo) {
        m_photo->setParent(this);
        m_core.setPhoto(m_photo->core());
        connect(m_photo.data(), &ChatPhotoObject::coreChanged, this, &ChatObject::corePhotoChanged);
    }
    Q_EMIT photoChanged();
    Q_EMIT coreChanged();
}

inline ChatPhotoObject*  ChatObject::photo() const {
    return m_photo;
}

inline void ChatObject::setTitle(const QString &title) {
    if(m_core.title() == title) return;
    m_core.setTitle(title);
    Q_EMIT titleChanged();
    Q_EMIT coreChanged();
}

inline QString ChatObject::title() const {
    return m_core.title();
}

inline void ChatObject::setVenue(const QString &venue) {
    if(m_core.venue() == venue) return;
    m_core.setVenue(venue);
    Q_EMIT venueChanged();
    Q_EMIT coreChanged();
}

inline QString ChatObject::venue() const {
    return m_core.venue();
}

inline void ChatObject::setVersion(qint32 version) {
    if(m_core.version() == version) return;
    m_core.setVersion(version);
    Q_EMIT versionChanged();
    Q_EMIT coreChanged();
}

inline qint32 ChatObject::version() const {
    return m_core.version();
}

inline ChatObject &ChatObject::operator =(const Chat &b) {
    if(m_core == b) return *this;
    m_core = b;
    m_geo->setCore(b.geo());
    m_photo->setCore(b.photo());

    Q_EMIT accessHashChanged();
    Q_EMIT addressChanged();
    Q_EMIT checkedInChanged();
    Q_EMIT dateChanged();
    Q_EMIT geoChanged();
    Q_EMIT idChanged();
    Q_EMIT leftChanged();
    Q_EMIT participantsCountChanged();
    Q_EMIT photoChanged();
    Q_EMIT titleChanged();
    Q_EMIT venueChanged();
    Q_EMIT versionChanged();
    Q_EMIT coreChanged();
    return *this;
}

inline bool ChatObject::operator ==(const Chat &b) const {
    return m_core == b;
}

inline void ChatObject::setClassType(quint32 classType) {
    Chat::ChatClassType result;
    switch(classType) {
    case TypeChatEmpty:
        result = Chat::typeChatEmpty;
        break;
    case TypeChat:
        result = Chat::typeChat;
        break;
    case TypeChatForbidden:
        result = Chat::typeChatForbidden;
        break;
    case TypeGeoChat:
        result = Chat::typeGeoChat;
        break;
    default:
        result = Chat::typeChatEmpty;
        break;
    }

    if(m_core.classType() == result) return;
    m_core.setClassType(result);
    Q_EMIT classTypeChanged();
    Q_EMIT coreChanged();
}

inline quint32 ChatObject::classType() const {
    int result;
    switch(static_cast<qint64>(m_core.classType())) {
    case Chat::typeChatEmpty:
        result = TypeChatEmpty;
        break;
    case Chat::typeChat:
        result = TypeChat;
        break;
    case Chat::typeChatForbidden:
        result = TypeChatForbidden;
        break;
    case Chat::typeGeoChat:
        result = TypeGeoChat;
        break;
    default:
        result = TypeChatEmpty;
        break;
    }

    return result;
}

inline void ChatObject::setCore(const Chat &core) {
    operator =(core);
}

inline Chat ChatObject::core() const {
    return m_core;
}

inline void ChatObject::coreGeoChanged() {
    if(m_core.geo() == m_geo->core()) return;
    m_core.setGeo(m_geo->core());
    Q_EMIT geoChanged();
    Q_EMIT coreChanged();
}

inline void ChatObject::corePhotoChanged() {
    if(m_core.photo() == m_photo->core()) return;
    m_core.setPhoto(m_photo->core());
    Q_EMIT photoChanged();
    Q_EMIT coreChanged();
}

#endif // LQTG_TYPE_CHAT_OBJECT
