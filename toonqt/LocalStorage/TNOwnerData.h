#ifndef TNOWNERDATA_H
#define TNOWNERDATA_H

#include <memory>
#include <QMap>
#include "TNBaseTable.h"
#include "LocalStorageCommon.h"

class TNOwnerData : public TNBaseTable
{
public:
	TNOwnerData();
	~TNOwnerData();

	bool InsertDatas(st_OwnerDataPtr owner);
	void checkTable() override;
	void createTable() override;
	void dropTable() override;
	bool Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue);
	bool Delete(const QString &queryItem, const QString &queryValue);
	bool getOwnerStatus(const QString &userId);
	bool GetAllFields(TableBaseVec &tableBaseVec);
private:
	
};
typedef std::shared_ptr<TNOwnerData> TNOwnerDataPtr;
#endif // TNOWNERDATA_H
