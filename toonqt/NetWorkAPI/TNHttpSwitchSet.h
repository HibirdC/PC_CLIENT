#ifndef TNHTTPSwitchSet_H
#define TNHTTPSwitchSet_H

#include <functional>
#include <QList>
#include <QPair>
#include <map>
#include <vector>

#include "common_global.h"
#include "TNHttpBaseApi.h"


class NETWORKAPI_EXPORT TNHttpSwitchSet : public TNHttpBaseApi
{
public:
	TNHttpSwitchSet();
	~TNHttpSwitchSet();

    void GetJson(std::function<void(bool, QJsonObject,std::vector<QVariant>)> callback, const TNPluginParamPtr &pluginParam, bool bOn,const std::vector<QVariant>& extern_params);
    void SetSwitchInfo(const QString& feedId,const QString& passiveFeedId,const QString& passiveUserId);
protected:
	void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);
	


private:
    std::function<void(bool, QJsonObject,std::vector<QVariant> extern_params)> checkCallback;
	QString _feedId;
	QString _passiveFeedId;
	QString _passiveUserId;
    std::map<QNetworkReply*,std::vector<QVariant>> _extern_params;
};

typedef std::shared_ptr<TNHttpSwitchSet>  TNHttpSwitchSetPtr;

#endif // TNHTTPSwitchSet_H
