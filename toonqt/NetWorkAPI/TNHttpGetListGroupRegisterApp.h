#ifndef TNHTTPGetListGroupRegisterApp_H
#define TNHTTPGetListGroupRegisterApp_H

#include <functional>
#include <QList>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"


class NETWORKAPI_EXPORT TNHttpGetListGroupRegisterApp : public TNHttpBaseApi
{
public:
    TNHttpGetListGroupRegisterApp();
    ~TNHttpGetListGroupRegisterApp();

    void GetJson(std::function<void(bool, QString, QJsonObject)> getAppCallback, const TNPluginParamPtr &pluginParam, const QString &feedId);

protected:
    void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);

private:
    std::function<void(bool, QString, QJsonObject)> getAppCallback;
    QMap<QNetworkReply*, QString> m_replyToFeedId;
};

typedef std::shared_ptr<TNHttpGetListGroupRegisterApp>  TNHttpGetListGroupRegisterAppPtr;

#endif // TNHTTPGetListGroupRegisterApp_H
