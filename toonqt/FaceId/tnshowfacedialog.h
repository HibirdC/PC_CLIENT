#ifndef TNSHOWFACEDIALOG_H
#define TNSHOWFACEDIALOG_H

#include "DropShadowWidget.h"
#include "tncapturevideo.h"

namespace Ui {
class TNShowFaceDialog;
}

class TNShowFaceDialog : public	DropShadowWidget
{
    Q_OBJECT

public:
    explicit TNShowFaceDialog(QWidget *parent = 0);
    ~TNShowFaceDialog();
    bool init();
    TNCaptureVideo*		 _captureVideo;//视频捕获,人脸识别
protected:
    void closeEvent(QCloseEvent *);
Q_SIGNALS:
    void self_close();
private Q_SLOTS:
    void showVideo(QImage image);
    void showFaceRects(QVector<QRect> faceRects);
    void on_okButton_clicked();

private:
    Ui::TNShowFaceDialog *ui;
};

#endif // TNSHOWFACEDIALOG_H
