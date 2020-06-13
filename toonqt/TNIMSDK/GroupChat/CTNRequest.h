//
// Created by juzenhon on 2017/9/7.
//

#ifndef TMTP_CTNBASECALLBACK_H
#define TMTP_CTNBASECALLBACK_H

#ifdef __linux__
#include <functional>
#endif
#include "CTNNetWork.h"
#include "CTNHttpConfig.h"
#include "CTNBaseBean.h"
#include "CTNJsonUtils.hpp"

namespace toonim {
#ifdef RAPIDJSONWRAPPER
    typedef std::function<void(CTNJsonValue &,CTNBaseInputBean* )> HandleResponseFun;
#else
    typedef std::function<void(rapidjson::Value &,CTNBaseInputBean* )> HandleResponseFun;
#endif
    
    typedef std::function<void(int, const char *, void *)> RequestCallbackFun;
    
    typedef std::function<void(void *)> CanceledFun;
    
    class CTNBizJsonRequest : public CTNHttpRequest {
        
    public:
        CTNBizJsonRequest();
        
        CTNBizJsonRequest(CTNBaseInputBean *bean, CTNHttpMethod method = Post);
        
        ~CTNBizJsonRequest();
        
        /**
         *
         * @param responseFun 业务处理函数
         * @param callbackFun 原数据往上层回调处理
         * @param userData 自定义指针,会通过callbackFun回传给你,用来做标识
         * @param canceledFun 请求处理函数
         */
        void setCallback(HandleResponseFun responseFun, RequestCallbackFun callbackFun,void *userData,CanceledFun canceledFun = nullptr);
        
        const char *getPostBody(int64_t &size);
        
        void handResponse(CTNHttpResponse &response);
        
    private:
        void initCommonHeader();
        
    private:
        
        HandleResponseFun _handleResponseFun;
        
        RequestCallbackFun _callbackFun;
        
        CanceledFun _cancelFun;
        
        void *_userData;
        
        CTNBaseInputBean* _inputContext;
    };
}

#endif //TMTP_CTNBASECALLBACK_H
