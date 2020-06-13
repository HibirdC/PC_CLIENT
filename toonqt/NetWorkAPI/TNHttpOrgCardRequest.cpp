#include "TNHttpOrgCardRequest.h"

#include "qdebug.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery> 
#include <QEventLoop>
										

TNHttpOrgCardRequest::TNHttpOrgCardRequest()
{
	
}

TNHttpOrgCardRequest::~TNHttpOrgCardRequest()
{

}

void TNHttpOrgCardRequest::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
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

void TNHttpOrgCardRequest::GetJson(std::function<void(bool, QJsonObject)> callback, const TNPluginParamPtr &pluginParam, bool bAccept)
{
	this->checkCallback = callback;

	QJsonObject jsonObject;
	jsonObject.insert("feedId", _feedId);

	QJsonDocument document;
	document.setObject(jsonObject);	
	QByteArray dataArray = document.toJson(QJsonDocument::Compact);

	// »ù±¾ URL
	QString baseUrl;
	if(bAccept)
		baseUrl = pluginParam->str_new_org_systoon_com + URL_ACCEPTOrgCARD_REQUEST;
	else
		baseUrl = pluginParam->str_new_org_systoon_com + URL_REFUSEOrgCARD_REQUEST;

	QUrl url(baseUrl);
    qInfo() << "[NetWorkAPI][TNHttpObtainGroupMembersByGroupId]-url=" << url;
	QNetworkRequest _httpRequest;
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));

	post(_httpRequest, url, dataArray);
}

void TNHttpOrgCardRequest::SetOrgCardFeedId(QString& feedId)
{
	this->_feedId = feedId;
}
