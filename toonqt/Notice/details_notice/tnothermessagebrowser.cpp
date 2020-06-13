#include "tnothermessagebrowser.h"
#include <QDebug>

TNOtherMessageBrowser::TNOtherMessageBrowser(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
    this->setStyleSheet("background-color: #F8F8F8; border-radius: 2px;padding: 3px 5px;");
}

TNOtherMessageBrowser::~TNOtherMessageBrowser()
{

}

void TNOtherMessageBrowser::setMessage(const QString& data)
{
	ui.label_othermessage_notify->setWordWrap(false);
	ui.label_othermessage_notify->setText(data);
	ui.label_othermessage_notify->adjustSize();
	int width = ui.label_othermessage_notify->width();
	if (width >= this->maximumWidth() - 30){
		ui.label_othermessage_notify->setFixedWidth(maximumWidth() - 30);
	}
	else{
		ui.label_othermessage_notify->setFixedWidth(width);
	}
	ui.label_othermessage_notify->setWordWrap(true);
	ui.label_othermessage_notify->setText(data);
	ui.label_othermessage_notify->adjustSize();
    int notify_height = ui.label_othermessage_notify->height();
    this->setFixedHeight(notify_height + 6);
}

void TNOtherMessageBrowser::paintEvent(QPaintEvent *event)
{
    return QWidget::paintEvent(event);
}
