#include "TNHttpReplyTimeout.h"


TNHttpReplyTimeout::TNHttpReplyTimeout(QNetworkReply *reply, const int timeout)
: QObject(reply), _timer(NULL), bHasError(false)
{
	if (reply && reply->isRunning())
	{
		connect(reply, SIGNAL(finished()), this, SLOT(onFinished()));
		connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
		/*_timer = new QTimer(this);
		_timer->setSingleShot(true);
		_timer->setInterval(timeout);
		connect(_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
		_timer->start();*/
	}
}

TNHttpReplyTimeout::~TNHttpReplyTimeout()
{

}

void TNHttpReplyTimeout::onTimeout()
{
	QNetworkReply *reply = static_cast<QNetworkReply*>(parent());
	if (reply->isRunning() && !reply->isFinished())
	{
		disconnect(reply, SIGNAL(finished()), this, SLOT(onFinished()));
		emit timeout();
		reply->abort();
		reply->deleteLater();
	}
}

void TNHttpReplyTimeout::onFinished()
{
	if (!bHasError)
		emit requestFinished(static_cast<QNetworkReply*>(parent()));
}

void TNHttpReplyTimeout::onError(QNetworkReply::NetworkError code)
{
	bHasError = true;
	emit requestFinishedError(static_cast<QNetworkReply*>(parent()), code);
}