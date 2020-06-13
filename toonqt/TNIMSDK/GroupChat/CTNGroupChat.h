//
// Created by juzenhon on 2017/8/28.
//

#ifndef TMTP_CHATBIZINTERFACE_H
#define TMTP_CHATBIZINTERFACE_H

#include <string>
#include <vector>
#include "CTNHttpBizApi.h"

using namespace std;

namespace toonim {
    
    class CTNGroupChat : public ITnGroupChat{
       
    private:
        static CTNGroupChat* _instance;
    public:
        CTNGroupChat();
        virtual ~CTNGroupChat();
        
        static CTNGroupChat* instance();
    
        virtual void createGroupChat(Feed &feed, const char *groupChatName, vector<Feed> &member,
                                     HttpCallback response,
                                     void *userData);
        
        
        virtual void obtainAllGroupChat(const char *userId, HttpCallback response, void *userData);
        virtual void changeDisturb(const char *feedId, const char *groupChatId, int disturbStatus,
                                   HttpCallback response, void *userData);
        
        virtual void addGroupChatMember(int64_t groupChatId, const char *feedId, const char *myName,
                                        int source,
                                        vector<Feed> &member, HttpCallback response, void *userData);
        
        virtual void obtainMembersByGroupChatId(const char *groupChatId, HttpCallback response,
                                                void *userData);
        
        
        virtual void obtainGroupChatsByFeedIds(vector<string> &feedIdList, const char *userId,
                                               HttpCallback response,
                                               void *userData);
        
        virtual void exitGroupChat(const char *groupChatId, const char *feedId, const char *title, HttpCallback response,
                                   void *userData);
        
        
        virtual void removeGroupChatMembers(const char *feedId, const char *title, int64_t groupChatId, vector<Feed> &removeList, HttpCallback response,void *userData);
        
        virtual void removeGroupChatMembersByFeedId(const char *feedId, const char *userId, const char *title,
                                                    HttpCallback response,
                                                    void *userData);
        
        virtual void updateGroupChat(int64_t groupChatId, const char *newGroupName, const char *myFeedId,
                                      const char *myName, HttpCallback response, void *userData);
        
     
        virtual void obtainGroupChatInfo(vector<string> &groupChatIdList, HttpCallback response,
                                         void *userData);
        
        virtual void groupChatTransferOwner(int64_t groupChatId, const char* feedId, const char* title, toonim::Feed memberFeed, HttpCallback response, void *userData);

        virtual void setupGroupChatVerify(int64_t groupChatId, int32_t verityStatus, HttpCallback response, void *userData);

    };
    
}

#endif //TMTP_CHATBIZINTERFACE_H
