#include <memory>

#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>


#include "TNNewFriend.h"
#include "common_global.h"
#include "ConnectionPool.h"

TNNewFriend::TNNewFriend() : TNBaseTable()
{
}

TNNewFriend::~TNNewFriend()
{
}

int TNNewFriend::InsertDatas(QList<TableBasePtr> stNewFriendList)
{
    int mCount = 0;
    if (!tableIsExist("NewFriend"))
    {
        return mCount;
    }
    bool ret = false;
    QList<TableBasePtr>::iterator it;
    beginTransaction();
    for (it = stNewFriendList.begin(); it != stNewFriendList.end(); it++)
    {
        st_NewFriendPtr stNewFriend = std::dynamic_pointer_cast<st_NewFriend>(*it);
        if (keyIsExist("NewFriend", "feed_belong", stNewFriend->getFeedBelong()))
        {
            QSqlQuery query(*_db);
            query.prepare(QString("UPDATE NewFriend SET isRead=?, mobilePhone=?, fromWhere=?, addComment=?, status=?, applyTime=?, expireTime=?"
                                  " where feed_belong='%1'").arg(stNewFriend->getFeedBelong()));

            query.bindValue(0, stNewFriend->getIsRead());
            query.bindValue(1, stNewFriend->getMobilePhone());
            query.bindValue(2, stNewFriend->getFromWhere());
            query.bindValue(3, stNewFriend->getAddComment());
            query.bindValue(4, stNewFriend->getStatus());
            query.bindValue(5, stNewFriend->getApplyTime());
            query.bindValue(6, stNewFriend->getExpireTime());
            ret = query.exec();
            if (!ret)
            {
                qDebug() << "update SQL Error NewFriend failed. error=" << query.lastError();
            }
            mCount = ret ? mCount + 1 : mCount;
        }
        else
        {
            QSqlQuery query(*_db);
            query.prepare("INSERT INTO NewFriend (isRead, feedId, myFeedId, mobilePhone, fromWhere, addComment, status, applyTime, expireTime, feed_belong) "
                          "VALUES (:isRead, :feedId, :myFeedId, :mobilePhone, :fromWhere, :addComment, :status, :applyTime, :expireTime, :feed_belong)");

            query.bindValue(":isRead", stNewFriend->getIsRead());
            query.bindValue(":feedId", stNewFriend->getFeedID());
            query.bindValue(":myFeedId", stNewFriend->getMyFeedID());
            query.bindValue(":mobilePhone", stNewFriend->getMobilePhone());
            query.bindValue(":fromWhere", stNewFriend->getFromWhere());
            query.bindValue(":addComment", stNewFriend->getAddComment());
            query.bindValue(":status", stNewFriend->getStatus());
            query.bindValue(":applyTime", stNewFriend->getApplyTime());
            query.bindValue(":expireTime", stNewFriend->getExpireTime());
            query.bindValue(":feed_belong", stNewFriend->getFeedBelong());

            ret = query.exec();
            if (!ret)
            {
                qDebug() << "INSERT SQL Error NewFriend failed. error=" << query.lastError();
            }
            mCount = ret ? mCount + 1 : mCount;
        }
    }
    commitTransaction();
    return mCount;
}

bool TNNewFriend::InsertDatas(st_NewFriendPtr stNewFriend)
{
    if (tableIsExist("NewFriend"))
    {
        if (keyIsExist("NewFriend", "feed_belong", stNewFriend->getFeedBelong()))
        {
            QSqlQuery query(*_db);
            query.prepare(QString("UPDATE NewFriend SET isRead=?, mobilePhone=?, fromWhere=?, addComment=?, status=?, applyTime=?, expireTime=?"
                                  " where feed_belong='%1'").arg(stNewFriend->getFeedBelong()));

            query.bindValue(0, stNewFriend->getIsRead());
            query.bindValue(1, stNewFriend->getMobilePhone());
            query.bindValue(2, stNewFriend->getFromWhere());
            query.bindValue(3, stNewFriend->getAddComment());
            query.bindValue(4, stNewFriend->getStatus());
            query.bindValue(5, stNewFriend->getApplyTime());
            query.bindValue(6, stNewFriend->getExpireTime());
            bool ret = query.exec();
            if (ret)
            {
                return true;
            }
            else
            {
                QString strLog = query.lastError().text();
                qDebug() << "UPDATE NewFriend FAIL" << strLog;
            }
        }
        else
        {
            QSqlQuery query(*_db);
            query.prepare("INSERT INTO NewFriend (isRead, feedId, myFeedId, mobilePhone, fromWhere, addComment, status, applyTime, expireTime, feed_belong) "
                          "VALUES (:isRead, :feedId, :myFeedId, :mobilePhone, :fromWhere, :addComment, :status, :applyTime, :expireTime, :feed_belong)");

            query.bindValue(":isRead", stNewFriend->getIsRead());
            query.bindValue(":feedId", stNewFriend->getFeedID());
            query.bindValue(":myFeedId", stNewFriend->getMyFeedID());
            query.bindValue(":mobilePhone", stNewFriend->getMobilePhone());
            query.bindValue(":fromWhere", stNewFriend->getFromWhere());
            query.bindValue(":addComment", stNewFriend->getAddComment());
            query.bindValue(":status", stNewFriend->getStatus());
            query.bindValue(":applyTime", stNewFriend->getApplyTime());
            query.bindValue(":expireTime", stNewFriend->getExpireTime());
            query.bindValue(":feed_belong", stNewFriend->getFeedBelong());

            bool ret = query.exec();
            if (ret)
            {
                return true;
            }
            else
            {
                QString strLog = query.lastError().text();
                qDebug() << "INSERT INTO NewFriend FAIL" << strLog;
            }
        }
    }
    return false;
}

bool TNNewFriend::Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue)
{
    if (tableIsExist("NewFriend"))
    {
        QSqlQuery query(*_db);
        bool ret = query.exec(QString("select * from NewFriend where %1='%2'").arg(queryItem).arg(queryValue));
        if (ret)
        {
            while (query.next())
            {
                st_NewFriendPtr newFriendTable = std::make_shared<st_NewFriend>();

                newFriendTable->setIsRead(query.value("isRead").toString());
                newFriendTable->setFeedID(query.value("feedId").toString());
                newFriendTable->setMyFeedID(query.value("myFeedId").toString());
                newFriendTable->setMobilePhone(query.value("mobilePhone").toString());
                newFriendTable->setFromWhere(query.value("fromWhere").toString());
                newFriendTable->setAddComment(query.value("addComment").toString());
                newFriendTable->setStatus(query.value("status").toString());
                newFriendTable->setApplyTime(query.value("applyTime").toString());
                newFriendTable->setExpireTime(query.value("expireTime").toString());
                newFriendTable->setFeedBelong(query.value("feed_belong").toString());

                TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(newFriendTable);
                tableBaseVec.push_back(tempTableBase);
            }
            return true;
        }
        else
        {
            QString strLog = query.lastError().text();
            qDebug() << "Query NewFriend FAIL" << strLog;
            return false;
        }
    }
    return false;
}

bool TNNewFriend::GetAllFields(TableBaseVec &tableBaseVec)
{
    if (tableIsExist("NewFriend"))
    {
        QSqlQuery query(*_db);
        bool ret = query.exec("select * from NewFriend order by applyTime DESC");
        if (ret)
        {
            while (query.next())
            {
                st_NewFriendPtr newFriendTable = std::make_shared<st_NewFriend>();

                newFriendTable->setIsRead(query.value("isRead").toString());
                newFriendTable->setFeedID(query.value("feedId").toString());
                newFriendTable->setMyFeedID(query.value("myFeedId").toString());
                newFriendTable->setMobilePhone(query.value("mobilePhone").toString());
                newFriendTable->setFromWhere(query.value("fromWhere").toString());
                newFriendTable->setAddComment(query.value("addComment").toString());
                newFriendTable->setStatus(query.value("status").toString());
                newFriendTable->setApplyTime(query.value("applyTime").toString());
                newFriendTable->setExpireTime(query.value("expireTime").toString());
                newFriendTable->setFeedBelong(query.value("feed_belong").toString());

                TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(newFriendTable);
                tableBaseVec.push_back(tempTableBase);
            }
            return true;
        }
        else
        {
            QString strLog = query.lastError().text();
            qDebug() << "INSERT INTO NewFriend FAIL" << strLog;
            return false;
        }
    }
    return false;
}

bool TNNewFriend::ClearAll()
{
    if (tableIsExist("NewFriend"))
    {
        QSqlQuery query(*_db);
        query.exec("DELETE FROM NewFriend");
    }
    return true;
}

void TNNewFriend::checkTable()
{

}

void TNNewFriend::createTable()
{
    if (!tableIsExist("NewFriend"))
    {
        QSqlQuery query(*_db);
        query.exec("Create TABLE MAIN.[NewFriend]([isRead] varchar(32), [feedId] varchar(32), [myFeedId] varchar(32),"
                   "[mobilePhone] varchar(32), [fromWhere] varchar(32), [addComment] varchar(256), [status] varchar(32),"
                   "[applyTime] varchar(32), [expireTime] varchar(32), [feed_belong] varchar(32) PRIMARY KEY UNIQUE NOT NULL)");
    }
}

void TNNewFriend::dropTable()
{
    if (tableIsExist("NewFriend"))
    {
        QSqlQuery query(*_db);
        query.exec("Drop Table MAIN.[NewFriend]");
    }
}

bool TNNewFriend::UpdateSetValueByField(const QString &fieldName, const QString &fieldValue,
                                        const QString &whereName, const QString &whereValue)
{
    QSqlQuery query(*_db);
    query.prepare(QString("update NewFriend set %1 = ?").arg(fieldName));
    query.bindValue(0, fieldValue);
    bool ret = query.exec();
    if (ret)
    {
        return true;
    }
    else
    {
        QString strLog = query.lastError().text();
        qDebug() << "UPDATE NewFriend FAIL" << strLog;
    }
    return false;
}

bool TNNewFriend::UpdateSetValueByFieldMap(QMap<QString, QString>& fieldMap, const QString &whereName, const QString &whereValue)
{
    QMap<QString, QString>::iterator fieldIter;
    QString updateSql = "update NewFriend set  ";
    for (fieldIter = fieldMap.begin(); fieldIter != fieldMap.end(); fieldIter++)
    {
        QString fieldKey = fieldIter.key();
        QString fieldValue = fieldIter.value();
        QString sqlField;
        if (fieldIter != fieldMap.begin())
            sqlField = ",";
        sqlField.append(QString("%1 = '%2'").arg(fieldKey, fieldValue));
        updateSql += sqlField;
    }
    QString whereSql = QString(" where %1 ='%2'").arg(whereName).arg(whereValue);

    updateSql.append(whereSql);
    QSqlQuery updateQuerty(*_db);
    if (updateQuerty.exec(updateSql))
        return true;
    else
    {
        QString strLog = updateQuerty.lastError().text();
        qDebug() << "update set NewFriend FAIL" << strLog;
        return false;
    }
}
int  TNNewFriend::Delete(const QString &queryItem, QList<QString> queryValueList)
{
	int nCount = 0;
	QList<QString>::iterator it;
	beginTransaction();
	for (it = queryValueList.begin(); it != queryValueList.end(); it++)
	{
		bool res = false;
		QSqlQuery query(*_db);
		res = query.exec(QString("DELETE FROM NewFriend where %1 = '%2'").arg(queryItem).arg((*it)));
		if (res)
			nCount++;
	}
	commitTransaction();
	return nCount;
}
bool TNNewFriend::Delete(const QString &queryItem, const QString &queryValue)
{
	bool res = false;
	QSqlQuery query(*_db);
	res = query.exec(QString("DELETE FROM NewFriend where %1 = '%2'").arg(queryItem).arg(queryValue));
	if (!res)
		qDebug() << "delete NewFriend fail" << query.lastError().text();
	return res;
}
