#ifndef TNHTTPUpdateGroupChat_H
#define TNHTTPUpdateGroupChat_H

#include <functional>
#include <QList>
#include <QPair>
#include <vector>
#include <map>

#include "common_global.h"
#include "TNHttpBaseApi.h"


class NETWORKAPI_EXPORT TNHttpUpdateGroupChat : public TNHttpBaseApi
{
public:
	TNHttpUpdateGroupChat();
	~TNHttpUpdateGroupChat();

    void GetJson(std::function<void(bool, QJsonObject,std::vector<QVariant>)> callback, const TNPluginParamPtr &pluginParam,const std::vector<QVariant>& extern_params);
    void SetUpdateInfo(const QString& feedId, const QString& groupChatId,const QString& groupChatTitle,const QString& feedTitle);
protected:
	void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);
	

private:
    std::function<void(bool, QJsonObject,std::vector<QVariant>)> checkCallback;
	QString _feedId;				//当前用户feeid
	QString _feedTitle;				//当前用户昵称
	QString _groupChatId;
	QString _groupChatName;
    std::map<QNetworkReply*,std::vector<QVariant>> _extern_params;
};

typedef std::shared_ptr<TNHttpUpdateGroupChat>  TNHttpUpdateGroupChatPtr;

#endif // TNHTTPUpdateGroupChat_H
