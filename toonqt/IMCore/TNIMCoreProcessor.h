#ifndef CTNIMCOREPROCESSOR_H
#define CTNIMCOREPROCESSOR_H
#include "ITNMPResponse.h"
#include "imcore_global.h"
#include <QString>
#include <QThread>
#include <qmap.h>
#include "common_global.h"
#include "tmtp.h"
#include "qobject.h"
#include "LocalStorageCommon.h"
namespace toonim
{
	class CTNMessage;
}
class TNDataControlServer;
class TNCMessage;
class TNNoticeUpdater;
class TNIMMessageOperater;
struct TNSessionItem
{
	QString sessionId;
	QString lastMsgId;
	int unReadCount;
	int readSeqId;
	qlonglong upSeqId;
	qlonglong downSeqId;
	qlonglong currentPullSeqId;
	//会话时否完成未读数统计
	bool bFinishReadCount;
	//会话是否完成取出最后一条消息
	bool bFinishLastMsg;
	bool bHasAtMeMsg;
	TNSessionItem(){
		unReadCount = 0;
		readSeqId = 0;
		bFinishReadCount = false;
		bFinishLastMsg = false;
		bHasAtMeMsg = false;
		lastMsgId = "";
	};
};
class TNIMCoreProcessor : public QObject
{
	Q_OBJECT

public:
	TNIMCoreProcessor();
	~TNIMCoreProcessor();
public:
	void ProcessMsgRevc(int type, Toon::MsgReq* req);
	//在线消息
	TNCMessage* ProcessOnLineMsg(int type, Toon::MsgReq * onLineMsg, bool isFromMyself = false);
	//热会话消息
	//void ProcessHotSessionSlot(Toon::HotSessionResp* hotSessions);
	//离线消息
	//void ProcessOffLineMsg(Toon::OffMsgCountResp* offLineMsgs);
	//拉取历史消息
	//void ProcessHistoryMsg(Toon::OffMsgResp* historyMsgs);
	//处理发送消息回执
	void ProcessSendMsgAck(QString& msgId, uint64_t seqId, int status);
	//处理群聊消息数据同步
	void ProcessChatSyncMsg(const QString& msgId, int catalogId, QString content);
	//是否需要显示的同步消息
	static bool ShouldShowSyncMsg(int  catalogId, QString content);
	//处理同步消息
	void ProcessSyncMsg(int catalogId);
	//发送消息预存
	void PreSaveSendMsg(TNCMessage* message);
	//更新消息状态
	void UpdateMsgStatus(QString& msgId, MSG_STATUS status);
	//开启增量更新数据线程
	void StartUpdateDbThread();
	//增量更新组织关系和组织
	void UpdateOrgGroupAndRelation();
	//增量更新群组成员
	void SynicGroupChatMember(QString& strGroupId);
	void SynicGroupChat();
	bool ShouldShowMessage(TNCMessage* message);
	bool ShouldShowMessage(toonim::CTNMessage* message);
	//更新新的朋友通知
	void updateNewFriendNotice();
	qlonglong GetLocalMaxSeqId(QString sessionId);
	//更新备注
	void UpdateFriendReMark(const QString &from, const QString &to);

signals:
	void SendHistoryMsgReq(TNOffMsg offMsg);
public slots:
	void OnSendHistoryMsgReq(TNOffMsg offMsg);
private:
	TNCMessage* storageOneMsgFromIM(int type, Toon::MsgReq* msg, bool isFromMyself = false, bool bOnline = true);
	//保存单个消息
	void SaveMsgToDB(TNCMessage* message, bool bSendMsg = false);
	void MsgDbToMessage(st_BMessage0Ptr dbMessage, TNCMessage& message);
	void requestUnDownLoadOffMsg(qlonglong maxSeqId, qlonglong maxTimeStmp, qlonglong minSeqId, TNCMessage* message);
	void ProcessChatSyncMsg(TNCMessage* msg);
	void SyncMyGroupInfo(int type, QString& content);
	void SynicMyGroupMember(int type, QString& content);
	//处理159消息，同步组织名片可配置状态 2018.1.29 王志勇添加
	void synicOrgCommunication(int type,const QString&content);
	void ProcessIsMyself(TNCMessage& message);
	void storageSessioFromIM(int type, int unReadCount, TNCMessage* lastMsg);
	QString genSessionIdFromServerMsg(Toon::OffMsgItem& msgItem);
public:
	QMap<QString, TNSessionItem*>	_sessionItems;
	TNNoticeUpdater*				_noticeUpdate;
	QThread							_threadUpdater;
	TNIMMessageOperater*			_messageOperate;
};
#endif

