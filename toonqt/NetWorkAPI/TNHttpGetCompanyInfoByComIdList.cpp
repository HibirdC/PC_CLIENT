#include "TNHttpGetCompanyInfoByComIdList.h"

#include "qdebug.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery> 
#include <QEventLoop>
										

TNHttpGetCompanyInfoByComIdList::TNHttpGetCompanyInfoByComIdList()
{
	
}

TNHttpGetCompanyInfoByComIdList::~TNHttpGetCompanyInfoByComIdList()
{

}


void TNHttpGetCompanyInfoByComIdList::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
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

void TNHttpGetCompanyInfoByComIdList::GetJson(std::function<void(bool, QJsonObject)> callback, const TNPluginParamPtr &pluginParam, const QSet<QString> & comIDList)
{
	this->checkCallback = callback;

	QJsonArray json;
	for (int i = 0; i < comIDList.size(); i++)
	{
		json.insert(i, comIDList.toList()[i]);
	}

	QJsonObject jsonObject;
	jsonObject.insert("comIdList", json);
	QJsonDocument document;
	document.setObject(jsonObject);
	QByteArray dataArray = document.toJson(QJsonDocument::Compact);

	// 基本 URL
	QString baseUrl = pluginParam->str_new_org_systoon_com + URL_COMPANYINFO_BYCOMIDLIST;
	QUrl url(baseUrl);
    qInfo() <<"[NetWorkAPI][TNHttpGetCompanyInfoByComIdList] url=" << url;
	QNetworkRequest _httpRequest;
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
	post(_httpRequest, url, dataArray);
}
