#include "TNCardCaseGroupAdapter.h"

TNCardCaseGroupAdapter::TNCardCaseGroupAdapter()
{
	_memberNumber = 0;
	_isForcerefreshAvator = false;
	_isCreator = false;
	_isAdministrtor = false;
}

TNCardCaseGroupAdapter::~TNCardCaseGroupAdapter()
{

}
void TNCardCaseGroupAdapter::setGroupId(const QString &groupId)
{
	_groupID = groupId;
}
const QString &TNCardCaseGroupAdapter::getGroupId()
{
	return _groupID;
}

void TNCardCaseGroupAdapter::setBelongFeedId(const QString &belongId)
{
	_belongFeedId = belongId;
}
const QString &TNCardCaseGroupAdapter::getBelongFeedId()
{
	return _belongFeedId;
}

void TNCardCaseGroupAdapter::setPhotoResourceID(const QString &photoID)
{
	_photoResourceID = photoID;
}
const QString &TNCardCaseGroupAdapter::getPhotoResourceID()
{
	return _photoResourceID;
}

void TNCardCaseGroupAdapter::setTitle(const QString &title)
{
	_title = title;
}
const QString &TNCardCaseGroupAdapter::getTitle()
{
	return _title;
}

void TNCardCaseGroupAdapter::setSubTitle(const QString &subTitle)
{
	_subTitle = subTitle;
}
const QString &TNCardCaseGroupAdapter::getSubTitle()
{
	return _subTitle;
}

void TNCardCaseGroupAdapter::setMemberCount(int count)
{
	_memberNumber = count;
}
int TNCardCaseGroupAdapter::getMemberCount()
{
	return _memberNumber;
}

void TNCardCaseGroupAdapter::setAvatarURL(const QString &avatarURL)
{
	_avatarURL = avatarURL;
}
const QString &TNCardCaseGroupAdapter::getAvatarURL()
{
	return _avatarURL;
}

void TNCardCaseGroupAdapter::setLatestAvatarURL(const QString &latestAvatarURL)
{
	_latestAvatarURL = latestAvatarURL;
}
const QString &TNCardCaseGroupAdapter::getLatestAvatarURL()
{
	return _latestAvatarURL;
}

void TNCardCaseGroupAdapter::setGroupSubject(const QString &subject)
{
	_groupSubject = subject;
}
const QString &TNCardCaseGroupAdapter::getGroupSubject()
{
	return _groupSubject;
}

void TNCardCaseGroupAdapter::setGroupTag(QStringList tagList)
{
	_tag = tagList;
}
QStringList TNCardCaseGroupAdapter::getGroupTag()
{
	return _tag;
}

void TNCardCaseGroupAdapter::setIsForceRefreshAvatar(bool isForceRefresh)
{
	_isForcerefreshAvator = isForceRefresh;
}
bool TNCardCaseGroupAdapter::getIsForceRefreshAvatar()
{
	return _isForcerefreshAvator;
}

void TNCardCaseGroupAdapter::setIsCreator(bool isCreator)
{
	_isCreator = isCreator;
}
bool TNCardCaseGroupAdapter::getIsCreator()
{
	return _isCreator;
}

void TNCardCaseGroupAdapter::setIsAdmin(bool isAdmin)
{
	_isAdministrtor = isAdmin;
}
bool TNCardCaseGroupAdapter::getIsAdmin()
{
	return _isAdministrtor;
}
void TNCardCaseGroupAdapter::setTitlePy(const QString &titlePy)
{
	_titlePy = titlePy;
}
const QString &TNCardCaseGroupAdapter::getTitlePy()
{
	return _titlePy;
}