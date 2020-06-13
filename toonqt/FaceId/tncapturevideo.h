#ifndef TNCAPTUREVIDEO_H
#define TNCAPTUREVIDEO_H

#include <QObject>
#include <QList>
#include <QCamera>
#include <QCameraInfo>
#include <thread>
#include "cameraframegrabber.h"
#include "facetracking.h"

class TNCaptureVideo : public QObject
{
    Q_OBJECT
public:
    TNCaptureVideo(QObject* parent = NULL);
    ~TNCaptureVideo();
    static QList<QCameraInfo> enumCamera();
    bool startCapture();
    void setReconPhoneNum(const QString& phone_num);
Q_SIGNALS:
    void grabImage(QImage image);
    void detectFaceRects(QVector<QRect> faceRects);
    void compareResult(int nRes);
private Q_SLOTS:
    void errorCamera(QCamera::Error);
    void onFrameAvaliable(QImage image);
private:
    QCamera*	  			_camera;
    CameraFrameGrabber*		_frameGrabber;
    FaceTracking*			_faceTracking;
};

#endif // TNCAPTUREVIDEO_H
