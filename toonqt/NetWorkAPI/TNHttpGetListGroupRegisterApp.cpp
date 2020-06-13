#include "TNHttpGetListGroupRegisterApp.h"

#include "qdebug.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery> 
#include <QEventLoop>

TNHttpGetListGroupRegisterApp::TNHttpGetListGroupRegisterApp()
{

}

TNHttpGetListGroupRegisterApp::~TNHttpGetListGroupRegisterApp()
{

}


void TNHttpGetListGroupRegisterApp::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
{
    if (statusCode == 200)
    {
        QJsonParseError jsonError;
        QJsonObject jsonObject = QJsonDocument::fromJson(data, &jsonError).object();
        if (jsonError.error == QJsonParseError::NoError)
        {
            this->getAppCallback(true, m_replyToFeedId.take(reply), jsonObject);
            return;
        }
    }
    QJsonObject jsonObject;
    this->getAppCallback(false, m_replyToFeedId.take(reply), jsonObject);
}

void TNHttpGetListGroupRegisterApp::GetJson(std::function<void(bool, QString, QJsonObject)> getAppCallback,
                                            const TNPluginParamPtr &pluginParam, const QString &feedId)
{
    this->getAppCallback = getAppCallback;

    // 基本 URL
    QString baseUrl = pluginParam->str_api_app_systoon_com + URL_LIST_GROUPREGISTERAPP;
    QUrlQuery query;
    query.addQueryItem("feedId", feedId);

    QUrl url(baseUrl);
    url.setQuery(query);
    qInfo() << "[NetWorkAPI][TNHttpGetListGroupRegisterApp]-url" << url;
	QNetworkRequest _httpRequest;
    _httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
    _httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
    _httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
    _httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
	QNetworkReply *reply = get(_httpRequest, url);
    m_replyToFeedId[reply] = feedId;
}
