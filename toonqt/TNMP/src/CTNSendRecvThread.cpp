//
//  CTNSendRecvThread.cpp
//  TNMP
//
//  Created by 兰怀玉 on 16/4/15.
//  Copyright © 2016年 兰怀玉. All rights reserved.
//

#include "CTNSendRecvThread.h"
#include "CTNMPConfig.h"
#include <iostream>
#include "tmtp_type.h"
#include "CSSLSocket.h"
#include "CLog.h"
#include "CTNProcessThread.h"
#include "CTNSocketSelect.h"

#ifndef WIN32

#include <unistd.h>
#else
#include <Windows.h>

#endif


using namespace std;

CTNSendRecvThread::CTNSendRecvThread(CTNProcessThread* processThread):_queuePacket(false)
{
    TNMPLOG("CTNSendRecvThread::CTNSendRecvThread...:"<<getId()<<" processThread:"<<processThread->getId());
    _pSocket = NULL;
    
    _processThread = processThread;
    _reconnectTimes = 0;
}

CTNSendRecvThread::~CTNSendRecvThread()
{
    TNMPLOG("CTNSendRecvThread::~CTNSendRecvThread...:"<<getId());
    if (_pSocket != NULL) {
        delete _pSocket;
        _pSocket = NULL;
    }
}


void CTNSendRecvThread::stop()
{
    if (!isRunning()) {
        TNMPLOG("CTNSendRecvThread isn't running return:"<<getId());
        return;
    }
    
    
    CThreadEx::stop();
    TNMPLOG("CTNSendRecvThread stopped:"<<getId()<<" isRunning:"<<isRunning());

    //notify exit the select wait
    _rwBreaker.fireon();
    
    if (_pSocket != NULL) {
        TNMPLOG("_pSocket will close:"<<getId());
        _pSocket->closeSocket();
    }
    
}

void  CTNSendRecvThread::postRecvPacketBuffer(TNPacketBuffer * packetBuffer)
{
    if  (_processThread == NULL){
        TNMPLOG("_processThread is NULL...:"<<getId());
        DELETE_PACKET(packetBuffer);
        return;
    }
    
    TNPacket packet;
    packet.type = TMTP_PACKET_TYPE_RECV;
    packet.param = this->getId();
    packet.packetBuffer = packetBuffer;
    
    _processThread->postPacket(packet);
}

void CTNSendRecvThread::socketClosed()
{
    TNMPLOG("CTNSendRecvThread socketClosed:"<<getId());
    TNPacket packet;
    packet.type = TMTP_PACKET_TYPE_SOKCET_CLOSED;
    packet.param = this->getId();
    _processThread->postPacket(packet);
}

#define  RECV_LEN   65534

//超过这个数就废了，直接丢弃数据包
#define  MAX_RECV_LEN   65534000

void CTNSendRecvThread::run()
{
    TNMPLOG("CTNSendRecvThread thread start RSThread:"<<this->getId());
	
    char recvBytes[RECV_LEN] = {0};
    
    //wait 100-500 ms
    int sleepTime = (this->getId()%5) * 100;

    tn_msleep(sleepTime);
    
    connect();
#if 0
    while (isRunning()){
        int len = _pSocket->recvData(recvBytes, RECV_LEN);
        if (len > 0){
            //            TNMPLOG("recv data:"<<len);
            _recvByteQueue.push(recvBytes, len);
            
            if (_recvByteQueue.size() < TNMP_HLEN) {
                //TNMPLOG("not enough continue recv:"<<TNMP_HLEN);
                continue;
            }
            
            processRecvData();
        }
        else if (!isRunning()){
             TNMPLOG("Thread will stop...:"<<getId());
            break;
        }
        else if (len == 0 || (len == -1 && errno != EINTR)){
             TNMPLOG("Recv data len , will close socket:"<<len);
            //中断需要继续重试 退出循环有判断，此判断重复，去掉
            break;
        }
    }

#else
    while (isRunning()){
        socket_t socketFD = _pSocket->socketFD();

        CTNSocketSelect sel(_rwBreaker, true);
        sel.preSelect();
        sel.read_FD_SET(socketFD);
        sel.exception_FD_SET(socketFD);
        if (!_queuePacket.empty()){
            sel.write_FD_SET(socketFD);
        }
        
        TNMPLOG("BEFORE CTNSendRecvThread sel.select"<<getId());
        int ret = sel.select();
        TNMPLOG("AFTER CTNSendRecvThread sel.select:"<<getId());
        if (ret < 0){
            TNMPLOG("CTNSendRecvThread will stop ret<0...:"<<getId());
            break;
        }
        if (sel.isException()) {
            TNMPLOG("sel isException will stop...:"<<getId());
            break;
        }
        
        if (sel.exception_FD_ISSET(socketFD)) {
            TNMPLOG("sel exception_FD_ISSET will stop...:"<<getId());
            break;
        }
        
        if (sel.read_FD_ISSET(socketFD)){
            int len = _pSocket->recvData(recvBytes, RECV_LEN);
            if (len == TMTP_ERR_SOCK_CLOSE){
                TNMPLOG("recvData socket will close...:"<<getId());
               break;
            }
            
            //process recv data
            _recvByteQueue.push(recvBytes, len);
            processRecvData();
        }
        
        if (sel.write_FD_ISSET(socketFD) && !_queuePacket.empty()){
            TNPacketBuffer* packet = nullptr;
            _queuePacket.pop(packet, 1);
            if (packet != nullptr){
                TNMPLOG("Send packet type:"<<packet->type<<" length:"<<packet->length<<" thread:"<<this->getId());
                size_t packetLen = packet->length + TNMP_HLEN;
                packet->encode();
                ret = _pSocket->sendData((char*)packet, packetLen);
                DELETE_PACKET(packet);
                
                if (ret == TMTP_ERR_SOCK_CLOSE){
                    TNMPLOG("sendData socket will close...:"<<getId());
                    break;
                }
                else if (ret < packetLen){
                    TNMPLOG("sendData failed,packet will be lost ret:"<<ret);
                }
            }
        }
    }
#endif
    
    //非主动断掉，需要重连
    if (isRunning()) {
        TNMPLOG("before socketClosed 2:"<<getId());
        this->socketClosed();
    }

    TNMPLOG("CTNSendRecvThread socket 3:"<<getId());
    this->stop();
  
    TNMPLOG("CTNSendRecvThread thread end...:"<<getId());
}

void CTNSendRecvThread::processRecvData()
{
    TNPacketBuffer headerParser;
    while (_recvByteQueue.size() >= TNMP_HLEN) {
        headerParser = *(TNPacketBuffer *)_recvByteQueue.getArray();
        headerParser.decode();
        
        int packLen = headerParser.length + TNMP_HLEN;
        if (packLen > 65534000) {
            TNMPLOG("packLen error size:"<<packLen<<" type:"<<headerParser.type);
            this->stop();
  
            this->socketClosed();

            break;
        }
        
        if (packLen > _recvByteQueue.size()){
            TNMPLOG("not enough continue curr size:"<<_recvByteQueue.size()<<" except size:"<<packLen<<" type:"<<headerParser.type);
            break;
        }
        
        
        TNMPLOG("RECV OK type:"<<headerParser.type<<" length:"<<headerParser.length<<" thread:"<<getId());
        char* buffer =  _recvByteQueue.pop(packLen);
        TNPacketBuffer * packetBuffer = (TNPacketBuffer *)buffer;
        packetBuffer->decode();
        
        postRecvPacketBuffer(packetBuffer);
    }
    
}

void CTNSendRecvThread::sendPacket(TNPacketBuffer* packet)
{
    if (_pSocket == NULL || packet == NULL) {
        TNMPLOG("_pSocket is null or packet is null");
        return;
    }
    
    TNPacketBuffer* clonePacket = packet->clone();
    if (clonePacket != nullptr){
        _queuePacket.push(clonePacket);
        _rwBreaker.fireon();
    }
}

void CTNSendRecvThread::connect()
{
    int connects = 0;
    
    while (isRunning()) {
        if (_pSocket != nullptr) {
            delete _pSocket;
            _pSocket = nullptr;
        }
        
        if (_hostInfo.isSSL){
            _pSocket = new CSSLSocket();
            TNMPLOG("CSSLSocket will connect:"<<_hostInfo.host<<" port:"<<_hostInfo.port<<" thread:"<<getId());
            
        }
        else {
            _pSocket = new CTcpSocket();
            TNMPLOG("CTcpSocket Will connect to host:"<<_hostInfo.host<<" port:"<<_hostInfo.port<<" thread:"<<getId());
        }
        
        TNMPLOG("Will connect to host:"<<_hostInfo.host<<" port:"<<_hostInfo.port<<" thread:"<<getId());
        int ret = _pSocket->connectToHost(_hostInfo.ip.c_str(), _hostInfo.port);
        TNMPLOG("after connect to host:"<<_hostInfo.ip<<" port:"<<_hostInfo.port<<" result:"<<ret<<" thread:"<<getId());
       
        //防止一段时间连接不上后，重新连接放弃此连接
        if (!isRunning()) {
            TNMPLOG("STOPED! The Current TCP will give up, thread:"<<getId());
            break;
        }
   
        if (ret == 0) {
            TNPacket packet;
            packet.type = TMTP_PACKET_TYPE_SOKCET_SUCCESS;
            packet.param = this->getId();
            _processThread->postPacket(packet);
            
            break;
        }
        else if (connects >= RECONN_MAX){
            TNMPLOG("connect failed retry times:"<<connects<<" thread:"<<getId());
            TNPacket packet;
            packet.type = TMTP_PACKET_TYPE_SOKCET_FAILED;
            packet.param = this->getId();
            _processThread->postPacket(packet);

            this->stop();
            
            CONFIG->removeIpCache(_hostInfo.host.c_str());
            
            break;
        }
        else {
            int sleepTime = RECONN_STEP[connects%RECONN_MAX];
            
            TNMPLOG("need reconnect:"<<sleepTime<<" thread:"<<getId());
			tn_msleep(sleepTime*1000);
            
            connects ++;
            _hostInfo = CONFIG->hostInfo();
            TNMPLOG("Reget host:"<<_hostInfo.host<<" port:"<<_hostInfo.port<<" thread:"<<getId());
        }
    }
}



