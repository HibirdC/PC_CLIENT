#include <memory>

#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>


#include "TNNoticelistTable.h"


TNNoticelistTable::TNNoticelistTable()
:TNBaseTable()
{
	createTable();
}


TNNoticelistTable::~TNNoticelistTable()
{
}

bool TNNoticelistTable::InsertDatas(NoticelistTablePtr noticeList)
{
	if (tableIsExist("NOTICELIST"))
	{
		QSqlQuery query(*_db);

		QString strSql = QString("INSERT INTO NOTICELIST (ID, NAME, DEPARTMENT,AVATAR) VALUES('%1', '%2', '%3', '%4')")
			.arg(noticeList->GetID()).arg(noticeList->GetName()).arg(noticeList->GetDepartMent()).arg(noticeList->GetAvatar());
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

bool TNNoticelistTable::GetAllFields(TableBaseVec &tableBaseVec)
{
	if (tableIsExist("NOTICELIST"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec("select *from NOTICELIST");
		if (ret)
		{
			while (query.next())
			{
				NoticelistTablePtr noticeListTable = std::make_shared<NoticelistTable>();
				noticeListTable->SetID(query.value("ID").toString());
				noticeListTable->SetName(query.value("NAME").toString());
				noticeListTable->SetDepartMent(query.value("DEPARTMENT").toString());
				noticeListTable->SetAvatar(query.value("AVATAR").toString());
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(noticeListTable);
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

bool TNNoticelistTable::GetAllFieldsOfTableNameByField(const QString &fieldName, const QString &fieldValue, TableBaseVec &tableBaseVec)
{
	if (fieldName.isEmpty() || fieldValue.isEmpty())
	{
		return false;
	}
	if (tableIsExist("NOTICELIST"))
	{
		QSqlQuery query(*_db);
		QString strSql = QString("select *from NOTICELIST where %1='%2'").arg(fieldName).arg(fieldValue);
		bool ret = query.exec(strSql);
		if (ret)
		{
			while (query.next())
			{
				NoticelistTablePtr noticeListTable = std::make_shared<NoticelistTable>();
				noticeListTable->SetID(query.value("ID").toString());
				noticeListTable->SetName(query.value("NAME").toString());
				noticeListTable->SetDepartMent(query.value("DEPARTMENT").toString());
				noticeListTable->SetAvatar(query.value("AVATAR").toString());
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(noticeListTable);
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


bool TNNoticelistTable::ClearAll()
{
	if (tableIsExist("NOTICELIST"))
	{
		QSqlQuery query(*_db);
		beginTransaction();
		query.exec("DELETE FROM NOTICELIST");
		commitTransaction();
	}
	return true;
}

void TNNoticelistTable::checkTable()
{

}

void TNNoticelistTable::createTable()
{
	if (!tableIsExist("NOTICELIST"))
	{
		QSqlQuery query(*_db);
		beginTransaction();
		query.exec("Create  TABLE MAIN.[NOTICELIST]([AVATAR] varchar(512), [DEPARTMENT] varchar(64),"
			"[NAME] varchar(64), [ID] varchar(64) PRIMARY KEY UNIQUE NOT NULL)");
		commitTransaction();
	}
}

void TNNoticelistTable::dropTable()
{
	if (tableIsExist("NOTICELIST"))
	{
		QSqlQuery query(*_db);
		beginTransaction();
		query.exec("Drop Table MAIN.[NOTICELIST]");
		commitTransaction();
	}
}
