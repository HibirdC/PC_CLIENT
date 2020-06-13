#include <memory>

#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>


#include "TNColleagueGroup.h"


TNColleagueGroup::TNColleagueGroup()
:TNBaseTable()
{
}


TNColleagueGroup::~TNColleagueGroup()
{
}
int  TNColleagueGroup::InsertDatas(QList<TableBasePtr> myColleagueGroupList)
{
	int mCount = 0;
	if (!tableIsExist("ColleagueGroup"))
	{
		return mCount;
	}
	QList<TableBasePtr>::iterator it;
	beginTransaction();
	for (it = myColleagueGroupList.begin(); it != myColleagueGroupList.end(); it++)
	{
		st_ColleagueGroupPtr group = std::dynamic_pointer_cast<st_ColleagueGroup>(*it);
		QString strSql;
		if (keyIsExist("ColleagueGroup", "groupId", group->GetGroupId()))
		{
			strSql = QString("UPDATE ColleagueGroup SET comId = '%1', createTime = '%2', groupName = '%3', orderValue = '%4', updateTime = '%5' WHERE groupId = '%6'")
				.arg(group->GetComId()).arg(group->GetCreateTime()).arg(group->GetGroupName()).arg(group->GetOrderValue()).arg(group->GetUpdateTime()).arg(group->GetGroupId());
		}
		else
		{
			strSql = QString("INSERT INTO ColleagueGroup (comId, createTime, groupId, groupName, orderValue, updateTime)"
				"VALUES('%1', '%2','%3', '%4','%5', '%6')")
				.arg(group->GetComId()).arg(group->GetCreateTime()).arg(group->GetGroupId())
				.arg(group->GetGroupName()).arg(group->GetOrderValue()).arg(group->GetUpdateTime());
		}
		QSqlQuery query(*_db);
		bool ret = query.exec(strSql);
		if (!ret)
		{
			qDebug() << "SQL Error FEED: " + strSql;
			qDebug() << query.lastError();
		}
		mCount = ret ? mCount + 1 : mCount;
	}
	commitTransaction();
	return mCount;
}
bool TNColleagueGroup::InsertDatas(st_ColleagueGroupPtr group)
{
	if (tableIsExist("ColleagueGroup"))
	{
		QSqlQuery query(*_db);
		QString strSql = QString("INSERT INTO ColleagueGroup (comId, createTime, groupId, groupName, orderValue, updateTime)"
			"VALUES('%1', '%2','%3', '%4','%5', '%6')")
			.arg(group->GetComId()).arg(group->GetCreateTime()).arg(group->GetGroupId())
			.arg(group->GetGroupName()).arg(group->GetOrderValue()).arg(group->GetUpdateTime());
		bool ret = query.exec(strSql);
		if (ret)
		{
			return true;
		} 
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO ColleagueGroup FAIL" << strLog;
		}
	}
	return false;
}

bool TNColleagueGroup::Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue)
{
	if (tableIsExist("ColleagueGroup"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec(QString("select *from ColleagueGroup where %1='%2'").arg(queryItem).arg(queryValue));
		if (ret)
		{
			while (query.next())
			{
				st_ColleagueGroupPtr group = std::make_shared<st_ColleagueGroup>();
				group->SetComId(query.value("comId").toString());
				group->SetCreateTime(query.value("createTime").toString());
				group->SetGroupId(query.value("groupId").toString());
				group->SetGroupName(query.value("groupName").toString());
				group->SetOrderValue(query.value("orderValue").toString());
				group->SetUpdateTime(query.value("updateTime").toString());
				if (group->GetGroupId().isEmpty() || group->GetComId().isEmpty()
					|| group->GetGroupName().isEmpty())
				{
					qDebug() << "[TNColleagueGroup] Error Query Invalid ColleagueGroup";
					continue;
				}
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(group);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO ColleagueGroup FAIL" << strLog;
			return false;
		}
	}
	return false;
}
int  TNColleagueGroup::Delete(const QString &queryItem, QList<QString> queryValueList)
{
	int nCount = 0;
	QList<QString>::iterator it;
	beginTransaction();
	for (it = queryValueList.begin(); it != queryValueList.end(); it++)
	{
		bool res = false;
		QSqlQuery query(*_db);
		res = query.exec(QString("DELETE FROM ColleagueGroup where %1 = '%2'").arg(queryItem).arg((*it)));
		if (res)
			nCount++;
	}
	commitTransaction();
	return nCount;
}
bool TNColleagueGroup::Delete(const QString &queryItem, const QString &queryValue)
{
	bool res = false;
	QSqlQuery query(*_db);
	res = query.exec(QString("DELETE FROM ColleagueGroup where %1 = '%2'").arg(queryItem).arg(queryValue));
	if (!res)
		qDebug() << "delete ColleagueGroup fail" << query.lastError().text();
	return res;
}


bool TNColleagueGroup::GetAllFields(TableBaseVec &tableBaseVec)
{
	if (tableIsExist("ColleagueGroup"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec("select *from ColleagueGroup");
		if (ret)
		{
			while (query.next())
			{
				st_ColleagueGroupPtr group = std::make_shared<st_ColleagueGroup>();
				group->SetComId(query.value("comId").toString());
				group->SetCreateTime(query.value("createTime").toString());
				group->SetGroupId(query.value("groupId").toString());
				group->SetGroupName(query.value("groupName").toString());
				group->SetOrderValue(query.value("orderValue").toString());
				group->SetUpdateTime(query.value("updateTime").toString());
				if (group->GetGroupId().isEmpty() || group->GetComId().isEmpty()
					|| group->GetGroupName().isEmpty())
				{
					qDebug() << "[TNColleagueGroup] Error GetAllFields Invalid ColleagueGroup";
					continue;
				}
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(group);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO ColleagueGroup FAIL" << strLog;
			return false;
		}
	}
	return false;
}


bool TNColleagueGroup::ClearAll()
{
	if (tableIsExist("ColleagueGroup"))
	{
		QSqlQuery query(*_db);
		query.exec("DELETE FROM ColleagueGroup");
	}
	return true;
}

void TNColleagueGroup::checkTable()
{

}

void TNColleagueGroup::createTable()
{
	if (!tableIsExist("ColleagueGroup"))
	{
		QSqlQuery query(*_db);
		query.exec("Create  TABLE MAIN.[ColleagueGroup]([comId] varchar(32) ,"
			"[createTime] varchar(32), [groupId] varchar(32) PRIMARY KEY UNIQUE NOT NULL,"
			"[groupName] text, [orderValue] varchar(2),[updateTime] varchar(32))");
	}
}

void TNColleagueGroup::dropTable()
{
	if (tableIsExist("ColleagueGroup"))
	{
		QSqlQuery query(*_db);
		query.exec("Drop Table MAIN.[ColleagueGroup]");
	}
}
