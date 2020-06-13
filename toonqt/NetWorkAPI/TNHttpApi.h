#ifndef TNHTTPAPI_H
#define TNHTTPAPI_H

#include <QSettings>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QUrlQuery>

#include "NetWorkAPI.h"
#include "common_global.h"

typedef struct Body
{
	QString strDeviceName;
	QString strDeviceToken;
	QString strIdfa;
	QString strImei;
	QString strMacAddress;
	QString strMobile;
	QString strPassword;
	bool bRegLogin;
	QString strTeleCode;
	QString strUuid;
}st_LoginWithPasswordHttpBody;

class NETWORKAPI_EXPORT TNHttpApi : public QObject
{
	Q_OBJECT

public:
	TNHttpApi();
	~TNHttpApi();
	void InitDomainUrl(QString strUrl);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Check register before login new. </summary>
	///
	/// <remarks>	田恒, 2017/3/7. </remarks>
	///
	/// <param name="strUserID">   	Identifier for the user. </param>
	/// <param name="strUserToken">	The user token. </param>
	/// <param name="strUserAgent">	The user agent. </param>
	/// <param name="strTeleCode"> 	The tele code. </param>
	/// <param name="strMobile">   	The mobile. </param>
	/// <param name="strUuid">	   	The uuid. </param>
	///
	/// <returns>	1:注册过且没有切换设备；2：注册过且切换过设备；3：没注册过. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

    int CheckRegisterBeforeLoginNew(QString strUserID, QString strUserToken, QString strUserAgent,
                                    QString strTeleCode, QString strMobile, QString strUuid);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Login with password. </summary>
	///
	/// <remarks>	田恒, 2017/3/7. </remarks>
	///
	/// <param name="strUserID">   	Identifier for the user. </param>
	/// <param name="strUserToken">	The user token. </param>
	/// <param name="strUserAgent">	The user agent. </param>
	/// <param name="body">		   	The body. </param>
	///
	/// <returns>	 0:失败 1:成功 2:短信验证码错误 3:验证码失效 . </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	int LoginWithPassword(const QString &strUserID, const QString &strUserToken, QJsonObject &object);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Logout. </summary>
	///
	/// <remarks>	田恒, 2017/4/12. </remarks>
	///
	/// <param name="pluginParam">	The plugin parameter. </param>
	/// <param name="body">		  	The body. </param>
	/// <param name="object">	  	[in,out] The object. </param>
	///
	/// <returns>	An int. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	int Logout(const TNPluginParamPtr &pluginParam, const st_LoginWithPasswordHttpBody &body, QJsonObject &object);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Sends a v code before login. </summary>
	///
	/// <remarks>	田恒, 2017/3/21. </remarks>
	///
	/// <param name="pluginParam">	The plugin parameter. </param>
	/// <param name="strTeleCode">	The tele code. </param>
	/// <param name="strMobile">  	The mobile. </param>
	/// <param name="strType">	  	The type. </param>
	///
	/// <returns>	0:成功 1:失败 一小时最多能发5条 2:一天最多能发10条 .  </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	int sendVCodeBeforeLogin(const TNPluginParamPtr &pluginParam, const QString& strTeleCode, const QString& strMobile, const QString& strType, int retry = 0);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Login with v code. </summary>
	///
	/// <remarks>	田恒, 2017/3/21. </remarks>
	///
	/// <param name="pluginParam">	The plugin parameter. </param>
	/// <param name="body">		  	The body. </param>
	/// <param name="object">	  	[in,out] The object. </param>
	///
	/// <returns>	0:失败；1：成功；2：短信验证码错误；3：验证码失效. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

    int LoginWithVCode(const TNPluginParamPtr &pluginParam, const st_LoginWithPasswordHttpBody &body, QJsonObject &object, int *code = 0);

    int GetFeedList(const TNPluginParamPtr &pluginParam, const QStringList &feedIds, QJsonObject &object);

    int GetGroupChatMembers(const TNPluginParamPtr &pluginParam, const QString &groupChatId, QJsonObject &object);

	int GetOCSStatus(const TNPluginParamPtr &pluginParam, const QString &feedId, QJsonObject &object);
    // 名片详情
	int GetListCard(const TNPluginParamPtr &pluginParam, const QStringList &feedids, QJsonObject &object);
	int GetListStaffCard(const TNPluginParamPtr &pluginParam, const QString &feedids, QJsonObject &object);
	int GetListOrgCard(const TNPluginParamPtr &pluginParam, const QString &feedids, QJsonObject &object);
    int GetListGroup(const TNPluginParamPtr &pluginParam, const QStringList &feedids, QJsonObject &object);

    // 公司详情
	int GetCompanyInfoByComIdList(const TNPluginParamPtr &pluginParam, const QStringList &comId, QJsonObject &object);
	int GetCompanyFeedIdByComId(const TNPluginParamPtr &pluginParam, const QString &comId, QJsonObject &object);
	int GetCompanyInfoByComId(const TNPluginParamPtr &pluginParam, const QString &comId, QJsonObject &object);
    int GetCompanyApps(const TNPluginParamPtr &pluginParam, const QString &companyId, const QString &orgFeedId, QJsonObject &object);
    int GetStaffApps(const TNPluginParamPtr &pluginParam, const QString &companyId, const QString &staffFeedId, QJsonObject &object);

    int GetRecommendApps(const TNPluginParamPtr &pluginParam, const QString &feedId, QJsonObject &object);
	bool LoginWithAuthCodeByOA(const QString& strMobile, const QString& autoCode, const QString& accessToken, const QString& orgId, const QString& appId, QString& outUserId, QString& outUserToken);
protected:
	void setRawHeader(QNetworkRequest & httpRequest);

public slots:
	void serviceRequestFinished(QNetworkReply *reply);

public:
	static void sslVerify(QNetworkRequest& httpRequest);
	void InitNetWorkManager();
protected:
	QNetworkRequest _httpRequest;
	QNetworkAccessManager* _networkAccessManager;
	QString _strUrl;
};

typedef std::shared_ptr<TNHttpApi>  TNHttpApiPtr;

#endif // TNHTTPAPI_H
