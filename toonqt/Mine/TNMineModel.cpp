#include "TNMineModel.h"
#include "TNPathUtil.h"

TNMineModel::TNMineModel(QObject *parent)
	: TNListModel(parent)
{

}

TNMineModel::~TNMineModel()
{

}
void TNMineModel::appendData(QList<TNMineAdapter *> adapterList)
{
	QList<TNMineAdapter *>::iterator it;
	QModelIndex modelIndex;
	int listSize = _listItemData.size();
	beginInsertRows(modelIndex, listSize, listSize + adapterList.size());
	for (it = adapterList.begin(); it != adapterList.end(); it++)
	{
		if ((*it) != NULL)
			_listItemData.append((*it));
	}
	endInsertRows();
}
void TNMineModel::appendData(TNMineAdapter * adapter)
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
void TNMineModel::refreshItem(const QString &feedId)
{
	QMutexLocker lock(&_mutex);
	for (int i = 0; i < _listItemData.size(); i++)
	{
		TNMineAdapter *itemData = static_cast<TNMineAdapter*>(_listItemData[i]);//[]返回的是引用
		if (itemData->getFeedId() == feedId)
		{
			itemData->setAvatarURL(itemData->getLatestAvatarURL());
			QModelIndex q_index = this->index(i, 0);
			emit dataChanged(q_index, q_index);
		}
	}
}
void TNMineModel::removeItem(const QString &feedId)
{
	QMutexLocker lock(&_mutex);
	int index = -1;
	for (int i = 0; i < _listItemData.size(); i++)
	{
		TNMineAdapter *itemData = static_cast<TNMineAdapter*>(_listItemData.at(i));
		Q_ASSERT(itemData != NULL);
		if (itemData->getFeedId() == feedId)
		{
			index = i;
			break;
		}
	}
	if (index != -1)
	{
		QModelIndex q_index;
		beginRemoveRows(q_index, index, index);
		delete _listItemData.at(index);
		_listItemData.removeAt(index);
		endRemoveRows();
	}
}
/*
新插入的社区插在类型队列头部
*/
void TNMineModel::insertItem(TNMineAdapter * adapter)
{
	if (adapter == NULL)
	{
		return;
	}
	int index = getValidPosition(adapter);
	if (index >= 0)
	{
		QModelIndex q_index;
		beginInsertRows(q_index, index, index);
		_listItemData.insert(index, adapter);
		endInsertRows();
	}
}
void TNMineModel::resetModel()
{
	QMutexLocker lock(&_mutex);
	beginResetModel();
	qDeleteAll(_listItemData.begin(), _listItemData.end());
	_listItemData.clear();
	endResetModel();
}
Qt::ItemFlags TNMineModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;
	return QAbstractListModel::flags(index);
}
int TNMineModel::getValidPosition(TNMineAdapter * adapter)
{
	Q_ASSERT(adapter != nullptr);
	int index = -1;
	QString feedId = adapter->getFeedId();
	if (feedId.startsWith("c_"))
	{
		return _listItemData.size() + 1;
	}
	for (int i = 0; i < _listItemData.size(); i++)
	{
		TNMineAdapter *itemData = static_cast<TNMineAdapter*>(_listItemData.at(i));
		if (feedId.startsWith("o_") &&
			itemData != nullptr && !itemData->getFeedId().startsWith("o_"))
		{
			index = i;
			break;
		}
		else if (feedId.startsWith("s_") &&
			itemData != nullptr && !itemData->getFeedId().startsWith("o_")
			&& !itemData->getFeedId().startsWith("s_"))
		{
			index = i;
			break;
		}
	}
	return index;
}
void TNMineModel::UpdateItemBaseInfo(st_FeedPtr feed)
{
	QMutexLocker lock(&_mutex);
	Q_ASSERT(feed != nullptr);
	for (int i = 0; i < _listItemData.size(); i++)
	{
		TNMineAdapter *data = static_cast<TNMineAdapter*>(_listItemData[i]);//[]返回的是引用
		if (data && data->getFeedId() == feed->GetFeedID())
		{

			QString avatarFileName = TNPathUtil::getFeedAvatarPath(feed->GetFeedID());
			QModelIndex index = this->index(i, 0);
			/*
			不更新实际头像URL
			*/
			data->setLatestAvatarURL(feed->GetAvatarID());
			data->setTitle(feed->GetTitle());
			data->setSubTitle(feed->GetSubTile());
			data->setPhotoResourceID(avatarFileName);
			data->setTitlePy(feed->GetTitlePinYin());
			emit dataChanged(index, index);
			break;
		}
	}
}
QModelIndex TNMineModel::getNextIndex(QModelIndex oldIndex)
{
	QModelIndex index;
	if (oldIndex.isValid() && oldIndex.row() <_listItemData.size() - 1)
	{
		index = this->index(oldIndex.row() + 1, 0);
	}
	if (!index.isValid())
	{
		index = this->index(0, 0);
	}
	return index;
}
QModelIndex TNMineModel::getPreIndex(QModelIndex oldIndex)
{
	QModelIndex index;
	if (oldIndex.isValid() && oldIndex.row() >0)
	{
		index = this->index(oldIndex.row() - 1, 0);
	}
	if (!index.isValid())
	{
		index = this->index(0, 0);
	}
	return index;
}