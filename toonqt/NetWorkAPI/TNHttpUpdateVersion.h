#ifndef TNHTTPUPDATEVERSION_H
#define TNHTTPUPDATEVERSION_H

#include <functional>
#include <QList>
#include <QPair>
#include <QFile>

#include "common_global.h"
#include "TNHttpBaseApi.h"


class NETWORKAPI_EXPORT TNHttpUpdateVersion : public TNHttpBaseApi
{
	Q_OBJECT

public:
	TNHttpUpdateVersion();
	~TNHttpUpdateVersion();
    void CheckNewVersion(std::function<void(bool, QJsonObject)> callback, const TNPluginParamPtr &pluginParam, QString& version);
	//receiver 用于连接下载进度信号
	void DownLoadNewVersion(std::function<void(bool, QString)> callback, QString& url, QObject& receiver);
protected:
	void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);
	
protected slots:
    void downloadReadyRead();
private:
	std::function<void(bool, QJsonObject)> checkVersionCallback;
	std::function<void(bool, QString)> downLoadCallBack;

	QString _url;
    QFile output;
    QNetworkReply *_reply;
};

typedef std::shared_ptr<TNHttpUpdateVersion>  TNHttpUpdateVersionPtr;

#endif // TNHTTPUPDATEVERSION_H
