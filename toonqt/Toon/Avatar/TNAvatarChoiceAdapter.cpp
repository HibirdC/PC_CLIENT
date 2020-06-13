#include "TNAvatarChoiceAdapter.h"
#include <QDebug>


TNAvatarChoiceAdapter::TNAvatarChoiceAdapter()
{
	_unReadCount = 0;
	_isCurrentCard = false;
	_isForcerefreshAvator = false;
}

TNAvatarChoiceAdapter::~TNAvatarChoiceAdapter()
{

}

QString TNAvatarChoiceAdapter::getName()
{
    return _name;
}


QString TNAvatarChoiceAdapter::getDialogID()
{
    return _dialogID;
}


QString TNAvatarChoiceAdapter::getPhotoResID()
{
	return _photoResID;
}


TNAvatarChoiceListModel::TNAvatarChoiceListModel(QObject *parent) :
    TNTableModel(parent),
	_tableView(NULL)
{
}

void TNAvatarChoiceListModel::appendData(QList<TNAvatarChoiceAdapter *> adapterList)
{
	QList<TNAvatarChoiceAdapter *>::iterator it;
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
void TNAvatarChoiceListModel::appendData(TNAvatarChoiceAdapter *adapter)
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
int TNAvatarChoiceListModel::setSearchSelected(TNAvatarChoiceAdapter *adapter)
{
	int index = -1;
	for (int i = 0; i < _listItemData.size(); i++)
	{
		TNAvatarChoiceAdapter *itemData = static_cast<TNAvatarChoiceAdapter*>(_listItemData.at(i));
		if (itemData->getDialogID() == adapter->getDialogID())
		{
			index = i;
			break;
		}
	}
	return index;
}
void TNAvatarChoiceListModel::UpdateItemAvatar(QString file, QString feedId)
{
	_mutex.lock();
	int index = -1;
	Cust_Type type = nothing;
	for (int i = 0; i < _listItemData.size(); i++)
	{
		TNAvatarChoiceAdapter *itemData = static_cast<TNAvatarChoiceAdapter*>(_listItemData.at(i));
		if (itemData->getDialogID() == feedId)
		{
			type = feedId.at(0).toLatin1() == 'c' ? Cust_Type::cust_ellipse : Cust_Type::cust_radius;
			index = i;
			break;
		}
	}
	QModelIndex q_index = this->index(index, 0);
	TNAvatarChoiceItem* item = static_cast<TNAvatarChoiceItem*>(_tableView->indexWidget(q_index));
	if (item != NULL){
		item->setPhoto(file, (QStringLiteral(":/Resources/toolWidget/defaultAvatar.png")), type);
	}
	_mutex.unlock();
}



void TNAvatarChoiceListModel::setTableView(QTableView* tableView)
{
	_tableView = tableView;
}
void TNAvatarChoiceListModel::ResetModel()
{
	beginResetModel();
	for (QList<TNModelItemBase*>::iterator it = _listItemData.begin();
		it != _listItemData.end(); it++)
	{
		delete (*it);
		(*it) = nullptr;
	}
	_listItemData.clear();
	endResetModel();
}
