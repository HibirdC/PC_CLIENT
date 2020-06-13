#ifndef TNNOTICEUPDATER_H
#define TNNOTICEUPDATER_H
#include <set>
#include "imcore_global.h"
#include "TNHttpObtainGroupChatsByUserId.h"
#include "TNHttpObtainGroupChatMembersByGroupChatId.h"
#include "TNHttpGetListRelationItem.h"
#include "TNHttpGetContactFriendFeed.h"
#include "TNHttpGetGroupCardByUser.h"
#include "TNUserVersionInfo.h"
#include "TNHttpGetListStaffContactByUserId.h"
#include "TNHttpGetListStaffCard.h"
#include "TNHttpGetListOrgCardByUserId.h"
#include "TNHttpGetListGroupContactByUserId.h"
#include "TNHttpGetOrgGroupList.h"
#include "TNHttpApi.h"
#include "TNHttpObtainGroupMembersByGroupId.h"
#include "TNHttpGetListStaffCardByUserId.h"
#include "TNHttpQuertySwitchInfo.h"
#include "TNHttpGetCompanyInfoByComIdList.h"
#include "TNHttpGetCompanyFeedIdByComId.h"
#include "TNHttpGetListOrgCard.h"
#include "TNHttpGetUnConfirmFriendFeed.h"
#include "TNHttpGetMyGroup.h"
#include "TNHttpGetFeedRemark.h"
#include "TNHttpGetOrgCommunicationStatus.h"
#include <qstringlist.h>
#include <QTimer>

class TNUserDataHelper;
class TNNoticeUpdaterSyncHelper;
class TNHttpObtainFeedList;
class IMCORE_EXPORT TNNoticeUpdater : public QObject
{
	Q_OBJECT

public:
    TNNoticeUpdater(bool isIncreamentUpdate = true);
	~TNNoticeUpdater();
public:
	void ProcessUpdateUI(int type, QString info = "");
	void ProcessStartUpdateDb();
	void ProcessUpdateGroupAndRelation();
	void ProcessUpdateCompany();
	void ProcessUpdateRemark(const QString&from, const QString &to);

private:
	//更新群聊数据
	void updateGroupChat();
	//更新群聊成员数据
	void updateGroupChatMember(QString groupId);
	//更新我的好友
	void updateMyFriend();
	//更新好友的备注
	//void updateFriendReMark();
	void updateFriendReMarkSingle(QString from,QStringList tos);
	//更新群组
	void updateGroup();
	void updateGroupMember(QString groupId);
	//更新我的普通名片
	void updateMyCard();
	//更新我的同事
	void updateMyCompany();
	//更新单聊免打扰列表
	void updateDisturibData();
	//更新新学员
	void updateNewFriend();
	//转换数据库表： BMessage0和Session 
	static void castDBTable();
	static bool castBmssageToCTNMessage();
	static bool castSession();

    void init(bool needUpdateCompany);
	void appendUINotifyData(QString feedId, QString belongId,UIOperateType operateType, QList<UINotifyData> &dataList);
	QString GetBelongId(const QString &feedId);
	//更新组织名片配置能力
	void updateOrgCommunicationStatus(QSet<QString> oFeeds,bool needRefreshUI);
signals:
	void UpdateRefreshUI(int type, QString info);
	void FinishedThread();
    void AllUpdateFinished();    //全部更新完毕
    void companyUpdateFinished();//同事通讯录更新完毕
	void StartUpdateDb();
	void StartUpdateCompany();
	void startUpdateReMark(const QString&,const QString &);

public slots:
	void OnFinishLoadSlots(int type, QList<UINotifyData> dataList);
	void OnUpdateRefreshUI(int type, QString info);
	void StartUpdateThread();
	void onTimerout();
private slots:	
	void companyUpdateFinishedSlot();
    void monitorHttpApi(TNHttpBaseApi * httpApi);
    void onHttpApiReturn(TNHttpBaseApi * httpApi);
    void onNewFeedGetApi(TNHttpObtainFeedList *);
	void StartUpdateCompanySlot();
	void startUpdateReMarkSlot(const QString&from, const QString &to);

private:
    bool                                                    _isIncreamentUpdate;
    bool                                                    _hasStartedUpdating;//是否已经开始更新通讯录
    bool                                                    _needEmitCompanyFinished;//是否需要发送通讯录更新
	bool                                                    _isChangedOfCompanyInfo;
	TNHttpGetListRelationItemPtr							_httpGetListRelationItem;
	TNHttpObtainGroupChatsByUserIdPtr						_httpObtainGroupChatsByUserId;
	TNHttpObtainGroupChatMembersByGroupChatIdPtr            _httpObtainGroupChatMembersByGroupChatId;
	TNHttpObtainGroupMembersByGroupIdPtr                    _httpObtainGroupMembersByGroupId;
	TNHttpGetContactFriendFeedPtr							_httpGetContactFriendFeed;
	TNHttpGetContactFriendFeedPtr							_httpGetAllFriendFeed;
	TNHttpGetMyGroupPtr                                     _httpGetMyGroup;
	TNHttpGetListStaffContactByUserIdPtr					_httpGetListStaffContactByUserId;
	TNHttpGetListStaffCardPtr								_httpGetListStaffCard;
	TNHttpGetListStaffCardByUserIdPtr						_httpGetListStaffCardByUserId;
	TNHttpGetListOrgCardByUserIdPtr					        _httpGetListOrgCardByUserId;
	TNHttpGetListGroupContactByUserIdPtr					_httpGetListGroupContactByUserId;
	TNHttpGetOrgGroupListPtr								_httpGetOrgGroupList;
	TNHttpApiPtr											_httpApi;
	TNHttpQuertySwitchInfoPtr								_httpQuerySwitchInfo;
	TNHttpGetCompanyInfoByComIdListPtr                      _httpGetCompanyInfobyComIdList;
	QList<UINotifyData>										_UIRefreshList;
    TNUserDataHelper                                        *_userDataHelper;
    std::set<TNHttpBaseApi *>                                _ConnectingHttpApis;//处于连接中的对象容器
	TNHttpGetCompanyFeedIdByComIdPtr                        _httpGetCompanyFeedIdByComId;
	TNHttpGetListOrgCardPtr                                 _httpGetListOrgCardByFeeds;
	TNHttpGetListOrgCardPtr                                 _httpGetListOrgCardByFeedForOrg;
	TNHttpGetUnConfirmFriendFeedPtr                         _httpGetUnConfirmFriendFeed;
	TNHttpGetFeedRemarkPtr                                  _httpGetFeedReMark;
	TNHttpGetOrgCommunicationStatusPtr                      _httpGetOrgCommunication;
	QTimer*													_outTimer;
	QDateTime                                               _latestUpdateCompanyTime;
	QNetworkAccessManager*									_netWorkManager;
};
#endif

