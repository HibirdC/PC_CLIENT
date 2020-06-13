#include "TNBaseTable.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include "ConnectionPool.h"
TNBaseTable::TNBaseTable() :_db(NULL)
{
    _tableExist = false;
}

TNBaseTable::~TNBaseTable()
{

}

bool TNBaseTable::beginTransaction()
{
   //_poolDb = ConnectionPool::openConnection();
   return _db->transaction();
}

bool TNBaseTable::commitTransaction()
{
	bool bRet = _db->commit();
   if (!bRet)
   {
	   _db->rollback();
        //qDebug()<<"commit failed:"<<_db->lastError();
   }
   //ConnectionPool::closeConnection(_poolDb);
   return bRet;
}

/**
 * 判断某张表是否存在
 * @param tabName 表名
 * @return
 */
bool TNBaseTable::tableIsExist(QString tableName)
{
    //如果已经存在，则不判断
    if (_tableExist)
    {
        return true;
    }
    bool result = false;
    if(tableName.length() == 0)
    {
		return result;
    }
    QSqlQuery  query(*_db);
    QString sql = "select count(*) as c from Sqlite_master  where type ='table' and name ='"+tableName+"' ";
    if (!query.exec(sql))
    {
		return result;
    }
    if (query.next())
    {
        QSqlRecord record = query.record();
        int nCount = record.value(0).toInt();
        if (nCount > 0)
        {
            result = true;
        }
    }

    _tableExist = result;
    return result;
}

bool TNBaseTable::keyIsExist(const QString& tableName, const QString& key, const QString& Value)
{
	bool result = false;
	if (tableName.isEmpty() || key.isEmpty())
	{
		return result;
	}
	QSqlQuery  query(*_db);
    QString sql = QString("select * from %1  where %2 ='%3'").arg(tableName).arg(key).arg(Value);
	bool ret = query.exec(sql);
	if (ret && query.next())
	{
		result = true;
	}
	return result;
}

void TNBaseTable::SetDBConnect(QSqlDatabase* dbConnect)
{
	this->_db = dbConnect;
}
