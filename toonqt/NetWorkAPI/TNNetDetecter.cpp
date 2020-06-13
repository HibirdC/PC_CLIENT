#include "TNNetDetecter.h"
#include "NetWorkAPI_global.h"

TNNetDetecter::TNNetDetecter() :_netStatus(NetStatusNone), _timer(NULL)
{
}


TNNetDetecter::~TNNetDetecter()
{
	if (_timer)
	{
		_timer->stop();
		delete _timer;
		_timer = NULL;
	}
}

void TNNetDetecter::DetectNetStatus() 
{
	if (_timer == NULL)
	{	
		_timer = new QTimer();
		connect(_timer, SIGNAL(timeout()), this, SLOT(onTimerDetect()));
		_timer->setInterval(DETECT_INTERVAL);
		_timer->start();
	}
	
}

void TNNetDetecter::onLookedUp(const QHostInfo& host)
{

	if (host.error() != QHostInfo::NoError)
	{
        qInfo() << "[NetWorkAPI][TNNetDetecter] TNNetDetecter:current net work disconnect";
		_netStatus = NetStatusDisconnect;
	}
	else
	{
		qInfo() << "[NetWorkAPI][TNNetDetecter]" <<host.addresses().first().toString();
		_netStatus = NetStatusConnect;
	}
	emit SendNetDetectStatus(_netStatus);
}

void TNNetDetecter::onTimerDetect()
{
	QHostInfo::lookupHost(URL_ROUTER_HOST, this, SLOT(onLookedUp(QHostInfo)));
}
