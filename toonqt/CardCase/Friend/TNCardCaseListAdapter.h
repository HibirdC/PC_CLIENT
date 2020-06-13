#ifndef TNCARDCASELISTADAPTER_H
#define TNCARDCASELISTADAPTER_H

#include <QListView>
#include <QList>
#include <QString>
#include <QPixmap>
#include <QMutex>
#include "TNListModel.h"

#include "common_global.h"
#include "TNDbUtil.h"

class TNCardCaseListAdapter : public TNModelItemBaseV2
{
public:
	enum ItemType{FriendLetter=0, FriendItem =1,NewFriend};

private:
    int _type;
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
	QString _latestAvatarURL;
	QString _subTitle;
	QString _myTitle;
	QString _staticTitle;   //此处存的永远是title
	QString _staticTitlePy; //此处存的永远是titlePy

	bool _isShowMyInfo;
	bool _isRepaint;
	int	 _newFriendUnRead;
	bool _isShowRemark;

public:
	explicit TNCardCaseListAdapter(int type);

    ~TNCardCaseListAdapter();

    int getType()
    {
        return _type;
    }
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

	void setLatestAvatarUrl(const QString &latestAvatarUrl)
	{
		_latestAvatarURL = latestAvatarUrl;
	}
	QString getLatestAvatarUrl() const
	{
		return _latestAvatarURL;
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

	QString getMyTitle(){ return _myTitle; }

	void setMyTitle(const QString &myTitle)
	{
		_myTitle = myTitle;
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

	void setIsShowMyInfo(bool isShow)
	{
		_isShowMyInfo = isShow;
	}
	bool getIsShowMyInfo() const{ return _isShowMyInfo; }

	void setIsRepaint(bool repaint){ _isRepaint = repaint; }
	bool getIsRepaint(){ return _isRepaint; }

	void setNewFriendUnRead(int unRead){ _newFriendUnRead = unRead; }
	int  getNewFriendUnRead(){ return _newFriendUnRead; }

	void setIsShowReMark(bool isShow){ _isShowRemark = isShow; }
	bool getIsShowReMark(){ return _isShowRemark; }

	void setStaticTitle(const QString &title)
	{
		_staticTitle = title;
	}
	QString getStaticTitle(){
		return _staticTitle;
	}

	void setStaticTitlePy(const QString &staticTitlePy)
	{
		_staticTitlePy = staticTitlePy;
	}
	QString getStaticTitlePy(){
		return _staticTitlePy;
	}
};

typedef std::shared_ptr<TNCardCaseListAdapter> TNCardCaseListAdapterPtr;

class TNCardCaseListModel : public TNListModel
{
    Q_OBJECT
public:
    explicit TNCardCaseListModel(QObject *parent = 0);

	Qt::ItemFlags flags(const QModelIndex &index) const;
    void appendData(TNCardCaseListAdapter *adapter);
	void appendData(QList<TNCardCaseListAdapter *> adapterList);
    int	 removeRowsExceptKeyword(const QString& keyword);
    bool removeRowByDialogId(const QString& dialogId);
	int  setSearchSelected(const QString &feedId,const QString &belongId);
	void insertItem(TNCardCaseListAdapter * adapter,int enbaleDup = false);
	void removeItem(const QString &feedId, const QString &belongId);
	void updateFriendBelong(const QString &feedId,int infactCount,bool isAdd);
	int  getDupItemIndex(const QString &feedId);
	void updateFriendItemInfo(const QString &feedId, const QString &file, const QString &name,const QString &namePy, const QString &subName,const QString &avatarURL);
	void updateFriendItemMyInfo(const QString &feedId, const QString myName);
	void resetModel();
	void updateNewFriendUnRead(int count);
	void refreshItem(const QString &feedId);
	void updateFriendItemReMark(QString feedId, QString reMark, QString belongFeed);
	QModelIndex getNextIndex(QModelIndex oldIndex);
	QModelIndex getPreIndex(QModelIndex oldIndex);
	void updateKeyStartFlag(bool flag);
private:
	int getValidPosition(TNCardCaseListAdapter * adapter,bool &newItem);
	int getValidPositionNOTDup(TNCardCaseListAdapter * adapter, bool &newItem);
	int getSubItemStruct(QMap<QChar, int> &firstLetterToFriendMap, QMap<QChar, int> &firstSCharToFriendMap);
private:
	QMutex _mutex;
	bool _startFlag;
};
#endif // TNCARDCASELISTADAPTER_H
