#ifndef TNBMESSAGE0_H
#define TNBMESSAGE0_H

#include <memory>

#include "TNBaseTable.h"
#include "LocalStorageCommon.h"

class TNBMessage0 :
	public TNBaseTable
{
public:
	TNBMessage0();
	~TNBMessage0();

	bool InsertDatas(st_BMessage0Ptr message);
	bool ClearAll();

	void checkTable() override;
	void createTable() override;
	void dropTable() override;
	bool GetAllFields(TableBaseVec &tableBaseVec);
	bool UpdateSetValueByField(const QString &fieldName, const QString &fieldValue, const QString &whereName, const QString &whereValue);
	bool UpdateSetValueByFieldEx(const QString &fieldName, const QString &fieldValue, const QString &whereName, const QString &whereValue, const QString &fieldNameEx, const QString &fieldValueEx);
	bool UpdateSetValueByFieldMap(QMap<QString, QString>& fieldMap , const QString &whereName, const QString &whereValue);
	bool GetAllFieldsOfTableNameByField(const QString &fieldName, const QString &fieldValue, TableBaseVec &tableBaseVec);
    bool Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue, int pageNum = -1, int pageIndex = 0, int newMsgNum = 0);
    bool queryHistoryMsg(TableBaseVec& tableBaseVec,const QString& sessionId,
                         const QString& msgId,int num);
	bool Delete(const QString &queryItem, const QString &queryValue);
	int  Delete(const QString &queryItem, QList<QString> queryValueList);
    bool getUnreadFirstMsg(const QString& sessionId,int num,st_BMessage0Ptr& message);
    bool getUnreadMsg(TableBaseVec &tableBaseVec,
                      const QString& sessionId,
                      const QString& currentFristMsgId,
                      const QString& firstUnreadMsgId);
};

typedef std::shared_ptr<TNBMessage0> TNBMessage0Ptr;

#endif
