//
//  CTNChatManager.hpp
//  TNIMSDK
//
//  Created by 王旭影 on 17/8/23.
//  Copyright © 2017年 syswin. All rights reserved.
//

#ifndef CTNChatManager_hpp
#define CTNChatManager_hpp

#include <stdio.h>

#include <ITNMPResponse.h>
#include <CTNProcessThread.h>
#include <TMTPHostInfo.h>
#include "tmtp_type.h"
#include "tmtp_biz.h"
#include "CLog.h"
#include "CTNDBHeader.h"
#include "document.h"
#include <set>
#include <mutex>

using namespace toonim;

#include "CTNChatAPI.h"
#include "CTNDBAPI.h"

namespace toonim {
    
#define TNCSYNCMESSAGESEQID_HIGHMAXSEQID "TNCSYNCMESSAGESEQID_HIGHMAXSEQID"
#define TNCSYNCMESSAGESEQID_MAXSEQID "TNCSYNCMESSAGESEQID_MAXSEQID"
#define ALL_GROUPCHAT_UPDATETIME     "TNC_ALL_GROUPCHAT_UPDATETIME"
#define LAST_GROUPCHAT_UPDATETIME    "TNC_LAST_GROUP_CHAT_UPDATETIME"


//当前是语音消息
#define TNC_DOWNLOAD_VOICE    "TNC_DOWNLOAD_VOICE"
//群资料变化
#define TNC_GROUP_CHANGED    "TNC_GROUP_CHANGED"
//群成员变化（搜索用）
#define TNC_GROUP_MEMBER_CHANGED    "TNC_GROUP_MEMBER_CHANGED"
//未读数变化
#define TNC_UNREAD           "TNC_UNREAD"
//session除未读数外的改变
#define TNC_SESSION_CHANGE      "TNC_SESSION_CHANGE"
#define TNC_IMPORTANT_MESSAGE(type)  ("TNC_IMPORTANT_MESSAGE_" + type)

#define MAXLOADNUM 150 //请求消息数
#define ACCUMUMAXLOADNUM 1000//断层最大填充消息数目
    
#define TNC_CHECK_RET(pointer, ret) if (pointer == nullptr) {return ret;}
    
    
    enum CTNIMSystemType{
        CTNIMSystemTypeText = 0,
        CTNIMSystemTypeFeed = 1,
        CTNIMSystemTypeIcon = 2,
        CTNIMSystemTypeButton = 3,
    };
    
    struct OffMsgMgr {
        OffMsgMgr(){
            type = -1;
            priority = -1;
            minSeqId = -1;
            maxSeqId = -1;
            count = -1;
            accumuCount = 0;
        }
        string reqId;
        int32_t type;//del
        int32_t priority;//del
        string from;//del
        string to;//del
        int64_t minSeqId;//min local //del
        int64_t maxSeqId;//max server //del
        int32_t count;
        int32_t accumuCount;//单个断层累积拉取消息数目，控制断层拉取
        CTNMessage faultMsg;
    };
    
/*
 * 聊天管理类
 */
class CTNChatManager : public ITNMPResponse , public ITnImSdk
{
public:
    CTNChatManager();
    virtual ~CTNChatManager();
    static CTNChatManager* instance();
    
    /////// ITNMPResponse ////////////
    virtual void loginResp(int32_t code,vector<int32_t>& contentTypes, map<string, int> &forbiddenMap);
    virtual void kickOut();
    virtual void offMsgResp(Toon::OffMsgResp* offMsg);
    virtual void hotSessionResp(Toon::HotSessionResp* hotSessions);
    virtual void syncSessionStatusResp(Toon::SyncSessionStatusResp* sessionStatus);
    virtual void syncSessionStatusReq(Toon::SyncSessionStatusReq* sessionStatus);
    virtual void msgAck(string& msgId, int64_t seqId, int32_t type, string& from,string& to, int32_t result, int64_t timestamp);
    virtual void msgRecv(int32_t type, Toon::MsgReq * req);
    virtual void netStatusChanged(TNMPNetStatus status);
    virtual void userOlineStatus(Toon::NotifyPresenceStatusResp& userStatus);

    virtual void daInfo(string& atrName, map<string, string> & property);//埋点信息
    
    /////// ITnImSdk ////////////
    virtual void addNoticeFilter(int32_t catalogId, std::vector<int32_t>& subCatalogId, const char* broadcast);
    virtual int32_t getNetStatus();
    virtual void addHostInfo(const char* host, int32_t port, bool isSSL);
    virtual void setCallback(ITnImSdkCallback* callback) { _callback = callback; }
    virtual int32_t login(const char* name, const char* password);
    virtual int32_t logout (bool notifyServer);
    virtual int32_t sendMessage (CTNMessage* message);
    virtual int32_t revokeMessage(const char* sessionId ,const char* msgId, const char* operatorFeedId, const char* operatorName);
    virtual void reqSync(int32_t unreadCount, const char* pushToken);
    virtual void dissolveGroup(int64_t groupId);
    virtual void reqSyncSessionStatus(const char* sessionId);
    virtual void clientReport(int32_t type,const char* content);
    virtual void subOrganize(vector<string> &vctOrgId);
    
 
    /////// 功能接口 ////////////
    //初始化
    void addHostInfo(TMTPHostInfo &hostInfo);
    void setClientInfo(CTNClientInfo &clientInfo);
    //update feedList
    void updateMyFeedList(vector<string>& feedList);
    bool isMySelfFeed(std::string& feedIdArray);
    
protected:
    void createProcessThread ();
    void checkPorcessThread ();
    void addToDiedArray(CTNProcessThread* processThread);
    
private:
    static CTNChatManager*          _instance;
    CTNProcessThread*               _currProcess;
    toonim::CTNClientInfo           _clientInfo;
    vector<TMTPHostInfo>            _serverVector;
    ITnImSdkCallback*               _callback;
    vector<string>                  _arrRecvMsgId;
    string                          _toonType;
    map<string, OffMsgMgr>          _offMsgQueue;//断层管理
    map<string, CTNMessageOperate>  _cacheOperateMsg;//操作消息管理
    
    map<int, CTNNoticeFilter> _noticeFilterMap;
    std::mutex _noticeFileterMutex;
    vector<CTNProcessThread*> _diedArray;
    std::mutex _diedArrayMutex;
    std::mutex _loginMutex;
    std::mutex _cacheOperateMutex;
    
   //内部接口
    int32_t login();
        
    //lanhuaiyu for hot
    void loadOperateMessages();
    void processRecvOnlineMessage(CTNMessage& message);
    void processHotSessionResp(vector<Toon::HotSessionItem> &vctSession);
    void processHistoryMessages(vector<Toon::OffMsgItem> & historyMessages, string& reqId);
    
    void transOffmsgs(vector<Toon::OffMsgItem> &vctSrc, vector<CTNMessage> &vctDest, int64_t &maxSeqId);
    void processMessageChat(CTNMessage &message);
    
    //return 0 not sync, 1 for groupInfo, 2 for member
    bool processMessageGroupChat(CTNMessage &message, set<int64_t> &syncMemberGroupId);
    bool processMessageNotice(CTNMessage &message, bool isOnline);
    void processMessageSync(CTNMessage &message, bool isOnline);
    CTNMessage processMessageOperate(CTNMessage &message);
    CTNIMMessageStatus checkSystemMessageStatus(CTNMessage& message);
    void checkMessageRevoked(CTNMessage &message);
    void fillSessionFaultMessage();//填充断层
    void processFollowMessage(CTNMessage &message);
    void processAtMeMessage(CTNMessage &message);
    void deleteImportantMessage(CTNSession session);
        
    //end for hot
    
    //离线消息处理
   CTNMessage msgReqToIMMessage(int32_t type, Toon::MsgReq * req);
    Toon::MsgReq * imMessageToMsgReq(int32_t type, CTNMessage& message);
    void contentToJson(int32_t type, vector<taf::Char> &vctContent,CTNMessage& imMessage);
    bool isInvalid(int32_t type, Toon::MsgReq * req);
    CTNMessage obtaionNoticeMessage(CTNMessage& message);
    
    CTNSession getSessionByMessage(CTNMessage& message, bool &isNewSession);
    
    bool messageIsForbidden(CTNMessage& message);
    bool isFilterNotice(CTNMessage& message, string &broadcast);
    void addSessionWithArray(std::vector<CTNSession>& sessionArray);

    bool chatAndNoticeMessageIsValid(CTNMessage& message);
    CTNOwner getMessageOwner(CTNMessage& message);
    
    bool isMySelfFeed(std::set<std::string>& feedIdArray);
    bool isMySelfClientID(const string& clientID);
    void printMyFeedIdList();

    CTNIMMessageStatus checkSystemMessageStatus(CTNMessage& message, bool needSync);
    void processMsgOperateAck(CTNMessage& message, bool success);
  
    string genRevokeMessageContent(toonim::CTNMessage& message, const std::string& operateName);
    void updateSessionWithArray(vector<CTNSession>& sessionArray);
   
    void processMessageAck(CTNMessage& message, int32_t errorCode);
    void checkMessageFileStatus(CTNMessage& message,CTNMessageFileStatus status);
    void checkMessageVoice(CTNMessage& message);
    bool checkMessageRepeat(const string& msgId);
   
   void syncMyGroupFromServerSucceed();
 
    CTNGroupInfo getGroupInfoWithTopic(const string& topic);
    void syncGroupMember(int64_t groupId);
    bool isAtMeFromMsgIdWithMessage(CTNMessage& message);
    //处理离线消息，包括断层消息 wxy
    void pullOffMessage(OffMsgMgr& offMsgInfo, int32_t requestNum, int32_t priority);
    //根据sessionId生成json串
    std::string genSessionIdToJson(std::string &sessionId);
    bool isDisableMessageSend(CTNMessage& message);
    void getLocalSessionBySessionItem(Toon::HotSessionItem& sessionItem, CTNSession& localSession);
};
    
    
    class CTNLog : public ITnIMLog{
    public:
        static CTNLog* instance();
        
        virtual void writeLog(const char* logs);
        virtual const char* getLogFileName();
    private:
        static CTNLog* _instance;
    };

    
};
#endif /* CTNChatManager_hpp */

