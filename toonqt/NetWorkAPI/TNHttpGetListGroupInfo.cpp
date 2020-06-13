#include "TNHttpGetListGroupInfo.h"

#include "qdebug.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery> 
#include <QEventLoop>
										

TNHttpGetListGroupInfo::TNHttpGetListGroupInfo()
{
	
}

TNHttpGetListGroupInfo::~TNHttpGetListGroupInfo()
{

}


void TNHttpGetListGroupInfo::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
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

void TNHttpGetListGroupInfo::GetJson(std::function<void(bool, QJsonObject)> callback, const TNPluginParamPtr &pluginParam, const QString& groupId)
{
	this->checkCallback = callback;

	QJsonObject jsonObject;

	QJsonArray groupFeedArray;
	QJsonObject aGroup;
    aGroup.insert("feedId", groupId);
	aGroup.insert("version", 0);
	groupFeedArray.insert(0, aGroup);

	jsonObject.insert("list", groupFeedArray);

	QJsonDocument document;
	document.setObject(jsonObject);	
	QByteArray dataArray = document.toJson(QJsonDocument::Compact);

	// 基本 URL
	QString baseUrl;
	baseUrl = pluginParam->str_new_group_systoon_com + URL_GetListGroup_Info;
	QUrl url(baseUrl);
    qInfo() << "[NetWorkAPI][TNHttpGetListGroupInfo]-url" << url;
	QNetworkRequest _httpRequest;
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
	post(_httpRequest, url, dataArray);
}
