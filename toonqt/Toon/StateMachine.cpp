#include "StateMachine.h"
#include "login.h"
#include "Toon.h"
#include "TNDataControlServer.h"
#include "TNIMCoreClient.h"
#include "tnnotifycenter.h"
#include "TNDataCache.h"
#include "TNUserVersionInfo.h"
#include "TNConfig.h"
#include "TNCheckUpdateInfoDialog.h"
#include "TNCheckUpdateDialog.h"
#include "TNUpgradeMangement.h"
#include "TNSettingData.h"
#include "TNWarningMessageBox.h"
#include "TNDataStatistics.h"
#include "TNOfflineNoticeDialog.h"
#include "TNVersionInfo.h"
#include "TNPathUtil.h"
#include "TNUtil.h"

#include <QProcess>
#ifdef  Q_OS_WIN32
#include <Windows.h>
#endif 
#ifdef Q_OS_MAC
#include "macqapplication.h"
#endif

StateMachine::StateMachine(QObject *parent)
: QObject(parent)
, _mainWidget(nullptr)
, _loginDlg(nullptr)
, _loadingPage(nullptr)
, _currentStatus(NetStatusNone)
{
	qRegisterMetaType<TNPluginParamPtr>("TNPluginParamPtr");	
	QObject::connect(TNDataCache::GetInstance(), SIGNAL(HasUpdateAllCache()), this, SLOT(SyncedWithCatcheSlot()));
    TNNotifyCenter::instance()->connectNotifyNetStatus(this);
    connect(TNUpgradeMangement::instance(), SIGNAL(checkVersionFinished(bool, bool, QString, int, QString)),
        this, SLOT(onCheckVersionFinished(bool, bool, QString, int, QString)));
    TNNotifyCenter::instance()->connectNotifyCheckVersionFinished(this);
	QObject::connect(TNDataControlServer::GetInstance(), SIGNAL(dbOwnerError(int)), this, SLOT(dbOwnerErrorSlot(int)));
    QObject::connect(qGuiApp, SIGNAL(applicationStateChanged(Qt::ApplicationState)), this, SLOT(slotApplicationStateChanged(Qt::ApplicationState)));
#ifdef Q_OS_MAC
    macQApplication* app = (macQApplication*)parent;
    app->setDockFunc(StateMachine::dockEvent,this);
#endif
}

void TerminateApp()
{
#ifdef Q_OS_WIN
	HANDLE hself = GetCurrentProcess();
	TerminateProcess(hself, 0);
#else
    //exit(0);
#endif
}

StateMachine::~StateMachine()
{	
	qInfo() << "[Toon][StateMachine] StateMachine destroy";
	if (_loginDlg)
	{
		_loginDlg->close();
		_loginDlg->deleteLater();
		_loginDlg = NULL;
	}
	if (_mainWidget)
	{
		_mainWidget->close();
		delete _mainWidget;
		_mainWidget = NULL;
		ClearData();
		TNIMCoreClient::GetIMClient()->DestoryIMClient();
		qInfo() << "[Toon][StateMachine] ~StateMachine";
	}
	//强制退出
	TerminateApp();
}



void StateMachine::OnLoginSuccessSlot(TNPluginParamPtr pluginParam)
{
	_loginDlg->close();
	_loginDlg->deleteLater();
	_loginDlg = NULL;
	_pluginParam = pluginParam;
	/*
	启动等待
	*/
	ShowLoading();
}

void StateMachine::OnLoginOutSlot()
{
#ifdef DAOTOON
	qApp->quit();
	return;
#endif
	qInfo() << "[Toon][StateMachine] OnLoginOutSlot";
	QWidgetList list = qApp->allWidgets();
    for (int i = 0; i < list.size(); i++)
	{
		QWidget *pWidget = list[i];
		if (pWidget->parent() == nullptr && pWidget != _mainWidget)
		{
			pWidget->close();
		}
	}

	_mainWidget->close();
	delete _mainWidget;
	_mainWidget = NULL;
	ClearData();
	Init(false);
}

void StateMachine::ClearData()
{
	try
	{
		TNIMCoreClient::GetIMClient()->IMLogout();
		TNDataCache::GetInstance()->ReSetCache();
		TNUserVersionInfo::GetInstance()->ResetVersion();
		TNDataControlServer::GetInstance()->CloseDb();
		TNDataStatistics::CloseStatisData();
		TNConfig::instance()->resetSettings();
		TNUserDataHelper::GetInstance()->clearNativeCardStatus();
	}
	catch (...)
	{
		qInfo() << "[Toon][StateMachine]:clearData exception";
	}
	qInfo() << "[Toon][StateMachine]:clearData";
}

void StateMachine::Init(bool enableAutoLogin)
{
    _loginDlg = new Login();
    _loginDlg->Init(enableAutoLogin);
	QObject::connect(_loginDlg, SIGNAL(SendPluginParamSignal(TNPluginParamPtr)), this, SLOT(OnLoginSuccessSlot(TNPluginParamPtr)));

    TNUtil::setIsFirstLoginHomePage(true);

	bool bShow = true;
	if (enableAutoLogin && qApp->arguments().size() == 2)
		bShow = false;
	if (bShow)
        _loginDlg->showWidget();
	else
		ShowLoading();
}

void StateMachine::onCheckVersionFinished(bool isNeedUpgrade, bool isForceUpgrade, QString downLoadURL, int nCheckType, QString versionDesc)
{
    if (isNeedUpgrade)
    {
        TNNotifyCenter::instance()->postNotifyCheckVersionFinished(isNeedUpgrade, isForceUpgrade, downLoadURL, nCheckType, versionDesc);
    }
    else
    {
        if (nCheckType == TNUpgradeMangement::ctUser)
        {
            //用户检查时，如果没有更新需要提示
            TNCheckUpdateDialog *checkUpdateDlg = new TNCheckUpdateDialog();
            checkUpdateDlg->setObjectName("checkUpdateDlg");
            checkUpdateDlg->setAttribute(Qt::WA_DeleteOnClose);
            if (checkUpdateDlg->exec() == QDialog::Accepted)
            {
            }

        }
    }
}

void StateMachine::on_notifyNetStatus(int netstatus)
{
    if (NetStatusConnect == netstatus && netstatus != _currentStatus)
    {
        //网络恢复
        emit connectRestored();
    }
    else if (NetStatusDisconnect == netstatus && netstatus != _currentStatus)
    {
        if (_mainWidget != nullptr)
        {
            QString content = ("网络不可用，请检查你的网络设置");
            TNWarningMessageBox *disconnectMessageBox = new TNWarningMessageBox(_mainWidget);
            disconnectMessageBox->setMsg(content);
            disconnectMessageBox->resize(QSize(300, 40));
            disconnectMessageBox->raise();
            disconnectMessageBox->move(400, 30);
            disconnectMessageBox->show();
            connect(this, SIGNAL(connectRestored()), disconnectMessageBox, SLOT(accept()));
        }
    }
	else if (NetStatusLogout == netstatus)
	{
        if (_mainWidget)
        {
#ifdef DAOTOON
			TNOfflineNoticeDialog offlineNoticeDialog(TNOfflineNoticeDialog::warning,_loginDlg);
			offlineNoticeDialog.exec();
			qApp->quit();
			return;
#else
			qInfo() << "[toon][StateMachine] on_notifyNetStatus logout";
            OnLoginOutSlot();
			TNOfflineNoticeDialog offlineNoticeDialog(TNOfflineNoticeDialog::warning,_loginDlg);
			offlineNoticeDialog.exec();
#endif
        }
	}

    _currentStatus = netstatus;
}

void StateMachine::on_notifyCheckVersionFinished(
    bool isNeedUpgrade,
    bool isForceUpgrade,
    QString downLoadURL,
    int nCheckType,
    QString versionDesc
    )
{
    bool isShowTip = false;
    switch (nCheckType)
    {
        //启动检查时，只有在强制更新或者有“稍后提醒”标志时，才提示更新
    case TNUpgradeMangement::ctBoot:
        TNSettingData::instance()->SetIsNewestVersion(false);
        if (isForceUpgrade || TNConfig::instance()->isRemindLatar())
        {
            isShowTip = true;
        }
        break;

        //定时检查时，只有在强制更新时才提醒, 并且提醒方式同“非强制”更新的提醒方式
    case TNUpgradeMangement::ctTimed:
        qDebug() << "Regular check, execution complete; Has new version, but not farce";
        if (isForceUpgrade)
        {
            isShowTip = true;
            isForceUpgrade = false;
        }
        break;

        //用户检查时，总是有提醒
    case TNUpgradeMangement::ctUser:
        isShowTip = true;
        break;

    default:
        break;
    }
    if (isShowTip)
    {
        static TNCheckUpdateInfoDialog *checkUpdateInfoDlg = nullptr;//避免连续弹出两个对话框,用静态变量
        if (nullptr == checkUpdateInfoDlg)
        {
            qDebug()<<"TNCheckUpdateInfoDialog show begin. time="<<QDateTime::currentMSecsSinceEpoch();
            checkUpdateInfoDlg = new TNCheckUpdateInfoDialog(isForceUpgrade, downLoadURL, versionDesc, _mainWidget);
            checkUpdateInfoDlg->setObjectName("checkUpdateInfoDlg");
            checkUpdateInfoDlg->exec();
            delete checkUpdateInfoDlg;
            checkUpdateInfoDlg = nullptr;
            qDebug()<<"TNCheckUpdateInfoDialog show end. time="<<QDateTime::currentMSecsSinceEpoch();
        }
    }
}


void StateMachine::ShowMainFrame(bool bStopLoad)
{
	if (_mainWidget == NULL)
	{
		if (TNVersionInfo::IsBaseToonVersion())
           InitSkin();
		_mainWidget = new Toon();
        _mainWidget->init();
		QObject::connect(_mainWidget, SIGNAL(SendQuitSignal()), this, SLOT(OnLoginOutSlot()));
		if (bStopLoad&& _loadingPage != NULL)
		{
			delete _loadingPage;
			_loadingPage = NULL;
		}
#ifdef Q_OS_WIN32
		::SetWindowPos(HWND(_mainWidget->winId()), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
		::SetWindowPos(HWND(_mainWidget->winId()), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
#endif
		_mainWidget->showWidget();
		_mainWidget->activateWindow();
		TNIMCoreClient* client = TNIMCoreClient::GetIMClient();
        client->IMLogin(_pluginParam->strEmailAddress, _pluginParam->strTnUserToken);
	}
}

void StateMachine::SyncedWithCatcheSlot()
{
	qDebug() << "Sync over";
	ShowMainFrame(true);
}

void StateMachine::SyncedTimeOutSlot()
{
	qDebug() << "loading time out";
	ShowMainFrame(true);
}

void StateMachine::InitSkin()
{
	TableBaseVec setTables;
	TNDataControlServer::GetInstance()->Query(setTables, "SetUp", "Key", STR_SKIN_KEY,DBTYPE_USER);
	if (setTables.size() > 0)
	{
		st_SetUpPtr skinItem = std::dynamic_pointer_cast<st_SetUp>(setTables[0]);
		SKIN_TYPE skinType = (SKIN_TYPE)skinItem->GetValue().toInt();
		TNSettingData::instance()->ApplySkinType(skinType);
	}
}

void StateMachine::ShowLoading()
{
	if (_loadingPage == NULL)
	{
		_loadingPage = new TNStartloadingpage();
		qDebug() << "Start loading page";
		_loadingPage->start();
	}
}

/*
此时未登录IM，主窗口未加载
1. 数据库未加密，但是配置文件显示加密，会异常
2. 数据库不是自己的，会显示异常
3. 如果异常类型是 common 数据库， 此时所有数据库均未连接
4. 如果异常类型是 toon 数据库 ，此时common 数据库已经连接。不需要清理common数据库
5. 如果异常类型是 message 数据库，此时toon数据库已经连接，需要关闭toon数据库
*/
void StateMachine::dbOwnerErrorSlot(int dbType)
{
#ifdef DAOTOON
	TNOfflineNoticeDialog offlineNoticeDialog(TNOfflineNoticeDialog::warning,_loginDlg);
    offlineNoticeDialog.setText(("异常通知"), ("数据库异常，登录失败"));
	offlineNoticeDialog.exec();
	qApp->quit();
	return;
#else
	int fixed = TNConfig::instance()->getFixedFailed();
	if (fixed>0)
	{
		showFixFailed();
		return;
	}
	TNOfflineNoticeDialog offlineNoticeDialog(TNOfflineNoticeDialog::errorAndFixed, _loginDlg);
    offlineNoticeDialog.setText(("异常通知"), ("数据库文件异常，登录失败"));
	if (offlineNoticeDialog.exec() == QDialog::Accepted)
	{
		qInfo() << "[Toon][StateMachine]dbOwnerErrorSlot fix error.";
		int level = 0;
		switch (dbType)
		{
		case DBTYPE_USER:
			level = 2;
			break;
		case DBTYPE_COMMON:
			level = 1;
			break;
		case DBTYPE_MSG:
			level = 3;
			break;
		default:
			break;
		}
		TNConfig::instance()->setFixedErrStatus(level);
		qApp->quit();
		QProcess::startDetached(qApp->applicationFilePath(), QStringList());
	}
#endif
}

void StateMachine::slotApplicationStateChanged(Qt::ApplicationState state)
{
    qDebug()<<"state="<<state;
    if (state == Qt::ApplicationActive)
    {
        if (QApplication::activeModalWidget() && _mainWidget)
            _mainWidget->activateWindow();
    }
}

void StateMachine::showFixFailed()
{
	TNOfflineNoticeDialog offlineNoticeDialog(TNOfflineNoticeDialog::warning, _loginDlg);
    offlineNoticeDialog.setText(("异常通知"), ("部分文件正在被其他进程使用，修复失败!"));
	offlineNoticeDialog.exec();
}
#ifdef Q_OS_MAC
void StateMachine::dockEvent(void* param)
{
    StateMachine* pThis = (StateMachine*)param;
    if(pThis == NULL)
        return;
    Q_ASSERT(pThis);
    if(pThis->_mainWidget != NULL)
        if(pThis->_mainWidget->isHidden())
            pThis->_mainWidget->show();
}

#endif
