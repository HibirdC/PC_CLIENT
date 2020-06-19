#include "TNIMCoreProcessor.h"
#include "tncmessage.h"
#include "TNDataControlServer.h"
#include "CTNProcessThread.h"
#include <QJsonObject>
#include <QJsonArray>
#include "tnimutil.h"
#include "TNUserDataHelper.h"
#include "TNIMNoticeProcessor.h"
#include "TNNoticeUpdater.h"
#include "tnnotifycenter.h"
#include "TNIMMessageOperater.h"
#include "TNVersionInfo.h"
#include "CTNDBAPI.h"
#include "TNDataCache.h"
#include "TNCHNHelper.h"
#define OFFMSG_MAXNUM   15
#define HISMSG_MAXNUM   500
TNIMCoreProcessor::TNIMCoreProcessor() :_noticeUpdate(NULL), _messageOperate(NULL)
{
	_messageOperate = new TNIMMessageOperater;
	qRegisterMetaType<TNOffMsg>("TNOffMsg");
	QObject::connect(this, SIGNAL(SendHistoryMsgReq(TNOffMsg)), this, SLOT(OnSendHistoryMsgReq(TNOffMsg)));
	_noticeUpdate = new TNNoticeUpdater;
	_noticeUpdate->moveToThread(&_threadUpdater);
	_threadUpdater.start();
}


TNIMCoreProcessor::~TNIMCoreProcessor()
{
	_threadUpdater.quit();
	if (_noticeUpdate)
		delete _noticeUpdate;
	if (_messageOperate)
		delete _messageOperate;
}

void TNIMCoreProcessor::SaveMsgToDB(TNCMessage* message, bool bSendMsg)
{
	if (message == NULL)
		return;
    qInfo() << "[IMCore][TNIMCoreProcessor]:SaveMsgToDB" << message->msgId;
	CTNMessage imMessage;
	imMessage.sessionId = message->getSesssionId().toUtf8().data();
	imMessage.msgId = message->msgId.toUtf8().data();
	imMessage.type = message->type;
	imMessage.seqId = message->seqId;
	imMessage.fromId = message->from.toUtf8().data();
	imMessage.fromClientId = message->fromUserId.toUtf8().data();
	imMessage.toId = message->to.toUtf8().data();
	imMessage.toClientId = message->toUserId.toUtf8().data();
	imMessage.timestamp = message->timestamp;
	imMessage.pushInfo = message->pushInfo.toUtf8().data();
	imMessage.expireTime = message->expireTime;
	imMessage.sendStatus = message->sendStatus;
	imMessage.priority = message->priority;
	imMessage.catalogId = message->catalogId;
	imMessage.contentType = message->contentType;
	imMessage.atType = message->atType;
	imMessage.atFeeds = message->GetAtFeedlist().toUtf8().data();
	imMessage.status = MSG_USE_NORMAL;
	if (bSendMsg)
	{
		QString content = message->packBody();
		if (content.isEmpty())
			content = message->getContent();
		imMessage.content = content.toUtf8().data();
	}
	else
		imMessage.content = message->getContent().toUtf8().data();
	imMessage.isMyself = message->isMyself;
	imMessage.senderName = message->senderName.toUtf8().data();
	QVariantMap addtion;
	addtion[ADDTION_LOCALPATH] = message->localPath.toUtf8().data();
	addtion[ADDTION_FILE_STATUS] = message->fileStatus;
	imMessage.addition = TNIMUtil::mapToJson(addtion).toUtf8().data();
	toonim::getChatDB()->replaceMessage(imMessage);
	return;
}

void TNIMCoreProcessor::PreSaveSendMsg(TNCMessage* message)
{
	//预存单个消息
	SaveMsgToDB(message, true);
	//更新会话表
	storageSessioFromIM(message->type, 0, message);
}

void TNIMCoreProcessor::MsgDbToMessage(st_BMessage0Ptr dbMessage, TNCMessage& message)
{
	if (!dbMessage)
		return;
	message.SetSessionId(dbMessage->GetSessionId());
	message.msgId = dbMessage->GetMsgId();
	message.type = (Toon_TMTP_TYPE)dbMessage->GetType();
	message.seqId = dbMessage->GetSeqId();
	message.from = dbMessage->GetFromId();
	message.fromUserId = dbMessage->GetFormClientId();
	message.toUserId = dbMessage->GetToClientId();
	message.to = dbMessage->GetToId();
	message.timestamp = dbMessage->GetTimestamp();
	message.pushInfo = dbMessage->GetPushInfo();
	message.expireTime = dbMessage->GetExpireTime();
	message.sendStatus = (TNIMMessageSendStatus)dbMessage->GetSendStatus();
	message.priority = dbMessage->GetPriority();
	message.catalogId = dbMessage->GetCatalogId();
	message.catalog = dbMessage->GetCatalog();
	message.contentType = (TNMessageContentType)dbMessage->GetContentType();
	message.setContent(dbMessage->GetContent());
	message.isMyself = dbMessage->GetIsMyself();
	message.senderName = dbMessage->GetSenderName();
}


void TNIMCoreProcessor::UpdateMsgStatus(QString& msgId, MSG_STATUS status)
{
	QString strStatus = QString::number((int)status);
	TNDataControlServer::GetInstance()->UpdateSetValueByField("BMessage0", "status", strStatus, "msgId", msgId, DBTYPE_MSG);
}


TNCMessage* TNIMCoreProcessor::storageOneMsgFromIM(int type, Toon::MsgReq* msg, bool isFromMyself, bool bOnline)
{
	if (!msg)
		return NULL;
	//bool bNeedProcessMsg = false;
	//if (msg->to_toon_type.size() > 0)
	//{
	//	std::vector<string> toToonTypes = msg->to_toon_type;
 //       for (size_t index = 0; index < toToonTypes.size(); index++)
	//	{
	//		QString toonType = toToonTypes[index].c_str();
	//		qInfo() << "[IMCore][TNIMCoreProcessor]:storageOneMsgFromIM toToonType" << toonType;
	//		if (toonType == APPTYPE)
	//		{
	//			bNeedProcessMsg = true;
	//			break;
	//		}
	//	}
	//}
	//else
	//	bNeedProcessMsg = true;
	//if (!bNeedProcessMsg)
	//	return NULL;
	TNCMessage* message = TNCMessage::instanceFromMsgReq(type, msg);
    if (message->getSesssionId() == "v_11" && message->contentType == TNChatTypeText)
    {
        delete message;
        return NULL;
    }
	message->isMyself = isFromMyself;
	if (!isFromMyself)
		ProcessIsMyself(*message);

	bool bRevertMsg = false;
	bRevertMsg = _messageOperate->ProcessMessageRevert(message);
	
	//离线正常消息过滤
	if (!bRevertMsg)
	{
		if (bOnline == false)
			_messageOperate->ProcessChatMsgFilterRvert(message);
		SaveMsgToDB(message);
	}
		
	if (message->catalogId != 0)
		ProcessChatSyncMsg(message);
	return message;
}
bool TNIMCoreProcessor::ShouldShowSyncMsg(int  catalogId, QString content)
{
	bool bShow = false;
	switch (catalogId)
	{ 
		case CATALOG_ME_JOIN_GROUP:
		case CATALOG_CHANGE_GROUP:
		//主动退出群聊不展示
		//case CATALOG_OTHER_QUIT_GROUP: 
		case CATALOG_OTHER_QUIT:
		case CATALOG_ME_QUIT_GROUP:
		{
			QVariantMap mapResp = TNIMUtil::jsonToMap(content);
			QList<QVariant> userIds = mapResp["showFeedIdList"].toList();
			for (int index = 0; index < userIds.size(); index++)
			{
				QString userId = userIds[index].toString();
				if (TNDataCache::GetInstance()->IsInMyStuff(userId))
				{
					bShow = true;
					break;
				}
			}
		}
		default:
			break;
	}
	return bShow; 
}

void TNIMCoreProcessor::ProcessSyncMsg(int catalogId)
{
	_noticeUpdate->ProcessUpdateUI(catalogId);
}

void TNIMCoreProcessor::ProcessChatSyncMsg(const QString& msgId, int catalogId, QString content)
{
	qInfo() << "[IMCore][TNIMCoreProcessor]:ProcessChatSyncMsg" << msgId << "type:" << catalogId;
	switch (catalogId)
	{
		case CATALOG_ME_JOIN_GROUP:
		case CATALOG_CHANGE_GROUP:
		case CATALOG_ME_QUIT_GROUP:
			SyncMyGroupInfo(catalogId, content);
			break;
		case CATALOG_OTHER_QUIT:
		case CATALOG_OTHER_QUIT_GROUP:
			SynicMyGroupMember(catalogId, content);
			break;
		case CATALOG_STNC_ORGCOMMUNICATION:
			synicOrgCommunication(catalogId, content);
			break;
		default:
		break; 
	}
}


void TNIMCoreProcessor::ProcessChatSyncMsg(TNCMessage* msg)
{
	qInfo() << "[IMCore][TNIMCoreProcessor]:ProcessChatSyncMsg" << msg->msgId << "type:" << msg->catalogId;
	switch (msg->catalogId)
	{
		case CATALOG_ME_JOIN_GROUP:
		case CATALOG_CHANGE_GROUP:
		case CATALOG_ME_QUIT_GROUP:
		{
            QString content = msg->getContent();
            SyncMyGroupInfo(msg->catalogId, content);
			break;
		}
		case CATALOG_OTHER_QUIT:
		case CATALOG_OTHER_QUIT_GROUP:
		{
            QString content = msg->getContent();
            SynicMyGroupMember(msg->catalogId, content);
			break;
		}
		default:
			break;
	}
}

void TNIMCoreProcessor::SyncMyGroupInfo(int type, QString& content)
{
	/*if (type == CATALOG_CHANGE_GROUP)
	{
	QVariantMap mapResp = TNIMUtil::jsonToMap(content);
	QString groupID = "gc_" + mapResp["groupId"].toString();
	QVariantMap groupInfo = mapResp["groupInfo"].toMap();
	QString groupName = groupInfo["groupName"].toString();
	QString createFeedId = groupInfo["creatorFeedId"].toString();

	if (!groupName.isEmpty())
	{
	QString newPinying = TNCHNHelper::GetPinyins(groupName);
	TNDataControlServer::GetInstance()->UpdateSetValueByFieldEx("GroupInfo", "name", groupName, "groupId", groupID,"namePinyin",newPinying, DBTYPE_USER);
	toonim::getChatDB()->updateSessionTitleAndImage(groupID.toUtf8().data(), groupName.toUtf8().data(), NULL);
	QList<UINotifyData> notifyData;
	UINotifyData itemdata;
	itemdata.operateType = UI_OPERATE_ADD;
	itemdata.feedId = groupID;
	notifyData.append(itemdata);
	TNNotifyCenter::instance()->postNotifyRefresh(RefreshTypeUI_GroupChat, notifyData);
	}
	else
	{
	if (!createFeedId.isEmpty())
	TNDataControlServer::GetInstance()->UpdateSetValueByField("GroupInfo", "creatorFeedId", createFeedId, "groupId", groupID, DBTYPE_USER);
	}
	}
	else*/
		_noticeUpdate->ProcessUpdateUI(CATALOG_SYNC_GROUPCHAT);
}

void TNIMCoreProcessor::SynicMyGroupMember(int type, QString& content)
{
	QVariantMap mapResp = TNIMUtil::jsonToMap(content);
	QString groupID = mapResp["groupId"].toString();
	_noticeUpdate->ProcessUpdateUI(CATALOG_SYNC_GROUPMEMBER, groupID);
}

void TNIMCoreProcessor::SynicGroupChatMember(QString& strGroupId)
{
    QString groupId = strGroupId;
    if (!groupId.startsWith("gc_"))
        groupId = "gc_" + groupId;
    TNUserVersionInfo::GetInstance()->ResetUpdateVersion(groupId);
    if (_noticeUpdate && !strGroupId.isEmpty())
        _noticeUpdate->ProcessUpdateUI(CATALOG_SYNC_GROUPMEMBER, strGroupId);
}

void TNIMCoreProcessor::SynicGroupChat()
{
	if (_noticeUpdate)
		_noticeUpdate->ProcessUpdateUI(CATALOG_SYNC_GROUPCHAT);
}

bool TNIMCoreProcessor::ShouldShowMessage(TNCMessage* message)
{
	bool bShow = true;
	if (message->type == TYPE_NOTIFY_MSGREQ && message->catalogId == CATALOG_FRIEND_REQ)
	{
		//新的朋友通知过滤好友交换，手机通讯录交换名片
		QVariantMap context = TNIMUtil::jsonToMap(message->getContent());
		SubCatalogType subNoticeType = (SubCatalogType)context["subCatalogId"].toInt();
		if (subNoticeType == SubCatalogType_ChangeCard || subNoticeType == SubCatalogType_PhoneChangeCard)
			bShow = false;
		if (_noticeUpdate)
			_noticeUpdate->ProcessUpdateUI(CATALOG_FRIEND_REQ);
	}
	else if (message->type == TYPE_GROUP_CHAT_MSGREQ && message->catalogId != 0)
	{
		if (!ShouldShowSyncMsg(message->catalogId, message->getContent()))
			bShow = false;
	}
	else
	{
		if (message->getSesssionId() == "v_11" && message->contentType == TNChatTypeText)
			bShow = false;
	}
	return bShow;
}

bool TNIMCoreProcessor::ShouldShowMessage(toonim::CTNMessage* message)
{
	bool bShow = true;
	if (message->type == TYPE_NOTIFY_MSGREQ)
	{
		if (message->catalogId == CATALOG_FRIEND_REQ)
		{
			//新的朋友通知过滤好友交换，手机通讯录交换名片
			QVariantMap context = TNIMUtil::jsonToMap(message->content.c_str());
			SubCatalogType subNoticeType = (SubCatalogType)context["subCatalogId"].toInt();
			if (subNoticeType == SubCatalogType_ChangeCard || subNoticeType == SubCatalogType_PhoneChangeCard)
				bShow = false;
			if (_noticeUpdate)
				_noticeUpdate->ProcessUpdateUI(CATALOG_FRIEND_REQ); 
		}
		else if (message->catalogId == CATALOG_SCAN_INFO)
			bShow = false;
	}
	else if (message->type == TYPE_GROUP_CHAT_MSGREQ && message->catalogId != 0)
	{
		if (!ShouldShowSyncMsg(message->catalogId, message->content.c_str()))
			bShow = false;
	}
	else
	{
		if (message->sessionId == "v_11" && message->contentType == TNChatTypeText)
			bShow = false;
	}
	return bShow;

}

void TNIMCoreProcessor::updateNewFriendNotice()
{
	if (_noticeUpdate)
		_noticeUpdate->ProcessUpdateUI(CATALOG_FRIEND_REQ);
}

qlonglong TNIMCoreProcessor::GetLocalMaxSeqId(QString sessionId)
{
	return toonim::getChatDB()->getMaxSeqAllMessage(sessionId.toUtf8().data(), 2);
}

void TNIMCoreProcessor::ProcessIsMyself(TNCMessage& message)
{
	QString myFeedId = message.from;
	bool bIsMyself = false;
	TableBaseVec myFeedVec;
	//多端多活，我新建的名片，名片没有入库，直接来消息,查库不准，需要根据userid
	if (message.type == message.type == TYPE_SINGLE_CHAT_MSGREQ)
	{
		if (!message.toUserId.isEmpty())
		{
			if (message.toUserId != TNUserDataHelper::GetInstance()->_pluginParam->strTnUserID)
				bIsMyself = true;
		}
	}
	else if (message.type == message.type == TYPE_GROUP_CHAT_MSGREQ)
	{
		if (!message.fromUserId.isEmpty())
		{
			if (message.fromUserId == TNUserDataHelper::GetInstance()->_pluginParam->strTnUserID)
				bIsMyself = true;
		}
	}
	message.isMyself = bIsMyself;
}

TNCMessage* TNIMCoreProcessor::ProcessOnLineMsg(int type, Toon::MsgReq* onLineMsg, bool isFromMyself)
{
	if (!onLineMsg)
		return NULL;
	TNCMessage* msg = storageOneMsgFromIM(type, onLineMsg, isFromMyself);
	if (msg)
	{
		int unReadCount = 1;
		if (isFromMyself)
			unReadCount = 0;
		else
		{
			if (_messageOperate->IsRevertMsg(msg))
				unReadCount = -1;
		}
		if (ShouldShowMessage(msg))
			storageSessioFromIM(type, unReadCount, msg);
	}
		
	return msg;
}

//void TNIMCoreProcessor::ProcessHotSessionSlot(Toon::HotSessionResp* hotSessions)
//{
//	if (hotSessions->code != 0)
//		return;
//	QMap<qlonglong, Toon::HotSessionItem> hotSessionsMap;
//	QMap<QString, qlonglong> sessionMaxSeqMap;
//	//order by timestamp
//	for (int32_t i = 0; i < hotSessions->vSessionInfo.size(); ++i)
//	{
//		Toon::HotSessionItem& sessionItem = hotSessions->vSessionInfo.at(i);
//		int sessionType = 0;
//		qlonglong maxSeqId = 0;
//		qlonglong maxTimestamp = 0;
//		QString sessionId;
//		vector<Toon::OffMsgItem>   offMsgItems;
//		offMsgItems.insert(offMsgItems.end(), sessionItem.priority_top_msg.begin(), sessionItem.priority_top_msg.end());
//		offMsgItems.insert(offMsgItems.end(), sessionItem.normal_top_msg.begin(), sessionItem.normal_top_msg.end());
//		for (int index = 0; index < offMsgItems.size(); ++index)
//		{
//			Toon::OffMsgItem& msgItem = offMsgItems[index];
//			//取最大seqid
//			if (msgItem.item.seq_id > maxSeqId)
//			{
//				maxSeqId = msgItem.item.seq_id;
//				maxTimestamp = msgItem.item.timestamp;
//			}
//			if (index == 0)
//			{
//				sessionId = genSessionIdFromServerMsg(msgItem);
//				sessionType = msgItem.type;
//			}
//				
//		}
//		//同步消息过滤
//		if (sessionType == TYPE_SYNC_MSGREQ)
//			continue;
//		hotSessionsMap.insert(maxTimestamp, sessionItem);
//		sessionMaxSeqMap.insert(sessionId, maxSeqId);
//	}
//    const QList<Toon::HotSessionItem>& hostSessionItemList = hotSessionsMap.values();
//	for (int32_t i = hostSessionItemList.size() - 1; i >= 0; i--)
//	{
//		Toon::HotSessionItem sessionItem = hostSessionItemList.at(i);
//		qlonglong readSeqId = (qlonglong)sessionItem.read_seq_id;
//		qlonglong localMaxSeqId = 0; 
//		qlonglong maxSeqId = 0;
//		qlonglong maxTimestamp = 0;
//		QString sessionId;
//		int sessionType = 0;
//		vector<TNCMessage*> msgs;
//		vector<Toon::OffMsgItem>   offMsgItems;
//		offMsgItems.insert(offMsgItems.end(), sessionItem.priority_top_msg.begin(), sessionItem.priority_top_msg.end());
//		offMsgItems.insert(offMsgItems.end(), sessionItem.normal_top_msg.begin(), sessionItem.normal_top_msg.end());
//		for (int index = 0; index < offMsgItems.size(); ++index)
//		{
//			Toon::OffMsgItem msgItem = offMsgItems[index];
//			if (index == 0)
//			{
//				sessionType = msgItem.type;
//				sessionId = genSessionIdFromServerMsg(msgItem);
//				localMaxSeqId = GetLocalMaxSeqId(sessionId);
//				maxSeqId = sessionMaxSeqMap[sessionId];
//			}
//			if (msgItem.item.seq_id == maxSeqId)
//			{
//				maxTimestamp = msgItem.item.timestamp;
//				TNCMessage* msg = storageOneMsgFromIM(msgItem.type, &msgItem.item, false, false);
//				if (!msg)
//					continue;
//				msgs.push_back(msg);
//			}
//		}
//		qInfo() << "[IMCore][TNIMCoreProcessor] hotSession sessionId:" << sessionId << "readSeqId:" << readSeqId << "maxSeqId:" << maxSeqId;
//		TNCMessage* lastMsg = NULL;
//		bool bLastRevertMsg = false;
//		bool bHasAtMeMsg = false;
//		for (int indexMsg = 0; indexMsg < msgs.size(); indexMsg++)
//		{
//			TNCMessage* msg = msgs[indexMsg];
//			//本地已经拉全推的重复消息过滤
//			if (maxSeqId == localMaxSeqId)
//			{
//				delete msg;
//				continue;
//			}
//
//			bool bShowMsg = true;
//			if (!ShouldShowMessage(msg))
//				bShowMsg = false;
//			//find should show lastmessage 
//			bool bLastCopy = false;
//			
//			if (bShowMsg)
//			{
//				if (msg->type != TYPE_MSG_SINGLE_OPERATE && msg->type != TYPE_MSG_GROUP_OPERATE)
//				{
//					if (lastMsg == NULL)
//					{
//						lastMsg = msg;
//						bLastCopy = true;
//					}
//					else if (msg->seqId > lastMsg->seqId)
//					{
//						if (lastMsg)
//							delete lastMsg;
//						lastMsg = NULL;
//						lastMsg = msg;
//						bLastCopy = true;
//					}
//				}
//				else
//				{
//					if (msg->seqId == maxSeqId)
//						bLastRevertMsg = true;
//				}
//				if (msg->IsContaionMeAtFeeds(TNUserDataHelper::GetInstance()->_pluginParam->strTnUserID))
//				{
//					bHasAtMeMsg = true;
//					qInfo() << "[IMCore][TNIMCoreProcessor] hotsession hasAtMefeeds sessionId:" << sessionId << "msgId:" << msg->msgId;
//				}
//					
//			}
//			if (indexMsg == msgs.size() - 1) 
//			{
//				//最后消息更新session
//				TNSessionItem* session = new TNSessionItem;
//				session->bHasAtMeMsg = bHasAtMeMsg;
//				session->readSeqId = readSeqId;
//				if (lastMsg)
//				{
//					session->sessionId = lastMsg->getSesssionId();
//					session->bFinishLastMsg = true;
//					session->lastMsgId = lastMsg->msgId;
//					storageSessioFromIM(sessionType, 0, lastMsg);
//					if (maxSeqId - localMaxSeqId <= 1)
//					{
//						session->unReadCount = maxSeqId - session->readSeqId;
//						if (session->unReadCount == 1 && lastMsg->isMyself)
//							session->unReadCount = 0;
//						else if (bLastRevertMsg)
//							session->unReadCount = 0;
//						session->bFinishReadCount = true;
//						QString bHasAtMeMsg;
//						QString unReadCount = QString::number(session->unReadCount);
//						if (session->unReadCount> 0 && session->bHasAtMeMsg)
//							bHasAtMeMsg = QString::number(session->bHasAtMeMsg);
//						else
//							bHasAtMeMsg = QString::number(0);
//						TNDataControlServer::GetInstance()->UpdateSetValueByFieldEx("Session", "unreadCount", unReadCount, "sessionId", session->sessionId, "atMeStatus", bHasAtMeMsg, DBTYPE_MSG);
//					}
//					else
//					{
//						session->unReadCount = 0;
//						session->bFinishReadCount = false;
//					}
//				}
//				else
//				{
//					session->sessionId = msg->getSesssionId();
//					session->bFinishLastMsg = false;
//					session->bFinishReadCount = false;
//				}
//				//本次没有拉取全
//				if (maxSeqId - localMaxSeqId > 1)
//				{
//					session->upSeqId = maxSeqId;
//					//本地没有拉过，只拉一页
//					if (localMaxSeqId == 0 && maxSeqId > OFFMSG_MAXNUM)
//					{
//						if (maxSeqId == session->readSeqId)
//							session->downSeqId = maxSeqId - OFFMSG_MAXNUM;
//						else
//							session->downSeqId = readSeqId;
//					}
//					else
//						session->downSeqId = localMaxSeqId; 
//					session->currentPullSeqId = 0;
//					_sessionItems.insert(session->sessionId, session);
//					requestUnDownLoadOffMsg(maxSeqId, maxTimestamp, session->downSeqId, msg);
//				}
//				else
//				{
//					//通知ui刷新
//					QStringList sessionItems;
//					sessionItems.append(session->sessionId);
//					TNNotifyCenter::instance()->postNotifyRefresh(sessionItems);
//					delete session;
//				}
//				if (lastMsg)
//					delete lastMsg;
//			}
//			if (!bLastCopy) 
//				delete msg;	
//		}
//	}
//}


//void TNIMCoreProcessor::ProcessOffLineMsg(Toon::OffMsgCountResp* offLineMsgs)
//{
//	if (offLineMsgs->code == 0)
//	{
//		//成功入库
//		QMultiMap<qlonglong, QString> sessionMap;
//		for (int index = 0; index < offLineMsgs->msg_counts.size(); index++)
//		{
//			Toon::OffMsgCountItem& offMsgItem = offLineMsgs->msg_counts[index];
//			std::vector<Toon::MsgReq>& msgs = offMsgItem.msgs;
//			TNCMessage* lastMsg = NULL;
//			int UnReadReduce = 0;
//			for (int indexMsg = 0; indexMsg < msgs.size(); indexMsg++)
//			{
//				//存message
//				bool bShowMsg = true;
//				TNCMessage* msg = storageOneMsgFromIM(offMsgItem.type, &msgs[indexMsg], false, false);
//				if (!msg)
//					continue;
//				if (msg->bubbleFlag == 1)
//					bShowMsg = false;
//				else if (!ShouldShowMessage(msg))
//					bShowMsg = false;
//
//				//find should show lastmessage 
//				bool bLastCopy = false;
//				if (bShowMsg && msg->type != TYPE_MSG_SINGLE_OPERATE && msg->type != TYPE_MSG_GROUP_OPERATE)
//				{
//					if (lastMsg == NULL)
//					{
//						lastMsg = msg;
//						bLastCopy = true;
//					}
//					else if (msg->seqId > lastMsg->seqId)
//					{
//						if (lastMsg)
//							delete lastMsg;
//						lastMsg = NULL;
//						lastMsg = msg;
//						bLastCopy = true;
//					}
//				}
//				
//				if (!bShowMsg)
//					UnReadReduce++;
//				if (indexMsg == msgs.size() - 1)
//				{
//					//最后消息更新session
//					if (lastMsg)
//					{
//						storageSessioFromIM(offMsgItem.type, offMsgItem.count - UnReadReduce, lastMsg);
//						sessionMap.insert(lastMsg->timestamp, lastMsg->getSesssionId());
//						delete lastMsg;
//					}
//				}
//				else if (indexMsg == 0)
//					requestUnDownLoadOffMsg(offMsgItem, msg);
//				if (!bLastCopy)
//					delete msg;
//			}
//		}
//		TNNotifyCenter::instance()->postNotifyRefresh(sessionMap.values());
//	}
//
//} 

void TNIMCoreProcessor::requestUnDownLoadOffMsg(qlonglong maxSeqId, qlonglong maxTimeStmp, qlonglong minSeqId, TNCMessage* message)
{
	int unDownloadCount = maxSeqId - minSeqId;
	if (unDownloadCount > 0)
	{
		TNOffMsg offMsg;
		offMsg.from = message->from;
		offMsg.to = message->to;
		offMsg.type = message->type;
		offMsg.maxSeqId = maxSeqId;
		offMsg.maxTimeStamp = maxTimeStmp;
		offMsg.minSeqId = minSeqId;
		if (minSeqId == 0)
			offMsg.count = unDownloadCount;
		else
			offMsg.count = unDownloadCount + 1;
		TNIMCoreClient::GetIMClient()->RequestOffMsg(offMsg);
	}
}

void TNIMCoreProcessor::OnSendHistoryMsgReq(TNOffMsg offMsg)
{
	TNIMCoreClient::GetIMClient()->RequestOffMsg(offMsg);
}

void TNIMCoreProcessor::storageSessioFromIM(int type, int unReadCount, TNCMessage* lastMsg)
{
	if (lastMsg == NULL)
		return;
	qDebug() << "[IMCore]:storageSessioFromIM begin" << lastMsg->msgId;
	CTNSession session;
	session.sessionId = lastMsg->getSesssionId().toUtf8().data();
	session.topic = lastMsg->getTopic().toUtf8().data();
	session.myFeedId = lastMsg->from.toUtf8().data();
	session.type = lastMsg->type;
	if (lastMsg->type == TYPE_SINGLE_CHAT_MSGREQ)
	{
		TableBaseVec feedTableBaseVec;
		QString feedOther;
		if (lastMsg->isMyself)
		{
			session.myFeedId = lastMsg->from.toUtf8().data();
			session.topic = lastMsg->to.toUtf8().data();
			feedOther = lastMsg->to;
		}
		else
		{
			session.myFeedId = lastMsg->to.toUtf8().data();
			session.topic = lastMsg->from.toUtf8().data();
			feedOther = lastMsg->from;
		}
		st_FeedPtr feed;
		TNUserDataHelper::GetInstance()->GetFeedInfo(feedOther, feed);
		if (feed.get() != NULL)
		{
			session.title = feed->GetTitle().toUtf8().data();
			session.avatarId = feed->GetAvatarID().toUtf8().data();
		}

	}
	else if (lastMsg->type == TYPE_GROUP_CHAT_MSGREQ)
	{
		QString groupId = lastMsg->getSesssionId();
		st_GroupInfo groupInfo;
		TNUserDataHelper::GetInstance()->GetGroupInfo(groupId, groupInfo);
		session.title = groupInfo.GetName().toUtf8().data();
		session.myFeedId = groupInfo.GetMyFeedId().toUtf8().data();
		session.avatarId = groupInfo.GetHeaderImage().toUtf8().data();
	}
	else if (lastMsg->type == TYPE_NOTIFY_MSGREQ)
	{
		st_MessageAppInfoPtr messageAppInfo;
		TNUserDataHelper::GetInstance()->GetAppInfo(lastMsg->getSesssionId(), messageAppInfo);
		if (messageAppInfo.get() != NULL)
		{
			session.title = messageAppInfo->GetAppTitle().toUtf8().data();
			session.avatarId = messageAppInfo->GetAppLittleIcon().toUtf8().data();
		}
	}
	else if (lastMsg->type == TYPE_GROUP_NOTIFY_REQ)
	{
		st_FeedPtr feed;
		TNUserDataHelper::GetInstance()->GetFeedInfo(lastMsg->getSesssionId(), feed);
		if (feed.get() != NULL)
		{
			session.title = feed->GetTitle().toUtf8().data();
			session.avatarId = feed->GetAvatarID().toUtf8().data();
		}
	}
	else
		session.title = lastMsg->pushInfo.toUtf8().data();
	session.lastTime = lastMsg->timestamp;
	session.sortTime = lastMsg->timestamp;
	session.lastMsgId = lastMsg->msgId.toUtf8().data();
	session.lastMsg = lastMsg->pushInfo.toUtf8().data();
	session.lastMsgSendStatus = lastMsg->sendStatus;
	session.unreadCount = unReadCount;
	toonim::CTNSession oldSession = toonim::getChatDB()->getSession(session.sessionId.c_str());
	vector<CTNSession> sessionList;
	if (oldSession.sessionId.empty())
	{
		sessionList.push_back(session);
		toonim::getChatDB()->addSession(sessionList);
	}
	else
	{
		session.atMeMsgId = oldSession.atMeMsgId;
		session.topStatus = oldSession.topStatus;
		session.disturbStatus = oldSession.disturbStatus;
		session.draft = oldSession.draft;
		session.readSeqId = oldSession.readSeqId;
		sessionList.push_back(session);
		toonim::getChatDB()->updateSession(sessionList);
	}
		
	return;
}


//void TNIMCoreProcessor::ProcessHistoryMsg(Toon::OffMsgResp* historyMsgs)
//{
//	int32_t code = historyMsgs->code;
//	// code 0 成功 code 1 成功了 但是没有拉完
//	qInfo() << "[IMCore][TNIMCoreProcessor] :ProcessHistoryMsg begin";
//	if (code != 0 && code != 1) 
//	{
//		return;
//	}
//	TNCMessage* lastShowMsg = NULL;
//	qlonglong minSeqId = 0;
//	qlonglong minTimeStamp = 0;
//	qInfo() << "[IMCore][TNIMCoreProcessor] :ProcessHistoryMsg count " << historyMsgs->msgs.size();
//	for (int index = 0; index < historyMsgs->msgs.size(); index++)
//	{
//		Toon::OffMsgItem& offMsg = historyMsgs->msgs[index];
//		//处理断层，找到当前最小seqid,从原始消息取。
//		if (minSeqId == 0)
//			minSeqId = offMsg.item.seq_id;
//		if (minSeqId > offMsg.item.seq_id)
//		{
//			minSeqId = offMsg.item.seq_id;
//			minTimeStamp = offMsg.item.timestamp;
//		}
//
//		TNCMessage* msg = storageOneMsgFromIM(offMsg.type, &offMsg.item, false);
//		if (msg == NULL)
//			continue;
//		bool bLastCopy = false;
//		TNSessionItem* session = _sessionItems[msg->getSesssionId()];
//		if (ShouldShowMessage(msg))
//		{
//			//unreadCount
//			if (!session->bFinishReadCount)
//			{
//				if (session->readSeqId < msg->seqId && !msg->isMyself)
//				{
//					if (msg->type == TYPE_MSG_SINGLE_OPERATE || msg->type == TYPE_MSG_GROUP_OPERATE)
//					{
//						session->unReadCount--;
//					}
//					else
//						session->unReadCount++;
//				}
//			}
//			//find last msg
//			if (!session->bFinishLastMsg)
//			{
//				if (lastShowMsg == NULL)
//				{
//					lastShowMsg = msg;
//					bLastCopy = true;
//				}
//				else
//				{
//					if (msg->seqId > lastShowMsg->seqId)
//					{
//						delete lastShowMsg;
//						lastShowMsg = msg;
//						bLastCopy = true;
//					}
//				}
//			}
//			if (!session->bHasAtMeMsg)
//			{
//				if (msg->IsContaionMeAtFeeds(TNUserDataHelper::GetInstance()->_pluginParam->strTnUserID))
//				{
//					session->bHasAtMeMsg = true;
//					qInfo() << "[IMCore][TNIMCoreProcessor] hotsession hasAtMefeeds sessionId:" << session->sessionId << "msgId:" << msg->msgId;
//				}
//			}
//			
//		}
//		if (index ==  historyMsgs->msgs.size()-1)
//		{
//			if (!session->bFinishLastMsg && lastShowMsg)
//			{
//				storageSessioFromIM(lastShowMsg->type, 0, lastShowMsg);
//				session->bFinishLastMsg = true;
//				session->lastMsgId = lastShowMsg->msgId;
//			}
//			bool bFinishPull = false;
//			if (historyMsgs->msgs.size() < HISMSG_MAXNUM)
//				bFinishPull = true;
//			else if (session->downSeqId == minSeqId)
//				bFinishPull = true;
//
//			if (!session->bFinishReadCount && bFinishPull)
//			{
//				session->bFinishReadCount = true;
//				if (session->unReadCount < 0)
//					session->unReadCount = 0;
//				QString bHasAtMeMsg;
//				QString unReadCount = QString::number(session->unReadCount);
//				if (session->unReadCount> 0 && session->bHasAtMeMsg)
//					bHasAtMeMsg = QString::number(session->bHasAtMeMsg);
//				else
//					bHasAtMeMsg = QString::number(0);
//				TNDataControlServer::GetInstance()->UpdateSetValueByFieldEx("Session", "unreadCount", unReadCount, "sessionId", session->sessionId, "atMeStatus", bHasAtMeMsg, DBTYPE_MSG);
//			}
//			if (!bFinishPull)
//			{
//				//没拉全，需要再去拉取
//				requestUnDownLoadOffMsg(minSeqId, minTimeStamp, session->downSeqId, msg);
//			}
//			else
//			{
//				//销毁会话记录
//				QString sessionId = session->sessionId;
//				_sessionItems.remove(session->sessionId);
//				delete session;
//				//拉全通知ui刷新
//				QStringList sessionList;
//				sessionList.append(sessionId);
//				TNNotifyCenter::instance()->postNotifyRefresh(sessionList);
//			}
//			if (lastShowMsg)
//				delete lastShowMsg;
//		}
//		if (!bLastCopy)
//			delete msg;
//	}
//	qInfo() << "[IMCore][TNIMCoreProcessor] :ProcessHistoryMsg end";
//}

void TNIMCoreProcessor::ProcessSendMsgAck(QString& msgId, uint64_t seqId, int status)
{
	TableBaseVec messageVec;
	st_BMessage0Ptr message;
	TNDataControlServer::GetInstance()->Query(messageVec, "BMessage0", "msgId", msgId,DBTYPE_MSG);
	if (messageVec.size() > 0)
		message = std::dynamic_pointer_cast<st_BMessage0>(messageVec[0]);
	if (message)
	{
		TNCMessage tnmessage;
		MsgDbToMessage(message, tnmessage);
		if (message->GetType() == TYPE_GROUP_CHAT_MSGREQ || message->GetType() == TYPE_SINGLE_CHAT_MSGREQ)
		{
			QString strSeqId = QString::number(seqId);
			QString strStatus = QString::number(status);
			QMap<QString, QString> fieldMap;
			if (strSeqId !=  "0")
				fieldMap.insert("seqId", strSeqId);
			fieldMap.insert("status", QString::number(MSG_STATUS_FILE_SUC));
			if (status == 0)
				fieldMap.insert("sendStatus", QString::number(TNIMMessageSuccess));
			else
				fieldMap.insert("sendStatus", QString::number(TNIMMessageFailed));
			TNDataControlServer::GetInstance()->UpdateSetValueByFieldMap("BMessage0", fieldMap, "msgId", msgId,DBTYPE_MSG);
			TNNotifyCenter::instance()->postNotifyOnlineMsg(msgId, status == 0 ? TNIMMessageSuccess : TNIMMessageFailed);
		}
	}
}

void TNIMCoreProcessor::StartUpdateDbThread()
{
	_noticeUpdate->ProcessStartUpdateDb();
}
void TNIMCoreProcessor::UpdateOrgGroupAndRelation()
{
	_noticeUpdate->ProcessUpdateCompany();
}

QString TNIMCoreProcessor::genSessionIdFromServerMsg(Toon::OffMsgItem& msgItem)
{
	QString from = msgItem.item.from.c_str();
	QString to = msgItem.item.to.c_str();
	return TNCMessage::genSessionId((Toon_TMTP_TYPE)msgItem.type, from, to);
}
void TNIMCoreProcessor::UpdateFriendReMark(const QString &from, const QString &to)
{
	_noticeUpdate->ProcessUpdateRemark(from, to);
}
void TNIMCoreProcessor::synicOrgCommunication(int type, const QString&content)
{
	QVariantMap mapResp = TNIMUtil::jsonToMap(content);
	QString oFeed = mapResp["headFeed"].toString();
	_noticeUpdate->ProcessUpdateUI(CATALOG_STNC_ORGCOMMUNICATION, oFeed);
	qInfo() << "[IMCore][TNIMCoreProcessor]synicOrgCommunication,feed:" << oFeed;
}