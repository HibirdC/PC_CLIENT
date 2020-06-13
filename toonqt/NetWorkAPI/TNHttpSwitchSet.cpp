#include "TNHttpSwitchSet.h"

#include "qdebug.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery> 
#include <QEventLoop>
#define  BIZ_TYPE_DISTURB   2  										

TNHttpSwitchSet::TNHttpSwitchSet()
{
	
}

TNHttpSwitchSet::~TNHttpSwitchSet()
{

}


void TNHttpSwitchSet::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
{
	if (statusCode == 200) 
	{
		QJsonParseError jsonError;
		QJsonObject jsonObject = QJsonDocument::fromJson(data, &jsonError).object();
		if (jsonError.error == QJsonParseError::NoError) 
		{
            this->checkCallback(true, jsonObject,_extern_params[reply]);
			return;
		}
	}
	QJsonObject jsonObject;
    this->checkCallback(false, jsonObject,_extern_params[reply]);
}

void TNHttpSwitchSet::GetJson(std::function<void(bool, QJsonObject,std::vector<QVariant>)> callback, const TNPluginParamPtr &pluginParam, bool bOn,const std::vector<QVariant>& extern_params)
{
	this->checkCallback = callback;

	QJsonObject jsonObject;
	jsonObject.insert("bizType", BIZ_TYPE_DISTURB);
	jsonObject.insert("feedId", _feedId);
	jsonObject.insert("passiveFeedId", _passiveFeedId);
	jsonObject.insert("passiveUserId", _passiveUserId);
	QJsonDocument document;
	document.setObject(jsonObject);	
	QByteArray dataArray = document.toJson(QJsonDocument::Compact);

	// 基本 URL
	QString baseUrl;
	if (bOn)
		baseUrl = pluginParam->str_new_contact_systoon_com + URL_SWITCH_ON;
	else
		baseUrl = pluginParam->str_new_contact_systoon_com + URL_SWITCH_OFF;
	QUrl url(baseUrl);
	qDebug() << url;
	QNetworkRequest _httpRequest;
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
    QNetworkReply* reply = post(_httpRequest, url, dataArray);
    _extern_params[reply] = extern_params;
}

void TNHttpSwitchSet::SetSwitchInfo(const QString& feedId,const QString& passiveFeedId,const QString& passiveUserId)
{
	this->_feedId = feedId;
	if (passiveFeedId.startsWith("gc_")){
		this->_passiveFeedId = passiveFeedId.mid(3);
	}
	else{
		this->_passiveFeedId = passiveFeedId;
	}
	this->_passiveUserId = passiveUserId;
}
