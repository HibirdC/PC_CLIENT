#ifndef TNHTTPFriendRequestPhone_H
#define TNHTTPFriendRequestPhone_H

#include <functional>
#include <QList>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"

class NETWORKAPI_EXPORT TNHttpFriendRequestByPhone : public TNHttpBaseApi
{
public:
    TNHttpFriendRequestByPhone();
    ~TNHttpFriendRequestByPhone();

    void GetJson(std::function<void(bool, QString, QJsonObject)> callback, const TNPluginParamPtr &pluginParam);
    void SetFriendInfo(QString& mineFeedId, QString& friendFeedId, QString& friendTitle, QString& friendUserId, QString& mobilePhone, QString& mineFeedTitle);

protected:
    void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);

private:
    std::function<void(bool, QString, QJsonObject)> checkCallback;
    QString _feedId;
    QString _friendFeedId;
    QString _friendTitle;
    QString _friendUserId;
    QString _mobilePhone;
    QString _feedTitle;

    QMap<QNetworkReply*, QString> m_replyToFeedId;
};

typedef std::shared_ptr<TNHttpFriendRequestByPhone>  TNHttpFriendRequestByPhonePtr;

#endif // TNHTTPFriendRequestPhone_H
