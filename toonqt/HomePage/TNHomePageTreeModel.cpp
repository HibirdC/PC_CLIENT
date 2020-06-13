#include "TNHomePageTreeModel.h"

#include <QSize>
#include <QStringList>

TNHomePageTreeModel::TNHomePageTreeModel(TNHomePageTreeItem *rootItem, QObject *parent)
    : QAbstractItemModel(parent), _rootItem(rootItem)
{

}

TNHomePageTreeModel::~TNHomePageTreeModel()
{
    if (_rootItem != nullptr)
    {
        delete _rootItem;
        _rootItem = nullptr;
    }
}

TNHomePageTreeItem *TNHomePageTreeModel::rootItem() const
{
    return _rootItem;
}

int TNHomePageTreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TNHomePageTreeItem*>(parent.internalPointer())->columnCount();
    else
        return _rootItem->columnCount();
}

QVariant TNHomePageTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    TNHomePageTreeItem *item = static_cast<TNHomePageTreeItem*>(index.internalPointer());
    if (role == Qt::DisplayRole)
    {
        return item->data(index.column());
    }
    return QVariant();
}

Qt::ItemFlags TNHomePageTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return QAbstractItemModel::flags(index);
}

QVariant TNHomePageTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return _rootItem->data(section);

    return QVariant();
}

QModelIndex TNHomePageTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TNHomePageTreeItem *parentItem;

    if (!parent.isValid())
        parentItem = _rootItem;
    else
        parentItem = static_cast<TNHomePageTreeItem*>(parent.internalPointer());

    TNHomePageTreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex TNHomePageTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TNHomePageTreeItem *childItem = static_cast<TNHomePageTreeItem*>(index.internalPointer());
    TNHomePageTreeItem *parentItem = childItem->parentItem();

    if (parentItem == _rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int TNHomePageTreeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;

    TNHomePageTreeItem *parentItem;
    if (!parent.isValid())
        parentItem = _rootItem;
    else
        parentItem = static_cast<TNHomePageTreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

void TNHomePageTreeModel::removeItem(const QModelIndex index, int totalItemCount, int type)
{
    if (_rootItem == NULL || !index.isValid())
    {
        return;
    }

    TNHomePageTreeItem * subItem = _rootItem->child(index.row());
    Q_ASSERT(subItem != NULL);
    beginRemoveRows(index,SEARCH_SHOW_COUNT, totalItemCount);
    for (int i = SEARCH_SHOW_COUNT; i < totalItemCount; i++)
    {
        subItem->removeChild(SEARCH_SHOW_COUNT);
    }
    endRemoveRows();
    qInfo() << "[Search][TNSearchListModelV2]removeItem";
}

void TNHomePageTreeModel::insertItem(const QModelIndex index, QList<TNHomePageTreeItem *> itemList, int type)
{
    if (_rootItem == NULL || itemList.size() == 0 || !index.isValid())
    {
        return;
    }

    TNHomePageTreeItem * subItem = _rootItem->child(index.row());
    Q_ASSERT(subItem != NULL);
    beginInsertRows(index, SEARCH_SHOW_COUNT, SEARCH_SHOW_COUNT+itemList.size());
    foreach(TNHomePageTreeItem *temp, itemList)
    {
        subItem->appendChild(temp);
    }
    endInsertRows();
    qInfo() << "[Search][TNSearchListModelV2]insertItem";
}

void TNHomePageTreeModel::resetModel(TNHomePageTreeItem *rootItem)
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

QModelIndex TNHomePageTreeModel::getNextIndex(QModelIndex oldIndex)
{
    QModelIndex index;
    if (oldIndex.isValid())
    {
        index = this->index(oldIndex.row() + 1, 0,_latestSelectedParent);
        TNHomePageTreeItem * typeItem = _rootItem->child(_latestSelectedParent.row());
        Q_ASSERT(typeItem != nullptr);
        if ((oldIndex.row() >= typeItem->childCount()-1) && (_latestSelectedParent.row() < _rootItem->childCount()-1))
        {
            _latestSelectedParent = this->index(_latestSelectedParent.row()+1, 0);
            index = this->index(0, 0, _latestSelectedParent);
        }
    }
    if (!index.isValid())
    {
        _latestSelectedParent = this->index(0, 0);
        index = this->index(0, 0, _latestSelectedParent);
    }
    return index;
}

QModelIndex TNHomePageTreeModel::getPreIndex(QModelIndex oldIndex)
{
    QModelIndex index;
    if (oldIndex.isValid())
    {
        index = this->index(oldIndex.row() - 1, 0, _latestSelectedParent);
        if (oldIndex.row() ==0 && _latestSelectedParent.row() >0)
        {
            _latestSelectedParent = this->index(_latestSelectedParent.row() - 1, 0);
            TNHomePageTreeItem * typeItem = _rootItem->child(_latestSelectedParent.row());
            Q_ASSERT(typeItem != nullptr);
            index = this->index(typeItem->childCount()-1, 0, _latestSelectedParent);
        }
    }
    if (!index.isValid())
    {
        _latestSelectedParent = this->index(0, 0);
        index = this->index(0, 0, _latestSelectedParent);
    }
    return index;
}
