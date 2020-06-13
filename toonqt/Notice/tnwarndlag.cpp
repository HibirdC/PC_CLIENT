#include "tnwarndlag.h"

TNWarnDlag::TNWarnDlag(QWidget *parent)
: DropShadowWidget(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton_notify_close, SIGNAL(clicked()), this, SLOT(onClose()));
}

TNWarnDlag::~TNWarnDlag()
{

}

void TNWarnDlag::setWarnContent(const QString& content)
{
	ui.label_notify->setText(content);
}

void TNWarnDlag::onClose()
{
	hide();
}

void TNWarnDlag::focusOutEvent(QFocusEvent *event)
{
	QWidget::focusOutEvent(event);
	hide();
}
