#ifndef TNCARDCASEGROUPCHATADAPTER_H
#define TNCARDCASEGROUPCHATADAPTER_H

#include <QListView>
#include <QList>
#include <QString>
#include <QPixmap>
#include <QMutex>
#include "TNListModel.h"

#include "common_global.h"
#include "TNDbUtil.h"

class TNCardCaseGroupChatAdapter : public TNModelItemBaseV2
{
public:
	explicit TNCardCaseGroupChatAdapter();
	~TNCardCaseGroupChatAdapter();

	void setGroupChatId(const QString &groupChatId);
	const QString &getGroupChatId();

	void setBelongFeedId(const QString &belongId);
	const QString &getBelongFeedId();

	void setPhotoResourceID(const QString &photoID);
	const QString &getPhotoResourceID();

	void setTitle(const QString &title);
	const QString &getTitle();

	void setMemberCount(int count);
	int  getMemberCount();

	void setAvatarURL(const QString &avatarURL);
	const QString &getAvatarURL();

	void setLatestAvatarURL(const QString &latestAvatarURL);
	const QString &getLatestAvatarURL();

	void setIsForceRefreshAvatar(bool isForceRefresh);
	bool getIsForceRefreshAvatar();

	void setIsCreator(bool isCreator);
	bool getIsCreator();

	void setTopic(const QString &topic);
	const QString &getTopic();

private:
	QString _title;
	QString _groupChatID;
	QString _belongFeedId;
	QString _photoResourceID;
	int _memberNumber;
	QString _avatarURL;
	QString _latestAvatarURL;
	QString _groupChatTopic;
	bool _isForcerefreshAvator;
	bool _isCreator;
};

#endif // TNCARDCASEGROUPCHATADAPTER_H
