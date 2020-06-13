#ifndef TNHTTPGETCOMPANYFEEDIDBYCOMID_H
#define TNHTTPGETCOMPANYFEEDIDBYCOMID_H

#include <functional>
#include <QList>
#include <QSet>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"


class NETWORKAPI_EXPORT TNHttpGetCompanyFeedIdByComId : public TNHttpBaseApi
{	

public:
	TNHttpGetCompanyFeedIdByComId();
	~TNHttpGetCompanyFeedIdByComId();

    void GetJson(std::function<void(bool, QString, QJsonObject)> callback, const TNPluginParamPtr &pluginParam,
                 const QString &staffFeedId, const QString &comId);

protected:
	void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);

private:
    std::function<void(bool, QString, QJsonObject)> checkCallback;
    QMap<QNetworkReply*, QString> m_replyToFeedId;
};
typedef std::shared_ptr<TNHttpGetCompanyFeedIdByComId>  TNHttpGetCompanyFeedIdByComIdPtr;
#endif // TNHTTPGETCOMPANYFEEDIDBYCOMID_H
