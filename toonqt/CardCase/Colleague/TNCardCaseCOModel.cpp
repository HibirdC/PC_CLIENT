#include "TNCardCaseCOModel.h"
#include <QSize>
#include <QStringList>

#include "Colleague/TNCompanyItem.h"
#include "Colleague/TNDepartmentItem.h"
#include "Colleague/TNStaffItem.h"

TNCardCaseCOModel::TNCardCaseCOModel(TNCardCaseTreeItem *rootItem, QObject *parent)
: QAbstractItemModel(parent), _rootItem(rootItem), _colleagueListWidgtView(nullptr)
{
	_startFlag = false;
}

TNCardCaseCOModel::~TNCardCaseCOModel()
{
	delete _rootItem;
}
int TNCardCaseCOModel::columnCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return static_cast<TNCardCaseTreeItem*>(parent.internalPointer())->columnCount();
	else
		return _rootItem->columnCount();
}

QVariant TNCardCaseCOModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	TNCardCaseTreeItem *item = static_cast<TNCardCaseTreeItem*>(index.internalPointer());
	if (role == Qt::DisplayRole)
	{
		return item->data(index.column());
	}
	return QVariant();
}

Qt::ItemFlags TNCardCaseCOModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;

	return QAbstractItemModel::flags(index);
}

QVariant TNCardCaseCOModel::headerData(int section, Qt::Orientation orientation,
	int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
		return _rootItem->data(section);

	return QVariant();
}

QModelIndex TNCardCaseCOModel::index(int row, int column, const QModelIndex &parent)
const
{
	if (!hasIndex(row, column, parent))
		return QModelIndex();

	TNCardCaseTreeItem *parentItem;

	if (!parent.isValid())
		parentItem = _rootItem;
	else
		parentItem = static_cast<TNCardCaseTreeItem*>(parent.internalPointer());

	TNCardCaseTreeItem *childItem = parentItem->child(row);
	if (childItem)
		return createIndex(row, column, childItem);
	else
		return QModelIndex();
}

QModelIndex TNCardCaseCOModel::parent(const QModelIndex &index) const
{
	if (!index.isValid())
		return QModelIndex();

	TNCardCaseTreeItem *childItem = static_cast<TNCardCaseTreeItem*>(index.internalPointer());
	TNCardCaseTreeItem *parentItem = childItem->parentItem();

	if (parentItem == _rootItem)
		return QModelIndex();

	return createIndex(parentItem->row(), 0, parentItem);
}

int TNCardCaseCOModel::rowCount(const QModelIndex &parent) const
{
	TNCardCaseTreeItem *parentItem;
	if (parent.column() > 0)
		return 0;

	if (!parent.isValid())
		parentItem = _rootItem;
	else
		parentItem = static_cast<TNCardCaseTreeItem*>(parent.internalPointer());

	return parentItem->childCount();
}
void TNCardCaseCOModel::removeItem(QString feedId, int type)
{
	QMutexLocker locker(&_mutex);
}
void TNCardCaseCOModel::insertItem(bool isCreate, TNCardCaseTreeItem * item, int type)
{
	QMutexLocker locker(&_mutex);
}

void TNCardCaseCOModel::setColleagueListView(TNCoTreeView *view)
{
	if (view != nullptr)
		_colleagueListWidgtView = view;
}
void TNCardCaseCOModel::setItemStatus(const QModelIndex & index, bool status)
{
	TNCardCaseTreeItem *item = static_cast<TNCardCaseTreeItem*>(index.internalPointer());
	if (item != nullptr &&item->getItemGrade() == TNCardCaseTreeItem::Department)
		item->setStatus(status);
}
void TNCardCaseCOModel::updateColleagueItemInfo(const QString &feedId, const QString &file,
	const QString &name, const QString &namePy, const QString &userId, const QString &sunName, const QString &avatarURL)
{
	QMutexLocker locker(&_mutex);
	if (_colleagueListWidgtView == nullptr || _rootItem == nullptr)
		return;
	QModelIndex rootIndex = _colleagueListWidgtView->rootIndex();
	for (size_t ic = 0; ic < _rootItem->childCount(); ic++)
	{
		TNCardCaseTreeItem * aCompanyItem = _rootItem->child(ic);
		QModelIndex companyIndex = this->index(ic, 0, rootIndex);
		for (size_t id = 0; id < aCompanyItem->childCount(); id++)
		{
			QModelIndex departmentIndex = this->index(id, 0, companyIndex);
			TNCardCaseTreeItem * aStaffItem = aCompanyItem->child(id);
			if (aStaffItem->childCount() == 0)
			{
				TNStaffItem *staffItem = static_cast<TNStaffItem*>(aStaffItem);
				if (staffItem != NULL && staffItem->getDialogID() == feedId)
				{
					staffItem->setPhotoResourceID(file);
					staffItem->setTitle(QList<QVariant>() << name);
					staffItem->setTitlePy(namePy);
					staffItem->setSubTitle(sunName);
					staffItem->setUserId(userId);
					//实际头像URL此处不更新
					staffItem->setLatestAvatarURL(avatarURL);
					emit dataChanged(departmentIndex, departmentIndex);
				}
			}
			else
			{
				for (size_t ie = 0; ie < aStaffItem->childCount(); ie++)
				{
					QModelIndex staffIndex = this->index(ie, 0, departmentIndex);
					TNStaffItem *staffItem = static_cast<TNStaffItem*>(aStaffItem->child(ie));
					if (staffItem != NULL && staffItem->getDialogID() == feedId)
					{
						staffItem->setPhotoResourceID(file);
						staffItem->setTitle(QList<QVariant>() << name);
						staffItem->setTitlePy(namePy);
						staffItem->setSubTitle(sunName);
						staffItem->setUserId(userId);
						//实际头像URL此处不更新
						staffItem->setLatestAvatarURL(avatarURL);
						emit dataChanged(staffIndex, staffIndex);
					}
				}
			}
		}
	}
}
QModelIndex TNCardCaseCOModel::setColleagueSearchSelected(const QString &feedId, const QString &belongId, QModelIndex &parentIndex)
{
	if (_colleagueListWidgtView == nullptr || _rootItem == nullptr)
		return QModelIndex();
	QModelIndex rootIndex = _colleagueListWidgtView->rootIndex();
	for (size_t ic = 0; ic < _rootItem->childCount(); ic++)
	{
		TNCardCaseTreeItem * aCompanyItem = _rootItem->child(ic);
		QModelIndex companyIndex = this->index(ic, 0, rootIndex);
		for (size_t id = 0; id < aCompanyItem->childCount(); id++)
		{
			QModelIndex departmentIndex = this->index(id, 0, companyIndex);
			TNCardCaseTreeItem * aStaffItem = aCompanyItem->child(id);
			if (aStaffItem->childCount() == 0)
			{
				//没有部门
				TNStaffItem *staffItem = static_cast<TNStaffItem*>(aStaffItem);
				if (staffItem->getDialogID() == feedId && staffItem->getBelongFeedId() == belongId)
				{
					//此处应该设置选中状态
					parentIndex = QModelIndex();
					return departmentIndex;
				}
			}
			else
			{
				for (size_t ie = 0; ie < aStaffItem->childCount(); ie++)
				{
					//三级目录-----未测试
					TNStaffItem *staffItem = static_cast<TNStaffItem*>(aStaffItem->child(ie));
					if (staffItem->getDialogID() == feedId  && staffItem->getBelongFeedId() == belongId)
					{
						parentIndex = departmentIndex;
						QModelIndex staffIndex = this->index(ie, 0, departmentIndex);
						return staffIndex;
					}
				}
			}
		}
	}
	return QModelIndex();
}
void TNCardCaseCOModel::setSecondNodeStatus(QModelIndex &index, bool status, NodeType type)
{
	if (index.column() > 0 || !index.isValid())
		return;

	TNCardCaseTreeItem * item = _rootItem->child(index.row());
	if (item != nullptr)
		item->setStatus(status);
}
void TNCardCaseCOModel::refreshItem(const QString &feedId)
{
	QMutexLocker locker(&_mutex);
	if (_colleagueListWidgtView == nullptr || _rootItem == nullptr)
		return;
	QModelIndex rootIndex = _colleagueListWidgtView->rootIndex();
	for (size_t ic = 0; ic < _rootItem->childCount(); ic++)
	{
		TNCardCaseTreeItem * aCompanyItem = _rootItem->child(ic);
		QModelIndex companyIndex = this->index(ic, 0, rootIndex);
		for (size_t id = 0; id < aCompanyItem->childCount(); id++)
		{
			QModelIndex departmentIndex = this->index(id, 0, companyIndex);
			TNCardCaseTreeItem * aStaffItem = aCompanyItem->child(id);
			if (aStaffItem->childCount() == 0)
			{
				TNStaffItem *staffItem = static_cast<TNStaffItem*>(aStaffItem);
				if (staffItem != NULL && staffItem->getDialogID() == feedId)
				{
					staffItem->setAvatarURL(staffItem->getLatestAvatarURL());
					emit dataChanged(departmentIndex, departmentIndex);
				}
			}
			else
			{
				for (size_t ie = 0; ie < aStaffItem->childCount(); ie++)
				{
					QModelIndex staffIndex = this->index(ie, 0, departmentIndex);
					TNStaffItem *staffItem = static_cast<TNStaffItem*>(aStaffItem->child(ie));
					if (staffItem != NULL && staffItem->getDialogID() == feedId)
					{
						staffItem->setAvatarURL(staffItem->getLatestAvatarURL());
						emit dataChanged(staffIndex, staffIndex);
					}
				}
			}
		}
	}
}
QModelIndex TNCardCaseCOModel::getNextIndex(QModelIndex oldIndex)
{
	QModelIndex index;
	if (oldIndex.isValid() && _startFlag )
	{
		if (_latestSelectedParentParent.isValid())
		{
			if (_latestSelectedParent.isValid())
			{
				//完整的三级结构
				if (_colleagueListWidgtView->isExpanded(_latestSelectedParentParent) &&
					_colleagueListWidgtView->isExpanded(_latestSelectedParent))
				{
					index = this->index(oldIndex.row() + 1, 0, _latestSelectedParent);
				}
				TNCardCaseTreeItem * companyItem = _rootItem->child(_latestSelectedParentParent.row());
				Q_ASSERT(companyItem != nullptr);
				TNCardCaseTreeItem * typeItem = companyItem->child(_latestSelectedParent.row());
				Q_ASSERT(typeItem != nullptr);
				//验证index是否有效
				if (index.isValid())
				{
					TNCardCaseTreeItem * staffItem = typeItem->child(index.row());
					if (staffItem == nullptr ||
						staffItem->childCount() != 0)
					{
						index = QModelIndex();
					}
				}
				//当前部门最后一个人
				if (oldIndex.row() >= typeItem->childCount() - 1)
				{   
					index = findNextValidItem(companyItem);
				}
			}
			else
			{
				if (_colleagueListWidgtView->isExpanded(_latestSelectedParentParent))
				{
					index = this->index(oldIndex.row() + 1, 0, _latestSelectedParentParent);
				}
				//当前二级结构
				int roaming = false; //二级三级混合
				TNCardCaseTreeItem * companyItem = _rootItem->child(_latestSelectedParentParent.row());
				Q_ASSERT(companyItem != nullptr);
				//验证index是否有效
				if (index.isValid())
				{
					TNCardCaseTreeItem * staffItem = companyItem->child(index.row());
					if (staffItem != nullptr && staffItem->childCount() != 0)
					{
						roaming = true;
						//二级节点从上一个开始， 因为下一个是三级节点。遍历的时候会+1
						_latestSelectedParent = oldIndex;
					}
					else
						index = QModelIndex();
				}
				//当前部门最后一个人
				if (oldIndex.row() >= companyItem->childCount() - 1
					|| roaming)
				{
					index = findNextValidItem(companyItem);
				}
			}
		}
	}
	if (!index.isValid())
	{
		_startFlag = true;
		bool hit = false;
		QModelIndex rootIndex = _colleagueListWidgtView->rootIndex();
		for (size_t c = 0; c < _rootItem->childCount(); c++)
		{
			if (hit)
				break;
			QModelIndex companyIndex = this->index(c, 0, rootIndex);
			TNCardCaseTreeItem * companyItem = _rootItem->child(companyIndex.row());
			if (_colleagueListWidgtView->isExpanded(companyIndex))
			{
				for (int i = 0; i < companyItem->childCount(); i++)
				{
					if (hit)
						break;
					QModelIndex departmentIndex = this->index(i, 0, companyIndex);
					TNCardCaseTreeItem * staffItem = companyItem->child(i);
					if (staffItem == nullptr)
						continue;
					if (staffItem->childCount() == 0)
					{
						hit = true;
						index = departmentIndex;
						_latestSelectedParentParent = companyIndex;
						_latestSelectedParent = QModelIndex();
						break;
					}
					else
					{
						for (size_t j = 0; j < staffItem->childCount(); j++)
						{
							QModelIndex staffIndex = this->index(j, 0, departmentIndex);
							if (_colleagueListWidgtView->isExpanded(departmentIndex))
							{
								if (staffIndex.isValid())
								{
									hit = true;
									index = staffIndex;
									_latestSelectedParentParent = companyIndex;
									_latestSelectedParent = departmentIndex;
									break;
								}
							}
						}
					}
				}
			}
		}
	}
	return index;
}
QModelIndex TNCardCaseCOModel::getPreIndex(QModelIndex oldIndex)
{
	QModelIndex index;
	if (oldIndex.isValid() && _startFlag)
	{
		if (_latestSelectedParentParent.isValid())
		{
			if (_latestSelectedParent.isValid())
			{
				if (_latestSelectedParent.isValid())
				{
					//完整的三级结构
					if (_colleagueListWidgtView->isExpanded(_latestSelectedParentParent) &&
						_colleagueListWidgtView->isExpanded(_latestSelectedParent))
					{
						index = this->index(oldIndex.row() - 1, 0, _latestSelectedParent);
					}
					TNCardCaseTreeItem * companyItem = _rootItem->child(_latestSelectedParentParent.row());
					Q_ASSERT(companyItem != nullptr);
					TNCardCaseTreeItem * typeItem = companyItem->child(_latestSelectedParent.row());
					Q_ASSERT(typeItem != nullptr);
					//验证index是否有效
					if (index.isValid())
					{
						TNCardCaseTreeItem * staffItem = typeItem->child(index.row());
						if (staffItem == nullptr ||
							staffItem->childCount() != 0)
						{
							index = QModelIndex();
						}
					}
					if (oldIndex.row() == 0)
					{
						index = findPreValidItem();
					}
				}
			}
			else
			{
				if (_colleagueListWidgtView->isExpanded(_latestSelectedParentParent))
				{
					index = this->index(oldIndex.row()-1, 0, _latestSelectedParentParent);
				}
				//当前二级结构
				TNCardCaseTreeItem * companyItem = _rootItem->child(_latestSelectedParentParent.row());
				Q_ASSERT(companyItem != nullptr);
				//验证index是否有效
				if (index.isValid())
				{
					TNCardCaseTreeItem * staffItem = companyItem->child(index.row());
					if (staffItem == nullptr ||
						staffItem->childCount() != 0)
					{
						index = QModelIndex();
					}
				}
				//已经到了当前节点的第一个item
				if (oldIndex.row() == 0)
				{
					index = findPreValidItem();
				}
			}
		}
	}
	if (!index.isValid())
	{
		_startFlag = true;
		bool hit = false;
		QModelIndex rootIndex = _colleagueListWidgtView->rootIndex();
		for (size_t c = 0; c < _rootItem->childCount(); c++)
		{
			if (hit)
				break;
			QModelIndex companyIndex = this->index(c, 0, rootIndex);
			TNCardCaseTreeItem * companyItem = _rootItem->child(companyIndex.row());
			Q_ASSERT(companyItem!= nullptr);
			if (_colleagueListWidgtView->isExpanded(companyIndex))
			{
				for (int i = 0; i < companyItem->childCount(); i++)
				{
					if (hit)
						break;
					QModelIndex departmentIndex = this->index(i, 0, companyIndex);
					TNCardCaseTreeItem * staffItem = companyItem->child(i);
					if (staffItem == nullptr)
						continue;
					if (staffItem->childCount() == 0)
					{
						hit = true;
						index = departmentIndex;
						_latestSelectedParentParent = companyIndex;
						_latestSelectedParent = QModelIndex();
						break;
					}
					else
					{
						for (size_t j = 0; j < staffItem->childCount(); j++)
						{
							QModelIndex staffIndex = this->index(j, 0, departmentIndex);
							if (_colleagueListWidgtView->isExpanded(departmentIndex))
							{
								if (staffIndex.isValid())
								{
									hit = true;
									index = staffIndex;
									_latestSelectedParentParent = companyIndex;
									_latestSelectedParent = departmentIndex;
									break;
								}
							}
						}
					}
				}
			}
		}
	}
	return index;
}
void TNCardCaseCOModel::updateKeyStartFlag(bool flag)
{
	_startFlag = flag;
}
QModelIndex TNCardCaseCOModel::findNextValidItem(TNCardCaseTreeItem * companyItem)
{
	Q_ASSERT(companyItem);
	//找到下一个有效的item
	bool hit = false;
	QModelIndex resIndex = QModelIndex();
	QModelIndex rootIndex = _colleagueListWidgtView->rootIndex();
	if (_latestSelectedParent.row() == companyItem->childCount() - 1)
	{
		//最后一个部门
		for (int i = _latestSelectedParentParent.row() + 1; i < _rootItem->childCount(); i++)
		{
			if (hit)
				break;
			TNCardCaseTreeItem * tempCompany = _rootItem->child(i);
			if (tempCompany == nullptr)
				continue;
			QModelIndex companyIndex = this->index(i, 0, rootIndex);
			if (_colleagueListWidgtView->isExpanded(companyIndex))
			{
				for (int c = 0; c < tempCompany->childCount(); c++)
				{
					if (hit)
						break;
					QModelIndex departIndex = this->index(c, 0, companyIndex);
					TNCardCaseTreeItem * staffItem = tempCompany->child(c);
					if (staffItem == nullptr) //只有公司名称，没有其他数据
						continue;
					if (staffItem->childCount() == 0)
					{
						hit = true;
						resIndex = this->index(0, 0, companyIndex);
						_latestSelectedParentParent = companyIndex;
						_latestSelectedParent = QModelIndex(); //父节点是空的
						break;
					}
					else
					{
						for (int j = 0; j < staffItem->childCount(); j++)
						{
							if (_colleagueListWidgtView->isExpanded(departIndex))
							{
								hit = true;
								resIndex = this->index(0, 0, departIndex);
								_latestSelectedParentParent = companyIndex;
								_latestSelectedParent = departIndex;
								break;
							}
						}
					}
				}
			}
		}
	}
	else
	{
		for (int i = _latestSelectedParentParent.row(); i < _rootItem->childCount(); i++)
		{
			if (hit)
				break;
			TNCardCaseTreeItem * tempCompany = _rootItem->child(i);
			if (tempCompany == nullptr)
				continue;
			QModelIndex companyIndex = this->index(i, 0, rootIndex);
			if (_colleagueListWidgtView->isExpanded(companyIndex))
			{
				int start = 0;
				if (i == _latestSelectedParentParent.row())
					start = _latestSelectedParent.row() + 1;
				for (int d = start; d < tempCompany->childCount(); d++)
				{
					if (hit)
						break;
					QModelIndex departIndex = this->index(d, 0, companyIndex);
					TNCardCaseTreeItem * staffItem = tempCompany->child(d);
					if (staffItem == nullptr)
						continue;
					if (staffItem->childCount() == 0)
					{
						hit = true;
						resIndex = this->index(0, 0, companyIndex);
						_latestSelectedParentParent = companyIndex;
						_latestSelectedParent = QModelIndex(); //父节点是空的
						break;
					}
					else
					{
						if (_colleagueListWidgtView->isExpanded(departIndex))
						{
							hit = true;
							resIndex = this->index(0, 0, departIndex);
							_latestSelectedParentParent = companyIndex;
							_latestSelectedParent = departIndex;
							break;
						}
					}
				}
			}
		}
	}
	return resIndex;
}
QModelIndex TNCardCaseCOModel::findPreValidItem()
{
	//找到下一个有效的item
	bool hit = false;
	QModelIndex resIndex = QModelIndex();
	QModelIndex rootIndex = _colleagueListWidgtView->rootIndex();
	if (_latestSelectedParent.row() == 0)
	{
		//已经到第一个部门
		for (int i = _latestSelectedParentParent.row() - 1; i >= 0; i--)
		{
			if (hit)
				break;
			TNCardCaseTreeItem * tempCompany = _rootItem->child(i);
			if (tempCompany == nullptr)
				continue;
			QModelIndex companyIndex = this->index(i, 0, rootIndex);
			if (_colleagueListWidgtView->isExpanded(companyIndex))
			{
				for (int c = tempCompany->childCount() - 1; c > 0; c--)
				{
					if (hit)
						break;
					QModelIndex departIndex = this->index(c, 0, companyIndex);
					TNCardCaseTreeItem * staffItem = tempCompany->child(c);
					if (staffItem == nullptr) //只有公司名称，没有其他数据
						continue;
					if (staffItem->childCount() == 0)
					{
						hit = true;
						resIndex = this->index(0, 0, companyIndex);
						_latestSelectedParentParent = companyIndex;
						_latestSelectedParent = QModelIndex(); //父节点是空的
						break;
					}
					else
					{
						if (_colleagueListWidgtView->isExpanded(departIndex))
						{
							hit = true;
							resIndex = this->index(staffItem->childCount() - 1, 0, departIndex);
							_latestSelectedParentParent = companyIndex;
							_latestSelectedParent = departIndex;
							break;
						}
					}
				}
			}
		}
	}
	else
	{
		for (int i = _latestSelectedParentParent.row(); i >= 0; i--)
		{
			if (hit)
				break;
			TNCardCaseTreeItem * tempCompany = _rootItem->child(i);
			if (tempCompany == nullptr)
				continue;
			QModelIndex companyIndex = this->index(i, 0, rootIndex);
			if (_colleagueListWidgtView->isExpanded(companyIndex))
			{
				for (int d = _latestSelectedParent.row() - 1; d >= 0; d--)
				{
					if (hit)
						break;
					QModelIndex departIndex = this->index(d, 0, companyIndex);
					TNCardCaseTreeItem * staffItem = tempCompany->child(d);
					if (staffItem == nullptr)
						continue;
					if (staffItem->childCount() == 0)
					{
						hit = true;
						resIndex = this->index(d, 0, companyIndex);
						_latestSelectedParentParent = companyIndex;
						_latestSelectedParent = QModelIndex(); //父节点是空的
						break;
					}
					else
					{
						if (_colleagueListWidgtView->isExpanded(departIndex))
						{
							hit = true;
							resIndex = this->index(staffItem->childCount() - 1, 0, departIndex);
							_latestSelectedParentParent = companyIndex;
							_latestSelectedParent = departIndex;
							break;
						}
					}
				}
			}
		}
	}
	return resIndex;
}