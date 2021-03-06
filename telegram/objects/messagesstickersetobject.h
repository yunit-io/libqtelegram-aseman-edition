// This file generated by libqtelegram-code-generator.
// You can download it from: https://github.com/Aseman-Land/libqtelegram-code-generator
// DO NOT EDIT THIS FILE BY HAND -- YOUR CHANGES WILL BE OVERWRITTEN

#ifndef LQTG_TYPE_MESSAGESSTICKERSET_OBJECT
#define LQTG_TYPE_MESSAGESSTICKERSET_OBJECT

#include "telegramtypeqobject.h"
#include "telegram/types/messagesstickerset.h"

#include <QPointer>
#include "stickersetobject.h"

class LIBQTELEGRAMSHARED_EXPORT MessagesStickerSetObject : public TelegramTypeQObject
{
    Q_OBJECT
    Q_ENUMS(MessagesStickerSetClassType)
    Q_PROPERTY(QList<Document> documents READ documents WRITE setDocuments NOTIFY documentsChanged)
    Q_PROPERTY(QList<StickerPack> packs READ packs WRITE setPacks NOTIFY packsChanged)
    Q_PROPERTY(StickerSetObject* set READ set WRITE setSet NOTIFY setChanged)
    Q_PROPERTY(MessagesStickerSet core READ core WRITE setCore NOTIFY coreChanged)
    Q_PROPERTY(quint32 classType READ classType WRITE setClassType NOTIFY classTypeChanged)

public:
    enum MessagesStickerSetClassType {
        TypeMessagesStickerSet
    };

    MessagesStickerSetObject(const MessagesStickerSet &core, QObject *parent = 0);
    MessagesStickerSetObject(QObject *parent = 0);
    virtual ~MessagesStickerSetObject();

    void setDocuments(const QList<Document> &documents);
    QList<Document> documents() const;

    void setPacks(const QList<StickerPack> &packs);
    QList<StickerPack> packs() const;

    void setSet(StickerSetObject* set);
    StickerSetObject* set() const;

    void setClassType(quint32 classType);
    quint32 classType() const;

    void setCore(const MessagesStickerSet &core);
    MessagesStickerSet core() const;

    MessagesStickerSetObject &operator =(const MessagesStickerSet &b);
    bool operator ==(const MessagesStickerSet &b) const;

Q_SIGNALS:
    void coreChanged();
    void classTypeChanged();
    void documentsChanged();
    void packsChanged();
    void setChanged();

private Q_SLOTS:
    void coreSetChanged();

private:
    QPointer<StickerSetObject> m_set;
    MessagesStickerSet m_core;
};

inline MessagesStickerSetObject::MessagesStickerSetObject(const MessagesStickerSet &core, QObject *parent) :
    TelegramTypeQObject(parent),
    m_set(0),
    m_core(core)
{
    m_set = new StickerSetObject(m_core.set(), this);
    connect(m_set.data(), &StickerSetObject::coreChanged, this, &MessagesStickerSetObject::coreSetChanged);
}

inline MessagesStickerSetObject::MessagesStickerSetObject(QObject *parent) :
    TelegramTypeQObject(parent),
    m_set(0),
    m_core()
{
    m_set = new StickerSetObject(m_core.set(), this);
    connect(m_set.data(), &StickerSetObject::coreChanged, this, &MessagesStickerSetObject::coreSetChanged);
}

inline MessagesStickerSetObject::~MessagesStickerSetObject() {
}

inline void MessagesStickerSetObject::setDocuments(const QList<Document> &documents) {
    if(m_core.documents() == documents) return;
    m_core.setDocuments(documents);
    Q_EMIT documentsChanged();
    Q_EMIT coreChanged();
}

inline QList<Document> MessagesStickerSetObject::documents() const {
    return m_core.documents();
}

inline void MessagesStickerSetObject::setPacks(const QList<StickerPack> &packs) {
    if(m_core.packs() == packs) return;
    m_core.setPacks(packs);
    Q_EMIT packsChanged();
    Q_EMIT coreChanged();
}

inline QList<StickerPack> MessagesStickerSetObject::packs() const {
    return m_core.packs();
}

inline void MessagesStickerSetObject::setSet(StickerSetObject* set) {
    if(m_set == set) return;
    if(m_set) delete m_set;
    m_set = set;
    if(m_set) {
        m_set->setParent(this);
        m_core.setSet(m_set->core());
        connect(m_set.data(), &StickerSetObject::coreChanged, this, &MessagesStickerSetObject::coreSetChanged);
    }
    Q_EMIT setChanged();
    Q_EMIT coreChanged();
}

inline StickerSetObject*  MessagesStickerSetObject::set() const {
    return m_set;
}

inline MessagesStickerSetObject &MessagesStickerSetObject::operator =(const MessagesStickerSet &b) {
    if(m_core == b) return *this;
    m_core = b;
    m_set->setCore(b.set());

    Q_EMIT documentsChanged();
    Q_EMIT packsChanged();
    Q_EMIT setChanged();
    Q_EMIT coreChanged();
    return *this;
}

inline bool MessagesStickerSetObject::operator ==(const MessagesStickerSet &b) const {
    return m_core == b;
}

inline void MessagesStickerSetObject::setClassType(quint32 classType) {
    MessagesStickerSet::MessagesStickerSetClassType result;
    switch(classType) {
    case TypeMessagesStickerSet:
        result = MessagesStickerSet::typeMessagesStickerSet;
        break;
    default:
        result = MessagesStickerSet::typeMessagesStickerSet;
        break;
    }

    if(m_core.classType() == result) return;
    m_core.setClassType(result);
    Q_EMIT classTypeChanged();
    Q_EMIT coreChanged();
}

inline quint32 MessagesStickerSetObject::classType() const {
    int result;
    switch(static_cast<qint64>(m_core.classType())) {
    case MessagesStickerSet::typeMessagesStickerSet:
        result = TypeMessagesStickerSet;
        break;
    default:
        result = TypeMessagesStickerSet;
        break;
    }

    return result;
}

inline void MessagesStickerSetObject::setCore(const MessagesStickerSet &core) {
    operator =(core);
}

inline MessagesStickerSet MessagesStickerSetObject::core() const {
    return m_core;
}

inline void MessagesStickerSetObject::coreSetChanged() {
    if(m_core.set() == m_set->core()) return;
    m_core.setSet(m_set->core());
    Q_EMIT setChanged();
    Q_EMIT coreChanged();
}

#endif // LQTG_TYPE_MESSAGESSTICKERSET_OBJECT
