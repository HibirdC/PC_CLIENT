#ifndef TNHttpAddGroupChatMember_H
#define TNHttpAddGroupChatMember_H

#include <functional>
#include <QList>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"
#include "TNHttpCreateGroupChat.h"

class NETWORKAPI_EXPORT TNHttpAddGroupChatMember : public TNHttpBaseApi
{
public:
    TNHttpAddGroupChatMember();
    ~TNHttpAddGroupChatMember();

    // 设置邀请者的信息
    void setAddGroupChatInfo(const QString& myFeedId, const QString& myFeedTitle, const QString& groupChatId, INVIT_SOURCE inviteType);

    //添加一个成员，多个成员需要调用多次
    void addGroupMember(const QString& userId, const QString& memberFeedId, const QString& memberFeedTitle, const QString& memberAvatartId);

    // 增加群聊成员
    void requestAddGroupChatMember(std::function<void(bool, QJsonObject, QStringList)> callback, const TNPluginParamPtr& pluginParam, const QStringList& memberNames);

protected:
    void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);

private:
    std::function<void(bool, QJsonObject, QStringList)> checkCallback;

    QString								   m_myFeedId;
    QString								   m_myFeedTitle;
    QString								   m_groupChatId;
    INVIT_SOURCE						   m_inviteType;

    QList<TNFeedInfo>					   m_memberFeeds;

    QMap<QNetworkReply*, QStringList> m_replyToMemberNames;
};

typedef std::shared_ptr<TNHttpAddGroupChatMember>  TNHttpAddGroupChatMemberPtr;

#endif // TNHttpAddGroupChatMember_H
