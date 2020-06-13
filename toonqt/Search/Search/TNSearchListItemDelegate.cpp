#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDebug>
#include <QPainter>
#include <QTableView>

#include "TNSearchAdapter.h"
#include "TNSearchItemWidget.h"
#include "TNSearchListItemDelegate.h"
#include "TNSearchDataItemWidget.h"
#include "TNSearchTreeItemV2.h"
#include "TNSearchNameItem.h"

TNSearchListItemDelegate::TNSearchListItemDelegate(QAbstractItemView *itemView)
:TNAbstractItemDelegate(itemView), _parentWidget(NULL)
{
}

//QWidget *TNSearchListItemDelegate::createItemWidget(const QModelIndex &index) const
//{
//	TNSearchAdapter *adapter = (TNSearchAdapter*)index.data().toLongLong();
//	if (adapter == NULL)
//		return NULL;
//
//	QString defaultPhoto;
//	TNSearchDataItemWidget *msgListItem = NULL;
//	if (adapter->getType() == TNSearchAdapter::FriendLetter)
//	{
//		bool showAll = adapter->getItemCount() > SEARCH_SHOW_COUNT ? true : false;
//		TNSearchItemWidget *Widget = new TNSearchItemWidget(adapter->getName(), showAll, index);
//		if (showAll)
//		{
//			Widget->setShowButtonName(adapter->getShowButtonName());
//			Widget->setShowButtonStatus(false);
//			connect(Widget, SIGNAL(showButtonClicked(QModelIndex, QString, QString ,bool)), SIGNAL(showButtonClickedIntag(QModelIndex, QString,QString, bool)));
//		}
//		return Widget;
//	}
//	else 
//	{
//		msgListItem = new TNSearchDataItemWidget(index);
//		defaultPhoto = (":/Resources/DefaltAvarta.png");
//		msgListItem->setFeedID(adapter->getDialogID());
//		msgListItem->setFixedSize(LIST_SEARCH_WIDTH, LIST_SEARCH_HEIGHT);
//		msgListItem->setPhoto(adapter->getPhotoResID(), defaultPhoto, adapter->getDialogID().at(0).toLatin1() == 'c' ? Cust_Type::cust_ellipse : Cust_Type::cust_radius,QSize(30,30));
//		msgListItem->setTitle(adapter->getName());
//
//		switch (adapter->getType())
//		{
//		case TNSearchAdapter::FriendItem:
//		case TNSearchAdapter::ColleagueItem:
//			if (adapter->getShowBelongStatus())
//			{
//				msgListItem->setArrowVisible(true);
//				msgListItem->setMyPhotoVisible(true);
//				msgListItem->setMyPhoto(adapter->getBelongPhotoResID(), defaultPhoto, adapter->getBelongFeedId().at(0).toLatin1() == 'c' ? Cust_Type::cust_ellipse : Cust_Type::cust_radius, QSize(30, 30));
//			}
//			break;
//		default:
//			msgListItem->setMyPhotoVisible(false);
//			break;
//		}
//		msgListItem->setSexLabelVisible(false);
//		msgListItem->setAgeLabelVisible(false);
//		msgListItem->setArrowVisible(false);
//
//		connect(msgListItem, SIGNAL(photoClicked(QModelIndex)), SIGNAL(photoButtonClicked(QModelIndex)));
//		emit createWidgetFinished(index, TNSearchAdapter::FriendItem);
//
//		return msgListItem;
//	}
//
//	Q_ASSERT(!"never come to here");
//	return NULL;
//}

//void TNSearchListItemDelegate::setRowHeight(const QModelIndex &index) const
//{
//	TNSearchAdapter *adapter = (TNSearchAdapter*)index.data().toLongLong();
//	if (adapter == NULL)
//		return;
//
//	QTableView *tableView = dynamic_cast<QTableView*>(_itemView);
//	if (tableView == NULL)
//		return;
//
//	if (adapter->getType() == TNSearchAdapter::FriendLetter)
//	{
//		tableView->setRowHeight(index.row(), 24);
//	}
//	else
//	{
//		tableView->setRowHeight(index.row(), LIST_SEARCH_HEIGHT);
//	}
//}
QWidget *TNSearchListItemDelegate::createItemWidget(const QModelIndex &index) const
{
	TNSearchTreeItemV2 *item = static_cast<TNSearchTreeItemV2*>(index.internalPointer());
	if (item == NULL)
		return NULL;

	if (item->getItemGrade() == TNSearchTreeItemV2::Type)
	{
		bool showAll = item->getItemCount() > SEARCH_SHOW_COUNT ? true : false;
		QString data = item->data(0).toString();
		QString name;
		if (data == "AFriend")
		{
			name = tr(QStringLiteral("好友").toUtf8().data());
		}
		else if (data == "BColleague")
		{
			name = tr(QStringLiteral("同事").toUtf8().data());
		}
		else if (data == "CGroup")
		{
			name = tr(QStringLiteral("社区").toUtf8().data());
		}
		else if (data == "DGroupChat")
		{
			name = tr(QStringLiteral("群聊").toUtf8().data());
		}
		TNSearchItemWidget *typeItem = new TNSearchItemWidget(name, showAll, index);
		if (showAll)
		{
			typeItem->setShowButtonName(tr(QStringLiteral("显示全部").toUtf8().data()));
			typeItem->setShowButtonStatus(false);
			connect(typeItem, SIGNAL(showButtonClicked(QModelIndex, QString, QString, bool)), SIGNAL(showButtonClickedIntag(QModelIndex, QString, QString, bool)));
		}
		typeItem->setFixedSize(QSize(LIST_SEARCH_WIDTH, 24));
		connect(typeItem, SIGNAL(expandButtonClicked(QModelIndex, bool)), SIGNAL(itemButtonClicked(QModelIndex, bool)));
		return typeItem;
	}
	if (item->getItemGrade() == TNSearchTreeItemV2::Name)
	{
		TNSearchDataItemWidget *msgListItem = new TNSearchDataItemWidget(index);
		TNSearchNameItem *nameItem = static_cast<TNSearchNameItem*>(item);
		QString defaultPhoto = (":/Resources/DefaltAvarta.png");
		msgListItem->setFeedID(nameItem->getFeedID());
		msgListItem->setFixedSize(LIST_SEARCH_WIDTH, LIST_SEARCH_HEIGHT);
		msgListItem->setPhoto(nameItem->getPhotoResourceID(), defaultPhoto, QSize(30, 30));
		msgListItem->setTitle(nameItem->getTitle());
		msgListItem->setTypeString(nameItem->getTypeString());
		msgListItem->setMyFeedID(nameItem->getBelongFeedId());
		switch (nameItem->getType())
		{
		case TNSearchNameItem::FriendItem:
		case TNSearchNameItem::ColleagueItem:
				if (nameItem->getShowBelongStatus())
				{
					msgListItem->setArrowVisible(true);
					msgListItem->setMyPhotoVisible(true);
					msgListItem->setMyPhoto(nameItem->getBelongPhotoResID(), defaultPhoto, QSize(20, 20));
				}
				break;
				default:
					msgListItem->setMyPhotoVisible(false);
					break;
		}
		msgListItem->setSexLabelVisible(false);
		msgListItem->setAgeLabelVisible(false);
		msgListItem->setArrowVisible(false);
		
		connect(msgListItem, SIGNAL(photoClicked(QModelIndex)), SIGNAL(photoButtonClicked(QModelIndex)));
		emit createWidgetFinished(index, nameItem->getType());

		return msgListItem;
	}
	return NULL;
}
