#ifndef CTNIMCLIENTTNMP_H
#define CTNIMCLIENTTNMP_H

#include "imcore_global.h"
#include <QString>
#include <QVector>
#include "CTNProcessThread.h"
#include "tncmessage.h"


class TMTPHostInfo;
class CTNProcessThread;
class TNIMCoreProcessor;
class TNIMMsgManager;
class TNIMSDKClient;
class CTNIMClientTNMP
{
public:
    CTNIMClientTNMP();
	~CTNIMClientTNMP();

	void addHostInfo(TMTPHostInfo &hostInfo);
    void setClientId(QString clientId){
        _clientId = clientId;
    }
    void setDeviceToken(QString token){
        _deviceToken = token;
    }

    void setDeviceId(QString deviceId){
        _deviceId = deviceId;
    }

    void setAppType(int appType){
        _appType = appType;
    }

    void setVersion(QString version){
        _version = version;
    }
	void setMsgProcessor(TNIMMsgManager* msgManager)
	{
		_msgManager = msgManager;
	}

    int login(QString username, QString password);
    int logout(bool notifyServer);
	void InitIMSDK(TNIMMsgManager* msgManager);
    int sendMessage(TNCMessage* message, QString toClientId);
	int revokeMessage(TNCMessage* message, QString toClientId);
	void reqSyncReadSession(QString sessionId);

private:
    QString _deviceId;
    QString _clientId;
    QString _deviceToken;
    int _appType;
    QString _version;

	TNIMMsgManager*		  _msgManager;
	TNIMSDKClient*		  _imSDKClient;
};

#endif // CTNIMCLIENTTNMP_H
