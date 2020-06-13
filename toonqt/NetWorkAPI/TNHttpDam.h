#ifndef TNHTTPDAM_H
#define TNHTTPDAM_H

#include <functional>
#include <QList>
#include <QPair>

#include "common_global.h"
#include "TNHttpBaseApi.h"
enum OPERATE_TYPE
{
	OP_TYPE_STARTUP = 1,
	OP_TYPE_LOGIN = 5
};

enum FUNCTION_TYPE
{
	//登录
	FUNC_TYPE_PWD_Switch = 0,			//切换为密码登录
	FUNC_TYPE_PWD_Login,				//密码状态登录
	FUNC_TYPE_Code_Switch,				//切换为验证码
	FUNC_TYPE_Resend_Code,				//重新发送验证码
	FUNC_TYPE_Code_Login,				//验证码登录
	FUNC_TYPE_ScanCode_Switch,			//切换为扫码
	FUNC_TYPE_ForgetPWD,				//忘记密码	---1.5.0
	FUNC_TYPE_BackLogin,				//回到登录	---1.5.0
	//通知
	FUNC_TYPE_Notice,					//切换为通知
	FUNC_TYPE_Notice_Search,			//通知-搜索
	FUNC_TYPE_Notice_SetTop,			//通知-置顶
	FUNC_TYPE_Notice_DelSession,		//通知-删除会话
	FUNC_TYPE_Notice_ChangeGroup,		//通知-修改群名称
	FUNC_TYPE_Notice_Disturb,			//通知-消息免打扰
    FUNC_TYPE_NoticeDetail_Member,		//通知详情--点下拉成员（标题）
	FUNC_TYPE_NoticeDetail_AddMember,	//通知详情--点+
	FUNC_TYPE_NoticeDetail_CreateChat,	//通知详情--创建群聊
	FUNC_TYPE_NoticeDetail_SendForward,	//通知详情--右键转发
	FUNC_TYPE_NoticeDetail_Copy,		//通知详情--右键复制
	FUNC_TYPE_NoticeDetail_Del,			//通知详情--右键删除
	FUNC_TYPE_NoticeDetail_Revert,		//通知详情--右键撤回
	FUNC_TYPE_Notice_CreateChat,		//通知-创建群聊							---1.5.0
    FUNC_TYPE_NoticeDetail_ChatDropDown, //通知详情--点下拉菜单	(按钮)				---1.5.0
	FUNC_TYPE_NoticeDetail_DelMember,	 //通知详情--下拉菜单--删除成员			---1.5.0
	FUNC_TYPE_NoticeDetail_QuitChat,	 //通知详情--下拉菜单--退出群聊			---1.5.0
	//通讯录
	FUNC_TYPE_Address,					//切换为通讯录
	FUNC_TYPE_Address_Search,			//通讯录搜索
    FUNC_TYPE_Address_NewFriend,		//通讯录--新学员
	FUNC_TYPE_Address_Friend,			//通讯录--好友
	FUNC_TYPE_Address_Colleage,			//通讯录--同事
	FUNC_TYPE_Address_Group,			//通讯录--社区
	FUNC_TYPE_Address_GroupChat,		//通讯录--群聊
	FUNC_TYPE_Address_Talk,				//通讯录详情--沟通
	FUNC_TYPE_Address_App,				//通讯录详情--点击应用
	FUNC_TYPE_Address_ModifyRemark,		//通讯录详情--备注名修改				---1.5.0
	//我的
	FUNC_TYPE_MINE,						//切换为我的
	FUNC_TYPE_MINE_APP,					//我的--点击应用
    //设置
    FUNC_TYPE_Setup_Logout_OK,			//退出登录--确定
    FUNC_TYPE_Setup_Logout_Cancel,		//退出登录--取消
    //托盘
	FUNC_TYPE_Msgtip_IgnoreAll,			//消息提示框---忽略全部				    ---1.5.0
    FUNC_TYPE_Tray_Logout,			    //托盘-右键退出

	FUNC_TYPE_MAX
};
enum SEARCH_TYPE
{
	SERACH_TYPE_Friend =0,
	SERACH_TYPE_Colleage,
	SEARCH_TYPE_Group,
	SEARCH_TYPE_GroupChat,
	SEARCH_TYPE_MAX
};
struct TNDamSearchData
{
	QString keyWord;		//关键词
	QString number;		    //选择第几条数据
	QString dataId;			//数据id
	SEARCH_TYPE	 type;
};
class NETWORKAPI_EXPORT TNHttpDam : public TNHttpBaseApi
{
public:
	TNHttpDam();
	~TNHttpDam();
	QString GetUUID();
	void RecordDeviceData(const TNPluginParamPtr &pluginParam, OPERATE_TYPE type);
	void RecordFunctionData(const TNPluginParamPtr &pluginParam, FUNCTION_TYPE type);
	void RecordSearchData(const TNPluginParamPtr &pluginParam, FUNCTION_TYPE type, TNDamSearchData searchData);
protected:
	void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);
	void RecordFunctionInnerData(const TNPluginParamPtr &pluginParam, FUNCTION_TYPE type, const QJsonObject& searchData);
private:
	static QString s_funTables[FUNC_TYPE_MAX];
	static QString s_typeTables[SEARCH_TYPE_MAX];
};

typedef std::shared_ptr<TNHttpDam>  TNHttpDamPtr;

#endif // TNHTTPDAM_H
