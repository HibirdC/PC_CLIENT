#ifndef TNChatSettings_H
#define TNChatSettings_H

#include <memory>

#include "TNBaseTable.h"
#include "LocalStorageCommon.h"

class TNChatSettings :
	public TNBaseTable
{
public:
	TNChatSettings();
	~TNChatSettings();

	bool InsertDatas(st_ChatSettingsPtr login);
	bool ClearAll();

	void checkTable() override;
	void createTable() override;
	void dropTable() override;
	bool GetAllFields(TableBaseVec &tableBaseVec);
	bool GetAllFieldsOfTableNameByField(const QString &fieldName, const QString &fieldValue, TableBaseVec &tableBaseVec);
	bool Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue);
};

typedef std::shared_ptr<TNChatSettings> TNChatSettingsPtr;

#endif