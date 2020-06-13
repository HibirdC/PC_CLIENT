//
// Created by juzenhon on 2017/9/7.
//

#ifndef TMTP_CTNSETTINGS_H
#define TMTP_CTNSETTINGS_H

#include "CTNHttpBizApi.h"

namespace toonim {
    
    
    class CTNSettings : public ITnSettings{
        
    private:
        static CTNSettings* _instance;
    public:
        CTNSettings(){}
        virtual ~CTNSettings(){}
        
        static CTNSettings* instance();
    
        virtual void setSessionSwitchTop(const char *chatId, const char *myFeedId, int chatType,
                                         bool top, int64_t timestamp, HttpCallback response,
                                         void *userData);
        
        virtual void getAllSwitchTopSession(int64_t timestamp,HttpCallback response, void *userData);

        /**
        *
        * @param response response
        * @param userData userData
        */
        virtual void obtainAppListInfo(HttpCallback response, void *userData);
        
        virtual void obtainAppInfo(const char *appId, HttpCallback response, void *userData);
        
        virtual void switchOnDisturbAndBlackList(const char *feedId, const char *passiveFeedId, const char *passiveUserId, int32_t bizType, HttpCallback response, void *userData);
        
        virtual void switchOffDisturbAndBlackList(const char *feedId, const char *passiveFeedId, const char *passiveUserId, int32_t bizType, HttpCallback response, void *userData);
        
        virtual void querySwitchDisturbAndBlackList(HttpCallback response, void *userData);

    };
    
    
}


#endif //TMTP_CTNSETTINGS_H
