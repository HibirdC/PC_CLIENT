#ifndef TNHTTPOBTAINGROUPCHATINFOBYGROUPCHATID_H
#define TNHTTPOBTAINGROUPCHATINFOBYGROUPCHATID_H

#include <functional>
#include <QList>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"



class NETWORKAPI_EXPORT TNHttpObtainGroupChatInfoByGroupChatId : public TNHttpBaseApi
{
public:
	TNHttpObtainGroupChatInfoByGroupChatId();
	~TNHttpObtainGroupChatInfoByGroupChatId();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets a JSON. </summary>
	///
	/// <remarks>	Ìïºã, 2017/3/9. </remarks>
	///
	/// <param name="callback">   	The callback. </param>
	/// <param name="pluginParam">	The plugin parameter. </param>
	/// <param name="version">	  	The version. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void GetJson(std::function<void(bool, QJsonObject)> callback, const TNPluginParamPtr &pluginParam, const QString & groupChatId);
protected:
	void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);
	


private:
	std::function<void(bool, QJsonObject)> checkCallback;
};

typedef std::shared_ptr<TNHttpObtainGroupChatInfoByGroupChatId>  TNHttpObtainGroupChatInfoByGroupChatIdPtr;

#endif // TNHTTPOBTAINGROUPCHATINFOBYGROUPCHATID_H
