//
// Created by juzenhon on 2017/9/7.
//

//#include "TestRequest.h"
#include <CLog.h>
#include "CTNSettings.h"
#include "CTNRequest.h"
#include "CTNDBHeader.h"
#include "CTNDBAPI.h"
#include "CTNDBUtils.hpp"
#include "CTNBizInuputBean.h"
#include "CTNJsonUtils.hpp"


const char *DomainApp = "api.app.systoon.com";
const char *DomainConnect = "new.contact.systoon.com";

//using namespace rapidjson;

namespace toonim {


    ITnSettings *getSettings() {
        return CTNSettings::instance();
    }


    CTNSettings *CTNSettings::_instance = nullptr;

    CTNSettings *CTNSettings::instance() {
        if (_instance == nullptr) {
            _instance = new CTNSettings();
        }

        return _instance;
    }

#ifdef RAPIDJSONWRAPPER
    void conversationSwitchProcess(CTNJsonValue &dataValue, CTNBaseInputBean *context) {
        if (toonim::getChatDB() != nullptr && context != NULL) {
            CTNConversionSwitchInput *input = dynamic_cast<CTNConversionSwitchInput *>(context);
            //_chatId.length() > 0 &&
            CTNSession session = toonim::getChatDB()->getSession(input->_new_sessionId.c_str());
            session.topStatus = input->_status;
            session.sortTime = input->_updateTime;
            vector<CTNSession> vctSession;
            vctSession.push_back(session);
            toonim::getChatDB()->updateSession(vctSession);
        }
    }
#else
    void conversationSwitchProcess(rapidjson::Value &dataValue, CTNBaseInputBean *context) {
        if (toonim::getChatDB() != nullptr && context != NULL) {
            CTNConversionSwitchInput *input = dynamic_cast<CTNConversionSwitchInput *>(context);
            //_chatId.length() > 0 &&
            CTNSession session = toonim::getChatDB()->getSession(input->_new_sessionId.c_str());
            session.topStatus = input->_status;
            session.sortTime = input->_updateTime;
            vector<CTNSession> vctSession;
            vctSession.push_back(session);
            toonim::getChatDB()->updateSession(vctSession);
        }
    }
#endif

    void
    CTNSettings::setSessionSwitchTop(const char *chatId, const char *myfeedId, int32_t chatType,
                                     bool top, int64_t timestamp, HttpCallback responseFun,
                                     void *userData) {
        string to = chatId;
        CTNConversionSwitchInput *input = new CTNConversionSwitchInput();
        TNMPLOG("setSessionSwitchTop:chatId:" << to << " type " << chatType);
        input->_sessionId = to;
        if (chatType == 52) {
            input->_sessionId += "-";
            input->_sessionId += myfeedId;
        } else if (chatType == 53) {
            if (to.compare(0, 3, "gc_") != 0) {
                input->_sessionId = "gc_" + to;
                to = input->_sessionId;
            }
        }
        input->_chatType = chatType;
        input->_status = top ? 1 : 0;
        input->_updateTime = timestamp;
        input->_new_sessionId = toonim::generateSessionId(chatType, myfeedId, to, true);;
        TNMPLOG("setSessionSwitchTop:sessionId:" << input->_new_sessionId);
        CTNBizJsonRequest *request = new CTNBizJsonRequest(input);
        request->setCallback(conversationSwitchProcess, responseFun, userData);
        std::string ipString = "";
        if (CTNHttpConfig::getInstance()->getToonIp(DomainChat) != NULL) {
            ipString = CTNHttpConfig::getInstance()->getToonIp(DomainChat);
        }
        ipString += "/user/setupGroupChatSwitch";

        request->setUrl(ipString.c_str());
        request->enqueue();
    }

#pragma mark -----------SwitchOnDisturbAndBlackList-------------

#ifdef RAPIDJSONWRAPPER
    void switchOnDisturbAndBlackListProcess(CTNJsonValue &dataValue, CTNBaseInputBean *context) {
        if (toonim::getSettingsDB() != nullptr && context != NULL) {
            CTNSwitchDisturbAndBlackListInput *input = dynamic_cast<CTNSwitchDisturbAndBlackListInput *>(context);
            CTNBlackListModel model = toonim::getSettingsDB()->getBlackAndDisturbModel(
                    input->_feedId.c_str(), input->_passiveFeedId.c_str());
            int32_t status = model.status | input->_bizType;

            vector<CTNBlackListModel> blackList;
            model.feedId = input->_feedId;
            model.passiveFeedId = input->_passiveFeedId;
            model.status = status;
            blackList.push_back(model);

            toonim::getSettingsDB()->updateBlackList(blackList);
        }
    }
#else
    void switchOnDisturbAndBlackListProcess(rapidjson::Value &dataValue, CTNBaseInputBean *context) {
        if (toonim::getSettingsDB() != nullptr && context != NULL) {
            CTNSwitchDisturbAndBlackListInput *input = dynamic_cast<CTNSwitchDisturbAndBlackListInput *>(context);
            CTNBlackListModel model = toonim::getSettingsDB()->getBlackAndDisturbModel(
                                                                                       input->_feedId.c_str(), input->_passiveFeedId.c_str());
            int32_t status = model.status | input->_bizType;
            
            vector<CTNBlackListModel> blackList;
            model.feedId = input->_feedId;
            model.passiveFeedId = input->_passiveFeedId;
            model.status = status;
            blackList.push_back(model);
            
            toonim::getSettingsDB()->updateBlackList(blackList);
        }
    }
#endif

    void CTNSettings::switchOnDisturbAndBlackList(const char *feedId, const char *passiveFeedId,
                                                  const char *passiveUserId, int32_t bizType,
                                                  HttpCallback responseFun, void *userData) {
        CTNSwitchDisturbAndBlackListInput *input = new CTNSwitchDisturbAndBlackListInput(feedId,
                                                                                   passiveFeedId,
                                                                                   passiveUserId,
                                                                                   bizType);
        CTNBizJsonRequest *request = new CTNBizJsonRequest(input);
        request->setCallback(switchOnDisturbAndBlackListProcess, responseFun, userData);
        std::string ipString = "";
        if (CTNHttpConfig::getInstance()->getToonIp(DomainConnect) != NULL) {
            ipString = CTNHttpConfig::getInstance()->getToonIp(DomainConnect);
        }
        ipString += "/user/switchOn";

        request->setUrl(ipString.c_str());
        request->enqueue();
    }

#pragma mark ------------switchOffDisturbAndBlackList---------

#ifdef RAPIDJSONWRAPPER
    void switchOffDisturbAndBlackListProcess(CTNJsonValue &dataValue, CTNBaseInputBean *context) {
        if (toonim::getSettingsDB() != NULL && context != NULL) {
            CTNSwitchDisturbAndBlackListInput *input = dynamic_cast<CTNSwitchDisturbAndBlackListInput*>(context);
            CTNBlackListModel model = toonim::getSettingsDB()->getBlackAndDisturbModel(
                    input->_feedId.c_str(), input->_passiveFeedId.c_str());
            int32_t status = model.status & (~input->_bizType);
            vector<CTNBlackListModel> blackList;
            model.feedId = input->_feedId;
            model.passiveFeedId = input->_passiveFeedId;
            model.status = status;
            blackList.push_back(model);
            if (status == 0) {
                //删除
                toonim::getSettingsDB()->deleteBlackList(blackList);
            } else {
                //更新
                toonim::getSettingsDB()->updateBlackList(blackList);
            }
        }
    }
#else
    void switchOffDisturbAndBlackListProcess(rapidjson::Value &dataValue, CTNBaseInputBean *context) {
        if (toonim::getSettingsDB() != NULL && context != NULL) {
            CTNSwitchDisturbAndBlackListInput *input = dynamic_cast<CTNSwitchDisturbAndBlackListInput*>(context);
            CTNBlackListModel model = toonim::getSettingsDB()->getBlackAndDisturbModel(
                                                                                       input->_feedId.c_str(), input->_passiveFeedId.c_str());
            int32_t status = model.status & (~input->_bizType);
            vector<CTNBlackListModel> blackList;
            model.feedId = input->_feedId;
            model.passiveFeedId = input->_passiveFeedId;
            model.status = status;
            blackList.push_back(model);
            if (status == 0) {
                //删除
                toonim::getSettingsDB()->deleteBlackList(blackList);
            } else {
                //更新
                toonim::getSettingsDB()->updateBlackList(blackList);
            }
        }
    }
#endif

    void CTNSettings::switchOffDisturbAndBlackList(const char *feedId, const char *passiveFeedId,
                                                   const char *passiveUserId, int32_t bizType,
                                                   HttpCallback responseFun, void *userData) {
        CTNSwitchDisturbAndBlackListInput *input = new CTNSwitchDisturbAndBlackListInput(feedId, passiveFeedId, passiveUserId, bizType);
        CTNBizJsonRequest *request = new CTNBizJsonRequest(input);
        request->setCallback(switchOffDisturbAndBlackListProcess,responseFun,userData);
        std::string ipString = "";
        if (CTNHttpConfig::getInstance()->getToonIp(DomainConnect) != NULL) {
            ipString = CTNHttpConfig::getInstance()->getToonIp(DomainConnect);
        }
        ipString += "/user/switchOff";

        request->setUrl(ipString.c_str());
        request->enqueue();
    }

#pragma mark --------------QuerySwitchDisturbAndBlackLis------------

#ifdef RAPIDJSONWRAPPER
        void querySwitchDisturbAndBlackListProcess(CTNJsonValue &dataValue, CTNBaseInputBean * context) {
            
            int64_t version = 0;
            version = dataValue["version"].getInt64();//ok
            
            CTNJsonValue& array = dataValue["userSwitches"];
            
            vector<CTNBlackListModel> blackList;
            vector<CTNBlackListModel> deleteData;
            
            for (int i = 0; i < array.getArraySize(); ++i) {
                int status = 0;
                status = array[i]["status"].getInt32();
                
                CTNBlackListModel model;
                model.parse(&array[i]);
                
                if (status == 0) {
                    //状态为0删除数据
                    deleteData.push_back(model);
                } else {
                    blackList.push_back(model);
                }
            }
            
            if (blackList.size() > 0 && toonim::getSettingsDB() != nullptr) {
                toonim::getSettingsDB()->updateBlackList(blackList);
            }
            
            if (deleteData.size() > 0 && toonim::getSettingsDB() != nullptr) {
                toonim::getSettingsDB()->deleteBlackList(deleteData);
            }
            
            ostringstream s;
            s << version;
            if (toonim::getSettingsDB() != nullptr) {
                toonim::getSettingsDB()->updateSessionSetting("SESSION_TYPE_BLACKLIST",
                                                              toonim::SESSION_TYPE_BLACKLIST,
                                                              s.str().c_str());
            }
        }
#else
    void querySwitchDisturbAndBlackListProcess(rapidjson::Value &dataValue, CTNBaseInputBean * context) {
        if (dataValue.IsObject()) {
            if (dataValue.HasMember("userSwitches") && dataValue["userSwitches"].IsArray()) {
                rapidjson::Document::Array switchArray = dataValue["userSwitches"].GetArray();
                vector<CTNBlackListModel> blackList;
                vector<CTNBlackListModel> deleteData;
                
                for (int32_t i = 0; i < switchArray.Size(); i++) {
                    rapidjson::Value *jsonValue = &switchArray[i];
                    int status = 0;
                    if (jsonValue->HasMember("status") && (*jsonValue)["status"].IsInt()) {
                        status = (*jsonValue)["status"].GetInt();
                    }
                    
                    CTNBlackListModel model;
                    model.parse(jsonValue);
                    
                    if (status == 0) {
                        //状态为0删除数据
                        deleteData.push_back(model);
                    } else {
                        blackList.push_back(model);
                    }
                }
                
                if (blackList.size() > 0 && toonim::getSettingsDB() != nullptr) {
                    toonim::getSettingsDB()->updateBlackList(blackList);
                }
                
                if (deleteData.size() > 0 && toonim::getSettingsDB() != nullptr) {
                    toonim::getSettingsDB()->deleteBlackList(deleteData);
                }
                
                int64_t version = 0;
                if (dataValue.HasMember("version") && dataValue["version"].IsInt64()) {
                    version = dataValue["version"].GetInt64();
                }
                
                ostringstream s;
                s << version;
                if (toonim::getSettingsDB() != nullptr) {
                    toonim::getSettingsDB()->updateSessionSetting("SESSION_TYPE_BLACKLIST",
                                                                  toonim::SESSION_TYPE_BLACKLIST,
                                                                  s.str().c_str());
                }
            }
        }
    }
#endif

    void CTNSettings::querySwitchDisturbAndBlackList(HttpCallback responseFun, void *userData) {
        CTNBizJsonRequest *request = new CTNBizJsonRequest();
        request->setCallback(querySwitchDisturbAndBlackListProcess,responseFun,userData);
        stringstream urlStream;
        toonim::ITnImDBSettings *dbSet = toonim::getSettingsDB();
        CTNSessionSetting setting = dbSet->getSessionSetting("SESSION_TYPE_BLACKLIST",
                                                             toonim::SESSION_TYPE_BLACKLIST);
        std::string timestamp = "0";
        if (setting.value.length() > 0) {
            timestamp = setting.value;
        }

        std::string ip = "";
        if (CTNHttpConfig::getInstance()->getToonIp(DomainConnect) != NULL) {
            ip = CTNHttpConfig::getInstance()->getToonIp(DomainConnect);
        }
        urlStream << ip
                  << "/user/querySwitchInfo?" << "version=" << timestamp;

        request->setUrl(urlStream.str().c_str());
        request->enqueue();
    }

#pragma mark ------------top-------------------

#ifdef RAPIDJSONWRAPPER
        void getAllTopSessionProcess(CTNJsonValue &dataValue, CTNBaseInputBean* context) {
            int64_t version = 0;
            
            version = dataValue["version"].getInt64();
            
            CTNJsonValue& array = dataValue["groupChatSwitchList"];
            
            vector<CTNSession> vctSession;
            for (int32_t i = 0; i < array.getArraySize(); ++i) {
                int32_t chatType = 0;
                std::string chatId;
                int64_t updateTime = 0;
                int32_t status = 0;
                
                chatType = array[i]["chatType"].getInt32();
                chatId = array[i]["sessionId"].getString();
                updateTime = array[i]["updateTime"].getInt64();
                status = array[i]["status"].getInt32();
                
                std::string sessionId;
                if (chatType == CTNIMMessageTypeGroupChat ||
                    chatType == CTNIMMessageTypeBizNotice) {
                    sessionId = chatId;
                } else {
                    const char *d = "-";
                    int32_t j = 0;
                    std::string from;
                    std::string to;
                    char *s = new char[strlen(chatId.c_str()) + 1];
                    strcpy(s, chatId.c_str());
                    char *subStr = strtok(s, d);
                    
                    while (subStr != nullptr) {
                        printf("%s\n", subStr);
                        if (j == 0) {
                            from = subStr;
                        } else {
                            to = subStr;
                        }
                        subStr = strtok(NULL, d);
                        j++;
                    }
                    
                    sessionId = toonim::generateSessionId(CTNIMMessageTypeChat, from, to,
                                                          false);
                    
                    delete[] s;
                }
                
                CTNSession session;
                if (toonim::getChatDB() != nullptr) {
                    session = toonim::getChatDB()->getSession(sessionId.c_str());
                }
                
                //标记为非置顶时不需要创建新的session会话
                if (session.sessionId.length() <= 0 && status == 0) {
                    continue;
                }
                
                if (session.sessionId.length() <= 0) {
                    session.sessionId = sessionId;
                }
                session.type = chatType;
                session.topStatus = status;
                session.sortTime = updateTime / 1000;
                if (session.lastTime == 0) {
                    session.lastTime = session.sortTime;
                }
                
                vctSession.push_back(session);
            }
            
            if (toonim::getChatDB() != nullptr) {
                toonim::getChatDB()->updateSession(vctSession);
            }
            
//            int64_t version = 0;
//
//            version = dataValue["version"].getInt64();
//
            if (toonim::getSettingsDB() != nullptr) {
                toonim::getSettingsDB()->updateSessionSetting("SESSION_TYPE_TOP",
                                                              toonim::SESSION_TYPE_TOP,
                                                              CTNDBUtils::stringFromInt64(
                                                                                          version).c_str());
            }
        }
#else
    void getAllTopSessionProcess(rapidjson::Value &dataValue, CTNBaseInputBean* context) {
        if (dataValue.IsObject()) {
            if (dataValue.HasMember("groupChatSwitchList") && dataValue["groupChatSwitchList"].IsArray()) {
                rapidjson::Document::Array topArray = dataValue["groupChatSwitchList"].GetArray();
                vector<CTNSession> vctSession;
                
                for (int32_t i = 0; i < topArray.Size(); i++) {
                    rapidjson::Value *jsonValue = &topArray[i];
                    int32_t chatType = 0;
                    std::string chatId;
                    int64_t updateTime = 0;
                    int32_t status = 0;
                    
                    if (jsonValue->HasMember("chatType") && (*jsonValue)["chatType"].IsInt()) {
                        chatType = (*jsonValue)["chatType"].GetInt();
                    }
                    if (jsonValue->HasMember("sessionId") && (*jsonValue)["sessionId"].IsString()) {
                        chatId = (*jsonValue)["sessionId"].GetString();
                    }
                    if (jsonValue->HasMember("updateTime") && (*jsonValue)["updateTime"].IsInt64()) {
                        updateTime = (*jsonValue)["updateTime"].GetInt64();
                    }
                    if (jsonValue->HasMember("status") && (*jsonValue)["status"].IsInt()) {
                        status = (*jsonValue)["status"].GetInt();
                    }
                    
                    std::string sessionId;
                    if (chatType == CTNIMMessageTypeGroupChat ||
                        chatType == CTNIMMessageTypeBizNotice) {
                        sessionId = chatId;
                    } else {
                        const char *d = "-";
                        int32_t j = 0;
                        std::string from;
                        std::string to;
                        char *s = new char[strlen(chatId.c_str()) + 1];
                        strcpy(s, chatId.c_str());
                        char *subStr = strtok(s, d);
                        
                        while (subStr != nullptr) {
                            printf("%s\n", subStr);
                            if (j == 0) {
                                from = subStr;
                            } else {
                                to = subStr;
                            }
                            subStr = strtok(NULL, d);
                            j++;
                        }
                        
                        sessionId = toonim::generateSessionId(CTNIMMessageTypeChat, from, to,
                                                              false);
                        
                        delete[] s;
                    }
                    
                    CTNSession session;
                    if (toonim::getChatDB() != nullptr) {
                        session = toonim::getChatDB()->getSession(sessionId.c_str());
                    }
                    
                    //标记为非置顶时不需要创建新的session会话
                    if (session.sessionId.length() <= 0 && status == 0) {
                        continue;
                    }
                    
                    if (session.sessionId.length() <= 0) {
                        session.sessionId = sessionId;
                    }
                    session.type = chatType;
                    session.topStatus = status;
                    session.sortTime = updateTime / 1000;
                    if (session.lastTime == 0) {
                        session.lastTime = session.sortTime;
                    }
                    
                    vctSession.push_back(session);
                }
                
                if (toonim::getChatDB() != nullptr) {
                    toonim::getChatDB()->updateSession(vctSession);
                }
                if (dataValue.HasMember("version") && dataValue["version"].IsInt64()) {
                    int64_t version = 0;
                    version = dataValue["version"].GetInt64();
                    if (toonim::getSettingsDB() != nullptr) {
                        toonim::getSettingsDB()->updateSessionSetting("SESSION_TYPE_TOP",
                                                                      toonim::SESSION_TYPE_TOP,
                                                                      CTNDBUtils::stringFromInt64(
                                                                                                  version).c_str());
                    }
                }
            }
        }
    }
#endif

    void
    CTNSettings::getAllSwitchTopSession(int64_t timestamp, HttpCallback responseFun, void *userData) {

        CTNBizJsonRequest *request = new CTNBizJsonRequest();
        request->setCallback(getAllTopSessionProcess,responseFun,userData);
        stringstream urlStream;
        std::string ip = "";
        if (CTNHttpConfig::getInstance()->getToonIp(DomainChat) != NULL) {
            ip = CTNHttpConfig::getInstance()->getToonIp(DomainChat);
        }
        urlStream << ip
                  << "/user/getGroupChatSwitch?" << "version=" << timestamp;

        request->setUrl(urlStream.str().c_str());
        request->enqueue();
    }

#pragma mark --------------appList---------------

#ifdef RAPIDJSONWRAPPER
    void obtainAppListInfoProcess(CTNJsonValue &dataValue, CTNBaseInputBean *context) {
        
        int64_t version = 0;
        version = dataValue["version"].getInt64();//ok
        
        CTNJsonValue& array = dataValue["noticeInfos"];
        vector<CTNAppInfo> vctAppAdd;
        
        if (toonim::getGroupChatDB() == nullptr) {
            return;
        }
        
        for (int32_t i = 0; i < array.getArraySize(); i++) {
            toonim::CTNAppInfo appinfo;
            appinfo.parse(&array[i]);
            if (appinfo.isDelete == 0) {
                //新增或修改
                vctAppAdd.push_back(appinfo);
            } else {
                //删除
                toonim::getGroupChatDB()->deleteAppInfo(appinfo.appId.c_str());
            }
        }
        
        toonim::getGroupChatDB()->updateAppInfo(vctAppAdd);
        
//        int64_t version = 0;
//        version = dataValue["version"].getInt64();
        if (toonim::getSettingsDB() != nullptr) {
            toonim::getSettingsDB()->addSessionSetting("SESSION_TYPE_appInfoVersion",
                                                       toonim::SESSION_TYPE_appInfoVersion,
                                                       CTNDBUtils::stringFromInt64(
                                                                                   version).c_str());
        }
    }
#else
    void obtainAppListInfoProcess(rapidjson::Value &dataValue, CTNBaseInputBean *context) {
        if (dataValue.IsObject()) {
            if (dataValue.HasMember("noticeInfos")) {
                vector<CTNAppInfo> vctAppAdd;
                rapidjson::Document::Array array = dataValue["noticeInfos"].GetArray();
                
                if (toonim::getGroupChatDB() == nullptr) {
                    return;
                }
                
                for (int32_t i = 0; i < array.Size(); i++) {
                    toonim::CTNAppInfo appinfo;
                    appinfo.parse(&array[i]);
                    if (appinfo.isDelete == 0) {
                        //新增或修改
                        vctAppAdd.push_back(appinfo);
                    } else {
                        //删除
                        toonim::getGroupChatDB()->deleteAppInfo(appinfo.appId.c_str());
                    }
                }
                
                toonim::getGroupChatDB()->updateAppInfo(vctAppAdd);
            }
            
            if (dataValue.HasMember("version")) {
                int64_t version = 0;
                version = dataValue["version"].GetInt64();
                if (toonim::getSettingsDB() != nullptr) {
                    toonim::getSettingsDB()->addSessionSetting("SESSION_TYPE_appInfoVersion",
                                                               toonim::SESSION_TYPE_appInfoVersion,
                                                               CTNDBUtils::stringFromInt64(
                                                                                           version).c_str());
                }
            }
        }
    }
#endif

    void CTNSettings::obtainAppListInfo(HttpCallback responseFun, void *userData) {
        CTNBizJsonRequest *request = new CTNBizJsonRequest();
        request->setCallback(obtainAppListInfoProcess, responseFun, userData);
        stringstream urlStream;
        toonim::ITnImDBSettings *dbSet = toonim::getSettingsDB();
        CTNSessionSetting setting = dbSet->getSessionSetting("SESSION_TYPE_appInfoVersion",
                                                             toonim::SESSION_TYPE_appInfoVersion);
        std::string timestamp = "0";
        if (setting.value.length() > 0) {
            timestamp = setting.value;
        }

        std::string ip = "";
        if (CTNHttpConfig::getInstance()->getToonIp(DomainApp) != NULL) {
            ip = CTNHttpConfig::getInstance()->getToonIp(DomainApp);
        }
        urlStream << ip << "/user/getAppNoticeListInfo?" << "version=" << timestamp;

        request->setUrl(urlStream.str().c_str());
        request->enqueue();
    }

#pragma mark ----------obtainAppinfoWithAppid---------------

#ifdef RAPIDJSONWRAPPER
    void obtainAppInfoProcess(CTNJsonValue &dataValue, CTNBaseInputBean *context) {
        toonim::CTNAppInfo appInfo;
        appInfo.parse(&dataValue);
        
        vector<CTNAppInfo> vctAppAdd;
        if (appInfo.appId.length() > 0) {
            vctAppAdd.push_back(appInfo);
        }
        
        if (toonim::getGroupChatDB() != nullptr) {
            toonim::getGroupChatDB()->addAppInfo(vctAppAdd);
        }
    }
#else
    void obtainAppInfoProcess(rapidjson::Value &dataValue, CTNBaseInputBean *context) {
        if (dataValue.IsObject()) {
            toonim::CTNAppInfo appInfo;
            appInfo.parse(&dataValue);
            
            vector<CTNAppInfo> vctAppAdd;
            if (appInfo.appId.length() > 0) {
                vctAppAdd.push_back(appInfo);
            }
            
            if (toonim::getGroupChatDB() != nullptr) {
                toonim::getGroupChatDB()->addAppInfo(vctAppAdd);
            }
        }
    }
#endif

    void CTNSettings::obtainAppInfo(const char *appId, HttpCallback responseFun, void *userData) {

        CTNBizJsonRequest *request = new CTNBizJsonRequest();
        request->setCallback(obtainAppInfoProcess, responseFun, userData);

        stringstream urlStream;
        std::string ip = "";
        if (CTNHttpConfig::getInstance()->getToonIp(DomainApp) != NULL) {
            ip = CTNHttpConfig::getInstance()->getToonIp(DomainApp);
        }
        urlStream << ip
                  << "/user/getAppNoticeByAppId?" << "appId=" << appId;

        request->setUrl(urlStream.str().c_str());
        request->enqueue();
    }
}
