#ifndef TNNOTIFYCENTER_H
#define TNNOTIFYCENTER_H
#include "imcore_global.h"
#include <QObject>
#include <QVariant>
#include "TNIMCoreClient.h"
#include "TNIMNoticeProcessor.h"
#include "TNMessageListAdapter.h"
#include "common_global.h"
const int TNMPNetKickout = 1000;

#define TNIMNetStatusNotification           "TNIMNetStatusNotification"
#define TNIMKickoutNotification             "TNIMKickoutNotification"
#define TNIMMsgACKNotification              "TNIMMsgACKNotification"
#define TNIMMsgRecvNotification             "TNIMMsgRecvNotification"
#define TNIMMsgCountNotification             "TNIMMsgCountNotification"
#define TNIMMsgHistoryNotification           "TNIMMsgHistoryNotification"
enum RefreshTypeUI
{
	RefreshTypeUI_NoFresh = -1,				//不刷新
	RefreshTypeUI_Myfriend = 0,				//好友列表刷新
	RefreshTypeUI_GroupChat = 1,			//群聊列表刷新
	RefreshTypeUI_Group = 2,				//群组列表刷新
	RefreshTypeUI_Colleague = 3,			//我的同事刷新
	RefreshTypeUI_MyCard = 4,               //我的名片刷新
	RefreshTypeUI_GroupMember = 5 ,          //
	RefreshTypeUI_Search     = 6,
	RefreshTypeUI_SwitchSingle = 7,			//单聊免打扰开关	
    RefreshTypeUI_RefreshAll  = 8,           //刷新所有数据

    RefreshTypeUI_Newfriend = 9				//新学员列表刷新
};
class IMCORE_EXPORT TNNotifyCenter : public QObject
{
    Q_OBJECT
public:
    explicit TNNotifyCenter(QObject *parent = 0);
public:
	static TNNotifyCenter* instance();

    void connectNotifyNetStatus(const QObject * receiver);
    void connectNotifyRefresh(const QObject * receiver);
	void connectNotifyRefreshAddressList(const QObject * receiver);
    void connectNotifyResource(const QObject * receiver);
	void connectNotifyOffMsg(const QObject * receiver);
	void connectNotifyRefreshSession(const QObject * receiver);
	void connectNotifyRemoveSession(const QObject * receiver);
	void connectNotifyReadSession(const QObject * receiver);
	void connectNotifyRefreshRevert(const QObject * receiver);
    void connectNotifySendHotKeyChanged(const QObject * receiver);
    void connectScreenShotByShortCut(const QObject * receiver);
	void connnectNotifyCurrentFeedChanged(const QObject * receiver);
    void connnectNotifyCreateGroupChatFinished(const QObject *receiver);
    void connnectNotifyCreateToChat(const QObject * receiver);
	void connectNotifyReMarkUpdate(const QObject * receiver);
	void connectNotifyOrgCommunicationStatus(const QObject * receiver);
	void connectNotifyKeyEventDis(const QObject * receiver);
    //通知检查版本返回结果
	void connectNotifyCheckVersionFinished(const QObject * receiver);
	void connectNotifySendForward(const QObject * receiver);
    void postNotifyCheckVersionFinished(
        bool isNeedUpgrade,
        bool isForceUpgrade,
        QString downLoadURL,
        int nCheckType,
        QString versionDesc
        );

    void postNotifyResource(const QString resID,int statCode, QVariantMap mapData = QVariantMap());

    void postNotifyNetStatus(int netStatus);
	void postNotifyRefresh(QString type, int statCode, const QString statDesc, TNMsgData& msgData);
	void postNotifyRefresh(QString type, TNNoticeInfo& noticeData);
	void postNotifyRefresh(QStringList sessionIds);
	void postNotifyRefreshRevert(int resultType,int msgType,qint64 msgTime,const QString &sessionId, const QString &msg, const QString &content);
	void postNotifyRefresh(int refreshType, QList<UINotifyData>& dataList);
	void postNotifyOffMsg(int count);
	void postNotifyOnlineMsg(QString msgId, int bSuc);
	void postNotifyRemoveSession(QString sessionId);
	void postNotifyReadSession(QString sessionId);
    //发送按键的快捷键变化
	void postNotifySendHotKeyChanged(const QString &key);
    //通过快捷键截图完成
    void postNotifyFinishedScreenShotByShortCut();
	//消息回执
	void connnectNotifyMessageback(const QObject * receiver);
    //转发
	void postNotifySendForward(QList<TNMessageListAdapter> listAdapter);
	//切换当前名片
	void postNotifyCurrentFeedChanged(const QString &feedID);

    void postNotifyCreateGroupChatFinished(TNMessageListAdapter session);
    void postNotifyCreateToChat(const QJsonObject &json);
	void postNotifyReMarkUpdate(const QString &from,const QString &to,const QString &reMark,int sources);
	void postNotifyOrgCommunicationStatus(const QString &feedId, const QString &status);
	void postNotifyKeyEventDis(int keyEvent);

private:
    static TNNotifyCenter *_instance;
signals:

    void notifyNetStatus(int netStatus);
	void notifyRefresh(QString type, int statCode, const QString statDesc, TNMsgData msgData);
	void notifyRefresh(QString type, TNNoticeInfo& msgData);
	void notifyRefresh(int refreshType, QList<UINotifyData> dataList);
	void notifyRefresh(QStringList sessionIds);
	void notifyRefeshRevert(int resultType, int msgType, qint64 msgTime,const QString &sessionId, const QString &msg, const QString &content);
	void notifyOffMsg(int count);
	void notifyOnlineMsg(QString msgId, int bSuc);
    void notifyResource(const QString resID,int statCode, QVariantMap mapData);

	void notifyRemoveSession(QString sessionId);
	void notifyReadSession(QString sessionId);
    void notifyCheckVersionFinished(
        bool isNeedUpgrade, 
        bool isForceUpgrade,
        QString downLoadURL,
        int nCheckType,
        QString versionDesc
        );
	void notifySendHotKeyChanged(const QString &key);
    void notifyFinishedScreenShotByShortCut();
	void notifySendForward(QList<TNMessageListAdapter> listAdapter);
	void notifyCurrentFeedChanged(const QString &feedID);
	void notifyKeyEventDis(int keyEvent);

    void createGroupChatFinished(TNMessageListAdapter session);
    void notifyCreateToChat(const QJsonObject &json);
	/*
	from永远是对方，to永远是自己
	*/
	void notifyReMarkUpdate(const QString &from, const QString &to, const QString &reMark,int sources);
	void notifyOrgCommunicationStatus(const QString &feedId, const QString &status);
    void signalHideGroupChatMemberWidget();
    void signalShowHomePageButton();
    void signalListAreaVisible(bool visible);
};

#endif // CGDNOTIFYCENTER_H
