#ifndef TNHTTPREPLYTIMEOUT_H
#define TNHTTPREPLYTIMEOUT_H

#include <QObject>
#include <QNetworkReply>
#include <QTimer>
#define REPLY_TIMEOUT	60*1000

class TNHttpReplyTimeout : public QObject
{
	Q_OBJECT

public:
	TNHttpReplyTimeout(QNetworkReply *reply, const int timeout);
	~TNHttpReplyTimeout();

signals:
	void timeout();
	void requestFinished(QNetworkReply* reply);
	void requestFinishedError(QNetworkReply* reply, QNetworkReply::NetworkError code);
private slots:
	void onTimeout();
	void onFinished();
	void onError(QNetworkReply::NetworkError code);
private:
	QTimer* _timer;
	bool bHasError;
};

#endif // TNHTTPREPLYTIMEOUT_H
