#include "tnoutlinemessagethread.h"
#include "TNDataCache.h"
#include "noticelistmodel.h"

TNOutLineMessageThread::TNOutLineMessageThread(NoticeListModel* model,
  QObject* parent) : QObject(parent)
  ,_model(model)
  ,_thread(NULL)
  ,_bStop(false)
{
}

TNOutLineMessageThread::~TNOutLineMessageThread()
{
    _bStop = true;
    _thread->join();
    delete _thread;
    _thread = NULL;
}

void TNOutLineMessageThread::start()
{
    _thread = new std::thread(function_t,this);
}

void TNOutLineMessageThread::function_t(void* ptr)
{
    TNOutLineMessageThread* _this = (TNOutLineMessageThread*)ptr;
    while(true){
        if(_this->_bStop)
            return;
        if(_this->_list_out_line_session.empty()){
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            continue;
        }
        _this->_mutex.lock();
        QString sessionId = _this->_list_out_line_session.front();
        _this->_list_out_line_session.pop_front();
        _this->_mutex.unlock();
        //从数据库读会话
        TNMessageListAdapter* new_session = _this->_model->createNewSession(sessionId);
        if(!new_session){
            continue;
        }
        TNMessageListAdapter tmp_session = *new_session;
        delete new_session;
        new_session = NULL;
        //更新最外层的名片红点信号,根据当前用户会话更新
        emit _this->main_view_operate(tmp_session);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void TNOutLineMessageThread::push_outline_session(const QString &sessionId)
{
    _mutex.lock();
    _list_out_line_session.push_back(sessionId);
    _mutex.unlock();
}
