//
// Created by juzenhon on 2017/8/30.
//

#ifndef TMTP_CROUTERMANAGER_H
#define TMTP_CROUTERMANAGER_H

#include <string>
#include <map>
#include <vector>
#include <cstdint>

using namespace std;

extern const char *DomainChat;

extern const char *DomainApp;

namespace toonim {


class CTNHttpConfig {

public:

    static CTNHttpConfig *getInstance() {
        static CTNHttpConfig instance;
        return &instance;
    }
    
    const char *getToonIp(const char* name);
    
    void addDomainIp(const char *domain, vector<string> &ipList);

    const char *getPlatform();

    const string &getUserId() const;

    void setUserId(const string &_userId);

    const string &getToken() const;

    void setToken(const string &_token);

    const string &getDeviceId() const;

    void setDeviceId(const string &_deviceId);

    const string &getAppVersion() const;

    void setAppVersion(const string &_appVersion);

    const string &getPlatformVersion() const;

    void setPlatformVersion(const string &_platformVersion);

    int32_t getToonType() const;

    void setToonType(int32_t _toonType);

    const string &getCerPath();

    void setCerPath(const string &_platformVersion);


private:
    CTNHttpConfig();

    ~CTNHttpConfig();

    const CTNHttpConfig &operator=(const CTNHttpConfig &rhs);
    
    map<string, vector<string> > mRouterMap;

//    string _platform;
    string _userId;

    string _token;

    string _deviceId;

    string _appVersion;

    string _platformVersion;

    string _cerPath;

    int32_t _toonType;
};

}

#endif //TMTP_CROUTERMANAGER_H
