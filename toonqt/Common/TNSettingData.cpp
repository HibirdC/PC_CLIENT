#include "TNSettingData.h"
#include <QFile>
#include <QApplication>

QString TNSettingData::m_skinList[8] = { ":/skin/Resources/img/skin/default/default.qss", ":/pink/Resources/img/skin/pink/default.qss",
":/green/Resources/img/skin/green/default.qss", ":/tea/Resources/img/skin/tea/default.qss", ":/orange/Resources/img/skin/orange/default.qss",":/purple/Resources/img/skin/purple/default.qss",":/bud/Resources/img/skin/bud/default.qss",":/orchid/Resources/img/skin/orchid/default.qss"};
QString TNSettingData::m_skinSelectColor[8] = { "#d4e6ff", "#FFE5F0", "#D9F7D7", "#D1F7EE", "#FFE7DF", "#FFE2FB", "#FFE5E7", "#E4E1FF" };
QString TNSettingData::m_skinHoverColor[8] = { "#e3efff", "#FFECF4", "#E4FAE2", "#E1FBF5", "#FFEEE8", "#FEE8FB", "#FFEAEC", "#ECEAFF" };
QString TNSettingData::m_skinThemeColor[8] = { "#3F94FC", "#E86AA2", "#68BF60", "#2ABB9C", "#FF794D", "#904187", "#FF5967", "#AFA9D0" };
TNSettingData::TNSettingData()
:m_isNewestVersion(true), m_currentSkinType(SKIN_TYPE_DEFAULT), m_isHideAtScreenShot(false)
{
}

TNSettingData * TNSettingData::instance()
{
	static TNSettingData settingData;
	return &settingData;
}

const QString& TNSettingData::GetCurrentSkinPath()
{
	return m_skinList[m_currentSkinType];
}

void TNSettingData::SetToonStyle(QList<QString>& styleList)
{
	QString strQss;
	for (int index = 0; index < styleList.size(); index++)
	{
		QString moduleStyle = styleList[index];
		QFile qss(moduleStyle);
		if (qss.open(QFile::ReadOnly))
		{
			strQss += QString::fromUtf8(qss.readAll());
			qss.close();
		}
	}
	qApp->setStyleSheet(strQss);
}


void TNSettingData::ApplySkinType(const SKIN_TYPE type)
{
	SetSkinType(type);
	QString skinQssPath = GetCurrentSkinPath();
	QList<QString> listStyle;
	listStyle.append(":/qss/Resources/toon.qss");
	listStyle.append(":/qss/Resources/systool.qss");
	listStyle.append(":/qss/Resources/emoji.qss");
	listStyle.append(skinQssPath);
	SetToonStyle(listStyle);
}

const QString& TNSettingData::GetCurrentHoverSkin()
{
	return m_skinHoverColor[m_currentSkinType];
}
const QString& TNSettingData::GetCurrentSelectSkin()
{
	return m_skinSelectColor[m_currentSkinType];
}
const QString& TNSettingData::GetCurrentThemeSkin()
{
    return m_skinThemeColor[m_currentSkinType];
}

void TNSettingData::SetHideAtScreenShot(bool value)
{
    m_isHideAtScreenShot = value;
}

void TNSettingData::InitDefaultAppSkinColor(const QString &themeColor, const QString &hoverColor, const QString &selectColor)
{
	m_skinThemeColor[SKIN_TYPE_DEFAULT] = themeColor;
	m_skinHoverColor[SKIN_TYPE_DEFAULT] = hoverColor;
	m_skinSelectColor[SKIN_TYPE_DEFAULT] = selectColor;
}