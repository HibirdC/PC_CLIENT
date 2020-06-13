#ifndef TNHTTPGetListCompanyStaffRegisterApp_H
#define TNHTTPGetListCompanyStaffRegisterApp_H

#include <functional>
#include <QList>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"


class NETWORKAPI_EXPORT TNHttpGetListCompanyStaffRegisterApp : public TNHttpBaseApi
{
public:
    TNHttpGetListCompanyStaffRegisterApp();
    ~TNHttpGetListCompanyStaffRegisterApp();

    void GetJson(std::function<void(bool, QString, QString, QJsonObject)> getAppCallback,
                 const TNPluginParamPtr &pluginParam, const QString &companyId, const QString &staffFeedId);

protected:
    void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);

private:
    std::function<void(bool, QString, QString, QJsonObject)> getAppCallback;
    QMap<QNetworkReply*, QString> m_replyToFeedId;
    QMap<QNetworkReply*, QString> m_replyToCompanyId;
};

typedef std::shared_ptr<TNHttpGetListCompanyStaffRegisterApp>  TNHttpGetListCompanyStaffRegisterAppPtr;

#endif // TNHTTPGetListCompanyStaffRegisterApp_H
