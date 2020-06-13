#ifndef TNHTTPOBTAINGROUPCHATMEMBERSBYGROUPCHATID_H
#define TNHTTPOBTAINGROUPCHATMEMBERSBYGROUPCHATID_H

#include <functional>
#include <QList>
#include <QPair>
#include <QMap>

#include "common_global.h"
#include "TNHttpBaseApi.h"

class NETWORKAPI_EXPORT TNHttpObtainGroupChatMembersByGroupChatId : public TNHttpBaseApi
{
    Q_OBJECT

public:
    TNHttpObtainGroupChatMembersByGroupChatId();
    ~TNHttpObtainGroupChatMembersByGroupChatId();

    void GetJson(std::function<void(bool, QString, QJsonObject)> callback, const TNPluginParamPtr &pluginParam,const QString &groupChatId, const QString &version);

protected:
    void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);

private:
    std::function<void(bool, QString, QJsonObject)> checkCallback;
    QMap<QNetworkReply*, QString> m_replyToGroupChatId;
};

typedef std::shared_ptr<TNHttpObtainGroupChatMembersByGroupChatId>  TNHttpObtainGroupChatMembersByGroupChatIdPtr;

#endif // TNHTTPOBTAINGROUPCHATMEMBERSBYGROUPCHATID_H
