#ifndef TNSessionBackground_H
#define TNSessionBackground_H

#include <memory>

#include "TNBaseTable.h"
#include "LocalStorageCommon.h"

class TNSessionBackground :
	public TNBaseTable
{
public:
	TNSessionBackground();
	~TNSessionBackground();

	bool InsertDatas(st_SessionBackgroundPtr sessionBackground);
	bool ClearAll();

	void checkTable() override;
	void createTable() override;
	void dropTable() override;
	bool GetAllFields(TableBaseVec &tableBaseVec);
	bool GetAllFieldsOfTableNameByField(const QString &fieldName, const QString &fieldValue, TableBaseVec &tableBaseVec);
	bool Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue);
};

typedef std::shared_ptr<TNSessionBackground> TNSessionBackgroundPtr;

#endif