#ifndef TNHTTPORGCARDRequest_H
#define TNHTTPORGCARDRequest_H

#include <functional>
#include <QList>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"


class NETWORKAPI_EXPORT TNHttpOrgCardRequest : public TNHttpBaseApi
{
public:
	TNHttpOrgCardRequest();
	~TNHttpOrgCardRequest();

	void GetJson(std::function<void(bool, QJsonObject)> callback, const TNPluginParamPtr &pluginParam, bool bAccept);
	void SetOrgCardFeedId(QString& feedId);

protected:
	void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);
	
private:
	std::function<void(bool, QJsonObject)> checkCallback;
	QString _feedId;
	QString _userId;
};

typedef std::shared_ptr<TNHttpOrgCardRequest>  TNHttpOrgCardRequestPtr;

#endif // TNHTTPORGCARDRequest_H
