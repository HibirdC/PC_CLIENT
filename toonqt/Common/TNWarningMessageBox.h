#ifndef TNWRANINGMESSAGEBOX_H 
#define TNWRANINGMESSAGEBOX_H 
#include <QMessageBox>
#include <QLabel>
#include <QString>
#include <QEvent>
#include "common_global.h"

class COMMON_EXPORT TNWarningMessageBox : public QDialog
{
	Q_OBJECT

public:
	TNWarningMessageBox(QWidget *parent = 0);
	~TNWarningMessageBox();

public:
    void setMsg(const QString msg);

private:
    QLabel * _msgLabel;
};

#endif // TNMESSAGEBOX_H
