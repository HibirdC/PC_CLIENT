//
//  CTNMPConfig.cpp
//  TNMP
//
//  Created by 兰怀玉 on 16/4/18.
//  Copyright © 2016年 兰怀玉. All rights reserved.
//

#include "CTNMPConfig.h"
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <map>
#include "CLog.h"

#ifdef WIN32

#include <winsock2.h>
#include <Ws2tcpip.h>

#define socklen_t    int

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#endif

#define CONFIG_FILE "/imconfigv4.ini"
#define IPCACHE_FILE "/ipcache.ini"

#define CID_MAX_LEN    128

CTNMPConfig::CTNMPConfig()
{
    m_deviceToken = "";
    
    m_keepAlive = 25 ;//* 1000;
    m_currHostIndex = -1;
    m_appType = 100;
    m_deviceType = 0;//iOS
    m_pushServiceType = 0;
    m_apnsType = 100;
}

CTNMPConfig::~CTNMPConfig()
{
}

CTNMPConfig* CTNMPConfig::m_instance = NULL;

CTNMPConfig* CTNMPConfig::instance(){
    if (m_instance == NULL) {
        m_instance = new CTNMPConfig();
    }
    
    return m_instance;
}

string CTNMPConfig::getIpCache(const char* host)
{
    if (host == NULL || strlen(host) == 0){
        return "";
    }
    
    std::unique_lock<std::mutex> unilock(_mutexHosts);
    TNMPLOG("BEFORE DNS:"<<host<<" map size:"<<_mapHosts.size());
    
    std::map<string, string>::iterator itTmp = _mapHosts.begin();
    while( itTmp != _mapHosts.end()){
        TNMPLOG(" DNS cache:"<<itTmp->first<<" ip:"<<itTmp->second);
        itTmp ++;
    }
    
    std::map<string, string>::iterator itFind = _mapHosts.find(host);
    if (itFind != _mapHosts.end()){
        TNMPLOG("after DNS cache:"<<host<<" ip:"<<itFind->second);
        return itFind->second;
    }
    
    struct addrinfo *result = 0;
    int error = getaddrinfo(host, NULL, NULL, &result);
    if (result == NULL){
        TNMPLOG("getaddrinfo error:"<<error);
        return host;
    }
    
    const struct sockaddr *sa = result->ai_addr;
    socklen_t maxlen = 128;
    char ip[128] = { 0 };
    strncpy(ip, host, 127);

    bool isOK = true;
    if(sa->sa_family == AF_INET6){
        TNMPLOG("IPV6 getIpCache");
        if (inet_ntop(AF_INET6, &(((struct sockaddr_in6 *)sa)->sin6_addr), ip, maxlen) == 0){
            TNMPLOG("getIpCache ipv6 failed:"<<ip);
            isOK = false;
        }
    }
    else{
        TNMPLOG("IPV4 getIpCache");
        if (inet_ntop(AF_INET, &(((struct sockaddr_in *)sa)->sin_addr), ip, maxlen) == 0){
            TNMPLOG("getIpCache ipv4 failed:"<<ip);
            isOK = false;
        }
    }
    TNMPLOG("after DNS:"<<host<<" ip:"<<ip);
    if (!isOK){
        freeaddrinfo(result);
        return host;
    }
    
    _mapHosts[host] = ip;
    this->saveIpCache();
    freeaddrinfo(result);
    return ip;
}

void CTNMPConfig::removeIpCache(const char *host)
{
    std::unique_lock<std::mutex> unilock(_mutexHosts);
    if (host == NULL || strlen(host) == 0
        || _mapHosts.empty()){
        return ;
    }
    
    _mapHosts.erase(host);
    
    this->saveIpCache();
    
    TNMPLOG("removeIpCache:"<<host);
}


void CTNMPConfig::clientId(const char*clientId){
    if (clientId != NULL) {
        m_clientId = clientId;
    }
}

void CTNMPConfig::appPath(string appPath){
    m_appPath = appPath;
    
    this->loadConfig();
    this->loadIpCache();
}

void CTNMPConfig::loadConfig()
{
    //need save to file
    string filename = m_appPath + CONFIG_FILE;
    
    //read ini
    FILE *fp = fopen(filename.c_str(), "rb+");
    if (fp == NULL){
        return;
    }
    
    //    std::cout<<"loadConfig thead:"<<pthread_mach_thread_np(pthread_self()) <<std::endl;
    
    char buffer[CID_MAX_LEN + 1] = {0};
    int64_t timestamp = 0;
    size_t readBuffBytes = 0;
    while (!feof(fp)) {
        memset(buffer, 0, sizeof(buffer));
        timestamp = 0;
        readBuffBytes = fread(buffer, CID_MAX_LEN, 1, fp);
        fread(&timestamp, sizeof(int64_t), 1, fp);
        
        if (readBuffBytes > 0){
            _mapClientTimestamp[buffer] = timestamp;
            printf("load clientId1 :%s tm:%lld\n", buffer, timestamp);
        }
    }
    
    fclose(fp);
    
}

void CTNMPConfig::loadIpCache()
{
    std::unique_lock<std::mutex> unilock(_mutexHosts);
    string filename = m_appPath + IPCACHE_FILE;
    
    //read ini
    FILE *fp = fopen(filename.c_str(), "rb+");
    if (fp == NULL){
        return;
    }
    
    char host[CID_MAX_LEN + 1] = {0};
    char ip[CID_MAX_LEN + 1] = {0};
    size_t nReadHostBytes = 0;
    size_t nReadIpBytes = 0;
    while (!feof(fp)) {
        memset(host, 0, sizeof(host));
        memset(ip, 0, sizeof(ip));
        
        nReadHostBytes = fread(host, CID_MAX_LEN, 1, fp);
        nReadIpBytes = fread(ip, CID_MAX_LEN, 1, fp);
        
        if (nReadHostBytes > 0 && nReadIpBytes > 0) {
            _mapHosts[host] = ip;
            TNMPLOG("load DNS cache:"<<host<<" ip:"<<ip);
        }
    }
    
    fclose(fp);
}

void CTNMPConfig::saveIpCache()
{
    //    std::unique_lock<std::mutex> unilock(_mutexHosts);
    string filename = m_appPath+IPCACHE_FILE;
    FILE *fp = fopen(filename.c_str(), "wb+");
    if (fp == NULL){
        return;
    }
    
    char host[CID_MAX_LEN + 1] = {0};
    char ip[CID_MAX_LEN + 1] = {0};
    std::map<std::string, std::string>::iterator itTmp = _mapHosts.begin();
    while (itTmp != _mapHosts.end()) {
        memset(host, 0, sizeof(host));
        memset(ip, 0, sizeof(ip));
        
        strncpy(host,itTmp->first.c_str(), CID_MAX_LEN);
        strncpy(ip,itTmp->second.c_str(), CID_MAX_LEN);
        
        fwrite(host, 1, CID_MAX_LEN, fp);
        fwrite(ip, 1, CID_MAX_LEN, fp);
        
        TNMPLOG("save saveIpCache host:"<<itTmp->first<<" ip:"<<itTmp->second);
        itTmp++;
    }
    
    fclose(fp);
}

int64_t CTNMPConfig::hsTimestamp()
{
    return _mapClientTimestamp[m_clientId];
}


void  CTNMPConfig::setHSTimestamp(int64_t hsTimestamp){
    
    if (m_clientId.length() == 0){
        return;
    }
    
    _mapClientTimestamp[m_clientId] = hsTimestamp;
    
    //need save to file
    string filename = m_appPath+CONFIG_FILE;
    FILE *fp = fopen(filename.c_str(), "wb+");
    if (fp == NULL){
        return;
    }
    
    std::map<std::string, int64_t>::iterator itTmp= _mapClientTimestamp.begin();
    while (itTmp != _mapClientTimestamp.end()) {
        char cientId[CID_MAX_LEN + 1] = {0};
        strncpy(cientId,itTmp->first.c_str(), CID_MAX_LEN);
        fwrite(cientId, 1, CID_MAX_LEN, fp);
        fwrite(&(itTmp->second), sizeof(int64_t), 1, fp);
        
        printf("save clientId client:%s tm:%lld\n", itTmp->first.c_str(), itTmp->second);
        itTmp++;
    }
    
    fclose(fp);
}


TMTPHostInfo CTNMPConfig::hostInfo()
{
    if (m_vctHostInfo.size() == 0) {
        return TMTPHostInfo();
    }
    
    if (m_currHostIndex < 0) {
        //        srand( (unsigned)time( NULL ) );
        //        m_currHostIndex = rand()% m_vctHostInfo.size();
        m_currHostIndex = 0;
    }
    
    m_currHostIndex = m_currHostIndex % m_vctHostInfo.size();
    
    TMTPHostInfo hostInfo = m_vctHostInfo.at(m_currHostIndex);
    if (hostInfo.ip.length() == 0){
        hostInfo.ip = this->getIpCache(hostInfo.host.c_str());
        hostInfo.ip = hostInfo.host;
    }
    
    m_currHostIndex ++;
    
    return hostInfo;
}

