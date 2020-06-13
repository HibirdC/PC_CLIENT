//
//  CTNDBGroupChat.hpp
//  CTNSDK
//
//  Created by 王海涛 on 2017/8/23.
//  Copyright © 2017年 syswin. All rights reserved.
//

#ifndef CTNDBGroupChat_hpp
#define CTNDBGroupChat_hpp

#include <stdio.h>
#include "CTNDBBase.hpp"
#include "CTNDBHeader.h"
#include "CTNDBAPI.h"

namespace toonim {
class CTNDBGroupChat: public CTNDBBase, public ITnImDBGroupChat
{
public:
    CTNDBGroupChat();
    
    virtual void createTable();
    
    static CTNDBGroupChat* instance();
    static CTNDBGroupChat* instance(const char* clientId, const char* appPath);
    
    virtual bool addAppInfo(vector<toonim::CTNAppInfo>& appInfos);
    virtual bool deleteAppInfo(const char*  appId);
    virtual bool updateAppInfo(vector<toonim::CTNAppInfo>& appInfos);
    virtual toonim::CTNAppInfo getAppInfo(const char*  appId);
    
    virtual bool addGroupInfo(vector<toonim::CTNGroupInfo>& groups);
    virtual bool deleteGroupInfo(int64_t groupId);
    virtual bool updateGroupInfo(vector<toonim::CTNGroupInfo>& groups);
    virtual toonim::CTNGroupInfo getGroupInfo(int64_t groupId);
    virtual vector<toonim::CTNGroupInfo> getGroupInfoWithMyFeedId(const char*  feedId);
    virtual void searchGroupInfo(const char* keyword, const char* feedId, vector<toonim::CTNGroupInfo> &groupInofs);
    virtual void searchGroupInfoWithPinyin(const char* keyword, const char* feedId, vector<toonim::CTNGroupInfo> &groupInofs);

    virtual bool addGroupMember(vector<toonim::CTNGroupMember>& members);
    virtual bool updateGroupMembers(vector<toonim::CTNGroupMember>& members);
    virtual bool deleteAllGroupMembers(int64_t groupId);
    virtual bool deleteGroupMember(int64_t groupId, const char*  feedId);
    virtual vector<toonim::CTNGroupMember> getGroupMembers(int64_t groupId);
    virtual CTNGroupMember getGroupMember(int64_t groupId, const char*  feedId);
    virtual void getGroupMembersWithFeedId(const char*  feedId, vector<toonim::CTNGroupMember> &groupMembers);
    virtual int getGroupMembersCount(int64_t groupId);
    virtual void searchGroupMember(const char* keyword, const vector<std::string> &groupIds, vector<toonim::CTNGroupMember> &groupMembers);
    virtual void searchGroupMemberWithPinyin(const char* keyword, const vector<std::string> &groupIds, vector<toonim::CTNGroupMember> &groupMembers);
    
    virtual const char* tableName () { return ""; }
    virtual const char* sqlCreate () { return ""; }
    
    vector<CTNGroupInfo> getGroupDisturb();
    
    virtual void upgradeTableWithOldVersion();
    
private:
    CTNGroupInfo generateGroupInfo(CSqliteDBStatement *stmt);
    CTNGroupMember generateGroupMember(CSqliteDBStatement *stmt);
    CTNAppInfo generateAppInfo(CSqliteDBStatement *stmt);
    void genGroupInfoMap(CTNGroupInfo &groupInfo, map<string, pair<CTNDBBase::FT, string>> &info);
    bool filterGroupMemberWithPinyin(const char* keyword, const char* header, const char* pinyin, toonim::CTNGroupMember groupMember, vector<toonim::CTNGroupMember> &groupMembers);
    
    static CTNDBGroupChat * _instance;

};
}

void contentFunc(sqlite3_context *context, int argc, sqlite3_value **argv);

#endif /* CTNDBGroupChat_hpp */
