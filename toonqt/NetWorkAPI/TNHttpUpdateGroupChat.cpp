#include "TNHttpUpdateGroupChat.h"

#include "qdebug.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery> 
#include <QEventLoop>
										

TNHttpUpdateGroupChat::TNHttpUpdateGroupChat()
{
	
}

TNHttpUpdateGroupChat::~TNHttpUpdateGroupChat()
{

}


void TNHttpUpdateGroupChat::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
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

void TNHttpUpdateGroupChat::GetJson(std::function<void(bool, QJsonObject,std::vector<QVariant>)> callback,
    const TNPluginParamPtr &pluginParam,
    const std::vector<QVariant> &extern_params)
{
	this->checkCallback = callback;

	QJsonObject jsonObject;
	jsonObject.insert("feedId", _feedId);
	jsonObject.insert("groupChatId", _groupChatId);
	jsonObject.insert("groupChatName", _groupChatName);
	jsonObject.insert("title", _feedTitle);
	QJsonDocument document;
	document.setObject(jsonObject);	
	QByteArray dataArray = document.toJson(QJsonDocument::Compact);

	// 基本 URL
	QString baseUrl = pluginParam->str_api_new_groupchat_systoon_com + URL_UPDATE_GROUPCHAT;
	QUrl url(baseUrl);
    qInfo() << "[NetWorkAPI][TNHttpUpdateGroupChat] url=" << url;
	QNetworkRequest _httpRequest;
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
    QNetworkReply* reply = post(_httpRequest, url, dataArray);
    _extern_params[reply] = extern_params;
}

void TNHttpUpdateGroupChat::SetUpdateInfo(const QString& feedId,const QString& groupChatId,const QString& groupChatTitle,const QString& feedTitle)
{
	if (groupChatId.startsWith("gc_")){
		this->_groupChatId = groupChatId.mid(3);
	}
	else{
		this->_groupChatId = groupChatId;
	}
	this->_feedId = feedId;
	this->_groupChatName = groupChatTitle;
	this->_feedTitle = feedTitle;
}
