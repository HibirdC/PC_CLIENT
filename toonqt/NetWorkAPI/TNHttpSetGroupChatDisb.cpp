#include "TNHttpSetGroupChatDisb.h"

#include "qdebug.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery> 
#include <QEventLoop>
										

TNHttpSetGroupChatDisb::TNHttpSetGroupChatDisb() :_bDisturbStatus(0)
{
	
}

TNHttpSetGroupChatDisb::~TNHttpSetGroupChatDisb()
{

}


void TNHttpSetGroupChatDisb::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
{
	if (statusCode == 200) {
		QJsonParseError jsonError;
		QJsonObject jsonObject = QJsonDocument::fromJson(data, &jsonError).object();
		if (jsonError.error == QJsonParseError::NoError) {
            this->checkCallback(true, jsonObject,_extern_params[reply]);
			return;
		}
	}
	QJsonObject jsonObject;
    this->checkCallback(false, jsonObject,_extern_params[reply]);
}

void TNHttpSetGroupChatDisb::GetJson(std::function<void(bool, QJsonObject,std::vector<QVariant>)> callback, const TNPluginParamPtr &pluginParam,const std::vector<QVariant>& extern_params)
{
	this->checkCallback = callback;

	QJsonObject jsonObject;
	int status = _bDisturbStatus;
	jsonObject.insert("disturbStatus", status);
	jsonObject.insert("feedId", _feedId);
	jsonObject.insert("groupChatId", _groupChatId);
	QJsonDocument document;
	document.setObject(jsonObject);	
	QByteArray dataArray = document.toJson(QJsonDocument::Compact);

	// 基本 URL
	QString baseUrl = pluginParam->str_api_new_groupchat_systoon_com + URL_SETGROUPCHAT_DISTURB;
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

void TNHttpSetGroupChatDisb::SetDisturb(bool disturbStatus,const QString& feedId,const QString& groupChatId)
{
	this->_bDisturbStatus = disturbStatus;
	this->_feedId = feedId;
	if (groupChatId.startsWith("gc_")){
		this->_groupChatId = groupChatId.mid(3);
	}
	else{
		this->_groupChatId = groupChatId;
	}
}
