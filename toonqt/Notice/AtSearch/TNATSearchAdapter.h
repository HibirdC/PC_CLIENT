#ifndef TNATSearchAdapter_H
#define TNATSearchAdapter_H

#include <QTableView>
#include <QList>
#include <QString>
#include <QPixmap>
#include <QMutex>
#include "TNTableModel.h"

#include "common_global.h"

class TNATSearchAdapter : public TNModelItemBase
{
public:
	enum ItemType{FriendLetter=0, FriendItem};

private:
    QString _dialogID;
	QString _belongFeedId;
	QString _userId;
	QString _pinYin;
	QStringList _tag;
	QString _sex;
	int _age;
    QString _name;
    QString _photoResID;
	QString _AvatarURL;
	QString _subTitle;
    qint32 _onTop;
	bool _isForcerefreshAvator;
	QString _nickName;
public:
    TNATSearchAdapter();

    ~TNATSearchAdapter();

	void setTitlePinYin(const QString &pinyin)
	{
		_pinYin = pinyin;
	}
	QString getTitlePinYin() const
	{
		return _pinYin;
	}

	void setTag(const QStringList &tag)
	{
		_tag = tag;
	}
	QStringList getTag() const
	{
		return _tag;
	}

	void setAvatarUrl(const QString &avatarUrl)
	{
		_AvatarURL = avatarUrl;
	}
	QString getAvatarUrl() const
	{
		return _AvatarURL;
	}

	void setSex(const QString &sex)
	{
		_sex = sex;
	}
	QString getSex() const
	{
		return _sex;
	}

	void setAge(int age)
	{
		_age = age;
	}
	int getAge() const
	{
		return _age;
	}

    void setName(const QString &name)
    {
        _name = name;
    }

    QString getName();
    QString getDialogID();

    void setDialogID(const QString &dialogID)
    {
        _dialogID = dialogID;
    }

	QString getSubTitle();

	void setSubTitle(const QString &subTitle)
    {
		_subTitle = subTitle;
    }

	void setPhotoResID(const QString &resID)
    {
		_photoResID = resID;
    }

    QString getPhotoResID();

	QString getBelongFeedId() const { return _belongFeedId; }
    void setBelongFeedId(const QString& feedId) { _belongFeedId = feedId; }

	QString getUserId() { return _userId; }
	void setUserId(QString userId) { _userId = userId; }

	void setIsForeceRefreshAvator(bool isRefresh)
	{
		_isForcerefreshAvator = isRefresh;
	}
	bool getIsForeceRefreshAvator() const{ return _isForcerefreshAvator; }

	void setNickName(QString nick){
		_nickName = nick;
	};
	QString getNickName(){ return _nickName; }
};

typedef std::shared_ptr<TNATSearchAdapter> TNATSearchAdapterPtr;

class TNATSearchListModel : public TNTableModel
{
    Q_OBJECT
public:
    explicit TNATSearchListModel(QObject *parent = 0);
    void appendData(TNATSearchAdapter *adapter);
	void appendData(QList<TNATSearchAdapter *> adapterList);
	void UpdateItemAvatar(QString file,QString feedId);
	void setTableView(QTableView* tableView);
	int  setSearchSelected(TNATSearchAdapter *adapter);
	void ResetModel();
private:
	QTableView*		  _tableView;
	QMutex _mutex;
};
#endif // TNATSearchAdapter_H
