#include <memory>

#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>


#include "TNBlackList.h"
#include "TNDataControlServer.h"

TNBlackList::TNBlackList()
:TNBaseTable()
{
}


TNBlackList::~TNBlackList()
{
}

bool TNBlackList::InsertDatas(st_BlackListPtr blackInfo)
{
	if (!tableIsExist("BlackList"))
	{
		return false;
	}
	QString strSql =  QString("INSERT INTO BlackList (feedId_passiveFeedId, feedId, passiveFeedId ,status) VALUES('%1', '%2','%3', '%4')")
		.arg(blackInfo->GetKey()).arg(blackInfo->GetFeedId()).arg(blackInfo->GetPassiveFeedId()).arg(blackInfo->GetStatus());

	QSqlQuery query(*_db);
	if (!query.exec(strSql))
	{
		QString strLog = query.lastError().text();
		qDebug() << "INSERT INTO blackList FAIL" << strLog;
	}
	return true;
}

bool TNBlackList::Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue)
{
	if (tableIsExist("BlackList"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec(QString("select *from BlackList where %1='%2'").arg(queryItem).arg(queryValue));
		if (ret)
		{
			while (query.next())
			{
				st_BlackListPtr blackInfo = std::make_shared<st_BlackList>();
				blackInfo->SetFeedId(query.value("feedId").toString());
				blackInfo->SetPassiveFeedId(query.value("passiveFeedId").toString());
				blackInfo->SetStatus(query.value("status").toInt());
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(blackInfo);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO BlackList FAIL" << strLog;
			return false;
		}
	}
	return false;
}

bool TNBlackList::GetAllFields(TableBaseVec &tableBaseVec)
{
	if (tableIsExist("BlackList"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec("select *from BlackList");
		if (ret)
		{
			while (query.next())
			{
				st_BlackListPtr blackInfo = std::make_shared<st_BlackList>();
				blackInfo->SetFeedId(query.value("feedId").toString());
				blackInfo->SetPassiveFeedId(query.value("passiveFeedId").toString());
				blackInfo->SetStatus(query.value("status").toInt());
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(blackInfo);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO BlackList FAIL" << strLog;
			return false;
		}
	}
	return false;
}


bool TNBlackList::ClearAll()
{
	if (tableIsExist("BlackList"))
	{
		QSqlQuery query(*_db);
		query.exec("DELETE FROM BlackList");
	}
	return true;
}

void TNBlackList::checkTable()
{

}

void TNBlackList::createTable()
{
	if (!tableIsExist("BlackList"))
	{
		QSqlQuery query(*_db);
		query.exec("Create  TABLE MAIN.[BlackList]([feedId_passiveFeedId] varchar(128) PRIMARY KEY, [feedId] varchar(64), [passiveFeedId] varchar(64),[status] int)");
	}
}

void TNBlackList::dropTable()
{
	if (tableIsExist("BlackList"))
	{
		QSqlQuery query(*_db);
		query.exec("Drop Table MAIN.[BlackList]");
	}
}

bool TNBlackList::UpdateSetValueByField(const QString &fieldName, const QString &fieldValue, const QString &whereName, const QString &whereValue)
{
    if (tableIsExist("BlackList"))
    {
        QSqlQuery update(*_db);
        bool ret = update.exec(QString("update BlackList set %1 = '%2' where %3='%4'")
            .arg(fieldName).arg(fieldValue).arg(whereName).arg(whereValue));
        if (ret)
        {
            return true;
        }
        else
        {
            QString strLog = update.lastError().text();
            qDebug() << "update BlackList FAIL" << strLog;
            return false;
        }
    }
    return false;
}
