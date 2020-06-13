#include <memory>

#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>


#include "TNChatAppList.h"


TNChatAppList::TNChatAppList()
:TNBaseTable()
{
}


TNChatAppList::~TNChatAppList()
{
}

bool TNChatAppList::InsertDatas(st_ChatAppListPtr chatAppList)
{
	if (tableIsExist("ChatAppList"))
	{
		QSqlQuery query(*_db);
		QString strSql = QString("INSERT INTO ChatAppList (data text) VALUES('%1')")
			.arg(chatAppList->GetData());
		bool ret = query.exec(strSql);
		if (ret)
		{
			return true;
		} 
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO ChatAppList FAIL" << strLog;
		}
	}
	return false;
}

bool TNChatAppList::Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue)
{
	if (tableIsExist("ChatAppList"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec(QString("select *from ChatAppList where %1='%2'").arg(queryItem).arg(queryValue));
		if (ret)
		{
			while (query.next())
			{
				st_ChatAppListPtr chatAppList = std::make_shared<st_ChatAppList>();
				chatAppList->SetData(query.value("data").toString());
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(chatAppList);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO ChatAppList FAIL" << strLog;
			return false;
		}
	}
	return false;
}


bool TNChatAppList::GetAllFields(TableBaseVec &tableBaseVec)
{
	if (tableIsExist("ChatAppList"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec("select *from ChatAppList");
		if (ret)
		{
			while (query.next())
			{
				st_ChatAppListPtr chatAppList = std::make_shared<st_ChatAppList>();
				chatAppList->SetData(query.value("data").toString());
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(chatAppList);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO ChatAppList FAIL" << strLog;
			return false;
		}
	}
	return false;
}


bool TNChatAppList::ClearAll()
{
	if (tableIsExist("ChatAppList"))
	{
		QSqlQuery query(*_db);
		query.exec("DELETE FROM ChatAppList");
	}
	return true;
}

void TNChatAppList::checkTable()
{

}

void TNChatAppList::createTable()
{
	if (!tableIsExist("ChatAppList"))
	{
		QSqlQuery query(*_db);
		query.exec("Create  TABLE MAIN.[ChatAppList]([data] text)");
	}
}

void TNChatAppList::dropTable()
{
	if (tableIsExist("ChatAppList"))
	{
		QSqlQuery query(*_db);
		query.exec("Drop Table MAIN.[ChatAppList]");
	}
}
