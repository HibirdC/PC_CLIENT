//
// Created by juzenhon on 2017/8/31.
//

#ifndef TMTP_META_H_H
#define TMTP_META_H_H

#include <string>
#include "document.h"
#include "CTNJsonUtils.hpp"

namespace toonim {
    class CTNBizMeta {
        
    public:
        
#ifdef RAPIDJSONWRAPPER
        static void Parse(CTNJsonValue& value, CTNBizMeta &bean) {
          bean.message = value["message"].getString();
          bean.code = value["code"].getInt32();
          bean.offset = value["offset"].getInt32();
          bean.limit = value["limit"].getInt32();
          bean.total = value["total"].getInt32();
        }
#else
        static void Parse(rapidjson::Value& value, CTNBizMeta &bean) {
            if (value.HasMember("message") && value["message"].IsString()) {
                bean.message = value["message"].GetString();
            }
            if (value.HasMember("code") && value["code"].IsInt()) {
                bean.code = value["code"].GetInt();
            }
            if (value.HasMember("offset") && value["offset"].IsInt()) {
                bean.offset = value["offset"].GetInt();
            }
            if (value.HasMember("limit") && value["limit"].IsInt()) {
                bean.limit = value["limit"].GetInt();
            }
            if (value.HasMember("total") && value["total"].IsInt()) {
                bean.total = value["total"].GetInt();
            }
        }
#endif
        
        std::string message;
        int code;
        int offset;
        int limit;
        long total;
    };
}


#endif //TMTP_META_H_H
