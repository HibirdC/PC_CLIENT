#ifndef TNHTTPQuitGroupChat_H
#define TNHTTPQuitGroupChat_H

#include <functional>
#include <QList>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"


class NETWORKAPI_EXPORT TNHttpQuitGroupChat : public TNHttpBaseApi
{
public:
    TNHttpQuitGroupChat();
    ~TNHttpQuitGroupChat();

    void GetJson(std::function<void(bool, QString, QJsonObject)> callback, const TNPluginParamPtr& pluginParam);
    void SetQuitGroupInfo(const QString& feedId, const QString& feedTitle, const QString& groupId, const QString& userId);

protected:
    void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);

private:
    std::function<void(bool, QString, QJsonObject)> checkCallback;
    QString		_feedId;
    QString		_groupId;
    QString		_feedTitle;
    QString		_userId;

    QMap<QNetworkReply*, QString> m_replyToGroupChat;
};

typedef std::shared_ptr<TNHttpQuitGroupChat>  TNHttpQuitGroupChatPtr;

#endif // TNHTTPQuitGroupChat_H
