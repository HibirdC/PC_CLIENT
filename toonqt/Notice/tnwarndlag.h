#ifndef TNWARNDLAG_H
#define TNWARNDLAG_H

#include "DropShadowWidget.h"
#include "ui_tnwarndlag.h"

class TNWarnDlag : public DropShadowWidget
{
	Q_OBJECT

public:
	TNWarnDlag(QWidget *parent = 0);
	~TNWarnDlag();
	void setWarnContent(const QString& content);
protected:
	void focusOutEvent(QFocusEvent *event);
private slots:
	void onClose();
private:
	Ui::TNWarnDlag ui;
};

#endif // TNWARNDLAG_H
