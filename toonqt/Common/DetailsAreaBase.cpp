#include "DetailsAreaBase.h"
#include <QDebug>
DetailsAreaBase::DetailsAreaBase(int id, QWidget *parent)
	: QWidget(parent)
	, _ID(id)
{

}

DetailsAreaBase::~DetailsAreaBase()
{
	qDebug() << "DetailsAreaBase";
}

int DetailsAreaBase::GetID()
{
	return _ID;
}