#include "TNCardCaseTreeItem.h"

#include <QStringList>

TNCardCaseTreeItem::TNCardCaseTreeItem(const QList<QVariant> &data, TNCardCaseTreeItem *parent) :
    _itemData(data), _parentItem(parent)
	, _secondNodeStatus(false)
{

}

TNCardCaseTreeItem::~TNCardCaseTreeItem()
{
    qDeleteAll(_childItems);
}

TNCardCaseTreeItem::ColleagueTreeItem TNCardCaseTreeItem::getItemGrade() const
{
    return Invalid;
}

void TNCardCaseTreeItem::appendChild(TNCardCaseTreeItem *item)
{
    _childItems.append(item);
}
void TNCardCaseTreeItem::removeChild(int row)
{
	_childItems.removeAt(row);
}
void TNCardCaseTreeItem::updateChild(int row, TNCardCaseTreeItem *item)
{
	_childItems[row] = item;
}
TNCardCaseTreeItem *TNCardCaseTreeItem::child(int row)
{
    return _childItems.value(row);
}

int TNCardCaseTreeItem::childCount() const
{
    return _childItems.count();
}

int TNCardCaseTreeItem::columnCount() const
{
    return _itemData.count();
}

QVariant TNCardCaseTreeItem::data(int column) const
{
    return _itemData.value(column);
}

TNCardCaseTreeItem *TNCardCaseTreeItem::parentItem() const
{
    return _parentItem;
}

int TNCardCaseTreeItem::row() const
{
    if (_parentItem)
        return _parentItem->_childItems.indexOf(const_cast<TNCardCaseTreeItem*>(this));

    return 0;
}
