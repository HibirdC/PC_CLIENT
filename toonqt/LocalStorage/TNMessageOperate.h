#ifndef TNMessageOperate_H
#define TNMessageOperate_H

#include <memory>

#include "TNBaseTable.h"
#include "LocalStorageCommon.h"

class TNMessageOperate :
	public TNBaseTable
{
public:
	TNMessageOperate();
	~TNMessageOperate();

	bool InsertDatas(st_MessageOperatePtr MessageOperate);
	bool ClearAll();

	void checkTable() override;
	void createTable() override;
	void dropTable() override;
	bool GetAllFields(TableBaseVec &tableBaseVec);
	bool GetAllFieldsOfTableNameByField(const QString &fieldName, const QString &fieldValue, TableBaseVec &tableBaseVec);
	bool Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue);
};

typedef std::shared_ptr<TNMessageOperate> TNMessageOperatePtr;

#endif