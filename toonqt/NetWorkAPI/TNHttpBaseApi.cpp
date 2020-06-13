#include <QByteArray> 
#include "TNHttpBaseApi.h"
#include <QNetworkConfigurationManager>
#include "TNHttpReplyTimeout.h"
#include "TNConfig.h"


TNHttpBaseApi::TNHttpBaseApi() :_networkAccessManager(NULL)
{
    _connectCount.store(0);
}


TNHttpBaseApi::~TNHttpBaseApi()
{
	if (_networkAccessManager)
		_networkAccessManager->disconnect();
}

bool TNHttpBaseApi::isNullConnection()
{
    return _connectCount.testAndSetRelaxed(0, 0);
}

int TNHttpBaseApi::getConnectCount()
{
    return _connectCount.load();
}

void TNHttpBaseApi::setRawHeader(QNetworkRequest & httpRequest)
{
}
QNetworkReply* TNHttpBaseApi::get(QNetworkRequest& request, const QUrl url)
{
	InitNetWorkManager();
	_networkAccessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);
    _connectCount.fetchAndAddRelaxed(1);
	QUrl latestUrl = covertHttpToHttps(url);
	Q_ASSERT(latestUrl.isValid());
	if (latestUrl.toString().indexOf(HTTPS) == 0)
		sslVerify(request);
	request.setUrl(QUrl(latestUrl));
	qInfo() << "[NetWorkAPI][TNHttpBaseApi]get url:" << latestUrl;
	QNetworkReply* reply = _networkAccessManager->get(request);
	TNHttpReplyTimeout *pTimeout = new TNHttpReplyTimeout(reply, REPLY_TIMEOUT);
	connect(pTimeout, &TNHttpReplyTimeout::timeout, [=]() {
		qInfo() << "[NetWorkAPI][TNHttpBaseApi] get url" << latestUrl << "timeout";
		requestFinished(reply, "request timeout", QNetworkReply::TimeoutError);
		_connectCount.fetchAndAddRelaxed(-1);
		emit SuccessfulReturn(this);
	});
	connect(pTimeout, SIGNAL(requestFinished(QNetworkReply*)), this, SLOT(serviceRequestFinished(QNetworkReply*)));
	connect(pTimeout, SIGNAL(requestFinishedError(QNetworkReply*, QNetworkReply::NetworkError)), this, SLOT(serviceRequestFinishedError(QNetworkReply*, QNetworkReply::NetworkError)));
	return reply;
}

QNetworkReply* TNHttpBaseApi::post(QNetworkRequest& request, const QUrl url, const QByteArray &data)
{
	InitNetWorkManager();
	_networkAccessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);
    _connectCount.fetchAndAddRelaxed(1);
	QUrl latestUrl = covertHttpToHttps(url);
	Q_ASSERT(latestUrl.isValid());
	if (latestUrl.toString().indexOf(HTTPS) == 0)
		sslVerify(request);
	request.setUrl(latestUrl);
	qInfo() << "[NetWorkAPI][TNHttpBaseApi]post url:" << latestUrl;
	QNetworkReply* reply = _networkAccessManager->post(request, data);
	TNHttpReplyTimeout *pTimeout = new TNHttpReplyTimeout(reply, REPLY_TIMEOUT);
	connect(pTimeout, &TNHttpReplyTimeout::timeout, [=]() {
		qInfo() << "[NetWorkAPI][TNHttpBaseApi] post url" << latestUrl << "timeout";
		requestFinished(reply, "request timeout", QNetworkReply::TimeoutError);
		_connectCount.fetchAndAddRelaxed(-1);
		emit SuccessfulReturn(this);
	});
	connect(pTimeout, SIGNAL(requestFinished(QNetworkReply*)), this, SLOT(serviceRequestFinished(QNetworkReply*)));
	connect(pTimeout, SIGNAL(requestFinishedError(QNetworkReply*, QNetworkReply::NetworkError)), this, SLOT(serviceRequestFinishedError(QNetworkReply*, QNetworkReply::NetworkError)));
	return reply;
}

void TNHttpBaseApi::sslVerify(QNetworkRequest& request)
{
	// 发送https请求前准备工作;
	QSslConfiguration conf = request.sslConfiguration();
	conf.setPeerVerifyMode(QSslSocket::VerifyNone);
	conf.setProtocol(QSsl::TlsV1SslV3);
	request.setSslConfiguration(conf);
}

void TNHttpBaseApi::serviceRequestFinished(QNetworkReply *reply)
{
	int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	qInfo() << "[NetWorkAPI][TNHttpBaseApi]serviceRequestFinished statusCode:" << statusCode << "url:" << reply->url();
	if (reply->error() == QNetworkReply::NoError) {
		requestFinished(reply, reply->readAll(), statusCode);
	}
	else {
		qCritical() << "[NetWorkAPI][TNHttpBaseApi] Error:" << reply->error();
		if (reply->error() != QNetworkReply::OperationCanceledError)
		{
			requestFinished(reply, "", statusCode);
		}
	}

	// At the end of that slot, we won't need it anymore
	reply->deleteLater();
    _connectCount.fetchAndAddRelaxed(-1);
    emit SuccessfulReturn(this);
}

void TNHttpBaseApi::serviceRequestFinishedError(QNetworkReply *reply, QNetworkReply::NetworkError code)
{
	int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	qWarning() << "[NetWorkAPI][TNHttpBaseApi] Error: statusCode:" << statusCode << "url:" << reply->url() <<  "errcode:" << reply->error();
	requestFinished(reply, "", statusCode);
	reply->deleteLater();
	_connectCount.fetchAndAddRelaxed(-1);
	emit SuccessfulReturn(this);
}


void TNHttpBaseApi::sslErrors(QNetworkReply* reply, const QList<QSslError> &errors)
{
	QString errorString;
	foreach(const QSslError &error, errors) {
		if (!errorString.isEmpty())
			errorString += '\n';
		errorString += error.errorString();
	}
	qCritical() << "[NetWorkAPI][TNHttpBaseApi] sslErrors:" << errorString;
	reply->ignoreSslErrors();
}

void TNHttpBaseApi::InitNetWorkManager()
{
	if (_networkAccessManager == NULL)
	{
		_networkAccessManager = new QNetworkAccessManager(this);
		QNetworkConfigurationManager manager;
		_networkAccessManager->setConfiguration(manager.defaultConfiguration());
		_networkAccessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);
		//QObject::connect(&_networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(serviceRequestFinished(QNetworkReply*)));
		connect(_networkAccessManager, &QNetworkAccessManager::sslErrors, this, &TNHttpBaseApi::sslErrors);
	}
}

void TNHttpBaseApi::SetNetWorkManager(QNetworkAccessManager* manager)
{
	if (_networkAccessManager == NULL)
		_networkAccessManager = manager;
	//QObject::connect(&_networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(serviceRequestFinished(QNetworkReply*)));
	connect(_networkAccessManager, &QNetworkAccessManager::sslErrors, this, &TNHttpBaseApi::sslErrors);
}
QUrl TNHttpBaseApi::covertHttpToHttps(QUrl baseUrl)
{
	Q_ASSERT(baseUrl.isValid());
	QUrl newUrl(baseUrl);
    ENV_TYPE eType = TNConfig::instance()->GetEnvType();
    if (eType == TYPE_ONLINE)
    {
        if (baseUrl.toString().indexOf(HTTPS) == 0)
            newUrl = baseUrl;
        else{
            QUrl tempURL = baseUrl;
            tempURL = HTTPS + tempURL.toString().right(tempURL.toString().length() - 4);
            newUrl = tempURL;
        }
    }
	return newUrl;
}
