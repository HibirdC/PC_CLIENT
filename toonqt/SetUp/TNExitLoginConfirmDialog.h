#ifndef TNEXITLOGINCONFIRMDIALOG_H
#define TNEXITLOGINCONFIRMDIALOG_H

#include "DropShadowWidget.h"

#include <QDialog>

namespace Ui {
class TNExitLoginConfirmDialog;
}

class TNExitLoginConfirmDialog : public /*QDialog*/DropShadowWidget
{
    Q_OBJECT

public:
    explicit TNExitLoginConfirmDialog(QWidget *parent = 0);
    ~TNExitLoginConfirmDialog();
    void setTitle(const QString &strTitle);
    void setText(const QString &strText);

private:
    Ui::TNExitLoginConfirmDialog *ui;
};

#endif // TNEXITLOGINCONFIRMDIALOG_H
