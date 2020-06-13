#include "TNHttpGetOrgCommunicationStatus.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery> 
#include <QEventLoop>

TNHttpGetOrgCommunicationStatus::TNHttpGetOrgCommunicationStatus()
{

}

TNHttpGetOrgCommunicationStatus::~TNHttpGetOrgCommunicationStatus()
{

}
void TNHttpGetOrgCommunicationStatus::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
{
	if (statusCode == 200)
	{
		QJsonParseError jsonError;
		QJsonObject jsonObject = QJsonDocument::fromJson(data, &jsonError).object();
		if (jsonError.error == QJsonParseError::NoError)
		{
			this->checkCallback(true, m_extParamMap[reply], jsonObject);
			return;
		}
	}
	QJsonObject jsonObject;
	this->checkCallback(false, m_extParamMap[reply], jsonObject);
}

void TNHttpGetOrgCommunicationStatus::GetJson(std::function<void(bool, bool, QJsonObject)> callback, const TNPluginParamPtr &pluginParam, const QSet<QString> & feedList, bool refreshCatche)
{
	this->checkCallback = callback;

	QJsonArray json;
	for (int i = 0; i < feedList.size(); i++)
	{
		json.insert(i, feedList.toList()[i]);
	}

	QJsonObject jsonObject;
	jsonObject.insert("feedIDList", json);
	QJsonDocument document;
	document.setObject(jsonObject);
	QByteArray dataArray = document.toJson(QJsonDocument::Compact);

	// »ù±¾ URL
	QString baseUrl = pluginParam->str_new_org_systoon_com + URL_COMPANYINFO_ORGCOMM;
	QUrl url(baseUrl);
	qInfo() << "[NetWorkAPI][TNHttpGetOrgCommunicationStatus] url=" << url;
	QNetworkRequest _httpRequest;
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
	QNetworkReply * reply = post(_httpRequest, url, dataArray);
	m_extParamMap.insert(reply, refreshCatche);
}
