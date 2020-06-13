//
//  CTNDBSettings.hpp
//  CTNSDK
//
//  Created by 王海涛 on 2017/8/23.
//  Copyright © 2017年 syswin. All rights reserved.
//

#ifndef CTNDBSettings_hpp
#define CTNDBSettings_hpp

#include <stdio.h>
#include <vector>

#include "CTNDBBase.hpp"
#include "CTNDBHeader.h"
#include "CTNDBAPI.h"
#include "CTNDBUtils.hpp"

namespace toonim {
    
    //黑名单
    static int CTNBlackListType = 1;
    //免打扰
    static int CTNDisturbType = 2;
    
class CTNDBSetting: public CTNDBBase, public ITnImDBSettings
{
public:
    CTNDBSetting();
    ~CTNDBSetting();
    
    static CTNDBSetting* instance();
    static CTNDBSetting* instance(const char* clientId, const char* appPath);
    virtual void createTable();
    
    
    bool addSessionSetting(const char* sessionId, CTNSESSIONTYPE type, const char* value);
    bool addSessionSettings(vector<CTNSessionSetting>& vecSessionSetting);
    bool updateSessionSetting(const char* sessionId, CTNSESSIONTYPE type, const char* value);
    bool deleteSessionSetting(const char* sessionId, CTNSESSIONTYPE type);
    CTNSessionSetting getSessionSetting(const char* sessionId, CTNSESSIONTYPE type);
    int32_t getSessionSettingDisturb(const char* sessionId);
    
    bool setImportantSwitch(CTNIMMessageType type, bool status);
    bool getImportantStatus(CTNIMMessageType type);
    void setAtMessageSwitch(bool status);
    bool getAtMessaeSwitch();
    void setFollowFeedId(const char* feedId, bool status);
    void setFollowFeedIdList(const vector<toonim::CTNFollowFeed> &followList);
    bool getFollowSwitch(const char* feedId);
    bool isFollowMessage(CTNMessage &message);
    vector<std::string> getMyFollowFeedList();

    virtual bool isForbiddenFeature(const char* key);
    void setForbiddenFeatureMap(std::map<string, int>  &mapForbidden);

    bool addBlackList(const char* feedId, const char* passiveFeedId, int32_t status);
    bool deleteBlackList(vector<CTNBlackListModel>& blackList);
    bool updateBlackList(vector<CTNBlackListModel>& blackList);
    vector<toonim::CTNBlackListModel> getBlackList(const char* feedId);
    CTNBlackListModel getBlackModel(const char* feedId, const char* passiveFeedId);
    CTNBlackListModel getBlackAndDisturbModel(const char* feedId, const char* passiveFeedId);
    
    void loadSettingCache();
    void loadSettingDisturbCache();
    void loadBlackListCache();
    void loadFollowListCache();
    bool isAtSwitchOn();
    int32_t getFollowFeedIdsCount();
    
    virtual const char* tableName () { return ""; }
    virtual const char* sqlCreate () { return ""; }
    
private:
    
    CTNSessionSetting generateSetting(CSqliteDBStatement *stmt);
    CTNBlackListModel generateBlackList(CSqliteDBStatement *stmt);
    
    vector<CTNBlackListModel> getDisturbList();
    void initAtSwitchStatus();
    
    static CTNDBSetting * _instance;
    //at开关设置
    bool _isAtSwitchOn;
    //followFeedIds count
    int32_t _followFeedidsCount;
    
    //免打扰缓存
    CSafeMap<std::string, int32_t> _mpCacheSetDisturb;
    //黑名单缓存
    CSafeMap<std::string, CTNBlackListModel> _mpCacheBlackList;

    //关注的人名单缓存
    CSafeMap<std::string, int32_t> _mpCacheFollowList;

    CSafeMap<std::string, int32_t> _forbiddenMap;

};
}

#endif /* CTNDBSettings_hpp */
