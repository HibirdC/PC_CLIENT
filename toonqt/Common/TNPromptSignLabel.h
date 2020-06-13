#ifndef TNPROMPTSIGNLABEL_H
#define TNPROMPTSIGNLABEL_H

#include <QLabel>
#include "common_global.h"

//! 提示标志label, 用来实现按钮控件右上角显示的红点
class COMMON_EXPORT TNPromptSignLabel : public QLabel
{
public:
    //红点再附着控件上的位置
    enum PosType
    {
        TopLeft,    //左上角
        TopRight,   //右上角
        CenterRight //右侧中间
        //... ...
    };

    //!attchWidget 本label所附着的控件, 
    TNPromptSignLabel(QWidget * attchWidget, TNPromptSignLabel::PosType type);
    virtual ~TNPromptSignLabel();
    void relocate();

protected:
    bool eventFilter(QObject *target, QEvent *event);
private:
    QWidget *_attachWidget;
    PosType _posType;
};

#endif
