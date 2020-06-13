#ifndef TNHTTPDOMAINROUTERAPI_H
#define TNHTTPDOMAINROUTERAPI_H

#include <functional>
#include <QList>
#include <QPair>
#include "TNHttpBaseApi.h"


class NETWORKAPI_EXPORT TNHttpDomainRouterApi : public TNHttpBaseApi
{
public:
	TNHttpDomainRouterApi();
	~TNHttpDomainRouterApi();

	void GetRouterList(std::function<void(bool, QJsonObject)> callback, QString strUrl, QString strUserAgent);

protected:
	void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);
	
private:
	std::function<void(bool, QJsonObject)> checkCallback;
    QMap<QNetworkReply*, QTime> m_replyToTime;
};

typedef std::shared_ptr<TNHttpDomainRouterApi>  TNHttpDomainRouterApiPtr;

#endif // TNHTTPDOMAINROUTERAPI_H
