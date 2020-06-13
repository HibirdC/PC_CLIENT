#include "TNImageLoadThread.h"

#include <QTime>
#include <QDebug>
#include <QMouseEvent>
#include <QMutexLocker>

#include "tnimagectr.h"

TNImageLoadThread::TNImageLoadThread(const QString &filename, const QSize &targetSize, QObject *parent) :
    QThread(parent), m_fileName(filename), m_targetSize(targetSize)
{

}

void TNImageLoadThread::run()
{
    QMutexLocker mutexLocker(&m_mutex);
    QTime time;
    time.start();
    QSize size(m_targetSize);
    TNImageCtr::speedLoadImage(m_fileName, true, m_targetImage, size);
    qDebug()<<"[Notice][TNImageLoadThread]QImage-load-time="<<time.elapsed();
    if (m_targetImage.isNull())
    {
        emit loadFailed(m_fileName);
    }
    else
    {
        emit loadFinished(m_fileName, m_targetImage);
    }
}
