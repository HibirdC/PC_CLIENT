#ifndef TNHttpGetListCompanyCardRegisterApp_H
#define TNHttpGetListCompanyCardRegisterApp_H

#include <functional>
#include <QList>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"


class NETWORKAPI_EXPORT TNHttpGetListCompanyCardRegisterApp : public TNHttpBaseApi
{
public:
    TNHttpGetListCompanyCardRegisterApp();
    ~TNHttpGetListCompanyCardRegisterApp();

    void GetJson(std::function<void(bool, QString, QJsonObject)> getAppCallback,
                 const TNPluginParamPtr &pluginParam, const QString &companyId, const QString &orgFeedId);

protected:
    void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);

private:
    std::function<void(bool, QString, QJsonObject)> getAppCallback;
    QMap<QNetworkReply*, QString> m_replyToFeedId;
};

typedef std::shared_ptr<TNHttpGetListCompanyCardRegisterApp>  TNHttpGetListCompanyCardRegisterAppPtr;

#endif // TNHttpGetListCompanyCardRegisterApp_H
