//
//  CTNDBChat.cpp
//  CTNSDK
//
//  Created by 王海涛 on 2017/8/23.
//  Copyright © 2017年 syswin. All rights reserved.
//

#include "CTNDBChat.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <thread>
#include <CLog.h>
#include "rapidjson.h"
#include "document.h"
#include "stringbuffer.h"
#include "writer.h"
#include "prettywriter.h"
#include "CTNDBHeader.h"
#include "CTNDBUtils.hpp"
#include "CTNDBMigrate.hpp"
#include "CTNDBSettings.hpp"
#include "CTNDBGroupChat.hpp"
#include <mutex>
#include <algorithm>
#include "CTNBaseBean.h"

#define CLBDB_VER 2

namespace toonim {
    
    void resetDB()
    {
        CSqliteDB::reset();
    }
    
    void initImDB(const char* clientId, const char* appPath)
    {
        if (clientId == nullptr || strlen(clientId) == 0
            || appPath == nullptr || strlen(appPath) == 0){
            return;
        }
        
        //判断是否为第一次启动或是切换账号
        bool isNeedUpdate = false;
        CTNDBChat* dbChat = CTNDBChat::instance();
        if (nullptr != dbChat) {
            if (dbChat->getClientId() != clientId) {
                isNeedUpdate = true;
            }
        } else {
            isNeedUpdate = true;
        }
        
        CTNDBChat::instance(clientId, appPath);
        CTNDBGroupChat::instance(clientId, appPath);
        CTNDBSetting::instance(clientId, appPath);
        if (CTNDBChat::instance() != nullptr) {
            CTNDBChat::instance()->resetSessionSendingStatus();
        }
        
        if (isNeedUpdate && CTNDBSetting::instance() != nullptr) {
            CTNDBSetting::instance()->loadSettingCache();
        }
    }
    
    
    ITnImDBChat* getChatDB()
    {
        return  CTNDBChat::instance();
    }
    
    
    CTNDBChat* CTNDBChat::_instance = nullptr;
    
    CTNDBChat* CTNDBChat::instance()
    {
//        assert(_instance != nullptr);
        return _instance;
    }
    
    CTNDBChat* CTNDBChat::instance(const char* clientId, const char* appPath)
    {
        if (_instance == nullptr) {
            _instance = new CTNDBChat();
        }
        
        //切换用户或者初次设置时进行初始化
        if (clientId != _instance->_clientId){
            _instance->doInitUserDB(clientId, IMCHATDB, appPath);
            _instance->getSessions("", false);
            _instance->getSessions("", true);
        }
        
        return _instance;
    }
    
    CTNDBChat::CTNDBChat()
    {
        _resetSessionSendStatus = false;
    }
    
    void CTNDBChat::createTable()
    {
        //需要判断是否创建表
        this->beginTransation();
        this->execSql("CREATE TABLE IF NOT EXISTS Session(sessionId varchar(40) NOT NULL, topic varchar(20), myFeedId varchar(20) not null default ' ', type int, title text,  avatarId text, draft text, lastTime long, lastMsg text, lastMsgId text, lastMsgSendStatus int, readSeqId int, sortTime long, atMeMsgId text ,unreadCount int, topStatus int default 0, PRIMARY KEY(sessionId))");
        this->execSql("CREATE INDEX if not exists Session_index ON Session(sessionId ASC, 'topic' ASC, 'sortTime' ASC, 'type' asc, 'myFeedId' asc, 'lastMsgId' asc, 'topStatus' asc)");
        
        TNMPLOG("createTable session");
        
        for (int i=0; i<TABLE_COUNT_MESSAGE; i++) {
            char sql[1024] = {0};
            
            sprintf(sql, "create table if not exists BMessage%d (msgId varchar(40) NOT NULL, sessionId varchar(50), type int, seqId long, fromId varchar(30),toId text,fromClientId text,toClientId varchar(30),timestamp long,pushInfo text, sendStatus int,senderName text, status int,priority int, catalogId int,content text,  contentType int, width int, height int, atType int,atFeeds  text,fileFormat text,noticeStatusType text,flags long,faultSeqId long, isMyself int,subCatalogId int,addition text, bizNo text, primary key (msgId));", i);
            this->execSql(sql);
            
            sprintf(sql, "create INDEX if not exists BMessage%d_index on BMessage%d('sessionId' asc, 'msgId' asc,'seqId' asc,'type' asc,'fromId' asc,'toId' ASC,'contentType' asc,'catalogId' asc, 'sendStatus' asc, 'faultSeqId' asc, 'bizNo' asc)", i, i);
            this->execSql(sql);
            
            TNMPLOG("createTableMessae:" << i);
        }
        
        this->execSql("CREATE TABLE IF NOT EXISTS MessageOperate(msgId text UNIQUE, seqId long default 0, type int default 0, mfrom text , mto text,timestamp int, catalogId int default 0, content text,opMsgId text,opFeedId text,opName text, primary key (msgId,seqId));");
        this->execSql("CREATE INDEX if not exists MessageOperate_index ON MessageOperate('msgId' asc,'seqId' asc,'type' ASC,'mfrom' ASC,'mto' ASC,'opMsgId' asc);");
        
        //at消息表
        this->execSql("create table if not exists AtMessage (msgId varchar(40) NOT NULL, sessionId varchar(50), type int, seqId long, fromId varchar(30),toId text,fromClientId text,toClientId varchar(30),timestamp long,pushInfo text, sendStatus int,senderName text, status int,priority int, catalogId int,content text,  contentType int, width int, height int, atType int,atFeeds  text,fileFormat text,noticeStatusType text,flags long,faultSeqId long, isMyself int,subCatalogId int,addition text, bizNo text, primary key (msgId))");
        this->execSql("create index if not exists AtMessage_index on AtMessage('msgId' asc,'sessionId' asc)");
        
        //关注的人表
        this->execSql("create table if not exists FollowMessage (msgId varchar(40) NOT NULL, sessionId varchar(50), type int, seqId long, fromId varchar(30),toId text,fromClientId text,toClientId varchar(30),timestamp long,pushInfo text, sendStatus int,senderName text, status int,priority int, catalogId int,content text,  contentType int, width int, height int, atType int,atFeeds  text,fileFormat text,noticeStatusType text,flags long,faultSeqId long, isMyself int,subCatalogId int,addition text, bizNo text, primary key (msgId))");
        this->execSql("create index if not exists FollowMessage_index on FollowMessage('msgId' asc,'sessionId' asc)");
        
        this->commitTransation();
        
        if (_sqliteDb != nullptr) {
            _sqliteDb->makeFunction("contentFunc", contentFunc);
        }
        
        return ;
    }
    
    
    void CTNDBChat::resetSessionSendingStatus()
    {
        if (_resetSessionSendStatus) {
            return;
        }
        //此处只更新session表，message表在启动首次进入每个会话的时候，分别更新每个会话
        std::ostringstream s;
        s << "update Session set lastMsgSendStatus=" << CTNMessageFailed << " where lastMsgSendStatus=" << CTNMessageSending;
        std::string sql = s.str();
        this->execSql(sql.c_str());
        
        _resetSessionSendStatus = true;
        
        TNMPLOG("resetSessionSendingStatus");
    }
    
    void CTNDBChat::resetMessageSendingStatusWithSessionId(const char* sessionId)
    {
        TNMPLOG("start resetMessageSendingStatusWithSessionId: " << sessionId << "");
        //启动后，首次进入某个会话，如果未reset过此session，则reset一遍
        if (sessionId == nullptr || strlen(sessionId) == 0) {
            return;
        }
        
        std::set<string>::iterator iter = _sessionIdSet.find(sessionId);
        if (iter != _sessionIdSet.end()) {
            TNMPLOG("don't need resetMessageSendingStatusWithSessionId: " << sessionId << "");
            return;
        }
        
        int tableIndex = this->generateTableIndex(sessionId);
        std::ostringstream s;
        s << "update BMessage" << tableIndex << " set sendStatus=" << CTNMessageFailed << " where sessionId ='" << sessionId << "' and sendStatus=" << CTNMessageSending << "";
        std::string sql = s.str();
        this->execSql(sql.c_str());
        
        _sessionIdSet.insert(sessionId);
        TNMPLOG("end resetMessageSendingStatusWithSessionId: " << sessionId << "");
    }

#pragma mark -------------Session-------------------
    bool CTNDBChat::addSession(vector<CTNSession> &sessions)
    {
        if (sessions.size() <= 0) {
            return false;
        }
        
        this->beginTransation();
        for (int i=0;i<sessions.size();i++) {
            CTNSession session = sessions.at(i);
            map<string, pair<CTNDBBase::FT, string>> info;
            this->genSessionMap(session, info);
            replaceRecord("Session", info);
         }
        this->commitTransation();

        return true;
    }
    
    bool CTNDBChat::updateSession(vector<CTNSession> &sessions)
    {
        if (sessions.size() <= 0) {
            return false;
        }
        
        this->beginTransation();
        for (int i=0;i<sessions.size();i++) {
            CTNSession session = sessions.at(i);
            map<string, pair<CTNDBBase::FT, string>> info;
            this->genSessionMap(session, info);
            replaceRecord("Session", info);
        }
        this->commitTransation();
        
        return true;
    }
    
    bool CTNDBChat::updateSessionTitleAndImage(const char* sessionId, const char* title, const char* avatarId)
    {
        if (sessionId == nullptr || strlen(sessionId) == 0) {
            TNMPLOG("updateSessionTitleAndImage sessionId is null");
            return false;
        }
        if ((title == nullptr || strlen(title) == 0) && (avatarId == nullptr || strlen(avatarId) == 0)) {
            TNMPLOG("updateSessionTitleAndImage title = " << title << ", avatarid = " << avatarId);
            return false;
        }
        
        map<string, pair<CTNDBBase::FT, string>> info;
        if (title != nullptr && strlen(title) != 0) {
            info["title"] = make_pair(CTNDBBase::DB_STR, title);
        }
        if (avatarId != nullptr && strlen(avatarId) != 0) {
            info["avatarId"] = make_pair(CTNDBBase::DB_STR, avatarId);
        }
        
        std::ostringstream s;
        s << "where sessionId='" << sessionId << "'";
        size_t result = updateRecord("Session", info, s.str().c_str());
        
        if (result <= 0) {
            return false;
        }
        
        return true;
    }
    
    bool CTNDBChat::updateSessionLastMsgAndLastTime(const char* sessionId, const char* lastMsg, int64_t lastTime)
    {
        if (sessionId == nullptr || strlen(sessionId) == 0) {
            TNMPLOG("updateSessionLastMsgAndLastTime sessionId is null");
            return false;
        }
        if ((lastMsg == nullptr || strlen(lastMsg) == 0) && lastTime <= 0) {
            TNMPLOG("updateSessionLastMsgAndLastTime lastMsg = " << lastMsg << " , lastTime = " << lastTime);
            return false;
        }
        
        map<string, pair<CTNDBBase::FT, string>> info;
        if (lastMsg != nullptr && strlen(lastMsg) != 0) {
            info["lastMsg"] = make_pair(CTNDBBase::DB_STR, lastMsg);
        }
        if (lastTime > 0) {
            info["lastTime"] = make_pair(CTNDBBase::DB_LONG, CTNDBUtils::stringFromInt64(lastTime));
            info["sortTime"] = make_pair(CTNDBBase::DB_LONG, CTNDBUtils::stringFromInt64(lastTime));
        }
        
        std::ostringstream s;
        s << "where sessionId='" << sessionId << "'";
        size_t result = updateRecord("Session", info, s.str().c_str());
        
        if (result <= 0) {
            return false;
        }
        return true;
    }
    
    void CTNDBChat::genSessionMap(toonim::CTNSession& session, map<string, pair<CTNDBBase::FT, string>> &info)
    {
        info["sessionId"] = make_pair(CTNDBBase::DB_STR, session.sessionId);
        info["topic"] = make_pair(CTNDBBase::DB_STR, session.topic);
        info["myFeedId"] = make_pair(CTNDBBase::DB_STR, session.myFeedId);
        info["type"] = make_pair(CTNDBBase::DB_INT, CTNDBUtils::stringFromInt32(session.type));
        info["title"] = make_pair(CTNDBBase::DB_STR, session.title);
        info["avatarId"] = make_pair(CTNDBBase::DB_STR, session.avatarId);
        info["draft"] = make_pair(CTNDBBase::DB_STR, session.draft);
        info["lastTime"] = make_pair(CTNDBBase::DB_LONG, CTNDBUtils::stringFromInt64(session.lastTime));
        info["lastMsg"] = make_pair(CTNDBBase::DB_STR, session.lastMsg);
        info["lastMsgId"] = make_pair(CTNDBBase::DB_STR, session.lastMsgId);
        info["lastMsgSendStatus"] = make_pair(CTNDBBase::DB_INT, CTNDBUtils::stringFromInt32(session.lastMsgSendStatus));
        info["readSeqId"] = make_pair(CTNDBBase::DB_LONG, CTNDBUtils::stringFromInt64(session.readSeqId));
        info["sortTime"] = make_pair(CTNDBBase::DB_LONG, CTNDBUtils::stringFromInt64(session.sortTime));
        info["atMeMsgId"] = make_pair(CTNDBBase::DB_STR, session.atMeMsgId);
        info["unreadCount"] = make_pair(CTNDBBase::DB_INT, CTNDBUtils::stringFromInt32(session.unreadCount));
        info["topStatus"] = make_pair(CTNDBBase::DB_INT, CTNDBUtils::stringFromInt32(session.topStatus));
    }
    
    bool CTNDBChat::deleteSession(const char* sessionId)
    {
        if (sessionId == nullptr || strlen(sessionId) == 0) {
            return false;
        }
        
        std::ostringstream s;
        s << "delete from Session where sessionId='" << sessionId << "'";
        std::string sql = s.str();
        this->execSql(sql.c_str());
        this->deleteAllMessage(sessionId);
        if (toonim::getSettingsDB() != nullptr) {
            toonim::getSettingsDB()->deleteSessionSetting(sessionId, SESSION_TYPE_BACKGROUND);
        }
        
        return true;
    }
    
    CTNSession CTNDBChat::getSession(const char* sessionId)
    {
        if (sessionId == nullptr || strlen(sessionId) == 0) {
            return CTNSession();
        }
        
        std::ostringstream s;
        s << "select * from Session where sessionId='" << sessionId << "'";
        std::string sql = s.str();
        
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
        
        if (records == NULL) {
            return CTNSession();
        }
        
        if (records->step() == CSqliteDBStatement::STEP_ROW) {
            return this->generateSession(records);
        } else {
            return CTNSession();
        }
    }
    
    vector<CTNSession> CTNDBChat::getSessions(const char* myFeedId, bool isContainNotice)
    {
        TNMPLOG("getSessions=====feedId:" << (myFeedId?myFeedId:""));
        
        std::string containNotice = "";
        ostringstream noticeStream;
        if (!isContainNotice) {
             noticeStream <<" and type!=" << CTNIMMessageTypeBizNotice;
            containNotice = noticeStream.str();
        }
        
        std::ostringstream s;
        if (myFeedId == nullptr || strlen(myFeedId) == 0) {
            s << "select * from Session where lastMsgId != ''" << containNotice << " order by topStatus desc, sortTime desc";
        } else {
            if (toonim::getGroupChatDB() != nullptr) {
                vector<toonim::CTNGroupInfo> groups = toonim::getGroupChatDB()->getGroupInfoWithMyFeedId(myFeedId);
                std::ostringstream g;
                for (int i=0; i<groups.size(); i++) {
                    CTNGroupInfo groupInfo = groups.at(i);
                    if (i == groups.size() - 1) {
                        g << groupInfo.topic;
                    } else {
                        g << groupInfo.topic << "','";
                    }
                }
                s << "select * from Session where lastMsgId != ''" << containNotice << " and  (myFeedId='" << myFeedId << "' or topic in ('" << g.str() << "')) order by topStatus desc, sortTime desc";
            } else {
                TNMPLOG("groupChatDB init failure");
            }
        }
        std::string sql = s.str();
        vector<CTNSession> sessionList = vector<CTNSession>();
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
        
        if (records == NULL) {
            TNMPLOG("getSessions=====finished,records == NULL,feedId:" << (myFeedId?myFeedId:""));
            return sessionList;
        }
        
        //判断是否打开at开关和关注的人开关，records为空说明没有会话消息不显示at和关注的人
        if (CTNDBSetting::instance() != nullptr) {
            //重要消息没有身份，只有当myfeedid为空时才需要获取重要消息的session
            if (myFeedId == nullptr || strlen(myFeedId) == 0) {
                this->insertImportantSession(sessionList);
            }
        }
        
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            CTNSession session = this->generateSession(records);
            if (session.type == CTNIMMessageTypeChat && toonim::getSettingsDB() != nullptr) {
                CTNBlackListModel blackModel = toonim::getSettingsDB()->getBlackModel(session.myFeedId.c_str(), session.topic.c_str());
                if ((blackModel.status & CTNBlackListType) == CTNBlackListType) {
                    continue;
                }
           }
            sessionList.push_back(session);
        }
        TNMPLOG("getSessions=====finished, sessionList.size:" << sessionList.size());
        
        return sessionList;
    }
    
    int CTNDBChat::getUnreadCount(const char* feedId, const char* sessionId)
    {
        vector<CTNSession> sessionList = this->getSessions(feedId, true);
        bool isShowRedPoint = false;
        int unreadCount = 0;

        for (int i=0; i<sessionList.size(); i++) {
            CTNSession session = sessionList.at(i);
            //过滤at和关注的人消息未读数
            if (session.type == CTNIMMessageTypeAt || session.type == CTNIMMessageTypeFollow) {
                continue;
            }
            
            if (sessionId != nullptr && strlen(sessionId) > 0) {
                if (strcmp(sessionId, session.sessionId.c_str()) == 0) {
                    //过滤该session的未读数
                    continue;
                }
            }

            if (session.unreadCount <= 0) {
                continue;
            }

            if (session.disturbStatus) {
                isShowRedPoint = true;
            } else {
                unreadCount += session.unreadCount;
            }
        }

        if (unreadCount > 0) {
            //显示未读数
            return unreadCount;
        } else if (isShowRedPoint) {
            //显示红点
            return -1;
        } else {
            //不显示未读
            return 0;
        }
    }
    
    int CTNDBChat::getUnreadCountUnContainFeedId(const char* feedId)
    {
        if (feedId == nullptr || strlen(feedId) == 0) {
            return 0;
        }
        
        vector<CTNSession> sessionList = this->getSessions("", true);
        
        for (int i=0; i<sessionList.size(); i++) {
            CTNSession session = sessionList.at(i);
            
            if (session.unreadCount <= 0) {
                continue;
            }
            
            if (strcmp(feedId, session.myFeedId.c_str()) == 0 && session.myFeedId.length() > 0) {
                //过滤该session的未读数
                continue;
            }
            
            if (session.type == CTNIMMessageTypeGroupChat) {
                if (toonim::getGroupChatDB() != nullptr) {
                    string strGroupId = session.topic.substr(3, session.topic.length());
                    int64_t groupId = atoll(strGroupId.c_str());
                    CTNGroupInfo groupInfo = toonim::getGroupChatDB()->getGroupInfo(groupId);
                    if (strcmp(groupInfo.myFeedId.c_str(), feedId) == 0) {
                        continue;
                    }
                }
            }
            
            //只要其他会话有未读数，左上角筛选都会显示红点，不需要再进行循环便利所有会话
            return -1;
        }
        
        //其他会话没有未读数
        return 0;
    }
    
    bool CTNDBChat::markSessionRead(const char* sessionId)
    {
        std::ostringstream s;
        s << "update Session set unreadCount=0,atMeMsgId='',readSeqId=" << getMaxSeqAllMessage(sessionId, 2) << " where sessionId='" << sessionId << "'";
        std::string sql = s.str();
        this->execSql(sql.c_str());
        
        return true;
    }
    
    bool CTNDBChat::markSessionUnread(const char* sessionId)
    {
        std::ostringstream s;
        s << "update Session set unreadCount=1 where sessionId='" << sessionId << "'";
        std::string sql = s.str();
        this->execSql(sql.c_str());
        
        return true;
    }
    
    bool CTNDBChat::clearAllUnreadCount()
    {
        vector<CTNSession> sessionList;
        
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql("select * from Session where unreadCount>0");
        if (records == NULL) {
            return false;
        }
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            CTNSession session = this->generateSession(records);
            sessionList.push_back(session);
        }
        
        this->beginTransation();
        for (int i=0; i<sessionList.size(); i++) {
            CTNSession session = sessionList.at(i);
            if (session.unreadCount == 0) {
                continue;
            }
            this->markSessionRead(session.sessionId.c_str());
        }
        this->commitTransation();
        
        return true;
    }
    
#pragma mark ----------BMessage-----------
    bool CTNDBChat::addMessages(vector<CTNMessage>& messages)
    {
        if (messages.size() <= 0) {
            return false;
        }
        
        this->beginTransation();
        for (int i=0; i<messages.size(); i++) {
            CTNMessage message = messages.at(i);
            if (message.isEmpty()) {
                continue;
            }
            
            map<string, pair<CTNDBBase::FT, string>> info;
            this->genMessageMap(message, info);
            int tableIndex = this->generateTableIndex(message.sessionId.c_str());
            insertRecord("BMessage"+CTNDBUtils::stringFromInt32(tableIndex), info);
        }
        this->commitTransation();
        
        return true;
    }
    
    bool CTNDBChat::addMessage(toonim::CTNMessage& message)
    {
        if (message.msgId.length() <= 0) {
            return false;
        }
        
        map<string, pair<CTNDBBase::FT, string>> info;
        this->genMessageMap(message, info);
        int tableIndex = this->generateTableIndex(message.sessionId.c_str());
        insertRecord("BMessage"+CTNDBUtils::stringFromInt32(tableIndex), info);

        return true;
    }
    
    bool CTNDBChat::replaceMessage(toonim::CTNMessage &message)
    {
        if (message.msgId.length() <= 0) {
            return false;
        }
        
        map<string, pair<CTNDBBase::FT, string>> info;
        this->genMessageMap(message, info);
        int tableIndex = this->generateTableIndex(message.sessionId.c_str());
        replaceRecord("BMessage"+CTNDBUtils::stringFromInt32(tableIndex), info);
        
        return true;
    }
    
    bool CTNDBChat::replaceMessages(vector<toonim::CTNMessage> &messages)
    {
        if (messages.size() <= 0) {
            return false;
        }
        
        this->beginTransation();
        for (int32_t i=0; i<messages.size(); i++) {
            CTNMessage message = messages.at(i);
            if (message.msgId.length() <= 0) {
                continue;
            }
            
            map<string, pair<CTNDBBase::FT, string>> info;
            this->genMessageMap(message, info);
            int tableIndex = this->generateTableIndex(message.sessionId.c_str());
            replaceRecord("BMessage"+CTNDBUtils::stringFromInt32(tableIndex), info);
        }
        this->commitTransation();
        
        return true;
    }
    
    void CTNDBChat::genMessageMap(toonim::CTNMessage &message, map<string, pair<CTNDBBase::FT, string>> &info)
    {
        info["msgId"] = make_pair(CTNDBBase::DB_STR, message.msgId);
        info["sessionId"] = make_pair(CTNDBBase::DB_STR, message.sessionId);
        info["type"] = make_pair(CTNDBBase::DB_INT, CTNDBUtils::stringFromInt32(message.type));
        info["seqId"] = make_pair(CTNDBBase::DB_LONG, CTNDBUtils::stringFromInt64(message.seqId));
        info["fromId"] = make_pair(CTNDBBase::DB_STR, message.fromId);
        info["toId"] = make_pair(CTNDBBase::DB_STR, message.toId);
        info["fromClientId"] = make_pair(CTNDBBase::DB_STR, message.fromClientId);
        info["toClientId"] = make_pair(CTNDBBase::DB_STR, message.toClientId);
        info["timestamp"] = make_pair(CTNDBBase::DB_LONG, CTNDBUtils::stringFromInt64(message.timestamp));
        info["pushInfo"] = make_pair(CTNDBBase::DB_STR, message.pushInfo);
        info["sendStatus"] = make_pair(CTNDBBase::DB_INT, CTNDBUtils::stringFromInt32(message.sendStatus));
        info["senderName"] = make_pair(CTNDBBase::DB_STR, message.senderName);
        info["status"] = make_pair(CTNDBBase::DB_INT, CTNDBUtils::stringFromInt64(message.status));
        info["priority"] = make_pair(CTNDBBase::DB_INT, CTNDBUtils::stringFromInt32(message.priority));
        info["catalogId"] = make_pair(CTNDBBase::DB_INT, CTNDBUtils::stringFromInt32(message.catalogId));
        info["content"] = make_pair(CTNDBBase::DB_STR, message.content);
        info["contentType"] = make_pair(CTNDBBase::DB_INT, CTNDBUtils::stringFromInt64(message.contentType));
        info["width"] = make_pair(CTNDBBase::DB_DOUBLE, CTNDBUtils::stringFromDouble(message.width));
        info["height"] = make_pair(CTNDBBase::DB_DOUBLE, CTNDBUtils::stringFromDouble(message.height));
        info["atType"] = make_pair(CTNDBBase::DB_INT, CTNDBUtils::stringFromInt64(message.atType));
        info["atFeeds"] = make_pair(CTNDBBase::DB_STR, message.atFeeds);
        info["fileFormat"] = make_pair(CTNDBBase::DB_STR, message.fileFormat);
        info["noticeStatusType"] = make_pair(CTNDBBase::DB_STR, message.noticeStatusType);
        info["flags"] = make_pair(CTNDBBase::DB_INT, CTNDBUtils::stringFromInt64(message.flags));
        info["faultSeqId"] = make_pair(CTNDBBase::DB_LONG, CTNDBUtils::stringFromInt64(message.faultSeqId));
        info["isMyself"] = make_pair(CTNDBBase::DB_INT, CTNDBUtils::stringFromInt32(message.isMyself));
        info["subCatalogId"] = make_pair(CTNDBBase::DB_INT, CTNDBUtils::stringFromInt32(message.subCatalogId));
        info["addition"] = make_pair(CTNDBBase::DB_STR, message.addition);
        info["bizNo"] = make_pair(CTNDBBase::DB_STR, message.bizNo);
    }
    
    bool CTNDBChat::deleteMessage(const char*  sessionId, const char*  msgId)
    {
        if (msgId == nullptr || strlen(msgId) == 0) {
            return false;
        }
        
        int tableIndex = this->generateTableIndex(sessionId);
        CTNMessage lastMessage = this->getLastMessage(sessionId);
        
        std::ostringstream s;
        s << "update Bmessage" << tableIndex << " set status=" << CTNIMMessageDeleted << " where msgId='" << msgId << "'";
        std::string sql = s.str();
        this->execSql(sql.c_str());
        
        CTNSession session = this->getSession(sessionId);
        if (lastMessage.msgId == msgId && session.isValid()) {
            CTNMessage message = this->getLastMessage(sessionId);
            vector<toonim::CTNSession> vctSession;
            if (message.isEmpty()) {
                session.sessionId = sessionId;
                session.lastMsgSendStatus = CTNMessageSuccess;
                session.lastMsg = "";
            }else {
                session.lastMsgSendStatus = message.sendStatus;
                session.lastMsgId = message.msgId;
                session.lastMsg = message.getAbstractText();
                session.lastTime = message.timestamp;
            }
            vctSession.push_back(session);
            this->updateSession(vctSession);
        }
        
        //删除消息的同时需要删除重要消息表的对应消息
        if (session.type == CTNIMMessageTypeGroupChat) {
            this->deleteImportantMessage(CTNIMMessageTypeAt, msgId);
            this->deleteImportantMessage(CTNIMMessageTypeFollow, msgId);
        }
        
        return true;
    }
    
    bool CTNDBChat::deleteAllMessage(const char*  sessionId)
    {
        if (sessionId == nullptr || strlen(sessionId) == 0) {
            return false;
        }
        
        int tableIndex = this->generateTableIndex(sessionId);
        
        std::ostringstream s;
        s << "update Bmessage" << tableIndex << " set faultSeqId=-1,status=" << CTNIMMessageDeleted << " where sessionId='" << sessionId << "'";
        std::string sql = s.str();
        this->execSql(sql.c_str());
        
        CTNSession session = this->getSession(sessionId);
        if (session.isValid()){
            session.lastMsgSendStatus = CTNMessageSuccess;
            //lastMsgId不需要进行置空处理，会以lastMsgId进行判断该session是否有效
//            session.lastMsgId = "";
            session.lastMsg = "";
            session.atMeMsgId = "";
            session.unreadCount = 0;
            
            vector<toonim::CTNSession> vctSession;
            vctSession.push_back(session);
            this->updateSession(vctSession);
        }
        
        //删除所有message的同时需要删除所有的重要消息
        this->deleteFollowMessageBySessionId(sessionId);
        this->deleteAtMessageBySessionId(sessionId);
        
        return true;
    }
    
    bool CTNDBChat::physicalDeletionMessage(const char*  sessionId, const char*  msgId)
    {
        if (sessionId == nullptr || msgId == nullptr || strlen(sessionId) == 0 || strlen(msgId) == 0) {
            return false;
        }
        
        int tableIndex = this->generateTableIndex(sessionId);
        std::ostringstream s;
        s << "delete from Bmessage" << tableIndex << " where msgId='" << msgId << "'";
        std::string sql = s.str();
        this->execSql(sql.c_str());
        
        return true;
    }
    
    bool CTNDBChat::updateMessage(CTNMessage& message)
    {
        if (message.msgId.length() <= 0) {
            return false;
        }
        
        map<string, pair<CTNDBBase::FT, string>> info;
        this->genMessageMap(message, info);
        int tableIndex = this->generateTableIndex(message.sessionId.c_str());
        replaceRecord("BMessage"+CTNDBUtils::stringFromInt32(tableIndex), info);
        
        return true;
    }
    
    bool CTNDBChat::updateContent(const char* msgId, const char* sessionId, const char* content)
    {
        if (msgId == nullptr || msgId[0] == '\0' || sessionId == nullptr || sessionId[0] == '\0' || content == nullptr || content[0] == '\0') {
            return false;
        }
        
        int tableIndex = this->generateTableIndex(sessionId);
        std::ostringstream s;
        s << "update BMessage" << tableIndex << " set content='" << content << "' where msgId='" << msgId << "'";
        
        std::string sql = s.str();
        if (this->execSql(sql.c_str())) {
            return true;
        } else {
            return false;
        }
    }
    
    bool CTNDBChat::updateSendStatus(const char* msgId, const char* sessionId, int32_t sendStatus)
    {
        if (msgId == nullptr || msgId[0] == '\0' || sessionId == nullptr || sessionId[0] == '\0') {
            return false;
        }
        
        int tableIndex = this->generateTableIndex(sessionId);
        std::ostringstream s;
        s << "update BMessage" << tableIndex << " set sendStatus='" << sendStatus << "' where msgId='" << msgId << "'";
        
        std::string sql = s.str();
        if (this->execSql(sql.c_str())) {
            return true;
        } else {
            return false;
        }
    }
    
    bool CTNDBChat::updateAddition(const char* msgId, const char* sessionId, const char* addition)
    {
        if (msgId == nullptr || msgId[0] == '\0' || sessionId == nullptr || sessionId[0] == '\0' || addition == nullptr || addition[0] == '\0') {
            return false;
        }
        
        int tableIndex = this->generateTableIndex(sessionId);
        std::ostringstream s;
        s << "update BMessage" << tableIndex << " set addition='" << addition << "' where msgId='" << msgId << "'";
        
        std::string sql = s.str();
        if (this->execSql(sql.c_str())) {
            return true;
        } else {
            return false;
        }
    }
    
    CTNMessage CTNDBChat::getMessage(const char* sessionId, const char* msgId)
    {
        if (msgId == nullptr || strlen(msgId) == 0) {
            return CTNMessage();
        }
        
        int tableIndex = this->generateTableIndex(sessionId);
        
        std::ostringstream s;
        s << "select * from Bmessage" << tableIndex << " where msgId='" << msgId << "'";
        std::string sql = s.str();
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
        
        toonim::CTNMessage message = CTNMessage();
        if (records == NULL) {
            return message;
        }
        
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            message = this->generateMessage(records);
        }
        
        return message;
    }
    
    CTNMessage CTNDBChat::getMaxNoticeMessage(const char* sessionId, const char* bizNo) {
        if (sessionId == nullptr || bizNo == nullptr || strlen(bizNo) == 0 || strlen(sessionId) == 0) {
            return CTNMessage();
        }
        
        int tableIndex = this->generateTableIndex(sessionId);
        
        std::ostringstream s;
        s << "select * from Bmessage" << tableIndex << " where bizNo='" << bizNo << "' and status=0 order by seqId desc limit 1";
        std::string sql = s.str();
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
        
        toonim::CTNMessage message = CTNMessage();
        if (records == NULL) {
            return message;
        }
        
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            message = this->generateMessage(records);
        }
        
        return message;
    }
    
    CTNMessage CTNDBChat::getFaultMessage(const char* sessionId, int32_t priority) {
        if (strlen(sessionId) == 0) {
            return CTNMessage();
        }
        
        int tableIndex = this->generateTableIndex(sessionId);
        
        std::ostringstream s;
        if (priority == 0){
            s << "select * from Bmessage" << tableIndex << " where sessionId='" << sessionId << "' and priority=0 and faultSeqId>=0 order by seqId desc limit 1";
        }
        else if (priority == 1){
            s << "select * from Bmessage" << tableIndex << " where sessionId='" << sessionId << "' and priority=1 and faultSeqId>=0 order by seqId desc limit 1";
        }
        else {
            s << "select * from Bmessage" << tableIndex << " where sessionId='" << sessionId << "' and faultSeqId>=0 order by seqId desc limit 1";
        }
        
        std::string sql = s.str();
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
        
        toonim::CTNMessage message = CTNMessage();
        if (records == NULL) {
            return message;
        }
        
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            message = this->generateMessage(records);
        }
        
        return message;
    }
    
    CTNMessage CTNDBChat::getLastMessage(const char*  sessionId)
    {
        if (sessionId == nullptr || strlen(sessionId) == 0) {
            return CTNMessage();
        }
        
//        vector<toonim::CTNMessage> msgV = this->getMessages(sessionId, 0, 1);
//        if (msgV.size() > 0) {
//            return msgV.at(msgV.size()-1);
//        } else {
//            return CTNMessage();
//        }
        
        int tableIndex = this->generateTableIndex(sessionId);
        std::ostringstream s;
        s << "select * from BMessage" << tableIndex << " where sessionId='" << sessionId << "' and status=0 order by seqId desc,timestamp desc limit 1";
        std::string sql = s.str();
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
        
        if (records == NULL) {
            return CTNMessage();
        }
        
        if (records->step() == CSqliteDBStatement::STEP_ROW) {
            CTNMessage message = this->generateMessage(records);
            return message;
        }
        return CTNMessage();
    }
    
    int64_t CTNDBChat::getMaxSeqAllMessage(const char*  sessionId, int32_t type = 2)//0 普通优先级 1 高优先级 2 混合优先级
    {
        if (sessionId == nullptr || strlen(sessionId) == 0) {
            return -1;
        }
        
        CTNMessage message;
        int tableIndex = this->generateTableIndex(sessionId);
        
        std::ostringstream s;
        
        switch (type) {
            case 0:
                s << "select max(seqId) from BMessage" << tableIndex << " where sessionId='" << sessionId << "' and priority=0 and sendStatus=2";
                break;
            case 1:
                s << "select max(seqId) from BMessage" << tableIndex << " where sessionId='" << sessionId << "' and priority=1 and sendStatus=2";
                break;
            default:
                s << "select max(seqId) from BMessage" << tableIndex << " where sessionId='" << sessionId << "' and sendStatus=2";
                break;
        }
        
        std::string sql = s.str();
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
        
        if (records == NULL) {
            return -1;
        }
        
        if (records->step() == CSqliteDBStatement::STEP_ROW) {//安卓的limit不能用，只能这里限制只取一条了🤣 wxy
            int64_t lstSeq = records->getLong(0);
            //解决新建群聊，其他群成员收离线后，群聊未显示问题
            //会引起其他bug：当新开启的单聊，从未聊过天，一方在断网情况下发送 >=15 条消息，会导致此会话消息显示不全。
            return lstSeq;
        } else {
            return 0;
//            return 1;//本地没有记录默认为1，有效的seqID是从1开始的
        }
    }

    vector<CTNMessage> CTNDBChat::getMessages(const char*  sessionId, int64_t seqId, int32_t count)
    {
        this->resetMessageSendingStatusWithSessionId(sessionId);
        
        vector<CTNMessage> vMessage;
        int tableIndex = this->generateTableIndex(sessionId);
        
        std::ostringstream s;
        if (seqId <= 0) {
            s << "select * from BMessage" << tableIndex << " where sessionId='" << sessionId << "' and status=0 order by seqId desc,timestamp desc limit " << count;
        } else {
            s << "select * from BMessage" << tableIndex << " where sessionId='" << sessionId << "' and seqId<" << seqId << " and status=0 order by seqId desc,timestamp desc limit " << count;
        }
        std::string sql = s.str();
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
        
        if (records == NULL) {
            return vMessage;
        }
        
        string strMsgIds;
        int pos = 0;
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            CTNMessage message = this->generateMessage(records);
            vMessage.insert(vMessage.begin(), message);
            if (pos == 0) {
                strMsgIds += "('";
                strMsgIds += message.msgId;
            } else {
                strMsgIds += "','";
                strMsgIds += message.msgId;
            }
            pos++;
        }
        strMsgIds += "')";
        
        if (vMessage.size() > 0) {//再次查询是由于存在相同seqId的情况，若查询的count条消息正好落在几个相同seqId范围内，由于count限制未将这些消息全部查出给上层，下次上层会从新的seqId查询消息，遗漏上次的seqId剩下的消息。因此再重新从数据库查询最后seqId的所有消息，同时还需去重。
            int64_t lastSeqId = vMessage.begin()->seqId;
            s.str("");
            s << "select * from BMessage" << tableIndex << " where sessionId='" << sessionId << "' and seqId=" << lastSeqId << " and status=0 and msgId not in "<< strMsgIds << " order by timestamp desc";
            
            sql = s.str();
            CQIPtr<CSqliteDBStatement, QI_NEW> sameSeqrecords = this->execQuerySql(sql.c_str());
            
            if (sameSeqrecords == NULL) {
                return vMessage;
            }
            
            while (sameSeqrecords->step() == CSqliteDBStatement::STEP_ROW) {
                CTNMessage message = this->generateMessage(sameSeqrecords);
                vMessage.insert(vMessage.begin(), message);
            }
        }
        
        return vMessage;
    }
    
    vector<CTNMessage> CTNDBChat::getMessagesAsc(const char*  sessionId, int64_t seqId, int32_t count)
    {
        this->resetMessageSendingStatusWithSessionId(sessionId);
        
        vector<CTNMessage> vMessage;
        int tableIndex = this->generateTableIndex(sessionId);
        
        std::ostringstream s;
        if (seqId <= 0) {
            s << "select * from BMessage" << tableIndex << " where sessionId='" << sessionId << "' and status=0 order by seqId asc,timestamp asc limit " << count;
        } else {
            s << "select * from BMessage" << tableIndex << " where sessionId='" << sessionId << "' and seqId>" << seqId << " and status=0 order by seqId asc,timestamp asc limit " << count;
        }
        std::string sql = s.str();
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
        
        if (records == NULL) {
            return vMessage;
        }
        
        string strMsgIds;
        int pos = 0;
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            CTNMessage message = this->generateMessage(records);
            vMessage.push_back(message);
            if (pos == 0) {
                strMsgIds += "('";
                strMsgIds += message.msgId;
            } else {
                strMsgIds += "','";
                strMsgIds += message.msgId;
            }
            pos++;
        }
        strMsgIds += "')";
        
        if (vMessage.size() > 0) {
            int64_t lastSeqId = (vMessage.end()-1)->seqId;
            s.str("");
            s << "select * from BMessage" << tableIndex << " where sessionId='" << sessionId << "' and seqId=" << lastSeqId << " and status=0 and msgId not in "<< strMsgIds << " order by timestamp asc";
            
            sql = s.str();
            CQIPtr<CSqliteDBStatement, QI_NEW> sameSeqrecords = this->execQuerySql(sql.c_str());
            
            if (sameSeqrecords == NULL) {
                return vMessage;
            }
            
            while (sameSeqrecords->step() == CSqliteDBStatement::STEP_ROW) {
                CTNMessage message = this->generateMessage(sameSeqrecords);
//                vMessage.insert(vMessage.begin(), message);
                vMessage.push_back(message);
            }
        }
        
        return vMessage;
    }
    
    vector<CTNMessage> CTNDBChat::getFaultMessages(const char* sessionId, int64_t seqId, int32_t count) {
        vector<CTNMessage> vMessage;
        int tableIndex = this->generateTableIndex(sessionId);
//        select * from (select * from BMessage3 where sessionId='c_1470033292544198_c_1347929798921753' and status=0  and priority = 0 order by seqId desc,timestamp desc limit 1000) where faultSeqId >= 0 order by seqId desc,timestamp desc limit 1
        std::ostringstream s;
        if (seqId <= 0) {
            s << "select * from (select * from BMessage" << tableIndex << " where sessionId='" << sessionId << "' and priority = 1  order by seqId desc,timestamp desc limit 1000) where faultSeqId >= 0 order by seqId desc,timestamp desc limit 1";// << count
        } else {
            s << "select * from (select * from BMessage" << tableIndex << " where sessionId='" << sessionId << "' and priority = 1  order by seqId desc,timestamp desc limit 1000) where faultSeqId >= 0 order by seqId desc,timestamp desc limit " << count;
        }
        std::string sql = s.str();
        TNMPLOG(sql);
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
        
        if (records == NULL) {
            return vMessage;
        }
        
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            CTNMessage message = this->generateMessage(records);
//            vMessage.insert(vMessage.begin(), message);
            vMessage.push_back(message);
        }
        s.str("");
        if (seqId <= 0) {
            s << "select * from (select * from BMessage" << tableIndex << " where sessionId='" << sessionId << "' and status=0 and priority = 0  order by seqId desc,timestamp desc limit 1000) where faultSeqId >= 0 order by seqId desc,timestamp desc limit 1";// << count
        } else {
            s << "select * from (select * from BMessage" << tableIndex << " where sessionId='" << sessionId << "' and status=0 and priority = 0  order by seqId desc,timestamp desc limit 1000) where faultSeqId >= 0 order by seqId desc,timestamp desc limit " << count;
        }
        sql = s.str();
        TNMPLOG(sql);
        CQIPtr<CSqliteDBStatement, QI_NEW> recordsFault = this->execQuerySql(sql.c_str());
        
        if (recordsFault == NULL) {
            return vMessage;
        }
        
        while (recordsFault->step() == CSqliteDBStatement::STEP_ROW) {
            CTNMessage message = this->generateMessage(recordsFault);
//            vMessage.insert(vMessage.begin(), message);
            vMessage.push_back(message);
        }
        
        return vMessage;
    }
    
    vector<CTNMessage> CTNDBChat::getMessagesWithContentType(const char*  sessionId, CTNMessageContentType contentType)
    {
        vector<CTNMessage> vMessage;
        int tableIndex = this->generateTableIndex(sessionId);
        
        std::ostringstream s;
        s << "select * from BMessage" << tableIndex << " where sessionId='" << sessionId << "'and status=0 and contentType=" << contentType << " order by seqId asc,timestamp asc";
        std::string sql = s.str();
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
        
        if (records == NULL) {
            return vMessage;
        }
        
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            CTNMessage message = this->generateMessage(records);
            vMessage.push_back(message);
        }
        
        return vMessage;
    }

    vector<CTNMessage> CTNDBChat::getFileMessagesWithSessionId(const char*  sessionId, CTNMessageContentType contentType,vector<std::string> formats)
    {
        vector<CTNMessage> vMessage;
        int tableIndex = this->generateTableIndex(sessionId);

        std::string fileFormats = "";
        if (formats.size() > 0) {
            for (int i=0; i<formats.size(); i++) {
                std::string noticeType = formats.at(i);
                if (formats.size() - 1 == i) {
                    fileFormats = fileFormats + "'" + noticeType +"'";
                }else{
                    fileFormats = fileFormats + "'" + noticeType +"',";
                }
            }
            fileFormats = "in (" + fileFormats +")";
        }else{
            fileFormats = "not in ('application/pdf', 'application/msword', 'application/vnd.openxmlformats-officedocument.wordprocessingml.document', 'application/vnd.ms-excel', 'application/vnd.openxmlformats-officedocument.spreadsheetml.sheet', 'application/vnd.ms-powerpoint', 'application/vnd.openxmlformats-officedocument.presentationml.presentation', 'application/x-iwork-pages-sffpages', 'application/x-iwork-numbers-sffnumbers', 'application/x-iwork-keynote-sffkey', 'text/plain', 'video/quicktime', 'video/mp4', 'video/3gpp')";
        }

        if (sessionId != nullptr && strlen(sessionId) != 0) {
            std::ostringstream s;
            s << "select * from BMessage" << tableIndex << " where sessionId='" << sessionId << "' and contentType=" << contentType << " and fileFormat " << fileFormats <<" and status ='0' order timestamp desc";

            std::string sql = s.str();
            CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());

            if (records == NULL) {
                return vMessage;
            }

            while (records->step() == CSqliteDBStatement::STEP_ROW) {
                CTNMessage message = this->generateMessage(records);
                vMessage.push_back(message);
            }
            
            
        }else{
            std::ostringstream s;
            s << "SELECT * FROM (";
            for (int i = 0; i < TABLE_COUNT_MESSAGE; i++) {
                if (i > 0) {
                    s << " UNION ALL ";
                }
                s << "select * from BMessage" << i << " where contentType=" << contentType << " and status ='0'";
            }
            s << ") where fileFormat " << fileFormats <<" ORDER BY timestamp DESC";
            
            std::string sql = s.str();
            TNMPLOG(sql);
            CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
            
            if (records == NULL) {
                return vMessage;
            }
            
            while (records->step() == CSqliteDBStatement::STEP_ROW) {
                CTNMessage message = this->generateMessage(records);
                vMessage.push_back(message);
            }
        }

        return vMessage;
    }

    vector<CTNMessage> CTNDBChat::getMessages(const char* sessionId, CTNMessageContentType contentType, CTNOwner isMySelf)
    {
        vector<CTNMessage> vctMessage;
        
        if (sessionId == nullptr || sessionId[0] == '\0') {
            //筛选10张表的数据
            for (int32_t i=0; i<TABLE_COUNT_MESSAGE; i++) {
                std::ostringstream s;
                s << "select * from BMessage" << i << " where contentType=" << contentType << " and isMyself="  << isMySelf;
                
                std::string sql = s.str();
                CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
                
                if (records == NULL) {
                    continue;
                }
                
                while (records->step() == CSqliteDBStatement::STEP_ROW) {
                    CTNMessage message = this->generateMessage(records);
                    vctMessage.push_back(message);
                }
            }
        } else {
            //筛选一个session的数据
            int tableIndex = this->generateTableIndex(sessionId);
            
            std::ostringstream s;
            s << "select * from BMessage" << tableIndex << " where sessionId='" << sessionId <<"' and contentType=" << contentType << " and isMyself="  << isMySelf;
            
            std::string sql = s.str();
            CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
            
            if (records == NULL) {
                return vctMessage;
            }
            
            while (records->step() == CSqliteDBStatement::STEP_ROW) {
                CTNMessage message = this->generateMessage(records);
                vctMessage.push_back(message);
            }
        }
        
        return vctMessage;
    }

    vector<CTNMessage> CTNDBChat::getMessagesWithSeqId(const char*  sessionId, int64_t maxSeqId, int64_t minSeqId)
    {
        vector<CTNMessage> vMessage;
        int tableIndex = this->generateTableIndex(sessionId);
        
        std::ostringstream s;
        s << "select * from BMessage" << tableIndex << " where sessionId='" << sessionId << "' and seqId<=" << maxSeqId << " and seqId>=" << minSeqId << " and status=" << CTNIMMessageNormal << " order by seqId desc,timestamp desc";
        std::string sql = s.str();
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
        
        if (records == NULL) {
            return vMessage;
        }
        
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            CTNMessage message = this->generateMessage(records);
            vMessage.insert(vMessage.begin(), message);
        }
        
        return vMessage;
    }
    
    vector<std::string> CTNDBChat::getNoticeStatusType(const char*  sessionId)
    {
        vector<std::string> vNotice;
        int tableIndex = this->generateTableIndex(sessionId);
        
        std::ostringstream s;
        s << "select distinct noticeStatusType from BMessage" << tableIndex << " where sessionId='" << sessionId << "' and status=" << CTNIMMessageNormal;
        std::string sql = s.str();
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
        
        if (records == NULL) {
            return vNotice;
        }
        
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            std::string noticeStatusType = records->getString(0);
            if (noticeStatusType.length() == 0) {
                continue;
            }
            vNotice.push_back(noticeStatusType);
        }
        
        return vNotice;
    }
    
    vector<toonim::CTNMessage> CTNDBChat::getMessageWithNoticeStatusType(const char*  sessionId, int64_t seqId, int32_t count, const char*  noticeStatusType)
    {
        vector<CTNMessage> vMessage;
        int tableIndex = this->generateTableIndex(sessionId);
        
        std::ostringstream s;
        if (seqId <= 0) {
            s << "select * from BMessage" << tableIndex << " where sessionId='" << sessionId << "' and noticeStatusType='" << noticeStatusType << "' and status=0 order by seqId desc,timestamp desc limit " << count;
        } else {
            s << "select * from BMessage" << tableIndex << " where sessionId='" << sessionId << "' and noticeStatusType='" << noticeStatusType << "' and seqId<" << seqId << " and status=0 order by seqId desc,timestamp desc limit " << count;
        }
        std::string sql = s.str();
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
        
        if (records == NULL) {
            return vMessage;
        }
        
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            CTNMessage message = this->generateMessage(records);
            vMessage.insert(vMessage.begin(), message);
        }
        
        return vMessage;
    }
    
    void CTNDBChat::searchMessage(const char* keyword, const char* sessionId, vector< std::vector<std::string> > &messages)
    {
        if (keyword == nullptr || strlen(keyword) == 0) {
            return;
        }
        TNMPLOG("searchMessage====keyword:" << (keyword?keyword:"") << " sessionId:" << (sessionId?sessionId:""));
        std::ostringstream s;
        if (sessionId != nullptr && strlen(sessionId) != 0) {
            int tableIndex = this->generateTableIndex(sessionId);
            s << "SELECT sessionId, msgId, content, timestamp FROM BMessage" << tableIndex << " WHERE sessionId='" << sessionId << "' AND contentType=1 AND status=0 AND type=52 AND contentFunc(content) LIKE '%%" << keyword << "%%' UNION ALL SELECT sessionId, msgId, content, timestamp FROM BMessage" << tableIndex << " WHERE sessionId='" << sessionId << "' AND contentType=1 AND status=0 AND type=53 AND contentFunc(content) LIKE '%%" << keyword << "%%' ORDER BY timestamp DESC";
            
            std::string sql = s.str();
            CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
            
            if (records == NULL) {
                return;
            }
            
            while (records->step() == CSqliteDBStatement::STEP_ROW) {
                std::string sessionId = records -> getString(0);
                std::string msgId = records -> getString(1);
                std::string content = records -> getString(2);
                std::string timestamp = records -> getString(3);
                
                vector<std::string> messageModel;
                messageModel.push_back(sessionId);
                messageModel.push_back(msgId);
                messageModel.push_back(content);
                messageModel.push_back(timestamp);
                
                messages.push_back(messageModel);
            }
        } else {
            
            std::string sql = "SELECT * FROM (";
            for (int i = 0; i < TABLE_COUNT_MESSAGE; i++) {
                if (i > 0) {
                    sql += " UNION ALL ";
                }
                std::ostringstream s;
                s << "SELECT sessionId, COUNT(msgId) AS msgCount, msgId, content, timestamp FROM BMessage" << i << " WHERE contentType=1 AND status=0 AND type=52 AND contentFunc(content) LIKE '%%" << keyword << "%%' GROUP BY sessionId UNION ALL SELECT sessionId, COUNT(msgId) AS msgCount, msgId, content, timestamp FROM BMessage" << i << " WHERE contentType=1 AND status=0 AND type=53 AND contentFunc(content) LIKE '%%" << keyword << "%%' GROUP BY sessionId";
                sql += s.str();
            }
            sql += ") ORDER BY timestamp DESC";
            
            CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
            
            if (records == NULL) {
                return;
            }
            
            while (records->step() == CSqliteDBStatement::STEP_ROW) {
                std::string sessionId = records -> getString(0);
                std::ostringstream s;
                s << records -> getInt(1);
                std::string msgCount = s.str();
                std::string msgId = records -> getString(2);
                std::string content = records -> getString(3);
                std::string timestamp = records -> getString(4);
                
                vector<std::string> messageModel;
                messageModel.push_back(sessionId);
                messageModel.push_back(msgCount);
                messageModel.push_back(msgId);
                messageModel.push_back(content);
                messageModel.push_back(timestamp);
                
                messages.push_back(messageModel);
            }
        }
        
        TNMPLOG("searchMessage====finished, messages.size:" << messages.size());
    }
    
    std::string CTNDBChat::genRevokeMessageContent(toonim::CTNMessage& message, const char*  operateName)
    {
        std::string content = "";
        std::string title = "";
        std::ostringstream s;
        
        if (message.fromClientId == this->_clientId) {
            title = "你撤回了一条消息";
        } else {
            if (operateName != nullptr) {
                s << operateName << "撤回了一条消息";
            } else {
                s << "对方撤回了一条消息";
            }
            title = s.str();
        }
        
#ifdef RAPIDJSONWRAPPER
        
        rapidjson::StringBuffer jsonS;
        rapidjson::Writer<rapidjson::StringBuffer> writer(jsonS);
        writer.StartObject();
        writer.Key("text");
        writer.String(title.c_str());
        writer.EndObject();
#else
        rapidjson::StringBuffer jsonS;
        rapidjson::Writer<rapidjson::StringBuffer> writer(jsonS);
        writer.StartObject();
        writer.Key("text");
        writer.String(title.c_str());
        writer.EndObject();
#endif
        content = jsonS.GetString();
        
        return content;
    }
    
    vector<CTNMessage> CTNDBChat::getAllFaultMessage()
    {
        vector<CTNMessage> messageList;
        
        for (int32_t i=0; i<TABLE_COUNT_MESSAGE; i++) {
            std::ostringstream s;
            
            s << "select * from BMessage" << i << " where faultSeqId>=0 order by timestamp desc";

            std::string sql = s.str();
            CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
            
            if (records == NULL) {
                continue;
            }
            
            while (records->step() == CSqliteDBStatement::STEP_ROW) {
                CTNMessage message = this->generateMessage(records);
                messageList.push_back(message);
            }
        }
        
        return messageList;
    }
    
#pragma mark -----------operateMessage----------
    bool CTNDBChat::addOperateMessage(vector<CTNMessageOperate>& operates)
    {
        if (operates.size() <= 0) {
            return false;
        }
        
        this->beginTransation();
        for (int i=0; i<operates.size(); i++) {
            CTNMessageOperate message = operates.at(i);
            if (message.msgId.length() <= 0) {
                continue;
            }
            map<string, pair<CTNDBBase::FT, string>> info;
            
            info["msgId"] = make_pair(CTNDBBase::DB_STR, message.msgId);
            info["seqId"] = make_pair(CTNDBBase::DB_LONG, CTNDBUtils::stringFromInt64(message.seqId));
            info["type"] = make_pair(CTNDBBase::DB_INT, CTNDBUtils::stringFromInt32(message.type));
            info["mfrom"] = make_pair(CTNDBBase::DB_STR, message.mfrom);
            info["mto"] = make_pair(CTNDBBase::DB_STR, message.mto);
            info["timestamp"] = make_pair(CTNDBBase::DB_LONG, CTNDBUtils::stringFromInt64(message.timestamp));
            info["catalogId"] = make_pair(CTNDBBase::DB_INT, CTNDBUtils::stringFromInt32(message.catalogId));
            info["content"] = make_pair(CTNDBBase::DB_STR, message.content);
            info["opMsgId"] = make_pair(CTNDBBase::DB_STR, message.opMsgId);
            info["opFeedId"] = make_pair(CTNDBBase::DB_STR, message.opFeedId);
            info["opName"] = make_pair(CTNDBBase::DB_STR, message.opName);
            insertRecord("MessageOperate", info);
        }
        this->commitTransation();
        
        return true;
    }
    
    bool CTNDBChat::updateOperateMessage(vector<CTNMessageOperate>& operates)
    {
        if (operates.size() <= 0) {
            return false;
        }
        this->beginTransation();
        for (int i=0; i<operates.size(); i++) {
            CTNMessageOperate message = operates.at(i);
            if (message.msgId.length() <= 0) {
                continue;
            }
            map<string, pair<CTNDBBase::FT, string>> info;
            
            info["msgId"] = make_pair(CTNDBBase::DB_STR, message.msgId);
            info["seqId"] = make_pair(CTNDBBase::DB_LONG, CTNDBUtils::stringFromInt64(message.seqId));
            info["type"] = make_pair(CTNDBBase::DB_INT, CTNDBUtils::stringFromInt32(message.type));
            info["mfrom"] = make_pair(CTNDBBase::DB_STR, message.mfrom);
            info["mto"] = make_pair(CTNDBBase::DB_STR, message.mto);
            info["timestamp"] = make_pair(CTNDBBase::DB_LONG, CTNDBUtils::stringFromInt64(message.timestamp));
            info["catalogId"] = make_pair(CTNDBBase::DB_INT, CTNDBUtils::stringFromInt32(message.catalogId));
            info["content"] = make_pair(CTNDBBase::DB_STR, message.content);
            info["opMsgId"] = make_pair(CTNDBBase::DB_STR, message.opMsgId);
            info["opFeedId"] = make_pair(CTNDBBase::DB_STR, message.opFeedId);
            info["opName"] = make_pair(CTNDBBase::DB_STR, message.opName);
            replaceRecord("MessageOperate", info);
        }
        this->commitTransation();
        
        return true;
    }
    
    bool CTNDBChat::deleteOperateMessage(const char*  msgId)
    {
        if (msgId == nullptr || strlen(msgId) == 0) {
            return false;
        }
        
        std::ostringstream s;
        s << "delete from MessageOperate where msgId='" << msgId << "'";
        std::string sql = s.str();
        this->execSql(sql.c_str());
        
        return true;
    }
    
    vector<CTNMessageOperate> CTNDBChat::getAllOperateMessages()
    {
        std::string sql = "select * from MessageOperate";
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
        vector<CTNMessageOperate> vMessage;
        
        if (records == NULL) {
            return vMessage;
        }
        
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            CTNMessageOperate message = this->generateOperateMessage(records);
            vMessage.push_back(message);
        }
        
        return vMessage;
    }
    
    bool CTNDBChat::translateOperateMessage(CTNMessageOperate operMessage) {
        std::ostringstream s;
        std::string sessionId = generateSessionId(operMessage.type, operMessage.mfrom, operMessage.mto, false);
        int tableIndex = this->generateTableIndex(sessionId.c_str());

        s << "select * from BMessage" << tableIndex << " where msgId ='" << operMessage.opMsgId << "'" ;
        std::string sql = s.str();
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
        
        if (records == NULL) {
            return false;
        }
        
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            CTNMessage message = this->generateMessage(records);
            //操作消息执行操作任务wxy
            message.content = genRevokeMessageContent(message, operMessage.opName.c_str());
            updateMessage(message);
        }
        
        return true;
    }
    
    uint32_t CTNDBChat::userVersion() {
        std::ostringstream s;
        s << "pragma user_version";
        std::string sql = s.str();
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
        
        if (records == NULL) {
            return -1;
        }
        
        uint32_t version = -1;
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            version = records->getInt(0);
        }
        
        return version;
    }
    void CTNDBChat::setUserVersion (uint32_t version ) {
        std::ostringstream s;
        s << "pragma user_version =" << version;
        std::string sql = s.str();
        this->execSql(sql.c_str());
    }
    
    CTNMessageOperate CTNDBChat::getOperateMessage(const char*  msgId)
    {
        std::ostringstream s;
        s << "select * from MessageOperate where msgId='" << msgId << "'";
        std::string sql = s.str();
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
        CTNMessageOperate message = CTNMessageOperate();
        
        if (records == NULL) {
            return message;
        }
        
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            message = this->generateOperateMessage(records);
        }
        
        return message;
    }
    
#pragma mark -------------importantMessage-----------
    void CTNDBChat::setImportantSession(vector<CTNSession> &sessionList)
    {
        unique_lock<std::mutex> uniqueLock(_importantMutex);
        _importantVct = sessionList;
    }
    
    bool compare(const CTNSession &a, const CTNSession &b)
    {
        if (a.lastTime >= b.lastTime) {
            return true;
        }
        
        return false;
    }
    
    void CTNDBChat::insertImportantSession(vector<CTNSession> &sessionList)
    {
        vector<CTNSession> vctImportant;
        unique_lock<std::mutex> uniqueLock(_importantMutex);
        vector<CTNSession>::iterator iter = _importantVct.begin();
        while (iter != _importantVct.end()) {
            if (iter->type == CTNIMMessageTypeAt) {
                if (CTNDBSetting::instance() != nullptr) {
                    if (CTNDBSetting::instance()->isAtSwitchOn()) {
                        //at开关打开
                        CTNMessage lastMessage = this->getLastAtMessage();
                        if (!lastMessage.isEmpty()) {
                            iter->lastTime = lastMessage.timestamp;
                            std::string lastMsg = lastMessage.getAbstractText();
                            if (lastMessage.senderName.length() > 0) {
                                lastMsg = lastMessage.senderName + ":" + lastMsg;
                            }
                            iter->lastMsg = lastMsg;
                            iter->unreadCount = this->getAtMessageCount();
                            vctImportant.push_back(*iter);
                        }
                    }
                }
            } else if (iter->type == CTNIMMessageTypeFollow) {
                //关注的人开关
                if (CTNDBSetting::instance() != nullptr) {
                    if (CTNDBSetting::instance()->getFollowFeedIdsCount() > 0) {
                        CTNMessage lastMessage = this->getLastFollowMessage();
                        if (!lastMessage.isEmpty()) {
                            iter->lastTime = lastMessage.timestamp;
                            std::string lastMsg = lastMessage.getAbstractText();
                            if (lastMessage.senderName.length() > 0) {
                                lastMsg = lastMessage.senderName + ":" + lastMsg;
                            }
                            iter->lastMsg = lastMsg;
                            iter->unreadCount = this->getFollowMessageCount();
                            vctImportant.push_back(*iter);
                        }
                    }
                }
            } else {
                vctImportant.push_back(*iter);
            }
            
            iter++;
        }
        
        //当有多余1个session时需要按照时间排序
        if (vctImportant.size() > 0) {
            sort(vctImportant.begin(), vctImportant.end(), compare);
            sessionList.insert(sessionList.begin(), vctImportant.begin(), vctImportant.end());
        }
    }
    
    void CTNDBChat::getSessionReadedId(std::map<std::string, int64_t>& sessionReadInfo){
        std::ostringstream s;
        s << "select sessionId,readSeqId from Session";
        std::string sql = s.str();
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
        
        if (records == NULL) {
            return ;
        }
        
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            sessionReadInfo[records->getString(0)] = records->getInt(1);
        }
    }
    
    void CTNDBChat::upgradeTableWithOldVersion(){
        std::unique_lock<std::mutex> unilock(m_mutex);
        int64_t oldVersion = 0;
        int64_t version = CLBDB_VER;
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql("pragma user_version");
        if (nullptr == records) {
            return;
        }
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            oldVersion = records->getLong(0);
        }
        
        if (oldVersion < version) {
            switch (oldVersion) {
                case 0: {
                    if (!_sqliteDb->existTableOrColom("BMessage0", "bizNo")) {
                        for (int32_t i=0; i<toonim::TABLE_COUNT_MESSAGE; i++) {
                            char sql[1024] = {0};
                            
                            sprintf(sql, "alter table BMessage%d add bizNo text", i);
                            this->execSql(sql);
                        }
                    }
					break;
                }
                    
                case 1:{
                    //删除免打扰和黑名单的版本号
                    if (_sqliteDb->existTableOrColom("SessionSettings", nullptr)) {
                        ostringstream s;
                        s << "delete from SessionSettings where sessionId='" << toonim::SESSION_TYPE_BLACKLIST << "' and type=" << toonim::SESSION_TYPE_BLACKLIST;
                        this->execSql(s.str().c_str());
                        
                        //删除setting表里的免打扰数据，免打扰数据不存储在setting表里
                        this->execSql("delete from SessionSettings where type='SESSION_TYPE_DISTURB'");
                    }
					break;
                }
                    
                default:
                    break;
            }
            std::ostringstream s;
            s << "pragma user_version=" << version << "";
            std::string sql = s.str();
            this->execSql(sql.c_str());
        }
    }
    
    bool CTNDBChat::deleteImportantSession(CTNIMMessageType type)
    {
        if (type == CTNIMMessageTypeAt) {
            this->deleteAllAtMessage();
        }
        
        if (type == CTNIMMessageTypeFollow) {
            this->deleteAllFollowMessage();
        }
        
        return true;
    }
    
    void CTNDBChat::addImportantMessage(CTNIMMessageType type, CTNMessage &message)
    {
        if (type == CTNIMMessageTypeAt) {
            this->addAtMessage(message);
        }
        
        if (type == CTNIMMessageTypeFollow) {
            this->addFollowMessage(message);
        }
    }
    
    vector<CTNMessage> CTNDBChat::getImportantMessageList(CTNIMMessageType type, const char* feedId, int64_t timestamp, const char *msgId, int32_t count)
    {
        if (type == CTNIMMessageTypeAt) {
            return this->getAtMessageList(feedId, timestamp, msgId, count);
        } else if (type == CTNIMMessageTypeFollow) {
            return this->getFollowMessageList(feedId, timestamp, msgId, count);
        }
        
        return vector<CTNMessage>();
    }
    
    void CTNDBChat::deleteImportantSessionBySessionId(const char* sessionId)
    {
        this->deleteAtMessageBySessionId(sessionId);
        this->deleteFollowMessageBySessionId(sessionId);
    }
    
    bool CTNDBChat::deleteImportantMessage(CTNIMMessageType type, const char* msgId)
    {
        bool result = true;
        if (type == CTNIMMessageTypeAt) {
            result = this->deleteAtMessage(msgId);
        }
        
        if (type == CTNIMMessageTypeFollow) {
            result = this->deleteFollowMessage(msgId);
        }
        
        if (!result) {
            return result;
        }
        
        std::unique_lock<std::mutex> uniqueLock(_importantMutex);
        vector<CTNSession>::iterator iter = _importantVct.begin();
        while (iter != _importantVct.end()) {
            if (iter->type == type) {
                CTNMessage message;
                if (type == CTNIMMessageTypeAt) {
                    message = this->getLastAtMessage();
                } else if (type == CTNIMMessageTypeFollow) {
                    message = this->getLastFollowMessage();
                }
                
                if (!message.isEmpty()) {
                    iter->lastTime = message.timestamp;
                    iter->lastMsg = message.getAbstractText();
                }
                
                break;
            }
            
            iter++;
        }
        
        return true;
    }
    
    bool CTNDBChat::deleteImportantMessageBySessionId(CTNIMMessageType type, const char* sessionId)
    {
        if (type == CTNIMMessageTypeAt) {
            this->deleteAtMessageBySessionId(sessionId);
        } else if (type == CTNIMMessageTypeFollow) {
            this->deleteFollowMessageBySessionId(sessionId);
        }
        
        return true;
    }
    
    bool CTNDBChat::deleteAllImportantMessage(CTNIMMessageType type)
    {
        if (type == CTNIMMessageTypeAt) {
            this->deleteAllAtMessage();
        }
        
        if (type == CTNIMMessageTypeFollow) {
            this->deleteAllFollowMessage();
        }
        
        return true;
    }
    
    int32_t CTNDBChat::getImportantMessageCount(CTNIMMessageType type)
    {
        int32_t count = 0;
        
        if (type == CTNIMMessageTypeAt) {
            count = this->getAtMessageCount();
        }
        
        if (type == CTNIMMessageTypeFollow) {
            count = this->getFollowMessageCount();
        }
        
        return 0;
    }
    
    vector<CTNMessage> CTNDBChat::getAtMessageList(const char* feedId, int64_t timestamp, const char *msgId, int32_t count)
    {
        vector<CTNMessage> vctMessage;
        std::ostringstream s;
        
        if (feedId == nullptr || strlen(feedId) == 0) {
            //获取所有at message
            if (timestamp <= 0) {
                s << "select * from AtMessage order by timestamp desc,rowid desc limit " << count;
            } else {
                s << "select * from AtMessage where msgId !='" << msgId << "' and timestamp <= " << timestamp << " order by timestamp desc,rowid desc limit " << count;
            }
        } else {
            //根据feedId筛选message
            if (timestamp <= 0) {
                s << "select * from AtMessage where fromId='" << feedId << "' order by timestamp desc,rowid desc limit " << count;
            } else {
                s << "select * from AtMessage where fromId='" << feedId << "' and msgId !='" << msgId << "' and timestamp <= " << timestamp << " order by timestamp desc,rowid desc limit " << count;
            }
        }
        std::string sql = s.str();
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
        
        if (records == nullptr) {
            return vctMessage;
        }
        
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            CTNMessage message = this->generateMessage(records);
            if (!message.isEmpty()) {
                vctMessage.push_back(message);
            }
        }
        
        return vctMessage;
    }
    
    bool CTNDBChat::addAtMessage(CTNMessage &message)
    {
        if (message.isEmpty()) {
            return false;
        }
        
        map<string, pair<CTNDBBase::FT, string>> info;
        this->genMessageMap(message, info);
        insertRecord("AtMessage", info);
        
        return true;
    }
    
    bool CTNDBChat::deleteAtMessage(const char* msgId)
    {
        if (msgId == nullptr || strlen(msgId) == 0) {
            return false;
        }
        
        std::ostringstream s;
        s << "delete from AtMessage where msgId = '" << msgId << "'";
        std::string sql = s.str();
        return this->execSql(sql.c_str());
    }
    
    CTNMessage CTNDBChat::getLastAtMessage()
    {
        CTNMessage message;
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql("select * from AtMessage where status=0 order by timestamp desc limit 1");
        
        if (records == nullptr) {
            return message;
        }
        
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            message = this->generateMessage(records);
        }
        
        return message;
    }
    
    bool CTNDBChat::deleteAllAtMessage()
    {
        this->execSql("delete from AtMessage");
        
        return true;
    }
    
    bool CTNDBChat::deleteAtMessageBySessionId(const char* sessionId)
    {
        ostringstream s;
        s << "delete from AtMessage where sessionId='" << sessionId << "'";
        
        return this->execSql(s.str().c_str());
    }
    
    int32_t CTNDBChat::getAtMessageCount()
    {
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql("select count(msgId) from AtMessage");
        if (records == NULL) {
            return 0;
        }
        
        int count = 0;
        if (records->step() == CSqliteDBStatement::STEP_ROW) {
            count = records->getInt(0);
        }
        
        return count;
    }
    
#pragma mark ----------followMessage--------
    vector<CTNMessage> CTNDBChat::getFollowMessageList(const char* feedId, int64_t timestamp, const char *msgId, int32_t count)
    {
        vector<CTNMessage> vctMessage;
        std::ostringstream s;
        
        if (feedId == nullptr || strlen(feedId) == 0) {
            //获取所有at message
            if (timestamp <= 0) {
                s << "select * from FollowMessage order by timestamp desc,rowid desc limit " << count;
            } else {
                s << "select * from FollowMessage where msgId !='" << msgId << "' and timestamp <= " << timestamp << " order by timestamp desc,rowid desc limit " << count;
            }
        } else {
            //根据feedId筛选message
            if (timestamp <= 0) {
                s << "select * from FollowMessage where fromId='" << feedId << "' order by timestamp desc,rowid desc limit " << count;
            } else {
                s << "select * from FollowMessage where fromId='" << feedId << "' and msgId !='" << msgId << "' and timestamp <= " << timestamp << " order by timestamp desc,rowid desc limit " << count;
            }
        }
        std::string sql = s.str();
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(sql.c_str());
        
        if (records == nullptr) {
            return vctMessage;
        }
        
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            CTNMessage message = this->generateMessage(records);
            if (!message.isEmpty()) {
                vctMessage.push_back(message);
            }
        }
        
        return vctMessage;
    }
    
    bool CTNDBChat::addFollowMessage(CTNMessage &message)
    {
        if (message.isEmpty()) {
            return false;
        }
        
        map<string, pair<CTNDBBase::FT, string>> info;
        this->genMessageMap(message, info);
        insertRecord("FollowMessage", info);
        
        return true;
    }
    
    bool CTNDBChat::deleteFollowMessage(const char* msgId)
    {
        if (msgId == nullptr || strlen(msgId) == 0) {
            return false;
        }
        
        std::ostringstream s;
        s << "delete from FollowMessage where msgId = '" << msgId << "'";
        std::string sql = s.str();
        return this->execSql(sql.c_str());
    }
    
    bool CTNDBChat::deleteFollowMessageBySessionId(const char* sessionId)
    {
        ostringstream s;
        s << "delete from FollowMessage where sessionId='" << sessionId << "'";
        
        return this->execSql(s.str().c_str());
    }
    
    bool CTNDBChat::deleteAllFollowMessage()
    {
        this->execSql("delete from FollowMessage");
        
        return true;
    }
    
    int32_t CTNDBChat::getFollowMessageCount()
    {
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql("select count(msgId) from FollowMessage");
        if (records == NULL) {
            return 0;
        }
        
        int count = 0;
        if (records->step() == CSqliteDBStatement::STEP_ROW) {
            count = records->getInt(0);
        }
        
        return count;
    }
    
    CTNMessage CTNDBChat::getLastFollowMessage()
    {
        CTNMessage message;
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql("select * from FollowMessage where status=0 order by timestamp desc limit 1");
        
        if (records == nullptr) {
            return message;
        }
        
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            message = this->generateMessage(records);
        }
        
        return message;
    }
    
    bool CTNDBChat::deleteFollowFeedId(const char* feedId)
    {
        ostringstream s;
        s << "delete from FollowMessage where fromId='" << feedId << "'";
        return this->execSql(s.str().c_str());
    }
    
#pragma mark ----------resultData---------
    CTNSession CTNDBChat::generateSession(CSqliteDBStatement *stmt)
    {
        CTNSession session = CTNSession();
        session.sessionId = stmt->getString(0);
        session.topic = stmt->getString(1);
        session.myFeedId = stmt->getString(2);
        session.type = stmt->getInt(3);
        session.title = stmt->getString(4);
        session.avatarId = stmt->getString(5);
        session.draft = stmt->getString(6);
        session.lastTime = (int64_t)stmt->getLong(7);
        session.lastMsg = stmt->getString(8);
        session.lastMsgId = stmt->getString(9);
        session.lastMsgSendStatus = stmt->getInt(10);
        session.readSeqId = (int64_t)stmt->getLong(11);
        session.sortTime = (int64_t)stmt->getLong(12);
        session.atMeMsgId = stmt->getString(13);
        session.unreadCount = stmt->getInt(14);
        session.topStatus = stmt->getInt(15);
        if (toonim::getSettingsDB() != nullptr) {
            session.disturbStatus = toonim::getSettingsDB()->getSessionSettingDisturb(session.sessionId.c_str());
        } else {
            TNMPLOG("getSettingsDB init failure, get disturbStatus failure");
        }
        
                
        return session;
    }
    
    toonim::CTNMessage CTNDBChat::generateMessage(CSqliteDBStatement *stmt)
    {
        CTNMessage message;
        message.msgId = stmt->getString(0);
        message.sessionId = stmt->getString(1);
        message.type = stmt->getInt(2);
        message.seqId = stmt->getLong(3);
        message.fromId = stmt->getString(4);
        message.toId = stmt->getString(5);
        message.fromClientId = stmt->getString(6);
        message.toClientId = stmt->getString(7);
        message.timestamp = stmt->getLong(8);
        message.pushInfo = stmt->getString(9);
        message.sendStatus = stmt->getInt(10);
        message.senderName = stmt->getString(11);
        message.status = stmt->getInt(12);
        message.priority = stmt->getInt(13);
        message.catalogId = stmt->getInt(14);
        message.content = stmt->getString(15);
        message.contentType = stmt->getInt(16);
        message.width = stmt->getInt(17);
        message.height = stmt->getInt(18);
        message.atType = stmt->getInt(19);
        message.atFeeds = stmt->getString(20);
        message.fileFormat = stmt->getString(21);
        message.noticeStatusType = stmt->getString(22);
        message.flags = stmt->getInt(23);
        message.faultSeqId = stmt->getInt(24);
        message.isMyself = (CTNOwner)stmt->getInt(25);
        message.subCatalogId = stmt->getInt(26);
        message.addition = stmt->getString(27);
        message.bizNo = stmt->getString(28);
        
        return message;
    }
    
    CTNMessageOperate CTNDBChat::generateOperateMessage(CSqliteDBStatement *stmt)
    {
        CTNMessageOperate messageOperate;
        messageOperate.msgId = stmt->getString(0);
        messageOperate.seqId = (int64_t)stmt->getLong(1);
        messageOperate.type = stmt->getInt(2);
        messageOperate.mfrom = stmt->getString(3);
        messageOperate.mto = stmt->getString(4);
        messageOperate.timestamp = (int64_t)stmt->getLong(5);
        messageOperate.catalogId = stmt->getInt(6);
        messageOperate.content = stmt->getString(7);
        messageOperate.opMsgId = stmt->getString(8);
        messageOperate.opFeedId = stmt->getString(9);
        messageOperate.opName = stmt->getString(10);
        
        return messageOperate;
    }
    
#pragma mark ------------tableIndex--------
    int CTNDBChat::generateTableIndex(const char*  sessionId)
    {
        if (sessionId == nullptr || strlen(sessionId) == 0) {
            return 0;
        }
        
        int tableIndex;
        std::string str = sessionId;
        std::string suffix = str.substr(str.length()-1, 1);
        if (suffix.length() > 0) {
            tableIndex = (std::atoi(suffix.c_str()))%TABLE_COUNT_MESSAGE;
        } else {
            tableIndex = 0;
        }
        
        return tableIndex;
    }
    
}

