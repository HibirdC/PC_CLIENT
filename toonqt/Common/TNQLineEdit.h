#ifndef TNQLINEEDIT_H
#define TNQLINEEDIT_H

#include <QLineEdit>
#include <QInputMethodEvent>

#include "common_global.h"

class COMMON_EXPORT TNQLineEdit : public QLineEdit
{
	Q_OBJECT

public:
	TNQLineEdit(QWidget *parent = 0);
	~TNQLineEdit();
protected:

	virtual void inputMethodEvent(QInputMethodEvent *e);
private:
	
};

#endif // TNQLINEEDIT_H
