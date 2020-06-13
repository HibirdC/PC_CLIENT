#ifndef TNAvatarChoiceAdapter_H
#define TNAvatarChoiceAdapter_H

#include <QTableView>
#include <QList>
#include <QString>
#include <QPixmap>
#include <QMutex>
#include "TNTableModel.h"

#include "common_global.h"
#include "TNAvatarChoiceItem.h"

class TNAvatarChoiceAdapter : public TNModelItemBase
{
private:
    QString _dialogID;
    QString _name;
    QString _photoResID;
	QString _AvatarURL;
	bool _isForcerefreshAvator;
	bool _isCurrentCard;
	int  _unReadCount;
public:
    TNAvatarChoiceAdapter();

    ~TNAvatarChoiceAdapter();

	int GetUnreadCount() const { return _unReadCount; }
	void SetUnreadCount(int unReadCount) { _unReadCount = unReadCount; }

	void setAvatarUrl(const QString &avatarUrl)
	{
		_AvatarURL = avatarUrl;
	}
	QString getAvatarUrl() const
	{
		return _AvatarURL;
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

	void setPhotoResID(const QString &resID)
    {
		_photoResID = resID;
    }

    QString getPhotoResID();
	void setIsForeceRefreshAvator(bool isRefresh)
	{
		_isForcerefreshAvator = isRefresh;
	}
	bool getIsForeceRefreshAvator() const{ return _isForcerefreshAvator; }

	void setIsCurrentCard(bool isCurrent)
	{
		_isCurrentCard = isCurrent;
	}
	bool getIsCurrentCard() const{ return _isCurrentCard; }
};

typedef std::shared_ptr<TNAvatarChoiceAdapter> TNAvatarChoiceAdapterPtr;

class TNAvatarChoiceListModel : public TNTableModel
{
    Q_OBJECT
public:
    explicit TNAvatarChoiceListModel(QObject *parent = 0);
    void appendData(TNAvatarChoiceAdapter *adapter);
	void appendData(QList<TNAvatarChoiceAdapter *> adapterList);
	void UpdateItemAvatar(QString file,QString feedId);
	void setTableView(QTableView* tableView);
	int  setSearchSelected(TNAvatarChoiceAdapter *adapter);
	void ResetModel();
private:
	QTableView*		  _tableView;
	QMutex _mutex;
};
#endif // TNAvatarChoiceAdapter_H
