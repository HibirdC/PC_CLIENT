#ifndef TNOUTLINEMESSAGETHREAD_H
#define TNOUTLINEMESSAGETHREAD_H

#include <QObject>
#include <thread>
#include <list>
#include <mutex>
#include "TNMessageListAdapter.h"

class NoticeListModel;//TNMessageListModel;

class TNOutLineMessageThread : public QObject
{
    Q_OBJECT
public:
    TNOutLineMessageThread(NoticeListModel* model,QObject* parent = 0);
    void push_outline_session(const QString& sessionId);
    void start();
    virtual ~TNOutLineMessageThread();
Q_SIGNALS:
    void main_view_operate(TNMessageListAdapter session);
private:
    static void function_t(void* ptr);
private:
    NoticeListModel*	_model;
    std::thread* 	_thread;
    std::list<QString> _list_out_line_session;
    std::mutex		_mutex;
    bool 			_bStop;
};

#endif // TNOUTLINEMESSAGETHREAD_H
