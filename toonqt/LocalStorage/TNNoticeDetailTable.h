#ifndef TNNOTICEDETAILTABLE_H
#define TNNOTICEDETAILTABLE_H

#include <memory>

#include "TNBaseTable.h"
#include "LocalStorageCommon.h"

class TNNoticeDetailTable :
	public TNBaseTable
{
public:
	TNNoticeDetailTable();
	~TNNoticeDetailTable();

	bool InsertDatas(NoticeDetailTablePtr noticeDetail);
	bool ClearAll();

	void checkTable() override;
	void createTable() override;
	void dropTable() override;
	bool GetAllFields(TableBaseVec &tableBaseVec);
	bool GetAllFieldsOfTableNameByField(const QString &fieldName, const QString &fieldValue, TableBaseVec &tableBaseVec);
};

typedef std::shared_ptr<TNNoticeDetailTable> TNNoticeDetailTablePtr;

#endif

