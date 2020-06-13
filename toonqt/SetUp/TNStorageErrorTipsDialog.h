#ifndef TNStorageErrorTipsDialog_H
#define TNStorageErrorTipsDialog_H

#include "DropShadowWidget.h"
#include <QDialog>

namespace Ui {
class TNStorageErrorTipsDialog;
}

class TNStorageErrorTipsDialog : public /*QDialog*/DropShadowWidget
{
    Q_OBJECT

public:
    explicit TNStorageErrorTipsDialog(QWidget *parent);
    ~TNStorageErrorTipsDialog();

private:
    Ui::TNStorageErrorTipsDialog *ui;
};

#endif // TNStorageErrorTipsDialog_H
