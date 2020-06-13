#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include "videowidgetsurface.h"
#include <QWidget>

class VideoWidget : public QWidget
{
    Q_OBJECT

public:
    VideoWidget(QWidget *parent = 0);
    ~VideoWidget();

    QAbstractVideoSurface *videoSurface() const { return surface; }

    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    VideoWidgetSurface *surface;
};

#endif // VIDEOWIDGET_H
