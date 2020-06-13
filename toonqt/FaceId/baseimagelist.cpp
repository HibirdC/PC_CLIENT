#include "baseimagelist.h"
#include <QDebug>

BaseImageList* BaseImageList::_baseImageListPtr=NULL;

BaseImageList::BaseImageList()
{

}

BaseImageList::~BaseImageList()
{
    clearFrData();
    _face_tracking_list.clear();
}

BaseImageList* BaseImageList::getInstance()
{
    if(_baseImageListPtr == NULL){
        _baseImageListPtr = new BaseImageList();
    }
    return _baseImageListPtr;
}

void BaseImageList::releaseInstance()
{
    if(_baseImageListPtr != NULL){
        delete _baseImageListPtr;
        _baseImageListPtr = NULL;
    }
}


void BaseImageList::appendImage(const QImage &image)
{
    _face_tracking_mutex.lock();
    if(_face_tracking_list.size() >= 25){
        qDebug() << "face_tracking list full";
        _face_tracking_list.pop_back();
    }
    _face_tracking_list.push_front(image);
    _face_tracking_mutex.unlock();
}

bool BaseImageList::getNewestImage(QImage &image)
{
    _face_tracking_mutex.lock();
    if(_face_tracking_list.empty()){
        _face_tracking_mutex.unlock();
        return false;
    }
    image = _face_tracking_list.front();
    _face_tracking_list.pop_front();
    _face_tracking_mutex.unlock();
    return true;
}

void BaseImageList::appendFrData(const FR_data &data)
{
    _face_recognition_mutex.lock();
    if(_face_recognition_list.size() >= 25){
        _face_recognition_list.pop_back();
    }
    _face_recognition_list.push_front(data);
    _face_recognition_mutex.unlock();
}

bool BaseImageList::getFrData(FR_data &data)
{
    _face_recognition_mutex.lock();
    if(_face_recognition_list.empty()){
        _face_recognition_mutex.unlock();
        return false;
    }
    data = _face_recognition_list.front();
    _face_recognition_list.pop_front();
    _face_recognition_mutex.unlock();
    return true;
}

void BaseImageList::clearFrData()
{
    _face_recognition_mutex.lock();
    _face_recognition_list.clear();
    _face_recognition_mutex.unlock();
}
