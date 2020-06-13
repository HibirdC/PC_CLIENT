#ifndef TNMINEMODEL_H
#define TNMINEMODEL_H

#include "TNListModel.h"
#include "TNMineAdapter.h"
#include "localstorage_global.h"

class TNMineModel : public TNListModel
{
	Q_OBJECT

public:
	TNMineModel(QObject *parent);
	~TNMineModel();

	Qt::ItemFlags flags(const QModelIndex &index) const;
	void appendData(TNMineAdapter * adapter);
	void appendData(QList<TNMineAdapter *> adapterList);
	void insertItem(TNMineAdapter * adapter);
	void removeItem(const QString &feedId);
	void resetModel();
	void refreshItem(const QString &feedId);
	int  getValidPosition(TNMineAdapter * adapter);
	void UpdateItemBaseInfo(st_FeedPtr feed);
	QModelIndex getNextIndex(QModelIndex oldIndex);
	QModelIndex getPreIndex(QModelIndex oldIndex);

private:
	QMutex _mutex;
};

#endif // TNMINEMODEL_H
