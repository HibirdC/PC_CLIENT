#include "TNHttpResetPassword.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery> 
#include <QDebug>

TNHttpResetPassword::TNHttpResetPassword()
{

}

TNHttpResetPassword::~TNHttpResetPassword()
{

}

void TNHttpResetPassword::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
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

void TNHttpResetPassword::GetJson(std::function<void(bool, QJsonObject)> callback,
                                  const TNPluginParamPtr& pluginParam,
                                  const QString &password)
{
    this->checkCallback = callback;

    QJsonObject jsonObject;
    jsonObject.insert("loginProtectStatus", 1);
    jsonObject.insert("password", password);

    QJsonDocument document;
    document.setObject(jsonObject);
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);

    QString baseUrl = pluginParam->str_new_user_systoon_com + URL_RESETPASSWORD;
    QUrl url(baseUrl);
    qInfo() << "[NetWorkAPI][TNHttpResetPassword]-url=" << url;
    QNetworkRequest _httpRequest;
    _httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
    _httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
    _httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
    _httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
    QNetworkReply* reply = post(_httpRequest, url, dataArray);
    Q_UNUSED(reply);
}
