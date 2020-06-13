#ifndef TNEXITLOGINWIDGET_H
#define TNEXITLOGINWIDGET_H

#include <QWidget>
#include "ui_TNExitLoginWidget.h"
#include "common_global.h"

class TNExitLoginWidget : public QWidget
{
	Q_OBJECT

public:
	TNExitLoginWidget(TNPluginParamPtr pluginParam, QWidget *parent = 0);
	~TNExitLoginWidget();

Q_SIGNALS:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Sends the quit signal. </summary>
	///
	/// <remarks>	Ìïºã, 2017/4/14. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void SendQuitSignal();

private slots:
	void slotExitLoginDialog();
	void on_notifyNetStatus(int);

private:
	Ui::TNExitLoginWidget ui;
    int _netStatus;//网络状态
	TNPluginParamPtr _pluginParam;
};

#endif // TNEXITLOGINWIDGET_H
