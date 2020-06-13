#ifndef TNHTTPFriendRequest_H
#define TNHTTPFriendRequest_H

#include <functional>
#include <QList>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"

class NETWORKAPI_EXPORT TNHttpFriendRequest : public TNHttpBaseApi
{
public:
    TNHttpFriendRequest();
    ~TNHttpFriendRequest();

    void GetJson(std::function<void(bool, QString, QJsonObject)> callback, const TNPluginParamPtr &pluginParam, bool bAccept);
    void SetFriendInfo(QString& mineFeedId, QString& friendFeedId, QString& friendTitle, QString& friendUserId, QString& mineFeedTitle);

protected:
    void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);

private:
    std::function<void(bool, QString, QJsonObject)> checkCallback;
    QString _feedId;
    QString _friendFeedId;
    QString _friendTitle;
    QString _friendUserId;
    QString _feedTitle;

    QMap<QNetworkReply*, QString> m_replyToFeedId;
};

typedef std::shared_ptr<TNHttpFriendRequest>  TNHttpFriendRequestPtr;

#endif // TNHTTPFriendRequest_H
