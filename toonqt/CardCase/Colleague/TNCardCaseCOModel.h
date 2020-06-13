#ifndef TNCARDCASECOMODEL_H
#define TNCARDCASECOMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QMutex>
#include "TNDbUtil.h"
#include "cardcase_global.h"
#include "TNCoTreeView.h"

class TNCardCaseTreeItem;

class TNCardCaseCOModel : public QAbstractItemModel
{
	Q_OBJECT

public:
	explicit TNCardCaseCOModel(TNCardCaseTreeItem *rootItem, QObject *parent = 0);
	~TNCardCaseCOModel();

	QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
	Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
	QVariant headerData(int section, Qt::Orientation orientation,
		int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
	QModelIndex index(int row, int column,
		const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
	QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
	int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
	int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
	void removeItem(QString feedId, int type);
	void insertItem(bool isCreate, TNCardCaseTreeItem * item, int type);
	void setItemStatus(const QModelIndex & index, bool status);
	QModelIndex  setColleagueSearchSelected(const QString &feedId, const QString &belongId, QModelIndex &parentIndex);
	void setColleagueListView(TNCoTreeView *view);
	void setSecondNodeStatus(QModelIndex &index, bool status, NodeType type);
	void updateColleagueItemInfo(const QString &feedId, const QString &file,
		const QString &name, const QString &namePy, const QString &userId, const QString &sunName, const QString &avatarURL);
	void refreshItem(const QString &feedId);

	QModelIndex getNextIndex(QModelIndex oldIndex);
	QModelIndex getPreIndex(QModelIndex oldIndex);
	void updateKeyStartFlag(bool flag);

private:
	TNCoTreeView * _colleagueListWidgtView;
	TNCardCaseTreeItem   * _rootItem;
	QModelIndex            _latestSelectedParent;
	QModelIndex            _latestSelectedParentParent;
	QMutex _mutex;
	bool                   	_startFlag;
private:
	QModelIndex findNextValidItem(TNCardCaseTreeItem * companyItem);
	QModelIndex findPreValidItem();
};

#endif // TNCARDCASECOMODEL_H
