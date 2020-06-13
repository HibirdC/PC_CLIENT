#ifndef TNCARDCASEGROUPADAPTER_H
#define TNCARDCASEGROUPADAPTER_H

#include <QListView>
#include <QList>
#include <QString>
#include <QPixmap>
#include <QMutex>
#include "TNListModel.h"

#include "common_global.h"
#include "TNDbUtil.h"

class TNCardCaseGroupAdapter : public TNModelItemBaseV2
{
public:
	explicit TNCardCaseGroupAdapter();
	~TNCardCaseGroupAdapter();

	void setGroupId(const QString &groupId);
	const QString &getGroupId();

	void setBelongFeedId(const QString &belongId);
	const QString &getBelongFeedId();

	void setPhotoResourceID(const QString &photoID);
	const QString &getPhotoResourceID();

	void setTitle(const QString &title);
	const QString &getTitle();

	void setSubTitle(const QString &subTitle);
	const QString &getSubTitle();

	void setMemberCount(int count);
	int  getMemberCount();

	void setAvatarURL(const QString &avatarURL);
	const QString &getAvatarURL();

	void setLatestAvatarURL(const QString &latestAvatarURL);
	const QString &getLatestAvatarURL();

	void setGroupSubject(const QString &subject);
	const QString &getGroupSubject();

	void setGroupTag(QStringList tagList);
	QStringList getGroupTag();

	void setIsForceRefreshAvatar(bool isForceRefresh);
	bool getIsForceRefreshAvatar();

	void setIsCreator(bool isCreator);
	bool getIsCreator();

	void setIsAdmin(bool isAdmin);
	bool getIsAdmin();

	void setTitlePy(const QString &titlePy);
	const QString &getTitlePy();
private:
	QString _title;
	QString _titlePy;
	QString _groupID;
	QString _belongFeedId;
	QString _photoResourceID;
	QString _subTitle;
	int _memberNumber;
	QString _groupSubject;
	QString _avatarURL;
	QString _latestAvatarURL;
	QStringList _tag;
	bool _isForcerefreshAvator;
	bool _isCreator;
	bool _isAdministrtor;
};
typedef std::shared_ptr<TNCardCaseGroupAdapter> TNCardCaseGroupAdapterPtr;
#endif // TNCARDCASEGROUPADAPTER_H
