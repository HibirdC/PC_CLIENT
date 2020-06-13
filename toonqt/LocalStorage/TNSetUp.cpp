#include <memory>

#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>


#include "TNSetUp.h"


TNSetUp::TNSetUp()
:TNBaseTable()
{
}


TNSetUp::~TNSetUp()
{
}

bool TNSetUp::InsertDatas(st_SetUpPtr settings)
{
	if (exist(settings->GetKey()))
	{
		UpdateData(settings->GetKey(), settings->GetValue());
	}
	else
	{
		InsertData(settings->GetKey(), settings->GetValue());
	}
	return true;
}

bool TNSetUp::Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue)
{
	if (tableIsExist("SetUp"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec(QString("select *from SetUp where %1='%2'").arg(queryItem).arg(queryValue));
		if (ret)
		{
			st_SetUpPtr settings = std::make_shared<st_SetUp>();
			while (query.next())
			{
				QString key = query.value("Key").toString();
				settings->SetKey(key);
				settings->SetValue(query.value("Value").toString());
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(settings);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO SetUp FAIL" << strLog;
			return false;
		}
	}
	return false;
}


bool TNSetUp::GetAllFields(TableBaseVec &tableBaseVec)
{
	if (tableIsExist("SetUp"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec("select *from SetUp");
		if (ret)
		{
			while (query.next())
			{
				st_SetUpPtr settings = std::make_shared<st_SetUp>();
				QString key = query.value("Key").toString();
				settings->SetKey(key);
				settings->SetValue(query.value("Value").toString());
     			TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(settings);
	    		tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO SetUp FAIL" << strLog;
			return false;
		}
	}
	return false;
}


bool TNSetUp::ClearAll()
{
	if (tableIsExist("SetUp"))
	{
		QSqlQuery query(*_db);
		query.exec("DELETE FROM SetUp");
	}
	return true;
}

void TNSetUp::checkTable()
{

}

void TNSetUp::createTable()
{
	if (!tableIsExist("SetUp"))
	{
		QSqlQuery query(*_db);
		query.exec("Create  TABLE MAIN.[SetUp]([Key] varchar(128), [Value] varchar(512))");
	}
}

void TNSetUp::dropTable()
{
	if (tableIsExist("SetUp"))
	{
		QSqlQuery query(*_db);
		query.exec("Drop Table MAIN.[SetUp]");
	}
}

bool TNSetUp::exist(const QString &fieldValue)
{
	if (tableIsExist("SetUp")) 
	{
		QSqlQuery query(*_db);
		bool ret = query.exec(QString("select Value from SetUp where Key='%1'").arg(fieldValue));
		if (ret)
		{
			while (query.next())
			{
				return true;
			}
		}
	}

	return false;
}

bool TNSetUp::UpdateData(const QString &key, const QString &newValue)
{
	if (tableIsExist("SetUp"))
	{
		QSqlQuery query(*_db);
        QString strSql = QString("update SetUp set Value = '%1' where Key = '%2'").arg(newValue).arg(key);
        bool ret = query.exec(strSql);
        qDebug() << "TNSetUp::UpdateData-strSql=" << strSql;
		if (ret)
		{
			return true;
		}
		else
		{
			QString errorLog = query.lastError().text();
			qDebug() << "update SetUp fail" << errorLog;
			return false;
		}
	}

	return false;
}

bool TNSetUp::InsertData(const QString &key, const QString &value)
{
	if (tableIsExist("SetUp"))
	{
		QSqlQuery query(*_db);
		QString strSql = QString("INSERT INTO SetUp (Key, Value) VALUES('%1', '%2')").arg(key).arg(value);
        qDebug() << "TNSetUp::InsertData-strSql=" << strSql;
		bool ret = query.exec(strSql);
		if (ret)
		{
			return true;
		}
		else
		{
			QString errorLog = query.lastError().text();
			qDebug() << "INSERT INTO SetUp FAIL" << errorLog;
			return false;
		}
	}

	return false;
}
