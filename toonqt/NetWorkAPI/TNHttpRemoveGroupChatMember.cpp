﻿#include "TNHttpRemoveGroupChatMember.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery> 
#include <QDebug>

TNHttpRemoveGroupChatMember::TNHttpRemoveGroupChatMember()
{

}

TNHttpRemoveGroupChatMember::~TNHttpRemoveGroupChatMember()
{

}

void TNHttpRemoveGroupChatMember::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
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

void TNHttpRemoveGroupChatMember::setRemoveGroupChatInfo(const QString& myFeedId, const QString& myFeedTitle, const QString& groupChatId)
{
    m_memberFeeds.clear();
    this->m_myFeedId = myFeedId;
    this->m_myFeedTitle = myFeedTitle;
    this->m_groupChatId = groupChatId;
}

void TNHttpRemoveGroupChatMember::appendRemovedGroupMember(const QString& userId, const QString& memberFeedId, const QString& memberFeedTitle)
{
    TNFeedInfo feedInfo;
    feedInfo.userId = userId;
    feedInfo.feedId = memberFeedId;
    feedInfo.feedTitle = memberFeedTitle;
    //feedInfo.feedAvatartId = memberAvatartId;

    this->m_memberFeeds.append(feedInfo);
}

void TNHttpRemoveGroupChatMember::removeGroupChatMember(std::function<void(bool, QJsonObject)> callback, const TNPluginParamPtr& pluginParam)
{
    this->checkCallback = callback;

    QJsonObject jsonObject;
    jsonObject.insert("feedId", m_myFeedId);

    Q_ASSERT(m_groupChatId.startsWith("gc_"));
    if (!m_groupChatId.startsWith("gc_"))
    {
        qWarning()<<"[NetWorkAPI][TNHttpRemoveGroupChatMember]error; m_groupChatId="<<m_groupChatId;
        return;
    }

    QString groupId = m_groupChatId.mid(3);
    jsonObject.insert("groupChatId", groupId);

    jsonObject.insert("title", m_myFeedTitle);

    QJsonArray members;
    QList<TNFeedInfo>::iterator memberItrator = m_memberFeeds.begin();
    while (memberItrator != m_memberFeeds.end())
    {
        TNFeedInfo memberInfo = *memberItrator;
        QJsonObject member;
        //member.insert("avatarId", memberInfo.feedAvatartId);
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
    QString baseUrl = pluginParam->str_api_new_groupchat_systoon_com + URL_REMOVE_GROUPCHAT_MEMBERS;
    QUrl url(baseUrl);
    qInfo()<<"[NetWorkAPI][TNHttpRemoveGroupChatMember]url=" << url;
    QNetworkRequest _httpRequest;
    _httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
    _httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
    _httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
    _httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
    post(_httpRequest, url, dataArray);
}
