#include <QDebug>
#include "TNNoticeMessageOperate.h"
#include "model_data/TNModelUserMessage.h"

TNNoticeMessageOperate::TNNoticeMessageOperate()
{
}


TNNoticeMessageOperate::~TNNoticeMessageOperate()
{
}

TNNoticeMessageOperate* TNNoticeMessageOperate::GetInstance()
{
    static TNNoticeMessageOperate operate;
	return &operate;
}

void TNNoticeMessageOperate::ProcessMsgForwordAction(TNModelUserMessage* message, QMap<QString, QString>& feedList)
{
    TNMsgData IMdata;
	MSG_TYPE type = MSG_TYPE_TEXT;
    switch(message->GetMessageType()){
    case em_text://文字表情
        type = MSG_TYPE_TEXT;
        break;
    case em_image:
        if(message->getFileSuffix() == ".gif"){
            type = MSG_TYPE_GIFIMG;
        }else{
            type = MSG_TYPE_IMG;
        }
        break;
    case em_file:
        type = MSG_TYPE_ATTACHMENT;
        break;
    case em_audio:
        type = MSG_TYPE_VOICE;
        break;
    case em_video:
        type = MSG_TYPE_VIDEO;
        break;
    case em_red_card:
        type = MSG_TYPE_RED_CARD;
        break;
    case em_groupchat_notice:
        type = MSG_TYPE_NOTICE;
        break;
    case em_notsupport:
        type = MSG_TYPE_OTHER;
        break;
    case em_card_not_exist:
        type = MSG_TYPE_CARD_FAILED;
        break;
    default:
        break;
    }

    IMdata.type = type;
	IMdata.from = message->getMyFeedId();
	IMdata.to = message->getToFeedId();
	IMdata.data = message->GetUserMessage();
	IMdata.toUserId = message->getUserId();
	IMdata.desc = message->getFileName();
	IMdata.size = message->getFileSize();
	IMdata.w = message->getPicSize().width();
	IMdata.h = message->getPicSize().height();
	IMdata.msgId = message->GetMsgID();
	IMdata.localPath = message->getFileLocalPath();
	IMdata.atType = message->GetAtType();
	IMdata.atFeeds = message->GetAtFeeds();
    IMdata.fileStatus = message->getMsgFileStatus();

    TNIMCoreClient::GetIMClient()->SendForwardMessage(&IMdata, feedList);
}

void TNNoticeMessageOperate::ProcessMsgRevokeAction(TNModelUserMessage* userMessage)
{
	st_RevokeData revokeData;
	revokeData.from = userMessage->getFromId();
	revokeData.to = userMessage->getToFeedId();
	revokeData.msgId = TNIMCoreClient::GetMsgId();
	revokeData.opFeedId = userMessage->getMyFeedId();
	revokeData.opMsgId = userMessage->GetMsgID();
	revokeData.opName = userMessage->GetFeedName();
	revokeData.toUserId = userMessage->getUserId();
    qInfo() << "[Notice] [TNNoticeMessageOpreate] revoke message from:" << revokeData.from
            << " to:" << revokeData.to << " opFeedId:" << revokeData.opFeedId
            << " opName:" << revokeData.opName << " opMsgId:" << revokeData.msgId;
	TNIMCoreClient::GetIMClient()->SendRevokeMessage(&revokeData, userMessage->getSessionType() == MSG_BIZ_SINGLECHAT);
}
