#include <QByteArray> 
#include <QEventLoop>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QTimer>
#include <QNetworkConfigurationManager>

#include "TNHttpApi.h"
#include "QJsonArray"
#include "TNVersionInfo.h"
#define HOUR_MAX_CODE  104102
#define DAY_MAX_CODE   104103
TNHttpApi::TNHttpApi()
{
	_networkAccessManager=NULL;
}



TNHttpApi::~TNHttpApi()
{
	
}

void TNHttpApi::setRawHeader(QNetworkRequest & httpRequest)
{
	//httpRequest.setRawHeader(QByteArray("Accept-Encoding"), QByteArray("gzip"));
	httpRequest.setRawHeader(QByteArray("Accept-Language"), QByteArray("en;q=1"));
	httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
	/*httpRequest.setRawHeader(QByteArray("Accept-Encoding"), QByteArray("gzip"));
	httpRequest.setRawHeader(QByteArray("Accept-Language"), QByteArray("zh-Hans-CN;q=1"));
	httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
	httpRequest.setRawHeader(QByteArray("TNDomain"), QByteArray("new.user.systoon.com"));
	httpRequest.setRawHeader(QByteArray("TNDomianRouterVersion"), QByteArray("1488504850405"));
	httpRequest.setRawHeader(QByteArray("TNPath"), QByteArray("user//router/domain"));
	httpRequest.setRawHeader(QByteArray("TNTaskIdentifier"), QByteArray("9B76C859-D8AC-4864-A3CF-43E93E6B50CD"));
	httpRequest.setRawHeader(QByteArray("User-Agent"), QByteArray("toon tong/3.3 (iPhone; iOS 10.0.2; Scale/3.00)" ));
	httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), QByteArray("deviceId:9B76C859-D8AC-4864-A3CF-43E93E6B50CD,ticket:02E2E025D6A8EA217D567734F43FDBAD,userId:305092,appVersion:3.3,platform:iOS,platformVersion:10.0.2,toonType:100,userToken:6d1d7c5e-7602-4ad2-a6cf-fd9ce4eab135"));
	httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), QByteArray("305092"));
	httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), QByteArray("6d1d7c5e-7602-4ad2-a6cf-fd9ce4eab135"));


	settings = new QSettings("XXX");
	QString id = settings->value(SETTING_ACCOUNT_ID, "").toString();
	QString token = settings->value(SETTING_ACCOUNT_TOKEN, "").toString();

	if (!id.isEmpty()) {
	httpRequest.setRawHeader("X-XXX-User-ID", id.toStdString().c_str());
	}

	if (!token.isEmpty()) {
	httpRequest.setRawHeader("X-XXX-User-Token", token.toStdString().c_str());
	}

	qDebug() << "BaseAPI...id:" << id << " token:" + token;*/
}

int TNHttpApi::CheckRegisterBeforeLoginNew(QString strUserID, QString strUserToken, QString strUserAgent,
                                           QString strTeleCode, QString strMobile, QString strUuid)
{
	InitNetWorkManager();
    _networkAccessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);

	int nRet = -1;
	QUrl url(_strUrl + URL_CHECKREGISTERBEFORELOGINNEW);
	QUrlQuery query;
	query.addQueryItem("teleCode", strTeleCode);
	query.addQueryItem("mobile", strMobile);
	query.addQueryItem("uuid", strUuid);
	url.setQuery(query);
	QNetworkRequest httpRequest;
	
	setRawHeader(httpRequest);
	//httpRequest.setRawHeader(QByteArray("Accept-Encoding"), QByteArray("gzip, deflate"));
	//httpRequest.setRawHeader(QByteArray("Accept-Encoding"), QByteArray("deflate"));
	//httpRequest.setRawHeader(QByteArray("Accept-Language"), QByteArray("en;q=1"));
	//httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));

	httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), strUserID.toStdString().c_str());
	httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), strUserToken.toStdString().c_str());
	httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), strUserAgent.toStdString().c_str());
	httpRequest.setRawHeader(QByteArray("TNPath"), URL_CHECKREGISTERBEFORELOGINNEW.toStdString().c_str());
	httpRequest.setUrl(url);
	qDebug() << url;

	QList<QByteArray> temp = httpRequest.rawHeaderList();
	for (int i = 0; i < temp.size(); i++)
	{
		qDebug() << temp[i] << httpRequest.rawHeader(temp[i]);
	}
	sslVerify(httpRequest);
	QNetworkReply* reply = _networkAccessManager->get(httpRequest);
	QEventLoop eventLoop;
	connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
	QTimer::singleShot(1000 * 5, &eventLoop, SLOT(quit()));
	eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
	int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	if (reply->error() == QNetworkReply::NoError) 
	{
		if (statusCode == 200)
		{
			QJsonParseError jsonError;
			QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll(), &jsonError).object();
			if (jsonError.error == QJsonParseError::NoError)
			{
				QString strRet = jsonObject.value("meta").toObject().value("message").toString();
				if (strRet.compare("success") == 0)
				{
					//0 删除 1 正常 2 锁定
					int nAccountState = jsonObject.value("data").toObject().value("accountState").toInt();
                    //bool bChangeDevice = jsonObject.value("data").toObject().value("changeDevice").toBool();
					if (nAccountState == 0)
					{
						//未注册
						nRet = 1;
					}
					else if (nAccountState == 1)
					{
						//正常
						nRet = 2;
					}
					else if (nAccountState == 2)
					{
						//锁定
						nRet = 3;
					}
				}
			}
		}
	}
	else
	{
		qDebug() << "errorString=" << reply->errorString();
	}
	reply->deleteLater();
	reply = nullptr;
	return nRet;
}

int TNHttpApi::sendVCodeBeforeLogin(const TNPluginParamPtr &pluginParam, const QString& strTeleCode, const QString& strMobile, const QString& strType, int retry)
{
	InitNetWorkManager();
    _networkAccessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);

	int nRet = -1;
	QUrl url(pluginParam->str_new_user_systoon_com + URL_SENDVCODEBEFORELOGIN);
	QUrlQuery query;
	query.addQueryItem("teleCode", strTeleCode);
	query.addQueryItem("mobile", strMobile);
	query.addQueryItem("toonType", strType);
	QString strRetry = QString::number(retry);
	//query.addQueryItem("retry", "0");
	url.setQuery(query);
	QNetworkRequest httpRequest;

	setRawHeader(httpRequest);

	httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
	httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
	httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
	httpRequest.setRawHeader(QByteArray("TNPath"), URL_SENDVCODEBEFORELOGIN.toStdString().c_str());
	httpRequest.setUrl(url);
	qDebug() << url;

	QList<QByteArray> temp = httpRequest.rawHeaderList();
	for (int i = 0; i < temp.size(); i++)
	{
		qDebug() << temp[i] << httpRequest.rawHeader(temp[i]);
	}
	sslVerify(httpRequest);
	QNetworkReply* reply = _networkAccessManager->get(httpRequest);
	QEventLoop eventLoop;
	connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
	QTimer::singleShot(1000 * 5, &eventLoop, SLOT(quit()));
	eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
	int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	if (reply->error() == QNetworkReply::NoError)
	{
		if (statusCode == 200)
		{
			QJsonParseError jsonError;
			//QString str = reply->readAll();
			QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll(), &jsonError).object();
			if (jsonError.error == QJsonParseError::NoError)
			{
				QString strRet = jsonObject.value("meta").toObject().value("message").toString();
				int code = jsonObject.value("meta").toObject().value("code").toInt();
				if (strRet.compare("success") == 0)
				{
					QString strRet = jsonObject.value("data").toObject().value("strValue").toString();
					nRet = strRet.toInt();
				}
				else
				{
					if (code == HOUR_MAX_CODE)
						nRet = 1;
					else if (code == DAY_MAX_CODE)
						nRet = 2;
					else
						nRet = 3;
				}
			}
		}
	}
	reply->deleteLater();
	reply = nullptr;
	return nRet;
}

void TNHttpApi::serviceRequestFinished(QNetworkReply *reply)
{
	int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	QString fff = reply->errorString();
	QByteArray sss = reply->readAll();
	QString tttggg = QString::fromStdString(sss.toStdString());
	qDebug() << "BaseAPI...serviceRequestFinished...statusCode:" << statusCode;
    //QNetworkReply::NetworkError ttt = reply->error();

	// At the end of that slot, we won't need it anymore
	reply->deleteLater();
    qDebug() << "serviceRequestFinished reply deleteLater";
}

int TNHttpApi::LoginWithPassword(const QString &strUserID, const QString &strUserToken, QJsonObject &object)
{
	InitNetWorkManager();
	_networkAccessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);

	int nRet = -1;
	QString baseUrl = "http://unilogin.qa.huohua.cn/auth";

	QUrlQuery query;
	query.addQueryItem("mail", strUserID);
	query.addQueryItem("pwd", strUserToken);
	query.addQueryItem("devId", "testdeviceId@lp");
	query.addQueryItem("devType", "2");
	query.addQueryItem("appType", "1");

	QUrl url(baseUrl);
	url.setQuery(query);

	QNetworkRequest httpRequest;
	setRawHeader(httpRequest);
	httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
	httpRequest.setUrl(url);

	qDebug() << "TNHttpApi::Auth-url=" << url;

	QList<QByteArray> temp = httpRequest.rawHeaderList();
	for (int i = 0; i < temp.size(); i++)
	{
		qDebug() << temp[i] << httpRequest.rawHeader(temp[i]);
	}
	sslVerify(httpRequest);
	QNetworkReply* reply = _networkAccessManager->get(httpRequest);
	QEventLoop eventLoop;
	connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
	QTimer::singleShot(1000 * 5, &eventLoop, SLOT(quit()));
	eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
	int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	if (reply->error() == QNetworkReply::NoError)
	{
		if (statusCode == 200)
		{
			QJsonParseError jsonError;
			QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll(), &jsonError).object();
			if (jsonError.error == QJsonParseError::NoError)
			{
				object = jsonObject;
				int ret = jsonObject.value("code").toInt();
				if(ret == 0)
				{
					nRet = 1;
				}
			}
		}
	}
	reply->deleteLater();
	reply = nullptr;
	return nRet;
}
void TNHttpApi::InitNetWorkManager()
{
	if (_networkAccessManager == NULL)
	{
		_networkAccessManager = new QNetworkAccessManager(this);
		QNetworkConfigurationManager manager;
		_networkAccessManager->setConfiguration(manager.defaultConfiguration());
		_networkAccessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);
	}
}
int TNHttpApi::Logout(const TNPluginParamPtr &pluginParam, const st_LoginWithPasswordHttpBody &body, QJsonObject &object)
{
	InitNetWorkManager();
    _networkAccessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);

	int nRet = -1;
	QUrl url(pluginParam->str_new_user_systoon_com + URL_LOGOUT);
	// Json数据
	QJsonObject json;
	json.insert("deviceName", body.strDeviceName);
	json.insert("deviceToken", body.strDeviceToken);
	json.insert("idfa", body.strIdfa);
	json.insert("imei", body.strImei);
	json.insert("macAddress", body.strMacAddress);
	json.insert("uuid", body.strUuid);
	QJsonDocument document;
	document.setObject(json);
	QByteArray dataArray = document.toJson(QJsonDocument::Compact);

	QNetworkRequest httpRequest;
	setRawHeader(httpRequest);
	httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
	httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
	httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
	httpRequest.setUrl(url);

	qDebug() << url;

	QList<QByteArray> temp = httpRequest.rawHeaderList();
	for (int i = 0; i < temp.size(); i++)
	{
		qDebug() << temp[i] << httpRequest.rawHeader(temp[i]);
	}
	sslVerify(httpRequest);
	QNetworkReply* reply = _networkAccessManager->post(httpRequest, dataArray);
	QEventLoop eventLoop;
	connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    QTimer::singleShot(5000, &eventLoop, SLOT(quit()));
	eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
	int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	if (reply->error() == QNetworkReply::NoError)
	{
		if (statusCode == 200)
		{
			QJsonParseError jsonError;
			QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll(), &jsonError).object();
			if (jsonError.error == QJsonParseError::NoError)
			{
				object = jsonObject;
				QString strRet = jsonObject.value("meta").toObject().value("message").toString();
				if (strRet.compare("success") == 0)
				{
					nRet = 0;
				}
			}
		}
        else
        {
            nRet = 0;
        }
	}
	reply->deleteLater();
	reply = nullptr;
	return nRet;
}

int TNHttpApi::LoginWithVCode(const TNPluginParamPtr &pluginParam, const st_LoginWithPasswordHttpBody &body, QJsonObject &object, int *code)
{
	InitNetWorkManager();
    _networkAccessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);

	int nRet = -1;
	QUrl url(pluginParam->str_new_user_systoon_com + URL_LOGINWITHVCODE);
	// Json数据
	QJsonObject json;
	json.insert("deviceName", body.strDeviceName);
	json.insert("deviceToken", body.strDeviceToken);
	json.insert("idfa", body.strIdfa);
	json.insert("imei", body.strImei);
	json.insert("macAddress", body.strMacAddress);
	json.insert("mobile", body.strMobile);
	json.insert("password", body.strPassword);

	json.insert("regLogin", body.bRegLogin);
	json.insert("teleCode", body.strTeleCode);
	json.insert("uuid", body.strUuid);
	QJsonDocument document;
	document.setObject(json);
	QByteArray dataArray = document.toJson(QJsonDocument::Compact);

	QNetworkRequest httpRequest;
	setRawHeader(httpRequest);
	httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
	httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
	httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
	httpRequest.setUrl(url);

	qDebug() << url;

	QList<QByteArray> temp = httpRequest.rawHeaderList();
	for (int i = 0; i < temp.size(); i++)
	{
		qDebug() << temp[i] << httpRequest.rawHeader(temp[i]);
	}
	sslVerify(httpRequest);
	QNetworkReply* reply = _networkAccessManager->post(httpRequest, dataArray);
	QEventLoop eventLoop;
	connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
	QTimer::singleShot(1000 * 5, &eventLoop, SLOT(quit()));
	eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
	int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	if (reply->error() == QNetworkReply::NoError)
	{
		if (statusCode == 200)
		{
			QJsonParseError jsonError;
			QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll(), &jsonError).object();
			if (jsonError.error == QJsonParseError::NoError)
			{
				object = jsonObject;
                QString debugText = QJsonDocument(jsonObject).toJson();
                qDebug()<<"TNHttpApi::LoginWithVCode-debugText="<<debugText;
                if (code)
                    *code = jsonObject.value("meta").toObject().value("code").toInt();
				QString strRet = jsonObject.value("meta").toObject().value("message").toString();
				if (strRet.compare("success") == 0)
				{
					QString strStatus = jsonObject.value("data").toObject().value("status").toString();
					nRet = strStatus.toInt();
				}
			}
		}
	}
	reply->deleteLater();
	reply = nullptr;
	return nRet;
}

int TNHttpApi::GetFeedList(const TNPluginParamPtr &pluginParam, const QStringList &feedIds, QJsonObject &object)
{
	InitNetWorkManager();
    _networkAccessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);

    int nRet = -1;
    QUrl url(pluginParam->str_api_feed_systoon_com + URL_OBTAIN_FEED_LIST);
    // Json数据
    QJsonArray json;
    for (int i = 0; i < feedIds.size(); i++)
    {
        json.insert(i, feedIds[i]);
    }

    QJsonObject jsonObject;
    jsonObject.insert("feedId", "");
    jsonObject.insert("feedIds", json);
    QJsonDocument document;
    document.setObject(jsonObject);
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);

    QNetworkRequest httpRequest;
    setRawHeader(httpRequest);
    httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
    httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
    httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
    httpRequest.setUrl(url);

    qDebug() << url;

    QList<QByteArray> temp = httpRequest.rawHeaderList();
    for (int i = 0; i < temp.size(); i++)
    {
        qDebug() << temp[i] << httpRequest.rawHeader(temp[i]);
    }
    sslVerify(httpRequest);
    QNetworkReply* reply = _networkAccessManager->post(httpRequest, dataArray);
    QEventLoop eventLoop;
    connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    QTimer::singleShot(1000*5, &eventLoop, SLOT(quit()));
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (reply->error() == QNetworkReply::NoError)
    {
        if (statusCode == 200)
        {
            QJsonParseError jsonError;
            QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll(), &jsonError).object();
            if (jsonError.error == QJsonParseError::NoError)
            {
                object = jsonObject;
                QString strRet = jsonObject.value("meta").toObject().value("message").toString();
                if (strRet.compare("success") == 0)
                {
                    nRet = 0;
                }
            }
        }
    }
    reply->deleteLater();
    reply = nullptr;
    return nRet;
}

int TNHttpApi::GetGroupChatMembers(const TNPluginParamPtr &pluginParam, const QString &groupChatId, QJsonObject &object)
{
	InitNetWorkManager();
    _networkAccessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);

    Q_ASSERT(!groupChatId.startsWith("gc_"));
    int nRet = -1;

    QString baseUrl = pluginParam->str_api_new_groupchat_systoon_com + URL_OBTAIN_GROUPCHATMEMBERS_BYGROUPCHATID;

    QUrlQuery query;
    query.addQueryItem("groupChatId", groupChatId);

    QUrl url(baseUrl);
    url.setQuery(query);

    QNetworkRequest httpRequest;
    setRawHeader(httpRequest);
    httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
    httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
    httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
    httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
    httpRequest.setUrl(url);

    qDebug() << "TNHttpApi::GetGroupChatMembers-url=" << url;

    QList<QByteArray> temp = httpRequest.rawHeaderList();
    for (int i = 0; i < temp.size(); i++)
    {
        qDebug() << temp[i] << httpRequest.rawHeader(temp[i]);
    }
    sslVerify(httpRequest);
    QNetworkReply* reply = _networkAccessManager->get(httpRequest);
    QEventLoop eventLoop;
    connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
	QTimer::singleShot(1000 * 5, &eventLoop, SLOT(quit()));
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (reply->error() == QNetworkReply::NoError)
    {
        if (statusCode == 200)
        {
            QJsonParseError jsonError;
            QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll(), &jsonError).object();
            if (jsonError.error == QJsonParseError::NoError)
            {
                object = jsonObject;
                QString strRet = jsonObject.value("meta").toObject().value("message").toString();
                if (strRet.compare("success") == 0)
                {
                    nRet = 0;
                }
            }
        }
    }
    reply->deleteLater();
    reply = nullptr;
    return nRet;
}

int TNHttpApi::GetListCard(const TNPluginParamPtr &pluginParam, const QStringList &feedids, QJsonObject &object)
{
	InitNetWorkManager();
    _networkAccessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);

	int nRet = -1;
	QUrl url(pluginParam->str_new_card_systoon_com + URL_GETLISTCARD);
	// Json数据
	QJsonArray json;
	for (int i = 0; i < feedids.size(); i++)
	{
		json.insert(i, feedids[i]);
	}

	QJsonObject jsonObject;
	jsonObject.insert("feedIdList", json);
	QJsonDocument document;
	document.setObject(jsonObject);
	QByteArray dataArray = document.toJson(QJsonDocument::Compact);

	QNetworkRequest httpRequest;
	setRawHeader(httpRequest);
	httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
	httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
	httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
	httpRequest.setUrl(url);

    //qDebug() << "TNHttpApi::GetListCard-strTnUserID=" << pluginParam->strTnUserID;
    //qDebug() << "TNHttpApi::GetListCard-strTnUserToken=" << pluginParam->strTnUserToken;
    //qDebug() << "TNHttpApi::GetListCard-strTnUserAgent=" << pluginParam->strTnUserAgent;
    qDebug() << "TNHttpApi::GetListCard-url=" << url;

	QList<QByteArray> temp = httpRequest.rawHeaderList();
	for (int i = 0; i < temp.size(); i++)
	{
		qDebug() << temp[i] << httpRequest.rawHeader(temp[i]);
	}
	sslVerify(httpRequest);
	QNetworkReply* reply = _networkAccessManager->post(httpRequest, dataArray);
	QEventLoop eventLoop;
	connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    QTimer::singleShot(1000*5, &eventLoop, SLOT(quit()));
	eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
	int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	if (reply->error() == QNetworkReply::NoError)
	{
		if (statusCode == 200)
		{
			QJsonParseError jsonError;
			QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll(), &jsonError).object();
			if (jsonError.error == QJsonParseError::NoError)
			{
				object = jsonObject;
				QString strRet = jsonObject.value("meta").toObject().value("message").toString();
				if (strRet.compare("success") == 0)
				{
					nRet = 0;
				}
			}
		}
	}
	reply->deleteLater();
	reply = nullptr;
	return nRet;
}

int TNHttpApi::GetListStaffCard(const TNPluginParamPtr &pluginParam, const QString &feedids, QJsonObject &object)
{
	InitNetWorkManager();
    _networkAccessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);

	int nRet = -1;
	QUrl url(pluginParam->str_new_org_systoon_com + URL_LIST_STAFF_CARD);
	// Json数据
	QUrlQuery query;
	query.addQueryItem("feedIdStr", feedids);
	url.setQuery(query);

	QNetworkRequest httpRequest;
	setRawHeader(httpRequest);
	httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
	httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
	httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
	httpRequest.setUrl(url);

    qDebug() << "TNHttpApi::GetListStaffCard-url=" << url;

	QList<QByteArray> temp = httpRequest.rawHeaderList();
	for (int i = 0; i < temp.size(); i++)
	{
		qDebug() << temp[i] << httpRequest.rawHeader(temp[i]);
	}
	sslVerify(httpRequest);
	QNetworkReply* reply = _networkAccessManager->get(httpRequest);
	QEventLoop eventLoop;
	connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    QTimer::singleShot(1000*5, &eventLoop, SLOT(quit()));
	eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
	int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	if (reply->error() == QNetworkReply::NoError)
	{
		if (statusCode == 200)
		{
			QJsonParseError jsonError;
			QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll(), &jsonError).object();
			if (jsonError.error == QJsonParseError::NoError)
			{
				object = jsonObject;
				QString strRet = jsonObject.value("meta").toObject().value("message").toString();
				if (strRet.compare("success") == 0)
				{
					nRet = 0;
				}
			}
		}
	}
	reply->deleteLater();
	reply = nullptr;
	return nRet;
}

int TNHttpApi::GetListOrgCard(const TNPluginParamPtr &pluginParam, const QString &feedids, QJsonObject &object)
{
	InitNetWorkManager();
    _networkAccessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);

	int nRet = -1;
	QUrl url(pluginParam->str_new_org_systoon_com + URL_LIST_ORG_CARD);
	// Json数据
	QUrlQuery query;
	query.addQueryItem("feedIdStr", feedids);
	url.setQuery(query);

	QNetworkRequest httpRequest;
	setRawHeader(httpRequest);
	httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
	httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
	httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
	httpRequest.setUrl(url);

    qDebug() <<"TNHttpApi::GetListOrgCard-url="  << url;

	QList<QByteArray> temp = httpRequest.rawHeaderList();
	for (int i = 0; i < temp.size(); i++)
	{
		qDebug() << temp[i] << httpRequest.rawHeader(temp[i]);
	}
	sslVerify(httpRequest);
	QNetworkReply* reply = _networkAccessManager->get(httpRequest);
	QEventLoop eventLoop;
	connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    QTimer::singleShot(1000*5, &eventLoop, SLOT(quit()));
	eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
	int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	if (reply->error() == QNetworkReply::NoError)
	{
		if (statusCode == 200)
		{
			QJsonParseError jsonError;
			QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll(), &jsonError).object();
			if (jsonError.error == QJsonParseError::NoError)
			{
				object = jsonObject;
				QString strRet = jsonObject.value("meta").toObject().value("message").toString();
				if (strRet.compare("success") == 0)
				{
					nRet = 0;
				}
			}
		}
	}
	reply->deleteLater();
	reply = nullptr;
    return nRet;
}

int TNHttpApi::GetListGroup(const TNPluginParamPtr &pluginParam, const QStringList &feedids, QJsonObject &object)
{
	InitNetWorkManager();
    _networkAccessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);

    int nRet = -1;
    QUrl url(pluginParam->str_new_group_systoon_com + URL_GetListGroup_Info);

    // Json数据
    QJsonObject jsonObject;
    QJsonArray groupFeedArray;
    for (QStringList::size_type i=0; i<feedids.size(); ++i)
    {
        QJsonObject aGroup;
        aGroup.insert("feedId", feedids.at(i));
        aGroup.insert("version", 0);
        groupFeedArray.insert(i, aGroup);
    }
    jsonObject.insert("list", groupFeedArray);

    QJsonDocument document;
    document.setObject(jsonObject);
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);

    QNetworkRequest httpRequest;
    setRawHeader(httpRequest);
    httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
    httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
    httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
    httpRequest.setUrl(url);

    qDebug() <<"TNHttpApi::GetListGroup-url=" << url;

    QList<QByteArray> temp = httpRequest.rawHeaderList();
    for (int i = 0; i < temp.size(); i++)
    {
        qDebug() << temp[i] << httpRequest.rawHeader(temp[i]);
    }
    sslVerify(httpRequest);
    QNetworkReply* reply =  _networkAccessManager->post(httpRequest, dataArray);
    QEventLoop eventLoop;
    connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    QTimer::singleShot(1000*5, &eventLoop, SLOT(quit()));
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (reply->error() == QNetworkReply::NoError)
    {
        if (statusCode == 200)
        {
            QJsonParseError jsonError;
            QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll(), &jsonError).object();
            if (jsonError.error == QJsonParseError::NoError)
            {
                object = jsonObject;
                QString strRet = jsonObject.value("meta").toObject().value("message").toString();
                if (strRet.compare("success") == 0)
                {
                    nRet = 0;
                }
            }
        }
    }
    reply->deleteLater();
    reply = nullptr;
    return nRet;
}

int TNHttpApi::GetCompanyInfoByComId(const TNPluginParamPtr &pluginParam, const QString &comId, QJsonObject &object)
{
	InitNetWorkManager();
    _networkAccessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);

	int nRet = -1;
	QUrl url(pluginParam->str_new_org_systoon_com + URL_COMPANYINFO_BYCOMID);

	QUrlQuery query;
	query.addQueryItem("comId", comId);
	url.setQuery(query);

	QNetworkRequest httpRequest;
	httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
	httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
	httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
	httpRequest.setUrl(url);

	qDebug() << url;

	QList<QByteArray> temp = httpRequest.rawHeaderList();
	for (int i = 0; i < temp.size(); i++)
	{
		qDebug() << temp[i] << httpRequest.rawHeader(temp[i]);
	}
	sslVerify(httpRequest);
	QNetworkReply* reply = _networkAccessManager->get(httpRequest);
	QEventLoop eventLoop;
	connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
	QTimer::singleShot(1000 * 5, &eventLoop, SLOT(quit()));
	eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
	int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	if (reply->error() == QNetworkReply::NoError)
	{
		if (statusCode == 200)
		{
			QJsonParseError jsonError;
			QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll(), &jsonError).object();
			if (jsonError.error == QJsonParseError::NoError)
			{
				object = jsonObject;
				QString strRet = jsonObject.value("meta").toObject().value("message").toString();
				if (strRet.compare("success") == 0)
				{
					nRet = 0;
				}
			}
		}
	}
	reply->deleteLater();
	reply = nullptr;
	return nRet;
}
int TNHttpApi::GetCompanyFeedIdByComId(const TNPluginParamPtr &pluginParam, const QString &comId, QJsonObject &object)
{
	InitNetWorkManager();
    _networkAccessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);

	int nRet = -1;
	QUrl url(pluginParam->str_new_org_systoon_com + URL_COMPANYFEED_BYCOMID);

	QUrlQuery query;
	query.addQueryItem("comId", comId);
	url.setQuery(query);

	QNetworkRequest httpRequest;
	httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
	httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
	httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
	httpRequest.setUrl(url);

	qDebug() << url;

	QList<QByteArray> temp = httpRequest.rawHeaderList();
	for (int i = 0; i < temp.size(); i++)
	{
		qDebug() << temp[i] << httpRequest.rawHeader(temp[i]);
	}
	sslVerify(httpRequest);
	QNetworkReply* reply = _networkAccessManager->get(httpRequest);
	QEventLoop eventLoop;
	connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    QTimer::singleShot(1000*5, &eventLoop, SLOT(quit()));
	eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
	int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	if (reply->error() == QNetworkReply::NoError)
	{
		if (statusCode == 200)
		{
			QJsonParseError jsonError;
			QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll(), &jsonError).object();
			if (jsonError.error == QJsonParseError::NoError)
			{
				object = jsonObject;
				QString strRet = jsonObject.value("meta").toObject().value("message").toString();
				if (strRet.compare("success") == 0)
				{
					nRet = 0;
				}
			}
		}
	}
	reply->deleteLater();
	reply = nullptr;
	return nRet;
}
int TNHttpApi::GetCompanyInfoByComIdList(const TNPluginParamPtr &pluginParam, const QStringList &comIDs, QJsonObject &object)
{
	InitNetWorkManager();
    _networkAccessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);

	int nRet = -1;
	QUrl url(pluginParam->str_new_org_systoon_com + URL_COMPANYINFO_BYCOMIDLIST);
	// Json数据
	QJsonArray json;
	for (int i = 0; i < comIDs.size(); i++)
	{
		json.insert(i, comIDs[i]);
	}

	QJsonObject jsonObject;
	jsonObject.insert("comIdList", json);
	QJsonDocument document;
	document.setObject(jsonObject);
	QByteArray dataArray = document.toJson(QJsonDocument::Compact);

	QNetworkRequest httpRequest;
	setRawHeader(httpRequest);
	httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
	httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
	httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
	httpRequest.setUrl(url);

	qDebug() << url;

	QList<QByteArray> temp = httpRequest.rawHeaderList();
	for (int i = 0; i < temp.size(); i++)
	{
		qDebug() << temp[i] << httpRequest.rawHeader(temp[i]);
	}
	sslVerify(httpRequest);
	QNetworkReply* reply = _networkAccessManager->post(httpRequest, dataArray);
	QEventLoop eventLoop;
	connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
	QTimer::singleShot(1000 * 5, &eventLoop, SLOT(quit()));
	eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
	int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	if (reply->error() == QNetworkReply::NoError)
	{
		if (statusCode == 200)
		{
			QJsonParseError jsonError;
			QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll(), &jsonError).object();
			if (jsonError.error == QJsonParseError::NoError)
			{
				object = jsonObject;
				QString strRet = jsonObject.value("meta").toObject().value("message").toString();
				if (strRet.compare("success") == 0)
				{
					nRet = 0;
				}
			}
		}
	}
	reply->deleteLater();
	reply = nullptr;
	return nRet;
}

int TNHttpApi::GetCompanyApps(const TNPluginParamPtr &pluginParam, const QString &companyId, const QString &orgFeedId, QJsonObject &object)
{
	InitNetWorkManager();
    _networkAccessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);

	int nRet = -1;

	QString baseUrl = pluginParam->str_api_app_systoon_com + URL_LIST_COMPANYCARDREGISTERAPP;

	QUrlQuery query;
	query.addQueryItem("companyId", companyId);
	query.addQueryItem("orgFeedId", orgFeedId);

	QUrl url(baseUrl);
	url.setQuery(query);

	QNetworkRequest httpRequest;
	setRawHeader(httpRequest);
	httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
	httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
	httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
	httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
	httpRequest.setUrl(url);

    qDebug() << "GetCompanyApps-url" << url;

	QList<QByteArray> temp = httpRequest.rawHeaderList();
	for (int i = 0; i < temp.size(); i++)
	{
		qDebug() << temp[i] << httpRequest.rawHeader(temp[i]);
	}
	sslVerify(httpRequest);
	QNetworkReply* reply = _networkAccessManager->get(httpRequest);
	QEventLoop eventLoop;
	connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
	QTimer::singleShot(1000 * 5, &eventLoop, SLOT(quit()));
	eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
	int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	if (reply->error() == QNetworkReply::NoError)
	{
		if (statusCode == 200)
		{
			QJsonParseError jsonError;
			QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll(), &jsonError).object();
			if (jsonError.error == QJsonParseError::NoError)
			{
				object = jsonObject;
				QString strRet = jsonObject.value("meta").toObject().value("message").toString();
				if (strRet.compare("success") == 0)
				{
					nRet = 0;
				}
			}
		}
	}
	reply->deleteLater();
	reply = nullptr;
	return nRet;
}

int TNHttpApi::GetStaffApps(const TNPluginParamPtr &pluginParam, const QString &companyId, const QString &staffFeedId, QJsonObject &object)
{
	InitNetWorkManager();
    _networkAccessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);

    int nRet = -1;

    QString baseUrl = pluginParam->str_api_app_systoon_com + URL_LIST_COMPANYSTAFFREGISTERAPP;

    QUrlQuery query;
    query.addQueryItem("companyId", companyId);
    query.addQueryItem("staffFeedId", staffFeedId);

    QUrl url(baseUrl);
    url.setQuery(query);

    QNetworkRequest httpRequest;
    setRawHeader(httpRequest);
    httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
    httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
    httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
    httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
    httpRequest.setUrl(url);

    qDebug() << "GetStaffApps-url" << url;

    QList<QByteArray> temp = httpRequest.rawHeaderList();
    for (int i = 0; i < temp.size(); i++)
    {
        qDebug() << temp[i] << httpRequest.rawHeader(temp[i]);
    }
    sslVerify(httpRequest);
    QNetworkReply* reply = _networkAccessManager->get(httpRequest);
    QEventLoop eventLoop;
    connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    QTimer::singleShot(1000 * 5, &eventLoop, SLOT(quit()));
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (reply->error() == QNetworkReply::NoError)
    {
        if (statusCode == 200)
        {
            QJsonParseError jsonError;
            QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll(), &jsonError).object();
            if (jsonError.error == QJsonParseError::NoError)
            {
                object = jsonObject;
                QString strRet = jsonObject.value("meta").toObject().value("message").toString();
                if (strRet.compare("success") == 0)
                {
                    nRet = 0;
                }
            }
        }
    }
    reply->deleteLater();
    reply = nullptr;
    return nRet;
}

int TNHttpApi::GetRecommendApps(const TNPluginParamPtr &pluginParam, const QString &feedId, QJsonObject &object)
{
	InitNetWorkManager();
    _networkAccessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);

    int nRet = -1;

    QString baseUrl = pluginParam->str_mix_systoon_com + URL_LIST_RECOMMEND_APP;

    QUrlQuery query;
    query.addQueryItem("feedId", feedId);

    QUrl url(baseUrl);
    url.setQuery(query);

    QNetworkRequest httpRequest;
    setRawHeader(httpRequest);
    httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
    httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
    httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
    httpRequest.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));
    httpRequest.setUrl(url);

    qDebug() << "TNHttpApi::GetRecommendApps-url=" << url;

    QList<QByteArray> temp = httpRequest.rawHeaderList();
    for (int i = 0; i < temp.size(); i++)
    {
        qDebug() << temp[i] << httpRequest.rawHeader(temp[i]);
    }
    sslVerify(httpRequest);
    QNetworkReply* reply = _networkAccessManager->get(httpRequest);
    QEventLoop eventLoop;
    connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
	QTimer::singleShot(1000 * 5, &eventLoop, SLOT(quit()));
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (reply->error() == QNetworkReply::NoError)
    {
        if (statusCode == 200)
        {
            QJsonParseError jsonError;
            QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll(), &jsonError).object();
            if (jsonError.error == QJsonParseError::NoError)
            {
                object = jsonObject;
                QString strRet = jsonObject.value("meta").toObject().value("message").toString();
                if (strRet.compare("success") == 0)
                {
                    nRet = 0;
                }
            }
        }
    }
    reply->deleteLater();
    reply = nullptr;
    return nRet;
}

bool TNHttpApi::LoginWithAuthCodeByOA(const QString& strMobile, const QString& autoCode, const QString& accessToken, const QString& orgId, const QString& appId, QString& outUserId, QString& outUserToken)
{
	InitNetWorkManager();
    _networkAccessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);

	QJsonObject jsonObject;
	jsonObject.insert("userMobilePhone", strMobile);
	jsonObject.insert("authCode", autoCode);
	jsonObject.insert("toonType", APPTYPE);
	QJsonDocument document;
	document.setObject(jsonObject);
	QByteArray dataArray = document.toJson(QJsonDocument::Compact);

	// 基本 URL
	QString baseUrl = URL_OA_LOGIN;
	//QString baseUrl = "http://t200oapi.qitoon.com/uua/toon_login";
	QUrl url(baseUrl);
	qDebug() << url;
	QNetworkRequest httpRequest;
	setRawHeader(httpRequest);
	httpRequest.setRawHeader(QByteArray("accesstoken"), accessToken.toStdString().c_str());
	httpRequest.setRawHeader(QByteArray("orgId"), orgId.toStdString().c_str());
	httpRequest.setRawHeader(QByteArray("appId"), appId.toStdString().c_str());
	httpRequest.setUrl(url);
	sslVerify(httpRequest);
	QNetworkReply* reply = _networkAccessManager->post(httpRequest, dataArray);
	QEventLoop eventLoop;
	connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
	QTimer::singleShot(1000 * 5, &eventLoop, SLOT(quit()));
	eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
	int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	if (reply->error() == QNetworkReply::NoError)
	{
		if (statusCode == 200)
		{
			QJsonParseError jsonError;
			QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll(), &jsonError).object();
			if (jsonError.error == QJsonParseError::NoError)
			{
				QString code = jsonObject.value("meta").toObject().value("code").toString();
				QString msg = jsonObject.value("meta").toObject().value("message").toString();
				qDebug() << "LoginWithAuthCodeByOA:" << msg;
				if (code == "0")
				{
					//success
					outUserId = jsonObject.value("data").toObject().value("toonUserId").toString();
					qDebug() << "LoginWithAuthCodeByOA:userId" << outUserId;
					outUserToken = jsonObject.value("data").toObject().value("toonUserToken").toString();
					qDebug() << "LoginWithAuthCodeByOA:UserToken" << outUserToken;
					return true;
				}
			}
		}
	}
	reply->deleteLater();
	reply = nullptr;
	return false;
}


void TNHttpApi::sslVerify(QNetworkRequest& httpRequest)
{
	if (httpRequest.url().toString().indexOf(HTTPS) == 0)
	{
		QSslConfiguration conf = httpRequest.sslConfiguration();
		conf.setPeerVerifyMode(QSslSocket::VerifyNone);
		conf.setProtocol(QSsl::TlsV1SslV3);
		httpRequest.setSslConfiguration(conf);
	}
}

void TNHttpApi::InitDomainUrl(QString strUrl)
{
	/*非常重要*/
	strUrl = "im.huohua.cn";
	Q_ASSERT(!strUrl.isEmpty());
	_strUrl = strUrl;
}
int TNHttpApi::GetOCSStatus(const TNPluginParamPtr &pluginParam, const QString &feedId, QJsonObject &object)
{
	InitNetWorkManager();
	_networkAccessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);

	int nRet = -1;
	QUrl url(pluginParam->str_new_org_systoon_com + URL_COMPANYINFO_ORGCOMM);
	// Json数据
	QJsonArray json;
	json.insert(0, feedId);

	QJsonObject jsonObject;
	jsonObject.insert("feedIDList", json);
	QJsonDocument document;
	document.setObject(jsonObject);
	QByteArray dataArray = document.toJson(QJsonDocument::Compact);

	QNetworkRequest httpRequest;
	setRawHeader(httpRequest);
	httpRequest.setRawHeader(QByteArray("X-Toon-User-ID"), pluginParam->strTnUserID.toStdString().c_str());
	httpRequest.setRawHeader(QByteArray("X-Toon-User-Token"), pluginParam->strTnUserToken.toStdString().c_str());
	httpRequest.setRawHeader(QByteArray("X-Toon-User-Agent"), pluginParam->strTnUserAgent.toStdString().c_str());
	httpRequest.setUrl(url);

	qDebug() << url;

	QList<QByteArray> temp = httpRequest.rawHeaderList();
	for (int i = 0; i < temp.size(); i++)
	{
		qDebug() << temp[i] << httpRequest.rawHeader(temp[i]);
	}
	sslVerify(httpRequest);
	QNetworkReply* reply = _networkAccessManager->post(httpRequest, dataArray);
	QEventLoop eventLoop;
	connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
	QTimer::singleShot(1000 * 5, &eventLoop, SLOT(quit()));
	eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
	int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	if (reply->error() == QNetworkReply::NoError)
	{
		if (statusCode == 200)
		{
			QJsonParseError jsonError;
			QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll(), &jsonError).object();
			if (jsonError.error == QJsonParseError::NoError)
			{
				object = jsonObject;
				QString strRet = jsonObject.value("meta").toObject().value("message").toString();
				if (strRet.compare("success") == 0)
				{
					nRet = 0;
				}
			}
		}
	}
	reply->deleteLater();
	reply = nullptr;
	return nRet;
}
