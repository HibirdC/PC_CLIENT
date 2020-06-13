////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	system_tray.h
// author: 田恒
// date:   2016/12/05
// summary:	系统托盘类
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SYSYTEMTRAY_H
#define SYSYTEMTRAY_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QWidgetAction>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QPainter>

class SystemTray : public QSystemTrayIcon
{
	Q_OBJECT

public:

	explicit SystemTray(QWidget *parent = 0);
	~SystemTray();
	void translateLanguage();

protected:



signals:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Shows the widget. </summary>
	///
	/// <remarks>	田恒, 2016/12/5. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void showWidget();
    void MessageSignal(int);


private slots:
    void showSetUp();
    void showLogout();

private:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Creates the action. </summary>
	///
	/// <remarks>	田恒, 2016/12/5. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void createAction();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Adds actions. </summary>
	///
	/// <remarks>	田恒, 2016/12/5. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

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

#endif //SYSYTEMTRAY_H
