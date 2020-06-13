#ifndef TNVERSION_H
#define TNVERSION_H

#include <memory>

#include "TNBaseTable.h"
#include "LocalStorageCommon.h"

class TNVersion :
	public TNBaseTable
{
public:
	TNVersion();
	~TNVersion();

	bool InsertDatas(st_VersionPtr version);
	bool ClearAll();

	void checkTable() override;
	void createTable() override;
	void dropTable() override;
	bool GetAllFields(TableBaseVec &tableBaseVec);
	bool GetAllFieldsOfTableNameByField(const QString &fieldName, const QString &fieldValue, TableBaseVec &tableBaseVec);
	bool UpdateSetValueByField(const QString &fieldName, const QString &fieldValue, const QString &whereName, const QString &whereValue);
	bool Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue);
};

typedef std::shared_ptr<TNVersion> TNVersionPtr;

#endif