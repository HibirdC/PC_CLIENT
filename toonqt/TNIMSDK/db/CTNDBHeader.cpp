//
//  CTNDBHeader.cpp
//  TNChatLibrary
//
//  Created by 王海涛 on 2017/10/11.
//

#include "CTNDBHeader.h"
#include <sstream>
#include "rapidjson.h"
#include "document.h"
#include "pointer.h"
#include "stringbuffer.h"
#include "writer.h"
#include "CTNDBUtils.hpp"
#include "CTNIMTypedef.h"
#include "CTNJsonUtils.hpp"
#include "CTNBaseBean.h"

#ifdef WIN32
#include <objbase.h>
#elif defined(ANDROID)
#else
#include <uuid/uuid.h>
#endif

namespace toonim {
    
    CTNMessage::CTNMessage(){
            seqId = 0;
            timestamp = 0;
            width = 0;
            height = 0;
            type = 0;
            atType = 0;
            sendStatus = 0;
            status = 0;
            priority = 0;
            catalogId = 0;
            subCatalogId = 0;
            contentType = 0;
            faultSeqId = -1;
            expireTime = 0;
            isMyself = CTNOwnerUnkown;
            flags = 0;
    }
    
    string CTNMessage::genBodyJson() {
        if(content.length() == 0) {
            return "";
        }
        
        string logContent = content;
        
        if (contentType == CTNChatTypeText) {
            
#ifdef RAPIDJSONWRAPPER
            CTNJsonReader dictBody(content);
            
            string logContent = dictBody["text"].getString();
            
            if(logContent.length() > 10) {
                logContent = logContent.substr(0, 10);
            }
#else
            rapidjson::Document dictBody;
            
            dictBody.Parse(content.c_str());
            string logContent;
            const rapidjson::Value* valLogContent = GetValueByPointer(dictBody, "/text");
            if (valLogContent && valLogContent->IsString()) {
                logContent = valLogContent->GetString();
            }
            
            if(logContent.length() > 10) {
                logContent = logContent.substr(0, 10);
            }
#endif
            
        }
        
#ifdef RAPIDJSONWRAPPER
        CTNJsonWriter dictMsg;
        
        dictMsg["msgId"] = msgId;
        dictMsg["seqId"] = CTNDBUtils::stringFromInt64(seqId);
        dictMsg["type"] = CTNDBUtils::stringFromInt64(type);
        dictMsg["to"] = toId;
//        dictMsg["topic"] = topic;
        dictMsg["from"] = fromId;
        dictMsg["fromClientId"] = fromClientId;
        dictMsg["content"] = logContent;
        dictMsg["contentType"] = CTNDBUtils::stringFromInt64(contentType);
        
        return dictMsg.toString();
#else
        rapidjson::StringBuffer dictMsg;
        rapidjson::Writer<rapidjson::StringBuffer> writer(dictMsg);
        
        writer.StartObject();
        writer.Key("msgId");
        writer.String(msgId.c_str());
        writer.Key("seqId");
        writer.String(CTNDBUtils::stringFromInt64(seqId).c_str());
        writer.Key("type");
        writer.String(CTNDBUtils::stringFromInt64(type).c_str());
        writer.Key("to");
        writer.String(toId.c_str());
        //        writer.Key("topic");
        //        writer.String(topic.c_str());
        writer.Key("from");
        writer.String(fromId.c_str());
        writer.Key("fromClientId");
        writer.String(fromClientId.c_str());
        writer.Key("content");
        writer.String(logContent.c_str());
        writer.Key("contentType");
        writer.String(CTNDBUtils::stringFromInt64(contentType).c_str());
        writer.EndObject();
        
        return dictMsg.GetString();
#endif
        
        
    }
    string CTNMessage::getAbstractText() {
        return toonim::getAbstractText(*this);
    }
    
    string CTNMessage::getToToonTypeString(){
        std::stringstream s;
        for (int i = 0; i < toToonTypes.size(); i++){
            s<<toToonTypes[i]<<";";
        }
        
        return s.str();
    }
    
    void parse(rapidjson::Value &dataValue);
    
    void CTNGroupInfo::parse(void* jsonValue) {
        if (jsonValue == nullptr){
            return;
        }
        
#ifdef RAPIDJSONWRAPPER
        CTNValue* dataValue = (CTNValue*)jsonValue;
        
        creatorFeedId = (*dataValue)["creatorFeedId"].getString();
        groupId = (*dataValue)["groupChatId"].getInt64();
        topic = (*dataValue)["topic"].getString();
        name = (*dataValue)["groupChatName"].getString();
        pinyin = (*dataValue).getString();
        headerImage = (*dataValue)["groupChatHeadImage"].getString();
        maxNum = (*dataValue)["maxNum"].getInt32();
        currNum = (*dataValue)["currNum"].getInt32();
        status = (*dataValue)["status"].getInt32();
        disturbStatus = (*dataValue)["disturbStatus"].getInt32();
        myFeedId = (*dataValue)["myFeedId"].getString();
        namePinyin = (*dataValue)["titlePinyin"].getString();
        verify = (*dataValue)["verify"].getInt32();
        version = (*dataValue)["version"].getInt64();
#else
        rapidjson::Value* dataValue = (rapidjson::Value*)jsonValue;
        if (dataValue->HasMember("creatorFeedId") && (*dataValue)["creatorFeedId"].IsString()) {
            creatorFeedId = (*dataValue)["creatorFeedId"].GetString();
        }
        if (dataValue->HasMember("groupChatId") && (*dataValue)["groupChatId"].IsInt64()) {
            groupId = (*dataValue)["groupChatId"].GetInt64();
        }
        if (dataValue->HasMember("topic") && (*dataValue)["topic"].IsString()) {
            topic = (*dataValue)["topic"].GetString();
        }
        if (dataValue->HasMember("groupChatName") && (*dataValue)["groupChatName"].IsString()) {
            name = (*dataValue)["groupChatName"].GetString();
        }
        if (dataValue->HasMember("pinyin") && (*dataValue)["pinyin"].IsString()) {
            pinyin = (*dataValue)["pinyin"].GetString();
        }
        if (dataValue->HasMember("groupChatHeadImage") && (*dataValue)["groupChatHeadImage"].IsString()) {
            headerImage = (*dataValue)["groupChatHeadImage"].GetString();
        }
        if (dataValue->HasMember("maxNum") && (*dataValue)["maxNum"].IsInt()) {
            maxNum = (*dataValue)["maxNum"].GetInt();
        }
        if (dataValue->HasMember("currNum") && (*dataValue)["currNum"].IsInt()) {
            currNum = (*dataValue)["currNum"].GetInt();
        }
        if (dataValue->HasMember("status") && (*dataValue)["status"].IsInt()) {
            status = (*dataValue)["status"].GetInt();
        }
        if (dataValue->HasMember("disturbStatus") && (*dataValue)["disturbStatus"].IsInt()) {
            disturbStatus = (*dataValue)["disturbStatus"].GetInt();
        }
        if (dataValue->HasMember("myFeedId") && (*dataValue)["myFeedId"].IsString()) {
            myFeedId = (*dataValue)["myFeedId"].GetString();
        }
        if (dataValue->HasMember("titlePinyin") && (*dataValue)["titlePinyin"].IsString()) {
            namePinyin = (*dataValue)["titlePinyin"].GetString();
        }
        if (dataValue->HasMember("verify") && (*dataValue)["verify"].IsInt()) {
            verify = (*dataValue)["verify"].GetInt();
        }
        if (dataValue->HasMember("version") && (*dataValue)["version"].IsInt64()) {
            version = (*dataValue)["version"].GetInt64();
        }
#endif
    }
    
    void CTNGroupMember::parse(void *jsonValue) {
        if (jsonValue == nullptr){
            return;
        }
        
#ifdef RAPIDJSONWRAPPER
        CTNValue* dataValue = (CTNValue*)jsonValue;
        groupId = (*dataValue)["groupChatId"].getInt64();
        
        feedId = (*dataValue)["feedId"].getString();
        name = (*dataValue)["nickname"].getString();
        headerImage = (*dataValue)["headImage"].getString();
        status = (*dataValue)["status"].getInt32();
        timestamp = (*dataValue)["timestamp"].getInt64();
#else
        rapidjson::Value* dataValue = (rapidjson::Value*)jsonValue;
        if (dataValue->HasMember("groupChatId") && (*dataValue)["groupChatId"].IsInt64()) {
            groupId = (*dataValue)["groupChatId"].GetInt64();
        }
        if (dataValue->HasMember("feedId") && (*dataValue)["feedId"].IsString()) {
            feedId = (*dataValue)["feedId"].GetString();
        }
        if (dataValue->HasMember("nickname") && (*dataValue)["nickname"].IsString()) {
            name = (*dataValue)["nickname"].GetString();
        }
        if (dataValue->HasMember("headImage") && (*dataValue)["headImage"].IsString()) {
            headerImage = (*dataValue)["headImage"].GetString();
        }
        if (dataValue->HasMember("status") && (*dataValue)["status"].IsInt()) {
            status = (*dataValue)["status"].GetInt();
        }
        if (dataValue->HasMember("timestamp") && (*dataValue)["timestamp"].IsInt64()) {
            timestamp = (*dataValue)["timestamp"].GetInt64();
        }
#endif
    }
    
    void CTNAppInfo::parse(void *dataValue) {
        if (dataValue == nullptr) {
            return;
        }

#ifdef RAPIDJSONWRAPPER
        CTNValue* jsonValue = (CTNValue*)dataValue;
        
        appId = (*jsonValue)["appId"].getString();
        appCode = (*jsonValue)["appCode"].getString();
        appTitle = (*jsonValue)["appTitle"].getString();
        appLittleIcon = (*jsonValue)["appLittleIcon"].getString();
        chatFlag = (*jsonValue)["chatFlag"].getInt32();
        isDelete = (*jsonValue)["isDelete"].getInt32();
#else
        rapidjson::Value* jsonValue = (rapidjson::Value*)dataValue;
        if (jsonValue->HasMember("appId") && (*jsonValue)["appId"].IsString()) {
            appId = (*jsonValue)["appId"].GetString();
        }
        if (jsonValue->HasMember("appCode") && (*jsonValue)["appCode"].IsString()) {
            appCode = (*jsonValue)["appCode"].GetString();
        }
        if (jsonValue->HasMember("appTitle") && (*jsonValue)["appTitle"].IsString()) {
            appTitle = (*jsonValue)["appTitle"].GetString();
        }
        if (jsonValue->HasMember("appLittleIcon") && (*jsonValue)["appLittleIcon"].IsString()) {
            appLittleIcon = (*jsonValue)["appLittleIcon"].GetString();
        }
        if (jsonValue->HasMember("chatFlag") && (*jsonValue)["chatFlag"].IsInt()) {
            chatFlag = (*jsonValue)["chatFlag"].GetInt();
        }
        if (jsonValue->HasMember("isDelete") && (*jsonValue)["isDelete"].IsInt()) {
            isDelete = (*jsonValue)["isDelete"].GetInt();
        }
#endif
    }
    
    void CTNBlackListModel::parse(void *dataValue)
    {
        if (dataValue == nullptr) {
            return;
        }
        
#ifdef RAPIDJSONWRAPPER
        CTNValue* jsonValue = (CTNValue*)dataValue;
        
        feedId = (*jsonValue)["feedId"].getString();
        passiveFeedId = (*jsonValue)["passiveFeedId"].getString();
        status = (*jsonValue)["status"].getInt32();
#else
        rapidjson::Value* jsonValue = (rapidjson::Value*)dataValue;
        if (jsonValue->HasMember("feedId") && (*jsonValue)["feedId"].IsString()) {
            feedId = (*jsonValue)["feedId"].GetString();
        }
        if (jsonValue->HasMember("passiveFeedId") && (*jsonValue)["passiveFeedId"].IsString()) {
            passiveFeedId = (*jsonValue)["passiveFeedId"].GetString();
        }
        if (jsonValue->HasMember("status") && (*jsonValue)["status"].IsInt()) {
            status = (*jsonValue)["status"].GetInt();
        }
#endif
    }
    
    std::string generateSessionId(int32_t type, std::string from, std::string to, bool isMyself)
    {
        std::string sessionId;
        if (type == CTNIMMessageTypeChat || type == CTNIMMessageTypeMsgSingleOperate ){
            //单聊，比较from和to的大小，大的在前，中间以 _ 相隔； wxy 兼容之前版本，小的在前
            std::ostringstream s;
            if (to.compare(from) > 0) {
                s << to << "_" << from;
            } else {
                s << from << "_" << to;
            }
            sessionId = s.str();
        } else if (type == CTNIMMessageTypeBizNotice){
            if (isMyself) {
                sessionId = to;
            } else {
                sessionId = from;
            }
        } else if (type == CTNIMMessageTypeGroupChat || type == CTNIMMessageTypeMsgGroupOperate) {
            sessionId = to;
        } else {
            std::ostringstream s;
            s << "otrherSessionType_" << type;
            sessionId = s.str();
        }
        
        return sessionId;
    }
    
    std::string generateMsgId()
    {
        char str[64];
        
#ifdef WIN32
		GUID guid;
		::CoCreateGuid(&guid);
		_snprintf_s(
			str,
			sizeof(str),
			"{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
			guid.Data1, guid.Data2, guid.Data3,
			guid.Data4[0], guid.Data4[1],
			guid.Data4[2], guid.Data4[3],
			guid.Data4[4], guid.Data4[5],
			guid.Data4[6], guid.Data4[7]);
#elif defined(ANDROID)
        time_t temp = time(NULL);
        sprintf(str,"%ld",temp);
#else
		uuid_t uuid;
		uuid_generate(uuid);
		uuid_unparse(uuid, str);
#endif
        
        return string(str);
    }
    
}
