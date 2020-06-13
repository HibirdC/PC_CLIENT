#ifndef TNEXITGROUPCHATCONFIRMDIALOG_H
#define TNEXITGROUPCHATCONFIRMDIALOG_H

#include "DropShadowWidget.h"

#include <QDialog>

namespace Ui {
class TNExitGroupChatConfirmDialog;
}

class TNExitGroupChatConfirmDialog : public /*QDialog*/DropShadowWidget
{
    Q_OBJECT

public:
    explicit TNExitGroupChatConfirmDialog(QWidget *parent = 0);
    ~TNExitGroupChatConfirmDialog();

private:
    Ui::TNExitGroupChatConfirmDialog *ui;
};

#endif // TNEXITGROUPCHATCONFIRMDIALOG_H
