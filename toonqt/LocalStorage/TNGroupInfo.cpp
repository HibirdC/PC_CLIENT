#include <memory>

#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>


#include "TNGroupInfo.h"


TNGroupInfo::TNGroupInfo()
:TNBaseTable()
{
}


TNGroupInfo::~TNGroupInfo()
{
}
int  TNGroupInfo::InsertDatas(QList<TableBasePtr> groupInfoList)
{
    /*
	int mCount = 0;
	bool ret = false;
	if (!tableIsExist("GroupInfo"))
	{
		return mCount;
	}
	QList<TableBasePtr>::iterator it;
	beginTransaction();
	for (it = groupInfoList.begin(); it != groupInfoList.end(); it++)
	{
		TableBaseVec groupList;
		st_GroupInfoPtr groupInfo = std::dynamic_pointer_cast<st_GroupInfo>(*it);
		if (Query(groupList, "groupId", groupInfo->GetGroupId()))
		{
			if (groupList.size() > 0)
			{
				//存在更新groupinfo信息
				QSqlQuery query(*_db);
				QString updateSql = QString("update GroupInfo set creatorFeedId = '%1', name = '%2', namePinyin = '%3', pinyinHeader ='%4',"
					"headerImage ='%5',topic ='%6',myFeedId ='%7',maxNum = '%8', currNum = '%9', disturbStatus = '%10', groupType = '%11' where groupId = '%12'")
					.arg(groupInfo->GetCreatorFeedId()).arg(groupInfo->GetName()).arg(groupInfo->GetNamePinyin())
					.arg(groupInfo->GetPinyinHeader()).arg(groupInfo->GetHeaderImage()).arg(groupInfo->GetTopic()).arg(groupInfo->GetMyFeedId())
					.arg(groupInfo->GetMaxNum()).arg(groupInfo->GetCurrNum()).arg(groupInfo->GetDisturbStatus()).arg(groupInfo->GetGroupType()).arg(groupInfo->GetGroupId());
				ret = query.exec(updateSql);
				if (!ret)
				{
					qDebug() << "SQL Error FEED: " + updateSql;
					qDebug() << query.lastError();
				}
				mCount = ret ? mCount + 1 : mCount;
			}
			else
			{
				QSqlQuery query(*_db);
				QString strSql = QString("INSERT INTO GroupInfo (groupId, creatorFeedId, name, namePinyin, pinyinHeader, headerImage,"
					"topic, myFeedId, maxNum, currNum, disturbStatus, groupType)"
					"VALUES('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8',  '%9', '%10',  '%11', '%12')")
					.arg(groupInfo->GetGroupId()).arg(groupInfo->GetCreatorFeedId()).arg(groupInfo->GetName()).arg(groupInfo->GetNamePinyin())
					.arg(groupInfo->GetPinyinHeader()).arg(groupInfo->GetHeaderImage()).arg(groupInfo->GetTopic()).arg(groupInfo->GetMyFeedId())
					.arg(groupInfo->GetMaxNum()).arg(groupInfo->GetCurrNum()).arg(groupInfo->GetDisturbStatus()).arg(groupInfo->GetGroupType());
				ret = query.exec(strSql);
				if (!ret)
				{
					qDebug() << "SQL Error FEED: " + strSql;
					qDebug() << query.lastError();
				}
				mCount = ret ? mCount + 1 : mCount;
			}
		}
	}
	commitTransaction();
	return mCount;
    */

    int mCount = 0;
    bool ret = false;
    if (!tableIsExist("GroupInfo"))
    {
        return mCount;
    }
    QList<TableBasePtr>::iterator it;
    beginTransaction();
    for (it = groupInfoList.begin(); it != groupInfoList.end(); it++)
    {
        TableBaseVec groupList;
        st_GroupInfoPtr groupInfo = std::dynamic_pointer_cast<st_GroupInfo>(*it);
		if (groupInfo->GetGroupId().isEmpty() || groupInfo->GetCreatorFeedId().isEmpty()
			|| groupInfo->GetCurrNum() == 0 || groupInfo->GetHeaderImage().isEmpty() ||
			groupInfo->GetMaxNum() == 0 || groupInfo->GetMyFeedId().isEmpty() || groupInfo->GetName().isEmpty()
			|| groupInfo->GetTopic().isEmpty())
		{
			qDebug() << "[TNGroupInfo]InsertDatas Invalid groupInfo";
			continue;
		}
        if (Query(groupList, "groupId", groupInfo->GetGroupId()))
        {
            if (groupList.size() > 0)
            {
                //存在更新groupinfo信息
                QSqlQuery query(*_db);
                query.prepare(QString("update GroupInfo set creatorFeedId = ?, name = ?, namePinyin = ?, pinyinHeader = ?,"
                                      " headerImage = ?, topic = ?, myFeedId = ?, maxNum = ?, currNum = ?, disturbStatus = ?, groupType = ?"
                                      " where groupId = '%1'").arg(groupInfo->GetGroupId()));

                query.bindValue(0, groupInfo->GetCreatorFeedId());
                query.bindValue(1, groupInfo->GetName());
                query.bindValue(2, groupInfo->GetNamePinyin());
                query.bindValue(3, groupInfo->GetPinyinHeader());
                query.bindValue(4, groupInfo->GetHeaderImage());
                query.bindValue(5, groupInfo->GetTopic());
                query.bindValue(6, groupInfo->GetMyFeedId());
                query.bindValue(7, groupInfo->GetMaxNum());
                query.bindValue(8, groupInfo->GetCurrNum());
                query.bindValue(9, groupInfo->GetDisturbStatus());
                query.bindValue(10, groupInfo->GetGroupType());

                ret = query.exec();
                if (!ret)
                {
                    qDebug() << "update SQL Error FEED failed. error=" << query.lastError();
                }
                mCount = ret ? mCount + 1 : mCount;
            }
            else
            {
                QSqlQuery query(*_db);
                query.prepare("INSERT INTO GroupInfo (groupId, creatorFeedId, name, namePinyin, pinyinHeader, headerImage, topic, myFeedId, maxNum, currNum, disturbStatus, groupType)"
                              " VALUES (:groupId, :creatorFeedId, :name, :namePinyin, :pinyinHeader, :headerImage, :topic, :myFeedId, :maxNum, :currNum, :disturbStatus, :groupType)");

                query.bindValue(":groupId", groupInfo->GetGroupId());
                query.bindValue(":creatorFeedId", groupInfo->GetCreatorFeedId());
                query.bindValue(":name", groupInfo->GetName());
                query.bindValue(":namePinyin", groupInfo->GetNamePinyin());
                query.bindValue(":pinyinHeader", groupInfo->GetPinyinHeader());
                query.bindValue(":headerImage", groupInfo->GetHeaderImage());
                query.bindValue(":topic", groupInfo->GetTopic());
                query.bindValue(":myFeedId", groupInfo->GetMyFeedId());
                query.bindValue(":maxNum", groupInfo->GetMaxNum());
                query.bindValue(":currNum", groupInfo->GetCurrNum());
                query.bindValue(":disturbStatus", groupInfo->GetDisturbStatus());
                query.bindValue(":groupType", groupInfo->GetGroupType());

                ret = query.exec();
                if (!ret)
                {
                    qDebug() << "INSERT SQL Error FEED failed. error=" << query.lastError();
                }
                mCount = ret ? mCount + 1 : mCount;
            }
        }
    }
    commitTransaction();
    return mCount;
}
bool TNGroupInfo::InsertDatas(st_GroupInfoPtr groupInfo)
{
    /*
	bool ret = false;
	if (tableIsExist("GroupInfo"))
	{
		TableBaseVec groupList;
		if (Query(groupList, "groupId", groupInfo->GetGroupId()))
		{
			if (groupList.size() > 0)
			{
				//存在更新groupinfo信息
				QSqlQuery query(*_db);
				QString updateSql = QString("update GroupInfo set creatorFeedId = '%1', name = '%2', namePinyin = '%3', pinyinHeader ='%4',"
					"headerImage ='%5',topic ='%6',myFeedId ='%7',maxNum = '%8', currNum = '%9', disturbStatus = '%10', groupType = '%11' where groupId = '%12'")
					.arg(groupInfo->GetCreatorFeedId()).arg(groupInfo->GetName()).arg(groupInfo->GetNamePinyin())
					.arg(groupInfo->GetPinyinHeader()).arg(groupInfo->GetHeaderImage()).arg(groupInfo->GetTopic()).arg(groupInfo->GetMyFeedId())
					.arg(groupInfo->GetMaxNum()).arg(groupInfo->GetCurrNum()).arg(groupInfo->GetDisturbStatus()).arg(groupInfo->GetGroupType()).arg(groupInfo->GetGroupId());
				ret = query.exec(updateSql);
				if (ret)
					return true;
				else
				{
					QString strLog = query.lastError().text();
					qDebug() << "update GroupInfo fail" << strLog;
				}
			}
			else
			{
				QSqlQuery query(*_db);
				QString strSql = QString("INSERT INTO GroupInfo (groupId, creatorFeedId, name, namePinyin, pinyinHeader, headerImage,"
					"topic, myFeedId, maxNum, currNum, disturbStatus, groupType)"
					"VALUES('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8',  '%9', '%10',  '%11', '%12')")
					.arg(groupInfo->GetGroupId()).arg(groupInfo->GetCreatorFeedId()).arg(groupInfo->GetName()).arg(groupInfo->GetNamePinyin())
					.arg(groupInfo->GetPinyinHeader()).arg(groupInfo->GetHeaderImage()).arg(groupInfo->GetTopic()).arg(groupInfo->GetMyFeedId())
					.arg(groupInfo->GetMaxNum()).arg(groupInfo->GetCurrNum()).arg(groupInfo->GetDisturbStatus()).arg(groupInfo->GetGroupType());
				ret = query.exec(strSql);
				if (ret)
					return true;
				else
				{
					QString strLog = query.lastError().text();
					qDebug() << "INSERT INTO GroupInfo FAIL" << strLog;
				}

			}
		}
	}
	return ret;
    */

    bool ret = false;
    if (tableIsExist("GroupInfo"))
    {
		if (groupInfo->GetGroupId().isEmpty() || groupInfo->GetCreatorFeedId().isEmpty()
			|| groupInfo->GetCurrNum() == 0 || groupInfo->GetHeaderImage().isEmpty() ||
			groupInfo->GetMaxNum() == 0 || groupInfo->GetMyFeedId().isEmpty() || groupInfo->GetName().isEmpty()
			|| groupInfo->GetTopic().isEmpty())
		{
			qDebug() << "[TNGroupInfo]InsertDatas Invalid groupInfo";
			return ret;
		}

        TableBaseVec groupList;
        if (Query(groupList, "groupId", groupInfo->GetGroupId()))
        {
            if (groupList.size() > 0)
            {
                //存在更新groupinfo信息
                QSqlQuery query(*_db);
                query.prepare(QString("update GroupInfo set creatorFeedId = ?, name = ?, namePinyin = ?, pinyinHeader = ?,"
                                      " headerImage = ?, topic = ?, myFeedId = ?, maxNum = ?, currNum = ?, disturbStatus = ?, groupType = ?"
                                      " where groupId = '%1'").arg(groupInfo->GetGroupId()));

                query.bindValue(0, groupInfo->GetCreatorFeedId());
                query.bindValue(1, groupInfo->GetName());
                query.bindValue(2, groupInfo->GetNamePinyin());
                query.bindValue(3, groupInfo->GetPinyinHeader());
                query.bindValue(4, groupInfo->GetHeaderImage());
                query.bindValue(5, groupInfo->GetTopic());
                query.bindValue(6, groupInfo->GetMyFeedId());
                query.bindValue(7, groupInfo->GetMaxNum());
                query.bindValue(8, groupInfo->GetCurrNum());
                query.bindValue(9, groupInfo->GetDisturbStatus());
                query.bindValue(10, groupInfo->GetGroupType());

                ret = query.exec();
                if (ret)
                {
                    return true;
                }
                else
                {
                    QString strLog = query.lastError().text();
                    qDebug() << "update GroupInfo fail" << strLog;
                }
            }
            else
            {
                QSqlQuery query(*_db);
                query.prepare("INSERT INTO GroupInfo (groupId, creatorFeedId, name, namePinyin, pinyinHeader, headerImage, topic, myFeedId, maxNum, currNum, disturbStatus, groupType)"
                              " VALUES (:groupId, :creatorFeedId, :name, :namePinyin, :pinyinHeader, :headerImage, :topic, :myFeedId, :maxNum, :currNum, :disturbStatus, :groupType)");

                query.bindValue(":groupId", groupInfo->GetGroupId());
                query.bindValue(":creatorFeedId", groupInfo->GetCreatorFeedId());
                query.bindValue(":name", groupInfo->GetName());
                query.bindValue(":namePinyin", groupInfo->GetNamePinyin());
                query.bindValue(":pinyinHeader", groupInfo->GetPinyinHeader());
                query.bindValue(":headerImage", groupInfo->GetHeaderImage());
                query.bindValue(":topic", groupInfo->GetTopic());
                query.bindValue(":myFeedId", groupInfo->GetMyFeedId());
                query.bindValue(":maxNum", groupInfo->GetMaxNum());
                query.bindValue(":currNum", groupInfo->GetCurrNum());
                query.bindValue(":disturbStatus", groupInfo->GetDisturbStatus());
                query.bindValue(":groupType", groupInfo->GetGroupType());

                ret = query.exec();
                if (ret)
                {
                    return true;
                }
                else
                {
                    QString strLog = query.lastError().text();
                    qDebug() << "INSERT INTO GroupInfo FAIL" << strLog;
                }
            }
        }
    }

    return ret;
}

bool TNGroupInfo::Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue)
{
	if (tableIsExist("GroupInfo"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec(QString("select *from GroupInfo where %1='%2'").arg(queryItem).arg(queryValue));
		if (ret)
		{
			while (query.next())
			{
				st_GroupInfoPtr groupInfo = std::make_shared<st_GroupInfo>();
				groupInfo->SetGroupId(query.value("groupId").toString());
				groupInfo->SetCreatorFeedId(query.value("creatorFeedId").toString());
				groupInfo->SetName(query.value("name").toString());
				groupInfo->SetNamePinyin(query.value("namePinyin").toString());
				groupInfo->SetPinyinHeader(query.value("pinyinHeader").toString());
				groupInfo->SetHeaderImage(query.value("headerImage").toString());
				groupInfo->SetTopic(query.value("topic").toString());
				groupInfo->SetMyFeedId(query.value("myFeedId").toString());
				groupInfo->SetMaxNum(query.value("maxNum").toInt());
				groupInfo->SetCurrNum(query.value("currNum").toInt());
				groupInfo->SetDisturbStatus(query.value("disturbStatus").toInt());
				groupInfo->SetGroupType(query.value("groupType").toInt());

				if (groupInfo->GetGroupId().isEmpty() || groupInfo->GetMyFeedId().isEmpty()
					|| groupInfo->GetName().isEmpty() || groupInfo->GetMaxNum() == 0
					|| groupInfo->GetCreatorFeedId().isEmpty() || groupInfo->GetTopic().isEmpty()
                    || groupInfo->GetCurrNum() <= 0)
				{
					qDebug() << "[TNGroupInfo] Error Query Invalid GroupChatInfo";
					continue;
				}

				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(groupInfo);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO GroupInfo FAIL" << strLog;
			return false;
		}
	}
	return false;
}

bool TNGroupInfo::UpdateSetValueByField(const QString &fieldName, const QString &fieldValue, const QString &whereName, const QString &whereValue)
{
	QSqlQuery query(*_db);
    query.prepare(QString("update GroupInfo set %1 = ? where %2 ='%3'").arg(fieldName).arg(whereName).arg(whereValue));
    query.bindValue(0, fieldValue);
    bool ret = query.exec();
	if (ret)
	{
		return true;
	}
	else
	{
		QString strLog = query.lastError().text();
		qDebug() << "update GroupInfo failed" << strLog;
		return false;
	}
}

bool TNGroupInfo::UpdateSetValueByFieldEx(const QString &fieldName, const QString &fieldValue,
                                          const QString &fieldNameEx, const QString &fieldValueEx,
                                          const QString &whereName, const QString &whereValue)
{
    QSqlQuery query(*_db);
    query.prepare(QString("update GroupInfo set %1 = ?, %2 = ? where %3 ='%4'").arg(fieldName).arg(fieldNameEx).arg(whereName).arg(whereValue));
    query.bindValue(0, fieldValue);
    query.bindValue(1, fieldValueEx);
    bool ret = query.exec();
    if (ret)
    {
        return true;
    }
    else
    {
        QString strLog = query.lastError().text();
        qDebug() << "update GroupInfo failed" << strLog;
        return false;
    }
}

bool TNGroupInfo::GetAllFields(TableBaseVec &tableBaseVec)
{
	if (tableIsExist("GroupInfo"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec("select *from GroupInfo");
		if (ret)
		{
			while (query.next())
			{
				st_GroupInfoPtr groupInfo = std::make_shared<st_GroupInfo>();
				groupInfo->SetGroupId(query.value("groupId").toString());
				groupInfo->SetCreatorFeedId(query.value("creatorFeedId").toString());
				groupInfo->SetName(query.value("name").toString());
				groupInfo->SetNamePinyin(query.value("namePinyin").toString());
				groupInfo->SetPinyinHeader(query.value("pinyinHeader").toString());
				groupInfo->SetHeaderImage(query.value("headerImage").toString());
				groupInfo->SetTopic(query.value("topic").toString());
				groupInfo->SetMyFeedId(query.value("myFeedId").toString());
				groupInfo->SetMaxNum(query.value("maxNum").toInt());
				groupInfo->SetCurrNum(query.value("currNum").toInt());
				groupInfo->SetDisturbStatus(query.value("disturbStatus").toInt());
				groupInfo->SetGroupType(query.value("groupType").toInt());
				if (groupInfo->GetGroupId().isEmpty() || groupInfo->GetMyFeedId().isEmpty()
					|| groupInfo->GetName().isEmpty() || groupInfo->GetMaxNum()== 0
					|| groupInfo->GetCreatorFeedId().isEmpty() || groupInfo->GetTopic().isEmpty()
                    ||groupInfo->GetCurrNum() <= 0)
				{
					qDebug() << "[TNGroupInfo] Error GetAllFields Invalid GroupChatInfo";
					continue;
				}
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(groupInfo);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO GroupInfo FAIL" << strLog;
			return false;
		}
	}
	return false;
}
int TNGroupInfo::Delete(const QString &queryItem, QList<QString> queryValueList)
{
	int nCount = 0;
	QList<QString>::iterator it;
	beginTransaction();
	for (it = queryValueList.begin(); it != queryValueList.end(); it++)
	{
		bool res = false;
		QSqlQuery query(*_db);
		res = query.exec(QString("DELETE FROM GroupInfo where %1 = '%2'").arg(queryItem).arg(*it));
		if (res)
			nCount++;
	}
	commitTransaction();
	return nCount;
}
bool TNGroupInfo::Delete(const QString &queryItem, const QString &queryValue)
{
	bool res = false;
	if (tableIsExist("GroupInfo"))
	{
		QSqlQuery query(*_db);
		res = query.exec(QString("DELETE FROM GroupInfo where %1 = '%2'").arg(queryItem).arg(queryValue));
		if (!res)
			qDebug() << "delete GroupInfo fail" << query.lastError().text();
	}
	return res;

}

bool TNGroupInfo::ClearAll()
{
	if (tableIsExist("GroupInfo"))
	{
		QSqlQuery query(*_db);
		query.exec("DELETE FROM GroupInfo");
	}
	return true;
}

void TNGroupInfo::checkTable()
{

}

void TNGroupInfo::createTable()
{
	if (!tableIsExist("GroupInfo"))
	{
		QSqlQuery query(*_db);
		query.exec("Create  TABLE MAIN.[GroupInfo]([groupId] varchar(40) PRIMARY KEY,[creatorFeedId] text,"
			"[name] text,[namePinyin] text, [pinyinHeader] text,[headerImage] text, [topic] text, [myFeedId] text,"
			"maxNum integer default 200,currNum integer,disturbStatus integer default 1,groupType integer default 1)");
	}
}

void TNGroupInfo::dropTable()
{
	if (tableIsExist("GroupInfo"))
	{
		QSqlQuery query(*_db);
		query.exec("Drop Table MAIN.[GroupInfo]");
	}
}
