//
// Created by juzenhon on 2017/8/31.
//

#ifndef TMTP_BIZOUTPUTBEAN_H
#define TMTP_BIZOUTPUTBEAN_H

#include <string>
#include <vector>
#include "CTNBaseBean.h"

using namespace std;

namespace toonim {
    class CTNGroupChatInfo : public CTNBaseOutputBean {
        
    public:
#ifdef RAPIDJSONWRAPPER
        void parse(CTNJsonValue &dataValue);
#else
        void parse(rapidjson::Value &dataValue);
#endif
        
        
        /* 群聊创建者 */
        string creatorFeedId;
        
        /* 群聊id */
        int64_t groupChatId;
        
        /* 群聊类型 1 群聊 2 聊天室 */
        int groupType = 1;
        
        /* 群聊topic */
        string topic;
        
        /* 描述：群聊名称 */
        string groupChatName;
        
        /* 群聊头像 */
        string groupChatHeadImage;
        
        /* 群聊人数 */
        int maxNum;
        
        /* 当前群聊人数 */
        long currNum;
        
        /* 增量查询时状态 */
        // 取值：1:新增或更新;0:删除;
        int status = 1;
        
        /* 是否免打扰 0否 1是 默认0关闭免打扰 */
        int disturbStatus;
        
        string myFeedId;
        
        string chatRoomId;
        
        // 名称全拼
        string titlePinyin;
        
        /* 群聊创建时间 */
        long version;
    };
}

#endif //TMTP_BIZOUTPUTBEAN_H
