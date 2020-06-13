//
//  CTNDataProcessThread.cpp
//  TNMP
//
//  Created by 兰怀玉 on 16/4/14.
//  Copyright © 2016年 兰怀玉. All rights reserved.
//

#include "CTNProcessThread.h"
#include  <mutex>
#include <thread>
#include <time.h>

//#include "CThreadEx.h"
#include "CTNSendRecvThread.h"
#include "tmtp_type.h"
#include "tmtp.h"

#ifdef WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <regex>
#include <random>
#include "CTNInflightVector.h"
#include "TMTPConst.h"
#include "CLog.h"

#define REQ_ID getReqId()

std::string getReqId(){
//    char buf[64] = {0};
//    static int s_reqId = 1000;
//    s_reqId++;
    std::uniform_int_distribution<uint64_t> dis;
    
    std::random_device rd;
    stringstream stff;
    stff<<rd();
//    sprintf(buf, "%lld", rd());
    
    return  stff.str();
}

string intToString(int i)
{
    stringstream stff;
    stff<<i;
 
    return stff.str();
}

CTNProcessThread::CTNProcessThread(ITNMPResponse *resp):m_response(resp)
{
    TNMPLOG("CTNProcessThread::CTNProcessThread:"<<getId());
    
    m_pingReqTime = 0;
    m_reconnects = 0;
    m_offMsgCountOk = false;
    m_netStatus = TNMPNetConnecting;
    
    m_pSRThread = NULL;
}


CTNProcessThread::~CTNProcessThread()
{
    TNMPLOG("CTNProcessThread::~CTNProcessThread enter:"<<this->getId());
    this->forceDestoryAllThread();
    
    TNMPLOG("CTNProcessThread::~CTNProcessThread exit:"<<this->getId());
}


void CTNProcessThread::setNetStatus(TNMPNetStatus status)
{
//    std::unique_lock<std::mutex> unilock(m_mutexNetStatus);
    CTNCMutexGuard guard(m_mutexNetStatus, "setNetStatus");

    if (m_netStatus == status) {
        return;
    }
    
    m_netStatus = status;
    
    TNMPLOG("setNetStatus:"<<m_netStatus<<" thread:"<<this->getId());
    
    if (m_response != NULL) {
        m_response->netStatusChanged(status);
    }
    else {
        TNMPLOG("m_response is NULL don't callback to caller netstatus:"<<m_netStatus);
    }
}

TNMPNetStatus CTNProcessThread::getNetStatus()
{
//    std::unique_lock<std::mutex> unilock(m_mutexNetStatus);
    CTNCMutexGuard guard(m_mutexNetStatus, "getNetStatus");

    TNMPLOG("getNetStatus :"<<m_netStatus<<" thread:"<<this->getId());
    
    return m_netStatus;
}

bool CTNProcessThread::isLogout()
{
    CTNCMutexGuard guard(m_mutexNetStatus, "isLogout");
    if (m_netStatus == TNMPNetLogout){
        return true;
    }

    return false;
}


void CTNProcessThread::postPacket(TNPacket &packet)
{
    TNMPLOG("postPacket type:"<<packet.type);
    
    m_queuePacket.push(packet);
}

void CTNProcessThread::createSocketThread()
{
    TNMPLOG("createSocketThread enter"<<" thread:"<<this->getId());
    
    if (m_pSRThread != NULL) {
        m_pSRThread->stop();
        m_pSRThread = NULL;
    }
    
    TNMPLOG("createSocketThread 1"<<" thread:"<<this->getId());
    
    TMTPHostInfo hostInfo = CONFIG->hostInfo();
    for (int i = 0; i < 1; i++)
    {
        CTNSendRecvThread *pSRThread = new CTNSendRecvThread(this);
        pSRThread->setHostInfo(hostInfo);
        
        pSRThread->start();
        
        m_vctRSThread.push_back(pSRThread);
        TNMPLOG("start RSThread:"<<pSRThread->getId());
        
    }
    TNMPLOG("createSocketThread 3"<<" thread:"<<this->getId());

    m_pingReqTime = 0;
}

void CTNProcessThread::processSuccessRSThread(int threadId)
{
    TNMPLOG("processSuccessRSThread:"<<threadId);
    if (m_pSRThread != NULL) {
        TNMPLOG("TCP CONNECT SUCCESS RS Thread:"<<threadId<<" current RSThread:"<<m_pSRThread->getId());
        return ;
    }
    
    
    for (int i = 0; i < m_vctRSThread.size(); i++)
    {
        CTNSendRecvThread* pThread = m_vctRSThread[i];
        if (pThread->getId() == threadId) {
            m_pSRThread = pThread;
           
            //need dataInfo
#ifndef WIN32
            map<string, string> property;
            if (m_pSRThread->hostInfo().isSSL){
                property["channel_type"] = "SSL加密";
            }
            else{
                property["channel_type"] = "无加密";
            }
            
            this->daInfo("MNetworkSuccess", property);
#endif
            TNMPLOG("SELECT TCP CONNECT SUCCESS RS Thread:"<<m_pSRThread->getId());
        }
        else{
            pThread->stop();
        }
    }
}


void CTNProcessThread::destoryRSThread(bool forceStop)
{
    TNMPLOG("ENTER destoryRSThread:"<<forceStop<<" size:"<<m_vctRSThread.size());

    if (this->getNetStatus() == TNMPNetConnecting){
        TNMPLOG("destoryRSThread  TNMPNetConnecting don't destory:"<<m_vctRSThread.size());
        return;
    }
    
    if (m_vctRSThread.size() == 0) {
        TNMPLOG("m_vctRSThread size:"<<m_vctRSThread.size());
        return ;
    }
    if (m_pSRThread != NULL && forceStop) {
        m_pSRThread->stop();
        m_pSRThread = NULL;
    }

    TNMPLOG("destoryRSThread:"<<forceStop);

    std::vector<CTNSendRecvThread*>::iterator itTmp = m_vctRSThread.begin();
    while (itTmp != m_vctRSThread.end()){
        CTNSendRecvThread* pThread = *itTmp;
        if (pThread == m_pSRThread){
            TNMPLOG("current Thread don't erase:"<<pThread->getId());
            itTmp ++;
            continue;
        }
        
        if (pThread->isDied()) {
            TNMPLOG("destoryRSThread will delete thread:"<<pThread->getId());
            delete pThread;
            itTmp = m_vctRSThread.erase(itTmp);
            continue;
        }
        
        pThread->stop();
        TNMPLOG("RSThread is not Died:"<<pThread->getId());
     
        itTmp ++;
    }

    TNMPLOG("EXIT destoryRSThread");
}

//退出时强制退出所有线程，最多重试1分钟
void CTNProcessThread::forceDestoryAllThread()
{
    TNMPLOG("CTNProcessThread::forceDestoryAllThread enter:"<<this->getId());

    for (int i = 0; i < 10; i++) {
        if (m_vctRSThread.empty()) {
            break;
        }

        this->destoryRSThread(true);

        tn_msleep(3000);
    }
    
    TNMPLOG("CTNProcessThread::forceDestoryAllThread exit:"<<this->getId());
    
}

//记录，如果超过两个keeplive 未收到CONNACK， 重连
//m_pingReqTime > 0 表示已经调用过login；
void CTNProcessThread::run()
{
    TNMPLOG("start CTNProcessThread:"<<getId());

    this->setNetStatus(TNMPNetConnecting);
    //重连reset index
    CONFIG->resetCurrHostIndex();
 
    this->createSocketThread();
    
    auto lambdaCheckInflight = [this](bool isResend, InflightMessage* inflightMsg)->void{
        if (isResend){
            inflightMsg->req->flags |= FLAG_BIT_ISDUP;
            this->sendMsgReq(inflightMsg->type, inflightMsg->req, false);
        }
        else if (m_response != NULL){
            m_response->msgAck(inflightMsg->req->msg_id, inflightMsg->req->seq_id,inflightMsg->type,inflightMsg->req->from,inflightMsg->req->to, -1, inflightMsg->req->timestamp);
        }
    };
    
    while (isRunning()) {
        if (this->isLogout()) {
            TNMPLOG("getNetStatus is TNMPNetLogout, exit Process trhead!");
            break;
        }
        
        TNPacket packet;
        int ret = m_queuePacket.pop(packet, CONFIG->keepAlive());
        if (!this->isRunning()){
            TNMPLOG("stoped!!, exit Process trhead!"<<this->isRunning());
            DELETE_PACKET(packet.packetBuffer);
            break;
        }
        
        if (this->getNetStatus() == TNMPNetConnected) {
            INFLIGHT_VECTOR->checkInflight(false, lambdaCheckInflight);
        }
        else if (this->getNetStatus() == TNMPNetNone){
            this->reconnect();
        }
        
        if (ret == SFQUEUE_TIMEOUT) {
            
            TNMPLOG("Wait time out, will checkPing");
            
            this->checkPing();
            
            //check RSThread
            this->destoryRSThread(false);
            continue;
        }

        TNMPLOG("PACKET Process type:"<<packet.type<<" param:"<<packet.param);
        switch (packet.type) {
            case TMTP_PACKET_TYPE_RECV:
            {
                this->processPacketMessage(packet.packetBuffer);
                
                break;
            }
            case TMTP_PACKET_TYPE_SEND:
            {
                if (m_pSRThread != nullptr){
                    m_pSRThread->sendPacket(packet.packetBuffer);
                }
                else{
                    this->reconnect();
                }
            
                break;
            }
            case TMTP_PACKET_TYPE_SOKCET_SUCCESS:
            {
                int threadId = (int)packet.param;
                TNMPLOG("TMTP_PACKET_TYPE_SOKCET_SUCCESS:"<<threadId);
                this->processSuccessRSThread(threadId);
                
                if (m_pingReqTime == 0) {
                    m_pingReqTime = time(NULL);
                    this->login();
                }
                
                break;
            }
            case TMTP_PACKET_TYPE_LOGOUT:
            {
                TNMPLOG("TMTP_PACKET_TYPE_LOGOUT;");
//                setNetStatus(TNMPNetLogout);

                if (m_pSRThread != nullptr){
                    if (packet.param != 0){
                        //用户主动退出时需要置空，防止消息串用户
                        m_response = NULL;
                        
                        TNPacketBuffer packerBuffer;
                        packerBuffer.type = TYPE_DISCONNECT;
                        packerBuffer.length = 0;
                        m_pSRThread->sendPacket(&packerBuffer);
                        TNMPLOG("SEND TYPE_DISCONNECT TO SERVER");
                    }

                    tn_msleep(300);//延时关闭socket，避免与上次发送消息时间间距过短导致服务端无法处理之前的消息的情况 wxy
                    
                    m_pSRThread->stop();
                }
                
                setNetStatus(TNMPNetLogout);
                m_reconnects = 0;
                
                goto threadStop;
                break;
            }
            case TMTP_PACKET_TYPE_SOKCET_FAILED:
            {
                TNMPLOG("TMTP_PACKET_TYPE_SOKCET_FAILED;");
                
                this->daInfo("MNetworkFail");

                this->setNetStatus(TNMPNetNone);
                this->reconnect();
                break;
            }
            case TMTP_PACKET_TYPE_SOKCET_CLOSED:
            {
                //增加判断解决Android 黑屏后连接上后闪断频繁重连问题
                TNMPLOG("CTNProcessThread TMTP_PACKET_TYPE_SOKCET_CLOSED RSThread:"<<packet.param);
                if (m_pSRThread != nullptr && packet.param == m_pSRThread->getId()){
                    if (this->getNetStatus() != TNMPNetLogout) {
                        this->setNetStatus(TNMPNetNone);
                    }
                    
                    this->reconnect();
                }
             
                break;
            }
                
            default:
                TNMPLOG("TCP can't parse on type:"<<packet.type);
                break;
        }
        
        DELETE_PACKET(packet.packetBuffer);
    }
    
threadStop:
    TNMPLOG("CTNProcessThread exit 1:"<<getId());
    
    try {
        m_response = NULL;
        //set run flag
        this->stop();
        this->setNetStatus(TNMPNetNone);
        
        this->forceDestoryAllThread();
    } catch (...) {
        TNMPLOG("Exception occur on CTNProcessThread run :"<<getId());
    }
    
    TNMPLOG("CTNProcessThread exit 2:"<<getId());
}

void CTNProcessThread::setClientInfo(std::vector<TMTPHostInfo> & vctHostInfo, const char* clientId, int appType,int apnsType, const char* version, int deviceType, int pushServiceType)
{
    CONFIG->setHostInfos(vctHostInfo);

    CONFIG->clientId(clientId);
    
    CONFIG->appType(appType);
    CONFIG->apnsType(apnsType);
    
    CONFIG->version(version);
    
    CONFIG->deviceType(deviceType);
    CONFIG->pushServiceType(pushServiceType);
}


void CTNProcessThread::setDeviceToken(const char* deviceToken)
{
    if (deviceToken != NULL) {
        TNMPLOG("setDeviceToken  token:"<<deviceToken);
    }
    
    CONFIG->deviceToken(deviceToken);
}

void CTNProcessThread::setUserInfo(const char* username, const char* password, const char* deviceId, const char* deviceToken)
{
    if (deviceToken != NULL) {
        TNMPLOG("setUserInfo  deviceToken:"<<deviceToken);
    }
    
    CONFIG->username(username);
    CONFIG->password(password);
    CONFIG->deviceId(deviceId);
    CONFIG->deviceToken(deviceToken);
    
    this->setNetStatus(TNMPNetConnecting);
}

void CTNProcessThread::setAppPath(const char* appPath)
{
    if (appPath == NULL){
        return;
    }
    
    CONFIG->appPath(appPath);
}

void CTNProcessThread::login()
{
    Toon::ConnectReq loginReq;
    loginReq.client_id = CONFIG->clientId();
    loginReq.user_name = CONFIG->username();
    loginReq.password = CONFIG->password();
    loginReq.deviceToken = CONFIG->deviceToken();
    loginReq.device_type = CONFIG->deviceType();
    loginReq.deviceId = CONFIG->deviceId();
    loginReq.app_type = CONFIG->apnsType();
    loginReq.toon_type = CONFIG->appType();
    loginReq.version = CONFIG->version();
    loginReq.protocol_version = 2;
    loginReq.push_service_type = CONFIG->pushServiceType();
   
    if (loginReq.password.length() == 0){
        TNMPLOG("CTNProcessThread::login password is EMPTY!!!");
    }

    taf::JceOutputStream<taf::BufferWriter> tos;
    loginReq.writeTo(tos);
    
    sendPacket(TYPE_CONNECTREQ, tos.getBuffer(), tos.getLength());
    
    TNMPLOG("CTNProcessThread::login:"<<loginReq.user_name<<" client_id:"<<loginReq.client_id<<" devicetoken:"<<loginReq.deviceToken<<" toonType:"<<loginReq.toon_type<<" push_service_type:"<<loginReq.push_service_type<<" appType:"<<loginReq.app_type);
}



void CTNProcessThread::logout(bool notifyServer)
{
    TNMPLOG("CTNProcessThread::logout notifyServer:"<<notifyServer<<" thread:"<<getId());
    //以下操作放到异步队列处理之后，该处若提前设置状态，导致后面发送同步未读数操作由于状态原因无法发送 wxy
//    setNetStatus(TNMPNetLogout);
//    m_reconnects = 0;

    TNPacket packet;
    packet.type = TMTP_PACKET_TYPE_LOGOUT;
    packet.param = notifyServer;
    m_queuePacket.push(packet);
}



void CTNProcessThread::reconnect()
{
    if (getNetStatus() == TNMPNetConnecting){
        TNMPLOG("TNMPNetConnecting don't connect"<<getId());
        return;
    }
    
    setNetStatus(TNMPNetConnecting);
    
    m_reconnects ++;
    
    int sleepTime = RECONN_STEP[m_reconnects%RECONN_MAX];
    
    TNMPLOG("CTNProcessThread reconnect:"<<sleepTime);
	tn_msleep(sleepTime*1000);
   
    TNMPLOG("will reconnect:"<<getId());
    createSocketThread();
    
    this->daInfo("BreakReconnection");
}

void CTNProcessThread::sendMsgReq(uint16_t type, Toon::MsgReq * req, bool inflight)
{
    if (req == NULL) {
        TNMPLOG("msg req is empty:"<<type);
        return;
    }
    
    
    taf::JceOutputStream<taf::BufferWriter> tos;
    req->writeTo(tos);
    
    //修正时间，防止不必要的重发
    req->timestamp = time(NULL);
    
//    离线未拉完，不能发送消息，否则离线消息数会发生错误
    sendPacket(type, tos.getBuffer(), tos.getLength());
    
    if (inflight) {
        //增加
        InflightMessage* inflightMsg = new InflightMessage();
        inflightMsg->type = type;
        inflightMsg->req = req;
        inflightMsg->size = (int)tos.getLength();
        
        INFLIGHT_VECTOR->addToInflight(inflightMsg);
    }
    
    if ((req->flags & FLAG_BIT_ISDUP)){
        map<string, string> property;
        property["msg_id"] = req->msg_id;
        property["msg_type"] = intToString(type);
        property["msg_size"] = intToString((int)tos.getLength());
        
        this->daInfo("MMessageResend", property);
    }

}


void CTNProcessThread::processPacketMessage(TNPacketBuffer* packetBuffer)
{
    if (packetBuffer == nullptr){
        return;
    }
    TNMPLOG("processPacketMessage type:"<<packetBuffer->type<<" length:"<<packetBuffer->length);
    
    switch (packetBuffer->type) {
        case TYPE_GROUP_NOTIFY_REQ:
        case TYPE_NOTIFY_MSGREQ:
        case TYPE_SINGLE_CHAT_MSGREQ:
        case TYPE_GROUP_CHAT_MSGREQ:
        case TYPE_SYNC_MSGREQ:
        case TYPE_MOMENT_MSGREQ:
        case TYPE_MSG_SINGLE_OPERATE:
        case TYPE_MSG_GROUP_OPERATE:
        {
            m_pingReqTime = 0;
            this->processRecvMsgReq(packetBuffer);
            
            break;
        }
        case TYPE_HOT_SESSION_RESP:
        {
            m_pingReqTime = 0;
            
            this->processHotSessionResp(packetBuffer);
            break;
        }
        case TYPE_SYNC_SESSION_STATUS_REQ:
        {
            m_pingReqTime = 0;
            
            this->processSessionStatusReq(packetBuffer);
            break;
        }
        case TYPE_SYNC_SESSION_STATUS_RESP:
        {
            m_pingReqTime = 0;
            
            this->processSyncSessionStatusResp(packetBuffer);
            break;
        }
        case TYPE_OFFMSG_RESP:
        {
            m_pingReqTime = 0;
            this->processOffMsgResp(packetBuffer);
            
            break;
        }
        case TYPE_MSGACK:
        {
            m_pingReqTime = 0;
            this->processMsgAck(packetBuffer);
            
            break;
        }
        case TYPE_PING:
            m_pingReqTime = 0;
            break;
        case TYPE_CONNECTRESP:
        {
            this->processConnectResp(packetBuffer);
            
            CONFIG->resetCurrHostIndex();
            
            break;
        }
        case TYPE_KICKOUT:
        {
            m_pingReqTime = 0;
            this->processKickout();
            break;
        }
        case TYPE_CLIENT_SYNCRESP:
        {
            TNMPLOG("TYPE_CLIENT_SYNCRESP OK;");
            break;
        }
        case TYPE_NOTIFY_CLIENT_PRESENCE:
        {
            this->processUserOnlineStatus(packetBuffer);
            break;
        }
    }
    
}

void CTNProcessThread::processRecvMsgReq(TNPacketBuffer* packetBuffer)
{
    if  (packetBuffer == NULL){
        return;
    }
    
    Toon::MsgReq *msgReq = new Toon::MsgReq();
    taf::JceInputStream<taf::BufferReader> is;
    
    is.setBuffer(packetBuffer->payload, packetBuffer->length);
    
    msgReq->readFrom(is);
    
    if (m_response == nullptr || !m_offMsgCountOk){
        InflightMessage* inflightMsg = new InflightMessage();
        inflightMsg->type = packetBuffer->type;
        inflightMsg->req = msgReq;
        
        _recvCache.push_back(inflightMsg);
        
        TNMPLOG("processRecvMsgReq m_offMsgCountOk is false ,recving msg will be cached!!!");
        return;
    }
    
    //call back to caller
    m_response->msgRecv(packetBuffer->type, msgReq);
    
    //ack
    sendAck(packetBuffer->type, msgReq);
    
    delete msgReq;
}

void CTNProcessThread::processSessionStatusReq(TNPacketBuffer* packetBuffer)
{
    if  (packetBuffer == NULL){
        return;
    }
    
    Toon::SyncSessionStatusReq *sessionStatusReq = new Toon::SyncSessionStatusReq();
    taf::JceInputStream<taf::BufferReader> is;
    
    is.setBuffer(packetBuffer->payload, packetBuffer->length);
    
    sessionStatusReq->readFrom(is);
    
    //call back to caller
    if (m_response != NULL) {
        m_response->syncSessionStatusReq(sessionStatusReq);
    }
    
    delete sessionStatusReq;
}

void CTNProcessThread::processMsgAck(TNPacketBuffer* packetBuffer)
{
    if  (packetBuffer == NULL){
        return;
    }
    
    Toon::MsgAck msgAck;
    taf::JceInputStream<taf::BufferReader> is;
    
    is.setBuffer(packetBuffer->payload, packetBuffer->length);
    
    msgAck.readFrom(is);
    
    TNMPLOG("processMsgAck:"<<msgAck.msg_id);
    
    //call back to caller
    if (m_response != NULL) {
        m_response->msgAck(msgAck.msg_id, msgAck.seq_id,msgAck.type,msgAck.from,msgAck.to, msgAck.retcode, msgAck.timestamp);
    }
    else{
        TNMPLOG("processMsgAck m_response is NULL:"<<msgAck.msg_id);
    }
    
    
    int size = INFLIGHT_VECTOR->removeInflightMutex(msgAck.msg_id);
    
    map<string, string> property;
    property["msg_id"] = msgAck.msg_id;
    property["msg_type"] = intToString(msgAck.type);
    property["msg_size"] = intToString(size);
    
    this->daInfo("MMessageSuccess", property);
}

void CTNProcessThread::processConnectResp(TNPacketBuffer* packetBuffer)
{
    if  (packetBuffer == NULL){
        return;
    }
    
    Toon::ConnectResp loginResp ;
    taf::JceInputStream<taf::BufferReader> is;
    
    is.setBuffer(packetBuffer->payload, packetBuffer->length);
    loginResp.readFrom(is);
    TNMPLOG("CONNECT RESP:"<<Toon::etos(loginResp.code));
    
    //call back to caller
    if (m_response != NULL) {
        m_response->loginResp(loginResp.code, loginResp.vforbidden_content_type, loginResp.mToonTypeSwitch);
    }
    
    if (loginResp.code == Toon::CONNECT_RESULT_SUCCESS) {
        setNetStatus(TNMPNetRecving);
        
        m_offMsgCountOk = false;
   
        this->reqHotSession(CONFIG->hsTimestamp());
     
        m_reconnects = 0;
        
    }
    else if (loginResp.code == Toon::CONNECT_RESULT_SERVICE_UNAVAILABLE){
        setNetStatus(TNMPNetNone);
    }
    else
    {
        setNetStatus(TNMPNetLogout);
        m_reconnects = 0;
    }
  
}

//void CTNProcessThread:
void CTNProcessThread::daInfo(string attrName, map<string, string> property)
{
    if (m_response != NULL) {
        m_response->daInfo(attrName, property);
    }
}

void CTNProcessThread::processKickout()
{
    TNMPLOG("CTNProcessThread::processKickout!");
    setNetStatus(TNMPNetLogout);
    
    m_reconnects = 0;
    
    if (m_response != NULL) {
        vector<int> vctTmp;
        map<string, int> tmpMap;
        m_response->loginResp(Toon::CONNECT_RESULT_KICKOUT, vctTmp, tmpMap);
    }
    else{
        TNMPLOG("processKickout m_response is NULL");
    }
}

void CTNProcessThread::forceResendInflight()
{
    TNMPLOG("forceResendInflight enter");
    m_offMsgCountOk = true;
    this->setNetStatus(TNMPNetConnected);
 
    this->checkRecvCache();
    
    //重新登录，强行重发堆积消息
    auto lambda = [this](InflightMessage* inflightMsg)->void{
       
        inflightMsg->req->flags |= FLAG_BIT_ISDUP;
        TNMPLOG("resend msg:"<<inflightMsg->req->msg_id<<" flags:"<<inflightMsg->req->flags);
        
        this->sendMsgReq(inflightMsg->type, inflightMsg->req, false);
        
     };
    
    INFLIGHT_VECTOR->forceResend(lambda);
    
    TNMPLOG("forceResendInflight exit");
}


//将缓存收取到的消息，通知到业务处理方
void CTNProcessThread::checkRecvCache()
{
//    std::unique_lock<std::mutex> unilock(m_mutexRSThread);
//    CTNCMutexGuard guard(m_mutexRSThread, "checkRecvCache");
    
    TNMPLOG("checkRecvCache:")
    
    if (m_response == nullptr){
        return;
    }
    
    for (int i = 0; i < _recvCache.size(); i++){
        InflightMessage* inflightMsg = _recvCache[i];
        m_response->msgRecv(inflightMsg->type, inflightMsg->req);
        
        TNMPLOG("checkRecvCache:"<<inflightMsg->req->msg_id)
        delete inflightMsg;
    }
    
    _recvCache.clear();
}

void  CTNProcessThread::processOffMsgResp(TNPacketBuffer* packetBuffer)
{
    if  (packetBuffer == NULL || packetBuffer->length == 0){
        return;
    }
    
    Toon::OffMsgResp offMsgResp;
    taf::JceInputStream<taf::BufferReader> is;
    
    is.setBuffer(packetBuffer->payload, packetBuffer->length);
    
    offMsgResp.readFrom(is);
    TNMPLOG("processOffMsgResp msg size:"<<offMsgResp.msgs.size());
    
    //call back to caller
    if (m_response != NULL) {
        m_response->offMsgResp(&offMsgResp);
    }
    else{
        TNMPLOG("processOffMsgResp m_response is NULL");
    }
   
}

void CTNProcessThread::processHotSessionResp(TNPacketBuffer* packetBuffer)
{
    if  (packetBuffer == NULL || packetBuffer->length == 0){
        return;
    }
    
    Toon::HotSessionResp hotSessionResp;
    taf::JceInputStream<taf::BufferReader> is;
    
    is.setBuffer(packetBuffer->payload, packetBuffer->length);
    
    hotSessionResp.readFrom(is);
    
    TNMPLOG("processHotSessionResp vSessionInfo size:"<<hotSessionResp.vSessionInfo.size()<<" code:"<<hotSessionResp.code<<" timestamp:"<<hotSessionResp.timestamp<<" req_id:"<<hotSessionResp.req_id);
    
    //call back to caller
    if (m_response != NULL) {
        m_response->hotSessionResp(&hotSessionResp);
    }
    else{
        TNMPLOG("processHotSessionResp m_response is NULL");
    }
   
    if (OFFMSG_CODE_MORE == hotSessionResp.code) {
        this->reqHotSession(hotSessionResp.timestamp);
    }
    else if (OFFMSG_CODE_OK == hotSessionResp.code) {
        CONFIG->setHSTimestamp(hotSessionResp.timestamp);
        this->forceResendInflight();
    }
    else {
        TNMPLOG("processHotSessionResp failed!,will reconnect");
        
        setNetStatus(TNMPNetNone);
        
        reconnect();
    }
    
}

void CTNProcessThread::processSyncSessionStatusResp(TNPacketBuffer* packetBuffer)
{
    if  (packetBuffer == NULL || packetBuffer->length == 0){
        return;
    }
    
    Toon::SyncSessionStatusResp syncSessionResp;
    taf::JceInputStream<taf::BufferReader> is;
    
    is.setBuffer(packetBuffer->payload, packetBuffer->length);
    
    syncSessionResp.readFrom(is);
     
    TNMPLOG("processSyncSessionStatusResp msg req_id:"<<syncSessionResp.req_id<<" code:"<<syncSessionResp.code);
    
    //call back to caller
    if (m_response != NULL) {
        m_response->syncSessionStatusResp(&syncSessionResp);
    }
    else{
        TNMPLOG("processSyncSessionStatusResp m_response is NULL");
    }
  
}


void CTNProcessThread::processUserOnlineStatus(TNPacketBuffer* packetBuffer)
{
    if  (packetBuffer == NULL || packetBuffer->length == 0){
        return;
    }

    Toon::NotifyPresenceStatusResp clientOnlineResp;
    taf::JceInputStream<taf::BufferReader> is;
    
    is.setBuffer(packetBuffer->payload, packetBuffer->length);
    clientOnlineResp.readFrom(is);
    
    TNMPLOG("processUserOnlineStatus msg vecPresenceStatus:"<<clientOnlineResp.vecPresenceStatus.size());
    
    //call back to caller
    if (m_response != NULL) {
        m_response->userOlineStatus(clientOnlineResp);
    }
    else{
        TNMPLOG("processUserOnlineStatus m_response is NULL");
    }
}

void CTNProcessThread::syncReq(Toon::SyncReq& req)
{
    
    taf::JceOutputStream<taf::BufferWriter> tos;
    req.writeTo(tos);
    
    sendPacket(TYPE_CLIENT_SYNCREQ, tos.getBuffer(), tos.getLength());
}

void CTNProcessThread::reqHotSession(int64_t timestamp)
{
    Toon::HotSessionReq req;
    if (req.req_id.length() == 0){
        req.req_id = REQ_ID;
    }
    req.timestamp = timestamp;
    
    taf::JceOutputStream<taf::BufferWriter> tos;
    req.writeTo(tos);
    
    sendPacket(TYPE_HOT_SESSION_REQ, tos.getBuffer(), tos.getLength());
    
    TNMPLOG("reqHotSession:"<<timestamp<<" req_id:"<<req.req_id);
    
    map<string, string> property;
    this->daInfo("MOfflineMessagePull", property);
}


void CTNProcessThread::reqSyncSessionStatus(Toon::SyncSessionStatusReq & req)
{
    
    taf::JceOutputStream<taf::BufferWriter> tos;

    if (req.req_id.length() == 0){
        req.req_id = REQ_ID;
    }
    req.writeTo(tos);

    TNMPLOG("reqSyncSessionStatus req_id:"<<req.req_id<<" type:"<<req.session_name.type<<" from:"<<req.session_name.from<<" rto:"<<req.session_name.to);
    
    sendPacket(TYPE_SYNC_SESSION_STATUS_REQ, tos.getBuffer(), tos.getLength());
}

void CTNProcessThread::reqPullOffMsg(Toon::PullOffMsgReq & req)
{
    if (this->isLogout()){
        TNMPLOG("reqPullOffMsg logout status,give up pull@@");
        return;
    }
    
    taf::JceOutputStream<taf::BufferWriter> tos;
    if (req.req_id.length() == 0){
        req.req_id = REQ_ID;
    }
    
    req.writeTo(tos);
    
    sendPacket(TYPE_PULL_OFFMSG_REQ, tos.getBuffer(), tos.getLength());
    
    //data info
    map<string, string> property;
    property["msg_num"] = intToString(req.limit_count);
    property["msg_type"] = intToString(req.session_name.type);
    
    this->daInfo("MHistoryMessagePull", property);
}

void CTNProcessThread::clientReport(Toon::ClientReport &req)
{
    if (this->isLogout()){
        TNMPLOG("reqPullOffMsg logout status,give up pull@@");
        return;
    }
    
    taf::JceOutputStream<taf::BufferWriter> tos;
    req.writeTo(tos);
    
    sendPacket(TYPE_CLIENT_REPORT, tos.getBuffer(), tos.getLength());
}

void CTNProcessThread::subOrganizeReq(Toon::SubOrganizeReq & req)
{
    if (this->isLogout()){
        TNMPLOG("subOrganizeReq logout status,give up pull@@");
        return;
    }
    
    taf::JceOutputStream<taf::BufferWriter> tos;
    req.writeTo(tos);
    
    sendPacket(TYPE_SUB_ORGANIZE_PRESENCE, tos.getBuffer(), tos.getLength());
}


void CTNProcessThread::sendPacket(uint16_t type, const char *payload, size_t length)
{
    if (m_pSRThread == NULL) {
        TNMPLOG("sendPacket m_pSRThread IS NULL getNetStatus:"<<getNetStatus());
        return;
    }
    
    TNPacketBuffer* packetBuffer = NEW_PACKET(TNMP_HLEN + length);
    packetBuffer->type = type;
    packetBuffer->length = (uint32_t)length;
    if (payload != NULL && length > 0) {
        memcpy(packetBuffer->payload, payload, length);
    }
    
    TNPacket packet;
    packet.type = TMTP_PACKET_TYPE_SEND;
    packet.packetBuffer = packetBuffer;
    
    this->postPacket(packet);
}


//1.网络状态为TNMPNetNone， 重连；
//2.两个keeplive 收不到PINGRESQ响应数据，重连,
//3.网络状态TNMPNetConnecting，一个周期收不到CONNACK也，重连
//4.网络状态TNMPNetConnected 发送PING
void CTNProcessThread::checkPing()
{
//    cout<<"CONFIG->keepAlive():"<< CONFIG->keepAlive()<<endl;
    //need judge reconnect
    int64_t now = time(NULL);
    TNMPNetStatus netStatus = getNetStatus();
    if (netStatus == TNMPNetNone){
        TNMPLOG("CheckPing TNMPNetNone, will reconnect");
        reconnect();
        return;
    }
    else if (netStatus == TNMPNetConnecting
             && m_pingReqTime > 0
             && now - m_pingReqTime > CONFIG->keepAlive()){
        setNetStatus(TNMPNetNone);
        
        reconnect();
        return;
    }
    
    
    if (m_pingReqTime > 0 && now - m_pingReqTime > 2 * CONFIG->keepAlive()) {
        TNMPLOG("CheckPing PING TIME OUT, will reconnect");
        
        setNetStatus(TNMPNetNone);
        
        reconnect();
    }
    else if (netStatus == TNMPNetConnected) {
        //send  ping
        sendPacket(TYPE_PING, NULL, 0);
        TNMPLOG("PING SEND!");
        
        //如果收不到MsgCount，一个keeplive后重新收取

        if (!m_offMsgCountOk) {
			this->reqHotSession(CONFIG->hsTimestamp());
        }
        
        //已经发过PING，未收到服务器端响应，不更新PING时间戳；
        if (m_pingReqTime == 0){
            m_pingReqTime = now;
        }
        
    }
}

void CTNProcessThread::sendAck(int type, Toon::MsgReq* msgReq)
{
    if (!m_offMsgCountOk) {
        TNMPLOG("sendAck will giveup:not recv offMsgCountResp");
        return;
    }
    
    //need send ack
    Toon::MsgAck ack;
    ack.type = type;
    ack.msg_id = msgReq->msg_id;
    ack.seq_id = msgReq->seq_id;
    ack.from = msgReq->from;
    ack.to = msgReq->to;
    ack.priority = msgReq->priority;
    ack.flags = msgReq->flags;
    
    taf::JceOutputStream<taf::BufferWriter> tos;
    ack.writeTo(tos);
    
    sendPacket(TYPE_MSGACK, tos.getBuffer(), tos.getLength());
}
