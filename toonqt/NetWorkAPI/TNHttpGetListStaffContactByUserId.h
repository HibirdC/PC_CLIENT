#ifndef TNHTTPGETLISTSTAFFCONTACTBYUSERID_H
#define TNHTTPGETLISTSTAFFCONTACTBYUSERID_H

#include <functional>
#include <QList>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"


class NETWORKAPI_EXPORT TNHttpGetListStaffContactByUserId : public TNHttpBaseApi
{
	Q_OBJECT

public:
	TNHttpGetListStaffContactByUserId();
	~TNHttpGetListStaffContactByUserId();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets a JSON. </summary>
	///
	/// <remarks>	田恒, 2017/3/9. </remarks>
	///
	/// <param name="callback">   	The callback. </param>
	/// <param name="pluginParam">	The plugin parameter. </param>
	/// <param name="version">	  	The version. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void GetJson(std::function<void(bool, QJsonObject)> callback, const TNPluginParamPtr &pluginParam, const QString & version);

protected:
	void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);
	


private:
	std::function<void(bool, QJsonObject)> checkCallback;
};

typedef std::shared_ptr<TNHttpGetListStaffContactByUserId>  TNHttpGetListStaffContactByUserIdPtr;

#endif // TNHTTPGETLISTSTAFFCONTACTBYUSERID_H
