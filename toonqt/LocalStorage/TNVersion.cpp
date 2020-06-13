#include <memory>

#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>


#include "TNVersion.h"


TNVersion::TNVersion()
:TNBaseTable()
{
}


TNVersion::~TNVersion()
{
}

bool TNVersion::InsertDatas(st_VersionPtr version)
{
	if (tableIsExist("Version"))
	{
		QSqlQuery query(*_db);

		QString strSql = QString("INSERT INTO Version (version, name) VALUES('%1', '%2')")
			.arg(version->GetVersion()).arg(version->GetName());
		bool ret = query.exec(strSql);
		if (ret)
		{
			return true;
		} 
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO Version FAIL" << strLog;
		}
	}
	return false;
}

bool TNVersion::Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue)
{
	if (tableIsExist("Version"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec(QString("select *from Version where %1='%2'").arg(queryItem).arg(queryValue));
		if (ret)
		{
			while (query.next())
			{
				st_VersionPtr versionTable = std::make_shared<st_Version>();
                QString qs_version = query.value("version").toString();
                //gcc error: versionTable->SetVersion(query.value("version").toString());
                versionTable->SetVersion(qs_version);
                QString qs_name = query.value("name").toString();
                //gcc error: versionTable->SetName(query.value("name").toString());
                versionTable->SetName(qs_name);
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(versionTable);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO Version FAIL" << strLog;
			return false;
		}
	}
	return false;
}


bool TNVersion::GetAllFields(TableBaseVec &tableBaseVec)
{
	if (tableIsExist("Version"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec("select * from Version");
		if (ret)
		{
			while (query.next())
			{
				st_VersionPtr versionTable = std::make_shared<st_Version>();
                QString qs_version = query.value("version").toString();
                //gcc error: versionTable->SetVersion(query.value("version").toString());
                versionTable->SetVersion(qs_version);
                QString qs_name = query.value("name").toString();
                //gcc error: versionTable->SetName(query.value("name").toString());
                versionTable->SetName(qs_name);
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(versionTable);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO Version FAIL" << strLog;
			return false;
		}
	}
	return false;
}


bool TNVersion::ClearAll()
{
	if (tableIsExist("Version"))
	{
		QSqlQuery query(*_db);
		query.exec("DELETE FROM Version");
	}
	return true;
}

void TNVersion::checkTable()
{

}

void TNVersion::createTable()
{
	if (!tableIsExist("Version"))
	{
		QSqlQuery query(*_db);
		query.exec("Create  TABLE MAIN.[Version]([version] varchar(256),"
			"[name] varchar(64) PRIMARY KEY UNIQUE NOT NULL)");
	}
}

void TNVersion::dropTable()
{
	if (tableIsExist("Version"))
	{
		QSqlQuery query(*_db);
		query.exec("Drop Table MAIN.[Version]");
	}
}

bool TNVersion::UpdateSetValueByField(const QString &fieldName, const QString &fieldValue, const QString &whereName, const QString &whereValue)
{
	if (tableIsExist("Version"))
	{
		QSqlQuery update(*_db);
		bool ret = update.exec(QString("update Version set %1 = '%2' where %3='%4'")
			.arg(fieldName).arg(fieldValue).arg(whereName).arg(whereValue));
		if (ret)
		{
			return true;
		}
		else
		{
			QString strLog = update.lastError().text();
			qDebug() << "update Version FAIL" << strLog;
			return false;
		}
	}
	return false;

}
