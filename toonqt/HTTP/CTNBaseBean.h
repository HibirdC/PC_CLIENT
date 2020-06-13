//
//  BaseBean.h
//  TNCHttp
//
//  Created by 王旭影 on 2018/3/28.
//  Copyright © 2018年 syswin. All rights reserved.
//

#ifndef CTNBaseBean_h
#define CTNBaseBean_h

#include "document.h"
#include "prettywriter.h"

using namespace rapidjson;

class CTNBaseOutputBean {
    
public:
    virtual void parse(rapidjson::Value &dataValue) = 0;
};

class CTNBaseInputBean {
    
public:
    virtual ~CTNBaseInputBean(){};
    virtual void serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer) = 0;
};


#endif /* CTNBaseBean_h */
