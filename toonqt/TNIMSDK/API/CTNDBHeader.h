//
//  CTNDBHeader.hpp
//  TNChatLibrary
//
//  Created by 王海涛 on 2017/10/11.
//

#ifndef CTNDBHeader_hpp
#define CTNDBHeader_hpp

#ifdef WIN32
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#endif

#include <stdio.h>

#include <string>
#include <vector>
#include <set>
#include <stdint.h>
#include "CTNIMTypedef.h"
#ifdef __linux__
#include <string.h>
#endif

using namespace std;

namespace toonim
{
    enum CTNSESSIONTYPE
    {
        SESSION_TYPE_TOP = 1,               //置顶version
        SESSION_TYPE_appInfoVersion = 2,    // 应用的更新时间，sessionid为SESSION_TYPE_appInfoVersion
        SESSION_TYPE_ATMESSAGE = 3,         //at消息聚合
        SESSION_TYPE_BLACKLIST = 4,         //黑名单增量更新version
        SESSION_TYPE_FOLLOWMESSAGE = 5,     //关注的人, sessionid对应SESSION_TYPE_ATMESSAGE_feedId
        SESSION_TYPE_BACKGROUND = 6,        //聊天背景
        SESSION_TYPE_ALLGROUPVERSION = 7,   //全部群聊的version，sesionId传入 “SESSION_TYPE_ALLGROUPVERSION”
        SESSION_TYPE_GROUPMEMBERVERSION = 8,    //群成员增量更新version时间戳，sissionId传入 “SESSION_TYPE_GROUPMEMBERVERSION_groupId” groupId为群聊id
        SESSION_TYPE_USERINFO = 9,//wxy 用户历史记录信息
    };
    
    //此类可以删除
    struct CTNSessionName {
        int32_t type;
        string from;
        string to;
        bool isValid () {
            if (from == "" && to == ""){
                return false;
            }
            
            return true;
        }
    };
    

    
//    typedef enum CTNIMMessageType{
//        CTNIMMessageTypeMsgACK = 49,
//        CTNIMMessageTypeGroupNotice = 50,//群业务通知消息 wxy
//        CTNIMMessageTypeBizNotice = 51,
//        CTNIMMessageTypeChat = 52,
//        CTNIMMessageTypeGroupChat = 53,
//        CTNIMMessageTypeSync = 54,
//        CTNIMMessageTypeMoment = 55,
//
//        CTNIMMessageTypeOffMsgCount = 57,
//        CTNIMMessageTypeOffMsgCountResp = 58,
//        CTNIMMessageTypeOffMsg = 60,
//        CTNIMMessageTypeOffMsgResp = 61,
//        CTNIMMessageTypeMsgSingleOperate = 62,
//        CTNIMMessageTypeMsgGroupOperate = 63,
//
//    }CTNIMMessageType;
//
//    enum CTNMessageSendStatus
//    {
//        CTNMessageDraft = 0,
//        CTNMessageSending = 1,
//        CTNMessageSuccess = 2,
//        CTNMessageFailed = 3,
//    };

//    enum CTNMessageFileStatus
//    {
//        CTNFileStatusNotDownload = 1,
//        CTNFileStatusDownloading = 2,
//        CTNFileStatusDownloaded = 3,
//        CTNFileStatusDownloadFailed = 4,
//        CTNFileStatusDownloadCancel = 5,
//
//        CTNFileStatusSended = 6,
//        CTNFileStatusSending = 7,
//        CTNFileStatusSendCancel = 8,
//        CTNFileStatusSendFailed = 9
//    };
    
//    //消息类型：1：文本， 2：语音，3：图片，4：名片，5：位置，6:表情(暂时没用),7：常用信息(暂时没用)，8：收藏,9:常用地址(暂时没用), 10:视频, 11:礼物, 12:gif表情图片, 15:分享
//    enum CTNMessageContentType{
//        CTNChatTypeNone = 0,
//        CTNChatTypeText = 1,
//        CTNChatTypeVoice = 2,
//        CTNChatTypeImage = 3,
//        CTNChatTypeVcard = 4,
//        CTNChatTypeLocation = 5,
//        CTNChatTypeNotification = 6,  // 通知
//        CTNChatTypeSystem = 7,//系统消息，类似纯文本
//        CTNChatTypeCollect = 8,
//        CTNChatTypeVedio = 10,
//        CTNChatTypeGifImage = 12,
//        CTNChatTypeFiles = 14, //发文件
//        CTNChatTypeShare = 15,
//        CTNChatTypeRedEnvelope = 16, // 红包
//        CTNChatTypeRichMedia = 17, // 富媒体
//        CTNChatTypeCustomizedNotification = 20,
//        STChatTypeRecommend = 21,
//        CTNChatTypeTime = 1001,
//        CTNChatTypeSeparate = 1007,
//        CTNChatTypeRevoked = 2000
//
//    };
//
//    enum CTNOwner{
//        CTNOwnerOther = 0,//对方
//        CTNOwnerMyself = 1, //我自己
//        CTNOwnerUnkown = 2,//不确定，需要重新
//    };
//
//    enum CTNAtType{
//        CTNAtTypeNone = 0,
//        CTNAtTypeAll = 1,  //所有人
//        CTNAtTypeSome = 2,//一部分人
//    };
//
//
    struct CTNClientInfo {
        CTNClientInfo(){
            toonType = 100;
            deviceType =  1;
            apnsType = 100;
            pushServiceType = 1;
        }
        
        int32_t toonType;
        int32_t apnsType;
        int32_t deviceType;
        int32_t pushServiceType;
        string username;
        string token;
        string clientId;
        string deviceId;
        string pushToken;
        string version;
        string appPath;
        vector<std::string> feedList;
        
        void setUsername(const char* value){
            if (value == nullptr || strlen(value) == 0){
                return;
            }
            
            this->username = value;
        }
        
        void setToken(const char* value){
            if (value == nullptr || strlen(value) == 0){
                return;
            }
            
            this->token = value;
        }
        
        bool isValid(){
            if (clientId.length() == 0 /*|| feedList.size() == 0*/){
                return false;
            }
            
            return true;
        }
    };
    
    struct CTNSession
    {
        CTNSession()
        {
            unreadCount = 0;
            lastTime = 0;
            sortTime = 0;
            readSeqId = 0;
            lastMsgSendStatus = 0;
            type = -1;
            topStatus = 0;
            disturbStatus = 0;
        }
    public:
        std::string sessionId;
        std::string myFeedId;
        std::string topic;
        std::string title;
        std::string avatarId;
        int32_t unreadCount;
        int32_t type;
        std::string draft;
        int64_t lastTime;//会话最后一条消息的时间
        int64_t sortTime;//会话的排序时间
        std::string lastMsg;
        std::string lastMsgId;
        int32_t lastMsgSendStatus;
        int64_t readSeqId;
        std::string atMeMsgId;
        int32_t disturbStatus;  //0关闭免打扰，1打开免打扰，默认0；
        int32_t topStatus;  //置顶状态0未置顶，1置顶，默认0；
        
        bool isValid () {
            if(topic.length() == 0 || sessionId.length() == 0) {
                //            TNMPLOG("------------Error! add dialoginfo error:session key:" << sessionId << " topic:" << topic << "-------------");
                return false;
            }
            return true;
        }
        
        //isMyself 参数能否去掉，add by lanhuaiyu@20170914
        
        
    };
    
    struct CTNMessage
    {
    public:
        CTNMessage();
        
        //此处可以进行运算符重载
        static bool greaterSort (CTNMessage &a,CTNMessage &b) { return (a.seqId>b.seqId); }
        static bool lessSort (CTNMessage &a,CTNMessage &b) { return (a.seqId<b.seqId); }
        
        bool isEmpty(){
            if (msgId.length() == 0
                || fromId.length() == 0 || toId.length() == 0){
                return true;
            }
            
            return false;
        }
        
        string getAbstractText();
        
        string genBodyJson();
        string getToToonTypeString();
    public:
        std::string msgId;
        std::string sessionId;
        int32_t type;//CTNIMMessageType
        int64_t seqId;
        //判断是否有断层
        //1、热会话建立断层，该值为本地消息的seqId，表示本地消息的seqID与服务端发过来的消息存储到本地之后，之间的消息为断层消息。
        int64_t faultSeqId;
        std::string fromId;
        std::string toId;
        std::string fromClientId;
        std::string toClientId;
        std::string pushInfo;
        int64_t timestamp;
        int32_t sendStatus;//CTNMessageSendStatus
        int32_t status;
        int32_t priority;//wxy 消息优先级
        int32_t catalogId;
        int32_t subCatalogId;
        int32_t contentType;//modify by wxy 与底层数据类型保持一致
        int64_t expireTime;//addby wxy 解析离线文件需要该信息
        std::string content;
        float width;
        float height;
        std::string senderName;
        int32_t atType;
        std::string atFeeds;
        std::string fileFormat;
        std::string noticeStatusType;
        int32_t isMyself;//addby wxy 提供给上层数据中包含消息来源信息
        vector<std::string> toToonTypes;//addby wxy 解析离线文件需要该信息
        int64_t flags;//Toon_FLAG_BITS
        std::string addition;   //json格式，附件的下载状态
        std::string bizNo;  //通知类型消息的bizNo,聊天消息不赋值
    };
    
    struct CTNAppInfo
    {
    public:
        CTNAppInfo()
        {
            chatFlag = 0;
            isDelete = 0;
        }
        void parse(void *dataValue);
        
    public:
        std::string appId;
        std::string appCode;
        std::string appTitle;
        std::string appLittleIcon;
        int32_t chatFlag;
        int32_t isDelete;
        
        bool isValid () {
            if(appId.length() <= 0) {
                return false;
            }
            return true;
        }
    };
    
    struct CTNMessageOperate
    {
    public:
        CTNMessageOperate()
        {
            seqId = 0;
            type = 0;
            timestamp = 0;
            catalogId = 0;
        }
    public:
        std::string msgId;
        int64_t seqId;
        int32_t type;
        std::string mfrom;
        std::string mto;
        int64_t timestamp;
        int32_t catalogId;
        std::string content;
        std::string opMsgId;
        std::string opFeedId;
        std::string opName;
    };
    
    struct CTNGroupInfo
    {
    public:
        CTNGroupInfo()
        {
            groupId = 0;
            maxNum = 0;
            currNum = 0;
            version = 0;
            status = 0;
            disturbStatus = 0;
            verify = 0;
        }
    public:
        
        int64_t groupId;
        std::string creatorFeedId;
        std::string name;
        std::string pinyin;
        std::string namePinyin;
        std::string pinyinHeader;
        std::string headerImage;
        std::string topic;
        std::string myFeedId;
        int32_t status;
        int32_t disturbStatus;
        int32_t maxNum;
        int32_t currNum;
        int64_t version;
        int32_t verify;
        
        void parse(void *dataValue);
        bool isValid () {
            if(groupId <= 0) {
                return false;
            }
            return true;
        }
    };
    
    struct CTNGroupMember
    {
    public:
        CTNGroupMember()
        {
            groupId = 0;
            status = 0;
            timestamp = 0;
        }
    public:
        void parse(void *dataValue);
        
        int64_t groupId;
        std::string groupTopic;
        std::string feedId;
        std::string name;
        std::string namePinyin;
        std::string namePinyinHeader;
        std::string remarkName;
        std::string remarkNamePinyin;
        std::string remarkNamePinyinHeader;
        std::string headerImage;
        int32_t status;
        int64_t timestamp;
        
        bool isValid () {
            if(groupId <= 0 || feedId.length() <= 0) {
                return false;
            }
            return true;
        }
    };
    
    struct CTNSessionSetting
    {
    public:
        CTNSessionSetting (){
            type = -1;
        }
        std::string sessionId;
        int32_t type;
        std::string value;
        
        bool isValid () {
            if(sessionId.length() <= 0 || type <= 0) {
                return false;
            }
            return true;
        }
    };
    
    struct CTNBlackListModel
    {
    public:
        CTNBlackListModel (){
            status = 0;
        }
        
        std::string feedId;
        std::string passiveFeedId;
        int32_t status;
        
        bool isValid () {
            if(feedId.length() <= 0 || passiveFeedId.length() <= 0) {
                return false;
            }
            return true;
        }
        
        void parse(void *dataValue);
    };
    
//    struct CTNFeed {
//        string feedId;// feedId 由c_(普通名片),o_(组织名片),s_(员工名片),g_(群组)加cardId拼接而成
//        string belongTo;// 当前feed属于的组织对应的FeedId或者card对应的FeedId
//        string avatarId;// 头像
//        string title;// 标题
//        string titlePinYin;// 标题拼音
//        string subtitle; // 子标题
//        string userId; // 用户Id
//        string tag;// 标签
//        string socialLevel;// 社交等级
//        string consumeLevel;// 消费等级
//        string serviceLevel;// 服务等级
//        string keyword;// 关键字
//        string sex;// 性别
//        string birthday;// 生日
//        vector<string> ext1;// 扩展字段
//        string recentTime;// 通讯录最近时间标记秒数
//        string unReadNum;// 通讯录群组未读数字
//        string comId;
//        // 内部使用初始化方法 feedId,avatarId,title,subtitle,belongTo,ext1
//        //    - (instancetype)initWithDictionary:(NSDictionary *)otherDictionary;
//        //    @interface TNPFeed(ForumPermission)
//        //permissionType (integer, optional): 权限类型：1 版主 2 管理员 3 普通成员
//        int32_t permissionType;
//        //    @interface TNPFeed(Remark)
//        //remarkName is not nil when having visual angle
//        string remarkName;
//        string remarkNamePinyin;
//    };
//
    struct CTNNoticeFilter{
        CTNNoticeFilter(){
            catalogId = 0;
        }
        
        CTNNoticeFilter(const CTNNoticeFilter& filter){
            catalogId = filter.catalogId;
            broadcast = filter.broadcast;
            set<int>::iterator iter;
            for (iter=filter.subCatalogIdSet.begin();iter!=filter.subCatalogIdSet.end();++iter){
                subCatalogIdSet.insert(*iter);
            }
        }
        
        CTNNoticeFilter& operator = (const CTNNoticeFilter& filter){
            catalogId = filter.catalogId;
            broadcast = filter.broadcast;
            set<int32_t>::iterator iter;
            for (iter=filter.subCatalogIdSet.begin();iter!=filter.subCatalogIdSet.end();++iter){
                subCatalogIdSet.insert(*iter);
            }
            
            return *this;
        }
        
        int32_t catalogId;
        set<int32_t> subCatalogIdSet;
        string broadcast;
    };
    
    //处理离线消息回调时存储在set中的结构体
    struct CTNOffMessageResult {
        std::string sessionId;
        int64_t maxSeqId;
        int64_t minSeqId;
        
        bool operator < (const CTNOffMessageResult &right) const
        {
            return this->sessionId < right.sessionId;
        }
    };
    
    //设置关注的人
    struct CTNFollowFeed {
        CTNFollowFeed() {
            status = false;
        }
        
        std::string feedId;     //关注的人的feedId
        bool status;            //状态，0不关注，1关注
    };
    
    
    std::string generateSessionId(int32_t type, std::string from, std::string to, bool isMyself);
    std::string generateMsgId();
    
}

#endif /* CTNDBHeader_hpp */
