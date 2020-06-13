#ifndef TNMINEADAPTER_H
#define TNMINEADAPTER_H

#include <QListView>
#include <QList>
#include <QString>
#include <QPixmap>
#include <QMutex>
#include "TNListModel.h"

#include "common_global.h"
#include "TNDbUtil.h"

class TNMineAdapter : public TNModelItemBaseV2
{

public:
	explicit TNMineAdapter();
	~TNMineAdapter();

	void setFeedId(const QString &groupId);
	const QString &getFeedId();

	void setPhotoResourceID(const QString &photoID);
	const QString &getPhotoResourceID();

	void setTitle(const QString &title);
	const QString &getTitle();

	void setTitlePy(const QString &titlePy);
	const QString &getTitlePy();

	void setSubTitle(const QString &subTitle);
	const QString &getSubTitle();

	void setAvatarURL(const QString &avatarURL);
	const QString &getAvatarURL();

	void setLatestAvatarURL(const QString &latestAvatarURL);
	const QString &getLatestAvatarURL();

	void setIsForceRefreshAvatar(bool isForceRefresh);
	bool getIsForceRefreshAvatar();
private:
	QString _title;
	QString _titlePy;
	QString _feedId;
	QString _photoResourceID;
	QString _subTitle;
	QString _avatarURL;
	QString _latestAvatarURL;
	bool _isForcerefreshAvator;
};

#endif // TNMINEADAPTER_H
