#ifndef TNHTTPQRCODEKEYGEN_H
#define TNHTTPQRCODEKEYGEN_H

#include <functional>
#include <QList>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"

#define OPERA_INVALIDATE    -1       //二维码失效状态
#define OPERA_SCAN		    1		 //已扫描
#define OPERA_LOGIN			2        //确认登录
class NETWORKAPI_EXPORT TNHttpQRCodeKeyGen : public TNHttpBaseApi
{
	Q_OBJECT

public:
	TNHttpQRCodeKeyGen();
	~TNHttpQRCodeKeyGen();

	//获取二维码key
	void GetQRCodeKey(std::function<void(bool, QString)> callback, const TNPluginParamPtr& pluginParam);
	//根据二维码key获取二维码图片
	void GetQRCodeInfo(std::function<void(bool, QString)> callback, const TNPluginParamPtr& pluginParam);
	//获取二维码状态
	void GetQRCodeStatus(std::function<void(bool, int, QString, QString, QString)> callback, const TNPluginParamPtr& pluginParam);
	//取消二维码登录
	void CancelQRCodeLogin(std::function<void(bool, QString)> callback, const TNPluginParamPtr& pluginParam);
protected:
	void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);
	
private:
	std::function<void(bool, QString)>					_funGetQRCodeKey;
	std::function<void(bool, QString)>					_funGetQRCodePic;
	std::function<void(bool, int, QString, QString, QString)>	_funGetQRCodeStatus;
	std::function<void(bool, QString)>					_funCancelQRLogin;
	std::function<void(bool, QString)>					_funGetMobile;
	QString												_strCodeKey;
};

typedef std::shared_ptr<TNHttpQRCodeKeyGen>  TNHttpQRCodeKeyGenPtr;

#endif // TNHTTPDOWNCLOUND_H
