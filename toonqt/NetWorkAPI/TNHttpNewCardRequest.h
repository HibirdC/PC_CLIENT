#ifndef TNHTTPNEWCARDRequest_H
#define TNHTTPNEWCARDRequest_H

#include <functional>
#include <QList>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"


class NETWORKAPI_EXPORT TNHttpNewCardRequest : public TNHttpBaseApi
{
public:
	TNHttpNewCardRequest();
	~TNHttpNewCardRequest();

	void GetJson(std::function<void(bool, QJsonObject)> callback, const TNPluginParamPtr &pluginParam, bool bAccept);
	void SetStaffInfo(QString& feedId, QString& userId);

protected:
	void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);
	
private:
	std::function<void(bool, QJsonObject)> checkCallback;
	QString _feedId;
	QString _userId;
};

typedef std::shared_ptr<TNHttpNewCardRequest>  TNHttpNewCardRequestPtr;

#endif // TNHTTPNEWCARDRequest_H
