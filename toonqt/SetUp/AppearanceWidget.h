#ifndef APPEARANCEWIDGET_H
#define APPEARANCEWIDGET_H

#include <QWidget>
#include "ui_AppearanceWidget.h"

class AppearanceWidget : public QWidget
{
	Q_OBJECT

public:
	AppearanceWidget(QWidget *parent = 0);
	~AppearanceWidget();

private:
	Ui::AppearanceWidget ui;
};

#endif // APPEARANCEWIDGET_H
