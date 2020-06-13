#include "facetracking.h"
#include "baseimagelist.h"
#include "tnimagehelper.h"
#include "faceid_global.h"
#include "merror.h"
#include <QDebug>

FaceTracking::FaceTracking(QObject* parent) : QObject(parent)
  ,_thread(NULL)
  ,_stop(false)
  ,_faceTrackWorkMem(NULL)
  ,_hEngine(NULL)
  ,_faceR(NULL)
{

}

FaceTracking::~FaceTracking()
{
    _stop = true;
    if(_thread){
        _thread->join();
        delete _thread;
        _thread = NULL;
    }
    AFT_FSDK_UninitialFaceEngine(_hEngine);
    if(_faceTrackWorkMem){
        delete [] _faceTrackWorkMem;
        _faceTrackWorkMem = NULL;
    }
    //faceR end
    if(_faceR){
        delete _faceR;
        _faceR = NULL;
    }
}

bool FaceTracking::start()
{
    bool flag = false;
    if(initFaceEngine()){
        //人脸识别
        _faceR = new FaceRecognition(this);
        connect(_faceR,SIGNAL(compareResult(int)),
                this,SIGNAL(compareTrackRes(int)));
        flag = _faceR->start();
        //人脸跟踪线程
        _thread = new std::thread(function_t,this);
    }else{
        emit compareTrackRes(Face_Init_Failed);
        return false;
    }
    return flag;
}

void FaceTracking::function_t(void *ptr)
{
    FaceTracking* _this = (FaceTracking*)ptr;
    while(!_this->_stop){
        QImage image;
        if(!BaseImageList::getInstance()->getNewestImage(image)){
            std::this_thread::sleep_for(std::chrono::milliseconds(25));
            continue;
        }
        _this->useFaceTracking(image);
    }
}

bool FaceTracking::initFaceEngine()
{
    _faceTrackWorkMem = new MByte[FACET_WORK_BUFFERSIZE];
    if(!_faceTrackWorkMem){
        qInfo() << "[faceId] [FaceTracking] new MByte failed";
        return false;
    }
    int ret = AFT_FSDK_InitialFaceEngine((char*)FACE_APPID,(char*)FACE_TRACKING_KEY,
        _faceTrackWorkMem, FACET_WORK_BUFFERSIZE, &_hEngine,
        AFT_FSDK_OPF_0_HIGHER_EXT, 16, FACE_MAX_NUM);
    if(ret != 0){
        qInfo() << "[faceId] [FaceTracking] error code:" << ret;
        delete [] _faceTrackWorkMem;
        _faceTrackWorkMem = NULL;
        return false;
    }
    return true;
}

bool FaceTracking::useFaceTracking(const QImage& image)
{
    ASVLOFFSCREEN inputImg = { 0 };
    inputImg.u32PixelArrayFormat = ASVL_PAF_RGB24_R8G8B8;//ASVL_PAF_RGB24_B8G8R8;
    inputImg.i32Width = image.width();
    inputImg.i32Height = image.height();
    inputImg.pi32Pitch[0] = inputImg.i32Width * 3;
    inputImg.ppu8Plane[0] = (MUInt8*)(image.bits());
    LPAFT_FSDK_FACERES faceResult;
    int ret = AFT_FSDK_FaceFeatureDetect(_hEngine, &inputImg, &faceResult);
    if(ret != 0){
        return false;
    }
    QVector<QRect> faceRects;
    for (int i = 0; i < faceResult->nFace; i++) {
        QRect rect(faceResult->rcFace[i].left,
                   faceResult->rcFace[i].top,
                   faceResult->rcFace[i].right - faceResult->rcFace[i].left,
                   faceResult->rcFace[i].bottom - faceResult->rcFace[i].top);
        faceRects.append(rect);
    }
    if(faceResult->nFace > 0){
        if(_faceR->getReady()){
            FR_data fr_data;
            fr_data.faceAngle = faceResult->lfaceOrient;
            fr_data.imageData = image;
            fr_data.faceRects = faceRects;
            BaseImageList::getInstance()->appendFrData(fr_data);
        }
    }
    emit detectFaceRect(faceRects);
    return true;
}

void FaceTracking::setReconPhoneNum(const QString &phone_num)
{
    if(_faceR != NULL)
        _faceR->setPhoneNum(phone_num);
}
