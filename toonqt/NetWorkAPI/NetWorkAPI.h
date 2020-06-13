#ifndef NETWORKAPI_H
#define NETWORKAPI_H

#include "NetWorkAPI_global.h"

class NETWORKAPI_EXPORT NetWorkAPI
{
public:
	NetWorkAPI();
	~NetWorkAPI();

	static void InitNetEnv();
    static QString s_urlLocalH5Url;
    static QString s_newFriendH5Url;
	static QString s_urlRouterHost;
	static QString s_urlRouterList; 
	static QString s_urlFeedBack;
	static QString s_urlDam;
	static QString s_urlDamFunc;
	static QString s_urlOAlogin;
    static QString s_urlHomePage;
private:

};//
#define URL_ROUTER_LIST NetWorkAPI::s_urlRouterList
#define URL_ROUTER_HOST "im.huohua.cn"
#define URL_FEEDBACK NetWorkAPI::s_urlFeedBack
#define URL_DAM NetWorkAPI::s_urlDam
#define URL_DAM_FUNC NetWorkAPI::s_urlDamFunc
#define URL_OA_LOGIN NetWorkAPI::s_urlOAlogin
#define URL_HOMEPAGE NetWorkAPI::s_urlHomePage
#endif // NETWORKAPI_H
