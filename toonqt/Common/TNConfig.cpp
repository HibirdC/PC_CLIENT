#include <QSettings>
#include "TNConfig.h"
#include "TNPathUtil.h"
#include <QApplication>
#include <QDebug>

TNConfig::TNConfig() :m_settings(NULL), m_globalSettings(NULL), m_userSettings(nullptr), m_langueType(TYPE_LANGUE_NONE)
, m_transEN(NULL), m_transZH(NULL), m_transTC(NULL)
{
    QString globaConfig = TNPathUtil::getGlocalConfigFile();
    // 如果是升级程序调用，需要修改路径才能找到 "global.ini" 文件
    if (globaConfig.contains("upgrade"))
        globaConfig = globaConfig.replace("upgrade", "toon");
    qInfo()<<"[Common][TNConfig]==========================getGlocalConfigFile="<<globaConfig;
    m_globalSettings = new QSettings(globaConfig, QSettings::IniFormat);
	if (GetEnvType() == TYPE_NONE)
	{
		m_bFirstStartUp = true;
		SetEnvType(TYPE_ONLINE);
	}
	else
		m_bFirstStartUp = false;
	if (GetCurrentLangueSet() == TYPE_LANGUE_NONE)
		SetCurrentLangueSet(TYPE_LANGUE_ZH);

}


TNConfig::~TNConfig()
{
	if (m_settings)
	{
		delete m_settings;
		m_settings = nullptr;
	}
	if (m_globalSettings)
	{
		delete m_globalSettings;
		m_globalSettings = nullptr;
	}
	if (m_userSettings)
	{
		delete m_userSettings;
		m_userSettings = nullptr;
	}
	if (m_transEN)
		delete m_transEN;
	m_transEN = nullptr;
	if (m_transZH)
		delete m_transZH;
	m_transZH = nullptr;
	if (m_transTC)
		delete m_transTC;
	m_transTC = nullptr;
}
void TNConfig::resetSettings()
{
	if (m_settings)
	{
		delete m_settings;
		m_settings = nullptr;
	}
	if (m_userSettings)
	{
		delete m_userSettings;
		m_userSettings = nullptr;
	}
}
TNConfig * TNConfig::instance()
{
	static TNConfig config;
	return &config;
}

bool TNConfig::isRemindLatar()
{
	if (m_settings == NULL)
		m_settings = new QSettings(TNPathUtil::getConfigFile(), QSettings::IniFormat);
    return m_settings->value("upgrade/remindlater").toBool();
}

void TNConfig::setRemindLater( bool value)
{
	if (m_settings == NULL)
		m_settings = new QSettings(TNPathUtil::getConfigFile(), QSettings::IniFormat);
    m_settings->setValue("upgrade/remindlater", value);
}

ENV_TYPE TNConfig::GetEnvType()
{
	return (ENV_TYPE)m_globalSettings->value("toon/env", QVariant(-1)).toInt();
}

void TNConfig::SetEnvType(ENV_TYPE eType)
{
	m_globalSettings->setValue("toon/env", (int)eType);
}
void TNConfig::setEncodeDB(bool status, int dbType)
{
	switch (dbType)
	{
	case DBTYPE_USER:
		if (m_userSettings == nullptr)
			m_userSettings = new QSettings(TNPathUtil::getUserConfigFile(), QSettings::IniFormat);
		m_userSettings->setValue("DataBase/uhotdog", status);
		break;
	case DBTYPE_COMMON:
		if (m_settings == NULL)
			m_settings = new QSettings(TNPathUtil::getConfigFile(), QSettings::IniFormat);
		m_settings->setValue("DataBase/chotdog", status);
		break;
	case DBTYPE_MSG:
		if (m_userSettings == nullptr)
			m_userSettings = new QSettings(TNPathUtil::getUserConfigFile(), QSettings::IniFormat);
		m_userSettings->setValue("DataBase/mhotdog", status);
		break;
	default:
		break;
	}
}
bool TNConfig::getEncodeDB(int dbType)
{
	bool status = true;
	switch (dbType)
	{
	case DBTYPE_USER:
		if (m_userSettings == nullptr)
			m_userSettings = new QSettings(TNPathUtil::getUserConfigFile(), QSettings::IniFormat);
		status = m_userSettings->value("DataBase/uhotdog").toBool();
		break;
	case DBTYPE_COMMON:
		if (m_settings == NULL)
			m_settings = new QSettings(TNPathUtil::getConfigFile(), QSettings::IniFormat);
		status = m_settings->value("DataBase/chotdog").toBool();
		break;
	case DBTYPE_MSG:
		if (m_userSettings == nullptr)
			m_userSettings = new QSettings(TNPathUtil::getUserConfigFile(), QSettings::IniFormat);
		status = m_userSettings->value("DataBase/mhotdog").toBool();
		break;
	default:
		break;
	}
	return status;
}

void TNConfig::ApplyCurrentLangueSet()
{
	if (m_langueType == TYPE_LANGUE_EN)
	{
		if (m_transEN == NULL)
		{
			m_transEN = new QTranslator;
			m_transEN->load(QString(":/shadow/Resources/toon_en.qm"));
		}
		if (m_transZH)
			qApp->removeTranslator(m_transZH);
		if (m_transTC)
			qApp->removeTranslator(m_transTC);
		qApp->installTranslator(m_transEN);
	}
	else if (m_langueType == TYPE_LANGUE_ZH)
	{
		if (m_transZH == NULL)
		{
			m_transZH = new QTranslator;
			m_transZH->load(QString(":/shadow/Resources/toon_zh.qm"));
		}
		if (m_transEN)
			qApp->removeTranslator(m_transEN);
		if (m_transTC)
			qApp->removeTranslator(m_transTC);
		qApp->installTranslator(m_transZH);
	}
	else if (m_langueType == TYPE_LANGUE_TC)
	{
		if (m_transTC == NULL)
		{
			m_transTC = new QTranslator;
			m_transTC->load(QString(":/shadow/Resources/toon_tc.qm"));
		}
		if (m_transEN)
			qApp->removeTranslator(m_transEN);
		if (m_transZH)
			qApp->removeTranslator(m_transZH);
		qApp->installTranslator(m_transTC);
	}
}

void TNConfig::SetCurrentLangueSet(LANGUE_TYPE type)
{
	m_langueType = type;
	m_globalSettings->setValue("toon/langue", (int)type);
	m_globalSettings->sync();
}

LANGUE_TYPE TNConfig::GetCurrentLangueSet()
{
	if (m_langueType == TYPE_LANGUE_NONE)
		m_langueType = (LANGUE_TYPE)m_globalSettings->value("toon/langue", QVariant(-1)).toInt();
	return m_langueType;
}

int TNConfig::GetCastStatus()
{
	if (m_userSettings == nullptr)
		m_userSettings = new QSettings(TNPathUtil::getUserConfigFile(), QSettings::IniFormat);
	return m_userSettings->value("CastDBTable/message_casted").toInt();
}

void TNConfig::SetCastStatus(int nStatus)
{
	if (m_userSettings == nullptr)
		m_userSettings = new QSettings(TNPathUtil::getUserConfigFile(), QSettings::IniFormat);
	m_userSettings->setValue("CastDBTable/message_casted", nStatus);
}
void TNConfig::setFixedErrStatus(int nStatus)
{
	m_globalSettings->setValue("selfCheck/level",nStatus);
	m_globalSettings->setValue("selfCheck/failTimes", 0);
	m_globalSettings->sync();
}
int  TNConfig::getFixedErrStatus()
{
	return m_globalSettings->value("selfCheck/level", QVariant(0)).toInt();
}
void TNConfig::setFixedFailed(int flag)
{
	m_globalSettings->setValue("selfCheck/failTimes", flag);
	m_globalSettings->sync();
}
int TNConfig::getFixedFailed()
{
	return m_globalSettings->value("selfCheck/failTimes", QVariant(0)).toInt();
}

bool TNConfig::hasHomePage()
{
    if (m_userSettings == nullptr)
        m_userSettings = new QSettings(TNPathUtil::getUserConfigFile(), QSettings::IniFormat);
    return m_userSettings->value("HomePage/onceHas", QVariant(false)).toBool();
}

void TNConfig::setHomePageStatus(bool yes)
{
    if (m_userSettings == nullptr)
        m_userSettings = new QSettings(TNPathUtil::getUserConfigFile(), QSettings::IniFormat);
    m_userSettings->setValue("HomePage/onceHas", yes);
}
