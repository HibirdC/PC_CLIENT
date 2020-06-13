#ifndef MACQAPPLICATION_H
#define MACQAPPLICATION_H

#include <QApplication>
#include <QObject>
#include "singleapplication.h"
class QLocalServer;

class macQApplication : public SingleApplication
{
    Q_OBJECT
public:
    explicit macQApplication(int &argc,char** argv);
    typedef void (*DockEvent)(void*);
    void setDockFunc(DockEvent dockEvent,void* param);
    void onClickOnDock();

private:
    DockEvent 	m_dockEvent;
    void*	  	m_param;
};

#endif // MACQAPPLICATION_H
