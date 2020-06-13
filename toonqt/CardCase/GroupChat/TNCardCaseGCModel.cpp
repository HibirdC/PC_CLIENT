#include "TNCardCaseGCModel.h"

#include <QSize>
#include <QStringList>
#include "GroupChat/TNGroupChatItem.h"

TNCardCaseGCModel::TNCardCaseGCModel(TNCardCaseTreeItem *rootItem, QObject *parent)
: QAbstractItemModel(parent), _rootItem(rootItem), _GroupChatListWidgtView(nullptr)
{

}

TNCardCaseGCModel::~TNCardCaseGCModel()
{
	delete _rootItem;
}

int TNCardCaseGCModel::columnCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return static_cast<TNCardCaseTreeItem*>(parent.internalPointer())->columnCount();
	else
		return _rootItem->columnCount();
}

QVariant TNCardCaseGCModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	TNCardCaseTreeItem *item = static_cast<TNCardCaseTreeItem*>(index.internalPointer());
	if (role == Qt::DisplayRole)
	{
		return item->data(index.column());
	}
	return QVariant();
}

Qt::ItemFlags TNCardCaseGCModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;

	return QAbstractItemModel::flags(index);
}

QVariant TNCardCaseGCModel::headerData(int section, Qt::Orientation orientation,
	int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
		return _rootItem->data(section);

	return QVariant();
}

QModelIndex TNCardCaseGCModel::index(int row, int column, const QModelIndex &parent)
const
{
	if (!hasIndex(row, column, parent))
		return QModelIndex();

	TNCardCaseTreeItem *parentItem;

	if (!parent.isValid())
		parentItem = _rootItem;
	else
		parentItem = static_cast<TNCardCaseTreeItem*>(parent.internalPointer());

	TNCardCaseTreeItem *childItem = parentItem->child(row);
	if (childItem)
		return createIndex(row, column, childItem);
	else
		return QModelIndex();
}

QModelIndex TNCardCaseGCModel::parent(const QModelIndex &index) const
{
	if (!index.isValid())
		return QModelIndex();

	TNCardCaseTreeItem *childItem = static_cast<TNCardCaseTreeItem*>(index.internalPointer());
	TNCardCaseTreeItem *parentItem = childItem->parentItem();

	if (parentItem == _rootItem)
		return QModelIndex();

	return createIndex(parentItem->row(), 0, parentItem);
}

int TNCardCaseGCModel::rowCount(const QModelIndex &parent) const
{
	TNCardCaseTreeItem *parentItem;
	if (parent.column() > 0)
		return 0;

	if (!parent.isValid())
		parentItem = _rootItem;
	else
		parentItem = static_cast<TNCardCaseTreeItem*>(parent.internalPointer());

	return parentItem->childCount();
}
void TNCardCaseGCModel::RemoveItem(QString feedId, int type)
{
	QMutexLocker locker(&_mutex);
	if (_rootItem == NULL || _rootItem->childCount() < 2)
	{
		return;
	}
	QModelIndex rootIndex = _GroupChatListWidgtView->rootIndex();
	for (size_t ic = 0; ic < _rootItem->childCount(); ic++)
	{
		TNCardCaseTreeItem * aGroupChatNameItem = _rootItem->child(ic);
		Q_ASSERT(aGroupChatNameItem != NULL);
		QModelIndex groupChatIndex = this->index(ic, 0, rootIndex);
		for (size_t id = 0; id < aGroupChatNameItem->childCount(); id++)
		{
			TNCardCaseTreeItem * aStaffItem = aGroupChatNameItem->child(id);
			Q_ASSERT(aStaffItem != NULL);
			if (aStaffItem->childCount() == 0)
			{
				TNGroupChatItem *groupChatItem = static_cast<TNGroupChatItem*>(aStaffItem);
				if (groupChatItem->getDialogID() == feedId)
				{
					beginRemoveRows(groupChatIndex, id, id);
					aGroupChatNameItem->removeChild(id);
					endRemoveRows();
					break;
				}
			}
		}
	}
}
void TNCardCaseGCModel::InsertItem(bool isCreate, TNCardCaseTreeItem * item, int type)
{
	QMutexLocker locker(&_mutex);
	if (_rootItem == NULL || _rootItem->childCount() < 2)
	{
		return;
	}
	int subParent = isCreate ? 0 : 1;
	Q_ASSERT(_GroupChatListWidgtView != NULL);
	QModelIndex groupChatIndex = this->index(subParent, 0, _GroupChatListWidgtView->rootIndex());
	TNCardCaseTreeItem * asubItem = _rootItem->child(subParent);
	Q_ASSERT(asubItem != NULL);
	beginInsertRows(groupChatIndex, asubItem->childCount(), asubItem->childCount());
	asubItem->appendChild(item);
	endInsertRows();
	//if (isCreate)
	//{
	//	QModelIndex joinChatIndex = this->index(subParent + 1, 0, _GroupChatListWidgtView->rootIndex());
	//	beginInsertRows(_GroupChatListWidgtView->rootIndex(), 1, 1);
	//	endInsertRows();
	//}
}
void TNCardCaseGCModel::setItemStatus(const QModelIndex & index, bool status)
{
	TNCardCaseTreeItem *item = static_cast<TNCardCaseTreeItem*>(index.internalPointer());
	if (item != nullptr &&item->getItemGrade() == TNCardCaseTreeItem::Expand)
		item->setStatus(status);
}
void TNCardCaseGCModel::SetGroupChatListView(TNGCTreeView *view)
{
	if (view != nullptr)
		_GroupChatListWidgtView = view;
}
QModelIndex TNCardCaseGCModel::setGroupChatSearchSelected(QString groupId)
{
	QModelIndex rootIndex = _GroupChatListWidgtView->rootIndex();
	for (size_t ic = 0; ic < _rootItem->childCount(); ic++)
	{
		TNCardCaseTreeItem * aGroupChatNameItem = _rootItem->child(ic);
		QModelIndex groupChatIndex = this->index(ic, 0, rootIndex);
		for (size_t id = 0; id < aGroupChatNameItem->childCount(); id++)
		{
			QModelIndex memberIndex = this->index(id, 0, groupChatIndex);
			TNCardCaseTreeItem * aGroupChatItem = aGroupChatNameItem->child(id);
			if (aGroupChatItem->childCount() == 0)
			{
				TNGroupChatItem *staffItem = static_cast<TNGroupChatItem*>(aGroupChatItem);
				if (staffItem->getDialogID() == groupId)
				{
					return memberIndex;
				}
			}
		}
	}
	return QModelIndex();
}
void TNCardCaseGCModel::SetSecondNodeStatus(QModelIndex &index, bool status, NodeType type)
{
	if (index.column() > 0 || !index.isValid())
		return;

	TNCardCaseTreeItem * item = _rootItem->child(index.row());
	if (item != nullptr)
		item->setStatus(status);
}
TNCardCaseTreeItem *  TNCardCaseGCModel::GetSubItemParent(bool isCreate)
{
	if (_rootItem == NULL || _rootItem->childCount() < 2)
	{
		return NULL;
	}
	return isCreate ? _rootItem->child(0) : _rootItem->child(1);
}
QModelIndex TNCardCaseGCModel::UpdateItem(QString feedId, bool isCreate, TNCardCaseTreeItem * item, int type)
{
	QMutexLocker locker(&_mutex);
	QModelIndex Index;
	if (_rootItem == NULL || _rootItem->childCount() < 2)
	{
		return Index;
	}
	Q_ASSERT(_GroupChatListWidgtView != NULL);
	int subParent = isCreate ? 0 : 1;
	QModelIndex rootIndex = _GroupChatListWidgtView->rootIndex();
	TNCardCaseTreeItem * aGroupChatNameItem = _rootItem->child(subParent);
	Q_ASSERT(aGroupChatNameItem != NULL);
	QModelIndex groupChatIndex = this->index(subParent, 0, rootIndex);
	for (size_t id = 0; id < aGroupChatNameItem->childCount(); id++)
	{
		QModelIndex memberIndex = this->index(id, 0, groupChatIndex);
		TNCardCaseTreeItem * aGroupChatItem = aGroupChatNameItem->child(id);
		Q_ASSERT(aGroupChatItem != NULL);
		if (aGroupChatItem->childCount() == 0)
		{
			TNGroupChatItem *gcitem = static_cast<TNGroupChatItem*>(aGroupChatItem);
			if (gcitem->getDialogID() == feedId)
			{
				Index = memberIndex;
				TNGroupChatItem *newItem = static_cast<TNGroupChatItem*>(item);
				if (item != nullptr)
				{
					qInfo() << "[CardCase][TNCardCaseGCModel]UpdateItem update group info, title: " << newItem->getTitle();
					gcitem->setTitle(QList<QVariant>() << newItem->getTitle());
					gcitem->setMemberNumber(newItem->getMemberNumber());
					emit dataChanged(memberIndex, memberIndex);
				}
				break;
			}
		}
	}
	return Index;
}
QModelIndex TNCardCaseGCModel::UpdateItem(st_GroupInfoPtr group)
{
	QMutexLocker locker(&_mutex);
	QModelIndex Index;
	if (_rootItem == NULL || _rootItem->childCount() < 2)
	{
		return Index;
	}
	Q_ASSERT(_GroupChatListWidgtView != NULL);
	QModelIndex rootIndex = _GroupChatListWidgtView->rootIndex();
	for (int i = 0; i < _rootItem->childCount(); i++)
	{
		TNCardCaseTreeItem * aGroupChatNameItem = _rootItem->child(i);
		Q_ASSERT(aGroupChatNameItem != NULL);
		QModelIndex groupChatIndex = this->index(i, 0, rootIndex);
		for (size_t id = 0; id < aGroupChatNameItem->childCount(); id++)
		{
			QModelIndex memberIndex = this->index(id, 0, groupChatIndex);
			TNCardCaseTreeItem * aGroupChatItem = aGroupChatNameItem->child(id);
			Q_ASSERT(aGroupChatItem != NULL);
			if (aGroupChatItem->childCount() == 0)
			{
				TNGroupChatItem *gcitem = static_cast<TNGroupChatItem*>(aGroupChatItem);
				if (gcitem->getDialogID() == group->GetGroupId())
				{
					Index = memberIndex;
					gcitem->setTitle(QList<QVariant>() << group->GetName());
					gcitem->setMemberNumber(group->GetCurrNum());
					emit dataChanged(memberIndex, memberIndex);
					break;
				}
			}
		}
	}
	return Index;
}
void TNCardCaseGCModel::refreshItem(const QString &feedId)
{
	QMutexLocker locker(&_mutex);
	if (_rootItem == NULL || _rootItem->childCount() < 2)
	{
		return ;
	}
	Q_ASSERT(_GroupChatListWidgtView != NULL);
	QModelIndex rootIndex = _GroupChatListWidgtView->rootIndex();
	for (int i = 0; i < _rootItem->childCount(); i++)
	{
		TNCardCaseTreeItem * aGroupChatNameItem = _rootItem->child(i);
		Q_ASSERT(aGroupChatNameItem != NULL);
		QModelIndex groupChatIndex = this->index(i, 0, rootIndex);
		for (size_t id = 0; id < aGroupChatNameItem->childCount(); id++)
		{
			QModelIndex memberIndex = this->index(id, 0, groupChatIndex);
			TNCardCaseTreeItem * aGroupChatItem = aGroupChatNameItem->child(id);
			Q_ASSERT(aGroupChatItem != NULL);
			if (aGroupChatItem->childCount() == 0)
			{
				TNGroupChatItem *gcitem = static_cast<TNGroupChatItem*>(aGroupChatItem);
				if (gcitem->getDialogID() == feedId)
				{
					emit dataChanged(memberIndex, memberIndex);
					break;
				}
			}
		}
	}
}