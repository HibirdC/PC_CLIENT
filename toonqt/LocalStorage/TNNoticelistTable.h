#ifndef TNNOTICELISTTABLE_H
#define TNNOTICELISTTABLE_H

#include <memory>

#include "TNBaseTable.h"
#include "LocalStorageCommon.h"

class TNNoticelistTable :
	public TNBaseTable
{
public:
	TNNoticelistTable();
	~TNNoticelistTable();

	bool InsertDatas(NoticelistTablePtr noticeList);
	bool ClearAll();

	void checkTable() override;
	void createTable() override;
	void dropTable() override;
	bool GetAllFields(TableBaseVec &tableBaseVec);
	bool GetAllFieldsOfTableNameByField(const QString &fieldName, const QString &fieldValue, TableBaseVec &tableBaseVec);
};

typedef std::shared_ptr<TNNoticelistTable> TNNoticelistTablePtr;

#endif