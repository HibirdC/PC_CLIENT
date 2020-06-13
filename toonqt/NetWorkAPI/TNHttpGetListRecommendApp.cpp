#include "TNHttpGetListRecommendApp.h"

#include "qdebug.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery> 
#include <QEventLoop>


TNHttpGetListRecommendApp::TNHttpGetListRecommendApp()
{

}

TNHttpGetListRecommendApp::~TNHttpGetListRecommendApp()
{

}

void TNHttpGetListRecommendApp::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
{
    if (statusCode == 200)
    {
        QJsonParseError jsonError;
        QJsonObject jsonObject = QJsonDocument::fromJson(data, &jsonError).object();
        if (jsonError.error == QJsonParseError::NoError)
        {
            this->checkCallback(true, jsonObject);
            return;
        }
    }
    QJsonObject jsonObject;
    this->checkCallback(false, jsonObject);
}

void TNHttpGetListRecommendApp::GetJson(std::function<void(bool, QJsonObject)> callback, const TNPluginParamPtr &pluginParam, const QString &feedId)
{
    this->checkCallback = callback;
    // 基本 URL
    QString baseUrl = pluginParam->str_mix_systoon_com + URL_LIST_RECOMMEND_APP;
    QUrl url(baseUrl);
    QUrlQuery query;
    query.addQueryItem("feedId", feedId);
    url.setQuery(query);
	QNetworkRequest _httpRequest;
    qInfo() <<"[NetWorkAPI][TNHttpGetListRecommendApp]-Url=" << url;
    _httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
    _httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
    _httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
    _httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
    get(_httpRequest, url);
}
