//
//  CSqliteDB.hpp
//  sqlite3
//
//  Created by 王旭影 on 17/8/19.
//  Copyright © 2017年 思源. All rights reserved.
//

#ifndef CSqliteDB_hpp
#define CSqliteDB_hpp

#include <stdio.h>
//#include "IDB.hpp"
#include "sqlite3.h"
//#include "RefCount.h"
#include <vector>
#include <string>
#include <mutex>
#include <condition_variable>
#include <map>

#define DEFAULTENCRYPTKEY "syswin"

class  CSqliteDBStatement;
struct DBQueryData {
    char** dbResult;
    int nRow;
    int nColum;
    char* errMsg;
    int result;
};

class CSqliteDB
{
//    sqlite3* mDB;
    std::mutex m_mutex;
    static std::map<std::string, CSqliteDB*> dbConnMap;//有内存泄露 wxy  CSafeMap
    static std::mutex sMutex;
    std::string _userId;
    
public:
    sqlite3* mDB;
    CSqliteDB();
    ~CSqliteDB();
    
    static CSqliteDB* getDb(const char* path, const char* tag, const char* userId, const char* encryptKey);
    static void reset();
    
    virtual bool openDB (const char* path);
    virtual bool close ();
    virtual bool goodConnection(bool &existTable);
    
    virtual bool encrypt(const char* path);
    virtual bool goodSetKey(const char* path);
    virtual bool setKey (const char* key);
    virtual bool encryptDatabase(const char* path, const char* key);//对已有未加密数据库进行加密
    virtual bool unEncryptDatabase(const char* path, const char* key);//对已有加密数据库进行解密
    
    virtual bool execSql (const char* sql);
    virtual int getChangedCount();
    int execSqlTransaction(std::vector<std::string> vecSql);
    void makeFunction(const char *name,void (*xSFunc)(sqlite3_context*,int,sqlite3_value **), int nArg = -1);
    
    virtual CSqliteDBStatement* execQuerySql (const char* sql);
    int32_t getDbErr(const char* err);
    bool existTableOrColom(const char* tableName, const char* columName,const char* dbName = nullptr);//仅查询表格是否存在，columName设置为空即可
};

class CSqliteDBStatement// : public IDBStatement
{
    sqlite3_stmt* mStmt;
    sqlite3* mDB;
    
public:
    enum {STEP_ROW = 100, STEP_DONE = 101};
    
    CSqliteDBStatement (sqlite3* db, sqlite3_stmt* stmt);
    ~CSqliteDBStatement ();
    
    //引用计数实现，可以后期定义为宏
//    RefCount mRef;
//    virtual void addRef () { mRef.increse(); }
//    virtual void release () {
//        if ( !mRef.decrease()) {delete this;}
//        }
//    
    virtual void bindInt (int index, int val);
    virtual void bindLong (int index, int64_t val);
    virtual void bindBlob (int index, int len, const unsigned char* blob);
    virtual void bindString (int index, int len, const char* str);
    virtual void bindDouble (int index, double val);
    
    virtual int getInt (int index);
    virtual int64_t getLong (int index);
    virtual const void* getBlob (int index, int* size);
    virtual const char* getString (int index);
    virtual double getDouble (int index);
    
    virtual int step ();
    virtual void clearBinding ();
    //返回操作改变的行数
    virtual long getChangeCount ();
};

#endif /* CSqliteDB_hpp */
