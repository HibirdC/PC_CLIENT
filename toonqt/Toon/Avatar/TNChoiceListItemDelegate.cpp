#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDebug>
#include <QPainter>
#include <QTableView>

#include "TNAvatarChoiceAdapter.h"
#include "TNChoiceListItemDelegate.h"
#include "TNAvatarChoiceItem.h"

TNAvatarChoiceListItemDelegate::TNAvatarChoiceListItemDelegate(QAbstractItemView *itemView)
:TNAbstractItemDelegate(itemView), _parentWidget(NULL)
{
}

QWidget *TNAvatarChoiceListItemDelegate::createItemWidget(const QModelIndex &index) const
{
	TNAvatarChoiceAdapter *adapter = (TNAvatarChoiceAdapter*)index.data().toLongLong();
	if (adapter == NULL)
		return NULL;

	QString defaultPhoto;
	TNAvatarChoiceItem *msgListItem = new TNAvatarChoiceItem(index);
	defaultPhoto = (":/Resources/DefaltAvarta.png");

	msgListItem->setDialogID(adapter->getDialogID());
	msgListItem->setMinimumSize(QSize(LIST_AVATARCHOICE_WIDTH, LIST_AVATARCHOICE_HEIGHT));
	msgListItem->setMaximumSize(QSize(LIST_AVATARCHOICE_WIDTH, LIST_AVATARCHOICE_HEIGHT));
	msgListItem->setPhoto(adapter->getPhotoResID(), defaultPhoto, adapter->getDialogID().at(0).toLatin1() == 'c' ? Cust_Type::cust_ellipse : Cust_Type::cust_radius);
	msgListItem->setTitle(adapter->getName());
	msgListItem->setCurrentStatus(adapter->getIsCurrentCard());
	msgListItem->setCurrentUnRead(adapter->GetUnreadCount()> 0? true:false);

	connect(msgListItem, SIGNAL(photoClicked(QModelIndex)), SIGNAL(photoButtonClicked(QModelIndex)));
	emit createWidgetFinished(index);

	return msgListItem;
}

void TNAvatarChoiceListItemDelegate::setRowHeight(const QModelIndex &index) const
{
	TNAvatarChoiceAdapter *adapter = (TNAvatarChoiceAdapter*)index.data().toLongLong();
	if (adapter == NULL)
		return;

	QTableView *tableView = dynamic_cast<QTableView*>(_itemView);
	if (tableView == NULL)
		return;
	tableView->setRowHeight(index.row(), LIST_AVATARCHOICE_HEIGHT);
}
