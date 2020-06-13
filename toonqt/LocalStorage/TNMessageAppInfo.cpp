#include <memory>

#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>


#include "TNMessageAppInfo.h"


TNMessageAppInfo::TNMessageAppInfo()
:TNBaseTable()
{
}


TNMessageAppInfo::~TNMessageAppInfo()
{
}

bool TNMessageAppInfo::InsertDatas(st_MessageAppInfoPtr messageAppInfo)
{
	if (tableIsExist("MessageAppInfo"))
	{
		QSqlQuery query(*_db);
		QString strSql = QString("INSERT INTO MessageAppInfo (appId, appCode, appTitle, appLittleIcon, isDelete, btnNumber, chatFlag) "
			"VALUES('%1', '%2','%3', '%4','%5', '%6','%7')")
			.arg(messageAppInfo->GetAppId()).arg(messageAppInfo->GetAppCode())
			.arg(messageAppInfo->GetAppTitle()).arg(messageAppInfo->GetAppLittleIcon())
			.arg(messageAppInfo->GetIsDelete()).arg(messageAppInfo->GetBtnNumber())
			.arg(messageAppInfo->GetChatFlag());
		bool ret = query.exec(strSql);
		if (ret)
		{
			return true;
		} 
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO MessageAppInfo FAIL" << strLog;
		}
	}
	return false;
}

bool TNMessageAppInfo::Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue)
{
	if (tableIsExist("MessageAppInfo"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec(QString("select *from MessageAppInfo where %1='%2'").arg(queryItem).arg(queryValue));
		if (ret)
		{
			while (query.next())
			{
				st_MessageAppInfoPtr messageAppInfo = std::make_shared<st_MessageAppInfo>();
				messageAppInfo->SetAppId(query.value("appId").toString());
				messageAppInfo->SetAppCode(query.value("appCode").toString());
				messageAppInfo->SetAppTitle(query.value("appTitle").toString());
				messageAppInfo->SetAppLittleIcon(query.value("appLittleIcon").toString());
				messageAppInfo->SetIsDelete(query.value("isDelete").toInt());
				messageAppInfo->SetBtnNumber(query.value("btnNumber").toInt());
				messageAppInfo->SetChatFlag(query.value("chatFlag").toInt());
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(messageAppInfo);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO MessageAppInfo FAIL" << strLog;
			return false;
		}
	}
	return false;
}


bool TNMessageAppInfo::GetAllFields(TableBaseVec &tableBaseVec)
{
	if (tableIsExist("MessageAppInfo"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec("select *from MessageAppInfo");
		if (ret)
		{
			while (query.next())
			{
				st_MessageAppInfoPtr messageAppInfo = std::make_shared<st_MessageAppInfo>();
				messageAppInfo->SetAppId(query.value("appId").toString());
				messageAppInfo->SetAppCode(query.value("appCode").toString());
				messageAppInfo->SetAppTitle(query.value("appTitle").toString());
				messageAppInfo->SetAppLittleIcon(query.value("appLittleIcon").toString());
				messageAppInfo->SetIsDelete(query.value("isDelete").toInt());
				messageAppInfo->SetBtnNumber(query.value("btnNumber").toInt());
				messageAppInfo->SetChatFlag(query.value("chatFlag").toInt());
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(messageAppInfo);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO MessageAppInfo FAIL" << strLog;
			return false;
		}
	}
	return false;
}


bool TNMessageAppInfo::ClearAll()
{
	if (tableIsExist("MessageAppInfo"))
	{
		QSqlQuery query(*_db);
		query.exec("DELETE FROM MessageAppInfo");
	}
	return true;
}

void TNMessageAppInfo::checkTable()
{

}

void TNMessageAppInfo::createTable()
{
	if (!tableIsExist("MessageAppInfo"))
	{
		QSqlQuery query(*_db);
		query.exec("Create  TABLE MAIN.[MessageAppInfo]([appId] text PRIMARY KEY"
			", [appCode] text DEFAULT ''"
			", [appTitle] text DEFAULT ''"
			", [appLittleIcon] text DEFAULT ''"
			", [isDelete] integer"
			", [btnNumber] integer"
			", [chatFlag] inteteger)");
	}
}

void TNMessageAppInfo::dropTable()
{
	if (tableIsExist("MessageAppInfo"))
	{
		QSqlQuery query(*_db);
		query.exec("Drop Table MAIN.[MessageAppInfo]");
	}
}
