#include "TNQRCodeLogin.h"
#include "TNUserDataHelper.h"

TNQRCodeLogin::TNQRCodeLogin(TNPluginParamPtr pluginParam) :_timer(NULL), _status(0)
{
	_pluginParam = pluginParam;
	_httpQRCode = std::make_shared<TNHttpQRCodeKeyGen>();
}


TNQRCodeLogin::~TNQRCodeLogin()
{
	if (_timer)
	{
		if (_timer->isActive())
			_timer->stop();
		delete _timer;
	}
}

void TNQRCodeLogin::GetQRCodePic()
{
	_httpQRCode->GetQRCodeKey([&](bool success, QString info)
	{
		if (success)
		{
			this->GetQRCodeInfo();
		}
	}, _pluginParam);

}

void  TNQRCodeLogin::GetQRCodeInfo()
{
	//成功获取key，请求二维码图片资源
	_httpQRCode->GetQRCodeInfo([&](bool success, QString path)
	{
		if (success)
		{
			AAAAA
			_strQRCodePath = path;
			emit DownQRCodeSuccess(_strQRCodePath);
		}
	}, _pluginParam);
}

void TNQRCodeLogin::GetQRCodeStatus()
{
	if (_timer == NULL)
	{
		_timer = new QTimer();
		connect(_timer, SIGNAL(timeout()), this, SLOT(onTimerGetStatus()));
		_timer->setInterval(1000);
		_timer->start();
	}
	else
		_timer->start();
}

void TNQRCodeLogin::CancelQRCodeLogin()
{
	//取消登录timer结束
	if (_timer == NULL)
		return;
	if (_timer->isActive())
		_timer->stop();
	_httpQRCode->CancelQRCodeLogin([&](bool success, QString info)
	{
		if (success)
		{
			emit CancelScanLogin();
		}
	}, _pluginParam);
}

void TNQRCodeLogin::onTimerGetStatus()
{
	_httpQRCode->GetQRCodeStatus([&](bool success, int status, QString info, QString userId, QString mobile)
	{
		if (success)
		{
			if (status == -1)
			{
				//二维码失效，timer结束
				if (_timer->isActive())
					_timer->stop();
				emit CurrentQRcodeInvalid();
				return;
			}
			//已经登录，则过滤之后处理
			if (_status == 2)
				return;
			_status = status;
			if (_status == 1)
				_strMobile = info;
			else if (status == 2)
			{
				//登录之后timer结束
				if (_timer->isActive())
					_timer->stop();
				_strToken = info;
				_strUserId = userId;
				_strMobile = mobile;
			}
			emit GetScanCodeStatus(status);
		}
	}, _pluginParam);
}

