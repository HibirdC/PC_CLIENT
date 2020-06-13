#ifndef TNSETTINGDATA_H
#define TNSETTINGDATA_H
#include "common_global.h"
#include <QString>
//设置数据缓存类
#define STR_SKIN_KEY  "skin_type"
enum SKIN_TYPE
{
	SKIN_TYPE_DEFAULT = 0,
	SKIN_TYPE_PINK,
	SKIN_TYPE_GREEN,
	SKIN_TYPE_TEA,
	SKIN_TYPE_ORANGE,
	SKIN_TYPE_PURPLE,
	SKIN_TYPE_BUD,
	SKIN_TYPE_ORCHID
};

class COMMON_EXPORT TNSettingData
{
public:
	static TNSettingData * instance();
    ~TNSettingData(){}
private:
	TNSettingData();
public:
	const QString & LocalPath() { return m_localPath; }
	void SetLocalPath(const QString &value) { m_localPath = value; }
    void SetIsNewestVersion(bool value) { m_isNewestVersion = value; }
    bool isNewestVersion() { return m_isNewestVersion; }
	const QString & sendHotKey() { return m_sendHotKey; }
	void SetSendHotKey(const QString &value) { m_sendHotKey = value; }
	void SetSkinType(const SKIN_TYPE type) { m_currentSkinType = type; }
	SKIN_TYPE GetSkinType() { return m_currentSkinType; }
	void ApplySkinType(const SKIN_TYPE type);
	static void SetToonStyle(QList<QString>& styleList);
	const QString& GetCurrentHoverSkin();
	const QString& GetCurrentSelectSkin();
    const QString& GetCurrentThemeSkin();

    //截图
	const QString & ScreenShotKey() { return m_screenHotKey; }
	void SetScreenShotKey(const QString &value) { m_screenHotKey= value; }
    bool IsHideAtScreenShot() { return m_isHideAtScreenShot; }
    void SetHideAtScreenShot(bool value);
	static void InitDefaultAppSkinColor(const QString &themeColor,const QString &hoverColor, const QString &selectColor);

private:
	const QString& GetCurrentSkinPath();
private:
	QString m_localPath;
    bool m_isNewestVersion;
	QString m_sendHotKey;
	QString m_screenHotKey;
    bool m_isHideAtScreenShot;//截屏时是否隐藏窗体
	SKIN_TYPE m_currentSkinType;
	static QString m_skinList[8];
	static QString m_skinSelectColor[8];
	static QString m_skinHoverColor[8];
    static QString m_skinThemeColor[8];
};

#endif
