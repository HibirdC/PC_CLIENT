#ifndef TNHTTPOBTAINGroupMemberFEEDLIST_H
#define TNHTTPOBTAINGroupMemberFEEDLIST_H

#include <functional>
#include <QList>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"

class NETWORKAPI_EXPORT TNHttpObtainGroupMemberFeedList : public TNHttpBaseApi
{
    Q_OBJECT

public:
    TNHttpObtainGroupMemberFeedList();
    ~TNHttpObtainGroupMemberFeedList();

    void GetJson(std::function<void(bool, QString, QJsonObject)> callback,
                 const TNPluginParamPtr &pluginParam, const QString &groupId, const QStringList &feedids);

protected:
    void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);

private:
    std::function<void(bool, QString, QJsonObject)> checkCallback;
    QMap<QNetworkReply*, QString> m_replyToFeedId;
};

typedef std::shared_ptr<TNHttpObtainGroupMemberFeedList>  TNHttpObtainGroupMemberFeedListPtr;

#endif // TNHTTPOBTAINGroupMemberFEEDLIST_H
