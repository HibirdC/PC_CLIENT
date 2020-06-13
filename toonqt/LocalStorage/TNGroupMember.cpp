#include <memory>

#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>

#include "TNDbUtil.h"
#include "TNGroupMember.h"


TNGroupMember::TNGroupMember()
:TNBaseTable()
{
}


TNGroupMember::~TNGroupMember()
{
}
int  TNGroupMember::InsertDatas(QList<TableBasePtr> groupMemberList)
{
	int mCount = 0;
	if (!tableIsExist("GroupMember"))
	{
		return mCount;
	}
	QList<TableBasePtr>::iterator it;
	beginTransaction();
	for (it = groupMemberList.begin(); it != groupMemberList.end(); it++)
	{
		st_GroupMemberPtr groupMember = std::dynamic_pointer_cast<st_GroupMember>(*it);

		if (keyIsExistExt("GroupMember", "groupId", groupMember->GetGroupId(), "feedId", groupMember->GetFeedId()))
		{
			QSqlQuery query(*_db);
			query.prepare(QString("UPDATE GroupMember SET groupTopic = ?,name = ?,headerImage = ?,status = ?,timestamp = ?,isUpdate = ?,permissionType = ? where groupId = '%1' and feedId = '%2'")
				.arg(groupMember->GetGroupId()).arg(groupMember->GetFeedId()));

			query.bindValue(0, groupMember->GetGroupTopic());
			query.bindValue(1, groupMember->GetName());
			query.bindValue(2, groupMember->GetHeaderImage());
			query.bindValue(3, groupMember->GetStatus());
			query.bindValue(4, groupMember->GetTimestamp());
			query.bindValue(5, groupMember->GetIsUpdate());
			query.bindValue(6, groupMember->GetPermissionType());

			bool ret = query.exec();
			if (!ret)
			{
				QString strLog = query.lastError().text();
				qDebug() << "update GroupMember FAIL" << strLog;
			}
			mCount = ret ? mCount + 1 : mCount;
		}
		else
		{
			QSqlQuery query(*_db);
			query.prepare("INSERT INTO GroupMember (groupId, groupTopic, feedId, name, headerImage, status, timestamp, isUpdate, permissionType)"
				"VALUES (:groupId, :groupTopic, :feedId, :name, :headerImage, :status, :timestamp, :isUpdate,:permissionType)");

			query.bindValue(":groupId", groupMember->GetGroupId());
			query.bindValue(":groupTopic", groupMember->GetGroupTopic());
			query.bindValue(":feedId", groupMember->GetFeedId());
			query.bindValue(":name", groupMember->GetName());
			query.bindValue(":headerImage", groupMember->GetHeaderImage());
			query.bindValue(":status", groupMember->GetStatus());
			query.bindValue(":timestamp", groupMember->GetTimestamp());
			query.bindValue(":isUpdate", groupMember->GetIsUpdate());
			query.bindValue(":permissionType", groupMember->GetPermissionType());

			bool ret = query.exec();
			if (!ret)
			{
				QString strLog = query.lastError().text();
				qDebug() << "INSERT INTO GroupMember FAIL" << strLog;
			}
			mCount = ret ? mCount + 1 : mCount;
		}
	}
	commitTransaction();
	return mCount;
}
bool TNGroupMember::InsertDatas(st_GroupMemberPtr groupMember)
{
	if (tableIsExist("GroupMember"))
	{
		if (keyIsExistExt("GroupMember", "groupId", groupMember->GetGroupId(), "feedId", groupMember->GetFeedId())){
			QSqlQuery query(*_db);
			query.prepare(QString("UPDATE GroupMember SET groupTopic = ?,name = ?,headerImage = ?,status = ?,timestamp = ?,isUpdate = ?,permissionType = ? where groupId = '%1' and feedId = '%2'")
				.arg(groupMember->GetGroupId()).arg(groupMember->GetFeedId()));

			query.bindValue(0, groupMember->GetGroupTopic());
			query.bindValue(1, groupMember->GetName());
			query.bindValue(2, groupMember->GetHeaderImage());
			query.bindValue(3, groupMember->GetStatus());
			query.bindValue(4, groupMember->GetTimestamp());
			query.bindValue(5, groupMember->GetIsUpdate());
			query.bindValue(6, groupMember->GetPermissionType());

			bool ret = query.exec();
			if (ret){
				return true;
			}
			else{
				QString strLog = query.lastError().text();
				qDebug() << "update GroupMember FAIL" << strLog;
			}
		}
		else{
			QSqlQuery query(*_db);
			query.prepare("INSERT INTO GroupMember (groupId, groupTopic, feedId, name, headerImage, status, timestamp, isUpdate, permissionType)"
				"VALUES (:groupId, :groupTopic, :feedId, :name, :headerImage, :status, :timestamp, :isUpdate,:permissionType)");

			query.bindValue(":groupId", groupMember->GetGroupId());
			query.bindValue(":groupTopic", groupMember->GetGroupTopic());
			query.bindValue(":feedId", groupMember->GetFeedId());
			query.bindValue(":name", groupMember->GetName());
			query.bindValue(":headerImage", groupMember->GetHeaderImage());
			query.bindValue(":status", groupMember->GetStatus());
			query.bindValue(":timestamp", groupMember->GetTimestamp());
			query.bindValue(":isUpdate", groupMember->GetIsUpdate());
			query.bindValue(":permissionType", groupMember->GetPermissionType());

			bool ret = query.exec();
			if (ret)
				return true;
			else{
				QString strLog = query.lastError().text();
				qDebug() << "INSERT INTO GroupMember FAIL" << strLog;
			}
		}
	}
	return false;
}

bool TNGroupMember::Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue)
{
	if (tableIsExist("GroupMember"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec(QString("select *from GroupMember where %1='%2'").arg(queryItem).arg(queryValue));
		if (ret)
		{
			while (query.next())
			{
				st_GroupMemberPtr groupMember = std::make_shared<st_GroupMember>();
				groupMember->SetGroupId(query.value("groupId").toString());
				groupMember->SetGroupTopic(query.value("groupTopic").toString());
				groupMember->SetFeedId(query.value("feedId").toString());
				groupMember->SetName(query.value("name").toString());
				groupMember->SetHeaderImage(query.value("headerImage").toString());
				groupMember->SetStatus(query.value("status").toInt());
                groupMember->SetTimestamp(query.value("timestamp").toDouble());
				groupMember->SetIsUpdate(query.value("isUpdate").toInt());
				groupMember->SetPermissionType(query.value("permissionType").toString());
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(groupMember);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO GroupMember FAIL" << strLog;
			return false;
		}
	}
	return false;
}

bool TNGroupMember::GetAllFields(TableBaseVec &tableBaseVec)
{
	if (tableIsExist("GroupMember"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec("select *from GroupMember");
		if (ret)
		{
			while (query.next())
			{
				st_GroupMemberPtr groupMember = std::make_shared<st_GroupMember>();
				groupMember->SetGroupId(query.value("groupId").toString());
				groupMember->SetGroupTopic(query.value("groupTopic").toString());
				groupMember->SetFeedId(query.value("feedId").toString());
				groupMember->SetName(query.value("name").toString());
				groupMember->SetHeaderImage(query.value("headerImage").toString());
				groupMember->SetStatus(query.value("status").toInt());
                groupMember->SetTimestamp(query.value("timestamp").toDouble());
				groupMember->SetIsUpdate(query.value("isUpdate").toInt());
				groupMember->SetPermissionType(query.value("permissionType").toString());
				if (groupMember->GetGroupId().isEmpty() || groupMember->GetFeedId().isEmpty())
				{
					qDebug() << "[TNGroupMember] Error GetAllFields Invalid GroupMember";
					continue;
				}

				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(groupMember);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO GroupMember FAIL" << strLog;
			return false;
		}
	}
	return false;
}


bool TNGroupMember::ClearAll()
{
	if (tableIsExist("GroupMember"))
	{
		QSqlQuery query(*_db);
		query.exec("DELETE FROM GroupMember");
	}
	return true;
}
int TNGroupMember::Delete(const QString &queryItem, QList<QString> queryValueList)
{
	int nCount = 0;
	QList<QString>::iterator it;
	beginTransaction();
	for (it = queryValueList.begin(); it != queryValueList.end(); it++)
	{
		bool res = false;
		QSqlQuery query(*_db);
		res = query.exec(QString("DELETE FROM GroupMember where %1 = '%2'").arg(queryItem).arg(*it));
		if (res)
			nCount++;
	}
	commitTransaction();
	return nCount;
}
int  TNGroupMember::Delete(QList<QVector<QString>> groupMemberList)
{
	int mCount = 0;
	if (!tableIsExist("GroupMember"))
	{
		return mCount;
	}
	beginTransaction();
	QList<QVector<QString>>::iterator it;
	for (it = groupMemberList.begin(); it != groupMemberList.end(); it++)
	{
		QVector<QString> deleteObject = (*it);
		if (deleteObject.size() != 4)
		{
			continue;
		}
		QSqlQuery query(*_db);
		bool ret = query.exec(QString("DELETE FROM GroupMember where %1 = '%2' and  %3 = '%4'").arg(deleteObject[0]).arg(deleteObject[1]).arg(deleteObject[2]).arg(deleteObject[3]));
		mCount = ret ? mCount + 1 : mCount;
	}
	commitTransaction();
	return mCount;
}
bool TNGroupMember::Delete(const QString &queryItem, const QString &queryValue)
{
	bool res = false;
	if (tableIsExist("GroupMember"))
	{
		QSqlQuery query(*_db);
		res = query.exec(QString("DELETE FROM GroupMember where %1 = '%2'").arg(queryItem).arg(queryValue));
		if (!res)
			qDebug() << "delete GroupInfo fail" << query.lastError().text();
	}
	return res;

}

bool TNGroupMember::DeleteEx(const QString &queryItem, const QString &queryValue, const QString &queryItemEx, const QString &queryValueEx)
{

	bool res = false;
	if (tableIsExist("GroupMember"))
	{
		QSqlQuery query(*_db);
		res = query.exec(QString("DELETE FROM GroupMember where %1 = '%2' and  %3 = '%4'").arg(queryItem).arg(queryValue).arg(queryItemEx).arg(queryValueEx));
		if (!res)
			qDebug() << "deleteEx GroupInfo fail" << query.lastError().text();
	}
	return res;

}

void TNGroupMember::checkTable()
{

}

void TNGroupMember::createTable()
{
	if (!tableIsExist("GroupMember")){
		QSqlQuery query(*_db);
		query.exec("Create  TABLE MAIN.[GroupMember]([groupId] varchar(40)"
			", [groupTopic] text"
			", [feedId] text"
			", [name] text"
			", [headerImage] text"
			", [status] integer"
			", [timestamp] integer"
			", [isUpdate] integer"
			", [permissionType] text"
			", Primary Key(groupId, feedId))");
	}
	else{
		QString strSql = "select * from sqlite_master where name='GroupMember' and sql like '%permissionType%'";
		QSqlQuery query(*_db);
		query.exec(strSql);
		if (!query.next())
		{
			QSqlQuery query(*_db);
			query.exec("ALTER TABLE 'GroupMember' ADD  'permissionType' text");
		}
	}
}

void TNGroupMember::dropTable()
{
	if (tableIsExist("GroupMember"))
	{
		QSqlQuery query(*_db);
		query.exec("Drop Table MAIN.[GroupMember]");
	}
}
bool TNGroupMember::keyIsExistExt(const QString& tableName, const QString& key, const QString& Value,
	const QString &keyExt, const QString &valueExt)
{
	bool result = false;
	if (tableName.isEmpty() || key.isEmpty())
	{
		return result;
	}
	QSqlQuery  query(*_db);
	QString sql = QString("select * from %1  where %2 ='%3' and %4= '%5'").arg(tableName).arg(key).arg(Value).arg(keyExt).arg(valueExt);
	bool ret = query.exec(sql);
	if (ret && query.next())
	{
		result = true;
	}
	return result;
}