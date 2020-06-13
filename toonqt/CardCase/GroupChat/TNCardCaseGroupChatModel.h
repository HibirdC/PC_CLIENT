#ifndef TNCARDCASEGROUPCHATMODEL_H
#define TNCARDCASEGROUPCHATMODEL_H

#include "TNListModel.h"
#include "TNCardCaseGroupChatAdapter.h"

class TNCardCaseGroupChatModel : public TNListModel
{
	Q_OBJECT

public:
	explicit TNCardCaseGroupChatModel(QObject *parent = 0);
	~TNCardCaseGroupChatModel();

	Qt::ItemFlags flags(const QModelIndex &index) const;
	void appendData(TNCardCaseGroupChatAdapter * adapter);
	void appendData(QList<TNCardCaseGroupChatAdapter *> adapterList);
	int  setSearchSelected(const QString &feedId, const QString &belongId);
	void insertItem(TNCardCaseGroupChatAdapter * adapter);
	void removeItem(const QString &feedId, const QString &belongId);
	QModelIndex updateGroupChatItemInfo(const QString &feedId, const QString &name, const QString &file,int memberCount,const QString& avatarURL);
	void resetModel();
	void refreshItem(const QString &feedId);
	int getValidPosition(TNCardCaseGroupChatAdapter * adapter);
	QModelIndex getNextIndex(QModelIndex oldIndex);
	QModelIndex getPreIndex(QModelIndex oldIndex);
	void updateKeyStartFlag(bool flag);
	bool isUpdateHeadImage(const QString &feedId, const QString &avatarURL);
	bool isUpdateGroupInfo(const QString &feedId, const QString &name, const QString &headImage, int memberCount);
private:
	QMutex _mutex;
	bool _startFlag;
};

#endif // TNCARDCASEGROUPCHATMODEL_H
