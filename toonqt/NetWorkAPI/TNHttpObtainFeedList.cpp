#include "TNHttpObtainFeedList.h"

#include "qdebug.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery> 
#include <QEventLoop>
										

TNHttpObtainFeedList::TNHttpObtainFeedList()
{
	
}

TNHttpObtainFeedList::~TNHttpObtainFeedList()
{

}


void TNHttpObtainFeedList::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
{
	if (statusCode == 200) 
	{
		QJsonParseError jsonError;
		QJsonObject jsonObject = QJsonDocument::fromJson(data, &jsonError).object();
		if (jsonError.error == QJsonParseError::NoError) 
		{
			this->checkCallback(true, jsonObject, _extData, this, _extern_params[reply]);
			return;
		}
	}
	QJsonObject jsonObject;
	this->checkCallback(false, jsonObject, _extData, this, _extern_params[reply]);
}

void TNHttpObtainFeedList::GetJson(std::function<void(bool, QJsonObject,QList<UINotifyData>, TNHttpObtainFeedList* httpFeed,
	std::vector<QVariant>)> callback, const TNPluginParamPtr &pluginParam, const QStringList & feedids, QList<UINotifyData> extData,
	const std::vector<QVariant> extern_params)
{
	this->checkCallback = callback;

	QJsonArray json;
	for (int i = 0; i < feedids.size(); i++)
	{
		json.insert(i, feedids[i]);
	}

	QJsonObject jsonObject;
	jsonObject.insert("feedId", "");
	jsonObject.insert("feedIds", json);
	QJsonDocument document;
	document.setObject(jsonObject);
	QByteArray dataArray = document.toJson(QJsonDocument::Compact);

	QString baseUrl = pluginParam->str_api_feed_systoon_com + URL_OBTAIN_FEED_LIST;
	QUrl url(baseUrl);
    qInfo() << "[NetWorkAPI][TNHttpObtainFeedList] url=" << url;
	QNetworkRequest _httpRequest;
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("Accept"), QByteArray("application/json"));
	_httpRequest.setRawHeader(QByteArray("Accept-Encoding"), QByteArray("deflate"));
	_httpRequest.setRawHeader(QByteArray("Accept-Language"), QByteArray("zh-CN,zh;q=0.8"));
	_httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
	QNetworkReply* reply = post(_httpRequest, url, dataArray);
	_extData = extData;
	_extern_params[reply] = extern_params;
}
