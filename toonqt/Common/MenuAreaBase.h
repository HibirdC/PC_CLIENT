#ifndef MENUAREABASE_H
#define MENUAREABASE_H


#include "common_global.h"
#include "ToolButton.h"


class COMMON_EXPORT MenuAreaBase : public ToolButton
{
	Q_OBJECT

public:
	MenuAreaBase(int id, const QString &pic_name, int type,QWidget *parent = 0);
	~MenuAreaBase();

	int GetID();

private:
	int _ID;

};

#endif // MENUAREABASE_H
