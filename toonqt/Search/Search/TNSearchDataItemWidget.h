#ifndef TNSEARCHDATAITEMWIDGET_H
#define TNSEARCHDATAITEMWIDGET_H

#include <QWidget>
#include "ui_TNSearchDataItemWidget.h"

#include "common_global.h"
#include "search_global.h"


class SEARCH_EXPORT TNSearchDataItemWidget : public QWidget
{
	Q_OBJECT

public:
	TNSearchDataItemWidget(QModelIndex index, QWidget *parent = 0);
	~TNSearchDataItemWidget();
	static TNSearchDataItemWidget *s_lastSeleted;

	void setFeedID(const QString &dialogID);
	void setMyFeedID(const QString &dialogID);
	void setPhoto(const QString &resid, const QString &defaultImg, QSize photoSize = QSize(30, 30));
	void setMyPhoto(const QString &resid, const QString &defaultImg, QSize photoSize = QSize(20, 20));
	void setTitle(const QString &title);

	void setSex(const QString &sex);
	void setAge(int age);

	void setSexLabelVisible(bool visible);
	void setAgeLabelVisible(bool visible);
	void setMyPhotoVisible(bool visibal);
	void setArrowVisible(bool visibal);
	const QString & getDialogID(){ return _dialogID; };
	const QString & getBelongFeedId(){ return _belongFeedID; }
	void setSelected(bool isSelect);
	void setTypeString(const QString &typeQString){ _typeString = typeQString; }
	const QString & getTypeString(){ return _typeString; }

private:
	Ui::TNSearchDataItemWidget *ui;


signals:
	void photoClicked(const QModelIndex &index);

protected slots:
	void onPhotoButtonClicked();

protected:
	QString _dialogID;
	QString _belongFeedID;
	virtual void enterEvent(QEvent * event);
	virtual void leaveEvent(QEvent *event);
	virtual void paintEvent(QPaintEvent *event);
	Cust_Type GetPhotoType(const QString &feedId);
private:
	bool		_selected;
	const QModelIndex _index;
	QString _typeString;
};

#endif // TNSEARCHDATAITEMWIDGET_H
