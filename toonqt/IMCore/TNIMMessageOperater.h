#ifndef TNIMMESSAGEOPERATER_H
#define TNIMMESSAGEOPERATER_H
class TNCMessage;
class TNIMMessageOperater
{
public:
	TNIMMessageOperater();
	~TNIMMessageOperater();
public:
	//撤销消息处理
	bool ProcessMessageRevert(TNCMessage* msg);
	//聊天消息撤销过滤,只在离线时候处理
	void ProcessChatMsgFilterRvert(TNCMessage* msg);
	//设置撤销消息pushinfo
	void SetRevertMessagePushInfo(TNCMessage* msg);
	bool IsRevertMsg(TNCMessage* msg);
private:
	bool SaveMsgToMessageOperate(TNCMessage* msg);
	
};
#endif

