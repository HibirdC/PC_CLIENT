#ifndef TNSession_H
#define TNSession_H

#include <memory>

#include "TNBaseTable.h"
#include "LocalStorageCommon.h"

class TNSession :
	public TNBaseTable
{
public:
	TNSession();
	~TNSession();

	bool InsertDatas(st_SessionPtr session);
	bool ClearAll();

	void checkTable() override;
	void createTable() override;
	void dropTable() override;
	bool GetAllFields(TableBaseVec &tableBaseVec);
	bool GetAllFieldsOfTableNameByField(const QString &fieldName, const QString &fieldValue, TableBaseVec &tableBaseVec);
	bool UpdateSetValueByField(const QString &fieldName, const QString &fieldValue, const QString &whereName, const QString &whereValue);
	bool UpdateSetValueByFieldEx(const QString &fieldName, const QString &fieldValue, const QString &whereName, const QString &whereValue, const QString &fieldNameEx, const QString &fieldValueEx);
	bool Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue);
	bool Delete(const QString &queryItem, const QString &queryValue);
	int  Delete(const QString &queryItem, QList<QString> queryValueList);
	int  GetUNReadCount(const QString &feedID);
};

typedef std::shared_ptr<TNSession> TNSessionPtr;

#endif