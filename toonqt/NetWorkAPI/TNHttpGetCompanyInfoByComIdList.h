#ifndef TNHTTPGETCOMPANYINFOBYCOMIDLIST_H
#define TNHTTPGETCOMPANYINFOBYCOMIDLIST_H

#include <functional>
#include <QList>
#include <QSet>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"


class NETWORKAPI_EXPORT TNHttpGetCompanyInfoByComIdList : public TNHttpBaseApi
{
public:
	TNHttpGetCompanyInfoByComIdList();
	~TNHttpGetCompanyInfoByComIdList();

	void GetJson(std::function<void(bool, QJsonObject)> callback, const TNPluginParamPtr &pluginParam, const QSet<QString> & comIDList);
protected:
	void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);
	


private:
	std::function<void(bool, QJsonObject)> checkCallback;
};

typedef std::shared_ptr<TNHttpGetCompanyInfoByComIdList>  TNHttpGetCompanyInfoByComIdListPtr;

#endif // TNHTTPGETCOMPANYINFOBYCOMIDLIST_H
