#ifndef IMCORE_GLOBAL_H
#define IMCORE_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QString>
#include <QList>
#include "limits.h"
#ifdef IMCORE_LIB
# define IMCORE_EXPORT Q_DECL_EXPORT
#else
# define IMCORE_EXPORT Q_DECL_IMPORT
#endif

//im连接地址
//t100 "172.28.18.40"
#define TEST_HOST_IP		"124.251.88.201"
#define TEST_HOST_PORT		20001
#define STATUS_READED		100

#define COMPANYINFO_FIELDID_ADDRESS  "57"
#define COMPANYINFO_FIELDID_TEL  "58"
#define COMPANYINFO_FIELDID_EMAIL  "59"
#define COMPANYINFO_FIELDID_INTERNET  "84"

//fileformat 类型
#define PDFMIME		"application/pdf"

#define DOCMIME		"application/msword"
#define DOCXMIME	"application/vnd.openxmlformats-officedocument.wordprocessingml.document"

#define XLSMIME		"application/vnd.ms-excel"
#define XLSXMIME	"application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"

#define PPTMIME		"application/vnd.ms-powerpoint"
#define PPTXMIME	"application/vnd.openxmlformats-officedocument.presentationml.presentation"

#define TXTMIME 	"text/plain"

#define MOVMIME		"video/quicktime"
#define MP4MIME		"video/mp4"
#define GP3MIME		"video/3gpp"
#define IM_REVOKE_TYPE	2000
//消息类型
typedef enum MSG_TYPE
{
	MSG_TYPE_TEXT = 1,
	MSG_TYPE_VOICE = 2,
	MSG_TYPE_IMG = 3,
	MSG_TYPE_NOTICE = 7,
	MSG_TYPE_VIDEO = 10,
	MSG_TYPE_GIFIMG = 12,
	MSG_TYPE_ATTACHMENT = 14,
    MSG_TYPE_CARD_FAILED = 15,		//名片不存在消息
	MSG_TYPE_RED_CARD = 16,			//红包消息
	MSG_TYPE_OTHER = 3000

}TNMsgType;
typedef enum MSG_BIZ_TYPE
{
	MSG_BIZ_GROUPNOTIFY = 50,
	MSG_BIZ_NOTIFY = 51,
	MSG_BIZ_SINGLECHAT = 52,
	MSG_BIZ_GROUPCHAT = 53,
	MSG_BIZ_SINGLECHAT_REVERT = 62,
	MSG_BIZ_GROUPCHAT_REVERT = 63,
	MSG_BIZ_UNSHOW
}TNBizType;
typedef enum MSG_STATUS
{
	MSG_STATUS_SENDING = 1,
	MSG_STATUS_SEND_SUC = 2,
    MSG_STATUS_SEND_FAIL = 3,
	MSG_STATUS_SEND_FAIL_Card,
	MSG_STATUS_SEND_FAIL_CoCard,
	MSG_STATUS_SEND_FAIL_OrCard,
    MSG_STATUS_UNSEND,
    MSG_STATUS_RESEND
}TNMsgStatus;
typedef enum MSG_FILE_STATUS
{ 
    MSG_STATUS_FILE_SUC = 0,
	MSG_STATUS_FILE_UPLOADING,
	MSG_STATUS_FILE_UPLOAD_FAIL,
	MSG_STATUS_FILE_DOWNLOADING,
	MSG_STATUS_FILE_DOWN_FAIL,
    MSG_STATUS_FILE_UNDOWN,
	MSG_STATUS_FILE_READED = 100
}TNMsgFileStatus;
typedef enum MSG_USE_STATUS
{
	MSG_USE_NORMAL = 0,
	MSG_USE_DEL = 1
}TNMsgUseStatus;


typedef struct st_MsgData
{
	QString msgId;		//消息id
	QString sessionId;	//sessionid
	QString senderName;
	QString from;		//发送人名片
	QString to;			//单聊：接收人名片 群聊：gc_groupid
	QString toUserId;	//接收人用户id  群聊可以不传
	QString data;		//文本：文本内容 图片：图片云存储路径 文件：文件云存储路径
	QString localPath;	//本地路径，没有下载过则为空
	QString url;		//云存储路径
	qlonglong timestmp;

	int		w;			//图片类型的宽
	int		h;			//图片类型的高

	QString desc;		//文件名称
	QString format;		//文件格式
	int		size;		//文件大小

	int		time;		//时长
	int		readed;		//语音格式是否已读 //1是已读，0是未读
	MSG_TYPE type;
	MSG_BIZ_TYPE bizType;	//业务类型

	bool   bShow;			//是否显示
	bool   bIsMyself;		//是否是我自己的消息
	bool   bSendSuc;		//是否发送成功

	bool   bIsAtMe;			//是否@了我
	bool   bIsBubble;		//是否需要冒泡
	int				atType;					//@类型	  0无@功能  1@全部群成员  2@一部分成员，
	QList<QString>  atFeeds;				//@用户列表
	TNMsgStatus		status;					//消息状态
	TNMsgFileStatus fileStatus;
	st_MsgData(){
		timestmp = 0;
		w = 0;
		h = 0;
		size = 0;
		time = 0;
		readed = 0;
		atType = 0;
		type = MSG_TYPE_TEXT;
		bizType = MSG_BIZ_UNSHOW;
		status = MSG_STATUS_SEND_SUC;
		fileStatus = MSG_STATUS_FILE_SUC;
		bIsAtMe = false;
		bIsBubble = true;
		bShow = true;
		bIsMyself = false;
		bSendSuc = false;
	}
}TNMsgData;
typedef struct st_RevokeData
{
	QString msgId;		//消息id
	QString from;		//发送人名片
	QString to;			//单聊：接收人名片 群聊：gc_groupid
	QString toUserId;   //userid
	QString opMsgId;   //撤销消息id
	QString opFeedId;  //操作者id
	QString opName;	   //操作者名称
	st_RevokeData()
	{

	}
}TNRevokeData;

typedef struct st_offMsg
{
	qlonglong maxTimeStamp;	//最大seqid消息的时间戳
	qlonglong maxSeqId;		//最大seqid
	qlonglong minSeqId;		//最小seqid
	QString from;
	QString to;
	int type;
	int count;				//限制数量
}TNOffMsg;

typedef struct st_readSession
{
	QString from;
	QString to;
	int		type;
	qlonglong readSeqId;
}TNReadSession;


//通知类型
enum ActTionType
{
	Action_APP = 0,  //无跳转
	Action_Url = 1,  //h5跳转
	Action_Toon = 5  //toon协议跳转
};
enum SubCatalogType
{
	SubCatalogType_NONE = -1,
	SubCatalogType_JoinGroupSuc = 0,				//成功加入群组
	SubCatalogType_ApplyJoinGroup = 1,				//申请加入群组			
	SubCatalogType_JoinGroup = 2,					//邀请入群组			
	SubCatalogType_ChangeCard = 3,					//普通交换名片
	SubCatalogType_PhoneChangeCard = 4,				//手机通讯录交换名片
	SubCatalogType_GrantCard = 5,					//组织发放名片
	SubCatalogType_CompandyAttorm = 6				//组织转让
};
enum SyncType
{
	SyncType_MyFriend = 1							//我的好友
};
enum CatalogType
{
	CATALOG_TYPE_NONE = 0,
	CATALOG_SEND_CARD = 1,								//公司发放名片
	CATALOG_ME_JOIN_GROUP = 45,							//我被邀请加入群
	CATALOG_CHANGE_GROUP = 47,							//群资料变动
	//CATALOG_OTHER_JOIN_GROUP = 49,					//群成员加入(谁邀请谁加入群)
	CATALOG_OTHER_QUIT_GROUP = 51,						//群成员主动退出群聊	
	CATALOG_ME_QUIT_GROUP = 53,							//自己被踢
	//CATALOG_JOIN_GROUP = 55,							//加入聊天室
	//CATALOG_QUIT_GROUP = 57,							//退出聊天室
	CATALOG_OTHER_QUIT = 63,							//群聊踢人
	CATALOG_FRIEND_REQ = 82,							//新的朋友会话
	CATALOG_SYNC_MYFRIEND = 113,						//通讯录同步好友
	CATALOG_SYNC_GROUP = 115,							//通讯录同步群组
	CATALOG_SYNC_SWITCH = 119,							//通讯录同步开关（免打扰）
	CATALOG_SYNC_GROUPCHAT = 120,						//群聊增量更新同步
	CATALOG_SYNC_GROUPMEMBER = 1201,					//群聊成员增量更新同步
	CATALOG_COMPANY_MANAGER = 132,						//企业管理
	CATALOG_GROUPNOTIFY = 101,							//群组公告
    CATALOG_SYNC_MYCARD = 139,							//我的组织名片同步
    CATALOG_GROUP_INVITEJOIN = 142,						//社区消息-邀请加入
	CATALOG_STNC_ORGCOMMUNICATION = 159,                //组织名片可沟通能力配置
	CATALOG_SCAN_INFO = 160								//扫码透传通知
};
typedef struct st_NoticeInfo
{
	QString msgId;
	qlonglong seqId;
	QString sessonId;
	QString bizId;			//业务id
	QString subCatalog;		//标题区----					通知标题

	int headFlag;
	QString leftFeed;		//头像区----					上信息
	QString rightFeed;		//					左（头像）                 右(头像)
	QString upFeedTitle;	//								下信息
	QString downFeedTitle;
    QString mobilePhone;

	QString			summary;        //内容标题
	QString			msgContent;		//内容区----					文本内容
	QString			resource;		//资源展示区----				图片|语音|视频

	QString			buttonName;		//按钮操作区----				 button	
	QString			Url;			//type = action_app 无用
	ActTionType     actionType;
	CatalogType	    noticeType;		//业务类型
	SubCatalogType  subNoticeType;	//子业务类型

	bool			bIsFinished;	//业务是否已经完成
	
	qlonglong		timestmp_s;		//时间戳,单位秒

	qlonglong		expireTime_s;	//过期时间,单位秒

	st_NoticeInfo() :seqId(0), bIsFinished(false), timestmp_s(0), expireTime_s(0)
	{
		
		headFlag = -1;
		actionType = Action_APP;
		noticeType = CATALOG_TYPE_NONE;
		subNoticeType = SubCatalogType_NONE;
	}
}TNNoticeInfo;


#define FAIL_SEQID				INT_FAST32_MAX - 1000
#define OPERATE_TYPE_REVOKE     1

#define GifImgSuffix  ".gif"
#define OrgCardPre	  "o_"	
#define UserCardPre   "c_"
#define CoCardPre	  "s_"
#define GifSize		  200
//广播通知
#define NEW_FRIEND_NOTICE   "NEW_FRIEND"
#endif // IMCORE_GLOBAL_H
