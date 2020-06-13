﻿#include "TNHttpGetListRelationItem.h"

#include "qdebug.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery> 
#include <QEventLoop>
										

TNHttpGetListRelationItem::TNHttpGetListRelationItem()
{
	
}

TNHttpGetListRelationItem::~TNHttpGetListRelationItem()
{

}


void TNHttpGetListRelationItem::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
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

void TNHttpGetListRelationItem::GetJson(std::function<void(bool, QJsonObject)> callback, const TNPluginParamPtr &pluginParam, const QString & version)
{
	this->checkCallback = callback;
	// »ù±¾ URL
	QString baseUrl = pluginParam->str_new_card_systoon_com + URL_LIST_RELATION_ITEM;
	QUrl url(baseUrl);
	QUrlQuery query;
	query.addQueryItem("version", version);
	query.addQueryItem("userId", pluginParam->strTnUserID);
	url.setQuery(query);
	qDebug() << url;
	QNetworkRequest _httpRequest;
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
	get(_httpRequest, url);
}
