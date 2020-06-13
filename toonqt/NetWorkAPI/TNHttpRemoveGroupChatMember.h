#ifndef TNHttpRemoveGroupChatMember_H
#define TNHttpRemoveGroupChatMember_H

#include <functional>
#include <QList>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"
#include "TNHttpCreateGroupChat.h"

class NETWORKAPI_EXPORT TNHttpRemoveGroupChatMember : public TNHttpBaseApi
{
public:
    TNHttpRemoveGroupChatMember();
    ~TNHttpRemoveGroupChatMember();

    // 设置操作者的信息
    void setRemoveGroupChatInfo(const QString& myFeedId, const QString& myFeedTitle, const QString& groupChatId);

    //添加一个预被删除的成员信息，多个成员需要调用多次
    void appendRemovedGroupMember(const QString& userId, const QString& memberFeedId, const QString& memberFeedTitle);

    // 删除群聊成员
    void removeGroupChatMember(std::function<void(bool, QJsonObject)> callback, const TNPluginParamPtr& pluginParam);

protected:
    void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);

private:
    std::function<void(bool, QJsonObject)> checkCallback;

    QString								   m_myFeedId;
    QString								   m_myFeedTitle;
    QString								   m_groupChatId;

    QList<TNFeedInfo>					   m_memberFeeds;
};

typedef std::shared_ptr<TNHttpRemoveGroupChatMember>  TNHttpRemoveGroupChatMemberPtr;

#endif // TNHttpRemoveGroupChatMember_H
