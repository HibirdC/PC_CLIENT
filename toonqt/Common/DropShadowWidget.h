////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	DropShadowWidget.h
//
// summary:	设置阴影边框
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef DROPSHADOWWIDGET_H
#define DROPSHADOWWIDGET_H

#include <QDialog>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <qmath.h>

#include "common_global.h"

class TNResizerDecorator;
class COMMON_EXPORT DropShadowWidget : public QDialog
{
	Q_OBJECT

public:
    explicit DropShadowWidget(QWidget *parent = 0);
	~DropShadowWidget();

public:
    //设置是否可以调整大小
    void setResizable(bool bIsResizable);

    //设置是否可以移动
    void setMoveable(bool bIsMoveable);

protected:
    void init();
protected:
    TNResizerDecorator *m_pResizerDecorator;
};

#endif //DROPSHADOWWIDGET_H