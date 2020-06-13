#include "TNHttpQuitGroupChat.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery> 
#include <QDebug>

TNHttpQuitGroupChat::TNHttpQuitGroupChat()
{

}

TNHttpQuitGroupChat::~TNHttpQuitGroupChat()
{

}

void TNHttpQuitGroupChat::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
{
    if (statusCode == 200)
    {
        QJsonParseError jsonError;
        QJsonObject jsonObject = QJsonDocument::fromJson(data, &jsonError).object();
        if (jsonError.error == QJsonParseError::NoError)
        {
            this->checkCallback(true, m_replyToGroupChat[reply], jsonObject);
            return;
        }
    }
    QJsonObject jsonObject;
    this->checkCallback(false, m_replyToGroupChat[reply], jsonObject);
}

void TNHttpQuitGroupChat::GetJson(std::function<void(bool, QString, QJsonObject)> callback, const TNPluginParamPtr& pluginParam)
{
    this->checkCallback = callback;
    QJsonObject jsonObject;
    jsonObject.insert("feedId", _feedId);
    jsonObject.insert("groupChatId", _groupId.mid(3));
    jsonObject.insert("title", _feedTitle);
    jsonObject.insert("tUserId", _userId);
    QJsonDocument document;
    document.setObject(jsonObject);
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);

    QString baseUrl = pluginParam->str_api_new_groupchat_systoon_com + URL_QUIT_GROUPCHAT;
    QUrl url(baseUrl);
    qInfo() << "[NetWorkAPI][TNHttpQuitGroupChat]-url=" << url;
    QNetworkRequest _httpRequest;
    _httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
    _httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
    _httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
    _httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
    QNetworkReply* reply = post(_httpRequest, url, dataArray);
    m_replyToGroupChat[reply] = _groupId;
}

void TNHttpQuitGroupChat::SetQuitGroupInfo(const QString& feedId, const QString& feedTitle, const QString& groupId, const QString& userId)
{
    this->_feedId = feedId;
    this->_feedTitle = feedTitle;
    this->_groupId = groupId;
    this->_userId = userId;
}
