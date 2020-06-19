#include "TNIMSDKClient.h"
#include <QDebug>
#include "TNIMMsgManager.h"
#include "tnnotifycenter.h"
#include "tnmessagebody.h"
#include "TNIMReadSessionManager.h"
#include "tnimutil.h"
#include "CTNDBAPI.h"
#include "TNUserDataHelper.h"
#define SERVER_ORG_CODE		8  //组织名片不可沟通
TNIMSDKClient::TNIMSDKClient(TNIMMsgManager* msgManager) :_msgManager(msgManager)
{

}

TNIMSDKClient::~TNIMSDKClient()
{

}

void TNIMSDKClient::netStatusChanged(int32_t status)
{
	//0 断开，
	qInfo() << "[IMCore][CTNIMClientTNMP]netStatusChanged:" << status;
}

void TNIMSDKClient::loginResp(int32_t code, vector<int32_t>& contentTypes)
{
	qInfo() << "[IMCore][TNIMSDKClient]loginResp:" << code;
	switch (code)
	{
		case Toon::CONNECT_RESULT_SUCCESS:
		{
			break;
		}
		case Toon::CONNECT_RESULT_SERVICE_UNAVAILABLE:
		case Toon::CONNECT_RESULT_ERROR_PROTOCOL:
		case Toon::CONNECT_RESULT_ERROR_INDICATE:
		case Toon::CONNECT_RESULT_ERROR_USERNAME_OR_PASSWORD:
		case Toon::CONNECT_RESULT_KICKOUT:
		case Toon::CONNECT_RESULT_OTHER:
		default:
		{
			//需要增加通知，通知UI 退回到登陆UI
			TNNotifyCenter::instance()->postNotifyNetStatus(TNMPNetKickout);
			break;
		}
	}
}

void TNIMSDKClient::kickOut()
{
	TNNotifyCenter::instance()->postNotifyNetStatus(TNMPNetKickout);
}

void TNIMSDKClient::hotSessionResp(set<CTNOffMessageResult> &sessionSet)
{
	processOffLineSession(sessionSet);
}

void TNIMSDKClient::offMsgResp(set<CTNOffMessageResult> &sessionSet)
{
	processOffLineSession(sessionSet);
}

void TNIMSDKClient::msgRecv(CTNMessage *message)
{
	qInfo() << "[IMCore][TNIMSDKClient]msgRecv type:" << message->type << " msg:" << message->msgId.c_str();
	if (_msgManager)
		_msgManager->ProcessMsgRecv(message->type, message);

}

void TNIMSDKClient::syncMessage(CTNMessage *message, int32_t isOnline)
{
	qInfo() << "[IMCore][TNIMSDKClient]msgRecv type:" << message->type << " msg:" << message->msgId.c_str();
	if (_msgManager)
		_msgManager->ProcessMsgRecv(message->type, message);

}

void TNIMSDKClient::noticeMessage(CTNMessage *message, const char * broadcast, int32_t isOnline)
{
	qInfo() << "[IMCore][TNIMSDKClient]msgRecv type:" << message->type << " msg:" << message->msgId.c_str();
	if (_msgManager)
		_msgManager->ProcessMsgRecv(message->type, message);
}

void TNIMSDKClient::messageOperate(CTNMessage *message, bool success)
{
	//撤消消息回调
	QString msgId = message->msgId.c_str();
	QVariantMap context = TNIMUtil::jsonToMap(message->content.c_str());
	QString pushInfo = context["text"].toString();
	qInfo() << "[IMCore][TNIMSDKClient]messageOperate Ack msgId:" << msgId << " seqId:" << message->seqId << " result:" << success << "sessionId" << message->sessionId.c_str();
	int type = MSG_BIZ_SINGLECHAT_REVERT;
	if (message->type == MSG_BIZ_GROUPCHAT)
		type = MSG_BIZ_GROUPCHAT_REVERT;
	TNNotifyCenter::instance()->postNotifyRefreshRevert(success, type, message->timestamp, message->sessionId.c_str(), msgId, pushInfo);
}

void TNIMSDKClient::syncSessionStatusResp(const char * sessionId)
{
	qInfo() << "[IMCore][TNIMSDKClient]sendSessionResp code:" << sessionId;
	//if (_msgManager)
		//_msgManager->GetReadSessionManager()->DeleteReadSessionReq(sessionId);

}

void TNIMSDKClient::syncSessionStatusReq(const char * sessionId)
{
	//在线重置已读当前会话
	QString strSessionId = sessionId;
	TNNotifyCenter::instance()->postNotifyReadSession(strSessionId);
}


void TNIMSDKClient::msgAck(const char * sessionId, const char * msgId, int64_t seqId, int32_t result)
{
	QString strId = msgId;
	qInfo() << "[IMCore][TNIMSDKClient]msgAck msgId:" << msgId << " seqId:" << seqId << " result:" << result << "sessionId" << sessionId;
	if (result == SERVER_ORG_CODE)
		TNNotifyCenter::instance()->postNotifyOnlineMsg(msgId, TNIMMessageFailedOrCard);
	else
		TNNotifyCenter::instance()->postNotifyOnlineMsg(msgId, result == 0 ? TNIMMessageSuccess : TNIMMessageFailed);
}

void TNIMSDKClient::notificationCenter(const char* broadcast, const char* userInfoJson)
{
	//暂不处理
	//if (broadcast != NULL)
	//{
	//	QString strBroadCast = broadcast;
	//	if (strBroadCast == NEW_FRIEND_NOTICE)
	//	{
	//		if (_msgManager)
	//			_msgManager->GetIMProcessor()->updateNewFriendNotice();
	//	}
	//}
}

/**
* 用户在线状态变化通知
* @param mapClientStatus 对应表 {用户名 在线状态} 0 不在线，1在线
*/
void TNIMSDKClient::userOnlineStatus(std::map<string, int32_t> &mapClientStatus)
{

}
   
void TNIMSDKClient::daInfo(const char* atrNamax, map<string, string> & property)
{

}

void TNIMSDKClient::syncGroupchat(CTNMessage *message)
{
	_msgManager->GetIMProcessor()->ProcessChatSyncMsg(message->msgId.c_str(), message->catalogId, message->content.c_str());
}

void TNIMSDKClient::processOffLineSession(set<CTNOffMessageResult> &sessionSet)
{
	if (sessionSet.size() == 0)
		return;
	QStringList sessionList;
	vector<CTNSession> updateSessionList;
	for (CTNOffMessageResult result : sessionSet)
	{
		QString sessionId = result.sessionId.c_str();
		if (_msgManager)
		{
			toonim::CTNSession existSession = toonim::getChatDB()->getSession(result.sessionId.c_str());
			if(_msgManager->UpdateSessionTitle(existSession))
				updateSessionList.push_back(existSession);
		}
		sessionList.append(sessionId);
	}
	toonim::getChatDB()->updateSession(updateSessionList);
	TNNotifyCenter::instance()->postNotifyRefresh(sessionList);
}
