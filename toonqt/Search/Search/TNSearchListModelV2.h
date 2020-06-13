#ifndef TNSEARCHLISTMODELV2_H
#define TNSEARCHLISTMODELV2_H

#include <QObject>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QMutex>
#include "TNMVD_global.h"
#include "TNDbUtil.h"
#include "TNSearchTreeItemV2.h"
#include "TNSearchViewV2.h"
#include "common_global.h"


class SEARCH_EXPORT TNSearchListModelV2 : public QAbstractItemModel
{
	Q_OBJECT

public:
	explicit TNSearchListModelV2(TNSearchTreeItemV2 *rootItem, QObject *parent = 0);
	virtual ~TNSearchListModelV2();

	QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
	Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
	QVariant headerData(int section, Qt::Orientation orientation,
		int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
	QModelIndex index(int row, int column,
		const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
	QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
	int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
	int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
	void setSearchListView(TNSearchViewV2 *view);
	void updateSearchAvatar(QString feedId, QString file);

	void removeItem(const QModelIndex index,int totalItemCount, int type);
	void insertItem(const QModelIndex index, QList<TNSearchTreeItemV2 *> itemList, int type);
	void resetModel(TNSearchTreeItemV2 *rootItem);
	QModelIndex getNextIndex(QModelIndex oldIndex);
	QModelIndex getPreIndex(QModelIndex oldIndex);

private:
	TNSearchTreeItemV2   * _rootItem;
	TNSearchViewV2  *     _SearchListWidgtView;
	QModelIndex           _latestSelectedParent;
	QMutex _mutex;
	
};

#endif // TNSEARCHLISTMODELV2_H
