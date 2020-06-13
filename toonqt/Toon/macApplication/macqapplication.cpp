#include "macqapplication.h"
#include <QDebug>
#include <QWidget>
#ifdef Q_OS_MAC
#include <objc/objc.h>
#include <objc/message.h>
bool dockClickHandler(id self,SEL _cmd,...)
{
    Q_UNUSED(self)
    Q_UNUSED(_cmd)
    ((macQApplication*)qApp)->onClickOnDock();
    return true;
}
#endif

macQApplication::macQApplication(int &argc,char** argv) : SingleApplication(argc,argv)
{
#ifdef Q_OS_MAC
    m_dockEvent = NULL;
    m_param = NULL;
    Class cls = objc_getClass("NSApplication");
    objc_object *appInst = objc_msgSend((objc_object*)cls, sel_registerName("sharedApplication"));
    if(appInst != NULL) {
        objc_object* delegate = objc_msgSend(appInst, sel_registerName("delegate"));
        Class delClass = (Class)objc_msgSend(delegate,  sel_registerName("class"));
        SEL shouldHandle = sel_registerName("applicationShouldHandleReopen:hasVisibleWindows:");
        if (class_getInstanceMethod(delClass, shouldHandle)) {
            if (class_replaceMethod(delClass, shouldHandle, (IMP)dockClickHandler, "B@:"))
                qDebug() << "Registered dock click handler (replaced original method)";
            else
                qWarning() << "Failed to replace method for dock click handler";
        }else{
            if (class_addMethod(delClass, shouldHandle, (IMP)dockClickHandler,"B@:"))
                qDebug() << "Registered dock click handler";
            else
                qWarning() << "Failed to register dock click handler";
        }
    }
#endif
}

void macQApplication::onClickOnDock()
{
    if(m_dockEvent != NULL){
        m_dockEvent(m_param);
    }
}

void macQApplication::setDockFunc(DockEvent dockEvent,void *param)
{
    m_param = param;
    m_dockEvent = dockEvent;
}
