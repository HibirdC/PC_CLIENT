#ifndef TNATLISTITEMWIDGET_H
#define TNATLISTITEMWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QModelIndex>

#include "common_global.h"
#include "TNMVD_global.h"


namespace Ui {
	class TNATListItemWidget;
}

class TNATListItemWidget : public QWidget
{
	Q_OBJECT

public:
	TNATListItemWidget(QModelIndex index, QWidget *parent = 0);
	~TNATListItemWidget();

	void setDialogID(const QString &dialogID);
	void setPhoto(const QString &resid, const QString &defaultImg, Cust_Type type);
	void setTitle(const QString &title);
	void setSelected(bool isSelect);
	QString & getDialogID(){ return _dialogID; };
	bool getSelected(){ return _selected; }

protected:
	virtual void enterEvent(QEvent * event);
	virtual void leaveEvent(QEvent *event);
	virtual void paintEvent(QPaintEvent *event);
private:
	Ui::TNATListItemWidget *ui;
	QString _dialogID;
	bool		_selected;
	const QModelIndex _index;
};

#endif // TNATLISTITEMWIDGET_H
