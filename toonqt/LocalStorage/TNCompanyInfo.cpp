#include "TNCompanyInfo.h"

#include <memory>

#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>


TNCompanyInfo::TNCompanyInfo()
	: TNBaseTable()
{

}

TNCompanyInfo::~TNCompanyInfo()
{

}
int TNCompanyInfo::InsertDatas(QList<TableBasePtr> myCompanyList)
{
	int mCount = 0;
	bool ret = false;
	if (!tableIsExist("CompanyInfo"))
	{
		return mCount;
	}
	QList<TableBasePtr>::iterator it;
	beginTransaction();
	for (it = myCompanyList.begin(); it != myCompanyList.end(); it++)
	{
		st_CompanyInfoPtr company = std::dynamic_pointer_cast<st_CompanyInfo>(*it);
		if (keyIsExist("CompanyInfo", "comId", company->getComId()))
		{
			QSqlQuery query(*_db);
			query.prepare(QString("UPDATE CompanyInfo SET feedId = ?, address = ?, cardNo = ?, createTime = ?, creatorId = ?, displayName = ?, displayNamePinyin = ?, exchangeMode = ?, industry = ?, introduction = ?, logo = ?, phone = ?, email = ?, updateTime = ?,ownerId = ? ,ext = ? WHERE comId = '%1'")
				.arg(company->getComId()));


			query.bindValue(0, company->getComFeedId());
			query.bindValue(1, company->getComAddress());
			query.bindValue(2, company->getCardNo());
			query.bindValue(3, company->getCreateTime());
			query.bindValue(4, company->getCreatorId());
			query.bindValue(5, company->getDisplayName());
			query.bindValue(6, company->getDisplayNamePinyin());
			query.bindValue(7, company->getExchangeMode());
			query.bindValue(8, company->getIndustry());
			query.bindValue(9, company->getIntroduction());
			query.bindValue(10, company->getLogo());
			query.bindValue(11, company->getPhone());
			query.bindValue(12, company->getEmail());
			query.bindValue(13, company->getUpdateTime());
			query.bindValue(14, company->getOwnerId());
			query.bindValue(15, company->getOrgCommunication());

			ret = query.exec();
			if (!ret)
			{
				qInfo() << "[LocalStorage][TNCompanyInfo]update SQL Error FEED failed. error=" << query.lastError();
			}
			mCount = ret ? mCount + 1 : mCount;
		}
		else
		{
			QSqlQuery query(*_db);
			query.prepare("INSERT INTO CompanyInfo (comId,comName,feedId,address,cardNo,createTime,creatorId,displayName,displayNamePinyin,exchangeMode,industry,introduction,logo,phone,email,updateTime,ext,ownerId)"
				"VALUES(:comId, :comName,:feedId, :address,:cardNo, :createTime,:creatorId,:displayName,:displayNamePinyin, :exchangeMode,:industry, :introduction, :logo, :phone, :email, :updateTime, :ext, :ownerId)");

			query.bindValue(":comId", company->getComId());
			query.bindValue(":comName", company->getComName());
			query.bindValue(":feedId", company->getComFeedId());
			query.bindValue(":address", company->getComAddress());
			query.bindValue(":cardNo", company->getCardNo());
			query.bindValue(":createTime", company->getCreateTime());
			query.bindValue(":creatorId", company->getCreatorId());
			query.bindValue(":displayName", company->getDisplayName());
			query.bindValue(":displayNamePinyin", company->getDisplayNamePinyin());
			query.bindValue(":exchangeMode", company->getExchangeMode());
			query.bindValue(":industry", company->getIndustry());
			query.bindValue(":introduction", company->getIntroduction());
			query.bindValue(":logo", company->getLogo());
			query.bindValue(":phone", company->getPhone());
			query.bindValue(":email", company->getEmail());
			query.bindValue(":updateTime", company->getUpdateTime());
			query.bindValue(":ext", company->getOrgCommunication());
			query.bindValue(":ownerId", company->getOwnerId());

			ret = query.exec();
			if (!ret)
			{
				qInfo() << "[LocalStorage][TNCompanyInfo]insert SQL Error FEED failed. error=" << query.lastError();
			}
			mCount = ret ? mCount + 1 : mCount;
		}
	}
	commitTransaction();
	return mCount;
}
bool TNCompanyInfo::InsertDatas(st_CompanyInfoPtr company)
{
	bool ret = false;
	if (tableIsExist("CompanyInfo"))
	{
		if (keyIsExist("CompanyInfo", "comId", company->getComId()))
		{
			QSqlQuery query(*_db);
			query.prepare(QString("UPDATE CompanyInfo SET feedId = ?, address = ?, cardNo = ?, createTime = ?, creatorId = ?, displayName = ?, displayNamePinyin = ?, exchangeMode = ?, industry = ?, introduction = ?, logo = ?, phone = ?, email = ?, updateTime = ?,ownerId = ? ,ext = ? WHERE comId = '%1'")
				.arg(company->getComId()));

			query.bindValue(0, company->getComFeedId());
			query.bindValue(1, company->getComAddress());
			query.bindValue(2, company->getCardNo());
			query.bindValue(3, company->getCreateTime());
			query.bindValue(4, company->getCreatorId());
			query.bindValue(5, company->getDisplayName());
			query.bindValue(6, company->getDisplayNamePinyin());
			query.bindValue(7, company->getExchangeMode());
			query.bindValue(8, company->getIndustry());
			query.bindValue(9, company->getIntroduction());
			query.bindValue(10, company->getLogo());
			query.bindValue(11, company->getPhone());
			query.bindValue(12, company->getEmail());
			query.bindValue(13, company->getUpdateTime());
			query.bindValue(14, company->getOwnerId());
			query.bindValue(15, company->getOrgCommunication());

			ret = query.exec();
			if (!ret)
			{
				qInfo() << "[LocalStorage][TNCompanyInfo]update SQL Error FEED failed. error=" << query.lastError();
			}
		}
		else
		{
			QSqlQuery query(*_db);
			query.prepare("INSERT INTO CompanyInfo (comId,comName,feedId,address,cardNo,createTime,creatorId,displayName,displayNamePinyin,exchangeMode,industry,introduction,logo,phone,email,updateTime,ext,ownerId)"
				"VALUES(:comId, :comName,:feedId, :address,:cardNo, :createTime,:creatorId,:displayName,:displayNamePinyin, :exchangeMode,:industry, :introduction, :logo, :phone, :email, :updateTime, :ext, :ownerId)");

			query.bindValue(":comId", company->getComId());
			query.bindValue(":comName", company->getComName());
			query.bindValue(":feedId", company->getComFeedId());
			query.bindValue(":address", company->getComAddress());
			query.bindValue(":cardNo", company->getCardNo());
			query.bindValue(":createTime", company->getCreateTime());
			query.bindValue(":creatorId", company->getCreatorId());
			query.bindValue(":displayName", company->getDisplayName());
			query.bindValue(":displayNamePinyin", company->getDisplayNamePinyin());
			query.bindValue(":exchangeMode", company->getExchangeMode());
			query.bindValue(":industry", company->getIndustry());
			query.bindValue(":introduction", company->getIntroduction());
			query.bindValue(":logo", company->getLogo());
			query.bindValue(":phone", company->getPhone());
			query.bindValue(":email", company->getEmail());
			query.bindValue(":updateTime", company->getUpdateTime());
			query.bindValue(":ext", company->getOrgCommunication());
			query.bindValue(":ownerId", company->getOwnerId());

			ret = query.exec();
			if (!ret)
			{
				qInfo() << "[LocalStorage][TNCompanyInfo]insert SQL Error FEED failed. error=" << query.lastError();
			}
		}
	}
	return ret;
}

bool TNCompanyInfo::Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue)
{
	if (tableIsExist("CompanyInfo"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec(QString("select *from CompanyInfo where %1='%2'").arg(queryItem).arg(queryValue));
		if (ret)
		{
			while (query.next())
			{
				st_CompanyInfoPtr company = std::make_shared<st_CompanyInfo>();
				company->setComId(query.value("comId").toString());
				company->setComName(query.value("comName").toString());
				company->setComFeedId(query.value("feedId").toString());
				company->setCardNo(query.value("cardNo").toString());
				company->setComAddress(query.value("address").toString());
				company->setCreateTime(query.value("createTime").toString());

				company->setCreatorId(query.value("creatorId").toString());
				company->setDisplayName(query.value("displayName").toString());
				company->setDisplayNamePinyin(query.value("displayNamePinyin").toString());
				company->setExchangeMode(query.value("exchangeMode").toString());
				company->setIndustry(query.value("industry").toString());
				company->setIntroduction(query.value("introduction").toString());

				company->setLogo(query.value("logo").toString());
				company->setPhone(query.value("phone").toString());
				company->setEmail(query.value("email").toString());
				company->setUpdateTime(query.value("updateTime").toString());
				company->setOwnerId(query.value("ownerId").toString());
				company->setOrgCommunication(query.value("ext").toString());

				if (company->getComId().isEmpty() || company->getComName().isEmpty()
					|| company->getComFeedId().isEmpty())
				{
					qDebug() << "[TNCompanyInfo] Error Query Invalid company";
					continue;
				}

				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(company);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "Query INTO CompanyInfo FAIL" << strLog;
			return false;
		}
	}
	return false;
}
int  TNCompanyInfo::Delete(const QString &queryItem, QList<QString> queryValueList)
{
	int nCount = 0;
	QList<QString>::iterator it;
	beginTransaction();
	for (it = queryValueList.begin(); it != queryValueList.end(); it++)
	{
		bool res = false;
		QSqlQuery query(*_db);
		res = query.exec(QString("DELETE FROM CompanyInfo where %1 = '%2'").arg(queryItem).arg((*it)));
		if (res)
			nCount++;
	}
	commitTransaction();
	return nCount;
}
bool TNCompanyInfo::Delete(const QString &queryItem, const QString &queryValue)
{
	bool res = false;
	QSqlQuery query(*_db);
	res = query.exec(QString("DELETE FROM CompanyInfo where %1 = '%2'").arg(queryItem).arg(queryValue));
	if (!res)
		qDebug() << "delete CompanyInfo fail" << query.lastError().text();
	return res;
}


bool TNCompanyInfo::GetAllFields(TableBaseVec &tableBaseVec)
{
	if (tableIsExist("CompanyInfo"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec("select *from CompanyInfo");
		if (ret)
		{
			while (query.next())
			{
				st_CompanyInfoPtr company = std::make_shared<st_CompanyInfo>();
				company->setComId(query.value("comId").toString());
				company->setComName(query.value("comName").toString());
				company->setComFeedId(query.value("feedId").toString());
				company->setCardNo(query.value("cardNo").toString());
				company->setComAddress(query.value("address").toString());
				company->setCreateTime(query.value("createTime").toString());

				company->setCreatorId(query.value("creatorId").toString());
				company->setDisplayName(query.value("displayName").toString());
				company->setDisplayNamePinyin(query.value("displayNamePinyin").toString());
				company->setExchangeMode(query.value("exchangeMode").toString());
				company->setIndustry(query.value("industry").toString());
				company->setIntroduction(query.value("introduction").toString());

				company->setLogo(query.value("logo").toString());
				company->setPhone(query.value("phone").toString());
				company->setEmail(query.value("email").toString());
				company->setUpdateTime(query.value("updateTime").toString());
				company->setOwnerId(query.value("ownerId").toString());
				company->setOrgCommunication(query.value("ext").toString());

				if (company->getComId().isEmpty() || company->getComName().isEmpty()
					|| company->getComFeedId().isEmpty())
				{
					qDebug() << "[TNCompanyInfo] Error GetAllFields Invalid company";
					continue;
				}
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(company);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "GetAllFields CompanyInfo FAIL" << strLog;
			return false;
		}
	}
	return false;
}


bool TNCompanyInfo::ClearAll()
{
	if (tableIsExist("CompanyInfo"))
	{
		QSqlQuery query(*_db);
		query.exec("DELETE FROM CompanyInfo");
	}
	return true;
}

void TNCompanyInfo::checkTable()
{

}

void TNCompanyInfo::createTable()
{
	if (!tableIsExist("CompanyInfo"))
	{
		QSqlQuery query(*_db);
		query.exec("Create  TABLE MAIN.[CompanyInfo]([comId] varchar(32) PRIMARY KEY UNIQUE NOT NULL,[comName] varchar(200), [feedId] varchar(32),[address] varchar(200), [cardNo] varchar(32),[createTime] varchar(32)"
			", [creatorId] varchar(32), [displayName] varchar(200), [displayNamePinyin] varchar(200), [exchangeMode] varchar(10),"
			"[industry] varchar(32), [introduction] varchar(32), [logo] varchar(200), [phone] varchar(32), [email] varchar(32), [updateTime] varchar(32), [ext] varchar(200), [ownerId] varchar(32))");
	}
}

void TNCompanyInfo::dropTable()
{
	if (tableIsExist("CompanyInfo"))
	{
		QSqlQuery query(*_db);
		query.exec("Drop Table MAIN.[CompanyInfo]");
	}
}
bool TNCompanyInfo::InsertDatas(QStringList list)
{
	if (tableIsExist("CompanyInfo"))
	{
		int i = 0;
		for (QString string : list.toSet())
		{
			if (!string.isEmpty())
			{
				QSqlQuery query(*_db);
				QString strSql = QString("INSERT INTO CompanyInfo (comId) VALUES('%1')")
					.arg(string);
				bool ret = query.exec(strSql);
				if (!ret)
				{
					QString strLog = query.lastError().text();
					qDebug() << "INSERT INTO CompanyId FAIL" << strLog;
				}
				else
				{
					++i;
				}
			}
		}
        if (i == list.toSet().size())
			return true;
	}
	return false;
}
bool TNCompanyInfo::UpdateSetValueByValueMap(QMap<QString, QString> valueMap, const QString field, const QString &whereName)
{
	int mCount = 0;
	if (!tableIsExist("CompanyInfo"))
	{
		return mCount;
	}
	QList<TableBasePtr>::iterator it;
	beginTransaction();
	for (QMap<QString, QString>::iterator it = valueMap.begin(); it != valueMap.end(); it++)
	{
		QString strSql = QString("UPDATE CompanyInfo SET %1 = '%2' WHERE %3 = '%4'")
				.arg(field)
				.arg(it.value())
				.arg(whereName)
				.arg(it.key());
		QSqlQuery query(*_db);
		bool ret = query.exec(strSql);
		if (!ret)
		{
			qInfo() << "[LocalStorage][TNCompanyInfo]UpdateSetValue SQL Error CompanyInfo: " << strSql << " Err:" << query.lastError();
		}
		mCount = ret ? mCount + 1 : mCount;
	}
	commitTransaction();
	return mCount;
}