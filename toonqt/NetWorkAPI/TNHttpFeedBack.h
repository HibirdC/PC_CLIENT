#ifndef TNHTTPFEEDBACK_H
#define TNHTTPFEEDBACK_H

#include <functional>
#include <QList>
#include <QPair>
#include <QFile>

#include "common_global.h"
#include "TNHttpBaseApi.h"


class NETWORKAPI_EXPORT TNHttpFeedBack : public TNHttpBaseApi
{
	Q_OBJECT

public:
	TNHttpFeedBack();
	~TNHttpFeedBack();
    void FeedBack(
        std::function<void(bool, QJsonObject)> callback,
        const TNPluginParamPtr &pluginParam,
        const QString& title, 
        const QString& issueType,
        const QString& issueDescrition,
        const QString& cardNum,
        const QString& phoneNum
        );
protected:
	void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);
	
private:
    QNetworkReply *m_reply;
    std::function<void(bool, QJsonObject)> m_callBack;
};

typedef std::shared_ptr<TNHttpFeedBack>  TNHttpFeedBackPtr;

#endif // TNHTTPUPDATEVERSION_H
