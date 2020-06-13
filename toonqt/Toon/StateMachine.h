#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <QObject>
#include <QApplication>

#include "common_global.h"
#include "login.h"
#include "Toon.h"
#include "TNStartloadingpage.h"


Q_DECLARE_METATYPE(TNPluginParamPtr)

class TNCheckUpdateInfoDialog;
class StateMachine : public QObject
{
	Q_OBJECT

public:
	StateMachine(QObject *parent = 0);
	~StateMachine();

	void Init(bool enableAutoLogin);
	void InitSkin();
	void ClearData();
	void ShowLoading();
private slots:
	void OnLoginSuccessSlot(TNPluginParamPtr pluginParam);
	void OnLoginOutSlot();
	void on_notifyNetStatus(int);
    void onCheckVersionFinished(
        bool isNeedUpgrade,
        bool isForceUpgrade,
        QString downLoadURL, 
        int nCheckType,
        QString versionDesc
        );
    //检查更新响应函数
    void on_notifyCheckVersionFinished(
        bool isNeedUpgrade,
        bool isForceUpgrade,
        QString downLoadURL,
        int nCheckType,
        QString versionDesc
        );
	void SyncedWithCatcheSlot();
	void SyncedTimeOutSlot();
	void dbOwnerErrorSlot(int dbType);
    void slotApplicationStateChanged(Qt::ApplicationState state);

private:
#ifdef Q_OS_MAC
    static void dockEvent(void* param);
#endif
	void ShowMainFrame(bool bStopLoad);
	bool removeFileContext(const QString &folder);
	void showFixFailed();

    Login * _loginDlg;
    Toon  * _mainWidget;

	TNPluginParamPtr	_pluginParam;
    int _currentStatus;
	TNStartloadingpage *_loadingPage;
signals:
    void connectRestored();
};

#endif // STATEMACHINE_H
