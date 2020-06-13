#ifndef TNAVATARCHOICEITEM_H
#define TNAVATARCHOICEITEM_H

#include <QWidget>
#include "ui_TNAvatarChoiceItem.h"
#include "TNMVD_global.h"
#include "tncommondealavator.h"

class TNAvatarChoiceItem : public QWidget
{
	Q_OBJECT

public:
	TNAvatarChoiceItem(QModelIndex index, QWidget *parent = 0);
	~TNAvatarChoiceItem();

	void setDialogID(const QString &dialogID);
	void setPhoto(const QString &resid, const QString &defaultImg, Cust_Type type);
	void setTitle(const QString &title);
	void setSelected(bool isSelect);
	QString & getDialogID(){ return _dialogID; };
	bool getSelected(){ return _selected; }
	void setCurrentStatus(bool status);
	void setCurrentUnRead(bool status);
protected:
	virtual void paintEvent(QPaintEvent *event);
private:
	QString _dialogID;
	bool		_selected;
	const QModelIndex _index;
	QLabel * _unReadCount;
private:
	Ui::TNAvatarChoiceItem *ui;

signals:
	void photoClicked(const QModelIndex &index);
private slots:
	void onPhotoButtonClicked();
};

#endif // TNAVATARCHOICEITEM_H
