#ifndef TNFACEID_H
#define TNFACEID_H

#include "TNBaseTable.h"
#include "LocalStorageCommon.h"

class TNFaceId : public TNBaseTable
{
public:
    TNFaceId();
    ~TNFaceId();
    bool insertData(st_FaceIdPtr st_face);
    int  insertDatas(QList<TableBasePtr> stFaceId_list);
    bool clearAll();

    void checkTable() override;
    void createTable() override;
    void dropTable() override;
    bool GetAllFields(TableBaseVec &tableBaseVec);
    bool Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue);
    bool Delete(const QString &queryItem, const QString &queryValue);
    int  Delete(const QString &queryItem, QList<QString> queryValueList);
};
typedef std::shared_ptr<TNFaceId> TNFaceIdPtr;

#endif // TNFACEID_H
