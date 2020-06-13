#include "TNATSearchAdapter.h"
#include "tnatlistitemwidget.h"

#include <QDebug>


TNATSearchAdapter::TNATSearchAdapter()
{
	_age = 0;
	_onTop = 0;
	_isForcerefreshAvator = false;
}

TNATSearchAdapter::~TNATSearchAdapter()
{

}

QString TNATSearchAdapter::getName()
{
    return _name;
}


QString TNATSearchAdapter::getDialogID()
{
    return _dialogID;
}

QString TNATSearchAdapter::getSubTitle()
{
	if (_subTitle.length() == 0)
    {
        return QString::fromUtf8("");
    }

	return _subTitle;
}

QString TNATSearchAdapter::getPhotoResID()
{
	return _photoResID;
}


TNATSearchListModel::TNATSearchListModel(QObject *parent) :
    TNTableModel(parent),
	_tableView(NULL)
{
}

void TNATSearchListModel::appendData(QList<TNATSearchAdapter *> adapterList)
{
	QList<TNATSearchAdapter *>::iterator it;
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
void TNATSearchListModel::appendData(TNATSearchAdapter *adapter)
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
int TNATSearchListModel::setSearchSelected(TNATSearchAdapter *adapter)
{
	int index = -1;
	for (int i = 0; i < _listItemData.size(); i++)
	{
		TNATSearchAdapter *itemData = static_cast<TNATSearchAdapter*>(_listItemData.at(i));
		if (itemData->getDialogID() == adapter->getDialogID())
		{
			index = i;
			break;
		}
	}
	return index;
}
void TNATSearchListModel::UpdateItemAvatar(QString file, QString feedId)
{
	_mutex.lock();
	int index = -1;
	Cust_Type type = nothing;
	for (int i = 0; i < _listItemData.size(); i++)
	{
		TNATSearchAdapter *itemData = static_cast<TNATSearchAdapter*>(_listItemData.at(i));
		if (itemData->getDialogID() == feedId)
		{
			type = feedId.at(0).toLatin1() == 'c' ? Cust_Type::cust_ellipse : Cust_Type::cust_radius;
			index = i;
			break;
		}
	}
	QModelIndex q_index = this->index(index, 0);
	TNATListItemWidget* item = static_cast<TNATListItemWidget*>(_tableView->indexWidget(q_index));
	if (item != NULL){
		item->setPhoto(file, ((":/Resources/toolWidget/defaultAvatar.png")), type);
	}
	_mutex.unlock();
}



void TNATSearchListModel::setTableView(QTableView* tableView)
{
	_tableView = tableView;
}
void TNATSearchListModel::ResetModel()
{
	beginResetModel();
	_listItemData.clear();
	endResetModel();
}
