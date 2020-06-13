//
//  CTNJsonUtils.cpp
//  tnimsdk
//
//  Created by 王旭影 on 2018/3/20.
//  Copyright © 2018年 syswin. All rights reserved.
//

#include "CTNJsonUtils.hpp"

namespace toonim {
    CTNValue::CTNValue():_val(nullptr), _pVal(nullptr){
        
    }
    
    std::string CTNValue::getString(std::string strKey){
        if (_val && _val->HasMember(strKey.c_str()) && (*_val)[strKey.c_str()].IsString()) {
            return _val->GetString();
        }else{
            return "";
        }
    }
    
    void CTNValue::setVal(rapidjson::Value* pVal){
        _val = pVal;
    }
    
    void CTNValue::setNull(){
        _val = nullptr;
    }
    
    CTNValue& CTNValue::operator [](std::string strKey){
        if (_pVal) {
            if (_val && _val->IsObject() && _val->HasMember(strKey.c_str())) {
                _pVal->setVal(&((*_val)[strKey.c_str()]));
            }else{
                _pVal->setNull();
            }

            return *_pVal;
        }else{
            _pVal = new CTNValue();
            
            if (_val && _val->IsObject() && _val->HasMember(strKey.c_str())) {
                _pVal->setVal(&((*_val)[strKey.c_str()]));
            }else{
                _pVal->setNull();
            }
            
            return *_pVal;
        }
    }
    
    int32_t CTNValue::getInt32(){
        if (_val && _val->IsInt()) {
            return _val->GetInt();
        }else{
            return 0;
        }
    }
    
    int64_t CTNValue::getInt64(){
        if (_val && _val->IsInt64()) {
            return _val->GetInt64();
        }else{
            return 0;
        }
    }
    
    std::string CTNValue::getString(){
        if (_val && _val->IsString() && _val->GetString()) {
            return _val->GetString();
        }else{
            return "";
        }
    }
    
    CTNValue::~CTNValue(){
        if (_pVal) {
            delete _pVal;
        }
    }
    
    
    
    CTNJsonValue::CTNJsonValue(rapidjson::Value& val):_val(val), _refVal(&val), _lastVal(&val), _ctnVal(*this){
    }
    
    void CTNJsonValue::resetValue(rapidjson::Value& val){
        _refVal = &val;
    }
    
    void CTNJsonValue::moveTo(rapidjson::Value& val){
        _lastVal = &val;
        _ctnVal._lastVal = &val;
        if (_refVal != &val) {
            _refVal = &val;
        }
    }
    
    std::string CTNJsonValue::getString(){
        
        std::string retStr;
        
        if (_refVal->IsString() && _refVal->GetString()) {
            retStr = _refVal->GetString();
        }
        
        if (_refVal != _lastVal) {
            _refVal = _lastVal;
        }
        
        return retStr;
    }
    
    int32_t CTNJsonValue::getInt32(){
        int32_t retInt = 0;
        if (_refVal->IsInt()) {
            retInt = _refVal->GetInt();
        }else{
            return 0;
        }
        
        if (_refVal != _lastVal) {
            _refVal = _lastVal;
        }
        
        return retInt;
    }
    
    bool CTNJsonValue::isNullValue(){
        if (_refVal->IsNull()) {
            return true;
        }else{
            return false;
        }
    }
    
    int64_t CTNJsonValue::getInt64(){
        
        int64_t retInt64 = 0;
        
        if (_refVal->IsInt64()) {
            retInt64 = _refVal->GetInt64();
        }
        
        if (_refVal != _lastVal) {
            _refVal = _lastVal;
        }
        
        return retInt64;
    }
    
    CTNValue& CTNJsonValue::operator [](int32_t index){
        if (_refVal->IsArray() && index < _refVal->Size()) {
            _value.setVal(&((*_refVal)[index]));
        }else{
            _value.setVal(&unUseVal);
        }

        return _value;
    }
    
    CTNValue& CTNJsonValue::getCTNValue(){
        _value.setVal(_refVal);
        return _value;
    }
    
    CTNJsonValue& CTNJsonValue::operator [](std::string strKey){
        if (_refVal->IsObject() && _refVal->HasMember(strKey.c_str())) {
            _ctnVal.resetValue((*_refVal)[strKey.c_str()]);
        }else{
            _ctnVal.resetValue(unUseVal);
        }
        
        return _ctnVal;
    }
    
    std::string CTNJsonValue::getString(std::string strKey){
        if (_refVal->IsObject() && _refVal->HasMember(strKey.c_str()) && (*_refVal)[strKey.c_str()].IsString()) {
            return (*_refVal)[strKey.c_str()].GetString();
        }else{
            return "";
        }
    }
    
    int32_t CTNJsonValue::getInt32(std::string strKey){
        if (_refVal->IsObject() && _refVal->HasMember(strKey.c_str()) && (*_refVal)[strKey.c_str()].IsInt()) {
            return (*_refVal)[strKey.c_str()].GetInt();
        }else{
            return 0;
        }
    }
    
    int64_t CTNJsonValue::getInt64(std::string strKey){
        if (_refVal->IsObject() && _refVal->HasMember(strKey.c_str()) && (*_refVal)[strKey.c_str()].IsInt64()) {
            return (*_refVal)[strKey.c_str()].GetInt64();
        }else{
            return 0;
        }
    }
    
    int32_t CTNJsonValue::getArraySize(){
        if (_refVal->IsArray()) {
            return _refVal->Size();
        }else{
            return 0;
        }
    }
    
    CTNJsonValue::~CTNJsonValue(){
    }
    
    rapidjson::Value CTNJsonReader::unUseVal;
    
    CTNJsonReader::CTNJsonReader():_val(_doc){}
    CTNJsonReader::~CTNJsonReader(){}
    
    CTNJsonReader::CTNJsonReader(std::string & strJson):_strJson(strJson), _val(_doc){
        _doc.Parse(strJson.c_str());
    }
    
    void CTNJsonReader::setString(std::string& strJson){
        _strJson = strJson;
        _doc.Parse(strJson.c_str());
    }
    
    CTNJsonValue& CTNJsonReader::operator [](std::string strKey){
        if (_doc.IsObject() && _doc.GetParseError() == rapidjson::kParseErrorNone && _doc.HasMember(strKey.c_str())) {
            rapidjson::Value& val = _doc;
            _val.moveTo(val[strKey.c_str()]);
//            _val.resetValue(val[strKey.c_str()]);
        }else{
            _val.resetValue(unUseVal);
        }
        
        return _val;
    }
    
    CTNJsonValue& CTNJsonReader::operator [](int32_t index){
        if (_doc.IsArray()) {
            rapidjson::Value& val = _doc;
            
            _val.moveTo(val[index]);
        }else{
            _val.resetValue(unUseVal);
        }
        
        return _val;
    }
    
    int32_t CTNJsonReader::getSize(){
        rapidjson::Value &dataArray = _doc;
        if (dataArray.IsArray()) {
            return dataArray.Size();
        }else{
            return 0;
        }
    }
    
    bool CTNJsonReader::hasParseErr(){
        if (_doc.GetParseError() == rapidjson::kParseErrorNone) {
            return false;
        }else{
            return true;
        }
        
    }
    
    rapidjson::Value CTNJsonValue::unUseVal;
    
    CTNJsonWriter::CTNJsonWriter():_writer(_buffer), _bBeginArray(false){
        _writer.StartObject();
        _curArray = new CTNJsonArray();
    }
    
    CTNJsonWriter::~CTNJsonWriter(){
        if (_curArray != nullptr) {
            delete _curArray;
            _curArray = nullptr;
        }
    }
    
    CTNJsonWriter& CTNJsonWriter::operator [](std::string strKey){
        if (_bBeginArray) {
            _writer.EndArray();
            _bBeginArray = false;
        }
        _writer.Key(strKey.c_str());
        return *this;
    }
    
    CTNJsonArray& CTNJsonWriter::operator [](int32_t index){
        if (!_bBeginArray) {
            _writer.Key("");
            _writer.StartArray();
            _bBeginArray = true;
        }
        
        _curArray->resetWriter(*this);
        
        return *_curArray;
    }
    
    void CTNJsonWriter::operator =(std::string strVal){
        _writer.String(strVal.c_str(), (rapidjson::SizeType)strVal.length());
    }
    
    void CTNJsonWriter::operator =(int32_t iVal){
        _writer.Int(iVal);
    }
    
    void CTNJsonWriter::operator =(int64_t iVal){
        _writer.Int64(iVal);
    }
    
    std::string CTNJsonWriter::toString(){
        if (_bBeginArray) {
            _writer.EndArray();
            _bBeginArray = false;
        }
        _writer.EndObject();
        
        if (_buffer.GetString()) {
            return std::string(_buffer.GetString(), _buffer.GetSize());
        }else{
            return "";
        }
    }
    
    ///////CTNJsonArray//////////
    CTNJsonArray::CTNJsonArray():_writer(_buffer), _curIndex(0), _refWriter(&_writer){
        _writer.StartArray();
        _refJsonWriter = nullptr;
    }
    
    CTNJsonArray::CTNJsonArray(CTNJsonWriter& writer, std::string strArrKey, bool hasKey):_writer(_buffer), _curIndex(0),_refWriter(&writer._writer), _refJsonWriter(&writer){
        _refWriter->Key(strArrKey.c_str());
        
        if (!hasKey && _refWriter) {
            _refWriter->StartArray();
            if (_refJsonWriter) {
                _refJsonWriter->_bBeginArray = true;
            }
        }
    }
    
    void CTNJsonArray::resetWriter(CTNJsonWriter& writer){
        _refWriter = &(writer._writer);
    }
    
    CTNJsonArray::~CTNJsonArray(){}
    
    CTNJsonArray& CTNJsonArray::operator [](int32_t index){
        if (index == _curIndex + 1 ) {
            _refWriter->EndObject();
            _refWriter->StartObject();
            _curIndex++;
        }
        
        if (index == 0 && !_bStartObj) {
            if (_refWriter && _refJsonWriter) {
                _refWriter->StartArray();
            }
            if (_refJsonWriter) {
                _refJsonWriter->_bBeginArray = true;
            }
            
            if (_refWriter) {
                _refWriter->StartObject();
            }else{
                _writer.StartObject();
            }
            
            _bStartObj = true;
        }
        
        return *this;
    }
    
    CTNJsonArray& CTNJsonArray::operator [](std::string strKey){
        if (!_bStartObj) {
            _writer.StartObject();
            _refWriter->StartObject();
            _bStartObj = true;
        }
        if (_refWriter) {
            _refWriter->Key(strKey.c_str());
        }else{
            _writer.Key(strKey.c_str());
        }
        
        return *this;
    }
    
    void CTNJsonArray::operator =(std::string strVal){
        _refWriter->String(strVal.c_str());
    }
    
    void CTNJsonArray::operator =(int32_t iVal){
        _refWriter->Int(iVal);
    }
    
    void CTNJsonArray::operator =(int64_t lVal){
        _refWriter->Int64(lVal);
    }
    
    std::string CTNJsonArray::toString(){
        if (_bStartObj) {
            _refWriter->EndObject();
            _bStartObj = false;
        }
        
        if (_refWriter && _refJsonWriter && _refJsonWriter->_bBeginArray) {
            _refWriter->EndArray();
        }else if(_refJsonWriter && _refJsonWriter->_bBeginArray){
            _writer.EndArray();
        }else if(!_refJsonWriter){
            _writer.EndArray();
        }
        
        
        if (_refJsonWriter) {
            _refJsonWriter->_bBeginArray = false;
        }
        
        return _buffer.GetString();
    }
}
