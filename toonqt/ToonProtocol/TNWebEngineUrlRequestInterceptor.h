#ifndef TNWebEngineUrlRequestInterceptor_H
#define TNWebEngineUrlRequestInterceptor_H

#include "ToonProtocol_global.h"
#include <QWebEngineUrlRequestInterceptor>

class TOONPROTOCOL_EXPORT TNWebEngineUrlRequestInterceptor : public QWebEngineUrlRequestInterceptor
{
    Q_OBJECT

public:
    explicit TNWebEngineUrlRequestInterceptor(QObject *parent = Q_NULLPTR);
    virtual void interceptRequest(QWebEngineUrlRequestInfo &info);

    // 为了解决崩溃的问题，这里讲TNWebEngineUrlRequestInterceptor定义为一个全局变量不释放（QTBUG-59876）
public:
    static TNWebEngineUrlRequestInterceptor *getInstance();

private:
    static TNWebEngineUrlRequestInterceptor* m_instance;
};

#endif // TNWebEngineUrlRequestInterceptor_H

