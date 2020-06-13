#ifndef TNCHECKUPDATEDIALOG_H
#define TNCHECKUPDATEDIALOG_H

#include "DropShadowWidget.h"

#include <QDialog>

namespace Ui {
	class TNCheckUpdateDialog;
}

class TNCheckUpdateDialog : public /*QDialog*/DropShadowWidget
{
    Q_OBJECT

public:
	explicit TNCheckUpdateDialog(QWidget *parent = 0);
	~TNCheckUpdateDialog();

private:
	Ui::TNCheckUpdateDialog *ui;
};

#endif // TNCHECKUPDATEDIALOG_H
