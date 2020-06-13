#ifndef TNLOADINGHOSITORY_H
#define TNLOADINGHOSITORY_H

#include <QWidget>
#include <QMovie>
#include "ui_tnloadinghository.h"

class tnLoadingHository : public QWidget
{
	Q_OBJECT

public:
	tnLoadingHository(QWidget *parent = 0);
	~tnLoadingHository();

private:
	Ui::tnLoadingHository ui;
	QMovie*		_pMovie;
};

#endif // TNLOADINGHOSITORY_H
