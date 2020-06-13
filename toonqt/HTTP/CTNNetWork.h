//
// Created by juzenhon on 2017/8/28.
//

#ifndef TMTP_CTNHTTPCLIENT_H
#define TMTP_CTNHTTPCLIENT_H

#include <string>
#include <map>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>

using namespace std;

enum CTNHttpMethod {
    Get,
    Post,
};

typedef int (*ProgressCallback)(void* progress_data, double t, double d, double ultotal, double ulnow);

class CTNHttpResponse {

public:
    string url;

    map<string, string> headers;

    string errStr;

    double dns_time;

    double connect_time;

    double ssl_connect_time;

    double transfer_time;

    double http_version;

    int32_t httpCode;
};

class CTNHttpRequest {

    friend class CTNNetWork;

public:

    CTNHttpRequest();

    virtual ~CTNHttpRequest();

    map<string, string> &getHeaders();
    
    std::map<std::string, std::string> &getFormdataList();
    
    void setFormdataList(std::map<std::string, std::string> formlist);

    CTNHttpMethod getMethod();

    string &getUrl();

    void setUrl(const char *url);
    
    ProgressCallback getProgressCallback();
    
    void setProgressCallback(ProgressCallback pCb);
    
    void setIdentifier(char* identifier);
    
    char* getIdentifier();
    
    void setDownloadRange(std::string range);
    
    std::string getDownloadRange();

    void cancel();

    /**
     * 入队开始执行
     */
    void enqueue();

    /**
     * 获取请求body中的数据
     * @param size 数据长度
     * @return  bufPtr body数据
     */
    virtual const char *getPostBody(int64_t &size);

    /**
     * 数据写到本地
     * @param dataPtr data
     * @param len   len
     * @return 实际处理的长度
     */
    virtual int32_t writeTo(const char *dataPtr, int32_t len);

protected:

    /**
   * 处理response
     * @param response 响应代码
   */
    virtual void handResponse(CTNHttpResponse &response) = 0;

protected:

    map<string, string> _headers;
    
    std::map<std::string, std::string> _formdataList;//wxy 上传
    char** _name;
    char** _content;

    ProgressCallback _proCb;
    
    CTNHttpMethod _method = Get;

    string _url;

    string _postBody;

    string _result;

    bool _cancel;

    CTNHttpResponse _response;

private:
    bool _running;
    void *_userP1;
    void *_requestHandle;
    char* _identifier;
    std::string _downloadRange;
};

class CTNNetWork {

public:

    static CTNNetWork *getClient() {
        static CTNNetWork sInstance;
        return &sInstance;
    }

    ~CTNNetWork();

public:

    void setTimeout(int seconds);

    void setCerPath(const char *cerPath);
    
    int64_t getDownloadFileLength(const char *url);

private:

    friend class CTNHttpRequest;

    void enqueue(CTNHttpRequest *request);

    void *initReqForHandle(CTNHttpRequest *request);

    void loopRequests();

    /**
     * 把队列中的请求加入client执行
     * @param multi_handle
     * @return
     */
    int joinRequestForExec(void *multi_handle);

    void readResponseInfo(void *cm_handle);

    void cancelRequest(CTNHttpRequest *request);

private:
    CTNNetWork();

    CTNNetWork(const CTNNetWork &rhs);

    const CTNNetWork operator=(const CTNNetWork &rhs);

    int _timeout;

    std::string _cerPath;

    queue<CTNHttpRequest *> _requestQueue;

    mutex _queueMutex;

    mutex _conditionMutex;

    std::condition_variable _condition;

    bool _net_running;

    int _exec_count;

    void *_multi_handle;
	
	void* _shareHandle;

    const static int MAX_EXEC_COUNT = 4;
};


#endif //TMTP_CTNHTTPCLIENT_H
