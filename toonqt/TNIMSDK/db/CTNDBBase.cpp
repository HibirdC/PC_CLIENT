//
//  CTNDBBase.cpp
//  DATABASE
//
//  Created by 王旭影 on 17/8/24.
//  Copyright © 2017年 syswin. All rights reserved.
//

#include "CTNDBBase.hpp"
#include <CLog.h>
#include <stdlib.h>
#include <string.h>
#include "CTNDBUtils.hpp"
#include "CTNDBHeader.h"

#ifdef WIN32
#include <Windows.h>

#define snprintf _snprintf
#else
#include <unistd.h>
#endif

#define DB_NAME(path, name, clientId)     (path + name +clientId+".db")

CTNDBBase::CTNDBBase(){
    _sqliteDb = nullptr;
}

CTNDBBase::~CTNDBBase () {
    
}

string CTNDBBase::getDBFileName(const std::string &name)
{
    string dbFile = DB_NAME(_appPath, name, _clientId);
    return dbFile;
}

sqlite3* CTNDBBase::getDB() {
    return _sqliteDb->mDB;
}

string CTNDBBase::getClientId(){
    return _clientId;
}

void CTNDBBase::doInitUserDB(const std::string& clientId, const std::string& name, const std::string& appPath)
 {
    if (appPath.length() == 0 || clientId.length() == 0){
//        TNMPLOG("dbFile path or clientId is empty!!!!!");
        return;
    }
     
     if (clientId == _clientId && name == _dbName){
         return;
     }
    
     _clientId = clientId;
     _appPath = appPath;
     _dbName = name;
     
    string dbFile = this->getDBFileName(name);
     
     //wangxuying 暂时用该方法获取数据库连接对象，三个表格分别打开同一个数据库的三个连接容易出现其中一个执行写操作遇到其他的数据库连接锁住的状态，造成错误码为5的现象，回头还可以调整该方案，暂时做此修改
     _sqliteDb = CSqliteDB::getDb(dbFile.c_str(), "", _clientId.c_str(), toonim::CTNDBUtils::generateEncryptKey(_clientId).c_str());
     if (_sqliteDb == nullptr){
         TNMPLOG("@@@@$$$$$ OPEN DB failed:"<<dbFile);
     }
     
     this->createTable();
     TNMPLOG("open db:"<<dbFile);
     
     this->upgradeTableWithOldVersion();
}

bool CTNDBBase::execSql(const char *sql)
{
    if (sql == NULL || strlen(sql) == 0){
        return  false;
    }
    
    if (_sqliteDb == nullptr){
        return false;
    }

    return _sqliteDb->execSql(sql);
}

int CTNDBBase::execSqlTransaction(std::vector<std::string> vecSql)
{
    if (vecSql.size() == 0){
        return  -1;
    }
    
    if (_sqliteDb == NULL){
        return -1;
    }
    
    return _sqliteDb->execSqlTransaction(vecSql);
}

void CTNDBBase::beginTransation()
{
    m_mutex.lock();
    this->execSql("BEGIN TRANSACTION");
}

void CTNDBBase::commitTransation()
{
    this->execSql("COMMIT TRANSACTION");
    m_mutex.unlock();
}

CQIPtr<CSqliteDBStatement, QI_NEW> CTNDBBase::execQuerySql(const char *sql)
{
    if (sql == NULL || strlen(sql) == 0){
        return  nullptr;
    }
    
    if (_sqliteDb == nullptr){
        return nullptr;
    }
    
    return _sqliteDb->execQuerySql(sql);
}

std::string CTNDBBase::buildInsertSQL (const std::string &sTableName, const RECORD_DATA &mpColumns) {
    
    std::ostringstream sColumnNames;
    ostringstream sColumnValues;

    map<string, pair<FT, string> >::const_iterator itEnd = mpColumns.end();

    for(map<string, pair<FT, string> >::const_iterator it = mpColumns.begin(); it != itEnd; ++it)
    {
        if (it == mpColumns.begin())
        {
            sColumnNames << "'" << it->first << "'";
            if(it->second.first == DB_INT || it->second.first == DB_LONG || it->second.first == DB_DOUBLE)
            {
                sColumnValues << it->second.second;
            }
            else
            {
                sColumnValues << "'" << escapeString(it->second.second) << "'";
            }
        }
        else
        {
            sColumnNames << ",'" << it->first << "'";
            if(it->second.first == DB_INT || it->second.first == DB_LONG || it->second.first == DB_DOUBLE)
            {
                sColumnValues << "," + it->second.second;
            }
            else
            {
                sColumnValues << ",'" + escapeString(it->second.second) << "'";
            }
        }
    }

    ostringstream os;
    os << "insert into " << sTableName << " (" << sColumnNames.str() << ") values (" << sColumnValues.str() << ")";
    return os.str();
}

std::string CTNDBBase::buildReplaceSQL (const string &sTableName, const RECORD_DATA &mpColumns) {
    ostringstream sColumnNames;
    ostringstream sColumnValues;

    map<string, pair<FT, string> >::const_iterator itEnd = mpColumns.end();
    for(map<string, pair<FT, string> >::const_iterator it = mpColumns.begin(); it != itEnd; ++it)
    {
        if (it == mpColumns.begin())
        {
            sColumnNames << "'" << it->first << "'";
            if(it->second.first == DB_INT || it->second.first == DB_LONG || it->second.first == DB_DOUBLE)
            {
                sColumnValues << it->second.second;
            }
            else
            {
                sColumnValues << "'" << escapeString(it->second.second) << "'";
            }
        }
        else
        {
            sColumnNames << ",`" << it->first << "`";
            if(it->second.first == DB_INT || it->second.first == DB_LONG || it->second.first == DB_DOUBLE)
            {
                sColumnValues << "," + it->second.second;
            }
            else
            {
                sColumnValues << ",'" << escapeString(it->second.second) << "'";
            }
        }
    }

    ostringstream os;
    os << "replace into " << sTableName << " (" << sColumnNames.str() << ") values (" << sColumnValues.str() << ")";
    return os.str();
}

string CTNDBBase::buildUpdateSQL(const string &sTableName,const RECORD_DATA &mpColumns, const string &sWhereFilter)
{
    ostringstream sColumnNameValueSet;

    map<string, pair<FT, string> >::const_iterator itEnd = mpColumns.end();

    for(map<string, pair<FT, string> >::const_iterator it = mpColumns.begin(); it != itEnd; ++it)
    {
        if (it == mpColumns.begin())
        {
            sColumnNameValueSet << "'" << it->first << "'";
        }
        else
        {
            sColumnNameValueSet << ",'" << it->first << "'";
        }

        if(it->second.first == DB_INT || it->second.first == DB_LONG || it->second.first == DB_DOUBLE)
        {
            sColumnNameValueSet << "= " << it->second.second;
        }
        else
        {
            sColumnNameValueSet << "= '" << escapeString(it->second.second) << "'";
        }
    }
    
    ostringstream os;
    os << "update " << sTableName << " set " << sColumnNameValueSet.str() << " " << sWhereFilter;

    return os.str();
}


//static inline bool isControlCharacter(char ch);
//
//static bool containsControlCharacter( const char* str )
//{
//    while ( *str )
//    {
//        if ( isControlCharacter( *(str++) ) )
//            return true;
//    }
//    return false;
//}

//static inline bool
//isControlCharacter(char ch)
//{
//    return ch > 0 && ch <= 0x1F;
//}

string CTNDBBase::valueToEscapedString ( const char *value )
{
    if (value == NULL)
        return "";
    // Not sure how to handle unicode...
//    if (strpbrk(value, "\"\\\b\f\n\r\t") == NULL && !containsControlCharacter( value ))
//     if (strpbrk(value, "/'[]%&_()") == NULL)
//        return std::string("\"") + value + "\"";
     if (strpbrk(value, "'") == NULL)
         return value;
    // We have to walk value and escape any special characters.
    // Appending to std::string is not efficient, but this should be rare.
    // (Note: forward slashes are *not* rare, but I am not escaping them.)
    std::string::size_type maxsize = strlen(value)*2 + 3; // allescaped+quotes+NULL
    std::string result;
    result.reserve(maxsize); // to avoid lots of mallocs
//    result += "\"";
    for (const char* c=value; *c != 0; ++c)
    {
        switch(*c)
        {
//            case '/':
//                result += "//";
//                break;
            case '\'':
                result += "''";
                break;
//            case '[':
//                result += "/[";
//                break;
//            case ']':
//                result += "/]";
//                break;
//            case '%':
//                result += "/%";
//                break;
//            case '&':
//                result += "/&";
//                break;
//            case '_':
//                result += "/_";
//                break;
//            case '(':
//                result += "/(";
//                break;
//            case ')':
//                result += "/)";
//                break;
            default:
//                if ( isControlCharacter( *c ) )
//                {
//                    std::ostringstream oss;
//                    oss << "\\u" << std::hex << std::uppercase << std::setfill('0') << setw(4) << static_cast<int>(*c);
//                    result += oss.str();
//                }
//                else
//                {
                    result += *c;
//                }
                break;
        }
    }
//    result += "\"";
    return result;
}

string CTNDBBase::escapeString (const string& sFrom) {
    
    string sTo;
//    mysql_real_escape_string(_pstMql, pTo, sFrom.c_str(), sFrom.length());
    sTo = valueToEscapedString(sFrom.c_str());
    
    return sTo;
}

size_t CTNDBBase::updateRecord(const string &sTableName, const RECORD_DATA &mpColumns, const string &sCondition)
{
    string sSql = buildUpdateSQL(sTableName, mpColumns, sCondition);

    if (this->execSql(sSql.c_str())) {
        return _sqliteDb->getChangedCount();
    } else {
        return -1;
    }
}

size_t CTNDBBase::insertRecord(const string &sTableName, const RECORD_DATA &mpColumns)
{
    string sSql = buildInsertSQL(sTableName, mpColumns);
    if (this->execSql(sSql.c_str())) {
        return _sqliteDb->getChangedCount();
    } else {
        return -1;
    }
}

size_t CTNDBBase::replaceRecord(const string &sTableName, const RECORD_DATA &mpColumns)
{
    string sSql = buildReplaceSQL(sTableName, mpColumns);
    
    if (this->execSql(sSql.c_str())) {
        return _sqliteDb->getChangedCount();
    } else {
        return -1;
    }
}

size_t CTNDBBase::deleteRecord(const string &sTableName, const string &sCondition)
{
    ostringstream sSql;
    sSql << "delete from " << sTableName << " " << sCondition;

    if (this->execSql(sSql.str().c_str())) {
        return _sqliteDb->getChangedCount();
    } else {
        return -1;
    }
}

size_t CTNDBBase::getRecordCount(const string& sTableName, const string &sCondition)
{
    ostringstream sSql;
    sSql << "select count(*) as num from " << sTableName << " " << sCondition;
    TNMPLOG(sSql.str())
    TNDBData data = queryRecord(sSql.str().c_str());
    long n = 0;

    try {
        n = atol(data[0]["num"].c_str());
    } catch (string e) {
        TNMPLOG("getRecordCount exception:" << e);
    }
    
    return n;
    
}

size_t CTNDBBase::getSqlCount(const string &sCondition)
{
    ostringstream sSql;
    sSql << "select count(*) as num " << sCondition;
    
    TNDBData data = queryRecord(sSql.str());
    
    long n = 0;
    
    try {
        n = atol(data[0]["num"].c_str());
    } catch (string e) {
        TNMPLOG("getRecordCount exception:" << e);
    }
    
    return n;
}

int CTNDBBase::getMaxValue(const string& sTableName, const string& sFieldName,const string &sCondition)
{
    ostringstream sSql;
    sSql << "select " << sFieldName << " as f from " << sTableName << " " << sCondition << " order by f desc limit 1";
    
    TNDBData data = queryRecord(sSql.str());
    
    int n = 0;
    
    if(data.size() == 0)
    {
        n = 0;
    }
    else
    {
        try {
            n = (int)atol(data[0]["f"].c_str());
        } catch (string e) {
            TNMPLOG("getRecordCount exception:" << e);
        }
    }
    
    return n;
}

bool CTNDBBase::existRecord(const string& sql)
{
    return queryRecord(sql).size() > 0;
}

long CTNDBBase::lastInsertID()
{
    return 0;//未完成 确定一下是否需要该接口
//    return mysql_insert_id(_pstMql);
}

CTNDBBase::TNDBData CTNDBBase::queryRecord(const string& sSql)
{
    TNDBData   data;
    
    /**
     没有连上, 连接数据库
     */
//    if(!_bConnected)
//    {
//        connect();
//    }
    
    _sLastSql = sSql;
    
//数据库断开连接重连机制需要后续考虑，或者加入到底层处理逻辑中 未处理
    //    int iRet = mysql_real_query(_pstMql, sSql.c_str(), sSql.length());
    //    if(iRet != 0)
    //    {
    //        /**
    //         自动重新连接
    //         */
    //        int iErrno = mysql_errno(_pstMql);
    //        if (iErrno == 2013 || iErrno == 2006)
    //        {
    //            connect();
    //            iRet = mysql_real_query(_pstMql, sSql.c_str(), sSql.length());
    //        }
    //    }
    //
    //    if (iRet != 0)
    //    {
    //        int iErrno = mysql_errno(_pstMql);
    //        throw TC_Mysql_Exception("[TC_Mysql::queryRecord]: mysql_query: [ " + sSql+" ] :" + string(mysql_error(_pstMql)), iErrno);
    //    }
    //
    //    MYSQL_RES *pstRes = mysql_store_result(_pstMql);
    //
    //    if(pstRes == NULL)
    //    {
    //        int iErrno = mysql_errno(_pstMql);
    //        throw TC_Mysql_Exception("[TC_Mysql::queryRecord]: mysql_store_result: " + sSql + " : " + string(mysql_error(_pstMql)), iErrno);
    //    }
    
    int result;
    char* errmsg = NULL;
    char** dbResult = nullptr; //是 char ** 类型，两个*号
    int nRow = 0, nColumn;
    int i, j;
    int index;
    
    //数据库操作代码
    //假设前面已经创建了 MyTable_1 表
    //开始查询，传入的 dbResult 已经是 char **，这里又加了一个 & 取地址符，传递进去的就成了 char ***
    result = sqlite3_get_table(getDB(), sSql.c_str(), &dbResult, &nRow, &nColumn, &errmsg);
    
    string strResult;
//    DBQueryData* queryData = this->execQuerySql(sSql.c_str());
    //查询成功
    if (SQLITE_OK == result) {
        vector<string> vtFields;
        int colNameIndex = 0;
        //存储查询结果列名称
        while (colNameIndex < nColumn) {//queryData->
            vtFields.push_back(dbResult[colNameIndex++]);//感觉此处重复存储 未处理
        }

        index = nColumn; //前面说过 dbResult 前面第一行数据是字段名称，从 nColumn 索引开始才是真正的数据
        
        TNMPLOG("queryed " << nRow << " record" );
        
        map<string, string> mpRow;
       
        for (i = 0; i < nRow; ++i) {
            TNMPLOG("the " << i << " record");
            mpRow.clear();
            for (j = 0; j < nColumn; ++j) {
                TNMPLOG("name:" << dbResult[j] << ", value:" << dbResult[index]);
                mpRow[vtFields[i]] = dbResult[index];
                index++; // dbResult 的字段值是连续的，从第0索引到第 nColumn - 1索引都是字段名称，从第 nColumn 索引开始，后面都是字段值，它把一个二维的表（传统的行列表示法）用一个扁平的形式来表示
            }
            data.data().push_back(mpRow);
        }
    }
    
    //到这里，不论数据库查询是否成功，都释放 char** 查询结果，使用 sqlite 提供的功能来释放
    sqlite3_free_table(dbResult);
//    delete queryData;
    return data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
CTNDBBase::TNDBRecord::TNDBRecord(const map<string, string> &record)
: _record(record)
{
}

const string CTNDBBase::TNDBRecord::operator[](const string &s)
{
    map<string, string>::const_iterator it = _record.find(s);
    if(it == _record.end())
    {
        throw "field '" + s + "' not exists.";
    }
    return it->second;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<map<string, string> >& CTNDBBase::TNDBData::data()
{
    return _data;
}

size_t CTNDBBase::TNDBData::size()
{
    return _data.size();
}

CTNDBBase::TNDBRecord CTNDBBase::TNDBData::operator[](size_t i)
{
    return TNDBRecord(_data[i]);
}
