//
//   CTNIMTypedef_h
//  
//
//  Created by 兰怀玉 on 2017/12/20.
//

#ifndef CTNIMTypedef_h
#define CTNIMTypedef_h

#include "TMTPConst.h"
#include "tmtp_type.h"


typedef enum Toon_TMTP_TYPE  CTNIMMessageType;
#define CTNIMMessageTypeMsgACK  TYPE_MSGACK
#define CTNIMMessageTypeChat    TYPE_SINGLE_CHAT_MSGREQ
#define CTNIMMessageTypeMsgSingleOperate  TYPE_MSG_SINGLE_OPERATE
#define CTNIMMessageTypeBizNotice  TYPE_NOTIFY_MSGREQ
#define CTNIMMessageTypeGroupNotice  TYPE_GROUP_NOTIFY_REQ
#define CTNIMMessageTypeGroupChat  TYPE_GROUP_CHAT_MSGREQ
#define CTNIMMessageTypeMsgGroupOperate  TYPE_MSG_GROUP_OPERATE
#define CTNIMMessageTypeSync  TYPE_SYNC_MSGREQ
#define CTNIMMessageTypeAt   TYPE_CLIENT_ATMESSAGE
#define CTNIMMessageTypeFollow  TYPE_CLIENT_FOLLOWMESSAGE


enum CTNMessageSendStatus
{
    CTNMessageDraft = 0,
    CTNMessageSending = 1,
    CTNMessageSuccess = 2,
    CTNMessageFailed = 3,
};

enum CTNMessageFileStatus
{
    CTNFileStatusNotDownload = 1,
    CTNFileStatusDownloading = 2,
    CTNFileStatusDownloaded = 3,
    CTNFileStatusDownloadFailed = 4,
    CTNFileStatusDownloadCancel = 5,
    
    CTNFileStatusSended = 6,
    CTNFileStatusSending = 7,
    CTNFileStatusSendCancel = 8,
    CTNFileStatusSendFailed = 9
};

//消息类型：1：文本， 2：语音，3：图片，4：名片，5：位置，6:表情(暂时没用),7：常用信息(暂时没用)，8：收藏,9:常用地址(暂时没用), 10:视频, 11:礼物, 12:gif表情图片, 15:分享
enum CTNMessageContentType{
    CTNChatTypeNone = 0,
    CTNChatTypeText = 1,
    CTNChatTypeVoice = 2,
    CTNChatTypeImage = 3,
    CTNChatTypeVcard = 4,
    CTNChatTypeLocation = 5,
    CTNChatTypeNotification = 6,  // 通知
    CTNChatTypeSystem = 7,//系统消息，类似纯文本
    CTNChatTypeCollect = 8,
    CTNChatTypeVedio = 10,
    CTNChatTypeGifImage = 12,
    CTNChatTypeFiles = 14, //发文件
    CTNChatTypeShare = 15,
    CTNChatTypeRedEnvelope = 16, // 红包
    CTNChatTypeRichMedia = 17, // 富媒体
    CTNChatTypeCustomizedNotification = 20,
    CTNChatTypeRecommend = 21,
    CTNChatTypeTime = 1001,
    CTNChatTypeSeparate = 1007,
    CTNChatTypeRevoked = 2000
};

enum CTNIMMessageStatus{
    CTNIMMessageNormal = 0,
    CTNIMMessageRevoked = 1,//撤回
    CTNIMMessageDeleted = 2,//删除或者废弃状态
    CTNIMMessageNoSession = 3,//本地不需要处理，直接抛给第三方
};


enum CTNOwner{
    CTNOwnerOther = 0,//对方
    CTNOwnerMyself = 1, //我自己
    CTNOwnerUnkown = 2,//不确定，需要重新
};

enum CTNAtType{
    CTNAtTypeNone = 0,
    CTNAtTypeAll = 1,  //所有人
    CTNAtTypeSome = 2,//一部分人
};


//判断某项功能是否禁止key 
#define IM_SINGLECHAT_SEND_DISABLE      "IM_SINGLECHAT_SEND_DISABLE"
#define IM_GROUCHAT_SEND_DISABLE        "IM_GROUCHAT_SEND_DISABLE"
#define IM_GROUPCHAT_CREATE_DISABLE     "IM_GROUPCHAT_CREATE_DISABLE"
#define IM_GROUPCHAT_ADDMEMBER_DISABLE  "IM_GROUPCHAT_ADDMEMBER_DISABLE"
#define IM_GROUPCHAT_RMMEMBER_DISABLE   "IM_GROUPCHAT_RMMEMBER_DISABLE"





#endif /* CTNDIMTypedef_h */
