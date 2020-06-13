#ifndef TNHTTPObtainStoken_H
#define TNHTTPObtainStoken_H

#include <functional>
#include <QList>
#include <QPair>

#include "TNVersionInfo.h"
#include "TNHttpBaseApi.h"


class NETWORKAPI_EXPORT TNHttpObtainStoken : public TNHttpBaseApi
{
public:
	TNHttpObtainStoken();
	~TNHttpObtainStoken();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets a JSON. </summary>
	///
	/// <remarks>	ÀîÌÎ, 2017/4/7. </remarks>
	///
	/// <param name="callback">   	The callback. </param>
	/// <param name="pluginParam">	The plugin parameter. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void GetJson(std::function<void(bool, QJsonObject)> callback, const TNPluginParamPtr& pluginParam);
protected:
	void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);
	


private:
	std::function<void(bool, QJsonObject)> checkCallback;
};

typedef std::shared_ptr<TNHttpObtainStoken>  TNHttpObtainStokenPtr;

#endif // TNHTTPObtainStoken_H
