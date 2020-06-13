//
// Created by juzenhon on 2017/8/29.
//

#ifndef TMTP_BIZINUPUTBEAN_H
#define TMTP_BIZINUPUTBEAN_H

#include <stdlib.h>
#include <string>
#include <vector>
#include "prettywriter.h"
#include "CTNHttpBizApi.h"

//using namespace rapidjson;
using namespace std;


namespace toonim {
    class CTNAddGroupMemberInput : public CTNBaseInputBean {
        
    public:
        CTNAddGroupMemberInput() {
        }
        
        CTNAddGroupMemberInput(int64_t groupId, const char *myFeedId, const char *myName,
                               int source,
                               vector<toonim::Feed> &member) {
            groupChatId = groupId;
            feedId = myFeedId;
            title = myName;
            invitSource = source;
            memberList = member;
        }
        
#ifdef RAPIDJSONWRAPPER
        //测试通过 wxy
        void serialize(CTNJsonWriter &writer) {
            writer["feedId"] = feedId;
            if (invitSource > -1) {
                writer["invitSource"] = invitSource;
            }
            writer["groupChatId"] = groupChatId;
            if (groupChatName.length() > 0) {
                writer["groupChatName"] = groupChatName;
            }
            if (title.length() > 0) {
                writer["title"] = title;
            }
            
            if (memberList.size() > 0) {
                CTNJsonArray arr(writer, "memberList");
                
                int32_t pos = 0;
                for (vector<toonim::Feed>::iterator iter = memberList.begin();
                     iter != memberList.end(); iter++) {
                    //@todo check lanhuaiyu
                    iter->serialize(&arr[pos++]);
                }
                arr.toString();
            }
        }
#else
        void serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer) {
            writer.StartObject();
            writer.Key("feedId");
            writer.String(feedId.c_str());
            if (invitSource > -1) {
                writer.Key("invitSource");
                writer.Int(invitSource);
            }
            writer.Key("groupChatId");
            writer.Int64(groupChatId);
            if (groupChatName.length() > 0) {
                writer.Key("groupChatName");
                writer.String(groupChatName.c_str());
            }
            if (title.length() > 0) {
                writer.Key("title");
                writer.String(title.c_str());
            }
            
            if (memberList.size() > 0) {
                writer.Key("memberList");
                writer.StartArray();
                for (vector<toonim::Feed>::iterator iter = memberList.begin();
                     iter != memberList.end(); iter++) {
                    //@todo check lanhuaiyu
                    iter->serialize(&writer);
                }
                writer.EndArray();
            }
            writer.EndObject();
        }
#endif
        
        /* 操作热feedId */
        string feedId;
        
        /* 加人群聊的方式   0邀请入群  1二维码 2主动加入 */
        int invitSource = -1;
        
        /* 群聊id */
        int64_t groupChatId = 0;
        
        /* 操作人的名称 */
        string title;
        
        string groupChatName;
        
        /* 操作的成员列表 */
        vector<toonim::Feed> memberList;
    };
    
    class CTNCreateGroupInput : public CTNBaseInputBean {
        
    public:
        CTNCreateGroupInput(toonim::Feed &feed, const char *groupChatName, vector<toonim::Feed> &members)
        : _feed(feed), _groupChatName(groupChatName), _members(members) {
        }
        
        ~CTNCreateGroupInput() {}
#ifdef RAPIDJSONWRAPPER
        //测试通过 wxy
        void serialize(CTNJsonWriter &writer) {
            writer["creatorFeedId"] = _feed._feedId;
            writer["creatorAvatarId"] = _feed._avatarId;
            writer["creatorTitle"] = _feed._title;
            writer["groupChatName"] = _groupChatName;
            
            CTNJsonArray array(writer, "memberList");
            
            int32_t i = 0;
            for (auto iter = _members.begin(); iter != _members.end(); ++iter){
                iter->serialize(&array[i++]);
            }
            
            array.toString();
        }
#else
        void serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer) {
            writer.StartObject();
            writer.Key("creatorFeedId");
            writer.String(_feed._feedId.c_str());
            writer.Key("creatorAvatarId");
            writer.String(_feed._avatarId.c_str());
            writer.Key("creatorTitle");
            writer.String(_feed._title.c_str());
            writer.Key("groupChatName");
            writer.String(_groupChatName.c_str());
            
            writer.Key("memberList");
            writer.StartArray();
            for (auto iter = _members.begin(); iter != _members.end(); ++iter){
                iter->serialize(&writer);
            }
            writer.EndArray();
            writer.EndObject();
        }
#endif
        
    private:
        toonim::Feed _feed;
        string _groupChatName;
        vector<toonim::Feed> _members;
    };
    
    class CTNObtainAllGroupChatInput : public CTNBaseInputBean {
        
    public:
        CTNObtainAllGroupChatInput(const char* userId,int64_t timestamp){
            _userId = userId;
            _version = timestamp;
        }
#ifdef RAPIDJSONWRAPPER
        //未测试
        void serialize(CTNJsonWriter &writer){
            writer["userId"] = _userId;
            writer["version"] = _version;
        }
#else
        void serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer){
            writer.StartObject();
            writer.String("userId");
            writer.String(_userId.c_str());
            writer.String("version");
            writer.Int64(_version);
            writer.EndObject();
        }
#endif
        
        string _userId;
        int64_t _version;
    };
    
    class CTNChangeDisturbInput : public CTNBaseInputBean {
        
    public:
        CTNChangeDisturbInput(const char *feedId, const char *userId, const char *groupChatId,
                              int32_t disturbStatus) {
            _feedId = feedId;
            _userId = userId;
            _groupChatId = groupChatId;
            _disturbStatus = disturbStatus;
        }
        
#ifdef RAPIDJSONWRAPPER
        //测试通过 wxy
        void serialize(CTNJsonWriter &writer) {
            writer["feedId"] = _feedId;
            writer["groupChatId"] = (int64_t)atoll(_groupChatId.c_str());
            writer["disturbStatus"] = _disturbStatus;
        }
#else
        void serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer) {
            writer.StartObject();
            writer.Key("feedId");
            writer.String(_feedId.c_str());
            //        writer.Key("userId");
            //        writer.String(_userId.c_str());
            writer.Key("groupChatId");
            writer.Int64((int64_t)atoll(_groupChatId.c_str()));
            writer.Key("disturbStatus");
            writer.Int(_disturbStatus);
            writer.EndObject();
        }
#endif
   
        string _feedId;
        string _groupChatId;
        string _userId;
        int32_t _disturbStatus;
    };
    
    class CTNObtainGroupByFeedIdsInput : public CTNBaseInputBean {
    public:
        CTNObtainGroupByFeedIdsInput(vector<string> &feedIdList, const char *userId) {
            _feedIdList = feedIdList;
            _userId = userId;
        }
        
#ifdef RAPIDJSONWRAPPER
        void serialize(CTNJsonWriter &writer) {
            CTNJsonArray array(writer, "feedIdList", false);
            for (int i = 0; i < _feedIdList.size(); i++) {
                writer = _feedIdList[i];
            }
            writer.toString();
            writer["userId"] = _userId;
            writer.toString();
        }

#else
        void serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer) {
            writer.StartObject();
            writer.Key("feedIdList");
            writer.StartArray();
            for (int i = 0; i < _feedIdList.size(); i++) {
                writer.String(_feedIdList[i].c_str());
            }
            writer.EndArray();
            writer.Key("userId");
            writer.String(_userId.c_str());
            writer.EndObject();
        }
#endif
        
        vector<string> _feedIdList;
        string _userId;
    };
    
    class CTNExitGroupChatInput : public CTNBaseInputBean {
    public:
        CTNExitGroupChatInput(const char *groupChatId, const char *feedId, const char *title) {
            _groupChatId = groupChatId;
            _feedId = feedId;
            _title = title;
        }
        
#ifdef RAPIDJSONWRAPPER
        void serialize(CTNJsonWriter &writer) {
            writer["groupChatId"] = _groupChatId;
            writer["feedId"] = _feedId;
            writer["title"] = _title;
        }
#else
        void serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer) {
            writer.StartObject();
            writer.Key("groupChatId");
            writer.String(_groupChatId.c_str());
            writer.Key("feedId");
            writer.String(_feedId.c_str());
            writer.Key("title");
            writer.String(_title.c_str());
            writer.EndObject();
        }

#endif
  
        string _groupChatId;
        string _feedId;
        string _title;
        
    };
    
    class CTNRemoveGroupChatMembersInput : public CTNBaseInputBean {
    public:
        CTNRemoveGroupChatMembersInput(const char *feedId, const char *title,int64_t groupChatId, vector<toonim::Feed> &members) {
            _feedId = feedId;
            _title = title;
            _groupChatId = groupChatId;
            _memberList = members;
        }
        
#ifdef RAPIDJSONWRAPPER
        //测试通过 wxy
        void serialize(CTNJsonWriter &writer) {
            writer["feedId"] = _feedId;
            writer["title"] = _title;
            writer["groupChatId"] = _groupChatId;
            CTNJsonArray array(writer, "memberList");
            
            int32_t i = 0;
            for (auto iter = _memberList.begin();iter != _memberList.end(); ++iter){
                iter->serialize(&array[i++]);
            }
            array.toString();
        }
#else
        void serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer) {
            writer.StartObject();
            writer.Key("feedId");
            writer.String(_feedId.c_str());
            writer.Key("title");
            writer.String(_title.c_str());
            writer.Key("groupChatId");
            writer.Int64(_groupChatId);
            writer.Key("memberList");
            writer.StartArray();
            for (auto iter = _memberList.begin();iter != _memberList.end(); ++iter)
                iter->serialize(&writer);
            writer.EndArray();
            writer.EndObject();
        }
#endif
        
        std::string _feedId;
        std::string _title;
        int64_t _groupChatId;
        vector<toonim::Feed> _memberList;
    };
    
    class CTNObtainGroupChatInfoInput : public CTNBaseInputBean {
    public:
        CTNObtainGroupChatInfoInput(vector<string> &groupChatIds) {
            _list = groupChatIds;
        }
        
#ifdef RAPIDJSONWRAPPER
        //测试通过 wxy
        void serialize(CTNJsonWriter &writer) {
            CTNJsonArray array(writer, "list", false);
            
            int32_t i = 0;
            for (auto iter = _list.begin(); iter != _list.end(); ++iter){
                array = *iter;
            }
            array.toString();
        }
#else
        void serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer) {
            writer.StartObject();
            writer.String("list");
            writer.StartArray();
            for (auto iter = _list.begin(); iter != _list.end(); ++iter)
                writer.String(iter->c_str());
            writer.EndArray();
            writer.EndObject();
        }
#endif
        
        vector<string> _list;
    };
    
    class CTNTransferGroupChatOwnerInput: public CTNBaseInputBean {
    public:
        CTNTransferGroupChatOwnerInput(int64_t groupChatId, const char* feedId, const char* title, toonim::Feed memberFeed) {
            _groupChatId = groupChatId;
            _feedId = feedId;
            _title = title;
            _memberFeed = memberFeed;
        }
        
#ifdef RAPIDJSONWRAPPER
        //测试通过 wxy
        void serialize(CTNJsonWriter &writer) {
            writer["groupChatId"] = _groupChatId;
            writer["feedId"] = _feedId;
            writer["title"] = _title;
            
            CTNJsonArray array(writer, "member");
            _memberFeed.serialize(&array);//若不希望拼接成数组形式，该处不加[]即可，若为数组形式，需添加[]为array[0]
            array.toString();
        }
#else
        void serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer) {
            writer.StartObject();
            
            writer.Key("groupChatId");
            writer.Int64(_groupChatId);
            writer.Key("feedId");
            writer.String(_feedId.c_str());
            writer.Key("title");
            writer.String(_title.c_str());
            writer.Key("member");
            _memberFeed.serialize(&writer);
            writer.EndObject();
            
        }

#endif
        
        int64_t _groupChatId;
        std::string _feedId;
        std::string _title;
        map<string, string> _member;
        toonim::Feed _memberFeed;
    };
    
    class CTNConversionSwitchInput : public CTNBaseInputBean {
        
    public:
        
#ifdef RAPIDJSONWRAPPER
        //测试通过 wxy
        void serialize(CTNJsonWriter &writer) {
            writer["sessionId"] = _sessionId;
            writer["status"] = _status;
            writer["chatType"] = _chatType;
            writer["updateTime"] = _updateTime;
        }
#else
        void serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer) {
            writer.StartObject();
            writer.Key("sessionId");
            writer.String(_sessionId.c_str());
            writer.Key("status");
            writer.Int(_status);
            writer.Key("chatType");
            writer.Int(_chatType);
            writer.Key("updateTime");
            writer.Int64(_updateTime);
            writer.EndObject();
        }
#endif
        
        
        /**
         * 以_拼接
         */
        string _sessionId;
        string _new_sessionId;
        
        /**
         * 1 置顶，0 取消置顶
         */
        int _status;
        
        int _chatType;
        
        int64_t _updateTime;
        
    };
    
    class CTNSwitchDisturbAndBlackListInput: public CTNBaseInputBean {
    public:
        CTNSwitchDisturbAndBlackListInput(const char* feedId, const char* passiveFeedId, const char* passiveUserId, int32_t bizType) {
            _feedId = feedId;
            _passiveFeedId = passiveFeedId;
            _passiveUserId = passiveUserId;
            _bizType = bizType;
        }
        
    public:
        
#ifdef RAPIDJSONWRAPPER
        //测试通过 wxy
        void serialize(CTNJsonWriter &writer) {
            writer["feedId"] = _feedId;
            writer["passiveFeedId"] = _passiveFeedId;
            writer["passiveUserId"] = _passiveUserId;
            writer["bizType"] = _bizType;
        }
#else
        void serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer) {
            writer.StartObject();
            
            writer.Key("feedId");
            writer.String(_feedId.c_str());
            writer.Key("passiveFeedId");
            writer.String(_passiveFeedId.c_str());
            writer.Key("passiveUserId");
            writer.String(_passiveUserId.c_str());
            writer.Key("bizType");
            writer.Int(_bizType);
            
            writer.EndObject();
        }
#endif
        
        string _feedId;
        string _passiveFeedId;
        string _passiveUserId;
        int32_t _bizType;
    };
    
    class CTNSwitchVerityInput: public CTNBaseInputBean {
    public:
        CTNSwitchVerityInput(int64_t groupChatId, int verifyStatus) {
            _groupChatId = groupChatId;
            _verifyStatus = verifyStatus;
        }
        
    public:
#ifdef RAPIDJSONWRAPPER
        void serialize(CTNJsonWriter &writer) {
            writer["groupChatId"] = _groupChatId;
            writer["verify"] = _verifyStatus;
        }
#else
        void serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer) {
            writer.StartObject();
            
            writer.Key("groupChatId");
            writer.Int64(_groupChatId);
            writer.Key("verify");
            writer.Int(_verifyStatus);
            
            writer.EndObject();
        }
#endif
        
        int64_t _groupChatId;
        int _verifyStatus;
    };
}

#endif //TMTP_BIZINUPUTBEAN_H
