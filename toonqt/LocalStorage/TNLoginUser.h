#ifndef TNLOGINUSER_H
#define TNLOGINUSER_H

#include <memory>

#include "TNBaseTable.h"
#include "LocalStorageCommon.h"

class TNLoginUser :
	public TNBaseTable
{
public:
	TNLoginUser();
	~TNLoginUser();

	bool InsertDatas(st_LoginUserPtr login);
	bool ClearAll();

	void checkTable() override;
	void createTable() override;
	void dropTable() override;
	bool GetAllFields(TableBaseVec &tableBaseVec);
	bool GetAllFieldsOfTableNameByField(const QString &fieldName, const QString &fieldValue, TableBaseVec &tableBaseVec);
	bool Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue);
	bool GetLatestUser(TableBaseVec &tableBaseVec);
	bool GetUserIsExist(const QString &userName);
};

typedef std::shared_ptr<TNLoginUser> TNLoginUserPtr;

#endif