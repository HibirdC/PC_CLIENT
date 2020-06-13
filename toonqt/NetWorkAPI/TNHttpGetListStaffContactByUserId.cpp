#include "TNHttpGetListStaffContactByUserId.h"

#include "qdebug.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery> 
#include <QEventLoop>
										

TNHttpGetListStaffContactByUserId::TNHttpGetListStaffContactByUserId()
{
	
}

TNHttpGetListStaffContactByUserId::~TNHttpGetListStaffContactByUserId()
{

}


void TNHttpGetListStaffContactByUserId::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
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

void TNHttpGetListStaffContactByUserId::GetJson(std::function<void(bool, QJsonObject)> callback, const TNPluginParamPtr &pluginParam, const QString & version)
{
	this->checkCallback = callback;
	// 基本 URL
	QString baseUrl = pluginParam->str_new_org_systoon_com + URL_LIST_STAFF_CONTACT_BY_USER_ID;
	QUrl url(baseUrl);
	QUrlQuery query; 
	query.addQueryItem("userId", pluginParam->strTnUserID);
	query.addQueryItem("version", version);
	url.setQuery(query);
    qInfo() <<"[NetWorkAPI][TNHttpGetListStaffContactByUserId]-url" << url;
	QNetworkRequest _httpRequest;
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
	get(_httpRequest, url);
}
