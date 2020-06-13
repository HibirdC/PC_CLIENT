#include <QPaintEvent>
#include <QPainter>
#include <QtMath>
#include "image_progress_bar.h"

image_progress_bar::image_progress_bar(QWidget* parent) : QProgressBar(parent)
{
}

image_progress_bar::~image_progress_bar()
{
}

void image_progress_bar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPainterPath path;
    int progress = value();
    QPolygonF poly = getPolygonByProgress(progress);
    if(!poly.isEmpty()){
        path.addPolygon(poly);
        painter.fillPath(path, QBrush(QColor(0, 0, 0, 255 * 0.3)));
    }
}

QPolygonF image_progress_bar::getPolygonByProgress(int progress)
{
    QPolygonF polygon;
    int angle = progress * 360 / 100;
    QRect rect = this->rect();
    QPointF center_point = QPoint(rect.left() + rect.width() / 2,rect.top() + rect.height() / 2);
    //四个角的点
    QPointF top_left = rect.topLeft();
    QPointF top_right = rect.topRight();
    QPointF bottom_left = rect.bottomLeft();
    QPointF bottom_right = rect.bottomRight();
    QPointF org_point = QPoint(center_point.x(),center_point.y() - rect.height() / 2);
    if(angle > 0 && angle <= 45){
        float redians = qDegreesToRadians((float)angle);
        float x = center_point.x() + rect.height() * qTan(redians) / 2;
        QPointF start_point(x, 0);
        polygon << center_point << start_point << top_right
                << bottom_right << bottom_left << top_left
                << org_point << center_point;
    }else if(angle > 45 && angle <= 90){
        float redians = qDegreesToRadians((float)90 - angle);
        float y = center_point.y() - rect.width() * qTan(redians) / 2;
        QPointF start_point(rect.right(),y);
        polygon << center_point << start_point << bottom_right
                << bottom_left << top_left << org_point
                << center_point;
    }else if(angle > 90 && angle <= 135){
        float redians = qDegreesToRadians((float)angle - 90);
        float y = center_point.y() + rect.width() * qTan(redians) / 2;
        QPointF start_point(rect.right(),y);
        polygon << center_point << start_point << bottom_right
                << bottom_left << top_left << org_point
                << center_point;
    }else if(angle > 135 && angle <= 180){
        float redians = qDegreesToRadians((float)180 - angle);
        float x = center_point.x() + rect.height() * qTan(redians) / 2;
        QPointF start_point(x,rect.bottom());
        polygon << center_point << start_point << bottom_left
                << top_left << org_point << center_point;
    }else if(angle > 180 && angle <= 225){
        float redians = qDegreesToRadians((float)angle - 180);
        float x = center_point.x() - rect.height() * qTan(redians) / 2;
        QPointF start_point(x,rect.bottom());
        polygon << center_point << start_point << bottom_left
                << top_left << org_point << center_point;
    }else if(angle > 225 && angle <= 270){
        float redians = qDegreesToRadians((float)(270 - angle));
        float y = center_point.y() + rect.width() * qTan(redians) / 2;
        QPointF start_point(rect.left(),y);
        polygon << center_point << start_point << top_left
                << org_point << center_point;
    }else if(angle > 270 && angle <= 315){
        float redians = qDegreesToRadians((float)angle - 270);
        float y = center_point.y() - rect.width() * qTan(redians) / 2;
        QPointF start_point(rect.left(),y);
        polygon << center_point << start_point << top_left
                << org_point << center_point;
    }else if(angle > 315 && angle < 360){
        float redians = qDegreesToRadians((float)360 - angle);
        float x = center_point.x() - rect.height() * qTan(redians) / 2;
        QPointF start_point(x,rect.top());
        polygon << center_point << start_point << org_point
                << center_point;
    }
    return polygon;
}
