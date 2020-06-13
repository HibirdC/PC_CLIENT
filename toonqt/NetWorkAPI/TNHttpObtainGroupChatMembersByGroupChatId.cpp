#include "TNHttpObtainGroupChatMembersByGroupChatId.h"

#include "qdebug.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery> 
#include <QEventLoop>


TNHttpObtainGroupChatMembersByGroupChatId::TNHttpObtainGroupChatMembersByGroupChatId()
{

}

TNHttpObtainGroupChatMembersByGroupChatId::~TNHttpObtainGroupChatMembersByGroupChatId()
{

}

void TNHttpObtainGroupChatMembersByGroupChatId::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
{
    if (statusCode == 200)
    {
        QJsonParseError jsonError;
        QJsonObject jsonObject = QJsonDocument::fromJson(data, &jsonError).object();
        if (jsonError.error == QJsonParseError::NoError)
        {
            this->checkCallback(true, m_replyToGroupChatId.take(reply), jsonObject);
            return;
        }
    }
    QJsonObject jsonObject;
    this->checkCallback(false, m_replyToGroupChatId.take(reply), jsonObject);
}

void TNHttpObtainGroupChatMembersByGroupChatId::GetJson(std::function<void(bool, QString, QJsonObject)> callback,
                                                        const TNPluginParamPtr &pluginParam,
                                                        const QString &groupChatId, const QString &version)
{
    this->checkCallback = callback;

    QString baseUrl = pluginParam->str_api_new_groupchat_systoon_com + URL_OBTAIN_GROUPCHATMEMBERS_BYGROUPCHATID;
    QUrl url(baseUrl);
    QUrlQuery query;
    query.addQueryItem("groupChatId", groupChatId);
    query.addQueryItem("version", version);
    url.setQuery(query);
    qInfo() <<"[NetWorkAPI][TNHttpObtainGroupChatMembersByGroupChatId]-url=" << url;
    QNetworkRequest _httpRequest;
    _httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
    _httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
    _httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
    _httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
    QNetworkReply *reply = get(_httpRequest, url);
    m_replyToGroupChatId[reply] = groupChatId;
}
