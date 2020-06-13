#ifndef TNSEARCHITEMWIDGET_H
#define TNSEARCHITEMWIDGET_H

#include <QWidget>
#include "search_global.h"
#include "ui_TNSearchItemWidget.h"
namespace Ui {
	class TNSearchItemWidget;
}

class SEARCH_EXPORT TNSearchItemWidget : public QWidget
{
	Q_OBJECT

public:
	TNSearchItemWidget(const QString labelName, bool show, const QModelIndex &index, QWidget *parent = 0);
	~TNSearchItemWidget();
	void setShowButtonName(QString text);
	void setShowButtonStatus(bool status);
signals:
	void showButtonClicked(const QModelIndex &index,const QString &tagString, const QString &buttonName,bool showType);

protected slots:
	void onShowButtonClicked(bool show);
private:
	Ui::TNSearchItemWidget *ui;
	const QModelIndex _index;
};

#endif // TNSEARCHITEMWIDGET_H
