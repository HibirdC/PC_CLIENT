#include "buildfacemodel.h"
#include "faceid_global.h"
#include <QImage>
#include <QDebug>
#include "tnimagehelper.h"
#include "merror.h"
#include "tnimagectr.h"

BuildFaceModel::BuildFaceModel(QObject* parent) : QObject(parent)
  ,_pWorkMem(NULL)
  ,_hEngine(NULL)
{
    init();
}

BuildFaceModel::~BuildFaceModel()
{
    AFD_FSDK_UninitialFaceEngine(_hEngine);
    if(_pWorkMem != NULL){
        delete [] _pWorkMem;
        _pWorkMem = NULL;
    }
}

bool BuildFaceModel::init()
{
    _pWorkMem = new MByte[FACED_WORK_BUFFERSIZE];
    if(!_pWorkMem){
        qInfo() << "[faceId] [BuildFaceModel] new MByte failed line:" << __LINE__;
        return false;
    }
    int ret = AFD_FSDK_InitialFaceEngine((char*)FACE_APPID,(char*)FACE_DETECTTION_KEY,_pWorkMem,
        FACED_WORK_BUFFERSIZE,&_hEngine,AFD_FSDK_OPF_0_HIGHER_EXT,16,12);
    if(ret != 0){
        qInfo() << "[faceId] [BuildFaceModel] initEngine failed error_code:" << ret;
        delete [] _pWorkMem;
        _pWorkMem = NULL;
        return false;
    }
    _inited = true;
    return true;
}

bool BuildFaceModel::inputFaceModelImage(const QString& path,
                                         LPAFD_FSDK_FACERES* faceRes,
                                         ASVLOFFSCREEN& offInput)
{
    if(!_inited){
        return false;
    }
    int image_width,image_height;
    unsigned char* data = NULL;
    QImage image;
    QString suffix =TNImageCtr::getImageTypeRetString(path);
    if(!image.load(path,suffix.toStdString().c_str())){
            return false;
    }
    if(image.isNull()){
        return false;
    }
    QImage::Format sample = image.format();
    image_width = image.width();
    image_height = image.height();
    data = new unsigned char[image_width * image_height * 3];
    if(sample == QImage::Format_RGB32){
        TNImageHelper::rgb32tobgr24(image,data);
    }
    offInput = {0};
    offInput.u32PixelArrayFormat = ASVL_PAF_RGB24_B8G8R8;
    offInput.i32Width = image_width;
    offInput.i32Height = image_height;
    offInput.pi32Pitch[0] = offInput.i32Width * 3;
    offInput.ppu8Plane[0] = data;
    //人脸检测
    int mRet = AFD_FSDK_StillImageFaceDetection(_hEngine,&offInput,faceRes);
    if (mRet != MOK){
        delete [] data;
        return false;
    }
    if((*faceRes)->nFace <=0 ){
        delete [] data;
        return false;
    }
    return true;
}

