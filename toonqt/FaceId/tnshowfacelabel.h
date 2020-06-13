#ifndef TNSHOWFACELABEL_H
#define TNSHOWFACELABEL_H
#include <QLabel>


class TNShowFaceLabel : public QLabel
{
    Q_OBJECT
public:
    explicit TNShowFaceLabel(QWidget* parent = 0);
    ~TNShowFaceLabel();
    void showFaceRects(QVector<QRect> faceRects);
    void showImage(const QImage& image);
protected:
    void paintEvent(QPaintEvent *event);
private:
    void drawFaceRects(bool h_mirrored,bool v_mirrored,
                       const QRect& ori_rect,QPainter& painter);
private:
    QVector<QRect> _faceRects;
    QImage 	   _showImage;
};

#endif // TNSHOWFACELABEL_H
