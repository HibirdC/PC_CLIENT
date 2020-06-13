//
//  TNMPHostInfo.hpp
//  TNMP
//
//  Created by lanhy on 2016/12/15.
//  Copyright © 2016年 兰怀玉. All rights reserved.
//

#ifndef TNMPHostInfo_hpp
#define TNMPHostInfo_hpp

#include <string>

class TMTPHostInfo{
public:
    std::string host;
    std::string ip;
    int32_t port;
    bool isSSL;
    
    TMTPHostInfo()
    {
        port = 0;
        isSSL = false;
    }

   TMTPHostInfo& operator = (const TMTPHostInfo& other){
        if (this == &other){
            return *this;
        }


        this->host = other.host;
        this->ip = other.ip;
        this->port = other.port;
        this->isSSL = other.isSSL;
       
       return *this;
   }

   bool operator == (const TMTPHostInfo& other){
       if (this == &other){
           return true;
       }

       if (this->host == other.host && this->port == other.port){
           return true;
       }

       return false;
   }
};


#endif /* TNMPHostInfo_hpp */
