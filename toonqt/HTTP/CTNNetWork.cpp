//
// Created by juzenhon on 2017/8/28.
//

#include "CTNNetWork.h"
#include "curl/curl.h"
#include "CLog.h"
#include <thread>
#ifdef __linux__
#include <string.h>
#include <functional>
#endif

CTNHttpRequest::CTNHttpRequest() : _cancel(false), _running(false), _userP1(NULL), _requestHandle(NULL) {
    TNMPLOG("CTNHttpRequest constructor");
    _url = "";
    _proCb = nullptr;
    _name = nullptr;
    _content = nullptr;
}

CTNHttpRequest::~CTNHttpRequest() {
//    for (int32_t formListPos = 0; formListPos < _formdataList.size(); ++formListPos) {
//        free(_name[formListPos]);
//        free(_content[formListPos]);
//    }
//    TNMPLOG("CTNHttpRequest destructor");
}

map<string, string> &CTNHttpRequest::getHeaders() {
    return _headers;
}

std::map<std::string, std::string> &CTNHttpRequest::getFormdataList(){
    return _formdataList;
}

void CTNHttpRequest::setFormdataList(std::map<std::string, std::string> formlist){
    _formdataList = formlist;
}

CTNHttpMethod CTNHttpRequest::getMethod() {
    return _method;
}

void CTNHttpRequest::cancel() {
    _cancel = true;
    if (_running) {
        CTNNetWork::getClient()->cancelRequest(this);
    }
}

string &CTNHttpRequest::getUrl() {
    return _url;
}

void CTNHttpRequest::setUrl(const char *url) {
    _url = url;
}

void CTNHttpRequest::enqueue() {
    CTNNetWork::getClient()->enqueue(this);
}

const char *CTNHttpRequest::getPostBody(int64_t &size) {
    size = 0;
    return NULL;
}

ProgressCallback CTNHttpRequest::getProgressCallback(){
    return _proCb;
}

void CTNHttpRequest::setProgressCallback(ProgressCallback pCb){
    _proCb = pCb;
}

void CTNHttpRequest::setIdentifier(char *identifier){
    _identifier = identifier;
}

char* CTNHttpRequest::getIdentifier(){
    return _identifier;
}

std::string CTNHttpRequest::getDownloadRange(){
    return _downloadRange;
}

void CTNHttpRequest::setDownloadRange(std::string range){
    _downloadRange = range;
}

size_t nousecb(char *buffer, size_t x, size_t y, void *userdata){
    (void)buffer;
    (void)userdata;
    return x * y;
}

int64_t CTNNetWork::getDownloadFileLength(const char *url){
    CURL *easy_handle = NULL;
    int ret = CURLE_OK;
    double size = -1;
    
    do{
        easy_handle = curl_easy_init();
        if (!easy_handle)
        {
            TNMPLOG("curl_easy_init error");
            break;
        }
        
        // Only get the header data
        ret = curl_easy_setopt(easy_handle, CURLOPT_URL, url);
        ret |= curl_easy_setopt(easy_handle, CURLOPT_HEADER, 1L);
        ret |= curl_easy_setopt(easy_handle, CURLOPT_NOBODY, 1L);
        ret |= curl_easy_setopt(easy_handle, CURLOPT_WRITEFUNCTION, nousecb);    //will return error code 23 without this sentence on windows
        
        if (0 == strncmp(url, "https", 5)) {
            curl_easy_setopt(easy_handle, CURLOPT_USE_SSL, CURLUSESSL_ALL);
            if (_cerPath.length() > 0) {
                curl_easy_setopt(easy_handle, CURLOPT_SSL_VERIFYPEER, 1L);
                curl_easy_setopt(easy_handle, CURLOPT_SSL_VERIFYHOST, 1L);
                //ca证书的路径
                curl_easy_setopt(easy_handle, CURLOPT_CAPATH, _cerPath.c_str());
            } else {
                curl_easy_setopt(easy_handle, CURLOPT_SSL_VERIFYPEER, 0L);
                curl_easy_setopt(easy_handle, CURLOPT_SSL_VERIFYHOST, 0L);
            }
        }
        
        if (ret != CURLE_OK){
            TNMPLOG("curl_easy_setopt error");
            break;
        }
        
        ret = curl_easy_perform(easy_handle);
        if (ret != CURLE_OK){
            TNMPLOG("error:" << ret <<":" << curl_easy_strerror(static_cast<CURLcode>(ret)));
            break;
        }
        
        // size = -1 if no Content-Length return or Content-Length=0
        ret = curl_easy_getinfo(easy_handle, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &size);
        if (ret != CURLE_OK){
            TNMPLOG("curl_easy_getinfo error");
            break;
        }
        
    }while(0);
    
    curl_easy_cleanup(easy_handle);
    return size;
}

/**
 *
 * @param dataPtr data
 * @param len len
 * @return 处理的字节数
 */
int32_t CTNHttpRequest::writeTo(const char *dataPtr, int32_t len) {
    string str(dataPtr, len);
//    TNMPLOG("writeTo : " << str.c_str());
    _result.append(dataPtr, len);
    return len;
}

//------------------------------------------------------

static char debugData[256];

int debug_callback(CURL *handle, curl_infotype type, char *data, size_t size, void *userPtr) {
    switch (type) {
        case CURLINFO_TEXT:
            break;
        case CURLINFO_HEADER_IN:
            break;
        case CURLINFO_HEADER_OUT:
            break;
        case CURLINFO_DATA_IN:
            break;
        case CURLINFO_DATA_OUT:
            break;
        case CURLINFO_SSL_DATA_IN:
            break;
        case CURLINFO_SSL_DATA_OUT:
            break;
        case CURLINFO_END:
            break;

    }
    TNMPLOG("debug_callback " << type);
    return 0;
}

static size_t header_callback(char *buffer, size_t size, size_t nitems, void *userdata) {
    /* received header is nitems * size long in 'buffer' NOT ZERO TERMINATED */
    /* 'userdata' is set with CURLOPT_HEADERDATA */
    string str(buffer, size * nitems);
    TNMPLOG("header_callback : " << str.c_str());
    return nitems * size;
}

static size_t http_write_callback(void *ptr, size_t size, size_t nmemb, void *requestPtr) {
    CTNHttpRequest *request = (CTNHttpRequest *) requestPtr;
    size_t len = size * nmemb;
    int32_t ret = request->writeTo((char *) ptr, len);
    return ret;
}

//size_t http_read_callback(char *buffer, size_t size, size_t nItems, void *requestPtr) {
//    return 0;
//}

static void
lock_function(CURL *handle, curl_lock_data data, curl_lock_access access, void *userptr) {

}

static void unlock_function(CURL *handle, curl_lock_data data, void *userptr) {

}


CTNNetWork::CTNNetWork() : _net_running(true), _exec_count(0), _timeout(30) {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    _shareHandle = curl_share_init();
    curl_share_setopt(_shareHandle, CURLSHOPT_SHARE, CURL_LOCK_DATA_DNS);
    curl_share_setopt(_shareHandle, CURLSHOPT_LOCKFUNC, lock_function);
    curl_share_setopt(_shareHandle, CURLSHOPT_UNLOCKFUNC, unlock_function);
//    curl_share_setopt(_shareHandle, CURLSHOPT_USERDATA, );
    auto execFun = std::bind(&CTNNetWork::loopRequests, this);
    std::thread task(execFun);
    task.detach();
}

CTNNetWork::~CTNNetWork() {
    curl_share_cleanup(_shareHandle);
    curl_global_cleanup();
}

void CTNNetWork::setTimeout(int seconds) {
    _timeout = seconds;
}

void CTNNetWork::setCerPath(const char *cerPath) {
    _cerPath = cerPath;
}

void CTNNetWork::cancelRequest(CTNHttpRequest *request) {
    if (_multi_handle && request->_requestHandle) {
        curl_multi_remove_handle(_multi_handle, request->_requestHandle);
    }
}

CURL *CTNNetWork::initReqForHandle(CTNHttpRequest *request) {
    string &url = request->getUrl();
    if (url.length() == 0) {
        TNMPLOG("CTNHttpRequest url is empty!!!!");
        return NULL;
    }
    CURL *easy_handle = curl_easy_init();
    curl_easy_setopt(easy_handle, CURLOPT_SHARE, _shareHandle);
    curl_easy_setopt(easy_handle, CURLOPT_DNS_CACHE_TIMEOUT, 4 * 3600);
    curl_easy_setopt(easy_handle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(easy_handle, CURLOPT_PRIVATE, request);
    struct curl_slist *curl_headers = NULL;
    std::map<string, string> &headerMap = request->getHeaders();
    std::map<std::string, std::string> &formdataList = request->getFormdataList();
    request->_name = new char*[formdataList.size()];
    request->_content = new char*[formdataList.size()];
    int formListPos = 0;
    for (auto iter = headerMap.begin(); iter != headerMap.end(); iter++) {
        string header(iter->first);
        header.append(":");
        header.append(iter->second);
        curl_headers = curl_slist_append(curl_headers, header.c_str());
    }
    curl_easy_setopt(easy_handle, CURLOPT_ACCEPT_ENCODING, "gzip");
    if (request->getMethod() == CTNHttpMethod::Get) {
        curl_easy_setopt(easy_handle, CURLOPT_HTTPGET, 1L);
        std::string range = request->getDownloadRange();
        if (range.length() > 0) {
            curl_easy_setopt(easy_handle, CURLOPT_RANGE, range.c_str());
        }
    } else if (request->getMethod() == CTNHttpMethod::Post) {
        curl_headers = curl_slist_append(curl_headers,
                                         "Content-Type:application/json; charset=utf-8");

        curl_easy_setopt(easy_handle, CURLOPT_POST, 1L);
        int64_t postSize;
        curl_easy_setopt(easy_handle, CURLOPT_POSTFIELDS, request->getPostBody(postSize));
        curl_easy_setopt(easy_handle, CURLOPT_POSTFIELDSIZE, postSize);
        
        
        
        if (formdataList.size() > 0) {
            struct curl_httppost *formpost=NULL;
            struct curl_httppost *lastptr=NULL;
            
            for (std::map<std::string, std::string>::iterator iter = formdataList.begin(); iter != formdataList.end() ; ++iter, ++formListPos) {
                request->_name[formListPos] = new char[iter->first.length() + 1];
                strcpy(request->_name[formListPos], iter->first.c_str());
                request->_name[formListPos][iter->first.length()] = 0;
                request->_content[formListPos] = new char[iter->second.length() + 1];
                strcpy(request->_content[formListPos], iter->second.c_str());
                request->_content[formListPos][iter->second.length()] = 0;
                curl_formadd(&formpost, &lastptr, CURLFORM_PTRNAME, request->_name[formListPos], CURLFORM_PTRCONTENTS, request->_content[formListPos], CURLFORM_END);
                // 设置POST 参数
                TNMPLOG("formpost name:" << iter->first << ", contents:" << iter->second);
            }
            
            int64_t bodySize = 0;
            
            curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "file", CURLFORM_BUFFER, "file",
                         CURLFORM_BUFFERPTR, request->getPostBody(bodySize),
                         CURLFORM_BUFFERLENGTH, bodySize,
                         CURLFORM_CONTENTTYPE, "application/octet-stream",CURLFORM_END);
            
            curl_easy_setopt(easy_handle, CURLOPT_HTTPPOST, formpost);
        }
    }
    curl_easy_setopt(easy_handle, CURLOPT_FORBID_REUSE, 1);
    curl_easy_setopt(easy_handle, CURLOPT_TIMEOUT, _timeout);
    curl_easy_setopt(easy_handle, CURLOPT_NOSIGNAL, 1L);

    //proxy调试
//    curl_easy_setopt(easy_handle,CURLOPT_PROXY,"172.31.245.135");
//    curl_easy_setopt(easy_handle,CURLOPT_PROXYPORT,8888L);

    curl_easy_setopt(easy_handle, CURLOPT_HTTPHEADER, curl_headers);

    request->_userP1 = curl_headers;
    request->_requestHandle = easy_handle;

    if (url.compare(0, 5, "https") == 0) {
        curl_easy_setopt(easy_handle, CURLOPT_USE_SSL, CURLUSESSL_ALL);
        if (_cerPath.length() > 0) {
            curl_easy_setopt(easy_handle, CURLOPT_SSL_VERIFYPEER, 1L);
            curl_easy_setopt(easy_handle, CURLOPT_SSL_VERIFYHOST, 1L);
            //ca证书的路径
            curl_easy_setopt(easy_handle, CURLOPT_CAPATH, _cerPath.c_str());
        } else {
            curl_easy_setopt(easy_handle, CURLOPT_SSL_VERIFYPEER, 0L);
            curl_easy_setopt(easy_handle, CURLOPT_SSL_VERIFYHOST, 0L);
        }
        //For SSL engines that don't support certificate files the CURLOPT_CAINFO option is ignored.
//        curl_easy_setopt(curl, CURLOPT_CAINFO, "/etc/certs/cabundle.pem");

        /* 双向验证下面是客户端的ＣＡ*/
        //  curl_easy_setopt(curl,CURLOPT_CAPATH,"./");
//        curl_easy_setopt(curl,CURLOPT_SSLCERT,"client-cert.pem");
//        curl_easy_setopt(curl,CURLOPT_SSLCERTPASSWD,"password");
//        curl_easy_setopt(curl,CURLOPT_SSLCERTTYPE,"PEM");
//        curl_easy_setopt(curl,CURLOPT_SSLKEY,"client-key.pem");
//        curl_easy_setopt(curl,CURLOPT_SSLKEYPASSWD,"password");
//        curl_easy_setopt(curl,CURLOPT_SSLKEYTYPE,"PEM");
    }
    curl_easy_setopt(easy_handle, CURLOPT_HEADERFUNCTION, header_callback);
    curl_easy_setopt(easy_handle, CURLOPT_HEADERDATA, request);

    curl_easy_setopt(easy_handle, CURLOPT_WRITEFUNCTION, http_write_callback);
    curl_easy_setopt(easy_handle, CURLOPT_WRITEDATA, request);
    
    //wxy 添加进度回调
    if (request->getProgressCallback()) {
        curl_easy_setopt(easy_handle, CURLOPT_PROGRESSFUNCTION, request->getProgressCallback());
        curl_easy_setopt(easy_handle, CURLOPT_NOPROGRESS, false);
        curl_easy_setopt(easy_handle, CURLOPT_PROGRESSDATA, (void*)request->getIdentifier());
    }

    //向server写数据,默认调用fread从CURLOPT_READDATA指定的文件读数据
//    curl_easy_setopt(easy_handle, CURLOPT_READFUNCTION, http_read_callback);
//    curl_easy_setopt(easy_handle, CURLOPT_READDATA, request);

    //debug
    curl_easy_setopt(easy_handle, CURLOPT_DEBUGFUNCTION, debug_callback);
    curl_easy_setopt(easy_handle, CURLOPT_DEBUGDATA, debugData);

    /* ask libcurl to show us the verbose output */
//    curl_easy_setopt(easy_handle, CURLOPT_VERBOSE, 1L);
    //错误信息获取

    return easy_handle;
}

void CTNNetWork::readResponseInfo(CURLM *cm) {
    TNMPLOG("readResponseInfo");
    int msgs_left;
    CURLMsg *msg = NULL;
    while ((msg = curl_multi_info_read(cm, &msgs_left))) {//每次调用都会删除cm结果集表列头部的结点

        if (msg->msg == CURLMSG_DONE) {
            CURL *easy_handle = msg->easy_handle;
            CURLcode return_code = msg->data.result;

            void *requestPtr = NULL;
            curl_easy_getinfo(easy_handle, CURLINFO_PRIVATE, &requestPtr);
            CTNHttpRequest *request = (CTNHttpRequest *) requestPtr;
            if (requestPtr == NULL) {
                TNMPLOG("request ptr is null");
                curl_easy_cleanup(easy_handle);
                return;
            }

            if (return_code != CURLE_OK) {
                TNMPLOG("response error !!!");
                request->_response.httpCode = -1;
                request->_response.errStr = curl_easy_strerror(return_code);
            } else{

                long ret_code = 0, http_version, verify_result;
                char *request_url = NULL;
//            char *ip = NULL;
//            const char *localIp = NULL;
                double lookup_time, connect_time, ssl_connect_time, pre_transfer_time, transfer_time;

                curl_easy_getinfo(easy_handle, CURLINFO_RESPONSE_CODE, &ret_code);
                curl_easy_getinfo(easy_handle, CURLINFO_EFFECTIVE_URL, &request_url);
                curl_easy_getinfo(easy_handle, CURLINFO_NAMELOOKUP_TIME, &lookup_time);
                curl_easy_getinfo(easy_handle, CURLINFO_CONNECT_TIME, &connect_time);
                curl_easy_getinfo(easy_handle, CURLINFO_APPCONNECT_TIME, &ssl_connect_time);
                curl_easy_getinfo(easy_handle, CURLINFO_PRETRANSFER_TIME, &pre_transfer_time);
                curl_easy_getinfo(easy_handle, CURLINFO_STARTTRANSFER_TIME, &transfer_time);
//            curl_easy_getinfo(easy_handle, CURLINFO_PRIMARY_IP, &ip);
//            curl_easy_getinfo(eh, CURLINFO_LOCAL_IP, &localIp);
                //CURL_HTTP_VERSION_1_0,CURL_HTTP_VERSION_1_1,CURL_HTTP_VERSION_2_0,0
                curl_easy_getinfo(easy_handle, CURLINFO_HTTP_VERSION, &http_version);
                curl_easy_getinfo(easy_handle, CURLINFO_SSL_VERIFYRESULT, &verify_result);

                curl_multi_remove_handle(cm, easy_handle);

                curl_slist_free_all((struct curl_slist *) request->_userP1);
                curl_easy_cleanup(easy_handle);

                CTNHttpResponse &response = request->_response;
                if (request_url) {
                    response.url = request_url;
                }
                response.dns_time = lookup_time;
                response.connect_time = connect_time;
                response.ssl_connect_time = ssl_connect_time;
                response.transfer_time = transfer_time;
                response.http_version = http_version;
                // Get HTTP status code
                response.httpCode = ret_code;
            }

            request->handResponse(request->_response);
        } else {
            TNMPLOG("error: after curl_multi_info_read(), CURLMsg " << msg->msg);
        }
    }

}

int CTNNetWork::joinRequestForExec(void *multi_handle) {

    unique_lock<mutex> lock(_queueMutex);
    int ret_count = _exec_count;
    while (_requestQueue.size() > 0 && ret_count < MAX_EXEC_COUNT) {
        CTNHttpRequest *request = _requestQueue.front();
        _requestQueue.pop();
        if (request->_cancel) {
            TNMPLOG("request has canceled ,and not joined for exec");
            request->handResponse(request->_response);
        } else {
            CURL *easy_handle = initReqForHandle(request);
            if (easy_handle) {
                curl_multi_add_handle(multi_handle, easy_handle);
                request->_running = true;
                ret_count++;
            }
        }
    }

    return ret_count;
}

void CTNNetWork::loopRequests() {

    CURLM *multi_handle = curl_multi_init();
    curl_multi_setopt(multi_handle, CURLMOPT_PIPELINING, CURLPIPE_HTTP1 | CURLPIPE_MULTIPLEX);
    curl_multi_setopt(multi_handle, CURLMOPT_MAX_PIPELINE_LENGTH, 5L);//default is 5
    curl_multi_setopt(multi_handle, CURLMoption::CURLMOPT_MAX_HOST_CONNECTIONS, 3L);//default is 0
    curl_multi_setopt(multi_handle, CURLMoption::CURLMOPT_MAX_TOTAL_CONNECTIONS, 6L);
//    curl_multi_setopt(cm, CURLMoption::CURLMOPT_SOCKETFUNCTION, curl_my_socket_callback);
//    curl_multi_setopt(cm, CURLMoption::CURLMOPT_TIMERFUNCTION, timer_callback);
//    curl_multi_setopt(cm, CURLMoption::CURLMOPT_TIMERDATA, myUserp);

    int still_running = 0, repeats = 0;

    while (_net_running) {

        int req_count = joinRequestForExec(multi_handle);
        if (req_count == 0) {
            TNMPLOG("----- no request waiting ---------");
            std::unique_lock<mutex> lock1(_conditionMutex);
            _condition.wait(lock1);
            continue;
        }
        int numfds = 0;
        CURLMcode mcode = curl_multi_perform(multi_handle, &still_running);
        if (mcode == CURLM_OK) {
            //实际上是调用了poll操作,time_us实际上由multi_timeout与time_us共同决定
            mcode = curl_multi_wait(multi_handle, NULL, 0, 300L, &numfds);
            _exec_count = still_running;
        }
        if (mcode != CURLM_OK) {
            TNMPLOG("curl_multi failed, code " << mcode);
            return;
        }

        TNMPLOG("--- netWork request  running -----count:  " << _exec_count);

        /* 'numfds' being zero means either a timeout or no file descriptors to
            wait for. Try timeout on first occurrence, then assume no file
            descriptors and no file descriptors to wait for means wait for 100
            milliseconds. */
        if (!numfds) {
            repeats++; /* count number of repeated zero numfds */
            if (repeats > 1) {
                /* sleep 100 milliseconds */
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        } else {
            repeats = 0;
        }

        readResponseInfo(multi_handle);
    }
    TNMPLOG("while is ended ");
    readResponseInfo(multi_handle);
    curl_multi_cleanup(multi_handle);
}

void CTNNetWork::enqueue(CTNHttpRequest *request) {
    _queueMutex.lock();
    _requestQueue.push(request);
    _queueMutex.unlock();
    _condition.notify_all();
}
