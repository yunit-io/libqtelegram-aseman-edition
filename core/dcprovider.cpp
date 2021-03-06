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
 */

#include "dcprovider.h"
#include "util/constants.h"
#include "session.h"

#include <QDebug>

Q_LOGGING_CATEGORY(TG_CORE_DCPROVIDER, "tg.core.dcprovider")

DcProvider::DcProvider(Settings *settings, CryptoUtils *crypto) :
    mSettings(settings),
    mCrypto(crypto),
    mApi(0),
    mPendingDcs(0),
    mPendingTransferSessions(0),
    mWorkingDcSession(0),
    nearestDc(0),
    mConfigReceived(0)
     { }

DcProvider::~DcProvider() {
   clean();
}

void DcProvider::clean() {
    Q_FOREACH (DC *dc, mDcs) {
        delete dc;
        dc = 0;
    }
    Q_FOREACH (DCAuth *dcAuth, mDcAuths) {
        if (dcAuth) {
            if (dcAuth->state() != QAbstractSocket::UnconnectedState) {
                connect(dcAuth, &DCAuth::disconnected, dcAuth, &DCAuth::deleteLater);
                dcAuth->disconnectFromHost();
            } else {
                dcAuth->deleteLater();
            }
            dcAuth = 0;
        }
    }
    Q_FOREACH (Session *session, mTransferSessions)  {
        if (session) {
            session->close();
        }
    }
    if (mApi) {
        mApi->deleteLater();
        mApi = 0;
    }
    mDcs.clear();
    mDcAuths.clear();
    mTransferSessions.clear();

    mPendingDcs = 0;
    mPendingTransferSessions = 0;
    mWorkingDcSession = 0;
}

DC *DcProvider::getDc(qint32 dcNum) const {
    return mDcs.value(dcNum, NULL);
}

DC *DcProvider::getWorkingDc() const {
    return mDcs.value(mSettings->workingDcNum(), 0);
}


void DcProvider::initialize() {

    clean();

    /**
      1.- Read settings (dcsList and working dc num)
      2.- Fullfill m_dcs map with dcsList
      3.- Connect to working dc
      4.- Ask for config when working dc is connected
      5.- Connect to the rest of the dcs received in config
      */

    // 1.- Get the settings dcs, fullfill m_dcs map and current dc num
    QList<DC *> dcsList = mSettings->dcsList();

    Q_FOREACH (DC *dc, dcsList) {
        mDcs.insert(dc->id(), dc);
    }

    qint32 defaultDcId = mSettings->testMode() ? TEST_DEFAULT_DC_ID : mSettings->defaultHostDcId();

    // 2.- connect to working DC
    if (!mSettings->workingDcConfigAvailabe()) {
        // If dcId == defaultDcId, it's the default one, so call default host and port
        if (!mDcs.value(defaultDcId, 0)) {
            mDcs[defaultDcId] = new DC(defaultDcId);
        }
        // if dc hasn't key created, create it
        if (mDcs[defaultDcId]->state() < DC::authKeyCreated) {
            QString defaultDcHost = mSettings->defaultHostAddress();
            qint32 defaultDcPort = mSettings->defaultHostPort();
            if (mSettings->testMode()) {
                defaultDcHost = TEST_DEFAULT_DC_HOST;
                defaultDcPort = TEST_DEFAULT_DC_PORT;
            }

            // create a dc authenticator based in dc info
            mDcs[defaultDcId]->addEndpoint(defaultDcHost, defaultDcPort);
            DCAuth *dcAuth = new DCAuth(mDcs[defaultDcId], mSettings, mCrypto, this);
            mDcAuths.insert(defaultDcId, dcAuth);
            connect(dcAuth, &DCAuth::fatalError, this, &DcProvider::logOut);
            connect(dcAuth, &DCAuth::fatalError, this, &DcProvider::fatalError);
            connect(dcAuth, &DCAuth::dcReady, this, &DcProvider::onDcReady);
            dcAuth->createAuthKey();
        } else {
            onDcReady(mDcs[defaultDcId]);
        }

    } else {
        // In any other case, the host and port have been retrieved from auth file settings and the DC object is already created
        if (mDcs[mSettings->workingDcNum()]->state() < DC::authKeyCreated) {
            // create a dc authenticator based in dc info
            DCAuth *dcAuth = new DCAuth(mDcs[mSettings->workingDcNum()], mSettings, mCrypto);
            mDcAuths.insert(mSettings->workingDcNum(), dcAuth);
            connect(dcAuth, &DCAuth::fatalError, this, &DcProvider::logOut);
            connect(dcAuth, &DCAuth::fatalError, this, &DcProvider::fatalError);
            connect(dcAuth, &DCAuth::dcReady, this, &DcProvider::onDcReady);
            dcAuth->createAuthKey();
        } else {
            onDcReady(mDcs[mSettings->workingDcNum()]);
        }
    }
}

void DcProvider::onDcReady(DC *dc) {
    qCDebug(TG_CORE_DCPROVIDER) << "DC" << dc->id() << "ready";
    // disconnect dcAuth to avoid consuming bandwidth with unnecessary connections
    DCAuth *dcAuth = mDcAuths.value(dc->id());
    if (dcAuth) {
        if (dcAuth->state() != QAbstractSocket::UnconnectedState) {
            connect(dcAuth, &DCAuth::disconnected, this, &DcProvider::onDcAuthDisconnected);
            dcAuth->disconnectFromHost();
        } else {
            processDcReady(dc);
        }
    } else {
        processDcReady(dc);
    }
}

void DcProvider::onDcAuthDisconnected() {
    DCAuth *dcAuth = qobject_cast<DCAuth *>(sender());
    processDcReady(dcAuth->dc());
    mDcAuths.remove(dcAuth->dc()->id());
    dcAuth->deleteLater();
}

void DcProvider::finalDcEstablished() {

    qCDebug(TG_CORE_DCPROVIDER) << "DcProvider ready";
    Q_EMIT dcProviderReady();

}

void DcProvider::setupApi(DC *dc) {

    Session *session = new Session(dc, mSettings, mCrypto, this);
    mApi = new TelegramApi(session, mSettings, mCrypto, this);
    setApi(mApi);
    connect(mApi, &SessionManager::mainSessionReady, this, &DcProvider::onApiReady);
    m_error = connect(session, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onApiError()));
    session->connectToServer();
}

void DcProvider::processDcReady(DC *dc) {
    mDcsLock.lock();
    // create api object if dc is workingDc, and get configuration
    if ((!mApi) && (dc->id() == mSettings->workingDcNum())) {
        setupApi(dc);
    } else if (--mPendingDcs == 0) { // if all dcs are authorized, emit provider ready signal
        // save the settings here, after all dcs are ready
        mSettings->setDcsList(mDcs.values());
        mSettings->writeAuthFile();

        // if current dc is in "authKeyCreated" state, authNeeded signal must be emitted for user to sign in.
        // if current dc is in "userSignedIn" state, check that all dcs are in that state or export/import auth.
        // If they aren't, transfer auth from workingDc to workingDc+1, from workingDc+1 to workingDc+2...etc until completed all.
        switch (mDcs.value(mSettings->workingDcNum())->state()) {
        case DC::authKeyCreated:
            Q_EMIT authNeeded();
            break;
        case DC::userSignedIn:
            transferAuth();
            break;
        default:
//            Q_ASSERT(0); // it's impossible getting here. This is done to avoid warning when compilation
            break;
        }

    }
    mDcsLock.unlock();
}

void DcProvider::onApiError() {

    Session *session = qobject_cast<Session *>(sender());
    qCWarning(TG_CORE_DCPROVIDER) << "Api init error when connecting session to server:" << session->errorString();

    // after emitting these startup offline signals, we don't want to do it again when session gets connected, so disconnect signal-slot
    disconnect(m_error);
    // also disconnect the signal-slot to query for current server config when connected (once logged in that info is irrelevant)
    disconnect(session, &Session::sessionReady, this, &DcProvider::onApiReady);

    bool userSignedInAllDCs = true;
    // because we haven't connection, we assume the available DCs have not changed since last startup.
    // Check if there is a shared key created for all DCs readed from config and if the user has
    // been authenticated in all them
    Q_FOREACH (DC *dc, mDcs) {
        if (dc->state() < DC::authKeyCreated) {
            // emit a fatal error that should be shown in app as the reason to abort starting up the app
            Q_EMIT error(-1,
                         500,
                         "Impossible to start application. There is no connection to server and stored credentials are not valid");
            return;
        } else if (dc->state() < DC::userSignedIn) {
            userSignedInAllDCs = false;
        }
    }

    Q_EMIT dcProviderReady();

    if (userSignedInAllDCs) {
        Q_EMIT authTransferCompleted();
    } else {
        Q_EMIT authNeeded();
    }
}

void DcProvider::onApiReady() {

    qCDebug(TG_CORE_DCPROVIDER) << "Api connected to server and ready";

    // after emitting the api startup signals, we don't want to do it again when session gets connected, so disconnect signal-slot
    disconnect(m_error);

    // get nearest DC
    connect(mApi, &TelegramApi::helpGetNearestDcAnswer, this, &DcProvider::onNearestDcReceived, Qt::UniqueConnection );
    mApi->helpGetNearestDc();
}

void DcProvider::onNearestDcReceived(qint64 msgId, const NearestDc &result) {

    qWarning() << "Nearest DC is" << result.nearestDc() << "country" << result.country() << "this DC" << result.thisDc();
    nearestDc = result.nearestDc();
    DC *dc = mDcs.value(nearestDc);
    if (result.thisDc() != nearestDc && dc)
    {
        if(mApi)
        {
            mSettings->setWorkingDcNum(nearestDc);
            mSettings->writeAuthFile();
            mApi->changeMainSessionToDc(dc);
        }
        return;
    }
    qWarning() << "Connected to the right DC, we can continue";

    // get the config
    if(mApi)
        disconnect(mApi, &SessionManager::mainSessionReady, this, &DcProvider::onApiReady);
    connect(mApi, &TelegramApi::helpGetConfigAnswer, this, &DcProvider::onConfigReceived, Qt::UniqueConnection );
    mApi->helpGetConfig();
    finalDcEstablished();
}

void DcProvider::onConfigReceived(qint64 msgId, const Config &config) {

    qCDebug(TG_CORE_DCPROVIDER) << "onConfigReceived(), msgId =" << QString::number(msgId, 16);
    qCDebug(TG_CORE_DCPROVIDER) << "date =" << config.date();
    qCDebug(TG_CORE_DCPROVIDER) << "testMode =" << config.testMode();
    qCDebug(TG_CORE_DCPROVIDER) << "thisDc =" << config.thisDc();

    if(mConfigReceived)
        return;

    mConfigReceived = true;

    const QList<DcOption> &dcOptions = config.dcOptions();
    QList<qint32> dcIndex = QList<qint32>();

    //We start at -1 to reduce the amount of pending DCs by one. The first DC where we got the config from is already processed
    mPendingDcs = -1;
    Q_FOREACH (DcOption dcOption, dcOptions) {
        if (dcIndex.indexOf(dcOption.id())==-1)
        {
            dcIndex.append(dcOption.id());
            mPendingDcs++;
        }
    }

    QList<DCAuth *> pendingDCs = QList<DCAuth *>();

    Q_FOREACH (DC *dc, mDcs)
        dc->deleteEndpoints();

    Q_FOREACH (DcOption dcOption, dcOptions) {
        qCDebug(TG_CORE_DCPROVIDER) << "dcOption | id =" << dcOption.id() << ", ipAddress =" << dcOption.ipAddress() <<
                    ", port =" << dcOption.port() << ", hostname =" << dcOption.ipAddress() << ", mediaOnly: " << dcOption.mediaOnly() << ", IPv6:" << dcOption.ipv6();
        // for every new DC or not authenticated DC, insert into m_dcs and authenticate
        DC *dc = mDcs.value(dcOption.id());

        // check if dc is not null or if received host and port are not equals than settings ones
        if (!dc) {
            // if the DC entry does not exist or no auth key is created create a new dc object for this dcId and add it to m_dcs map
            dc = new DC(dcOption.id());
            mDcs.insert(dcOption.id(), dc);
        }

        //Sad but true, this code cannot handle media-only DCs, and also not use IPv6, which is currently broken in UT anyways
        if(!(dcOption.mediaOnly() || dcOption.ipv6()))
            dc->addEndpoint(dcOption.ipAddress(), dcOption.port());
        else
        {
            //Make sure we remove old entries from the DC option list with mediaonly = true
            dc->deleteEndpoint(dcOption.ipAddress(), dcOption.port());
        }
    }
    //Need second loop to guarantee all possible IP addresses have been assigned to the DC structures
    Q_FOREACH (DcOption dcOption, dcOptions) {
        DC *dc = mDcs.value(dcOption.id());
        qint32 currentDc = dcIndex.indexOf(dcOption.id());
        if (currentDc>-1)
        {
            dcIndex.removeAt(currentDc);
            // let's see if needed to create shared key for it
            // In any other case, the host and port have been retrieved from auth file settings and the DC object is already created
            if (dc->state() < DC::authKeyCreated) {
                // create a dc authenticator based in dc info
                DCAuth *dcAuth = new DCAuth(dc, mSettings, mCrypto, this);
                mDcAuths.insert(dcOption.id(), dcAuth);
                connect(dcAuth, &DCAuth::fatalError, this, &DcProvider::logOut);
                connect(dcAuth, &DCAuth::fatalError, this, &DcProvider::fatalError);
                connect(dcAuth, &DCAuth::dcReady, this, &DcProvider::onDcReady);
                pendingDCs.append(dcAuth);
            } else if (dcOption.id() != config.thisDc()) {
                // if authorized and not working dc emit dcReady signal directly
                onDcReady(dc);
            }
        }
    }
    Q_FOREACH(DCAuth *dcAuth, pendingDCs) {
        dcAuth->createAuthKey();
    }

    qCDebug(TG_CORE_DCPROVIDER) << "chatMaxSize =" << config.chatSizeMax();
}

TelegramApi *DcProvider::getApi() const {
    return mApi;
}

QList<DC *> DcProvider::getDcs() const {
    return mDcs.values();
}

void DcProvider::transferAuth() {
    // add in a list all the dcs in DcState::authKeyCreated but not in DCState::userSignedIn
    // and receiving the authorization data (all but working dc one)
    Q_ASSERT(mApi);
    bool hasTransferSessions = false;
    mWorkingDcSession = mApi->mainSession();
    Q_ASSERT(mWorkingDcSession);
    QList<DC *> m_dcsList = mDcs.values();
    QList<DC *> pendingDCs;
    Q_FOREACH(DC *dc, m_dcsList) {
        if (dc->state() == DC::authKeyCreated &&
                dc->id() != mSettings->workingDcNum()) {
            pendingDCs << dc;
        }
    }
    mPendingTransferSessions = pendingDCs.count();
    if(mPendingTransferSessions>0)
    {
        hasTransferSessions = true;
        Q_FOREACH(DC *dc, pendingDCs) {
            // create a new session for this dc
            Session *session = mApi->fileSession(dc);
            connect(session, &Session::sessionReady, this, &DcProvider::onTransferSessionReady);
            session->connectToServer();
        }
    } else
        Q_EMIT authTransferCompleted();
}

void DcProvider::onTransferSessionReady(DC *) {
    qCDebug(TG_CORE_DCPROVIDER) << "onTransferSessionReady():";
    Session *session = qobject_cast<Session *>(sender());
    mTransferSessions.append(session);
    if (--mPendingTransferSessions == 0) {
        Callback<AuthExportedAuthorization> callback = [this](TG_AUTH_EXPORT_AUTHORIZATION_CALLBACK) {
            if(!error.null) {
                qWarning() << "onTransferSessionReady(): " << error.errorCode << error.errorText;
                qWarning() << mTransferSessions.first()->dc()->id();
                return;
            }
            onAuthExportedAuthorization(result);
        };
        authExportAuthorization(mTransferSessions.first()->dc()->id(), callback);
    }
}

void DcProvider::onAuthExportedAuthorization(const AuthExportedAuthorization &result) {
    qCDebug(TG_CORE_DCPROVIDER) << "onAuthExportedAuthorization()";
    // Set ourId into settings (It doesn't matter if set before)
    mSettings->setOurId(result.id());
    // Change api dc to first in the transfer dcs list
    mApi->setMainSession(mTransferSessions.first());
    // Execute import in this dc

    Callback<AuthAuthorization> callback = [this](TG_AUTH_IMPORT_AUTHORIZATION_CALLBACK) {
        if(!error.null) {
            qWarning() << "onAuthExportedAuthorization(): " << error.errorCode << error.errorText;
            qWarning() << mTransferSessions.first()->dc()->id();
            return;
        }
        onAuthImportedAuthorization(result);
    };
    authImportAuthorization(result.id(), result.bytes(), callback);
}

void DcProvider::onAuthImportedAuthorization(const AuthAuthorization &) {
    qCDebug(TG_CORE_DCPROVIDER) << "onAuthImportedAuthorization()";
    Session *session = mTransferSessions.takeFirst();
    DC *authorizedDc = session->dc();
    authorizedDc->setExpires(0);
    authorizedDc->setState(DC::userSignedIn);
    session->release();
    mApi->setMainSession(mWorkingDcSession);
    if (mTransferSessions.isEmpty()) {
        mSettings->setDcsList(mDcs.values());
        mSettings->writeAuthFile();
        Q_EMIT authTransferCompleted();
    } else {
        Callback<AuthExportedAuthorization> callback = [this](TG_AUTH_EXPORT_AUTHORIZATION_CALLBACK) {
            if(!error.null) {
                qWarning() << "onAuthImportedAuthorization(): " << error.errorCode << error.errorText;
                qWarning() << mTransferSessions.first()->dc()->id();
                return;
            }
            onAuthExportedAuthorization(result);
        };
        authExportAuthorization(mTransferSessions.first()->dc()->id(), callback);
    }
}

void DcProvider::logOut() {
    Q_FOREACH (qint32 dcId, mDcs.keys()) {
        DC *dc = mDcs.value(dcId);
        dc->setState(DC::init);
    }
    mSettings->setDcsList(mDcs.values());
    mSettings->writeAuthFile();
}

void DcProvider::init() {

}

