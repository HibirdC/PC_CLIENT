#include "TNLoginUtil.h"

#include <QDebug>
#include <QSysInfo>
#include <QObject>
#include <QNetworkInterface>
#include <QCryptographicHash>

#include "TNVersionInfo.h"

TNLoginUtil::TNLoginUtil()
{
}

TNLoginUtil::~TNLoginUtil()
{
}

bool TNLoginUtil::checkMobileNumber(const QString &mobilenumer)
{
    QRegExp e("^[1][0-9]{10}$");
    return e.exactMatch(mobilenumer);
}

bool TNLoginUtil::checkOperationNumber(const QString &mobilenumer)
{
    QRegExp e("^[1][0-9]{10}$");
    return e.exactMatch(mobilenumer);
}

bool TNLoginUtil::checkPasswordValid(const QString &password)
{
    bool hasNum = false;
    bool hasLetter = false;
    bool hasSymbol = false;

    // 如果小于8位或者大于16位，则为错误密码
    if (password.size()<8 || password.size()>16)
    {
        return false;
    }

    for (int i = 0; i < password.size(); i++)
    {
        QChar ch = password.at(i);

        // 只能为数字、字母和符号, 如果出现不符合规则的字符则为错误密码
        if (ch < 0x21 || ch > 0x7e)
        {
            return false;
        }

        if (ch.isDigit()) // 包含数字
        {
            hasNum = true;
        }
        else if (ch.isLetter()) // 包含字母
        {
            hasLetter = true;
        }
        else // if (ch.isSymbol()) // 包含符号
        {
            hasSymbol = true;
        }
    }

    bool isPwd = (hasNum && hasLetter) || (hasNum && hasSymbol) || (hasLetter && hasSymbol);
    return isPwd;
}

QString TNLoginUtil::getPasswordAfterMD5(const QString &strPassword)
{
    //密码md5加密
    QByteArray ba;
    ba.append(strPassword);
    QCryptographicHash md(QCryptographicHash::Md5);
    md.addData(ba);

    return QString(md.result().toHex());
}

void TNLoginUtil::TokenCode(const QString &original, QString &strPwd, const QString &key, int type)
{
    QString tempSubKey = key;
    tempSubKey = tempSubKey.replace(QRegExp("(?:-|\\s|:)"), "");
    QByteArray byteStr = original.toLatin1();
    QByteArray byteKey = tempSubKey.toLatin1();
    unsigned char subKey = 0;
    for (int i = 0; i < byteKey.size(); i++)
    {
        if (i % 2 == 1)
        {
            subKey += byteKey[i];
        }
    }
    if (type == 0)
    {
        for (int i = 0; i < byteStr.size(); i++){
            byteStr[i] = byteStr[i] ^ subKey;
        }
        strPwd.append(byteStr.toBase64());
    }
    else if (type == 1)
    {
        QByteArray byte = QByteArray::fromBase64(byteStr);
        for (int i = 0; i < byte.size(); i++){
            byte[i] = byte[i] ^ subKey;
        }
        strPwd.append(byte);
    }
}

QString TNLoginUtil::getHostMacAddress()
{
    QList<QNetworkInterface> nets = QNetworkInterface::allInterfaces(); // 获取所有网络接口列表
    int nCnt = nets.count();
    QString strMacAddr;
    for (int i = 0; i < nCnt; i++)
    {
        // 如果此网络接口被激活并且正在运行并且不是回环地址，则就是我们需要找的Mac地址
        if ( nets[i].flags().testFlag(QNetworkInterface::IsUp)
             && nets[i].flags().testFlag(QNetworkInterface::IsRunning)
             && !nets[i].flags().testFlag(QNetworkInterface::IsLoopBack) )
        {
            strMacAddr = nets[i].hardwareAddress();
            break;
        }
    }

    return strMacAddr;
}

QString TNLoginUtil::getUserAgent()
{
    QString strRet;
    strRet = QString("platform:%1,deviceId:%2,appVersion:%3,platformVersion:%4,toonType:%5")
            .arg(QSysInfo::productType())
            .arg(getHostMacAddress())
            .arg(TNVersionInfo::appVersion())
            .arg(QSysInfo::productVersion())
            .arg(APPTYPE);

    return strRet;
}

bool TNLoginUtil::parseMobileFromLoginUser(const st_LoginUserPtr &loginUser, QString *teleCode, QString *mobile, QString *errorContent)
{
    if (loginUser == nullptr)
        return false;

    QString teleCodeMobile = loginUser->GetMobile();
    if (!teleCodeMobile.startsWith("00"))
    {
        if (errorContent)
            *errorContent = QString("本次自动登录无效");
        return false;
    }

    if (teleCode)
        *teleCode = teleCodeMobile.left(4);
    if (mobile)
        *mobile   = teleCodeMobile.mid(4);

    return true;
}
