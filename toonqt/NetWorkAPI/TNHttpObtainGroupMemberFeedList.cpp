#include "TNHttpObtainGroupMemberFeedList.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery> 
#include <QEventLoop>


TNHttpObtainGroupMemberFeedList::TNHttpObtainGroupMemberFeedList()
{

}

TNHttpObtainGroupMemberFeedList::~TNHttpObtainGroupMemberFeedList()
{

}

void TNHttpObtainGroupMemberFeedList::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
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

void TNHttpObtainGroupMemberFeedList::GetJson(std::function<void(bool, QString, QJsonObject)> callback,
                                              const TNPluginParamPtr &pluginParam, const QString &groupId, const QStringList &feedids)
{
    this->checkCallback = callback;

    QJsonArray json;
    for (int i = 0; i < feedids.size(); i++)
    {
        json.insert(i, feedids[i]);
    }

    QJsonObject jsonObject;
    jsonObject.insert("feedId", "");
    jsonObject.insert("feedIds", json);
    QJsonDocument document;
    document.setObject(jsonObject);
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);

    QString baseUrl = pluginParam->str_api_feed_systoon_com + URL_OBTAIN_FEED_LIST;
    QUrl url(baseUrl);
    qInfo() << "[NetWorkAPI][TNHttpObtainGroupMemberFeedList]-url=" << url;
	QNetworkRequest _httpRequest;
    _httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
    _httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
    _httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
    _httpRequest.setRawHeader(QByteArray("Accept"), QByteArray("application/json"));
    _httpRequest.setRawHeader(QByteArray("Accept-Encoding"), QByteArray("deflate"));
    _httpRequest.setRawHeader(QByteArray("Accept-Language"), QByteArray("zh-CN,zh;q=0.8"));
    _httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
    QNetworkReply *reply = post(_httpRequest, url, dataArray);
    m_replyToFeedId[reply] = groupId;
}
