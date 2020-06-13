#ifndef TNHTTPGETLISTRECOMMENDAPP_H
#define TNHTTPGETLISTRECOMMENDAPP_H

#include <functional>
#include <QList>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"

class NETWORKAPI_EXPORT TNHttpGetListRecommendApp : public TNHttpBaseApi
{
    Q_OBJECT

public:
    TNHttpGetListRecommendApp();
    ~TNHttpGetListRecommendApp();

    void GetJson(std::function<void(bool, QJsonObject)> callback, const TNPluginParamPtr &pluginParam, const QString &feedId);

protected:
    void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);

private:
    std::function<void(bool, QJsonObject)> checkCallback;
};

typedef std::shared_ptr<TNHttpGetListRecommendApp>  TNHttpGetListRecommendAppPtr;

#endif // TNHTTPGETLISTRECOMMENDAPP_H
