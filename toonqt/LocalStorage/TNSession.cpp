#include <memory>

#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>


#include "TNSession.h"


TNSession::TNSession()
:TNBaseTable()
{
}


TNSession::~TNSession()
{
}

bool TNSession::InsertDatas(st_SessionPtr session)
{
    if (tableIsExist("Session"))
    {
        TableBaseVec tableDatas;
        if (Query(tableDatas, "sessionId", session->GetSessionId()))
        {
            if (tableDatas.size() == 0)
            {
                //not exist insert data
                QSqlQuery query(*_db);
                query.prepare("INSERT INTO Session (sessionId, topic, myFeedId, type, unreadCount, title,"
                              " titlePinyin, pinyinHeader, avatarId, draft, lastTime, lastMsg, lastMsgId, lastMsgSendStatus,"
                              " topStatus, atMeStatus, sortTime) VALUES (:sessionId, :topic, :myFeedId, :type, :unreadCount, :title,"
                              " :titlePinyin, :pinyinHeader, :avatarId, :draft, :lastTime, :lastMsg, :lastMsgId, :lastMsgSendStatus, :topStatus, :atMeStatus, :sortTime)");

                query.bindValue(":sessionId", session->GetSessionId());
                query.bindValue(":topic", session->GetTopic());
                query.bindValue(":myFeedId", session->GetMyFeedId());
                query.bindValue(":type", session->GetType());
                query.bindValue(":unreadCount", session->GetUnreadCount());
                query.bindValue(":title", session->GetTitle());
                query.bindValue(":titlePinyin", session->GetTitlePinyin());
                query.bindValue(":pinyinHeader", session->GetPinyinHeader());
                query.bindValue(":avatarId", session->GetAvatarId());
                query.bindValue(":draft", session->GetDraft());
                query.bindValue(":lastTime", session->GetLastTime());
                query.bindValue(":lastMsg", session->GetLastMsg());
                query.bindValue(":lastMsgId", session->GetLastMsgId());
                query.bindValue(":lastMsgSendStatus", session->GetLastMsgSendStatus());
                query.bindValue(":topStatus", session->GetTopStatus());
				query.bindValue(":atMeStatus", session->GetAtMeStatus());
                query.bindValue(":sortTime", session->GetSortTime());
                bool ret = query.exec();
                if (ret)
                {
                    return true;
                }
                else
                {
                    QString strLog = query.lastError().text();
                    qDebug() << "INSERT INTO Session FAIL" << strLog;
                }
            }
            else
            {
                //exist update data
                st_SessionPtr oldSession = std::dynamic_pointer_cast<st_Session>(tableDatas[0]);
                int unReadCount = oldSession->GetUnreadCount() + session->GetUnreadCount();
                if (unReadCount < 0)
                    unReadCount = 0;

                QString avatarUrl = session->GetAvatarId();
                if (avatarUrl.isEmpty())
                    avatarUrl = oldSession->GetAvatarId();

                QString title = session->GetTitle();
                if (title.isEmpty())
                    title = oldSession->GetTitle();

                QSqlQuery query(*_db);
                query.prepare(QString("update Session set unreadCount=?, title=?, lastTime=?, lastMsgId=?, lastMsg=?, lastMsgSendStatus=?, avatarId=? where sessionId ='%1'").arg(session->GetSessionId()));

                query.bindValue(0, unReadCount);
                query.bindValue(1, title);
                query.bindValue(2, session->GetLastTime());
                query.bindValue(3, session->GetLastMsgId());
                query.bindValue(4, session->GetLastMsg());
                query.bindValue(5, session->GetLastMsgSendStatus());
                query.bindValue(6, avatarUrl);

                bool ret = query.exec();
                if (ret)
                {
                    return true;
                }
                else
                {
                    QString strLog = query.lastError().text();
                    qDebug() << "update Session fail" << strLog;
                }
            }
        }
    }
    return false;
}

bool TNSession::UpdateSetValueByField(const QString &fieldName, const QString &fieldValue, const QString &whereName, const QString &whereValue)
{
    QSqlQuery query(*_db);
    query.prepare(QString("update Session set %1 = ? where %2 ='%3'").arg(fieldName).arg(whereName).arg(whereValue));
    query.bindValue(0, fieldValue);
    bool ret = query.exec();
    if (ret)
    {
        return true;
    }
    else
    {
        QString strLog = query.lastError().text();
        qDebug() << "UPDATE Session FAIL" << strLog;
    }
    return false;
}

bool TNSession::Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue)
{
	if (tableIsExist("Session"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec(QString("select *from Session where %1='%2'").arg(queryItem).arg(queryValue));
		if (ret)
		{
			while (query.next())
			{
				st_SessionPtr session = std::make_shared<st_Session>();
				session->SetSessionId(query.value("sessionId").toString());
				session->SetTopic(query.value("topic").toString());
				session->SetMyFeedId(query.value("myFeedId").toString());
				session->SetType(query.value("type").toInt());
				session->SetUnreadCount(query.value("unreadCount").toInt());
				session->SetTitle(query.value("title").toString());
				session->SetTitlePinyin(query.value("titlePinyin").toString());
				session->SetPinyinHeader(query.value("pinyinHeader").toString());
				session->SetAvatarId(query.value("avatarId").toString());
				session->SetDraft(query.value("draft").toString());
				session->SetLastTime(query.value("lastTime").toInt());
				session->SetLastMsg(query.value("lastMsg").toString());
				session->SetLastMsgId(query.value("lastMsgId").toString());
				session->SetLastMsgSendStatus(query.value("lastMsgSendStatus").toInt());
				session->SetTopStatus(query.value("topStatus").toInt());
				session->SetSortTime(query.value("sortTime").toInt());
				session->SetAtMeStatus(query.value("atMeStatus").toInt());
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(session);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO Session FAIL" << strLog;
			return false;
		}
	}
	return false;
}


bool TNSession::GetAllFields(TableBaseVec &tableBaseVec)
{
	if (tableIsExist("Session"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec("select * from Session order by topStatus,lastTime");
		if (ret)
		{
			while (query.next())
			{
				st_SessionPtr session = std::make_shared<st_Session>();
				session->SetSessionId(query.value("sessionId").toString());
				session->SetTopic(query.value("topic").toString());
				session->SetMyFeedId(query.value("myFeedId").toString());
				session->SetType(query.value("type").toInt());
				session->SetUnreadCount(query.value("unreadCount").toInt());
				session->SetTitle(query.value("title").toString());
				session->SetTitlePinyin(query.value("titlePinyin").toString());
				session->SetPinyinHeader(query.value("pinyinHeader").toString());
				session->SetAvatarId(query.value("avatarId").toString());
				session->SetDraft(query.value("draft").toString());
				session->SetLastTime(query.value("lastTime").toInt());
				session->SetLastMsg(query.value("lastMsg").toString());
				session->SetLastMsgId(query.value("lastMsgId").toString());
				session->SetLastMsgSendStatus(query.value("lastMsgSendStatus").toInt());
				session->SetTopStatus(query.value("topStatus").toInt());
				session->SetAtMeStatus(query.value("atMeStatus").toInt());
				session->SetSortTime(query.value("sortTime").toInt());
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(session);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO Session FAIL" << strLog;
			return false;
		}
	}
	return false;
}


bool TNSession::ClearAll()
{
	if (tableIsExist("Session"))
	{
		QSqlQuery query(*_db);
		query.exec("DELETE FROM Session");
	}
	return true;
}

void TNSession::checkTable()
{

}

void TNSession::createTable()
{
	if (!tableIsExist("Session"))
	{
		QSqlQuery query(*_db);
		query.exec("Create  TABLE MAIN.[Session]([sessionId] varchar(40) PRIMARY KEY"
			", [topic] varchar(20)"
			", [myFeedId] varchar(20) NOT NULL DEFAULT ' '"
			", [type] integer"
			", [unreadCount] integer"
			", [title] text"
			", [titlePinyin] text"
			", [pinyinHeader] text"
			", [avatarId] text"
			", [draft] text"
			", [lastTime] integer"
			", [lastMsg] text"
			", [lastMsgId] text"
			", [lastMsgSendStatus] integer"
			", [topStatus] integer"
			", [atMeStatus] integer"
			", [sortTime] integer)");
	}
	else
	{
		QString strSql = "select * from sqlite_master where name='Session' and sql like '%atMeStatus%'";
		QSqlQuery query(*_db);
		query.exec(strSql);
		if (!query.next())
		{  
			QSqlQuery query(*_db);
			query.exec("ALTER TABLE 'Session' ADD  'atMeStatus' integer");
		}
		
	}
}

void TNSession::dropTable()
{
	if (tableIsExist("Session"))
	{
		QSqlQuery query(*_db);
		query.exec("Drop Table MAIN.[Session]");
	}
}

bool TNSession::Delete(const QString &queryItem, const QString &queryValue)
{
	bool res = false;
	if (tableIsExist("Session"))
	{
		QSqlQuery query(*_db);
		res = query.exec(QString("DELETE FROM Session where %1 = '%2'").arg(queryItem).arg(queryValue));
		if (!res)
			qDebug() << "delete GroupInfo fail" << query.lastError().text();
	}
	return res;
}

int TNSession::Delete(const QString &queryItem, QList<QString> queryValueList)
{
	int nCount = 0;
	QList<QString>::iterator it;
	beginTransaction();
	for (it = queryValueList.begin(); it != queryValueList.end(); it++)
	{
		bool res = false;
		QSqlQuery query(*_db);
		res = query.exec(QString("DELETE FROM Session where %1 = '%2'").arg(queryItem).arg(*it));
		if (res)
			nCount++;
	}
	commitTransaction();
	return nCount;
}
int  TNSession::GetUNReadCount(const QString &feedID)
{
	int count = 0;
	if (tableIsExist("Session"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec(QString("select sum(unreadCount) from Session where myFeedId='%1'").arg(feedID));
		if (ret && query.next())
		{
			QSqlRecord record = query.record();
			count = record.value(0).toInt();
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "GetUNReadCount FAIL" << strLog;
		}
	}
	return count;
}

bool TNSession::UpdateSetValueByFieldEx(const QString &fieldName, const QString &fieldValue, const QString &whereName, const QString &whereValue, const QString &fieldNameEx, const QString &fieldValueEx)
{
	//update message table
	QSqlQuery updateQuerty(*_db);
	QString updateSql = QString("update Session set  %1 = '%2', %5 = '%6' where %3 ='%4'")
		.arg(fieldName).arg(fieldValue).arg(whereName).arg(whereValue).arg(fieldNameEx).arg(fieldValueEx);
	if (updateQuerty.exec(updateSql))
		return true;
	else
	{
		QString strLog = updateQuerty.lastError().text();
		qWarning() << "[LocalStorage][TNSession]update set TNSession FAIL" << strLog;
		return false;
	}

}
