#include "TNHttpFeedBack.h"

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
#include "TNVersionInfo.h"
TNHttpFeedBack::TNHttpFeedBack()
    : m_reply(nullptr)
{
}

TNHttpFeedBack::~TNHttpFeedBack()
{

}


void TNHttpFeedBack::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
{
    QJsonObject jsonObject;
    if (statusCode == 200)
    {
        qInfo()<<"[NetWorkAPI][TNHttpFeedBack]-data="<<data;
        QJsonParseError jsonError;
        QJsonObject jsonObject = QJsonDocument::fromJson(data, &jsonError).object();
        if (jsonError.error == QJsonParseError::NoError)
        {
            this->m_callBack(true, jsonObject);
            return;
        }
    }
    this->m_callBack(false, jsonObject);
}

void TNHttpFeedBack::FeedBack(
    std::function<void(bool, QJsonObject)> callback,
    const TNPluginParamPtr &pluginParam,
    const QString& title, 
    const QString& issueType,
    const QString& issueDescrition,
    const QString& card_num,
    const QString& phone_num
    )
{
	this->m_callBack = callback;

	QJsonObject jsonObject;
    jsonObject.insert("userId", pluginParam->strTnUserID.toStdString().c_str());
    jsonObject.insert("issueType", issueType);
	jsonObject.insert("issueDescripition", issueDescrition);//issueDescripition单词拼错了，多谢了一个i
	jsonObject.insert("cardNum", card_num);
    jsonObject.insert("title", title);
	jsonObject.insert("phoneNum", phone_num);
	jsonObject.insert("toonType", APPTYPE);
	jsonObject.insert("logUrl", "");
    jsonObject.insert("phoneType", QSysInfo::prettyProductName());

	QJsonDocument document;
	document.setObject(jsonObject);	
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);

	// 基本 URL
	QString baseUrl;
	baseUrl = URL_FEEDBACK;
	QUrl url(baseUrl);
	QNetworkRequest _httpRequest;
    qInfo() << "[NetWorkAPI][TNHttpFeedBack]::FeedBack-url=" << url;
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
	_httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
	post(_httpRequest, url, dataArray);
}
