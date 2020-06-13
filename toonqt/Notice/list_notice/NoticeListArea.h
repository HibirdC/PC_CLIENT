#ifndef NOTICELISTAREA_H
#define NOTICELISTAREA_H

#include <QWidget>
#include <list>
#include <QLineEdit>
#include <QPushButton>
#include <QDateTime>
#include <QTimer>

#include "NoticeEnum.h"
#include "TNMessageListAdapter.h"
#include "ListAreaBase.h"
#include "LocalStorageCommon.h"
#include "TNDefaultPage.h"
#include "TNHttpUpdateGroupChat.h"
#include "TNHttpSetGroupChatDisb.h"
#include "TNHttpSwitchSet.h"
#include "Search/QSearchLineText.h"
#include "TNHttpObtainFeedList.h"
#include "TNHttpObtainGroupChatInfoByGroupChatId.h"

using namespace std;

class TNQLineEdit;
class TNSearchAdapter;
class TNNoticeListTableView;
class TNSearchAreaV2;
class TNSearchNameItem;
class NoticeListModel;
class NoticeListDelegate;
class TNGroupChatCreator;

class NoticeListArea : public ListAreaBase
{
	Q_OBJECT
public:
	NoticeListArea(int id, TNPluginParamPtr param, QWidget *parent = 0);
	~NoticeListArea();
	void CardCaseModelappendData(TNMessageListAdapter MessageAdapter);
    void initView();
	void init();
	void LoadScropUnRead(bool isDoubleC);
protected:
    virtual bool eventFilter(QObject *watched, QEvent *event);
    virtual void paintEvent(QPaintEvent *event);
private:
	void ReadFeedUserId(const QString& feedID, TNMessageListAdapter* tempAdapter);
	void setSessionLastMsg(MESSAGE_TYPE type, const QString& last_msg, TNMessageListAdapter* adapter);
	void setItemUnSelected();
    QModelIndex getSelectedModelIndex();
    void downSelection();
    void upSelection();
    //搜索的函数是从cardcase中拷贝过来的
    void initSearchPage();
    void searchContent(QString text);
    void searchClick(TNSearchNameItem* resultItem);
	void showNullPage(bool status);
    //单聊免打扰处理
    void setSigleChatAlarmStatus(const TNMessageListAdapter* session,bool alarm);
    //群聊免打扰处理
    void setGroupChatAlarmStatus(const TNMessageListAdapter* session,bool alarm);
    //动态更新feedinfo,获取头像url
    void dynamicUpdateFeedInfo(const QString& feedId);
    //动态更新groupinfo,获取头像url
    void dynamicUpdateGroupChatInfo(const QString& groupId);
private Q_SLOTS:
    virtual void OnMessageSlot(TNMessageListAdapter messageListAdapter, bool showDetailArea) override;
    void slotInitiateGroupChat(const QString &belongFeedId, const QString &groupChatId);
    void slotCreateGroupChatFromMenuArea(TNMessageListAdapter adpter);
	void on_NotifySendForward(QList<TNMessageListAdapter> msgListAdapter);
    /*
     * 每一次发起会话都会调用此函数(一个入口,在线消息)
     * isSelected---该条会话是否选中
     * isSend---会话中新的这条消息是否是自己发送的消息
     * isActive---会话界面是否active
     * isBubble---会话中新的这条消息是否要冒泡
    */
	void slotAppendSessionTop(TNMessageListAdapter messageAdapter,
		bool isSelected = false,
        bool isSend = false,
        bool isActive = true,
        bool isOnLine = true,
        bool isBubble = true);

    void slotRemoveSessionTop(TNMessageListAdapter messageAdapter,bool isSelected);
    void slotReduceUnreadNum(const QString& sessionId,int number);
    void onListAreaClicked(const QModelIndex& index);
	virtual void OnUnreadedUpdate(const QString& sessionId) override;
	void on_notifyRefresh(QStringList);
	void onUpdateSessionName(QString sessionId);
    //菜单操作
    void onManualOnTop(QModelIndex q_index);
    void onManualNoTop(QModelIndex q_index);
    void onModifyGroupName(QModelIndex q_index);
    void onManualDelSession(QModelIndex q_index);
    void onManualOnAlarm(QModelIndex q_index);
    void onManualNoAlarm(QModelIndex q_index);

    void slotSearch(QString content);
    void searchClickedSlot(const QString &, const QString &, const QString &);
    //更新会话active状态
    bool updateSessionActive(const QString& sessionId, bool isActive);
    //更新该条会话未读num
    bool slotUpdateSessionUnreadNum(const QString& sessionId,int num);
    //搜索widget隐藏的slot
    void hideSearchArea();
    //删除会话包括数据库
    bool slotRemoveSession(const QString& sessionId);
    //
	void slotRemoveSession(const QString& sessionId,bool isSelected);
    //up down session
    void slotUpOrDownSession(bool upOrDown);
    //updateTime
    void updateTime();
    //更新会话状态
    void slotUpdateSession(const QString& sessionId,bool isAll);
	//初始化本地数据
	void initLocalSession();
    //隐藏默认背景
    void onShowDefaultBackGround();
	//双击托盘，消息滚动
	void trayDoubleClickMsg();
    //创建群聊
    void slotCreateGroupChat();
	void on_notifyKeyEventDis(int keyEvent);
    void onUpdateSessionLastMsg(QString sessionId);
    //群聊更新后更新头像,cardlist下载,noticelist就不下载
    void onUpdateSessionListAvatar(QList<UINotifyData> dataList,bool isReady);
Q_SIGNALS:
	void ListAreaClicked(const QModelIndex &index);
	void ListAreaDoubleClicked(const QModelIndex &index);
	void messageNumberChanged(int count);
	void manualModifyGroupName(QString sessionId, QString name);

    //删除当前会话通知详情区
	void manualRemoveCurrentSession(const QString& sessionId,bool isSelected);
	//消息声音/闪烁提醒
	void messageNotify(TNMessageListAdapter adpter, bool isNotice);
    //重新加载详情区数据
    void reLoadDetailsData(TNMessageListAdapter* adapter);
    void activeMenu(int id);
    //离线消息更新menu上面的红点
    void outlineUpdateUnread(const QString& feedId,int unreaded,int type);
	//通知Tray 未读列表状态
	void updateTrayUnRead(const QString & sessionId);
	//更新离线Tray 未读数量
	void outlineUpdateUnreadTray(TNMessageListAdapter, int);
	//手动设置免打扰，取消免打扰后通知Tray
	void manualNoAlarmNotifyTray(const QString &, bool, int);
	//手动删除会话后， 通知Tray
	void manualDeleteSession(const QString &);
	//通知Tray 减少未读
	void reduceUnReadTray(const QString &, int);
	//手动修改群聊名称后，通知Tray
	void manualModifySessionNameToTray(const QString &, const QString &);

private:
    TNNoticeListTableView*		_listWidgetMessage;
	TableBasePtr				_pNoticelistTable;
	bool						_isSelected;
	//因为界面走mvd是异步创建的,所以选中置顶需要等界面创建完成才能操作
	//list保存需要置顶选中的session左侧界面list的id
	TNPluginParamPtr			_pluginParam;
    QString                     _currentSessionID;
    QWidget*					_searchWidget;
	QSearchLineText*				    _searchLineEdit;
    QPushButton*				_createGroupChatButton;
    //搜索是从cardcase拷贝过来的
    TNSearchAreaV2*				_searchArea;
    //初始化的时间
    QDateTime					_initTime;
    QTimer*						_updateTimer;
	int                         _latestUnReadIndex; //上一次转到未读Item 的index
	int                         _latestUnReadIndexTray; //上一次转到未读Item 的index

	QList<int>                  _unReadList;      //为了实现单击通知按钮， 记录当前列表
    //默认空界面
    TNDefaultPage          		*_nullPage;
    bool                    	_nullPageStatus;
    //新的mvd
    NoticeListDelegate 			*_noticeListDelegate;
    NoticeListModel				*_noticeListModel;

    TNGroupChatCreator 			*_groupChatCreator;
    //免打扰.修改群名称http操作
    TNHttpUpdateGroupChat		_tnHttpUpdateGroup;
    TNHttpSwitchSet				_tnHttpSwitchSet;
    TNHttpSetGroupChatDisb		_tnHttpSetGroupChatDisb;
    //更新feedinfo http操作
    TNHttpObtainFeedListPtr 	_httpObtainFeedList;
    //更行groupinfo http操作
    TNHttpObtainGroupChatInfoByGroupChatIdPtr _httpObtainGroupInfo;
};

#endif // NOTICELISTAREA_H
