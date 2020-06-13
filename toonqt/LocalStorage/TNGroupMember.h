#ifndef TNGroupMember_H
#define TNGroupMember_H

#include <memory>

#include "TNBaseTable.h"
#include "LocalStorageCommon.h"

class TNGroupMember :
	public TNBaseTable
{
public:
	TNGroupMember();
	~TNGroupMember();

	bool InsertDatas(st_GroupMemberPtr groupMember);
	int  InsertDatas(QList<TableBasePtr> groupMemberList);
	bool ClearAll();

	void checkTable() override;
	void createTable() override;
	void dropTable() override;
	bool Delete(const QString &queryItem, const QString &queryValue);
	bool DeleteEx(const QString &queryItem, const QString &queryValue, const QString &queryItemEx, const QString &queryValueEx);
	bool GetAllFields(TableBaseVec &tableBaseVec);
	bool GetAllFieldsOfTableNameByField(const QString &fieldName, const QString &fieldValue, TableBaseVec &tableBaseVec);
	bool Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue);
	int  Delete(const QString &queryItem, QList<QString> queryValueList);
	int  Delete(QList<QVector<QString> > groupMemberList);
	bool keyIsExistExt(const QString& tableName, const QString& key, const QString& Value,
		const QString &keyExt,const QString &valueExt);
};

typedef std::shared_ptr<TNGroupMember> TNGroupMemberPtr;

#endif
