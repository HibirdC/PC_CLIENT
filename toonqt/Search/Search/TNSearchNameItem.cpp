#include "TNSearchNameItem.h"
#include <QDebug>
TNSearchNameItem::TNSearchNameItem(const QString &departmentName, TNSearchTreeItemV2 *parent) :
	TNSearchTreeItemV2(QList<QVariant>() << departmentName, 0, parent),
	_isShowBelong(false),
	_isForcerefreshAvator(false),
	_type(-1),
	_hitType(-1)
{

}

TNSearchNameItem::~TNSearchNameItem()
{
	qDebug() << "[~TNSearchNameItem]";
}

TNSearchNameItem::SearchTreeItemEnum TNSearchNameItem::getItemGrade() const
{
	return TNSearchTreeItemV2::Name;
}
void TNSearchNameItem::setPhotoResourceID(const QString &photoId)
{
	_photoResourceID = photoId;
}

QString TNSearchNameItem::getPhotoResourceID() const
{
	return _photoResourceID;
}

void TNSearchNameItem::setAvatarURL(const QString &avatarURL)
{
	_avatarURL = avatarURL;
}

QString TNSearchNameItem::getAvatarURL() const
{
	return _avatarURL;
}

void TNSearchNameItem::setFeedID(const QString &dialogID)
{
	_feedId = dialogID;
}

QString TNSearchNameItem::getFeedID() const
{
	return _feedId;
}

QString TNSearchNameItem::getTitle() const
{
	return _title;
}
void TNSearchNameItem::setBelongFeedId(const QString &belongFeedId)
{
	_belongFeedId = belongFeedId;
}

QString TNSearchNameItem::getBelongFeedId() const
{
	return 	_belongFeedId;
}
void TNSearchNameItem::setUserId(QString userId) 
{ 
	_userId = userId;
}
QString TNSearchNameItem::getUserId() const
{ 
	return _userId; 
}
void TNSearchNameItem::setTitle(QString title) 
{ 
	_title = title; 
}
void TNSearchNameItem::SetType(int type)
{
	_type = type;
}
void TNSearchNameItem::setBelongPhotoResID(const QString &belongResID)
{
	_belongPhotoResID = belongResID;
}
QString TNSearchNameItem::getBelongPhotoResID()
{ 
	return _belongPhotoResID; 
}

void TNSearchNameItem::setShowButtonName(const QString &Name)
{
	_showAllName = Name;
}
QString TNSearchNameItem::getShowButtonName() const
{
	return _showAllName;
}
void TNSearchNameItem::setIsForeceRefreshAvator(bool isRefresh)
{
	_isForcerefreshAvator = isRefresh;
}
bool TNSearchNameItem::getIsForeceRefreshAvator() const
{ 
	return _isForcerefreshAvator; 
}

void TNSearchNameItem::setShowBelongStatus(bool show)
{
	_isShowBelong = show;
}
bool TNSearchNameItem::getShowBelongStatus()
{
	return _isShowBelong;
}

int TNSearchNameItem::getType()
{
	return _type;
}
QString TNSearchNameItem::getTypeString()
{
	QString type;
	switch (_type)
	{
	case 1:
		type = "AFriend";
		break;
	case 2:
		type = "BColleague";
		break;
	case 3:
		type = "CGroup";
		break;
	case 4:
		type = "DGroupChat";
		break;
	case 5:
		type = "ENotifyMsg";
		break;
	default:
		break;
	}
	return type;
}
QString TNSearchNameItem::getNickName() const
{
	return _nickName;
}
void TNSearchNameItem::setNickName(QString nickName)
{
	_nickName = nickName;
}
QString TNSearchNameItem::getSearchHitKey() const
{
	return _hitKey;
}
void TNSearchNameItem::setSearchHitKey(QString key)
{
	_hitKey = key;
}
int TNSearchNameItem::getSearchHitType() const
{
	return _hitType;
}
void TNSearchNameItem::setSearchHitType(int hitType)
{
	_hitType = hitType;
}