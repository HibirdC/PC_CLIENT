#include "TNVersionInfo.h"

#include <QDebug>
#include <QIcon>
#include "TNPathUtil.h"
#include "TNSettingData.h"
QString TNVersionInfo::s_tableAppType[APP_TYPE_MAX] = {
    "100100",
    "100102",
    "100137",
    "100133",
    "100105",
    "100141",
    "100139",
    "100168"
};
QString TNVersionInfo::s_tableAppTitle[APP_TYPE_MAX] = {
    QStringLiteral("通toon"),
    QStringLiteral("北京通"),
    QStringLiteral("即时通讯"),
    QStringLiteral("北京青联"),
    QStringLiteral("门城通"),
    QStringLiteral("中青通"),
    QStringLiteral("朝阳通"),
    QStringLiteral("监事通")
};
QString TNVersionInfo::s_tableAppCopyRight[APP_TYPE_MAX] = {
    QStringLiteral("北京思源互联科技有限公司版权所有"),
    QStringLiteral("北京思源互联科技有限公司版权所有"),
    QStringLiteral("2022年冬奥会和冬残奥会组织委员会"),
    QStringLiteral("北京思源互联科技有限公司版权所有"),
    QStringLiteral("北京思源政务通科技有限公司版权所有"),
    QStringLiteral("中国青年报社版权所有"),
    QStringLiteral("北京朝阳信息化工作办公室"),
    QStringLiteral("国务院国有资产监督管理委员会")
};
QString TNVersionInfo::s_tableAppSelectColor[APP_TYPE_MAX] = {
	"#d4e6ff",
    "#f1f1f1",
	"",
	"",
	"",
	"",
	"",
	""
};
QString TNVersionInfo::s_tableAppHoverColor[APP_TYPE_MAX] = {
	"#e3efff",
    "#f6f6f6",
	"",
	"",
	"",
	"",
	"",
	""
};
QString TNVersionInfo::s_tableAppThemeColor[APP_TYPE_MAX] = {
	"#3F94FC",
    "#DF3031",
	"",
	"",
	"",
	"",
	"",
	""
};
TNVersionInfo::TNVersionInfo() :_versionSettings(NULL), _appType(APP_TYPE_TOON)
{
	_versionSettings = new QSettings(TNPathUtil::getVersionPath(), QSettings::IniFormat);
	int apptype = _versionSettings->value("version/apptype", QVariant(0)).toInt();
	if (apptype < APP_TYPE_MAX && apptype >= APP_TYPE_TOON)
		_appType = (APP_TYPE)apptype;
	TNSettingData::InitDefaultAppSkinColor(s_tableAppThemeColor[_appType], s_tableAppHoverColor[_appType], s_tableAppSelectColor[_appType]);
}

TNVersionInfo::~TNVersionInfo()
{
}

TNVersionInfo* TNVersionInfo::GetInstance()
{
	static TNVersionInfo s_versionInfo;
	return &s_versionInfo;
}


QString TNVersionInfo::appVersion()
{
    return "1.6.0";
}

QString TNVersionInfo::buildNo()
{ 
    return "2018052101";
}

QString TNVersionInfo::GetDefaultQss()
{
    return ":/custom/Resources/img/custom/default.qss";
}

QString TNVersionInfo::GetLoginWaveRes()
{
    return ":/custom/Resources/img/custom/login-wave.gif";
}

QString TNVersionInfo::GetSystemTrayRes()
{
#ifndef Q_OS_MAC
        return ":/custom/Resources/img/custom/SystemTray.ico";
#else
        return ":/custom/Resources/img/custom/MacSystemTray.icns";
#endif
}

QString TNVersionInfo::GetNullPageRes_cardcase()
{
    return ":/sysButton/Resources/img/sysButton/cardcase-none.png";
}

QString TNVersionInfo::GetNullPageRes_search()
{
    return ":/sysButton/Resources/img/sysButton/search-none.png";
}

QString TNVersionInfo::GetUserProtocolHtml()
{
    return ":/custom/Resources/img/custom/user_protocol.html";
}

bool TNVersionInfo::IsBaseToonVersion()
{
	if (GetInstance()->GetAppType() == APP_TYPE_TOON)
		return true;
	else
		return false;
}

APP_TYPE TNVersionInfo::GetAppType()
{
	return _appType;
}

QString TNVersionInfo::GetAppTypeString()
{
	return s_tableAppType[_appType];
}

QIcon TNVersionInfo::GetAppIcon()
{
    return  QIcon(":/custom/Resources/img/custom/windowsicon.png");
}

QString TNVersionInfo::GetAppTitle()
{
	return s_tableAppTitle[_appType];
}

QString TNVersionInfo::GetAppCopyRight()
{
	return s_tableAppCopyRight[_appType];
}
