#include <memory>

#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>


#include "TNBMessage0.h"


TNBMessage0::TNBMessage0()
:TNBaseTable()
{
}


TNBMessage0::~TNBMessage0()
{
}

bool TNBMessage0::InsertDatas(st_BMessage0Ptr message)
{
    /*
	if (tableIsExist("BMessage0"))
	{
		QSqlQuery query(*_db);
		QString strSql = QString("INSERT INTO BMessage0 (sessionId, msgId, type, seqId, fromId, toId, formClientId"
			",toClientId, timestamp, pushInfo, expireTime, sendStatus, status, priority, catalogId, catalog, contentType"
			", content, isMyself, width, height, senderName, atType, atFeeds, fileFormat) VALUES('%1', '%2', '%3', '%4',"
			"'%5', '%6','%7', '%8','%9', '%10','%11', '%12','%13', '%14','%15', '%16','%17', '%18','%19', '%20','%21',"
			" '%22','%23', '%24','%25')")
			.arg(message->GetSessionId()).arg(message->GetMsgId()).arg(message->GetType()).arg(message->GetSeqId())
			.arg(message->GetFromId()).arg(message->GetToId()).arg(message->GetFormClientId()).arg(message->GetToClientId())
			.arg(message->GetTimestamp()).arg(message->GetPushInfo()).arg(message->GetExpireTime()).arg(message->GetSendStatus())
			.arg(message->GetStatus()).arg(message->GetPriority()).arg(message->GetCatalogId()).arg(message->GetCatalog())
			.arg(message->GetContentType()).arg(message->GetContent()).arg(message->GetIsMyself()).arg(message->GetWidth())
			.arg(message->GetHeight()).arg(message->GetSenderName()).arg(message->GetAtType()).arg(message->GetAtFeeds())
			.arg(message->GetFileFormat());
        qDebug() << "insert bmessage0 sql:" << strSql;
		bool ret = query.exec(strSql);
		if (ret)
		{
			return true;
		} 
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO BMessage0 FAIL" << strLog;
			UpdateSetValueByField("content", message->GetContent(), "msgId", message->GetMsgId());
		}
	}
	return false;
    */

    if (tableIsExist("BMessage0"))
    {
        QSqlQuery query(*_db);
        query.prepare("INSERT INTO BMessage0 (sessionId, msgId, type, seqId, fromId, toId, formClientId "
                      ", toClientId, timestamp, pushInfo, expireTime, sendStatus, status, priority, catalogId, catalog, contentType "
                      ", content, isMyself, width, height, senderName, atType, atFeeds, fileFormat) "
                      "VALUES (:sessionId, :msgId, :type, :seqId, :fromId, :toId, :formClientId "
                      ", :toClientId, :timestamp, :pushInfo, :expireTime, :sendStatus, :status, :priority, :catalogId, :catalog, :contentType "
                      ", :content, :isMyself, :width, :height, :senderName, :atType, :atFeeds, :fileFormat)");

        query.bindValue(":sessionId", message->GetSessionId());
        query.bindValue(":msgId", message->GetMsgId());
        query.bindValue(":type", message->GetType());
        query.bindValue(":seqId", message->GetSeqId());
        query.bindValue(":fromId", message->GetFromId());
        query.bindValue(":toId", message->GetToId());
        query.bindValue(":formClientId", message->GetFormClientId());
        query.bindValue(":toClientId", message->GetToClientId());
        query.bindValue(":timestamp", message->GetTimestamp());
        query.bindValue(":pushInfo", message->GetPushInfo());
        query.bindValue(":expireTime", message->GetExpireTime());
        query.bindValue(":sendStatus", message->GetSendStatus());
        query.bindValue(":status", message->GetStatus());
        query.bindValue(":priority", message->GetPriority());
        query.bindValue(":catalogId", message->GetCatalogId());
        query.bindValue(":catalog", message->GetCatalog());
        query.bindValue(":contentType", message->GetContentType());
        query.bindValue(":content", message->GetContent());
        query.bindValue(":isMyself", message->GetIsMyself());
        query.bindValue(":width", message->GetWidth());
        query.bindValue(":height", message->GetHeight());
        query.bindValue(":senderName", message->GetSenderName());
        query.bindValue(":atType", message->GetAtType());
        query.bindValue(":atFeeds", message->GetAtFeeds());
        query.bindValue(":fileFormat", message->GetFileFormat());

        bool ret = query.exec();
        if (ret)
        {
            return true;
        }
        else
        {
            //QString strLog = query.lastError().text();
            //qDebug() << "INSERT INTO BMessage0 FAIL" << strLog;
            UpdateSetValueByFieldEx("content", message->GetContent(), "msgId", message->GetMsgId(), "sendStatus", QString::number(message->GetSendStatus()));
        }
    }
    return false;
}

bool TNBMessage0::UpdateSetValueByField(const QString &fieldName, const QString &fieldValue, const QString &whereName, const QString &whereValue)
{
	//update message table
	QSqlQuery updateQuerty(*_db);
	QString updateSql = QString("update BMessage0 set  %1 = '%2' where %3 ='%4'")
		.arg(fieldName).arg(fieldValue).arg(whereName).arg(whereValue);
	if (updateQuerty.exec(updateSql))
		return true;
	else
	{
		QString strLog = updateQuerty.lastError().text();
		qDebug() << "update set BMessage0 FAIL" << strLog;
		return false;
	}
}

bool TNBMessage0::UpdateSetValueByFieldEx(const QString &fieldName, const QString &fieldValue, const QString &whereName, const QString &whereValue, const QString &fieldNameEx, const QString &fieldValueEx)
{
	//update message table
	QSqlQuery updateQuerty(*_db);
	QString updateSql = QString("update BMessage0 set  %1 = '%2', %5 = '%6' where %3 ='%4'")
		.arg(fieldName).arg(fieldValue).arg(whereName).arg(whereValue).arg(fieldNameEx).arg(fieldValueEx);
	if (updateQuerty.exec(updateSql))
		return true;
	else
	{
		QString strLog = updateQuerty.lastError().text();
		qDebug() << "update set BMessage0 FAIL" << strLog;
		return false;
	}

}

bool TNBMessage0::UpdateSetValueByFieldMap(QMap<QString, QString>& fieldMap, const QString &whereName, const QString &whereValue)
{
	QMap<QString, QString>::iterator fieldIter;
	QString updateSql = "update BMessage0 set  ";
	for (fieldIter = fieldMap.begin(); fieldIter != fieldMap.end(); fieldIter++)
	{
		QString fieldKey = fieldIter.key();
		QString fieldValue = fieldIter.value();
		QString sqlField;
		if (fieldIter != fieldMap.begin())
			sqlField = ",";
		sqlField.append(QString("%1 = '%2'").arg(fieldKey, fieldValue));
		updateSql += sqlField;
	}
	QString whereSql = QString(" where %1 ='%2'").arg(whereName).arg(whereValue);

	updateSql.append(whereSql);
	QSqlQuery updateQuerty(*_db);
	if (updateQuerty.exec(updateSql))
		return true;
	else
	{
		QString strLog = updateQuerty.lastError().text();
		qDebug() << "update set BMessage0 FAIL" << strLog;
		return false;
	}
}

bool TNBMessage0::queryHistoryMsg(TableBaseVec &tableBaseVec,
                                  const QString &sessionId,
                                  const QString& msgId,
                                  int num)
{
    if (tableIsExist("BMessage0")){
        QSqlQuery query(*_db);
        int reqId = -1;
        bool ret = false;
        if(!msgId.isEmpty()){
            ret = query.exec(QString("select seqId from BMessage0 where msgId='%1'").arg(msgId));
            if(ret){
                while (query.next()){
                    reqId = query.value("seqId").toInt();
                }
            }else{
                QString strLog = query.lastError().text();
                qDebug() << "select from BMessage0 FAIL" << strLog;
                return false;
            }
            if (ret){
                ret = query.exec(QString("select * from BMessage0 where sessionId='%1' and type!=54 and seqId<%2 order by seqId desc , timestamp desc limit %3")
                    .arg(sessionId).arg(reqId).arg(num));
            }
        }else{
            ret = query.exec(QString("select * from BMessage0 where sessionId='%1' and type!=54 order by seqId desc , timestamp desc limit %2")
                .arg(sessionId).arg(num));
        }

        if (ret){
            while (query.next()){
                st_BMessage0Ptr message = std::make_shared<st_BMessage0>();
                message->SetSessionId(query.value("sessionId").toString());
                message->SetMsgId(query.value("msgId").toString());
                message->SetType(query.value("type").toInt());
                message->SetSeqId(query.value("seqId").toInt());
                message->SetFromId(query.value("fromId").toString());
                message->SetToId(query.value("toId").toString());
                message->SetFormClientId(query.value("formClientId").toString());
                message->SetToClientId(query.value("toClientId").toString());
                message->SetTimestamp(query.value("timestamp").toInt());
                message->SetPushInfo(query.value("pushInfo").toString());
                message->SetExpireTime(query.value("expireTime").toInt());
                message->SetSendStatus(query.value("sendStatus").toInt());
                message->SetStatus(query.value("status").toInt());
                message->SetPriority(query.value("priority").toInt());
                message->SetCatalogId(query.value("catalogId").toInt());
                message->SetCatalog(query.value("catalog").toString());
                message->SetContentType(query.value("contentType").toInt());
                message->SetContent(query.value("content").toString());
                message->SetIsMyself(query.value("isMyself").toInt());
                message->SetWidth(query.value("width").toInt());
                message->SetHeight(query.value("height").toInt());
                message->SetSenderName(query.value("senderName").toString());
                message->SetAtType(query.value("atType").toInt());
                message->SetAtFeeds(query.value("atFeeds").toString());
                message->SetFileFormat(query.value("fileFormat").toString());
                TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(message);
                tableBaseVec.push_back(tempTableBase);
            }
            return true;
        }else{
            QString strLog = query.lastError().text();
            qDebug() << "select from BMessage0 FAIL" << strLog;
            return false;
        }
    }
    return false;
}


bool TNBMessage0::Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue, int pageNum, int pageIndex, int newMsgNum)
{
	if (tableIsExist("BMessage0"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec(QString("select *from BMessage0 where %1='%2' order by seqId desc , timestamp desc limit %3 offset %4").arg(queryItem).arg(queryValue)
            .arg(pageNum).arg(pageIndex*pageNum+newMsgNum));
		if (ret)
		{
			while (query.next())
			{
				st_BMessage0Ptr message = std::make_shared<st_BMessage0>();
				message->SetSessionId(query.value("sessionId").toString());
				message->SetMsgId(query.value("msgId").toString());
				message->SetType(query.value("type").toInt());
				message->SetSeqId(query.value("seqId").toInt());
				message->SetFromId(query.value("fromId").toString());
				message->SetToId(query.value("toId").toString());
				message->SetFormClientId(query.value("formClientId").toString());
				message->SetToClientId(query.value("toClientId").toString());
				message->SetTimestamp(query.value("timestamp").toInt());
				message->SetPushInfo(query.value("pushInfo").toString());
				message->SetExpireTime(query.value("expireTime").toInt());
				message->SetSendStatus(query.value("sendStatus").toInt());
				message->SetStatus(query.value("status").toInt());
				message->SetPriority(query.value("priority").toInt());
				message->SetCatalogId(query.value("catalogId").toInt());
				message->SetCatalog(query.value("catalog").toString());
				message->SetContentType(query.value("contentType").toInt());
				message->SetContent(query.value("content").toString());
				message->SetIsMyself(query.value("isMyself").toInt());
				message->SetWidth(query.value("width").toInt());
				message->SetHeight(query.value("height").toInt());
				message->SetSenderName(query.value("senderName").toString());
				message->SetAtType(query.value("atType").toInt());
				message->SetAtFeeds(query.value("atFeeds").toString());
				message->SetFileFormat(query.value("fileFormat").toString());
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(message);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "select from BMessage0 FAIL" << strLog;
			return false;
		}
	}
	return false;
}


bool TNBMessage0::GetAllFields(TableBaseVec &tableBaseVec)
{
	if (tableIsExist("BMessage0"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec("select *from BMessage0");
		if (ret)
		{
			while (query.next())
			{
				st_BMessage0Ptr message = std::make_shared<st_BMessage0>();
				message->SetSessionId(query.value("sessionId").toString());
				message->SetMsgId(query.value("msgId").toString());
				message->SetType(query.value("type").toInt());
				message->SetSeqId(query.value("seqId").toInt());
				message->SetFromId(query.value("fromId").toString());
				message->SetToId(query.value("toId").toString());
				message->SetFormClientId(query.value("formClientId").toString());
				message->SetToClientId(query.value("toClientId").toString());
				message->SetTimestamp(query.value("timestamp").toInt());
				message->SetPushInfo(query.value("pushInfo").toString());
				message->SetExpireTime(query.value("expireTime").toInt());
				message->SetSendStatus(query.value("sendStatus").toInt());
				message->SetStatus(query.value("status").toInt());
				message->SetPriority(query.value("priority").toInt());
				message->SetCatalogId(query.value("catalogId").toInt());
				message->SetCatalog(query.value("catalog").toString());
				message->SetContentType(query.value	("contentType").toInt());
				message->SetContent(query.value("content").toString());
				message->SetIsMyself(query.value("isMyself").toInt());
				message->SetWidth(query.value("width").toInt());
				message->SetHeight(query.value("height").toInt());
				message->SetSenderName(query.value("senderName").toString());
				message->SetAtType(query.value("atType").toInt());
				message->SetAtFeeds(query.value("atFeeds").toString());
				message->SetFileFormat(query.value("fileFormat").toString());
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(message);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "GetAllFields  BMessage0 FAIL" << strLog;
			return false;
		}
	}
	return false;
}


bool TNBMessage0::ClearAll()
{
	if (tableIsExist("BMessage0"))
	{
		QSqlQuery query(*_db);
		query.exec("DELETE FROM BMessage0");
	}
	return true;
}

void TNBMessage0::checkTable()
{

}

void TNBMessage0::createTable()
{
	if (!tableIsExist("BMessage0"))
	{
		QSqlQuery query(*_db);
		query.exec("Create  TABLE MAIN.[BMessage0]([sessionId] varchar(50)"
			", [msgId] varchar(40) PRIMARY KEY UNIQUE NOT NULL"
			", [type] integer"
			", [seqId] integer"
			", [fromId] varchar(30)"
			", [toId] text"
			", [formClientId] text"
			", [toClientId] varchar(30)"
			", [timestamp] integer"
			", [pushInfo] text"
			", [expireTime] integer"
			", [sendStatus] integer"
			", [status] integer"
			", [priority] integer"
			", [catalogId] integer"
			", [catalog] text"
			", [contentType] integer"
			", [content] text"
			", [isMyself] integer"
			", [width] integer"
			", [height] integer"
			", [senderName] text"
			", [atType] integer"
			", [atFeeds] text"
			", [fileFormat] text)");
	}
}

void TNBMessage0::dropTable()
{
	if (tableIsExist("BMessage0"))
	{
		QSqlQuery query(*_db);
		query.exec("Drop Table MAIN.[BMessage0]");
	}
}

bool TNBMessage0::Delete(const QString &queryItem, const QString &queryValue)
{
	bool res = false;
	if (tableIsExist("BMessage0"))
	{
		QSqlQuery query(*_db);
		res = query.exec(QString("DELETE FROM BMessage0 where %1 = '%2'").arg(queryItem).arg(queryValue));
		if (!res)
			qDebug() << "delete GroupInfo fail" << query.lastError().text();
	}
	return res;
}

int TNBMessage0::Delete(const QString &queryItem, QList<QString> queryValueList)
{
	int nCount = 0;
	QList<QString>::iterator it;
	beginTransaction();
	for (it = queryValueList.begin(); it != queryValueList.end(); it++)
	{
		bool res = false;
		QSqlQuery query(*_db);
		res = query.exec(QString("DELETE FROM BMessage0 where %1 = '%2'").arg(queryItem).arg(*it));
		if (res)
			nCount++;
	}
	commitTransaction();
	return nCount;
}

bool TNBMessage0::getUnreadFirstMsg(const QString &sessionId, int num, st_BMessage0Ptr &message)
{
    if (tableIsExist("BMessage0")){
        QSqlQuery query(*_db);
        bool ret = query.exec(QString("select *from BMessage0 where sessionId='%1' order by seqId desc , timestamp desc limit %2")
            .arg(sessionId)
            .arg(num)
            );
        if (ret){
            message = std::make_shared<st_BMessage0>();
            if(query.last()){
                message->SetSessionId(query.value("sessionId").toString());
                message->SetMsgId(query.value("msgId").toString());
                message->SetType(query.value("type").toInt());
                message->SetSeqId(query.value("seqId").toInt());
                message->SetFromId(query.value("fromId").toString());
                message->SetToId(query.value("toId").toString());
                message->SetFormClientId(query.value("formClientId").toString());
                message->SetToClientId(query.value("toClientId").toString());
                message->SetTimestamp(query.value("timestamp").toInt());
                message->SetPushInfo(query.value("pushInfo").toString());
                message->SetExpireTime(query.value("expireTime").toInt());
                message->SetSendStatus(query.value("sendStatus").toInt());
                message->SetStatus(query.value("status").toInt());
                message->SetPriority(query.value("priority").toInt());
                message->SetCatalogId(query.value("catalogId").toInt());
                message->SetCatalog(query.value("catalog").toString());
                message->SetContentType(query.value("contentType").toInt());
                message->SetContent(query.value("content").toString());
                message->SetIsMyself(query.value("isMyself").toInt());
                message->SetWidth(query.value("width").toInt());
                message->SetHeight(query.value("height").toInt());
                message->SetSenderName(query.value("senderName").toString());
                message->SetAtType(query.value("atType").toInt());
                message->SetAtFeeds(query.value("atFeeds").toString());
                message->SetFileFormat(query.value("fileFormat").toString());
            }
            return true;
        }else{
            QString strLog = query.lastError().text();
            qDebug() << "getUnreadFirstMsg from BMessage0 FAIL" << strLog;
            return false;
        }
    }
    return false;
}

bool TNBMessage0::getUnreadMsg(TableBaseVec &tableBaseVec,
                               const QString &sessionId,
                               const QString &currentFristMsgId,
                               const QString &firstUnreadMsgId)
{
    if (!tableIsExist("BMessage0")){
        return false;
    }
    QSqlQuery query(*_db);
    int cur_reqId = -1,first_unread_reqId = -1;
    bool ret = false;
    if(currentFristMsgId.isEmpty() || firstUnreadMsgId.isEmpty()){
        qDebug() << "getUnreadMsg failed currentFristMsgId || firstUnreadMsgId isEmpty";
        return false;
    }
    ret = query.exec(QString("select seqId from BMessage0 where msgId='%1'").arg(currentFristMsgId));
    if(ret){
        if(query.first()){
            cur_reqId = query.value("seqId").toInt();
        }
    }else{
        return false;
    }
    ret = query.exec(QString("select seqId from BMessage0 where msgId='%1'").arg(firstUnreadMsgId));
    if(ret){
        if(query.first()){
            first_unread_reqId = query.value("seqId").toInt();
        }
    }else{
        return false;
    }
    ret = query.exec(QString("select * from BMessage0 where sessionId='%1' and type!=54 and seqId<%2 and seqId>=%3 order by seqId desc , timestamp desc")
                         .arg(sessionId).arg(cur_reqId).arg(first_unread_reqId));

    if (ret){
        while (query.next()){
            st_BMessage0Ptr message = std::make_shared<st_BMessage0>();
            message->SetSessionId(query.value("sessionId").toString());
            message->SetMsgId(query.value("msgId").toString());
            message->SetType(query.value("type").toInt());
            message->SetSeqId(query.value("seqId").toInt());
            message->SetFromId(query.value("fromId").toString());
            message->SetToId(query.value("toId").toString());
            message->SetFormClientId(query.value("formClientId").toString());
            message->SetToClientId(query.value("toClientId").toString());
            message->SetTimestamp(query.value("timestamp").toInt());
            message->SetPushInfo(query.value("pushInfo").toString());
            message->SetExpireTime(query.value("expireTime").toInt());
            message->SetSendStatus(query.value("sendStatus").toInt());
            message->SetStatus(query.value("status").toInt());
            message->SetPriority(query.value("priority").toInt());
            message->SetCatalogId(query.value("catalogId").toInt());
            message->SetCatalog(query.value("catalog").toString());
            message->SetContentType(query.value("contentType").toInt());
            message->SetContent(query.value("content").toString());
            message->SetIsMyself(query.value("isMyself").toInt());
            message->SetWidth(query.value("width").toInt());
            message->SetHeight(query.value("height").toInt());
            message->SetSenderName(query.value("senderName").toString());
            message->SetAtType(query.value("atType").toInt());
            message->SetAtFeeds(query.value("atFeeds").toString());
            message->SetFileFormat(query.value("fileFormat").toString());
            TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(message);
            tableBaseVec.push_back(tempTableBase);
        }
        return true;
    }
    return false;
}
