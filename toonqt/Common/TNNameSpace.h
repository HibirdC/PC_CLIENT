#ifndef TNNAMESPACE_H
#define TNNAMESPACE_H

#include <QSize>
#include <QTextFormat>

namespace TN
{
	const int ThumbWidth = 80;
	const int ThumbHeight = 80;

    enum H5BizType
    {
		InvalidBizType = -1,

		Friend = 0,
		Colleague = 1,
		GroupChat = 3,

		ClickAvatarViewBigPict = 13,

		ClickAvatarInApp = 20,
		AppOpen = 21,  // App展示
		OpenGroupChatSession = 22,
		OrgFrame = 23,
		ClickAvatarInNewFriend = 24,
		UpdateReMark = 25,
		UpdateOrgComm= 26
    };

    enum NewFriendStatus
    {
        Accepting = 0,
        Exchanged = 1
    };

    enum ScreenShotExitFlag
    {
        ClosedExit = 0,
        FinishedExit=1
    };

	//自定义文本对象
	enum TextObject
	{
		TO_ObjectAt = QTextFormat::UserObject + 1
	};

	enum TextObjectProperty
	{
		OP_Text = QTextFormat::UserProperty + 1,
		OP_TextFont
	};

	enum AvatarType
	{
		Normal,
		Middle,
		MiddleSmall,
		Small,
		MoreSmall
	};

	enum ImageType{
		jpg,
		bmp,
		png,
		gif,
		nothing
	};

	enum UpdateSource{
		SessionList,
		CardView,
		Mine
	};
}

#endif // TNNAMESPACE_H
