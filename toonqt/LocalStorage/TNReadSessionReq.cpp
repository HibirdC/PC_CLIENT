#include <memory>

#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>


#include "TNReadSessionReq.h"


TNReadSessionReq::TNReadSessionReq()
:TNBaseTable()
{
}


TNReadSessionReq::~TNReadSessionReq()
{
}

int  TNReadSessionReq::Delete(const QString &queryItem, const QString & queryValue)
{
	bool res = false;
	QSqlQuery query(*_db);
	res = query.exec(QString("DELETE FROM ReadSession where %1 = '%2'").arg(queryItem).arg(queryValue));
	if (!res)
		qDebug() << "delete ReadSession fail" << query.lastError().text();
	return res;
}
bool TNReadSessionReq::InsertDatas(st_ReadSessionReqPtr ReadSession)
{
	if (tableIsExist("ReadSession"))
	{
		QSqlQuery query(*_db);

		QString strSql = QString("INSERT INTO ReadSession (reqId, sessionId, fromId, toId, type, readSeqId) VALUES('%1', '%2', '%3', '%4', '%5' , '%6')")
			.arg(ReadSession->GetReqId()).arg(ReadSession->GetSessionId()).arg(ReadSession->GetFrom()).arg(ReadSession->GetTo()).arg(ReadSession->GetType()).arg(ReadSession->GetReadSeqId());
		bool ret = query.exec(strSql);
		if (ret)
		{
			return true;
		} 
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO ReadSession FAIL" << strLog;
		}
	}
	return false;
}

bool TNReadSessionReq::Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue)
{
	if (tableIsExist("ReadSession"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec(QString("select *from ReadSession where %1='%2'").arg(queryItem).arg(queryValue));
		if (ret)
		{
			while (query.next())
			{
				st_ReadSessionReqPtr ReadSession = std::make_shared<st_ReadSessionReq>();
				ReadSession->SetReqId(query.value("reqId").toString());
				ReadSession->SetSessionId(query.value("sessionId").toString());
				ReadSession->SetFrom(query.value("fromId").toString());
				ReadSession->SetTo(query.value("toId").toString());
				ReadSession->SetType(query.value("type").toInt());
				ReadSession->SetReadSeqId(query.value("readSeqId").toLongLong());
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(ReadSession);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO ReadSession FAIL" << strLog;
			return false;
		}
	}
	return false;
}

bool TNReadSessionReq::GetAllFields(TableBaseVec &tableBaseVec)
{
	if (tableIsExist("ReadSession"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec("select *from ReadSession");
		if (ret)
		{
			while (query.next())
			{
				st_ReadSessionReqPtr ReadSession = std::make_shared<st_ReadSessionReq>();
				ReadSession->SetReqId(query.value("reqId").toString());
				ReadSession->SetSessionId(query.value("sessionId").toString());
				ReadSession->SetFrom(query.value("fromId").toString());
				ReadSession->SetTo(query.value("toId").toString());
				ReadSession->SetType(query.value("type").toInt());
				ReadSession->SetReadSeqId(query.value("readSeqId").toLongLong());
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(ReadSession);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO ReadSession FAIL" << strLog;
			return false;
		}
	}
	return false;
}


bool TNReadSessionReq::ClearAll()
{
	if (tableIsExist("ReadSession"))
	{
		QSqlQuery query(*_db);
		query.exec("DELETE FROM ReadSession");
	}
	return true;
}

void TNReadSessionReq::checkTable()
{

}

void TNReadSessionReq::createTable()
{
	if (!tableIsExist("ReadSession"))
	{
		QSqlQuery query(*_db);
		query.exec("Create  TABLE MAIN.[ReadSession]([reqId] text PRIMARY KEY UNIQUE NOT NULL, [sessionId] text,"
			"[fromId] varchar(32), [toId] varchar(32), [type] integer, [readSeqId] integer)");
	}
}

void TNReadSessionReq::dropTable()
{
	if (tableIsExist("ReadSession"))
	{
		QSqlQuery query(*_db);
		query.exec("Drop Table MAIN.[ReadSession]");
	}
}
bool TNReadSessionReq::UpdateSetValueByField(const QString &fieldName, const QString &fieldValue, const QString &whereName, const QString &whereValue)
{
	QSqlQuery query(*_db);
	query.prepare(QString("update ReadSession set %1 = ? where %2 ='%3'").arg(fieldName).arg(whereName).arg(whereValue));
	query.bindValue(0, fieldValue);
	bool ret = query.exec();
	if (ret)
	{
		return true;
	}
	else
	{
		QString strLog = query.lastError().text();
		qDebug() << "update ReadSession failed" << strLog;
		return false;
	}
}