#ifndef TNHTTPGetMessageAppInfo_H
#define TNHTTPGetMessageAppInfo_H

#include <functional>
#include <QList>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"



class NETWORKAPI_EXPORT TNHttpGetMessageAppInfo : public TNHttpBaseApi
{
public:
	TNHttpGetMessageAppInfo();
	~TNHttpGetMessageAppInfo();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets a JSON. </summary>
	///
	/// <remarks>	litao, 2017/5/4. </remarks>
	///
	/// <param name="callback">   	The callback. </param>
	/// <param name="pluginParam">	The plugin parameter. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

    void GetAppNoticeById(std::function<void(bool, QJsonObject)> callback, const TNPluginParamPtr &pluginParam,const QString& appId);
protected:
	void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);
	


private:
	std::function<void(bool, QJsonObject)> checkCallback;
};

typedef std::shared_ptr<TNHttpGetMessageAppInfo>  TNHttpGetMessageAppInfoPtr;

#endif // TNHTTPGetMessageAppInfo_H
