#ifndef TNQRCODELOGIN_H
#define TNQRCODELOGIN_H
#include "TNHttpQRCodeKeyGen.h"
#include "qobject.h"
#include "qtimer.h"
class TNQRCodeLogin : public QObject
{
	Q_OBJECT

public:
	TNQRCodeLogin(TNPluginParamPtr pluginParam);
	~TNQRCodeLogin();
public:
	void GetQRCodePic();
	void GetQRCodeStatus();
	void CancelQRCodeLogin();
	QString GetMobile(){ return _strMobile; }
	QString GetToken(){ return _strToken; };
	QString GetUserId(){ return _strUserId; };
	int		GetStatus(){ return _status; }
signals:
	void DownQRCodeSuccess(QString path);
	void GetScanCodeStatus(int status);
	void CancelScanLogin();
	void CurrentQRcodeInvalid();
public slots:
	void onTimerGetStatus();
private:
	void GetQRCodeInfo();
private:
	QTimer*					_timer;
	TNPluginParamPtr	   _pluginParam;
	TNHttpQRCodeKeyGenPtr  _httpQRCode;
	QString _strQRCodePath;
	QString _strMobile;
	QString _strToken;
	QString _strUserId;
	int		_status;
};
#endif

