#ifndef TNSYSTRAY_H
#define TNSYSTRAY_H

#include <QObject>
#include <windows.h>
#include <QLabel>
#include <QMenu>
#include <QPoint>

class TNSysTray :public QObject
{
	Q_OBJECT

public:
	TNSysTray(QWidget *parent);
	~TNSysTray();

	void translateLanguage();
	void showMenu(QPoint pos);
protected:



signals :

	void showWidget();
	void MessageSignal(int);
	void quitAppSignal();

private slots:
	void showSetUp();
	void showLogout();

private:

	void createAction();
	void addActions();

private:

	QMenu *tray_menu; //托盘菜单

	/// <summary>	帮助. </summary>
	QAction *action_help_center;
	/// <summary>	设置. </summary>
	QAction *action_SetUp;
	/// <summary>	关于通. </summary>
	QAction *action_AboutToon;
	/// <summary>	意见反馈. </summary>
	QAction *action_Feedback;
	/// <summary>	升级. </summary>
	QAction *action_rise;
	/// <summary>	打开toon. </summary>
	QAction *action_open;
	/// <summary>	退出. </summary>
	QAction *action_logout;

};

#endif // TNSYSTRAY_H
