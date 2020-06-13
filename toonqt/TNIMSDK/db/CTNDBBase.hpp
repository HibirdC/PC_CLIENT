//
//  CTNDBBase.hpp
//  DATABASE
//
//  Created by 王旭影 on 17/8/24.
//  Copyright © 2017年 syswin. All rights reserved.
//

#ifndef CTNDBBase_hpp
#define CTNDBBase_hpp

#include <stdio.h>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include "CSqliteDB.hpp"

using namespace std;

#define IMCHATDB            "/imchat"
#define IMGROUPCHATDB       "/imgroupchat"

//pointer wrapper
typedef enum{QI_MALLOC, QI_NEW} QIPTRMALLOCTYPE;
template <class T, QIPTRMALLOCTYPE ptrmalloctype=QI_MALLOC>
class CQIPtr
{public:
    CQIPtr(T* p=0)         { m_p = p;               }    operator T*()          { return m_p;            }    T&   operator*() const { return *m_p;           }    T**  operator&()       { return &m_p;           }    bool operator!() const { return (m_p == NULL);  }    T*   operator->()const { return m_p;            }    T*   operator=(T* p)   { m_p = p; return m_p;   }    void Free()            { if(m_p) { if (ptrmalloctype == QI_NEW) delete(m_p);    else free(m_p); } m_p=0; }    ~CQIPtr()              { Free(); }
    private:
    T* m_p;
};

//class CSqliteDB;

/*
 * 表格操作基类定义，绑定到安全操作数据库类
 */
class CTNDBBase {
public:
    enum FT
    {
        DB_INT,     //virtual void bindInt (int index, int val);
        DB_LONG,    //virtual void bindLong (int index, int64_t val);
        DB_DOUBLE,  //virtual void bindDouble (int index, double val);
        DB_STR,     //virtual void bindString (int index, int len, const char* str);
        DB_BLOB     //virtual void bindBlob (int index, int len, const unsigned char* blob);        
    };
    typedef std::map<std::string, std::pair<FT, std::string> > RECORD_DATA;;
    typedef std::vector<std::pair<FT, std::string> > RECORD_VALUE;
    void doInitUserDB(const std::string& clientId, const std::string& name, const std::string& appPath);
    virtual string getDBFileName(const std::string &name);
    sqlite3* getDB();
    string getClientId();
    
    
    string valueToEscapedString ( const char *value );
    string escapeString (const string& sFrom);
    
    /**
     * Update Record
     * @param sTableName : 表名
     * @param mpColumns : 列名/值对
     * @param sCondition : where子语句,例如:where A = B
     * @throws TC_Mysql_Exception
     * @return size_t 影响的行数
     */
    size_t updateRecord(const string &sTableName, const RECORD_DATA &mpColumns, const string &sCondition);
    
    /**
     * insert Record
     * @param sTableName : 表名
     * @param mpColumns : 列名/值对
     * @throws TC_Mysql_Exception
     * @return size_t 影响的行数
     */
    size_t insertRecord(const string &sTableName, const RECORD_DATA &mpColumns);
    
    /**
     * replace Record
     * @param sTableName : 表名
     * @param mpColumns : 列名/值对
     * @throws TC_Mysql_Exception
     * @return size_t 影响的行数
     */
    size_t replaceRecord(const string &sTableName, const RECORD_DATA &mpColumns);
    
    /**
     * Delete Record
     * @param sTableName : 表名
     * @param sCondition : where子语句,例如:where A = B
     * @throws TC_Mysql_Exception
     * @return size_t 影响的行数
     */
    size_t deleteRecord(const string &sTableName, const string &sCondition = "");
    
    /**
     * 获取Table查询结果的数目
     * @param sTableName : 用于查询的表名
     * @param sCondition : where子语句,例如:where A = B
     * @throws TC_Mysql_Exception
     * @return size_t 查询的记录数目
     */
    size_t getRecordCount(const string& sTableName, const string &sCondition = "");
    
    /**
     * 获取Sql返回结果集的个数
     * @param sCondition : where子语句,例如:where A = B
     * @throws TC_Mysql_Exception
     * @return 查询的记录数目
     */
    size_t getSqlCount(const string &sCondition = "");
    
    /**
     * 存在记录
     * @param sql 需要判断记录是否存在的SQL语句
     * @throws TC_Mysql_Exception
     * @return bool
     */
    bool existRecord(const string& sql);
    
    /**
     * 获取字段最大值
     * @param sTableName : 用于查询的表名
     * @param sFieldName : 用于查询的字段
     * @param sCondition : where子语句,例如:where A = B
     * @throws TC_Mysql_Exception
     * @return 查询的记录数目
     */
    int getMaxValue(const string& sTableName, const string& sFieldName, const string &sCondition = "");
    
    /**
     * 获取auto_increment最后插入得ID
     * @return ID值
     */
    long lastInsertID();
    
    /**
     * 构造Insert-SQL语句
     * @param sTableName : 表名
     * @param mpColumns : 列名/值对
     * @return string insert-SQL语句
     */
    virtual string buildInsertSQL(const string &sTableName, const RECORD_DATA &mpColumns);
    
    /**
     * 构造Replace-SQL语句
     * @param sTableName : 表名
     * @param mpColumns : 列名/值对
     * @return string insert-SQL语句
     */
    virtual string buildReplaceSQL(const string &sTableName, const RECORD_DATA &mpColumns);
    
    /**
     * 构造Update-SQL语句
     * @param sTableName : 表名
     * @param mpColumns : 列名/值对
     * @param sCondition : where子语句
     * @return string Update-SQL语句
     */
    virtual string buildUpdateSQL(const string &sTableName,const RECORD_DATA &mpColumns, const string &sCondition);
    
    /**
     * 获取最后执行的SQL语句
     *
     * @return string
     */
    string getLastSQL() { return _sLastSql; }
    
    CTNDBBase ();

    virtual ~CTNDBBase ();
//    ISafeDB* getDB () { return mDb; }
    
    /*
     * 数据库一条记录
     */
    class TNDBRecord
    {
    public:
        /**
         * 构造函数
         * @param record 记录数据
         */
        TNDBRecord(const map<string, string> &record);
        
        /**
         * 获取数据
         * @param s 记录关键字
         *
         * @return string
         */
        const string operator[](const string &s);
    protected:
        const map<string, string> &_record;
    };
    
    /**
     * 查询出的数据库数据
     */
    class TNDBData
    {
    public:
        /**
         * 所有数据
         *
         * @return vector<map<string,string>>&
         */
        vector<map<string, string> >& data();
        
        /**
         *  数据的记录条数
         *
         * @return size_t
         */
        size_t size();
        
        /**
         * 获取某一条记录
         * @param i 记录的位置
         *
         * @return TNDBRecord
         */
        TNDBRecord operator[](size_t i);
        
    protected:
        vector<map<string, string> > _data;
    };
    
    /**
     * Query Record
     * @param sSql : sql语句
     * @throws TC_Mysql_Exception
     * @return MysqlData
     */
    TNDBData queryRecord(const string& sSql);
    
protected:
//    Pointer<ISafeDB> mDb;//便于子类访问
    
    /**
     * copy contructor
     * 只申明,不定义,保证不被使用
     */
    CTNDBBase(const CTNDBBase &myDB);
    
    virtual void createTable() = 0;
    
    /**
     * =
     * 只申明,不定义,保证不被使用
     */
    CTNDBBase &operator=(const CTNDBBase &tcMysql);

    void checkDBUpgrade();
    bool execSql(const char *sql);
    void beginTransation();
    void commitTransation();
    
  
    CQIPtr<CSqliteDBStatement, QI_NEW> execQuerySql(const char *sql);
    int execSqlTransaction(std::vector<std::string> vecSql);
    
    virtual void upgradeTableWithOldVersion(){};

private:
    /**
     * 最后执行的sql
     */
    string      _sLastSql;
    
protected:
    string _clientId;
    string _appPath;
    string _dbName;
    
//    std::string _dbFile;
    
    CSqliteDB* _sqliteDb;
    std::mutex m_mutex;
    
    int32_t getDbErr(const char *err);
};

#endif /* CTNDBBase_hpp */
