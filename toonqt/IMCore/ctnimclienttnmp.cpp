#include "ctnimclienttnmp.h"
#include <QDebug>
#include "tmtp_biz.h"
#include "tnnotifycenter.h"
#include "CTNProcessThread.h"
#include "TMTPHostInfo.h"
#include "CLog.h"
#include "TNIMCoreProcessor.h"
#include "TNIMCoreClient.h"
#include "tnimutil.h"
#include "TNVersionInfo.h"
#include "TNIMNoticeProcessor.h"
#include "TNUserDataHelper.h"
#include "TNIMMsgManager.h"
#include "TNPathUtil.h"
#include <QCoreApplication>
#include "TNIMCoreClient.h"
#include "TNIMReadSessionManager.h"
#include "CTNChatAPI.h"
#include "TNPathUtil.h"
#include "TNIMSDKClient.h"
#include "CTNHttpBizApi.h"
#include <QJsonArray>
#include <qjsonobject.h>
#include <qjsondocument.h>
#include "curl.h"
#include "TNDataCache.h"
#include "tnwinconvert.h"
#include "CTNDBAPI.h"


#define PRIORITY_LEVEL_LOW		0
#define PRIORITY_LEVEL_HIGH		1
CTNIMClientTNMP::CTNIMClientTNMP() :_deviceToken(""), _msgManager(NULL), _imSDKClient(NULL)
{
	curl_global_init(CURL_GLOBAL_DEFAULT);
    _appType = QString(APPTYPE).right(3).toInt();
	qInfo() << "[IMCore][CTNIMClientTNMP] apptype = " << _appType;
    _version = TNVersionInfo::appVersion();
}

CTNIMClientTNMP::~CTNIMClientTNMP()
{
	curl_global_cleanup();
}

/**
  */

void CTNIMClientTNMP::addHostInfo(TMTPHostInfo &hostInfo)
{
	toonim::getImSDK()->addHostInfo(hostInfo.host.c_str(), hostInfo.port, hostInfo.isSSL);
	return;
}

int CTNIMClientTNMP::login(QString username, QString password)
{
	//更新myfeedlist
	//QList<st_FeedPtr> myAllStuff;
	//TNDataCache::GetInstance()->getMyStuff(myAllStuff);
	//vector<std::string> feedList;
	//for (st_FeedPtr feed : myAllStuff)
	//{
	//	feedList.push_back(feed->GetFeedID().toUtf8().data());
	//}
	//qInfo() << "[IMCore][CTNIMClientTNMP] login myfeed size:"<< feedList.size();
	return toonim::getImSDK()->login(username.toUtf8().data(), password.toUtf8().data());
}

int CTNIMClientTNMP::logout(bool notifyServer)
{
    qInfo()<<"[IMCore][CTNIMClientTNMP]TNIMClientTNMP logout ENTER";
	return toonim::getImSDK()->logout(notifyServer);
}

void CTNIMClientTNMP::reqSyncReadSession(QString sessionId)
{
	qInfo() << "[IMCore][CTNIMClientTNMP]TNIMClientTNMP reqSyncReadSession sessionId = " << sessionId;
	toonim::getImSDK()->reqSyncSessionStatus(sessionId.toUtf8().data());
}

int CTNIMClientTNMP::sendMessage(TNCMessage* message, QString toClientId)
{
	if (message == NULL)
		return -1;

	CTNMessage	sdkMessage;
	sdkMessage.type = message->type;
	sdkMessage.msgId = message->msgId.toUtf8().data();
	sdkMessage.seqId = message->seqId;
	sdkMessage.sessionId = message->getSesssionId().toUtf8().data();
	sdkMessage.fromClientId = message->fromUserId.toUtf8().data();
	sdkMessage.fromId = message->from.toUtf8().data();
	sdkMessage.toId = message->to.toUtf8().data();
	sdkMessage.toClientId = message->toUserId.toUtf8().data();
	sdkMessage.timestamp = message->timestamp;
	sdkMessage.expireTime = message->expireTime;
	sdkMessage.priority = PRIORITY_LEVEL_LOW;
	sdkMessage.pushInfo = message->getAbstractText().toUtf8().data();
	sdkMessage.sendStatus = CTNMessageSending;
	sdkMessage.status = MSG_USE_NORMAL;
	sdkMessage.senderName = message->senderName.toUtf8().data();
	sdkMessage.contentType = message->contentType;
	sdkMessage.catalogId = message->catalogId;
	sdkMessage.content = message->packBody().toUtf8().data();
	sdkMessage.isMyself = message->isMyself;
	sdkMessage.atType = message->atType;
	QJsonArray atTypesArray;
	for (int i = 0; i < message->atFeeds.size(); i++) {
		QJsonObject jsonFeed;
		QString feedId = message->atFeeds.at(i);
		jsonFeed.insert("feedId", feedId.toUtf8().data());
		st_FeedPtr feedPtr;
		TNUserDataHelper::GetInstance()->GetFeedInfo(feedId, feedPtr);
		if (feedPtr)
			jsonFeed.insert("userId", feedPtr->GetUserID().toUtf8().data());
		atTypesArray.insert(i, jsonFeed);
	}
    sdkMessage.atFeeds = QJsonDocument(atTypesArray).toJson().toStdString();
	QVariantMap addtion;
	addtion[ADDTION_LOCALPATH] = message->localPath.toUtf8().data();
	addtion[ADDTION_FILE_STATUS] = message->fileStatus;
	sdkMessage.addition = TNIMUtil::mapToJson(addtion).toUtf8().data();
	return toonim::getImSDK()->sendMessage(&sdkMessage);
}


int CTNIMClientTNMP::revokeMessage(TNCMessage* message, QString toClientId)
{
	QString sessionId = message->getSesssionId();
	QVariantMap bizMap = TNIMUtil::jsonToMap(message->getContent());;
	QString opMsgId = bizMap["msgId"].toString();
	QString opFeedId = bizMap["operatorFeedId"].toString();
	QString opName = bizMap["operatorName"].toString();
	return toonim::getImSDK()->revokeMessage(sessionId.toUtf8().data(), opMsgId.toUtf8().data(), opFeedId.toUtf8().data(), opName.toUtf8().data());
}

void CTNIMClientTNMP::InitIMSDK(TNIMMsgManager* msgManager)
{
	setMsgProcessor(msgManager);
	//初始化log
#ifdef Q_OS_WIN
	std::string log_path;
	log_path = tnwinconvert::UnicodeToAscii(tnwinconvert::Utf8ToUnicode(TNPathUtil::getLogPath().toStdString()));
	qInfo() << "[IMCore][CTNIMClientTNMP] logpath = " << log_path.c_str();
	toonim::initLog(log_path.c_str());
#else
	toonim::initLog(TNPathUtil::getLogPath().toUtf8().data());
#endif
	
	//初始化db
#ifdef Q_OS_WIN
	std::string imDbpath;
	imDbpath = tnwinconvert::UnicodeToUtf8(TNPathUtil::getUserPath().toStdWString());
	toonim::initImDB(_clientId.toUtf8().data(), imDbpath.c_str());
	qInfo() << "[IMCore][CTNIMClientTNMP] dbpath = " << imDbpath.c_str();
#else
	toonim::initImDB(_clientId.toUtf8().data(), TNPathUtil::getUserPath().toUtf8().data());
#endif
	//初始化im信息
	toonim::CTNClientInfo clientInfo;
	clientInfo.clientId = _clientId.toUtf8().data();
	clientInfo.deviceId = _deviceId.toUtf8().data();
	clientInfo.userType = 2;
	clientInfo.authType = 3;
	clientInfo.appType = 3;
	clientInfo.deviceType = TOON_DEVICE_TYPE;
	clientInfo.version = _version.toUtf8().data();
	QString appPath = QCoreApplication::applicationDirPath();
	clientInfo.appPath = appPath.toUtf8().data();
	toonim::ITnImSdk* imSDK = toonim::initIm(clientInfo);
	if (_imSDKClient == NULL)
		_imSDKClient = new TNIMSDKClient(_msgManager);
	//std::vector<int> subCatalogIds;
	//subCatalogIds.push_back(SubCatalogType_ChangeCard);
	//subCatalogIds.push_back(SubCatalogType_PhoneChangeCard);
	//过滤新的朋友通知
	//imSDK->addNoticeFilter(CATALOG_FRIEND_REQ, subCatalogIds, NEW_FRIEND_NOTICE);
	imSDK->setCallback(_imSDKClient);
	//初始化接口信息
	//toonim::initHttpBiz(clientInfo.clientId.c_str(), "", clientInfo.deviceId.c_str(), 0, clientInfo.version.c_str(), QSysInfo::productVersion().toUtf8().data());
}



