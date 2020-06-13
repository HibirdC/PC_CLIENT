#ifndef TNSKINSET_H
#define TNSKINSET_H

#include <QWidget>
#include "ui_TNSkinSet.h"
class TNSkinSet : public QWidget
{
	Q_OBJECT

public:
	TNSkinSet(QWidget *parent = 0);
	~TNSkinSet();
private:
	void InitUI();
	void ResetCheck();
private slots:
	void OnClickApplySkinBlueSlot();
	void OnClickApplySkinPinkSlot();
	void OnClickApplySkinGreenSlot();
	void OnClickApplySkinTeaSlot();
	void OnClickApplySkinOrangeSlot();
	void OnClickApplySkinOrchidSlot();
	void OnClickApplySkinBudSlot();
	void OnClickApplySkinPurpleSlot();
private:
	void OnClickApplySkin(int type);
private:
	Ui::TNSkinSet ui;
	QList<QPushButton*> _listSkinBtn;
};
#endif // TNSKINSET_H
