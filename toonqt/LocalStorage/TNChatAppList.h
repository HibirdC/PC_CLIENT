#ifndef TNChatAppList_H
#define TNChatAppList_H

#include <memory>

#include "TNBaseTable.h"
#include "LocalStorageCommon.h"

class TNChatAppList :
	public TNBaseTable
{
public:
	TNChatAppList();
	~TNChatAppList();

	bool InsertDatas(st_ChatAppListPtr login);
	bool ClearAll();

	void checkTable() override;
	void createTable() override;
	void dropTable() override;
	bool GetAllFields(TableBaseVec &tableBaseVec);
	bool GetAllFieldsOfTableNameByField(const QString &fieldName, const QString &fieldValue, TableBaseVec &tableBaseVec);
	bool Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue);
};

typedef std::shared_ptr<TNChatAppList> TNChatAppListPtr;

#endif