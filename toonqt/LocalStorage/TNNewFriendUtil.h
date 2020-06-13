#ifndef TNNEWFRIENDUTIL_H
#define TNNEWFRIENDUTIL_H

#include "localstorage_global.h"
#include "LocalStorageCommon.h"
#include "common_global.h"

#include <QList>
#include <QString>
#include <QVariant>


class LOCALSTORAGE_EXPORT TNNewFriendUtil
{
public:
    TNNewFriendUtil();
    ~TNNewFriendUtil();

    static QList<st_NewFriendPtr> getNewFriendList();

    static int getUnReadCount();

    static void clearUnReadStatus();
};

#endif // TNNEWFRIENDUTIL_H
