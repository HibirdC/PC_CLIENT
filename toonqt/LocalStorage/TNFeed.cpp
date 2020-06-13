#include <memory>

#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>


#include "TNFeed.h"
#include "common_global.h"
#include "ConnectionPool.h"
TNFeed::TNFeed()
:TNBaseTable()
{
}


TNFeed::~TNFeed()
{
}
QString wrapSingleQuote(const QString &s)
{
	return QChar('\'') + s + QChar('\'');
}

int TNFeed::InsertDatas(QList<TableBasePtr> stFeedList)
{
	qDebug() << "TNFeed::InsertDatas begin";
	int mCount = 0;
	bool ret = false;
	if (!tableIsExist("Feed"))
	{
		return mCount;
	}
	QList<TableBasePtr>::iterator it;
	beginTransaction();
	for (it = stFeedList.begin(); it != stFeedList.end(); it++)
	{
		st_FeedPtr stFeed = std::dynamic_pointer_cast<st_Feed>(*it);
		if (keyIsExist("Feed", "feedId", stFeed->GetFeedID()))
		{
			QSqlQuery query(*_db);
			query.prepare(QString("UPDATE Feed SET comId = ?,version = ?,birthday = ?,sex = ?,keyword = ?,serviceLevel = ?,consumeLevel = ?,socialLevel = ?,"
				"tag = ?, userId = ?, subtitle = ?, titlePinYin = ?, title = ?, avatarId = ? where feedId = '%1'").arg(stFeed->GetFeedID()));

			query.bindValue(0, stFeed->GetComID());
			query.bindValue(1, stFeed->GetVersion());
			query.bindValue(2, stFeed->GetBirthday());
			query.bindValue(3, stFeed->GetSex());
			query.bindValue(4, stFeed->GetKeyWord());
			query.bindValue(5, stFeed->GetServiceLevel());
			query.bindValue(6, stFeed->GetConsumeLevel());
			query.bindValue(7, stFeed->GetSocialLevel());
			query.bindValue(8, stFeed->GetTag());
			query.bindValue(9, stFeed->GetUserID());
			query.bindValue(10, stFeed->GetSubTile());
			query.bindValue(11, stFeed->GetTitlePinYin());
			query.bindValue(12, stFeed->GetTitle());
			query.bindValue(13, stFeed->GetAvatarID());

			ret = query.exec();
			if (!ret)
			{
				qInfo() << "[LocalStorage][TNFeed]update SQL Error FEED failed. error=" << query.lastError();
			}
			mCount = ret ? mCount + 1 : mCount;
		}
		else
		{
			QSqlQuery query(*_db);
			query.prepare("INSERT INTO Feed ([feedId],[version],[birthday],[sex],[keyword],"
				"[serviceLevel],[consumeLevel],[socialLevel],[tag],[userId],[comId],[titlePinYin],"
				"[avatarId],[title],[subtitle]) VALUES(:feedId, :version, :birthday, :sex, :keyword, :serviceLevel, :consumeLevel, :socialLevel, :tag, :userId, :comId,:titlePinYin, :avatarId, :title, :subtitle)");

			query.bindValue(":feedId", stFeed->GetFeedID());
			query.bindValue(":version", stFeed->GetVersion());
			query.bindValue(":birthday", stFeed->GetBirthday());
			query.bindValue(":sex", stFeed->GetSex());
			query.bindValue(":keyword", stFeed->GetKeyWord());
			query.bindValue(":serviceLevel", stFeed->GetServiceLevel());
			query.bindValue(":consumeLevel", stFeed->GetConsumeLevel());
			query.bindValue(":socialLevel", stFeed->GetSocialLevel());
			query.bindValue(":tag", stFeed->GetTag());
			query.bindValue(":userId", stFeed->GetUserID());
			query.bindValue(":comId", stFeed->GetComID());
			query.bindValue(":titlePinYin", stFeed->GetTitlePinYin());
			query.bindValue(":avatarId", stFeed->GetAvatarID());
			query.bindValue(":title", stFeed->GetTitle());
			query.bindValue(":subtitle", stFeed->GetSubTile());

			ret = query.exec();
			if (!ret)
			{
				qInfo() << "[LocalStorage][TNFeed]insert SQL Error FEED failed. error=" << query.lastError();
			}
			mCount = ret ? mCount + 1 : mCount;
		}
	}
	commitTransaction();
	return mCount;
}
bool TNFeed::InsertDatas(st_FeedPtr stFeed)
{
	bool ret = false;
	if (tableIsExist("Feed"))
	{
		if (keyIsExist("Feed", "feedId", stFeed->GetFeedID()))
		{
			QSqlQuery query(*_db);
			query.prepare(QString("UPDATE Feed SET comId = ?,version = ?,birthday = ?,sex = ?,keyword = ?,serviceLevel = ?,consumeLevel = ?,socialLevel = ?,"
				"tag = ?, userId = ?, subtitle = ?, titlePinYin = ?, title = ?, avatarId = ? where feedId = '%1'").arg(stFeed->GetFeedID()));

			query.bindValue(0, stFeed->GetComID());
			query.bindValue(1, stFeed->GetVersion());
			query.bindValue(2, stFeed->GetBirthday());
			query.bindValue(3, stFeed->GetSex());
			query.bindValue(4, stFeed->GetKeyWord());
			query.bindValue(5, stFeed->GetServiceLevel());
			query.bindValue(6, stFeed->GetConsumeLevel());
			query.bindValue(7, stFeed->GetSocialLevel());
			query.bindValue(8, stFeed->GetTag());
			query.bindValue(9, stFeed->GetUserID());
			query.bindValue(10, stFeed->GetSubTile());
			query.bindValue(11, stFeed->GetTitlePinYin());
			query.bindValue(12, stFeed->GetTitle());
			query.bindValue(13, stFeed->GetAvatarID());

			ret = query.exec();
			if (!ret)
			{
				qInfo() << "[LocalStorage][TNFeed]update SQL Error FEED failed. error=" << query.lastError();
			}
		}
		else
		{
			QSqlQuery query(*_db);

			query.prepare("INSERT INTO Feed ([feedId],[version],[birthday],[sex],[keyword],"
				"[serviceLevel],[consumeLevel],[socialLevel],[tag],[userId],[comId],[titlePinYin],"
				"[avatarId],[title],[subtitle]) VALUES(:feedId, :version, :birthday, :sex, :keyword, :serviceLevel, :consumeLevel, :socialLevel, :tag, :userId, :comId,:titlePinYin, :avatarId, :title, :subtitle)");

			query.bindValue(":feedId", stFeed->GetFeedID());
			query.bindValue(":version", stFeed->GetVersion());
			query.bindValue(":birthday", stFeed->GetBirthday());
			query.bindValue(":sex", stFeed->GetSex());
			query.bindValue(":keyword", stFeed->GetKeyWord());
			query.bindValue(":serviceLevel", stFeed->GetServiceLevel());
			query.bindValue(":consumeLevel", stFeed->GetConsumeLevel());
			query.bindValue(":socialLevel", stFeed->GetSocialLevel());
			query.bindValue(":tag", stFeed->GetTag());
			query.bindValue(":userId", stFeed->GetUserID());
			query.bindValue(":comId", stFeed->GetComID());
			query.bindValue(":titlePinYin", stFeed->GetTitlePinYin());
			query.bindValue(":avatarId", stFeed->GetAvatarID());
			query.bindValue(":title", stFeed->GetTitle());
			query.bindValue(":subtitle", stFeed->GetSubTile());

			ret = query.exec();
			if (!ret)
			{
				qInfo() << "[LocalStorage][TNFeed]insert SQL Error FEED failed. error=" << query.lastError();
			}
		}
	}
	return ret;
}
int  TNFeed::FuzzyQuery(TableBaseVec &tableBaseVec, const QString &text, QStringList keyList,const QString &type)
{
	int nCount = 0;
	if (!tableIsExist("Feed"))
	{
		return nCount;
	}
	QString sql;
	QStringList values(keyList);
	std::transform(values.begin(), values.end(), values.begin(), wrapSingleQuote);
	if (type == FeedTypeContact)
	{
		sql = QString("select * from Feed where (title like '#%1#' or titlePinYin like '#%2#') and feedId in (%3)").arg(text).arg(text).arg(values.join(QChar(',')));
		sql = sql.replace(QRegExp("#"), "%");
	}
	QSqlQuery query(*_db);
	bool ret = query.exec(sql);
	if (ret)
	{
		while (query.next())
		{
			st_FeedPtr FeedTable = std::make_shared<st_Feed>();
			FeedTable->SetFeedID(query.value("feedId").toString());
			FeedTable->SetAvatarID(query.value("avatarId").toString());
			FeedTable->SetTitle(query.value("title").toString());
			FeedTable->SetTitlePinYin(query.value("titlePinYin").toString());
			FeedTable->SetSubTile(query.value("subtitle").toString());
			FeedTable->SetUserID(query.value("userId").toString());
			FeedTable->SetTag(query.value("tag").toString());
			FeedTable->SetSocialLevel(query.value("socialLevel").toString());
			FeedTable->SetConsumeLevel(query.value("consumeLevel").toString());
			FeedTable->SetServiceLevel(query.value("serviceLevel").toString());
			FeedTable->SetKeyWord(query.value("keyword").toString());
			FeedTable->SetSex(query.value("sex").toString());
			FeedTable->SetBirthday(query.value("birthday").toString());
			FeedTable->SetVersion(query.value("version").toString());
			FeedTable->SetComID(query.value("comId").toString());
			FeedTable->SetExt1(query.value("ext1").toString());
			FeedTable->SetExt2(query.value("ext2").toString());
			TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(FeedTable);
			tableBaseVec.push_back(tempTableBase);
			nCount++;
		}
	}
	return nCount;
}
bool TNFeed::Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue)
{
	if (tableIsExist("Feed"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec(QString("select *from Feed where %1='%2'").arg(queryItem).arg(queryValue));
		if (ret)
		{
			while (query.next())
			{
				st_FeedPtr FeedTable = std::make_shared<st_Feed>();
				FeedTable->SetFeedID(query.value("feedId").toString());
				FeedTable->SetAvatarID(query.value("avatarId").toString());
				FeedTable->SetTitle(query.value("title").toString());
				FeedTable->SetTitlePinYin(query.value("titlePinYin").toString());
				FeedTable->SetSubTile(query.value("subtitle").toString());
				FeedTable->SetUserID(query.value("userId").toString());
				FeedTable->SetTag(query.value("tag").toString());
				FeedTable->SetSocialLevel(query.value("socialLevel").toString());
				FeedTable->SetConsumeLevel(query.value("consumeLevel").toString());
				FeedTable->SetServiceLevel(query.value("serviceLevel").toString());
				FeedTable->SetKeyWord(query.value("keyword").toString());
				FeedTable->SetSex(query.value("sex").toString());
				FeedTable->SetBirthday(query.value("birthday").toString());
				FeedTable->SetVersion(query.value("version").toString());
				FeedTable->SetComID(query.value("comId").toString());
				FeedTable->SetExt1(query.value("ext1").toString());
				FeedTable->SetExt2(query.value("ext2").toString());
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(FeedTable);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "Query Feed FAIL" << strLog;
			return false;
		}
	}
	return false;
}

bool TNFeed::batchQuery(TableBaseVec &tableBaseVec, const QString &queryItem, const QStringList &queryValues)
{
	if (tableIsExist("Feed"))
	{
		QStringList values(queryValues);
		std::transform(values.begin(), values.end(), values.begin(), wrapSingleQuote);
		QSqlQuery query(*_db);
		QString sqlStatement = QString("select * from Feed where %1 in (%2)").arg(queryItem).arg(values.join(QChar(',')));
		bool ret = query.exec(sqlStatement);
		if (ret)
		{
			while (query.next())
			{
				st_FeedPtr FeedTable = std::make_shared<st_Feed>();
				FeedTable->SetFeedID(query.value("feedId").toString());
				FeedTable->SetAvatarID(query.value("avatarId").toString());
				FeedTable->SetTitle(query.value("title").toString());
				FeedTable->SetTitlePinYin(query.value("titlePinYin").toString());
				FeedTable->SetSubTile(query.value("subtitle").toString());
				FeedTable->SetUserID(query.value("userId").toString());
				FeedTable->SetTag(query.value("tag").toString());
				FeedTable->SetSocialLevel(query.value("socialLevel").toString());
				FeedTable->SetConsumeLevel(query.value("consumeLevel").toString());
				FeedTable->SetServiceLevel(query.value("serviceLevel").toString());
				FeedTable->SetKeyWord(query.value("keyword").toString());
				FeedTable->SetSex(query.value("sex").toString());
				FeedTable->SetBirthday(query.value("birthday").toString());
				FeedTable->SetVersion(query.value("version").toString());
				FeedTable->SetComID(query.value("comId").toString());
				FeedTable->SetExt1(query.value("ext1").toString());
				FeedTable->SetExt2(query.value("ext2").toString());
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(FeedTable);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "Query INTO Feed FAIL" << strLog;
			return false;
		}
	}
	return false;
}

bool TNFeed::GetAllFields(TableBaseVec &tableBaseVec)
{
	if (tableIsExist("Feed"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec("select *from Feed");
		if (ret)
		{
			while (query.next())
			{
				st_FeedPtr FeedTable = std::make_shared<st_Feed>();
				FeedTable->SetFeedID(query.value("feedId").toString());
				FeedTable->SetAvatarID(query.value("avatarId").toString());
				FeedTable->SetTitle(query.value("title").toString());
				FeedTable->SetTitlePinYin(query.value("titlePinYin").toString());
				FeedTable->SetSubTile(query.value("subtitle").toString());
				FeedTable->SetUserID(query.value("userId").toString());
				FeedTable->SetTag(query.value("tag").toString());
				FeedTable->SetSocialLevel(query.value("socialLevel").toString());
				FeedTable->SetConsumeLevel(query.value("consumeLevel").toString());
				FeedTable->SetServiceLevel(query.value("serviceLevel").toString());
				FeedTable->SetKeyWord(query.value("keyword").toString());
				FeedTable->SetSex(query.value("sex").toString());
				FeedTable->SetBirthday(query.value("birthday").toString());
				FeedTable->SetVersion(query.value("version").toString());
				FeedTable->SetComID(query.value("comId").toString());
				FeedTable->SetExt1(query.value("ext1").toString());
				FeedTable->SetExt2(query.value("ext2").toString());
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(FeedTable);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "INSERT INTO Feed FAIL" << strLog;
			return false;
		}
	}
	return false;
}


bool TNFeed::ClearAll()
{
	if (tableIsExist("Feed"))
	{
		QSqlQuery query(*_db);
		query.exec("DELETE FROM Feed");
	}
	return true;
}

void TNFeed::checkTable()
{

}

void TNFeed::createTable()
{
	if (!tableIsExist("Feed"))
	{
		QSqlQuery query(*_db);
		query.exec("Create  TABLE MAIN.[Feed]([comId] varchar(32), [version] varchar(64),"
			"[birthday] varchar(32), [sex] varchar(16), [keyword] varchar(32), [serviceLevel] varchar(16),"
			"[consumeLevel] varchar(16), [socialLevel] varchar(16), [tag] varchar(32), [userId] varchar(32),"
			"[subtitle] varchar(64), [titlePinYin] varchar(64), [title] varchar(64),[ext1] varchar(128),[ext2] varchar(128),[avatarId] varchar(256),"
			"[feedId] varchar(32) PRIMARY KEY UNIQUE NOT NULL)");
	}
}

void TNFeed::dropTable()
{
	if (tableIsExist("Feed"))
	{
		QSqlQuery query(*_db);
		query.exec("Drop Table MAIN.[Feed]");
	}
}

bool TNFeed::UpdateSetValueByFieldMap(QMap<QString, QString>& fieldMap, const QString &whereName, const QString &whereValue)
{
    QMap<QString, QString>::iterator fieldIter;
    QString updateSql = "update Feed set  ";
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
        qDebug() << "update set Feed FAIL" << strLog;
        return false;
    }
}
/*
更新ext1时， 可能此时feed 未插入
*/
bool TNFeed::UpdateSetValueByValueMap(QMap<QString, QString> valueMap, const QString field, const QString &whereName)
{
	int mCount = 0;
	if (!tableIsExist("Feed"))
	{
		return mCount;
	}
	QList<TableBasePtr>::iterator it;
	beginTransaction();
	for (QMap<QString, QString>::iterator it = valueMap.begin(); it != valueMap.end(); it++)
	{
		QString strSql;
		if (keyIsExist("Feed", whereName, it.key()))
		{
			strSql = QString("UPDATE Feed SET %1 = '%2' WHERE %3 = '%4'")
				.arg(field)
				.arg(it.value())
				.arg(whereName)
				.arg(it.key());
		}
		else
		{
			strSql = QString("INSERT INTO Feed ([feedId],[ext1]) VALUES('%1', '%2')")
				.arg(it.key())
				.arg(it.value());
		}
		QSqlQuery query(*_db);
		bool ret = query.exec(strSql);
		if (!ret)
		{
			qInfo() << "[LocalStorage][TNFeed]UpdateSetValueByValueMap SQL Error Feed: " << strSql << " Err:" << query.lastError();
		}
		mCount = ret ? mCount + 1 : mCount;
	}
	commitTransaction();
	return mCount;
}

bool TNFeed::updateSetValueByField(const QString &fieldName, const QString &fieldValue, const QString &whereName, const QString &whereValue)
{
    if (!tableIsExist("Feed")){
        return false;
    }
    QString strSql = QString("UPDATE Feed SET %1 = '%2' WHERE %3 = '%4'").arg(fieldName).arg(fieldValue).arg(whereName).arg(whereValue);
    beginTransaction();
    QSqlQuery query(*_db);
    bool ret = query.exec(strSql);
    commitTransaction();
    return ret;
}
