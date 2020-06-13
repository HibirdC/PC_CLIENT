#ifndef TNNewFriend_H
#define TNNewFriend_H

#include <memory>

#include "TNBaseTable.h"
#include "LocalStorageCommon.h"

class TNNewFriend : public TNBaseTable
{
public:
    TNNewFriend();
    ~TNNewFriend();

    int  InsertDatas(QList<TableBasePtr> stNewFriendList);
    bool InsertDatas(st_NewFriendPtr stNewFriend);
    bool ClearAll();

    void checkTable() override;
    void createTable() override;
    void dropTable() override;
    bool GetAllFields(TableBaseVec &tableBaseVec);
    bool GetAllFieldsOfTableNameByField(const QString &fieldName, const QString &fieldValue, TableBaseVec &tableBaseVec);
    bool Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue);
    bool UpdateSetValueByField(const QString &fieldName, const QString &fieldValue, const QString &whereName, const QString &whereValue);
    bool UpdateSetValueByFieldMap(QMap<QString, QString> &fieldMap, const QString &whereName, const QString &whereValue);
	int  Delete(const QString &queryItem, QList<QString> queryValueList);
	bool  Delete(const QString &queryItem, const QString &queryValue);
};

typedef std::shared_ptr<TNNewFriend> TNNewFriendPtr;

#endif // TNNewFriend_H
