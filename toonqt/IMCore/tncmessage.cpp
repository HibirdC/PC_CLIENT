#include "tncmessage.h"
#include "tmtp.h"
#include "tmtp_biz.h"
#include "tnimutil.h"
#include "imcore_global.h"

TNCMessage::TNCMessage() :type(TYPE_PING), msgId(""), msgOpId(""), seqId(0), from(""), fromUserId(""), to(""), toUserId(""), pushInfo(""),
timestamp(0), catalogId(0), bubbleFlag(0), _body(NULL), priority(0), isMyself(false), sendStatus(TNIMMessageSending), _topic(""), _content(""), atType(0),
toToonType(""), fileStatus(0), contentType(TNChatTypeText), flags(0), expireTime(0)
{
}

TNCMessage::~TNCMessage()
{
	if (_body)
		delete _body;
	_body = NULL;
}

TNCMessage* TNCMessage::instanceFromMsgReq(int type, Toon::MsgReq* req)
{
    if  (req == NULL){
        return NULL;
    }

    TNCMessage* message = new TNCMessage();
    message->type = (Toon_TMTP_TYPE)type;
	message->msgId = req->msg_id.c_str();
	message->seqId = req->seq_id;
    message->from = req->from.c_str();
	message->fromUserId = req->from_client_id.c_str();
    message->to = req->to.c_str();
	message->toUserId = req->to_client_id.c_str();
    message->pushInfo = req->pushinfo.c_str();
    message->timestamp = req->timestamp;
    message->priority = req->priority;
    message->isMyself = false;
    message->sendStatus = TNIMMessageSuccess;
	message->getTopic();
    taf::JceInputStream<taf::BufferReader> is;
     is.setBuffer(req->content.data(), req->content.size());

     QString json;
     switch (type) {
         case TYPE_NOTIFY_MSGREQ:
         case TYPE_SYNC_MSGREQ:
         case TYPE_GROUP_NOTIFY_REQ:
         case TYPE_SINGLE_CHAT_MSGREQ:
         case TYPE_GROUP_CHAT_MSGREQ:

         {
             Toon::BizMsg bizMsg;
             try {
                 bizMsg.readFrom(is);
             } catch (...) {
//                 NSString * log = [NSString stringWithFormat:@"bizMsg readFrom error:%@", @(type)];
//                 TNIM_INFO(log);
                 json = QString(req->content.data());

                 break;
             }
              message->catalogId = bizMsg.catalogId;
              message->catalog  = bizMsg.catalog.c_str();
              message->contentType = (TNMessageContentType)bizMsg.contentType;
              message->expireTime = bizMsg.expireTime;
              message->senderName = bizMsg.senderName.c_str();
			  message->bubbleFlag = bizMsg.bubbleFlag;
              message->atType = bizMsg.atType;
			  for (int i = 0; i < bizMsg.atFeeds.size(); i++) 
				  message->atFeeds.append(bizMsg.atFeeds[i].userId.c_str());

              QVariantMap bizMap;
              bizMap["catalogId"] = QVariant(bizMsg.catalogId);
              bizMap["headFlag"] = QVariant(bizMsg.headFlag);
              bizMap["finishFlag"] = QVariant(bizMsg.finishFlag);
              bizMap["actionType"] = QVariant(bizMsg.actionType);
              bizMap["showFlag"] = QVariant(bizMsg.showFlag);
              bizMap["bubbleFlag"] = QVariant(bizMsg.bubbleFlag);
              bizMap["subCatalogId"] = QVariant(bizMsg.subCatalogId);

             if (bizMsg.bizNo.length() > 0) {
                 bizMap["bizNo"] = QVariant(bizMsg.bizNo.c_str());
             }

             if (bizMsg.subCatalog.length() > 0) {
                 bizMap["subCatalog"] = QVariant(bizMsg.subCatalog.c_str());
             }
             if (bizMsg.headFeed.length() > 0) {
                 bizMap["headFeed"] = QVariant(bizMsg.headFeed.c_str());
             }
             if (bizMsg.summary.length() > 0) {
                 bizMap["summary"] = QVariant(bizMsg.summary.c_str());
             }
             if (bizMsg.content.length() > 0) {
                 QString jsonContent = bizMsg.content.c_str();
                 QVariantMap mapResp = TNIMUtil::jsonToMap(jsonContent);
                 bizMap.unite(mapResp);

              }
             json = TNIMUtil::mapToJson(bizMap);
             break;

         }
         default:
         {
            json = QString(req->content.data());
//             json = [NSString stringWithUTF8String:vctContent.data()];
         }

     }

     message->setContent(json);

	 return message;
}


QString TNCMessage::genSessionId(Toon_TMTP_TYPE type,const QString &from,const QString& to){
    QString sessionId;

       if (type == TYPE_GROUP_CHAT_MSGREQ) {
           sessionId = to;
       }
       else if (type == TYPE_SINGLE_CHAT_MSGREQ){
           if (to.compare(from, Qt::CaseInsensitive) > 0) {
               sessionId = to + "_" + from;
           }else{
               sessionId = from + "_" + to;
           }
       } else if (type == TYPE_GROUP_NOTIFY_REQ || type == TYPE_NOTIFY_MSGREQ){
           sessionId = from;
       }
       else{
           sessionId = QString("othersession_%1").arg(type);
       }

       return  sessionId;
}

QString TNCMessage::genTopic(Toon_TMTP_TYPE type, QString& toUserId, QString& to)
{
	QString topic;
	if (type == TYPE_GROUP_CHAT_MSGREQ) {
		topic = to;
	}
	else if (type == TYPE_SINGLE_CHAT_MSGREQ){
		topic = toUserId;
	}
	else{
		topic = to;
	}
	return  topic;
}

QString TNCMessage::getTopic()
{
	if (_topic.length() == 0)
		_topic = genTopic(this->type, this->toUserId, this->to);
	return _topic;

}

QString TNCMessage::getSesssionId()
{
    if (_sessionId.length() == 0) {
        _sessionId = TNCMessage::genSessionId(this->type, this->from, this->to);
    }

    return _sessionId;
}

TNMessageBodyBase* TNCMessage::getBody()
{
    if (_body == NULL || _body->isEmpty()) {
         _body = TNMessageBodyBase::instance(this->contentType);
     }
     return _body;
}

QString TNCMessage::packBody()
{
    if  (_body != NULL){
        QVariantMap mapBody = _body->pack();
        QString jsonBody = TNIMUtil::mapToJson(mapBody);
//        QJsonDocument doc = QJsonDocument::fromVariant(mapBody);
//        QByteArray baBodyJson = doc.toJson();

        return jsonBody;
    }

    return "";
}

void TNCMessage::parseBody(QString &jsonBody){

    QVariantMap mapResp = TNIMUtil::jsonToMap(jsonBody);
   //
}

QString TNCMessage::getAbstractText()
{
    if  (_body != NULL){
        return _body->getAbstractText();
    }

    return "";
}

bool TNCMessage::isEmpty()
{
    return true;
}

QString TNCMessage::getContent()
{
    if (_content.length() == 0){
        _content = this->pack();
    }

    return _content;
}

QString TNCMessage::GetAtFeedlist()
{
	QString strFeeds;
	for (int index = 0; index < atFeeds.size(); index++)
	{
		strFeeds += atFeeds[index];
		strFeeds += ",";
	}
	return strFeeds;
}

bool    TNCMessage::IsContaionMeAtFeeds(QString userId)
{
	if (type == TYPE_GROUP_CHAT_MSGREQ)
	{
		if (atType == 0 || isMyself)
			return false;
		if (atType == 1)
			return true;
		for (int index = 0; index < atFeeds.size(); index++)
		{
			if (atFeeds[index] == userId)
				return true;
		}
		return false;
	}
	return false;
}

bool TNCMessage::IsContainMeAtFeedsFromMsgData(QString userId, const TNMsgData& message)
{
	if (message.bizType == MSG_BIZ_GROUPCHAT)
	{
		if (message.atType == 0 || message.bIsMyself)
			return false;
		if (message.atType == 1)
			return true;
		for (int index = 0; index < message.atFeeds.size(); index++)
		{
			if (message.atFeeds[index] == userId)
				return true;
		}
		return false;
	}
	return false;
}


QString TNCMessage::pack()
{
    QVariantMap mapSelf;
    mapSelf["msgId"] = this->msgId;
    mapSelf["type"] = this->type;
    mapSelf["timestamp"] = QVariant(this->timestamp);
    mapSelf["catalogId"] = QVariant(this->catalogId);
    mapSelf["catalog"] = this->catalog;
    mapSelf["topic"] = getTopic();
    mapSelf["from"] = this->from;
    mapSelf["to"] = this->to;
    mapSelf["pushInfo"] = this->pushInfo;
    mapSelf["contentType"] = this->contentType;
    mapSelf["content"] = this->packBody();
    mapSelf["atType"] = QVariant(this->atType);
    mapSelf["senderName"] = this->senderName;
    mapSelf["flags"] = QVariant(this->flags);
    mapSelf["priority"] = QVariant(this->priority);
    mapSelf["expireTime"] = QVariant(this->expireTime);

    QVariantList varFeeds;// = listMsg.at(i).toMap();
    for (int i = 0; i < this->atFeeds.size(); i++){
        varFeeds.append(this->atFeeds[i]);
    }
    if (varFeeds.size() > 0){
        mapSelf["atFeeds"] = varFeeds;
    }

    QString jsonStr = TNIMUtil::mapToJson(mapSelf);

    return jsonStr;
}

