#ifndef TNHTTPSetGroupChatDisb_H
#define TNHTTPSetGroupChatDisb_H

#include <functional>
#include <QList>
#include <QPair>
#include <map>
#include <vector>

#include "common_global.h"
#include "TNHttpBaseApi.h"


class NETWORKAPI_EXPORT TNHttpSetGroupChatDisb : public TNHttpBaseApi
{
public:
	TNHttpSetGroupChatDisb();
	~TNHttpSetGroupChatDisb();

    void GetJson(std::function<void(bool, QJsonObject,std::vector<QVariant>)> callback, const TNPluginParamPtr &pluginParam,const std::vector<QVariant>& extern_params);
    void SetDisturb(bool disturbStatus,const QString& feedId,const QString& groupChatId);
protected:
	void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);
	


private:
    std::function<void(bool, QJsonObject,std::vector<QVariant>)> checkCallback;
	bool	_bDisturbStatus;
	QString _feedId;
	QString _groupChatId;
    std::map<QNetworkReply*,std::vector<QVariant>> _extern_params;
};

typedef std::shared_ptr<TNHttpSetGroupChatDisb>  TNHttpSetGroupChatDisbPtr;

#endif // TNHTTPSetGroupChatDisb_H
