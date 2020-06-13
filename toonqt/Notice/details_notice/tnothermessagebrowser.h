#ifndef TNOTHERMESSAGEBROWSER_H
#define TNOTHERMESSAGEBROWSER_H

#include <QWidget>
#include "ui_tnothermessagebrowser.h"

class TNOtherMessageBrowser : public QWidget
{
	Q_OBJECT

public:
	TNOtherMessageBrowser(QWidget *parent = 0);
	~TNOtherMessageBrowser();
	void setMessage(const QString& data);
	void paintEvent(QPaintEvent *event);
private:
	Ui::TNOtherMessageBrowser ui;
};

#endif // TNOTHERMESSAGEBROWSER_H
