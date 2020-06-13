#include "tnshowfacedialog.h"
#include "ui_tnshowfacedialog.h"
#include "tnimagehelper.h"
#include "faceid_global.h"

TNShowFaceDialog::TNShowFaceDialog(QWidget *parent) :
    DropShadowWidget(parent),
    _captureVideo(NULL),
    ui(new Ui::TNShowFaceDialog)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog | Qt::WindowMinimizeButtonHint);
    ui->setupUi(this);
    _captureVideo = new TNCaptureVideo();
    qRegisterMetaType<QVector<QRect>>("face_rect");
    ui->okButton->setCursor(Qt::PointingHandCursor);
}

TNShowFaceDialog::~TNShowFaceDialog()
{
    if(_captureVideo){
        delete _captureVideo;
        _captureVideo = NULL;
    }
    delete ui;
}

bool TNShowFaceDialog::init()
{
    connect(_captureVideo,SIGNAL(grabImage(QImage)),
            this,SLOT(showVideo(QImage)));
    connect(_captureVideo,SIGNAL(detectFaceRects(QVector<QRect>)),
            this,SLOT(showFaceRects(QVector<QRect>)));
    return _captureVideo->startCapture();
}

void TNShowFaceDialog::showVideo(QImage image)
{
    ui->label_show_video->showImage(image);
}

void TNShowFaceDialog::showFaceRects(QVector<QRect> faceRects)
{
    ui->label_show_video->showFaceRects(faceRects);
}

void TNShowFaceDialog::closeEvent(QCloseEvent *event)
{
    QDialog::closeEvent(event);
    emit self_close();
}

void TNShowFaceDialog::on_okButton_clicked()
{
    close();
}
