#ifndef TNHTTPROUTERAPI_H
#define TNHTTPROUTERAPI_H

#include <functional>
#include <QList>
#include <QPair>
#include "TNHttpBaseApi.h"



class NETWORKAPI_EXPORT TNHttpBasicRouterApi : public TNHttpBaseApi
{
public:
	TNHttpBasicRouterApi();
	~TNHttpBasicRouterApi();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets router list. </summary>
	///
	/// <remarks>	田恒, 2017/3/6. </remarks>
	///
	/// <param name="callback">	The callback. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void GetRouterList(std::function<void(bool, QJsonObject)> callback, QString strUserAgent);

protected:
	void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);
	

private:
	std::function<void(bool, QJsonObject)> checkCallback;
};

typedef std::shared_ptr<TNHttpBasicRouterApi>  TNHttpBasicRouterApiPtr;

#endif // TNHTTPROUTERAPI_H
