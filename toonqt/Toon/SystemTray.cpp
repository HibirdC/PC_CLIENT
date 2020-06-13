#include "SystemTray.h"
#include "common_global.h"
#include "TNDataStatistics.h"
#include "TNUserDataHelper.h"
#include "TNVersionInfo.h"
SystemTray::SystemTray(QWidget *parent)
	: QSystemTrayIcon(parent)
{
	this->createAction();
	this->addActions();
	this->translateLanguage();
}

SystemTray::~SystemTray()
{

}

void SystemTray::translateLanguage()
{
	//放在托盘图标上时候显示
	this->setToolTip(TOON_TITLE);

	action_open->setText(("打开"));
	action_help_center->setText(("帮助"));
	action_SetUp->setText(("设置"));
	action_AboutToon->setText(("关于"));
	action_Feedback->setText(("反馈"));
	action_rise->setText(("升级"));
	action_logout->setText(("退出"));
}

void SystemTray::createAction()
{
	setIcon(QIcon(TNVersionInfo::GetSystemTrayRes()));
	tray_menu = new QMenu();
	action_open = new QAction(this);
	action_help_center = new QAction(this);
	action_SetUp = new QAction(this);
	action_AboutToon = new QAction(this);
	action_Feedback = new QAction(this);
	action_rise = new QAction(this);
	action_logout = new QAction(this);

	tray_menu->setFixedWidth(100);

	connect(action_open, SIGNAL(triggered()), this, SIGNAL(showWidget()));
    connect(action_logout, SIGNAL(triggered()), this, SLOT(showLogout()));
	connect(action_SetUp, SIGNAL(triggered()), this, SLOT(showSetUp()));
#ifndef Q_OS_MAC
	this->setContextMenu(tray_menu);
#endif
}

void SystemTray::addActions()
{
	//添加菜单项
	//tray_menu->addAction(action_help_center);
	tray_menu->addAction(action_SetUp);
	//tray_menu->addAction(action_AboutToon);
	//tray_menu->addAction(action_Feedback);
	tray_menu->addSeparator();
	//tray_menu->addAction(action_rise);
	tray_menu->addAction(action_open);
	tray_menu->addAction(action_logout);
}

void SystemTray::showSetUp()
{
    emit MessageSignal(MENU_SETUP_ID);
    emit activated(QSystemTrayIcon::Trigger);
}

void SystemTray::showLogout()
{
    qApp->quit();
}
