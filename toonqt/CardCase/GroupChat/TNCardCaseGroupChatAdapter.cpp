#include "TNCardCaseGroupChatAdapter.h"

TNCardCaseGroupChatAdapter::TNCardCaseGroupChatAdapter()
{
	_isCreator = false;
	_memberNumber = 0;
	_isForcerefreshAvator = false;
}

TNCardCaseGroupChatAdapter::~TNCardCaseGroupChatAdapter()
{

}
void TNCardCaseGroupChatAdapter::setGroupChatId(const QString &groupId)
{
	_groupChatID = groupId;
}
const QString &TNCardCaseGroupChatAdapter::getGroupChatId()
{
	return _groupChatID;
}

void TNCardCaseGroupChatAdapter::setBelongFeedId(const QString &belongId)
{
	_belongFeedId = belongId;
}
const QString &TNCardCaseGroupChatAdapter::getBelongFeedId()
{
	return _belongFeedId;
}

void TNCardCaseGroupChatAdapter::setPhotoResourceID(const QString &photoID)
{
	_photoResourceID = photoID;
}
const QString &TNCardCaseGroupChatAdapter::getPhotoResourceID()
{
	return _photoResourceID;
}

void TNCardCaseGroupChatAdapter::setTitle(const QString &title)
{
	_title = title;
}
const QString &TNCardCaseGroupChatAdapter::getTitle()
{
	return _title;
}

void TNCardCaseGroupChatAdapter::setMemberCount(int count)
{
	_memberNumber = count;
}
int TNCardCaseGroupChatAdapter::getMemberCount()
{
	return _memberNumber;
}

void TNCardCaseGroupChatAdapter::setAvatarURL(const QString &avatarURL)
{
	_avatarURL = avatarURL;
}
const QString &TNCardCaseGroupChatAdapter::getAvatarURL()
{
	return _avatarURL;
}

void TNCardCaseGroupChatAdapter::setLatestAvatarURL(const QString &latestAvatarURL)
{
	_latestAvatarURL = latestAvatarURL;
}
const QString &TNCardCaseGroupChatAdapter::getLatestAvatarURL()
{
	return _latestAvatarURL;
}
void TNCardCaseGroupChatAdapter::setIsForceRefreshAvatar(bool isForceRefresh)
{
	_isForcerefreshAvator = isForceRefresh;
}
bool TNCardCaseGroupChatAdapter::getIsForceRefreshAvatar()
{
	return _isForcerefreshAvator;
}

void TNCardCaseGroupChatAdapter::setIsCreator(bool isCreator)
{
	_isCreator = isCreator;
}
bool TNCardCaseGroupChatAdapter::getIsCreator()
{
	return _isCreator;
}
void TNCardCaseGroupChatAdapter::setTopic(const QString &topic)
{
	_groupChatTopic = topic;
}
const QString &TNCardCaseGroupChatAdapter::getTopic()
{
	return _groupChatTopic;
}