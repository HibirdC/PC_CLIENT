#ifndef TNIMMSGMANAGER_H
#define TNIMMSGMANAGER_H
#include <QObject>
#include "TNIMCoreProcessor.h"
#include "CTNDBHeader.h"
class TNIMReadSessionManager;

class TNIMMsgManager : public QObject
{
	Q_OBJECT
public:
	TNIMMsgManager();
	~TNIMMsgManager();
public:
	//在线
	void ProcessMsgRecv(int type, toonim::CTNMessage* req);
	//热会话处理
	//void ProcessHotSession(Toon::HotSessionResp* hotSessions);
	//离线
	//void ProcessMsgOff(Toon::OffMsgCountResp* offMsgCount);
	//历史记录
	//void ProcessMsgHistory(Toon::OffMsgResp* offMsg);
	//消息回执
	void ProcessMsgAck(const QString& msgId, uint64_t seqId, int status);
	//预存消息
	void PreSaveMsgInThread(TNMsgData* msgData, bool singChat);
	//发送普通消息
	void SendMsgInThread(TNMsgData* msgData, bool singChat);
	//发送撤销消息
	void SendRevertMsgInThread(TNRevokeData* msgData, bool singChat);
	//转发消息
	void SendForwardMsgInThread(TNMsgData* msgData, const QMap<QString, QString>& feedList);
	//发送本端会话已读状态
	void SendSyncReadSessionInThread(const QString& readSessionID, bool bRemoveSession = false);
	//发送离线已读状态
	void SendOfflineReadSessionInThread();
    //等待所有消息处理结束
    void waitAllMsgOver();
	//只更新会话信息,不更新数据库
	bool UpdateSessionTitle(toonim::CTNSession& session);
	QString GetOtherFeed(const QString& sessionId, const QString& myFeedId);
	TNIMCoreProcessor* GetIMProcessor(){ return _msgProcessor; }
	TNIMReadSessionManager* GetReadSessionManager(){ return _readManager; }
signals:
    void waitOver();
    void allOver();
	void ProcessMsgRecvSign(int type, toonim::CTNMessage req);
	//void ProcessHotSessionSign(Toon::HotSessionResp hotSessions);
	//void ProcessMsgOffSign(Toon::OffMsgCountResp offMsgCount);
	//void ProcessMsgHistorySign(Toon::OffMsgResp offMsg);
	void ProcessMsgAckSign(QString msgId, uint64_t seqId, int status);
	void SendMsgSign(TNMsgData msgData, bool singChat, bool bSend);
	void SendRevertMsgSign(TNRevokeData msgData, bool singChat);
	void SendForwardMsgSign(TNMsgData msgData, QMap<QString, QString> feedList);
	void SendReadSessionSign(QString readSessionID, bool bRemoveSession);
	void SendOfflineReadSign();
private slots:
    void sendAllOverSignal();
public slots:
	void ProcessMsgRevcSlot(int type, toonim::CTNMessage req);
	//void ProcessHotSessionSlot(Toon::HotSessionResp hotSessions);
	//void ProcessMsgOffSlot(Toon::OffMsgCountResp offMsgCount);
	//void ProcessMsgHistorySlot(Toon::OffMsgResp offMsg);
	void ProcessMsgAckSlot(QString msgId, uint64_t seqId, int status);
	void SendMsgSlot(TNMsgData msgData, bool singChat, bool bSend);
	void SendRevertMsgSlot(TNRevokeData msgData, bool singChat);
	void SendForwardMsgSlot(TNMsgData msgData, QMap<QString, QString> feedList);
	void SendReadSessionSlot(QString readSessionID, bool bRemoveSession);
private:
	TNIMCoreProcessor*			_msgProcessor;
	QThread						_threadMsgProcessor;
	TNIMReadSessionManager*		_readManager;
};
#endif

