#ifndef TNCONFIG_H
#define TNCONFIG_H
#include "common_global.h"
#include <QSettings>
#include <QTranslator>
enum ENV_TYPE
{
	TYPE_NONE = -1,
	TYPE_DEV = 0,
	TYPE_TEST,
    TYPE_ONLINE,
    TYPE_UCLOUD
};
enum LANGUE_TYPE
{
	TYPE_LANGUE_NONE = -1,
	TYPE_LANGUE_ZH = 0,		//中文，默认
	TYPE_LANGUE_TC,			//繁体
	TYPE_LANGUE_EN			//英文
};
class COMMON_EXPORT TNConfig
{
public:
    static TNConfig * instance();
    ~TNConfig();

private:
    TNConfig();

public:
    //稍后提醒
    bool isRemindLatar();
    void setRemindLater(bool isRemindLater);
	ENV_TYPE GetEnvType();
	void SetEnvType(ENV_TYPE eType);
	bool isFirstStartUp(){ return m_bFirstStartUp; }

	void setEncodeDB(bool status,int dbType);
	bool getEncodeDB(int dbType);
	void resetSettings();
	void ApplyCurrentLangueSet();
	void SetCurrentLangueSet(LANGUE_TYPE type);
	LANGUE_TYPE GetCurrentLangueSet();

	int GetCastStatus();
	void SetCastStatus(int nStatus);
	void setFixedErrStatus(int nStatus);
	int  getFixedErrStatus();

	void setFixedFailed(int flag);
	int getFixedFailed();

    bool hasHomePage();
    void setHomePageStatus(bool yes);

private:
	bool m_bFirstStartUp;
    QSettings* m_settings;
	QSettings* m_globalSettings;
	QSettings* m_userSettings;
	QTranslator* m_transZH;
	QTranslator* m_transEN;
	QTranslator* m_transTC;
	LANGUE_TYPE m_langueType;
};
#endif // !TNCONFIG


