#ifndef COMMON_GLOBAL_H
#define COMMON_GLOBAL_H

#include <vector>
#include <memory>
#include <QtCore/qglobal.h>
#include <QString>


#ifdef COMMON_LIB
# define COMMON_EXPORT Q_DECL_EXPORT
#else
# define COMMON_EXPORT Q_DECL_IMPORT
#endif

#define MENU_SHOW_TYPE_SETUP 0
#define MENU_SHOW_TYPE_AVATAR 1
#define MENU_SHOW_TYPE_CARDCASE 2
#define MEUNU_SHOW_TYPE_MESSAGE 3
#define MEUNU_SHOW_TYPE_CREATE 4
#define MEUNU_SHOW_TYPE_MINE 5
#define MEUNU_SHOW_TYPE_HOMEPAGE 6

#define DBTYPE_USER 0
#define DBTYPE_COMMON 1
#define DBTYPE_MSG	2

#define SPACE_STR   " "
typedef struct PluginStruct
{
	/// <summary>	模块动态库的名称. </summary>
	QString strName;
	/// <summary>	描述信息. </summary>
	QString strDescribe;
	/// <summary>	动态库所在路径. </summary>
	QString strPath;
	/// <summary>	维度. </summary>
	int nDimension;
	/// <summary>	是否启用. </summary>
	bool bEnable;
}XmlPluginStruct;

typedef std::vector<std::shared_ptr<XmlPluginStruct> > XmlPluginStructVec;

#define DIMENSION_MENUTOP 1
#define DIMENSION_MENUCENTER 2
#define DIMENSION_MENUBOTTOM 3

//各个菜单部份ID
#define MENU_CARDCASE_ID          0x0001
#define MENU_CREATE_ID	          0x0002
#define MENU_DISCOVER_ID	      0x0003
#define MENU_DYNIMICSTATE_ID	  0x0004
#define MENU_HOMEPAGE_ID	      0x0005
#define MENU_MINE_ID			  0x0006
#define MENU_NOTICE_ID			  0x0007
#define MENU_SEARCH_ID			  0x0008
#define MENU_SETUP_ID			  0x0009
#define MENU_AVATAR_ID            0x0010

//消息ID
#define WM_TRAYNOTIFY             (WM_USER+110)


typedef struct Param
{
public:
    Param() : _currentSelectPage(MENU_NOTICE_ID){}
    ~Param(){}

	//用户认证
	QString strTnUserID;
	QString strTnUserToken;
	QString strTnUserAgent;
	QString strMobile;
	QString strMacAddress;

	//路由表
	QString str_new_user_systoon_com;
	QString str_new_contact_systoon_com; 
	QString str_api_feed_systoon_com;
	QString str_new_org_systoon_com; 
	QString str_new_card_systoon_com; 
	QString str_new_group_systoon_com; 
	QString str_api_new_groupchat_systoon_com;
	QString str_api_app_systoon_com;
	QString str_appdown_systoon_com;
	QString str_api_im_systoon_com;
	QString str_api_imssl_systoon_com;
    QString str_mix_systoon_com;
    QString str_cams_systoon_com;

    //界面当前选中的page(通知,通讯录,我的....)
    int _currentSelectPage;
}PluginParam;

typedef std::shared_ptr<PluginParam> TNPluginParamPtr;


//菜单区宽度
#define MENU_AREA_WIDTH   71
//列表区宽度
#define LIST_AREA_WIDTH   250
#define LIST_AREA_HEIGHT    70
#define LIST_TAG_HEIGHT   24
//详情区宽度
#define DETAIL_AREA_WIDTH   680

//Search面板区域 宽度
#define SEARCH_SHOW_COUNT 3
#define LIST_SEARCH_WIDTH   250
#define LIST_SEARCH_HEIGHT    50
#define LIST_AT_WIDTH   150
#define LIST_AT_HEIGHT    30

//名片选择面板
#define AVATAR_ALL_NAME QStringLiteral("全部名片")
#define AVATAR_ALL_FEED QStringLiteral("c_8888888888")
#define AVATAR_SHOW_COUNT 7
#define LIST_AVATARCHOICE_WIDTH   180
#define LIST_AVATARCHOICE_HEIGHT    46

//TreeView 面板区域
#define TREE_ITEM_WIDTH 250
#define TREE_THIRDNODE_HEIGHT 70
#define TREE_SECONDNODE_HEIGHT 40
#define TREE_FIRSTNODE_HEIGHT 30

#define LIST_UNREAD_WIDTH   230
#define LIST_UNREAD_HEIGHT  40
#define LIST_UNREAD_TITLE_HEIGHT   40
#define LIST_UNREAD_BUTTOM_HEIGHT   40

#define FeedTypeCard "1"  //自己的普通名片
#define FeedTypeContact "2" //好友关系类型
#define FeedTypeGroup "3"   //群组关系类型，包括我创建的群组和加入的群组
#define FeedTypeOrgStaff "4"  //同事关系类型
#define FeedTypeStaff "5"   //自己的员工类型名片
#define FeedTypeOrg "6"   //自己的组织类型名片

//程序中图片和附件发送的大小限制
#define MAX_PIC_SIZE 	 10 * 1024 * 1024
#define MAX_FILE_SIZE    60 * 1024 * 1024


#ifndef Q_OS_MAC
#define TOON_DEVICE_TYPE  3
#else
#define TOON_DEVICE_TYPE  4
#endif

//同步数据类型
typedef enum OperateType
{
	UI_OPERATE_ADD = 1,
	UI_OPERATE_DEL = 2,
}UIOperateType;
typedef struct st_UINotifyData
{
	QString feedId;
	QString belongId;
	UIOperateType     operateType;
}UINotifyData;

typedef enum CacheGroupChatOperate
{
	gcAdd = 0,
	gcModify = 1,
	gcDel = 2
}CacheGCOp;

typedef enum CacheFriendOperate
{
	frAdd = 0,
	frModify = 1,
	frDel = 2
}CacheFOp;

typedef enum CacheColleagueOperate
{
	coAdd = 0,
	coModify = 1,
	coDel = 2
}CacheCOOp;

typedef enum CacheGroupOperate
{
	grAdd = 0,
	grModify = 1,
	grDel = 2
}CacheGOp;

#endif // COMMON_GLOBAL_H
