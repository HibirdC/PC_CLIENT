#include "TNHttpQRCodeKeyGen.h"

#include "qdebug.h"

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
#define ERR_CODE_INVALID   104107	 //二维码失效
#define ERR_CODE_SUCCESS    0        //成功

TNHttpQRCodeKeyGen::TNHttpQRCodeKeyGen(): _strCodeKey("")
{
}

TNHttpQRCodeKeyGen::~TNHttpQRCodeKeyGen()
{
}


void TNHttpQRCodeKeyGen::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
{
	if (reply->url().toString().contains(URL_QRCODEKEY_GEN))
	{
		if (statusCode == 200)
		{
			QJsonParseError jsonError;
			QJsonObject jsonObject = QJsonDocument::fromJson(data, &jsonError).object();
			if (jsonError.error == QJsonParseError::NoError)
			{
				_strCodeKey = jsonObject["data"].toObject().value("qrCodeKey").toString();
				this->_funGetQRCodeKey(true, _strCodeKey);
				return;
			}
		}
		else
			this->_funGetQRCodeKey(false, "");
	}
	else if (reply->url().toString().contains(URL_GETQRCODE_STATUS))
	{
		if (statusCode == 200)
		{
			QJsonParseError jsonError;
			QJsonObject jsonObject = QJsonDocument::fromJson(data, &jsonError).object();
			int resCode = jsonObject["meta"].toObject().value("code").toInt();
			if (resCode == ERR_CODE_INVALID)
			{
				//二维码失效，重新获取二维码
				this->_funGetQRCodeStatus(true, OPERA_INVALIDATE, "", "", "");
			}
			else if (resCode == ERR_CODE_SUCCESS)
			{
				int status = jsonObject["data"].toObject().value("status").toInt();
				if (status == OPERA_SCAN)
				{
					QString mobile = jsonObject["data"].toObject().value("dataMap").toObject().value("mobile").toString();
					this->_funGetQRCodeStatus(true, status, mobile, "", "");
				}
				else if (status == OPERA_LOGIN)
				{
					QString token = jsonObject["data"].toObject().value("dataMap").toObject().value("token").toString();
					QString userid = jsonObject["data"].toObject().value("dataMap").toObject().value("userid").toString();
					QString mobile = jsonObject["data"].toObject().value("dataMap").toObject().value("mobile").toString();
					this->_funGetQRCodeStatus(true, status, token, userid, mobile);
				}
			}
		}
		else
			this->_funGetQRCodeStatus(false, -1, "", "", "");
	}
	else if (reply->url().toString().contains(URL_GETQRCODE))
	{
		if (statusCode == 200)
		{
			QString saveFile = TNPathUtil::getScanCodePath() + _strCodeKey;
			QFile file(saveFile);
			if (file.open(QIODevice::WriteOnly))
			{
				file.write(data);
				file.close();
				this->_funGetQRCodePic(true, saveFile);
			}
			else
			{
				qDebug() << file.error();
				qDebug() << file.errorString();
			}
		}
		else
			this->_funGetQRCodePic(false, "");
	}
	else if (reply->url().toString().contains(URL_CANCEL_QRCODE_LOGIN))
	{
		if (statusCode == 200)
			this->_funCancelQRLogin(true, "");
		else
			this->_funCancelQRLogin(false, "");
	}
	
}

void TNHttpQRCodeKeyGen::GetQRCodeKey(std::function<void(bool, QString)> callback, const TNPluginParamPtr &pluginParam)
{
	this->_funGetQRCodeKey = callback;
	QString baseUrl = pluginParam->str_new_user_systoon_com + URL_QRCODEKEY_GEN;
	QUrl url(baseUrl);
	qDebug() << url;
	QNetworkRequest _httpRequest;
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), "1");
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), "1");
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
	get(_httpRequest, url);
}

void TNHttpQRCodeKeyGen::GetQRCodeInfo(std::function<void(bool, QString)> callback, const TNPluginParamPtr &pluginParam)
{
	this->_funGetQRCodePic = callback;
	QJsonObject jsonObject;
	jsonObject.insert("qrCodeKey", _strCodeKey);
	QJsonDocument document;
	document.setObject(jsonObject);
	QByteArray dataArray = document.toJson(QJsonDocument::Compact);
	QString baseUrl = pluginParam->str_new_user_systoon_com + URL_GETQRCODE;
	QUrl url(baseUrl);
	qDebug() << url;
	QNetworkRequest _httpRequest;
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), "1");
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), "1");
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
	post(_httpRequest, url, dataArray);
}

void TNHttpQRCodeKeyGen::GetQRCodeStatus(std::function<void(bool, int, QString, QString, QString)> callback, const TNPluginParamPtr& pluginParam)
{
	this->_funGetQRCodeStatus = callback;
	QJsonObject jsonObject;
	jsonObject.insert("qrCodeKey", _strCodeKey);
	QJsonDocument document;
	document.setObject(jsonObject);
	QByteArray dataArray = document.toJson(QJsonDocument::Compact);
	QString baseUrl = pluginParam->str_new_user_systoon_com + URL_GETQRCODE_STATUS;
	QUrl url(baseUrl);
	qDebug() << url;
	QNetworkRequest _httpRequest;
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), "1");
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), "1");
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
	post(_httpRequest, url, dataArray);

}

void TNHttpQRCodeKeyGen::CancelQRCodeLogin(std::function<void(bool, QString)> callback, const TNPluginParamPtr& pluginParam)
{
	this->_funCancelQRLogin = callback;
	QJsonObject jsonObject;
	jsonObject.insert("qrCodeKey", _strCodeKey);
	QJsonDocument document;
	document.setObject(jsonObject);
	QByteArray dataArray = document.toJson(QJsonDocument::Compact);
	QString baseUrl = pluginParam->str_new_user_systoon_com + URL_CANCEL_QRCODE_LOGIN;
	QUrl url(baseUrl);
	qDebug() << url;
	QNetworkRequest _httpRequest;
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), "1");
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), "1");
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
	post(_httpRequest, url, dataArray);

}