/*******************************************************************
*  Copyright(c) 2000-2018 syswin
*  All rights reserved.
*
*  文件名称: TNMagnifierWidget.h
*  说明:    截图用放大镜控件
******************************************************************/
#ifndef TNMAGNIFIERWIDGET_H
#define TNMAGNIFIERWIDGET_H

#include <QWidget>

class QLabel;
class TNMagnifierWidget : public QWidget
{
    Q_OBJECT

public:
    TNMagnifierWidget(QWidget *parent);
    ~TNMagnifierWidget();

    //pixmap要放大的位图， width和height分别为选中区域的宽度和高度
    void updatePixmap(QPixmap pixmap, int width, int height);
    void relocate(QPoint refPoint);

protected:
    virtual bool eventFilter(QObject *watched, QEvent *event);
    virtual void paintEvent(QPaintEvent *event);

private:
    QWidget *m_pPicViewer;
    QLabel *m_pPromptLabel;
    QPixmap m_pixmap;
};

#endif // TNMAGNIFIERWIDGET_H
