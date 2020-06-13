#include "TNHttpObtainGroupMembersByGroupId.h"
#include "qdebug.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery> 

TNHttpObtainGroupMembersByGroupId::TNHttpObtainGroupMembersByGroupId()
{
}

TNHttpObtainGroupMembersByGroupId::~TNHttpObtainGroupMembersByGroupId()
{
}

void TNHttpObtainGroupMembersByGroupId::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
{
    if (statusCode == 200)
    {
        QJsonParseError jsonError;
        QJsonObject jsonObject = QJsonDocument::fromJson(data, &jsonError).object();
        if (jsonError.error == QJsonParseError::NoError)
        {
            this->checkCallback(true, m_replyToFeedId.take(reply), jsonObject);
            return;
        }
    }
    QJsonObject jsonObject;
    this->checkCallback(false, m_replyToFeedId.take(reply), jsonObject);
}

void TNHttpObtainGroupMembersByGroupId::GetJson(std::function<void(bool, QString, QJsonObject)> callback,
                                                const TNPluginParamPtr &pluginParam, const QString &groupId, const QString & version)
{
    this->checkCallback = callback;

    QString baseUrl = pluginParam->str_new_group_systoon_com + URL_OBTAIN_GROUPMEMBERS_BYGROUPID;
    QUrl url(baseUrl);
    QUrlQuery query;
    query.addQueryItem("feedId", groupId);
    query.addQueryItem("version", version);
    url.setQuery(query);

    qInfo() <<"[NetWorkAPI][TNHttpObtainGroupMembersByGroupId]-url=" << url;
	QNetworkRequest _httpRequest;
    _httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
    _httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
    _httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
    _httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
    QNetworkReply *reply = get(_httpRequest, url);
    m_replyToFeedId[reply] = groupId;
}
