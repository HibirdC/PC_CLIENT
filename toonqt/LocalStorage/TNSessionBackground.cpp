#include <memory>

#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>


#include "TNSessionBackground.h"


TNSessionBackground::TNSessionBackground()
:TNBaseTable()
{
}


TNSessionBackground::~TNSessionBackground()
{
}

bool TNSessionBackground::InsertDatas(st_SessionBackgroundPtr sessionBackground)
{
	if (tableIsExist("SessionBackground"))
	{
		QSqlQuery query(*_db);
		QString strSql = QString("INSERT INTO SessionBackground (sessionId, backgroundImagePath) VALUES('%1', '%2')")
			.arg(sessionBackground->GetSessionId()).arg(sessionBackground->GetBackgroundImagePath());
		bool ret = query.exec(strSql);
		if (ret)
		{
			return true;
		} 
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO SessionBackground FAIL" << strLog;
		}
	}
	return false;
}

bool TNSessionBackground::Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue)
{
	if (tableIsExist("SessionBackground"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec(QString("select *from SessionBackground where %1='%2'").arg(queryItem).arg(queryValue));
		if (ret)
		{
			while (query.next())
			{
				st_SessionBackgroundPtr sessionBackground = std::make_shared<st_SessionBackground>();
				sessionBackground->SetSessionId(query.value("sessionId").toString());
				sessionBackground->SetBackgroundImagePath(query.value("backgroundImagePath").toString());
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(sessionBackground);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO SessionBackground FAIL" << strLog;
			return false;
		}
	}
	return false;
}


bool TNSessionBackground::GetAllFields(TableBaseVec &tableBaseVec)
{
	if (tableIsExist("SessionBackground"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec("select *from SessionBackground");
		if (ret)
		{
			while (query.next())
			{
				st_SessionBackgroundPtr sessionBackground = std::make_shared<st_SessionBackground>();
				sessionBackground->SetSessionId(query.value("sessionId").toString());
				sessionBackground->SetBackgroundImagePath(query.value("backgroundImagePath").toString());
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(sessionBackground);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO SessionBackground FAIL" << strLog;
			return false;
		}
	}
	return false;
}


bool TNSessionBackground::ClearAll()
{
	if (tableIsExist("SessionBackground"))
	{
		QSqlQuery query(*_db);
		query.exec("DELETE FROM SessionBackground");
	}
	return true;
}

void TNSessionBackground::checkTable()
{

}

void TNSessionBackground::createTable()
{
	if (!tableIsExist("SessionBackground"))
	{
		QSqlQuery query(*_db);
		query.exec("Create  TABLE MAIN.[SessionBackground]([sessionId] text, [backgroundImagePath] text, Primary Key(sessionId))");
	}
}

void TNSessionBackground::dropTable()
{
	if (tableIsExist("SessionBackground"))
	{
		QSqlQuery query(*_db);
		query.exec("Drop Table MAIN.[SessionBackground]");
	}
}
