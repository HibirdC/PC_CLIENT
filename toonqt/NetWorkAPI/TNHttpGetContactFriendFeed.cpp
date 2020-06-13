#include "TNHttpGetContactFriendFeed.h"

#include "qdebug.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery> 
#include <QEventLoop>
										

TNHttpGetContactFriendFeed::TNHttpGetContactFriendFeed()
{
	
}

TNHttpGetContactFriendFeed::~TNHttpGetContactFriendFeed()
{

}


void TNHttpGetContactFriendFeed::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
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

void TNHttpGetContactFriendFeed::GetJson(std::function<void(bool, QJsonObject)> callback, const TNPluginParamPtr &pluginParam, const QString & version)
{
	this->checkCallback = callback;
	// 基本 URL
	QString baseUrl = pluginParam->str_new_contact_systoon_com + URL_CONTACT_FRIEND_FEED;
	QUrl url(baseUrl);
	QUrlQuery query;
	query.addQueryItem("version", version);
	url.setQuery(query);
    qInfo() << "[NetWorkAPI][TNHttpGetContactFriendFeed]-url" << url;
	QNetworkRequest _httpRequest;
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
	get(_httpRequest, url);
}
