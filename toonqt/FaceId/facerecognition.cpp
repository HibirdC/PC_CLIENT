#include "facerecognition.h"
#include "faceid_global.h"
#include "merror.h"
#include "tnimagehelper.h"
#include "baseimagelist.h"
#include "TNPathUtil.h"
#include "TNDataControlServer.h"
#include "tnimagectr.h"
#include <QImage>
#include <QDebug>
#include <QDir>

FaceRecognition::FaceRecognition(QObject* parent) : QObject(parent)
  ,_pWorkMem(NULL)
  ,_hEngine(NULL)
  ,_thread(NULL)
  ,_build_model_thread(NULL)
  ,_stop(false)
  ,_ready(false)
  ,_buildFaceModel(NULL)
  ,_compared_num(0)
  ,_timer(NULL)
{
    connect(this,SIGNAL(startCompareTimer()),
            this,SLOT(compareTimerSlot()));
    connect(this,SIGNAL(compareResult(int)),
            this,SLOT(compareResultSlot(int)));
}

FaceRecognition::~FaceRecognition()
{
    _stop = true;
    if(_thread){
        _thread->join();
        delete _thread;
        _thread = NULL;
    }
    if(_build_model_thread){
        _build_model_thread->join();
        delete _build_model_thread;
        _build_model_thread = NULL;
    }
    AFR_FSDK_UninitialEngine(_hEngine);
    if(_pWorkMem){
        delete [] _pWorkMem;
        _pWorkMem = NULL;
    }
    if(_buildFaceModel){
        delete _buildFaceModel;
        _buildFaceModel = NULL;
    }

    std::list<AFR_FSDK_FACEMODEL*>::iterator itera = _list_local_models.begin();
    for(;itera != _list_local_models.end();++itera){
        AFR_FSDK_FACEMODEL* model_fea = *itera;
        delete [] model_fea->pbFeature;
        delete model_fea;
    }
    if(_timer){
        delete _timer;
        _timer = NULL;
    }
}

bool FaceRecognition::initFaceREngine()
{
    _pWorkMem = new MByte[FACER_WORK_BUFFERSIZE];
    if(!_pWorkMem){
        qInfo() << "[faceId] [FaceRecognition] new MByte failed line:" << __LINE__;
        return false;
    }
    int ret = AFR_FSDK_InitialEngine((char*)FACE_APPID,(char*)FACE_RECOGNITION_KEY,
        _pWorkMem,FACER_WORK_BUFFERSIZE,&_hEngine);
    if(ret != 0){
        qInfo() << "[faceId] [FaceRecognition] initFaceREngine error_code:" << ret;
        delete [] _pWorkMem;
        _pWorkMem = NULL;
        return false;
    }
    return true;
}

bool FaceRecognition::buildModel(const QString &path)
{
    if(!_buildFaceModel){
        _buildFaceModel = new BuildFaceModel();
    }
    if(!_buildFaceModel->getInited()){
        return false;
    }
    LPAFD_FSDK_FACERES faceRes = NULL;
    ASVLOFFSCREEN offInput = {0};
    if(!_buildFaceModel->inputFaceModelImage(path,&faceRes,offInput)){
        return false;
    }
    for (int i = 0; i < faceRes->nFace; i++){
        AFR_FSDK_FACEMODEL localFaceModels = {0};
        AFR_FSDK_FACEINPUT faceLocation = {0};
        faceLocation.rcFace = faceRes->rcFace[i];
        faceLocation.lOrient = faceRes->lfaceOrient[i];
        int mRet = AFR_FSDK_ExtractFRFeature(_hEngine,&offInput,&faceLocation,&localFaceModels);
        if (mRet != MOK){
            continue;
        }
        AFR_FSDK_FACEMODEL* save_model = new AFR_FSDK_FACEMODEL;
        save_model->lFeatureSize = localFaceModels.lFeatureSize;
        save_model->pbFeature = new MByte[save_model->lFeatureSize];
        memcpy(save_model->pbFeature,localFaceModels.pbFeature,save_model->lFeatureSize);
        _list_local_models.push_back(save_model);
    }
    //释放内存
    delete [] offInput.ppu8Plane[0];
    return true;
}

void FaceRecognition::function_t(void *ptr)
{
    FaceRecognition* _this = (FaceRecognition*)ptr;
    while(!_this->_stop){
        if(!_this->_ready){//比对开关
            std::this_thread::sleep_for(std::chrono::milliseconds(25));
            continue;
        }
        FR_data data;
        if(!BaseImageList::getInstance()->getFrData(data)){
            std::this_thread::sleep_for(std::chrono::milliseconds(25));
            continue;
        }
        _this->recognition(&data);
    }
}

bool FaceRecognition::start()
{
    if(initFaceREngine()){
        //比对线程
        _thread = new std::thread(function_t,this);
    }else{
        emit compareResult(Face_Init_Failed);
        return false;
    }
    return true;
}

void FaceRecognition::build_model_function_t(void *ptr)
{
    FaceRecognition* _this = (FaceRecognition*)ptr;
    bool flag = false;
    qInfo() << "[faceId] [FaceRecognition] buildModel phone num:" << _this->_phone_num;
    //查询数据库电话对应的feed
    TableBaseVec feedVec;
    if(!TNDataControlServer::GetInstance()->Query(feedVec,"FaceId",
        "phone_num",_this->_phone_num,DBTYPE_COMMON)){
        emit _this->compareResult(Face_Model_Failed);
        return;
    }
    QString model_path = TNPathUtil::getFaceModelPath();
    QDir dir(model_path);
    QStringList files = dir.entryList(QStringList(),QDir::Files);
    for(QString file : files){
        bool is_match = false;
        for (TableBaseVec::const_iterator iter = feedVec.begin();
             iter != feedVec.end(); ++iter){
            st_FaceIdPtr st_faceidptr = std::dynamic_pointer_cast<st_FaceId>(*iter);
            if(st_faceidptr->get_feedId() == file){
                is_match = true;
                break;
            }
        }
        if(!is_match){
            continue;
        }
        QString file_path = model_path + file;
        bool isSuccess = _this->buildModel(file_path);
        if(!flag){
            flag = isSuccess;
        }
    }
    if(!flag){
        emit _this->compareResult(Face_Model_Failed);
    }else{
        _this->_ready = true;
    }
}

void FaceRecognition::recognition(FR_data *data)
{
    emit startCompareTimer();
    //提特征
    ASVLOFFSCREEN offInput = {0};
    offInput.i32Height = data->imageData.height();
    offInput.i32Width = data->imageData.width();
    offInput.u32PixelArrayFormat = ASVL_PAF_RGB24_B8G8R8;
    if(data->imageData.format() != QImage::Format_RGB888){
        data->imageData = data->imageData.convertToFormat(QImage::Format_RGB888);
        //data->imageData = data->imageData.rgbSwapped();
    }
    offInput.ppu8Plane[0] = (unsigned char*)data->imageData.bits();
    offInput.pi32Pitch[0] = offInput.i32Width * 3;
    float maxScore = 0.0f;
    for(int i=0;i<data->faceRects.size();++i){
        AFR_FSDK_FACEMODEL localFaceModels = {0};
        AFR_FSDK_FACEINPUT faceLocation = {0};
        faceLocation.rcFace.left = data->faceRects[i].left();
        faceLocation.rcFace.top = data->faceRects[i].top();
        faceLocation.rcFace.right = data->faceRects[i].right();
        faceLocation.rcFace.bottom = data->faceRects[i].bottom();
        faceLocation.lOrient = data->faceAngle;
        int mRet = AFR_FSDK_ExtractFRFeature(_hEngine,&offInput,&faceLocation,&localFaceModels);
        if (mRet != MOK){
            continue;
        }
        //比对
        std::list<AFR_FSDK_FACEMODEL*>::iterator itera = _list_local_models.begin();
        for(;itera != _list_local_models.end();++itera){
            float score = 0.0f;
            AFR_FSDK_FACEMODEL* model_fea = *itera;
            mRet = AFR_FSDK_FacePairMatching(_hEngine,model_fea,&localFaceModels,&score);
            if(mRet != MOK){
                continue;
            }
            maxScore = maxScore > score ? maxScore : score;
        }
    }
    qInfo() << "[faceId] [FaceRecongnition] compare score:" << maxScore;
    if(maxScore > 0.5f){
        //目前的策略是比中5次即比中
        if((++_compared_num) >= 5){
            emit compareResult(Face_Succ);
            return;
        }
    }
}

void FaceRecognition::timerSlot()
{
    //比对超时
    _compared_num = 0;
    _ready = false;
    BaseImageList::getInstance()->clearFrData();
    _timer->stop();
    emit compareResult(Face_Compare_Failed);
}

void FaceRecognition::compareTimerSlot()
{
    if(!_timer){
        _timer = new QTimer(this);
        connect(_timer,SIGNAL(timeout()),this,SLOT(timerSlot()));
        _timer->start(3000);
    }
}

void FaceRecognition::compareResultSlot(int nRes)
{
    switch(nRes){
    case Face_Succ:
        _timer->stop();
        _compared_num = 0;
        _ready = false;
        BaseImageList::getInstance()->clearFrData();
        break;
    default:
        break;
    }
}

void FaceRecognition::setPhoneNum(const QString &phone_num)
{
    _phone_num = phone_num;
    //建模线程
    _build_model_thread = new std::thread(build_model_function_t,this);
}
