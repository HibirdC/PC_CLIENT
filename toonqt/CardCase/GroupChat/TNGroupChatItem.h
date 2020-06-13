#ifndef TNGROUPCHATITEM_H
#define TNGROUPCHATITEM_H

#include "TNCardCaseTreeItem.h"

#include <QList>
#include <QVariant>

class TNGroupChatItem : public TNCardCaseTreeItem
{
public:
	explicit TNGroupChatItem(const QString &staffName, TNCardCaseTreeItem *parentItem = 0);
	~TNGroupChatItem();

    virtual ColleagueTreeItem getItemGrade() const;

	QString getTitle() const;

	void setSubTitle(const QString &val);
	QString getSubTitle() const;

	void setDialogID(const QString &dialogID);
	QString getDialogID() const;

	void setTopic(const QString &topic);
	QString getTopic() const;

	void setMyFeedID(const QString &myFeedID);
	QString getMyFeedID() const;

	void setAvatarURL(const QString &avatarURL);
	QString getAvatarURL() const;

    void setPhotoResourceID(const QString &photoId);
    QString getPhotoResourceID() const;

	void setBelongFeedId(const QString &belongFeedId);
	QString getBelongFeedId() const;
	
	void setUserId(const QString &userId);
	QString	getUserId() const;

	void setMemberNumber(int val);
	int getMemberNumber() const;

	void setIsForeceRefreshAvator(bool isRefresh)
	{
		_isForcerefreshAvator = isRefresh;
	}
	bool getIsForeceRefreshAvator() const{ return _isForcerefreshAvator; }
private:
	QString _dialogID;

	QString _topic;
	QString _myFeedID;
	QString _belongFeedId;
	QString _userId;

    QString _photoResourceID;
	QString _subTitle;
	int _memberNumber;
	QString _avatarURL;
	bool _isForcerefreshAvator;
};

#endif // TNGROUPCHATITEM_H
