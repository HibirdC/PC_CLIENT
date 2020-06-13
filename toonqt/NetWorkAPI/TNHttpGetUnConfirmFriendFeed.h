#ifndef TNHTTPGETUNCONFIRMFRIENDFEED_H
#define TNHTTPGETUNCONFIRMFRIENDFEED_H
#include <functional>
#include <QList>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"

class NETWORKAPI_EXPORT TNHttpGetUnConfirmFriendFeed : public TNHttpBaseApi
{
	Q_OBJECT

public:
	TNHttpGetUnConfirmFriendFeed();
	~TNHttpGetUnConfirmFriendFeed();

	void GetJson(std::function<void(bool, QJsonObject)> callback, const TNPluginParamPtr &pluginParam, const QString & version);
protected:
	void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);



private:
	std::function<void(bool, QJsonObject)> checkCallback;
};
typedef std::shared_ptr<TNHttpGetUnConfirmFriendFeed>  TNHttpGetUnConfirmFriendFeedPtr;
#endif // TNHTTPGETUNCONFIRMFRIENDFEED_H
