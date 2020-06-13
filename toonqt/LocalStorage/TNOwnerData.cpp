#include "TNOwnerData.h"
#include <memory>

#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>

TNOwnerData::TNOwnerData()
	: TNBaseTable()
{

}

TNOwnerData::~TNOwnerData()
{

}

bool TNOwnerData::InsertDatas(st_OwnerDataPtr owner)
{
	if (tableIsExist("OwnerData"))
	{
		QString strSql;
		if (keyIsExist("OwnerData", "userId", owner->getUserId()))
		{
			strSql = QString("UPDATE OwnerData SET mobile = '%1', ext = '%2' where userId = '%3'")
				.arg(owner->getMobileId())
				.arg(owner->getExt()).arg(owner->getUserId());
		}
		else
		{
			strSql = QString("INSERT INTO OwnerData (userId,mobile,ext) VALUES('%1', '%2','%3')")
				.arg(owner->getUserId()).arg(owner->getMobileId()).arg(owner->getExt());
		}
		QSqlQuery query(*_db);
		bool ret = query.exec(strSql);
		if (ret)
		{
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO OwnerData FAIL" << strLog;
		}
	}
	return false;
}

bool TNOwnerData::Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue)
{
	if (tableIsExist("OwnerData"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec(QString("select *from OwnerData where %1='%2'").arg(queryItem).arg(queryValue));
		if (ret)
		{
			while (query.next())
			{
				st_OwnerDataPtr owner = std::make_shared<st_OwnerData>();
				owner->setUserId(query.value("userId").toString());
				owner->setMobileId(query.value("mobile").toString());
				owner->setExt(query.value("ext").toString());

				if (owner->getUserId().isEmpty())
				{
					continue;
				}

				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(owner);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "Query OwnerData FAIL" << strLog;
			return false;
		}
	}
	return false;
}

bool TNOwnerData::Delete(const QString &queryItem, const QString &queryValue)
{
	bool res = false;
	QSqlQuery query(*_db);
	res = query.exec(QString("DELETE FROM OwnerData where %1 = '%2'").arg(queryItem).arg(queryValue));
	if (!res)
		qDebug() << "delete OwnerData fail" << query.lastError().text();
	return res;
}

void TNOwnerData::checkTable()
{

}

void TNOwnerData::createTable()
{
	if (!tableIsExist("OwnerData"))
	{
		QSqlQuery query(*_db);
		query.exec("Create TABLE MAIN.[OwnerData]([userId] varchar(64) PRIMARY KEY UNIQUE NOT NULL,[mobile] varchar(64),[ext] varchar(64))");
	}
}

void TNOwnerData::dropTable()
{
	if (tableIsExist("OwnerData"))
	{
		QSqlQuery query(*_db);
		query.exec("Drop Table MAIN.[userId]");
	}
}
bool TNOwnerData::getOwnerStatus(const QString &userId)
{
	if (tableIsExist("OwnerData"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec(QString("select *from OwnerData where userId='%1'").arg(userId));
		if (ret && query.next())
		{
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "getOwnerStatus query  FAIL" << strLog;
			return false;
		}
	}
	return false;
}
bool TNOwnerData::GetAllFields(TableBaseVec &tableBaseVec)
{
	if (tableIsExist("OwnerData"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec("select *from OwnerData");
		if (ret)
		{
			while (query.next())
			{
				st_OwnerDataPtr owner = std::make_shared<st_OwnerData>();
				owner->setUserId(query.value("userId").toString());
				owner->setMobileId(query.value("mobile").toString());
				owner->setExt(query.value("ext").toString());

				if (owner->getUserId().isEmpty())
				{
					continue;
				}
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(owner);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "GetAllFields TNOwnerData FAIL" << strLog;
			return false;
		}
	}
	return false;
}