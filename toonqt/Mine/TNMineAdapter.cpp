#include "TNMineAdapter.h"

TNMineAdapter::TNMineAdapter()
{
	_isForcerefreshAvator = false;
}

TNMineAdapter::~TNMineAdapter()
{

}
void TNMineAdapter::setFeedId(const QString &feedId)
{
	_feedId = feedId;
}
const QString &TNMineAdapter::getFeedId()
{
	return _feedId;
}

void TNMineAdapter::setPhotoResourceID(const QString &photoID)
{
	_photoResourceID = photoID;
}
const QString &TNMineAdapter::getPhotoResourceID()
{
	return _photoResourceID;
}

void TNMineAdapter::setTitle(const QString &title)
{
	_title = title;
}
const QString &TNMineAdapter::getTitle()
{
	return _title;
}

void TNMineAdapter::setSubTitle(const QString &subTitle)
{
	_subTitle = subTitle;
}
const QString &TNMineAdapter::getSubTitle()
{
	return _subTitle;
}

void TNMineAdapter::setAvatarURL(const QString &avatarURL)
{
	_avatarURL = avatarURL;
}
const QString &TNMineAdapter::getAvatarURL()
{
	return _avatarURL;
}

void TNMineAdapter::setLatestAvatarURL(const QString &latestAvatarURL)
{
	_latestAvatarURL = latestAvatarURL;
}
const QString &TNMineAdapter::getLatestAvatarURL()
{
	return _latestAvatarURL;
}

void TNMineAdapter::setIsForceRefreshAvatar(bool isForceRefresh)
{
	_isForcerefreshAvator = isForceRefresh;
}
bool TNMineAdapter::getIsForceRefreshAvatar()
{
	return _isForcerefreshAvator;
}
void TNMineAdapter::setTitlePy(const QString &titlePy)
{
	_titlePy = titlePy;
}
const QString &TNMineAdapter::getTitlePy()
{
	return _titlePy;
}
