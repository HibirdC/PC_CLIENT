#include "TNHomePageConfigParser.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QNetworkReply>
#include <QNetworkConfigurationManager>

#include "NetWorkAPI.h"
#include "TNVersionInfo.h"

TNHomePageConfigParser::TNHomePageConfigParser(const TNPluginParamPtr &pluginParam, QObject *parent) : QObject(parent), m_pluginParam(pluginParam), m_reply(0)
{
    m_networkAccessManager = new QNetworkAccessManager(this);
    QNetworkConfigurationManager manager;
    m_networkAccessManager->setConfiguration(manager.defaultConfiguration());
    m_networkAccessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);
    connect(m_networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slotServiceRequestFinished(QNetworkReply*)));
}

TNHomePageConfigParser::~TNHomePageConfigParser()
{
}

void TNHomePageConfigParser::requestHomePageConfigInfos(const QMap<QString, QString> &comIdToFeedIdMap)
{
    m_comIdToFeedIdMap = comIdToFeedIdMap;

    QJsonObject jsonObject;
    jsonObject.insert("toonType", APPTYPE);
    QJsonArray jsonArray;
    foreach (const QString &comId, m_comIdToFeedIdMap.keys())
    {
        jsonArray.append(comId);
    }
    jsonObject.insert("orgIds", jsonArray);
    QJsonDocument document;
    document.setObject(jsonObject);
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);

    QNetworkRequest request;
    request.setRawHeader(QByteArray("X-Toon-User-ID"), m_pluginParam->strTnUserID.toStdString().c_str());
    request.setRawHeader(QByteArray("X-Toon-User-Token"), m_pluginParam->strTnUserToken.toStdString().c_str());
    request.setRawHeader(QByteArray("X-Toon-User-Agent"), m_pluginParam->strTnUserAgent.toStdString().c_str());
    request.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
    request.setUrl(QUrl(URL_HOMEPAGE));
    m_reply = m_networkAccessManager->post(request, dataArray);
    connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(slotOnError(QNetworkReply::NetworkError)));
}

QList<HomePageInfo> TNHomePageConfigParser::getHomePageInfos() const
{
    return m_homePageInfos.values();
}

void TNHomePageConfigParser::slotServiceRequestFinished(QNetworkReply *reply)
{
    qInfo()<<"slotServiceRequestFinished-debugTex99999999t=";
    if (reply == m_reply)
    {
        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qInfo()<<"slotServiceRequestFinished-statusCode="<<statusCode;
        if ((statusCode == 200)  && (reply->error() == QNetworkReply::NoError))
        {
            QJsonParseError jsonError;
            QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll(), &jsonError).object();
            if (jsonError.error == QJsonParseError::NoError)
            {
                QString debugText = QJsonDocument(jsonObject).toJson();
                qInfo()<<"slotServiceRequestFinished-debugText="<<debugText;
                int retCode = jsonObject.value("code").toInt();
                if (retCode == 0)
                {
                    m_homePageInfos.clear();
                    QJsonArray jsonArray = jsonObject.value("data").toArray();
                    for (int i=0; i<jsonArray.size(); ++i)
                    {
                        QJsonObject aHomePageJson = jsonArray.at(i).toObject();
                        int homePageType  = aHomePageJson.value("type").toInt();
                        int order = i; // 按照服务器返回来的顺序排序
                        HomePageInfo aHomePage;
                        if (homePageType == 1)
                        {
                            aHomePage.id    = aHomePageJson.value("id").toInt();
                            aHomePage.iconUrl = aHomePageJson.value("iconUrl").toString().trimmed();
                            aHomePage.title = aHomePageJson.value("name").toString();
                            aHomePage.url   = aHomePageJson.value("url").toString().trimmed();
                            aHomePage.comId = QString::null;
                            aHomePage.showOrgApp = false;
                            aHomePage.showStaffApp = false;
                            m_homePageInfos[order] = aHomePage;
                        }
                        else if (homePageType == 2)
                        {
                            aHomePage.id    = aHomePageJson.value("id").toInt();
                            aHomePage.iconUrl = aHomePageJson.value("iconUrl").toString().trimmed();
                            aHomePage.title = aHomePageJson.value("name").toString();
                            aHomePage.url   = aHomePageJson.value("url").toString().trimmed();
                            aHomePage.comId = QString::number(aHomePageJson.value("orgId").toInt());
                            aHomePage.showOrgApp = (aHomePageJson.value("showOrgApp").toInt() == 1);
                            aHomePage.showStaffApp = (aHomePageJson.value("showStaffApp").toInt() == 1);
                            if (m_comIdToFeedIdMap.contains(aHomePage.comId))
                            {
                                aHomePage.staffFeedId = m_comIdToFeedIdMap.value(aHomePage.comId);
                                //aHomePage.url += m_comIdToFeedIdMap.value(aHomePage.comId);
                                m_homePageInfos[order] = aHomePage;
                            }
                        }
                        else
                        {
                            qInfo()<<"error! invalid home page configure information. homePageType="<<homePageType;
                            Q_ASSERT(!"error!");
                        }
                    }
                }
            }
        }
        else
        {
            qInfo()<<"[HomePage][TNHomePageConfigParser]slotServiceRequestFinished error="<<reply->errorString();
        }
    }

    emit parserFinished();
    reply->deleteLater();
}

void TNHomePageConfigParser::slotOnError(QNetworkReply::NetworkError code)
{
    emit parserFinished();
}
