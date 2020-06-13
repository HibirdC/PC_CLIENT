#include <qmath.h>
#include "TNArrowDrawTool.h"

TNArrowDrawTool::TNArrowDrawTool()
{

}

TNArrowDrawTool::~TNArrowDrawTool()
{

}

void TNArrowDrawTool::getArrowPath(LineWidthSize size, QPainterPath &path, QPoint start, QPoint end)
{
    TNParametricLine line(start, end);
    double dArrowWidth = 8;
    switch (size)
    {
    case lwsLarge:
        if (abs(end.x() - start.x()) > 22 || abs(end.y() - start.y()) > 22)
        {
            dArrowWidth = 22;
        }
        else if (abs(end.x() - start.x()) > 16 || abs(end.y() - start.y()) > 16)
        {
            dArrowWidth = 16;
        }
        break;
    case lwsMiddle:
        if (abs(end.x() - start.x()) > 16 || abs(end.y() - start.y()) > 16)
        {
            dArrowWidth = 16;
        }
        break;
    default:
        break;
    }
    //箭头头部三角形底边上的中点
    QPoint ptMiddle = line.pointAtLength(line.lengthFromStart(end) - dArrowWidth);
    TNParametricLine vertical(ptMiddle, line.angle() + M_PI * 0.5);

    //箭头头部三角形底边上的四个点
    QPoint pt1 = vertical.pointAtLength(dArrowWidth / 2); 
    QPoint pt2 = vertical.pointAtLength(dArrowWidth / 4);
    QPoint pt3 = vertical.pointAtLength(-dArrowWidth / 4 + 1);
    QPoint pt4 = vertical.pointAtLength(-dArrowWidth / 2 + 1);
    path.moveTo(start);
    path.lineTo(pt2);
    path.lineTo(pt1);
    path.lineTo(end);
    path.lineTo(pt4);
    path.lineTo(pt3);
    path.lineTo(start);
}

TNParametricLine::TNParametricLine(QPoint start, QPoint end)
: a(0)
{
    double dx = end.x() - start.x();
    double dy = end.y() - start.y();
    if (dx == 0)
    {
        a = M_PI * 0.5;
    }
    else
    {
        if (dx > 0)
        {
            a = qAtan(dy / dx);
        }
        else
        {
            a = M_PI + qAtan(dy / dx);
        }
    }
    x0 = start.x();
    y0 = start.y();
}

TNParametricLine::TNParametricLine(QPoint start, double angle)
{
    x0 = start.x();
    y0 = start.y();
    a = angle;
}

QPoint TNParametricLine::pointAtLength(double length)
{
    double x = x0 + length * qCos(a);
    double y = y0 + length * qSin(a);
    return QPoint((int)x, (int)y);
}

double TNParametricLine::lengthFromStart(QPoint point)
{
    return (point.x() - x0) / qCos(a);
}