#ifndef TNIMSDKCLIENT_H
#define TNIMSDKCLIENT_H
#include "CTNChatAPI.h"
using namespace toonim;
class TNIMMsgManager;
class TNIMSDKClient : public ITnImSdkCallback
{
public:
	TNIMSDKClient(TNIMMsgManager* msgManager);
	~TNIMSDKClient();
	/**
	* 网络状态变
	* @param status 网络状态，未连接，已连接，收取中，断开
	*/
	void netStatusChanged(int32_t status);
	/**
	* 登录响应
	* @param code 错误码，0 为成功，
	* @param contentTypes 禁止扩展contentType列表
	*/
	void loginResp(int32_t code, vector<int32_t>& contentTypes);

	/**
	* 被踢出
	*/
	void kickOut();
	/**
	* 热会话响应
	*/
	void hotSessionResp(set<CTNOffMessageResult> &sessionSet);
	/**
	* 离线消息响应
	* sessionId离线消息 sessionId
	*/
	void offMsgResp(set<CTNOffMessageResult> &sessionSet);
	/**
	* 收到在线消息
	* @param message 消息内容
	*/
	void msgRecv(CTNMessage *message);
	/**
	* 收到同步消息
	* @param message 消息内容
	*/
	void syncMessage(CTNMessage *message, int32_t isOnline);
	/**
	* 收到通知消息
	* @param message 消息内容
	*/
	void noticeMessage(CTNMessage *message, const char * broadcast, int32_t isOnline);
	/**
	* 收到（发送）操作类型消息，
	* @param message 消息内容
	* @param success 发送成功，true 成功，false失败
	*/
	void messageOperate(CTNMessage *message, bool success);
	/**
	* 同步未读数响应
	* @param sessionId 会话Id
	*/
	void syncSessionStatusResp(const char * sessionId);
	/**
	* 收到同步未读数请求
	* @param sessionId 会话Id
	*/
	void syncSessionStatusReq(const char * sessionId);
	/**
	* 发送消息响应
	* @param sessionId 会话Id
	* @param msgId msgId
	* @param seqId seqId
	* @param result 0 成功，非0 失败；
	*/
	void msgAck(const char * sessionId, const char * msgId, int64_t seqId, int32_t result);
	/**
	* SDK 向上发送的通知
	* @param broadcast 通知名称
	* @param userInfoJson 附加json字符串
	*/
	void notificationCenter(const char* broadcast, const char* userInfoJson = NULL);


	/**
	* 用户在线状态变化通知
	* @param mapClientStatus 对应表 {用户名 在线状态} 0 不在线，1在线
	*/
	void userOnlineStatus(std::map<string, int32_t> &mapClientStatus);


	/**
	埋点回调

	@param atrNamax 埋点的模块
	@param property 埋点的数据，key value
	*/
	void daInfo(const char* atrNamax, map<string, string> & property);

	void syncGroupchat(CTNMessage *message);
private:
	void processOffLineSession(set<CTNOffMessageResult> &sessionSet);
private:
	TNIMMsgManager*	_msgManager;
};
#endif