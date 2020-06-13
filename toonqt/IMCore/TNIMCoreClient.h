#ifndef TNIMCORECLIENT_H
#define TNIMCORECLIENT_H
#include "imcore_global.h"
#include <QString>
#include <QThread>
#include "common_global.h"
#include "LocalStorageCommon.h" 
#include "TNIMNoticeProcessor.h"
#include "TNNetDetecter.h"
using namespace toonim;
class CTNIMClientTNMP;
class TNCMessage;
class TNDataControlServer;
class TNIMCoreProcessor;
class TNNoticeUpdater;
class TNIMMsgManager;
namespace toonim
{
	class CTNMessage;
	class ITnImDBChat;
	class CTNSession;
}
//拉历史消息使用字段描述：
//type： TYPE_GROUP_CHAT_MSGREQ，TYPE_GROUP_NOTIFY_REQ，TYPE_MSG_GROUP_OPERATE 时，type、to字段生效，to填群Id
//type： TYPE_SYNC_MSGREQ，type字段生效
//type： TYPE_NOTIFY_MSGREQ，type、from字段生效，from填服务端AppId
//type： TYPE_SINGLE_CHAT_MSGREQ，TYPE_MSG_SINGLE_OPERATE，type、from、to字段生效，from、to：填名片Id，不区分谁发 谁收
class IMCORE_EXPORT TNIMCoreClient : public QObject
{
	Q_OBJECT
private:
	TNIMCoreClient();
public:
	~TNIMCoreClient();
	static TNIMCoreClient* GetIMClient();
	static void DestoryIMClient();
	static void MessageCastToData(const st_BMessage0Ptr bmessage, st_MsgData& data); 
	static void IMMessageCastToData(const CTNMessage& imMessage, st_MsgData& data);
	static void IMSessioniCastToData(const CTNSession& imMessage, st_Session& data);
    static void ParseContextToMsgData(const QString& content, int type, TNMsgData& data);
    static QString GetSessionId(const QString& from, const QString& to, MSG_BIZ_TYPE type);
	static QString GetMsgId();
	static ITnImDBChat* GetDBChat();
	static void BMessageCastToIMMessage(const st_BMessage0Ptr bmessage, CTNMessage& imMessage);
	static void BSessionCastToIMSession(const st_SessionPtr bSession, CTNSession& imSession);
public:
	void InitIM(TNPluginParamPtr pluginParm);
	void Init(QString& userId, QString& deviceId, QString& hostSSL, QString& host);
	void AddIMServerAddr(QString& host, bool isSSL);
	int IMLogin(QString& username, QString& userToken);
	int IMLogout();
	
	int PreSaveIMMessage(TNMsgData* msgData, bool singChat = true);
	int SendIMMessage(TNMsgData* msgData, bool singChat = true);
	int SendIMMessageInner(TNMsgData* msgData, bool singChat, bool bSend = true);
	int SendForwardMessage(TNMsgData* msgData, QMap<QString, QString>& feedList);
	int SendForwardMessageInner(TNMsgData* msgData, QMap<QString, QString>& feedList);
	int SendRevokeMessage(TNRevokeData* msgData, bool singChat = true);
	int SendRevokeMessageInner(TNRevokeData* msgData, bool singChat);
	void SendReadSessionInner(QString readSessionId);
	//从服务器拉取历史记录
	void RequestOffMsg(TNOffMsg& offMsg);
	//增量更新数据库
	void UpdateAddressBookFromServer();
	//将unread 置0
	void ReadSession(const QString& sessionId);
	void RemoveAndReadSession(const QString& sessionId);
	//本地已读
	void ReadSessionLocal(const QString& sessionId);
    void ReadMsg(const QString& msgId, QString sessionId);
    bool SaveDraft(const QString& sessionId, const QString& strDraft);
    void SetMsgFileStatus(const QString& msgId, const QString& sessionId, TNMsgFileStatus fileStatus, QString upUrlPath = QString(""), bool bUpSuc = true);
    void SetMsgSendStatus(const QString& msgId, const QString& sessionId, TNMsgStatus sendStatus);
	//返回会话类型，如果是通知则返回appinfo信息。
	MSG_BIZ_TYPE GetSessionType(const st_SessionPtr session, st_MessageAppInfoPtr& appInfo);	
    MSG_BIZ_TYPE GetSessionType(const CTNSession* session);
    void GetNoticeListFromSessionId(QList<st_NoticeInfo>& noticeList, const QString& sessionId, qlonglong seqId = 0, int msgCount = 20);
    void SynicGroupChatMember(QString strGroupId);
	void SynicGroupChat();
	CTNIMClientTNMP* GetClientTNMP(){ return _clientImpl; }
public slots:
	void onSendNetDetectStatus(NetStatus status);
	void UpdateOrgGroupAndRelationSlots();
	void UpdateFriendReMarkSlots(const QString &from, const QString &to);
private:
	//更新发送状态，将上次发送中置为发送失败
	void ResetSendStatus();
	int SendIMMessage(TNCMessage* message, QString toClientId, bool bSend = true);
	void GetTNCMessage(TNMsgData* msgData, TNCMessage& message, bool singChat = true);
	bool GetReadSessionData(QString sessionId, TNReadSession& readSession);
private:
	CTNIMClientTNMP*			_clientImpl;
	TNIMMsgManager*				_msgManager;
	TNNetDetecter*				_netDetecter;
	NetStatus					_lastNetStatus;
	QString						_userName;
	QString						_userToken;
	bool						_bLogined;		//是否已经登录
};
#endif

