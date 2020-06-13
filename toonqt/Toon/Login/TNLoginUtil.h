#ifndef TNLOGINUTIL_H
#define TNLOGINUTIL_H

#include <QString>
#include <QDateTime>

#include "LocalStorageCommon.h"

class TNLoginUtil
{
public:
    TNLoginUtil();
    ~TNLoginUtil();

    static bool checkMobileNumber(const QString &mobilenumer);

    static bool checkOperationNumber(const QString &mobilenumer);

    static bool checkPasswordValid(const QString &password);

    static QString getPasswordAfterMD5(const QString &strPassword);

    static void TokenCode(const QString &original, QString &strPwd,const QString &key, int type);

    static QString getHostMacAddress();

    static QString getUserAgent();

    static bool parseMobileFromLoginUser(const st_LoginUserPtr &loginUser, QString *teleCode, QString *mobile, QString *errorContent);
};

#endif // TNLOGINUTIL_H
