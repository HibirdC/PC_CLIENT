#ifndef TNMessageFault_H
#define TNMessageFault_H

#include <memory>

#include "TNBaseTable.h"
#include "LocalStorageCommon.h"

class TNMessageFault :
	public TNBaseTable
{
public:
	TNMessageFault();
	~TNMessageFault();

	bool InsertDatas(st_MessageFaultPtr messageFault);
	bool ClearAll();

	void checkTable() override;
	void createTable() override;
	void dropTable() override;
	bool GetAllFields(TableBaseVec &tableBaseVec);
	bool GetAllFieldsOfTableNameByField(const QString &fieldName, const QString &fieldValue, TableBaseVec &tableBaseVec);
	bool Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue);
};

typedef std::shared_ptr<TNMessageFault> TNMessageFaultPtr;

#endif