#ifndef TNHTTPOBTAINGROUPMEMBERSBYGROUPID_H
#define TNHTTPOBTAINGROUPMEMBERSBYGROUPID_H

#include <functional>
#include <QList>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"

class NETWORKAPI_EXPORT TNHttpObtainGroupMembersByGroupId : public TNHttpBaseApi
{
    Q_OBJECT

public:
    TNHttpObtainGroupMembersByGroupId();
    ~TNHttpObtainGroupMembersByGroupId();

    void GetJson(std::function<void(bool, QString, QJsonObject)> callback, const TNPluginParamPtr &pluginParam, const QString &groupId, const QString &version);

protected:
    void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);

private:
    std::function<void(bool, QString, QJsonObject)> checkCallback;
    QMap<QNetworkReply*, QString> m_replyToFeedId;
};

typedef std::shared_ptr<TNHttpObtainGroupMembersByGroupId>  TNHttpObtainGroupMembersByGroupIdPtr;

#endif // TNHTTPOBTAINGROUPMEMBERSBYGROUPID_H
