#include "TNHttpCreateGroupChat.h"

#include "qdebug.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery> 


TNHttpCreateGroupChat::TNHttpCreateGroupChat()
{

}

TNHttpCreateGroupChat::~TNHttpCreateGroupChat()
{

}

void TNHttpCreateGroupChat::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
{
    if (statusCode == 200)
    {
        QJsonParseError jsonError;
        QJsonObject jsonObject = QJsonDocument::fromJson(data, &jsonError).object();
        if (jsonError.error == QJsonParseError::NoError)
        {
            this->checkCallback(true, _replyToBelongFeedId[reply], jsonObject);
            return;
        }
    }
    QJsonObject jsonObject;
    this->checkCallback(false, _replyToBelongFeedId[reply], jsonObject);
}

void TNHttpCreateGroupChat::requestCreateGroupChat(std::function<void(bool, QString, QJsonObject)> callback, const TNPluginParamPtr& pluginParam,
                                                   const QString &belongFeedId)
{
    this->checkCallback = callback;
    QJsonObject jsonObject;
    jsonObject.insert("creatorAvatarId", _createFeedInfo.feedAvatartId);
    jsonObject.insert("creatorFeedId", _createFeedInfo.feedId);
    jsonObject.insert("creatorTitle", _createFeedInfo.feedTitle);

    QJsonArray members;
    QList<TNFeedInfo>::iterator memberItrator = _memberFeeds.begin();
    while (memberItrator != _memberFeeds.end())
    {
        TNFeedInfo memberInfo = *memberItrator;
        QJsonObject member;
        member.insert("avatarId", memberInfo.feedAvatartId);
        member.insert("feedId", memberInfo.feedId);
        member.insert("title", memberInfo.feedTitle);
        member.insert("userId", memberInfo.userId);
        members.append(member);
        memberItrator++;
    }
    jsonObject.insert("memberList", members);
    QJsonDocument document;
    document.setObject(jsonObject);
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);

    // 基本 URL
    QString baseUrl = pluginParam->str_api_new_groupchat_systoon_com + URL_CREAT_GROUPCHAT;
    QUrl url(baseUrl);
    qInfo() << "[NetWorkAPI][TNHttpCreateGroupChat] url=" << url;
    QNetworkRequest _httpRequest;
    _httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
    _httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
    _httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
    _httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
    QNetworkReply* reply = post(_httpRequest, url, dataArray);
    _replyToBelongFeedId[reply] = belongFeedId;
    ClearAddMembers();
}

void TNHttpCreateGroupChat::SetCreateFeed(const QString &feedAvatartId, const QString &feedId, const QString &feedTitle)
{
    ClearAddMembers();
    this->_createFeedInfo.feedAvatartId = feedAvatartId;
    this->_createFeedInfo.feedId = feedId;
    this->_createFeedInfo.feedTitle = feedTitle;
}

void TNHttpCreateGroupChat::AddGroupMember(const QString &memberAvatartId, const QString &memberFeedId, const QString &memberFeedTitle, const QString &userId)
{
    TNFeedInfo feedInfo;
    feedInfo.feedAvatartId = memberAvatartId;
    feedInfo.feedId = memberFeedId;
    feedInfo.feedTitle = memberFeedTitle;
    feedInfo.userId = userId;
    this->_memberFeeds.append(feedInfo);
}

void TNHttpCreateGroupChat::ClearAddMembers()
{
    this->_memberFeeds.clear();
}

