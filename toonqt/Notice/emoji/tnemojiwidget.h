#ifndef TNEMOJIWIDGET_H
#define TNEMOJIWIDGET_H

#include <QWidget>
#include "ui_tnemojiwidget.h"

class TNEmojiWidget : public QWidget
{
	Q_OBJECT

public:
	TNEmojiWidget(QWidget *parent = 0);
	~TNEmojiWidget();
protected:
	void focusOutEvent(QFocusEvent *event);
    virtual void paintEvent(QPaintEvent *event);
private:
	Ui::TNEmojiWidget ui;
};

#endif // TNEMOJIWIDGET_H
