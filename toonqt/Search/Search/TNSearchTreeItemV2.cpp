#include "TNSearchTreeItemV2.h"
#include <QStringList>

TNSearchTreeItemV2::TNSearchTreeItemV2(const QList<QVariant> &data,int itemCount, TNSearchTreeItemV2 *parent) :
_itemData(data), _parentItem(parent), _itemCount(-1)
{
	_itemCount = itemCount;
}

TNSearchTreeItemV2::~TNSearchTreeItemV2()
{
	qDeleteAll(_childItems);
}

TNSearchTreeItemV2::SearchTreeItemEnum TNSearchTreeItemV2::getItemGrade() const
{
	return Invalid;
}
void TNSearchTreeItemV2::appendChild(TNSearchTreeItemV2 *item)
{
	_childItems.append(item);
}
void TNSearchTreeItemV2::removeChild(int row)
{
	_childItems.removeAt(row);
}
void TNSearchTreeItemV2::updateChild(int row, TNSearchTreeItemV2 *item)
{
	_childItems[row] = item;
}
TNSearchTreeItemV2 *TNSearchTreeItemV2::child(int row)
{
	return _childItems.value(row);
}

int TNSearchTreeItemV2::childCount() const
{
	return _childItems.count();
}

int TNSearchTreeItemV2::columnCount() const
{
	return _itemData.count();
}

QVariant TNSearchTreeItemV2::data(int column) const
{
	return _itemData.value(column);
}

TNSearchTreeItemV2 *TNSearchTreeItemV2::parentItem() const
{
	return _parentItem;
}

int TNSearchTreeItemV2::row() const
{
	if (_parentItem)
		return _parentItem->_childItems.indexOf(const_cast<TNSearchTreeItemV2*>(this));

	return 0;
}
