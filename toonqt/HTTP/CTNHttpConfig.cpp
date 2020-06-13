//
// Created by juzenhon on 2017/8/30.
//

#include "CTNHttpConfig.h"
#include <cstdint>
#include <algorithm>
#include <string.h>

#include "CLog.h"

namespace toonim {


CTNHttpConfig::CTNHttpConfig() {
    _toonType = 0;//默认值，所有toon
}

CTNHttpConfig::~CTNHttpConfig() {
}

void CTNHttpConfig::addDomainIp(const char *domain, vector<string> &ipList) {
    if (domain == NULL || strlen(domain) == 0 || ipList.size() == 0){
        TNMPLOG("addDomainIp domain OR IPList is EMPTY!");
        return;
    }


    TNMPLOG("before domain:"<<domain<<" ipLst:"<<ipList.size());

    map<string, vector<string> >::iterator itTmp = mRouterMap.find(domain);
    if (itTmp == mRouterMap.end()){
        mRouterMap.insert(make_pair(domain, ipList));
        return;
    }

    for (int i = 0; i < ipList.size(); i++){
        vector<string>::iterator itListFind = find(itTmp->second.begin(), itTmp->second.end(), ipList[i]);
        if (itListFind == itTmp->second.end()){
            itTmp->second.push_back(ipList[i]);
        }
    }

    TNMPLOG("after domain:"<<domain<<" ipLst:"<<itTmp->second.size());
}

const char *CTNHttpConfig::getToonIp(const char* name) {
    if (name == nullptr || strlen(name) == 0) {
        TNMPLOG("before getToonIp nullptr name=" << name);
        return nullptr;
    }
    
    static int count = 1;
    vector<string> &ipList = mRouterMap[name];
    if (ipList.size() > 0) {
        return ipList[(count++) % ipList.size()].c_str();
    }

    TNMPLOG("end getToonIp nullptr name=" << name);
    return NULL;
}

const char *CTNHttpConfig::getPlatform() {
#ifdef ANDROID
    return "android";
#elif defined(IOS)
    return "ios";
#elif defined(MAC)
    return "Mac OS";
#else
    return "windows";
#endif
}

const string &CTNHttpConfig::getUserId() const {
    return _userId;
}

void CTNHttpConfig::setUserId(const string &userId) {
    _userId = userId;
}

const string &CTNHttpConfig::getToken() const {
    return _token;
}

void CTNHttpConfig::setToken(const string &token) {
    _token = token;
}

const string &CTNHttpConfig::getDeviceId() const {
    return _deviceId;
}

void CTNHttpConfig::setDeviceId(const string &deviceId) {
    _deviceId = deviceId;
}

const string &CTNHttpConfig::getAppVersion() const {
    return _appVersion;
}

void CTNHttpConfig::setAppVersion(const string &appVersion) {
    _appVersion = appVersion;
}

const string &CTNHttpConfig::getPlatformVersion() const {
    return _platformVersion;
}

void CTNHttpConfig::setPlatformVersion(const string &platformVersion) {
    _platformVersion = platformVersion;
}

int32_t CTNHttpConfig::getToonType() const {
    return _toonType;
}

void CTNHttpConfig::setToonType(int32_t toonType) {
    _toonType = toonType;
}

const string &CTNHttpConfig::getCerPath(){
    return _cerPath;
}

void CTNHttpConfig::setCerPath(const string &cerPath){
    _cerPath = cerPath;
}

}
