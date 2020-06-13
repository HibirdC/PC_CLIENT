#include <QSqlError>
#include <QDebug>

#include "TNNoticeDetailTable.h"
#include "QSqlQuery"


TNNoticeDetailTable::TNNoticeDetailTable()
:TNBaseTable()
{
	createTable();
}


TNNoticeDetailTable::~TNNoticeDetailTable()
{
}

bool TNNoticeDetailTable::InsertDatas(NoticeDetailTablePtr noticeDetail)
{
	if (tableIsExist("NOTICEDETAIL"))
	{
		QSqlQuery query(*_db);

		QString strSql = QString("INSERT INTO NOTICEDETAIL (ID, ROW, PEOPLE,AVATAR,CONTENT) VALUES('%1', %2, %3,'%4','%5')")
			.arg(noticeDetail->GetID()).arg(noticeDetail->GetRow()).arg(noticeDetail->GetPeople()).arg(noticeDetail->GetAvatar())
			.arg(noticeDetail->GetContext());
		bool ret = query.exec(strSql);
		if (ret)
		{
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO NOTICELIST FAIL" << strLog;
		}
	}
	return false;
}

bool TNNoticeDetailTable::GetAllFields(TableBaseVec &tableBaseVec)
{
	if (tableIsExist("NOTICEDETAIL"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec("select *from NOTICEDETAIL");
		if (ret)
		{
			while (query.next())
			{
				NoticeDetailTablePtr noticeDetailTable = std::make_shared<NoticeDetailTable>();
				noticeDetailTable->SetID(query.value("ID").toString());
				noticeDetailTable->SetRow(query.value("ROW").toInt());
				noticeDetailTable->SetAvatar(query.value("AVATAR").toString());
				noticeDetailTable->SetPeople(query.value("PEOPLE").toInt());
				noticeDetailTable->SetContext(query.value("CONTENT").toString());
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(noticeDetailTable);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO NOTICELIST FAIL" << strLog;
			return false;
		}
	}
	return false;
}

bool TNNoticeDetailTable::GetAllFieldsOfTableNameByField(const QString &fieldName, const QString &fieldValue, TableBaseVec &tableBaseVec)
{
	if (fieldName.isEmpty() || fieldValue.isEmpty())
	{
		return false;
	}
	if (tableIsExist("NOTICEDETAIL"))
	{
		QSqlQuery query(*_db);
		QString strSql = QString("select *from NOTICEDETAIL where %1='%2'").arg(fieldName).arg(fieldValue);
		bool ret = query.exec(strSql);
		if (ret)
		{
			while (query.next())
			{
				NoticeDetailTablePtr noticeDetailTable = std::make_shared<NoticeDetailTable>();
				noticeDetailTable->SetID(query.value("ID").toString());
				noticeDetailTable->SetRow(query.value("ROW").toInt());
				noticeDetailTable->SetAvatar(query.value("AVATAR").toString());
				noticeDetailTable->SetPeople(query.value("PEOPLE").toInt());
				noticeDetailTable->SetContext(query.value("CONTENT").toString());
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(noticeDetailTable);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO NOTICELIST FAIL" << strLog;
			return false;
		}
	}
	return false;
}

bool TNNoticeDetailTable::ClearAll()
{
	return true;
}

void TNNoticeDetailTable::checkTable()
{

}

void TNNoticeDetailTable::createTable()
{
	if (!tableIsExist("NOTICEDETAIL"))
	{
		QSqlQuery query(*_db);
		beginTransaction();
		query.exec("Create  TABLE MAIN.[NOTICEDETAIL]([PEOPLE] INt, [CONTENT] Text, [ROW] INt NOT NULL,"
			"[ID] varchar(64) NOT NULL, [AVATAR] varchar(512), Primary Key(ROW, ID))");
		commitTransaction();
	}
}

void TNNoticeDetailTable::dropTable()
{
	if (tableIsExist("NOTICEDETAIL"))
	{
		QSqlQuery query(*_db);
		beginTransaction();
		query.exec("Drop Table MAIN.[NOTICEDETAIL]");
		commitTransaction();
	}
}
