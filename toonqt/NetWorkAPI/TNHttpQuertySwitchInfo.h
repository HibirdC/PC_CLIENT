#ifndef TNHTTPQuertySwitchInfo_H
#define TNHTTPQuertySwitchInfo_H

#include <functional>
#include <QList>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"


class NETWORKAPI_EXPORT TNHttpQuertySwitchInfo : public TNHttpBaseApi
{
	Q_OBJECT

public:
	TNHttpQuertySwitchInfo();
	~TNHttpQuertySwitchInfo();

	void GetJson(std::function<void(bool, QJsonObject)> callback, const TNPluginParamPtr &pluginParam, QString& version);
protected:
	void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);
	


private:
	std::function<void(bool, QJsonObject)> checkCallback;
};

typedef std::shared_ptr<TNHttpQuertySwitchInfo>  TNHttpQuertySwitchInfoPtr;

#endif // TNHTTPQuertySwitchInfo_H
