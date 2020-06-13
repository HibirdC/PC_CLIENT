#ifndef TNHTTPBASEAPI_H
#define TNHTTPBASEAPI_H

#include <QSettings>
#include <QNetworkRequest>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QAtomicInt>
#include "NetWorkAPI.h"

class NETWORKAPI_EXPORT TNHttpBaseApi : public QObject
{
	Q_OBJECT

public:
	TNHttpBaseApi();
	~TNHttpBaseApi();
	QNetworkReply* get(QNetworkRequest& request, const QUrl url);
	QNetworkReply* post(QNetworkRequest& request, const QUrl url, const QByteArray &data);
    int getConnectCount();
    bool isNullConnection();
protected:
	virtual void requestFinished(QNetworkReply *reply, const QByteArray data, const int statusCode) = 0;
	void setRawHeader(QNetworkRequest & httpRequest);
	
public slots:
	void serviceRequestFinished(QNetworkReply *reply);
	void serviceRequestFinishedError(QNetworkReply *reply, QNetworkReply::NetworkError code);
	void sslErrors(QNetworkReply*, const QList<QSslError> &errors);
private:
	void sslVerify(QNetworkRequest& request);
	void InitNetWorkManager();
signals:
    void SuccessfulReturn(TNHttpBaseApi *);
public:
	void SetNetWorkManager(QNetworkAccessManager* manager);
	QUrl covertHttpToHttps(QUrl http);
protected:
	QNetworkAccessManager* _networkAccessManager;
    QAtomicInt _connectCount;
};

#endif // TNHTTPBASEAPI_H
