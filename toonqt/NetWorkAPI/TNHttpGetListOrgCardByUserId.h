#ifndef TNHTTPGETLISTORGCARDBYUSERID_H
#define TNHTTPGETLISTORGCARDBYUSERID_H

#include <functional>
#include <QList>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"

class NETWORKAPI_EXPORT TNHttpGetListOrgCardByUserId : public TNHttpBaseApi
{
	Q_OBJECT

public:
	TNHttpGetListOrgCardByUserId();
	~TNHttpGetListOrgCardByUserId();

	void GetJson(std::function<void(bool, QJsonObject)> callback, const TNPluginParamPtr &pluginParam, const QString &version);

protected:
	void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);

private:
	std::function<void(bool, QJsonObject)> checkCallback;
};

typedef std::shared_ptr<TNHttpGetListOrgCardByUserId>  TNHttpGetListOrgCardByUserIdPtr;

#endif // TNHTTPGETLISTORGCARDBYUSERID_H
