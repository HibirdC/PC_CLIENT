#ifndef NETWORKAPI_GLOBAL_H
#define NETWORKAPI_GLOBAL_H

#include <vector>
#include <memory>
#include <QtCore/qglobal.h>
#include <QString>

#ifdef NETWORKAPI_LIB
# define NETWORKAPI_EXPORT Q_DECL_EXPORT
#else
# define NETWORKAPI_EXPORT Q_DECL_IMPORT
#endif

#define HTTPS		"https"

const QString HttpUserAgent_H5 = QString("Toon-pc/1.0.0 windows,android,iphone,ipad");

//sit环境
const QString DEV_URL_H5 = QString("http://t200desktop.systoon.com/card/web");
const QString DEV_URL_NEWFRIEND = QString("http://t200desktop.systoon.com/card/web/newfriend");
const QString DEV_URL_ROUTER_HOST = QString("t200api.systoon.com");
const QString DEV_URL_ROUTER_LIST = QString("http://t200api.systoon.com/router");
const QString DEV_URL_FEEDBACK = QString("http://t200api.systoon.com/operatingplatform/feedback/save");
const QString DEV_URL_OALOGIN = QString("http://t200.oapi.qitoon.com/uua/toon_login");
const QString DEV_URL_HomePageList = QString("http://t200desktop.systoon.com/homepage/api/listHomePage");

//线上环境
const QString ONLINE_URL_H5 = QString("https://desktop.systoon.com/card/web");
const QString ONLINE_URL_NEWFRIEND = QString("https://desktop.systoon.com/card/web/newfriend");
const QString ONLINE_URL_ROUTER_HOST = QString("apirouter.systoon.com");
const QString ONLINE_URL_ROUTER_LIST = QString("https://apirouter.systoon.com");
const QString ONLINE_URL_FEEDBACK = QString("http://operatingplatform.systoon.com/feedback/save"); // 和闫润杰确认过，反馈建议是http接口
const QString ONLINE_URL_OALOGIN = QString("https://oapi.qitoon.com/uua/toon_login");
const QString ONLINE_URL_HomePageList = QString("http://desktop.systoon.com/homepage/api/listHomePage");

//t100环境
const QString TEST_URL_H5 = QString("http://t100desktop.systoon.com/card/web");
const QString TEST_URL_NEWFRIEND = QString("http://t100desktop.systoon.com/card/web/newfriend");
const QString TEST_URL_ROUTER_HOST = QString("t100.api.router.systoon.com");
const QString TEST_URL_ROUTER_LIST = QString("http://t100.api.router.systoon.com");
const QString TEST_URL_FEEDBACK = QString("http://t100api.systoon.com/operatingplatform/feedback/save");
const QString TEST_URL_OALOGIN = QString("http://t100.oapi.qitoon.com/uua/toon_login");
const QString TEST_URL_HomePageList = QString("http://t100desktop.systoon.com/homepage/api/listHomePage");

//ucloud环境
const QString UCLOUD_URL_H5 = QString("http://desktop.systoontest.com/card/web");
const QString UCLOUD_URL_NEWFRIEND = QString("http://desktop.systoontest.com/card/web/newfriend");
const QString UCLOUD_URL_ROUTER_HOST = QString("api.systoontest.com");
const QString UCLOUD_URL_ROUTER_LIST = QString("http://api.systoontest.com/router");
const QString UCLOUD_URL_FEEDBACK = QString("http://api.systoontest.com/operatingplatform/feedback/save");
const QString UCLOUD_URL_OALOGIN = QString("http://oapi.qitoontest.com/uua/toon_login");
const QString UCLOUD_URL_HomePageList = QString("http://desktop.systoontest.com/homepage/api/listHomePage");

//埋点统计服务
const QString TEST_URL_DAM = QString("http://172.28.16.206:8081/datainterDevice/deviceServlet/saveDeviceInfo");
const QString ONLINE_URL_DAM = QString("http://da.syswin.com/datainterDevice/deviceServlet/saveDeviceInfo");
const QString TEST_URL_DAM_FUNC = QString("http://172.28.18.42/dataInterOper/operServlet/saveOperInfo");
const QString ONLINE_URL_DAM_FUNC = QString("http://da.syswin.com/dataInterOper/operServlet/saveOperInfo");

const QString URL_NEW_USER_SYSTOON_COM = QString("new.user.systoon.com");
const QString URL_NEW_CONTACT_SYSTOON_COM = QString("new.contact.systoon.com");
const QString URL_API_FEED_SYSTOON_COM = QString("api.feed.systoon.com");
const QString URL_NEW_ORG_SYSTOON_COM = QString("new.org.systoon.com");
const QString URL_API_NEW_GROUPCHAT_SYSTOON_COM = QString("api.new.groupchat.systoon.com");
const QString URL_CARD_SYSTOON_COM = QString("new.card.systoon.com");
const QString URL_TOON_SCLOUD_SYSTOON_COM = QString("toon.scloud.systoon.com");
const QString URL_NEW_GROUP_SYSTOON_COM = QString("new.group.systoon.com");
const QString URL_API_APP_SYSTOON_COM = QString("api.app.systoon.com");
const QString URL_APPDOWN_SYSTOON_COM = QString("api.appdown.systoon.com");
const QString URL_API_IM_SYSTOON_COM = QString("api.im.systoon.com");
const QString URL_API_IMSSL_SYSTOON_COM = QString("api.imssl.systoon.com");
const QString URL_MIX_SYSTOON_COM = QString("api.mix.systoon.com");
const QString URL_CAMS_SYSTOON_COM = QString("apicams.systoon.com");

const QString URL_CHECKREGISTERBEFORELOGINNEW = QString("/user/checkRegisterBeforeLoginNew");
const QString URL_LOGINWITHPASSWORD = QString("/user/loginWithPassword");
const QString URL_SENDVCODEBEFORELOGIN = QString("/user/sendVCodeBeforeLogin");
const QString URL_LOGINWITHVCODE = QString("/user/loginWithVCode");
const QString URL_LOGOUT = QString("/user/logout");
const QString URL_CHECK_VCODE = QString("/user/checkVCodeBeforeLoginNew");
const QString URL_RESETPASSWORD = QString("/user/updatePasswordBeforeLoginNew");
const QString URL_GETLISTCARD = QString("/user/getListCard");

//联系人
const QString URL_CONTACT_FRIEND_FEED = QString("/user/getContactFriendFeed");
const QString URL_LIST_STAFF_CONTACT_BY_USER_ID = QString("/user/getListStaffContactByUserId");
const QString URL_OBTAIN_FEED_LIST = QString("/user/obtainFeedList");
const QString URL_LIST_RELATION_ITEM = QString("/user/getListRelationItem");

const QString URL_GROUP_CARD_GETMYGROUP = QString("/user/getMyGroup");
//此接口即将废弃 2017.12.5
const QString URL_GROUP_CARD_BYUSER = QString("/user/getGroupCardByUser");
//
const QString URL_LIST_GROUPCONTACT_BYUSERID = QString("/user/getListGroupContactByUserId");
const QString URL_ORG_GROUP_LIST = QString("/user/getOrgGroupList");
const QString URL_LIST_STAFF_CARD_BYUSERID = QString("/user/getListStaffCardByUserId");
const QString URL_LIST_STAFF_CARD = QString("/user/getListStaffCard");
const QString URL_LIST_ORG_CARD_BYUSERID = QString("/user/getListOrgCardByUserId");
const QString URL_OBTAIN_STOKEN = QString("/user/obtainUserStoken");
const QString URL_UPLOAD_CLOUD = QString("/uploadFile");
const QString URL_LIST_ORG_CARD = QString("/user/getListOrgCard");
const QString URL_LIST_RECOMMEND_APP = QString("/user/getListToonApp");

const QString URL_QUIT_GROUPCHAT = QString("/user/quitGroupChat");
const QString URL_COMPANYINFO_BYCOMIDLIST = QString("/user/getCompanyInfoByComIdList");
const QString URL_COMPANYINFO_BYCOMID = QString("/user/getCompanyInfoByComId");
const QString URL_COMPANYFEED_BYCOMID = QString("/user/getListOrgByComId");
const QString URL_COMPANYINFO_ORGCOMM = QString("/user/getOrgCommunicateStatus");
const QString URL_ACCEPTJOINGROUP_REQUEST = QString("/user/acceptJoinGroupRequest");

const QString URL_GetListGroup_Info = QString("/user/getListGroup");
const QString URL_ApplyJoinGroup = QString("/user/applyJoinGroup");
const QString URL_OBTAIN_GROUPMEMBERS_BYGROUPID = QString("/user/getListGroupCard");

//app
const QString URL_LIST_CARDREGISTERAPP = QString("/user/getListCardRegisteredApp");
const QString URL_LIST_COMPANYSTAFFREGISTERAPP = QString("/user/getListCompanyStaffRegisteredApp");
const QString URL_LIST_COMPANYCARDREGISTERAPP = QString("/user/getListCompanyCardRegisteredApp");
const QString URL_LIST_GROUPREGISTERAPP = QString("/user/getListGroupRegisteredApp");
const QString URL_GETAPPCODE_TEXT = QString("/user/generateCypherText");
const QString URL_GETAPPNOTICE_BYID = QString("/user/getAppNoticeByAppId");

//好友
const QString URL_ADDFRIEND = QString("/user/addFriend");
const QString URL_ASKFORFRIEND = QString("/user/askForFriend");
const QString URL_ACCEPTFRIEND_REQUEST = QString("/user/acceptFriendRequest");
const QString URL_REFUSEFRIEND_REQUEST = QString("/user/refuseFriendRequest");
const QString URL_ACCEPTFRIEND_REQUEST_Phone = QString("/user/acceptContactFriendRequest");
const QString URL_QUERY_SWITCHINFO = QString("/user/querySwitchInfo");
const QString URL_SWITCH_OFF = QString("/user/switchOff");
const QString URL_SWITCH_ON = QString("/user/switchOn");
const QString URL_GETFEEDREMARK = QString("/user/qrySenderRemarks");

//新学员
const QString URL_GETUNCONFIRMFRIENDFEED = QString("/user/getUnConfirmFriendFeed");

//二维码扫码
const QString URL_QRCODEKEY_GEN = QString("/user/qrCodeKeyGen");
const QString URL_GETQRCODE = QString("/user/getQRCode");
const QString URL_GETQRCODE_STATUS = QString("/user/getQRCodeStatus");
const QString URL_CANCEL_QRCODE_LOGIN = QString("/user/clientCanceQRCodelLogin");

//群聊
const QString URL_CREAT_GROUPCHAT = QString("/user/createGroupChat");
const QString URL_ADD_GROUPCHAT_MEMBERS = QString("/user/addGroupChatMembers");
const QString URL_REMOVE_GROUPCHAT_MEMBERS = QString("/user/removeGroupChatMembers");
const QString URL_OBTAIN_GROUP_CHATINFO_BYGROUPCHATID = QString("/user/obtainGroupChatInfoByGroupChatId");
const QString URL_OBTAIN_GROUPCHATMEMBERS_BYGROUPCHATID = QString("/user/obtainGroupChatMembersByGroupChatId");
const QString URL_OBTAIN_GROUPCHATS_BYUSERID = QString("/user/obtainGroupChatsByUserId");
const QString URL_UPDATE_GROUPCHAT = QString("/user/updateGroupChat");
const QString URL_SETGROUPCHAT_DISTURB = QString("/user/setupGroupChatDisturb");

// 员工名片
const QString URL_ACCEPTStaffCARD_REQUEST = QString("/user/acceptStaffCard");
const QString URL_REFUSEStaffCARD_REQUEST = QString("/user/refuseStaffCard");

// 组织名片
const QString URL_ACCEPTOrgCARD_REQUEST = QString("/user/doAcceptOrgCard");
const QString URL_REFUSEOrgCARD_REQUEST = QString("/user/doRefuseOrgCard");

//自动更新
const QString URL_CHECKNEW_VERION = QString("/user/checkNewVersion");
const QString URL_DOWNLOAD_VERION = QString("/user/toDownload");
#endif // NETWORKAPI_GLOBAL_H
