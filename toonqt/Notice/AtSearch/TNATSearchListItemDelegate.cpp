#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDebug>
#include <QPainter>
#include <QTableView>

#include "TNATSearchAdapter.h"
#include "TNATSearchListItemDelegate.h"
#include "tnatlistitemwidget.h"

TNATSearchListItemDelegate::TNATSearchListItemDelegate(QAbstractItemView *itemView)
:TNAbstractItemDelegate(itemView), _parentWidget(NULL)
{
}

QWidget *TNATSearchListItemDelegate::createItemWidget(const QModelIndex &index) const
{
	TNATSearchAdapter *adapter = (TNATSearchAdapter*)index.data().toLongLong();
	if (adapter == NULL)
		return NULL;

	QString defaultPhoto;
	TNATListItemWidget *msgListItem = new TNATListItemWidget(index);
	defaultPhoto = (":/Resources/DefaltAvarta.png");

	msgListItem->setDialogID(adapter->getDialogID());
	msgListItem->setMaximumWidth(LIST_AT_WIDTH);
	msgListItem->setMinimumWidth(LIST_AT_WIDTH);
	msgListItem->setMinimumHeight(LIST_AT_HEIGHT);
	msgListItem->setFixedSize(LIST_AT_WIDTH, LIST_AT_HEIGHT);
	msgListItem->setPhoto(adapter->getPhotoResID(), defaultPhoto, adapter->getDialogID().at(0).toLatin1() == 'c' ? Cust_Type::cust_ellipse : Cust_Type::cust_radius);
	msgListItem->setTitle(adapter->getName());

	emit createWidgetFinished(index);

	return msgListItem;
}

void TNATSearchListItemDelegate::setRowHeight(const QModelIndex &index) const
{
	TNATSearchAdapter *adapter = (TNATSearchAdapter*)index.data().toLongLong();
	if (adapter == NULL)
		return;

	QTableView *tableView = dynamic_cast<QTableView*>(_itemView);
	if (tableView == NULL)
		return;
	tableView->setRowHeight(index.row(), LIST_AT_HEIGHT);
}
