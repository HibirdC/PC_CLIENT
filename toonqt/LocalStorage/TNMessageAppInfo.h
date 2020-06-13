#ifndef TNMessageAppInfo_H
#define TNMessageAppInfo_H

#include <memory>

#include "TNBaseTable.h"
#include "LocalStorageCommon.h"

class TNMessageAppInfo :
	public TNBaseTable
{
public:
	TNMessageAppInfo();
	~TNMessageAppInfo();

	bool InsertDatas(st_MessageAppInfoPtr messageAppInfo);
	bool ClearAll();

	void checkTable() override;
	void createTable() override;
	void dropTable() override;
	bool GetAllFields(TableBaseVec &tableBaseVec);
	bool GetAllFieldsOfTableNameByField(const QString &fieldName, const QString &fieldValue, TableBaseVec &tableBaseVec);
	bool Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue);
};

typedef std::shared_ptr<TNMessageAppInfo> TNMessageAppInfoPtr;

#endif