#ifndef TNEMOTIONLINEEDIT_H
#define TNEMOTIONLINEEDIT_H

#include <QLineEdit>
#include <QFocusEvent>

#include "TNMVD_global.h"

class TNMVD_EXPORT TNEmotionLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    TNEmotionLineEdit(QWidget *parent = 0);
    ~TNEmotionLineEdit();

protected:
    virtual void focusInEvent(QFocusEvent *e);
};

#endif // TNEMOTIONLINEEDIT_H
