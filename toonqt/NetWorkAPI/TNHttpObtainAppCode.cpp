#include "TNHttpObtainAppCode.h"

#include "qdebug.h"
#include "TNVersionInfo.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery> 


TNHttpObtainAppCode::TNHttpObtainAppCode()
{

}

TNHttpObtainAppCode::~TNHttpObtainAppCode()
{

}

void TNHttpObtainAppCode::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
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

void TNHttpObtainAppCode::GetJson(std::function<void(bool, QString, QJsonObject)> callback, const TNPluginParamPtr &pluginParam,
	const QString &appId, const QString &frame, const QString &companyId_owner, const QString &feedId_owner, const QString &userId_visitor, const QString &feedId_visitor)
{
	this->checkCallback = callback;

	QString baseUrl = pluginParam->str_api_app_systoon_com + URL_GETAPPCODE_TEXT;
	QUrl url(baseUrl);

	QJsonObject json;
	json.insert("frame", frame);
    json.insert("toon_type", APPTYPE);

	QJsonObject ownerJson;
	ownerJson.insert("company_id", companyId_owner);
	ownerJson.insert("feed_id", feedId_owner);
	json.insert("owner", ownerJson);

	QJsonObject visitorJson;
	visitorJson.insert("user_id", userId_visitor);
	visitorJson.insert("feed_id", feedId_visitor);
	json.insert("visitor", visitorJson);

	qint64 timestamp = QDateTime::currentMSecsSinceEpoch();
	json.insert("timestamp", QString::number(timestamp));

	QJsonDocument document;
	document.setObject(json);
	QByteArray plainText = document.toJson(QJsonDocument::Compact);
	//QString plainText = QJsonDocument(json).toJson(QJsonDocument::Compact);

	QUrlQuery query; 
	query.addQueryItem("appId", appId);
	query.addQueryItem("plainText", plainText); 
	url.setQuery(query);
	QNetworkRequest _httpRequest;
    qInfo() << "[NetWorkAPI][TNHttpObtainAppCode]-url=" << url;
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
    QNetworkReply *reply = get(_httpRequest, url);
    m_replyToFeedId[reply] = feedId_owner;
}
