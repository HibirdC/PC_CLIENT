#ifndef TNHTTPGETORGGROUPLIST_H
#define TNHTTPGETORGGROUPLIST_H

#include <functional>
#include <QList>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"



class NETWORKAPI_EXPORT TNHttpGetOrgGroupList : public TNHttpBaseApi
{
	Q_OBJECT

public:
	TNHttpGetOrgGroupList();
	~TNHttpGetOrgGroupList();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets a JSON. </summary>
	///
	/// <remarks>	Ìïºã, 2017/3/9. </remarks>
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

typedef std::shared_ptr<TNHttpGetOrgGroupList>  TNHttpGetOrgGroupListPtr;

#endif // TNHTTPGETORGGROUPLIST_H
