#include <memory>

#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>


#include "TNChatSettings.h"


TNChatSettings::TNChatSettings()
:TNBaseTable()
{
}


TNChatSettings::~TNChatSettings()
{
}

bool TNChatSettings::InsertDatas(st_ChatSettingsPtr chatSettings)
{
	if (tableIsExist("ChatSettings"))
	{
		QSqlQuery query(*_db);
		QString strSql = QString("INSERT INTO ChatSettings (key, value, comment) VALUES('%1', '%2', '%3')")
			.arg(chatSettings->GetKey()).arg(chatSettings->GetValue()).arg(chatSettings->GetComment());
		bool ret = query.exec(strSql);
		if (ret)
		{
			return true;
		} 
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO ChatSettings FAIL" << strLog;
		}
	}
	return false;
}

bool TNChatSettings::Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue)
{
	if (tableIsExist("ChatSettings"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec(QString("select *from ChatSettings where %1='%2'").arg(queryItem).arg(queryValue));
		if (ret)
		{
			while (query.next())
			{
				st_ChatSettingsPtr chatSettings = std::make_shared<st_ChatSettings>();
				chatSettings->SetKey(query.value("key").toString());
				chatSettings->SetValue(query.value("value").toString());
				chatSettings->SetComment(query.value("comment").toString());
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(chatSettings);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO ChatSettings FAIL" << strLog;
			return false;
		}
	}
	return false;
}


bool TNChatSettings::GetAllFields(TableBaseVec &tableBaseVec)
{
	if (tableIsExist("ChatSettings"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec("select *from ChatSettings");
		if (ret)
		{
			while (query.next())
			{
				st_ChatSettingsPtr chatSettings = std::make_shared<st_ChatSettings>();
				chatSettings->SetKey(query.value("key").toString());
				chatSettings->SetValue(query.value("value").toString());
				chatSettings->SetComment(query.value("comment").toString());
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(chatSettings);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO ChatSettings FAIL" << strLog;
			return false;
		}
	}
	return false;
}


bool TNChatSettings::ClearAll()
{
	if (tableIsExist("ChatSettings"))
	{
		QSqlQuery query(*_db);
		query.exec("DELETE FROM ChatSettings");
	}
	return true;
}

void TNChatSettings::checkTable()
{

}

void TNChatSettings::createTable()
{
	if (!tableIsExist("ChatSettings"))
	{
		QSqlQuery query(*_db);
		query.exec("Create  TABLE MAIN.[ChatSettings]([key] text"
			", [value] text"
			", [comment] text"
			", Primary Key(key))");
	}
}

void TNChatSettings::dropTable()
{
	if (tableIsExist("ChatSettings"))
	{
		QSqlQuery query(*_db);
		query.exec("Drop Table MAIN.[ChatSettings]");
	}
}
