#include "MenuAreaBase.h"

MenuAreaBase::MenuAreaBase(int id, const QString &pic_name, int type,QWidget *parent)
: ToolButton(pic_name, type, parent)
	, _ID(id)
{
	
}

MenuAreaBase::~MenuAreaBase()
{

}

int MenuAreaBase::GetID()
{
	return _ID;
}