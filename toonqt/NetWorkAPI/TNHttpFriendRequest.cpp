#include "TNHttpFriendRequest.h"

#include "qdebug.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery> 
#include <QEventLoop>
										

TNHttpFriendRequest::TNHttpFriendRequest()
{
	
}

TNHttpFriendRequest::~TNHttpFriendRequest()
{

}


void TNHttpFriendRequest::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
{
	if (statusCode == 200) 
	{
		QJsonParseError jsonError;
		QJsonObject jsonObject = QJsonDocument::fromJson(data, &jsonError).object();
		if (jsonError.error == QJsonParseError::NoError) 
		{
            this->checkCallback(true, m_replyToFeedId.take(reply), jsonObject);
			return;
		}
	}
	QJsonObject jsonObject;
    this->checkCallback(false, m_replyToFeedId.take(reply), jsonObject);
}

void TNHttpFriendRequest::GetJson(std::function<void(bool, QString, QJsonObject)> callback,
                                  const TNPluginParamPtr &pluginParam, bool bAccept)
{
	this->checkCallback = callback;

	QJsonObject jsonObject;
	jsonObject.insert("feedId", _feedId);
	jsonObject.insert("friendFeedId", _friendFeedId);
	jsonObject.insert("friendTitle", _friendTitle);
	jsonObject.insert("friendUserId", _friendUserId);
	jsonObject.insert("title", _feedTitle);
	QJsonDocument document;
	document.setObject(jsonObject);	
	QByteArray dataArray = document.toJson(QJsonDocument::Compact);

	// 基本 URL
	QString baseUrl;
	if(bAccept)
		baseUrl = pluginParam->str_new_contact_systoon_com + URL_ACCEPTFRIEND_REQUEST;
	else
		baseUrl = pluginParam->str_new_contact_systoon_com + URL_REFUSEFRIEND_REQUEST;
	QUrl url(baseUrl);
    qInfo() << "[NetWorkAPI][TNHttpFeedBack] url=" << url;
	QNetworkRequest _httpRequest;
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
    QNetworkReply *reply = post(_httpRequest, url, dataArray);
    m_replyToFeedId[reply] = _friendFeedId;
}

void TNHttpFriendRequest::SetFriendInfo(QString& mineFeedId, QString& friendFeedId, QString& friendTitle, QString& friendUserId, QString& mineFeedTitle)
{
    this->_feedId = mineFeedId;
	this->_friendFeedId = friendFeedId;
	this->_friendTitle = friendTitle;
	this->_friendUserId = friendUserId;
    this->_feedTitle = mineFeedTitle;
}
