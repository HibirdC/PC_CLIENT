#ifndef TNMESSAGELISTADAPTER_H
#define TNMESSAGELISTADAPTER_H

#include "common_global.h"

#include "TNTableModel.h"

#include <QList>
#include <QString>
#include <QPixmap>

class COMMON_EXPORT TNMessageListAdapter : public TNModelItemBase
{
public:
    enum Back_Status{
        em_notice_list_normal= 1,
        em_notice_list_hover,
        em_notice_list_select
    };
private:
    int		_type;//会话类型,单聊/群聊/通知
	QString _sessionId; // 标识一个会话
    QString _name; // _type == 单聊时表示昵称 | _type == 群聊时表示群聊名称
    QString _photoResID;
	QString _avatarPhotoUrl;//头像url
    QString _lastMessage;//最后一条消息
    qint64	_time;
    int		_unreadCount;//未读消息
	QString _toFeedId; //（toID）: _type == 单聊时表示好友ID | _type == 群聊时表示群聊ID 
	QString _userId;
	QString _tag; // _type == 单聊时表示个性签名 | _type == 群聊时表示群聊标签
	QString _myFeedId;// （fromID）: 本人名片id
	int		_topStatus;//置顶的优先级
	bool	_bNoAlarm;//是否开启免打扰
    QString _SenderName;//发消息的昵称
    bool    _active;//该选中且界面处在active状态,即用户注释在该条会话窗口
    QString _draft;//草稿
    QString _remark;//备注
	bool    _bAtMe;//是否有人@我
    QMap<int, QVector<QString>>         _AtUserMap;//@存储信息
    Back_Status	_back_status;//select,hover状态
public:
    TNMessageListAdapter();
    explicit TNMessageListAdapter(const QString &sessionId, int type);
    ~TNMessageListAdapter();

    bool isValid() const{
        if(_type == 52 || _type == 53){
            return !_myFeedId.isEmpty() && !_sessionId.isEmpty()
                && !_toFeedId.isEmpty();
        }else{
            return !_sessionId.isEmpty() && _type != -1;
        }
    }

	void setType(int type){
		_type = type;
	}
    int getType() const{
        return _type;
    }

	void setSessionId(const QString &sessionId){
		_sessionId = sessionId;
	}
    QString getSessionId() const{
		Q_ASSERT(!_sessionId.isEmpty());
		return _sessionId;
	}

    void setName(const QString &name);
    QString getName() const;

    QString getLastMessage() const;
    void setLastMessage(const QString &lastMessage);

    void setUnreadCount(int count){
        _unreadCount = count;
    }
    int getUnreadCount() const{
        return _unreadCount;
    }

	void setPhotoResID(const QString &resID);
    QString getPhotoResID() const;

    void setTime(qint64 time){
        _time = time;
    }
    qint64 getTime() const{
        return _time;
    }

	QString getToFeed() const { return _toFeedId; }
    void setToFeed(const QString& to) { _toFeedId = to; }

    QString getUserId() const { return _userId; }
    void setUserId(const QString& userId) { _userId = userId; }

    QString getTag() const { return _tag; }
	void setTag(QString tag){ _tag = tag; }

    QString getMyFeedId() const { return _myFeedId; }
	void setMyFeedId(const QString& feedId){ _myFeedId = feedId; }

    QString getAvatarPhotoUrl() const { return _avatarPhotoUrl; }
	void setAvatarPhotoUrl(const QString& url){ _avatarPhotoUrl = url; }

    int getTopStatus() const { return _topStatus; }
	void setTopSatus(int topStatus){ _topStatus = topStatus; }

    bool getNoAlarm() const { return _bNoAlarm; }
	void setNoAlarm(bool flag){ _bNoAlarm = flag; }

	void setSenderName(const QString & senderName){ _SenderName = senderName; }
    const QString getSenderName() const { return _SenderName; }

    void setDraft(const QString& draft){_draft = draft;}
    QString getDraft()const{return _draft;}

    void setAtUserMap(const QMap<int, QVector<QString>>& data){_AtUserMap = data;}
    QMap<int,QVector<QString>> getAtUserMap(){return _AtUserMap;}

    void setActive(bool active){_active = active;}
    bool getActive() const {return _active;}

	void setIsAtMe(bool status){ _bAtMe = status; }
    bool getIsAtMe() const { return _bAtMe; }

    void setBackStatus(Back_Status status){_back_status = status;}
    Back_Status getBackStatus() const {return _back_status;}

    void setRemark(const QString& remark){_remark = remark;}
    QString getRemark() const {return _remark;}
};
#endif // TNMESSAGELISTADAPTER_H
