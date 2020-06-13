#ifndef TNCARDCASEGROUPMODEL_H
#define TNCARDCASEGROUPMODEL_H

#include "TNListModel.h"
#include "TNCardCaseGroupAdapter.h"

class TNCardCaseGroupModel : public TNListModel
{
	Q_OBJECT

public:
	explicit TNCardCaseGroupModel(QObject *parent = 0);
	~TNCardCaseGroupModel();

	Qt::ItemFlags flags(const QModelIndex &index) const;
	void appendData(TNCardCaseGroupAdapter * adapter);
	void appendData(QList<TNCardCaseGroupAdapter *> adapterList);
	int  setSearchSelected(const QString &feedId, const QString &belongId);
	void insertItem(TNCardCaseGroupAdapter * adapter);
	void removeItem(const QString &feedId, const QString &belongId);
	void updateGroupItemInfo(const QString &feedId, const QString &name,
		const QString &file, const QString &subject, TNStructGroup oldGroup, TNStructGroup newGroup);
	void resetModel();
	void refreshItem(const QString &feedId);
	int getValidPosition(TNCardCaseGroupAdapter * adapter);
	void UpdateGroupMemberCount(const QString &feedId, int count);
	void UpdateItemBaseInfo(st_FeedPtr feed);
	QModelIndex getNextIndex(QModelIndex oldIndex);
	QModelIndex getPreIndex(QModelIndex oldIndex);
	void updateKeyStartFlag(bool flag);

private:
	QMutex _mutex;
	bool _startFlag;
};

#endif // TNCARDCASEGROUPMODEL_H
