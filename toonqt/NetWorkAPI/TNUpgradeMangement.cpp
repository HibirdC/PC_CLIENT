#include <QJsonObject>
#include <QEventLoop>
#include <QTimer>

#include <QJsonObject>
#include <QJsonDocument>
#include "TNVersionInfo.h"
#include "TNUpgradeMangement.h"
#include "TNHttpUpdateVersion.h"

TNUpgradeMangement * TNUpgradeMangement::instance()
{
    static TNUpgradeMangement instance;
    return &instance;
}

TNUpgradeMangement::TNUpgradeMangement()
{
    m_currentVersion = TNVersionInfo::buildNo();
    m_isNeedUpgrade = false;
    m_isForceUpgrade = false;
}

void TNUpgradeMangement::checkNewVersion(TNPluginParamPtr _pluginParam, int nCheckType)
{
    qInfo()<<"[NetWorkAPI][TNUpgradeMangement]********************checkNewVersion-begin********************";
    qInfo()<<"[NetWorkAPI][TNUpgradeMangement]TNUpgradeMangement::checkNewVersion begin";
    qInfo()<<"[NetWorkAPI][TNUpgradeMangement]TNUpgradeMangement::m_currentVersion="<<m_currentVersion;
    m_newestVersion = "";
    m_downLoadURL = "";
    m_isNeedUpgrade = false;
    m_isForceUpgrade = false; //是否强制升级
    m_verDesc = "";
    TNHttpUpdateVersionPtr _httpUpdateVersionPtr = std::make_shared<TNHttpUpdateVersion>();
    _httpUpdateVersionPtr->CheckNewVersion([&](bool success, QJsonObject jsonObject)
    {        
        QString debugText = QString(QJsonDocument(jsonObject).toJson());
        qInfo()<<"outCheckNewVersion-debugText="<<debugText;
        if (success)
        {
            m_newestVersion = jsonObject.value("data").toObject().value("version").toString();
            m_downLoadURL = jsonObject.value("data").toObject().value("parameter").toString();
            m_isForceUpgrade = (jsonObject.value("data").toObject().value("force").toString() == QString("1"));
            m_verDesc = jsonObject.value("data").toObject().value("versionDes").toString();
            m_isNeedUpgrade = (m_newestVersion > m_currentVersion);
        }
        emit checkVersionFinished(
            m_isNeedUpgrade,
            m_isForceUpgrade,
            m_downLoadURL,
            nCheckType,
            m_verDesc
            );
        qInfo()<<"********************checkNewVersion-end********************";
    }, _pluginParam, m_currentVersion);

    qInfo()<<"[NetWorkAPI][TNUpgradeMangement]checkNewVersion-eventLoop";
    QEventLoop eventLoop;
    connect(this, &TNUpgradeMangement::checkVersionFinished, &eventLoop, &QEventLoop::quit);
	QTimer::singleShot(5000, &eventLoop, SLOT(quit()));
    eventLoop.exec();
    qInfo()<<"[NetWorkAPI][TNUpgradeMangement]checkNewVersion end";
}
