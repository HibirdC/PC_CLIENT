#ifndef FACERECOGNITION_H
#define FACERECOGNITION_H

#include <QObject>
#include <thread>
#include <list>
#include <QTimer>
#include "arcsoft_fsdk_face_recognition.h"
#include "buildfacemodel.h"

struct FR_data;

class FaceRecognition : public QObject
{
    Q_OBJECT
public:
    explicit FaceRecognition(QObject* parent = NULL);
    ~FaceRecognition();
    bool start();
    bool getReady(){return _ready;}
    void setPhoneNum(const QString& phone_num);
Q_SIGNALS:
    void compareResult(int nRes);
    void startCompareTimer();
private Q_SLOTS:
    void timerSlot();
    void compareTimerSlot();
    void compareResultSlot(int nRes);
private:
    bool buildModel(const QString& path);
    bool initFaceREngine();
    static void function_t(void* ptr);
    static void build_model_function_t(void* ptr);
    void recognition(FR_data* data);
private:
    MByte* 			_pWorkMem;
    MHandle			_hEngine;
    std::thread* 	_thread;
    std::thread*	_build_model_thread;
    bool 		 	_stop;
    bool 			_ready;
    BuildFaceModel* _buildFaceModel;
    std::list<AFR_FSDK_FACEMODEL*> _list_local_models;
    int 			_compared_num;//比中次数
    QTimer*			_timer;
    //人脸比对对应的电话<-->model
    QString 		_phone_num;
};

#endif // FACERECOGNITION_H
