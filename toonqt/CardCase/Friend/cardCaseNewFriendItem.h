#ifndef CARDCASENEWFRIENDITEM_H
#define CARDCASENEWFRIENDITEM_H

#include <QWidget>
#include "ui_cardCaseNewFriendItem.h"
#include <QLabel>
#include "common_global.h"
#include "TNMVD_global.h"

class cardCaseNewFriendItem : public QWidget
{
	Q_OBJECT

public:
	cardCaseNewFriendItem(QModelIndex index, QWidget *parent = 0);
	~cardCaseNewFriendItem();

	void setDialogID(const QString &dialogID);
	void setPhoto(const QString &resid, const QString &defaultImg, Cust_Type type, QSize photoSize = QSize(40, 40));
	void setTitle(const QString &title);
	QString & getDialogID(){ return _dialogID; }

    int getNewRequestNumber() const;
    void setNewRequestNumber(int number);
	void setSelected(bool isSelect);

signals:
	void doubleClicked();
	void photoClicked(const QModelIndex &index);

protected slots:
	void onPhotoButtonClicked();

protected:
	virtual void paintEvent(QPaintEvent *event);
	virtual void enterEvent(QEvent * event);
	virtual void leaveEvent(QEvent *event);

private:
	Ui::cardCaseNewFriendItem *ui;
	const QModelIndex _index;
	QString _dialogID;
	QLabel * _numberLabel;
    int m_number;
	bool		_selected;
};

#endif // CARDCASENEWFRIENDITEM_H
