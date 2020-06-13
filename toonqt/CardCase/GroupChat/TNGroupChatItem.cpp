#include "TNGroupChatItem.h"
#include <QStringList>

TNGroupChatItem::TNGroupChatItem(const QString &groupChatName, TNCardCaseTreeItem *parent) :
TNCardCaseTreeItem(QList<QVariant>() << groupChatName, parent)
{
	_memberNumber = 0;
	_isForcerefreshAvator = false;
}

TNGroupChatItem::~TNGroupChatItem()
{
}

TNCardCaseTreeItem::ColleagueTreeItem TNGroupChatItem::getItemGrade() const
{
	return TNCardCaseTreeItem::GroupChat;
}

QString TNGroupChatItem::getTitle() const
{
	return data(0).toString();
}

void TNGroupChatItem::setSubTitle(const QString &val)
{
	_subTitle = val;
}

QString TNGroupChatItem::getSubTitle() const
{
	return _subTitle;
}

void TNGroupChatItem::setPhotoResourceID(const QString &photoId)
{
	_photoResourceID = photoId;
}

QString TNGroupChatItem::getPhotoResourceID() const
{
	return _photoResourceID;
}

void TNGroupChatItem::setMemberNumber(int val)
{
	_memberNumber = val;
}

int TNGroupChatItem::getMemberNumber() const
{
	return _memberNumber;
}

void TNGroupChatItem::setAvatarURL(const QString &avatarURL)
{
	_avatarURL = avatarURL;
}

QString TNGroupChatItem::getAvatarURL() const
{
	return _avatarURL;
}

void TNGroupChatItem::setDialogID(const QString &dialogID)
{
	_dialogID = dialogID;
}

QString TNGroupChatItem::getDialogID() const
{
	return _dialogID;
}

void TNGroupChatItem::setTopic(const QString &topic)
{
	_topic = topic;
}

QString TNGroupChatItem::getTopic() const
{
	return _topic;
}

void TNGroupChatItem::setMyFeedID(const QString &myFeedID)
{
	_myFeedID = myFeedID;
}

QString TNGroupChatItem::getMyFeedID() const
{
	return _myFeedID;
}

void TNGroupChatItem::setBelongFeedId(const QString &belongFeedId)
{
	_belongFeedId = belongFeedId;
}

QString TNGroupChatItem::getBelongFeedId() const
{
	return _belongFeedId;
}

void TNGroupChatItem::setUserId(const QString &userId)
{
	_userId = userId;
}

QString	TNGroupChatItem::getUserId() const
{
	return _userId;
}
