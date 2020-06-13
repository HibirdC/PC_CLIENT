#ifndef TNHttpGetListOrgCard_H
#define TNHttpGetListOrgCard_H

#include <functional>
#include <QList>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"


class NETWORKAPI_EXPORT TNHttpGetListOrgCard : public TNHttpBaseApi
{
public:
	TNHttpGetListOrgCard();
	~TNHttpGetListOrgCard();

    void GetJson(std::function<void(bool, QString, QJsonObject)> callback, const TNPluginParamPtr &pluginParam,
                 const QString &staffFeedId, const QStringList &feedids);

protected:
	void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);

private:
    std::function<void(bool, QString, QJsonObject)> checkCallback;
    QMap<QNetworkReply*, QString> m_replyToFeedId;
};

typedef std::shared_ptr<TNHttpGetListOrgCard>  TNHttpGetListOrgCardPtr;

#endif // TNHttpGetListOrgCard_H
