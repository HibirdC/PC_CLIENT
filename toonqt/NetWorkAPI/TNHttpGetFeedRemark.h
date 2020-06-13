#ifndef TNHTTPGETFEEDREMARK_H
#define TNHTTPGETFEEDREMARK_H

#include <functional>
#include <QList>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"
class NETWORKAPI_EXPORT TNHttpGetFeedRemark : public TNHttpBaseApi
{
public:
	TNHttpGetFeedRemark();
	~TNHttpGetFeedRemark();

	void GetJson(std::function<void(bool, QJsonObject)> callback, const TNPluginParamPtr &pluginParam, QString fromId,QStringList tosId);

protected:
	void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);

private:
	std::function<void(bool,QJsonObject)> checkCallback;
};

typedef std::shared_ptr<TNHttpGetFeedRemark>  TNHttpGetFeedRemarkPtr;
#endif // TNHTTPGETFEEDREMARK_H
