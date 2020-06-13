#ifndef TNColleagueRelation_H
#define TNColleagueRelation_H

#include <memory>

#include "TNBaseTable.h"
#include "LocalStorageCommon.h"

class TNColleagueRelation :
	public TNBaseTable
{
public:
	TNColleagueRelation();
	~TNColleagueRelation();

	bool InsertDatas(st_ColleagueRelationPtr relation);
	int  InsertDatas(QList<TableBasePtr> relationList);
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

typedef std::shared_ptr<TNColleagueRelation> TNColleagueRelationPtr;

#endif