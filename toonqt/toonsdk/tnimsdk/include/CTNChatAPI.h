#ifndef _TOON_IMSDK_TNIMSDK_H
#define _TOON_IMSDK_TNIMSDK_H

#include <string>
#include "CTNDBHeader.h"
#include <stdint.h>
#include <map>

using namespace std;


namespace toonim {
    
    
    
    /**
     * TMTP回调接口
     */
    class ITnImSdkCallback
    {
    public:
        virtual ~ITnImSdkCallback(){}
        
        /**
         * 网络状态变
         * @param status 网络状态，未连接，已连接，收取中，断开
         */
        virtual void netStatusChanged(int32_t status) = 0;
        /**
         * 登录响应
         * @param code 错误码，0 为成功，
         * @param contentTypes 禁止扩展contentType列表
         */
        virtual void loginResp(int32_t code,vector<int32_t>& contentTypes) = 0;
    
        /**
         * 被踢出
         */
        virtual void kickOut() = 0;
        /**
         * 热会话响应
         */
        virtual void hotSessionResp(set<CTNOffMessageResult> &sessionSet) = 0;
        /**
         * 离线消息响应
         * sessionId离线消息 sessionId
         */
        virtual void offMsgResp(set<CTNOffMessageResult> &sessionSet) = 0;
        /**
         * 收到在线消息
         * @param message 消息内容
         */
        virtual void msgRecv(CTNMessage *message) = 0;
        /**
         * 收到同步消息
         * @param message 消息内容
         */
        virtual void syncMessage(CTNMessage *message, int32_t isOnline) = 0;
        /**
         * 收到通知消息
         * @param message 消息内容
         */
        virtual void noticeMessage(CTNMessage *message, const char * broadcast, int32_t isOnline) = 0;
        /**
         * 收到（发送）操作类型消息，
         * @param message 消息内容
         * @param success 发送成功，true 成功，false失败
         */
        virtual void messageOperate(CTNMessage *message, bool success) = 0;
        /**
         * 同步未读数响应
         * @param sessionId 会话Id
         */
        virtual void syncSessionStatusResp(const char * sessionId) = 0;
        /**
         * 收到同步未读数请求
         * @param sessionId 会话Id
         */
        virtual void syncSessionStatusReq(const char * sessionId) = 0;
        /**
         * 发送消息响应
         * @param sessionId 会话Id
         * @param msgId msgId
         * @param seqId seqId
         * @param result 0 成功，非0 失败；
         */
        virtual void msgAck(const char * sessionId, const char * msgId, int64_t seqId, int32_t result) = 0;
        /**
         * SDK 向上发送的通知
         * @param broadcast 通知名称
         * @param userInfoJson 附加json字符串
         */
        virtual void notificationCenter(const char* broadcast, const char* userInfoJson = NULL) = 0;
        
    
        /**
         * 用户在线状态变化通知
         * @param mapClientStatus 对应表 {用户名 在线状态} 0 不在线，1在线
         */
        virtual void userOnlineStatus(std::map<string, int32_t> &mapClientStatus) = 0;
        
        
        /**
         埋点回调

         @param atrNamax 埋点的模块
         @param property 埋点的数据，key value
         */
        virtual void daInfo(const char* atrNamax, map<string, string> & property) = 0;
		virtual void syncGroupchat(CTNMessage *message) = 0;
    };
    
    class ITnImSdk
    {
    public:
        virtual ~ITnImSdk(){}
        
        /**
         * 增加过滤的通知类型，加入此名单后，通知中心不保存会话和消息，直接通过通知方式转移到其他业务模块
         * @param catalogId 通知catalogId
         * @param subCatalogId catalogId 下的subCatalogId，如果为空，只比对catalogId；
         * @param broadcast 通知名称
         */
        virtual void addNoticeFilter(int catalogId, std::vector<int32_t>& subCatalogId, const char * broadcast) = 0;
        
        /**
         * 增加IM 服务器ip地址和端口
         * @param host ip地址
         * @param port 端口
         * @param isSSL 是否支持ssl连接
         */
        virtual void addHostInfo(const char * host, int32_t port, bool isSSL) = 0;
        
        /**
         更新clientInfo的feedList
         
         @param feedList feedList
         */
        virtual void updateMyFeedList(vector<std::string>& feedList) = 0;
        
        
        /**
         * 设置SDK 回调指针
         * @param callback 回调接口指针
         */
        virtual void setCallback(ITnImSdkCallback* callback) = 0;
        /**
         * 登录
         * @param name 用户名，可以不填写
         * @param password 密码，必须填写token
         */
        virtual int32_t login (const char * name, const char * password) = 0;
        /**
         * 登出
         * @param notifyServer 是否向server发送数据报文
         */
        virtual int32_t logout (bool notifyServer) = 0;
        /**
         * 发送消息
         * @param message 消息体
         */
        virtual int32_t sendMessage (CTNMessage* message) = 0;
        /**
         * 撤回消息
         * @param sessionId 会话Id
         * @param msgId 消息Id
         * @param operatorFeedId 操作者feedId
         * @param operatorName 操作者名称
         */
        virtual int32_t revokeMessage(const char * sessionId ,const char * msgId, const char * operatorFeedId, const char * operatorName) = 0;
        /**
         * 获取网络状态
         */
        virtual int32_t getNetStatus() = 0;
        /**
         * 同步总未读数或者push token
         * @param unreadCount 总未读数，小于零表示不更新
         * @param pushToken apns token 不填写表示不更新
         */
        virtual void reqSync(int32_t unreadCount, const char * pushToken) = 0;
        /**
         * 解散群聊
         * @param groupId 群聊Id
         */
        virtual void dissolveGroup(int64_t groupId) = 0;
        /**
         * 同步会话未读数
         * @param sessionId 会话Id
         */
        virtual void reqSyncSessionStatus(const char* sessionId) = 0;
        
        /**
         * 客户端数据统计警报传输接口，仅供IM使用
         * @param type 类型：1，云存储
         * @param content 内容：json串
         */
        virtual void clientReport(int32_t type,const char* content) = 0;
        
        /*订阅组织，用户属于哪个组织需要传输，
        * @param vctOrgId组织Id列表
        * 此接口用来接收用户在线状态使用，只有调用此接口后才能收到组织内其他用户的在线状态通知信息
        */
        virtual void subOrganize(vector<string> &vctOrgId) = 0;
        
     };
    
    
    /**
     * 日志记录接口
     */
    class ITnIMLog{
    public:
        virtual ~ITnIMLog(){}

        /**
         * 写日志
         * @param logs 日志内容
         */
        virtual void writeLog(const char* logs) = 0;
        
        /**
         * 获取日志文件名称及路径
         * @return 日志文件路径及名称 外部必须释放 返回字符串内存
         */
        virtual const char* getLogFileName() = 0;
        
    };
    
    /**
     * 初始化日志模块
     * @param appPath 日志保存路径
     */
    void initLog(const char* appPath);
    /**
     * 获取日志接口实例，调用此接口前必须调用 initLog
     */
    ITnIMLog* getLogInstance();
    
    /**
     * 初始化IM 模块
     * @param clientInfo IM 所需要的参数
     */
    ITnImSdk* initIm(CTNClientInfo &clientInfo);
    
  
    /**
     * 获取IMSDK IM模块实例
     * 调用此函数前必须调用 initIm接口
     */
    ITnImSdk* getImSDK();

}
#endif
