#ifndef TNHTTPGetListCardRegisterApp_H
#define TNHTTPGetListCardRegisterApp_H

#include <functional>
#include <QList>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"


class NETWORKAPI_EXPORT TNHttpGetListCardRegisterApp : public TNHttpBaseApi
{
public:
	TNHttpGetListCardRegisterApp();
	~TNHttpGetListCardRegisterApp();

    void GetJson(std::function<void(bool, QString, QJsonObject)> getAppCallback, const TNPluginParamPtr &pluginParam, const QString& feedId);

protected:
	void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);

private:
    std::function<void(bool, QString, QJsonObject)> getAppCallback;
    QMap<QNetworkReply*, QString> m_replyToFeedId;
};

typedef std::shared_ptr<TNHttpGetListCardRegisterApp>  TNHttpGetListCardRegisterAppPtr;

#endif // TNHTTPGetListCardRegisterApp_H
