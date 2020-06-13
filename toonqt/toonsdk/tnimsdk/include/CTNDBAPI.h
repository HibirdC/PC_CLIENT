//
//  CTNDBAPI.hpp
//  CTNSDK
//
//  Created by 王海涛 on 2017/8/22.
//  Copyright © 2017年 syswin. All rights reserved.
//

#ifndef CTNDBAPI_hpp
#define CTNDBAPI_hpp

#include <stdio.h>
#include <vector>
#include <stdint.h>
#include "CTNDBHeader.h"

using namespace std;

namespace toonim {
    
    class ITnImDBChat
    {
    public:
        virtual ~ITnImDBChat(){}
                
#pragma mark ------------------session-----------------
        /**
         addsession

         @param sessions session对象集合
         @return true
         */
        virtual bool addSession(vector<CTNSession> &sessions) = 0;
        
        /**
         updateSession

         @param sessions session对象集合
         @return true
         */
        virtual bool updateSession(vector<CTNSession> &sessions) = 0;
        
        
        /**
         修改session的名称和头像,title和avaterid至少传一个值，否则返回false

         @param sessionId sessionId
         @param title title
         @param avatarId avaterid
         @return true
         */
        virtual bool updateSessionTitleAndImage(const char* sessionId, const char* title, const char* avatarId) = 0;
        
        /**
         修改session的最后一条消息内容和lastTime

         @param sessionId sessionId
         @param lastMsg lastMsg
         @param lastTime lastTime
         @return true
         */
        virtual bool updateSessionLastMsgAndLastTime(const char* sessionId, const char* lastMsg, int64_t lastTime) = 0;
        
        /**
         delete session
         
         @param sessionId sessionId
         @return true
         */
        virtual bool deleteSession(const char* sessionId) = 0;
        
        /**
         根据myFeedid获取session，myFeedid为空获取所有会话，不为空则获取该feedid的单聊和加入的群聊会话
         
         @param myFeedId 我自己的myFeedId
         @param isContainNotice 是否包含通知类消息
         @return session集合
         */
        virtual vector<CTNSession> getSessions(const char* myFeedId, bool isContainNotice)  = 0;
        
        /**
         根据sessionid获取session

         @param sessionId sessionId
         @return session对象
         */
        virtual CTNSession getSession(const char* sessionId)  = 0;
        
        /**
         根据myfeedid获取未读数，不传myFeedId为查询全部，myfeedid不为空则为筛选名片后的session，sessionid不为空则不计算该session的未读数

         @param myFeedId 自己的feedId
         @param sessionId 不计算未读数的会话sesionId
         @return 未读数
         */
        virtual int getUnreadCount(const char* myFeedId, const char* sessionId)  = 0;
        
        /**
         查询不包含该feedId下的session的未读数

         @param feedId 不被包含的feedId
         @return unreadCount
         */
        virtual int getUnreadCountUnContainFeedId(const char* feedId) = 0;
        
        /**
         标记对应会话为已读

         @param sessionId sessionid
         @return true
         */
        virtual bool markSessionRead(const char* sessionId)  = 0;
        
        /**
         标记对应会话为未读状态

         @param sessionId sessionid
         @return true
         */
        virtual bool markSessionUnread(const char* sessionId) = 0;
        
        /**
         清除所有会话未读数

         @return true
         */
        virtual bool clearAllUnreadCount()  = 0;
        
        /**
         设置at和关注的人的会话session
         
         @param sessionList 会话list
         */
        virtual void setImportantSession(vector<CTNSession> &sessionList) = 0;
        
        /**
          删除重要消息会话

         @param type 消息类型
         @return result
         */
        virtual bool deleteImportantSession(CTNIMMessageType type) = 0;
        
        /**
         删除关注的人，删除对应的消息

         @param feedId feedId
         @return result
         */
        virtual bool deleteFollowFeedId(const char* feedId) = 0;
        
#pragma mark -----------------message------------------
        /**
         addMessage

         @param messages message对象集合
         @return true
         */
        virtual bool addMessages(vector<CTNMessage> &messages)  = 0;
        
        /**
         addMessage

         @param message message对象
         @return true
         */
        virtual bool addMessage(toonim::CTNMessage &message) = 0;
        
        /**
         replace message

         @param message message
         @return true
         */
        virtual bool replaceMessage(toonim::CTNMessage &message) = 0;
        
        /**
         replace message

         @param messages message
         @return true
         */
        virtual bool replaceMessages(vector<CTNMessage> &messages) = 0;
        
        /**
         deleteMessage，只标记消息状态为删除，不真实删除数据

         @param sessionId sessionId
         @param msgId msgId
         @return true
         */
        virtual bool deleteMessage(const char* sessionId, const char* msgId)  = 0;
        
        /**
         删除某一会话的所有message

         @param sessionId sessionId
         @return true
         */
        virtual bool deleteAllMessage(const char* sessionId)  = 0;
        
        /**
         彻底删除数据

         @param sessionId sessionid
         @param msgId msgId
         @return true
         */
        virtual bool physicalDeletionMessage(const char* sessionId, const char* msgId) = 0;
        
        /**
         更新message

         @param message message对象
         @return true
         */
        virtual bool updateMessage(CTNMessage &message)  = 0;
        
        /**
         更新message content

         @param msgId msgid
         @param sessionId sessionId
         @param content content json
         @return true
         */
        virtual bool updateContent(const char* msgId, const char* sessionId, const char* content)  = 0;
        
        /**
         update sendStatus

         @param msgId msgId
         @param sessionId sessionId
         @param sendStatus sendStatus
         @return true
         */
        virtual bool updateSendStatus(const char* msgId, const char* sessionId, int32_t sendStatus)  = 0;
        
        /**
         update addition

         @param msgId msgId
         @param sessionId sessionId
         @param addition addition
         @return true
         */
        virtual bool updateAddition(const char* msgId, const char* sessionId, const char* addition)  = 0;
        
        /**
         获取message

         @param sessionId sessionId
         @param seqId seqId
         @param count count
         @return message对象集合
         */
        virtual vector<CTNMessage> getMessages(const char* sessionId, int64_t seqId, int32_t count)  = 0;
        
        /**
         根据seqId、顺序获取message
         
         @param sessionId sessionId
         @param seqId seqId
         @param count count
         @return message对象集合
         */
        virtual vector<CTNMessage> getMessagesAsc(const char*  sessionId, int64_t seqId, int32_t count) = 0;

        /**
         获取断层message

         @param sessionId sessionid
         @param seqId seqId
         @param count count
         @return message集合
         */
        virtual vector<CTNMessage> getFaultMessages(const char* sessionId, int64_t seqId, int32_t count)  = 0;
        
        /**
         根据不同的contenttype取每个会话的消息

         @param sessionId sessionId
         @param contentType contentType
         @return message集合
         */
        virtual vector<CTNMessage> getMessagesWithContentType(const char* sessionId, CTNMessageContentType contentType) = 0;
        
        /**
         根据文件类型获取message

         @param sessionId sessionId
         @param contentType contentType
         @param formats 文件后缀名类型
         @return message对象集合
         */
        virtual vector<CTNMessage> getFileMessagesWithSessionId(const char*  sessionId, CTNMessageContentType contentType,vector<std::string> formats) = 0;
        
        /**
         根据contenttype和ismyself获取message
         
         @param sessionId sessionId为空筛选全部消息，不为空筛选当前会话
         @param contentType 消息类型
         @param isMySelf 是否自己发送的
         @return 消息集合
         */
        virtual vector<CTNMessage> getMessages(const char* sessionId, CTNMessageContentType contentType, CTNOwner isMySelf) = 0;
        
        /**
         根据两个seqid区间取消息，取得区间内的message

         @param sessionId sessionId
         @param maxSeqId maxSeqId
         @param minSeqId minSeqId
         @return message对象集合
         */
        virtual vector<CTNMessage> getMessagesWithSeqId(const char* sessionId, int64_t maxSeqId, int64_t minSeqId) = 0;
        
        /**
         getMessage

         @param sessionId sessionId
         @param msgId msgId
         @return message对象
         */
        virtual CTNMessage getMessage(const char* sessionId, const char* msgId)  = 0;
        
        
        /**
         根据bizNo获取bizNo相同的通知消息中seqid最大的消息

         @param sessionId sessionId
         @param bizNo bizNo
         @return message
         */
        virtual CTNMessage getMaxNoticeMessage(const char* sessionId, const char* bizNo) = 0;
        
        /**
         getFultMessage

         @param sessionId sessionid
         @param priority 优先级
         @return message
         */
        virtual CTNMessage getFaultMessage(const char* sessionId, int32_t priority)  = 0;
        
        /**
         getLastMessage

         @param sessionId sessionId
         @return message对象
         */
        virtual CTNMessage getLastMessage(const char* sessionId) = 0;
        
        /**
         获取某一会话的最大seqId

         @param sessionId sessionId
         @param type 权限类型，0:普通优先级，1:高优先级，2:混合优先级
         @return message对象
         */
        virtual int64_t getMaxSeqAllMessage(const char* sessionId, int32_t type) = 0;
        
        /**
         获取通知消息的noticeStatusType

         @param sessionId sessionId
         @return string集合
         */
        virtual vector<std::string> getNoticeStatusType(const char* sessionId) = 0;
        
        /**
         通知类型消息根据noticeStatusType筛选

         @param sessionId sessionId
         @param seqId seqId
         @param count count
         @param noticeStatusType 通知状态类型
         @return message对象集合
         */
        virtual vector<toonim::CTNMessage> getMessageWithNoticeStatusType(const char* sessionId, int64_t seqId, int32_t count, const char* noticeStatusType) = 0;
        
        /**
         搜索message

         @param keyword keyword
         @param sessionId sessionId
         @param messages message对象集合
         */
        virtual void searchMessage(const char* keyword, const char* sessionId, vector<std::vector<std::string> > &messages) = 0;
        
        /**
         获取所有断层

         @return 断层的sessions
         */
        virtual vector<CTNMessage> getAllFaultMessage() = 0;
        
#pragma mark -------------------importantMessage---------------
        
        /**
         添加重要消息，at和关注的人等

         @param type 消息类型
         @param message 消息
         */
        virtual void addImportantMessage(CTNIMMessageType type, CTNMessage &message) = 0;
        
        /**
         删除某个session的所有重要消息，不区分类型
         @param sessionId sessionId
         */
        virtual void deleteImportantSessionBySessionId(const char* sessionId) = 0;
        
        /**
         删除at或关注的人等消息
         
         @param msgId 消息id
         @param type 消息类型
         @return result
         */
        virtual bool deleteImportantMessage(CTNIMMessageType type, const char* msgId) = 0;
        
        /**
         根据消息类型和sessionId删除重要的消息

         @param type 消息类型
         @param sessionId 会话id
         @return result
         */
        virtual bool deleteImportantMessageBySessionId(CTNIMMessageType type, const char* sessionId) = 0;
        
        /**
         删除所有重要消息
         
         @param type 消息类型
         @return result
         */
        virtual bool deleteAllImportantMessage(CTNIMMessageType type) = 0;
        
        /**
         获取重要消息的数量
         
         @param type 消息类型
         @return count
         */
        virtual int32_t getImportantMessageCount(CTNIMMessageType type) = 0;
        
        /**
         获取重要的消息列表
         
         @param type 消息类型
         @param feedId 我的feedId，为空获取全部，不为空获取和该feedId相关的消息
         @param timestamp 消息时间戳，第一次获取填0，再次获为上次获取列表的最后一条消息的时间戳
         @param msgId 第一次填空，再次获取为上次获取列表的最后一条消息的magId
         @param count 分页获取数量
         @return 关注的人列表
         */
        virtual vector<CTNMessage> getImportantMessageList(CTNIMMessageType type, const char* feedId, int64_t timestamp, const char *msgId, int32_t count) = 0;
        
#pragma mark ------------------operateMessage------------
        
        /**
         add operate message

         @param operates operates
         @return true
         */
        virtual bool addOperateMessage(vector<CTNMessageOperate> &operates) = 0;
        
        /**
         delete operate message

         @param msgId msgId
         @return true
         */
        virtual bool deleteOperateMessage(const char* msgId) = 0;
        
        /**
         get operate message

         @param msgId msgId
         @return true
         */
        virtual CTNMessageOperate getOperateMessage(const char* msgId) = 0;
        
        /**
         get all operate message

         @return operateMessage
         */
        virtual vector<CTNMessageOperate> getAllOperateMessages() = 0;
        
        /**
         translate Operate Message

         @param operMessage operMessage
         @return true
         */
        virtual bool translateOperateMessage(CTNMessageOperate operMessage) = 0;//wxy
        
        /**
         数据库版本管理

         @return void
         */
        virtual uint32_t userVersion() = 0;
        
        /**
         设置数据管理

         @param version version
         */
        virtual void setUserVersion (uint32_t version ) = 0;
        
#ifdef __APPLE__
        /**
         迁移数据库 适用于ios平台
         */
        virtual void migrateDataOfSession() = 0;
#endif
    };

   
    class ITnImDBGroupChat
    {
    public:
        virtual ~ITnImDBGroupChat(){}
        
#pragma mark ------------appInfo----------------
        
        /**
         add appInfo

         @param appInfos appinfos
         @return true
         */
        virtual bool addAppInfo(vector<CTNAppInfo> &appInfos)   = 0;
        
        /**
         delete appInfo

         @param appId appId
         @return true
         */
        virtual bool deleteAppInfo(const char* appId)  = 0;
        
        /**
         update appInfo

         @param appInfos appInfos
         @return true
         */
        virtual bool updateAppInfo(vector<CTNAppInfo> &appInfos)  = 0;
        
        /**
         get appInfo

         @param appId appId
         @return true
         */
        virtual CTNAppInfo getAppInfo(const char* appId)  = 0;
        
#pragma mark ------------groupInfo--------------
        
        /**
         add groupInfo

         @param groups groups
         @return true
         */
        virtual bool addGroupInfo(vector<CTNGroupInfo> &groups)  = 0;
        
        /**
         delete groupInfo

         @param groupId groupId
         @return true
         */
        virtual bool deleteGroupInfo(int64_t groupId)  = 0;
        
        /**
         update groupInfo

         @param groups groups
         @return true
         */
        virtual bool updateGroupInfo(vector<CTNGroupInfo> &groups)  = 0;
        
        /**
         get groupInfo

         @param groupId groupId
         @return groupInfo对象
         */
        virtual CTNGroupInfo getGroupInfo(int64_t groupId)  = 0;
        
        /**
         根据feedId获取该feedId加入的群聊

         @param feedId feedId
         @return groupInfo对象集合
         */
        virtual vector<toonim::CTNGroupInfo> getGroupInfoWithMyFeedId(const char* feedId) = 0;
        
        /**
         根据关键字搜索该feedid加入的群聊，feedid为空则搜索所有的群聊

         @param keyword 关键字
         @param feedId feedid
         @param groupInofs groupInfos
         */
        virtual void searchGroupInfo(const char* keyword, const char* feedId, vector<toonim::CTNGroupInfo> &groupInofs) = 0;
        
        /**
         根据拼音搜索该feedid加入的群聊，feedid为空则搜索所有的群聊

         @param keyword 关键字
         @param feedId feedid
         @param groupInofs groups
         */
        virtual void searchGroupInfoWithPinyin(const char* keyword, const char* feedId, vector<toonim::CTNGroupInfo> &groupInofs) = 0;

#pragma mark -------------------groupMember----------------
        
        /**
         add groupMember

         @param members members
         @return true
         */
        virtual bool addGroupMember(vector<CTNGroupMember> &members)  = 0;
        
        /**
         update groupMembers

         @param members members
         @return true
         */
        virtual bool updateGroupMembers(vector<CTNGroupMember> &members)  = 0;
        
        /**
         delete all groupMeber by groupId

         @param groupId groupId
         @return true
         */
        virtual bool deleteAllGroupMembers(int64_t groupId)  = 0;
        
        /**
         delete groupMember by groupid and feedId

         @param groupId groupId
         @param feedId feedId
         @return true
         */
        virtual bool deleteGroupMember(int64_t groupId, const char* feedId)  = 0;
        
        /**
         get groupMembers

         @param groupId groupId
         @return groupMember对象集合
         */
        virtual vector<CTNGroupMember> getGroupMembers(int64_t groupId)  = 0;
        
        /**
         get groupMember by groupId and feedId

         @param groupId groupId
         @param feedId feedId
         @return groupMember对象
         */
        virtual CTNGroupMember getGroupMember(int64_t groupId, const char* feedId) = 0;
        
        /**
         根据feedId获取groupMember

         @param feedId feedId
         @param groupMembers groupMember对象集合
         */
        virtual void getGroupMembersWithFeedId(const char*  feedId, vector<toonim::CTNGroupMember> &groupMembers) = 0;
        
        /**
         获取群聊人数

         @param groupId groupId
         @return count
         */
        virtual int getGroupMembersCount(int64_t groupId) = 0;
        
        /**
         搜索群成员

         @param keyword 关键字
         @param groupIds groupIds
         @param groupMembers groupMembers
         */
        virtual void searchGroupMember(const char* keyword, const vector<std::string> &groupIds, vector<toonim::CTNGroupMember> &groupMembers) = 0;
        
        /**
         根据拼音搜索群成员
         
         @param keyword 关键字
         @param groupIds groupIds
         @param groupMembers groupMembers
         */
        virtual void searchGroupMemberWithPinyin(const char* keyword, const vector<std::string> &groupIds, vector<toonim::CTNGroupMember> &groupMembers) = 0;
    };

    
    class ITnImDBSettings
    {
    public:
        virtual ~ITnImDBSettings(){}
        
#pragma mark --------------setting-----------
        
        /**
         add setting

         @param sessionId key 根据type确定
         @param type type
         @param value value
         @return true
         */
        virtual bool addSessionSetting(const char* sessionId, CTNSESSIONTYPE type, const char* value) = 0;
        
        /**
         update setting

         @param sessionId key 根据type确定
         @param type type
         @param value value
         @return true
         */
        virtual bool updateSessionSetting(const char* sessionId, CTNSESSIONTYPE type, const char* value) = 0;
        
        /**
         get setting

         @param sessionId key 根据type确定
         @param type type
         @return setting对象
         */
        virtual CTNSessionSetting getSessionSetting(const char* sessionId, CTNSESSIONTYPE type) = 0;
        
        /**
         get SessionSettingDisturb
         
         @param sessionId key 根据type确定
         @return 是否免打扰
         */
        virtual int32_t getSessionSettingDisturb(const char* sessionId) = 0;
        
        /**
         delete setting

         @param sessionId key 根据type确定
         @param type type
         @return true
         */
        virtual bool deleteSessionSetting(const char* sessionId, CTNSESSIONTYPE type) = 0;
        
#pragma mark -----------importantMessage--------
        
        /**
         设置at和关注人等开关

         @param type 消息类型
         @param status 状态
         @return result
         */
        virtual bool setImportantSwitch(CTNIMMessageType type, bool status) = 0;
        
        /**
         获取at和关注的人等开关状态

         @param type 消息类型
         @return result
         */
        virtual bool getImportantStatus(CTNIMMessageType type) = 0;
        
        /**
         设置关注的人

         @param feedId 关注的人的feedId
         @param status 设置状态
         */
        virtual void setFollowFeedId(const char* feedId, bool status) = 0;
        
        /**
         设置关注的人，批量设置
         
         @param followList CTNFollowFeed
         */
        virtual void setFollowFeedIdList(const vector<toonim::CTNFollowFeed> &followList) = 0;
        
        /**
         获取我关注的人名单
         */
        virtual vector<std::string> getMyFollowFeedList() = 0;
        
#pragma mark ----------blackList-----------------
        
        /**
         add blackList

         @param feedId feedId
         @param passiveFeedId passiveFeedId
         @return true
         */
        virtual bool addBlackList(const char* feedId, const char* passiveFeedId, int32_t status) = 0;
        
        /**
         delete blackList

         @param blackList 删除的数据
         @return true
         */
        virtual bool deleteBlackList(vector<CTNBlackListModel>& blackList) = 0;
        
        /**
         update blackList

         @param blackList blackList对象
         @return true
         */
        virtual bool updateBlackList(vector<CTNBlackListModel>& blackList) = 0;
        
        /**
         get blackList by feedid，feedid为空获取全部

         @param feedId feedId
         @return true
         */
        virtual vector<toonim::CTNBlackListModel> getBlackList(const char* feedId) = 0;
        
        /**
         get blackModel

         @param feedId feedid
         @param passiveFeedId passiveFeedId
         @return blackModel
         */
        virtual CTNBlackListModel getBlackModel(const char* feedId, const char* passiveFeedId) = 0;
        
        /**
         get BlackAndDisturb
         
         @param feedId feedId
         @param passiveFeedId passiveFeedId
         @return blackModel
         */
        virtual CTNBlackListModel getBlackAndDisturbModel(const char* feedId, const char* passiveFeedId) = 0;
        
        /*判断某项功能是否禁止
         * @param key 功能key，定义见：TNIMTypedef.h
         * 判断某项功能是否禁止
         */
        virtual bool isForbiddenFeature(const char* key) = 0;

    };
    
    void resetDB();
    
    //@todo 此处函数调用，多线程可能会有问题，需要进一步进行处理 add by lanhuaiyu@20171014
  
    void initImDB(const char* clientId, const char* appPath);
    
//    ITnImDBChat* initChatDB(const char* clientId, const char* appPath);
    //    ITnImDBGroupChat* initGroupChatDB(const char* clientId, const char* appPath);
    //    ITnImDBSettings* initSettingsDB(const char* clientId, const char * appPath);

    ITnImDBChat* getChatDB();
    
    ITnImDBGroupChat* getGroupChatDB();
    
    ITnImDBSettings* getSettingsDB();
    
    
}


#endif /* CTNDBAPI_hpp */
