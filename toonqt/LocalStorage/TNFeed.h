#ifndef TNFEED_H
#define TNFEED_H

#include <memory>

#include "TNBaseTable.h"
#include "LocalStorageCommon.h"

class TNFeed :
	public TNBaseTable
{
public:
	TNFeed();
	~TNFeed();

	int  InsertDatas(QList<TableBasePtr> stFeedList);
	bool InsertDatas(st_FeedPtr stFeed);
	bool ClearAll();

	void checkTable() override;
	void createTable() override;
	void dropTable() override;
	bool GetAllFields(TableBaseVec &tableBaseVec);
	bool GetAllFieldsOfTableNameByField(const QString &fieldName, const QString &fieldValue, TableBaseVec &tableBaseVec);
	bool Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue);
	bool batchQuery(TableBaseVec &tableBaseVec, const QString &queryItem, const QStringList &queryValues);
    int  FuzzyQuery(TableBaseVec &tableBaseVec, const QString &text,QStringList keyList,const QString &type);
    bool UpdateSetValueByFieldMap(QMap<QString, QString> &fieldMap, const QString &whereName, const QString &whereValue);
	bool UpdateSetValueByValueMap(QMap<QString, QString> valueMap, const QString field, const QString &whereName);
    bool updateSetValueByField(const QString& fieldName,const QString& fieldValue,const QString& whereName,const QString& whereValue);
};

typedef std::shared_ptr<TNFeed> TNFeedPtr;

#endif
