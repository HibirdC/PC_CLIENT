#include "TNSearchListModelV2.h"
#include "TNSearchNameItem.h"

#include <QSize>
#include <QStringList>

TNSearchListModelV2::TNSearchListModelV2(TNSearchTreeItemV2 *rootItem, QObject *parent)
	: QAbstractItemModel(parent), _rootItem(rootItem)
	, _SearchListWidgtView(nullptr)
{

}

TNSearchListModelV2::~TNSearchListModelV2()
{
	if (_rootItem != nullptr)
	{
		delete _rootItem;
		_rootItem = nullptr;
	}
}

int TNSearchListModelV2::columnCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return static_cast<TNSearchTreeItemV2*>(parent.internalPointer())->columnCount();
	else
		return _rootItem->columnCount();
}

QVariant TNSearchListModelV2::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	TNSearchTreeItemV2 *item = static_cast<TNSearchTreeItemV2*>(index.internalPointer());
	if (role == Qt::DisplayRole)
	{
		return item->data(index.column());
	}
	return QVariant();
}

Qt::ItemFlags TNSearchListModelV2::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;

	return QAbstractItemModel::flags(index);
}

QVariant TNSearchListModelV2::headerData(int section, Qt::Orientation orientation,
	int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
		return _rootItem->data(section);

	return QVariant();
}

QModelIndex TNSearchListModelV2::index(int row, int column, const QModelIndex &parent)
const
{
	if (!hasIndex(row, column, parent))
		return QModelIndex();

	TNSearchTreeItemV2 *parentItem;

	if (!parent.isValid())
		parentItem = _rootItem;
	else
		parentItem = static_cast<TNSearchTreeItemV2*>(parent.internalPointer());

	TNSearchTreeItemV2 *childItem = parentItem->child(row);
	if (childItem)
		return createIndex(row, column, childItem);
	else
		return QModelIndex();
}

QModelIndex TNSearchListModelV2::parent(const QModelIndex &index) const
{
	if (!index.isValid())
		return QModelIndex();

	TNSearchTreeItemV2 *childItem = static_cast<TNSearchTreeItemV2*>(index.internalPointer());
	TNSearchTreeItemV2 *parentItem = childItem->parentItem();

	if (parentItem == _rootItem)
		return QModelIndex();

	return createIndex(parentItem->row(), 0, parentItem);
}

int TNSearchListModelV2::rowCount(const QModelIndex &parent) const
{
	TNSearchTreeItemV2 *parentItem;
	if (parent.column() > 0)
		return 0;

	if (!parent.isValid())
		parentItem = _rootItem;
	else
		parentItem = static_cast<TNSearchTreeItemV2*>(parent.internalPointer());

	return parentItem->childCount();
}
void TNSearchListModelV2::setSearchListView(TNSearchViewV2 *view)
{
	_SearchListWidgtView = view;
}
void TNSearchListModelV2::updateSearchAvatar(QString feedId, QString file)
{
	QMutexLocker locker(&_mutex);
	qInfo() << "[Search][TNSearchListModelV2]updateSearchAvatar feedId: " << feedId;
	QModelIndex rootIndex = _SearchListWidgtView->rootIndex();
	for (size_t ic = 0; ic < _rootItem->childCount(); ic++)
	{
		TNSearchTreeItemV2 * aTypeItem = _rootItem->child(ic);
		if (aTypeItem != nullptr){
			QModelIndex typeIndex = this->index(ic, 0, rootIndex);
			for (size_t id = 0; id < aTypeItem->childCount(); id++)
			{
				QModelIndex nameIndex = this->index(id, 0, typeIndex);
				TNSearchNameItem *nameItem = static_cast<TNSearchNameItem*>(aTypeItem->child(id));
				if (nameItem != nullptr &&nameItem->getFeedID() == feedId)
				{
					nameItem->setPhotoResourceID(file);
				}
			}
		}
	}
}
void TNSearchListModelV2::removeItem(const QModelIndex index, int totalItemCount, int type)
{
	if (_rootItem == nullptr || !index.isValid())
	{
		return;
	}
	Q_ASSERT(_SearchListWidgtView != nullptr);
	TNSearchTreeItemV2 * subItem = _rootItem->child(index.row());
	Q_ASSERT(subItem != nullptr);
	if (subItem != nullptr){
		beginRemoveRows(index, SEARCH_SHOW_COUNT, totalItemCount);
		for (int i = SEARCH_SHOW_COUNT; i < totalItemCount; i++)
		{
			subItem->removeChild(SEARCH_SHOW_COUNT);
		}
		endRemoveRows();
	}
	qInfo() << "[Search][TNSearchListModelV2]removeItem";
}
void TNSearchListModelV2::insertItem(const QModelIndex index, QList<TNSearchTreeItemV2 *> itemList, int type)
{
	if (_rootItem == nullptr || itemList.size() == 0 || !index.isValid())
	{
		return;
	}
	Q_ASSERT(_SearchListWidgtView != nullptr);
	TNSearchTreeItemV2 * subItem = _rootItem->child(index.row());
	Q_ASSERT(subItem != nullptr);
	if (subItem != nullptr){
		beginInsertRows(index, SEARCH_SHOW_COUNT, SEARCH_SHOW_COUNT + itemList.size());
		foreach(TNSearchTreeItemV2 *temp, itemList)
		{
			subItem->appendChild(temp);
		}
		endInsertRows();
	}
	qInfo() << "[Search][TNSearchListModelV2]insertItem";
}
void TNSearchListModelV2::resetModel(TNSearchTreeItemV2 *rootItem)
{
	beginResetModel();
	if (_rootItem != nullptr)
	{
		delete _rootItem;
		_rootItem = nullptr;
	}
	_rootItem = rootItem;
	endResetModel();
}
QModelIndex TNSearchListModelV2::getNextIndex(QModelIndex oldIndex)
{
	QModelIndex index;
	if (oldIndex.isValid())
	{
		index = this->index(oldIndex.row() + 1, 0,_latestSelectedParent);
		TNSearchTreeItemV2 * typeItem = _rootItem->child(_latestSelectedParent.row());
		Q_ASSERT(typeItem!= nullptr);
		if (typeItem != nullptr){
			if (oldIndex.row() >= typeItem->childCount() - 1 &&
				_latestSelectedParent.row() < _rootItem->childCount() - 1)
			{
				_latestSelectedParent = this->index(_latestSelectedParent.row() + 1, 0);
				index = this->index(0, 0, _latestSelectedParent);
			}
		}
	}
	if (!index.isValid())
	{
		_latestSelectedParent = this->index(0, 0);
		index = this->index(0, 0, _latestSelectedParent);
	}
	return index;
}
QModelIndex TNSearchListModelV2::getPreIndex(QModelIndex oldIndex)
{
	QModelIndex index;
	if (oldIndex.isValid())
	{
		index = this->index(oldIndex.row() - 1, 0, _latestSelectedParent);
		if (oldIndex.row() ==0 &&
			_latestSelectedParent.row() >0)
		{
			_latestSelectedParent = this->index(_latestSelectedParent.row() - 1, 0);
			TNSearchTreeItemV2 * typeItem = _rootItem->child(_latestSelectedParent.row());
			Q_ASSERT(typeItem != nullptr);
			if (typeItem != nullptr){
				index = this->index(typeItem->childCount() - 1, 0, _latestSelectedParent);
			}
		}
	}
	if (!index.isValid())
	{
		_latestSelectedParent = this->index(0, 0);
		index = this->index(0, 0, _latestSelectedParent);
	}
	return index;
}
