//
// Created by juzenhon on 2017/8/30.
//

#ifndef TMTP_CTNHTTPBIZAPI_H
#define TMTP_CTNHTTPBIZAPI_H

#include <string>
#include <map>
#include <vector>
#include <stdint.h>
#include <functional>

using namespace std;

namespace toonim {

    typedef std::function<void(int, const char *, void *)> HttpCallback;

    class Feed {
    public:
        void serialize(void *writerJson);

        std::string _feedId;
        std::string _avatarId;
        std::string _title;
        std::string _userId;
    };


    class ITnGroupChat
    {
    public:
        ITnGroupChat(){}
        virtual ~ITnGroupChat(){}


        /**
         * 创建群聊
         * @param feed 创建者的feed
         * @param groupChatName 群聊名称
         * @param member 初始成员
         * @param response 回调函数
         * @param userData 用户传递的数据,内部不做任务处理,会回调给callback中的最后一个参数
         */
        virtual void createGroupChat(Feed &feed, const char *groupChatName, vector<Feed> &member,
                                     HttpCallback response,
                                     void *userData) = 0;


        /**
         * 获取用户已加入的群聊
         * @param userId 用户Id
         * @param response 回调函数
         * @param userData 用户传递的数据,内部不做任务处理,会回调给callback中的最后一个参数
         */
        virtual void obtainAllGroupChat(const char *userId, HttpCallback response, void *userData) = 0;


        /**
         *  群聊消息免打扰
         * @param feedId feedId
         * @param disturbStatus 免打扰
         * @param groupChatId 群聊Id
         * @param response 回调函数
         * @param userData 用户传递的数据,内部不做任务处理,会回调给callback中的最后一个参数
         */
        virtual void changeDisturb(const char *feedId, const char *groupChatId, int32_t disturbStatus,
                                   HttpCallback response, void *userData) = 0;

        /**
         * 邀请加入群聊
         * @param groupChatId 群聊id
         * @param feedId 我的feedId
         * @param myName 我的名字
         * @param source 来源
         * @param member 邀请加入的来源
         * @param response 回调函数
         * @param userData 用户传递的数据,内部不做任务处理,会回调给callback中的最后一个参数
         */
        virtual void addGroupChatMember(int64_t groupChatId, const char *feedId, const char *myName,
                                        int32_t source,
                                        vector<Feed> &member, HttpCallback response, void *userData) = 0;
        /**
         * 获取群聊成员列表
         * @param groupChatId 群聊Id
         * @param response 响应回调
         * @param userData 用户数据
         */

        virtual void obtainMembersByGroupChatId(const char *groupChatId, HttpCallback response,
                                                void *userData) = 0;


        /**
         * 获取每张名片所在的群聊
         * @param feedIdList 名片列表
         * @param userId 用户Id
         * @param response 响应回调
         * @param userData 用户数据
         */
        virtual void obtainGroupChatsByFeedIds(vector<string> &feedIdList, const char *userId,
                                               HttpCallback response,
                                               void *userData) = 0;


        /**
         * 退出群聊
         * @param groupChatId 群聊Id
         * @param feedId  名片Id
         * @param response 响应回调
         * @param userData 用户数据
         */

        virtual void exitGroupChat(const char* groupChatId, const char *feedId, const char *title,
                                   HttpCallback response,
                                   void *userData) = 0;


        /**
         * 批量移除群成员
         * @param groupChatId  群聊Id
         * @param removeList 移除成员列表
         * @param response 回调函数
         * @param userData 用户传递的数据,内部不做任务处理,会回调给callback中的最后一个参数
         */
        virtual void removeGroupChatMembers(const char *feedId, const char *title, int64_t groupChatId,
                               vector<Feed> &removeList, HttpCallback response, void *userData) = 0;

        /**
         * 批量移除feed下所有群聊
         * @param feedId 名片Id
         * @param userId 用户Id
         * @param title 名片昵称
         * @param response 回调函数
         * @param userData 用户传递的数据,内部不做任务处理,会回调给callback中的最后一个参数
         */
        virtual void removeGroupChatMembersByFeedId(const char *feedId, const char *userId, const char *title,  HttpCallback response,
                                                    void *userData) = 0;

        /**
         * 修改群聊名称
         * @param groupChatId 群聊Id
         * @param newGroupName 群聊名称
         * @param myFeedId 我自己feedId
         * @param myName 我的名称
         * @param response 回调函数
         * @param userData 用户传递的数据,内部不做任务处理,会回调给callback中的最后一个参数
         */
        virtual void updateGroupChat(int64_t groupChatId, const char *newGroupName, const char *myFeedId,
                        const char *myName, HttpCallback response, void *userData) = 0;

        /**
         * 批量获取群聊信息
         *
         * @param groupChatIdList 要获取的群成员信息
         * @param response 回调函数
         * @param userData 用户传递的数据,内部不做任务处理,会回调给callback中的最后一个参数
         */
        virtual void obtainGroupChatInfo(vector<string> &groupChatIdList, HttpCallback response,
                                         void *userData) = 0;
        
        /**
         群主转让

         @param groupChatId 群聊id
         @param feedId 我自己的feedid
         @param title 我自己的title
         @param memberFeed 转让的群成员信息（avatarId，feedId，title，userId）
         */
        virtual void groupChatTransferOwner(int64_t groupChatId, const char* feedId, const char* title, toonim::Feed memberFeed, HttpCallback response, void *userData) = 0;

        /**
         群聊设置申请审核

         @param groupChatId 群聊id
         @param verityStatus 审核开关
         */
        virtual void setupGroupChatVerify(int64_t groupChatId, int32_t verityStatus, HttpCallback response, void *userData) = 0;

    };

    class ITnSettings {

    public:
        ITnSettings(){}
        virtual ~ITnSettings(){}
        
        /**
         * 设置置顶的session
         * @param chatId 单聊时为好友的feedid，群聊时为群聊topic，应用时为appid
         * @param myFeedId 单聊时为我的feedid，群聊和通知为空
         * @param timestamp 时间戳
         * @param response 响应回调
         * @param userData 用户数据
         */
        virtual void setSessionSwitchTop(const char *chatId, const char *myFeedId, int32_t chatType,
                                         bool top, int64_t timestamp, HttpCallback response,
                                         void *userData) = 0;

        /**
         * 获取所有置顶的session
         * @param timestamp 时间戳
         * @param response 响应回调
         * @param userData 用户数据
         */
        virtual void getAllSwitchTopSession(int64_t timestamp, HttpCallback response, void *userData) = 0;

        /**
        *
        * @param response response
        * @param userData userData
        */
        virtual void obtainAppListInfo(HttpCallback response, void *userData) = 0;
        
        /**
         根据appid获取应用信息
         
         @param appId appId
         @param response response
         @param userData userData
         */
        virtual void obtainAppInfo(const char *appId, HttpCallback response, void *userData) = 0;
        
        /**
         设置单聊免打扰和黑名单

         @param feedId 操作者feedId
         @param passiveFeedId 被操作者feedid
         @param passiveUserId 被操作者的userid
         @param bizType 类型，1黑名单，2免打扰
         @param response response
         @param userData userData
         */
        virtual void switchOnDisturbAndBlackList(const char *feedId, const char *passiveFeedId, const char *passiveUserId, int32_t bizType, HttpCallback response, void *userData) = 0;
        
        /**
         设置单聊免打扰和黑名单
         
         @param feedId 操作者feedId
         @param passiveFeedId 被操作者feedid
         @param passiveUserId 被操作者的userid
         @param bizType 类型，1黑名单，2免打扰
         @param response response
         @param userData userData
         */
        virtual void switchOffDisturbAndBlackList(const char *feedId, const char *passiveFeedId, const char *passiveUserId, int32_t bizType, HttpCallback response, void *userData) = 0;
        
        
        /**
         增量更新获取单聊免打扰和黑名单

         @param response response
         @param userData userData
         */
        virtual void querySwitchDisturbAndBlackList(HttpCallback response, void *userData) = 0;
    };

    
    
    /**
     * 初始化http业务接口
     * @param clientId userId
     * @param token 用户登录token
     * @param deviceId deviceId
     * @param toonType toonType
     * @param version app版本号
     * @param platformVersion  系统版本号"iOS 10.2.1"
     */
    void initHttpBiz(const char* clientId, const char* token, const char* deviceId,
                              int32_t toonType, const char* version, const char* platformVersion,const char* cerPath="");
    
    
    /**
     * 添加HTTP 业务用到的MLB
     * @param domain 域名
     * @param url 对应的真实URL
     */
     void appendHttpRouter(const char* domain, const char* url);
        
    ITnGroupChat* getGroupChat();
    ITnSettings* getSettings();

#define TNCBIZ_GROUPCHAT  toonim::getGroupChat()
#define TNCBIZ_SETTINGS   toonim::getSettings()

}

#endif //TMTP_CTNHTTPBIZAPI_H
