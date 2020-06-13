#ifndef NOTICEDETAILSAREA_H
#define NOTICEDETAILSAREA_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QWidget>
#include <QTableView>
#include <QPixmap>
#include <QStack>
#include <QTimer>

#include "TNMsgDetailModel.h"
#include "DetailsAreaBase.h"
#include "TNChatDetailBase.h"
#include "LocalStorageCommon.h"
#include "tnnotifycenter.h"
#include "TNHttpCloudApi.h"
#include "mytableview.h"
#include "tnnoticeatarea.h"
#include "loadhistorydata.h"

namespace Ui {class NoticeDetailsArea;}


class tnLoadingHository;
class TNGenerateNoticeModelData;
class TNSendIMsg;
class TNEmojiWidget;
class TNWarnDlag;
class TNDetailsUnreadWdiget;
class TNGroupChatMembersWidget;
class someoneatyou;


class NoticeDetailsArea : public TNChatDetailBase
{
	Q_OBJECT

public:
	NoticeDetailsArea(int id, TNPluginParamPtr param, QWidget *parent = 0);
	~NoticeDetailsArea();

public Q_SLOTS:
	void OnListAreaClickedSlot(const QModelIndex & index);
	void OnSendMessageSlot();
	void OnExpressionSlot();
	void btn_clicked();
	void onAddFile();
	void onScreenShot();//截屏
    void slotFinishedScreenShotByShortCut();
	void onScreenShotPopupMenu();//截屏按钮的弹出菜单
    void onActionHideAtScreenShot(bool isChecked);//截屏时隐藏聊天对话框action响应
	//接收消息显示
	void on_notifyRefresh(QString type, int statCode, const QString statDesc, TNMsgData msgData);
	void on_notifyRefresh(QString type, TNNoticeInfo &noticeInfo);
	void on_notifyRefresh(int type, QList<UINotifyData> dataList);
    void on_notifySendHotKeyChanged(const QString &key);
	//top
	void onPsuhButtonName(bool checked);
    void loadHistoryFinshed(bool isLastPage,int num,bool isJump);

	void slotCreateGroupChatFinished(TNMessageListAdapter);
	void slotExitGroupChatFinished(TNMessageListAdapter adpter);
	void slotUpdateArrowStatus();

	//拖拽实现发送图片和文件
	void dragImageSend(QString filePath);
    void dragImageBatchSend(const QStringList &filePaths);
	void dragFileSend(QString filePath);
    void dragFileBatchSend(const QStringList &filePaths);
    //文件最大60M信号
    void warnMaxFileSize(QString content);

    //处理撤回消息
	void revokeProcess(int resultType,int msgType,qint64 msgTime,const QString &sessionId,
		const QString &msgId,const QString &pushInfo);
	//手动删除当前会话
	void on_manualRemoveCurrentSession(const QString & sessionId,bool isSelected);
    //重新加载详情区数据
    //重新加载详情区用于离线唤醒重新加载当前选择会话数据
    void reloadChatDetails(TNMessageListAdapter* adapter);
    //加载该条会话的草稿
    void reloadDraft(TNMessageListAdapter* adapter);
    //保存会话的草稿
    void saveDraft(TNMessageListAdapter* adapter);
    //返生成@样式到富文本框
    void reverseAtObject(int pos, QString atFeedId, QString atFeedName,QString showText);
    //更新备注
	void on_notifyReMarkUpdate(const QString &from, const QString &to, const QString &remark, int sources);
    //页面选择切换
    void onTurnPage(int page);
private Q_SLOTS:
	void on_notifyRemoveSession(QString);
	void on_notifyReadSession(QString);
	void on_manualModifyGroupName(QString sessionId, QString name);
    void feedCardUpdateFromCatche(const QString &feedId,
                                  const QString &avatarId,
                                  const QString &name,
                                  const QString &subName,
                                  const QString &userId,
                                  const QString &namePy,
                                  int sourceType);
	void deleteMsgSlots(const QString &msgId);
    void on_reSendData(TNModelUserMessage data);
    //切换名片
    void on_notifyCurrentFeedChanged(const QString &feedId);
    void scrollBarValueChanged(int value);
    void slotEditCtr(int position,int charsRemoved,int charsAdded);
    void SearchClickedSlot(QString name,QString feedId,QString nickName);
    void atMsgBoxCliecked(QString msgId, int index, bool isScroll = true);
    void onFocuseInTimeOut();
    void onUnreadWidgetDownClicked();
    void onUnreadWidgetUpClicked();
    void onDropUrlsSlot(QList<QUrl>);
    void jumpToMsgSlots(QString msgId);
Q_SIGNALS:
	void activeSessionTop(TNMessageListAdapter adpter,
		bool isSelected = false,
        bool isSend = false,
        bool isActive = true,
        bool isOnline = true,
        bool isBubble = true);
    void removeSession(TNMessageListAdapter adpter, bool isSelected);
	void updateSessionName(QString sessionId);
	void messageNotify(TNMessageListAdapter adpter,bool isNotice);
    void reduceUnreadNum(const QString& sessionId,int number);
    void readSessionUnreadNum(const QString& sessionId,int number);
    void unReadCountSignal(const QString &feedID,int unCount,int type);
    void updateSessionClicked(const QModelIndex& index);
    void upOrDownSession(bool upOrDown);
	//通知Tray 未读列表状态
	void updateTrayUnRead(const QString & sessionId);
    //通知会话区更新最后一条消息
    void updateSessionLastMsg(const QString& sessionId);
protected:
	void wheelEvent(QWheelEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);
	void resizeEvent(QResizeEvent *event);
private:
    struct SomeOneAtData{
        SomeOneAtData(){
            index = -1;
        }
        SomeOneAtData(QString name,QString id,int n = -1){
            atName = name;
            msgId = id;
            index = n;
        }

        QString atName;
        QString msgId;
        int index;
    };
    void InitReceiveWidget();
    void someoneAtme(const QString &name, const QString& msgId, int index = -1);
    void showSomeoneAtme();
    bool moveSomeOneAtWidget();
	/*
	增加发送消息
	*/
	void AppendSendWidget(MESSAGE_TYPE type,
		const QString& content,
        bool bSend = true,
        bool isAt = false,
        QList<QString> list_feedId = QList<QString>());

	/*
	增加接收消息
	*/
	void AppendRecvWidget(MESSAGE_TYPE type,
		TNMsgData msgData,
		const QString& myFeedId,
		bool bDownloaded = true);
	/*
    增加撤回消息
	*/
	void AppendRevokeWidget(const QString& content, MESSAGE_TYPE type, int revokeResult,int index);
	/*
     * 生成草稿数据
    */
    QString generateDraft();
	/*
	生成文件数据
	*/
	void generateSendFileData(const QString& file_name);

    void showChatDetails();
    //显示企业等通知的详情区
    void showNoticeDetails(const QString &sessionId,TNMessageListAdapter* adapter);
    void setSessionLastMsg(MESSAGE_TYPE type, const QString& last_msg, TNMessageListAdapter* adapter,bool isAt,bool isSenderName,const QString& from = "");
	void InitATSearchPage(int x,int y,int itemCount);
	int  DoSearch(const QString & text,const QString &groupId,const QString &myFeed);
    bool isNoticeActive();
    void noticeFocuseIn();
    /*
     * 创建未读消息悬浮窗口
     * unread未读消息条数,用于向上未读消息点击时展示未读条数
     * up表示展示向上或者向下未读消息widget,向下时未读消息数累加
     *
    */
    void showUnreadWidget(int unread = 0,bool up = true,
                          bool isAdd = false,bool isClear = false);
    void moveUnreadWidget(bool up);
    /*
     *加载历史记录
    */
    void loadHistoryMsg(int num = PAGE_NUM,bool isJump = false);
    /*
     *加载向上跳转历史数据
    */
    void loadUpJumpMsg(const QString& fristUnreadMsgId);
    void showHistoryGif();
    /*
     * 判断字符串全为空格
    */
    bool isAllSpace(const QString& content);

    QString wrapTitleLabelName(const QString& oldName);

    void insertTag(const QString& text,const QString& feedId,const QString& feedName);
private:
	Ui::NoticeDetailsArea *ui;

    friend class 		   TNNoticeDetailTableWidget;

    MyTableView*		   _tableView;
    TNMsgDetailModel*	   _msgModel;

    tnnoticeatarea* 	   _ATSearchArea;

	TNMessageListAdapter*  _currentAdpter;//当前会话
    LoadHistoryData*	   _loadHistoryData;
	TNPluginParamPtr	   _pluginParam;//路由表


	tnLoadingHository      *_lodingHositoryGif;//加载历史记录ui
	bool				   _isLoading;//当前正在加载数据
	bool				   _isLastMsg;//历史记录加载完了
	//生成数据
	TNGenerateNoticeModelData* _generateModelData;
	//负责发送接收数据
	TNSendIMsg*				   _imClient;
	TNEmojiWidget*			   _emojiWidget;//表情
	int						   _modelSize;
    bool  					   _isSendNeedPressCtrl;//发送消息是否需要按下ctrl键
	QList<QString>             _atActiveList; //存储未选中的adapter at list
	QString					   _oldSelectDir; //上次选择的目录
	bool                       _bisAting;
    QMenu*                     _screenShotMenu;
    QAction*                   _actionHideAtScreenShot;//截图时，隐藏当前窗口
    bool                       _isHideAtScreenShot;
    //focuseIn timer定时器
    std::map<QTimer*,TNMessageListAdapter> _focuseInTimer;
    //未读消息悬浮窗
    TNDetailsUnreadWdiget*	   _tnDetailsUnreadWdiget;

    //down lastmsg index
    int 					   _downLastMsgIndex;
    TNGroupChatMembersWidget   *_membersWidget;
    //显示@你的界面
    someoneatyou*			   _someOneAtYouWidget;
    //存储@你的数据
    std::list<SomeOneAtData>   _someOneAtYouData;
};

#endif // NOTICEDETAILSAREA_H
