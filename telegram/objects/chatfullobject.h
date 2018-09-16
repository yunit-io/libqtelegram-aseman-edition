// This file generated by libqtelegram-code-generator.
// You can download it from: https://github.com/Aseman-Land/libqtelegram-code-generator
// DO NOT EDIT THIS FILE BY HAND -- YOUR CHANGES WILL BE OVERWRITTEN

#ifndef LQTG_TYPE_CHATFULL_OBJECT
#define LQTG_TYPE_CHATFULL_OBJECT

#include "telegramtypeqobject.h"
#include "telegram/types/chatfull.h"

#include <QPointer>
#include "photoobject.h"
#include "exportedchatinviteobject.h"
#include "peernotifysettingsobject.h"
#include "chatparticipantsobject.h"

class LIBQTELEGRAMSHARED_EXPORT ChatFullObject : public TelegramTypeQObject
{
    Q_OBJECT
    Q_ENUMS(ChatFullClassType)
    Q_PROPERTY(QString about READ about WRITE setAbout NOTIFY aboutChanged)
    Q_PROPERTY(qint32 adminsCount READ adminsCount WRITE setAdminsCount NOTIFY adminsCountChanged)
    Q_PROPERTY(QList<BotInfo> botInfo READ botInfo WRITE setBotInfo NOTIFY botInfoChanged)
    Q_PROPERTY(bool canViewParticipants READ canViewParticipants WRITE setCanViewParticipants NOTIFY canViewParticipantsChanged)
    Q_PROPERTY(PhotoObject* chatPhoto READ chatPhoto WRITE setChatPhoto NOTIFY chatPhotoChanged)
    Q_PROPERTY(ExportedChatInviteObject* exportedInvite READ exportedInvite WRITE setExportedInvite NOTIFY exportedInviteChanged)
    Q_PROPERTY(qint32 flags READ flags WRITE setFlags NOTIFY flagsChanged)
    Q_PROPERTY(qint32 id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(qint32 kickedCount READ kickedCount WRITE setKickedCount NOTIFY kickedCountChanged)
    Q_PROPERTY(qint32 migratedFromChatId READ migratedFromChatId WRITE setMigratedFromChatId NOTIFY migratedFromChatIdChanged)
    Q_PROPERTY(qint32 migratedFromMaxId READ migratedFromMaxId WRITE setMigratedFromMaxId NOTIFY migratedFromMaxIdChanged)
    Q_PROPERTY(PeerNotifySettingsObject* notifySettings READ notifySettings WRITE setNotifySettings NOTIFY notifySettingsChanged)
    Q_PROPERTY(ChatParticipantsObject* participants READ participants WRITE setParticipants NOTIFY participantsChanged)
    Q_PROPERTY(qint32 participantsCount READ participantsCount WRITE setParticipantsCount NOTIFY participantsCountChanged)
    Q_PROPERTY(qint32 readInboxMaxId READ readInboxMaxId WRITE setReadInboxMaxId NOTIFY readInboxMaxIdChanged)
    Q_PROPERTY(qint32 unreadCount READ unreadCount WRITE setUnreadCount NOTIFY unreadCountChanged)
    Q_PROPERTY(qint32 unreadImportantCount READ unreadImportantCount WRITE setUnreadImportantCount NOTIFY unreadImportantCountChanged)
    Q_PROPERTY(ChatFull core READ core WRITE setCore NOTIFY coreChanged)
    Q_PROPERTY(quint32 classType READ classType WRITE setClassType NOTIFY classTypeChanged)

public:
    enum ChatFullClassType {
        TypeChatFull,
        TypeChannelFull
    };

    ChatFullObject(const ChatFull &core, QObject *parent = 0);
    ChatFullObject(QObject *parent = 0);
    virtual ~ChatFullObject();

    void setAbout(const QString &about);
    QString about() const;

    void setAdminsCount(qint32 adminsCount);
    qint32 adminsCount() const;

    void setBotInfo(const QList<BotInfo> &botInfo);
    QList<BotInfo> botInfo() const;

    void setCanViewParticipants(bool canViewParticipants);
    bool canViewParticipants() const;

    void setChatPhoto(PhotoObject* chatPhoto);
    PhotoObject* chatPhoto() const;

    void setExportedInvite(ExportedChatInviteObject* exportedInvite);
    ExportedChatInviteObject* exportedInvite() const;

    void setFlags(qint32 flags);
    qint32 flags() const;

    void setId(qint32 id);
    qint32 id() const;

    void setKickedCount(qint32 kickedCount);
    qint32 kickedCount() const;

    void setMigratedFromChatId(qint32 migratedFromChatId);
    qint32 migratedFromChatId() const;

    void setMigratedFromMaxId(qint32 migratedFromMaxId);
    qint32 migratedFromMaxId() const;

    void setNotifySettings(PeerNotifySettingsObject* notifySettings);
    PeerNotifySettingsObject* notifySettings() const;

    void setParticipants(ChatParticipantsObject* participants);
    ChatParticipantsObject* participants() const;

    void setParticipantsCount(qint32 participantsCount);
    qint32 participantsCount() const;

    void setReadInboxMaxId(qint32 readInboxMaxId);
    qint32 readInboxMaxId() const;

    void setUnreadCount(qint32 unreadCount);
    qint32 unreadCount() const;

    void setUnreadImportantCount(qint32 unreadImportantCount);
    qint32 unreadImportantCount() const;

    void setClassType(quint32 classType);
    quint32 classType() const;

    void setCore(const ChatFull &core);
    ChatFull core() const;

    ChatFullObject &operator =(const ChatFull &b);
    bool operator ==(const ChatFull &b) const;

Q_SIGNALS:
    void coreChanged();
    void classTypeChanged();
    void aboutChanged();
    void adminsCountChanged();
    void botInfoChanged();
    void canViewParticipantsChanged();
    void chatPhotoChanged();
    void exportedInviteChanged();
    void flagsChanged();
    void idChanged();
    void kickedCountChanged();
    void migratedFromChatIdChanged();
    void migratedFromMaxIdChanged();
    void notifySettingsChanged();
    void participantsChanged();
    void participantsCountChanged();
    void readInboxMaxIdChanged();
    void unreadCountChanged();
    void unreadImportantCountChanged();

private Q_SLOTS:
    void coreChatPhotoChanged();
    void coreExportedInviteChanged();
    void coreNotifySettingsChanged();
    void coreParticipantsChanged();

private:
    QPointer<PhotoObject> m_chatPhoto;
    QPointer<ExportedChatInviteObject> m_exportedInvite;
    QPointer<PeerNotifySettingsObject> m_notifySettings;
    QPointer<ChatParticipantsObject> m_participants;
    ChatFull m_core;
};

inline ChatFullObject::ChatFullObject(const ChatFull &core, QObject *parent) :
    TelegramTypeQObject(parent),
    m_chatPhoto(0),
    m_exportedInvite(0),
    m_notifySettings(0),
    m_participants(0),
    m_core(core)
{
    m_chatPhoto = new PhotoObject(m_core.chatPhoto(), this);
    connect(m_chatPhoto.data(), &PhotoObject::coreChanged, this, &ChatFullObject::coreChatPhotoChanged);
    m_exportedInvite = new ExportedChatInviteObject(m_core.exportedInvite(), this);
    connect(m_exportedInvite.data(), &ExportedChatInviteObject::coreChanged, this, &ChatFullObject::coreExportedInviteChanged);
    m_notifySettings = new PeerNotifySettingsObject(m_core.notifySettings(), this);
    connect(m_notifySettings.data(), &PeerNotifySettingsObject::coreChanged, this, &ChatFullObject::coreNotifySettingsChanged);
    m_participants = new ChatParticipantsObject(m_core.participants(), this);
    connect(m_participants.data(), &ChatParticipantsObject::coreChanged, this, &ChatFullObject::coreParticipantsChanged);
}

inline ChatFullObject::ChatFullObject(QObject *parent) :
    TelegramTypeQObject(parent),
    m_chatPhoto(0),
    m_exportedInvite(0),
    m_notifySettings(0),
    m_participants(0),
    m_core()
{
    m_chatPhoto = new PhotoObject(m_core.chatPhoto(), this);
    connect(m_chatPhoto.data(), &PhotoObject::coreChanged, this, &ChatFullObject::coreChatPhotoChanged);
    m_exportedInvite = new ExportedChatInviteObject(m_core.exportedInvite(), this);
    connect(m_exportedInvite.data(), &ExportedChatInviteObject::coreChanged, this, &ChatFullObject::coreExportedInviteChanged);
    m_notifySettings = new PeerNotifySettingsObject(m_core.notifySettings(), this);
    connect(m_notifySettings.data(), &PeerNotifySettingsObject::coreChanged, this, &ChatFullObject::coreNotifySettingsChanged);
    m_participants = new ChatParticipantsObject(m_core.participants(), this);
    connect(m_participants.data(), &ChatParticipantsObject::coreChanged, this, &ChatFullObject::coreParticipantsChanged);
}

inline ChatFullObject::~ChatFullObject() {
}

inline void ChatFullObject::setAbout(const QString &about) {
    if(m_core.about() == about) return;
    m_core.setAbout(about);
    Q_EMIT aboutChanged();
    Q_EMIT coreChanged();
}

inline QString ChatFullObject::about() const {
    return m_core.about();
}

inline void ChatFullObject::setAdminsCount(qint32 adminsCount) {
    if(m_core.adminsCount() == adminsCount) return;
    m_core.setAdminsCount(adminsCount);
    Q_EMIT adminsCountChanged();
    Q_EMIT coreChanged();
}

inline qint32 ChatFullObject::adminsCount() const {
    return m_core.adminsCount();
}

inline void ChatFullObject::setBotInfo(const QList<BotInfo> &botInfo) {
    if(m_core.botInfo() == botInfo) return;
    m_core.setBotInfo(botInfo);
    Q_EMIT botInfoChanged();
    Q_EMIT coreChanged();
}

inline QList<BotInfo> ChatFullObject::botInfo() const {
    return m_core.botInfo();
}

inline void ChatFullObject::setCanViewParticipants(bool canViewParticipants) {
    if(m_core.canViewParticipants() == canViewParticipants) return;
    m_core.setCanViewParticipants(canViewParticipants);
    Q_EMIT canViewParticipantsChanged();
    Q_EMIT coreChanged();
}

inline bool ChatFullObject::canViewParticipants() const {
    return m_core.canViewParticipants();
}

inline void ChatFullObject::setChatPhoto(PhotoObject* chatPhoto) {
    if(m_chatPhoto == chatPhoto) return;
    if(m_chatPhoto) delete m_chatPhoto;
    m_chatPhoto = chatPhoto;
    if(m_chatPhoto) {
        m_chatPhoto->setParent(this);
        m_core.setChatPhoto(m_chatPhoto->core());
        connect(m_chatPhoto.data(), &PhotoObject::coreChanged, this, &ChatFullObject::coreChatPhotoChanged);
    }
    Q_EMIT chatPhotoChanged();
    Q_EMIT coreChanged();
}

inline PhotoObject*  ChatFullObject::chatPhoto() const {
    return m_chatPhoto;
}

inline void ChatFullObject::setExportedInvite(ExportedChatInviteObject* exportedInvite) {
    if(m_exportedInvite == exportedInvite) return;
    if(m_exportedInvite) delete m_exportedInvite;
    m_exportedInvite = exportedInvite;
    if(m_exportedInvite) {
        m_exportedInvite->setParent(this);
        m_core.setExportedInvite(m_exportedInvite->core());
        connect(m_exportedInvite.data(), &ExportedChatInviteObject::coreChanged, this, &ChatFullObject::coreExportedInviteChanged);
    }
    Q_EMIT exportedInviteChanged();
    Q_EMIT coreChanged();
}

inline ExportedChatInviteObject*  ChatFullObject::exportedInvite() const {
    return m_exportedInvite;
}

inline void ChatFullObject::setFlags(qint32 flags) {
    if(m_core.flags() == flags) return;
    m_core.setFlags(flags);
    Q_EMIT flagsChanged();
    Q_EMIT coreChanged();
}

inline qint32 ChatFullObject::flags() const {
    return m_core.flags();
}

inline void ChatFullObject::setId(qint32 id) {
    if(m_core.id() == id) return;
    m_core.setId(id);
    Q_EMIT idChanged();
    Q_EMIT coreChanged();
}

inline qint32 ChatFullObject::id() const {
    return m_core.id();
}

inline void ChatFullObject::setKickedCount(qint32 kickedCount) {
    if(m_core.kickedCount() == kickedCount) return;
    m_core.setKickedCount(kickedCount);
    Q_EMIT kickedCountChanged();
    Q_EMIT coreChanged();
}

inline qint32 ChatFullObject::kickedCount() const {
    return m_core.kickedCount();
}

inline void ChatFullObject::setMigratedFromChatId(qint32 migratedFromChatId) {
    if(m_core.migratedFromChatId() == migratedFromChatId) return;
    m_core.setMigratedFromChatId(migratedFromChatId);
    Q_EMIT migratedFromChatIdChanged();
    Q_EMIT coreChanged();
}

inline qint32 ChatFullObject::migratedFromChatId() const {
    return m_core.migratedFromChatId();
}

inline void ChatFullObject::setMigratedFromMaxId(qint32 migratedFromMaxId) {
    if(m_core.migratedFromMaxId() == migratedFromMaxId) return;
    m_core.setMigratedFromMaxId(migratedFromMaxId);
    Q_EMIT migratedFromMaxIdChanged();
    Q_EMIT coreChanged();
}

inline qint32 ChatFullObject::migratedFromMaxId() const {
    return m_core.migratedFromMaxId();
}

inline void ChatFullObject::setNotifySettings(PeerNotifySettingsObject* notifySettings) {
    if(m_notifySettings == notifySettings) return;
    if(m_notifySettings) delete m_notifySettings;
    m_notifySettings = notifySettings;
    if(m_notifySettings) {
        m_notifySettings->setParent(this);
        m_core.setNotifySettings(m_notifySettings->core());
        connect(m_notifySettings.data(), &PeerNotifySettingsObject::coreChanged, this, &ChatFullObject::coreNotifySettingsChanged);
    }
    Q_EMIT notifySettingsChanged();
    Q_EMIT coreChanged();
}

inline PeerNotifySettingsObject*  ChatFullObject::notifySettings() const {
    return m_notifySettings;
}

inline void ChatFullObject::setParticipants(ChatParticipantsObject* participants) {
    if(m_participants == participants) return;
    if(m_participants) delete m_participants;
    m_participants = participants;
    if(m_participants) {
        m_participants->setParent(this);
        m_core.setParticipants(m_participants->core());
        connect(m_participants.data(), &ChatParticipantsObject::coreChanged, this, &ChatFullObject::coreParticipantsChanged);
    }
    Q_EMIT participantsChanged();
    Q_EMIT coreChanged();
}

inline ChatParticipantsObject*  ChatFullObject::participants() const {
    return m_participants;
}

inline void ChatFullObject::setParticipantsCount(qint32 participantsCount) {
    if(m_core.participantsCount() == participantsCount) return;
    m_core.setParticipantsCount(participantsCount);
    Q_EMIT participantsCountChanged();
    Q_EMIT coreChanged();
}

inline qint32 ChatFullObject::participantsCount() const {
    return m_core.participantsCount();
}

inline void ChatFullObject::setReadInboxMaxId(qint32 readInboxMaxId) {
    if(m_core.readInboxMaxId() == readInboxMaxId) return;
    m_core.setReadInboxMaxId(readInboxMaxId);
    Q_EMIT readInboxMaxIdChanged();
    Q_EMIT coreChanged();
}

inline qint32 ChatFullObject::readInboxMaxId() const {
    return m_core.readInboxMaxId();
}

inline void ChatFullObject::setUnreadCount(qint32 unreadCount) {
    if(m_core.unreadCount() == unreadCount) return;
    m_core.setUnreadCount(unreadCount);
    Q_EMIT unreadCountChanged();
    Q_EMIT coreChanged();
}

inline qint32 ChatFullObject::unreadCount() const {
    return m_core.unreadCount();
}

inline void ChatFullObject::setUnreadImportantCount(qint32 unreadImportantCount) {
    if(m_core.unreadImportantCount() == unreadImportantCount) return;
    m_core.setUnreadImportantCount(unreadImportantCount);
    Q_EMIT unreadImportantCountChanged();
    Q_EMIT coreChanged();
}

inline qint32 ChatFullObject::unreadImportantCount() const {
    return m_core.unreadImportantCount();
}

inline ChatFullObject &ChatFullObject::operator =(const ChatFull &b) {
    if(m_core == b) return *this;
    m_core = b;
    m_chatPhoto->setCore(b.chatPhoto());
    m_exportedInvite->setCore(b.exportedInvite());
    m_notifySettings->setCore(b.notifySettings());
    m_participants->setCore(b.participants());

    Q_EMIT aboutChanged();
    Q_EMIT adminsCountChanged();
    Q_EMIT botInfoChanged();
    Q_EMIT canViewParticipantsChanged();
    Q_EMIT chatPhotoChanged();
    Q_EMIT exportedInviteChanged();
    Q_EMIT flagsChanged();
    Q_EMIT idChanged();
    Q_EMIT kickedCountChanged();
    Q_EMIT migratedFromChatIdChanged();
    Q_EMIT migratedFromMaxIdChanged();
    Q_EMIT notifySettingsChanged();
    Q_EMIT participantsChanged();
    Q_EMIT participantsCountChanged();
    Q_EMIT readInboxMaxIdChanged();
    Q_EMIT unreadCountChanged();
    Q_EMIT unreadImportantCountChanged();
    Q_EMIT coreChanged();
    return *this;
}

inline bool ChatFullObject::operator ==(const ChatFull &b) const {
    return m_core == b;
}

inline void ChatFullObject::setClassType(quint32 classType) {
    ChatFull::ChatFullClassType result;
    switch(classType) {
    case TypeChatFull:
        result = ChatFull::typeChatFull;
        break;
    case TypeChannelFull:
        result = ChatFull::typeChannelFull;
        break;
    default:
        result = ChatFull::typeChatFull;
        break;
    }

    if(m_core.classType() == result) return;
    m_core.setClassType(result);
    Q_EMIT classTypeChanged();
    Q_EMIT coreChanged();
}

inline quint32 ChatFullObject::classType() const {
    int result;
    switch(static_cast<qint64>(m_core.classType())) {
    case ChatFull::typeChatFull:
        result = TypeChatFull;
        break;
    case ChatFull::typeChannelFull:
        result = TypeChannelFull;
        break;
    default:
        result = TypeChatFull;
        break;
    }

    return result;
}

inline void ChatFullObject::setCore(const ChatFull &core) {
    operator =(core);
}

inline ChatFull ChatFullObject::core() const {
    return m_core;
}

inline void ChatFullObject::coreChatPhotoChanged() {
    if(m_core.chatPhoto() == m_chatPhoto->core()) return;
    m_core.setChatPhoto(m_chatPhoto->core());
    Q_EMIT chatPhotoChanged();
    Q_EMIT coreChanged();
}

inline void ChatFullObject::coreExportedInviteChanged() {
    if(m_core.exportedInvite() == m_exportedInvite->core()) return;
    m_core.setExportedInvite(m_exportedInvite->core());
    Q_EMIT exportedInviteChanged();
    Q_EMIT coreChanged();
}

inline void ChatFullObject::coreNotifySettingsChanged() {
    if(m_core.notifySettings() == m_notifySettings->core()) return;
    m_core.setNotifySettings(m_notifySettings->core());
    Q_EMIT notifySettingsChanged();
    Q_EMIT coreChanged();
}

inline void ChatFullObject::coreParticipantsChanged() {
    if(m_core.participants() == m_participants->core()) return;
    m_core.setParticipants(m_participants->core());
    Q_EMIT participantsChanged();
    Q_EMIT coreChanged();
}

#endif // LQTG_TYPE_CHATFULL_OBJECT