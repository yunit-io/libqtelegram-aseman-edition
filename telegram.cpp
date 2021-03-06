/*
 * Copyright 2014 Canonical Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors:
 *      Roberto Mier
 *      Tiago Herrmann
 */

#include "telegram.h"

#include <exception>
#include <stdexcept>
#include <openssl/sha.h>
#include <openssl/md5.h>

#include <QDebug>
#include <QLoggingCategory>
#include <QCryptographicHash>
#include <QFile>
#include <QFileInfo>
#include <QMimeDatabase>
#include <QtEndian>
#include <QImage>
#include <QImageReader>
#include <QCryptographicHash>

#include "util/tlvalues.h"
#include "telegram/types/types.h"
#include "core/dcprovider.h"
#include "telegram/telegramapi.h"
#include "secret/secretstate.h"
#include "secret/encrypter.h"
#include "secret/decrypter.h"
#include "file/filehandler.h"
#include "core/dcprovider.h"
#include "telegram/coretypes.h"
#include "secret/secretchat.h"

Q_LOGGING_CATEGORY(TG_TELEGRAM, "tg.telegram")
Q_LOGGING_CATEGORY(TG_LIB_SECRET, "tg.lib.secret")

#define CHECK_API if(!mApi) {qDebug() << __FUNCTION__ << "Error: API is not ready."; return 0;}

QSettings::Format qtelegram_default_settings_format = QSettings::IniFormat;

class TelegramPrivate
{
public:
    TelegramPrivate() :
        mLibraryState(Telegram::LoggedOut),
        mLastRetryType(Telegram::NotRetry),
        mSlept(false),
        mSecretState(0) {}

    Telegram::LibraryState mLibraryState;
    Telegram::LastRetryType mLastRetryType;

    bool mSlept;
    int initTimeout;
    int initTimerId;

    QString configPath;
    QString phoneNumber;
    QString publicKeyFile;
    Settings *mSettings;
    CryptoUtils *mCrypto;

    DcProvider *mDcProvider;
    FileHandler::Ptr mFileHandler;

    QString m_phoneCodeHash;

    // cached contacts
    QList<Contact> m_cachedContacts;
    QList<User> m_cachedUsers;
    QHash<qint64, int> pendingForwards;
    QHash<qint64, int> pendingMediaSends;

    // encrypted chats
    SecretState mSecretState;
    Encrypter *mEncrypter;
    Decrypter *mDecrypter;
    QHash<qint64, TelegramCore::Callback<EncryptedChat> > secretChatCallbacks;

    bool mLoggedIn;
    bool mCreatedSharedKeys;

    //info for retries
    QString mLastPhoneChecked;
    QString mLastLangCode;
    QList<InputContact> mLastContacts;

    QString appHash;
    qint32 appId;

    QString defaultHostAddress;
    qint16 defaultHostPort;
    qint16 defaultHostDcId;
};

Telegram::Telegram(const QString &defaultHostAddress, qint16 defaultHostPort, qint16 defaultHostDcId, qint32 appId, const QString &appHash, const QString &phoneNumber, const QString &configPath, const QString &publicKeyFile) :
    TelegramCore()
{
    // Qt5.2 doesn't support .ini files to control logging, so use this
    // manual workaround instead.
    // http://blog.qt.io/blog/2014/03/11/qt-weekly-1-categorized-logging/
    QLoggingCategory::setFilterRules(QString(qgetenv("QT_LOGGING_RULES")));

    prv = new TelegramPrivate;
    prv->initTimeout = 0;
    prv->initTimerId = 0;
    prv->configPath = configPath;
    prv->phoneNumber = phoneNumber;
    prv->publicKeyFile = publicKeyFile;
    prv->appHash = appHash;
    prv->appId = appId;
    prv->defaultHostAddress = defaultHostAddress;
    prv->defaultHostPort = defaultHostPort;
    prv->defaultHostDcId = defaultHostDcId;

    prv->mEncrypter = 0;
    prv->mDecrypter = 0;
    prv->mDcProvider = 0;
    prv->mCrypto = 0;
    prv->mSettings = 0;

}

bool Telegram::sleep() {
    // sleep only if not slept and library already logged in. Returns true if sleep operations completes
    if (!prv->mSlept && prv->mLibraryState >= LoggedIn) {
        if (mApi && mApi->mainSession()) {
            mApi->mainSession()->close();
        }
        prv->mSlept = true;
        return true;
    }
    return false;
}

bool Telegram::wake() {
    // wake only if slept and library already logged in. Returns true if wake operation completes
    if (prv->mSlept && prv->mDcProvider && prv->mLibraryState >= LoggedIn) {
        CHECK_API;
        connect(mApi, SIGNAL(mainSessionReady()), this, SIGNAL(woken()), Qt::UniqueConnection);
        DC *dc = prv->mDcProvider->getWorkingDc();
        mApi->createMainSessionToDc(dc);
        prv->mSlept = false;
        return true;
    }
    return false;
}

bool Telegram::isSlept() const
{
    return prv->mSlept;
}

void Telegram::setPhoneNumber(const QString &phoneNumber) {
    if (!prv->mSettings->loadSettings(phoneNumber)) {
        throw std::runtime_error("setPhoneNumber: could not load settings");
    }
    prv->mSecretState.load();
    prv->phoneNumber = phoneNumber;
}

void Telegram::init() {
    init(timeOut());
}

void Telegram::init(qint32 timeout) {
    // check the auth values stored in settings, check the available DCs config data if there is
    // connection to servers, and emit signals depending on user authenticated or not.
    if(mApi)
        return;

    if(prv->mEncrypter) delete prv->mEncrypter;
    if(prv->mDecrypter) delete prv->mDecrypter;
    if(prv->mDcProvider) delete prv->mDcProvider;
    if(prv->mCrypto) delete prv->mCrypto;
    if(prv->mSettings) delete prv->mSettings;

    prv->mSettings = new Settings();
    prv->mSettings->setAppHash(prv->appHash);
    prv->mSettings->setAppId(prv->appId);
    prv->mSettings->setDefaultHostAddress(prv->defaultHostAddress);
    prv->mSettings->setDefaultHostDcId(prv->defaultHostDcId);
    prv->mSettings->setDefaultHostPort(prv->defaultHostPort);

    // load settings
    if (!prv->mSettings->loadSettings(prv->phoneNumber, prv->configPath, prv->publicKeyFile)) {
        throw std::runtime_error("loadSettings failure");
    }

    prv->mCrypto = new CryptoUtils(prv->mSettings);

    prv->mDcProvider = new DcProvider(prv->mSettings, prv->mCrypto);
    prv->mDcProvider->setParent(this);

    connect(prv->mDcProvider, &DcProvider::fatalError, this, &Telegram::fatalError);
    // activate dc provider ready signal
    connect(prv->mDcProvider, &DcProvider::dcProviderReady, this, &Telegram::onDcProviderReady);
    // activate rest of dc provider signal connections
    connect(prv->mDcProvider, &DcProvider::authNeeded, this, &Telegram::authNeeded);
    connect(prv->mDcProvider, &DcProvider::authTransferCompleted, this, &Telegram::onAuthLoggedIn);

    prv->mSecretState = SecretState(prv->mSettings);
    prv->mSecretState.load();

    prv->mEncrypter = new Encrypter(prv->mSettings);
    prv->mDecrypter = new Decrypter(prv->mSettings);

    connect(prv->mDecrypter, &Decrypter::sequenceNumberGap,
            this, &Telegram::onSequenceNumberGap);

    prv->mDcProvider->initialize();

    prv->initTimeout = timeout;
    prv->initTimerId = startTimer(prv->initTimeout);
}

Telegram::~Telegram()
{
    prv->mSecretState.save();
    if(prv->mEncrypter)
        delete prv->mEncrypter;
    if(prv->mDecrypter)
        delete prv->mDecrypter;
    if(prv->mDcProvider)
        delete prv->mDcProvider;
    if(prv->mCrypto)
        delete prv->mCrypto;
    if(prv->mSettings)
        delete prv->mSettings;
    delete prv;
}

QString Telegram::defaultHostAddress()
{
    return prv->mSettings->defaultHostAddress();
}

qint16 Telegram::defaultHostPort()
{
    return prv->mSettings->defaultHostPort();
}

qint16 Telegram::defaultHostDcId()
{
    return prv->mSettings->defaultHostDcId();
}

qint32 Telegram::appId()
{
    return prv->mSettings->appId();
}

QString Telegram::appHash()
{
    return prv->mSettings->appHash();
}

Settings *Telegram::settings() const
{
    return prv->mSettings;
}

CryptoUtils *Telegram::crypto() const
{
    return prv->mCrypto;
}

void Telegram::setDefaultSettingsFormat(const QSettings::Format &format)
{
    qtelegram_default_settings_format = format;
}

QSettings::Format Telegram::defaultSettingsFormat()
{
    return qtelegram_default_settings_format;
}

bool Telegram::isConnected() {
    if (mApi && mApi->mainSession()) {
        return mApi->mainSession()->state() == QAbstractSocket::ConnectedState;
    }
    return false;
}

bool Telegram::isLoggedIn() {
    return prv->mLibraryState == LoggedIn;
}

void Telegram::onAuthLoggedIn() {
    prv->mLibraryState = LoggedIn;
    Q_EMIT authLoggedIn();
}

void Telegram::onAuthLogOutAnswer(qint64 id, bool result, const QVariant &attachedData) {
    prv->mDcProvider->logOut();
    prv->mLibraryState = LoggedOut;
    TelegramCore::onAuthLogOutAnswer(id, result, attachedData);
}

qint32 Telegram::ourId() {
    return prv->mSettings->ourId();
}

void Telegram::onDcProviderReady() {
    prv->mLibraryState = CreatedSharedKeys;
    setApi( prv->mDcProvider->getApi() );

    // secret chats
    connect(mApi, &TelegramApi::messagesRequestEncryptionAnswer, this, &Telegram::onMessagesRequestEncryptionEncryptedChat);
    connect(mApi, &TelegramApi::messagesAcceptEncryptionAnswer, this, &Telegram::onMessagesAcceptEncryptionEncryptedChat);
    connect(mApi, &TelegramApi::messagesReadEncryptedHistoryAnswer, this, &Telegram::messagesReadEncryptedHistoryAnswer);
    connect(mApi, &TelegramApi::messagesSendEncryptedAnswer, this, &Telegram::messagesSendEncryptedAnswer);
    connect(mApi, &TelegramApi::messagesSendEncryptedFileAnswer, this, &Telegram::messagesSendEncryptedFileAnswer);
    connect(mApi, &TelegramApi::messagesSendEncryptedServiceAnswer, this, &Telegram::messagesSendEncryptedServiceAnswer);

    // updates    
    connect(mApi, &TelegramApi::error, this, &Telegram::onError);
    connect(mApi, &TelegramApi::fatalError, this, &Telegram::fatalError);
    connect(mApi, &TelegramApi::updates, this, &Telegram::updates);
    connect(mApi, &TelegramApi::updatesCombined, this, &Telegram::updatesCombined);
    connect(mApi, &TelegramApi::updates, this, &Telegram::onUpdates);
    connect(mApi, &TelegramApi::updatesCombined, this, &Telegram::onUpdates);
    connect(mApi, &TelegramApi::updateShort, this, &Telegram::updateShort);
    connect(mApi, &TelegramApi::updateShort, this, &Telegram::onUpdateShort);
    connect(mApi, &TelegramApi::updateShortChatMessage, this, &Telegram::updateShortChatMessage);
    connect(mApi, &TelegramApi::updateShortMessage, this, &Telegram::updateShortMessage);
    connect(mApi, &TelegramApi::updatesTooLong, this, &Telegram::updatesTooLong);
    connect(mApi, SIGNAL(updatesGetStateAnswer(qint64, const UpdatesState&, const QVariant)), this, SIGNAL(updatesGetStateAnswer(qint64, const UpdatesState&)));

    // logic additional signal slots
    connect(mApi, SIGNAL(mainSessionDcChanged(DC*)), this, SLOT(onAuthCheckPhoneDcChanged()));
    connect(mApi, SIGNAL(mainSessionDcChanged(DC*)), this, SLOT(onHelpGetInviteTextDcChanged()));
    connect(mApi, SIGNAL(mainSessionDcChanged(DC*)), this, SLOT(onImportContactsDcChanged()));
    connect(mApi, &TelegramApi::mainSessionReady, this, &Telegram::connected);
    connect(mApi, &TelegramApi::mainSessionClosed, this, &Telegram::disconnected);

    prv->mFileHandler = FileHandler::Ptr(new FileHandler(this, mApi, prv->mCrypto, prv->mSettings, *prv->mDcProvider, prv->mSecretState));
    connect(prv->mFileHandler.data(), &FileHandler::uploadSendFileAnswer, this, &Telegram::uploadSendFileAnswer);
    connect(prv->mFileHandler.data(), &FileHandler::uploadGetFileAnswer, this, &Telegram::uploadGetFileAnswer);
    connect(prv->mFileHandler.data(), &FileHandler::uploadCancelFileAnswer, this, &Telegram::uploadCancelFileAnswer);
    connect(prv->mFileHandler.data(), &FileHandler::error, this, &Telegram::error);
    connect(prv->mFileHandler.data(), &FileHandler::messagesSentMedia, this, &Telegram::onMessagesSendMediaAnswer);
    connect(prv->mFileHandler.data(), &FileHandler::messagesSendEncryptedFileAnswer, this, &Telegram::messagesSendEncryptedFileAnswer);

    // At this point we should test the main session state and emit by hand signals of connected/disconnected
    // depending on the connection state of the session. This is so because first main session connection, if done,
    // is performed before we could connect the signal-slots to advise about it;
    if (mApi->mainSession()->state() == QAbstractSocket::ConnectedState) {
        Q_EMIT connected();
    } else {
        Q_EMIT disconnected();
    }
}

qint64 Telegram::messagesCreateEncryptedChat(const InputUser &user) {
    qCDebug(TG_LIB_SECRET) << "creating new encrypted chat";
    // generate a new object where store all the needed secret chat data
    SecretChat *secretChat = new SecretChat(prv->mSettings);
    secretChat->setAdminId(prv->mSettings->ourId());
    secretChat->setParticipantId(user.userId());
    secretChat->setRequestedUser(user);
    return generateGAorB(secretChat);
}

qint64 Telegram::messagesAcceptEncryptedChat(qint32 chatId) {
    qCDebug(TG_LIB_SECRET) << "accepting requested encrypted chat with id" << chatId;
    SecretChat *secretChat = prv->mSecretState.chats().value(chatId);

    if (!secretChat) {
        qCWarning(TG_LIB_SECRET) << "Not found any chat related to" << chatId;
        return -1;
    }
    return generateGAorB(secretChat);
}

qint64 Telegram::messagesDiscardEncryptedChat(qint32 chatId) {
    CHECK_API;
    qCDebug(TG_LIB_SECRET) << "discarding encrypted chat with id" << chatId;
    SecretChat *secretChat = prv->mSecretState.chats().value(chatId);
    if (!secretChat) {
        qCWarning(TG_LIB_SECRET) << "Trying to discard a not existant chat";
        Q_EMIT messagesEncryptedChatDiscarded(chatId);
        return -1;
    }

    TelegramCore::CallbackError error;
    TelegramCore::Callback<bool> callback = [this, secretChat](TG_MESSAGES_DISCARD_ENCRYPTION_CALLBACK) mutable {
        qint32 chatId = secretChat->chatId();
        prv->mSecretState.chats().remove(chatId);
        prv->mSecretState.save();
        qCDebug(TG_LIB_SECRET) << "Discarded secret chat" << chatId;
        delete secretChat;
        secretChat = 0;
        Q_EMIT messagesEncryptedChatDiscarded(chatId);
    };
    return messagesDiscardEncryption(chatId, callback);
}

qint64 Telegram::messagesSetEncryptedTTL(qint64 randomId, qint32 chatId, qint32 ttl) {
    CHECK_API;
    SecretChat *secretChat = prv->mSecretState.chats().value(chatId);
    if (!secretChat) {
        qCWarning(TG_LIB_SECRET) << "Could not set secret chat TTL, chat not found.";
        return -1;
    }

    DecryptedMessageAction action(DecryptedMessageAction::typeDecryptedMessageActionSetMessageTTLSecret8);
    action.setTtlSeconds(ttl);

    DecryptedMessage decryptedMessage(DecryptedMessage::typeDecryptedMessageServiceSecret17);
    decryptedMessage.setRandomId(randomId);
    decryptedMessage.setAction(action);

    prv->mEncrypter->setSecretChat(secretChat);
    QByteArray data = prv->mEncrypter->generateEncryptedData(decryptedMessage);
    InputEncryptedChat inputEncryptedChat;
    inputEncryptedChat.setChatId(chatId);
    inputEncryptedChat.setAccessHash(secretChat->accessHash());
    qint64 requestId = mApi->messagesSendEncrypted(inputEncryptedChat, randomId, data);

    secretChat->increaseOutSeqNo();
    secretChat->appendToSequence(randomId);
    prv->mSecretState.save();

    return requestId;
}

qint64 Telegram::messagesReadEncryptedHistory(qint32 chatId, qint32 maxDate) {
    CHECK_API;
    SecretChat *secretChat = prv->mSecretState.chats().value(chatId);
    if (!secretChat) {
        qCWarning(TG_LIB_SECRET) << "Could not read history of a not yet existant chat";
        return -1;
    }

    InputEncryptedChat inputEncryptedChat;
    inputEncryptedChat.setChatId(chatId);
    inputEncryptedChat.setAccessHash(secretChat->accessHash());
    return mApi->messagesReadEncryptedHistory(inputEncryptedChat, maxDate);
}

qint64 Telegram::messagesSendEncrypted(qint32 chatId, qint64 randomId, qint32 ttl, const QString &text) {
    CHECK_API;

    SecretChat *secretChat = prv->mSecretState.chats().value(chatId);
    if (!secretChat) {
        qCWarning(TG_LIB_SECRET) << "Could not find any related secret chat to send the message";
        return -1;
    }

    InputEncryptedChat inputEncryptedChat;
    inputEncryptedChat.setChatId(secretChat->chatId());
    inputEncryptedChat.setAccessHash(secretChat->accessHash());

    DecryptedMessage decryptedMessage(DecryptedMessage::typeDecryptedMessageSecret17);
    decryptedMessage.setRandomId(randomId);
    decryptedMessage.setTtl(ttl);
    decryptedMessage.setMessage(text);
    prv->mEncrypter->setSecretChat(secretChat);
    QByteArray data = prv->mEncrypter->generateEncryptedData(decryptedMessage);
    qint64 request = mApi->messagesSendEncrypted(inputEncryptedChat, randomId, data);

    secretChat->increaseOutSeqNo();
    secretChat->appendToSequence(randomId);
    prv->mSecretState.save();

    return request;
}

void Telegram::onSequenceNumberGap(qint32 chatId, qint32 startSeqNo, qint32 endSeqNo) {
    SecretChat *secretChat = prv->mSecretState.chats().value(chatId);
    ASSERT(secretChat);

    InputEncryptedChat inputEncryptedChat;
    inputEncryptedChat.setChatId(secretChat->chatId());
    inputEncryptedChat.setAccessHash(secretChat->accessHash());

    qint64 randomId;
    Utils::randomBytes(&randomId, 8);


    DecryptedMessage decryptedMessage(DecryptedMessage::typeDecryptedMessageServiceSecret17);
    decryptedMessage.setRandomId(randomId);
    DecryptedMessageAction action(DecryptedMessageAction::typeDecryptedMessageActionResendSecret17);
    action.setStartSeqNo(startSeqNo);
    action.setEndSeqNo(endSeqNo);
    decryptedMessage.setAction(action);
    prv->mEncrypter->setSecretChat(secretChat);
    QByteArray data = prv->mEncrypter->generateEncryptedData(decryptedMessage);
    mApi->messagesSendEncrypted(inputEncryptedChat, randomId, data);

    secretChat->increaseOutSeqNo();
    secretChat->appendToSequence(randomId);
    prv->mSecretState.save();
}

qint64 Telegram::messagesSendEncryptedPhoto(qint32 chatId, qint64 randomId, qint32 ttl, const QString &filePath) {

    SecretChat *secretChat = prv->mSecretState.chats().value(chatId);
    if (!secretChat) {
        qCWarning(TG_LIB_SECRET) << "Could not find any related secret chat to send the photo";
        return -1;
    }

    InputEncryptedChat inputEncryptedChat;
    inputEncryptedChat.setChatId(secretChat->chatId());
    inputEncryptedChat.setAccessHash(secretChat->accessHash());

    FileOperation *op = new FileOperation(FileOperation::sendEncryptedFile);
    op->setInputEncryptedChat(inputEncryptedChat);
    op->setRandomId(randomId);
    op->initializeKeyAndIv();
    QByteArray key = op->key();
    QByteArray iv = op->iv();

    QFileInfo fileInfo(filePath);
    qint32 size = fileInfo.size();

    QImage image;
    image.load(filePath);
    qint32 width = image.width();
    qint32 height = image.height();

    DecryptedMessage decryptedMessage(DecryptedMessage::typeDecryptedMessageSecret17);
    decryptedMessage.setRandomId(randomId);
    decryptedMessage.setTtl(ttl);

    DecryptedMessageMedia media(DecryptedMessageMedia::typeDecryptedMessageMediaPhotoSecret8);
    media.setThumbBytes(QByteArray());
    media.setW(width);
    media.setH(height);
    media.setSize(size);
    media.setKey(key);
    media.setIv(iv);
    decryptedMessage.setMedia(media);

    op->setDecryptedMessage(decryptedMessage);

    return prv->mFileHandler->uploadSendFile(*op, filePath);
}

qint64 Telegram::messagesSendEncryptedVideo(qint32 chatId, qint64 randomId, qint32 ttl, const QString &filePath, qint32 duration, qint32 width, qint32 height, const QByteArray &thumbnailBytes) {
    SecretChat *secretChat = prv->mSecretState.chats().value(chatId);
    if (!secretChat) {
        qCWarning(TG_LIB_SECRET) << "Could not find any related secret chat to send the video";
        return -1;
    }

    InputEncryptedChat inputEncryptedChat;
    inputEncryptedChat.setChatId(secretChat->chatId());
    inputEncryptedChat.setAccessHash(secretChat->accessHash());

    FileOperation *op = new FileOperation(FileOperation::sendEncryptedFile);
    op->setInputEncryptedChat(inputEncryptedChat);
    op->setRandomId(randomId);
    op->initializeKeyAndIv();
    QByteArray key = op->key();
    QByteArray iv = op->iv();

    QFileInfo fileInfo(filePath);
    qint32 size = fileInfo.size();
    QString mimeType = QMimeDatabase().mimeTypeForFile(QFileInfo(filePath)).name();

    DecryptedMessage decryptedMessage(DecryptedMessage::typeDecryptedMessageSecret17);
    decryptedMessage.setRandomId(randomId);
    decryptedMessage.setTtl(ttl);

    DecryptedMessageMedia media(DecryptedMessageMedia::typeDecryptedMessageMediaVideoSecret17);
    media.setDuration(duration);
    media.setMimeType(mimeType);
    media.setW(width);
    media.setH(height);
    media.setSize(size);
    media.setKey(key);
    media.setIv(iv);
    media.setThumbBytes(thumbnailBytes);
    decryptedMessage.setMedia(media);

    op->setDecryptedMessage(decryptedMessage);

    return prv->mFileHandler->uploadSendFile(*op, filePath);
}

qint64 Telegram::messagesSendEncryptedDocument(qint32 chatId, qint64 randomId, qint32 ttl, const QString &filePath) {

    SecretChat *secretChat = prv->mSecretState.chats().value(chatId);
    if (!secretChat) {
        qCWarning(TG_LIB_SECRET) << "Could not find any related secret chat to send the document";
        return -1;
    }

    InputEncryptedChat inputEncryptedChat;
    inputEncryptedChat.setChatId(secretChat->chatId());
    inputEncryptedChat.setAccessHash(secretChat->accessHash());

    FileOperation *op = new FileOperation(FileOperation::sendEncryptedFile);
    op->setInputEncryptedChat(inputEncryptedChat);
    op->setRandomId(randomId);
    op->initializeKeyAndIv();
    QByteArray key = op->key();
    QByteArray iv = op->iv();

    QFileInfo fileInfo(filePath);
    qint32 size = fileInfo.size();
    QString fileName = fileInfo.fileName();
    QString mimeType = QMimeDatabase().mimeTypeForFile(filePath).name();

    DecryptedMessage decryptedMessage(DecryptedMessage::typeDecryptedMessageSecret17);
    decryptedMessage.setRandomId(randomId);
    decryptedMessage.setTtl(ttl);

    DecryptedMessageMedia media(DecryptedMessageMedia::typeDecryptedMessageMediaDocumentSecret8);
    media.setThumbBytes(QByteArray());
    media.setFileName(fileName);
    media.setMimeType(mimeType);
    media.setSize(size);
    media.setKey(key);
    media.setIv(iv);
    decryptedMessage.setMedia(media);

    op->setDecryptedMessage(decryptedMessage);

    return prv->mFileHandler->uploadSendFile(*op, filePath);
}

qint64 Telegram::messagesReceivedQueue(qint32 maxQts) {
    CHECK_API;
    return mApi->messagesReceivedQueue(maxQts);
}

qint64 Telegram::messagesGetStickers(const QString &emoticon, const QString &hash) {
    CHECK_API;
    return mApi->messagesGetStickers(emoticon, hash);
}

qint64 Telegram::messagesGetAllStickers(const qint32 &hash) {
    CHECK_API;
    return mApi->messagesGetAllStickers(hash);
}

qint64 Telegram::messagesUninstallStickerSet(const InputStickerSet &stickerset) {
    CHECK_API;
    return mApi->messagesUninstallStickerSet(stickerset);
}

qint64 Telegram::messagesExportChatInvite(qint32 chatId) {
    CHECK_API;
    return mApi->messagesExportChatInvite(chatId);
}

qint64 Telegram::messagesCheckChatInvite(const QString &hash) {
    CHECK_API;
    return mApi->messagesCheckChatInvite(hash);
}

qint64 Telegram::messagesImportChatInvite(const QString &hash) {
    CHECK_API;
    return mApi->messagesImportChatInvite(hash);
}

qint64 Telegram::generateGAorB(SecretChat *secretChat) {
    CHECK_API;
    qCDebug(TG_LIB_SECRET) << "requesting for DH config parameters";
    // call messages.getDhConfig to get p and g for start creating shared key
    qint64 reqId = mApi->messagesGetDhConfig(prv->mSecretState.version(), DH_CONFIG_SERVER_RANDOM_LENGTH);
    // store in secret chats map related to this request id, temporally
    prv->mSecretState.chats().insert(reqId, secretChat);
    prv->mSecretState.save();
    return reqId;
}

void Telegram::onMessagesGetDhConfigAnswer(qint64 msgId, const MessagesDhConfig &result, const QVariant &attachedData) {

    if (result.classType() == MessagesDhConfig::MessagesDhConfigClassType::typeMessagesDhConfigNotModified)
    {
        onMessagesDhConfigNotModified(msgId, result.random());
        return;
    }
    qCDebug(TG_LIB_SECRET) << "received new DH parameters g ="<< result.g() << ",p =" << result.p().toBase64()
                           << ",version =" << result.version();

    prv->mSecretState.setVersion(result.version());
    prv->mSecretState.setG(result.g());
    prv->mSecretState.setP(result.p());

    if (prv->mCrypto->checkDHParams(prv->mSecretState.p(), result.g()) < 0 &&
        result.classType() == MessagesDhConfig::typeMessagesDhConfig) {
        qCCritical(TG_TELEGRAM) << "Diffie-Hellman config parameters are not valid";

    } else {
        onMessagesDhConfigNotModified(msgId, result.random());
    }
}

void Telegram::onMessagesDhConfigNotModified(qint64 msgId, const QByteArray &random) {
    qCDebug(TG_LIB_SECRET) << "processing DH parameters";
    SecretChat *secretChat = prv->mSecretState.chats().take(msgId);
    prv->mSecretState.save();
    ASSERT(secretChat);
    // create secret a number by taking server random (and generating a client random also to have more entrophy)
    secretChat->createMyKey(random);
    // create empty bignum where store the result of operation g^a mod p
    BIGNUM *r = BN_new();
    Utils::ensurePtr(r);
    // do the opeation -> r = g^a mod p
    Utils::ensure(prv->mCrypto->BNModExp(r, prv->mSecretState.g(), secretChat->myKey(), prv->mSecretState.p()));
    // check that g and r are greater than one and smaller than p-1. Also checking that r is between 2^{2048-64} and p - 2^{2048-64}
    if (prv->mCrypto->checkCalculatedParams(r, prv->mSecretState.g(), prv->mSecretState.p()) < 0) {
        qCCritical(TG_LIB_SECRET) << "gAOrB or g params are not valid";
        return;
    }
    // convert result to big endian before sending request encryption query
    uchar rawGAOrB[256];
    memset(rawGAOrB, 0, 256);
    BN_bn2bin(r, rawGAOrB);
    QByteArray gAOrB = QByteArray::fromRawData(reinterpret_cast<char*>(rawGAOrB), 256);

    switch (static_cast<qint32>(secretChat->state())) {
    case SecretChat::Init: {
        // generate randomId, used not only to request encryption but as chatId
        qint32 randomId;
        Utils::randomBytes(&randomId, 4);
        secretChat->setChatId(randomId);
        prv->mSecretState.chats().insert(randomId, secretChat);
        prv->mSecretState.save();
        qCDebug(TG_LIB_SECRET) << "Requesting encryption for chatId" << secretChat->chatId();
        mApi->messagesRequestEncryption(secretChat->requestedUser(), randomId, gAOrB);
        break;
    }
    case SecretChat::Requested: {
        QByteArray gA = secretChat->gAOrB();

        createSharedKey(secretChat, prv->mSecretState.p(), gA);
        qint64 keyFingerprint = secretChat->keyFingerprint();

        InputEncryptedChat inputEncryptedChat;
        inputEncryptedChat.setChatId(secretChat->chatId());
        inputEncryptedChat.setAccessHash(secretChat->accessHash());
        qCDebug(TG_LIB_SECRET) << "Accepting encryption for chatId" << secretChat->chatId();
        mApi->messagesAcceptEncryption(inputEncryptedChat, gAOrB, keyFingerprint);
        break;
    }
    default:
        Q_ASSERT("Not handled");
        break;
    }

    BN_free(r);
    prv->mSecretState.save();
}

void Telegram::onMessagesRequestEncryptionEncryptedChat(qint64, const EncryptedChat &chat) {
    Q_EMIT messagesCreateEncryptedChatAnswer(chat.id(), chat.date(), chat.participantId(), chat.accessHash());
}

void Telegram::onMessagesAcceptEncryptionEncryptedChat(qint64, const EncryptedChat &chat) {
    qCDebug(TG_LIB_SECRET) << "Joined to secret chat" << chat.id() << "with peer" << chat.adminId();
    SecretChat *secretChat = prv->mSecretState.chats().value(chat.id());
    secretChat->setState(SecretChat::Accepted);
    prv->mSecretState.save();
    Q_EMIT messagesEncryptedChatCreated(chat.id(), chat.date(), chat.adminId(), chat.accessHash());

    //notify peer about our layer
    InputEncryptedChat inputEncryptedChat;
    inputEncryptedChat.setChatId(chat.id());
    inputEncryptedChat.setAccessHash(secretChat->accessHash());

    prv->mEncrypter->setSecretChat(secretChat);
    qint64 randomId;
    Utils::randomBytes(&randomId, 8);

    DecryptedMessage decryptedMessage(DecryptedMessage::typeDecryptedMessageServiceSecret17);
    decryptedMessage.setRandomId(randomId);

    DecryptedMessageAction action(DecryptedMessageAction::typeDecryptedMessageActionNotifyLayerSecret17);
    action.setLayer(CoreTypes::typeLayerVersion);
    decryptedMessage.setAction(action);

    QByteArray data = prv->mEncrypter->generateEncryptedData(decryptedMessage);
    mApi->messagesSendEncryptedService(inputEncryptedChat, randomId, data);

    secretChat->increaseOutSeqNo();
    secretChat->appendToSequence(randomId);
    prv->mSecretState.save();

    qCDebug(TG_LIB_SECRET) << "Notified our layer:" << CoreTypes::typeLayerVersion;
}

void Telegram::onUpdateShort(const Update &update) {
    processSecretChatUpdate(update);
}

void Telegram::onUpdates(const QList<Update> &udts) {
    Q_FOREACH (const Update &update, udts) {
        processSecretChatUpdate(update);
    }
}

void Telegram::timerEvent(QTimerEvent *e)
{
    if(e->timerId() == prv->initTimerId)
    {
        killTimer(prv->initTimerId);
        prv->initTimerId = 0;
        if(!mApi)
	{
            qWarning() << "Timeout error initializing. Retrying...";
            if(prv->initTimeout <= 30000)
                prv->initTimeout *= 2;
            init(prv->initTimeout);
	}
    }
    else
        QObject::timerEvent(e);
}

SecretChatMessage Telegram::toSecretChatMessage(const EncryptedMessage &encrypted) {

    SecretChatMessage secretChatMessage;

    qint32 chatId = encrypted.chatId();
    SecretChat *secretChat = prv->mSecretState.chats().value(chatId);

    if (!secretChat) {
        qCWarning(TG_LIB_SECRET) << "received encrypted message does not belong to any known secret chat";
        return secretChatMessage;
    }

    secretChatMessage.setChatId(chatId);
    secretChatMessage.setDate(encrypted.date());

    prv->mDecrypter->setSecretChat(secretChat);
    DecryptedMessage decrypted = prv->mDecrypter->decryptEncryptedData(encrypted.randomId(), encrypted.bytes());
    secretChatMessage.setDecryptedMessage(decrypted);

    // if having a not 0 randomId, the decrypted message is valid
    if (decrypted.randomId()) {

        EncryptedFile attachment = encrypted.file();

        //if attachment, check keyFingerprint
        if (attachment.classType() != EncryptedFile::typeEncryptedFileEmpty) {

            qint32 receivedKeyFingerprint = attachment.keyFingerprint();
            const QByteArray &key = decrypted.media().key();
            const QByteArray &iv = decrypted.media().iv();
            qint32 computedKeyFingerprint = prv->mCrypto->computeKeyFingerprint(key, iv);

            qCDebug(TG_LIB_SECRET) << "received keyFingerprint:" << receivedKeyFingerprint;
            qCDebug(TG_LIB_SECRET) << "computed keyFingerprint:" << computedKeyFingerprint;

            if (receivedKeyFingerprint != computedKeyFingerprint) {
                 qCWarning(TG_LIB_SECRET) << "Computed and received key fingerprints are not equals. Discarding message";
                 return secretChatMessage;
            }

            secretChatMessage.setAttachment(attachment);
        }

        prv->mSecretState.save();
    }

    return secretChatMessage;
}

void Telegram::processSecretChatUpdate(const Update &update) {
    switch (static_cast<qint32>(update.classType())) {
    case Update::typeUpdateNewEncryptedMessage: {
        EncryptedMessage encrypted = update.messageEncrypted();

        SecretChatMessage secretChatMessage = toSecretChatMessage(encrypted);

        // if having a not 0 randomId, the decrypted message is valid
        if (secretChatMessage.decryptedMessage().randomId()) {
            prv->mSecretState.save();
            qint32 qts = update.qts();
            Q_EMIT updateSecretChatMessage(secretChatMessage, qts);
        }

        break;
    }
    case Update::typeUpdateEncryption: {

        const EncryptedChat &encryptedChat = update.chat();
        qint32 chatId = encryptedChat.id();
        switch (static_cast<qint32>(encryptedChat.classType())) {
        case EncryptedChat::typeEncryptedChatRequested: {

            // here, we have received a request of creating a new secret chat. Emit a signal
            // with chat details for user B to accept or reject chat creation
            qint64 accessHash = encryptedChat.accessHash();
            qint32 date = encryptedChat.date();
            qint32 adminId = encryptedChat.adminId();
            qint32 participantId = encryptedChat.participantId();
            QByteArray gA = encryptedChat.gA();

            qCDebug(TG_LIB_SECRET) << "Requested secret chat creation:";
            qCDebug(TG_LIB_SECRET) << "chatId:" << chatId;
            qCDebug(TG_LIB_SECRET) << "date:" << date;
            qCDebug(TG_LIB_SECRET) << "adminId:" << adminId;
            qCDebug(TG_LIB_SECRET) << "participantId:" << participantId;
            qCDebug(TG_LIB_SECRET) << "gA:" << gA.toBase64();
            qCDebug(TG_LIB_SECRET) << "ourId:" << ourId();

            ASSERT(participantId == ourId());

            SecretChat* secretChat = new SecretChat(prv->mSettings);
            secretChat->setChatId(encryptedChat.id());
            secretChat->setAccessHash(encryptedChat.accessHash());
            secretChat->setDate(encryptedChat.date());
            secretChat->setAdminId(encryptedChat.adminId());
            secretChat->setParticipantId(encryptedChat.participantId());
            secretChat->setGAOrB(gA);
            secretChat->setState(SecretChat::Requested);

            prv->mSecretState.chats().insert(chatId, secretChat);
            prv->mSecretState.save();
            Q_EMIT messagesEncryptedChatRequested(chatId, date, adminId, accessHash);
            break;
        }
        case EncryptedChat::typeEncryptedChat: {

            qCDebug(TG_LIB_SECRET) << "received encrypted chat creation update";
            // here, the request for encryption has been accepted. Take the secret chat data
            qint64 accessHash = encryptedChat.accessHash();
            qint32 date = encryptedChat.date();
            qint32 adminId = encryptedChat.adminId();
            qint32 participantId = encryptedChat.participantId();
            QByteArray gB = encryptedChat.gAOrB();
            qint64 keyFingerprint = encryptedChat.keyFingerprint();

            qCDebug(TG_LIB_SECRET) << "Peer accepted secret chat creation:";
            qCDebug(TG_LIB_SECRET) << "chatId:" << chatId;
            qCDebug(TG_LIB_SECRET) << "accessHash:" << accessHash;
            qCDebug(TG_LIB_SECRET) << "date:" << date;
            qCDebug(TG_LIB_SECRET) << "adminId:" << adminId;
            qCDebug(TG_LIB_SECRET) << "participantId:" << participantId;
            qCDebug(TG_LIB_SECRET) << "gB:" << gB.toBase64();
            qCDebug(TG_LIB_SECRET) << "received keyFingerprint:" << keyFingerprint;

            SecretChat *secretChat = prv->mSecretState.chats().value(chatId);
            if (!secretChat) {
                qCWarning(TG_LIB_SECRET) << "Could not find secret chat with id" << chatId;
                return;
            }

            createSharedKey(secretChat, prv->mSecretState.p(), gB);

            qint64 calculatedKeyFingerprint = secretChat->keyFingerprint();
            qCDebug(TG_LIB_SECRET) << "calculated keyFingerprint:" << calculatedKeyFingerprint;

            if (calculatedKeyFingerprint == keyFingerprint) {
                qCDebug(TG_LIB_SECRET) << "Generated shared key for secret chat" << chatId;
                secretChat->setChatId(chatId);
                secretChat->setAccessHash(accessHash);
                secretChat->setDate(date);
                secretChat->setAdminId(adminId);
                secretChat->setParticipantId(participantId);
                secretChat->setState(SecretChat::Accepted);
                qCDebug(TG_LIB_SECRET) << "Joined to secret chat" << chatId << "with peer" << participantId;
                prv->mSecretState.save();
                Q_EMIT messagesEncryptedChatCreated(chatId, date, participantId, accessHash);

                //notify peer about our layer
                InputEncryptedChat inputEncryptedChat;
                inputEncryptedChat.setChatId(chatId);
                inputEncryptedChat.setAccessHash(accessHash);

                prv->mEncrypter->setSecretChat(secretChat);
                qint64 randomId;
                Utils::randomBytes(&randomId, 8);

                DecryptedMessage decryptedMessage(DecryptedMessage::typeDecryptedMessageServiceSecret17);
                decryptedMessage.setRandomId(randomId);

                DecryptedMessageAction action(DecryptedMessageAction::typeDecryptedMessageActionNotifyLayerSecret17);
                action.setLayer(CoreTypes::typeLayerVersion);
                decryptedMessage.setAction(action);


                QByteArray data = prv->mEncrypter->generateEncryptedData(decryptedMessage);
                mApi->messagesSendEncryptedService(inputEncryptedChat, randomId, data);

                secretChat->increaseOutSeqNo();
                secretChat->appendToSequence(randomId);
                prv->mSecretState.save();

                qCDebug(TG_LIB_SECRET) << "Notified our layer:" << CoreTypes::typeLayerVersion;
            } else {
                qCCritical(TG_LIB_SECRET) << "Key fingerprint mismatch. Discarding encryption";
                messagesDiscardEncryptedChat(chatId);
            }
            break;
        }
        case EncryptedChat::typeEncryptedChatDiscarded: {
            qCDebug(TG_LIB_SECRET) << "Discarded chat" << chatId;
            SecretChat *secretChat = prv->mSecretState.chats().take(chatId);
            if (secretChat) {
                prv->mSecretState.save();
                delete secretChat;
                secretChat = 0;
            }
            Q_EMIT messagesEncryptedChatDiscarded(chatId);
            break;
        }
        case EncryptedChat::typeEncryptedChatWaiting: {
            qCDebug(TG_LIB_SECRET) << "Waiting for peer to accept chat" << chatId;

            if (encryptedChat.participantId() != ourId()) {
#if (QT_VERSION >= QT_VERSION_CHECK(5, 4, 0))
                qCritical(TG_LIB_SECRET()) << "Received request to create a secret chat is not for you!";
#endif
                return;
            }

            SecretChat* secretChat = prv->mSecretState.chats().value(chatId);
            if (secretChat) {
                secretChat->setState(SecretChat::Requested);
                qint32 date = encryptedChat.date();
                qint32 adminId = encryptedChat.adminId();
                qint64 accessHash = encryptedChat.accessHash();
                Q_EMIT messagesEncryptedChatRequested(chatId, date, adminId, accessHash);
            }
            break;
        }
        default:
            Q_ASSERT("Not handled");
            break;
        }
    }
    default:
        Q_ASSERT("Not handled");
        break;
    }
}

void Telegram::createSharedKey(SecretChat *secretChat, BIGNUM *p, QByteArray gAOrB) {
    // calculate the shared key by doing key = B^a mod p
    BIGNUM *myKey = secretChat->myKey();
    // padding of B (gAOrB) must have exactly 256 bytes. After pad, transform to bignum
    BIGNUM *bigNumGAOrB = Utils::padBytesAndGetBignum(gAOrB);

    // create empty bignum where store the result of operation g^a mod p
    BIGNUM *result = BN_new();
    Utils::ensurePtr(result);
    // do the opeation -> k = g_b^a mod p
    Utils::ensure(prv->mCrypto->BNModExp(result, bigNumGAOrB, myKey, p));

    // move r (BIGNUM) to shared key (char[]) array format
    uchar *sharedKey = secretChat->sharedKey();
    memset(sharedKey, 0, SHARED_KEY_LENGTH);
    BN_bn2bin(result, sharedKey + (SHARED_KEY_LENGTH - BN_num_bytes (result)));

    qint64 keyFingerprint = Utils::getKeyFingerprint(sharedKey);
    secretChat->setKeyFingerprint(keyFingerprint);

    BN_free(bigNumGAOrB);
}

// error and internal managements
void Telegram::onError(qint64 id, qint32 errorCode, const QString &errorText, const QString &functionName, const QVariant &attachedData, bool &accepted) {
    if (errorText.contains("_MIGRATE_"))
    {
        //prv->mLastRetryMessages << id;
        qint32 newDc = errorText.mid(errorText.lastIndexOf("_") + 1).toInt();
        qWarning() << "migrated to dc" << newDc;
        prv->mSettings->setWorkingDcNum(newDc);
        prv->mSettings->writeAuthFile();
        DC *dc = prv->mDcProvider->getDc(newDc);
        mApi->changeMainSessionToDc(dc);
    }
    else
    if(errorCode == 400)
    {
        if(errorText == "ENCRYPTION_ALREADY_DECLINED") { /* This is an already declined chat, remove it from DB */
            onMessagesDiscardEncryptionAnswer(id, true, attachedData);
            return;
        }
    }
    else
    if (errorCode == 401)
    {
        if(errorText == "SESSION_PASSWORD_NEEDED")
            qDebug() << errorText; // Nothing to do
        else
            onAuthLogOutAnswer(id, true, attachedData);
    }
    else
    if(functionName == "onUploadGetFileError")
    {
        onUploadGetFileError(id, errorCode, errorText, attachedData);
    }
    TelegramCore::onError(id, errorCode, errorText, functionName, attachedData, accepted);
}

void Telegram::onErrorRetry(qint64 id, qint32 errorCode, const QString &errorText) {
    if (errorText.contains("_MIGRATE_")) {
        qint32 newDc = errorText.mid(errorText.lastIndexOf("_") + 1).toInt();
        qWarning() << "migrated to dc" << newDc;
        prv->mSettings->setWorkingDcNum(newDc);
        prv->mSettings->writeAuthFile();
        DC *dc = prv->mDcProvider->getDc(newDc);
        mApi->changeMainSessionToDc(dc);
    } else {
        Q_EMIT error(id, errorCode, errorText, QString());
    }
}

void Telegram::onAuthCheckPhoneDcChanged() {
    if (prv->mLastRetryType != PhoneCheck) return;
    TelegramCore::authCheckPhone(prv->mLastPhoneChecked);
}
void Telegram::onHelpGetInviteTextDcChanged() {
    if (prv->mLastRetryType != GetInviteText) return;
    helpGetInviteText();
}
void Telegram::onImportContactsDcChanged() {
    if (prv->mLastRetryType != ImportContacts)
        return;
    // Retry is hardcoded to not overwrite contacts.
    contactsImportContacts(prv->mLastContacts, false);
}


void Telegram::authorizeUser(qint64, const User &) {
    // change state of current dc
    qint32 workingDcNum = prv->mSettings->workingDcNum();
    DC *dc = prv->mDcProvider->getDc(workingDcNum);
    dc->setState(DC::userSignedIn);
    QList<DC *> dcsList = prv->mDcProvider->getDcs();
    // save the settings here, after user auth ready in current dc
    prv->mSettings->setDcsList(dcsList);
    prv->mSettings->writeAuthFile();
    // transfer current dc authorization to other dcs
    prv->mDcProvider->transferAuth();
}

void Telegram::onContactsGetContactsAnswer(qint64 msgId, const ContactsContacts &result, const QVariant &attachedData) {
    prv->m_cachedContacts = result.contacts();
    prv->m_cachedUsers = result.users();
    TelegramCore::onContactsGetContactsAnswer(msgId, result, attachedData);
}


void Telegram::onContactsImportContactsAnswer() {
    prv->mLastContacts.clear();
}

// not direct Responses

void Telegram::onAuthSendCodeAnswer(qint64 msgId, const AuthSentCode &result, const QVariant &attachedData) {
    prv->m_phoneCodeHash = result.phoneCodeHash();
    TelegramCore::onAuthSendCodeAnswer(msgId, result, attachedData);
}

void Telegram::onAuthSignUpAnswer(qint64 msgId, const AuthAuthorization &result, const QVariant &attachedData)
{
    authorizeUser(msgId, result.user());
    TelegramCore::onAuthSignUpAnswer(msgId, result, attachedData);
}

void Telegram::onAuthSignInAnswer(qint64 msgId, const AuthAuthorization &result, const QVariant &attachedData)
{
    authorizeUser(msgId, result.user());
    TelegramCore::onAuthSignInAnswer(msgId, result, attachedData);
}

void Telegram::onAuthCheckPasswordAnswer(qint64 msgId, const AuthAuthorization &result, const QVariant &attachedData)
{
    authorizeUser(msgId, result.user());
    TelegramCore::onAuthCheckPasswordAnswer(msgId, result, attachedData);
}

//void Telegram::onAuthImportBotAuthorizationAnswer(qint64 msgId, const AuthAuthorization &result, const QVariant &attachedData)
//{
//    authorizeUser(msgId, result.user());
//    TelegramCore::onAuthImportBotAuthorizationAnswer(msgId, result, attachedData);
//}

void Telegram::onUpdatesGetDifferenceAnswer(qint64 id, const UpdatesDifference &result, const QVariant &attachedData) {
    processDifferences(id, result.newMessages(), result.newEncryptedMessages(), result.otherUpdates(),
                       result.chats(), result.users(), result.state(),
                       (result.classType() == UpdatesDifference::typeUpdatesDifferenceSlice));
    TelegramCore::onUpdatesGetDifferenceAnswer(id, result, attachedData);
}

void Telegram::onMessagesAcceptEncryptionAnswer(qint64 msgId, const EncryptedChat &result, const QVariant &attachedData)
{
    qCDebug(TG_LIB_SECRET) << "Joined to secret chat" << result.id() << "with peer" << result.adminId();
    SecretChat *secretChat = prv->mSecretState.chats().value(result.id());
    secretChat->setState(SecretChat::Accepted);
    prv->mSecretState.save();
    Q_EMIT messagesEncryptedChatCreated(result.id(), result.date(), result.adminId(), result.accessHash());

    //notify peer about our layer
    InputEncryptedChat inputEncryptedChat;
    inputEncryptedChat.setChatId(result.id());
    inputEncryptedChat.setAccessHash(secretChat->accessHash());

    prv->mEncrypter->setSecretChat(secretChat);
    qint64 randomId;
    Utils::randomBytes(&randomId, 8);

    DecryptedMessageAction action(DecryptedMessageAction::typeDecryptedMessageActionNotifyLayerSecret17);
    action.setLayer(CoreTypes::typeLayerVersion);

    DecryptedMessage decryptedMessage(DecryptedMessage::typeDecryptedMessageServiceSecret17);
    decryptedMessage.setRandomId(randomId);
    decryptedMessage.setAction(action);

    QByteArray data = prv->mEncrypter->generateEncryptedData(decryptedMessage);
    TelegramCore::messagesSendEncryptedService(inputEncryptedChat, randomId, data);

    secretChat->increaseOutSeqNo();
    secretChat->appendToSequence(randomId);
    prv->mSecretState.save();

    qCDebug(TG_LIB_SECRET) << "Notified our layer:" << CoreTypes::typeLayerVersion;
    TelegramCore::onMessagesAcceptEncryptionAnswer(msgId, result, attachedData);
}

void Telegram::processDifferences(qint64 id, const QList<Message> &messages, const QList<EncryptedMessage> &newEncryptedMessages, const QList<Update> &otherUpdates, const QList<Chat> &chats, const QList<User> &users, const UpdatesState &state, bool isIntermediateState) {

    Q_FOREACH (const Update &update, otherUpdates) {
        processSecretChatUpdate(update);
    }

    QList<SecretChatMessage> secretChatMessages;

    Q_FOREACH (const EncryptedMessage &encrypted, newEncryptedMessages) {
        SecretChatMessage secretChatMessage = toSecretChatMessage(encrypted);

        if (secretChatMessage.decryptedMessage().randomId()) {
            secretChatMessages << secretChatMessage;
        }
    }

    Q_EMIT updatesGetDifferenceAnswer(id, messages, secretChatMessages, otherUpdates, chats, users, state, isIntermediateState);
}
// Requests

qint64 Telegram::authCheckPhone() {
   return TelegramCore::authCheckPhone(prv->mSettings->phoneNumber());
}

qint64 Telegram::authSendCode() {
    CHECK_API;
    return mApi->authSendCode(true, prv->mSettings->phoneNumber(), true, prv->mSettings->appId(), prv->mSettings->appHash());
}

qint64 Telegram::authSignIn(const QString &code) {
    CHECK_API;
    return mApi->authSignIn(prv->mSettings->phoneNumber(), prv->m_phoneCodeHash, code);
}

qint64 Telegram::authSignUp(const QString &code, const QString &firstName, const QString &lastName) {
    CHECK_API;
    return mApi->authSignUp(prv->mSettings->phoneNumber(), prv->m_phoneCodeHash, code, firstName, lastName);
}

qint64 Telegram::authLogOut() {
    CHECK_API;
    return mApi->authLogOut();
}

qint64 Telegram::authSendInvites(const QStringList &phoneNumbers, const QString &inviteText) {
    CHECK_API;
    return mApi->authSendInvites(phoneNumbers, inviteText);
}

qint64 Telegram::authResetAuthorizations() {
    CHECK_API;
    return mApi->authResetAuthorizations();
}

qint64 Telegram::authCheckPassword(const QByteArray &password) {
    CHECK_API;
    return mApi->authCheckPassword(password);
}

qint64 Telegram::accountRegisterDevice(const QString &token, const QString &appVersion, bool appSandbox) {
    CHECK_API;
    if (token.length() == 0) {
        qCCritical(TG_TELEGRAM) << "refuse to register with empty token!";
        return -1;
    }
    QString version = appVersion;
    if (!version.length()) {
        version = Utils::getAppVersion();
    }
    qCDebug(TG_TELEGRAM) << "registering device for push - app version" << version;
    return mApi->accountRegisterDevice(UBUNTU_PHONE_TOKEN_TYPE, token);
}

qint64 Telegram::accountUnregisterDevice(const QString &token) {
    CHECK_API;
    return mApi->accountUnregisterDevice(UBUNTU_PHONE_TOKEN_TYPE, token);
}

qint64 Telegram::accountUpdateNotifySettings(const InputNotifyPeer &peer, const InputPeerNotifySettings &settings) {
    CHECK_API;
    return mApi->accountUpdateNotifySettings(peer, settings);
}

qint64 Telegram::accountGetNotifySettings(const InputNotifyPeer &peer) {
    CHECK_API;
    return mApi->accountGetNotifySettings(peer);
}

qint64 Telegram::accountResetNotifySettings() {
    CHECK_API;
    return mApi->accountResetNotifySettings();
}

qint64 Telegram::accountUpdateProfile(const QString &firstName, const QString &lastName) {
    CHECK_API;
    return mApi->accountUpdateProfile(firstName, lastName, QString());
}

qint64 Telegram::accountUpdateStatus(bool offline) {
    CHECK_API;
    return mApi->accountUpdateStatus(offline);
}

qint64 Telegram::accountGetWallPapers() {
    CHECK_API;
    return mApi->accountGetWallPapers();
}

qint64 Telegram::accountCheckUsername(const QString &username) {
    CHECK_API;
    return mApi->accountCheckUsername(username);
}

qint64 Telegram::accountUpdateUsername(const QString &username) {
    CHECK_API;
    return mApi->accountUpdateUsername(username);
}

qint64 Telegram::accountGetPrivacy(const InputPrivacyKey &key) {
    CHECK_API;
    return mApi->accountGetPrivacy(key);
}

qint64 Telegram::accountSetPrivacy(const InputPrivacyKey &key, const QList<InputPrivacyRule> &rules) {
    CHECK_API;
    return mApi->accountSetPrivacy(key, rules);
}

qint64 Telegram::accountDeleteAccount(const QString &reason) {
    CHECK_API;
    return mApi->accountDeleteAccount(reason);
}

qint64 Telegram::accountGetAccountTTL() {
    CHECK_API;
    return mApi->accountGetAccountTTL();
}

qint64 Telegram::accountSetAccountTTL(const AccountDaysTTL &ttl) {
    CHECK_API;
    return mApi->accountSetAccountTTL(ttl);
}

qint64 Telegram::accountUpdateDeviceLocked(int period) {
    CHECK_API;
    return mApi->accountUpdateDeviceLocked(period);
}

qint64 Telegram::accountSendChangePhoneCode(const QString &phone_number) {
    CHECK_API;
    return mApi->accountSendChangePhoneCode(true, phone_number, true);
}

qint64 Telegram::accountChangePhone(const QString &phone_number, const QString &phone_code_hash, const QString &phone_code) {
    CHECK_API;
    return mApi->accountChangePhone(phone_number, phone_code_hash, phone_code);
}

qint64 Telegram::accountGetPassword() {
    CHECK_API;
    return mApi->accountGetPassword();
}

qint64 Telegram::accountGetAuthorizations() {
    CHECK_API;
    return mApi->accountGetAuthorizations();
}

qint64 Telegram::accountResetAuthorization(qint64 hash) {
    CHECK_API;
    return mApi->accountResetAuthorization(hash);
}

qint64 Telegram::accountGetPasswordSettings(const QByteArray &currentPasswordHash) {
    CHECK_API;
    return mApi->accountGetPasswordSettings(currentPasswordHash);
}

qint64 Telegram::accountUpdatePasswordSettings(const QByteArray &currentPasswordHash, const AccountPasswordInputSettings &newSettings) {
    CHECK_API;
    return mApi->accountUpdatePasswordSettings(currentPasswordHash, newSettings);
}

qint64 Telegram::photosUploadProfilePhoto(const QByteArray &bytes, const QString &fileName, const QString &caption, const InputGeoPoint &geoPoint, const InputPhotoCrop &crop) {
    FileOperation *op = new FileOperation(FileOperation::uploadProfilePhoto);
    op->setCaption(caption);
    op->setGeoPoint(geoPoint);
    op->setCrop(crop);
    return prv->mFileHandler->uploadSendFile(*op, fileName, bytes);
}

qint64 Telegram::photosUploadProfilePhoto(const QString &filePath, const QString &caption, const InputGeoPoint &geoPoint, const InputPhotoCrop &crop) {
    FileOperation *op = new FileOperation(FileOperation::uploadProfilePhoto);
    op->setCaption(caption);
    op->setGeoPoint(geoPoint);
    op->setCrop(crop);
    return prv->mFileHandler->uploadSendFile(*op, filePath);
}

qint64 Telegram::photosUpdateProfilePhoto(qint64 photoId, qint64 accessHash, const InputPhotoCrop &crop) {
    CHECK_API;
    InputPhoto inputPhoto(InputPhoto::typeInputPhoto);
    inputPhoto.setId(photoId);
    inputPhoto.setAccessHash(accessHash);
    return mApi->photosUpdateProfilePhoto(inputPhoto, crop);
}

qint64 Telegram::usersGetUsers(const QList<InputUser> &users) {
    CHECK_API;
    return mApi->usersGetUsers(users);
}

qint64 Telegram::usersGetFullUser(const InputUser &user) {
    CHECK_API;
    return mApi->usersGetFullUser(user);
}

qint64 Telegram::photosGetUserPhotos(const InputUser &user, qint32 offset, qint32 maxId, qint32 limit) {
    CHECK_API;
    return mApi->photosGetUserPhotos(user, offset, maxId, limit);
}

qint64 Telegram::contactsGetStatuses() {
    CHECK_API;
    return mApi->contactsGetStatuses();
}

bool lessThan(const Contact &c1, const Contact &c2) {
    return c1.userId() < c2.userId();
}

qint64 Telegram::contactsImportContacts(const QList<InputContact> &contacts, bool replace) {
    CHECK_API;
    prv->mLastContacts = contacts;
    prv->mLastRetryType = ImportContacts;
    return mApi->contactsImportContacts(contacts, replace);
}

qint64 Telegram::contactsDeleteContact(const InputUser &user) {
    CHECK_API;
    return mApi->contactsDeleteContact(user);
}

qint64 Telegram::contactsDeleteContacts(const QList<InputUser> &users) {
    CHECK_API;
    return mApi->contactsDeleteContacts(users);
}

qint64 Telegram::contactsSearch(const QString &q, qint32 limit) {
    CHECK_API;
    return mApi->contactsSearch(q, limit);
}

//qint64 Telegram::contactsResolveUsername(const QString &username) {
//    CHECK_API;
//    return mApi->contactsResolveUsername(username);
//}

qint64 Telegram::contactsBlock(const InputUser &user) {
    CHECK_API;
    return mApi->contactsBlock(user);
}

qint64 Telegram::contactsUnblock(const InputUser &user) {
    CHECK_API;
    return mApi->contactsUnblock(user);
}

qint64 Telegram::contactsGetBlocked(qint32 offset, qint32 limit) {
    CHECK_API;
    return mApi->contactsGetBlocked(offset, limit);
}

qint64 Telegram::contactsGetContacts() {
    //If there already is a full contact list on the client, an md5-hash of a comma-separated list of contact IDs
    //in ascending order may be passed in this 'hash' parameter. If the contact set was not changed,
    //contactsContactsNotModified() will be returned from Api, so the cached client list is returned with the
    //signal that they are the same contacts as previous request
    QString hash;
    if (!prv->m_cachedContacts.isEmpty()) {
        qSort(prv->m_cachedContacts.begin(), prv->m_cachedContacts.end(), lessThan); //lessThan method must be outside any class or be static
        QString hashBase;
        if (prv->m_cachedContacts.size() > 0) {
            hashBase.append(QString::number(prv->m_cachedContacts.at(0).userId()));
        }
        for (qint32 i = 1; i < prv->m_cachedContacts.size(); i++) {
            hashBase.append(",");
            hashBase.append(QString::number(prv->m_cachedContacts.at(i).userId()));
        }
        QCryptographicHash md5Generator(QCryptographicHash::Md5);
        md5Generator.addData(hashBase.toStdString().c_str());
        hash = md5Generator.result().toHex();
    }
    return TelegramCore::contactsGetContacts(hash);
}

// Working with channels

qint64 Telegram::channelsReadHistory(const InputChannel &channel, qint32 max_id)
{
    CHECK_API;
    return mApi->channelsReadHistory(channel, max_id);
}

qint64 Telegram::channelsDeleteMessages(const InputChannel &channel, const QList<qint32> &id)
{
    CHECK_API;
    return mApi->channelsDeleteMessages(channel, id);
}

qint64 Telegram::channelsDeleteUserHistory(const InputChannel &channel, const InputUser &user_id)
{
    CHECK_API;
    return mApi->channelsDeleteUserHistory(channel, user_id);
}

qint64 Telegram::channelsReportSpam(const InputChannel &channel, const InputUser &user_id, const QList<qint32> &id)
{
    CHECK_API;
    return mApi->channelsReportSpam(channel, user_id, id);
}

qint64 Telegram::channelsGetMessages(const InputChannel &channel, const QList<qint32> &id)
{
    CHECK_API;
    return mApi->channelsGetMessages(channel, id);
}

qint64 Telegram::channelsGetChannels(const QList<InputChannel> &id)
{
    CHECK_API;
    return mApi->channelsGetChannels(id);
}

qint64 Telegram::channelsCreateChannel(bool broadcast, bool megagroup, const QString &title, const QString &about)
{
    CHECK_API;
    return mApi->channelsCreateChannel(broadcast, megagroup, title, about);
}

qint64 Telegram::channelsEditAbout(const InputChannel &channel, const QString &about)
{
    CHECK_API;
    return mApi->channelsEditAbout(channel, about);
}

qint64 Telegram::channelsEditAdmin(const InputChannel &channel, const InputUser &user_id, const ChannelParticipantRole &role)
{
    CHECK_API;
    return mApi->channelsEditAdmin(channel, user_id, role);
}

qint64 Telegram::channelsEditTitle(const InputChannel &channel, const QString &title)
{
    CHECK_API;
    return mApi->channelsEditTitle(channel, title);
}

qint64 Telegram::channelsEditPhoto(const InputChannel &channel, const InputChatPhoto &photo)
{
    CHECK_API;
    return mApi->channelsEditPhoto(channel, photo);
}

qint64 Telegram::channelsCheckUsername(const InputChannel &channel, const QString &username)
{
    CHECK_API;
    return mApi->channelsCheckUsername(channel, username);
}

qint64 Telegram::channelsUpdateUsername(const InputChannel &channel, const QString &username)
{
    CHECK_API;
    return mApi->channelsUpdateUsername(channel, username);
}

qint64 Telegram::channelsJoinChannel(const InputChannel &channel)
{
    CHECK_API;
    return mApi->channelsJoinChannel(channel);
}

qint64 Telegram::channelsLeaveChannel(const InputChannel &channel)
{
    CHECK_API;
    return mApi->channelsLeaveChannel(channel);
}

qint64 Telegram::channelsInviteToChannel(const InputChannel &channel, const QList<InputUser> &users)
{
    CHECK_API;
    return mApi->channelsInviteToChannel(channel, users);
}

qint64 Telegram::channelsKickFromChannel(const InputChannel &channel, const InputUser &user_id, bool kicked)
{
    CHECK_API;
    return mApi->channelsKickFromChannel(channel, user_id, kicked);
}

qint64 Telegram::channelsExportInvite(const InputChannel &channel)
{
    CHECK_API;
    return mApi->channelsExportInvite(channel);
}

qint64 Telegram::channelsDeleteChannel(const InputChannel &channel)
{
    CHECK_API;
    return mApi->channelsDeleteChannel(channel);
}

qint64 Telegram::messagesSendPhoto(const InputPeer &peer, qint64 randomId, const QByteArray &bytes, const QString &fileName, qint32 replyToMsgId) {
    InputMedia inputMedia(InputMedia::typeInputMediaUploadedPhoto);
    FileOperation *op = new FileOperation(FileOperation::sendMedia);
    op->setInputPeer(peer);
    op->setInputMedia(inputMedia);
    op->setRandomId(randomId);
    op->setReplyToMsgId(replyToMsgId);
    return uploadSendFile(*op, inputMedia.classType(), fileName, bytes);
}

qint64 Telegram::messagesSendPhoto(const InputPeer &peer, qint64 randomId, const QString &filePath, qint32 replyToMsgId) {
    InputMedia inputMedia(InputMedia::typeInputMediaUploadedPhoto);
    FileOperation *op = new FileOperation(FileOperation::sendMedia);
    op->setInputPeer(peer);
    op->setInputMedia(inputMedia);
    op->setRandomId(randomId);
    op->setReplyToMsgId(replyToMsgId);
    return uploadSendFile(*op, inputMedia.classType(), filePath);
}

qint64 Telegram::messagesSendGeoPoint(const InputPeer &peer, qint64 randomId, const InputGeoPoint &inputGeoPoint, qint32 replyToMsgId) {
    CHECK_API;
    InputMedia inputMedia(InputMedia::typeInputMediaGeoPoint);
    inputMedia.setGeoPoint(inputGeoPoint);
    qint64 msgId = mApi->messagesSendMedia(false, false, true, peer, replyToMsgId, inputMedia, randomId, ReplyMarkup());
    prv->pendingMediaSends[msgId] = inputMedia.classType();
    return msgId;
}

qint64 Telegram::messagesSendContact(const InputPeer &peer, qint64 randomId, const QString &phoneNumber, const QString &firstName, const QString &lastName, qint32 replyToMsgId) {
    CHECK_API;
    InputMedia inputMedia(InputMedia::typeInputMediaContact);
    inputMedia.setPhoneNumber(phoneNumber);
    inputMedia.setFirstName(firstName);
    inputMedia.setLastName(lastName);
    qint64 msgId = mApi->messagesSendMedia(false, false, true, peer, replyToMsgId, inputMedia, randomId, ReplyMarkup());
    prv->pendingMediaSends[msgId] = inputMedia.classType();
    return msgId;
}

qint64 Telegram::messagesSendVideo(const InputPeer &peer, qint64 randomId, const QByteArray &bytes, const QString &fileName, qint32 duration, qint32 width, qint32 height, const QString &mimeType, const QByteArray &thumbnailBytes, const QString &thumbnailName, qint32 replyToMsgId) {
    InputMedia inputMedia(InputMedia::typeInputMediaUploadedDocument);
    inputMedia.setMimeType(mimeType);
    FileOperation *op = new FileOperation(FileOperation::sendMedia);
    op->setInputPeer(peer);
    op->setInputMedia(inputMedia);
    op->setRandomId(randomId);
    op->setReplyToMsgId(replyToMsgId);
    return uploadSendFile(*op, inputMedia.classType(), fileName, bytes, thumbnailBytes, thumbnailName);
}

qint64 Telegram::messagesSendVideo(const InputPeer &peer, qint64 randomId, const QString &filePath, qint32 duration, qint32 width, qint32 height, const QString &thumbnailFilePath, qint32 replyToMsgId) {
    InputMedia inputMedia(InputMedia::typeInputMediaUploadedDocument);
    inputMedia.setMimeType(QMimeDatabase().mimeTypeForFile(QFileInfo(filePath)).name());
    FileOperation *op = new FileOperation(FileOperation::sendMedia);
    op->setInputPeer(peer);
    op->setInputMedia(inputMedia);
    op->setRandomId(randomId);
    op->setReplyToMsgId(replyToMsgId);
    return uploadSendFile(*op, inputMedia.classType(), filePath, thumbnailFilePath);
}

qint64 Telegram::messagesSendAudio(const InputPeer &peer, qint64 randomId, const QByteArray &bytes, const QString &fileName, qint32 duration, const QString &mimeType, qint32 replyToMsgId) {
    InputMedia inputMedia(InputMedia::typeInputMediaUploadedDocument);
    FileOperation *op = new FileOperation(FileOperation::sendMedia);
    op->setInputPeer(peer);
    op->setInputMedia(inputMedia);
    op->setRandomId(randomId);
    op->setReplyToMsgId(replyToMsgId);
    return uploadSendFile(*op, inputMedia.classType(), fileName, bytes);
}

qint64 Telegram::messagesSendAudio(const InputPeer &peer, qint64 randomId, const QString &filePath, qint32 duration, qint32 replyToMsgId) {
    InputMedia inputMedia(InputMedia::typeInputMediaUploadedDocument);
    inputMedia.setMimeType(QMimeDatabase().mimeTypeForFile(QFileInfo(filePath)).name());
    FileOperation *op = new FileOperation(FileOperation::sendMedia);
    op->setInputPeer(peer);
    op->setInputMedia(inputMedia);
    op->setRandomId(randomId);
    op->setReplyToMsgId(replyToMsgId);
    return uploadSendFile(*op, inputMedia.classType(), filePath);
}

qint64 Telegram::messagesSendDocument(const InputPeer &peer, qint64 randomId, const QByteArray &bytes, const QString &fileName, const QString &mimeType, const QByteArray &thumbnailBytes, const QString &thumbnailName, const QString &caption, const QList<DocumentAttribute> &extraAttributes, qint32 replyToMsgId) {
    DocumentAttribute fileAttr(DocumentAttribute::typeDocumentAttributeFilename);
    fileAttr.setFileName(fileName);

    QList<DocumentAttribute> attributes;
    attributes << fileAttr;
    attributes << extraAttributes;

    InputMedia inputMedia(InputMedia::typeInputMediaUploadedDocument);
    inputMedia.setAttributes(attributes);
    inputMedia.setMimeType(mimeType);
    inputMedia.setCaption(caption);
    if (!thumbnailBytes.isEmpty()) {
        inputMedia.setClassType(InputMedia::typeInputMediaUploadedThumbDocument);
    }
    FileOperation *op = new FileOperation(FileOperation::sendMedia);
    op->setInputPeer(peer);
    op->setInputMedia(inputMedia);
    op->setRandomId(randomId);
    op->setReplyToMsgId(replyToMsgId);
    return uploadSendFile(*op, inputMedia.classType(), fileName, bytes, thumbnailBytes, thumbnailName);
}

qint64 Telegram::messagesSendDocument(const InputPeer &peer, qint64 randomId, const QString &filePath, const QString &thumbnailFilePath, const QString &caption, bool sendAsSticker, qint32 replyToMsgId) {
    const QMimeType t = QMimeDatabase().mimeTypeForFile(QFileInfo(filePath));
    QString mimeType = t.name();

    DocumentAttribute fileAttr(DocumentAttribute::typeDocumentAttributeFilename);
    fileAttr.setFileName(QFileInfo(filePath).fileName());

    QList<DocumentAttribute> attributes;
    attributes << fileAttr;
    if(sendAsSticker) {
        QImageReader reader(filePath);
        DocumentAttribute imageSizeAttr(DocumentAttribute::typeDocumentAttributeImageSize);
        imageSizeAttr.setH(reader.size().height());
        imageSizeAttr.setW(reader.size().width());

        attributes << DocumentAttribute(DocumentAttribute::typeDocumentAttributeSticker) << imageSizeAttr;

        if(mimeType.contains("webp"))
            mimeType = "image/webp";
    }

    InputMedia inputMedia(InputMedia::typeInputMediaUploadedDocument);
    inputMedia.setMimeType(mimeType);
    inputMedia.setAttributes(attributes);
    inputMedia.setCaption(caption);
    if (thumbnailFilePath.length() > 0) {
        inputMedia.setClassType(InputMedia::typeInputMediaUploadedThumbDocument);
    }
    FileOperation *op = new FileOperation(FileOperation::sendMedia);
    op->setInputPeer(peer);
    op->setInputMedia(inputMedia);
    op->setRandomId(randomId);
    op->setReplyToMsgId(replyToMsgId);
    return uploadSendFile(*op, inputMedia.classType(), filePath, thumbnailFilePath);
}

qint64 Telegram::messagesForwardPhoto(const InputPeer &peer, qint64 randomId, qint64 photoId, qint64 accessHash, qint32 replyToMsgId) {
    CHECK_API;
    InputPhoto inputPhoto(InputPhoto::typeInputPhoto);
    inputPhoto.setId(photoId);
    inputPhoto.setAccessHash(accessHash);
    InputMedia inputMedia(InputMedia::typeInputMediaPhoto);
    inputMedia.setIdInputPhoto(inputPhoto);
    return messagesSendMedia(false, false, true, peer, replyToMsgId, inputMedia, randomId, ReplyMarkup());
}

qint64 Telegram::messagesForwardVideo(const InputPeer &peer, qint64 randomId, qint64 videoId, qint64 accessHash, qint32 replyToMsgId) {
    CHECK_API;
    InputDocument inputVideo(InputDocument::typeInputDocument);
    inputVideo.setId(videoId);
    inputVideo.setAccessHash(accessHash);
    InputMedia inputMedia(InputMedia::typeInputMediaDocument);
    inputMedia.setIdInputDocument(inputVideo);
    return messagesSendMedia(false, false, true, peer, replyToMsgId, inputMedia, randomId, ReplyMarkup());
}

qint64 Telegram::messagesForwardAudio(const InputPeer &peer, qint64 randomId, qint64 audioId, qint64 accessHash, qint32 replyToMsgId) {
    CHECK_API;
    InputDocument inputAudio(InputDocument::typeInputDocument);
    inputAudio.setId(audioId);
    inputAudio.setAccessHash(accessHash);
    InputMedia inputMedia(InputMedia::typeInputMediaDocument);
    inputMedia.setIdInputDocument(inputAudio);
    return messagesSendMedia(false, false, true, peer, replyToMsgId, inputMedia, randomId, ReplyMarkup());
}

qint64 Telegram::messagesForwardDocument(const InputPeer &peer, qint64 randomId, qint64 documentId, qint64 accessHash, qint32 replyToMsgId) {
    CHECK_API;
    InputDocument inputDocument(InputDocument::typeInputDocument);
    inputDocument.setId(documentId);
    inputDocument.setAccessHash(accessHash);
    InputMedia inputMedia(InputMedia::typeInputMediaDocument);
    inputMedia.setIdInputDocument(inputDocument);
    return messagesSendMedia(false, false, true, peer, replyToMsgId, inputMedia, randomId, ReplyMarkup());
}

qint64 Telegram::uploadSendFile(FileOperation &op, int mediaType, const QString &fileName, const QByteArray &bytes, const QByteArray &thumbnailBytes, const QString &thumbnailName)
{
    const qint64 fileId = prv->mFileHandler->uploadSendFile(op, fileName, bytes, thumbnailBytes, thumbnailName);
    prv->pendingMediaSends[fileId] = mediaType;
    return fileId;
}

qint64 Telegram::uploadSendFile(FileOperation &op, int mediaType, const QString &filePath, const QString &thumbnailPath)
{
    const qint64 fileId = prv->mFileHandler->uploadSendFile(op, filePath, thumbnailPath);
    prv->pendingMediaSends[fileId] = mediaType;
    return fileId;
}

qint64 Telegram::messagesSetEncryptedTyping(qint32 chatId, bool typing) {
    CHECK_API;
    SecretChat *secretChat = prv->mSecretState.chats().value(chatId);
    if (!secretChat) {
        qCWarning(TG_LIB_SECRET) << "Could not read history of a not yet existant chat";
        return -1;
    }
    InputEncryptedChat mChat;
    mChat.setChatId(chatId);
    mChat.setAccessHash(secretChat->accessHash());
    return mApi->messagesSetEncryptedTyping(mChat,typing);
}

qint64 Telegram::messagesSetTyping(const InputPeer &peer, const SendMessageAction &action) {
    CHECK_API;
    return mApi->messagesSetTyping(peer, action);
}

qint64 Telegram::messagesGetMessages(const QList<qint32> &msgIds) {
    CHECK_API;
    return mApi->messagesGetMessages(msgIds);
}

qint64 Telegram::messagesReadHistory(const InputPeer &peer, qint32 maxId, qint32 offset) {
    CHECK_API;
    return mApi->messagesReadHistory(peer, maxId, offset);
}

qint64 Telegram::messagesReadMessageContents(const QList<qint32> &ids) {
    CHECK_API;
    return mApi->messagesReadMessageContents(ids);
}

qint64 Telegram::messagesDeleteHistory(const InputPeer &peer, qint32 offset) {
    CHECK_API;
    return mApi->messagesDeleteHistory(false, peer, offset);
}

qint64 Telegram::messagesDeleteMessages(const QList<qint32> &msgIds) {
    CHECK_API;
    return mApi->messagesDeleteMessages(msgIds);
}

qint64 Telegram::messagesReceivedMessages(qint32 maxId) {
    CHECK_API;
    return mApi->messagesReceivedMessages(maxId);
}

qint64 Telegram::messagesSendBroadcast(const QList<InputUser> &users, const QList<qint64> &randomIds, const QString &message, const InputMedia &media) {
    CHECK_API;
    return mApi->messagesSendBroadcast(users, randomIds, message, media);
}

qint64 Telegram::messagesGetChats(const QList<qint32> &chatIds) {
    CHECK_API;
    return mApi->messagesGetChats(chatIds);
}

qint64 Telegram::messagesGetFullChat(qint32 chatId) {
    CHECK_API;
    return mApi->messagesGetFullChat(chatId);
}

qint64 Telegram::messagesEditChatTitle(qint32 chatId, const QString &title) {
    CHECK_API;
    return mApi->messagesEditChatTitle(chatId, title);
}

qint64 Telegram::messagesEditChatPhoto(qint32 chatId, const QString &filePath, const InputPhotoCrop &crop) {
    InputChatPhoto inputChatPhoto(InputChatPhoto::typeInputChatUploadedPhoto);
    inputChatPhoto.setCrop(crop);
    FileOperation *op = new FileOperation(FileOperation::editChatPhoto);
    op->setChatId(chatId);
    op->setInputChatPhoto(inputChatPhoto);
    return prv->mFileHandler->uploadSendFile(*op, filePath);
}

qint64 Telegram::messagesEditChatPhoto(qint32 chatId, qint64 photoId, qint64 accessHash, const InputPhotoCrop &crop) {
    CHECK_API;
    InputChatPhoto inputChatPhoto(InputChatPhoto::typeInputChatPhoto);
    InputPhoto inputPhoto(InputPhoto::typeInputPhoto);
    inputPhoto.setId(photoId);
    inputPhoto.setAccessHash(accessHash);
    inputChatPhoto.setId(inputPhoto);
    inputChatPhoto.setCrop(crop);
    return mApi->messagesEditChatPhoto(chatId, inputChatPhoto);
}

qint64 Telegram::messagesAddChatUser(qint32 chatId, const InputUser &user, qint32 fwdLimit) {
    CHECK_API;
    return mApi->messagesAddChatUser(chatId, user, fwdLimit);
}

qint64 Telegram::messagesDeleteChatUser(qint32 chatId, const InputUser &user) {
    CHECK_API;
    return mApi->messagesDeleteChatUser(chatId, user);
}

qint64 Telegram::messagesCreateChat(const QList<InputUser> &users, const QString &chatTopic) {
    CHECK_API;
    return mApi->messagesCreateChat(users, chatTopic);
}

qint64 Telegram::updatesGetState() {
    CHECK_API;
    return mApi->updatesGetState();
}

qint64 Telegram::updatesGetDifference(qint32 pts, qint32 date, qint32 qts) {
    CHECK_API;
    return mApi->updatesGetDifference(pts, date, qts);
}

qint64 Telegram::uploadGetFile(const InputFileLocation &location, qint32 fileSize, qint32 dcNum, const QByteArray &key, const QByteArray &iv) {
    if(!prv->mFileHandler) return 0;
    return prv->mFileHandler->uploadGetFile(location, fileSize, dcNum, key, iv);
}

qint64 Telegram::uploadCancelFile(qint64 fileId) {
    if(!prv->mFileHandler) return 0;
    return prv->mFileHandler->uploadCancelFile(fileId);
}
