#include "TNUnReadMsgAdapter.h"
#include <QDebug>
#include "TNDataCache.h"

TNUnReadMsgAdapter::TNUnReadMsgAdapter(int type)
{
	_type = type;
	_bNoShowCount = false;
}

TNUnReadMsgAdapter::~TNUnReadMsgAdapter()
{
}
TNUnReadMsgModel::TNUnReadMsgModel(QObject *parent) :
TNListModel(parent)
{
}

void TNUnReadMsgModel::appendData(QList<TNUnReadMsgAdapter *> adapterList)
{
	QList<TNUnReadMsgAdapter *>::iterator it;
	QModelIndex modelIndex;
	int listSize = _listItemData.size();
	beginInsertRows(modelIndex, listSize, listSize + adapterList.size() - 1);
	for (it = adapterList.begin(); it != adapterList.end(); it++)
	{
		if ((*it) != NULL)
			_listItemData.append(*it);
	}
	endInsertRows();
}
void TNUnReadMsgModel::appendData(TNUnReadMsgAdapter *adapter)
{
	if (adapter != NULL)
	{
		QModelIndex modelIndex;
		int listSize = _listItemData.size();
		beginInsertRows(modelIndex, listSize, listSize);
		_listItemData.append(adapter);
		endInsertRows();
	}
}
void TNUnReadMsgModel::updateItemInfo(const QString &feedId, const QString &file,
	const QString &name, int count)
{
}
int TNUnReadMsgModel::removeRowsExceptKeyword(const QString& keyword)
{
	return 0;
}

bool TNUnReadMsgModel::removeRowByDialogId(const QString& dialogId)
{
	if (dialogId.length() == 0)
		return false;

	bool ret = false;
	for (int i = 0; i < _listItemData.size(); i++)
	{
		TNUnReadMsgAdapter *itemData = static_cast<TNUnReadMsgAdapter*>(_listItemData.at(i));
		if (itemData->getFromFeedID() == dialogId)
		{
			beginRemoveRows(QModelIndex(), i, i);

			delete _listItemData.at(i);
			_listItemData.removeAt(i);

			endRemoveRows();

			ret = true;
			break;
		}
	}

	return ret;
}
void TNUnReadMsgModel::removeItem(const QString &feedId, int index)
{
	Q_ASSERT(!feedId.isEmpty());
	QMutexLocker lock(&_mutex);
	beginRemoveRows(QModelIndex(), index, index);
	delete _listItemData.at(index);
	_listItemData.removeAt(index);
	endRemoveRows();
}
void TNUnReadMsgModel::insertItem(TNUnReadMsgAdapter * adapter)
{
	if (adapter == NULL)
	{
		return;
	}
}
void TNUnReadMsgModel::resetModel()
{
	QMutexLocker lock(&_mutex);
	beginResetModel();
	qDeleteAll(_listItemData.begin(), _listItemData.end());
	_listItemData.clear();
	endResetModel();
}
Qt::ItemFlags TNUnReadMsgModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;
	return QAbstractListModel::flags(index);
}