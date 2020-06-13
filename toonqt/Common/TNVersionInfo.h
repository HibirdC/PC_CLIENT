#pragma once

#include "common_global.h"

#include <QString>
#include <QSettings>
//#define BJTOON                    //北京通定制版标识
//#define DAOTOON						//东奥通定制版标识
//#define QLTOON					//北京青联定制版标识
//#define MCTOON					//门城通定制版标识
enum APP_TYPE
{
	APP_TYPE_TOON = 0,				//基础toon
	APP_TYPE_BJTOON,				//北京通
	APP_TYPE_DAOTOON,				//冬奥通
	APP_TYPE_QLTOON,				//北京青联
	APP_TYPE_MCTOON,				//门城通
	APP_TYPE_ZQTOON,				//中青通
	APP_TYPE_CYTOON,				//朝阳通
	APP_TYPE_JSTOON,				//监事通
	APP_TYPE_MAX
};
//#ifdef BJTOON
//    #define TOON_ICON    QIcon(":/bjtoon/Resources/img/skin/bjtoon/windowsicon.png")
//    #define TOON_TITLE   QStringLiteral("北京通")
//    #define APPTYPE		"100102"	//应用类型
//#elif defined(DAOTOON)
//    #define TOON_TITLE   QStringLiteral("即时通讯")
//    #define TOON_ICON    QIcon(":/dongao/Resources/img/skin/dongao/windowsicon.png")
//    #define APPTYPE		"100137"	//应用类型
//#elif defined(QLTOON)
//    #define TOON_TITLE   QStringLiteral("北京青联")
//    #define TOON_ICON    QIcon(":/qltoon/Resources/img/skin/qltoon/windowsicon.png")
//    #define APPTYPE		"100133"	//应用类型
//#elif defined(MCTOON)
//    #define TOON_TITLE   QStringLiteral("门城通")
//    #define TOON_ICON    QIcon(":/mctoon/Resources/img/skin/mctoon/windowsicon.png")
//    #define APPTYPE		"100105"	//应用类型
//#elif defined(ZQTOON)
//    #define TOON_TITLE   QStringLiteral("中青通")
//    #define TOON_ICON    QIcon(":/zqtoon/Resources/img/skin/zqtoon/windowsicon.png")
//    #define APPTYPE		"100141"	//应用类型
//#else
//    #define TOON_TITLE   QStringLiteral("toon")
//    #define TOON_ICON    QIcon(":/img/Resources/img/windowsicon.png")
//    #define APPTYPE		"100100"	//应用类型
//#endif
class COMMON_EXPORT TNVersionInfo
{
public:
    TNVersionInfo();
    ~TNVersionInfo();
	static TNVersionInfo* GetInstance();
    static QString appVersion(); //版本号
    static QString buildNo();    //打包编号
	static QString GetDefaultQss();
	static QString GetLoginWaveRes();
	static QString GetUserProtocolHtml();
	static QString GetSystemTrayRes();
    static QString GetNullPageRes_cardcase();
    static QString GetNullPageRes_search();
	static bool	   IsBaseToonVersion();
	APP_TYPE GetAppType();
	QIcon GetAppIcon();
	QString GetAppTypeString();
	QString GetAppTitle();
	QString GetAppCopyRight();
private:
	QSettings* _versionSettings;
	APP_TYPE   _appType;
private:
	static QString s_tableAppType[APP_TYPE_MAX];
	static QString s_tableAppTitle[APP_TYPE_MAX];
	static QString s_tableAppCopyRight[APP_TYPE_MAX];
	static QString s_tableAppSelectColor[APP_TYPE_MAX];
	static QString s_tableAppHoverColor[APP_TYPE_MAX];
	static QString s_tableAppThemeColor[APP_TYPE_MAX];
#define TOON_TITLE		TNVersionInfo::GetInstance()->GetAppTitle()
#define APPTYPE			TNVersionInfo::GetInstance()->GetAppTypeString()	
#define ENUM_APPTYPE	TNVersionInfo::GetInstance()->GetAppType()	
#define TOON_ICON		TNVersionInfo::GetInstance()->GetAppIcon()
#define APP_COPYRIGHT	TNVersionInfo::GetInstance()->GetAppCopyRight()
};

