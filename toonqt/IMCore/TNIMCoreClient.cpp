#include "TNIMCoreClient.h"
#include "ctnimclienttnmp.h"
#include "TNIMCoreProcessor.h"
#include "TNDataControlServer.h"
#include "tnimutil.h"
#include "TNUserDataHelper.h"
#include "TNNetDetecter.h"
#include "TMTPHostInfo.h"
#include "tnnotifycenter.h"
#include "TNUserVersionInfo.h"
#include "TNIMMsgManager.h"
#include "tnimagectr.h"
#include "TNDataControlServer.h"
#include "TNDebugLog.h"
#include "TNUserDataHelper.h"
#include "TNIMReadSessionManager.h"
#include "CTNDBAPI.h"
#include "TNDataCache.h"
TNIMCoreClient::TNIMCoreClient()
:_clientImpl(NULL), _userName(""), _userToken(""), _lastNetStatus(NetStatusNone)
, _netDetecter(NULL), _msgManager(NULL), _bLogined(false)
{
 	_netDetecter = new TNNetDetecter;
	connect(_netDetecter, SIGNAL(SendNetDetectStatus(NetStatus)), this, SLOT(onSendNetDetectStatus(NetStatus)));
	_netDetecter->DetectNetStatus();
}


TNIMCoreClient::~TNIMCoreClient()
{
	if (_clientImpl)
	{
		delete _clientImpl;
		_clientImpl = NULL;
	}
	if (_msgManager)
	{
		delete _msgManager;
		_msgManager = NULL;
	}
	if (_netDetecter)
	{
		delete _netDetecter;
		_netDetecter = NULL;
	}
	qDebug() << "[TNIMCoreClient]~TNIMCoreClient";
}

void TNIMCoreClient::InitIM(TNPluginParamPtr pluginParm)
{
	TNUserDataHelper::GetInstance()->Init(pluginParm);
	//增量更新版本数据缓存
	TNUserVersionInfo::GetInstance()->InitVesionMap();
	Init(pluginParm->strTnUserID, pluginParm->strMacAddress, pluginParm->str_api_imssl_systoon_com, pluginParm->str_api_im_systoon_com);
	//IMLogin(pluginParm->strMobile, pluginParm->strTnUserToken);
}

void TNIMCoreClient::Init(QString& userId, QString& deviceId, QString& hostSSL, QString& host)
{ 
	if (_clientImpl == NULL)
		_clientImpl = new CTNIMClientTNMP();
	if (_msgManager == NULL)
		_msgManager = new TNIMMsgManager();
	_clientImpl->setClientId(userId);
	_clientImpl->setDeviceId(deviceId);
	_clientImpl->InitIMSDK(_msgManager);
	AddIMServerAddr(hostSSL, true);
	AddIMServerAddr(host, false);
}

void TNIMCoreClient::AddIMServerAddr(QString& host, bool isSSL)
{
	QString ipHost = host.right(host.size() - host.indexOf("/") - 2);
	QStringList hostList = ipHost.split(":");
	TMTPHostInfo hostInfo;
	hostInfo.isSSL = isSSL;
	hostInfo.host = hostList[0].toUtf8().toStdString();
	if (hostList.size() > 1)
		hostInfo.port = hostList[1].toUtf8().toInt();
	_clientImpl->addHostInfo(hostInfo);
}

int TNIMCoreClient::IMLogin(QString& username, QString& userToken)
{
	ResetSendStatus();
	_userName = username;
	_userToken = userToken;
	_bLogined = true;
	return _clientImpl->login(username, userToken);
}

int TNIMCoreClient::IMLogout()
{
	_bLogined = false;
	bool bRet = _clientImpl->logout(true);
    _msgManager->waitAllMsgOver();
    return bRet;
}

int TNIMCoreClient::PreSaveIMMessage(TNMsgData* msgData, bool singChat)
{
	SendIMMessageInner(msgData, singChat, false);
	//if (_msgManager)
		//_msgManager->PreSaveMsgInThread(msgData, singChat);
	return 0;
}

int TNIMCoreClient::SendIMMessage(TNMsgData* msgData, bool singChat)
{
	if (msgData->from.isEmpty() || msgData->to.isEmpty())
	{
		qWarning() << "[IMCore][TNIMCoreClient]:SendIMMessage msgId" <<msgData->msgId <<"from " << msgData->from << "to" << msgData->to;
		TNNotifyCenter::instance()->postNotifyOnlineMsg(msgData->msgId, false);
		return -1;
	}
	if (msgData->bizType == MSG_BIZ_SINGLECHAT && msgData->toUserId.isEmpty())
	{
		qWarning() << "[IMCore][TNIMCoreClient]:SendIMMessage invalid toUserId";
		TNNotifyCenter::instance()->postNotifyOnlineMsg(msgData->msgId, false);
		return -1;
	}
	if (_msgManager)
		_msgManager->SendMsgInThread(msgData, singChat);
	return 0;
}

int TNIMCoreClient::SendForwardMessage(TNMsgData* msgData, QMap<QString, QString>& feedList)
{
	if (_msgManager)
		_msgManager->SendForwardMsgInThread(msgData, feedList);
	return 0;
}

int TNIMCoreClient::SendForwardMessageInner(TNMsgData* msgData, QMap<QString, QString>& feedList)
{
	if (msgData == NULL)
		return -1;
	TNCMessage message;
	GetTNCMessage(msgData, message);
	for (QMap<QString, QString>::iterator msgIter = feedList.begin(); msgIter != feedList.end(); msgIter++)
	{
		message.SetSessionId(QString(""));
		QString toFeedId = msgIter.key();
		message.to = toFeedId;
		if (toFeedId.indexOf("gc_") == 0)
			message.type = TYPE_GROUP_CHAT_MSGREQ;
		else
			message.type = TYPE_SINGLE_CHAT_MSGREQ;
		if (message.type == TYPE_SINGLE_CHAT_MSGREQ)
		{
			st_FeedPtr feedInfo;
			TNUserDataHelper::GetInstance()->GetFeedInfo(toFeedId, feedInfo);
			if (feedInfo)
				message.toUserId = feedInfo->GetUserID();
		}
		else
			message.toUserId = "";
		QString msgId = msgIter.value();
		if (msgId.isEmpty())
			message.msgId = TNIMUtil::getUUID();
		else
			message.msgId = msgId;
		SendIMMessage(&message, message.toUserId);
	}
    return 0;
}


int TNIMCoreClient::SendIMMessageInner(TNMsgData* msgData, bool singChat, bool bSend)
{
	if (msgData == NULL)
		return -1;
	qInfo() << "[IMCore][TNIMCoreClient] SendIMMessageInner" << "msgId:" << msgData->msgId << "from" << msgData->from << "to" << msgData->to;
	TNCMessage message;
	GetTNCMessage(msgData, message, singChat);
	SendIMMessage(&message, msgData->toUserId, bSend);
	return 0;

}

void TNIMCoreClient::GetTNCMessage(TNMsgData* msgData, TNCMessage& message, bool singChat)
{
	if (msgData == NULL)
		return;
	message.msgId = msgData->msgId;
	//业务类型
	if (singChat)
		message.type = TYPE_SINGLE_CHAT_MSGREQ;
	else
		message.type = TYPE_GROUP_CHAT_MSGREQ;
	message.timestamp = TNIMUtil::getCurrentTime();
	message.from = msgData->from;
	message.to = msgData->to;
	message.toUserId = msgData->toUserId;
	message.isMyself = true;
	message.atType = msgData->atType;
	message.atFeeds = msgData->atFeeds;
	message.sendStatus = (TNIMMessageSendStatus)msgData->status;
	message.fileStatus = msgData->fileStatus;
	st_FeedPtr feedInfo;
	TNUserDataHelper::GetInstance()->GetFeedInfo(msgData->from, feedInfo);
	if (feedInfo)
		message.senderName = feedInfo->GetTitle();

	message.contentType = (TNMessageContentType)msgData->type;
	if (msgData->type == MSG_TYPE_TEXT)
	{
		TNMessageBodyText* body = new TNMessageBodyText();
		body->setText(msgData->data);
		message.pushInfo = body->getAbstractText();
		message.setBody(body);
	}
	else if (msgData->type == MSG_TYPE_IMG)
	{
		TNMessageBodyImage* body = new TNMessageBodyImage();
		body->setHeight(msgData->h);
		body->setWdith(msgData->w);
		body->setUrl(msgData->data);
		if (msgData->format.isEmpty())
		{
			QString suffix = TNImageCtr::getImageTypeRetString(msgData->localPath);
			body->setSuffix(suffix);
		}
		else
			body->setSuffix(msgData->format);
		if (msgData->format == GifImgSuffix)
			message.contentType = (TNMessageContentType)MSG_TYPE_GIFIMG;
		message.pushInfo = body->getAbstractText();
		message.setBody(body);
	}
	else if (msgData->type == MSG_TYPE_ATTACHMENT)
	{
		TNMessageBodyAttachment *body = new TNMessageBodyAttachment();
		QString fileName = msgData->desc;
		QString ext = fileName.right(fileName.size() - fileName.lastIndexOf("."));
		body->setUrl(msgData->data);
		body->setSuffix(ext);
		body->setSize(msgData->size);
		body->setDesc(msgData->desc);
		body->setFormat(TNIMUtil::GetFileFormat(ext));
		message.pushInfo = body->getAbstractText();
		message.setBody(body);
	}
	//生成topic
	message.localPath = msgData->localPath;
	message.getTopic();
	//if (msgData->status == MSG_STATUS_UPLOAD_FAIL)
	//{
	//	_msgProcessor->SaveMsgToDB(&message);
	//	return;
	//}
}

int TNIMCoreClient::SendRevokeMessage(TNRevokeData* msgData, bool singChat)
{
	if (msgData->from.isEmpty() || msgData->to.isEmpty())
	{
		qInfo() << "[IMCore][TNIMCoreClient]:SendRevokeMessage msgId" << msgData->msgId << "from " << msgData->from << "to" << msgData->to;
		return -1;
	}
	if (_msgManager)
		_msgManager->SendRevertMsgInThread(msgData, singChat);
	return 0;
}

int TNIMCoreClient::SendRevokeMessageInner(TNRevokeData* msgData, bool singChat)
{
	if (msgData == NULL)
		return -1;
	TNCMessage message;
	message.msgId = msgData->msgId;
	//业务类型
	if (singChat)
		message.type = TYPE_MSG_SINGLE_OPERATE;
	else
		message.type = TYPE_MSG_GROUP_OPERATE;
	message.timestamp = TNIMUtil::getCurrentTime();
	message.from = msgData->from;
	message.to = msgData->to;
	message.toUserId = msgData->toUserId;
	message.isMyself = true;
	message.catalogId = OPERATE_TYPE_REVOKE;
	message.msgOpId = msgData->opMsgId;
	//撤销类型
	QVariantMap bizMap;
	bizMap["catalogId"] = QVariant(OPERATE_TYPE_REVOKE);
	bizMap["operatorFeedId"] = QVariant(msgData->opFeedId);
	bizMap["operatorName"] = QVariant(msgData->opName);
	bizMap["msgId"] = QVariant(msgData->opMsgId);
	message.setContent(TNIMUtil::mapToJson(bizMap));
	SendIMMessage(&message, message.toUserId);
	return 0;
}

bool TNIMCoreClient::GetReadSessionData(QString sessionId, TNReadSession& readSession)
{
	toonim:CTNSession imSession = toonim::getChatDB()->getSession(sessionId.toUtf8().data());
	if (!imSession.sessionId.empty())
	{
		//lastmsg
		toonim::CTNMessage lastMessage = toonim::getChatDB()->getMessage(imSession.sessionId.c_str(), imSession.lastMsgId.c_str());
		if (!lastMessage.msgId.empty())
		{
			if (lastMessage.type == MSG_BIZ_SINGLECHAT || lastMessage.type == MSG_BIZ_SINGLECHAT_REVERT)
			{
				if (lastMessage.isMyself)
				{
					readSession.from = lastMessage.fromId.c_str();
					readSession.to = lastMessage.toId.c_str();
				}
				else
				{
					readSession.from = lastMessage.toId.c_str();
					readSession.to = lastMessage.fromId.c_str();
				}
			}
			else if (lastMessage.type == TYPE_NOTIFY_MSGREQ || lastMessage.type == TYPE_GROUP_NOTIFY_REQ)
			{
				readSession.from = imSession.sessionId.c_str();
				readSession.to = "";
			}
			else
			{
				readSession.from = imSession.myFeedId.c_str();
				readSession.to = imSession.sessionId.c_str();
			}
			readSession.type = imSession.type;
			readSession.readSeqId = _msgManager->GetIMProcessor()->GetLocalMaxSeqId(sessionId);
			return true;
		}
	}
	qWarning() << "[IMCore][TNIMCoreClient] GetReadSessionData error sessionId:" << sessionId;
	return false;
}


void TNIMCoreClient::SendReadSessionInner(QString readSessionId)
{
	//客户端已读
	toonim::getChatDB()->markSessionRead(readSessionId.toUtf8().data());
	_clientImpl->reqSyncReadSession(readSessionId);
}

void TNIMCoreClient::ReadSessionLocal(const QString& sessionId)
{
	toonim::getChatDB()->markSessionRead(sessionId.toUtf8().data());
}


void TNIMCoreClient::ReadSession(const QString& sessionId)
{	
	if (_msgManager)
		_msgManager->SendSyncReadSessionInThread(sessionId);
}

void TNIMCoreClient::RemoveAndReadSession(const QString& sessionId)
{
	if (_msgManager)
		_msgManager->SendSyncReadSessionInThread(sessionId, true);
}


int TNIMCoreClient::SendIMMessage(TNCMessage* message, QString toClientId, bool bSend)
{
	//消息预存，回执update状态。
	qInfo() << "[IMCore][TNIMCoreClient] GetLocalMaxSeqId";
	qlonglong localMaxSeqId = _msgManager->GetIMProcessor()->GetLocalMaxSeqId(message->getSesssionId());
	message->seqId = localMaxSeqId + 1;
	message->sendStatus = TNIMMessageSending;
	if (message->type != MSG_BIZ_SINGLECHAT_REVERT && message->type != MSG_BIZ_GROUPCHAT_REVERT)
		_msgManager->GetIMProcessor()->PreSaveSendMsg(message);
	if (!bSend)
		return 0;

	if (message->type == MSG_BIZ_SINGLECHAT || message->type == MSG_BIZ_SINGLECHAT_REVERT)
	{
		//组织名片不可沟通服务器做判断
		/*if (message->from.startsWith(OrgCardPre))
		{
		if (!TNDataCache::GetInstance()->getOrgCommunicationStatus(message->from))
		{
		message->sendStatus = TNIMMessageFailedOrCard;
		toonim::getChatDB()->updateSendStatus(message->msgId.toUtf8().data(), message->getSesssionId().toUtf8().data(), message->sendStatus);
		TNNotifyCenter::instance()->postNotifyOnlineMsg(message->msgId, message->sendStatus);
		return -1;
		}
		}
		if (message->to.startsWith(OrgCardPre))
		{
		if (!TNUserDataHelper::GetInstance()->GetOrgCommStatus(message->to))
		{
		message->sendStatus = TNIMMessageFailedOrCard;
		toonim::getChatDB()->updateSendStatus(message->msgId.toUtf8().data(), message->getSesssionId().toUtf8().data(), message->sendStatus);
		TNNotifyCenter::instance()->postNotifyOnlineMsg(message->msgId, message->sendStatus);
		return -1;
		}
		}*/
		bool bFeedStatus, bBelongStatus;
		bFeedStatus = TNUserDataHelper::GetInstance()->GetNativeCardStatus(message->from);
		bBelongStatus = TNUserDataHelper::GetInstance()->GetNativeCardStatus(message->to);
		if (!bFeedStatus || !bBelongStatus)
		{
			qWarning() << "[IMCore][TNIMCoreClient]:feed status:" << bFeedStatus << "belongStatus:" << bBelongStatus;
			if (!bFeedStatus)
			{
				if (message->from.startsWith(UserCardPre))
					message->sendStatus = TNIMMessageFailedCard;
				else
					message->sendStatus = TNIMMessageFailedCoCard;
			}
			else if (!bBelongStatus)
			{ 
				if (message->to.startsWith(UserCardPre))
					message->sendStatus = TNIMMessageFailedCard;
				else
					message->sendStatus = TNIMMessageFailedCoCard;
			}
		}
	}
	else if (message->type == MSG_BIZ_GROUPCHAT || message->type == MSG_BIZ_GROUPCHAT_REVERT)
	{
		if (!TNUserDataHelper::GetInstance()->GetNativeCardStatus(message->from))
		{
			qWarning() << "[IMCore][TNIMCoreClient]: groupchat status: failed";
			if (message->from.startsWith(UserCardPre))
				message->sendStatus = TNIMMessageFailedCard;
			else
				message->sendStatus = TNIMMessageFailedCoCard;
		}
	}
	if (message->sendStatus != TNIMMessageSending)
	{
		toonim::getChatDB()->updateSendStatus(message->msgId.toUtf8().data(), message->getSesssionId().toUtf8().data(), message->sendStatus);
		TNNotifyCenter::instance()->postNotifyOnlineMsg(message->msgId, message->sendStatus);
		return -1;
	}
	qInfo() << "[IMCore][TNIMCoreClient]: send message to IM server msgId= " << message->msgId;
	_clientImpl->sendMessage(message, toClientId);
	return 0;
}

TNIMCoreClient* TNIMCoreClient::GetIMClient()
{
	static TNIMCoreClient* s_client = NULL;
	if (s_client == NULL)
		s_client = new TNIMCoreClient;
	return s_client;
}

void TNIMCoreClient::DestoryIMClient()
{
	TNIMCoreClient* client = GetIMClient();
	delete client;
}

void TNIMCoreClient::IMMessageCastToData(const CTNMessage& imMessage, st_MsgData& data)
{
	data.msgId = imMessage.msgId.c_str();
	data.sessionId = imMessage.sessionId.c_str();
	data.from = imMessage.fromId.c_str();
	data.senderName = imMessage.senderName.c_str();
	data.to = imMessage.toId.c_str();
	data.timestmp = imMessage.timestamp;
	data.bizType = (MSG_BIZ_TYPE)imMessage.type;

	if (imMessage.type == TYPE_MSG_SINGLE_OPERATE || imMessage.type == TYPE_MSG_GROUP_OPERATE)
	{
		data.type = MSG_TYPE_NOTICE;
		data.data = imMessage.pushInfo.c_str();
	}
	else
		ParseContextToMsgData(imMessage.content.c_str(), imMessage.contentType, data);
	data.toUserId = imMessage.toClientId.c_str();
	if (imMessage.type == TYPE_GROUP_CHAT_MSGREQ && imMessage.catalogId != 0)
	{
		data.bShow = TNIMCoreProcessor::ShouldShowSyncMsg(imMessage.catalogId, imMessage.content.c_str());
	}
	else
		data.bShow = true;
	data.bIsMyself = imMessage.isMyself;
	if (imMessage.sendStatus == TNIMMessageFailed)
		data.bSendSuc = false;
	else
		data.bSendSuc = true;
	QVariantMap addition = TNIMUtil::jsonToMap(imMessage.addition.c_str());
	QVariantMap::Iterator iterFind = addition.find(ADDTION_LOCALPATH);
	if (iterFind != addition.end())
		data.localPath = iterFind.value().toString();
	if (data.url.isEmpty())
	{
		if (data.fileStatus == MSG_STATUS_FILE_SUC)
		{
			iterFind = addition.find(ADDTION_URL);
			if (iterFind != addition.end())
				data.url = iterFind.value().toString();

		}
	}
	data.status = (TNMsgStatus)imMessage.sendStatus;
	data.fileStatus = (TNMsgFileStatus)addition[ADDTION_FILE_STATUS].toInt();
	if (data.fileStatus == MSG_STATUS_FILE_READED)
		data.readed = 1;
	else
		data.readed = 0;
}

void TNIMCoreClient::IMSessioniCastToData(const CTNSession& imMessage, st_Session& data)
{
	data.SetSessionId(imMessage.sessionId.c_str());
	if (imMessage.atMeMsgId.length() == 0)
		data.SetAtMeStatus(false);
	else
		data.SetAtMeStatus(true);
	data.SetTitle(imMessage.title.c_str());
	data.SetLastMsgId(imMessage.lastMsgId.c_str());
	data.SetLastMsg(imMessage.lastMsg.c_str());
	data.SetUnreadCount(imMessage.unreadCount);
	data.SetAvatarId(imMessage.avatarId.c_str());
	data.SetDraft(imMessage.draft.c_str());
	data.SetMyFeedId(imMessage.myFeedId.c_str());
	data.SetLastTime(imMessage.lastTime);
	data.SetLastMsgSendStatus(imMessage.lastMsgSendStatus);
	data.SetSortTime(imMessage.sortTime);
	data.SetTopic(imMessage.topic.c_str());
	data.SetTopStatus(imMessage.topStatus);
	data.SetType(imMessage.type);
}


void TNIMCoreClient::MessageCastToData(const st_BMessage0Ptr bmessage, st_MsgData& data)
{
	data.msgId = bmessage->GetMsgId();
	data.sessionId = bmessage->GetSessionId();
	data.from = bmessage->GetFromId();
	data.to = bmessage->GetToId();
	data.timestmp = bmessage->GetTimestamp();
	if (bmessage->GetStatus() == MSG_STATUS_FILE_READED)
		data.readed = 1;
	else
		data.readed = 0;
	if (bmessage->GetType() == TYPE_MSG_SINGLE_OPERATE || bmessage->GetType() == TYPE_MSG_GROUP_OPERATE)
	{
		data.type = MSG_TYPE_NOTICE;
		data.data = bmessage->GetPushInfo();
	}
	else
		ParseContextToMsgData(bmessage->GetContent(  ), bmessage->GetContentType(), data);
	data.localPath = bmessage->GetFileFormat();
	data.toUserId = bmessage->GetToClientId();
	if (bmessage->GetType() == TYPE_GROUP_CHAT_MSGREQ && bmessage->GetCatalogId() != 0)
	{
		data.bShow = TNIMCoreProcessor::ShouldShowSyncMsg(bmessage->GetCatalogId(), bmessage->GetContent());
	}
	else
		data.bShow = true;
	data.bIsMyself = bmessage->GetIsMyself();
	if (bmessage->GetSendStatus() == TNIMMessageFailed)
		data.bSendSuc = false;
	else
		data.bSendSuc = true;
	data.status = (TNMsgStatus)bmessage->GetSendStatus();
	data.fileStatus = (TNMsgFileStatus)bmessage->GetStatus();
	if (data.url.isEmpty())
	{
        if (data.fileStatus == MSG_STATUS_FILE_SUC)
			data.url = bmessage->GetCatalog();
	}
	
}

void TNIMCoreClient::ParseContextToMsgData(const QString& content, int type, TNMsgData& data)
{
	static int needTypes[] = { 1, 2, 3, 7, 10, 12, 14, 16, IM_REVOKE_TYPE };
	bool bNeedProcess = false;
    for(int i = 0; i < 9; i++)
	{
		if (needTypes[i] == type)
		{
			bNeedProcess = true;
			break;
		}
	}
	if (bNeedProcess)
	{
		if (type == IM_REVOKE_TYPE)
			data.type = MSG_TYPE_NOTICE;
		else
			data.type = (MSG_TYPE)type;
	}
	else
		data.type = MSG_TYPE_OTHER; 
	if (data.type == MSG_TYPE_OTHER || data.type == MSG_TYPE_NOTICE)
		data.bIsBubble = false;
	else
		data.bIsBubble = true;
	QVariantMap context = TNIMUtil::jsonToMap(content);
	if (data.type == MSG_TYPE_TEXT || data.type == MSG_TYPE_NOTICE)
	{
		QVariant subContext = context["attributedText"];
		if (data.type == MSG_TYPE_TEXT || !subContext.isValid() || subContext.type() != QVariant::List)
		{
			data.data = context["text"].toString();
		}
		else
		{
			QString msgContent;
			for (QVariant contentItem : subContext.toList())
			{
				if (contentItem.type() != QVariant::Map)
				{
					data.data = context["text"].toString();
					break;
				}
				QString contentType = contentItem.toMap()["type"].toString();
				QString strContentItem = contentItem.toMap()["content"].toString();
				if (contentType.toInt() == 0)
				{
					//数据不变
					msgContent += strContentItem;
				}
				else if (contentType.toInt() == 1)
				{
					//替换feedname
					QStringList feedList = strContentItem.split(",");
					QString feedContent;
					for (int index = 0; index < feedList.size(); index++)
					{
						if (TNDataCache::GetInstance()->IsInMyStuff(feedList[index]))
							feedContent += QStringLiteral("你");
						else
						{
							//群聊通知from都是自己
							QString FriendRemark = TNDataCache::GetInstance()->getFriendFeedReMark(feedList[index], data.from);
							if (FriendRemark.isEmpty())
							{
								st_FeedPtr feedInfo;
								TNUserDataHelper::GetInstance()->GetFeedInfo(feedList[index], feedInfo);
								if (feedInfo)
									feedContent += feedInfo->GetTitle();
							}
							else
								feedContent += FriendRemark;
						}
						if (index != feedList.size() -1)
							feedContent += "、";
					}
					msgContent += feedContent;
				}
				data.data = msgContent;
			}
		}
	}
	else if (data.type == MSG_TYPE_IMG || data.type == MSG_TYPE_ATTACHMENT || data.type == MSG_TYPE_VOICE || data.type == MSG_TYPE_VIDEO)
	{
		data.url = context["url"].toString();
		data.data = data.url;
		if (data.type == MSG_TYPE_IMG)
		{
			data.w = context["w"].toInt();
			data.h = context["h"].toInt();
			data.format = context["suffix"].toString();
		}
		else if (data.type == MSG_TYPE_ATTACHMENT)
		{
			data.desc = context["desc"].toString();
			data.size = context["size"].toInt();
			data.format = context["format"].toString();
		}
		else if (data.type == MSG_TYPE_VOICE)
			data.time = context["time"].toInt();
		else if (data.type == MSG_TYPE_VIDEO)
		{
			data.w = context["w"].toInt();
			data.h = context["h"].toInt();
			data.time = context["time"].toInt();
			data.size = context["size"].toInt();
			data.desc = QStringLiteral("[视频]");
		}
	}
	else if (data.type == MSG_TYPE_GIFIMG)
	{
		data.url = context["url"].toString();
		data.data = data.url;
		data.format = GifImgSuffix;
		data.w = GifSize;
		data.h = GifSize;
	}
	else if (data.type == MSG_TYPE_RED_CARD)
	{
		//todo 
		data.url = context["url"].toString();
		data.data = context["name"].toString();
	}
	if (data.type == MSG_TYPE_GIFIMG)
		data.type = MSG_TYPE_IMG;
}


QString TNIMCoreClient::GetSessionId(const QString& from,const QString& to, MSG_BIZ_TYPE type)
{
	return TNCMessage::genSessionId((Toon_TMTP_TYPE)type, from, to);
}

QString TNIMCoreClient::GetMsgId()
{
	return TNIMUtil::getUUID();
}

ITnImDBChat* TNIMCoreClient::GetDBChat()
{
	return getChatDB();
}

void TNIMCoreClient::RequestOffMsg(TNOffMsg& offMsg)
{
	Toon::SessionName session;
	session.from = offMsg.from.toUtf8().toStdString();
	session.to = offMsg.to.toUtf8().toStdString();
	session.type = offMsg.type;
	Toon::PullOffMsgReq offReq;
	offReq.req_id = TNIMUtil::getUUID().toUtf8().data();
	offReq.up_seq_id = offMsg.maxSeqId;
	offReq.down_seq_id = offMsg.minSeqId;
	offReq.limit_count = offMsg.count;
	offReq.timestamp = offMsg.maxTimeStamp;
	offReq.priority = 2;
	offReq.session_name = session;
	qInfo() << "[IMCore][TNIMCoreClient]:reqHistoryMessage" << "from:" << offMsg.from << "to:" << offMsg.to << "maxseqid:" << offMsg.maxSeqId << "count:" << offMsg.count;
	//_clientImpl->reqOffMessage(offReq);
}

MSG_BIZ_TYPE TNIMCoreClient::GetSessionType(const st_SessionPtr session, st_MessageAppInfoPtr& appInfo)
{
	if (session->GetType() == TYPE_SINGLE_CHAT_MSGREQ || session->GetType() == TYPE_MSG_SINGLE_OPERATE)
		return MSG_BIZ_SINGLECHAT;
	else if (session->GetType() == TYPE_GROUP_CHAT_MSGREQ || session->GetType() == TYPE_MSG_GROUP_OPERATE)
		return MSG_BIZ_GROUPCHAT;
	else if (session->GetType() == TYPE_NOTIFY_MSGREQ)
	{
		TNUserDataHelper::GetInstance()->GetAppInfo(session->GetSessionId(), appInfo);
		return MSG_BIZ_NOTIFY;
	}
	else if (session->GetType() == TYPE_GROUP_NOTIFY_REQ)
	{
		return MSG_BIZ_NOTIFY;
	}
	return MSG_BIZ_UNSHOW;
}


MSG_BIZ_TYPE TNIMCoreClient::GetSessionType(const CTNSession* session)
{
	if (session->type == TYPE_SINGLE_CHAT_MSGREQ || session->type == TYPE_MSG_SINGLE_OPERATE)
		return MSG_BIZ_SINGLECHAT;
	else if (session->type == TYPE_GROUP_CHAT_MSGREQ || session->type == TYPE_MSG_GROUP_OPERATE)
		return MSG_BIZ_GROUPCHAT;
	else if (session->type == TYPE_NOTIFY_MSGREQ)
	{
		return MSG_BIZ_NOTIFY;
	}
	else if (session->type == TYPE_GROUP_NOTIFY_REQ)
	{
		return MSG_BIZ_NOTIFY;
	}
	return MSG_BIZ_UNSHOW;
}

void TNIMCoreClient::GetNoticeListFromSessionId(QList<st_NoticeInfo>& noticeList, const QString& sessionId, qlonglong seqId, int msgCount)
{
    noticeList.clear();
	vector<CTNMessage> messageVec = toonim::getChatDB()->getMessages(sessionId.toUtf8().data(), seqId, msgCount);
    QMap<QString, st_NoticeInfo> bizMap;
	for (vector<CTNMessage>::iterator iter = messageVec.begin(); iter != messageVec.end(); iter++)
    {
		CTNMessage message = *iter;
		if(!TNIMNoticeProcessor::GetInstance().ShouldShowNotice(&message))
			continue;
        st_NoticeInfo noticeInfo;
        TNIMNoticeProcessor::IMMessageCastToNotice(&message, noticeInfo);
        if (!noticeInfo.bizId.isEmpty())
        {
            if (!bizMap.contains(noticeInfo.bizId))
            {
                bizMap.insert(noticeInfo.bizId, noticeInfo);
            }
        }
    }
    qDebug()<<"GetNoticeListFromSessionId-bizMap.keys="<<bizMap.keys();
	noticeList.append(bizMap.values());
}

bool TNIMCoreClient::SaveDraft(const QString& sessionId, const QString& strDraft)
{
	toonim::CTNSession session = toonim::getChatDB()->getSession(sessionId.toUtf8().data());
	session.draft = strDraft.toUtf8().data();
    session.lastTime = QDateTime::currentDateTime().toTime_t();
	vector<toonim::CTNSession> sessionList;
	sessionList.push_back(session);
	return toonim::getChatDB()->updateSession(sessionList);
}

void TNIMCoreClient::ReadMsg(const QString& msgId, QString sessionId)
{
	toonim::CTNMessage message = toonim::getChatDB()->getMessage(sessionId.toUtf8().data(), msgId.toUtf8().data());
	QVariantMap addition = TNIMUtil::jsonToMap(message.addition.c_str());
	addition[ADDTION_FILE_STATUS] = MSG_STATUS_FILE_READED;
	message.addition = TNIMUtil::mapToJson(addition).toUtf8().data();
	toonim::getChatDB()->updateMessage(message);
}

void  TNIMCoreClient::UpdateAddressBookFromServer()
{
	if (_msgManager)
		_msgManager->GetIMProcessor()->StartUpdateDbThread();
}

void TNIMCoreClient::ResetSendStatus()
{
	//TNDataControlServer::GetInstance()->UpdateSetValueByField("BMessage0", "sendStatus", QString::number(TNIMMessageFailed), "sendStatus", QString::number(TNIMMessageSending), DBTYPE_MSG);
	//TNDataControlServer::GetInstance()->UpdateSetValueByField("BMessage0", "status", QString::number(MSG_STATUS_FILE_UPLOAD_FAIL), "status", QString::number(MSG_STATUS_FILE_UPLOADING), DBTYPE_MSG);
	//TNDataControlServer::GetInstance()->UpdateSetValueByField("BMessage0", "status", QString::number(MSG_STATUS_FILE_DOWN_FAIL), "status", QString::number(MSG_STATUS_FILE_DOWNLOADING), DBTYPE_MSG);
}

void TNIMCoreClient::SetMsgFileStatus(const QString &msgId,const QString& sessionId,TNMsgFileStatus fileStatus,QString upUrlPath,bool bUpSuc)
{
    Q_ASSERT(!msgId.isEmpty() && !sessionId.isEmpty());
	toonim::CTNMessage message = toonim::getChatDB()->getMessage(sessionId.toUtf8().data(), msgId.toUtf8().data());
	QVariantMap addition = TNIMUtil::jsonToMap(message.addition.c_str());
	addition[ADDTION_FILE_STATUS] = fileStatus;
	if (fileStatus == MSG_STATUS_FILE_SUC){
		if (bUpSuc)
			addition[ADDTION_URL] = upUrlPath;
		else
			addition[ADDTION_LOCALPATH] = upUrlPath;
    }
	message.addition = TNIMUtil::mapToJson(addition).toUtf8().data();
	toonim::getChatDB()->updateMessage(message);
}

void TNIMCoreClient::SetMsgSendStatus(const QString& msgId, const QString& sessionId, TNMsgStatus sendStatus)
{
	toonim::getChatDB()->updateSendStatus(msgId.toUtf8().data(), sessionId.toUtf8().data(), sendStatus);
}


void TNIMCoreClient::onSendNetDetectStatus(NetStatus status)
{
	if (status == NetStatusConnect)
	{
		if (_lastNetStatus == NetStatusDisconnect && _bLogined)
		{
			qInfo() << "[IMCore][TNIMCoreClient] netdetecter loginIM";
			IMLogout();
			IMLogin(_userName, _userToken);
		}
	}
	else if (status == NetStatusDisconnect)
	{
		/*if (_lastNetStatus == NetStatusConnect)
		{

		}*/
	}
	_lastNetStatus = status;
	TNNotifyCenter::instance()->postNotifyNetStatus(status);
}
void TNIMCoreClient::UpdateOrgGroupAndRelationSlots()
{
	if (_msgManager)
		_msgManager->GetIMProcessor()->UpdateOrgGroupAndRelation();
}

void TNIMCoreClient::SynicGroupChatMember(QString strGroupId)
{
	if (_msgManager)
		_msgManager->GetIMProcessor()->SynicGroupChatMember(strGroupId);
}

void TNIMCoreClient::SynicGroupChat()
{
	if (_msgManager)
		_msgManager->GetIMProcessor()->SynicGroupChat();
}

void TNIMCoreClient::UpdateFriendReMarkSlots(const QString &from, const QString &to)
{
	if (_msgManager)
		_msgManager->GetIMProcessor()->UpdateFriendReMark(from,to);
}

void TNIMCoreClient::BMessageCastToIMMessage(const st_BMessage0Ptr bmessage, CTNMessage& imMessage)
{
	if (!bmessage)
		return;
	imMessage.sessionId = bmessage->GetSessionId().toUtf8().data();
	imMessage.msgId = bmessage->GetMsgId().toUtf8().data();
	imMessage.type = (Toon_TMTP_TYPE)bmessage->GetType();
	imMessage.seqId = bmessage->GetSeqId();
	imMessage.fromId = bmessage->GetFromId().toUtf8().data();
	imMessage.fromClientId = bmessage->GetFormClientId().toUtf8().data();
	imMessage.toClientId = bmessage->GetToClientId().toUtf8().data();
	imMessage.toId = bmessage->GetToId().toUtf8().data();
	imMessage.timestamp = bmessage->GetTimestamp();
	imMessage.pushInfo = bmessage->GetPushInfo().toUtf8().data();
	imMessage.expireTime = bmessage->GetExpireTime();
	imMessage.sendStatus = bmessage->GetSendStatus();
	imMessage.priority = bmessage->GetPriority();
	imMessage.catalogId = bmessage->GetCatalogId();
	//imMessage.catalog = bmessage->GetCatalog();//local path
	imMessage.contentType = bmessage->GetContentType();
	imMessage.content = bmessage->GetContent().toUtf8().data();
	imMessage.isMyself = bmessage->GetIsMyself();
	imMessage.senderName = bmessage->GetSenderName().toUtf8().data();

	QVariantMap addtion;
	if(imMessage.type == TYPE_SINGLE_CHAT_MSGREQ || imMessage.type == TYPE_GROUP_CHAT_MSGREQ)
		addtion[ADDTION_LOCALPATH] = bmessage->GetCatalog().toUtf8().data();
	addtion[ADDTION_FILE_STATUS] = bmessage->GetStatus();
	addtion[ADDTION_URL] = bmessage->GetFileFormat();
	imMessage.addition = TNIMUtil::mapToJson(addtion).toUtf8().data();
}

void TNIMCoreClient::BSessionCastToIMSession(const st_SessionPtr bSession, CTNSession& imSession)
{
	if (!bSession)
		return;

	imSession.sessionId = bSession->GetSessionId().toUtf8().data();
	imSession.topic = bSession->GetTopic().toUtf8().data();

	imSession.myFeedId = bSession->GetMyFeedId().toUtf8().data();
	imSession.type = bSession->GetType();
	imSession.title = bSession->GetTitle().toUtf8().data();
	imSession.avatarId = bSession->GetAvatarId().toUtf8().data();

	imSession.draft = bSession->GetDraft().toUtf8().data();
	imSession.lastTime = bSession->GetLastTime();
	imSession.lastMsg = bSession->GetLastMsg().toUtf8().data();
	imSession.lastMsgId = bSession->GetLastMsgId().toUtf8().data();

	imSession.lastMsgSendStatus = bSession->GetLastMsgSendStatus();
	//imSession.sortTime = bSession->GetSortTime();使用旧表的LastTime
	imSession.sortTime = bSession->GetLastTime();
	imSession.atMeMsgId = bSession->GetAtMeStatus();

	imSession.unreadCount = bSession->GetUnreadCount();
	imSession.topStatus = bSession->GetTopStatus();
}
