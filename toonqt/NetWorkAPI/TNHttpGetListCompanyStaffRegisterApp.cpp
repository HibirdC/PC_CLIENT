#include "TNHttpGetListCompanyStaffRegisterApp.h"

#include "qdebug.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery> 

TNHttpGetListCompanyStaffRegisterApp::TNHttpGetListCompanyStaffRegisterApp()
{

}

TNHttpGetListCompanyStaffRegisterApp::~TNHttpGetListCompanyStaffRegisterApp()
{

}

void TNHttpGetListCompanyStaffRegisterApp::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
{
	if (statusCode == 200)
	{
		QJsonParseError jsonError;
		QJsonObject jsonObject = QJsonDocument::fromJson(data, &jsonError).object();
		if (jsonError.error == QJsonParseError::NoError)
		{
            this->getAppCallback(true, m_replyToFeedId.take(reply), m_replyToCompanyId.take(reply), jsonObject);
			return;
		}
	}
	QJsonObject jsonObject;
    this->getAppCallback(false, m_replyToFeedId.take(reply), m_replyToCompanyId.take(reply), jsonObject);
}

void TNHttpGetListCompanyStaffRegisterApp::GetJson(std::function<void(bool, QString, QString, QJsonObject)> getAppCallback,
                                                   const TNPluginParamPtr &pluginParam, const QString &companyId, const QString &staffFeedId)
{
	this->getAppCallback = getAppCallback;

	QString baseUrl = pluginParam->str_api_app_systoon_com + URL_LIST_COMPANYSTAFFREGISTERAPP;

	QUrlQuery query;
	query.addQueryItem("companyId", companyId);
	query.addQueryItem("staffFeedId", staffFeedId);

	QUrl url(baseUrl);
	url.setQuery(query);
    qInfo() << "[NetWorkAPI][TNHttpGetListCardRegisterApp]-url=" << url;
	QNetworkRequest _httpRequest;
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
	QNetworkReply *reply = get(_httpRequest, url);
    m_replyToFeedId[reply] = staffFeedId;
    m_replyToCompanyId[reply] = companyId;
}
