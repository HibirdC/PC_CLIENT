#ifndef TNJOINSTUFF_H
#define TNJOINSTUFF_H

#include <memory>

#include "TNBaseTable.h"
#include "LocalStorageCommon.h"

class TNJoinStuff :
	public TNBaseTable
{
public:
	TNJoinStuff();
	~TNJoinStuff();

	bool InsertDatas(st_JoinStuffPtr joinStuff);
	int  InsertDatas(QList<TableBasePtr> joinStuffList);
	bool ClearAll();

	void checkTable() override;
	void createTable() override;
	void dropTable() override;
	bool GetAllFields(TableBaseVec &tableBaseVec);
	bool GetAllFieldsOfTableNameByField(const QString &fieldName, const QString &fieldValue, TableBaseVec &tableBaseVec);
	bool Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue);
	bool MultiQuery(TableBaseVec &tableBaseVec, const QString &queryItem1, const QString &queryItem2, const QString &queryValue1, const QString &queryValue2);
	bool Delete(const QString &queryItem, const QString &queryValue);
	int  Delete(const QString &queryItem, QList<QString> Feeds);

	bool updateFeedRemark(QString feedBelongId,QString remark,QString remarkPY);
};

typedef std::shared_ptr<TNJoinStuff> TNJoinStuffPtr;

#endif