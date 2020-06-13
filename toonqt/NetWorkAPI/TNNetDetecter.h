#ifndef TNNETDETECTER_H
#define TNNETDETECTER_H
#include <QObject>
#include <QHostInfo>
#include <QTimer>
#include "NetWorkAPI.h"

#define DETECT_INTERVAL	 5000*3		//单位ms
enum NetStatus
{
	NetStatusNone = 0,
	NetStatusConnect = 5,		//网络正常
	NetStatusDisconnect = 6,	//网络断开
	NetStatusLogout	= 1000		//被踢出
};
class NETWORKAPI_EXPORT TNNetDetecter : public QObject
{
	Q_OBJECT

public:
	TNNetDetecter();
	~TNNetDetecter();
	void DetectNetStatus();
	NetStatus GetNetStatus(){ return _netStatus; };
public slots:
	void onLookedUp(const QHostInfo&);
	void onTimerDetect();
signals:
	void SendNetDetectStatus(NetStatus status);
private:
	NetStatus _netStatus;
	QTimer*	  _timer;
};
#endif
