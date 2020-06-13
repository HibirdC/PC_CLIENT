#ifndef TNBlackList_H
#define TNBlackList_H

#include <memory>

#include "TNBaseTable.h"
#include "LocalStorageCommon.h"

#define STATUS_NONE				0   //未设置
#define STATUS_BLACK			1   //只拉黑
#define STATUS_DISTURB			2   //只免扰
#define STATUS_BLK_AND_DIS		3   //拉黑且免扰
class TNBlackList :
	public TNBaseTable
{
public:
	TNBlackList();
	~TNBlackList();

	bool InsertDatas(st_BlackListPtr blackInfo);
	bool ClearAll();

	void checkTable() override;
	void createTable() override;
	void dropTable() override;
	bool GetAllFields(TableBaseVec &tableBaseVec);
	bool GetAllFieldsOfTableNameByField(const QString &fieldName, const QString &fieldValue, TableBaseVec &tableBaseVec);
	bool Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue);
	bool GetLatestUser(TableBaseVec &tableBaseVec);
    bool UpdateSetValueByField(const QString &fieldName, const QString &fieldValue, const QString &whereName, const QString &whereValue);
};

typedef std::shared_ptr<TNBlackList> TNBlackListPtr;

#endif
