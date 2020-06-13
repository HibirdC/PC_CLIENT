#ifndef TNHTTPOBTAINAPPCODE_H
#define TNHTTPOBTAINAPPCODE_H

#include <functional>
#include <QList>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"

class NETWORKAPI_EXPORT TNHttpObtainAppCode : public TNHttpBaseApi
{
public:
	TNHttpObtainAppCode();
	~TNHttpObtainAppCode();

    void GetJson(std::function<void(bool, QString, QJsonObject)> callback, const TNPluginParamPtr &pluginParam,
		const QString &appId, const QString &frame, const QString &companyId_owner, const QString &feedId_owner, const QString &userId_visitor, const QString &feedId_visitor);

protected:
	void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);

private:
    std::function<void(bool, QString, QJsonObject)> checkCallback;
    QMap<QNetworkReply*, QString> m_replyToFeedId;
};

typedef std::shared_ptr<TNHttpObtainAppCode>  TNHttpObtainAppCodePtr;

#endif // TNHTTPOBTAINAPPCODE_H
