//
//  CTNDataProcessThread.hpp
//  TNMP
//
//  Created by 兰怀玉 on 16/4/14.
//  Copyright © 2016年 兰怀玉. All rights reserved.
//

#ifndef CTNDataProcessThread_hpp
#define CTNDataProcessThread_hpp

#include "CThreadEx.h"
#include "CSafeQueue.h"

#include "tmtp.h"

#include <string>
#include <vector>
#include <map>
#include <mutex>
#include "TMTPConst.h"
#include "ITNMPResponse.h"



class CTNSendRecvThread;
class TNPacketBuffer;
class CTcpSocket;
class TMTPHostInfo;
class InflightMessage;


struct TNPacket{
    int16_t type;
    int64_t param;
    TNPacketBuffer *packetBuffer;
    
    TNPacket(){
        type  = 0;
        param = 0;
        packetBuffer = nullptr;
    }
};



const uint16_t TMTP_PACKET_TYPE_SEND = 1;
const uint16_t TMTP_PACKET_TYPE_RECV = 2;
const uint16_t TMTP_PACKET_TYPE_LOGOUT = 3;
const uint16_t TMTP_PACKET_TYPE_SOKCET_CLOSED = 4;
const uint16_t TMTP_PACKET_TYPE_SOKCET_FAILED = 5;
const uint16_t TMTP_PACKET_TYPE_SOKCET_SUCCESS = 6;



class CTNProcessThread : public CThreadEx
{
public:
    CTNProcessThread(ITNMPResponse *resp);
    ~CTNProcessThread();
  
    virtual void run();
    
    void setClientInfo(std::vector<TMTPHostInfo> & vctHostInfo, const char* clientId, int appType,int apnsType, const char* version, int deviceType = 0, int pushServiceType = 0);
    void setUserInfo(const char* username, const char* password, const char* deviceId,const char* deviceToken);
    void setDeviceToken(const char* deviceToken);
    void setAppPath(const char* appPath);
    
    void postPacket(TNPacket &packet);
  
    TNMPNetStatus getNetStatus();
    
    void login();
    void logout(bool notifyServer);
    
    void sendMsgReq(uint16_t type, Toon::MsgReq * req, bool inflight);

    //return messages include seqId messag
    void syncReq(Toon::SyncReq& req);
    
    void reqSyncSessionStatus(Toon::SyncSessionStatusReq & req);
    void reqPullOffMsg(Toon::PullOffMsgReq & req);
    void clientReport(Toon::ClientReport & req);
    void subOrganizeReq(Toon::SubOrganizeReq & req);
    
private:
    
    bool currSocketValid();
    void createSocketThread();
    void processSuccessRSThread(int theadId);
    void destoryRSThread(bool forceStop);
    void forceDestoryAllThread();
    
    void reconnect();
    bool isLogout();
    
 
    void sendPacket(uint16_t type, const char *payload, size_t length);
    void sendAck(int type, Toon::MsgReq* req);
    void checkPing();
    void reqHotSession(int64_t timestamp);

    void forceResendInflight();
    void checkRecvCache();
 
    void processPacketMessage(TNPacketBuffer* packetBuffer);
    void processRecvMsgReq(TNPacketBuffer* packetBuffer);
    void processSessionStatusReq(TNPacketBuffer* packetBuffer);
    void processMsgAck(TNPacketBuffer* packetBuffer);
    void processConnectResp(TNPacketBuffer* packetBuffer);
    void processOffMsgResp(TNPacketBuffer* packetBuffer);
    void processHotSessionResp(TNPacketBuffer* packetBuffer);
    void processSyncSessionStatusResp(TNPacketBuffer* packetBuffer);
    void processUserOnlineStatus(TNPacketBuffer* packetBuffer);
  
    void processKickout();
    
    
    void sendPacket();
    
    virtual void setNetStatus(TNMPNetStatus status);
    
    void daInfo(string attrName, map<string, string> propertyJson =  map<string, string>());
private:
    
    ITNMPResponse *m_response;
    int64_t m_pingReqTime;
    int m_reconnects;
    bool m_offMsgCountOk;//离线消息数是否已经获取，断线重连需要复位
 
    std::mutex m_mutexNetStatus;
    TNMPNetStatus m_netStatus;
    
    //跑马策略保存地址
//    std::mutex m_mutexRSThread;
    std::vector<CTNSendRecvThread*> m_vctRSThread;
    CTNSendRecvThread *m_pSRThread;
   
    CSafeQueue<TNPacket> m_queuePacket;
    
    std::vector<InflightMessage*> _recvCache;
    
    
 };

#endif /* CTNDataProcessThread_hpp */
