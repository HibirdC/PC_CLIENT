#include "tnfaceid.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#define TABLE_NAME "FaceId"
#define PHONE_NUM "phone_num"
#define FEED_ID "feed_id"
TNFaceId::TNFaceId()
{

}


TNFaceId::~TNFaceId()
{

}

bool TNFaceId::insertData(st_FaceIdPtr st_face)
{
    if(!tableIsExist(TABLE_NAME))
        return false;

    QSqlQuery query(*_db);
    QString strSql = QString("INSERT INTO FaceId ([phone_num],[feed_id])"
                             "VALUES('%1', '%2'))")
                            .arg(st_face->get_phone_num())
                            .arg(st_face->get_feedId());
    bool ret = query.exec(strSql);
    if (ret){
        return true;
    }else{
        QString strLog = query.lastError().text();
        qDebug() << "INSERT INTO FaceId FAIL" << strLog;
    }
    return false;
}

void TNFaceId::createTable()
{
    if (!tableIsExist(TABLE_NAME)){
        QSqlQuery query(*_db);
        bool ret = query.exec("Create TABLE FaceId"
                   "(id integer primary key autoincrement,"
                   "[phone_num] varchar(32),"
                   "[feed_id] varchar(32))");
        if(!ret){
            qDebug() << "Create TABLE FaceId failed!";
        }
    }
}

bool TNFaceId::clearAll()
{
    if(!tableIsExist(TABLE_NAME))
        return false;
    QSqlQuery query(*_db);
    query.exec("DELETE FROM FaceId");
    return true;
}

void TNFaceId::checkTable()
{
}

bool TNFaceId::GetAllFields(TableBaseVec &tableBaseVec)
{
    if (tableIsExist(TABLE_NAME)){
        QSqlQuery query(*_db);
        bool ret = query.exec("select * from FaceId");
        if (ret){
            while (query.next()){
                st_FaceIdPtr FeedTable = std::make_shared<st_FaceId>();
                FeedTable->set_phone_num(query.value(PHONE_NUM).toString());
                FeedTable->set_feedId(query.value(FEED_ID).toString());
                TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(FeedTable);
                tableBaseVec.push_back(tempTableBase);
            }
            return true;
        }else{
            QString strLog = query.lastError().text();
            qDebug() << "query" << TABLE_NAME << "failed:" << strLog;
            return false;
        }
    }
    return false;
}

void TNFaceId::dropTable()
{
    if (tableIsExist(TABLE_NAME)){
        QSqlQuery query(*_db);
        query.exec("Drop Table FaceId");
    }
}

bool TNFaceId::Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue)
{
    if (tableIsExist(TABLE_NAME)){
        QSqlQuery query(*_db);
        bool ret = query.exec(QString("select * from FaceId where %1='%2'").arg(queryItem).arg(queryValue));
        if (ret){
            while (query.next()){
                st_FaceIdPtr faceIdTable= std::make_shared<st_FaceId>();
                faceIdTable->set_feedId(query.value(FEED_ID).toString());
                faceIdTable->set_phone_num(query.value(PHONE_NUM).toString());
                TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(faceIdTable);
                tableBaseVec.push_back(tempTableBase);
            }
            return true;
        }else{
            QString strLog = query.lastError().text();
            qDebug() << "Query FaceId failed:" << strLog;
            return false;
        }
    }
    return false;
}

int TNFaceId::insertDatas(QList<TableBasePtr> stFaceId_list)
{
    int mCount = 0;
    QList<TableBasePtr>::iterator it;
    beginTransaction();
    for (it = stFaceId_list.begin(); it != stFaceId_list.end(); ++it){
        st_FaceIdPtr stFaceId = std::dynamic_pointer_cast<st_FaceId>(*it);
        QString strSql;
        if (keyIsExist(TABLE_NAME, FEED_ID, stFaceId->get_feedId())){
            continue;
        }else{
            strSql = QString("INSERT INTO FaceId ([phone_num],[feed_id])"
                             "VALUES('%1', '%2')")
                            .arg(stFaceId->get_phone_num())
                            .arg(stFaceId->get_feedId());
        }
        QSqlQuery query(*_db);
        bool ret = query.exec(strSql);
        if (!ret){
            qDebug() << "SQL Error FaceId: " + strSql;
            qDebug() << query.lastError();
        }
        mCount = ret ? mCount + 1 : mCount;
    }
    commitTransaction();
    return mCount;
}

bool TNFaceId::Delete(const QString &queryItem, const QString &queryValue)
{
    bool res = false;
    QSqlQuery query(*_db);
    res = query.exec(QString("DELETE FROM FaceId where %1 = '%2'").arg(queryItem).arg(queryValue));
    if (!res)
        qDebug() << "delete NewFriend fail" << query.lastError().text();
    return res;
}

int TNFaceId::Delete(const QString &queryItem, QList<QString> queryValueList)
{
    int nCount = 0;
    QList<QString>::iterator it;
    beginTransaction();
    for (it = queryValueList.begin(); it != queryValueList.end(); it++)
    {
        bool res = false;
        QSqlQuery query(*_db);
        res = query.exec(QString("DELETE FROM FaceId where %1 = '%2'").arg(queryItem).arg((*it)));
        if (res)
            nCount++;
    }
    commitTransaction();
    return nCount;
}
