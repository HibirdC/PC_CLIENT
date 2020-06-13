//
//  CTNDBMigrate.cpp
//  tnimsdk
//
//  Created by 王旭影 on 2017/12/29.
//  Copyright © 2017年 syswin. All rights reserved.
//

#ifdef __APPLE__
#include "CTNDBMigrate.hpp"
#include "rapidjson.h"
#include "document.h"
#include "pointer.h"
#include "CSqliteDB.hpp"
#include "CTNDBUtils.hpp"
#include "stringbuffer.h"
#include "writer.h"
#include "CTNDBChat.hpp"
#include "CLog.h"

#define DB_OLD_NAME(path, clientId) (path + "/chatlibrary_v5_" + clientId+ ".db")//3.6之前的数据库存储路径格式
#define DB_MIGRATE_VER 21//3.6版本的数据库最新版本为20，3.7迁移过来之后设置为加1的21，表明是否已经迁移
#define CLBDB_VER 20

namespace toonim {
    //wxy 迁移数据库使用，从3.6版本的数据库中获取atMe信息（ios客户端）
    void getAtMeMsgId(sqlite3_context *context, int argc, sqlite3_value **argv){
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
        
        if (1 == argc) {
            const char *lastMsg = (const char *)sqlite3_value_text(argv[0]);
            
            rapidjson::Document doc;
            doc.Parse(lastMsg);
            
            rapidjson::Value &atMeMsg = GetValueByPointerWithDefault(doc, "/atMe", "");
            
            if (atMeMsg.IsString()) {
                if (atMeMsg.GetStringLength() > 0) {
                    rapidjson::Value &msgId = GetValueByPointerWithDefault(doc, "/msgId", "");
                    if (msgId.IsString()) {
                        sqlite3_result_text(context, msgId.GetString(), -1, SQLITE_TRANSIENT);
                    }
                }
            }
        }
    }
    
    void calcUnReadCount(sqlite3_context *context, int argc, sqlite3_value **argv){
        if (argc < 3) {
            sqlite3_result_null(context);
            return;
        }
        if (sqlite3_value_type(argv[0]) == SQLITE_NULL) {
            sqlite3_result_null(context);
            return;
        }
        if (sqlite3_value_type(argv[0]) != SQLITE_TEXT) {
            //        sqlite3_result_error(context, "Expected text", -1);防止错误数据导致的迁移失败
            switch (sqlite3_value_type(argv[0])) {
                case SQLITE_INTEGER:
                    TNMPLOG("err data expect text,now " << "SQLITE_INTEGER sessionId:" << sqlite3_value_int(argv[0]));
                    break;
                case SQLITE_FLOAT:
                    TNMPLOG("err data expect text,now " << "SQLITE_FLOAT sessionId:" << sqlite3_value_double(argv[0]));
                    break;
                case SQLITE_TEXT:
                    TNMPLOG("err data expect text,now " << "SQLITE_TEXT sessionId:" << sqlite3_value_text(argv[0]));
                    break;
                    
                default:
                    break;
            }
            sqlite3_result_int64(context, 0);
            return;
        }
        
        if (sqlite3_value_type(argv[1]) != SQLITE_INTEGER) {
            //        sqlite3_result_error(context, "Expected integer", -1);防止错误数据导致的迁移失败
            switch (sqlite3_value_type(argv[1])) {
                case SQLITE_INTEGER:
                    //                TNMPLOG("err data expect integer,now SQLITE_INTEGER sessionId:" << sqlite3_value_int(argv[1]));
                    TNMPLOG("err data expect integer,now SQLITE_INTEGER sessionId:" << sqlite3_value_int(argv[1]));
                    break;
                case SQLITE_FLOAT:
                    TNMPLOG("err data expect integer,now SQLITE_FLOAT sessionId:" << sqlite3_value_double(argv[1]));
                    break;
                case SQLITE_TEXT:
                    TNMPLOG("err data expect integer,now SQLITE_TEXT sessionId:" << sqlite3_value_text(argv[1]));
                    break;
                    
                default:
                    break;
            }
            sqlite3_result_int64(context, 0);
            return;
        }
        
        if (sqlite3_value_type(argv[2]) != SQLITE_INTEGER) {
            //        sqlite3_result_error(context, "Expected integer", -1);防止错误数据导致的迁移失败
            switch (sqlite3_value_type(argv[2])) {
                case SQLITE_INTEGER:
                    TNMPLOG("err data expect integer,now SQLITE_INTEGER sessionId:" << sqlite3_value_int(argv[2]));
                    break;
                case SQLITE_FLOAT:
                    TNMPLOG("err data expect integer,now SQLITE_FLOAT sessionId:" << sqlite3_value_double(argv[2]));
                    break;
                case SQLITE_TEXT:
                    TNMPLOG("err data expect integer,now SQLITE_TEXT sessionId:" << sqlite3_value_text(argv[2]));
                    break;
                    
                default:
                    break;
            }
            sqlite3_result_int64(context, 0);
            return;
        }
        
        if (argc == 3) {
            const char* sessionId = (const char*)sqlite3_value_text(argv[0]);
            int64_t readSeqId = sqlite3_value_int64(argv[1]);
            CSqliteDB* pDb = (CSqliteDB*)sqlite3_value_int64(argv[2]);
            
            if (sessionId != nullptr && sessionId[0] != '\0') {//sessionId有值且不为空串
                if (pDb) {
                    std::string strSql = "select count(*) from ";
                    strSql.append(DB_MIGRATE);
                    strSql.append(".BMessage");
                    strSql.append(toonim::CTNDBUtils::stringFromInt32(toonim::CTNDBUtils::generateTableIndex(sessionId)));
                    strSql.append(" where sessionId='");
                    strSql.append(sessionId);
                    strSql.append("' and seqId>");
                    strSql.append(toonim::CTNDBUtils::stringFromInt64(readSeqId));
                    strSql.append(" and sendStatus=2 and status=0 and isMyself<>1");
                    
                    CSqliteDBStatement* records = pDb->execQuerySql(strSql.c_str());
                    
                    if (nullptr != records) {
                        if (CSqliteDBStatement::STEP_ROW == records->step()) {
                            int64_t unReadCount = records->getLong(0);
                            sqlite3_result_int64(context, unReadCount);
                        }else{
                            sqlite3_result_int64(context, 0);
                        }
                        delete records;
                        return;
                    }
                }
            }
        }
        
        sqlite3_result_int64(context, 0);
    }
    
    void extractContent(sqlite3_context *context, int argc, sqlite3_value **argv){
        if (argc < 2) {
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
        if (sqlite3_value_type(argv[1]) == SQLITE_NULL) {
            sqlite3_result_null(context);
            return;
        }
        if (sqlite3_value_type(argv[1]) != SQLITE_TEXT) {
            sqlite3_result_null(context);
            return;
        }
        
        if (argc == 2) {
            const char* content = (const char*)sqlite3_value_text(argv[0]);
            const char* key = (const char*)sqlite3_value_text(argv[1]);
            //参数已在前面做判空
            
            rapidjson::Document doc;
            doc.Parse(content);
            
            if (doc.HasMember(key)) {
                rapidjson::Value& val = doc[key];
                if (val.IsString()) {
                    std::string strVal = val.GetString();
                    sqlite3_result_text(context, doc[key].GetString(), doc[key].GetStringLength(), SQLITE_TRANSIENT);
                }
                
                if (val.IsInt()) {
                    sqlite3_result_int(context, doc[key].GetInt());
                }
            }else{
                sqlite3_result_null(context);
            }
        }
    }
    
    void supplyContent(sqlite3_context *context, int argc, sqlite3_value **argv){
        if (argc < 3) {
            sqlite3_result_null(context);
            return;
        }
        if (sqlite3_value_type(argv[0]) == SQLITE_NULL || sqlite3_value_type(argv[1]) == SQLITE_NULL || sqlite3_value_type(argv[2]) == SQLITE_NULL) {
            sqlite3_result_null(context);
            return;
        }
        if (sqlite3_value_type(argv[0]) != SQLITE_TEXT || sqlite3_value_type(argv[1]) != SQLITE_TEXT || sqlite3_value_type(argv[2]) != SQLITE_INTEGER) {
            sqlite3_result_null(context);
            return;
        }
        if (3 == argc) {
            const char* srcContent = (const char*)sqlite3_value_text(argv[0]);
            const char* addKey = (const char*)sqlite3_value_text(argv[1]);
            //        const char* addValue = (const char*)sqlite3_value_text(argv[0]);
            int64_t addValue = sqlite3_value_int64(argv[2]);
            
            //atMe情况特殊处理，3.6之前的版本中atMe信息需要重置为0，但该接口本意是要设置expireTime值，而expireTime值为0，无需设置，因此在此作区分
            if ((strcmp(addKey, "atMe") && addValue > 0) || (!strcmp(addKey, "atMe"))) {
                rapidjson::Document sDoc;
                sDoc.Parse(srcContent);
                
                rapidjson::Value keyVal;
                keyVal.SetString(addKey, (int32_t)strlen(addKey));
                rapidjson::Value& expireTime = sDoc[addKey];
                if (expireTime.IsNull()) {
                    sDoc.AddMember(keyVal, addValue, sDoc.GetAllocator());
                }else{
                    expireTime.SetInt((int32_t)addValue);
                }
                
                //            rapidjson::Pointer(addKey).Set(sDoc, addValue);
                
                rapidjson::StringBuffer buffer;
                rapidjson::Writer<rapidjson::StringBuffer> docWriter(buffer);
                sDoc.Accept(docWriter);
                
                sqlite3_result_text(context, buffer.GetString(), (int32_t)buffer.GetLength(), SQLITE_TRANSIENT);
            }else{
                sqlite3_result_text(context, srcContent, -1, SQLITE_TRANSIENT);
            }
        }
    }
    
    void chatFileSize(sqlite3_context *context, int argc, sqlite3_value **argv) {
        if (argc < 2) {
            sqlite3_result_null(context);
            return;
        }
        if (sqlite3_value_type(argv[0]) == SQLITE_NULL || sqlite3_value_type(argv[1]) == SQLITE_NULL) {
            sqlite3_result_null(context);
            return;
        }
        if (sqlite3_value_type(argv[0]) != SQLITE_INTEGER) {
            sqlite3_result_null(context);
            return;
        }
        if (sqlite3_value_type(argv[1]) != SQLITE_INTEGER && sqlite3_value_type(argv[1]) != SQLITE_FLOAT) {
            sqlite3_result_null(context);
            return;
        }
        if (argc == 2) {
            int64_t contentType = sqlite3_value_int64(argv[0]);
            float msgSize = (float)sqlite3_value_double(argv[1]);
            
            if (contentType == CTNChatTypeFiles || contentType == CTNChatTypeRecommend) {
                msgSize = 0.0;
            }
            sqlite3_result_double(context, msgSize);
        }
    }
    
    void lastMsgToJson(sqlite3_context *context, int argc, sqlite3_value **argv){
        if (argc < 2) {
            sqlite3_result_null(context);
            return;
        }
        if (sqlite3_value_type(argv[0]) == SQLITE_NULL || sqlite3_value_type(argv[1]) == SQLITE_NULL) {
            sqlite3_result_null(context);
            return;
        }
        if (sqlite3_value_type(argv[0]) != SQLITE_TEXT || sqlite3_value_type(argv[1]) != SQLITE_TEXT) {
            sqlite3_result_null(context);
            return;
        }
        
        if (argc == 2) {
            const char *lastMsg = (const char *)sqlite3_value_text(argv[0]);
            const char *draft = (const char *)sqlite3_value_text(argv[1]);
            
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> docWriter(buffer);
            
            docWriter.StartObject();
            docWriter.Key("lastMsg");
            docWriter.String(lastMsg);
            docWriter.Key("drafts");
            docWriter.String(draft);
            docWriter.EndObject();
            
            sqlite3_result_text(context, buffer.GetString(), -1, SQLITE_TRANSIENT);
        }else{
            sqlite3_result_null(context);
        }
    }
    
    void getLocalMaxSeq(sqlite3_context *context, int argc, sqlite3_value **argv){
        if (argc < 2) {
            sqlite3_result_null(context);
            return;
        }
        if (sqlite3_value_type(argv[0]) == SQLITE_NULL || sqlite3_value_type(argv[1]) == SQLITE_NULL) {
            sqlite3_result_null(context);
            return;
        }
        if (sqlite3_value_type(argv[0]) != SQLITE_TEXT) {
            //        sqlite3_result_error(context, "Expected text", -1);防止错误数据导致的迁移失败
            switch (sqlite3_value_type(argv[0])) {
                case SQLITE_INTEGER:
                    TNMPLOG("err data expect text,now " << "SQLITE_INTEGER sessionId:" << sqlite3_value_int(argv[0]));
                    break;
                case SQLITE_FLOAT:
                    TNMPLOG("err data expect text,now " << "SQLITE_FLOAT sessionId:" << sqlite3_value_double(argv[0]));
                    break;
                case SQLITE_TEXT:
                    TNMPLOG("err data expect text,now " << "SQLITE_TEXT sessionId:" << sqlite3_value_text(argv[0]));
                    break;
                    
                default:
                    break;
            }
            sqlite3_result_int64(context, 0);
            return;
        }
        
        if (sqlite3_value_type(argv[1]) != SQLITE_INTEGER) {
            //        sqlite3_result_error(context, "Expected integer", -1);防止错误数据导致的迁移失败
            switch (sqlite3_value_type(argv[1])) {
                case SQLITE_INTEGER:
                    TNMPLOG("err data expect integer,now SQLITE_INTEGER sessionId:" << sqlite3_value_int(argv[1]));
                    break;
                case SQLITE_FLOAT:
                    TNMPLOG("err data expect integer,now SQLITE_FLOAT sessionId:" << sqlite3_value_double(argv[1]));
                    break;
                case SQLITE_TEXT:
                    TNMPLOG("err data expect integer,now SQLITE_TEXT sessionId:" << sqlite3_value_text(argv[1]));
                    break;
                    
                default:
                    break;
            }
            sqlite3_result_int64(context, 0);
            return;
        }
        
        if (argc == 2) {
            const char* sessionId = (const char*)sqlite3_value_text(argv[0]);
            CSqliteDB* pDb = (CSqliteDB*)sqlite3_value_int64(argv[1]);
            
            if (sessionId != nullptr && sessionId[0] != '\0') {//sessionId有值且不为空串
                if (pDb) {
                    std::string strSql = "select max(seqId) from ";
                    strSql.append(DB_MIGRATE);
                    strSql.append(".BMessage");
                    strSql.append(toonim::CTNDBUtils::stringFromInt32(toonim::CTNDBUtils::generateTableIndex(sessionId)));
                    strSql.append(" where sessionId='");
                    strSql.append(sessionId);
                    strSql.append("'");
                    
                    CSqliteDBStatement* records = pDb->execQuerySql(strSql.c_str());
                    
                    if (nullptr != records) {
                        if (CSqliteDBStatement::STEP_ROW == records->step()) {
                            int64_t maxLocalSeq = records->getLong(0);
                            sqlite3_result_int64(context, maxLocalSeq);
                        }else{
                            sqlite3_result_int64(context, 0);
                        }
                        delete records;
                        return;
                    }
                }
            }
        }
        
        sqlite3_result_int64(context, 0);
    }
    
    void generatSessionId(sqlite3_context *context, int argc, sqlite3_value **argv){
        if (argc < 3) {
            sqlite3_result_null(context);
            return;
        }
        if (sqlite3_value_type(argv[0]) == SQLITE_NULL || sqlite3_value_type(argv[1]) == SQLITE_NULL || sqlite3_value_type(argv[2]) == SQLITE_NULL) {
            sqlite3_result_null(context);
            return;
        }
        if (sqlite3_value_type(argv[0]) != SQLITE_INTEGER) {
            sqlite3_result_error(context, "Expected integer", -1);
            return;
        }
        if (sqlite3_value_type(argv[1]) != SQLITE_TEXT || sqlite3_value_type(argv[2]) != SQLITE_TEXT) {
            sqlite3_result_error(context, "Expected text", -1);
            return;
        }
        
        if (argc == 3) {
            int32_t type = sqlite3_value_int(argv[0]);
            const char* fromId = (const char*)sqlite3_value_text(argv[1]);
            const char* toId = (const char*)sqlite3_value_text(argv[2]);
            //参数已在前面做判空
            sqlite3_result_text(context, toonim::generateSessionId(type, fromId, toId, false).c_str(), -1, SQLITE_TRANSIENT);
        }else{
            sqlite3_result_null(context);
        }
    }
    
    void CTNDBChat::migrateDataOfSession(){
        //attach 数据库，提高迁移效率 wxy
        TNMPLOG("migrateDataOfSession begin");
        if (nullptr == _sqliteDb) {
            return;
        }
        
        //加上锁 加上版本控制
        std::unique_lock<std::mutex> unilock(m_mutex);
        
        //兼容3.6版本之前的数据库
        string strOldDb = DB_OLD_NAME(_appPath, _clientId);
        if (!CTNDBUtils::fileExistsAtPath(strOldDb)) {
            TNMPLOG("v5 database file not exist,need not to migrate db");
            return;
        }
        
        std::string strSql = "attach DataBase '";
        strSql += strOldDb;
        strSql += "' as ";
        strSql += DB_MIGRATE;
#ifdef ENCODE_DATABASE
        strSql += " KEY '";
        strSql += toonim::CTNDBUtils::generateEncryptKey(_clientId);
        strSql += "'";
#endif
        
        _sqliteDb->execSql(strSql.c_str());
        
        strSql = "pragma ";
        strSql.append(DB_MIGRATE);
        strSql.append(".user_version");
        
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(strSql.c_str());
        uint32_t ver = 0;
        if (records == NULL) {
            ver = 0;
        }else{
            while (records->step() == CSqliteDBStatement::STEP_ROW) {
                ver = records->getInt(0);
            }
        }
        if (ver >= DB_MIGRATE_VER) {
            strSql = "detach database ";
            strSql += DB_MIGRATE;
            _sqliteDb->execSql(strSql.c_str());
            return;
        }
        
        if (ver < 10) {
            //10以前的版本数据重构，无需迁移，不作删除老DB操作
            return;
        }
        else if (ver < CLBDB_VER){
            _sqliteDb->makeFunction("lastMsgToJson", lastMsgToJson, 2);
            _sqliteDb->makeFunction("getLocalMaxSeq", getLocalMaxSeq, 2);
            _sqliteDb->makeFunction("supplyContent", supplyContent, 3);
            _sqliteDb->makeFunction("generatSessionId", generatSessionId, 3);
            upgradeTableWithOldVersion(ver);
        }else{
            _sqliteDb->makeFunction("supplyContent", supplyContent, 3);
        }
        
        TNMPLOG("TNChatLibraryDB oldVersion:" << ver << "  CLBDB_VER:" << CLBDB_VER);
        
        _sqliteDb->makeFunction("getAtMeMsgId", getAtMeMsgId, 1);
        _sqliteDb->makeFunction("calcUnReadCount", calcUnReadCount, 3);
        _sqliteDb->makeFunction("extractContent", extractContent, 2);
        _sqliteDb->makeFunction("chatFileSize", chatFileSize, 2);
        
        strSql = "insert into Session select A.sessionId,A.topic,A.myFeedId,A.type,A.title,A.avatarId,A.draft,A.lastTime,extractContent(A.lastMsg, 'lastMsg'),A.lastMsgId,A.lastMsgSendStatus,A.readSeqId,A.sortTime,getAtMeMsgId(A.lastMsg),calcUnReadCount(A.sessionId,A.readSeqId,";
        strSql.append(toonim::CTNDBUtils::stringFromInt64((int64_t)_sqliteDb));//A.unreadCount
        strSql.append("),A.topStatus from ");
        strSql.append(DB_MIGRATE);
        strSql.append(".Session as A where (((myFeedId not in (select feedId from BlackList) or topic not in(select passiveFeedId from BlackList)) and type=52) or type!=52);");
        if (!_sqliteDb->execSql(strSql.c_str())) {//会话迁移失败，直接返回
            strSql = "detach database ";
            strSql += DB_MIGRATE;
            _sqliteDb->execSql(strSql.c_str());
            TNMPLOG("migrate Session failed!");
            return;
        }
        
        //同步session之后的操作放到子线程中
        TNMPLOG("migrateDataOfSession end");
        
        std::thread migrateThread(&CTNDBChat::migrateRemainder, this);
        migrateThread.detach();
    }
    
    void CTNDBChat::migrateRemainder(){
        TNMPLOG("migrateThread begin");
        if (nullptr == _sqliteDb) {
            return;
        }
        std::unique_lock<std::mutex> unilock(m_mutex);
        std::string strSql;
        
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(strSql.c_str());
        uint32_t ver = 0;
        if (records == NULL) {
            ver = 0;
        }else{
            while (records->step() == CSqliteDBStatement::STEP_ROW) {
                ver = records->getInt(0);
            }
        }
        
        if (ver >= DB_MIGRATE_VER) {
            strSql = "detach database ";
            strSql += DB_MIGRATE;
            _sqliteDb->execSql(strSql.c_str());
            return;
        }
        
        std::string strSqlMsg;
        bool bMigSuc = true;
        
        for (int i = 0; i < toonim::TABLE_COUNT_MESSAGE; ++i) {
            strSqlMsg = "insert into BMessage";
            strSqlMsg.append(toonim::CTNDBUtils::stringFromInt32(i));
            //A.flags 默认值0，A.faultSeqId 默认值-1,A.addition 默认值'' formClientId 😳,A.noticeStatusType替换为msgStatusType
            strSqlMsg.append(" select A.msgId,A.sessionId,A.type,A.seqId,A.fromId,A.toId,A.formClientId,A.toClientId,A.timestamp,A.pushInfo,A.sendStatus,A.senderName,A.status,A.priority,A.catalogId,supplyContent(A.content,'expireTime',A.expireTime),A.contentType,chatFileSize(A.contentType, A.width),chatFileSize(A.contentType, A.height),A.atType,A.atFeeds,A.fileFormat,A.msgStatusType,0,-1,A.isMyself,extractContent(A.content, 'subCatalogId'),'',extractContent(A.content,'bizNo') from ");
            strSqlMsg.append(DB_MIGRATE);
            strSqlMsg.append(".BMessage");
            strSqlMsg.append(toonim::CTNDBUtils::stringFromInt32(i));
            strSqlMsg.append(" as A where status=0 order by seqId desc,timestamp desc");
            
            if (!_sqliteDb->execSql(strSqlMsg.c_str())) {
                bMigSuc = false;
            }
        }
        
        //设置信息迁移
        strSql ="insert into sessionSettings select A.sessionId,6,A.backgroundImagePath from ";
        strSql.append(DB_MIGRATE);
        strSql.append(".SessionBackground as A ");//6 key type value
        if (!_sqliteDb->execSql(strSql.c_str())) {
            bMigSuc = false;
        }
        
        //操作消息
        strSql = "insert into MessageOperate select A.msgId,A.seqId,A.type,A.mfrom,A.mto,A.timestamp,A.catalogId,'',A.opMsgId,A.opFeedId,A.opName from ";
        strSql.append(DB_MIGRATE);
        strSql.append(".MessageOperate as A");
        if (!_sqliteDb->execSql(strSql.c_str())) {
            bMigSuc =false;
        }
        
        //断层消息
        strSql = "select priority,sessionId,maxSeqId,minSeqId from ";
        strSql.append(DB_MIGRATE);
        strSql.append(".MessageFault");
        CQIPtr<CSqliteDBStatement, QI_NEW> record2 = _sqliteDb->execQuerySql(strSql.c_str());
        
        if (record2) {
            while (record2->step() == CSqliteDBStatement::STEP_ROW) {
                int64_t pri = record2->getLong(0);
                const char* sessionId = record2->getString(1);
                int64_t maxSeq = record2->getLong(2);
                int64_t minSeq = record2->getLong(3);
                
                strSql = "update BMessage";
                strSql.append(toonim::CTNDBUtils::stringFromInt32(toonim::CTNDBUtils::generateTableIndex(sessionId)));
                strSql.append(" set faultSeqId=");
                strSql.append(toonim::CTNDBUtils::stringFromInt64(minSeq));
                strSql.append(" where sessionId='");
                strSql.append(sessionId);
                strSql.append("' and seqId=");
                strSql.append(toonim::CTNDBUtils::stringFromInt64(maxSeq));
                strSql.append(" and priority=");
                strSql.append(toonim::CTNDBUtils::stringFromInt64(pri));
                
                if (!_sqliteDb->execSql(strSql.c_str())) {
                    bMigSuc = false;
                }
            }
        }
        
        if (bMigSuc) {
            strSql = "pragma ";
            strSql.append(DB_MIGRATE);
            strSql.append(".user_version =");
            strSql.append(toonim::CTNDBUtils::stringFromInt32(DB_MIGRATE_VER));
            
            this->execSql(strSql.c_str());
        }
        
        strSql = "detach database ";
        strSql += DB_MIGRATE;
        _sqliteDb->execSql(strSql.c_str());
        TNMPLOG("migrateThread end");
    }
    
    bool CTNDBChat::upgradeTableWithOldVersion(int32_t oldVer){
        //need upgrade
        std::string strSql;
        const char* err = nullptr;
        int32_t code = -1;
        switch (oldVer) {
            case 10:
            case 11:
            {
                //添加了发送状态字段（lastMsgSendStatus）
                strSql = "alter table ";
                strSql.append(DB_MIGRATE);
                strSql.append(".DialogInfo add lastMsgSendStatus integer");
                execSql(strSql.c_str());
                
                strSql = "update ";
                strSql.append(DB_MIGRATE);
                strSql.append(".dialogInfo set firstSeqId=1 where firstSeqId=0");
                execSql(strSql.c_str());
                //MESSAGE TABLE
                strSql = "CREATE TABLE IF NOT EXISTS ";
                strSql.append(DB_MIGRATE);
                strSql.append(".MessageOperate(msgId text UNIQUE, seqId integer, type integer, mfrom text, mto text,timestamp integer, catalogId integer,opMsgId text,opFeedId text,opName text, primary key (msgId,seqId))");
                if (!execSql(strSql.c_str())) {
                    code = getDbErr(err);
                    TNMPLOG("createTable MessageOperate Err code:" << code << ",err:" << (err?err:""));
                }
            }
            case 12:
            case 13:
            {
                strSql = "CREATE TABLE IF NOT EXISTS ";
                strSql.append(DB_MIGRATE);
                strSql.append(".BlackList(feedId text, passiveFeedId text, status integer, primary key(feedId, passiveFeedId))");
                if (!execSql(strSql.c_str())) {
                    code = getDbErr(err);
                    TNMPLOG("createTable BlackList Err code:" << code << ",err:" << (err?err:""));
                }
                
                strSql = "CREATE INDEX IF NOT EXISTS BlackList_index ON ";
                strSql.append(DB_MIGRATE);
                strSql.append(".BlackList('feedId', 'passiveFeedId')");
                
                if (!execSql(strSql.c_str())) {
                    code = getDbErr(err);
                    TNMPLOG("SQL Err code:" << code << ",err:" << (err?err:""));
                }
                
                createMessageTable();
                createSessionTable();
                createMessageFault();
                versionUpdateOldSession();
            }
            case 14:
            {
                for (int i = 0; i < toonim::TABLE_COUNT_MESSAGE; i++){
                    strSql = "alter table ";
                    strSql.append(DB_MIGRATE);
                    strSql.append(".BMessage");
                    strSql.append(toonim::CTNDBUtils::stringFromInt32(i));
                    strSql.append(" add senderName text");
                    execSql(strSql.c_str());
                    
                    strSql = "alter table ";
                    strSql.append(DB_MIGRATE);
                    strSql.append(".BMessage");
                    strSql.append(toonim::CTNDBUtils::stringFromInt32(i));
                    strSql.append(" add atType integer");
                    execSql(strSql.c_str());
                    
                    strSql = "alter table ";
                    strSql.append(DB_MIGRATE);
                    strSql.append(".BMessage");
                    strSql.append(toonim::CTNDBUtils::stringFromInt32(i));
                    strSql.append(" add atFeeds text");
                    execSql(strSql.c_str());
                    
                    strSql = "update ";
                    strSql.append(DB_MIGRATE);
                    strSql.append(".BMessage");
                    strSql.append(toonim::CTNDBUtils::stringFromInt32(i));
                    strSql.append(" set width=0, height=0");
                    execSql(strSql.c_str());
                }
                
                //把原来数据库中的lastMsg 转出json
                versionUpdateSessionWithLastMsg();
                createChatAppListTable();
            }
            case 15:
            {
                strSql = "alter table ";
                strSql.append(DB_MIGRATE);
                strSql.append(".Session add sortTime integer;alter table ");
                strSql.append(DB_MIGRATE);
                strSql.append(".Session add sortTime integer;alter table ");
                strSql.append(DB_MIGRATE);
                strSql.append(".Session add topStatus integer;alter table ");
                strSql.append(DB_MIGRATE);
                strSql.append(".TNMessageAppInfo add chatFlag integer;");
                execSql(strSql.c_str());
                
                for (int i = 0; i < toonim::TABLE_COUNT_MESSAGE; i++){
                    strSql = "alter table ";
                    strSql.append(DB_MIGRATE);
                    strSql.append(".BMessage");
                    strSql.append(toonim::CTNDBUtils::stringFromInt32(i));
                    strSql.append(" add fileFormat text");
                    execSql(strSql.c_str());
                }
            }
            case 16:
            {
                for (int i = 0; i < toonim::TABLE_COUNT_MESSAGE; i++){
                    strSql = "alter table ";
                    strSql.append(DB_MIGRATE);
                    strSql.append(".BMessage");
                    strSql.append(toonim::CTNDBUtils::stringFromInt32(i));
                    strSql.append(" add formClientId text");
                    execSql(strSql.c_str());
                    
                    strSql = "alter table ";
                    strSql.append(DB_MIGRATE);
                    strSql.append(".BMessage");
                    strSql.append(toonim::CTNDBUtils::stringFromInt32(i));
                    strSql.append(" add toClientId text");
                    execSql(strSql.c_str());
                }
            }
            case 17:
            case 18:
            {
                //3.5版本 数据库升级
                strSql = "alter table ";
                strSql.append(DB_MIGRATE);
                strSql.append(".Session add maxSeqId integer");
                execSql(strSql.c_str());
                
                strSql = "alter table ";
                strSql.append(DB_MIGRATE);
                strSql.append(".Session add readSeqId integer");
                execSql(strSql.c_str());
                
                strSql = "alter table ";
                strSql.append(DB_MIGRATE);
                strSql.append(".Session add highMaxSeqId integer");
                execSql(strSql.c_str());
                
                strSql = "alter table ";
                strSql.append(DB_MIGRATE);
                strSql.append(".MessageFault add fromId text");
                execSql(strSql.c_str());
                
                strSql = "alter table ";
                strSql.append(DB_MIGRATE);
                strSql.append(".MessageFault add toId text");
                execSql(strSql.c_str());
                
                strSql = "alter table ";
                strSql.append(DB_MIGRATE);
                strSql.append(".MessageFault add type integer");
                execSql(strSql.c_str());
                
                strSql = "alter table ";
                strSql.append(DB_MIGRATE);
                strSql.append(".MessageFault add priority integer");
                execSql(strSql.c_str());
                
                strSql = "alter table ";
                strSql.append(DB_MIGRATE);
                strSql.append(".MessageFault add requestId text");
                execSql(strSql.c_str());
                
                strSql = "alter table ";
                strSql.append(DB_MIGRATE);
                strSql.append(".MessageFault add minTime integer");
                execSql(strSql.c_str());
                
                strSql = "alter table ";
                strSql.append(DB_MIGRATE);
                strSql.append(".MessageFault add maxTime integer");
                execSql(strSql.c_str());
                
                for (int i = 0; i < toonim::TABLE_COUNT_MESSAGE; i++){
                    strSql = "alter table ";
                    strSql.append(DB_MIGRATE);
                    strSql.append(".BMessage");
                    strSql.append(toonim::CTNDBUtils::stringFromInt32(i));
                    strSql.append(" add msgStatusType text");
                    execSql(strSql.c_str());
                }
                strSql = "drop table ";
                strSql.append(DB_MIGRATE);
                strSql.append(".GroupInfo;drop table ");
                strSql.append(DB_MIGRATE);
                strSql.append(".GroupMember;drop table ");
                strSql.append(DB_MIGRATE);
                strSql.append(".ChatAppList;drop table ");
                strSql.append(DB_MIGRATE);
                strSql.append(".JokesInfo;drop table ");
                strSql.append(DB_MIGRATE);
                strSql.append(".JokesCategoryInfo;");
                execSql(strSql.c_str());
            }
            case 19:
            {
                strSql = "delete from ";
                strSql.append(DB_MIGRATE);
                strSql.append(".MessageFault");
                execSql(strSql.c_str());
                
                strSql = "update ";
                strSql.append(DB_MIGRATE);
                strSql.append(".session set lastMsg=supplyContent(lastMsg,'atMe',0),readSeqId=getLocalMaxSeq(sessionId,");
                strSql.append(toonim::CTNDBUtils::stringFromInt64((int64_t)_sqliteDb));
                strSql.append(")");
                execSql(strSql.c_str());
            }
            default:
                break;
        }
        return true;
    }
    
    bool CTNDBChat::createMessageTable(){
        int32_t code = -1;
        const char* err = nullptr;
        for (int i = 0; i < toonim::TABLE_COUNT_MESSAGE; i++){
            std::string strSql = "create table if not exists ";
            strSql.append(DB_MIGRATE);
            strSql.append(".BMessage");
            strSql.append(toonim::CTNDBUtils::stringFromInt32(i));
            strSql.append(" (sessionId varchar(50),msgId varchar(40), type integer, seqId integer, fromId varchar(30),toId text,formClientId text,toClientId varchar(30),timestamp integer,pushInfo text,expireTime integer, sendStatus integer, status integer,priority integer, catalogId integer,catalog text, contentType integer, content text,isMyself integer, width integer, height integer, senderName text,atType integer,atFeeds  text,fileFormat text,msgStatusType text, primary key (msgId));");
            if (!execSql(strSql.c_str())) {
                code = getDbErr(err);
                TNMPLOG("create BMessage" << i << " Err code:" << code << ",err:" << (err?err:""));
                return false;
            }
            
            strSql = "create index if not exists BMessage";
            strSql.append(toonim::CTNDBUtils::stringFromInt32(i));
            strSql.append("_index ON");
            strSql.append(DB_MIGRATE);
            strSql.append(".BMessage");
            strSql.append(toonim::CTNDBUtils::stringFromInt32(i));
            strSql.append("('sessionId' asc, 'msgId' asc,'seqId' asc,'type' asc,'fromId' asc,'toId' ASC,'contentType' asc,'catalogId' asc, 'sendStatus' asc);");
            if (!execSql(strSql.c_str())) {
                code = getDbErr(err);
                TNMPLOG("create index of BMessage" << i << " Err code:" << code << ",err:" << (err?err:""));
                return false;
            }
        }
        return true;
    }
    
    // 创建会话表
    bool CTNDBChat::createSessionTable(){
        int32_t code = -1;
        const char* err = nullptr;
        std::string strSql = "CREATE TABLE IF NOT EXISTS ";
        strSql.append(DB_MIGRATE);
        strSql.append(".Session(sessionId varchar(40) PRIMARY KEY, topic varchar(20), myFeedId varchar(20) not null default ' ', type integer, unreadCount integer, title text, titlePinyin text, pinyinHeader text, avatarId text, draft text, lastTime integer, lastMsg text, lastMsgId text, lastMsgSendStatus integer,topStatus integer,sortTime integer,maxSeqId integer,highMaxSeqId integer, readSeqId integer);");
        if (!execSql(strSql.c_str())) {
            code = getDbErr(err);
            TNMPLOG("createTable Session Err code:" << code << ",err:" << (err?err:""));
            return false;
        }
        
        strSql = "CREATE INDEX if not exists Session_index ON ";
        strSql.append(DB_MIGRATE);
        strSql.append(".Session(sessionId ASC, 'topic' ASC, 'lastTime' ASC, 'type' asc, 'myFeedId' asc);");
        
        if (!execSql(strSql.c_str())) {
            code = getDbErr(err);
            TNMPLOG("SQL Err code:" << code << ",err:" << (err?err:""));
            return false;
        }
        
        return true;
    }
    
    bool CTNDBChat::createMessageFault(){
        int32_t code = -1;
        const char* err = nullptr;
        //RESIDENT TABEL (断层表)
        std::string strSql = "CREATE TABLE IF NOT EXISTS ";
        strSql.append(DB_MIGRATE);
        strSql.append(".MessageFault (fromId text,toId text,type integer,priority integer,requestId text,minTime integer,maxTime integer, sessionId text,maxSeqId integer, count integer,minSeqId integer ,PRIMARY KEY(sessionId, minSeqId));");
        
        if (!execSql(strSql.c_str())) {
            code = getDbErr(err);
            TNMPLOG("CREATE TABLE MessageFault Err code:" << code << ",err:" << (err?err:""));
            return false;
        }
        
        strSql = "CREATE INDEX if not exists MessageFault_index ON ";
        strSql.append(DB_MIGRATE);
        strSql.append(".MessageFault('minSeqId' ASC);");
        
        if (!execSql(strSql.c_str())) {
            code = getDbErr(err);
            TNMPLOG("CREATE INDEX of MessageFault Err code:" << code << ",err:" << (err?err:""));
            return false;
        }
        
        return true;
    }
    
    bool CTNDBChat::versionUpdateSessionWithLastMsg(){
        int32_t code = -1;
        const char* err = nullptr;
        std::string strSql = "update ";
        strSql.append(DB_MIGRATE);
        strSql.append(".Session set lastMsg=lastMsgToJson(lastMsg,draft)");
        
        if(!execSql(strSql.c_str())){
            code = getDbErr(err);
            TNMPLOG("update session Session Err code:" << code << ",err:" << (err?err:""));
            return false;
        }
        
        return true;
    }
    
    bool CTNDBChat::createChatAppListTable(){
        int32_t code = -1;
        const char* err = nullptr;
        std::string strSql = "CREATE TABLE IF NOT EXISTS ";
        strSql.append(DB_MIGRATE);
        strSql.append(".ChatAppList(data text)");
        
        if(!execSql(strSql.c_str())){
            code = getDbErr(err);
            TNMPLOG("createTable ChatAppList Err code:" << code << ",err:" << (err?err:""));
            return false;
        }
        return true;
    }
    
    //获取老版本的列表
    bool CTNDBChat::versionUpdateOldSession(){
        std::string strSql = "insert into ";
        strSql.append(DB_MIGRATE);
        strSql.append(".Session select generatSessionId(A.type,A.myFeedId,A.topic),A.topic,A.myFeedId,A.type,A.unreadCount,A.name,'','',A.headerImage,A.draft,A.lastTime,A.lastMsg,A.ext3,A.lastMsgSendStatus,0,A.lastTime,0,0,0 from ");
        strSql.append(DB_MIGRATE);
        strSql.append(".DialogInfo as A");
        
        //单聊消息，从Message表格中分别捞取对应下标的数据到对应的表格中 群聊消息，查询所有群ID，对应存储到表格中
        for (int i = 0; i < toonim::TABLE_COUNT_MESSAGE; ++i) {
            std::string strSql = "insert into ";
            strSql.append(DB_MIGRATE);
            strSql.append(".BMessage");
            strSql.append(toonim::CTNDBUtils::stringFromInt32(i));
            strSql.append(" select generatSessionId(A.type,A.fromId,A.toId),A.msgId,A.type,A.seqId,A.mfrom,A.mto,'','',timestamp,extractContent(A.body,'pushInfo'),extractContent(A.body,'expireTime'),A.sendStatus,A.status,extractContent(A.body,'priority'), A.catalogId,extractContent(A.body,'catalog'),A.contentType,A.body,extractContent(A.body,'isMyself'),A.width,A.height,extractContent(A.body,'senderName'),extractContent(A.body,'atType'),extractContent(A.body,'atFeeds'),extractContent(A.body,'fileFormat'),extractContent(A.body,'msgStatusType') from ");
            strSql.append(DB_MIGRATE);
            strSql.append(".Message as A where status=0 and getTableIndex(A.type,A.fromId,A.toId)=");
            strSql.append(toonim::CTNDBUtils::stringFromInt32(i));
            execSql(strSql.c_str());
        }
        
        strSql = "select topic from ";
        strSql.append(DB_MIGRATE);
        strSql.append(".DialogInfo");
        
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(strSql.c_str());
        std::string strGroupSql;
        std::string strGroupTopic;
        if (records != NULL) {
            while (records->step() == CSqliteDBStatement::STEP_ROW) {
                strGroupTopic = records->getString(0);
                strGroupSql = "insert into ";
                strGroupSql.append(DB_MIGRATE);
                strGroupSql.append(".BMessage");
                strSql.append(toonim::CTNDBUtils::stringFromInt32(toonim::CTNDBUtils::generateTableIndex(strGroupTopic.c_str())));
                strSql.append(" select generatSessionId(A.type,A.fromId,A.toId),A.msgId,A.type,A.seqId,A.mfrom,A.mto,'','',timestamp,extractContent(A.body,'pushInfo'),extractContent(A.body,'expireTime'),A.sendStatus,A.status,extractContent(A.body,'priority'), A.catalogId,extractContent(A.body,'catalog'),A.contentType,A.body,extractContent(A.body,'isMyself'),A.width,A.height,extractContent(A.body,'senderName'),extractContent(A.body,'atType'),extractContent(A.body,'atFeeds'),extractContent(A.body,'fileFormat'),extractContent(A.body,'msgStatusType') from ");
                strSql.append(DB_MIGRATE);
                strSql.append(".gc_");
                strSql.append(strGroupTopic);
                strSql.append(" where status=0");
                execSql(strSql.c_str());
            }
        }
        
        return false;
    }
}

int32_t CTNDBBase::getDbErr(const char *err){
    return _sqliteDb->getDbErr(err);
}
#endif

