#include "NetWorkAPI.h"
#include "TNConfig.h"
#include "TNPathUtil.h"

QString NetWorkAPI::s_urlLocalH5Url = ONLINE_URL_H5;
QString NetWorkAPI::s_newFriendH5Url = ONLINE_URL_NEWFRIEND;
QString NetWorkAPI::s_urlRouterHost = ONLINE_URL_ROUTER_HOST;
QString NetWorkAPI::s_urlRouterList = ONLINE_URL_ROUTER_LIST;
QString NetWorkAPI::s_urlFeedBack = ONLINE_URL_FEEDBACK;
QString NetWorkAPI::s_urlDam = ONLINE_URL_DAM;
QString NetWorkAPI::s_urlDamFunc = ONLINE_URL_DAM_FUNC;
QString NetWorkAPI::s_urlOAlogin = ONLINE_URL_OALOGIN;
QString NetWorkAPI::s_urlHomePage = ONLINE_URL_HomePageList;
NetWorkAPI::NetWorkAPI()
{

}

NetWorkAPI::~NetWorkAPI()
{

}

void NetWorkAPI::InitNetEnv()
{
	ENV_TYPE eType = TNConfig::instance()->GetEnvType();
	switch (eType)
	{
	case TYPE_DEV:
		/*
        s_urlLocalH5Url = DEV_URL_H5;
        s_newFriendH5Url = DEV_URL_NEWFRIEND;
		s_urlRouterHost = DEV_URL_ROUTER_HOST;
		s_urlRouterList = DEV_URL_ROUTER_LIST;
		s_urlFeedBack = DEV_URL_FEEDBACK;
        s_urlHomePage = DEV_URL_HomePageList;
		*/
		TNPathUtil::SetToonFile(TOON_FILE_DEV);
		break;
	case TYPE_TEST:
		/*
        s_urlLocalH5Url = TEST_URL_H5;
        s_newFriendH5Url = TEST_URL_NEWFRIEND;
		s_urlRouterHost = TEST_URL_ROUTER_HOST;
		s_urlRouterList = TEST_URL_ROUTER_LIST;
		s_urlFeedBack = TEST_URL_FEEDBACK;
		s_urlDam = TEST_URL_DAM;
		s_urlDamFunc = TEST_URL_DAM_FUNC;
		s_urlOAlogin = TEST_URL_OALOGIN;
        s_urlHomePage = TEST_URL_HomePageList;
		*/
		TNPathUtil::SetToonFile(TOON_FILE_TEST);
		break;
	case TYPE_ONLINE:
		/*
        s_urlLocalH5Url = ONLINE_URL_H5;
        s_newFriendH5Url = ONLINE_URL_NEWFRIEND;
		s_urlRouterHost = ONLINE_URL_ROUTER_HOST;
		s_urlRouterList = ONLINE_URL_ROUTER_LIST;
		s_urlFeedBack = ONLINE_URL_FEEDBACK;
		s_urlDam = ONLINE_URL_DAM;
		s_urlDamFunc = ONLINE_URL_DAM_FUNC;
		s_urlOAlogin = ONLINE_URL_OALOGIN;
        s_urlHomePage = ONLINE_URL_HomePageList;
		*/
		TNPathUtil::SetToonFile(TOON_FILE_ONLINE);
		break;
    case TYPE_UCLOUD:
		/*
        s_urlLocalH5Url = UCLOUD_URL_H5;
        s_newFriendH5Url = UCLOUD_URL_NEWFRIEND;
        s_urlRouterHost = UCLOUD_URL_ROUTER_HOST;
        s_urlRouterList = UCLOUD_URL_ROUTER_LIST;
        s_urlFeedBack = UCLOUD_URL_FEEDBACK;
        //s_urlDam = UCLOUD_URL_DAM;
        //s_urlDamFunc = UCLOUD_URL_DAM_FUNC;
        //s_urlOAlogin = UCLOUD_URL_OALOGIN;
        s_urlHomePage = UCLOUD_URL_HomePageList;
		*/
        TNPathUtil::SetToonFile(TOON_FILE_UCLOUD);
        break;
	case TYPE_NONE:
	default:
		/*
        s_urlLocalH5Url = ONLINE_URL_H5;
        s_newFriendH5Url = ONLINE_URL_NEWFRIEND;
		s_urlRouterHost = ONLINE_URL_ROUTER_HOST;
		s_urlRouterList = ONLINE_URL_ROUTER_LIST;
		s_urlFeedBack = ONLINE_URL_FEEDBACK;
		s_urlDam = ONLINE_URL_DAM;
		s_urlDamFunc = ONLINE_URL_DAM_FUNC;
        s_urlHomePage = ONLINE_URL_HomePageList;
		*/
		TNPathUtil::SetToonFile(TOON_FILE_ONLINE);
		break;
	}
}
