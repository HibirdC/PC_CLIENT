#ifndef TNSearchAdapter_H
#define TNSearchAdapter_H

#include <QTableView>
#include <QList>
#include <QString>
#include <QPixmap>
#include <QMutex>

#include "TNMVD_global.h"
#include "TNTableModel.h"

#include "common_global.h"
#include "search_global.h"

class SEARCH_EXPORT TNSearchAdapter : public TNModelItemBase
{
private:
    int _type;
	int _itemCountIflabel;
    QString _dialogID;
	QString _belongPhotoResID;
	QString _belongFeedId;
	QString _userId;
	QString _pinYin;
	QString _sex;
	int _age;
    QString _name;
    QString _photoResID;
	QString _AvatarURL;
	QString _showAllName;
	bool _isForcerefreshAvator;
	bool _isShowBelong;

public:
	enum ItemType{ FriendLetter = 0, FriendItem, ColleagueItem, GroupItem, GroupChatItem, NotifyItem};

public:
	explicit TNSearchAdapter(int type);

    ~TNSearchAdapter();

	void setShowBelongStatus(bool show)
	{
		_isShowBelong = show;
	}
	bool getShowBelongStatus()
	{
		return _isShowBelong;
	}

    int getType()
    {
        return _type;
    }
	QString getTypeString()
	{
		QString type;
		switch (_type)
		{
		case 1:
			type = QStringLiteral("AFriend");
			break;
		case 2:
			type = QStringLiteral("BColleague");
			break;
		case 3:
			type = QStringLiteral("CGroup");
			break;
		case 4:
			type = QStringLiteral("DGroupChat");
			break;
		default:
			break;
		}
		return type;
	}
	void SetType(int type)
	{
		_type = type;
	}
	int getItemCount()
	{
		return _itemCountIflabel;
	}
	void setTitlePinYin(const QString &pinyin)
	{
		_pinYin = pinyin;
	}
	QString getTitlePinYin() const
	{
		return _pinYin;
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

	void setPhotoResID(const QString &resID)
    {
		_photoResID = resID;
    }
	void setBelongPhotoResID(const QString &belongResID)
	{
		_belongPhotoResID = belongResID;
	}
	QString getPhotoResID();
	QString getBelongPhotoResID(){ return _belongPhotoResID; }

	QString getBelongFeedId() const { return _belongFeedId; }
    void setBelongFeedId(const QString& feedId) { _belongFeedId = feedId; }

	QString getUserId() { return _userId; }
	void setUserId(QString userId) { _userId = userId; }

	void setIsForeceRefreshAvator(bool isRefresh)
	{
		_isForcerefreshAvator = isRefresh;
	}
	bool getIsForeceRefreshAvator() const{ return _isForcerefreshAvator; }
	void setItemCount(int itemCount){ _itemCountIflabel = itemCount; }
	void setShowButtonName(const QString &Name)
	{
		_showAllName = Name;
	}
	QString getShowButtonName() const
	{
		return _showAllName;
	}
};

typedef std::shared_ptr<TNSearchAdapter> TNSearchAdapterPtr;

class TNCardCaseSearchListModel : public TNTableModel
{
    Q_OBJECT
public:
    explicit TNCardCaseSearchListModel(QObject *parent = 0);
    void appendData(TNSearchAdapter *adapter);
	void appendData(QList<TNSearchAdapter *> adapterList);
	void UpdateItemAvatar(QString file,QString feedId);
	void setTableView(QTableView* tableView);
	int  setSearchSelected(TNSearchAdapter *adapter);
	void ResetModel();
private:
	QTableView*		  _tableView;
	QMutex _mutex;
};
#endif // TNSearchAdapter_H
