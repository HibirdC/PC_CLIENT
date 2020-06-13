#include "TNAppJsonObjectParser.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QDebug>

TNAppJsonObjectParser::TNAppJsonObjectParser(QObject *parent) : QObject(parent), m_pubStatus(0), m_registerType(1), m_linkType(0), m_sublinkType(0)
{

}

TNAppJsonObjectParser::TNAppJsonObjectParser(const QString &feedId, const QJsonObject &json, QObject *parent) : QObject(parent),
m_feedId(feedId), m_jsonObject(json), m_pubStatus(0), m_registerType(1), m_linkType(0), m_sublinkType(0)
{
	if (m_jsonObject.isEmpty())
		qWarning() << "TNAppJsonObjectParser-m_jsonObject is null";

	parser();
}

TNAppJsonObjectParser::~TNAppJsonObjectParser()
{

}

void TNAppJsonObjectParser::setJsonObject(const QString &feedId, const QJsonObject &json)
{
    m_feedId = feedId;
	m_jsonObject = json;
	if (m_jsonObject.isEmpty())
		qWarning() << "TNAppJsonObjectParser-m_jsonObject is null";

	parser();
}

QString TNAppJsonObjectParser::getAppId() const
{
	return m_appId;
}

QString TNAppJsonObjectParser::getAppRegisterId() const
{
    return m_appRegisterId;
}

QString TNAppJsonObjectParser::getFeedId() const
{
	return m_feedId;
}

int TNAppJsonObjectParser::getPubStatus() const
{
	return m_pubStatus;
}

int TNAppJsonObjectParser::getRegisterType() const
{
	return m_registerType;
}

int TNAppJsonObjectParser::getLinkType() const
{
	return m_linkType;
}

int TNAppJsonObjectParser::getSubLinkType() const
{
	return m_sublinkType;
}

QString TNAppJsonObjectParser::getFrame() const
{
	QString frame;
	if (isMyself())
	{
		frame = ("sf");
	}
	else if (isFriend())
	{
		frame = ("ff");
	}
	else
	{
		frame = ("af");
	}

	return frame;
}

QString TNAppJsonObjectParser::getAppName() const
{
	QString appName;
	if (isMyself())
	{
		appName = m_jsonObject.value("sfTitle").toString();
	}
	else if (isFriend())
	{
		appName = m_jsonObject.value("ffTitle").toString();
	}
	else
	{
		appName = m_jsonObject.value("afTitle").toString();
	}

	return appName;
}

QString TNAppJsonObjectParser::getAppIconUrl() const
{
	QString appIconUrl;
	if (isMyself())
	{
		appIconUrl = m_jsonObject.value("sfIcon").toString();
	}
	else if (isFriend())
	{
		appIconUrl = m_jsonObject.value("ffIcon").toString();
	}
	else
	{
		appIconUrl = m_jsonObject.value("afIcon").toString();
	}

	return appIconUrl;
}

QString TNAppJsonObjectParser::getAppLinkUrl() const
{
	QString appLinkUrl;
	if (isMyself())
	{
		appLinkUrl = m_jsonObject.value("sfUrl").toString();
	}
	else if (isFriend())
	{
		appLinkUrl = m_jsonObject.value("ffUrl").toString();
	}
	else
	{
		appLinkUrl = m_jsonObject.value("afUrl").toString();
	}
	
	if (isGeneralLink())
		reParser(appLinkUrl);

	return appLinkUrl;
}

void TNAppJsonObjectParser::parser()
{
    if (m_jsonObject.contains("appId"))
        m_appId = QString::number(m_jsonObject.value("appId").toInt());

    Q_ASSERT(m_jsonObject.contains("appRegisterId"));
    m_appRegisterId = QString::number(m_jsonObject.value("appRegisterId").toInt());

    //m_feedId = m_jsonObject.value("feedId").toString(); // json串传回来的feedId有可能不对
	Q_ASSERT(!m_feedId.isEmpty());
	m_pubStatus = m_jsonObject.value("pubStatus").toInt();
	m_registerType = m_jsonObject.value("registerType").toInt();
	m_linkType = m_jsonObject.value("linkType").toInt();
    if (m_registerType == 1)
    {
        // 如果 registerType==1， 则一定有 appId
        Q_ASSERT(!m_appId.isEmpty());
        if (m_appId.isEmpty())
            qInfo()<<"error! registerType==1,  but there no appId----------------------";
    }
}

bool TNAppJsonObjectParser::isMyself() const
{
    return true;
}

bool TNAppJsonObjectParser::isFriend() const
{
	// TODO: 目前阶段，没有陌生人
	return true;
}

bool TNAppJsonObjectParser::isGeneralLink() const
{
	return (m_registerType == 2) && (m_linkType == 0);
}

void TNAppJsonObjectParser::reParser(QString &appLinkUrl) const
{
	QJsonParseError jsonError;
	QJsonDocument jsonDoucment = QJsonDocument::fromJson(appLinkUrl.toUtf8(), &jsonError);
	if (jsonError.error == QJsonParseError::NoError)
	{
		if (jsonDoucment.isArray())
		{
			qDebug() << Q_FUNC_INFO << "error! json format error! json should object.";
		}
		if (jsonDoucment.isObject())
		{
			const QJsonObject jsonObject(jsonDoucment.object());
			QString debugText = QJsonDocument(jsonObject).toJson();
            m_sublinkType = jsonObject.value("linkType").toString().toInt();
			appLinkUrl = jsonObject.value("content").toString();
		}
    }
}

bool TNAppJsonObjectParser::showInHomePage() const
{
    if (m_registerType == 2)
    {
        if ((m_linkType == 0) && (m_sublinkType == 1)) // 名片
            return false;

        if  (m_linkType == 1) // 群聊
            return false;
    }

    return true;
}
