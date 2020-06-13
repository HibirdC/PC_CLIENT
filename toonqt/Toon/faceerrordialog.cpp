#include "faceerrordialog.h"
#include "ui_faceerrordialog.h"

FaceErrorDialog::FaceErrorDialog(QWidget *parent) :
    DropShadowWidget(parent),
    ui(new Ui::FaceErrorDialog)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog | Qt::WindowMinimizeButtonHint);
    ui->setupUi(this);
}

FaceErrorDialog::~FaceErrorDialog()
{
    delete ui;
}

void FaceErrorDialog::on_btn_close_clicked()
{
    this->close();
}

void FaceErrorDialog::on_btn_redetect_device_clicked()
{
    this->close();
    emit redetect_device();
}

void FaceErrorDialog::setErrorString(const QString &errorinfo)
{
    ui->label_camera_status->setText(errorinfo);
}
