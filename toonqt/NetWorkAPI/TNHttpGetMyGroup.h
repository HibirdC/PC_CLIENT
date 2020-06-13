#ifndef TNHTTPGETMYGROUP_H
#define TNHTTPGETMYGROUP_H

#include <functional>
#include <QObject>
#include "common_global.h"
#include "TNHttpBaseApi.h"

class NETWORKAPI_EXPORT TNHttpGetMyGroup : public TNHttpBaseApi
{
    Q_OBJECT

public:
	TNHttpGetMyGroup();
	~TNHttpGetMyGroup();

	void GetJson(std::function<void(bool, QJsonObject)> callback, const TNPluginParamPtr &pluginParam, const QString & version, const QString &myFeed);
protected:
	void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);

private:
	std::function<void(bool, QJsonObject)> checkCallback;
	
};
typedef std::shared_ptr<TNHttpGetMyGroup>  TNHttpGetMyGroupPtr;

#endif // TNHTTPGETMYGROUP_H
