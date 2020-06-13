#ifndef TNCOLLEAGUEGROUP_H
#define TNCOLLEAGUEGROUP_H

#include <memory>

#include "TNBaseTable.h"
#include "LocalStorageCommon.h"

class TNColleagueGroup :
	public TNBaseTable
{
public:
	TNColleagueGroup();
	~TNColleagueGroup();

	bool InsertDatas(st_ColleagueGroupPtr group);
	int  InsertDatas(QList<TableBasePtr> myColleagueGroupList);
	bool ClearAll();

	void checkTable() override;
	void createTable() override;
	void dropTable() override;
	bool GetAllFields(TableBaseVec &tableBaseVec);
	bool GetAllFieldsOfTableNameByField(const QString &fieldName, const QString &fieldValue, TableBaseVec &tableBaseVec);
	bool Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue);
	bool Delete(const QString &queryItem, const QString &queryValue);
	int  Delete(const QString &queryItem, QList<QString> queryValueList);
};

typedef std::shared_ptr<TNColleagueGroup> TNColleagueGroupPtr;

#endif