#include "TNUpgradePlatform.h"
#include "TNVersionInfo.h"
#include <QDebug>

QMap<QString, QString> TNUpgradePlatform::m_platformToChannelNo;
QMap<QString, QString> TNUpgradePlatform::initialChannelNo()
{
    QMap<QString, QString> channelNoMap;
    channelNoMap[xpPlatformName()] = APPTYPE + QStringLiteral("2012") + QStringLiteral("04");

    channelNoMap[win32PlatformName()] = APPTYPE + QStringLiteral("2012") + QStringLiteral("01");
    channelNoMap[win64PlatformName()] = APPTYPE + QStringLiteral("2012") + QStringLiteral("02");

    channelNoMap[macPlatformName()] =  APPTYPE + QStringLiteral("2012") + QStringLiteral("03");

    channelNoMap[linuxPlatformName()] = APPTYPE + QStringLiteral("2012") + QStringLiteral("05");

    return channelNoMap;
}

TNUpgradePlatform::TNUpgradePlatform()
{
}

TNUpgradePlatform::~TNUpgradePlatform()
{
}

QString TNUpgradePlatform::xpPlatformName()
{
    return "winxp";
}

QString TNUpgradePlatform::win32PlatformName()
{
    return "win32";
}

QString TNUpgradePlatform::win64PlatformName()
{
    return "win64";
}

QString TNUpgradePlatform::macPlatformName()
{
    return "mac";
}

QString TNUpgradePlatform::linuxPlatformName()
{
    return "linux";
}

QString TNUpgradePlatform::getPlatformName()
{
    QString platformName;
#ifdef Q_OS_MAC
    platformName = macPlatformName();
#elif __linux__
    platformName = linuxPlatformName();
#else
    #ifdef _WIN64
		platformName = win64PlatformName();
    #else
		platformName = win32PlatformName();
    #endif
#endif

    //platformName = macPlatformName();
    qDebug()<<"platformName="<<platformName;
    return platformName;
}

QString TNUpgradePlatform::getPlatformChannelNo()
{
    const QString platformName = TNUpgradePlatform::getPlatformName();
    if (m_platformToChannelNo.isEmpty())
        m_platformToChannelNo = initialChannelNo();
    Q_ASSERT(m_platformToChannelNo.contains(platformName));
    return m_platformToChannelNo[platformName];
}
