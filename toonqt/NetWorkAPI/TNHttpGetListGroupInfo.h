#ifndef TNHTTPGETLISTGroupInfo_H
#define TNHTTPGETLISTGroupInfo_H

#include <functional>
#include <QList>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"


class NETWORKAPI_EXPORT TNHttpGetListGroupInfo : public TNHttpBaseApi
{
public:
	TNHttpGetListGroupInfo();
	~TNHttpGetListGroupInfo();

    void GetJson(std::function<void(bool, QJsonObject)> callback, const TNPluginParamPtr &pluginParam, const QString& groupId);

protected:
	void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);
	
private:
	std::function<void(bool, QJsonObject)> checkCallback;
};

typedef std::shared_ptr<TNHttpGetListGroupInfo> TNHttpGetListGroupInfoPtr;

#endif // TNHTTPGETLISTGroupInfo_H
