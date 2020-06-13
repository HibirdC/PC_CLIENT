#ifndef TNCHECKUPDATEINFODIALOG_H
#define TNCHECKUPDATEINFODIALOG_H

#include "DropShadowWidget.h"

#include <QDialog>

namespace Ui {
class TNCheckUpdateInfoDialog;
}

class TNCheckUpdateInfoDialog : public /*QDialog*/DropShadowWidget
{
    Q_OBJECT

public:
    explicit TNCheckUpdateInfoDialog(
            bool isForceUpgrade,
            QString downLoadURL,
            QString versionDesc,
            QWidget *parent = 0);
    ~TNCheckUpdateInfoDialog();

private slots:
    void slotNowUpgrade();
    void slotRemindAfter();

protected:
    virtual void closeEvent(QCloseEvent *event);

private:
    void doUpgrade();

private:
    Ui::TNCheckUpdateInfoDialog *ui;
    QString _downLoadURL;
};

#endif // TNCHECKUPDATEINFODIALOG_H
