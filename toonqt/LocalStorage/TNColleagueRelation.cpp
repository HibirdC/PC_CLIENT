#include <memory>

#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>


#include "TNColleagueRelation.h"


TNColleagueRelation::TNColleagueRelation()
:TNBaseTable()
{
}


TNColleagueRelation::~TNColleagueRelation()
{
}
int  TNColleagueRelation::InsertDatas(QList<TableBasePtr> relationList)
{
	int mCount = 0;
	if (!tableIsExist("ColleagueRelation"))
	{
		return mCount;
	}
	QList<TableBasePtr>::iterator it;
	beginTransaction();
	for (it = relationList.begin(); it != relationList.end(); it++)
	{
		st_ColleagueRelationPtr relation = std::dynamic_pointer_cast<st_ColleagueRelation>(*it);
		
		QString strSql;
		if (keyIsExist("ColleagueRelation", "feed_belongTo_group", relation->GetFeedBelongToGroup()))
		{
			strSql = QString("UPDATE ColleagueRelation SET feedId = '%1', belongTo = '%2', groupId= '%3',relationId = '%4', staffId = '%5', updateTime = '%6', createTime = '%7', comId ='%8', orderValue= '%9' where feed_belongTo_group = '%10'")
				.arg(relation->GetFeedId()).arg(relation->GetBelongTo())
				.arg(relation->GetGroupId()).arg(relation->GetRelationId()).arg(relation->GetStaffId())
				.arg(relation->GetUpdateTime()).arg(relation->GetCreateTime()).arg(relation->GetComId())
				.arg(relation->GetOrderValue()).arg(relation->GetFeedBelongToGroup());
		}
		else
		{
			strSql = QString("INSERT INTO ColleagueRelation (feed_belongTo_group, feedId, belongTo, groupId,"
				"relationId, staffId, updateTime, createTime, comId, orderValue)"
				"VALUES('%1', '%2','%3', '%4','%5', '%6','%7', '%8','%9', '%10')")
				.arg(relation->GetFeedBelongToGroup()).arg(relation->GetFeedId()).arg(relation->GetBelongTo())
				.arg(relation->GetGroupId()).arg(relation->GetRelationId()).arg(relation->GetStaffId())
				.arg(relation->GetUpdateTime()).arg(relation->GetCreateTime()).arg(relation->GetComId())
				.arg(relation->GetOrderValue());
		}
		QSqlQuery query(*_db);
		bool ret = query.exec(strSql);
		if (!ret)
		{
			qDebug() << "SQL Error ColleagueRelation: "<< strSql;
			qDebug() << query.lastError();
		}
		mCount = ret ? mCount + 1 : mCount;
	}
	commitTransaction();
	return mCount;
}
bool TNColleagueRelation::InsertDatas(st_ColleagueRelationPtr relation)
{
	if (tableIsExist("ColleagueRelation"))
	{
		QSqlQuery query(*_db);
		QString strSql = QString("INSERT INTO ColleagueRelation (feed_belongTo_group, feedId, belongTo, groupId,"
			"relationId, staffId, updateTime, createTime, comId, orderValue)"
			"VALUES('%1', '%2','%3', '%4','%5', '%6','%7', '%8','%9', '%10')")
			.arg(relation->GetFeedBelongToGroup()).arg(relation->GetFeedId()).arg(relation->GetBelongTo())
			.arg(relation->GetGroupId()).arg(relation->GetRelationId()).arg(relation->GetStaffId())
			.arg(relation->GetUpdateTime()).arg(relation->GetCreateTime()).arg(relation->GetComId())
			.arg(relation->GetOrderValue());
		bool ret = query.exec(strSql);
		if (ret)
		{
			return true;
		} 
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO ColleagueRelation FAIL" << strLog;
		}
	}
	return false;
}

bool TNColleagueRelation::Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue)
{
	if (tableIsExist("ColleagueRelation"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec(QString("select *from ColleagueRelation where %1='%2'").arg(queryItem).arg(queryValue));
		if (ret)
		{
			while (query.next())
			{
				st_ColleagueRelationPtr relation = std::make_shared<st_ColleagueRelation>();
				relation->SetFeedBelongToGroup(query.value("feed_belongTo_group").toString());
				relation->SetFeedId(query.value("feedId").toString());
				relation->SetBelongTo(query.value("belongTo").toString());
				relation->SetGroupId(query.value("groupId").toString());
				relation->SetRelationId(query.value("relationId").toString());
				relation->SetStaffId(query.value("staffId").toString());
				relation->SetUpdateTime(query.value("updateTime").toString());
				relation->SetCreateTime(query.value("createTime").toString());
				relation->SetComId(query.value("comId").toString());
				relation->SetOrderValue(query.value("orderValue").toString());
				if (relation->GetFeedBelongToGroup().isEmpty() || relation->GetComId().isEmpty()
					|| relation->GetFeedId().isEmpty() || relation->GetBelongTo().isEmpty() ||
					relation->GetGroupId().isEmpty() || relation->GetStaffId().isEmpty() || relation->GetRelationId().isEmpty())
				{
					qDebug() << "[TNColleagueRelation] Error Query Invalid relation";
					continue;
				}
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(relation);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO ColleagueRelation FAIL" << strLog;
			return false;
		}
	}
	return false;
}


bool TNColleagueRelation::GetAllFields(TableBaseVec &tableBaseVec)
{
	if (tableIsExist("ColleagueRelation"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec("select *from ColleagueRelation");
		if (ret)
		{
			while (query.next())
			{
				st_ColleagueRelationPtr relation = std::make_shared<st_ColleagueRelation>();
				relation->SetFeedBelongToGroup(query.value("feed_belongTo_group").toString());
				relation->SetFeedId(query.value("feedId").toString());
				relation->SetBelongTo(query.value("belongTo").toString());
				relation->SetGroupId(query.value("groupId").toString());
				relation->SetRelationId(query.value("relationId").toString());
				relation->SetStaffId(query.value("staffId").toString());
				relation->SetUpdateTime(query.value("updateTime").toString());
				relation->SetCreateTime(query.value("createTime").toString());
				relation->SetComId(query.value("comId").toString());
				relation->SetOrderValue(query.value("orderValue").toString());
				if (relation->GetFeedBelongToGroup().isEmpty() || relation->GetComId().isEmpty()
					|| relation->GetFeedId().isEmpty() || relation->GetBelongTo().isEmpty()||
					relation->GetGroupId().isEmpty() || relation->GetStaffId().isEmpty() || relation->GetRelationId().isEmpty())
				{
					qDebug() << "[TNColleagueRelation] Error GetAllFields Invalid relation";
					continue;
				}
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(relation);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO ColleagueRelation FAIL" << strLog;
			return false;
		}
	}
	return false;
}


bool TNColleagueRelation::ClearAll()
{
	if (tableIsExist("ColleagueRelation"))
	{
		QSqlQuery query(*_db);
		query.exec("DELETE FROM ColleagueRelation");
	}
	return true;
}

void TNColleagueRelation::checkTable()
{

}

void TNColleagueRelation::createTable()
{
	if (!tableIsExist("ColleagueRelation"))
	{
		QSqlQuery query(*_db);
		query.exec("Create  TABLE MAIN.[ColleagueRelation]([feed_belongTo_group] varchar(50)  PRIMARY KEY UNIQUE NOT NULL,"
			"[feedId] varchar(40), [belongTo] varchar(40), [groupId] varchar(16), [relationId], [staffId] varchar(40),"
			"[updateTime] varchar(40), [createTime] varchar(40), [comId] varchar(8), [orderValue] varchar(2))");
	}
}

void TNColleagueRelation::dropTable()
{
	if (tableIsExist("ColleagueRelation"))
	{
		QSqlQuery query(*_db);
		query.exec("Drop Table MAIN.[ColleagueRelation]");
	}
}
int  TNColleagueRelation::Delete(const QString &queryItem, QList<QString> queryValueList)
{
	int nCount = 0;
	QList<QString>::iterator it;
	beginTransaction();
	for (it = queryValueList.begin(); it != queryValueList.end(); it++)
	{
		bool res = false;
		QSqlQuery query(*_db);
		res = query.exec(QString("DELETE FROM ColleagueRelation where %1 = '%2'").arg(queryItem).arg((*it)));
		if (res)
			nCount++;
	}
	commitTransaction();
	return nCount;
}
bool TNColleagueRelation::Delete(const QString &queryItem, const QString &queryValue)
{
	bool res = false;
	QSqlQuery query(*_db);
	res = query.exec(QString("DELETE FROM ColleagueRelation where %1 = '%2'").arg(queryItem).arg(queryValue));
	if (!res)
		qDebug() << "delete ColleagueRelation fail" << query.lastError().text();
	return res;
}
