#include <QEventLoop>
#include "TNIMMsgManager.h"
#include "TNIMCoreClient.h"
#include "tncmessage.h"
#include "tnnotifycenter.h"
#include "TNUserDataHelper.h"
#include "TNDataControlServer.h"
#include "TNIMReadSessionManager.h"
#include "ctnimclienttnmp.h"
#include "CTNDBAPI.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
TNIMMsgManager::TNIMMsgManager() :_readManager(NULL), _msgProcessor(NULL)
{
	_msgProcessor = new TNIMCoreProcessor;
	_readManager = new TNIMReadSessionManager(this);
	qRegisterMetaType<toonim::CTNMessage>("toonim::CTNMessage");
	qRegisterMetaType<Toon::OffMsgCountResp>("Toon::OffMsgCountResp");
	qRegisterMetaType<Toon::HotSessionResp>("Toon::HotSessionResp");
	qRegisterMetaType<Toon::OffMsgResp>("Toon::OffMsgResp");
	qRegisterMetaType<Toon::SyncSessionStatusReq>("Toon::SyncSessionStatusReq");
	qRegisterMetaType<uint64_t>("uint64_t");
	qRegisterMetaType<TNMsgData>("TNMsgData");
	qRegisterMetaType<TNRevokeData>("TNRevokeData");
	qRegisterMetaType<QMap<QString, QString>>("QMap<QString, QString>");
	QObject::connect(this, SIGNAL(ProcessMsgRecvSign(int, toonim::CTNMessage)), this, SLOT(ProcessMsgRevcSlot(int, toonim::CTNMessage)));
	//QObject::connect(this, SIGNAL(ProcessHotSessionSign(Toon::HotSessionResp)), this, SLOT(ProcessHotSessionSlot(Toon::HotSessionResp)));
	//QObject::connect(this, SIGNAL(ProcessMsgOffSign(Toon::OffMsgCountResp)), this, SLOT(ProcessMsgOffSlot(Toon::OffMsgCountResp)));
	//QObject::connect(this, SIGNAL(ProcessMsgHistorySign(Toon::OffMsgResp)), this, SLOT(ProcessMsgHistorySlot(Toon::OffMsgResp)));
	QObject::connect(this, SIGNAL(ProcessMsgAckSign(QString, uint64_t, int)), this, SLOT(ProcessMsgAckSlot(QString, uint64_t, int)));
	QObject::connect(this, SIGNAL(SendMsgSign(TNMsgData, bool, bool)), this, SLOT(SendMsgSlot(TNMsgData, bool, bool)));
	QObject::connect(this, SIGNAL(SendRevertMsgSign(TNRevokeData, bool)), this, SLOT(SendRevertMsgSlot(TNRevokeData, bool)));
	QObject::connect(this, SIGNAL(SendReadSessionSign(QString, bool)), this, SLOT(SendReadSessionSlot(QString, bool)));
	QObject::connect(this, SIGNAL(SendForwardMsgSign(TNMsgData, QMap<QString, QString>)), this, SLOT(SendForwardMsgSlot(TNMsgData, QMap<QString, QString>)));
	QObject::connect(this, SIGNAL(SendOfflineReadSign()), this, SLOT(SendOfflineReadSlot()));
    QObject::connect(this, SIGNAL(waitOver()), this, SLOT(sendAllOverSignal()));
	this->moveToThread(&_threadMsgProcessor);
	_threadMsgProcessor.start();
}


TNIMMsgManager::~TNIMMsgManager()
{
	_threadMsgProcessor.quit();
	if (_msgProcessor)
		delete _msgProcessor;
}

void TNIMMsgManager::waitAllMsgOver()
{
    QEventLoop loop;
    QObject::connect(this, SIGNAL(allOver()), &loop, SLOT(quit()));
    emit waitOver();
    loop.exec();
}

void TNIMMsgManager::sendAllOverSignal()
{
    emit allOver();
}

void TNIMMsgManager::ProcessMsgRecv(int type, toonim::CTNMessage* req)
{
	qInfo() << "[IMCore][TNIMMsgManager]:ProcessMsgRecv";
	toonim::CTNMessage toonReq = *req;
	emit ProcessMsgRecvSign(type, toonReq);
}

//void TNIMMsgManager::ProcessHotSession(Toon::HotSessionResp* hotSessions)
//{
//	qInfo() << "[IMCore][TNIMMsgManager]:ProcessHotSession";
//	Toon::HotSessionResp hotSessionsResp = *hotSessions;
//	emit ProcessHotSessionSign(hotSessionsResp);
//}

//void TNIMMsgManager::ProcessMsgOff(Toon::OffMsgCountResp* offMsgCount)
//{
//	qDebug() << "[IMCore]:ProcessMsgOff";
//	Toon::OffMsgCountResp toonOffCount = *offMsgCount;
//	emit ProcessMsgOffSign(toonOffCount);
//}

//void TNIMMsgManager::ProcessMsgHistory(Toon::OffMsgResp* offMsg)
//{
//	qInfo() << "[IMCore][TNIMMsgManager]:ProcessMsgHistory";
//	Toon::OffMsgResp toonHisMsg = *offMsg;
//	emit ProcessMsgHistorySign(toonHisMsg);
//
//}

void TNIMMsgManager::ProcessMsgAck(const QString& msgId, uint64_t seqId, int status)
{
	qInfo() << "[IMCore][TNIMMsgManager]:ProcessMsgAck" << msgId;
	emit ProcessMsgAckSign(msgId, seqId, status);
}

void TNIMMsgManager::PreSaveMsgInThread(TNMsgData* msgData, bool singChat)
{
	qInfo() << "[IMCore][TNIMMsgManager]:PreSaveMsgInThread";
	emit SendMsgSign(*msgData, singChat, false);
}


void TNIMMsgManager::ProcessMsgRevcSlot(int type, toonim::CTNMessage req)
{
	qInfo() << "[IMCore][TNIMMsgManager]:ProcessMsgRevcSlot begin" << req.msgId.c_str();
	if (!_msgProcessor)
		return;
	//更新会话表
	toonim::CTNSession existSession = toonim::getChatDB()->getSession(req.sessionId.c_str());
	if (UpdateSessionTitle(existSession))
	{
		vector<CTNSession> sessionList;
		sessionList.push_back(existSession);
		toonim::getChatDB()->updateSession(sessionList);
	}
	if (req.type == TYPE_SINGLE_CHAT_MSGREQ || req.type == TYPE_GROUP_CHAT_MSGREQ)
	{
		//if (req.catalogId != 0)
			//_msgProcessor->ProcessChatSyncMsg(req.msgId.c_str(), req.catalogId, req.content.c_str());

		TNMsgData IMdata;
		IMdata.sessionId = req.sessionId.c_str();
		IMdata.msgId = req.msgId.c_str();
		IMdata.senderName = req.senderName.c_str();
		IMdata.from = req.fromId.c_str();
		IMdata.to = req.toId.c_str();
		IMdata.timestmp = req.timestamp;
		IMdata.bizType = (MSG_BIZ_TYPE)req.type;
		IMdata.bIsMyself = req.isMyself;
		IMdata.desc = req.pushInfo.c_str();
		IMdata.localPath = "";
		IMdata.atType = req.atType;
		if (!req.atFeeds.empty())
		{
			QJsonParseError jsonError;
			QJsonArray jsonFeeds = QJsonDocument::fromJson(req.atFeeds.c_str(), &jsonError).array();
			for (int index = 0; index < jsonFeeds.size(); index++)
			{
				QVariantMap feedItem = jsonFeeds[index].toVariant().toMap();
				//QString feed = feedItem["feedId"].toString();
				QString userId = feedItem["userId"].toString();
				IMdata.atFeeds.append(userId);
			}
		}
		IMdata.bIsAtMe = TNCMessage::IsContainMeAtFeedsFromMsgData(TNUserDataHelper::GetInstance()->_pluginParam->strTnUserID, IMdata);
		if (req.seqId > 0)
			IMdata.bSendSuc = true;
		else
			IMdata.bSendSuc = false;
		TNIMCoreClient::ParseContextToMsgData(req.content.c_str(), req.contentType, IMdata);
		IMdata.toUserId = req.toClientId.c_str();
		if (!_msgProcessor->ShouldShowMessage(&req))
		{
			return;
		}
		TNNotifyCenter::instance()->postNotifyRefresh(TNIMMsgRecvNotification, 0, "", IMdata);
	}
	else if (req.type == TYPE_NOTIFY_MSGREQ || req.type == TYPE_GROUP_NOTIFY_REQ)
	{
		//小秘书普通消息过滤
		if (!_msgProcessor->ShouldShowMessage(&req))
		{
			return;
		}
		TNNoticeInfo noticeInfo;
		TNIMNoticeProcessor::GetInstance().OnlineMsgToNotice(&req, noticeInfo);
		TNNotifyCenter::instance()->postNotifyRefresh(TNIMMsgRecvNotification, noticeInfo);
	}
	else if (req.type == TYPE_SYNC_MSGREQ)
	{
		if (req.catalogId == CATALOG_STNC_ORGCOMMUNICATION)
			_msgProcessor->ProcessChatSyncMsg(req.msgId.c_str(), req.catalogId, req.content.c_str());
		else
			_msgProcessor->ProcessSyncMsg(req.catalogId);
	}
	qDebug() << "[IMCore][TNIMMsgManager]:ProcessMsgRevcSlot end";
}

//void TNIMMsgManager::ProcessHotSessionSlot(Toon::HotSessionResp hotSessions)
//{
//	if (!_msgProcessor)
//		return;
//	qDebug() << "[IMCore][TNIMMsgManager]:ProcessHotSessionSlot begin";
//	_msgProcessor->ProcessHotSessionSlot(&hotSessions);
//	qDebug() << "[IMCore][TNIMMsgManager]:ProcessHotSessionSlot end";
//
//}

//void TNIMMsgManager::ProcessMsgOffSlot(Toon::OffMsgCountResp offMsgCount)
//{
//	if (!_msgProcessor)
//		return;
//	qDebug() << "[IMCore][TNIMMsgManager]:ProcessMsgOffSlot begin";
//	_msgProcessor->ProcessOffLineMsg(&offMsgCount);
//	qDebug() << "[IMCore][TNIMMsgManager]:ProcessMsgOffSlot end";
//}


void TNIMMsgManager::SendMsgInThread(TNMsgData* msgData, bool singChat)
{
	emit SendMsgSign(*msgData, singChat, true);
}

void TNIMMsgManager::SendRevertMsgInThread(TNRevokeData* msgData, bool singChat)
{
	emit SendRevertMsgSign(*msgData, singChat);
}

void TNIMMsgManager::SendForwardMsgInThread(TNMsgData* msgData, const QMap<QString, QString>& feedList)
{
	emit SendForwardMsgSign(*msgData, feedList);
}

void TNIMMsgManager::SendSyncReadSessionInThread(const QString& readSessionId, bool bRemoveSession)
{
	emit SendReadSessionSign(readSessionId, bRemoveSession);
}

void TNIMMsgManager::SendReadSessionSlot(QString readSessionID, bool bRemoveSession)
{
	TNIMCoreClient::GetIMClient()->SendReadSessionInner(readSessionID);
	if (bRemoveSession)
	{
		TNIMCoreClient::GetDBChat()->deleteSession(readSessionID.toUtf8().data());
		TNIMCoreClient::GetDBChat()->deleteAllMessage(readSessionID.toUtf8().data());
	}
}

void TNIMMsgManager::SendForwardMsgSlot(TNMsgData msgData, QMap<QString, QString> feedList)
{
	qInfo() << "[IMCore][TNIMMsgManager]:SendForwardMsgSlot ";
	TNIMCoreClient::GetIMClient()->SendForwardMessageInner(&msgData, feedList);
}


//void TNIMMsgManager::ProcessMsgHistorySlot(Toon::OffMsgResp offMsg)
//{
//	if (!_msgProcessor)
//		return;
//	qDebug() << "[IMCore]:ProcessMsgHistorySlot begin";
//	_msgProcessor->ProcessHistoryMsg(&offMsg);
//	TNNotifyCenter::instance()->postNotifyOffMsg(offMsg.msgs.size());
//	qDebug() << "[IMCore]:ProcessMsgHistorySlot end";
//}

void TNIMMsgManager::ProcessMsgAckSlot(QString msgId, uint64_t seqId, int status)
{
	if (!_msgProcessor)
		return;
	qInfo() << "[IMCore][TNIMMsgManager]:ProcessMsgAck ";
	_msgProcessor->ProcessSendMsgAck(msgId, seqId, status);
}

void TNIMMsgManager::SendMsgSlot(TNMsgData msgData, bool singChat, bool bSend)
{
	TNIMCoreClient::GetIMClient()->SendIMMessageInner(&msgData, singChat, bSend);
}

void TNIMMsgManager::SendRevertMsgSlot(TNRevokeData msgData, bool singChat)
{
	qInfo() << "[IMCore][TNIMMsgManager]:SendRevertMsgSlot";
	TNIMCoreClient::GetIMClient()->SendRevokeMessageInner(&msgData, singChat);
}

void TNIMMsgManager::SendOfflineReadSessionInThread()
{
	emit SendOfflineReadSign();
}

bool TNIMMsgManager::UpdateSessionTitle(toonim::CTNSession& session)
{
	if (!session.sessionId.empty() && (session.title.empty() || session.avatarId.empty() || session.myFeedId.empty()))
	{
		QString sessionId = session.sessionId.c_str();
		if (session.type == TYPE_SINGLE_CHAT_MSGREQ || session.type == TYPE_MSG_SINGLE_OPERATE)
		{
			QString myFeedId = session.myFeedId.c_str(); 
			if (!myFeedId.isEmpty())
			{
				QString feedOther = GetOtherFeed(sessionId, myFeedId).toUtf8().data();
				st_FeedPtr feed;
				TNUserDataHelper::GetInstance()->GetFeedInfo(feedOther, feed);
				if (feed.get() != NULL)
				{
					session.title = feed->GetTitle().toUtf8().data();
					session.avatarId = feed->GetAvatarID().toUtf8().data();
				}
			}
		}
		else if (session.type == TYPE_GROUP_CHAT_MSGREQ || session.type == TYPE_MSG_GROUP_OPERATE)
		{
			QString groupId = sessionId;
			st_GroupInfo groupInfo;
			TNUserDataHelper::GetInstance()->GetGroupInfo(groupId, groupInfo);
			session.title = groupInfo.GetName().toUtf8().data();
			session.myFeedId = groupInfo.GetMyFeedId().toUtf8().data();
			session.avatarId = groupInfo.GetHeaderImage().toUtf8().data();
		}
		else if (session.type == TYPE_NOTIFY_MSGREQ)
		{
			st_MessageAppInfoPtr messageAppInfo;
			TNUserDataHelper::GetInstance()->GetAppInfo(sessionId, messageAppInfo);
			if (messageAppInfo.get() != NULL)
			{
				session.title = messageAppInfo->GetAppTitle().toUtf8().data();
				session.avatarId = messageAppInfo->GetAppLittleIcon().toUtf8().data();
			}
		}
		else if (session.type == TYPE_GROUP_NOTIFY_REQ)
		{
			st_FeedPtr feed;
			TNUserDataHelper::GetInstance()->GetFeedInfo(sessionId, feed);
			if (feed.get() != NULL)
			{
				session.title = feed->GetTitle().toUtf8().data();
				session.avatarId = feed->GetAvatarID().toUtf8().data();
			}
		}
		return true;
	}
	//单聊更新topic，旧版本topic于sdk不一致，导致已读单聊有问题
	if (session.type == TYPE_SINGLE_CHAT_MSGREQ || session.type == TYPE_MSG_SINGLE_OPERATE)
	{
		if (session.topic.empty() || session.topic.find("_") == std::string::npos)
		{
			QString sessionId = session.sessionId.c_str();
			QString myFeedId = session.myFeedId.c_str();
			if (!myFeedId.isEmpty())
			{
				QString otherFeed = GetOtherFeed(sessionId, myFeedId).toUtf8().data();
				session.topic = otherFeed.toUtf8().data();
				return true;
			}
		}
	}
	return false;
}

QString TNIMMsgManager::GetOtherFeed(const QString& sessionId, const QString& myFeedId)
{
	int iMeIndex = sessionId.indexOf(myFeedId);
	QString otherFeed;
	if (iMeIndex == 0)
		otherFeed = sessionId.right(sessionId.size() - myFeedId.size() - 1);
	else
		otherFeed = sessionId.left(sessionId.size() - myFeedId.size() - 1);
	return otherFeed;
}