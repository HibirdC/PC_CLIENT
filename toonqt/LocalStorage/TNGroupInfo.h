#ifndef TNGroupInfo_H
#define TNGroupInfo_H

#include <memory>

#include "TNBaseTable.h"
#include "LocalStorageCommon.h"

class TNGroupInfo :
	public TNBaseTable
{
public:
	TNGroupInfo();
	~TNGroupInfo();

	bool InsertDatas(st_GroupInfoPtr groupInfo);
	int  InsertDatas(QList<TableBasePtr> groupInfoList);
	bool ClearAll();

	void checkTable() override;
	void createTable() override;
	void dropTable() override;
	bool GetAllFields(TableBaseVec &tableBaseVec);
	bool Delete(const QString &queryItem, const QString &queryValue);
	bool GetAllFieldsOfTableNameByField(const QString &fieldName, const QString &fieldValue, TableBaseVec &tableBaseVec);
	bool Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue);
	bool UpdateSetValueByField(const QString &fieldName, const QString &fieldValue, const QString &whereName, const QString &whereValue);
	bool UpdateSetValueByFieldEx(const QString &fieldName, const QString &fieldValue, const QString &fieldNameEx, const QString &fieldValueEx, const QString &whereName, const QString &whereValue);
	int  Delete(const QString &queryItem, QList<QString> queryValueList);
};

typedef std::shared_ptr<TNGroupInfo> TNGroupInfoPtr;

#endif