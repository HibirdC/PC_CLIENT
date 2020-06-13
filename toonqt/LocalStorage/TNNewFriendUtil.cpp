#include "TNNewFriendUtil.h"

#include "TNDataControlServer.h"

#include <QDate>
#include <QDebug>

TNNewFriendUtil::TNNewFriendUtil()
{
}


TNNewFriendUtil::~TNNewFriendUtil()
{
}

QList<st_NewFriendPtr> TNNewFriendUtil::getNewFriendList()
{
    QTime time;
    time.start();
    qDebug()<<"TNNewFriendUtil::getNewFriendList begin...";
    QStringList feedIdList;
    QList<st_NewFriendPtr> newFriendList;
    TableBaseVec feedTableBaseVec;
    TNDataControlServer::GetInstance()->GetAllFieldsByTableName("NewFriend", feedTableBaseVec,DBTYPE_USER);
    for (TableBaseVec::iterator iter = feedTableBaseVec.begin(); iter != feedTableBaseVec.end(); iter++)
    {
        st_NewFriendPtr aFriend = std::dynamic_pointer_cast<st_NewFriend>(*iter);
        feedIdList.append(aFriend->getFeedID());
        newFriendList.append(aFriend);
    }

    QList<st_NewFriendPtr> tempNewFriendList(newFriendList);
    foreach (const st_NewFriendPtr &var, tempNewFriendList)
    {
        // 如果是手机通讯录添加的好友申请且已经通过一次交换了，则将手机通讯录添加的好友申请过滤掉
        if ((var->getFromWhere() == QString("1")) && (var->getMyFeedID().isEmpty()) && !(var->getMobilePhone().isEmpty())
                && (feedIdList.count(var->getFeedID()) > 1))
        {
            newFriendList.removeOne(var);
        }
    }
    qDebug()<<"TNNewFriendUtil::getNewFriendList end. Time="<<time.elapsed();
    return newFriendList;
}

int TNNewFriendUtil::getUnReadCount()
{
    int count = 0;
    QList<st_NewFriendPtr> newFriendList = TNNewFriendUtil::getNewFriendList();
    foreach (const st_NewFriendPtr &aNewFriend, newFriendList)
    {
        if ((aNewFriend->getStatus() == QString("2")) && (aNewFriend->getIsRead() == QString("1")))
            count += 1;
    }

    return count;
}

void TNNewFriendUtil::clearUnReadStatus()
{
    TNDataControlServer::GetInstance()->UpdateSetValueByField("NewFriend", "isRead", "0", QString::null, QString::null,DBTYPE_USER);
}
