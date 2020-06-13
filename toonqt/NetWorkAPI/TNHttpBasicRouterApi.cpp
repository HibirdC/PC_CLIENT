#include "TNHttpBasicRouterApi.h"

#include "qdebug.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery> 
#include <QEventLoop>


TNHttpBasicRouterApi::TNHttpBasicRouterApi()
{
	
}

TNHttpBasicRouterApi::~TNHttpBasicRouterApi()
{

}


void TNHttpBasicRouterApi::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
{
	if (statusCode == 200) 
	{
		QJsonParseError jsonError;
		QJsonObject jsonObject = QJsonDocument::fromJson(data, &jsonError).object();
		if (jsonError.error == QJsonParseError::NoError) 
		{
			this->checkCallback(true, jsonObject);
			return;
		}
	}
	QJsonObject jsonObject;
	this->checkCallback(false, jsonObject);
}

void TNHttpBasicRouterApi::GetRouterList(std::function<void(bool, QJsonObject)> callback, QString strUserAgent)
{
	this->checkCallback = callback;
	// 基本 URL
	QString baseUrl = URL_ROUTER_LIST;
	QUrl url(baseUrl);
    qDebug() << "TNHttpBasicRouterApi-url=" << url;
	QNetworkRequest _httpRequest;
	//X-Toon-User-ID,X-Toon-User-Token 无关值 任意值都可以
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), QByteArray("305146"));
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), QByteArray("2a11a1e2-91ef-457b-91a2-f82688325f4c"));
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), strUserAgent.toStdString().c_str());
	get(_httpRequest, url);
}
