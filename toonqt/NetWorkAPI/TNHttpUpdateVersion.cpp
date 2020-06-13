#include "TNHttpUpdateVersion.h"

#include "TNUpgradePlatform.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery> 
#include <QEventLoop>
#include <QPixmap>
#include <QWidget>
#include <QCoreApplication>						
#include <QDir>

#include "TNPathUtil.h"
#define	INSTALLFILE		"toon.zip"
TNHttpUpdateVersion::TNHttpUpdateVersion() : _url(""), _reply(0)
{
}

TNHttpUpdateVersion::~TNHttpUpdateVersion()
{

}


void TNHttpUpdateVersion::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
{
	if (reply->url().toString().contains(URL_CHECKNEW_VERION))
	{
		if (statusCode == 200)
		{
			QJsonParseError jsonError;
			QJsonObject jsonObject = QJsonDocument::fromJson(data, &jsonError).object();
			if (jsonError.error == QJsonParseError::NoError)
			{
				this->checkVersionCallback(true, jsonObject);
				return;
			}
		}
        QJsonObject jsonObject;
		this->checkVersionCallback(false, jsonObject);
	}
	else if (reply->url().toString().contains(_url))
	{
		if (statusCode == 200)
		{
			QString installPath = TNPathUtil::getInstallPackageFile() + INSTALLFILE;
            output.close();
			this->downLoadCallBack(true, installPath);
			return;
		}
		else
		{
			QJsonObject jsonObject;
			this->downLoadCallBack(false, "");
		}
		
	}
}

void TNHttpUpdateVersion::CheckNewVersion(std::function<void(bool, QJsonObject)> callback, const TNPluginParamPtr &pluginParam, QString& version)
{
	this->checkVersionCallback = callback;

    QJsonObject jsonObject;
    jsonObject.insert("chNo", TNUpgradePlatform::getPlatformChannelNo());
    jsonObject.insert("platForm", TNUpgradePlatform::getPlatformName());
    jsonObject.insert("version", version);

    QString debugText = QString(QJsonDocument(jsonObject).toJson());
    qDebug()<<"inCheckNewVersion-debugText="<<debugText;

    QJsonDocument document;
    document.setObject(jsonObject);
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);

	QString baseUrl;
    baseUrl = pluginParam->str_cams_systoon_com + URL_CHECKNEW_VERION;
	QUrl url(baseUrl);
    qInfo()<<"[NetWorkAPI][TNHttpUpdateVersion] url=" << url;

	QNetworkRequest _httpRequest;
    _httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
    _httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
    _httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
    _httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
    QNetworkReply *reply = post(_httpRequest, url, dataArray);
}

void TNHttpUpdateVersion::DownLoadNewVersion(std::function<void(bool, QString)> callback, QString& url, QObject& receiver)
{
    QString installPath = TNPathUtil::getInstallPackageFile() + INSTALLFILE;
    output.setFileName(installPath);
    if (!output.open(QIODevice::WriteOnly))
    {
        return;
    }

	this->downLoadCallBack = callback;
	_url = url;
	QNetworkRequest _httpRequest;
	_reply = get(_httpRequest, url);
    connect(_reply, SIGNAL(readyRead()), this, SLOT(downloadReadyRead()));
	connect(_reply, SIGNAL(downloadProgress(qint64, qint64)),
		&receiver, SLOT(On_DownLoadProgress(qint64, qint64)));
}


void TNHttpUpdateVersion::downloadReadyRead()
{
    output.write(_reply->readAll());
}
