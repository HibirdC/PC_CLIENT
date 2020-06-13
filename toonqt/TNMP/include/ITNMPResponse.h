//
//  ITNMPResponse.h
//  TNMP
//
//  Created by 兰怀玉 on 16/6/1.
//  Copyright © 2016年 兰怀玉. All rights reserved.
//

#ifndef ITNMPResponse_h
#define ITNMPResponse_h

#include <string>
#include <map>
#include <vector>
#include <stdint.h>

#include "TMTPConst.h"

using namespace std;

namespace Toon{
    class OffMsgCountResp;
    class MsgReq;
    class OffMsgResp;
    class HotSessionResp;
    class SyncSessionStatusResp;
    class SyncSessionStatusReq;
    class NotifyPresenceStatusResp;
}

class ITNMPResponse{
public:
    ITNMPResponse(){};
    virtual ~ITNMPResponse(){}
    
    virtual void loginResp(int code, vector<int>& contentTypes, map<string, int> &forbiddenMap) = 0;
    virtual void offMsgResp(Toon::OffMsgResp* offMsg) = 0;
    virtual void hotSessionResp(Toon::HotSessionResp* hotSessions) = 0;
    virtual void syncSessionStatusResp(Toon::SyncSessionStatusResp* sessionStatus) = 0;
    virtual void syncSessionStatusReq(Toon::SyncSessionStatusReq* sessionStatus) = 0;
    
	virtual void msgAck(string& msgId, int64_t seqId, int32_t type, string& from, string& to, int32_t result, int64_t timestamp) = 0;
    virtual void msgRecv(int type, Toon::MsgReq * req) = 0;
    virtual void netStatusChanged(TNMPNetStatus status) = 0;
    virtual void userOlineStatus(Toon::NotifyPresenceStatusResp& userStatus) = 0;
   
    //埋点信息
    virtual void daInfo(string& atrName, map<string, string> & property) = 0;//埋点信息
};


#endif /* ITNMPResponse_h */
