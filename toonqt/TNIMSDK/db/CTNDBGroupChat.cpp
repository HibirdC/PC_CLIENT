//
//  CTNDBGroupChat.cpp
//  CTNSDK
//
//  Created by 王海涛 on 2017/8/23.
//  Copyright © 2017年 syswin. All rights reserved.
//

#include "CTNDBGroupChat.hpp"
#include <sstream>
#include <assert.h>
#include <string.h>
#include <CLog.h>

#include "CTNDBUtils.hpp"
#include "rapidjson.h"
#include "document.h"
#include "writer.h"
#include "stringbuffer.h"
#include "pointer.h"
#include "CTNDBSettings.hpp"
#include "CTNBaseBean.h"

using namespace std;

namespace toonim {
    
#define CLBGROUPDB_VER  2
    
    ITnImDBGroupChat* getGroupChatDB()
    {
        return CTNDBGroupChat::instance();
    }
    
    
    
    CTNDBGroupChat* CTNDBGroupChat::_instance = nullptr;
    
    CTNDBGroupChat* CTNDBGroupChat::instance()
    {
        //防止出现未初始化调用崩溃问题
//        assert(_instance != nullptr);
        
        return _instance;
    }
    
    CTNDBGroupChat* CTNDBGroupChat::instance(const char* clientId, const char* appPath)//wxy 调整初始化逻辑，获取单例时初始化一次数据库创建一次数据库表格
    {
        if (_instance == nullptr) {
            _instance = new CTNDBGroupChat();
        }
        _instance->doInitUserDB(clientId, IMGROUPCHATDB, appPath);
        
        return _instance;
    }
    
    CTNDBGroupChat::CTNDBGroupChat(){
        //std::cout<<"CTNDBGroupChat"<<endl;
    }
    
    void CTNDBGroupChat::createTable()
    {
        this->beginTransation();
        this->execSql(
                "CREATE TABLE IF NOT EXISTS GroupInfo(groupId UNSIGNED BIG INT not null PRIMARY KEY,creatorFeedId text, name text, namePinyin text, pinyinHeader text,headerImage text, topic text, myFeedId text, maxNum int default 0,currNum int,version int, disturbStatus int, pinyin text, verify int);");
        this->execSql("CREATE INDEX if not exists GroupInfo_index ON GroupInfo('topic' ASC,'groupId' ASC,'creatorFeedId' ASC,'myFeedId' ASC, 'version' asc);");
        
        this->execSql("CREATE TABLE IF NOT EXISTS GroupMember(groupId UNSIGNED BIG INT not null, groupTopic text, feedId text not null, name text, namePinyin text, namePinyinHeader text, remarkName text, remarkNamePinyin text, remarkNamePinyinHeader text, headerImage text, status int, timestamp int, PRIMARY KEY(groupId, feedId));");
        this->execSql("CREATE INDEX if not exists GroupMember_index ON GroupMember('groupId' ASC,'groupTopic' ASC,'feedId' ASC, 'status' ASC, 'timestamp' asc);");
        
        this->execSql("create table if not exists CTNAppInfo(appId text not null primary key, appCode text default '', appTitle text default '', appLittleIcon text default '', chatFlag inteter)");
        this->execSql("create index if not exists CTNAppInfo_index on CTNAppInfo('appId' asc)");
        this->commitTransation();
        TNMPLOG("create GroupInfo GroupMember CTNAppInfo table");
        
    }
    
#pragma mark -------------GroupInfo-------------
    bool CTNDBGroupChat::addGroupInfo(vector<CTNGroupInfo>& groups)
    {
        if (groups.size() <= 0) {
            return false;
        }
        
        this->beginTransation();
        for (int i=0; i<groups.size(); i++) {
            CTNGroupInfo groupInfo = groups.at(i);
            if (groupInfo.groupId <= 0) {
                continue;
            }
            
            map<string, pair<CTNDBBase::FT, string>> info;
            this->genGroupInfoMap(groupInfo, info);
            replaceRecord("GroupInfo", info);
            
            std::string sessionId = toonim::generateSessionId(CTNIMMessageTypeGroupChat, groupInfo.topic, groupInfo.topic, false);
            if (getChatDB() != nullptr) {
                std::string groupName = groupInfo.name;
                std::string headerImage = groupInfo.headerImage;
                getChatDB()->updateSessionTitleAndImage(sessionId.c_str(), groupName.c_str(), headerImage.c_str());
            }
        }
        this->commitTransation();
        
        //更新免打扰缓存
        if (toonim::getSettingsDB() != nullptr) {
            ((CTNDBSetting *)toonim::getSettingsDB())->loadSettingDisturbCache();
        }
        
        return true;
    }
    
    bool CTNDBGroupChat::updateGroupInfo(vector<CTNGroupInfo>& groups)
    {
        if (groups.size() <= 0) {
            return false;
        }
        
        this->beginTransation();
        for (int i=0; i<groups.size(); i++) {
            CTNGroupInfo groupInfo = groups.at(i);
            if (groupInfo.groupId <= 0) {
                continue;
            }
            
            map<string, pair<CTNDBBase::FT, string>> info;
            this->genGroupInfoMap(groupInfo, info);
            replaceRecord("GroupInfo", info);
            
            std::string sessionId = toonim::generateSessionId(CTNIMMessageTypeGroupChat, groupInfo.topic, groupInfo.topic, false);
            if (getChatDB() != nullptr) {
                std::string groupName = groupInfo.name;
                std::string headerImage = groupInfo.headerImage;
                getChatDB()->updateSessionTitleAndImage(sessionId.c_str(), groupName.c_str(), headerImage.c_str());
            }
        }
        this->commitTransation();
        
        //更新免打扰缓存
        if (toonim::getSettingsDB() != nullptr) {
            ((CTNDBSetting *)toonim::getSettingsDB())->loadSettingDisturbCache();
        }
        
        return true;
    }
    
    void CTNDBGroupChat::genGroupInfoMap(CTNGroupInfo &groupInfo, map<string, pair<CTNDBBase::FT, string>> &info)
    {
        info["groupId"] = make_pair(CTNDBBase::DB_LONG, CTNDBUtils::stringFromInt64(groupInfo.groupId));
        info["creatorFeedId"] = make_pair(CTNDBBase::DB_STR, groupInfo.creatorFeedId);
        info["name"] = make_pair(CTNDBBase::DB_STR, groupInfo.name);
        info["pinyin"] = make_pair(CTNDBBase::DB_STR, groupInfo.pinyin);
        info["namePinyin"] = make_pair(CTNDBBase::DB_STR, groupInfo.namePinyin);
        info["pinyinHeader"] = make_pair(CTNDBBase::DB_STR, groupInfo.pinyinHeader);
        info["headerImage"] = make_pair(CTNDBBase::DB_STR, groupInfo.headerImage);
        info["topic"] = make_pair(CTNDBBase::DB_STR, groupInfo.topic);
        info["myFeedId"] = make_pair(CTNDBBase::DB_STR, groupInfo.myFeedId);
        info["maxNum"] = make_pair(CTNDBBase::DB_INT, CTNDBUtils::stringFromInt32(groupInfo.maxNum));
        info["currNum"] = make_pair(CTNDBBase::DB_INT, CTNDBUtils::stringFromInt32(groupInfo.currNum));
        info["version"] = make_pair(CTNDBBase::DB_LONG, CTNDBUtils::stringFromInt64(groupInfo.version));
        info["disturbStatus"] = make_pair(CTNDBBase::DB_INT, CTNDBUtils::stringFromInt32(groupInfo.disturbStatus));
        info["verify"] = make_pair(CTNDBBase::DB_INT, CTNDBUtils::stringFromInt32(groupInfo.verify));
    }
    
    bool CTNDBGroupChat::deleteGroupInfo(int64_t groupId)
    {
        if (groupId <= 0) {
            return false;
        }
        
        std::ostringstream s;
        s << "delete from GroupInfo where groupId=" << groupId;
        std::string sql = s.str();
        this->execSql(sql.c_str());
        
        return true;
    }
    
    CTNGroupInfo CTNDBGroupChat::getGroupInfo(int64_t groupId)
    {
        if (groupId <= 0) {
            return CTNGroupInfo();
        }
        
        std::ostringstream s;
        s << "select * from GroupInfo where groupId=" << groupId;
        std::string sql = s.str();
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
        CTNGroupInfo groupInfo = CTNGroupInfo();
        
        if (records == NULL) {
            return groupInfo;
        }
        
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            groupInfo = this->generateGroupInfo(records);
        }
        
        return groupInfo;
    }
    
    vector<CTNGroupInfo> CTNDBGroupChat::getGroupDisturb()
    {
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql("select * from GroupInfo where disturbStatus=1");
        
        vector<CTNGroupInfo> groupVct;
        if (records == NULL) {
            return groupVct;
        }
        
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            CTNGroupInfo groupInfo = this->generateGroupInfo(records);
            groupVct.push_back(groupInfo);
        }
        
        return groupVct;
    }
    
    void CTNDBGroupChat::upgradeTableWithOldVersion(){
        std::unique_lock<std::mutex> unilock(m_mutex);
        int64_t oldVersion = 0;
        int64_t version = CLBGROUPDB_VER;
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql("pragma user_version");
        if (nullptr == records) {
            return;
        }
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            oldVersion = records->getLong(0);
        }
        
        //把imchat库里的群聊、群成员、应用表对应的内容迁移到imgroupchat
        if (oldVersion == 0) {
            std::string sql = "attach DataBase '";
            sql += _appPath;
            sql += IMCHATDB;
            sql += _clientId;
            sql += ".db' as NewChatDB";
#ifdef ENCODE_DATABASE
            sql += " KEY '";
            sql += toonim::CTNDBUtils::generateEncryptKey(_clientId);
            sql += "'";
#endif
            
            if (!this->execSql(sql.c_str())) {
                TNMPLOG("attach dataBase failure");
            }
            
            if (_sqliteDb->existTableOrColom("GroupInfo", nullptr, "NewChatDB")){
                sql = "insert into GroupInfo select a.groupId,a.creatorFeedId,a.name,a.namePinyin,a.pinyinHeader,a.headerImage,a.topic,a.myFeedId,a.maxNum,a.currNum,a.version,a.disturbStatus,'',0 from NewChatDB.GroupInfo as a";
                if (this->execSql(sql.c_str())) {
                    this->execSql("drop table NewChatDB.GroupInfo");
                } else {
                    TNMPLOG("move GroupInfo to imgroupchat failure");
                }
                
                sql = "insert into GroupMember select a.groupId,a.groupTopic,a.feedId,a.name,a.namePinyin,a.namePinyinHeader,a.remarkName,a.remarkNamePinyin,a.remarkNamePinyinHeader,a.headerImage,a.status,a.timestamp from NewChatDB.GroupMember as a";
                if (this->execSql(sql.c_str())) {
                    this->execSql("drop table NewChatDB.GroupMember");
                } else {
                    TNMPLOG("move GroupMember to imgroupchat failure");
                }
            }
            
            if (_sqliteDb->existTableOrColom("CTNAppInfo", nullptr, "NewChatDB")){
                sql = "insert into CTNAppInfo select a.appId,a.appCode,a.appTitle,a.appLittleIcon,a.chatFlag from NewChatDB.CTNAppInfo as a";
                if (this->execSql(sql.c_str())) {
                    this->execSql("drop table NewChatDB.CTNAppInfo");
                } else {
                    TNMPLOG("move CTNAppInfo to imgroupchat failure");
                }
            }
            
            this->execSql("detach database NewChatDB");
        }
        
        if (oldVersion < version) {
            switch (oldVersion) {
                case 1:{
                    this->execSql("alter table GroupInfo add pinyin text");
                    this->execSql("alter table GroupInfo add verify INTEGER DEFAULT 0");
                }
                    
                default:
                    break;
            }
        }
        
        std::ostringstream s;
        s << "pragma user_version=" << version << "";
        this->execSql(s.str().c_str());
    }
    
    vector<toonim::CTNGroupInfo> CTNDBGroupChat::getGroupInfoWithMyFeedId(const char*  feedId)
    {
        std::ostringstream s;
        if (feedId == nullptr || strlen(feedId) == 0) {
            s << "select * from GroupInfo order by version desc";
        } else {
            s << "select * from GroupInfo where myFeedId='" << feedId << "' order by version desc";
        }
        std::string sql = s.str();
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
        vector<toonim::CTNGroupInfo> vGroup;
        
        if (records == NULL) {
            return vGroup;
        }
        
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            CTNGroupInfo groupInfo = this->generateGroupInfo(records);
            vGroup.push_back(groupInfo);
        }
        
        return vGroup;
    }
    
    
    /*
     1、判断keyword是否包含中文或emoji，包含中文或emoji直接根据name like搜索（暂时使用外层object-c代码判断）
     2、不包含中文，则根据拼音搜
       2.1、字符长度大于1，首先取keyword第一位，去搜首字母字段，能搜到，则过滤整个keyword是否包含在pinyin或pinyinHeader中
       2.2、字符长度等于1，直接搜pinyinHeader like
       *避免随便一个字母，都能根据拼音搜索到（例如输入a，如果用like %a%，则liang也能搜到）
     */
    void CTNDBGroupChat::searchGroupInfo(const char* keyword, const char* feedId, vector<toonim::CTNGroupInfo> &groupInofs)
    {
        if (keyword == nullptr || strlen(keyword) == 0) {
            return;
        }
        std::ostringstream s;
        if (feedId == nullptr || strlen(feedId) == 0) {
            s << "select * from GroupInfo where name like '%%" << keyword << "%%' order by namePinyin,groupId asc";
        } else {
            s << "select * from GroupInfo where name like '%%" << keyword << "%%' and myFeedId = '" << feedId << "' order by namePinyin,groupId asc";
        }
        std::string sql = s.str();
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
        
        if (records == NULL) {
            return;
        }
        
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            CTNGroupInfo groupInfo = this->generateGroupInfo(records);
            groupInofs.push_back(groupInfo);
        }
    }
    
    void CTNDBGroupChat::searchGroupInfoWithPinyin(const char* keyword, const char* feedId, vector<toonim::CTNGroupInfo> &groupInofs)
    {
        if (keyword != nullptr && strlen(keyword) > 1) {
            std::string strKeyword = keyword;
            std::string header = strKeyword.substr(0,1);
            std::ostringstream s;
            if (feedId == nullptr || strlen(feedId) == 0) {
                s << "select * from GroupInfo where pinyinHeader like '%%" << header << "%%' order by namePinyin,groupId asc";
            } else {
                s << "select * from GroupInfo where pinyinHeader like '%%" << header << "%%' and myFeedId = '" << feedId << "' order by namePinyin,groupId asc";
            }
            std::string sql = s.str();
            CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
            
            if (records == NULL) {
                return;
            }
            
            while (records->step() == CSqliteDBStatement::STEP_ROW) {
                CTNGroupInfo groupInfo = this->generateGroupInfo(records);
                
                std::string pinyinHeader = groupInfo.pinyinHeader;

                if (pinyinHeader.find(strKeyword) != pinyinHeader.npos) {
                    groupInofs.push_back(groupInfo);
                    continue;
                }
                
                std::string namePinyin = groupInfo.namePinyin;
                std::string sep = "**";
                std::string::size_type pos = namePinyin.find(sep);
                if (pos != namePinyin.npos) {
                    if (CTNDBUtils::isEqualAOE(header)) {
                        std::string namePinyinAOE = namePinyin.substr(pos+sep.length(), namePinyin.length()-pos-sep.length());
                        std::string aoeKeyword = strKeyword;
                        aoeKeyword.insert(0, "*");
                        if (namePinyinAOE.find(aoeKeyword) != namePinyinAOE.npos) {
                            groupInofs.push_back(groupInfo);
                        }else {
                            if (namePinyinAOE.find_first_of("*") != namePinyinAOE.find_last_of("*")) {
                                if (namePinyin.find(strKeyword) != namePinyin.npos) {
                                    groupInofs.push_back(groupInfo);
                                }
                            }
                        }
                    }else {
                        if (namePinyin.find(strKeyword) != namePinyin.npos) {
                            groupInofs.push_back(groupInfo);
                        }
                    }
                }else {
                    if (namePinyin.find(strKeyword) != namePinyin.npos) {
                        groupInofs.push_back(groupInfo);
                    }
                }
            }
        }else if (keyword != nullptr && strlen(keyword) == 1) {
            std::ostringstream s;
            if (feedId == nullptr || strlen(feedId) == 0) {
                s << "select * from GroupInfo where pinyinHeader like '%%" << keyword << "%%' order by namePinyin,groupId asc";
            } else {
                s << "select * from GroupInfo where pinyinHeader like '%%" << keyword << "%%' and myFeedId = '" << feedId << "' order by namePinyin,groupId asc";
            }
            std::string sql = s.str();
            CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
            
            if (records == NULL) {
                return;
            }
            
            while (records->step() == CSqliteDBStatement::STEP_ROW) {
                CTNGroupInfo groupInfo = this->generateGroupInfo(records);
                groupInofs.push_back(groupInfo);
            }
        }
    }
    
#pragma mark ---------------groupMembers----------
    bool CTNDBGroupChat::addGroupMember(vector<CTNGroupMember>& members)
    {
        if (members.size() <= 0) {
            return false;
        }
        
        this->beginTransation();
        for (int i=0; i<members.size(); i++) {
            CTNGroupMember member = members.at(i);
            if (member.groupId <= 0 || member.feedId.length() <= 0) {
                continue;
            }
            
            map<string, pair<CTNDBBase::FT, string>> info;
            
            info["groupId"] = make_pair(CTNDBBase::DB_LONG, CTNDBUtils::stringFromInt64(member.groupId));
            info["groupTopic"] = make_pair(CTNDBBase::DB_STR, member.groupTopic);
            info["feedId"] = make_pair(CTNDBBase::DB_STR, member.feedId);
            info["name"] = make_pair(CTNDBBase::DB_STR, member.name);
            info["namePinyin"] = make_pair(CTNDBBase::DB_STR, member.namePinyin);
            info["namePinyinHeader"] = make_pair(CTNDBBase::DB_STR, member.namePinyinHeader);
            info["remarkName"] = make_pair(CTNDBBase::DB_STR, member.remarkName);
            info["remarkNamePinyin"] = make_pair(CTNDBBase::DB_STR, member.remarkNamePinyin);
            info["remarkNamePinyinHeader"] = make_pair(CTNDBBase::DB_STR, member.remarkNamePinyinHeader);
            info["headerImage"] = make_pair(CTNDBBase::DB_STR, member.headerImage);
            info["status"] = make_pair(CTNDBBase::DB_INT, CTNDBUtils::stringFromInt32(member.status));
            info["timestamp"] = make_pair(CTNDBBase::DB_LONG, CTNDBUtils::stringFromInt64(member.timestamp));
            
            replaceRecord("GroupMember", info);
        }
        this->commitTransation();
        
        return true;
    }
    
    bool CTNDBGroupChat::updateGroupMembers(vector<CTNGroupMember>& members)
    {
        if (members.size() <= 0) {
            return false;
        }
        
        vector<std::string> sqls;
        this->addGroupMember(members);
        
        return true;
    }
    
    bool CTNDBGroupChat::deleteGroupMember(int64_t groupId, const char*  feedId)
    {
        if (groupId <= 0 || feedId == nullptr || strlen(feedId) == 0) {
            return false;
        }
        
        std::ostringstream s;
        s << "delete from GroupMember where groupId=" << groupId << " and feedId='" << feedId << "'";
        std::string sql = s.str();
        this->execSql(sql.c_str());
        
        return true;
    }
    
    bool CTNDBGroupChat::deleteAllGroupMembers(int64_t groupId)
    {
        if (groupId <= 0) {
            return false;
        }
        
        std::ostringstream s;
        s << "delete from GroupMember where groupId=" << groupId;
        std::string sql = s.str();
        this->execSql(sql.c_str());
        
        return true;
    }
    
    vector<CTNGroupMember> CTNDBGroupChat::getGroupMembers(int64_t groupId)
    {
        if (groupId <= 0) {
            return vector<CTNGroupMember>();
        }
        
        std::ostringstream s;
        s << "select * from GroupMember where groupId=" << groupId;
        std::string sql = s.str();
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
        vector<CTNGroupMember> vMember = vector<CTNGroupMember>();
        
        if (records == NULL) {
            return vMember;
        }
        
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            CTNGroupMember member = this->generateGroupMember(records);
            vMember.push_back(member);
        }
        
        return vMember;
    }
    
    CTNGroupMember CTNDBGroupChat::getGroupMember(int64_t groupId, const char*  feedId)
    {
        if (groupId <= 0 || feedId == nullptr || strlen(feedId) == 0) {
            return CTNGroupMember();
        }
        
        std::ostringstream s;
        s << "select * from GroupMember where groupId=" << groupId << " and feedId='" << feedId << "'";
        std::string sql = s.str();
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
        CTNGroupMember member = CTNGroupMember();
        
        if (records == NULL) {
            return member;
        }
        
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            member = this->generateGroupMember(records);
        }
        
        return member;
    }
    
    void CTNDBGroupChat::getGroupMembersWithFeedId(const char*  feedId, vector<toonim::CTNGroupMember> &groupMembers)
    {
        if (feedId == nullptr || strlen(feedId) == 0) {
            return;
        }
        std::ostringstream s;
        s << "select * from GroupMember where feedId='" << feedId << "' and status != 0";
        std::string sql = s.str();
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
        CTNGroupMember member = CTNGroupMember();
        
        if (records == NULL) {
            return;
        }
        
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            CTNGroupMember member = this->generateGroupMember(records);
            groupMembers.push_back(member);
        }
    }
    
    int CTNDBGroupChat::getGroupMembersCount(int64_t groupId)
    {
        if (groupId == 0){
            return 0;
        }
        std::ostringstream s;
        s << "select count(groupId) from GroupMember where status != 0 and groupId=" << groupId;
        std::string sql = s.str();
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
        if (records == NULL) {
            return 0;
        }
        
        int count = 0;
        if (records->step() == CSqliteDBStatement::STEP_ROW) {
            count = records->getInt(0);
        }
        
        return count;
    }
    
    /*
     1、判断keyword是否包含中文或emoji，包含中文或emoji直接根据name like搜索（暂时使用外层object-c代码判断）
     2、不包含中文，则根据拼音搜
     2.1、字符长度大于1，首先取keyword第一位，去搜首字母字段，能搜到，则过滤整个keyword是否包含在pinyin或pinyinHeader中
     2.2、字符长度等于1，直接搜pinyinHeader like
     *避免随便一个字母，都能根据拼音搜索到（例如输入a，如果用like %a%，则liang也能搜到）
     */
    void CTNDBGroupChat::searchGroupMember(const char* keyword,const vector<std::string> &groupIds, vector<toonim::CTNGroupMember> &groupMembers)
    {
        if (keyword == nullptr) {
            return;
        }
        std::ostringstream s;
        if (groupIds.size() <= 0) {
            s << "select * from (select * from GroupMember where remarkName like '%%" << keyword << "%%' and status != 0 union select * from GroupMember where name like '%%" << keyword << "%%' and status != 0) order by groupId";
        } else {
            std::ostringstream g;
            for (int i=0; i<groupIds.size(); i++) {
                std::string groupId = groupIds.at(i);
                if (i == groupIds.size() - 1) {
                    g << groupId;
                } else {
                    g << groupId << "','";
                }
            }
            s << "select * from (select * from GroupMember where remarkName like '%%" << keyword << "%%' and status != 0 and groupId in ('" << g.str() << "') union select * from GroupMember where name like '%%" << keyword << "%%' and status != 0 and groupId in ('" << g.str() << "')) order by groupId";
        }
        std::string sql = s.str();
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
        
        if (records == NULL) {
            return;
        }
        
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            CTNGroupMember groupMember = this->generateGroupMember(records);
            groupMembers.push_back(groupMember);
        }
    }
    
    void CTNDBGroupChat::searchGroupMemberWithPinyin(const char* keyword, const vector<std::string> &groupIds, vector<toonim::CTNGroupMember> &groupMembers)
    {
        if (keyword != nullptr && strlen(keyword) > 1) {
            std::string strKeyword = keyword;
            std::string header = strKeyword.substr(0,1);
            std::ostringstream s;
            if (groupIds.size() <= 0) {
                s << "select * from (select * from GroupMember where remarkNamePinyinHeader like '%%" << header << "%%' and status != 0 union select * from GroupMember where namePinyinHeader like '%%" << header << "%%' and status != 0) order by groupId";
            } else {
                std::ostringstream g;
                for (int i=0; i<groupIds.size(); i++) {
                    std::string groupId = groupIds.at(i);
                    if (i == groupIds.size() - 1) {
                        g << groupId;
                    } else {
                        g << groupId << "','";
                    }
                }
                s << "select * from (select * from GroupMember where remarkNamePinyinHeader like '%%" << header << "%%' and status != 0 and groupId in ('" << g.str() << "') union select * from GroupMember where namePinyinHeader like '%%" << header << "%%' and status != 0 and groupId in ('" << g.str() << "')) order by groupId";
            }
            
            std::string sql = s.str();
            CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
            
            if (records == NULL) {
                return;
            }
            
            while (records->step() == CSqliteDBStatement::STEP_ROW) {
                CTNGroupMember groupMember = this->generateGroupMember(records);
                
                std::string pinyinHeader = groupMember.namePinyinHeader;
                std::string remarkPinyinHeader = groupMember.remarkNamePinyinHeader.length()>0?groupMember.remarkNamePinyinHeader:"";
                
                if (pinyinHeader.find(strKeyword) != pinyinHeader.npos || remarkPinyinHeader.find(strKeyword) != remarkPinyinHeader.npos) {
                    groupMembers.push_back(groupMember);
                    continue;
                }
                
                std::string namePinyin = groupMember.remarkNamePinyin.length()>0?groupMember.remarkNamePinyin:groupMember.namePinyin;
                bool resultDone = this->filterGroupMemberWithPinyin(keyword, header.c_str(), namePinyin.c_str(), groupMember, groupMembers);
                if (resultDone == false && groupMember.remarkNamePinyin.length()>0) {
                    namePinyin = groupMember.namePinyin;
                    this->filterGroupMemberWithPinyin(keyword, header.c_str(), namePinyin.c_str(), groupMember, groupMembers);
                }
            }
        }else if (keyword != nullptr && strlen(keyword) == 1) {
            std::ostringstream s;
            if (groupIds.size() <= 0) {
                s << "select * from (select * from GroupMember where remarkNamePinyinHeader like '%%" << keyword << "%%' and status != 0 union select * from GroupMember where namePinyinHeader like '%%" << keyword << "%%' and status != 0) order by groupId";
            } else {
                std::ostringstream g;
                for (int i=0; i<groupIds.size(); i++) {
                    std::string groupId = groupIds.at(i);
                    if (i == groupIds.size() - 1) {
                        g << groupId;
                    } else {
                        g << groupId << "','";
                    }
                }
                s << "select * from (select * from GroupMember where remarkNamePinyinHeader like '%%" << keyword << "%%' and status != 0 and groupId in ('" << g.str() << "') union select * from GroupMember where namePinyinHeader like '%%" << keyword << "%%' and status != 0 and groupId in ('" << g.str() << "')) order by groupId";
            }
            
            std::string sql = s.str();
            CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
            
            if (records == NULL) {
                return;
            }
            
            while (records->step() == CSqliteDBStatement::STEP_ROW) {
                CTNGroupMember groupMember = this->generateGroupMember(records);
                groupMembers.push_back(groupMember);
            }
        }
    }
    
    bool CTNDBGroupChat::filterGroupMemberWithPinyin(const char* keyword, const char* header, const char* pinyin, toonim::CTNGroupMember groupMember, vector<toonim::CTNGroupMember> &groupMembers)
    {
        bool resultDone = false;
        std::string strKeyword = keyword;
        std::string strHeader = header;
        std::string namePinyin = pinyin;
        
        std::string sep = "**";
        std::string::size_type pos = namePinyin.find(sep);
        if (pos != namePinyin.npos) {
            if (CTNDBUtils::isEqualAOE(strHeader)) {
                std::string namePinyinAOE = namePinyin.substr(pos+sep.length(), namePinyin.length()-pos-sep.length());
                std::string aoeKeyword = strKeyword;
                aoeKeyword.insert(0, "*");
                if (namePinyinAOE.find(aoeKeyword) != namePinyinAOE.npos) {
                    groupMembers.push_back(groupMember);
                    resultDone = true;
                }else {
                    if (namePinyinAOE.find_first_of("*") != namePinyinAOE.find_last_of("*")) {
                        if (namePinyin.find(strKeyword) != namePinyin.npos) {
                            groupMembers.push_back(groupMember);
                            resultDone = true;
                        }
                    }
                }
            }else {
                if (namePinyin.find(strKeyword) != namePinyin.npos) {
                    groupMembers.push_back(groupMember);
                    resultDone = true;
                }
            }
        }else {
            if (namePinyin.find(strKeyword) != namePinyin.npos) {
                groupMembers.push_back(groupMember);
                resultDone = true;
            }
        }
        return resultDone;
    }
    
#pragma mark -------------appInfo--------
    bool CTNDBGroupChat::addAppInfo(vector<CTNAppInfo>& appInfos)
    {
        if (appInfos.size() <= 0) {
            return false;
        }
        
        this->beginTransation();
        for (int i=0; i<appInfos.size(); i++) {
            CTNAppInfo appInfo = appInfos.at(i);
            if (appInfo.appId.length() <= 0) {
                continue;
            }
            
            map<string, pair<CTNDBBase::FT, string>> info;
            info["appId"] = make_pair(CTNDBBase::DB_STR, appInfo.appId);
            info["appCode"] = make_pair(CTNDBBase::DB_STR, appInfo.appCode);
            info["appTitle"] = make_pair(CTNDBBase::DB_STR, appInfo.appTitle);
            info["appLittleIcon"] = make_pair(CTNDBBase::DB_STR, appInfo.appLittleIcon);
            info["chatFlag"] = make_pair(CTNDBBase::DB_INT, CTNDBUtils::stringFromInt32(appInfo.chatFlag));
            
            insertRecord("CTNAppInfo", info);
        }
        this->commitTransation();
        
        return true;
    }
    
    bool CTNDBGroupChat::updateAppInfo(vector<CTNAppInfo>& appInfos)
    {
        if (appInfos.size() <= 0) {
            return false;
        }
        
        this->beginTransation();
        for (int i=0; i<appInfos.size(); i++) {
            CTNAppInfo appInfo = appInfos.at(i);
            if (appInfo.appId.length() <= 0) {
                continue;
            }
            
            map<string, pair<CTNDBBase::FT, string>> info;
            info["appId"] = make_pair(CTNDBBase::DB_STR, appInfo.appId);
            info["appCode"] = make_pair(CTNDBBase::DB_STR, appInfo.appCode);
            info["appTitle"] = make_pair(CTNDBBase::DB_STR, appInfo.appTitle);
            info["appLittleIcon"] = make_pair(CTNDBBase::DB_STR, appInfo.appLittleIcon);
            info["chatFlag"] = make_pair(CTNDBBase::DB_INT, CTNDBUtils::stringFromInt32(appInfo.chatFlag));
            
            replaceRecord("CTNAppInfo", info);
        }
        this->commitTransation();
        
        return true;
    }
    
    bool CTNDBGroupChat::deleteAppInfo(const char*  appId)
    {
        if (appId == nullptr) {
            return false;
        }
        
        std::ostringstream s;
        s << "delete from CTNAppInfo where appId='" << appId << "'";
        std::string sql = s.str();
        this->execSql(sql.c_str());
        
        return true;
    }
    
    CTNAppInfo CTNDBGroupChat::getAppInfo(const char*  appId)
    {
        if (appId == nullptr || strlen(appId) == 0) {
            return CTNAppInfo();
        }
        
        std::ostringstream s;
        s << "select * from CTNAppInfo where appId='" << appId << "'";
        std::string sql = s.str();
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
        CTNAppInfo appInfo = CTNAppInfo();
        
        if (records == NULL) {
            return appInfo;
        }
        
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            appInfo = this->generateAppInfo(records);
        }
        
        return appInfo;
    }
    
#pragma mark ---------------resultData------------
    CTNGroupInfo CTNDBGroupChat::generateGroupInfo(CSqliteDBStatement *stmt)
    {
        CTNGroupInfo groupInfo;
        groupInfo.groupId = stmt->getLong(0);
        groupInfo.creatorFeedId = stmt->getString(1);
        groupInfo.name = stmt->getString(2);
        groupInfo.namePinyin = stmt->getString(3);
        groupInfo.pinyinHeader = stmt->getString(4);
        groupInfo.headerImage = stmt->getString(5);
        groupInfo.topic = stmt->getString(6);
        groupInfo.myFeedId = stmt->getString(7);
        groupInfo.maxNum = stmt->getInt(8);
        groupInfo.currNum = stmt->getInt(9);
        groupInfo.version = stmt->getLong(10);
        groupInfo.disturbStatus = stmt->getInt(11);
        groupInfo.pinyin = stmt->getString(12);
        groupInfo.verify = stmt->getInt(13);
        
        return groupInfo;
    }
    
    CTNGroupMember CTNDBGroupChat::generateGroupMember(CSqliteDBStatement *stmt)
    {
        CTNGroupMember groupMember;
        groupMember.groupId = stmt->getLong(0);
        groupMember.groupTopic = stmt->getString(1);
        groupMember.feedId = stmt->getString(2);
        groupMember.name = stmt->getString(3);
        groupMember.namePinyin = stmt->getString(4);
        groupMember.namePinyinHeader = stmt->getString(5);
        groupMember.remarkName = stmt->getString(6);
        groupMember.remarkNamePinyin = stmt->getString(7);
        groupMember.remarkNamePinyinHeader = stmt->getString(8);
        groupMember.headerImage = stmt->getString(9);
        groupMember.status = stmt->getInt(10);
        groupMember.timestamp = stmt->getInt(11);
        
        return groupMember;
    }
    
    CTNAppInfo CTNDBGroupChat::generateAppInfo(CSqliteDBStatement *stmt)
    {
        CTNAppInfo appInfo;
        appInfo.appId = stmt->getString(0);
        appInfo.appCode = stmt->getString(1);
        appInfo.appTitle = stmt->getString(2);
        appInfo.appLittleIcon = stmt->getString(3);
        appInfo.chatFlag = stmt->getInt(4);
        
        return appInfo;
    }
    
}

void contentFunc(sqlite3_context *context, int argc, sqlite3_value **argv)
{
    if (argc < 1) {
        sqlite3_result_null(context);
        return;
    }
    if (sqlite3_value_type(argv[0]) == SQLITE_NULL) {
        sqlite3_result_null(context);
        return;
    }
    if (sqlite3_value_type(argv[0]) != SQLITE_TEXT) {
        sqlite3_result_error(context, "Expected text", -1);
        return;
    }
    
    const char *result = (const char *)sqlite3_value_text(argv[0]);
    
#ifdef RAPIDJSONWRAPPER
    std::string strResult;
    if (result) {
        strResult = result;
    }
    toonim::CTNJsonReader doc(strResult);
    
    strResult = doc["text"].getString();
    
    result = strResult.c_str();
#else
    rapidjson::Document doc;
    doc.Parse(result);
    rapidjson::Value &text = GetValueByPointerWithDefault(doc, "/text", "");
    
    if (text.IsString()) {
        result = text.GetString();
    }
#endif

    sqlite3_result_text(context, result, -1, SQLITE_TRANSIENT);
}
