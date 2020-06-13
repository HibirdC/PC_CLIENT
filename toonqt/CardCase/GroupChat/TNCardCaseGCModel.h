#ifndef TNCARDCASEGCMODEL_H
#define TNCARDCASEGCMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QMutex>
#include "TNDbUtil.h"
#include "cardcase_global.h"
#include "TNGCTreeView.h"

class TNCardCaseTreeItem;

class TNCardCaseGCModel : public QAbstractItemModel
{
	Q_OBJECT

public:
	explicit TNCardCaseGCModel(TNCardCaseTreeItem *rootItem, QObject *parent = 0);
	virtual ~TNCardCaseGCModel();

	QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
	Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
	QVariant headerData(int section, Qt::Orientation orientation,
		int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
	QModelIndex index(int row, int column,
		const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
	QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
	int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
	int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
	void RemoveItem(QString feedId, int type);
	void InsertItem(bool isCreate, TNCardCaseTreeItem * item, int type);
	void setItemStatus(const QModelIndex & index,bool status);
	QModelIndex  setGroupChatSearchSelected(QString groupId);
	void SetGroupChatListView(TNGCTreeView *view);
	void SetSecondNodeStatus(QModelIndex &index, bool status, NodeType type);
	TNCardCaseTreeItem *  GetSubItemParent(bool isCreate);
	QModelIndex UpdateItem(QString feedId, bool isCreate, TNCardCaseTreeItem * item, int type);
	QModelIndex UpdateItem(st_GroupInfoPtr group);
	void refreshItem(const QString &feedId);
private:
	TNGCTreeView * _GroupChatListWidgtView;
	TNCardCaseTreeItem   * _rootItem;
	QMutex _mutex;
};

#endif // TNCARDCASEGCMODEL_H
