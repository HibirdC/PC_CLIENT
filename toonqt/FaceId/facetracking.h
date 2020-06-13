#ifndef FACETRACKING_H
#define FACETRACKING_H

#include <QObject>
#include <thread>
#include "arcsoft_fsdk_face_tracking.h"
#include "facerecognition.h"
#include <QRect>
class FaceTracking : public QObject
{
    Q_OBJECT
public:
    explicit FaceTracking(QObject* parent = NULL);
    ~FaceTracking();
    bool start();
    void setReconPhoneNum(const QString& phone_num);
Q_SIGNALS:
    void detectFaceRect(QVector<QRect> faceRects);
    void compareTrackRes(int nRes);
private:
    static void function_t(void* ptr);
    bool initFaceEngine();
    bool useFaceTracking(const QImage& image);
private:
    std::thread* 		_thread;
    bool 				_stop;
    MByte*          	_faceTrackWorkMem;
    MHandle 			_hEngine;
    FaceRecognition*	_faceR;
};

#endif // FACETRACKING_H
