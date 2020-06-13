#include "TNHttpGetListOrgCard.h"

#include "qdebug.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery> 


TNHttpGetListOrgCard::TNHttpGetListOrgCard()
{

}

TNHttpGetListOrgCard::~TNHttpGetListOrgCard()
{

}

void TNHttpGetListOrgCard::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
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

void TNHttpGetListOrgCard::GetJson(std::function<void(bool, QString, QJsonObject)> callback, const TNPluginParamPtr &pluginParam,
                                   const QString &staffFeedId, const QStringList &feedids)
{
	this->checkCallback = callback;

	QString baseUrl = pluginParam->str_new_org_systoon_com + URL_LIST_ORG_CARD;
	QUrl url(baseUrl);
	QUrlQuery query;
	query.addQueryItem("feedIdStr", feedids.join(QChar(',')));
	url.setQuery(query);

    qInfo() << "[NetWorkAPI][TNHttpGetListOrgCard]-url=" << url;
	QNetworkRequest _httpRequest;
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
    QNetworkReply *reply = get(_httpRequest, url);
    m_replyToFeedId[reply] = staffFeedId;
}
