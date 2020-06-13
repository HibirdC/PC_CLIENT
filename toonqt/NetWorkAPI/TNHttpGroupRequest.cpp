#include "TNHttpGroupRequest.h"

#include "qdebug.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery> 
#include <QEventLoop>
										

TNHttpGroupRequest::TNHttpGroupRequest()
{
	
}

TNHttpGroupRequest::~TNHttpGroupRequest()
{

}


void TNHttpGroupRequest::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
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

void TNHttpGroupRequest::GetJson(std::function<void(bool, QJsonObject)> callback, const TNPluginParamPtr &pluginParam, bool bAccept)
{
	this->checkCallback = callback;

	QJsonObject jsonObject;
	jsonObject.insert("cardFeedId", _feedId);
	jsonObject.insert("cardName", _feedName);
	jsonObject.insert("cardUserId", _userId);
	jsonObject.insert("feedId", _groupId);
	jsonObject.insert("isDel", bAccept ? 1 : 0);
	QJsonDocument document;
	document.setObject(jsonObject);	
	QByteArray dataArray = document.toJson(QJsonDocument::Compact);

	// »ù±¾ URL
	QString baseUrl;
	baseUrl = pluginParam->str_new_group_systoon_com + URL_ACCEPTJOINGROUP_REQUEST;
	QUrl url(baseUrl);
    qInfo() << "[NetWorkAPI][TNHttpGroupRequest] url=" << url;
	QNetworkRequest _httpRequest;
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
	post(_httpRequest, url, dataArray);
}

void TNHttpGroupRequest::SetGroupReqInfo(QString& feedId, QString& feedName, QString& userId, QString& groupId)
{
	this->_feedId = feedId;
	this->_feedName = feedName;
	this->_userId = userId;
	this->_groupId = groupId;
}
