#ifndef TNHTTPGETORGCOMMUNICATIONSTATUS_H
#define TNHTTPGETORGCOMMUNICATIONSTATUS_H

#include <functional>

#include "common_global.h"
#include "TNHttpBaseApi.h"

class NETWORKAPI_EXPORT TNHttpGetOrgCommunicationStatus : public TNHttpBaseApi
{
public:
	TNHttpGetOrgCommunicationStatus();
	~TNHttpGetOrgCommunicationStatus();

	void GetJson(std::function<void(bool,bool, QJsonObject)> callback, const TNPluginParamPtr &pluginParam, const QSet<QString> & feedList,bool refreshCatche);
protected:
	void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);



private:
	std::function<void(bool,bool, QJsonObject)> checkCallback;
	QMap<QNetworkReply*, bool> m_extParamMap;
};

typedef std::shared_ptr<TNHttpGetOrgCommunicationStatus>  TNHttpGetOrgCommunicationStatusPtr;

#endif // TNHTTPGETORGCOMMUNICATIONSTATUS_H
