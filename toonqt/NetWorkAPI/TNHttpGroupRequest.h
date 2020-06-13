#ifndef TNHTTPGroupRequest_H
#define TNHTTPGroupRequest_H

#include <functional>
#include <QList>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"


class NETWORKAPI_EXPORT TNHttpGroupRequest : public TNHttpBaseApi
{
public:
	TNHttpGroupRequest();
	~TNHttpGroupRequest();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets a JSON. </summary>
	///
	/// <remarks>	ÀîÌÎ, 2017/4/19. </remarks>
	///
	/// <param name="callback">   	The callback. </param>
	/// <param name="pluginParam">	The plugin parameter. </param>
	/// <param name="bAccept">		is accept friend request. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void GetJson(std::function<void(bool, QJsonObject)> callback, const TNPluginParamPtr &pluginParam, bool bAccept);
	void SetGroupReqInfo(QString& feedId, QString& feedName, QString& userId, QString& groupId);
protected:
	void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);
	


private:
	std::function<void(bool, QJsonObject)> checkCallback;
	QString _feedId;
	QString _feedName;
	QString _userId;
	QString _groupId;
};

typedef std::shared_ptr<TNHttpGroupRequest>  TNHttpGroupRequestPtr;

#endif // TNHTTPGroupRequest_H
