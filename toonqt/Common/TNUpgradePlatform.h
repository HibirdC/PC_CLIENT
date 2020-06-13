#pragma once

#include "common_global.h"

#include <QMap>
#include <QString>

class COMMON_EXPORT TNUpgradePlatform
{
public:
    ~TNUpgradePlatform();

    static QString xpPlatformName();
    static QString win32PlatformName();
    static QString win64PlatformName();
    static QString macPlatformName();
    static QString linuxPlatformName();

    static QString getPlatformName();
    static QString getPlatformChannelNo();

private:
    TNUpgradePlatform();
    static QMap<QString, QString> m_platformToChannelNo;
    static QMap<QString, QString> initialChannelNo();
};

