#include "TNHttpGetFeedRemark.h"
#include "qdebug.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery> 
#include <QEventLoop>

TNHttpGetFeedRemark::TNHttpGetFeedRemark()
	: TNHttpBaseApi()
{

}

TNHttpGetFeedRemark::~TNHttpGetFeedRemark()
{

}
void TNHttpGetFeedRemark::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
{
	if (statusCode == 200)
	{
		QJsonParseError jsonError;
		QJsonObject jsonObject = QJsonDocument::fromJson(data, &jsonError).object();
		if (jsonError.error == QJsonParseError::NoError)
		{
			this->checkCallback(true,jsonObject);
			return;
		}
	}
	QJsonObject jsonObject;
	this->checkCallback(false,jsonObject);
}

void TNHttpGetFeedRemark::GetJson(std::function<void(bool, QJsonObject)> callback,
	const TNPluginParamPtr &pluginParam, QString fromId, QStringList tosID)
{
	this->checkCallback = callback;

	QJsonArray json;
	for (int i = 0; i < tosID.size(); i++)
	{
		json.insert(i, tosID[i]);
	}
	QJsonObject jsonObject;
	jsonObject.insert("from", fromId);
	jsonObject.insert("tos", json);
	QJsonDocument document;
	document.setObject(jsonObject);
	QByteArray dataArray = document.toJson(QJsonDocument::Compact);

	// »ù±¾ URL
	QString baseUrl = pluginParam->str_new_contact_systoon_com + URL_GETFEEDREMARK;
	QUrl url(baseUrl);
	qInfo() << "[NetWorkAPI][TNHttpGetFeedRemark] url=" << url;
	QNetworkRequest _httpRequest;
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
	post(_httpRequest, url, dataArray);
}
