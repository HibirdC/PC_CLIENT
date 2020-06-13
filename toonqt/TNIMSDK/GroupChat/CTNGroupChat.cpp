//
// Created by juzenhon on 2017/8/28.
//

#include "CTNGroupChat.h"
#include "CTNBizOutputBean.h"
#include "CTNRequest.h"
#include "CTNDBHeader.h"
#include "CTNDBAPI.h"
#include "CTNChatAPI.h"
#include <sstream>
#include "document.h"
#include "prettywriter.h"
#include "CTNDBUtils.hpp"
#include "../CHAT/CTNChatManager.hpp"
#include "curl/curl.h"
#include "CTNBizInuputBean.h"

const char *DomainChat = "api.new.groupchat.systoon.com";

using namespace toonim;

//--------------------创建群聊接口----------------------
namespace toonim {

    void initHttpBiz(const char *clientId, const char *token, const char *deviceId,
                     int32_t toonType, const char *version, const char *platformVersion,
                     const char *cerPath) {
        if (clientId == nullptr || strlen(clientId) == 0) {
            TNMPLOG("initHttpBiz clientId is empty!");
            return;
        }
        if (token == nullptr || strlen(token) == 0) {
            TNMPLOG("initHttpBiz token is empty!");
            return;
        }
        if (deviceId == nullptr || strlen(deviceId) == 0) {
            TNMPLOG("initHttpBiz deviceId is empty!");
            return;
        }
        if (version == nullptr || strlen(version) == 0) {
            TNMPLOG("initHttpBiz deviceId is empty!");
            return;
        }
        if (platformVersion == nullptr || strlen(platformVersion) == 0) {
            TNMPLOG("initHttpBiz platformVersion is empty!");
            return;
        }

        CTNHttpConfig::getInstance()->setToken(token);
        CTNHttpConfig::getInstance()->setUserId(clientId);
        CTNHttpConfig::getInstance()->setDeviceId(deviceId);
        CTNHttpConfig::getInstance()->setToonType(toonType);
        CTNHttpConfig::getInstance()->setAppVersion(version);
        CTNHttpConfig::getInstance()->setPlatformVersion(platformVersion);
        CTNHttpConfig::getInstance()->setCerPath(cerPath);
    }

    void appendHttpRouter(const char *domain, const char *url) {
        if (domain == nullptr || strlen(domain) == 0) {
            TNMPLOG("appendHttpRouter domain is empty!");
            return;
        }

        if (url == nullptr || strlen(url) == 0) {
            TNMPLOG("appendHttpRouter url is empty!");
            return;
        }

        vector<std::string> iplist;
        iplist.push_back(string(url));

        CTNHttpConfig::getInstance()->addDomainIp(domain, iplist);
    }

    ITnGroupChat *getGroupChat() {
        return CTNGroupChat::instance();
    }


    void Feed::serialize(void *writerJson) {
        if (writerJson == nullptr) {
            return;
        }
        
#ifdef RAPIDJSONWRAPPER
        CTNJsonArray* writer = (CTNJsonArray*)writerJson;

        (*writer)["feedId"] = _feedId;
        if (_avatarId.length() > 0) {
            (*writer)["avatarId"] = _avatarId;
        }
        if (_title.length() > 0) {
            (*writer)["title"] = _title;
        }
        (*writer)["userId"] = _userId;
#else
        rapidjson::PrettyWriter<rapidjson::StringBuffer> *writer = (rapidjson::PrettyWriter<rapidjson::StringBuffer> *) writerJson;
        writer->StartObject();
        writer->Key("feedId");
        writer->String(_feedId.c_str(), (unsigned) _feedId.length());
        if (_avatarId.length() > 0) {
            writer->Key("avatarId");
            writer->String(_avatarId.c_str(), (unsigned) _avatarId.length());
        }
        if (_title.length() > 0) {
            writer->Key("title");
            writer->String(_title.c_str(), (unsigned) _title.length());
        }
        writer->Key("userId");
        writer->String(_userId.c_str(), (unsigned) _userId.length());
        writer->EndObject();
#endif
    };


    CTNGroupChat *CTNGroupChat::_instance = nullptr;

    CTNGroupChat *CTNGroupChat::instance() {
        if (_instance == nullptr) {
            _instance = new CTNGroupChat();
        }

        return _instance;
    }

    CTNGroupChat::CTNGroupChat() {

    }

    CTNGroupChat::~CTNGroupChat() {

    }

#ifdef RAPIDJSONWRAPPER
    void createGroupChatProcess(CTNJsonValue &dataValue, CTNBaseInputBean *input) {
        vector<CTNGroupChatInfo> groupChatVector;
        CTNGroupInfo groupInfo;
        groupInfo.parse(&(dataValue.getCTNValue()));
        groupInfo.myFeedId = groupInfo.creatorFeedId;
        
        if (groupInfo.groupId) {
            vector<toonim::CTNGroupInfo> groups;
            groups.push_back(groupInfo);
            toonim::ITnImDBGroupChat *groupChatDB = toonim::getGroupChatDB();
            groupChatDB->addGroupInfo(groups);
        }
    }
#else
    void createGroupChatProcess(rapidjson::Value &dataValue, CTNBaseInputBean *input) {
        if (dataValue.IsObject()) {
            vector<CTNGroupChatInfo> groupChatVector;
            CTNGroupInfo groupInfo;
            groupInfo.parse(&dataValue);
            groupInfo.myFeedId = groupInfo.creatorFeedId;
            
            if (groupInfo.groupId) {
                vector<toonim::CTNGroupInfo> groups;
                groups.push_back(groupInfo);
                toonim::ITnImDBGroupChat *groupChatDB = toonim::getGroupChatDB();
                groupChatDB->addGroupInfo(groups);
            }
        }
    }
#endif

    void CTNGroupChat::createGroupChat(Feed &feed, const char *groupChatName, vector<Feed> &member,
                                       HttpCallback responseFun, void *userData) {

        toonim::ITnImDBSettings *dbSettings = toonim::getSettingsDB();
        if (dbSettings != nullptr && dbSettings->isForbiddenFeature(IM_GROUPCHAT_CREATE_DISABLE)) {
            if (responseFun != nullptr) {
                responseFun(200, "Disable feature!", userData);
            }
            return;
        }

        CTNCreateGroupInput *input = new CTNCreateGroupInput(feed, groupChatName, member);

        CTNBizJsonRequest *request = new CTNBizJsonRequest(input);
        request->setCallback(createGroupChatProcess, responseFun, userData);

        std::string ipString = "";
        if (CTNHttpConfig::getInstance()->getToonIp(DomainChat) != NULL) {
            ipString = CTNHttpConfig::getInstance()->getToonIp(DomainChat);
        }
        ipString += "/user/createGroupChat";

        request->setUrl(ipString.c_str());
        request->enqueue();
    }


    //--------------------获取用户已加入的群聊----------------------
#ifdef RAPIDJSONWRAPPER
    void obtainAllGroupProcess(CTNJsonValue &dataValue, CTNBaseInputBean *context) {
        
        int64_t version = dataValue["version"].getInt64();//ok
        
        vector<toonim::CTNGroupInfo> groupChatVector;
        
        CTNJsonValue& groupChatList = dataValue["groupChatList"];
        
        for (int i = 0; i < groupChatList.getArraySize(); i++) {
            toonim::CTNGroupInfo output;
            output.parse(&groupChatList[i]);
            if (output.status == 1) {
                //1位正常状态，其他状态不存储
                groupChatVector.push_back(output);
            } else {
                ITnImSdk *imsdk = toonim::getImSDK();
                imsdk->dissolveGroup(output.groupId);
            }
            
            std::string sessionId = toonim::generateSessionId(CTNIMMessageTypeGroupChat,
                                                              output.topic,
                                                              output.topic, false);
            if (toonim::getChatDB() != nullptr) {
                toonim::getChatDB()->updateSessionTitleAndImage(sessionId.c_str(),
                                                                output.name.c_str(),
                                                                output.headerImage.c_str());
            }
        }
        
        if (groupChatVector.size() > 0 && toonim::getGroupChatDB() != nullptr) {
            toonim::getGroupChatDB()->addGroupInfo(groupChatVector);
        }
        
//        int64_t version = dataValue["version"].getInt64();
        if (toonim::getSettingsDB() != nullptr) {
            toonim::getSettingsDB()->addSessionSetting("SESSION_TYPE_ALLGROUPVERSION",
                                                       toonim::SESSION_TYPE_ALLGROUPVERSION,
                                                       CTNDBUtils::stringFromInt64(
                                                                                   version).c_str());
        }
    }
#else
    void obtainAllGroupProcess(rapidjson::Value &dataValue, CTNBaseInputBean *context) {
        
        if (dataValue.IsObject()) {
            vector<toonim::CTNGroupInfo> groupChatVector;
            
            if (dataValue.HasMember("groupChatList")) {
                rapidjson::Document::Array groupChatList = dataValue["groupChatList"].GetArray();
                for (int i = 0; i < groupChatList.Size(); i++) {
                    toonim::CTNGroupInfo output;
                    output.parse(&groupChatList[i]);
                    if (output.status == 1) {
                        //1位正常状态，其他状态不存储
                        groupChatVector.push_back(output);
                    } else {
                        ITnImSdk *imsdk = toonim::getImSDK();
                        imsdk->dissolveGroup(output.groupId);
                    }
                    
                    std::string sessionId = toonim::generateSessionId(CTNIMMessageTypeGroupChat,
                                                                      output.topic,
                                                                      output.topic, false);
                    if (toonim::getChatDB() != nullptr) {
                        toonim::getChatDB()->updateSessionTitleAndImage(sessionId.c_str(),
                                                                        output.name.c_str(),
                                                                        output.headerImage.c_str());
                    }
                }
            }
            
            if (groupChatVector.size() > 0 && toonim::getGroupChatDB() != nullptr) {
                toonim::getGroupChatDB()->addGroupInfo(groupChatVector);
            }
            
            int64_t version = dataValue.HasMember("version") ? dataValue["version"].GetInt64()
            : 0;
            if (toonim::getSettingsDB() != nullptr) {
                toonim::getSettingsDB()->addSessionSetting("SESSION_TYPE_ALLGROUPVERSION",
                                                           toonim::SESSION_TYPE_ALLGROUPVERSION,
                                                           CTNDBUtils::stringFromInt64(
                                                                                       version).c_str());
            }
        }
    }
#endif

    void
    CTNGroupChat::obtainAllGroupChat(const char *userId, HttpCallback response, void *userData) {

        CTNBizJsonRequest *request = new CTNBizJsonRequest();
        request->setCallback(obtainAllGroupProcess, response, userData);
        stringstream urlStream;
        std::string ip = "";
        if (CTNHttpConfig::getInstance()->getToonIp(DomainChat) != NULL) {
            ip = CTNHttpConfig::getInstance()->getToonIp(DomainChat);
        }
        toonim::ITnImDBSettings *dbSet = toonim::getSettingsDB();
        CTNSessionSetting setting = dbSet->getSessionSetting("SESSION_TYPE_ALLGROUPVERSION",
                                                             toonim::SESSION_TYPE_ALLGROUPVERSION);
        string version = setting.isValid() ? setting.value : "0";
        urlStream << ip << "/user/obtainGroupChatsByUserId?userId="
                  << userId << "&version=" << version;
        request->setUrl(urlStream.str().c_str());
        request->enqueue();
    }

    //--------------------群聊消息免打扰----------------------

#ifdef RAPIDJSONWRAPPER
    void changeDisturbProcess(CTNJsonValue &dataValue, CTNBaseInputBean *context) {
        if (toonim::getGroupChatDB() != nullptr && context != NULL) {

            CTNChangeDisturbInput *input = dynamic_cast<CTNChangeDisturbInput *>(context);
            toonim::CTNGroupInfo groupInfo = toonim::getGroupChatDB()->getGroupInfo(
                    CTNDBUtils::stringToInt64(input->_groupChatId));
            groupInfo.disturbStatus = input->_disturbStatus;
            vector<CTNGroupInfo> vctGroupinfo;
            vctGroupinfo.push_back(groupInfo);

            toonim::getGroupChatDB()->updateGroupInfo(vctGroupinfo);
        }
    }
#else
    void changeDisturbProcess(rapidjson::Value &dataValue, CTNBaseInputBean *context) {
        if (toonim::getGroupChatDB() != nullptr && context != NULL) {
            
            CTNChangeDisturbInput *input = dynamic_cast<CTNChangeDisturbInput *>(context);
            toonim::CTNGroupInfo groupInfo = toonim::getGroupChatDB()->getGroupInfo(
                                                                                    CTNDBUtils::stringToInt64(input->_groupChatId));
            groupInfo.disturbStatus = input->_disturbStatus;
            vector<CTNGroupInfo> vctGroupinfo;
            vctGroupinfo.push_back(groupInfo);
            
            toonim::getGroupChatDB()->updateGroupInfo(vctGroupinfo);
        }
    }
#endif

    void CTNGroupChat::changeDisturb(const char *feedId, const char *groupChatId,
                                     int32_t disturbStatus,
                                     HttpCallback responseFun, void *userData) {

        CTNChangeDisturbInput *input = new CTNChangeDisturbInput(feedId, "", groupChatId, disturbStatus);

        CTNBizJsonRequest *request = new CTNBizJsonRequest(input);
        request->setCallback(changeDisturbProcess, responseFun, userData);
        stringstream urlStream;
        std::string ip = "";
        if (CTNHttpConfig::getInstance()->getToonIp(DomainChat) != NULL) {
            ip = CTNHttpConfig::getInstance()->getToonIp(DomainChat);
        }
        urlStream << ip << "/user/setupGroupChatDisturb";
        request->setUrl(urlStream.str().c_str());
        request->enqueue();
    }

    //--------------------邀请加入群聊接口----------------------


    void CTNGroupChat::addGroupChatMember(int64_t groupId, const char *myFeedId,
                                          const char *myName, int32_t source,
                                          vector<Feed> &member, HttpCallback responseFun,
                                          void *userData) {

        toonim::ITnImDBSettings *dbSettings = toonim::getSettingsDB();
        if (dbSettings != nullptr &&
            dbSettings->isForbiddenFeature(IM_GROUPCHAT_ADDMEMBER_DISABLE)) {
            if (responseFun != nullptr) {
                responseFun(200, "Disable feature!", userData);
            }
            return;
        }

        CTNAddGroupMemberInput *input = new CTNAddGroupMemberInput(groupId, myFeedId, myName, source,
                                                             member);

        CTNBizJsonRequest *request = new CTNBizJsonRequest(input);
        request->setCallback(nullptr, responseFun, userData);

        std::string ipString = "";
        if (CTNHttpConfig::getInstance()->getToonIp(DomainChat) != NULL) {
            ipString = CTNHttpConfig::getInstance()->getToonIp(DomainChat);
        }
        ipString.append("/user/addGroupChatMembers");

        request->setUrl(ipString.c_str());
        request->enqueue();
    }

    //--------------------获取群聊成员列表接口----------------------
#ifdef RAPIDJSONWRAPPER
    void obtainGroupChatMemberProcess(CTNJsonValue &dataValue, CTNBaseInputBean *context) {
        int64_t version = dataValue["version"].getInt64();
        
        vector<toonim::CTNGroupMember> memberVector;
        CTNJsonValue& memberList = dataValue["memberList"];
        
        for (int i = 0; i < memberList.getArraySize(); i++) {
            toonim::CTNGroupMember output;
            output.parse(&memberList[i]);
            if (output.status == 1 || output.status == 22) {
                //1位正常状态，其他状态不存储
                memberVector.push_back(output);
            } else if (output.status == 0) {
                //0位删除成员
                if (toonim::getGroupChatDB() != nullptr) {
                    toonim::getGroupChatDB()->deleteGroupMember(output.groupId,
                                                                output.feedId.c_str());
                }
            }
            TNMPLOG("obtainGroupChatMember feedid = " << output.feedId);
        }
        
        if (memberVector.size() > 0) {
            toonim::CTNGroupMember groupMember = memberVector.at(0);
            
            TNMPLOG("obtainGroupChatMember by groupId=" << groupMember.groupId
                    << " members="
                    << memberVector.size());
            
            if (toonim::getGroupChatDB() != nullptr) {
                toonim::getGroupChatDB()->addGroupMember(memberVector);
                //add后再修改版本号，防止出现未add数据版本号已修改问题
//                int64_t version = dataValue["version"].getInt64();
                std::ostringstream timeStr;
                timeStr << version;
                std::ostringstream groupId;
                groupId << "SESSION_TYPE_GROUPMEMBERVERSION_" << groupMember.groupId;
                if (toonim::getSettingsDB() != nullptr) {
                    toonim::getSettingsDB()->addSessionSetting(groupId.str().c_str(),
                                                               SESSION_TYPE_GROUPMEMBERVERSION,
                                                               timeStr.str().c_str());
                }
            }
        }
    }
#else
    void obtainGroupChatMemberProcess(rapidjson::Value &dataValue, CTNBaseInputBean *context) {
        if (dataValue.IsObject()) {
            vector<toonim::CTNGroupMember> memberVector;
            if (dataValue.HasMember("memberList")) {
                rapidjson::Document::Array memberList = dataValue["memberList"].GetArray();
                for (int i = 0; i < memberList.Size(); i++) {
                    toonim::CTNGroupMember output;
                    output.parse(&memberList[i]);
                    if (output.status == 1 || output.status == 22) {
                        //1位正常状态，其他状态不存储
                        memberVector.push_back(output);
                    } else if (output.status == 0) {
                        //0位删除成员
                        if (toonim::getGroupChatDB() != nullptr) {
                            toonim::getGroupChatDB()->deleteGroupMember(output.groupId,
                                                                        output.feedId.c_str());
                        }
                    }
                    TNMPLOG("obtainGroupChatMember feedid = " << output.feedId);
                }
            }
            
            if (memberVector.size() > 0) {
                toonim::CTNGroupMember groupMember = memberVector.at(0);
                
                TNMPLOG("obtainGroupChatMember by groupId=" << groupMember.groupId
                        << " members="
                        << memberVector.size());
                
                if (toonim::getGroupChatDB() != nullptr) {
                    toonim::getGroupChatDB()->addGroupMember(memberVector);
                    //add后再修改版本号，防止出现未add数据版本号已修改问题
                    int64_t version = dataValue.HasMember("version")
                    ? dataValue["version"].GetInt64() : 0;
                    std::ostringstream timeStr;
                    timeStr << version;
                    std::ostringstream groupId;
                    groupId << "SESSION_TYPE_GROUPMEMBERVERSION_" << groupMember.groupId;
                    if (toonim::getSettingsDB() != nullptr) {
                        toonim::getSettingsDB()->addSessionSetting(groupId.str().c_str(),
                                                                   SESSION_TYPE_GROUPMEMBERVERSION,
                                                                   timeStr.str().c_str());
                    }
                }
            }
        }
    }
#endif

    void CTNGroupChat::obtainMembersByGroupChatId(const char *groupChatId, HttpCallback responseFun,
                                                  void *userData) {

        CTNBizJsonRequest *request = new CTNBizJsonRequest();
        request->setCallback(obtainGroupChatMemberProcess, responseFun, userData);

        stringstream urlStream;
        std::string ipString = "";
        if (CTNHttpConfig::getInstance()->getToonIp(DomainChat) != NULL) {
            ipString = CTNHttpConfig::getInstance()->getToonIp(DomainChat);
        }

        std::stringstream groupId;
        groupId << "SESSION_TYPE_GROUPMEMBERVERSION_" << groupChatId;
        toonim::ITnImDBSettings *settingDB = toonim::getSettingsDB();
        toonim::CTNSessionSetting setting = settingDB->getSessionSetting(groupId.str().c_str(),
                                                                         SESSION_TYPE_GROUPMEMBERVERSION);
        std::string version = setting.isValid() ? setting.value : "0";
        urlStream << ipString
                  << "/user/obtainGroupChatMembersByGroupChatId?"
                  << "groupChatId=" << groupChatId << "&version="
                  << version;

        TNMPLOG("obtainGroupChatMembersByGroupChatId start request version = " << version);

        request->setUrl(urlStream.str().c_str());
        request->enqueue();
    }

    //--------------------获取每张名片所在的群聊接口----------------------

#ifdef RAPIDJSONWRAPPER
    void obtainGroupChatsProcess(CTNJsonValue &dataValue, CTNBaseInputBean *context) {
        //TODO::parse json hand business or database operate
    }
#else
    void obtainGroupChatsProcess(rapidjson::Value &dataValue, CTNBaseInputBean *context) {
        //TODO::parse json hand business or database operate
    }
#endif

    void
    CTNGroupChat::obtainGroupChatsByFeedIds(vector<string> &feedIdList, const char *userId,
                                            HttpCallback responseFun,
                                            void *userData) {

        CTNObtainGroupByFeedIdsInput *input = new CTNObtainGroupByFeedIdsInput(feedIdList, userId);
        CTNBizJsonRequest *request = new CTNBizJsonRequest(input);
        request->setCallback(obtainGroupChatsProcess, responseFun, userData);
        std::string ipString = "";
        if (CTNHttpConfig::getInstance()->getToonIp(DomainChat) != NULL) {
            ipString = CTNHttpConfig::getInstance()->getToonIp(DomainChat);
        }
        ipString += "/user/obtainGroupChatsByFeedIds";
        request->setUrl(ipString.c_str());
        request->enqueue();
    }


    //--------------------退出群聊接口----------------------

#ifdef RAPIDJSONWRAPPER
    void exitGroupChatProcess(CTNJsonValue &dataValue, CTNBaseInputBean *context) {
        if (context == NULL) {
            return;
        }
        CTNExitGroupChatInput *input = dynamic_cast<CTNExitGroupChatInput *> (context);
        toonim::ITnImDBGroupChat *dbGroup = toonim::getGroupChatDB();
        toonim::ITnImDBChat *dbChat = toonim::getChatDB();

        CTNGroupInfo groupInfo = dbGroup->getGroupInfo(
                CTNDBUtils::stringToInt64(input->_groupChatId));
        //删除群聊
        dbGroup->deleteGroupInfo(CTNDBUtils::stringToInt64(input->_groupChatId));
        //删除群成员
        dbGroup->deleteAllGroupMembers(CTNDBUtils::stringToInt64(input->_groupChatId));
        std::string sessionId = toonim::generateSessionId(CTNIMMessageTypeGroupChat,
                                                          groupInfo.topic, groupInfo.topic,
                                                          false);
        //删除群成员时间戳
        std::ostringstream s;
        s << "SESSION_TYPE_GROUPMEMBERVERSION_" << groupInfo.groupId;
        toonim::getSettingsDB()->deleteSessionSetting(s.str().c_str(),
                                                      SESSION_TYPE_GROUPMEMBERVERSION);
        dbChat->deleteSession(sessionId.c_str());
    }
#else
    void exitGroupChatProcess(rapidjson::Value &dataValue, CTNBaseInputBean *context) {
        if (context == NULL) {
            return;
        }
        CTNExitGroupChatInput *input = dynamic_cast<CTNExitGroupChatInput *> (context);
        toonim::ITnImDBGroupChat *dbGroup = toonim::getGroupChatDB();
        toonim::ITnImDBChat *dbChat = toonim::getChatDB();
        
        CTNGroupInfo groupInfo = dbGroup->getGroupInfo(
                                                       CTNDBUtils::stringToInt64(input->_groupChatId));
        //删除群聊
        dbGroup->deleteGroupInfo(CTNDBUtils::stringToInt64(input->_groupChatId));
        //删除群成员
        dbGroup->deleteAllGroupMembers(CTNDBUtils::stringToInt64(input->_groupChatId));
        std::string sessionId = toonim::generateSessionId(CTNIMMessageTypeGroupChat,
                                                          groupInfo.topic, groupInfo.topic,
                                                          false);
        //删除群成员时间戳
        std::ostringstream s;
        s << "SESSION_TYPE_GROUPMEMBERVERSION_" << groupInfo.groupId;
        toonim::getSettingsDB()->deleteSessionSetting(s.str().c_str(),
                                                      SESSION_TYPE_GROUPMEMBERVERSION);
        dbChat->deleteSession(sessionId.c_str());
    }
#endif

    void CTNGroupChat::exitGroupChat(const char *groupChatId, const char *feedId, const char *title,
                                     HttpCallback responseFun,
                                     void *userData) {
        CTNExitGroupChatInput *input = new CTNExitGroupChatInput(groupChatId, feedId, title);
        CTNBizJsonRequest *request = new CTNBizJsonRequest(input);
        request->setCallback(exitGroupChatProcess, responseFun, userData);
        std::string ipString = "";
        if (CTNHttpConfig::getInstance()->getToonIp(DomainChat) != NULL) {
            ipString = CTNHttpConfig::getInstance()->getToonIp(DomainChat);
        }
        ipString += "/user/quitGroupChat";

        request->setUrl(ipString.c_str());
        request->enqueue();
    }

    //--------------------批量移除群成员接口----------------------

#ifdef RAPIDJSONWRAPPER
    void removeGroupChatMembersProcess(CTNJsonValue &dataValue, CTNBaseInputBean *context) {
#else
    void removeGroupChatMembersProcess(rapidjson::Value &dataValue, CTNBaseInputBean *context) {
#endif
        if (toonim::getGroupChatDB() == nullptr || context == NULL) {
            return;
        }
        CTNRemoveGroupChatMembersInput *input = dynamic_cast<CTNRemoveGroupChatMembersInput *>(context);
        for (int i = 0; i < input->_memberList.size(); i++) {
            Feed feed = input->_memberList.at(i);
            if (feed._feedId.length() <= 0) {
                continue;
            }
            toonim::getGroupChatDB()->deleteGroupMember(input->_groupChatId, feed._feedId.c_str());
        }
    }

    void
    CTNGroupChat::removeGroupChatMembers(const char *feedId, const char *title, int64_t groupChatId,
                                         vector<Feed> &removeList,
                                         HttpCallback responseFun,
                                         void *userData) {
        toonim::ITnImDBSettings *dbSettings = toonim::getSettingsDB();
        if (dbSettings != nullptr &&
            dbSettings->isForbiddenFeature(IM_GROUPCHAT_RMMEMBER_DISABLE)) {
            if (responseFun != nullptr) {
                responseFun(200, "Disable feature!", userData);
            }
            return;
        }

        CTNRemoveGroupChatMembersInput *input = new CTNRemoveGroupChatMembersInput(feedId, title,
                                                                             groupChatId,
                                                                             removeList);
        CTNBizJsonRequest *request = new CTNBizJsonRequest(input);
        request->setCallback(removeGroupChatMembersProcess, responseFun, userData);
        std::string ipString = "";
        if (CTNHttpConfig::getInstance()->getToonIp(DomainChat) != NULL) {
            ipString = CTNHttpConfig::getInstance()->getToonIp(DomainChat);
        }
        ipString += "/user/removeGroupChatMembers";

        request->setUrl(ipString.c_str());
        request->enqueue();
    }


    //--------------------批量移除feed下所有群聊接口----------------------


    void CTNGroupChat::removeGroupChatMembersByFeedId(const char *feedId, const char *userId,
                                                      const char *title,
                                                      HttpCallback responseFun, void *userData) {
        CTNBizJsonRequest *request = new CTNBizJsonRequest();
        request->setCallback(nullptr, responseFun, userData);
        std::string urlStream = "";
        if (CTNHttpConfig::getInstance()->getToonIp(DomainChat) != NULL) {
            urlStream = CTNHttpConfig::getInstance()->getToonIp(DomainChat);
        }
        urlStream += "/user/removeGroupChatMembersByCardFeedId?";
        urlStream += "feedId=";
        urlStream += feedId;
        urlStream += "&userId=";
        urlStream += userId;
        urlStream += "&title=";
        urlStream += curl_escape(title, 0);
        request->setUrl(urlStream.c_str());
        request->enqueue();
    }

    //--------------------修改群聊名称接口----------------------

#ifdef RAPIDJSONWRAPPER
    void updateGroupChatProcess(CTNJsonValue &dataValue, CTNBaseInputBean *context) {
#else
        void updateGroupChatProcess(rapidjson::Value &dataValue, CTNBaseInputBean *context) {
#endif

        if (context == NULL) {
            return;
        }
        CTNAddGroupMemberInput *input = dynamic_cast<CTNAddGroupMemberInput *>(context);
        TNMPLOG("update groupChatName groupId= " << input->groupChatId << ", newName="
                                                 << input->groupChatName);
        //因为修改名称后会收到群聊变更的消息，会增量更新群聊信息，这里不需要更新db
//            toonim::ITnImDBGroupChat *dbGroup = toonim::getGroupChatDB();
//            CTNGroupInfo info = dbGroup->getGroupInfo(_groupChatId);
//            info.name = _newGroupName;
//            vector<CTNGroupInfo> vctGroup;
//            if (info.groupId > 0) {
//                vctGroup.push_back(info);
//            }
//            dbGroup->updateGroupInfo(vctGroup);
    }

    void CTNGroupChat::updateGroupChat(int64_t groupChatId, const char *newGroupName,
                                       const char *myFeedId,
                                       const char *myName, HttpCallback responseFun,
                                       void *userData) {

        CTNAddGroupMemberInput *input = new CTNAddGroupMemberInput();
        input->groupChatId = groupChatId;
        input->groupChatName = newGroupName;
        input->feedId = myFeedId;
        input->title = myName;

        CTNBizJsonRequest *request = new CTNBizJsonRequest(input);
        request->setCallback(updateGroupChatProcess, responseFun, userData);
        std::string ipString = "";
        if (CTNHttpConfig::getInstance()->getToonIp(DomainChat) != NULL) {
            ipString = CTNHttpConfig::getInstance()->getToonIp(DomainChat);
        }
        ipString += "/user/updateGroupChat";

        request->setUrl(ipString.c_str());
        request->enqueue();
    }

    //--------------------批量获取群聊信息接口----------------------
#ifdef RAPIDJSONWRAPPER
    void obtainGroupChatInfoProcess(CTNJsonValue &dataValue, CTNBaseInputBean *context) {
        //需要判断是否为自己的群聊，进行存储
        vector<toonim::CTNGroupInfo> groupChatVector;
        CTNJsonValue& groupChatList = dataValue["groupChatList"];
        
        vector<CTNGroupInfo> groupVct;
        for (int i = 0; i < groupChatList.getArraySize(); i++) {
            toonim::CTNGroupInfo output;
            output.parse(&groupChatList[i]);
            bool isMyFeed = CTNChatManager::instance()->isMySelfFeed(output.myFeedId);
            if (isMyFeed) {
                groupVct.push_back(output);
            }
        }
        if (groupVct.size() > 0 && toonim::getGroupChatDB() != nullptr) {
            toonim::getGroupChatDB()->addGroupInfo(groupVct);
        }
    }
#else
        void obtainGroupChatInfoProcess(rapidjson::Value &dataValue, CTNBaseInputBean *context) {
            //需要判断是否为自己的群聊，进行存储
            if (dataValue.IsObject()) {
                vector<toonim::CTNGroupInfo> groupChatVector;
                
                if (dataValue.HasMember("groupChatList")) {
                    rapidjson::Document::Array groupChatList = dataValue["groupChatList"].GetArray();
                    vector<CTNGroupInfo> groupVct;
                    for (int i = 0; i < groupChatList.Size(); i++) {
                        toonim::CTNGroupInfo output;
                        output.parse(&groupChatList[i]);
                        bool isMyFeed = CTNChatManager::instance()->isMySelfFeed(output.myFeedId);
                        if (isMyFeed) {
                            groupVct.push_back(output);
                        }
                    }
                    if (groupVct.size() > 0 && toonim::getGroupChatDB() != nullptr) {
                        toonim::getGroupChatDB()->addGroupInfo(groupVct);
                    }
                }
            }
        }
#endif

    void
    CTNGroupChat::obtainGroupChatInfo(vector<string> &groupChatIdList, HttpCallback responseFun,
                                      void *userData) {
        CTNObtainGroupChatInfoInput *input = new CTNObtainGroupChatInfoInput(groupChatIdList);
        CTNBizJsonRequest *request = new CTNBizJsonRequest(input);
        request->setCallback(obtainGroupChatInfoProcess, responseFun, userData);
        std::string ipString = "";
        if (CTNHttpConfig::getInstance()->getToonIp(DomainChat) != NULL) {
            ipString = CTNHttpConfig::getInstance()->getToonIp(DomainChat);
        }
        ipString += "/user/obtainGroupChatInfoByGroupChatIdList";

        request->setUrl(ipString.c_str());
        request->enqueue();
    }

    //-------------------群主转让----------------

    void
    CTNGroupChat::groupChatTransferOwner(int64_t groupChatId, const char *feedId, const char *title,
                                         toonim::Feed memberFeed, HttpCallback responseFun,
                                         void *userData) {

        CTNTransferGroupChatOwnerInput *input = new CTNTransferGroupChatOwnerInput(groupChatId, feedId,
                                                                             title, memberFeed);
        CTNBizJsonRequest *request = new CTNBizJsonRequest(input);
        request->setCallback(nullptr, responseFun, userData);
        std::string ipString = "";
        if (CTNHttpConfig::getInstance()->getToonIp(DomainChat) != NULL) {
            ipString = CTNHttpConfig::getInstance()->getToonIp(DomainChat);
        }
        ipString += "/user/groupChatTransferOwner";

        request->setUrl(ipString.c_str());
        request->enqueue();
    }

    void
    CTNGroupChat::setupGroupChatVerify(int64_t groupChatId, int32_t verityStatus, HttpCallback responseFun,
                                         void *userData) {

        CTNSwitchVerityInput *input = new CTNSwitchVerityInput(groupChatId, verityStatus);
        CTNBizJsonRequest *request = new CTNBizJsonRequest(input);
		request->setCallback(nullptr, responseFun, userData);
        std::string ipString = "";
        if (CTNHttpConfig::getInstance()->getToonIp(DomainChat) != NULL) {
            ipString = CTNHttpConfig::getInstance()->getToonIp(DomainChat);
        }
        ipString += "/user/setupGroupChatVerify";

        request->setUrl(ipString.c_str());
        request->enqueue();
    }

}
