#ifndef TNSETUP_H
#define TNSETUP_H

#include <memory>

#include "TNBaseTable.h"
#include "LocalStorageCommon.h"

class TNSetUp :
	public TNBaseTable
{
public:
	TNSetUp();
	~TNSetUp();

	bool InsertDatas(st_SetUpPtr settings);
	bool ClearAll();

	void checkTable() override;
	void createTable() override;
	void dropTable() override;
	bool GetAllFields(TableBaseVec &tableBaseVec);
	bool GetAllFieldsOfTableNameByField(const QString &fieldName, const QString &fieldValue, TableBaseVec &tableBaseVec);
	bool Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue);

private:
	bool exist(const QString &fieldValue);
	bool UpdateData(const QString &key, const QString &newValue);
	bool InsertData(const QString &key, const QString &value);
};

typedef std::shared_ptr<TNSetUp> TNSetUpPtr;

#endif