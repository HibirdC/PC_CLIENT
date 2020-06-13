#ifndef TNOPFORGETPSDTIPDIALOG_H
#define TNOPFORGETPSDTIPDIALOG_H

#include "DropShadowWidget.h"
#include <QDialog>

namespace Ui {
class TNOpForgetPsdTipDialog;
}

class TNOpForgetPsdTipDialog : public /*QDialog*/DropShadowWidget
{
    Q_OBJECT

public:
    explicit TNOpForgetPsdTipDialog(QWidget *parent = 0);
    ~TNOpForgetPsdTipDialog();

private:
    Ui::TNOpForgetPsdTipDialog *ui;
};

#endif // TNOPFORGETPSDTIPDIALOG_H
