#include "TNCardCaseGroupChatModel.h"
#include "TNPathUtil.h"

TNCardCaseGroupChatModel::TNCardCaseGroupChatModel(QObject *parent)
	: TNListModel(parent)
{
	_startFlag = false;
}

TNCardCaseGroupChatModel::~TNCardCaseGroupChatModel()
{

}
void TNCardCaseGroupChatModel::appendData(QList<TNCardCaseGroupChatAdapter *> adapterList)
{
	QList<TNCardCaseGroupChatAdapter *>::iterator it;
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
void TNCardCaseGroupChatModel::appendData(TNCardCaseGroupChatAdapter * adapter)
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
int TNCardCaseGroupChatModel::setSearchSelected(const QString & feedId, const QString &belongId)
{
	int index = -1;
	for (int i = 0; i < _listItemData.size(); i++)
	{
		TNCardCaseGroupChatAdapter *itemData = static_cast<TNCardCaseGroupChatAdapter*>(_listItemData.at(i));
		if (itemData && itemData->getGroupChatId() == feedId 
			&& itemData->getBelongFeedId() == belongId)
		{
			index = i;
			break;
		}
	}
	return index;
}
void TNCardCaseGroupChatModel::refreshItem(const QString &feedId)
{
	QMutexLocker lock(&_mutex);
	for (int i = 0; i < _listItemData.size(); i++)
	{
		TNCardCaseGroupChatAdapter *itemData = static_cast<TNCardCaseGroupChatAdapter*>(_listItemData[i]);//[]返回的是引用
		if (itemData && itemData->getGroupChatId() == feedId)
		{
			itemData->setAvatarURL(itemData->getLatestAvatarURL());
			QModelIndex q_index = this->index(i, 0);
			emit dataChanged(q_index, q_index);
		}
	}
}
QModelIndex TNCardCaseGroupChatModel::updateGroupChatItemInfo(const QString &feedId, const QString &name, const QString &file, int memberCount,
	const QString& avatarURL)
{
	QMutexLocker lock(&_mutex);
	QModelIndex index;
	for (int i = 0; i < _listItemData.size(); i++)
	{
		TNCardCaseGroupChatAdapter *data = static_cast<TNCardCaseGroupChatAdapter*>(_listItemData[i]);//[]返回的是引用
		if (data && data->getGroupChatId() == feedId)
		{
			index = this->index(i, 0);
			//更新model
			data->setPhotoResourceID(file);
			data->setTitle(name);
			data->setMemberCount(memberCount);
			/*
			此处不更新实际头像URL
			*/
			data->setLatestAvatarURL(avatarURL);
			emit dataChanged(index, index);
			break;
		}
	}
	return index;
}
void TNCardCaseGroupChatModel::removeItem(const QString &feedId, const QString &belongId)
{
	QMutexLocker lock(&_mutex);
	int index = -1;
	for (int i = 0; i < _listItemData.size(); i++)
	{
		TNCardCaseGroupChatAdapter *itemData = static_cast<TNCardCaseGroupChatAdapter*>(_listItemData.at(i));
		Q_ASSERT(itemData != NULL);
		if (itemData && itemData->getGroupChatId() == feedId 
			&& itemData->getBelongFeedId() == belongId)
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
void TNCardCaseGroupChatModel::insertItem(TNCardCaseGroupChatAdapter * adapter)
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
void TNCardCaseGroupChatModel::resetModel()
{
	QMutexLocker lock(&_mutex);
	beginResetModel();
	qDeleteAll(_listItemData.begin(), _listItemData.end());
	_listItemData.clear();
	endResetModel();
}
Qt::ItemFlags TNCardCaseGroupChatModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;
	return QAbstractListModel::flags(index);
}
int TNCardCaseGroupChatModel::getValidPosition(TNCardCaseGroupChatAdapter * adapter)
{
	Q_ASSERT(adapter != nullptr);
	int index = -1;
	if (adapter->getIsCreator())
	{
		index = 0;
	}
	else
	{
		for (int i = 0; i < _listItemData.size(); i++)
		{
			TNCardCaseGroupChatAdapter *itemData = static_cast<TNCardCaseGroupChatAdapter*>(_listItemData.at(i));
			if (itemData && itemData != nullptr 
				&& itemData->getIsCreator() == false)
			{
				index = i;
				break;
			}
		}
	}
	return index;
}
QModelIndex TNCardCaseGroupChatModel::getNextIndex(QModelIndex oldIndex)
{
	QModelIndex index;
	if (oldIndex.isValid() && oldIndex.row() <_listItemData.size() - 1 && _startFlag)
	{
		index = this->index(oldIndex.row() + 1, 0);
	}
	if (!index.isValid())
	{
		_startFlag = true;
		index = this->index(0, 0);
	}
	return index;
}
QModelIndex TNCardCaseGroupChatModel::getPreIndex(QModelIndex oldIndex)
{
	QModelIndex index;
	if (oldIndex.isValid() && oldIndex.row() >0 && _startFlag)
	{
		index = this->index(oldIndex.row() - 1, 0);
	}
	if (!index.isValid())
	{
		_startFlag = true;
		index = this->index(0, 0);
	}
	return index;
}
void TNCardCaseGroupChatModel::updateKeyStartFlag(bool flag)
{
	_startFlag = flag;
}
bool TNCardCaseGroupChatModel::isUpdateHeadImage(const QString &feedId, const QString &avatarURL)
{
	QMutexLocker lock(&_mutex);
	qInfo() << "[CardCase][TNCardCaseGroupChatModel]isUpdateHeadImage feed:" << feedId;

	bool ret = true;
	for (int i = 0; i < _listItemData.size(); i++)
	{
		TNCardCaseGroupChatAdapter *data = static_cast<TNCardCaseGroupChatAdapter*>(_listItemData[i]);//[]返回的是引用
		if (data && data->getGroupChatId() == feedId)
		{
			ret = data->getAvatarURL() != avatarURL;
			break;
		}
	}
	qInfo() << "[CardCase][TNCardCaseGroupChatModel]isUpdateHeadImage return:" << ret;
	return ret;
}
bool TNCardCaseGroupChatModel::isUpdateGroupInfo(const QString &feedId, const QString &name, 
	const QString &headImage, int memberCount)
{
	QMutexLocker lock(&_mutex);
	qInfo() << "[CardCase][TNCardCaseGroupChatModel]isUpdateGroupInfo feed:" << feedId;

	bool ret = true;
	for (int i = 0; i < _listItemData.size(); i++)
	{
		TNCardCaseGroupChatAdapter *data = static_cast<TNCardCaseGroupChatAdapter*>(_listItemData[i]);//[]返回的是引用
		if (data && data->getGroupChatId() == feedId)
		{
			ret = ((data->getAvatarURL() != headImage) || 
				(data->getTitle() != name) || (data->getMemberCount() != memberCount));
			break;
		}
	}
	qInfo() << "[CardCase][TNCardCaseGroupChatModel]isUpdateGroupInfo return:" << ret;
	return ret;
}