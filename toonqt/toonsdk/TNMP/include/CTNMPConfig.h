//
//  CTNMPConfig.hpp
//  TNMP
//
//  Created by 兰怀玉 on 16/4/18.
//  Copyright © 2016年 兰怀玉. All rights reserved.
//

#ifndef CTNMPConfig_hpp
#define CTNMPConfig_hpp

#include <string>
#include <vector>
#include <mutex>
#include <map>
#include "TMTPConst.h"
#include "TMTPHostInfo.h"

using namespace std;



#define CONFIG  CTNMPConfig::instance()

class CTNMPConfig
{
public:
    static CTNMPConfig* instance();
    
    void appPath(string appPath);
    
    string appPath(){
        return m_appPath;
    }
    
    void setHostInfos(std::vector<TMTPHostInfo> & vctHostInfo){
        m_vctHostInfo = vctHostInfo;
    }
    
    TMTPHostInfo hostInfo();
        
        
    void clientId(const char*clientId);
    
    string clientId(){
        return m_clientId;
    }
    
    void deviceToken(const char* token){
        if (token != NULL) {
            m_deviceToken = token;
        }
    }
    
    string deviceToken(){
        return m_deviceToken;
    }
    
    void deviceId(const char* deviceId){
        if (deviceId != NULL) {
            m_deviceId = deviceId;
        }
    }
    
    string deviceId(){
        return m_deviceId;
    }

    
    void username(const char* username){
        if (username != NULL && strlen(username)) {
            m_username = username;
        }
    }
    
    string username(){
        return m_username;
    }
    

    void password(const char* password){
        if (password != NULL && strlen(password) > 0) {
            m_password = password;
        }
    }
    
    string password(){
        return m_password;
    }
    
    
    void keepAlive(int keepAlive){
        m_keepAlive = keepAlive;
    }
    int keepAlive(){
        return m_keepAlive;
    }
  
    void appType(int appType){
        m_appType = appType;
    }
    int appType(){
        return m_appType;
    }
  
    void apnsType(int appType){
        m_apnsType = appType;
    }
    int apnsType(){
        return m_apnsType;
    }
    
    void deviceType(int appType){
        m_deviceType = appType;
    }
    int deviceType(){
        return m_deviceType;
    }
    
  
    void version(const char* version){
        if (version != NULL) {
            m_version = version;
        }
    }
    
    string version(){
        return m_version;
    }
    
    int pushServiceType(){
        return m_pushServiceType;
    }
    
    void  pushServiceType(int pushServiceType){
        m_pushServiceType = pushServiceType;
    }
    
    void resetCurrHostIndex(){
        m_currHostIndex = 0;
    }
    
    
    int64_t hsTimestamp();
    
    void setHSTimestamp(int64_t hsTimestamp);
    
    string getIpCache(const char* host);
    void removeIpCache(const char* host);
    
private:
    CTNMPConfig();
    ~CTNMPConfig();
    
    void loadConfig();
    void loadIpCache();
    void saveIpCache();

    static CTNMPConfig* m_instance;
    
    std::vector<TMTPHostInfo> m_vctHostInfo;
    //host->ip
    std::map<string, string> _mapHosts;
    mutex _mutexHosts;

    int m_currHostIndex;
    int m_deviceType;
    int m_appType;
    int m_apnsType;
    //push服务提供商类型，默认值0:无push服务 1:苹果push服务  2:华为push服务  3:小米push服务 4:魅族push服务
    int m_pushServiceType;
    
    string m_appPath;
    string m_version;
    string m_deviceId;
    string m_clientId;
    string m_deviceToken;
    string m_username;
    string m_password;
    
    
    //重连次数
    int m_keepAlive;// = 60 * 1000;
    
//    int64_t m_hsTimestamp;//热会话同步时间
    
    std::map<std::string, int64_t> _mapClientTimestamp;
    
   
};


#endif /* CTNMPConfig_hpp */
