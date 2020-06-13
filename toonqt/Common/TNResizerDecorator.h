/*******************************************************************
*  Copyright(c) 2000-2018 syswin
*  All rights reserved.
*
*  文件名称: TNResizerDecorator.h
*  说明:    用来实现鼠标拉伸、移动功能的装饰类
******************************************************************/
#ifndef TNRESIZERDECORATOR_H
#define TNRESIZERDECORATOR_H

#include <QObject>
#include <QPoint>
#include <QRect>
#include "common_global.h"

class QWidget;
class QMouseEvent;
class COMMON_EXPORT TNResizerDecorator : public QObject
{
    Q_OBJECT

public:
    TNResizerDecorator(QWidget *parent);
    ~TNResizerDecorator();
    enum ResizeRegion
    {
        Default,
        North,
        NorthEast,
        East,
        SouthEast,
        South,
        SouthWest,
        West,
        NorthWest
    };
    ResizeRegion getCurrentResizeRegion()
    {
        return m_CurrentResizeRegion;
    }
    bool isMousePress() { return m_bIsMousePress; }
    QPoint posAtPressMouse() { return m_curPosAtPressMouse; }

    void init();
    //设置默认光标样式
    void setDefaultCursor(Qt::CursorShape shape);
    //设置外边界
    void setOuterBoundary(const QRect &rect);
    //设置内边界
    void setInnerBoundary(const QRect &rect);
    //设置是否可移动
    void setMovable(bool bIsMoveable);
    //设置是否可拉伸
    void setResizable(bool bIsResizable);

protected:
    virtual bool eventFilter(QObject *watched, QEvent *event);

private:
    void handleResize(QPoint globalPos);
    ResizeRegion getResizeRegion(QPoint clientPos);
    void setResizeCursor(ResizeRegion region);
private:
    void onMouseButtonPress(QMouseEvent *);
    void onMouseButtonRelease(QMouseEvent *);
    void onMouseMove(QMouseEvent *);
    void onMouseDrag(QMouseEvent *);
private:
    QWidget *m_pParentWidget;
    Qt::CursorShape m_defaultShape;
    ResizeRegion m_CurrentResizeRegion;         //当前光标所在区域
    QPoint m_curPosAtPressMouse;                //鼠标按下时，光标所在位置
	QPoint m_TopLeftAtPress;                    //左上角在按下时的位置

    QRect m_rectAtPressMouse;                   //鼠标按下时，窗体大小
    QRect m_rectOuterBoundary;                  //控件可移动和可缩放的最大尺寸范围
    QRect m_rectInnerBoundary;                  //控件可移动和可缩放的最小尺寸范围

    bool m_isMoveable;                          //是否可移动
    bool m_isResizalbe;                         //是否可拉伸
	bool m_bIsMousePress;                       //鼠标左键是否按下
};

#endif // TNRESIZERDECORATOR_H
