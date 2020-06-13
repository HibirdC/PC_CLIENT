#ifndef NOTICELISTMODEL_H
#define NOTICELISTMODEL_H

#include <QMutex>
#include "TNTableModel.h"
#include "TNMessageListAdapter.h"
#include "LocalStorageCommon.h"
#include "NoticeEnum.h"
#include "imcore_global.h"

class TNOutLineMessageThread;
class TNSessionNetWork;
namespace toonim {
struct CTNSession;
struct CTNMessage;
}

class NoticeListModel : public TNTableModel
{
    Q_OBJECT
public:
    NoticeListModel(QObject* parent=NULL);
    ~NoticeListModel();
    //从数据库读取会话数据,参数传名片信息
    void init_data(QString feedId=AVATAR_ALL_FEED);
    /*
     *插入数据,返回插入的位置
     *isSelected会话被选中
     *autoAddUnread在线消息自增未读条数
     *isSend自己发送的消息
    */
    int prependData(TNMessageListAdapter adapter,
        TNMessageListAdapter** destData,
        bool isSelected = false,
        bool autoAddUnread = true,
        bool isSend = false,
        bool isBubble = true);
    /*
     * 判断会话在Model中是否是第一条会话(包括置顶的情况)
    */
    bool isTop(const TNMessageListAdapter& adapter,
        TNMessageListAdapter** topItemData,
        int& index,
        bool isSelected = false,
        bool autoAddUnread = true,
        bool isSend = false,
        bool isBubble = true);
    /*
     *删除会话
    */
    void removeSession(QModelIndex q_index);
    bool removeRowBySessionId(const QString& sessionId);
    bool removeSession(const QString& sessionId, bool isSelect);
    void incrementalSession(QStringList listSession);
    void incrementalSession(const QString& sessionId);
    void incrementUnreadCount(const QString &sessionId);
    void setUnreadCount(const QModelIndex &index, int count);
    int  setUnreadCount(const QString& sessionId, int count);
    int  getUnreadCount(const QModelIndex &index);
    int  getUnreadCount(const QString& sessionId);
    //设置有人@你的状态
    int setSomeoneAtYou(const QString& sessionId,bool isAt);
    //手动置顶
    void manulOnTopSession(QModelIndex q_index);
    //取消置顶
    int manulCancelTopSession(QModelIndex q_index);
    //手动更新群聊名称
    void manulModifySessionName(const QString& session_id,const QString& name);
    //设置/取消免打扰
    void manulSetSessionAlarm(QModelIndex q_index,bool noAlarm);
    void manulSetSessionAlarm(const QString& sessionId, bool noAlarm);
    //更新会话active状态
    bool updateActive(const QString& sessionId, bool isActive);
    //feed更新后,更新会话
    bool updateSessionByFeedId(const QString& feedId,const QString& avatorUrl,const QString& name);
    //更新userId,单聊发送消息
    void updateSessionUserIdByFeedId(const QString& feedId,const QString& userId);
    //更新头像
    void updateSessionAvatarByFeedId(const QString& feedId,const QString& avatorUrl);
    void updateSessionAvatarBySessionId(const QString& sessionId,const QString& avatorUrl);

    void updateAvatarPhoto(const QString& sessionId, const QString& file_path);
    TNMessageListAdapter* updateSessionName(const QString& sessionId, const QString& name);
    //所有会话未读置0
    void setAllSessionReaded();
    //创建会话
    TNMessageListAdapter* createNewSession(const QString& sessionId);
    //查找会话
    int findItemDataBySessionId(const QString &sessionId,
        TNMessageListAdapter **itemData);

    QList<TNMessageListAdapter> getSessionList() const;
    int getScropUnReadItem(int latestItem);
    //设置hotover状态
    void setBackStatus(const QString& session_id,TNMessageListAdapter::Back_Status status);
    //取消选中状态
    void setSessionUnSelected(const QString& session_id);
    //更新备注
    void updateRemark(const QString& sessionId,const QString& remark);
    //更新最后一条消息
    void updateLastMsg(const QString& sessionId);
    //找到item by feedId
    bool findItemDataByFeedId(const QString &feedId,
        std::map<int,TNMessageListAdapter*>& map_itemData);
public Q_SLOTS:
    void onUpdateTotalUnread();
    void onOutLineOperate(TNMessageListAdapter session);
    void on_notifyCurrentFeedChanged(const QString &feedId);
	void on_notifyReMarkUpdate(const QString &from, const QString &to, const QString &remark, int sources);
    void on_notifyOrgCommunicationStatus(const QString& feedId,const QString& status);
Q_SIGNALS:
    void updateTotalUnread();//循环读+总数
    //通知menu界面未读条数
    void messageNumberChanged(int count);
    void manualModifySessionName(QString sessionId, QString name);
    void manualRemoveCurSession(const QString &sessionId,bool isSelected);
    //离线数据重新加载detailsmodel的数据(选中)
    void reLoadDetailsModel(TNMessageListAdapter* adapter);
    void reSelectOutLine(TNMessageListAdapter session, bool isSelect = false,
                         bool isSend = false, bool isActive = true, bool isOnLine = true, bool isBubble = true);
    //离线数据更新外层menu的红点
    void outlineUpdateUnread(const QString& feedId,int unread,int type);
    //更新Tray 离线未读
    void outlineUpdateUnreadTray(TNMessageListAdapter ,int);
    //默认ListNotice背景信号
    void showDefaultBack();
    //手动设置免打扰后， 通知Tray消息
    void manualNoAlarmNotifyTray(const QString & sessionId,bool noAlarm,int unReadCount);
protected:
    Qt::ItemFlags flags(const QModelIndex &index) const;
private:
    //创建session
    TNMessageListAdapter* createNewSession(const toonim::CTNSession* ctn_session);

    void setLastMsg(const QString& lastMsgId, TNMessageListAdapter* itemData);
    void readFeedUserId(const QString& feedID, TNMessageListAdapter* tempAdapter);
    bool setAvatarPhoto(TNMessageListAdapter* itemData, QString& file_path);
    void setSessionLastMsg(MESSAGE_TYPE type,TNMessageListAdapter* adapter, const TNMsgData& msgData);
    void setSessionLastMsg(TNMessageListAdapter *adapter, const st_NoticeInfo &noticeInfo);
    void set_unread_active_status(const TNMessageListAdapter& adapter,
        TNMessageListAdapter* itemData,
        bool isSelected = false,
        bool autoAddUnread = true,
        bool isSend = false,
        bool isBubble = true);

    void insertAt(TNMessageListAdapter* itemData, int index);
    void pushFront(TNMessageListAdapter * itemData);
    void pushBack(TNMessageListAdapter* itemData);

    bool getNoAlarm(const QString& sessionId, const QString& myFeedId,
                    const QString& toFeedId, TNBizType type);

    //会话插入到正确的位置,用于新会话
    void insertSort(const TNMessageListAdapter& session,
                    TNMessageListAdapter** itemData,
                    int& insert_index);
    //会话move到正确的位置,不会删除会话数据,用于已经存在的会话
    void moveSort(TNMessageListAdapter* itemData,int src_index, int& dst_index);
private:
    QMutex 		_mutex;
    TNOutLineMessageThread* _outLineThread;
};

#endif // NOTICELISTMODEL_H
