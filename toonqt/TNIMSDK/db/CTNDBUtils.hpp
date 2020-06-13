//
//  CTNDBUtils.hpp
//  AFNetworking
//
//  Created by 王海涛 on 2017/9/25.
//

#ifndef CTNDBUtils_hpp
#define CTNDBUtils_hpp

#include <stdio.h>
#include <string>
#include <stdint.h>
#include <map>
#include <mutex>

using namespace std;

namespace toonim {
    
    template <typename S, typename T>
    class CSafeMap {
        std::map<S, T> m_map;
        
        //        std::condition_variable m_condition;
        std::mutex m_mutex;
    public:
        inline CSafeMap() {}
        inline ~CSafeMap() {}
        
        inline T& operator [] (S s) {
            std::unique_lock<std::mutex> unilock(m_mutex);
            T& t = m_map[s];
            return t;
        }
        
        inline T operator = (T t) {
            std::unique_lock<std::mutex> unilock(m_mutex);
            T tt = t;
            return tt;
        }
        
        inline size_t size() {
            std::unique_lock<std::mutex> unilock(m_mutex);
            return m_map.size();
        }
        
        inline bool empty(){
            std::unique_lock<std::mutex> unilock(m_mutex);
            return m_map.empty();
        }
        
        inline void clear() {
            std::unique_lock<std::mutex> unilock(m_mutex);
            return m_map.clear();
        }
        
        inline void erase(typename std::map<S,T>::iterator s) {
            std::unique_lock<std::mutex> unilock(m_mutex);
            m_map.erase(s);
            //            m_condition.notify_all();
        }
        
        inline void erase(S s) {
            std::unique_lock<std::mutex> unilock(m_mutex);
            m_map.erase(s);
        }
        
        inline typename std::map<S, T>::iterator find(S s) {
            std::unique_lock<std::mutex> unilock(m_mutex);
            typename std::map<S, T>::iterator iter = m_map.find(s);
            return iter;
        }
        
        inline typename std::map<S, T>::iterator end() {
            std::unique_lock<std::mutex> unilock(m_mutex);
            typename std::map<S, T>::iterator iter = m_map.end();
            return iter;
        }
        
        inline CSafeMap<S, T>& operator= (const CSafeMap<S, T>& mp){
            std::unique_lock<std::mutex> unilock(m_mutex);
            m_map = mp.m_map;
            return *this;
        }
    };
    
    static const int32_t TABLE_COUNT_MESSAGE = 10;
    
    class CTNMessage;
    
    class CTNDBUtils {
    public:
        
        static std::string getReqId();
        static string stringFromInt32(int32_t n);
        static string stringFromInt64(int64_t n);
        static string stringFromDouble(double n);
        static int32_t stringToInt32(string s);
        static int64_t stringToInt64(string s);
        static double stringToDouble(string s);
        static std::string getMD5String(const string s);
        static std::string getMd5String(const string s);
        static bool isEqualAOE(string s);
        static int generateTableIndex(const char* sessionId);//改成通用接口，方便各个模块调用wxy
        static std::string generateEncryptKey(string s);
        static bool fileExistsAtPath(string path);
        static bool isDirExist(std::string dir, bool bCreate);
        
        static std::string getTextTypeContent(CTNMessage& message);
        static std::string getTextTypeVCard(CTNMessage& message);
        static std::string getTextTypeNotification(CTNMessage& message);
        static std::string getTextTypeGifImage(CTNMessage& message);
        static std::string getTextTypeFiles(CTNMessage& message);
        static std::string getTextTypeRevoked(CTNMessage& message);
        static std::string getTextTypeRedEnvelope(CTNMessage& message);
        static std::string getTextTypeRecommend(CTNMessage& message);
        
        static std::string getTextJson(std::string jsonStr, std::string key);
        
    };
    
    //根据message生成lastMsg方法，前后端共用同一套生成机制
    std::string getAbstractText(CTNMessage& message);
    
#define REQ_ID CTNDBUtils::getReqId()
}

#endif /* CTNDBUtils_hpp */
