#include <memory>

#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>


#include "TNJoinStuff.h"


TNJoinStuff::TNJoinStuff()
:TNBaseTable()
{
}


TNJoinStuff::~TNJoinStuff()
{
}
int TNJoinStuff::InsertDatas(QList<TableBasePtr> joinStuffList)
{
	int mCount = 0;
	if (!tableIsExist("JoinStuff"))
	{
		return mCount;
	}
	QList<TableBasePtr>::iterator it;
	beginTransaction();
	for (it = joinStuffList.begin(); it != joinStuffList.end(); it++)
	{
		st_JoinStuffPtr joinStuff = std::dynamic_pointer_cast<st_JoinStuff>(*it);
		QString strSql;
		if (keyIsExist("JoinStuff", "feed_belong", joinStuff->GetFeedBelong()))
		{
			strSql = QString("UPDATE JoinStuff SET feedId = '%1', feedType = '%2',belongTo = '%3',ext1 = '%4',ext2 = '%5',ext3 = '%6',remark = '%7',remarkPy = '%8' where feed_belong = '%9'").arg(joinStuff->GetFeedID()).arg(joinStuff->GetFeedType()).arg(joinStuff->GetBelongTo()).arg(joinStuff->GetExt1()).arg(joinStuff->GetExt2()).arg(joinStuff->GetExt3()).arg(joinStuff->GetReMark()).arg(joinStuff->GetReMarkPY()).arg(joinStuff->GetFeedBelong());
		}
		else
		{
			strSql = QString("INSERT INTO JoinStuff (feed_belong, feedId, feedType,belongTo,ext1,ext2,ext3,remark,remarkPy) VALUES('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9')")
				.arg(joinStuff->GetFeedBelong()).arg(joinStuff->GetFeedID()).arg(joinStuff->GetFeedType()).arg(joinStuff->GetBelongTo())
				.arg(joinStuff->GetExt1()).arg(joinStuff->GetExt2()).arg(joinStuff->GetExt3()).arg(joinStuff->GetReMark()).arg(joinStuff->GetReMarkPY());
		}
		QSqlQuery query(*_db);
		bool ret = query.exec(strSql);
		if (!ret)
		{
			qDebug() << "SQL Error JoinStuff: " + strSql;
			qDebug() << query.lastError();
		}
		mCount = ret ? mCount + 1 : mCount;
	}
	commitTransaction();
	return mCount;
}
bool TNJoinStuff::InsertDatas(st_JoinStuffPtr joinStuff)
{
	if (tableIsExist("JoinStuff"))
	{
		QSqlQuery query(*_db);

		QString strSql = QString("INSERT INTO JoinStuff (feed_belong, feedId, feedType,belongTo,ext1,ext2,ext3,remark,remarkPy) VALUES('%1', '%2', '%3', '%4', '%5', '%6', '%7','%8','%9')")
			.arg(joinStuff->GetFeedBelong()).arg(joinStuff->GetFeedID()).arg(joinStuff->GetFeedType()).arg(joinStuff->GetBelongTo())
			.arg(joinStuff->GetExt1()).arg(joinStuff->GetExt2()).arg(joinStuff->GetExt3().arg(joinStuff->GetReMark()).arg(joinStuff->GetReMarkPY()));
		bool ret = query.exec(strSql);
		if (ret)
		{
			return true;
		} 
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO JoinStuff FAIL" << strLog;
		}
	}
	return false;
}
bool TNJoinStuff::MultiQuery(TableBaseVec &tableBaseVec, const QString &queryItem1, const QString &queryItem2, const QString &queryValue1, const QString &queryValue2)
{
	if (tableIsExist("JoinStuff"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec(QString("select *from JoinStuff where %1='%2'and %3 = '%4'").arg(queryItem1).arg(queryValue1).arg(queryItem2).arg(queryValue2));
		if (ret)
		{
			while (query.next())
			{
				st_JoinStuffPtr joinStuff = std::make_shared<st_JoinStuff>();
				joinStuff->SetFeedBelong(query.value("feed_belong").toString());
				joinStuff->SetFeedID(query.value("feedId").toString());
				joinStuff->SetFeedType(query.value("feedType").toString());
				joinStuff->SetBelongTo(query.value("belongTo").toString());
				joinStuff->SetExt1(query.value("ext1").toString());
				joinStuff->SetExt2(query.value("ext2").toString());
				joinStuff->SetExt3(query.value("ext3").toString());
				joinStuff->SetReMark(query.value("remark").toString());
				joinStuff->SetReMarkPY(query.value("remarkPy").toString());
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(joinStuff);
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
bool TNJoinStuff::Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue)
{
	if (tableIsExist("JoinStuff"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec(QString("select *from JoinStuff where %1='%2'").arg(queryItem).arg(queryValue));
		if (ret)
		{
			while (query.next())
			{
				st_JoinStuffPtr joinStuff = std::make_shared<st_JoinStuff>();
				joinStuff->SetFeedBelong(query.value("feed_belong").toString());
				joinStuff->SetFeedID(query.value("feedId").toString());
				joinStuff->SetFeedType(query.value("feedType").toString());
				joinStuff->SetBelongTo(query.value("belongTo").toString());
				joinStuff->SetExt1(query.value("ext1").toString());
				joinStuff->SetExt2(query.value("ext2").toString());
				joinStuff->SetExt3(query.value("ext3").toString());
				joinStuff->SetReMark(query.value("remark").toString());
				joinStuff->SetReMarkPY(query.value("remarkPy").toString());
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(joinStuff);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "Query joinStuff FAIL" << strLog;
			return false;
		}
	}
	return false;
}
int TNJoinStuff::Delete(const QString &queryItem, QList<QString> Feeds)
{
	int nCount = 0;
	QList<QString>::iterator it;
	beginTransaction();
	for (it = Feeds.begin(); it != Feeds.end(); it++)
	{
		bool res = false;
		QSqlQuery query(*_db);
		res = query.exec(QString("DELETE FROM JoinStuff where %1 = '%2'").arg(queryItem).arg((*it)));
		if (res)
			nCount++;
	}
	commitTransaction();
	return nCount;
}
bool TNJoinStuff::Delete(const QString &queryItem, const QString &queryValue)
{
	bool res = false;
	QSqlQuery query(*_db);
	res = query.exec(QString("DELETE FROM JoinStuff where %1 = '%2'").arg(queryItem).arg(queryValue));
	if (!res)
		qDebug() << "delete JoinStuff fail" << query.lastError().text();
	return res;
}

bool TNJoinStuff::GetAllFields(TableBaseVec &tableBaseVec)
{
	if (tableIsExist("JoinStuff"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec("select *from JoinStuff");
		if (ret)
		{
			while (query.next())
			{
				st_JoinStuffPtr joinStuff = std::make_shared<st_JoinStuff>();
				joinStuff->SetFeedBelong(query.value("feed_belong").toString());
				joinStuff->SetFeedID(query.value("feedId").toString());
				joinStuff->SetFeedType(query.value("feedType").toString());
				joinStuff->SetBelongTo(query.value("belongTo").toString());
				joinStuff->SetExt1(query.value("ext1").toString());
				joinStuff->SetExt2(query.value("ext2").toString());
				joinStuff->SetExt3(query.value("ext3").toString());
				joinStuff->SetReMark(query.value("remark").toString());
				joinStuff->SetReMarkPY(query.value("remarkPy").toString());
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(joinStuff);
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

bool TNJoinStuff::ClearAll()
{
	if (tableIsExist("JoinStuff"))
	{
		QSqlQuery query(*_db);
		query.exec("DELETE FROM JoinStuff");
	}
	return true;
}

void TNJoinStuff::checkTable()
{

}

void TNJoinStuff::createTable()
{
	if (!tableIsExist("JoinStuff"))
	{
		QSqlQuery query(*_db);
		query.exec("Create  TABLE MAIN.[JoinStuff]([ext1] varchar(256),[ext2] varchar(256),[ext3] varchar(256), [belongTo] varchar(64),"
			"[feedType] varchar(8), [feedId] varchar(64),[remark] varchar(128),[remarkPy] varchar(128), [feed_belong] varchar(128) PRIMARY KEY UNIQUE NOT NULL)");
	}
}

void TNJoinStuff::dropTable()
{
	if (tableIsExist("JoinStuff"))
	{
		QSqlQuery query(*_db);
		query.exec("Drop Table MAIN.[JoinStuff]");
	}
}
bool TNJoinStuff::updateFeedRemark(QString feedBelongId,QString remark, QString remarkPY)
{
	if (!tableIsExist("JoinStuff"))
	{
		return false;
	}
	QString strSql = QString("UPDATE JoinStuff SET remark = '%1',remarkPy = '%2' where feed_belong = '%3'").arg(remark).arg(remarkPY).arg(feedBelongId);
	QSqlQuery query(*_db);
	bool ret = query.exec(strSql);
	if (!ret)
		qInfo() << "[LocalStorage][TNJoinStuff]updateFeedRemark SQL Error FEED: " + strSql << " Err:" << query.lastError();
	return ret;
}