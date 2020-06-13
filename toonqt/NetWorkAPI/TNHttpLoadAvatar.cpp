#include "TNHttpLoadAvatar.h"

#include "qdebug.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery> 
#include <QEventLoop>
#include <QPixmap>
#include <QWidget>
										

TNHttpLoadAvatar::TNHttpLoadAvatar()
{
	
}

TNHttpLoadAvatar::~TNHttpLoadAvatar()
{

}


void TNHttpLoadAvatar::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
{
	if (statusCode == 200) 
	{
		QPixmap pixmap;
		pixmap.loadFromData(data);
		pixmap.save(_SavePath, "PNG");
		this->checkCallback(true, data);
		return;
	}
	QByteArray jsonData;
	this->checkCallback(false, jsonData);
}

void TNHttpLoadAvatar::GetJson(std::function<void(bool, QByteArray)> callback, const TNPluginParamPtr &pluginParam, const QString & URL, const QString &SavePath)
{
	this->checkCallback = callback;
	QString baseUrl = URL;
	_SavePath = SavePath;
	// »ù±¾ URL
	//baseUrl.replace("http://" + URL_TOON_SCLOUD_SYSTOON_COM, pluginParam->str_toon_scloud_systoon_com);
	QUrl url(baseUrl);
	QNetworkRequest _httpRequest;
	qDebug() << url;
	//_httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
	//_httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
	//_httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
	//_httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
	get(_httpRequest, url);
}