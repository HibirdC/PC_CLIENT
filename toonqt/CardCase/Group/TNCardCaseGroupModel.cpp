#include "TNCardCaseGroupModel.h"
#include "TNPathUtil.h"
TNCardCaseGroupModel::TNCardCaseGroupModel(QObject *parent)
	: TNListModel(parent)
{
	_startFlag = false;
}

TNCardCaseGroupModel::~TNCardCaseGroupModel()
{

}
void TNCardCaseGroupModel::appendData(QList<TNCardCaseGroupAdapter *> adapterList)
{
	QList<TNCardCaseGroupAdapter *>::iterator it;
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
void TNCardCaseGroupModel::appendData(TNCardCaseGroupAdapter * adapter)
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
int TNCardCaseGroupModel::setSearchSelected(const QString & feedId, const QString &belongId)
{
	int index = -1;
	for (int i = 0; i < _listItemData.size(); i++)
	{
		TNCardCaseGroupAdapter *itemData = static_cast<TNCardCaseGroupAdapter*>(_listItemData.at(i));
		Q_ASSERT(itemData);
		if (itemData && itemData->getGroupId() == feedId 
			&& itemData->getBelongFeedId() == belongId)
		{
			index = i;
			break;
		}
	}
	return index;
}
void TNCardCaseGroupModel::refreshItem(const QString &feedId)
{
	QMutexLocker lock(&_mutex);
	for (int i = 0; i < _listItemData.size(); i++)
	{
		TNCardCaseGroupAdapter *itemData = static_cast<TNCardCaseGroupAdapter*>(_listItemData[i]);//[]返回的是引用
		Q_ASSERT(itemData);
		if (itemData && itemData->getGroupId() == feedId)
		{
			itemData->setAvatarURL(itemData->getLatestAvatarURL());
			QModelIndex q_index = this->index(i, 0);
			emit dataChanged(q_index, q_index);
		}
	}
}
void TNCardCaseGroupModel::updateGroupItemInfo(const QString &feedId, const QString &name, const QString &file, const QString &subject,
	TNStructGroup oldGroup, TNStructGroup newGroup)
{
	QMutexLocker lock(&_mutex);
	for (int i = 0; i < _listItemData.size(); i++)
	{
		TNCardCaseGroupAdapter *data = static_cast<TNCardCaseGroupAdapter*>(_listItemData[i]);//[]返回的是引用
		Q_ASSERT(data);
		if (data && data->getGroupId() == feedId)
		{
			QModelIndex index = this->index(i, 0);
			if (oldGroup.m_flag != newGroup.m_flag)
			{
				//需要将此节点删除，因为角色发生变化
				QModelIndex q_index;
				beginRemoveRows(q_index, i, i);
				_listItemData.removeAt(i);
				endRemoveRows();
				//新添加一个节点
				data->setTitle(name);
				data->setPhotoResourceID(file);
				data->setGroupSubject(subject);
				data->setMemberCount(newGroup.m_memberCount);
				data->setBelongFeedId(newGroup.m_belongId);
				data->setGroupId(feedId);
				data->setIsCreator(newGroup.m_flag == 1);
				data->setIsAdmin(newGroup.m_flag == 2);
				insertItem(data);
			}
			else
			{
				//更新model
				data->setPhotoResourceID(file);
				data->setTitle(name);
				data->setGroupSubject(subject);
				data->setMemberCount(newGroup.m_memberCount);
				emit dataChanged(index, index);
			}
			break;
		}
	}
}
void TNCardCaseGroupModel::removeItem(const QString &feedId, const QString &belongId)
{
	QMutexLocker lock(&_mutex);
	int index = -1;
	for (int i = 0; i < _listItemData.size(); i++)
	{
		TNCardCaseGroupAdapter *itemData = static_cast<TNCardCaseGroupAdapter*>(_listItemData.at(i));
		Q_ASSERT(itemData != NULL);
		if (itemData && itemData->getGroupId() == feedId 
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
void TNCardCaseGroupModel::insertItem(TNCardCaseGroupAdapter * adapter)
{
	if (adapter == NULL)
	{
		return;
	}
	int index = getValidPosition(adapter);
	if (index>=0)
	{
		QModelIndex q_index;
		beginInsertRows(q_index, index, index);
		_listItemData.insert(index, adapter);
		endInsertRows();
	}
}
void TNCardCaseGroupModel::resetModel()
{
	QMutexLocker lock(&_mutex);
	beginResetModel();
	qDeleteAll(_listItemData.begin(), _listItemData.end());
	_listItemData.clear();
	endResetModel();
}
Qt::ItemFlags TNCardCaseGroupModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;
	return QAbstractListModel::flags(index);
}
int TNCardCaseGroupModel::getValidPosition(TNCardCaseGroupAdapter * adapter)
{
	Q_ASSERT(adapter!= nullptr);
	int index = -1;
	if (adapter->getIsCreator())
	{
		index = 0;
	}
	else if (adapter->getIsAdmin())
	{
		int latestAdmin = -1;
		for (int i = 0; i < _listItemData.size(); i++)
		{
			TNCardCaseGroupAdapter *itemData = static_cast<TNCardCaseGroupAdapter*>(_listItemData.at(i));
			Q_ASSERT(itemData);
			if (itemData != nullptr)
			{
				if (itemData->getIsCreator() == false){
					index = i;
					break;
				}
				else{
					latestAdmin = i;
				}
			}
		}
		if (index == -1)
		{
			index = latestAdmin + 1;
		}
	}
	else
	{
		for (int i = 0; i < _listItemData.size(); i++)
		{
			TNCardCaseGroupAdapter *itemData = static_cast<TNCardCaseGroupAdapter*>(_listItemData.at(i));
			Q_ASSERT(itemData);
			if (itemData != nullptr && itemData->getIsCreator() == false 
				&& itemData->getIsAdmin() == false)
			{
				index = i;
				break;
			}
		}
		if (index == -1)
			index = _listItemData.size() + 1;
	}
	return index;
}
void TNCardCaseGroupModel::UpdateGroupMemberCount(const QString &feedId, int count)
{
	QMutexLocker lock(&_mutex);
	for (int i = 0; i < _listItemData.size(); i++)
	{
		TNCardCaseGroupAdapter *data = static_cast<TNCardCaseGroupAdapter*>(_listItemData[i]);//[]返回的是引用
		Q_ASSERT(data);
		if (data && data->getGroupId() == feedId)
		{
			QModelIndex index = this->index(i, 0);
			data->setMemberCount(count);
			emit dataChanged(index, index);
			break;
		}
	}
}
void TNCardCaseGroupModel::UpdateItemBaseInfo(st_FeedPtr feed)
{
	QMutexLocker lock(&_mutex);
	Q_ASSERT(feed!= nullptr);
	for (int i = 0; i < _listItemData.size(); i++)
	{
		TNCardCaseGroupAdapter *data = static_cast<TNCardCaseGroupAdapter*>(_listItemData[i]);//[]返回的是引用
		Q_ASSERT(data);
		if (data && data->getGroupId() == feed->GetFeedID())
		{
			QString tag = feed->GetTag();
			if (!tag.isEmpty())
			{
				QStringList temptag = tag.split(",");
				data->setGroupSubject(temptag[0]);
			}
			QString avatarFileName = TNPathUtil::getFeedAvatarPath(feed->GetFeedID());
			QModelIndex index = this->index(i, 0);
			/*
			此处不更新头像URL，头像下载完成后更新
			*/
			data->setLatestAvatarURL(feed->GetAvatarID());
			data->setTitle(feed->GetTitle());
			data->setTitlePy(feed->GetTitlePinYin());
			data->setPhotoResourceID(avatarFileName);
			emit dataChanged(index, index);
			break;
		}
	}
}
QModelIndex TNCardCaseGroupModel::getNextIndex(QModelIndex oldIndex)
{
	QModelIndex index;
	if (oldIndex.isValid() && 
		oldIndex.row() <_listItemData.size() - 1 && _startFlag)
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
QModelIndex TNCardCaseGroupModel::getPreIndex(QModelIndex oldIndex)
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
void TNCardCaseGroupModel::updateKeyStartFlag(bool flag)
{
	_startFlag = flag;
}