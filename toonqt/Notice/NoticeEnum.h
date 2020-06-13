#ifndef NOTICE_ENUM_H
#define NOTICE_ENUM_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <vector>
#include <memory>
#include <QString>
#include <QMap>


//消息从哪里发出
enum messageSendFrom
{
	GROUP_MESSAGE_TYPE_CURRENT_ACCOUNT = 2,
	GROUP_MESSAGE_TYPE_OTHER = 3
};

//多端多活区分该条消息时发送的消息还是接收的消息
enum messageRecvSend
{
	MESSAGE_SEND = 1,
    MESSAGE_RECV = 2,
    MESSAGE_CONVERT = 3 //转发
};

//表情宽高
#define EMOJI_WIDTH		30
#define EMOJI_HEIGHT    30

/*
消息类型
*/
enum MESSAGE_TYPE{
	em_text = 1,//文字表情
	em_image = 3,//图片
	em_file = 14,//附件
	em_audio = 2,//音频
    em_video = 10,//视频
    em_red_card = 16,//红包
	em_groupchat_notice = 7,//群聊通知
	em_notsupport = 3000,//暂不支持消息
    em_group_operate = 63, //群聊撤回
    em_single_operate = 62, //单聊撤回
    em_card_not_exist = 99
};

/*
图片类型
*/
#define IMAGE_TYPE_GIF "GIF"


#define NOTSUPPORT_TEXT  "不支持的数据类型,请在手机端查看"
#define RED_ENVELOPES 	 "红包消息,请在手机端查看"
#define DEFAULT_IMAGE_LAST_MESSAGE  "[图片]"
#define DEFAULT_FILE_LAST_MESSAGE   "[附件]"
#define DEFAULT_AUDIO_LAST_MESSAGE  "[语音]"
#define DEFAULT_VIDEO_LAST_MESSAGE  "[视频]"
#define REVOKE_FAILED_TEXT "消息发送时间超过两分钟，无法撤回"
#define AT_YOU_SUCCESS     "[有人@你]"
#define AT_YOU_SUCCESS_LENGTH     6
#define ICO_LISTITEM_AVATAR_W 40
#define ICO_LISTITEM_AVATAR_H 40

#endif // NOTICE_ENUM_H
