#ifndef TNHTTPGETLISTCARD_H
#define TNHTTPGETLISTCARD_H

#include <functional>
#include <QList>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"

class NETWORKAPI_EXPORT TNHttpGetListCard : public TNHttpBaseApi
{
public:
    TNHttpGetListCard();
    ~TNHttpGetListCard();

    void GetJson(std::function<void(bool, QJsonObject)> callback, const TNPluginParamPtr &pluginParam, const QStringList &feedids);

protected:
    void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);

private:
    std::function<void(bool, QJsonObject)> checkCallback;
};

typedef std::shared_ptr<TNHttpGetListCard>  TNHttpGetListCardPtr;

#endif // TNHTTPGETLISTCARD_H
