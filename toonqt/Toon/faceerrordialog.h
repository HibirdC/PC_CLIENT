#ifndef FACEERRORDIALOG_H
#define FACEERRORDIALOG_H

#include "DropShadowWidget.h"

namespace Ui {
class FaceErrorDialog;
}

class FaceErrorDialog : public DropShadowWidget
{
    Q_OBJECT

public:
    explicit FaceErrorDialog(QWidget *parent = 0);
    ~FaceErrorDialog();
    void setErrorString(const QString& errorinfo);
Q_SIGNALS:
    void redetect_device();
private slots:
    void on_btn_close_clicked();

    void on_btn_redetect_device_clicked();

private:
    Ui::FaceErrorDialog *ui;
};

#endif // FACEERRORDIALOG_H
