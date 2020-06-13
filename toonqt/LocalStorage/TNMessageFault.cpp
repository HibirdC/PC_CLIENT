#include <memory>

#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>


#include "TNMessageFault.h"


TNMessageFault::TNMessageFault()
:TNBaseTable()
{
}


TNMessageFault::~TNMessageFault()
{
}

bool TNMessageFault::InsertDatas(st_MessageFaultPtr login)
{
	if (tableIsExist("MessageFault"))
	{
		QSqlQuery query(*_db);
		QString strSql = QString("INSERT INTO MessageFault (sessionId, maxSeqId, count, minSeqId) VALUES('%1', '%2','%3', '%4')")
			.arg(login->GetSessionId()).arg(login->GetnMaxSeqId()).arg(login->GetCount()).arg(login->GetMinSeqId());
		bool ret = query.exec(strSql);
		if (ret)
		{
			return true;
		} 
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO MessageFault FAIL" << strLog;
		}
	}
	return false;
}

bool TNMessageFault::Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue)
{
	if (tableIsExist("MessageFault"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec(QString("select *from MessageFault where %1='%2'").arg(queryItem).arg(queryValue));
		if (ret)
		{
			while (query.next())
			{
				st_MessageFaultPtr messageFault = std::make_shared<st_MessageFault>();
				messageFault->SetSessionId(query.value("sessionId").toString());
				messageFault->SetMaxSeqId(query.value("maxSeqId").toInt());
				messageFault->SetCount(query.value("count").toInt());
				messageFault->SetMinSeqId(query.value("minSeqId").toInt());
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(messageFault);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO LoginUser FAIL" << strLog;
			return false;
		}
	}
	return false;
}


bool TNMessageFault::GetAllFields(TableBaseVec &tableBaseVec)
{
	if (tableIsExist("MessageFault"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec("select *from MessageFault");
		if (ret)
		{
			while (query.next())
			{
				st_MessageFaultPtr messageFault = std::make_shared<st_MessageFault>();
				messageFault->SetSessionId(query.value("sessionId").toString());
				messageFault->SetMaxSeqId(query.value("maxSeqId").toInt());
				messageFault->SetCount(query.value("count").toInt());
				messageFault->SetMinSeqId(query.value("minSeqId").toInt());
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(messageFault);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO MessageFault FAIL" << strLog;
			return false;
		}
	}
	return false;
}


bool TNMessageFault::ClearAll()
{
	if (tableIsExist("MessageFault"))
	{
		QSqlQuery query(*_db);
		query.exec("DELETE FROM MessageFault");
	}
	return true;
}

void TNMessageFault::checkTable()
{

}

void TNMessageFault::createTable()
{
	if (!tableIsExist("MessageFault"))
	{
		QSqlQuery query(*_db);
		query.exec("Create  TABLE MAIN.[MessageFault]([sessionId] text ,"
			"[maxSeqId] integer, [count] integer, [minSeqId] integer, Primary Key(sessionId,minSeqId))");
	}
}

void TNMessageFault::dropTable()
{
	if (tableIsExist("MessageFault"))
	{
		QSqlQuery query(*_db);
		query.exec("Drop Table MAIN.[MessageFault]");
	}
}
