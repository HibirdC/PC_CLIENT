#ifndef TNIMAGELOADTHREAD_H
#define TNIMAGELOADTHREAD_H

#include <QThread>
#include <QImage>
#include <QString>
#include <QMutex>

class TNImageLoadThread: public QThread
{
    Q_OBJECT

public:
    explicit TNImageLoadThread(const QString &filename, const QSize &targetSize, QObject *parent = Q_NULLPTR);

signals:
    void loadFailed(const QString &filename);
    void loadFinished(const QString &filename, const QImage &bigImage);

protected:
    virtual void run();

private:
    const QString m_fileName;
    const QSize m_targetSize;
    QImage m_targetImage;

    QMutex m_mutex;
};

#endif // TNIMAGELOADTHREAD_H
