/*******************************************************************
*  Copyright(c) 2000-2018 syswin
*  All rights reserved.
*
*  文件名称: TNArrowDrawTool.h
*  说明:    箭头绘制工具类
******************************************************************/

#ifndef TNARROWDRAWTOOL_H
#define TNARROWDRAWTOOL_H
#include "TNScreenshotEditOptionData.h"
#include <QRegion>
#include <QPainterPath>

class TNArrowDrawTool
{
public:
    TNArrowDrawTool();
    ~TNArrowDrawTool();
    void getArrowPath(LineWidthSize size, QPainterPath &path, QPoint start, QPoint end);
};

//直线参数方程
class TNParametricLine
{
public:
    TNParametricLine(QPoint start, QPoint end);
    TNParametricLine(QPoint start, double angle);
    ~TNParametricLine(){}

    QPoint pointAtLength(double length);
    double lengthFromStart(QPoint point);
    double angle() { return a; }

private:
    //参数方程表达式
    //x = x0 + t*cos(a)
    //y = y0 + t*sin(a)
    double a;
    double x0;
    double y0;
};

#endif // TNARROWDRAWTOOL_H
