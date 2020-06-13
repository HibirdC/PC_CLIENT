#include "TNAbstractItemDelegate.h"
#include <QAbstractItemView>
#include <QTableView>
#include <QPainter>


TNAbstractItemDelegate::TNAbstractItemDelegate(QAbstractItemView *itemView)
{
    _itemView = itemView;
}

void TNAbstractItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                                    const QModelIndex &index) const
{
    Q_UNUSED(painter);
    Q_UNUSED(option);

	if (_itemView->indexWidget(index) == NULL)
	{
		QWidget *itemWidget = createItemWidget(index);
		if (itemWidget != NULL)
		{
			_itemView->setIndexWidget(index, itemWidget);
		}
	}
	else{
		setRowHeight(index);
	}
}

void TNAbstractItemDelegate::setRowHeight(const QModelIndex &index) const
{

}

void TNAbstractItemDelegate::onItemClicked(QModelIndex index)
{
	emit itemClicked(index);
}

void TNAbstractItemDelegate::onItemDoubleClicked(QModelIndex index)
{
	emit itemDoubleClicked(index);
}
