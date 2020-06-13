#ifndef VIDEOWIDGETSURFACE_H
#define VIDEOWIDGETSURFACE_H

#include <QAbstractVideoSurface>

class VideoWidgetSurface : public QAbstractVideoSurface
{
    Q_OBJECT
public:
    explicit VideoWidgetSurface(QWidget* widget,QObject *parent = nullptr);
    ~VideoWidgetSurface();

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(
            QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const override;

    bool isFormatSupported(const QVideoSurfaceFormat &format) const override;

    bool start(const QVideoSurfaceFormat &format) override;
    void stop() override;

    bool present(const QVideoFrame &frame) override;

    QRect videoRect() const { return _targetRect; }
    void updateVideoRect();

    void paint(QPainter *painter);

private:
    QWidget *_widget;
    QImage::Format _imageFormat;
    QRect _targetRect;
    QSize _imageSize;
    QRect _sourceRect;
    QVideoFrame _currentFrame;
};

#endif // VIDEOWIDGETSURFACE_H
