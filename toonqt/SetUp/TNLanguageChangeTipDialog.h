#ifndef TNLANGUAGECHANGEDIALOG_H
#define TNLANGUAGECHANGEDIALOG_H

#include "DropShadowWidget.h"
#include <QDialog>

namespace Ui {
class TNLanguageChangeTipDialog;
}

class TNLanguageChangeTipDialog : public /*QDialog*/DropShadowWidget
{
    Q_OBJECT

public:
    explicit TNLanguageChangeTipDialog(QWidget *parent = 0);
    ~TNLanguageChangeTipDialog();

private:
    Ui::TNLanguageChangeTipDialog *ui;
};

#endif // TNLANGUAGECHANGEDIALOG_H
