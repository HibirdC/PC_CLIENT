//
//  CTNDBChat.hpp
//  CTNSDK
//
//  Created by 王海涛 on 2017/8/23.
//  Copyright © 2017年 syswin. All rights reserved.
//

#ifndef CTNDBChat_hpp
#define CTNDBChat_hpp

#include <stdio.h>
#include "CTNDBBase.hpp"
#include "CTNDBHeader.h"
#include "CTNDBAPI.h"

using namespace std;

#define DB_MIGRATE "dbMigrate"

namespace toonim {

enum CTNChatParams{
    Chat_params_getSession = 0,     //session数据
    Chat_params_getMessage = 1,     //message数据
    Chat_params_getUnreadCount = 2, //unreadCount
    Chat_params_getOperate = 3,     //operate数据
};

class CTNDBChat: public CTNDBBase, public ITnImDBChat
{
    
public:
    static CTNDBChat* instance();
    static CTNDBChat* instance(const char* clientId, const char* appPath);
    
    virtual void createTable();
  
    bool addSession(vector<CTNSession> &sessions);
    bool updateSession(vector<CTNSession> &sessions);
    bool updateSessionTitleAndImage(const char* sessionId, const char* title, const char* avatarId);
    bool updateSessionLastMsgAndLastTime(const char* sessionId, const char* lastMsg, int64_t lastTime);
    bool deleteSession(const char* sessionId);
    vector<CTNSession> getSessions(const char* myFeedId, bool isContainNotice);
    CTNSession getSession(const char* sessionId);
    int getUnreadCount(const char* feedId, const char* sessionId);
    int getUnreadCountUnContainFeedId(const char* feedId);
    bool markSessionRead(const char* sessionId);
    bool markSessionUnread(const char* sessionId);
    bool clearAllUnreadCount();
    void setImportantSession(vector<CTNSession> &sessionList);
    bool deleteImportantSession(CTNIMMessageType type);
    
    bool addMessages(vector<CTNMessage> &messages);
    bool addMessage(toonim::CTNMessage &message);
    bool replaceMessage(toonim::CTNMessage &message);
    bool replaceMessages(vector<CTNMessage> &messages);
    bool deleteMessage(const char* sessionId, const char* msgId);
    bool deleteAllMessage(const char* sessionId);
    bool physicalDeletionMessage(const char* sessionId, const char* msgId);
    bool updateMessage(CTNMessage &message);
    bool updateContent(const char* msgId, const char* sessionId, const char* content);
    bool updateSendStatus(const char* msgId, const char* sessionId, int32_t sendStatus);
    bool updateAddition(const char* msgId, const char* sessionId, const char* addition);
    CTNMessage getMessage(const char*  sessionId, const char*  msgId);
    CTNMessage getMaxNoticeMessage(const char* sessionId, const char* bizNo);
    CTNMessage getFaultMessage(const char* sessionId, int32_t priority);
    CTNMessage getLastMessage(const char*  sessionId);
    int64_t getMaxSeqAllMessage(const char*  sessionId, int32_t type);
    vector<CTNMessage> getMessages(const char*  sessionId, int64_t seqId, int32_t count);
    vector<CTNMessage> getMessagesAsc(const char*  sessionId, int64_t seqId, int32_t count);
    vector<CTNMessage> getFaultMessages(const char*  sessionId, int64_t seqId, int32_t count);
    vector<CTNMessage> getMessagesWithContentType(const char*  sessionId, CTNMessageContentType contentType);
    vector<CTNMessage> getFileMessagesWithSessionId(const char*  sessionId, CTNMessageContentType contentType,vector<std::string> formats);
    vector<CTNMessage> getMessages(const char* sessionId, CTNMessageContentType contentType, CTNOwner isMySelf);
    vector<CTNMessage> getMessagesWithSeqId(const char*  sessionId, int64_t maxSeqId, int64_t minSeqId);
    vector<std::string> getNoticeStatusType(const char*  sessionId);
    vector<toonim::CTNMessage> getMessageWithNoticeStatusType(const char*  sessionId, int64_t seqId, int32_t count, const char*  noticeStatusType);
    virtual void searchMessage(const char* keyword, const char* sessionId, vector<std::vector<std::string> > &messages);
    vector<CTNMessage> getAllFaultMessage();
    
    bool addOperateMessage(vector<CTNMessageOperate> &operates);
    bool updateOperateMessage(vector<CTNMessageOperate> &operates);
    bool deleteOperateMessage(const char*  msgId);
    vector<CTNMessageOperate> getAllOperateMessages();
    bool translateOperateMessage(CTNMessageOperate operMessage);
    uint32_t userVersion();
    void setUserVersion (uint32_t version );
    CTNMessageOperate getOperateMessage(const char*  msgId);
    
    void addImportantMessage(CTNIMMessageType type, CTNMessage &message);
    vector<CTNMessage> getImportantMessageList(CTNIMMessageType type, const char* feedId, int64_t timestamp, const char *msgId, int32_t count);
    void deleteImportantSessionBySessionId(const char* sessionId);
    bool deleteImportantMessage(CTNIMMessageType type, const char* msgId);
    bool deleteImportantMessageBySessionId(CTNIMMessageType type, const char* sessionId);
    bool deleteAllImportantMessage(CTNIMMessageType type);
    int32_t getImportantMessageCount(CTNIMMessageType type);
    bool deleteFollowFeedId(const char* feedId);
    CTNMessage getLastAtMessage();
    CTNMessage getLastFollowMessage();
    //在session列表里增加at和关注的session
    void insertImportantSession(vector<CTNSession> &sessionList);
    void getSessionReadedId(std::map<std::string, int64_t>& sessionReadInfo);
    
    virtual void upgradeTableWithOldVersion();
    
#ifdef __APPLE__
    void migrateDataOfSession();//迁移数据库入口接口
#endif
    
    void resetSessionSendingStatus();
    void resetMessageSendingStatusWithSessionId(const char* sessionId);
    
private:
    CTNDBChat();
    
    CTNSession generateSession(CSqliteDBStatement *stmt);
    CTNMessage generateMessage(CSqliteDBStatement *stmt);
    int generateTableIndex(const char* sessionId);
    CTNMessageOperate generateOperateMessage(CSqliteDBStatement *stmt);
    std::string genRevokeMessageContent(toonim::CTNMessage &message, const char* operateName);
    void genMessageMap(toonim::CTNMessage& message, map<string, pair<CTNDBBase::FT, string>> &info);
    void genSessionMap(toonim::CTNSession& session, map<string, pair<CTNDBBase::FT, string>> &info);
    
    vector<CTNMessage> getAtMessageList(const char* feedId, int64_t timestamp, const char *msgId, int32_t count);
    bool addAtMessage(CTNMessage &message);
    bool deleteAtMessage(const char* msgId);
    bool deleteAllAtMessage();
    int32_t getAtMessageCount();

    vector<CTNMessage> getFollowMessageList( const char* feedId, int64_t timestamp, const char *msgId, int32_t count);
    bool addFollowMessage(CTNMessage &message);
    bool deleteFollowMessage(const char* msgId);
    bool deleteAllFollowMessage();
    bool deleteAtMessageBySessionId(const char* sessionId);
    bool deleteFollowMessageBySessionId(const char* sessionId);
    int32_t getFollowMessageCount();
    
    
#ifdef __APPLE__
    void migrateRemainder();//迁移数据库除去session之外的数据
    bool upgradeTableWithOldVersion(int32_t oldVer);
    bool createMessageTable();
    bool createSessionTable();
    bool createMessageFault();
    bool versionUpdateOldSession();
    bool versionUpdateSessionWithLastMsg();
    bool createChatAppListTable();
#endif
    
    static CTNDBChat* _instance;
    
    bool _resetSessionSendStatus;//重置发送状态函数 防止多次调用
    std::set<string> _sessionIdSet;
    
    vector<CTNSession> _importantVct;
    
    std::mutex _importantMutex;
    
};
    
}

#endif /* CTNDBChat_hpp */
