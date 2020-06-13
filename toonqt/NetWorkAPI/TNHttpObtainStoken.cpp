#include "TNHttpObtainStoken.h"

#include "qdebug.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery> 
#include <QEventLoop>
										

TNHttpObtainStoken::TNHttpObtainStoken()
{
	
}

TNHttpObtainStoken::~TNHttpObtainStoken()
{

}


void TNHttpObtainStoken::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
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

void TNHttpObtainStoken::GetJson(std::function<void(bool, QJsonObject)> callback, const TNPluginParamPtr& pluginParam)
{
	this->checkCallback = callback;
	QJsonObject jsonObject;
	jsonObject.insert("appType", APPTYPE);//100,开发环境用1001
	jsonObject.insert("isWriteAble", "1");
	QJsonDocument document;
	document.setObject(jsonObject);
	QByteArray dataArray = document.toJson(QJsonDocument::Compact);

	// 基本 URL
	QString baseUrl = pluginParam->str_api_new_groupchat_systoon_com + URL_OBTAIN_STOKEN;
	QUrl url(baseUrl);
	qDebug() << url;
	QNetworkRequest _httpRequest;
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
	post(_httpRequest, url, dataArray);
}