#ifndef TNHTTPGETGROUPCARDBYUSER_H
#define TNHTTPGETGROUPCARDBYUSER_H

#include <functional>
#include <QList>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"



class NETWORKAPI_EXPORT TNHttpGetGroupCardByUser : public TNHttpBaseApi
{
	Q_OBJECT

public:
	TNHttpGetGroupCardByUser();
	~TNHttpGetGroupCardByUser();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets a JSON. </summary>
	///
	/// <remarks>	田恒, 2017/3/9. </remarks>
	///
	/// <param name="callback">   	The callback. </param>
	/// <param name="pluginParam">	The plugin parameter. </param>
	/// <param name="version">	  	The version. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void GetJson(std::function<void(bool, QJsonObject)> callback, const TNPluginParamPtr &pluginParam, const QString & version, const QString &queryType);
protected:
	void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);
	


private:
	std::function<void(bool, QJsonObject)> checkCallback;
};

typedef std::shared_ptr<TNHttpGetGroupCardByUser>  TNHttpGetGroupCardByUserPtr;

#endif // TNHTTPGETGROUPCARDBYUSER_H
