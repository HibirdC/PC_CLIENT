#ifndef CAMERAFRAMEGRABBER_H
#define CAMERAFRAMEGRABBER_H
#include <QAbstractVideoSurface>
#include <QList>

class CameraFrameGrabber : public QAbstractVideoSurface
{
    Q_OBJECT
public:
    explicit CameraFrameGrabber(QObject *parent = 0);

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const;

    bool present(const QVideoFrame &frame);

    void setNativeResolution(const QSize &resolution);
    bool start(const QVideoSurfaceFormat &format);
    void stop();
signals:
    void frameAvailable(QImage frame);

public slots:

};

#endif // CAMERAFRAMEGRABBER_H
