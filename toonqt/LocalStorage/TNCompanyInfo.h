#ifndef TNCOMPANYINFO_H
#define TNCOMPANYINFO_H

#include <memory>
#include <QMap>
#include "TNBaseTable.h"
#include "LocalStorageCommon.h"

class TNCompanyInfo : public TNBaseTable
{
public:
	TNCompanyInfo();
	~TNCompanyInfo();

	bool InsertDatas(QStringList list);
	bool InsertDatas(st_CompanyInfoPtr group);
	int  InsertDatas(QList<TableBasePtr> myCompanyList);
	bool ClearAll();
	void checkTable() override;
	void createTable() override;
	void dropTable() override;
	bool GetAllFields(TableBaseVec &tableBaseVec);
	bool GetAllFieldsOfTableNameByField(const QString &fieldName, const QString &fieldValue, TableBaseVec &tableBaseVec);
	bool Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue);
	bool Delete(const QString &queryItem, const QString &queryValue);
	int  Delete(const QString &queryItem, QList<QString> queryValueList);
	bool UpdateSetValueByValueMap(QMap<QString, QString> ValueMap, const QString field, const QString &whereName);
private:
	
};
typedef std::shared_ptr<TNCompanyInfo> TNCompanyInfoPtr;
#endif // TNCOMPANYINFO_H
