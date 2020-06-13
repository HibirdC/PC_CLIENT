#include "TNSearchAdapter.h"
#include <QDebug>
#include "TNSearchDataItemWidget.h"


TNSearchAdapter::TNSearchAdapter(int type)
{
	_age = 0;
    _type = type;
	_itemCountIflabel = -1;
	_isShowBelong = false;
	_isForcerefreshAvator = false;
}

TNSearchAdapter::~TNSearchAdapter()
{

}

QString TNSearchAdapter::getName()
{
    return _name;
}


QString TNSearchAdapter::getDialogID()
{
    return _dialogID;
}
QString TNSearchAdapter::getPhotoResID()
{
	return _photoResID;
}


TNCardCaseSearchListModel::TNCardCaseSearchListModel(QObject *parent) :
    TNTableModel(parent),
	_tableView(NULL)
{
}

void TNCardCaseSearchListModel::appendData(QList<TNSearchAdapter *> adapterList)
{
	QList<TNSearchAdapter *>::iterator it;
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
void TNCardCaseSearchListModel::appendData(TNSearchAdapter *adapter)
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
int TNCardCaseSearchListModel::setSearchSelected(TNSearchAdapter *adapter)
{
	int index = -1;
	for (int i = 0; i < _listItemData.size(); i++)
	{
		TNSearchAdapter *itemData = static_cast<TNSearchAdapter*>(_listItemData.at(i));
		if (itemData->getDialogID() == adapter->getDialogID())
		{
			index = i;
			break;
		}
	}
	return index;
}
void TNCardCaseSearchListModel::UpdateItemAvatar(QString file, QString feedId)
{
	_mutex.lock();
	int index = -1;
	for (int i = 0; i < _listItemData.size(); i++)
	{
		TNSearchAdapter *itemData = static_cast<TNSearchAdapter*>(_listItemData.at(i));
		if (itemData->getDialogID() == feedId)
		{
			index = i;
			break;
		}
	}
	QModelIndex q_index = this->index(index, 0);
	TNSearchDataItemWidget* item = static_cast<TNSearchDataItemWidget*>(_tableView->indexWidget(q_index));
	if (item != NULL){
		item->setPhoto(file, ((":/Resources/toolWidget/defaultAvatar.png")),QSize(30,30));
	}
	_mutex.unlock();
}



void TNCardCaseSearchListModel::setTableView(QTableView* tableView)
{
	_tableView = tableView;
}
void TNCardCaseSearchListModel::ResetModel()
{
	beginResetModel();
	_listItemData.clear();
	endResetModel();
}
