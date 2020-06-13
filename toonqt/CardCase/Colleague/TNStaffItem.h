#ifndef TNSTAFFITEM_H
#define TNSTAFFITEM_H

#include "TNCardCaseTreeItem.h"

#include <QList>
#include <QVariant>

class TNStaffItem : public TNCardCaseTreeItem
{
public:
    explicit TNStaffItem(const QString &staffName, TNCardCaseTreeItem *parentItem = 0);
    ~TNStaffItem();

    virtual ColleagueTreeItem getItemGrade() const;

	void setDialogID(const QString &dialogID);
	QString getDialogID() const;

    void setPhotoResourceID(const QString &photoId);
    QString getPhotoResourceID() const;

	void setAvatarURL(const QString &avatarURL);
	QString getAvatarURL() const;

	void setLatestAvatarURL(const QString &latestAvatarURL);
	QString getLatestAvatarURL() const;

	QString getTitle() const;
	QString getSubTitle() const;
	void setSubTitle(const QString &subTitle)
	{
		_subTitle = subTitle;
	}
	void setUserId(const QString &userId);
	QString getUserId() const;

	QString getTitlePy() const;
	void setTitlePy(const QString &titlePy)
	{
		_titlePy = titlePy;
	}
	void setBelongFeedId(const QString &belongFeedId);
	QString getBelongFeedId() const;

	void setCompanyId(const QString &companyId);
	QString getCompanyId() const;

	QString getCompanyName() const;
	void setCompanyName(const QString &companyName)
	{
		_companyName = companyName;
	}
	void setCompanyLogoUrl(const QString &logoUrl);
	QString getCompanyLogoUrl() const;

	void setCompanyLogoText(const QString &logoText);
	QString getCompanyLogoText() const;

	void setCompanyExt(const QString &ext);
	QString getCompanyExt() const;

	QString getDepartmentName() const;

	void setTag(const QStringList &tag)
	{
		_tag = tag;
	}
	QStringList getTag() const
	{
		return _tag;
	}
	void setIsForeceRefreshAvator(bool isRefresh)
	{
		_isForcerefreshAvator = isRefresh;
	}
	bool getIsForeceRefreshAvator() const{ return _isForcerefreshAvator; }
private:
	QString _dialogID;
    QString _photoResourceID;
	QString _avatarURL;
	QString _latestAvatarURL;
	QStringList _tag;
	QString _subTitle;
	QString _companyName;

	QString _userId;
	QString _belongFeedId;

	QString _companyId;
	QString _companyLogoUrl;
	QString _companyLogoText;
	QString _companyExt;
	QString _titlePy;
	bool _isForcerefreshAvator;
};

#endif // TNSTAFFITEM_H
