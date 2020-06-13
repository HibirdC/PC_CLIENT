#ifndef TNMYSTUFF_H
#define TNMYSTUFF_H

#include <memory>

#include "TNBaseTable.h"
#include "LocalStorageCommon.h"

class TNMyStuff :
	public TNBaseTable
{
public:
	TNMyStuff();
	~TNMyStuff();

	bool InsertDatas(st_MyStuffPtr myStuff);
	int  InsertDatas(QList<TableBasePtr> myStuffList);
	bool ClearAll();
	bool isMySelf(const QString &feedId);
	void checkTable() override;
	void createTable() override;
	void dropTable() override;
	bool GetAllFields(TableBaseVec &tableBaseVec);
	bool GetAllFieldsOfTableNameByField(const QString &fieldName, const QString &fieldValue, TableBaseVec &tableBaseVec);
	bool Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue);
	int  Delete(const QString &queryItem, QList<QString> queryValueList);
	int  Delete(const QString &queryItem, const QString & queryValue);
	bool MultiQuery(TableBaseVec &tableBaseVec, const QString &queryItem1, const QString &queryItem2, const QString &queryValue1, const QString &queryValue2);
	bool UpdateSetValueByField(const QString &fieldName, const QString &fieldValue, const QString &whereName, const QString &whereValue);
};

typedef std::shared_ptr<TNMyStuff> TNMyStuffPtr;

#endif