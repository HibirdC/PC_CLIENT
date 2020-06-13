#ifndef TNHTTPOBTAINFEEDLIST_H
#define TNHTTPOBTAINFEEDLIST_H

#include <functional>
#include <QList>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"


class NETWORKAPI_EXPORT TNHttpObtainFeedList : public TNHttpBaseApi
{
    Q_OBJECT

public:
	TNHttpObtainFeedList();
	~TNHttpObtainFeedList();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets a JSON. </summary>
	///
	/// <remarks>	Ìïºã, 2017/3/9. </remarks>
	///
	/// <param name="callback">   	The callback. </param>
	/// <param name="pluginParam">	The plugin parameter. </param>
	/// <param name="feedids">	  	The feedids. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void GetJson(std::function<void(bool, QJsonObject, QList<UINotifyData> extData, TNHttpObtainFeedList* httpFeed, std::vector<QVariant>)> callback, const TNPluginParamPtr &pluginParam, 
		const QStringList & feedids, QList<UINotifyData> extData,const std::vector<QVariant> extern_params);
protected:
	void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);

private:
	std::function<void(bool, QJsonObject, QList<UINotifyData> extData, TNHttpObtainFeedList* httpFeed, std::vector<QVariant>)> checkCallback;
	QList<UINotifyData>						_extData;
	std::map<QNetworkReply*, std::vector<QVariant>> _extern_params;
};

typedef std::shared_ptr<TNHttpObtainFeedList>  TNHttpObtainFeedListPtr;

#endif // TNHTTPOBTAINFEEDLIST_H
