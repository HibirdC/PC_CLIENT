#include <memory>

#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>


#include "TNMessageOperate.h"


TNMessageOperate::TNMessageOperate()
:TNBaseTable()
{
}


TNMessageOperate::~TNMessageOperate()
{
}

bool TNMessageOperate::InsertDatas(st_MessageOperatePtr MessageOperate)
{
	if (tableIsExist("MessageOperate"))
	{
		QSqlQuery query(*_db);
		QString strSql = QString("INSERT INTO MessageOperate (msgId, seqId, type, mfrom, mto, timestamp, catalogId, opMsgId, opFeedId, opName)"
			"VALUES('%1', '%2','%3', '%4','%5', '%6','%7', '%8','%9', '%10')")
		.arg(MessageOperate->GetMsgId()).arg(MessageOperate->GetSeqId()).arg(MessageOperate->GetType()).arg(MessageOperate->GetMfrom())
		.arg(MessageOperate->GetMto()).arg(MessageOperate->GetTimestamp()).arg(MessageOperate->GetCatalogId()).arg(MessageOperate->GetOpMsgId())
		.arg(MessageOperate->GetOpFeedId()).arg(MessageOperate->GetOpName());
		bool ret = query.exec(strSql);
		if (ret)
		{
			return true;
		} 
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO Login FAIL" << strLog;
		}
	}
	return false;
}

bool TNMessageOperate::Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue)
{
	if (tableIsExist("MessageOperate"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec(QString("select *from MessageOperate where %1='%2'").arg(queryItem).arg(queryValue));
		if (ret)
		{
			while (query.next())
			{
				st_MessageOperatePtr messageOperate = std::make_shared<st_MessageOperate>();
				messageOperate->SetMsgId(query.value("msgId").toString());
				messageOperate->SetSeqId(query.value("seqId").toInt());
				messageOperate->SetType(query.value("type").toInt());
				messageOperate->SetMfrom(query.value("mfrom").toString());
				messageOperate->SetMsgId(query.value("msgId").toString());
				messageOperate->SetMto(query.value("mto").toString());
				messageOperate->SetTimestamp(query.value("timestamp").toInt());
				messageOperate->SetCatalogId(query.value("catalogId").toInt());
				messageOperate->SetOpMsgId(query.value("opMsgId").toString());
				messageOperate->SetOpFeedId(query.value("opFeedId").toString());
				messageOperate->SetOpName(query.value("opName").toString());
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(messageOperate);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO MessageOperate FAIL" << strLog;
			return false;
		}
	}
	return false;
}


bool TNMessageOperate::GetAllFields(TableBaseVec &tableBaseVec)
{
	if (tableIsExist("MessageOperate"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec("select *from LoginUser");
		if (ret)
		{
			while (query.next())
			{
				st_MessageOperatePtr messageOperate = std::make_shared<st_MessageOperate>();
				messageOperate->SetMsgId(query.value("msgId").toString());
				messageOperate->SetSeqId(query.value("seqId").toInt());
				messageOperate->SetType(query.value("type").toInt());
				messageOperate->SetMfrom(query.value("mfrom").toString());
				messageOperate->SetMsgId(query.value("msgId").toString());
				messageOperate->SetMto(query.value("mto").toString());
				messageOperate->SetTimestamp(query.value("timestamp").toInt());
				messageOperate->SetCatalogId(query.value("catalogId").toInt());
				messageOperate->SetOpMsgId(query.value("opMsgId").toString());
				messageOperate->SetOpFeedId(query.value("opFeedId").toString());
				messageOperate->SetOpName(query.value("opName").toString());
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(messageOperate);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO MessageOperate FAIL" << strLog;
			return false;
		}
	}
	return false;
}


bool TNMessageOperate::ClearAll()
{
	if (tableIsExist("MessageOperate"))
	{
		QSqlQuery query(*_db);
		query.exec("DELETE FROM MessageOperate");
	}
	return true;
}

void TNMessageOperate::checkTable()
{

}

void TNMessageOperate::createTable()
{
	if (!tableIsExist("MessageOperate"))
	{
		QSqlQuery query(*_db);
		query.exec("Create  TABLE MAIN.[MessageOperate]([msgId] text UNIQUE"
			", [seqId] integer"
			", [type] integer"
			", [mfrom] text"
			", [mto] text"
			", [timestamp] integer"
			", [catalogId] integer"
			", [opMsgId] text"
			", [opFeedId] text"
			", [opName] text"
			", Primary Key(msgId, seqId))");
	}
}

void TNMessageOperate::dropTable()
{
	if (tableIsExist("MessageOperate"))
	{
		QSqlQuery query(*_db);
		query.exec("Drop Table MAIN.[MessageOperate]");
	}
}
