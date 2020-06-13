#pragma once
#include "localstorage_global.h"
#include "LocalStorageCommon.h"
#include "common_global.h"

#include "TNDbUtil.h"
#include <QObject>
#include <QUrlQuery>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QMap>
#include <QEventLoop>
#include <QMargins>
#include <QMutex>

#define DEFAULT_FEED ""
#define NOTIFYSESSION_TYPE "51"
class LOCALSTORAGE_EXPORT TNDataCache :public QObject
{
	Q_OBJECT
protected:
	TNDataCache(QObject *parent = 0);
public:

	~TNDataCache();
	static TNDataCache* GetInstance();
	/*************************************************
	Function:       GetColleagueCache
	Description:    获取同事缓存
	Input:          空QList
	Output:         包含数据的Qlist
	Return:			void
	Others:         调用完毕后应该检测是否成功，如果获得数据为空，说明当前缓存未初始化，应该进行初始化
	*************************************************/
	void GetColleagueCache(QList<TNStructCompany>& companyList, QString myFeedId = DEFAULT_FEED);

	/*************************************************
	Function:       GetGroupCache
	Description:    获取群组缓存
	Input:          空QList
	Output:         包含数据的Qlist
	Return:			void
	Others:         调用完毕后应该检测是否成功，如果获得数据为空，说明当前缓存未初始化，应该进行初始化
	*************************************************/
	void GetGroupCache(QList<TNStructGroup>& groupList, QString myFeedId = DEFAULT_FEED);

	/*************************************************
	Function:       GetGroupChatCache
	Description:    获取群聊缓存
	Input:          空QList
	Output:         包含数据的Qlist
	Return:			void
	Others:         调用完毕后应该检测是否成功，如果获得数据为空，说明当前缓存未初始化，应该进行初始化
	*************************************************/
	void  GetGroupChatCache(QList<TNStructGroupChat>& groupChatList, QString myFeedId = DEFAULT_FEED);

	/*************************************************
	Function:       GetFriendCache
	Description:    获取指定我的名片好友缓存，如果当前传入名片为空，则返回当前登录名片好友信息
	Input:          空QList
	Output:         包含数据的Qlist
	Return:			void
	Others:         调用完毕后应该检测是否成功，如果获得数据为空，说明当前缓存未初始化，应该进行初始化
	*************************************************/
	void  GetFriendCache(QList<TNStructFriend>& friendList, QString myFeedId = DEFAULT_FEED);

	/*************************************************
	Function:       UpdateGroupCachebyId
	Description:    根据群组feed ID 来更新缓存
	Input:          QList： 空的Qlist
					QString： feed ID
					type : 1 : 添加 2： 修改 3： 删除
	Output:			包含数据的Qlist
	Return:			void
	Others:         此函数的目的在于维护缓存和数据库的匹配度， 在数据库插入新的数据后调用有效
	*************************************************/
	void UpdateGroupCachebyId(QList<TNStructGroup> &groupInfoList, QString feedId, CacheGOp type);
	void UpdateGroupCachebyId(QList<TNStructGroup> &groupInfoList, QString feedId, CacheGOp type, TNStructGroup &group); //返回group结构
	/*************************************************
	Function:       UpdateGroupChatCachebyId
	Description:    根据群聊feed ID 来更新缓存
	Input:          QList： 空的Qlist
					QString： feed ID
					type : 1 : 添加 2： 修改 3： 删除
	Output:			包含数据的Qlist
	Return:			void
	Others:         此函数的目的在于维护缓存和数据库的匹配度， 在数据库插入新的数据后调用有效
	*************************************************/
	void UpdateGroupChatCachebyId(QList<TNStructGroupChat> &groupChatInfoList, QString feedId, CacheGCOp type);
	void UpdateGroupChatCachebyId(QList<TNStructGroupChat> &groupChatInfoList, QString feedId, CacheGCOp type,TNStructGroupChat &groupChat);
	/*************************************************
	Function:       UpdateFriendCachebyId
	Description:    根据好友feed ID 来更新缓存
	Input:
					QString： feed ID
					QString： 我的名片的 feed ID
					type : 1 : 添加 2： 修改 3： 删除
	Output:			包含数据的Qlist
	Return:			void
	Others:         此函数的目的在于维护缓存和数据库的匹配度， 在数据库插入新的数据后调用有效
	*************************************************/
	void UpdateFriendCachebyId(QString feedId, QString belongId, CacheFOp type, TNStructFriend &myFrind);
	
	/*************************************************
	Function:       UpdateColleagueCachebyId
	Description:    根据员工feed ID 来更新缓存
	Input:          QList： 空的Qlist
	QString：		feed ID
	QString：		我的名片的 feed ID
					type : 1 : 添加 2： 修改 3： 删除
	Output:			包含数据的Qlist
	Return:			void
	Others:         此函数的目的在于维护缓存和数据库的匹配度， 在数据库插入新的数据后调用有效
	*************************************************/
	void getMyStuff(QList<st_FeedPtr>& mystuff, const QString &feedId = DEFAULT_FEED);
	st_FeedPtr getMyFirstPersonalCard();
	/*************************************************
	Function:       GetGroucpChatMemberCache
	Description:    获取群聊成员接口
	Input:          群聊feed ID
	Output:			QList<TNFriend>
	Return:			QList<TNFriend>
	Others:
	*************************************************/
	QList<TNFriend> GetGroupChatMemberCache(const QString &groupId);
	void SwitchCurrentMyFeed(QString currentFeed){ _currentMyfeedId = currentFeed; }
	const QString& GetCurrentMyFeed(){ return _currentMyfeedId; }
	void UpdateInStepCache(QList<UINotifyData> dataList, int type);
	void ReSetCache();
	bool IsCurrentCardCache(const QString &feedId);
	void SynUpdateFeedCache(st_FeedPtr feed,int type,int sources);
	void SynUpdateGroupChatCache(st_GroupInfoPtr group);
	int GetSpecialFriendCount(const QString & feedID);//获取指定Feed 的数量
	st_FeedPtr getSpecialFriendFeed(const QString & feedID,const QString &belongFeed);
	QString GetMyTitle(const QString &myFeed);
	void InstallCatcheFeedUpdateNotify(const QObject * resultReceiver);
	void InstallCatcheGroupChatUpdateNotify(const QObject * resultReceiver);
	void UpdateMyStuffCache(); 
	bool IsInMyStuff(const QString &feed);
	bool IsInMyStuffFromDB(const QString &feed);
	int  updateFriendListDupCount(const QString &feedId,CacheFOp op);
    QString getPhoneNum(){return _currentPhoneNum;}
    void setPhoneNum(const QString& phone_num);
	int getGroupStatusByID(const QString &groupId);
	void updateGroupMemberCount(const QString &groupId,int count);
	//获取当前好友备注
	const QString getFriendFeedReMark(const QString &feedId, const QString &belongFeed);
	const TNStructRemark getFriendFeedReMarkWithPY(const QString &feedId,const QString &belongFeed);
	//更新好友备注
	bool  updateFriendFeedReMark(const QString &feedId, const QString &belongFeed,const QString &remark);
	//获取通知消息
	int getNotifyMsgCache(QList<st_SessionPtr> &notifyList);
	//更新组织名片沟通能力状态
	void updateOrgCommunicationStatus(const QString &feedId, const QString & status);
	//注意：业务层不能使用此接口
	QString innerGetOrgCommunicationStatus(const QString &feedId);
	//获取组织名片沟通能力
	bool  getOrgCommunicationStatus(const QString &feedId);
	//feed base信息是否变化
	bool  isChangedOfBaseInfo(QString feedId,QString name,QString subtitle,QString headImage,int type);
	bool  isChangedOfGroupInfo(QString feedId, QString name, QString headImage,int memberCount);
Q_SIGNALS:
	void HasUpdateAllCache();
	void ResetSignal();
	void guysUpdateGroupChat(const QString &feed);
	void guysUpdateCard(const QString &feedId, const QString &avatarUrl, const QString &title
		, const QString &subTitle, const QString &userId, const QString &titlePy, int sources);

public slots:
	void updateAllCacheSlot();
	void reSetCacheSlot();
	void UpdateColleagueSlot();
private:
	void UpdateFriendCache();
	void UpdateColleagueCache();
	void UpdateGroupCache();
	void UpdateGroupChatCache();
	bool GetGroupInfobyId(TNStructGroup &group, QString feedId);
	bool IsExistbyFriendFeedId(QString feedId);
	bool IsExistbyGroupChatId(QString feedId);
	const TNStructRemark getRemarkFromRelation(const QString &feedId,const QString &belongFeed);
	static TNDataCache* _Instance;
	bool _isUpdateAllCache;
	QMutex _mutex;
	/*
	Friend
	*/
	QMultiMap<QString, TNStructFriend>		_FriendList;

	/*
	Colleague 
	*/
	QMultiMap<QString, TNStructCompany>		_CompanyList;

	/*
	Group
	*/
	QMultiMap<QString, TNStructGroup>		_GroupList;

	/*
	GroupChat
	*/
	QMultiMap<QString, TNStructGroupChat>	_GroupChatList;
	QList<st_FeedPtr>				        _myStuff;
	QString									_currentMyfeedId;
    QString 								_currentPhoneNum;
};

