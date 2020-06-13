//
// Created by juzenhon on 2018/3/8.
//

#include "CTNRequest.h"
#include "CLog.h"
#include "CTNNetWork.h"
#include "CTNBaseBean.h"
#include "CTNHttpConfig.h"
#include "CTNBizMeta.h"

namespace toonim {
    CTNBizJsonRequest::CTNBizJsonRequest() {
        _inputContext = NULL;
        _method = CTNHttpMethod::Get;
        initCommonHeader();
    }
    
    CTNBizJsonRequest::CTNBizJsonRequest(CTNBaseInputBean *bean, CTNHttpMethod method) {
        _method = method;
        _inputContext = bean;
        initCommonHeader();
    }
    
    CTNBizJsonRequest::~CTNBizJsonRequest() {
        if (_inputContext) {
            delete _inputContext;
        }
    }
    
    void CTNBizJsonRequest::setCallback(HandleResponseFun responseFun, RequestCallbackFun callbackFun,
                                        void *userData, CanceledFun canceledFun) {
        _handleResponseFun = responseFun;
        _callbackFun = callbackFun;
        _cancelFun = canceledFun;
        _userData = userData;
    }
    
    void CTNBizJsonRequest::initCommonHeader() {
        std::stringstream agent;
        agent << "platform:" << toonim::CTNHttpConfig::getInstance()->getPlatform()
        << ",deviceId:" << toonim::CTNHttpConfig::getInstance()->getDeviceId()
        << ",appVersion:" << toonim::CTNHttpConfig::getInstance()->getAppVersion()
        << ",platformVersion:" << toonim::CTNHttpConfig::getInstance()->getPlatformVersion()
        << ",toonType:" << toonim::CTNHttpConfig::getInstance()->getToonType();
        
        _headers.insert(make_pair("Accept-Encoding", "gzip"));
        _headers.insert(make_pair("Accept", "application/json"));
        _headers.insert(
                        make_pair("X-Toon-User-ID", toonim::CTNHttpConfig::getInstance()->getUserId()));
        _headers.insert(
                        make_pair("X-Toon-User-Token", toonim::CTNHttpConfig::getInstance()->getToken()));
        _headers.insert(make_pair("X-Toon-User-Agent", agent.str()));
    }
    
    const char *CTNBizJsonRequest::getPostBody(int64_t &size) {
        if (_inputContext != NULL) {
            
#ifdef RAPIDJSONWRAPPER
            CTNJsonWriter writer2;

            _inputContext->serialize(writer2);
            _postBody = writer2.toString();
            size = _postBody.length();
#else
            rapidjson::StringBuffer buffer;
            rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
            _inputContext->serialize(writer);
            size = buffer.GetSize();
            _postBody = string(buffer.GetString(), size);
#endif
            return _postBody.c_str();
        }
        return NULL;
    }
    
    void CTNBizJsonRequest::handResponse(CTNHttpResponse &response) {
        if (_cancel) {
            TNMPLOG("request has been canceled");
            if (_cancelFun) {
                _cancelFun(_userData);
            }
        } else {
            if (response.httpCode == 200) {
                thread execThread([](CTNBizJsonRequest* requst) -> void {
                    
#ifdef RAPIDJSONWRAPPER
                    CTNJsonReader doc(requst->_result);

                    if (!doc.hasParseErr()) {
                        CTNBizMeta meta;
                        CTNBizMeta::Parse(doc["meta"], meta);
                        CTNJsonValue& dataValue = doc["data"];
                        
                        if (meta.code == 0) {
                            if (requst->_handleResponseFun) {
                                requst->_handleResponseFun(dataValue, requst->_inputContext);
                            }
                            if (requst->_callbackFun) {//success
                                requst->_callbackFun(0, requst->_result.c_str(), requst->_userData);
                            }
                            TNMPLOG("hand callback  over");
                        }else{
                            TNMPLOG("handResponse url: " << requst->getUrl() << ", data =" << requst->_result << ", metaError = " << meta.code);
                            if (requst->_callbackFun) {//business failed
                                requst->_callbackFun(meta.code, meta.message.c_str(), requst->_userData);
                            }
                        }
                    }else{
                        //parse error
                        TNMPLOG("handResponse  url: " << requst->getUrl() << ", data =" << requst->_result << ", error = -1");
                        if (requst->_callbackFun) {//business failed
                            requst->_callbackFun(-1, requst->_result.c_str(), requst->_userData);
                        }
                    }
#else
                    rapidjson::Document doc;
                    doc.Parse(requst->_result.c_str(), requst->_result.length());
                    
                    if (doc.GetParseError() == rapidjson::kParseErrorNone) {
                        rapidjson::Value &metaValue = doc["meta"];
                        CTNBizMeta meta;
                        CTNBizMeta::Parse(metaValue, meta);
                        rapidjson::Value &dataValue = doc["data"];
                        if (meta.code == 0) {
                            if (requst->_handleResponseFun) {
                                requst->_handleResponseFun(dataValue, requst->_inputContext);
                            }
                            if (requst->_callbackFun) {//success
                                requst->_callbackFun(0, requst->_result.c_str(), requst->_userData);
                            }
                            TNMPLOG("hand callback  over");
                        } else {
                            TNMPLOG("handResponse url: " << requst->getUrl() << ", data =" << requst->_result << ", metaError = " << meta.code);
                            if (requst->_callbackFun) {//business failed
                                requst->_callbackFun(meta.code, meta.message.c_str(), requst->_userData);
                            }
                        }
                    } else {
                        //parse error
                        TNMPLOG("handResponse  url: " << requst->getUrl() << ", data =" << requst->_result << ", error = -1");
                        if (requst->_callbackFun) {//business failed
                            requst->_callbackFun(-1, requst->_result.c_str(), requst->_userData);
                        }
                    }
#endif
                    delete requst;
                },this);
                execThread.detach();
                return;
            } else {
                TNMPLOG("handResponse error url=" << getUrl() << ", error=" << response.errStr);
                if (_callbackFun) {//net error failed
                    _callbackFun(response.httpCode, response.errStr.c_str(), _userData);
                }
            }
            
        }
        
        delete this;
        
    }
}


