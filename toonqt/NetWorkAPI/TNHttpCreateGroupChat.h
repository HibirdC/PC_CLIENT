#ifndef TNHTTPCreateGroupChat_H
#define TNHTTPCreateGroupChat_H

#include <functional>
#include <QList>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"

typedef struct st_feedInfo
{
    QString feedAvatartId;
    QString feedId;
    QString feedTitle;
    QString userId;
}TNFeedInfo;

enum INVIT_SOURCE
{
    SOURCE_TYPE_INVIT = 0,			//被邀请加入
    SOURCE_TYPE_BARCODE,			//扫二维码加入
    SOUCE_TYPE_ACTICE				//主动加入
};

class NETWORKAPI_EXPORT TNHttpCreateGroupChat : public TNHttpBaseApi
{
public:
    TNHttpCreateGroupChat();
    ~TNHttpCreateGroupChat();

    // 新创建群聊
    void requestCreateGroupChat(std::function<void(bool, QString, QJsonObject)> callback, const TNPluginParamPtr& pluginParam, const QString &belongFeedId);
    void SetCreateFeed(const QString &feedAvatartId, const QString &feedId, const QString &feedTitle);

    //添加一个成员，多个成员需要调用多次
    void AddGroupMember(const QString &memberAvatartId, const QString &memberFeedId, const QString &memberFeedTitle, const QString &userId);

protected:
    void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);

    //清空之前添加的所有成员，限当次请求
    void ClearAddMembers();

private:
    std::function<void(bool, QString, QJsonObject)> checkCallback;
    QMap<QNetworkReply*, QString>          _replyToBelongFeedId;
    TNFeedInfo							   _createFeedInfo;
    QList<TNFeedInfo>					   _memberFeeds;
};

typedef std::shared_ptr<TNHttpCreateGroupChat>  TNHttpCreateGroupChatPtr;

#endif // TNHTTPCreateGroupChat_H
