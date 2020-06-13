#include "TNHttpDomainRouterApi.h"

#include "qdebug.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery> 
#include <QEventLoop>
										

TNHttpDomainRouterApi::TNHttpDomainRouterApi()
{
	
}

TNHttpDomainRouterApi::~TNHttpDomainRouterApi()
{

}


void TNHttpDomainRouterApi::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
{
	if (statusCode == 200) 
	{
		QJsonParseError jsonError;
		QJsonObject jsonObject = QJsonDocument::fromJson(data, &jsonError).object();
		if (jsonError.error == QJsonParseError::NoError) 
		{
			this->checkCallback(true, jsonObject);
            qInfo() << "TNHttpDomainRouterApi-request time=" << m_replyToTime.take(reply).elapsed();
			return;
		}
	}
	QJsonObject jsonObject;
	this->checkCallback(false, jsonObject);
    qInfo() << "TNHttpDomainRouterApi-request time=" << m_replyToTime.take(reply).elapsed();
}

void TNHttpDomainRouterApi::GetRouterList(std::function<void(bool, QJsonObject)> callback, QString strUrl, QString strUserAgent)
{
	this->checkCallback = callback;
	// Json数据
	QJsonObject json;
	json.insert("version", "0");
	QJsonDocument document;
	document.setObject(json);
	QByteArray dataArray = document.toJson(QJsonDocument::Compact);
	// 基本 URL
	QString baseUrl = strUrl + "/user/router/domain";
	QUrl url(baseUrl);
    qDebug() << "TNHttpDomainRouterApi-url=" << url;
	QNetworkRequest _httpRequest;
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), QByteArray("305146"));
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), QByteArray("2a11a1e2-91ef-457b-91a2-f82688325f4c"));
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), strUserAgent.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
    QNetworkReply *reply = post(_httpRequest, url, dataArray);
    m_replyToTime[reply].start();
}
