//
//  CSqliteDB.cpp
//  sqlite3
//
//  Created by 王旭影 on 17/8/19.
//  Copyright © 2017年 思源. All rights reserved.
//

#include "CSqliteDB.hpp"
#include <CLog.h>
#include "CTNDBUtils.hpp"
#include "TMTPConst.h"
#include "CTNDBBase.hpp"

#ifdef WIN32
#include <windows.h>
#elif __linux__
#include <string.h>
#endif

std::map<std::string, CSqliteDB*> CSqliteDB::dbConnMap;// CSafeMap
std::mutex CSqliteDB::sMutex;

void CSqliteDB::reset()
{
    std::unique_lock<std::mutex> unilock(sMutex);
    std::map<std::string, CSqliteDB*>::iterator iter = CSqliteDB::dbConnMap.begin();
    
    while(iter != CSqliteDB::dbConnMap.end()) {
//        delete  iter->second;切换账号可能会有crash问题，暂时内存泄露
        TNMPLOG("destory DB CONN:"<<iter->first);
        iter++;
    }
    
    CSqliteDB::dbConnMap.clear();
    
    TNMPLOG("CSqliteDB::reset()");
}

CSqliteDB* CSqliteDB::getDb (const char* path, const char* tag, const char* userId, const char* encryptKey) {
    CSqliteDB* pDb = nullptr;
    
    std::unique_lock<std::mutex> unilock(sMutex);
    std::map<std::string, CSqliteDB*>::iterator iter = CSqliteDB::dbConnMap.find(path);
    
    if(iter != CSqliteDB::dbConnMap.end()) {
        pDb = iter->second;
        return pDb;
    }
    
    pDb = new CSqliteDB();
    
    if (userId != nullptr) {
        pDb->_userId = userId;
    }
    
    int ret = pDb->openDB(path);
    
    if (!ret){
        TNMPLOG("openDB failed:"<<path);
        delete pDb;
        return nullptr;
    }
    
    if (encryptKey != nullptr && strlen(encryptKey) > 0) {
#ifdef ENCODE_DATABASE
        int ret = pDb->encrypt(path);
        if (!ret) {
            TNMPLOG("encrypt failed:"<<path);
            delete pDb;
            return nullptr;
        }
#endif
    }
    
    CSqliteDB::dbConnMap[path] = pDb;
    
    return pDb;
}


CSqliteDB::CSqliteDB()
{
    mDB = NULL;
}

CSqliteDB::~CSqliteDB()
{
    close();
}

void sqlite_write_log(const char* log){
    if (log == nullptr || strlen(log) == 0){
        return;
    }
    
    TNMPLOG("sqlite_write_log:"<<log);
}

bool CSqliteDB::openDB (const char* path) {
    if (mDB != NULL) {
        return false;
    }
    
    sqlite_set_log_callback(sqlite_write_log);
    
    int ret = sqlite3_open(path, &mDB);
    
    if (ret != SQLITE_OK){
        TNMPLOG("can't open database:"<<sqlite3_errmsg(mDB));
        return false;
    }
    
    return true;
}

bool CSqliteDB::close() {
    if (mDB == NULL) {
        return false;
    }
    
    return sqlite3_close(mDB) == SQLITE_OK;
}

bool CSqliteDB::goodConnection(bool &existTable) {
    if (mDB == NULL) {
        return false;
    }
    
    CSqliteDBStatement *records = this -> execQuerySql("select name from sqlite_master where type='table'");
    string strTableName;
    if (records != NULL) {
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            strTableName += ",";
            strTableName += records->getString(0);
        }
        if (strTableName.length() > 0) {
            existTable = true;
        }
        delete records;
        return true;
    }
    
    return false;
}

bool CSqliteDB::encrypt (const char* path) {
    bool existTable = false;
    bool isConnected = this->goodConnection(existTable);
    if (isConnected && existTable) {//有表格存在，说明之前的数据库未加密，需要处理数据并加密 wxy
        sqlite3_close(mDB);
        if (this->encryptDatabase(path, toonim::CTNDBUtils::generateEncryptKey(_userId).c_str()) == false) {
            TNMPLOG("can't encrypt a plaintext database:"<<sqlite3_errmsg(mDB));
            return false;
        }
        sqlite3_open(path, &mDB);
        
        return this->goodSetKey(path);
    }else {
        return this->goodSetKey(path);
    }
}

bool CSqliteDB::goodSetKey(const char* path) {
    this->setKey(toonim::CTNDBUtils::generateEncryptKey(_userId).c_str());
    bool exitTable = false;
    if (this->goodConnection(exitTable)) {
        sqlite3_exec(mDB, "PRAGMA auto_vacuum = 0", NULL, NULL, NULL);
        sqlite3_exec(mDB, "PRAGMA cache_size = 8000", NULL, NULL, NULL);
        //安卓强杀进程会出现数据库文件损坏，目前注释
//        sqlite3_exec(mDB, "PRAGMA page_size = 16384", NULL, NULL, NULL);
        sqlite3_exec(mDB, "PRAGMA synchronous = FULL", NULL, NULL, NULL);
        sqlite3_exec(mDB, "PRAGMA temp_store = MEMORY", NULL, NULL, NULL);
        return true;
    }
    
    for (int i = 0; i < 3; i++) {
        sqlite3_close(mDB);
        sqlite3_open(path, &mDB);
        this->setKey(toonim::CTNDBUtils::generateEncryptKey(_userId).c_str());
        if (this->goodConnection(exitTable)) {
            sqlite3_exec(mDB, "PRAGMA auto_vacuum = 0", NULL, NULL, NULL);
            sqlite3_exec(mDB, "PRAGMA cache_size = 8000", NULL, NULL, NULL);
            //安卓强杀进程会出现数据库文件损坏，目前注释
//            sqlite3_exec(mDB, "PRAGMA page_size = 16384", NULL, NULL, NULL);
            sqlite3_exec(mDB, "PRAGMA synchronous = FULL", NULL, NULL, NULL);
            sqlite3_exec(mDB, "PRAGMA temp_store = MEMORY", NULL, NULL, NULL);

            return true;
        }
        tn_msleep(300);
    }
    return false;
}

bool CSqliteDB::setKey (const char* key) {
    if (key == nullptr || key[0] == '\0') {
        return false;
    }
    //数据库加密
#ifdef SQLITE_HAS_CODEC
    int rc = sqlite3_key(mDB, key, (int)strlen(key));
    if (rc != SQLITE_OK) {
        TNMPLOG("sqlite setKey failed code:" << sqlite3_system_errno(mDB)<< ", errmsg:" << sqlite3_errmsg(mDB));
    }
    
    return (rc == SQLITE_OK);
#else
    
    return false;
#endif
}

bool CSqliteDB::encryptDatabase(const char* path, const char* key) {
    if (key == nullptr || strlen(key) == 0) {
        return false;
    }
    std::string targetPath = path;
    targetPath += ".tmp.db";
    
    std::ostringstream s;
    s << "ATTACH DATABASE '" << targetPath << "' AS encrypted KEY '" << key  << "';";
    std::string sql = s.str();
    const char* sqlQ = sql.c_str();
    
    sqlite3 *unencrypted_DB;
    if (sqlite3_open(path, &unencrypted_DB) == SQLITE_OK) {
        
        // Attach empty encrypted database to unencrypted database
        sqlite3_exec(unencrypted_DB, sqlQ, NULL, NULL, NULL);
        
        // export database
        sqlite3_exec(unencrypted_DB, "SELECT sqlcipher_export('encrypted');", NULL, NULL, NULL);
        
        // Detach encrypted database
        sqlite3_exec(unencrypted_DB, "DETACH DATABASE encrypted;", NULL, NULL, NULL);
        
        sqlite3_close(unencrypted_DB);
        
        if (remove(path) != 0) {//如果成功，则返回零。如果错误，则返回 -1，并设置 errno
            return false;
        }
        if (rename(targetPath.c_str(), path) == 0) {
            return true;
        }else{
            return false;
        }
    }else {
        return false;
    }
}

bool CSqliteDB::unEncryptDatabase(const char* path, const char* key) {
    if (key == nullptr || strlen(key) == 0) {
        return false;
    }
    std::string targetPath = path;
    targetPath += ".tmp.db";
    
    std::ostringstream s;
    s << "ATTACH DATABASE '" << targetPath << "' AS plaintext KEY '';";
    std::string sql = s.str();
    const char* sqlQ = sql.c_str();
    
    std::ostringstream keyS;
    keyS << "PRAGMA key = '" << key  << "';";
    std::string keySql = keyS.str();
    const char* keySqlQ = keySql.c_str();
    
    sqlite3 *encrypted_DB;
    if (sqlite3_open(path, &encrypted_DB) == SQLITE_OK) {
        
        sqlite3_exec(encrypted_DB, keySqlQ, NULL, NULL, NULL);
        
        // Attach empty unencrypted database to encrypted database
        sqlite3_exec(encrypted_DB, sqlQ, NULL, NULL, NULL);
        
        // export database
        sqlite3_exec(encrypted_DB, "SELECT sqlcipher_export('plaintext');", NULL, NULL, NULL);
        
        // Detach encrypted database
        sqlite3_exec(encrypted_DB, "DETACH DATABASE plaintext;", NULL, NULL, NULL);
        
        sqlite3_close(encrypted_DB);
        
        if (remove(path) != 0) {//如果成功，则返回零。如果错误，则返回 -1，并设置 errno
            return false;
        }
        
        if (rename(targetPath.c_str(), path) == 0) {
            return true;
        }else{
            return false;
        }
    }else {
        return false;
    }
}

bool CSqliteDB::execSql(const char *sql) {
    int result;
    char* err = NULL;
    
    if (sql == nullptr) {
        return false;
    }
    
    std::unique_lock<std::mutex> unilock(m_mutex);
    result = sqlite3_exec(mDB, sql, NULL, NULL, &err);
    
    if (result != SQLITE_OK) {
//        TNMPLOG("database SQL execute failed:" << sql << ",error coude:" << result << ",error reaseon:" << (err ? err : ""));
        if (result != 19) {
            TNMPLOG("database SQL execute failed(not SQLITE_CONSTRAINT):" << sql << ",error coude:" << result << ",error reaseon:" << (err ? err : ""));
        }
        sqlite3_free(err);
        return false;
    }
    
//    TNMPLOG("execute SQL succeed\n" << sql);
    
    return true;
}

int CSqliteDB::getChangedCount() {
    return sqlite3_changes(mDB);
}

int CSqliteDB::execSqlTransaction(std::vector<std::string> vecSql) {
    int result;
    char* err = NULL;
    
    if(NULL == mDB)
        return -1;
    std::unique_lock<std::mutex> unilock(m_mutex);
    result = sqlite3_exec(mDB,"BEGIN TRANSACTION", NULL,NULL, &err);
    if(result != SQLITE_OK)
    {
        TNMPLOG("result = " << result << ", BEGIN TRANSACTION err: " << (err == NULL?"":err));
    }
    
    std::vector<string>::iterator iter = vecSql.begin();
    
    while( vecSql.end() != iter)
    {
//        TNMPLOG("sql:" << (*iter));
        result += sqlite3_exec(mDB, iter->c_str(), 0, 0, &err);
        if(SQLITE_OK != result)
        {
            TNMPLOG("ret = " << result << ", sql: " << iter->c_str() << " err:" << (err == NULL?"":err));
            break;
        }
        
        iter++;
    }
    if(result == SQLITE_OK)
    {
        result=sqlite3_exec(mDB,"COMMIT TRANSACTION", NULL,NULL, &err);
        if(result != SQLITE_OK)
        {
            TNMPLOG("ret = " << result << ", COMMIT TRANSACTION, err:" << (err == NULL?"":err));
        }
    }
    else
    {
        result = sqlite3_exec(mDB,"ROLLBACK TRANSACTION", NULL,NULL, &err);
        if(result != SQLITE_OK)
        {
            TNMPLOG("ret = " << result << ", ROLLBACK TRANSACTION, err:" << (err == NULL?"":err));
        }
        sqlite3_free(err);
        return -2;
    }
    sqlite3_free(err);

    return result;
}

void CSqliteDB::makeFunction(const char *name,void (*xSFunc)(sqlite3_context*,int,sqlite3_value **), int nArg)
{
    if (name == nullptr || strlen(name) == 0 || mDB == nullptr) {
        return;
    }
    
    std::unique_lock<std::mutex> unilock(m_mutex);
    sqlite3_create_function(mDB, name, nArg, SQLITE_UTF8, NULL, xSFunc, NULL, NULL);
}

//bool CSqliteDB::statement(const char *sql, IDBDelegate *deli, IObject *param) {
//    sqlite3_stmt* stmt;
//    
//    if (SQLITE_OK != sqlite3_prepare(mDB, sql, -1, &stmt, NULL)) {
//        TNMPLOG("prepare failed,sql:" << sql << "err: " << sqlite3_errmsg(mDB));
//        return false;
//    }
//    TNMPLOG("sql:%s\n" << sql);
//    
////    CSqliteDBStatement* dbStmt = new CSqliteDBStatement(mDB, stmt);
//    
////    dbStmt->addRef();
//    deli->onDo(dbStmt, param);
////    dbStmt->release();
//    return true;
//}

//bool CSqliteDB::execSqlTransaction(const char *sql, IDBDelegate *deli, IObject *param) {
//    
//    TNMPLOG("transaction sql:%s\n" << sql);
//    
//    this->execSql("BEGIN TRANSACTION");
//    statement(sql, deli, param);
//    this->execSql("COMMIT TRANSACTION");
//    
//    return true;
//}

//需要处理回滚操作 rollback transaction
//bool CSqliteDB::execSqlAssociateOper(const char** sqls, IDBDelegate *deli, IObject *param) {
//    TNMPLOG("exec associate sqls");
//    
//    this->execSql("BEGIN TRANSATION");
//    
//    bool noErr = true;
//    
//    for (int i = 0; sqls[i] != NULL && noErr; ++i) {
//        sqlite3_stmt* stmt = NULL;
//        
//        if (SQLITE_OK != sqlite3_prepare(mDB, sqls[i], -1, &stmt, NULL)) {
//            TNMPLOG("associate sql:" << sqls[i] << "errors:" << sqlite3_errmsg(mDB));
//            break;
//        }
//        
//        TNMPLOG("associate sql:" << sqls[i]);
//
//        CSqliteDBStatement* dbStmt = new CSqliteDBStatement(mDB, stmt);
//        dbStmt->addRef();
//        noErr = deli->onDoAssociSql(dbStmt, param, i);
//        dbStmt->release();
//    }
//    
//    execSQL("COMMIT TRANSACTION");
//    
//    return false;
//}

CSqliteDBStatement* CSqliteDB::execQuerySql(const char* sql) {
    
    sqlite3_stmt* stmt;
    
    if(sql == nullptr) {
        return nullptr;
    }//sqlite3_prepare
//    sqlite3_exec(mDB, "BEGIN", 0, 0, NULL);
    if (SQLITE_OK != sqlite3_prepare_v2(mDB, sql, -1, &stmt, NULL)) {
        TNMPLOG("prepare failed,sql:" << sql << "err: " << sqlite3_errmsg(mDB));
        return nullptr;
    }
//    TNMPLOG("sql:" << sql);
    
    //需要外部是否，最好修改成对象 add by lanhuaiyu
    CSqliteDBStatement* dbStmt = new CSqliteDBStatement(mDB, stmt);

    return dbStmt;
}

int32_t CSqliteDB::getDbErr(const char *err){
    std::unique_lock<std::mutex> unilock(m_mutex);
    err = sqlite3_errmsg(mDB);
    return sqlite3_errcode(mDB);
}

bool CSqliteDB::existTableOrColom(const char *tableName, const char *columName, const char* dbName){
    
    if (nullptr != tableName && tableName[0] != '\0' && nullptr != columName && columName[0] != '\0') {
        std::string querySql = "PRAGMA ";
        
        if (dbName != nullptr && dbName[0] != '\0') {
            querySql.append(dbName);
            querySql.append(".");
        }
        
        querySql.append("table_info(");
        querySql.append(tableName);
        querySql.append(")");
        
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(querySql.c_str());
        if (nullptr == records) {
            return false;
        }
        
        std::string queryColomName;
        bool found = false;
        
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            queryColomName = records->getString(1);//第2列为表格名字
            if (queryColomName == columName) {
                found = true;
            }
        }
        
        return found;
    }else if (nullptr != tableName && tableName[0] != '\0' && columName == nullptr){
        std::string querySql = "select name from ";
        
        if (dbName != nullptr && dbName[0] != '\0') {
            querySql.append(dbName);
            querySql.append(".");
        }
        
        querySql.append("sqlite_master where name='");
        querySql.append(tableName);
        
        querySql.append("'");
        
        CQIPtr<CSqliteDBStatement, QI_NEW> records = this->execQuerySql(querySql.c_str());
        if (nullptr == records) {
            return false;
        }
        
        while (records->step() == CSqliteDBStatement::STEP_ROW) {
            if (!strcmp(records->getString(0), tableName)) {
                return true;
            }
        }
    }
    
    return false;
}

CSqliteDBStatement::CSqliteDBStatement (sqlite3* db, sqlite3_stmt* stmt) {
    mDB = db;
    mStmt = stmt;
}

CSqliteDBStatement::~CSqliteDBStatement () {
    if (mStmt == NULL) {
        return;
    }
    sqlite3_finalize(mStmt);
//    sqlite3_exec(mDB, "COMMIT", 0, 0, NULL);
}

void CSqliteDBStatement::bindInt(int index, int val) {
//    sqlite3_bind_int64(mStmt, index, val);
    sqlite3_bind_int(mStmt, index, val);
}

void CSqliteDBStatement::bindLong(int index, int64_t val) {
    sqlite3_bind_int64(mStmt, index, val);
}

void CSqliteDBStatement::bindBlob (int index, int len, const unsigned char* blob) {
    sqlite3_bind_blob(mStmt, index, blob, len, SQLITE_STATIC);
}

void CSqliteDBStatement::bindString (int index, int len, const char* str) {
    sqlite3_bind_text(mStmt, index, str, len, SQLITE_STATIC);
}

void CSqliteDBStatement::bindDouble (int index, double val) {
    sqlite3_bind_double(mStmt, index, val);
}

int CSqliteDBStatement::getInt (int index) {
    return sqlite3_column_int(mStmt, index);
}

int64_t CSqliteDBStatement::getLong (int index) {
    return sqlite3_column_int64(mStmt, index);
    
}

const void* CSqliteDBStatement::getBlob (int index, int* size) {
    *size = sqlite3_column_bytes(mStmt, index);
    return sqlite3_column_blob(mStmt, index);
}

const char* CSqliteDBStatement::getString (int index) {
    const unsigned char* str = sqlite3_column_text(mStmt, index);
    
    if (str == NULL) {
        return "";
    }
    
    return (const char*)str;
}

double CSqliteDBStatement::getDouble (int index) {
    return sqlite3_column_double(mStmt, index);
}

int CSqliteDBStatement::step () {
    return sqlite3_step(mStmt);
}

void CSqliteDBStatement::clearBinding () {
    sqlite3_clear_bindings(mStmt);
    sqlite3_reset(mStmt);
}

//返回操作改变的行数
long CSqliteDBStatement::getChangeCount () {
    return sqlite3_changes(mDB);
}

