#ifndef TNReadSession_H
#define TNReadSession_H

#include <memory>

#include "TNBaseTable.h"
#include "LocalStorageCommon.h"

class TNReadSessionReq :
	public TNBaseTable
{
public:
	TNReadSessionReq();
	~TNReadSessionReq();

	bool InsertDatas(st_ReadSessionReqPtr myStuff);
	bool ClearAll();
	void checkTable() override;
	void createTable() override;
	void dropTable() override;
	bool GetAllFields(TableBaseVec &tableBaseVec);
	bool GetAllFieldsOfTableNameByField(const QString &fieldName, const QString &fieldValue, TableBaseVec &tableBaseVec);
	bool Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue);
	int  Delete(const QString &queryItem, const QString & queryValue);
	bool UpdateSetValueByField(const QString &fieldName, const QString &fieldValue, const QString &whereName, const QString &whereValue);
};

typedef std::shared_ptr<TNReadSessionReq> TNReadSessionReqPtr;

#endif