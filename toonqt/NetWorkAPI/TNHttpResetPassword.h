#ifndef TNHttpResetPassword_H
#define TNHttpResetPassword_H

#include <functional>
#include <QList>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"


class NETWORKAPI_EXPORT TNHttpResetPassword : public TNHttpBaseApi
{
public:
    TNHttpResetPassword();
    ~TNHttpResetPassword();

    void GetJson(std::function<void(bool, QJsonObject)> callback,
                 const TNPluginParamPtr& pluginParam,
                 const QString &password);

protected:
    void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);

private:
    std::function<void(bool, QJsonObject)> checkCallback;
};

typedef std::shared_ptr<TNHttpResetPassword>  TNHttpResetPasswordPtr;

#endif // TNHttpResetPassword_H
