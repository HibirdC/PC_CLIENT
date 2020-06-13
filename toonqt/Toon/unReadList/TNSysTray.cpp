#include "TNSysTray.h"
#include "common_global.h"

TNSysTray::TNSysTray(QWidget *parent)
{
	this->createAction();
	this->addActions();
	this->translateLanguage();
}

TNSysTray::~TNSysTray()
{

}
void TNSysTray::translateLanguage()
{
	action_open->setText(tr(QStringLiteral("打开").toUtf8().data()));
	action_help_center->setText(QStringLiteral("帮助"));
	action_SetUp->setText(tr(QStringLiteral("设置").toUtf8().data()));
	action_AboutToon->setText(QStringLiteral("关于"));
	action_Feedback->setText(QStringLiteral("反馈"));
	action_rise->setText(QStringLiteral("升级"));
	action_logout->setText(tr(QStringLiteral("退出").toUtf8().data()));
}

void TNSysTray::createAction()
{
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
}

void TNSysTray::addActions()
{
	//添加菜单项
	tray_menu->addAction(action_SetUp);
	tray_menu->addSeparator();
	tray_menu->addAction(action_open);
	tray_menu->addAction(action_logout);
}

void TNSysTray::showSetUp()
{
	emit MessageSignal(MENU_SETUP_ID);
	emit showWidget();
}

void TNSysTray::showLogout()
{
	emit quitAppSignal();
}
void TNSysTray::showMenu(QPoint pos)
{
	tray_menu->exec(pos);
}