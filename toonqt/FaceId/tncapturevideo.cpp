#include "tncapturevideo.h"
#include "baseimagelist.h"
#include "faceid_global.h"

TNCaptureVideo::TNCaptureVideo(QObject* parent) : QObject(parent)
  ,_camera(NULL)
  ,_frameGrabber(NULL)
  ,_faceTracking(NULL)
{
    qRegisterMetaType<QVector<QRect>>("");
}

TNCaptureVideo::~TNCaptureVideo()
{
    if(_camera){
        _camera->stop();
        delete _camera;
        _camera = NULL;
    }
    if(_frameGrabber){
        delete _frameGrabber;
        _frameGrabber = NULL;
    }
    if(_faceTracking){
        delete _faceTracking;
        _faceTracking = NULL;
    }
    BaseImageList::releaseInstance();
}

QList<QCameraInfo> TNCaptureVideo::enumCamera()
{
    return QCameraInfo::availableCameras();
}

bool TNCaptureVideo::startCapture()
{
    QList<QCameraInfo> list_info = enumCamera();
    if(list_info.isEmpty()){
        qInfo() << "[faceId] [TNCaptureVideo] enumCamera 0";
        emit compareResult(Face_Device_Error);
        return false;
    }
    QCameraInfo defaultCamera = QCameraInfo::defaultCamera();
    if(defaultCamera.isNull()){
        qInfo() << "[faceId] [TNCaptureVideo] defaultCamera 0";
        return false;
    }
    _camera = new QCamera(defaultCamera);
    _frameGrabber = new CameraFrameGrabber();
    _camera->setCaptureMode(QCamera::CaptureVideo);
    _camera->setViewfinder(_frameGrabber);
    connect(_frameGrabber,SIGNAL(frameAvailable(QImage)),this,
            SLOT(onFrameAvaliable(QImage)));
    connect(_camera,SIGNAL(error(QCamera::Error)),
            this,SLOT(errorCamera(QCamera::Error)));
    _camera->start();

    _faceTracking = new FaceTracking();

    connect(_faceTracking,SIGNAL(detectFaceRect(QVector<QRect>)),
            this,SIGNAL(detectFaceRects(QVector<QRect>)));
    connect(_faceTracking,SIGNAL(compareTrackRes(int)),
            this,SIGNAL(compareResult(int)));
    return _faceTracking->start();
}


void TNCaptureVideo::errorCamera(QCamera::Error)
{
    qInfo() << "[faceId] [TNCaptureVideo] camera error:" << _camera->errorString();
}

void TNCaptureVideo::onFrameAvaliable(QImage image)
{
    BaseImageList::getInstance()->appendImage(image);
    emit grabImage(image);
}

void TNCaptureVideo::setReconPhoneNum(const QString &phone_num)
{
    _faceTracking->setReconPhoneNum(phone_num);
}
