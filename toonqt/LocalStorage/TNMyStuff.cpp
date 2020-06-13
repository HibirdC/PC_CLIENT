#include <memory>

#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>


#include "TNMyStuff.h"


TNMyStuff::TNMyStuff()
:TNBaseTable()
{
}


TNMyStuff::~TNMyStuff()
{
}
int  TNMyStuff::Delete(const QString &queryItem, QList<QString> queryValueList)
{
	int nCount = 0;
	QList<QString>::iterator it;
	beginTransaction();
	for (it = queryValueList.begin(); it != queryValueList.end(); it++)
	{
		bool res = false;
		QSqlQuery query(*_db);
		res = query.exec(QString("DELETE FROM MyStuff where %1 = '%2'").arg(queryItem).arg((*it)));
		if (res)
			nCount++;
	}
	commitTransaction();
	return nCount;
}
int  TNMyStuff::Delete(const QString &queryItem, const QString & queryValue)
{
	bool res = false;
	QSqlQuery query(*_db);
	res = query.exec(QString("DELETE FROM MyStuff where %1 = '%2'").arg(queryItem).arg(queryValue));
	if (!res)
		qDebug() << "delete MyStuff fail" << query.lastError().text();
	return res;
}
int  TNMyStuff::InsertDatas(QList<TableBasePtr> myStuffList)
{
	int mCount = 0;
	if (!tableIsExist("MyStuff"))
	{
		return mCount;
	}
	QList<TableBasePtr>::iterator it;
	beginTransaction();
	for (it = myStuffList.begin(); it != myStuffList.end(); it++)
	{
		st_MyStuffPtr myStuff = std::dynamic_pointer_cast<st_MyStuff>(*it);
		QString strSql;
        if (keyIsExist("MyStuff", "feedId", myStuff->GetFeedID()))
		{
			strSql = QString("UPDATE MyStuff SET feedType = '%1', belongTo = '%2',ext1 = '%3',contentDict = '%4' where feedId = '%5'").arg(myStuff->GetFeedType()).arg(myStuff->GetBelongTo()).arg(myStuff->GetExt()).arg(myStuff->GetContentDict()).arg(myStuff->GetFeedID());
		}
		else
		{
			strSql = QString("INSERT INTO MyStuff (feedId, feedType, belongTo,ext1,contentDict) VALUES('%1', '%2', '%3', '%4', '%5')")
				.arg(myStuff->GetFeedID()).arg(myStuff->GetFeedType()).arg(myStuff->GetBelongTo()).arg(myStuff->GetExt()).arg(myStuff->GetContentDict());
		}
		QSqlQuery query(*_db);
		bool ret = query.exec(strSql);
		if (!ret)
		{
			qDebug() << "SQL Error FEED: " + strSql;
			qDebug() << query.lastError();
		}
		mCount = ret ? mCount + 1 : mCount;
	}
	commitTransaction();
	return mCount;
}
bool TNMyStuff::InsertDatas(st_MyStuffPtr myStuff)
{
	if (tableIsExist("MyStuff"))
	{
		QSqlQuery query(*_db);

		QString strSql = QString("INSERT INTO MyStuff (feedId, feedType, belongTo,ext1,contentDict) VALUES('%1', '%2', '%3', '%4', '%5')")
			.arg(myStuff->GetFeedID()).arg(myStuff->GetFeedType()).arg(myStuff->GetBelongTo()).arg(myStuff->GetExt()).arg(myStuff->GetContentDict());
		bool ret = query.exec(strSql);
		if (ret)
		{
			return true;
		} 
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO MyStuff FAIL" << strLog;
		}
	}
	return false;
}
bool TNMyStuff::isMySelf(const QString &feedId)
{
	return keyIsExist("MyStuff", "feedId", feedId);
}
bool TNMyStuff::Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue)
{
	if (tableIsExist("MyStuff"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec(QString("select *from MyStuff where %1='%2'").arg(queryItem).arg(queryValue));
		if (ret)
		{
			while (query.next())
			{
				st_MyStuffPtr myStuff = std::make_shared<st_MyStuff>();
				myStuff->SetFeedID(query.value("feedId").toString());
				myStuff->SetFeedType(query.value("feedType").toString());
				myStuff->SetBelongTo(query.value("belongTo").toString());
				myStuff->SetExt(query.value("ext1").toString());
				myStuff->SetContentDict(query.value("contentDict").toString());
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(myStuff);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO MyStuff FAIL" << strLog;
			return false;
		}
	}
	return false;
}
bool TNMyStuff::MultiQuery(TableBaseVec &tableBaseVec, const QString &queryItem1, const QString &queryItem2, const QString &queryValue1, const QString &queryValue2)
{
	if (tableIsExist("MyStuff"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec(QString("select *from MyStuff where %1='%2'and %3 = '%4'").arg(queryItem1).arg(queryValue1).arg(queryItem2).arg(queryValue2));
		if (ret)
		{
			while (query.next())
			{
				st_MyStuffPtr myStuff = std::make_shared<st_MyStuff>();
				myStuff->SetFeedID(query.value("feedId").toString());
				myStuff->SetFeedType(query.value("feedType").toString());
				myStuff->SetBelongTo(query.value("belongTo").toString());
				myStuff->SetExt(query.value("ext1").toString());
				myStuff->SetContentDict(query.value("contentDict").toString());
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(myStuff);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO joinStuff FAIL" << strLog;
			return false;
		}
	}
	return false;
}

bool TNMyStuff::GetAllFields(TableBaseVec &tableBaseVec)
{
	if (tableIsExist("MyStuff"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec("select *from MyStuff");
		if (ret)
		{
			while (query.next())
			{
				st_MyStuffPtr myStuff = std::make_shared<st_MyStuff>();
				myStuff->SetFeedID(query.value("feedId").toString());
				myStuff->SetFeedType(query.value("feedType").toString());
				myStuff->SetBelongTo(query.value("belongTo").toString());
				myStuff->SetExt(query.value("ext1").toString());
				myStuff->SetContentDict(query.value("contentDict").toString());
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(myStuff);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO MyStuff FAIL" << strLog;
			return false;
		}
	}
	return false;
}


bool TNMyStuff::ClearAll()
{
	if (tableIsExist("MyStuff"))
	{
		QSqlQuery query(*_db);
		query.exec("DELETE FROM MyStuff");
	}
	return true;
}

void TNMyStuff::checkTable()
{

}

void TNMyStuff::createTable()
{
	if (!tableIsExist("MyStuff"))
	{
		QSqlQuery query(*_db);
		query.exec("Create  TABLE MAIN.[MyStuff]([contentDict] varchar(512), [ext1] varchar(512),"
			"[belongTo] varchar(64), [feedType] varchar(8), [feedId] varchar(64) PRIMARY KEY UNIQUE NOT NULL)");
	}
}

void TNMyStuff::dropTable()
{
	if (tableIsExist("MyStuff"))
	{
		QSqlQuery query(*_db);
		query.exec("Drop Table MAIN.[MyStuff]");
	}
}
bool TNMyStuff::UpdateSetValueByField(const QString &fieldName, const QString &fieldValue, const QString &whereName, const QString &whereValue)
{
	QSqlQuery query(*_db);
	query.prepare(QString("update MyStuff set %1 = ? where %2 ='%3'").arg(fieldName).arg(whereName).arg(whereValue));
	query.bindValue(0, fieldValue);
	bool ret = query.exec();
	if (ret)
	{
		return true;
	}
	else
	{
		QString strLog = query.lastError().text();
		qDebug() << "update MyStuff failed" << strLog;
		return false;
	}
}