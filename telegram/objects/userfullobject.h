// This file generated by libqtelegram-code-generator.
// You can download it from: https://github.com/Aseman-Land/libqtelegram-code-generator
// DO NOT EDIT THIS FILE BY HAND -- YOUR CHANGES WILL BE OVERWRITTEN

#ifndef LQTG_TYPE_USERFULL_OBJECT
#define LQTG_TYPE_USERFULL_OBJECT

#include "telegramtypeqobject.h"
#include "telegram/types/userfull.h"

#include <QPointer>
#include "botinfoobject.h"
#include "contactslinkobject.h"
#include "peernotifysettingsobject.h"
#include "photoobject.h"
#include "userobject.h"

class LIBQTELEGRAMSHARED_EXPORT UserFullObject : public TelegramTypeQObject
{
    Q_OBJECT
    Q_ENUMS(UserFullClassType)
    Q_PROPERTY(QString about READ about WRITE setAbout NOTIFY aboutChanged)
    Q_PROPERTY(bool blocked READ blocked WRITE setBlocked NOTIFY blockedChanged)
    Q_PROPERTY(BotInfoObject* botInfo READ botInfo WRITE setBotInfo NOTIFY botInfoChanged)
    Q_PROPERTY(qint32 flags READ flags WRITE setFlags NOTIFY flagsChanged)
    Q_PROPERTY(ContactsLinkObject* link READ link WRITE setLink NOTIFY linkChanged)
    Q_PROPERTY(PeerNotifySettingsObject* notifySettings READ notifySettings WRITE setNotifySettings NOTIFY notifySettingsChanged)
    Q_PROPERTY(PhotoObject* profilePhoto READ profilePhoto WRITE setProfilePhoto NOTIFY profilePhotoChanged)
    Q_PROPERTY(UserObject* user READ user WRITE setUser NOTIFY userChanged)
    Q_PROPERTY(UserFull core READ core WRITE setCore NOTIFY coreChanged)
    Q_PROPERTY(quint32 classType READ classType WRITE setClassType NOTIFY classTypeChanged)

public:
    enum UserFullClassType {
        TypeUserFull
    };

    UserFullObject(const UserFull &core, QObject *parent = 0);
    UserFullObject(QObject *parent = 0);
    virtual ~UserFullObject();

    void setAbout(const QString &about);
    QString about() const;

    void setBlocked(bool blocked);
    bool blocked() const;

    void setBotInfo(BotInfoObject* botInfo);
    BotInfoObject* botInfo() const;

    void setFlags(qint32 flags);
    qint32 flags() const;

    void setLink(ContactsLinkObject* link);
    ContactsLinkObject* link() const;

    void setNotifySettings(PeerNotifySettingsObject* notifySettings);
    PeerNotifySettingsObject* notifySettings() const;

    void setProfilePhoto(PhotoObject* profilePhoto);
    PhotoObject* profilePhoto() const;

    void setUser(UserObject* user);
    UserObject* user() const;

    void setClassType(quint32 classType);
    quint32 classType() const;

    void setCore(const UserFull &core);
    UserFull core() const;

    UserFullObject &operator =(const UserFull &b);
    bool operator ==(const UserFull &b) const;

Q_SIGNALS:
    void coreChanged();
    void classTypeChanged();
    void aboutChanged();
    void blockedChanged();
    void botInfoChanged();
    void flagsChanged();
    void linkChanged();
    void notifySettingsChanged();
    void profilePhotoChanged();
    void userChanged();

private Q_SLOTS:
    void coreBotInfoChanged();
    void coreLinkChanged();
    void coreNotifySettingsChanged();
    void coreProfilePhotoChanged();
    void coreUserChanged();

private:
    QPointer<BotInfoObject> m_botInfo;
    QPointer<ContactsLinkObject> m_link;
    QPointer<PeerNotifySettingsObject> m_notifySettings;
    QPointer<PhotoObject> m_profilePhoto;
    QPointer<UserObject> m_user;
    UserFull m_core;
};

inline UserFullObject::UserFullObject(const UserFull &core, QObject *parent) :
    TelegramTypeQObject(parent),
    m_botInfo(0),
    m_link(0),
    m_notifySettings(0),
    m_profilePhoto(0),
    m_user(0),
    m_core(core)
{
    m_botInfo = new BotInfoObject(m_core.botInfo(), this);
    connect(m_botInfo.data(), &BotInfoObject::coreChanged, this, &UserFullObject::coreBotInfoChanged);
    m_link = new ContactsLinkObject(m_core.link(), this);
    connect(m_link.data(), &ContactsLinkObject::coreChanged, this, &UserFullObject::coreLinkChanged);
    m_notifySettings = new PeerNotifySettingsObject(m_core.notifySettings(), this);
    connect(m_notifySettings.data(), &PeerNotifySettingsObject::coreChanged, this, &UserFullObject::coreNotifySettingsChanged);
    m_profilePhoto = new PhotoObject(m_core.profilePhoto(), this);
    connect(m_profilePhoto.data(), &PhotoObject::coreChanged, this, &UserFullObject::coreProfilePhotoChanged);
    m_user = new UserObject(m_core.user(), this);
    connect(m_user.data(), &UserObject::coreChanged, this, &UserFullObject::coreUserChanged);
}

inline UserFullObject::UserFullObject(QObject *parent) :
    TelegramTypeQObject(parent),
    m_botInfo(0),
    m_link(0),
    m_notifySettings(0),
    m_profilePhoto(0),
    m_user(0),
    m_core()
{
    m_botInfo = new BotInfoObject(m_core.botInfo(), this);
    connect(m_botInfo.data(), &BotInfoObject::coreChanged, this, &UserFullObject::coreBotInfoChanged);
    m_link = new ContactsLinkObject(m_core.link(), this);
    connect(m_link.data(), &ContactsLinkObject::coreChanged, this, &UserFullObject::coreLinkChanged);
    m_notifySettings = new PeerNotifySettingsObject(m_core.notifySettings(), this);
    connect(m_notifySettings.data(), &PeerNotifySettingsObject::coreChanged, this, &UserFullObject::coreNotifySettingsChanged);
    m_profilePhoto = new PhotoObject(m_core.profilePhoto(), this);
    connect(m_profilePhoto.data(), &PhotoObject::coreChanged, this, &UserFullObject::coreProfilePhotoChanged);
    m_user = new UserObject(m_core.user(), this);
    connect(m_user.data(), &UserObject::coreChanged, this, &UserFullObject::coreUserChanged);
}

inline UserFullObject::~UserFullObject() {
}

inline void UserFullObject::setAbout(const QString &about) {
    if(m_core.about() == about) return;
    m_core.setAbout(about);
    Q_EMIT aboutChanged();
    Q_EMIT coreChanged();
}

inline QString UserFullObject::about() const {
    return m_core.about();
}

inline void UserFullObject::setBlocked(bool blocked) {
    if(m_core.blocked() == blocked) return;
    m_core.setBlocked(blocked);
    Q_EMIT blockedChanged();
    Q_EMIT coreChanged();
}

inline bool UserFullObject::blocked() const {
    return m_core.blocked();
}

inline void UserFullObject::setBotInfo(BotInfoObject* botInfo) {
    if(m_botInfo == botInfo) return;
    if(m_botInfo) delete m_botInfo;
    m_botInfo = botInfo;
    if(m_botInfo) {
        m_botInfo->setParent(this);
        m_core.setBotInfo(m_botInfo->core());
        connect(m_botInfo.data(), &BotInfoObject::coreChanged, this, &UserFullObject::coreBotInfoChanged);
    }
    Q_EMIT botInfoChanged();
    Q_EMIT coreChanged();
}

inline BotInfoObject*  UserFullObject::botInfo() const {
    return m_botInfo;
}

inline void UserFullObject::setFlags(qint32 flags) {
    if(m_core.flags() == flags) return;
    m_core.setFlags(flags);
    Q_EMIT flagsChanged();
    Q_EMIT coreChanged();
}

inline qint32 UserFullObject::flags() const {
    return m_core.flags();
}

inline void UserFullObject::setLink(ContactsLinkObject* link) {
    if(m_link == link) return;
    if(m_link) delete m_link;
    m_link = link;
    if(m_link) {
        m_link->setParent(this);
        m_core.setLink(m_link->core());
        connect(m_link.data(), &ContactsLinkObject::coreChanged, this, &UserFullObject::coreLinkChanged);
    }
    Q_EMIT linkChanged();
    Q_EMIT coreChanged();
}

inline ContactsLinkObject*  UserFullObject::link() const {
    return m_link;
}

inline void UserFullObject::setNotifySettings(PeerNotifySettingsObject* notifySettings) {
    if(m_notifySettings == notifySettings) return;
    if(m_notifySettings) delete m_notifySettings;
    m_notifySettings = notifySettings;
    if(m_notifySettings) {
        m_notifySettings->setParent(this);
        m_core.setNotifySettings(m_notifySettings->core());
        connect(m_notifySettings.data(), &PeerNotifySettingsObject::coreChanged, this, &UserFullObject::coreNotifySettingsChanged);
    }
    Q_EMIT notifySettingsChanged();
    Q_EMIT coreChanged();
}

inline PeerNotifySettingsObject*  UserFullObject::notifySettings() const {
    return m_notifySettings;
}

inline void UserFullObject::setProfilePhoto(PhotoObject* profilePhoto) {
    if(m_profilePhoto == profilePhoto) return;
    if(m_profilePhoto) delete m_profilePhoto;
    m_profilePhoto = profilePhoto;
    if(m_profilePhoto) {
        m_profilePhoto->setParent(this);
        m_core.setProfilePhoto(m_profilePhoto->core());
        connect(m_profilePhoto.data(), &PhotoObject::coreChanged, this, &UserFullObject::coreProfilePhotoChanged);
    }
    Q_EMIT profilePhotoChanged();
    Q_EMIT coreChanged();
}

inline PhotoObject*  UserFullObject::profilePhoto() const {
    return m_profilePhoto;
}

inline void UserFullObject::setUser(UserObject* user) {
    if(m_user == user) return;
    if(m_user) delete m_user;
    m_user = user;
    if(m_user) {
        m_user->setParent(this);
        m_core.setUser(m_user->core());
        connect(m_user.data(), &UserObject::coreChanged, this, &UserFullObject::coreUserChanged);
    }
    Q_EMIT userChanged();
    Q_EMIT coreChanged();
}

inline UserObject*  UserFullObject::user() const {
    return m_user;
}

inline UserFullObject &UserFullObject::operator =(const UserFull &b) {
    if(m_core == b) return *this;
    m_core = b;
    m_botInfo->setCore(b.botInfo());
    m_link->setCore(b.link());
    m_notifySettings->setCore(b.notifySettings());
    m_profilePhoto->setCore(b.profilePhoto());
    m_user->setCore(b.user());

    Q_EMIT aboutChanged();
    Q_EMIT blockedChanged();
    Q_EMIT botInfoChanged();
    Q_EMIT flagsChanged();
    Q_EMIT linkChanged();
    Q_EMIT notifySettingsChanged();
    Q_EMIT profilePhotoChanged();
    Q_EMIT userChanged();
    Q_EMIT coreChanged();
    return *this;
}

inline bool UserFullObject::operator ==(const UserFull &b) const {
    return m_core == b;
}

inline void UserFullObject::setClassType(quint32 classType) {
    UserFull::UserFullClassType result;
    switch(classType) {
    case TypeUserFull:
        result = UserFull::typeUserFull;
        break;
    default:
        result = UserFull::typeUserFull;
        break;
    }

    if(m_core.classType() == result) return;
    m_core.setClassType(result);
    Q_EMIT classTypeChanged();
    Q_EMIT coreChanged();
}

inline quint32 UserFullObject::classType() const {
    int result;
    switch(static_cast<qint64>(m_core.classType())) {
    case UserFull::typeUserFull:
        result = TypeUserFull;
        break;
    default:
        result = TypeUserFull;
        break;
    }

    return result;
}

inline void UserFullObject::setCore(const UserFull &core) {
    operator =(core);
}

inline UserFull UserFullObject::core() const {
    return m_core;
}

inline void UserFullObject::coreBotInfoChanged() {
    if(m_core.botInfo() == m_botInfo->core()) return;
    m_core.setBotInfo(m_botInfo->core());
    Q_EMIT botInfoChanged();
    Q_EMIT coreChanged();
}

inline void UserFullObject::coreLinkChanged() {
    if(m_core.link() == m_link->core()) return;
    m_core.setLink(m_link->core());
    Q_EMIT linkChanged();
    Q_EMIT coreChanged();
}

inline void UserFullObject::coreNotifySettingsChanged() {
    if(m_core.notifySettings() == m_notifySettings->core()) return;
    m_core.setNotifySettings(m_notifySettings->core());
    Q_EMIT notifySettingsChanged();
    Q_EMIT coreChanged();
}

inline void UserFullObject::coreProfilePhotoChanged() {
    if(m_core.profilePhoto() == m_profilePhoto->core()) return;
    m_core.setProfilePhoto(m_profilePhoto->core());
    Q_EMIT profilePhotoChanged();
    Q_EMIT coreChanged();
}

inline void UserFullObject::coreUserChanged() {
    if(m_core.user() == m_user->core()) return;
    m_core.setUser(m_user->core());
    Q_EMIT userChanged();
    Q_EMIT coreChanged();
}

#endif // LQTG_TYPE_USERFULL_OBJECT
