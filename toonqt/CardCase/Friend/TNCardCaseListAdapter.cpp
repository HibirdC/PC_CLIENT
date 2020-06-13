#include "TNCardCaseListAdapter.h"
#include <QDebug>
#include "TNDataCache.h"
#include "TNCHNHelper.h"

TNCardCaseListAdapter::TNCardCaseListAdapter(int type)
{
	_age = 0;
    _type = type;
	_isShowMyInfo = false;
	_isRepaint = true;
	_isShowRemark = false;
	_newFriendUnRead = 0;
}

TNCardCaseListAdapter::~TNCardCaseListAdapter()
{

}

QString TNCardCaseListAdapter::getName()
{
    return _name;
}


QString TNCardCaseListAdapter::getDialogID()
{
    return _dialogID;
}

QString TNCardCaseListAdapter::getSubTitle()
{
	if (_subTitle.length() == 0)
    {
        return QString::fromUtf8("");
    }

	return _subTitle;
}

QString TNCardCaseListAdapter::getPhotoResID()
{
	return _photoResID;
}


TNCardCaseListModel::TNCardCaseListModel(QObject *parent) :
    TNListModel(parent)
{
	_startFlag = false;
}

void TNCardCaseListModel::appendData(QList<TNCardCaseListAdapter *> adapterList)
{
	QList<TNCardCaseListAdapter *>::iterator it;
	QModelIndex modelIndex;
	int listSize = _listItemData.size();
	beginInsertRows(modelIndex, listSize, listSize + adapterList.size()-1);
	for (it = adapterList.begin(); it != adapterList.end();it++)
	{
		if ((*it)!=NULL)
			_listItemData.append(*it);
	}
	endInsertRows();
}
void TNCardCaseListModel::appendData(TNCardCaseListAdapter *adapter)
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
int TNCardCaseListModel::setSearchSelected(const QString & feedId,const QString &belongId)
{
	int index = -1;
	for (int i = 0; i < _listItemData.size(); i++)
	{
		TNCardCaseListAdapter *itemData = static_cast<TNCardCaseListAdapter*>(_listItemData.at(i));
		Q_ASSERT(itemData);
		if (itemData && itemData->getDialogID() == feedId
			&& itemData->getBelongFeedId() == belongId)
		{
			index = i;
			break;
		}
	}
	return index;
}
void TNCardCaseListModel::updateFriendBelong(const QString &feedId, int infactCount, bool isAdd)
{
	QMutexLocker lock(&_mutex);
	int count = 0;
	for (int i = 0; i < _listItemData.size(); i++)
	{
		if (count >= infactCount)
		{
			break;
		}
		TNCardCaseListAdapter *itemData = static_cast<TNCardCaseListAdapter*>(_listItemData.at(i));
		Q_ASSERT(itemData);
		if (itemData && itemData->getDialogID() == feedId)
		{
			QModelIndex q_index = this->index(i, 0);
			TNCardCaseListAdapter *data = static_cast<TNCardCaseListAdapter*>(_listItemData[i]);//[]返回的是引用
			if (data != NULL)
			{
				data->setIsShowMyInfo(isAdd);
				qInfo() << "[CardCase][TNCardCaseListModel]updateFriendBelong update belong flag,flag: " << isAdd;
				count++;
			}
		}
	}
}
void TNCardCaseListModel::refreshItem(const QString &feedId)
{
	QMutexLocker lock(&_mutex);
	for (int i = 0; i < _listItemData.size(); i++)
	{
		TNCardCaseListAdapter *itemData = static_cast<TNCardCaseListAdapter*>(_listItemData[i]);//[]返回的是引用
		Q_ASSERT(itemData);
		if (itemData && itemData->getDialogID() == feedId)
		{
			itemData->setAvatarUrl(itemData->getLatestAvatarUrl());
			QModelIndex q_index = this->index(i, 0);
			emit dataChanged(q_index, q_index);
		}
	}
}
void TNCardCaseListModel::updateFriendItemInfo(const QString &feedId, const QString &file,
	const QString &name, const QString &namePy, const QString &subName, const QString &avatarURL)
{
	QMutexLocker lock(&_mutex);
	qInfo() << "[CardCase][TNCardCaseListModel]updateFriendItemInfo feed: " << feedId <<" name:" << name;
	for (int i = 0; i < _listItemData.size(); i++)
	{
		TNCardCaseListAdapter *itemData = static_cast<TNCardCaseListAdapter*>(_listItemData.at(i));
		Q_ASSERT(itemData);
		/*
		涉及到备注的好友，不一定显示在一起。需要遍历所有item
		*/
		if (itemData && itemData->getDialogID() == feedId)
		{
			QModelIndex q_index = this->index(i, 0);
			//更新model
			TNCardCaseListAdapter *data = static_cast<TNCardCaseListAdapter*>(_listItemData[i]);//[]返回的是引用
			if (data != NULL)
			{
				qInfo() << "[CardCase][TNCardCaseListModel]updateFriendItemInfo update";
				data->setPhotoResID(file);
				if (!data->getIsShowReMark())
				{
					qInfo() << "[CardCase][TNCardCaseListModel]updateFriendItemInfo getIsShowReMark true";
					data->setName(name);
				}
				data->setStaticTitle(name);
				data->setStaticTitlePy(namePy);
				data->setSubTitle(subName);
				/*
				头像下载完成后，重置
				*/
				data->setLatestAvatarUrl(avatarURL);
				emit dataChanged(q_index, q_index);
			}
		}
	}
}
void TNCardCaseListModel::updateFriendItemMyInfo(const QString &feedId, const QString myName)
{
	QMutexLocker lock(&_mutex);
	for (int i = 0; i < _listItemData.size(); i++)
	{
		TNCardCaseListAdapter *itemData = static_cast<TNCardCaseListAdapter*>(_listItemData.at(i));
		Q_ASSERT(itemData);
		if (itemData && itemData->getBelongFeedId() == feedId)
		{
			QModelIndex q_index = this->index(i, 0);
			//更新model
			TNCardCaseListAdapter *data = static_cast<TNCardCaseListAdapter*>(_listItemData[i]);//[]返回的是引用
			if (data != NULL)
			{
				data->setMyTitle(myName);
			}
		}
	}
}
int TNCardCaseListModel::removeRowsExceptKeyword(const QString& keyword)
{
    //QString enKeyword = CWQPinyin::PinyinFromChiniseString(keyword);
    int removedCount = 0;
	/* beginResetModel();
	 for(int i = _listItemData.size() - 1 ; i >= 0; i--)
	 {
	 CWQMessageListAdapter *itemData = static_cast<CWQMessageListAdapter*>(_listItemData.at(i));
	 QString enName = CWQPinyin::PinyinFromChiniseString(itemData->getName());
	 if (!enName.startsWith(enKeyword))
	 {
	 delete _listItemData.at(i);
	 _listItemData.removeAt(i);
	 removedCount++;
	 }
	 }
	 endResetModel();*/

    return removedCount;
}

bool TNCardCaseListModel::removeRowByDialogId(const QString& dialogId)
{
    if (dialogId.length() == 0)
        return false;

    bool ret = false;
    for (int i = 0; i < _listItemData.size(); i++)
    {
        TNCardCaseListAdapter *itemData = static_cast<TNCardCaseListAdapter*>(_listItemData.at(i));
		Q_ASSERT(itemData);
		if (itemData && itemData->getDialogID() == dialogId)
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
int TNCardCaseListModel::getDupItemIndex(const QString &feedId)
{
	int index = -1;
	for (int i = 0; i < _listItemData.size(); i++)
	{
		TNCardCaseListAdapter *itemData = static_cast<TNCardCaseListAdapter*>(_listItemData.at(i));
		Q_ASSERT(itemData);
		if (itemData && itemData->getDialogID() == feedId)
		{
			index = i;
			break;
		}
	}
	return index;
}
int TNCardCaseListModel::getValidPosition(TNCardCaseListAdapter * adapter,bool &newItem)
{
	Q_ASSERT(adapter != NULL);
	newItem = false;
	QMap<QChar, int> firstLetterToFriendMap;
	QMap<QChar, int> firstSCharToFriendMap;
	QString Name = adapter->getName();
	QChar Key = adapter->getTitlePinYin().at(0).toUpper();
	int index = -1;
	getSubItemStruct(firstLetterToFriendMap, firstSCharToFriendMap);
	if (isalpha(Key.toLatin1()))
	{
		int item = 0; //因为新学员 常驻0的位置
		QMap<QChar, int>::iterator It;
		if ((It = firstLetterToFriendMap.find(Key)) == firstLetterToFriendMap.end())
		{
			//没有此节点，插入一个
			newItem = true;
			firstLetterToFriendMap[Key] = 1;
		}
		for (QMap<QChar, int>::iterator myIt = firstLetterToFriendMap.begin(); myIt != firstLetterToFriendMap.end(); myIt++)
		{
			if (myIt.key() == Key)
			{
				//需要找到相同节点的下一个
				if (newItem)
				{
					index = item + myIt.value() + 1;
				}
				else
				{
					int subindex = getDupItemIndex(adapter->getDialogID());
					index = subindex == -1 ? (item + myIt.value() + 2) : subindex+1;
				}
				//index = newItem?():(item+myIt.value()+2); //包括当前Key 的Item 因此是2
				break;
			}
			item += myIt.value() + 1;
		}
	}
	else
	{
		Key = '#';
		int item = firstLetterToFriendMap.size();
		for (QMap<QChar, int>::iterator myIt = firstLetterToFriendMap.begin(); myIt != firstLetterToFriendMap.end(); myIt++)
		{
			item += myIt.value();
		}
		QMap<QChar, int>::iterator It;
		if ((It = firstSCharToFriendMap.find(Key)) == firstSCharToFriendMap.end())
		{
			//没有此节点，插入一个
			newItem = true;
			firstSCharToFriendMap[Key] = 1;
		}
		for (QMap<QChar, int>::iterator myIt = firstSCharToFriendMap.begin(); myIt != firstSCharToFriendMap.end(); myIt++)
		{
			if (myIt.key() == Key)
			{
				//需要找到相同节点的下一个
				if (newItem)
				{
					index = item + myIt.value() + 1;
				}
				else
				{
					int subindex = getDupItemIndex(adapter->getDialogID());
					index = subindex == -1 ? (item + myIt.value() + 2) : subindex + 1;
				}
				//index = newItem ? (item + myIt.value() + 1) : (item + myIt.value() + 2); //包括当前Key 的Item 因此是2
				break;
			}
			item += myIt.value() + 1;
		}
	}
	qInfo() << "[CardCase][TNCardCaseListModel] getValidPosition :" << index;
	return index;
}
int TNCardCaseListModel::getValidPositionNOTDup(TNCardCaseListAdapter * adapter, bool &newItem)
{
	Q_ASSERT(adapter != NULL);
	newItem = false;
	QMap<QChar, int> firstLetterToFriendMap;
	QMap<QChar, int> firstSCharToFriendMap;
	QString Name = adapter->getName();
	QChar Key = adapter->getTitlePinYin().at(0).toUpper();
	int index = -1;
	getSubItemStruct(firstLetterToFriendMap, firstSCharToFriendMap);
	if (isalpha(Key.toLatin1()))
	{
		int item = 0; //因为新学员 常驻0的位置
		QMap<QChar, int>::iterator It;
		if ((It = firstLetterToFriendMap.find(Key)) == firstLetterToFriendMap.end())
		{
			//没有此节点，插入一个
			newItem = true;
			firstLetterToFriendMap[Key] = 1;
		}
		for (QMap<QChar, int>::iterator myIt = firstLetterToFriendMap.begin(); myIt != firstLetterToFriendMap.end(); myIt++)
		{
			if (myIt.key() == Key)
			{
				//需要找到相同节点的下一个
				if (newItem)
				{
					index = item + myIt.value() + 1;
				}
				else
				{
					index = item + myIt.value() + 2;
				}
				//index = newItem?():(item+myIt.value()+2); //包括当前Key 的Item 因此是2
				break;
			}
			item += myIt.value() + 1;
		}
	}
	else
	{
		Key = '#';
		int item = firstLetterToFriendMap.size();
		for (QMap<QChar, int>::iterator myIt = firstLetterToFriendMap.begin(); myIt != firstLetterToFriendMap.end(); myIt++)
		{
			item += myIt.value();
		}
		QMap<QChar, int>::iterator It;
		if ((It = firstSCharToFriendMap.find(Key)) == firstSCharToFriendMap.end())
		{
			//没有此节点，插入一个
			newItem = true;
			firstSCharToFriendMap[Key] = 1;
		}
		for (QMap<QChar, int>::iterator myIt = firstSCharToFriendMap.begin(); myIt != firstSCharToFriendMap.end(); myIt++)
		{
			if (myIt.key() == Key)
			{
				//需要找到相同节点的下一个
				if (newItem)
				{
					index = item + myIt.value() + 1;
				}
				else
				{
					index = item + myIt.value() + 2;
				}
				//index = newItem ? (item + myIt.value() + 1) : (item + myIt.value() + 2); //包括当前Key 的Item 因此是2
				break;
			}
			item += myIt.value() + 1;
		}
	}
	qInfo() << "[CardCase][TNCardCaseListModel] getValidPosition :" << index;
	return index;
}
int TNCardCaseListModel::getSubItemStruct(QMap<QChar, int> &firstLetterToFriendMap,QMap<QChar, int> &firstSCharToFriendMap)
{
	for (int i = 0; i < _listItemData.size(); i++)
	{
		TNCardCaseListAdapter *itemData = static_cast<TNCardCaseListAdapter*>(_listItemData.at(i));
		Q_ASSERT(itemData != NULL);
		QChar start = itemData->getName().at(0);
		if (itemData && itemData->getType() == 0 
			&& isalpha(start.toLatin1()))
		{
			int count = 0;
			for (int j = i + 1; j < _listItemData.size(); j++)
			{
				TNCardCaseListAdapter *subItemData = static_cast<TNCardCaseListAdapter*>(_listItemData.at(j));
				Q_ASSERT(subItemData != NULL);
				if (subItemData && 
					subItemData->getType() == 0)
				{
					i = i + count;
					break;
				}
				count++;
			}
			firstLetterToFriendMap[start] = count;
		}
		else if (itemData->getType() == 0)
		{
			int count = 0;
			for (int j = i + 1; j < _listItemData.size(); j++)
			{
				TNCardCaseListAdapter *subItemData = static_cast<TNCardCaseListAdapter*>(_listItemData.at(j));
				Q_ASSERT(subItemData != NULL);
				if (subItemData && subItemData->getType() == 0)
				{
					i = i + count;
					break;
				}
				count++;
			}
			firstSCharToFriendMap[start] = count;
		}
	}
	return _listItemData.size();
}
void TNCardCaseListModel::removeItem(const QString &feedId, const QString &belongId)
{
	QMutexLocker lock(&_mutex);
	int index = -1;
	bool IsOnlyOneItem = false;
	for (int i = 0; i < _listItemData.size(); i++)
	{
		TNCardCaseListAdapter *itemData = static_cast<TNCardCaseListAdapter*>(_listItemData.at(i));
		Q_ASSERT(itemData != NULL);
		if (itemData && itemData->getDialogID() == feedId 
			&& itemData->getBelongFeedId() == belongId)
		{
			index = i;
			QMap<QChar, int> firstLetterToFriendMap;
			QMap<QChar, int> firstNumberToFriendMap;
			QMap<QChar, int> firstSCharToFriendMap;
			getSubItemStruct(firstLetterToFriendMap, firstSCharToFriendMap);
			QChar pKey = itemData->getTitlePinYin().at(0).toUpper();
			if (isalpha(pKey.toLatin1()))
			{
				QMap<QChar, int>::iterator it;
				if (((it = firstLetterToFriendMap.find(pKey)) != firstLetterToFriendMap.end()) && it.value() <= 1)
				{
					IsOnlyOneItem = true;
				}
			}
			else
			{
				pKey = '#';
				QMap<QChar, int>::iterator it;
				if (((it = firstSCharToFriendMap.find(pKey)) != firstSCharToFriendMap.end()) && it.value() <= 1)
				{
					IsOnlyOneItem = true;
				}
			}
			break;
		}
	}
	if (index != -1)
	{
		if (IsOnlyOneItem)
		{
			QModelIndex q_index;
			beginRemoveRows(q_index, index - 1, index);
			for (int i = 0; i < 2; i++)
			{
				delete _listItemData.at(index - 1);
				_listItemData.removeAt(index - 1); //执行两次，第一次 字母Item, 第二次 真实的Item
			}
			endRemoveRows();
		}
		else
		{
			QModelIndex q_index;
			beginRemoveRows(q_index, index, index);
			delete _listItemData.at(index);
			_listItemData.removeAt(index);
			endRemoveRows();
		}
	}
}
void TNCardCaseListModel::insertItem(TNCardCaseListAdapter * adapter,int enbaleDup)
{
	if (adapter == NULL)
	{
		return;
	}
	bool newItem = false;
	int index = enbaleDup ? getValidPositionNOTDup(adapter, newItem) : getValidPosition(adapter, newItem);
	if (index>0)
	{
		if (newItem)
		{
			TNCardCaseListAdapter * tempAdapter = new TNCardCaseListAdapter(TNCardCaseListAdapter::FriendLetter);
			QChar name = adapter->getTitlePinYin().at(0).toUpper();
			if (!isalpha(name.toLatin1()))
			{
				name = '#';
			}
			tempAdapter->setName(name);
			QModelIndex q_index;
			beginInsertRows(q_index, index-1, index);
			_listItemData.insert(index - 1, tempAdapter);
			_listItemData.insert(index, adapter);
			endInsertRows();
		}
		else
		{
			QModelIndex q_index;
			beginInsertRows(q_index, index, index);
			_listItemData.insert(index, adapter);
			endInsertRows();
		}
	}
}
void TNCardCaseListModel::resetModel()
{
	QMutexLocker lock(&_mutex);
	beginResetModel();
	qDeleteAll(_listItemData.begin(), _listItemData.end());
	_listItemData.clear();
	endResetModel();
}
void TNCardCaseListModel::updateNewFriendUnRead(int count)
{
	QMutexLocker lock(&_mutex);
	TNCardCaseListAdapter *itemData  = static_cast<TNCardCaseListAdapter*>(_listItemData[0]);//[]返回的是引用
	if (itemData != nullptr && itemData->getType() == TNCardCaseListAdapter::NewFriend)
	{
		itemData->setNewFriendUnRead(count);
	}
}
Qt::ItemFlags TNCardCaseListModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;
	return QAbstractListModel::flags(index);
}
void TNCardCaseListModel::updateFriendItemReMark(QString feedId, QString reMark, QString belongFeed)
{
	for (int i = 0; i < _listItemData.size(); i++)
	{
		TNCardCaseListAdapter *itemData = static_cast<TNCardCaseListAdapter*>(_listItemData.at(i));
		Q_ASSERT(itemData);
		if (itemData && itemData->getDialogID() == feedId 
			&& itemData->getBelongFeedId() == belongFeed)
		{
			QString remarkpy = TNCHNHelper::GetPinyins(reMark);
			if (itemData->getIsShowReMark() && itemData->getName() == reMark) //当前已经是备注
			{
				break;
			}
			else if (reMark.isEmpty())
			{
				st_FeedPtr feed = TNDataCache::GetInstance()->getSpecialFriendFeed(feedId, belongFeed);
				if (feed != nullptr)
				{
					reMark = feed->GetTitle();
					remarkpy = feed->GetTitlePinYin();
				}
			}

			TNCardCaseListAdapter * newItem = new TNCardCaseListAdapter(TNCardCaseListAdapter::FriendItem);
			newItem->setName(reMark);
			newItem->setTitlePinYin(remarkpy);
			newItem->setIsShowReMark(true);
			newItem->setAge(itemData->getAge());
			newItem->setAvatarUrl(itemData->getAvatarUrl());
			newItem->setLatestAvatarUrl(itemData->getLatestAvatarUrl());
			newItem->setBelongFeedId(itemData->getBelongFeedId());
			newItem->setDialogID(itemData->getDialogID());
			newItem->setIsRepaint(itemData->getIsRepaint());
			newItem->setIsShowMyInfo(itemData->getIsShowMyInfo());
			newItem->setMyTitle(itemData->getMyTitle());
			newItem->setPhotoResID(itemData->getPhotoResID());
			newItem->setSex(itemData->getSex());
			newItem->setSubTitle(itemData->getSubTitle());
			newItem->setTag(itemData->getTag());
			newItem->setUserId(itemData->getUserId());
			newItem->setStaticTitle(itemData->getStaticTitle());
			newItem->setStaticTitlePy(itemData->getStaticTitlePy());

			removeItem(feedId, belongFeed);
			insertItem(newItem,true);
			break;
		}
	}
}
QModelIndex TNCardCaseListModel::getNextIndex(QModelIndex oldIndex)
{
	QModelIndex index;
	if (oldIndex.isValid()
		&& oldIndex.row() <_listItemData.size() - 1 && _startFlag)
	{
		index = this->index(oldIndex.row() + 1, 0);
		TNCardCaseListAdapter * typeItem = static_cast<TNCardCaseListAdapter*>(_listItemData.at(index.row()));
		Q_ASSERT(typeItem != nullptr);
		if (typeItem && typeItem->getType() == TNCardCaseListAdapter::FriendLetter
			&& index.row() <_listItemData.size())
		{
			index = this->index(oldIndex.row() + 2, 0);
		}
	}
	if (!index.isValid())
	{
		_startFlag = true;
		index = this->index(0, 0);
	}
	return index;
}
QModelIndex TNCardCaseListModel::getPreIndex(QModelIndex oldIndex)
{
	QModelIndex index;
	if (oldIndex.isValid() && oldIndex.row() >1 && _startFlag)
	{
		index = this->index(oldIndex.row() - 1, 0);
		TNCardCaseListAdapter * typeItem = static_cast<TNCardCaseListAdapter*>(_listItemData.at(index.row()));
		Q_ASSERT(typeItem != nullptr);
		if (typeItem && typeItem->getType() == TNCardCaseListAdapter::FriendLetter
			&& index.row() <_listItemData.size())
		{
			index = this->index(oldIndex.row() - 2, 0);
		}
	}
	if (!index.isValid())
	{
		_startFlag = true;
		index = this->index(0, 0);
	}
	return index;
}
void TNCardCaseListModel::updateKeyStartFlag(bool flag)
{
	_startFlag = flag;
}