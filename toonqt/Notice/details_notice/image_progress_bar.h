#ifndef IMAGE_PROGRESS_BAR_H
#define IMAGE_PROGRESS_BAR_H

#include <QObject>
#include <QProgressBar>
#include <QTimer>

class image_progress_bar : public QProgressBar
{
    Q_OBJECT
public:
    image_progress_bar(QWidget* parent=NULL);
    ~image_progress_bar();
protected:
    void paintEvent(QPaintEvent *);
private:
    QPolygonF getPolygonByProgress(int progress);
};

#endif // IMAGE_PROGRESS_BAR_H
