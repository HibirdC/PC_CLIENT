#include <QMouseEvent>
#include "TNDropDownPushButton.h"

TNDropDownPushButton::TNDropDownPushButton(QWidget *parent)
    : QPushButton(parent)
{

}

TNDropDownPushButton::~TNDropDownPushButton()
{

}

void TNDropDownPushButton::mousePressEvent(QMouseEvent *e)
{
    if (e->pos().x() > 25)
    {
        emit arrowClick();
    }
    else
    {
        QPushButton::mousePressEvent(e);
    }
}

