#ifndef TNHttpCheckVCodeBeforeLogin_H
#define TNHttpCheckVCodeBeforeLogin_H

#include <functional>
#include <QList>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"


class NETWORKAPI_EXPORT TNHttpCheckVCodeBeforeLogin : public TNHttpBaseApi
{
public:
    TNHttpCheckVCodeBeforeLogin();
    ~TNHttpCheckVCodeBeforeLogin();

    void setParams(const QString &teleCode, const QString &mobile, const QString &mobileVerfiyCode);
    void GetJson(std::function<void(bool, QJsonObject)> callback,
                 const TNPluginParamPtr& pluginParam);

protected:
    void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);

private:
    std::function<void(bool, QJsonObject)> checkCallback;

    QString m_teleCode;
    QString m_mobile;
    QString m_mobileVerfiyCode;
};

typedef std::shared_ptr<TNHttpCheckVCodeBeforeLogin>  TNHttpCheckVCodeBeforeLoginPtr;

#endif // TNHttpCheckVCodeBeforeLogin_H
