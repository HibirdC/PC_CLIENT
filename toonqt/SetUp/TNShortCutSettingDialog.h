#ifndef TNSHORTCUTSETTINGDIALOG_H
#define TNSHORTCUTSETTINGDIALOG_H

#include "DropShadowWidget.h"

#include <QDialog>

namespace Ui {
class TNShortCutSettingDialog;
}

class TNShortCutSettingDialog : public /*QDialog*/DropShadowWidget
{
    Q_OBJECT

public:
    explicit TNShortCutSettingDialog(const QString &shortCutText, QWidget *parent = 0);
    ~TNShortCutSettingDialog();

    QString getShortCutText() const;

protected:
    virtual void keyPressEvent(QKeyEvent *event);

private:
    Ui::TNShortCutSettingDialog *ui;

    QString m_screenHotKey;
};

#endif // TNSHORTCUTSETTINGDIALOG_H
