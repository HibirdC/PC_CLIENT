#ifndef TNSEARCHNAMEITEM_H
#define TNSEARCHNAMEITEM_H

#include <QObject>
#include <QList>
#include <QVariant>
#include "search_global.h"
#include "TNSearchTreeItemV2.h"

class SEARCH_EXPORT TNSearchNameItem : public TNSearchTreeItemV2
{

public:
	explicit TNSearchNameItem(const QString &TypeName,TNSearchTreeItemV2 *parentItem = 0);
	~TNSearchNameItem();

	enum ItemType{FriendItem= 1, ColleagueItem, GroupItem, GroupChatItem ,NotifyItem};

	virtual SearchTreeItemEnum getItemGrade() const;
	void setFeedID(const QString &feedId);
	QString getFeedID() const;

	void setPhotoResourceID(const QString &photoId);
	QString getPhotoResourceID() const;

	void setAvatarURL(const QString &avatarURL);
	QString getAvatarURL() const;

	void setBelongFeedId(const QString &belongFeedId);
	QString getBelongFeedId() const;
	void setIsForeceRefreshAvator(bool isRefresh);
	bool getIsForeceRefreshAvator() const;

	void setShowBelongStatus(bool show);
	bool getShowBelongStatus();

	int getType();
	QString getTypeString();
	void SetType(int type);
	void setBelongPhotoResID(const QString &belongResID);
	QString getBelongPhotoResID();

	void setShowButtonName(const QString &Name);
	QString getShowButtonName() const;

	void setUserId(QString userId);
	QString getUserId() const;

	QString getTitle() const;
	void setTitle(QString title);

	QString getNickName() const;
	void setNickName(QString nickName);

	QString getSearchHitKey() const;
	void setSearchHitKey(QString hitString);

	int getSearchHitType() const;
	void setSearchHitType(int hitType);
private:
	QString _feedId;
	QString _photoResourceID;
	QString _avatarURL;
	QString _showAllName;
	QString _belongPhotoResID;
	QString _belongFeedId;
	QString _userId;
	QString _title;
	QString _nickName;
	QString _hitKey;
	bool _isForcerefreshAvator;
	bool _isShowBelong;
	int _type;
	int  _hitType;
};

#endif // TNSEARCHNAMEITEM_H
