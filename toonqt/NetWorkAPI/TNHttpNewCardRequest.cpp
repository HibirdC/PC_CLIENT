#include "TNHttpNewCardRequest.h"

#include "qdebug.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery> 
#include <QEventLoop>
										

TNHttpNewCardRequest::TNHttpNewCardRequest()
{
	
}

TNHttpNewCardRequest::~TNHttpNewCardRequest()
{

}

void TNHttpNewCardRequest::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
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

void TNHttpNewCardRequest::GetJson(std::function<void(bool, QJsonObject)> callback, const TNPluginParamPtr &pluginParam, bool bAccept)
{
	this->checkCallback = callback;

	QJsonObject jsonObject;
	jsonObject.insert("feedId", _feedId);
	jsonObject.insert("userId", _userId);

	QJsonDocument document;
	document.setObject(jsonObject);	
	QByteArray dataArray = document.toJson(QJsonDocument::Compact);

	// »ù±¾ URL
	QString baseUrl;
	if(bAccept)
		baseUrl = pluginParam->str_new_org_systoon_com + URL_ACCEPTStaffCARD_REQUEST;
	else
		baseUrl = pluginParam->str_new_org_systoon_com + URL_REFUSEStaffCARD_REQUEST;
	QUrl url(baseUrl);
	QNetworkRequest _httpRequest;
    qInfo() << "[NetWorkAPI][TNHttpNewCardRequest] url=" << url;
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
	post(_httpRequest, url, dataArray);
}

void TNHttpNewCardRequest::SetStaffInfo(QString& feedId, QString& userId)
{
	this->_feedId = feedId;
	this->_userId = userId;
}
