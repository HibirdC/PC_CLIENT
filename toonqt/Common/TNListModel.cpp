#include "TNListModel.h"

TNListModel::TNListModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

TNListModel::~TNListModel()
{
    qDeleteAll(_listItemData);
}

qint32 TNListModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return _listItemData.size();

    return 0;
}

qint32 TNListModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 1;

    return 0;
}

QVariant TNListModel::data(const QModelIndex &index, qint32 role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::TextAlignmentRole)
    {
        return qint32 (Qt::AlignLeft | Qt::AlignVCenter);
    }
    else if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        if (index.row() >= _listItemData.size())
            return QVariant();

        return (qint64)_listItemData.at(index.row());
    }

    return QVariant();
}

QVariant TNListModel::headerData(qint32 section, Qt::Orientation orientation, qint32 role) const
{
    Q_UNUSED(section);
    Q_UNUSED(orientation);
    Q_UNUSED(role);
    return QVariant();
}

Qt::ItemFlags TNListModel::flags(const QModelIndex &index) const
{
    if (index.isValid())
        return Qt::ItemIsEnabled;

//    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
    return QAbstractListModel::flags(index);
}

bool TNListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (parent.isValid())
        return false;

    if (row < 0 || count <= 0 || row + count > _listItemData.size())
        return false;

	QModelIndex modelIndex;
	beginRemoveRows(modelIndex, row, row);
	QList<TNModelItemBaseV2*>::iterator begin = _listItemData.begin() + row;
	QList<TNModelItemBaseV2*>::iterator end = begin + count;
    qDeleteAll(begin, end);
    _listItemData.erase(begin, end);

	endRemoveRows();
    return true;
}

bool TNListModel::insertData(int row, QList<TNModelItemBaseV2*> &listData)
{
    if (row < 0 || row > _listItemData.size())
        return false;

    beginInsertRows(QModelIndex(), row, row + listData.size() - 1);
	for (QList<TNModelItemBaseV2*>::iterator it = listData.begin(); it != listData.end(); it++)
        _listItemData.insert(row, *it);

    endInsertRows();

    return true;
}

bool TNListModel::insertData(int row, TNModelItemBaseV2 *data)
{
    if (row < 0 || row > _listItemData.size())
        return false;

    beginInsertRows(QModelIndex(), row, row);
    _listItemData.insert(row, data);
    endInsertRows();

    return true;
}

void TNListModel::clearData()
{
    if (_listItemData.size() > 0)
    {
        QModelIndex modelIndex;
        beginRemoveRows(modelIndex, 0, _listItemData.size() - 1);
		qDeleteAll(_listItemData.begin(), _listItemData.end());
        _listItemData.clear();
        endRemoveRows();
    }
}
