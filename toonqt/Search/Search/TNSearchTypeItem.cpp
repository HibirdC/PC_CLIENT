#include "TNSearchTypeItem.h"

TNSearchTypeItem::TNSearchTypeItem(const QString &departmentName, int itemCount, TNSearchTreeItemV2 *parent) :
TNSearchTreeItemV2(QList<QVariant>() << departmentName, itemCount, parent)
{

}

TNSearchTypeItem::~TNSearchTypeItem()
{
}

TNSearchTypeItem::SearchTreeItemEnum TNSearchTypeItem::getItemGrade() const
{
	return TNSearchTreeItemV2::Type;
}
