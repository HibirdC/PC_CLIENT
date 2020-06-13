#ifndef TNUNREADMSGLISTW_H
#define TNUNREADMSGLISTW_H

#include <QWidget>
#include <QEvent>
#include <QPainter>
#include <QTimer>
#include "TNUnReadMsgAdapter.h"
#include "TNUnReadListDelegate.h"
#include "ui_TNUnReadMsgListW.h"

class TNUnReadMsgListW : public QWidget
{
	Q_OBJECT

public:
	explicit TNUnReadMsgListW(QWidget *parent = 0);
	~TNUnReadMsgListW();

	void setDelegate(TNUnReadListDelegate *delegate);
	void setModel(TNUnReadMsgModel *model);
	void setTotalCount(int count);
	void setViewHeight(int height);
	void delayHide();
	void showWindow();
	void showWindowStatus(bool status);

private slots:
	void delayHideSlot();
protected:
	bool event(QEvent *event);
    virtual void paintEvent(QPaintEvent *event);

Q_SIGNALS:
	void unReadListAreaClicked(const QModelIndex &);
	void ignoreAll(bool);

private:
	Ui::TNUnReadMsgListW *ui;
	QTimer _delayTimer;
	bool _bFocus;
};

#endif // TNUNREADMSGLISTW_H
