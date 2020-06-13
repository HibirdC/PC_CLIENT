//
//  CTNDBUtils.cpp
//  AFNetworking
//
//  Created by 王海涛 on 2017/9/25.
//

#include "CTNDBUtils.hpp"
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <random>
#include <fstream>
#include <sys/stat.h>

#include "rapidjson.h"
#include "document.h"
#include "pointer.h"
#include "CTNDBHeader.h"
#include <openssl/md5.h>
#include "CTNMPConfig.h"
#ifdef WIN32
#include <windows.h>
#include <io.h>
#endif
#include "CLog.h"
#include "CTNJsonUtils.hpp"


#ifdef WIN32
#define snprintf _snprintf
#endif


#define MD5_LENTH 16
#define MD5_STR_LENTH (MD5_LENTH*2+2)
#define JSON_KEY_MAX_LEN 256

using namespace std;
namespace toonim {
    std::string getAbstractText(CTNMessage& message){
        std::string lastMsg;
        switch (message.contentType) {
            case CTNChatTypeText:{
            case CTNChatTypeSystem:
            case CTNChatTypeRevoked:
                lastMsg = CTNDBUtils::getTextTypeContent(message);
                break;
            }
            case CTNChatTypeVoice:
                lastMsg = "[语音]";
                break;
            case CTNChatTypeImage:
                lastMsg = "[图片]";
                break;
            case CTNChatTypeVcard:{
                lastMsg = CTNDBUtils::getTextTypeVCard(message);
                break;
            }
            case CTNChatTypeLocation:
                lastMsg = "[位置]";
                break;
            case CTNChatTypeNotification:
                lastMsg = CTNDBUtils::getTextTypeNotification(message);
                break;
            case CTNChatTypeCollect:
                lastMsg = "[收藏]";
                break;
            case CTNChatTypeVedio:
                lastMsg = "[视频]";
                break;
            case CTNChatTypeGifImage:
                lastMsg = CTNDBUtils::getTextTypeGifImage(message);
                break;
            case CTNChatTypeFiles:
                lastMsg = CTNDBUtils::getTextTypeFiles(message);
                break;
            case CTNChatTypeShare:
                lastMsg = "[分享]";
                break;
            case CTNChatTypeRedEnvelope:
            case CTNChatTypeRichMedia:
                lastMsg = CTNDBUtils::getTextTypeRedEnvelope(message);
                break;
            case CTNChatTypeCustomizedNotification:
                lastMsg = "[通知]";
                break;
            case CTNChatTypeRecommend:
                lastMsg = CTNDBUtils::getTextTypeRecommend(message);
                break;
            default:
                lastMsg = "[未知消息]";
                break;
        }
        
        return lastMsg;
    }
    
    std::string CTNDBUtils::getTextTypeContent(CTNMessage& message)
    {
        return CTNDBUtils::getTextJson(message.content, "/text");
    }
    
    std::string CTNDBUtils::getTextTypeVCard(CTNMessage& message)
    {
        std::string feedId = CTNDBUtils::getTextJson(message.content, "/feedId");
        
        if (feedId.length() <= 0) {
            return "[名片]";
        }
        
        unsigned long size = feedId.find_first_of("g");
        if (size == 0) {
            return "[小组]";
        } else {
            return "[名片]";
        }
    }
    
    std::string CTNDBUtils::getTextTypeNotification(CTNMessage& message)
    {
        std::string summary = CTNDBUtils::getTextJson(message.content, "/summary");
        if (summary.length() <= 0) {
            summary = CTNDBUtils::getTextJson(message.content, "/subCatalog");
        }
        return summary;
    }
    
    std::string CTNDBUtils::getTextTypeGifImage(CTNMessage& message)
    {
        std::string desc = CTNDBUtils::getTextJson(message.content, "/desc");
        if (desc.length() > 0) {
            return "["+desc+"]";
        } else {
            return "[表情]";
        }
    }

    std::string CTNDBUtils::getTextTypeFiles(CTNMessage& message)
    {
        std::string desc = CTNDBUtils::getTextJson(message.content, "/format");
        if (desc == "video/quicktime" || desc == "video/mp4" || desc == "video/3gpp") {
            return "[视频]";
        } else {
            return "[文件]";
        }
    }

    std::string CTNDBUtils::getTextTypeRedEnvelope(CTNMessage& message)
    {
        std::string name = CTNDBUtils::getTextJson(message.content, "/name");
        if (name.length() > 0) {
            return "["+name+"]";
        } else {
            return "[红包]";
        }
    }
    
    std::string CTNDBUtils::getTextTypeRecommend(CTNMessage& message)
    {
        std::string name = CTNDBUtils::getTextJson(message.content, "/title");
        if (name.length() > 0) {
            return "["+name+"]";
        } else {
            return "[推荐]";
        }
    }
    
    std::string CTNDBUtils::getTextJson(std::string jsonStr, std::string key)
    {
#ifdef RAPIDJSONWRAPPER
        CTNJsonReader reader(jsonStr);
        
        return reader[key].getString();
#else
        rapidjson::Document contentDict;
        if (jsonStr != "") {
            contentDict.Parse<0>(jsonStr.c_str());
        }
        
        char c[JSON_KEY_MAX_LEN] = {0};
        
        strncpy(c, key.c_str(), JSON_KEY_MAX_LEN - 1);
        
        rapidjson::Value& text = GetValueByPointerWithDefault(contentDict, c, "");
        
//        return text.GetString();
        return string(text.GetString(), text.GetStringLength());

#endif
    }
    
    
    
    std::string CTNDBUtils::getReqId(){
        std::uniform_int_distribution<int64_t> dis;
        
        std::random_device rd;
        std::stringstream stff;
        stff<<rd();
        
        return  stff.str();
    }
    
    std::string CTNDBUtils::stringFromInt32(int32_t n) {
        std::string s;
        std::stringstream ss;
        ss << n;
        ss >> s;
        return s;
    }
    
    std::string CTNDBUtils::stringFromInt64(int64_t n) {
        std::string s;
        std::stringstream ss;
        ss << n;
        ss >> s;
        return s;
    }
    
    std::string CTNDBUtils::stringFromDouble(double d) {
        std::string s;
        std::stringstream ss;
        ss << d;
        ss >> s;
        return s;
    }
    
    int32_t CTNDBUtils::stringToInt32(std::string s) {
        if (s.length() == 0){
            return 0;
        }
        
        int32_t d;
        sscanf(s.c_str(),"%d",&d);
        return d;
    }
    
    int64_t CTNDBUtils::stringToInt64(std::string s) {
        if (s.length() == 0){
            return 0;
        }
        
        int64_t l;
        sscanf(s.c_str(),"%lld",&l);
        return l;
    }
    
    double CTNDBUtils::stringToDouble(std::string s) {
        if (s.length() == 0){
            return 0;
        }
        
        double d;
        sscanf(s.c_str(),"%le",&d);
        return d;
    }
    
    std::string CTNDBUtils::getMD5String(const string s) {
        if (s.length() == 0) {
            return "";
        }
       unsigned char md5result[MD5_LENTH];
        
        MD5((const unsigned char *)s.c_str(), s.length(), md5result);

        char hex[MD5_STR_LENTH] = {0};
        for(int i = 0; i < MD5_LENTH; i++) {
            snprintf(&hex[i*2], MD5_STR_LENTH-i*2, "%02X", md5result[i]);
        }
        
        return hex;
    }
    
    std::string CTNDBUtils::getMd5String(const string s) {
        if (s.length() == 0) {
            return "";
        }
        unsigned char md5result[MD5_LENTH];
        
        MD5((const unsigned char *)s.c_str(), s.length(), md5result);
        
        char hex[MD5_STR_LENTH] = {0};
        for(int i = 0; i < MD5_LENTH; i++) {
            snprintf(&hex[i*2], MD5_STR_LENTH-i*2, "%02x", md5result[i]);
        }
        
        return hex;
    }
    
    bool CTNDBUtils::isEqualAOE(string s) {
        if (s=="a" || s=="o" || s=="e" || s=="h") {
            return true;
        }
        return false;
    }

    int CTNDBUtils::generateTableIndex(const char* sessionId){
        if (sessionId == nullptr || strlen(sessionId) == 0) {
            return 0;
        }
        
        int tableIndex;
        std::string str = sessionId;
        std::string suffix = str.substr(str.length()-1, 1);
        if (suffix.length() > 0) {
            tableIndex = (std::atoi(suffix.c_str()))%TABLE_COUNT_MESSAGE;
        } else {
            tableIndex = 0;
        }
        
        return tableIndex;
    }
    
    std::string CTNDBUtils::generateEncryptKey(string s) {
        string strOriginKey = "syswin";
        if (s != "") {
            strOriginKey += "_";
            strOriginKey += CTNDBUtils::stringFromInt64((CTNDBUtils::stringToInt64(s) * 8));
        }
        return CTNDBUtils::getMD5String(strOriginKey);
    }
    
    bool CTNDBUtils::fileExistsAtPath(string path){
        ifstream fin(path);

        if (!fin) {
            return false;
        }else{
            return true;
        }
    }
    
    bool CTNDBUtils::isDirExist(std::string dir, bool bCreate){
		if(access(dir.c_str(), 0) == -1){
			TNMPLOG(dir << " is not existed!");
            if (!bCreate) {
                return false;
            }else{
                TNMPLOG(",now create it:" << dir);
            }
#ifdef WIN32
            int flag = CreateDirectoryA(dir.c_str(), 0);
#else
            int flag = mkdir(dir.c_str(), 0777);
#endif
            if(flag == 0){
                TNMPLOG("create dir:" << dir << ",successfully");
                return true;
            } else {
                TNMPLOG("create dir:" << dir << ",failed");
                return false;
            }
        }else{
            return true;
        }
        
        return false;
    }
}
