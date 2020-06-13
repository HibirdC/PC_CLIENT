//
//  CTNDBSettings.cpp
//  CTNSDK
//
//  Created by 王海涛 on 2017/8/23.
//  Copyright © 2017年 syswin. All rights reserved.
//

#include "CTNDBSettings.hpp"
#include <sstream>
#include <assert.h>
#include <string.h>
#include <CLog.h>
#include "CTNDBGroupChat.hpp"
#include "CTNChatManager.hpp"
#include "CTNDBUtils.hpp"
#include "CTNDBChat.hpp"

namespace toonim {
  
    ITnImDBSettings* getSettingsDB() {
        return CTNDBSetting::instance();
    }
    
    CTNDBSetting* CTNDBSetting::_instance = nullptr;
    
    CTNDBSetting* CTNDBSetting::instance()
    {
        //防止出现未初始化调用崩溃问题
//        assert(_instance != nullptr);
        
        return _instance;
    }
    
    CTNDBSetting* CTNDBSetting::instance(const char* clientId, const char* appPath)
    {
        if (_instance == nullptr) {
            _instance = new CTNDBSetting();
        }
        
        string oldUserId = instance()->getClientId();
        
        _instance->doInitUserDB(clientId, IMCHATDB, appPath);
        _instance->initAtSwitchStatus();
        
        if (oldUserId != clientId) {
            _instance->loadSettingDisturbCache();
            _instance->loadBlackListCache();
        }
                
        return _instance;
    }
    
    CTNDBSetting::CTNDBSetting()
    {
    }
    
    CTNDBSetting::~CTNDBSetting()
    {
        
    }
    
    void CTNDBSetting::createTable()
    {
        this->beginTransation();
        this->execSql("create table if not exists SessionSettings(sessionId text not null, type int not null, value text default '', primary key(sessionId,type))");
        this->execSql("create index if not exists SessionSettings_index on SessionSettings('sessionId' asc)");
        
        this->execSql("CREATE TABLE IF NOT EXISTS BlackList(feedId text, passiveFeedId text, status integer, primary key(feedId, passiveFeedId))");
        this->execSql("CREATE INDEX IF NOT EXISTS BlackList_index ON BlackList('feedId', 'passiveFeedId')");
        this->commitTransation();
        
    }
    
#pragma mark -----------settings----------------
    bool CTNDBSetting::addSessionSetting(const char* sessionId, CTNSESSIONTYPE type, const char* value) {
        if (sessionId == nullptr || sessionId[0] == '\0' || value == nullptr || value[0] == '\0') {
            return false;
        }
        
        std::ostringstream s;
        s << "replace into SessionSettings(sessionId,type,value)values('" << sessionId << "'," << type << ",'" << value << "')";
        std::string sql = s.str();
        this->execSql(sql.c_str());
        
        TNMPLOG("add sessionSettings with sessionId=" << sessionId << ", value=" << value);
        
        return true;
    }
    
    bool CTNDBSetting::addSessionSettings(vector<CTNSessionSetting>& vecSessionSetting) {
        if (vecSessionSetting.size() <= 0) {
            return false;
        }
        
        this->beginTransation();
        for (int i = 0; i < vecSessionSetting.size(); ++i) {
            CTNSessionSetting setting = vecSessionSetting.at(i);
            map<string, pair<CTNDBBase::FT, string>> info;
            info["sessionId"] = make_pair(CTNDBBase::DB_STR, setting.sessionId);
            info["type"] = make_pair(CTNDBBase::DB_INT, CTNDBUtils::stringFromInt32(setting.type));
            info["value"] = make_pair(CTNDBBase::DB_STR, setting.value);
            
            insertRecord("SessionSettings", info);
        }
        this->commitTransation();
        
        return true;
    }

    bool CTNDBSetting::updateSessionSetting(const char* sessionId, CTNSESSIONTYPE type, const char* value)
    {
        if (sessionId == nullptr || sessionId[0] == '\0' || value == nullptr || value[0] == '\0') {
            return false;
        }
        
        map<string, pair<CTNDBBase::FT, string>> info;
        info["sessionId"] = make_pair(CTNDBBase::DB_STR, sessionId);
        info["type"] = make_pair(CTNDBBase::DB_INT, CTNDBUtils::stringFromInt32(type));
        info["value"] = make_pair(CTNDBBase::DB_STR, value);
        
        replaceRecord("SessionSettings", info);
        
        return true;
    }
    
    bool CTNDBSetting::deleteSessionSetting(const char* sessionId, CTNSESSIONTYPE type)
    {
        if (sessionId == nullptr || sessionId[0] == '\0') {
            return false;
        }
        
        std::ostringstream s;
        s << "delete from SessionSettings where sessionId='" << sessionId << "' and type=" << type;
        std::string sql = s.str();
        this->execSql(sql.c_str());
        
        return true;
    }
    
    void CTNDBSetting::loadSettingDisturbCache()
    {
        vector<CTNGroupInfo> groupDisturb;
        if (toonim::getGroupChatDB() != nullptr) {
            groupDisturb = CTNDBGroupChat::instance()->getGroupDisturb();
        }
        vector<CTNBlackListModel> blackDisturb = this->getDisturbList();
        CSafeMap<std::string, int32_t> disturbMap;
        
        for (int i=0; i<groupDisturb.size(); i++) {
            CTNGroupInfo groupInfo = groupDisturb.at(i);
            std::string sessionId = toonim::generateSessionId(CTNIMMessageTypeGroupChat, groupInfo.topic, groupInfo.topic, true);
            disturbMap[sessionId] = 1;
        }
        
        for (int i=0; i<blackDisturb.size(); i++) {
            CTNBlackListModel blackModel = blackDisturb.at(i);
            if (CTNChatManager::instance()->isMySelfFeed(blackModel.feedId)) {
                std::string sessionId = toonim::generateSessionId(CTNIMMessageTypeChat, blackModel.feedId, blackModel.passiveFeedId, true);
                disturbMap[sessionId] = 1;
            }
        }

        _mpCacheSetDisturb = disturbMap;
    }
    
    CTNSessionSetting CTNDBSetting::getSessionSetting(const char* sessionId, CTNSESSIONTYPE type)
    {
        if (sessionId == nullptr || strlen(sessionId) == 0) {
            return CTNSessionSetting();
        }
        
        std::ostringstream s;
        s << "select sessionId,type,value from SessionSettings where sessionId='" << sessionId << "' and type=" << type;
        std::string sql = s.str();
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
        
        CTNSessionSetting seting = CTNSessionSetting();
        
        if (records == NULL) {
            return seting;
        }
        
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            seting = this->generateSetting(records);
        }
        
        return seting;
    }
    
    //获取免打扰数据，缓存
    int32_t CTNDBSetting::getSessionSettingDisturb(const char* sessionId){
        if (sessionId == nullptr || strlen(sessionId) == 0) {
            return 0;
        }
        
        int32_t iDisturb = 0;
        map<string,int>::iterator key = _mpCacheSetDisturb.find(sessionId);
        if (key != _mpCacheSetDisturb.end()){
            iDisturb = key->second;
        }
        
        return iDisturb;
    }
    
    void CTNDBSetting::loadSettingCache()
    {
        _instance->loadSettingDisturbCache();
        _instance->loadBlackListCache();
        _instance->loadFollowListCache();
    }
    
#pragma mark -----------important---------------------
    bool CTNDBSetting::setImportantSwitch(CTNIMMessageType type, bool status)
    {
        if (type == CTNIMMessageTypeAt) {
            this->setAtMessageSwitch(status);
        }
        
        return true;
    }
    
    bool CTNDBSetting::getImportantStatus(CTNIMMessageType type)
    {
        if (type == CTNIMMessageTypeAt) {
            return this->getAtMessaeSwitch();
        }
        
        return false;
    }
    
    void CTNDBSetting::setAtMessageSwitch(bool status)
    {
        std::ostringstream s;
        s << status;
        std::string str = s.str();
        this->updateSessionSetting("SESSION_TYPE_ATMESSAGE", SESSION_TYPE_ATMESSAGE, str.c_str());
        _isAtSwitchOn = status;
        
        //关闭at消息开关时需要清楚at表存储的消息
        if (!status && toonim::getChatDB() != nullptr) {
            toonim::getChatDB()->deleteAllImportantMessage(CTNIMMessageTypeAt);
        }
    }
    
    bool CTNDBSetting::getAtMessaeSwitch()
    {
        return _isAtSwitchOn;
    }
    
    //初始化at开关状态，以后每次去的时候直接取_isAtSwitchOn的值，不需要每次都查数据库
    void CTNDBSetting::initAtSwitchStatus()
    {
        CTNSessionSetting setting = this->getSessionSetting("SESSION_TYPE_ATMESSAGE", SESSION_TYPE_ATMESSAGE);
        if (setting.isValid()) {
            int32_t status = std::atoi(setting.value.c_str());
            _isAtSwitchOn = status;
        } else {
            //默认设置为开的状态，再次进行设置时只改变状态，不删除
            _isAtSwitchOn = true;
        }
    }
    
    void CTNDBSetting::setFollowFeedId(const char* feedId, bool status)
    {
        if (feedId == nullptr || strlen(feedId) == 0) {
            return;
        }
        
        std::ostringstream s;
        s << "SESSION_TYPE_FOLLOWMESSAGE_" << feedId;
        if (status) {
            //value保存为feedId，获取烈表示时可以直接用value的值
            this->updateSessionSetting(s.str().c_str(), SESSION_TYPE_FOLLOWMESSAGE, feedId);
        } else {
            //取消时删除
            this->deleteSessionSetting(s.str().c_str(), SESSION_TYPE_FOLLOWMESSAGE);
            if (toonim::getChatDB() != nullptr) {
                toonim::getChatDB()->deleteFollowFeedId(feedId);
            }
        }
        
        this->loadFollowListCache();
    }
    
    void CTNDBSetting::setFollowFeedIdList(const vector<toonim::CTNFollowFeed> &followList)
    {
        if (followList.size() <= 0) {
            return;
        }
        
        this->beginTransation();
        for (int i=0; i<followList.size(); i++) {
            CTNFollowFeed followFeed = followList.at(i);
            std::ostringstream s;
            s << "SESSION_TYPE_FOLLOWMESSAGE_" << followFeed.feedId;
            if (followFeed.status) {
                //value保存为feedId，获取烈表示时可以直接用value的值
                this->updateSessionSetting(s.str().c_str(), SESSION_TYPE_FOLLOWMESSAGE, followFeed.feedId.c_str());
            } else {
                //取消时删除
                this->deleteSessionSetting(s.str().c_str(), SESSION_TYPE_FOLLOWMESSAGE);
                if (toonim::getChatDB() != nullptr) {
                    toonim::getChatDB()->deleteFollowFeedId(followFeed.feedId.c_str());
                }
            }
        }
        this->commitTransation();
        
        this->loadFollowListCache();
    }
    
    vector<std::string> CTNDBSetting::getMyFollowFeedList()
    {
        vector<std::string> list;
        
        std::ostringstream s;
        s << "select * from SessionSettings where type=" << SESSION_TYPE_FOLLOWMESSAGE;
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(s.str().c_str());
        
        if (records == nullptr) {
            return list;
        }
        
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            CTNSessionSetting setting = this->generateSetting(records);
            if (setting.isValid()) {
                list.push_back(setting.value);
            }
        }
        
        return list;
    }
    
    bool CTNDBSetting::getFollowSwitch(const char* feedId)
    {
        std::ostringstream s;
        s << "SESSION_TYPE_FOLLOWMESSAGE_" << feedId;
        CTNSessionSetting setting = this->getSessionSetting(s.str().c_str(), SESSION_TYPE_FOLLOWMESSAGE);
        
        if (setting.isValid()) {
            int32_t status = std::atoi(setting.value.c_str());
            return status;
        } else {
            return false;
        }
    }
    
    void CTNDBSetting::loadFollowListCache()
    {
        std::ostringstream s;
        s << "select * from SessionSettings where type = '" << SESSION_TYPE_FOLLOWMESSAGE << "'";
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(s.str().c_str());
        
        if (records == NULL) {
            return;
        }
        
        CSafeMap<std::string, int32_t> followMap;
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            CTNSessionSetting setting = this->generateSetting(records);
            if (setting.isValid()) {
                followMap[setting.value] = 1;
            }
        }
        
        _mpCacheFollowList = followMap;
    }
    
    bool CTNDBSetting::isFollowMessage(CTNMessage &message)
    {
        if (message.isEmpty() || _mpCacheFollowList.size() == 0) {
            return false;
        }
        
        map<std::string, int32_t>::iterator key = _mpCacheFollowList.find(message.fromId);
        if (key != _mpCacheFollowList.end()) {
            return true;
        }
        return false;
    }
    
    bool CTNDBSetting::isAtSwitchOn()
    {
        return _isAtSwitchOn;
    }
    
    int32_t CTNDBSetting::getFollowFeedIdsCount()
    {
        return (int32_t)_mpCacheFollowList.size();
    }

#pragma mark -----------blackList---------------------
    bool CTNDBSetting::addBlackList(const char* feedId, const char* passiveFeedId, int32_t status)
    {
        if (feedId == nullptr || passiveFeedId == nullptr || strlen(feedId) == 0 || strlen(passiveFeedId) == 0) {
            return false;
        }
        
        std::ostringstream s;
        s << "insert into BlackList(feedId,passiveFeedId,status)values('" << feedId << "','" << passiveFeedId << "'," << status << ")";
        std::string sql = s.str();
        this->execSql(sql.c_str());
        
        std::ostringstream logs;
        logs << "insert BlackList feedid=" << feedId << " and passiveFeedId=" << passiveFeedId;
        TNMPLOG(logs.str());
        
        this->loadSettingDisturbCache();
        this->loadBlackListCache();
        
        return true;
    }
    
    bool CTNDBSetting::deleteBlackList(vector<CTNBlackListModel>& blackList)
    {
        if (blackList.size() <= 0) {
            return false;
        }
        
        this->beginTransation();
        for (int i=0; i<blackList.size(); i++) {
            CTNBlackListModel model = blackList.at(i);
            if (!model.isValid()) {
                continue;
            }
            
            std::ostringstream s;
            s << "delete from BlackList where feedId='" << model.feedId << "' and passiveFeedId='" << model.passiveFeedId << "'";
            std::string sql = s.str();
            this->execSql(sql.c_str());
        }
        this->commitTransation();
        
        this->loadSettingDisturbCache();
        this->loadBlackListCache();
        
        return true;
    }
    
    bool CTNDBSetting::updateBlackList(vector<CTNBlackListModel>& blackList)
    {
        if (blackList.size() <= 0) {
            return false;
        }
        
        this->beginTransation();
        for (int i=0; i<blackList.size(); i++) {
            CTNBlackListModel model = blackList.at(i);
            if (!model.isValid()) {
                continue;
            }
            
            std::ostringstream s;
            if (model.status == 0) {
                s << "delete from BlackList where feedId='" << model.feedId << "' and passiveFeedId='" << model.passiveFeedId << "'";
            } else {
                s << "replace into BlackList (feedId,passiveFeedId,status)values('"  << model.feedId << "','" << model.passiveFeedId << "'," << model.status << ")";
            }
            
            std::string sql = s.str();
            this->execSql(sql.c_str());
        }
        this->commitTransation();

        this->loadSettingDisturbCache();
        this->loadBlackListCache();
        
        return true;
    }
    
    vector<toonim::CTNBlackListModel> CTNDBSetting::getBlackList(const char* feedId)
    {
        std::ostringstream s;
        if (feedId == nullptr || strlen(feedId) == 0) {
            s << "select * from BlackList where (status & 1)=1";
        } else {
            s << "select * from BlackList where (status & 1)=1 and feedId='" << feedId << "'";
        }
        std::string sql = s.str();
        
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
        CTNBlackListModel blackModel = CTNBlackListModel();
        vector<toonim::CTNBlackListModel> blackList;

        if (records == NULL) {
            return blackList;
        }

        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            blackModel = this->generateBlackList(records);
            if (blackModel.isValid()){
                blackList.push_back(blackModel);
            }
        }
        
        return blackList;
    }
    
    vector<CTNBlackListModel> CTNDBSetting::getDisturbList()
    {
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql("select * from BlackList where (2 & status) = 2");
        vector<CTNBlackListModel> vctDisturb;
        
        if (records == NULL) {
            return vctDisturb;
        }
        
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            CTNBlackListModel blackModel = this->generateBlackList(records);
            if (blackModel.isValid()){
                vctDisturb.push_back(blackModel);
            }
        }
        
        return vctDisturb;
    }
    
#define BLK_KEY(feedId, passiveFeedId) (string(feedId)+"_"+string(passiveFeedId))
    
    CTNBlackListModel CTNDBSetting::getBlackModel(const char* feedId, const char* passiveFeedId)
    {
        if (feedId == nullptr || passiveFeedId == nullptr || strlen(feedId) == 0 || strlen(passiveFeedId) == 0) {
            return CTNBlackListModel();
        }
        
        std::string strKey = BLK_KEY(feedId, passiveFeedId);
        
        CTNBlackListModel blackModel;
        map<string, CTNBlackListModel>::iterator key = _mpCacheBlackList.find(strKey);
        if(key != _mpCacheBlackList.end()){
            blackModel = key->second;
            TNMPLOG("getBlackModel:"<<strKey<<" status:"<<blackModel.status);
        }

  
        return blackModel;
    }
    
    CTNBlackListModel CTNDBSetting::getBlackAndDisturbModel(const char* feedId, const char* passiveFeedId){
        if (feedId == nullptr || passiveFeedId == nullptr || strlen(feedId) == 0 || strlen(passiveFeedId) == 0) {
            return CTNBlackListModel();
        }
        
        ostringstream s;
        s << "select * from BlackList where feedId='" << feedId << "' and passiveFeedId='" << passiveFeedId << "'";
        std::string sql = s.str();
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
        CTNBlackListModel blackModel;
        
        if (records == nullptr) {
            return blackModel;
        }
        
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            blackModel = this->generateBlackList(records);
        }
        
        return blackModel;
    }
    
   void CTNDBSetting::loadBlackListCache(){
       
       ostringstream s;
       s << "select * from BlackList where (1 & status) = 1";
       std::string sql = s.str();
        
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
        if (records == nullptr) {
            return ;
        }
       
       CSafeMap<std::string, CTNBlackListModel> blackListMap;
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            CTNBlackListModel blackModel = this->generateBlackList(records);
            if (!blackModel.isValid()){
                continue;
            }
            
            std::string strKey = BLK_KEY(blackModel.feedId.c_str(), blackModel.passiveFeedId.c_str());
            blackListMap[strKey] = blackModel;
            TNMPLOG("load blacklist:"<<strKey<<" status:"<<blackModel.status);
        }
       
       _mpCacheBlackList = blackListMap;
    }
    
#pragma mark -----------dataResult--------------------
    CTNSessionSetting CTNDBSetting::generateSetting(CSqliteDBStatement *stmt)
    {
        CTNSessionSetting setting;
        setting.sessionId = stmt->getString(0);
        setting.type = stmt->getInt(1);
        setting.value = stmt->getString(2);
        
        return setting;
    }
    
    CTNBlackListModel CTNDBSetting::generateBlackList(CSqliteDBStatement *stmt)
    {
        CTNBlackListModel blackListModel;
        blackListModel.feedId = stmt->getString(0);
        blackListModel.passiveFeedId = stmt->getString(1);
        blackListModel.status = stmt->getInt(2);
        
        return blackListModel;
    }
    
    void CTNDBSetting::setForbiddenFeatureMap(std::map<string, int>  &mapForbidden)
    {
        _forbiddenMap.clear();
        
        std::map<string, int>::iterator iter = mapForbidden.begin();
        while (iter != mapForbidden.end()){
            _forbiddenMap[iter->first] = iter->second;
            
            iter++;
        }
    }
    
    bool CTNDBSetting::isForbiddenFeature(const char* key)
    {
        if (key == nullptr || strlen(key) == 0 || _forbiddenMap.empty()){
            return  false;
        }
        
        std::map<std::string, int32_t>::iterator itFind = _forbiddenMap.find(key);
        if (itFind == _forbiddenMap.end()){
            return false;
        }
        
        if (itFind->second == 0){
            return false;
        }
        
        TNMPLOG("isForbiddenFeature true:"<<key);
        return true;
    }
    
}

