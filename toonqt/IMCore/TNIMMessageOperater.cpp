#include "TNIMMessageOperater.h"
#include "tncmessage.h"
#include "tnimutil.h"
#include "tnnotifycenter.h"
#include "LocalStorageCommon.h"
#include "TNDataControlServer.h"
#include <QString>
#include <QList>

#define REVERT_MSG_INFO "撤回了一条消息"
#define ME_REVERT_MSG_INFO "你撤回了一条消息"
TNIMMessageOperater::TNIMMessageOperater()
{
}


TNIMMessageOperater::~TNIMMessageOperater()
{
}

bool TNIMMessageOperater::ProcessMessageRevert(TNCMessage* msg)
{
	if (!IsRevertMsg(msg))
		return false;
	SetRevertMessagePushInfo(msg);
	TableBaseVec tableMessage;
	st_BMessage0Ptr messageInfo;
	TNDataControlServer::GetInstance()->Query(tableMessage, "BMessage0", "msgId", msg->msgOpId, DBTYPE_MSG);
	if (tableMessage.size() > 0)
	{
		messageInfo = std::dynamic_pointer_cast<st_BMessage0>(tableMessage[0]);
		QString type = QString::number(msg->type);
		QMap<QString, QString> fieldMap;
		fieldMap.insert("type", type);
		fieldMap.insert("content", msg->getContent());
		fieldMap.insert("pushInfo", msg->pushInfo);
		TNDataControlServer::GetInstance()->UpdateSetValueByFieldMap("BMessage0", fieldMap, "msgId", messageInfo->GetMsgId(), DBTYPE_MSG);
	}
	else
		SaveMsgToMessageOperate(msg);
	return true;
}

void TNIMMessageOperater::ProcessChatMsgFilterRvert(TNCMessage* msg)
{
	if (msg->type == TYPE_SINGLE_CHAT_MSGREQ || msg->type == TYPE_GROUP_CHAT_MSGREQ)
	{
		TableBaseVec tableMessageOp;
		TNDataControlServer::GetInstance()->Query(tableMessageOp, "MessageOperate", "opMsgId", msg->msgId, DBTYPE_MSG);
		if (tableMessageOp.size() > 0)
		{
			st_MessageOperatePtr st_msgOp = std::dynamic_pointer_cast<st_MessageOperate>(tableMessageOp[0]);
			if (msg->type == TYPE_SINGLE_CHAT_MSGREQ)
				msg->type = TYPE_MSG_SINGLE_OPERATE;
			if (msg->type == TYPE_GROUP_CHAT_MSGREQ)
				msg->type = TYPE_MSG_GROUP_OPERATE;
			QString pushInfo;
			pushInfo.append(st_msgOp->GetOpName());
			pushInfo.append(QStringLiteral(REVERT_MSG_INFO));
			msg->pushInfo = pushInfo;
			TNDataControlServer::GetInstance()->DeleteFromTableNameByField("MessageOperate", "opMsgId", msg->msgId, DBTYPE_MSG);
		}
	}

}

bool TNIMMessageOperater::SaveMsgToMessageOperate(TNCMessage* msg)
{
	if (!IsRevertMsg(msg))
		return false;

	st_MessageOperatePtr st_msgOp = std::make_shared<st_MessageOperate>();
	st_msgOp->SetMsgId(msg->msgId);
	st_msgOp->SetType(msg->type);
	st_msgOp->SetSeqId(msg->seqId);
	st_msgOp->SetMfrom(msg->from);
	st_msgOp->SetMto(msg->to);
	st_msgOp->SetTimestamp(msg->timestamp);
	st_msgOp->SetCatalogId(msg->catalogId);
	QString strContent = msg->getContent();
    QVariantMap bizMap = TNIMUtil::jsonToMap(strContent);
	st_msgOp->SetOpMsgId(bizMap["msgId"].toString());
	st_msgOp->SetOpFeedId(bizMap["operatorFeedId"].toString());
	st_msgOp->SetOpName(bizMap["operatorName"].toString());
	TNDataControlServer::GetInstance()->InsertDatas(std::dynamic_pointer_cast<TableBase>(st_msgOp), DBTYPE_MSG);
	return true;
}

bool TNIMMessageOperater::IsRevertMsg(TNCMessage* msg)
{
	if (msg == NULL)
		return false;
	if (msg->type == TYPE_MSG_SINGLE_OPERATE || msg->type == TYPE_MSG_GROUP_OPERATE)
	{
		if (msg->catalogId == OPERATE_TYPE_REVOKE)
			return true;
	}
		
	return false;
}

void TNIMMessageOperater::SetRevertMessagePushInfo(TNCMessage* msg)
{
	if (!IsRevertMsg(msg))
		return;
	QString strContent = msg->getContent();
    const QVariantMap& bizMap = TNIMUtil::jsonToMap(strContent);
	QString pushInfo;
	if (!msg->isMyself)
	{
		pushInfo.append(bizMap["operatorName"].toString());
		pushInfo.append(QStringLiteral(REVERT_MSG_INFO));
	}
	else
		pushInfo.append(QStringLiteral(ME_REVERT_MSG_INFO));
	
	msg->pushInfo = pushInfo;
	if (msg->msgOpId.isEmpty())
		msg->msgOpId = bizMap["msgId"].toString();
}
