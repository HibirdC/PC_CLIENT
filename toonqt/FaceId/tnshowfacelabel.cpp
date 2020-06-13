#include "tnshowfacelabel.h"
#include <QPainter>
#include <QDebug>

TNShowFaceLabel::TNShowFaceLabel(QWidget* parent) : QLabel(parent)
{

}

TNShowFaceLabel::~TNShowFaceLabel()
{

}

void TNShowFaceLabel::showFaceRects(QVector<QRect> faceRects)
{
    _faceRects = faceRects;
    update();
}

void TNShowFaceLabel::showImage(const QImage &image)
{
    _showImage = image;
    update();
}

void TNShowFaceLabel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    bool h_mirrored = false;
    bool v_mirrored = false;
    if(!_showImage.isNull()){
        QRect original_rect = _showImage.rect();
        QImage image = _showImage;
#ifdef Q_OS_WIN
        h_mirrored = true;
        v_mirrored = true;
        image = image.mirrored(h_mirrored,v_mirrored);
#else
        h_mirrored = true;
        v_mirrored = false;
        image = image.mirrored(h_mirrored,v_mirrored);
#endif

        image = image.scaled(this->size(),Qt::KeepAspectRatio);
        painter.drawImage(QPoint(0,0),image);
        if(!_faceRects.empty()){
            drawFaceRects(h_mirrored,v_mirrored,original_rect,painter);
        }
    }
    return QLabel::paintEvent(event);
}

void TNShowFaceLabel::drawFaceRects(bool h_mirrored,bool v_mirrored,
                                    const QRect& ori_rect,QPainter& painter)
{
    QPoint center(ori_rect.width() / 2, ori_rect.height() / 2);
    for(QVector<QRect>::const_iterator itera = _faceRects.begin();
        itera != _faceRects.end();++itera){
        QRect rect = *itera;
        //镜像计算
        if(h_mirrored){
            int left = center.x() + (center.x() - rect.right());
            int top = rect.top();
            int width = rect.width();
            int height = rect.height();
            QRect new_rect(left,top,width,height);
            rect = new_rect;
        }
        if(v_mirrored){
            int left = rect.left();
            int top = center.y() + (center.y() - rect.bottom());
            int width = rect.width();
            int height = rect.height();
            QRect new_rect(left,top,width,height);
            rect = new_rect;
        }
        //比例缩放计算
        float rate = ori_rect.width() * 1.0 / this->rect().width();
        int new_width = rect.width() * 1.0 / rate;
        int new_height = rect.height() * 1.0 / rate;
        int new_left = rect.left() * 1.0 / rate;
        int new_top = rect.top() *  1.0 / rate;
        rect = QRect(new_left,new_top,new_width,new_height);
        QPen pen;
        pen.setColor(QColor(0,255,255));
        pen.setWidthF(2.0f);
        painter.setPen(pen);
        QPoint top_left(rect.left(),rect.top());
        int angle = rect.width() / 5;
        painter.drawLine(top_left,QPoint(top_left.x() + angle,top_left.y()));
        painter.drawLine(top_left,QPoint(top_left.x(),top_left.y() + angle));

        QPoint top_right(rect.right(),rect.top());
        painter.drawLine(top_right,QPoint(top_right.x() - angle,top_right.y()));
        painter.drawLine(top_right,QPoint(top_right.x(),top_right.y() + angle));

        QPoint bottom_left(rect.left(),rect.bottom());
        painter.drawLine(bottom_left,QPoint(bottom_left.x() + angle,bottom_left.y()));
        painter.drawLine(bottom_left,QPoint(bottom_left.x(),bottom_left.y() - angle));

        QPoint bottom_right(rect.right(),rect.bottom());
        painter.drawLine(bottom_right,QPoint(bottom_right.x() - angle,bottom_left.y()));
        painter.drawLine(bottom_right,QPoint(bottom_right.x(),bottom_left.y() - angle));
    }
}
