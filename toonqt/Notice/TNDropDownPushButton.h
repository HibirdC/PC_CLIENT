/*******************************************************************
*  Copyright(c) 2000-2018 syswin
*  All rights reserved.
*
*  文件名称: TNDropDownPushButton.h
*  说明:    下拉式按钮，如“截屏按钮“
******************************************************************/
#ifndef TNDROPDOWNPUSHBUTTON_H
#define TNDROPDOWNPUSHBUTTON_H

#include <QPushButton>

class TNDropDownPushButton : public QPushButton
{
    Q_OBJECT

public:
    TNDropDownPushButton(QWidget *parent);
    ~TNDropDownPushButton();
signals:
    void arrowClick();//向下箭头被单击
protected:
    void mousePressEvent(QMouseEvent *e);
private:
     
};

#endif // TNDROPDOWNPUSHBUTTON_H
