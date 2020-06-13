#include "ListAreaBase.h"

ListAreaBase::ListAreaBase(int id, QWidget *parent)
	: QWidget(parent)
	, _ID(id)
{

}

ListAreaBase::~ListAreaBase()
{

}

int ListAreaBase::GetID()
{
	return _ID;
}
