#include "TNWebEngineUrlRequestInterceptor.h"

#include <QDebug>
#include <QMutex>

TNWebEngineUrlRequestInterceptor* TNWebEngineUrlRequestInterceptor::m_instance = NULL;
TNWebEngineUrlRequestInterceptor::TNWebEngineUrlRequestInterceptor(QObject *parent) : QWebEngineUrlRequestInterceptor(parent)
{

}

void TNWebEngineUrlRequestInterceptor::interceptRequest(QWebEngineUrlRequestInfo &info)
{
    info.setHttpHeader("Accept-Language", "zh-CN,zh;q=0.8");
}

TNWebEngineUrlRequestInterceptor* TNWebEngineUrlRequestInterceptor::getInstance()
{
    static QMutex s_mutex;
    if (m_instance == NULL)
    {
        QMutexLocker locker(&s_mutex);
        if (m_instance == NULL)
        {
            m_instance = new TNWebEngineUrlRequestInterceptor();
        }
    }

    return m_instance;
}
