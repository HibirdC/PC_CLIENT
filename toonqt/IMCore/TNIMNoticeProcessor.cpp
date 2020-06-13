#include "TNIMNoticeProcessor.h"
#include "TNDataControlServer.h"
#include "tnimutil.h"
#include "tncmessage.h"
#include "TNIMCoreProcessor.h"
#include "TNUserDataHelper.h"
#include "CTNDBHeader.h"
#define COMPANY_BUTTON    QString("去看看")

TNIMNoticeProcessor::TNIMNoticeProcessor()
{
}


TNIMNoticeProcessor::~TNIMNoticeProcessor()
{
}


bool TNIMNoticeProcessor::ShouldShowNotice(st_BMessage0Ptr bmessage)
{
	bool bShow = true;
	//小秘书普通消息过滤
	if (bmessage->GetSessionId() == "v_11" && bmessage->GetContentType() == TNChatTypeText)
		bShow =  false;
	else
	{
		//新的朋友“个人关系建立”消息过滤
		QVariantMap context = TNIMUtil::jsonToMap(bmessage->GetContent());
		CatalogType noticeType = (CatalogType)context["catalogId"].toInt();
		if (noticeType == CATALOG_FRIEND_REQ)
		{
			SubCatalogType subNoticeType = (SubCatalogType)context["subCatalogId"].toInt();
			if (subNoticeType == SubCatalogType_ChangeCard || subNoticeType == SubCatalogType_PhoneChangeCard)
				bShow = false;
		}
	}
	return bShow;
}

bool TNIMNoticeProcessor::ShouldShowNotice(toonim::CTNMessage* bmessage)
{
	bool bShow = true;
	//小秘书普通消息过滤
	QString sessionId = bmessage->sessionId.c_str();
	if (sessionId == "v_11" && bmessage->contentType == TNChatTypeText)
		bShow = false;
	else
	{
		//新的朋友“个人关系建立”消息过滤
		QVariantMap context = TNIMUtil::jsonToMap(bmessage->content.c_str());
		CatalogType noticeType = (CatalogType)context["catalogId"].toInt();
		if (noticeType == CATALOG_FRIEND_REQ)
		{
			SubCatalogType subNoticeType = (SubCatalogType)context["subCatalogId"].toInt();
			if (subNoticeType == SubCatalogType_ChangeCard || subNoticeType == SubCatalogType_PhoneChangeCard)
				bShow = false;
		}
	}
	return bShow;

}


void TNIMNoticeProcessor::ProcessTitle(TNNoticeInfo& notice, QVariantMap& context)
{
	notice.bizId = context["bizNo"].toString();
	notice.subCatalog = context["subCatalog"].toString();
}

void TNIMNoticeProcessor::ProcessAvaTar(TNNoticeInfo& notice, QVariantMap& context,const QString& to)
{
	int headFlag = context["headFlag"].toInt();
	if (headFlag == 0)
	{
		//不显示头像
		notice.headFlag = 0;
	}
	else if (headFlag == 1)
	{
		//显示左侧头像
		notice.headFlag = 1;
		notice.leftFeed = context["headFeed"].toString();
		notice.upFeedTitle = GetTitleFromFeedId(notice.leftFeed);
	}
	else if (headFlag == 2)
	{
		//2侧都显示头像
		notice.headFlag = 2;
		notice.leftFeed = context["headFeed"].toString();
		notice.upFeedTitle = GetTitleFromFeedId(notice.leftFeed);
		if (notice.upFeedTitle.isEmpty())
		{
			notice.upFeedTitle = context["friendTitle"].toString();
		}
		notice.rightFeed = to;
		notice.downFeedTitle = GetTitleFromFeedId(to);
	}
}

QString TNIMNoticeProcessor::GetTitleFromFeedId(const QString& feedId)
{
	st_FeedPtr feedInfo;
	TNUserDataHelper::GetInstance()->GetFeedInfo(feedId, feedInfo);
	if (feedInfo)
		return feedInfo->GetTitle();

	return QString::null;
}

void TNIMNoticeProcessor::ProcessContent(TNNoticeInfo& notice, QVariantMap& context)
{
    notice.summary = context["summary"].toString();
	if (notice.summary.isEmpty())
		notice.summary = context["subCatalog"].toString();
    notice.msgContent = context["msg"].toString();
	notice.expireTime_s = context["expireTime"].toLongLong();
    if (context.contains("mobilePhone"))
        notice.mobilePhone = context["mobilePhone"].toString();
    if (notice.msgContent.isEmpty())
    {
        QVariantList contentDetails = context["contentDetail"].toList();
        if (contentDetails.size()>0)
        {
            notice.msgContent = contentDetails.first().toMap()["content"].toString();
        }
    }
}


void TNIMNoticeProcessor::ProcessOperate(TNNoticeInfo& notice, QVariantMap& context)
{
	notice.noticeType = (CatalogType)context["catalogId"].toInt();
    if (notice.noticeType == CATALOG_GROUP_INVITEJOIN || notice.noticeType == CATALOG_FRIEND_REQ || notice.noticeType == CATALOG_SEND_CARD)
	{
		notice.subNoticeType = (SubCatalogType)context["subCatalogId"].toInt();
	}
	notice.buttonName = context["buttonTitle"].toString();
	notice.actionType = (ActTionType)context["actionType"].toInt();
	int  finishFlag = context["finishFlag"].toInt();
	if (finishFlag)
		notice.bIsFinished = true;
	else
		notice.bIsFinished = false;
	if (notice.actionType == Action_Url)
	{
		//业务完成url
		if (notice.bIsFinished)
			notice.Url = context["finishUrl"].toString();
		else
			notice.Url = context["url"].toString();
			
		/*if (notice.Url.length() != 0)
		{
		QString params = context["args"].toString();
		if (params.length() != 0)
		{
		QVariantMap paramMap = TNIMUtil::jsonToMap(params);
		QString paraUrl = "?";
		QVariantMap::Iterator iter = paramMap.begin();
		for (iter; iter != paramMap.end(); iter++)
		{
		QString paramKey = iter.key();
		QString paramValue = iter.value().toString();
		QString ParaItem = paramKey + "=" + paramValue;
		if (iter != paramMap.begin())
		paraUrl += "&";
		paraUrl += ParaItem;
		}
		notice.Url += paraUrl;
		}
		}*/
	}
	else if (notice.actionType == Action_Toon)
		notice.Url = context["toonUrl"].toString();
	
	if ((notice.buttonName.isEmpty()) && !(notice.Url.isEmpty()))
		notice.buttonName = COMPANY_BUTTON;
	if (notice.actionType == Action_APP)
		notice.buttonName = "";
}

void TNIMNoticeProcessor::OnlineMsgToNotice(toonim::CTNMessage* message, TNNoticeInfo& info)
{
	info.msgId = message->msgId.c_str();
	info.seqId = message->seqId;
	info.sessonId = message->sessionId.c_str();
	info.timestmp_s = message->timestamp;
	info.expireTime_s = message->expireTime;
    //gcc error:
    QString qs_content = message->content.c_str();
    QVariantMap context = TNIMUtil::jsonToMap(qs_content);
	ProcessTitle(info, context);
	QString toId = message->toId.c_str();
	ProcessAvaTar(info, context, toId);
	ProcessContent(info, context);
	ProcessOperate(info, context);
}

void TNIMNoticeProcessor::OfflineMsgToNotice(const st_BMessage0Ptr bmessage, TNNoticeInfo& info)
{
	info.msgId = bmessage->GetMsgId();
	info.sessonId = bmessage->GetSessionId();
	info.timestmp_s = bmessage->GetTimestamp();
	info.expireTime_s = bmessage->GetExpireTime();
	QVariantMap context = TNIMUtil::jsonToMap(bmessage->GetContent());
	ProcessTitle(info, context);
	ProcessAvaTar(info, context, bmessage->GetToId());
	ProcessContent(info, context);
	ProcessOperate(info, context);
}

TNIMNoticeProcessor& TNIMNoticeProcessor::GetInstance()
{
	static TNIMNoticeProcessor noticeProcessor;
	return noticeProcessor;
}

void  TNIMNoticeProcessor::MessageCastToNotice(const st_BMessage0Ptr bmessage, st_NoticeInfo& data)
{
	GetInstance().OfflineMsgToNotice(bmessage, data);
}

void   TNIMNoticeProcessor::IMMessageCastToNotice(toonim::CTNMessage* bmessage, st_NoticeInfo& data)
{
	GetInstance().OnlineMsgToNotice(bmessage, data);
}
