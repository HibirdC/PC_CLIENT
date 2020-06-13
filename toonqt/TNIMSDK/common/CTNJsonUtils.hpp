//
//  CTNJsonUtils.hpp
//  tnimsdk
//
//  Created by 王旭影 on 2018/3/20.
//  Copyright © 2018年 syswin. All rights reserved.
//

#ifndef CTNJsonUtils_hpp
#define CTNJsonUtils_hpp

#include <stdio.h>
#include <string>
#include "stringbuffer.h"
#include "writer.h"
#include "document.h"

namespace toonim {
    class CTNValue{
    public:
        std::string getString(std::string strKey);
        
        void setVal(rapidjson::Value* pVal);
        
        void setNull();
        
        CTNValue& operator [](std::string strKey);
        
        int32_t getInt32();
        
        int64_t getInt64();
        
        std::string getString();
        
        ~CTNValue();
        
    private:
        rapidjson::Value *_val;
        CTNValue* _pVal;
        CTNValue();
        
        friend class CTNJsonValue;
    };
    
    
    class CTNJsonValue{
    public:
        CTNJsonValue(rapidjson::Value& val);
        
        void resetValue(rapidjson::Value& val);
        
        void moveTo(rapidjson::Value& val);
        
        std::string getString();
        
        int32_t getInt32();
        
        bool isNullValue();
        
        int64_t getInt64();
        
        CTNJsonValue& operator [](std::string strKey);
        
        std::string getString(std::string strKey);
        
        int32_t getInt32(std::string strKey);
        
        int64_t getInt64(std::string strKey);
        
        CTNValue& operator [](int32_t index);
        
        CTNValue& getCTNValue();
        
        int32_t getArraySize();
        
        ~CTNJsonValue();
        
    private:
        rapidjson::Value& _val;
        rapidjson::Value* _refVal;
        rapidjson::Value* _lastVal;
        CTNJsonValue& _ctnVal;
        CTNValue _value;//
        static rapidjson::Value unUseVal;
    };
    
    class CTNJsonReader{
    public:
        CTNJsonReader();
        ~CTNJsonReader();
        
        CTNJsonReader(std::string & strJson);
        
        void setString(std::string& strJson);
        
        CTNJsonValue& operator [](std::string strKey);
        
        CTNJsonValue& operator [](int32_t index);
        
        int32_t getSize();
        
        bool hasParseErr();
        
    private:
        rapidjson::Document _doc;
        std::string _strJson;
        CTNJsonValue _val;
        
        static rapidjson::Value unUseVal;
    };
    
    class CTNJsonArray;
    
    class CTNJsonWriter{
    public:
        CTNJsonWriter();
        ~CTNJsonWriter();
        
        CTNJsonWriter& operator [](std::string strKey);
        
        CTNJsonArray& operator [](int32_t index);
        
        void operator =(std::string strVal);
        
        void operator =(int32_t iVal);
        
        void operator =(int64_t iVal);
        
        std::string toString();
    private:
        rapidjson::StringBuffer _buffer;
        rapidjson::Writer<rapidjson::StringBuffer> _writer;
        bool _bBeginArray;
        
        CTNJsonArray* _curArray;
        friend class CTNJsonArray;
        static CTNJsonArray _unUserArr;
    };
    
    class CTNJsonArray{
    public:
        CTNJsonArray();
        CTNJsonArray(CTNJsonWriter& writer, std::string strArrKey = "", bool hasKey = true);
        ~CTNJsonArray();
        
        void resetWriter(CTNJsonWriter& writer);
        
        CTNJsonArray& operator [](int32_t index);
        
        CTNJsonArray& operator [](std::string strKey);
        
        void operator =(std::string strVal);
        
        void operator =(int32_t iVal);
        
        void operator =(int64_t lVal);
        
        std::string toString();
    private:
        rapidjson::StringBuffer _buffer;
        rapidjson::Writer<rapidjson::StringBuffer> _writer;
        rapidjson::Writer<rapidjson::StringBuffer>* _refWriter;
        CTNJsonWriter *_refJsonWriter;
        int32_t _curIndex;
        bool _bStartObj = false;
    };
}


#endif /* CTNJsonUtils_hpp */
