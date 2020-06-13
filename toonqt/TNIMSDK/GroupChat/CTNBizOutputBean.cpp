//
// Created by juzenhon on 2017/9/5.
//

#include "CTNBizOutputBean.h"


namespace toonim {
#ifdef RAPIDJSONWRAPPER
    void CTNGroupChatInfo::parse(toonim::CTNJsonValue &dataValue) {
        creatorFeedId = dataValue["creatorFeedId"].getString();
        groupChatId = dataValue["groupChatId"].getInt64();
        groupType = dataValue["groupType"].getInt32();
        topic = dataValue["topic"].getString();
        groupChatName = dataValue["groupChatName"].getString();
        groupChatHeadImage = dataValue["groupChatHeadImage"].getString();
        maxNum = dataValue["maxNum"].getInt32();
        status = dataValue["status"].getInt32();
        disturbStatus = dataValue["disturbStatus"].getInt32();
        myFeedId = dataValue["myFeedId"].getString();
        chatRoomId = dataValue["chatRoomId"].getString();
        titlePinyin = dataValue["titlePinyin"].getString();
        version = dataValue["version"].getInt64();
#else
        void CTNGroupChatInfo::parse(rapidjson::Value &dataValue) {
        if (dataValue.HasMember("creatorFeedId") && dataValue["creatorFeedId"].IsString()) {
            creatorFeedId = dataValue["creatorFeedId"].GetString();
        }
        if (dataValue.HasMember("groupChatId") && dataValue["groupChatId"].IsInt64()) {
            groupChatId = dataValue["groupChatId"].GetInt64();
        }
        if (dataValue.HasMember("groupType") && dataValue["groupType"].IsInt()) {
            groupType = dataValue["groupType"].GetInt();
        }
        if (dataValue.HasMember("topic") && dataValue["topic"].IsString()) {
            topic = dataValue["topic"].GetString();
        }
        if (dataValue.HasMember("groupChatName") && dataValue["groupChatName"].IsString()) {
            groupChatName = dataValue["groupChatName"].GetString();
        }
        if (dataValue.HasMember("groupChatHeadImage") && dataValue["groupChatHeadImage"].IsString()) {
            groupChatHeadImage = dataValue["groupChatHeadImage"].GetString();
        }
        if (dataValue.HasMember("maxNum") && dataValue["maxNum"].IsInt()) {
            maxNum = dataValue["maxNum"].GetInt();
        }
        if (dataValue.HasMember("currNum") && dataValue["currNum"].IsInt()) {
            currNum = dataValue["currNum"].GetInt();
        }
        if (dataValue.HasMember("status") && dataValue["status"].IsInt()) {
            status = dataValue["status"].GetInt();
        }
        if (dataValue.HasMember("disturbStatus") && dataValue["disturbStatus"].IsInt()) {
            disturbStatus = dataValue["disturbStatus"].GetInt();
        }
        if (dataValue.HasMember("myFeedId") && dataValue["myFeedId"].IsString()) {
            myFeedId = dataValue["myFeedId"].GetString();
        }
        if (dataValue.HasMember("chatRoomId") && dataValue["chatRoomId"].IsString()) {
            chatRoomId = dataValue["chatRoomId"].GetString();
        }
        if (dataValue.HasMember("titlePinyin") && dataValue["titlePinyin"].IsString()) {
            titlePinyin = dataValue["titlePinyin"].GetString();
        }
        if (dataValue.HasMember("version") && dataValue["version"].IsInt64()) {
            version = dataValue["version"].GetInt64();
        }
#endif
    }
}


