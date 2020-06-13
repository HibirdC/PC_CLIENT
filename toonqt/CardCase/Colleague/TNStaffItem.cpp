#include "TNStaffItem.h"
#include <QStringList>

TNStaffItem::TNStaffItem(const QString &staffName, TNCardCaseTreeItem *parent) :
    TNCardCaseTreeItem(QList<QVariant>()<<staffName, parent)
	, _dialogID("")
{
	_isForcerefreshAvator = false;
}

TNStaffItem::~TNStaffItem()
{
}

TNCardCaseTreeItem::ColleagueTreeItem TNStaffItem::getItemGrade() const
{
    return TNCardCaseTreeItem::Staff;
}

void TNStaffItem::setPhotoResourceID(const QString &photoId)
{
    _photoResourceID = photoId;
}

QString TNStaffItem::getPhotoResourceID() const
{
    return _photoResourceID;
}

void TNStaffItem::setAvatarURL(const QString &avatarURL)
{
	_avatarURL = avatarURL;
}

QString TNStaffItem::getAvatarURL() const
{
	return _avatarURL;
}

void TNStaffItem::setLatestAvatarURL(const QString &latestAvatarURL)
{
	_latestAvatarURL = latestAvatarURL;
}

QString TNStaffItem::getLatestAvatarURL() const
{
	return _latestAvatarURL;
}

void TNStaffItem::setDialogID(const QString &dialogID)
{
	_dialogID = dialogID;
}

QString TNStaffItem::getDialogID() const
{
	return _dialogID;
}

QString TNStaffItem::getTitle() const
{
	return this->data(0).toString();
}

QString TNStaffItem::getSubTitle() const
{
	return _subTitle == (QString::null)?_parentItem->data(0).toString():_subTitle;
}

void TNStaffItem::setUserId(const QString &userId)
{	
	_userId = userId;
}

QString TNStaffItem::getUserId() const
{
	return 	_userId;
}

void TNStaffItem::setBelongFeedId(const QString &belongFeedId)
{
	_belongFeedId = belongFeedId;
}

QString TNStaffItem::getBelongFeedId() const
{
	return 	_belongFeedId;
}

void TNStaffItem::setCompanyId(const QString &companyId)
{
	_companyId = companyId;
}

QString TNStaffItem::getCompanyId() const
{
	return _companyId;
}

QString TNStaffItem::getCompanyName() const
{
	return _companyName == (QString::null)?this->parentItem()->parentItem()->data(0).toString():_companyName;
}

void TNStaffItem::setCompanyLogoUrl(const QString &logoUrl)
{
	_companyLogoUrl = logoUrl;
}

QString TNStaffItem::getCompanyLogoUrl() const
{
	return _companyLogoUrl;
}

void TNStaffItem::setCompanyLogoText(const QString &logoText)
{
	_companyLogoText = logoText;
}

QString TNStaffItem::getCompanyLogoText() const
{
	return _companyLogoText;
}

QString TNStaffItem::getDepartmentName() const
{
	return this->parentItem()->data(0).toString();
}

void TNStaffItem::setCompanyExt(const QString &ExtText)
{
	_companyExt = ExtText;
}

QString TNStaffItem::getCompanyExt() const
{
	return _companyExt;
}
QString TNStaffItem::getTitlePy() const
{
	return 	_titlePy;
}