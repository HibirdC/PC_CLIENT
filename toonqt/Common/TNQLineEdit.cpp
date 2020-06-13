#include "TNQLineEdit.h"

TNQLineEdit::TNQLineEdit(QWidget *parent)
	: QLineEdit(parent)
{

}

TNQLineEdit::~TNQLineEdit()
{

}
void TNQLineEdit::inputMethodEvent(QInputMethodEvent *e)
{
	if (e->commitString().isEmpty() && !e->preeditString().isEmpty())
		return;
	QLineEdit::inputMethodEvent(e);
}