//
//  CTNChatManager.cpp
//  TNIMSDK
//
//  Created by 王旭影 on 17/8/23.
//  Copyright © 2017年 syswin. All rights reserved.
//

#include "CTNChatManager.hpp"
#include <tmtp_type.h>
#include <CLog.h>
#include "tmtp_biz.h"
#include <sstream>
#include <algorithm>
#include <regex>
#include "CTNDBHeader.h"
#include "CTNMPConfig.h"
#include "writer.h"
#include "rapidjson.h"
#include "stringbuffer.h"
#include "document.h"
#include "pointer.h"
#include "CTNHttpBizApi.h"
#include "CTNDBUtils.hpp"
#include "prettywriter.h"
#include "CTNDBSettings.hpp"
#include "CTNJsonUtils.hpp"
#include "CTNDBChat.hpp"
#include "CTNBaseBean.h"

//using namespace rapidjson;

namespace toonim {
    

    void initLog(const char* appPath){
        if (appPath == nullptr || strlen(appPath) == 0){
            return;
        }
        
        CLog::instance()->setPath(appPath);
   }

    ITnImSdk* initIm(CTNClientInfo &clientInfo) {
        CTNChatManager::instance()->setClientInfo(clientInfo);
        
        //免打扰依赖于myfeedid信息，修改后需要重新加载
        if (CTNDBSetting::instance() != nullptr && clientInfo.feedList.size() > 0){
            CTNDBSetting::instance()->loadSettingDisturbCache();
        }
        return CTNChatManager::instance();
    }
    
 
    ITnImSdk* getImSDK(){
//        assert(CTNChatManager::_instance !== nullptr);
        return CTNChatManager::instance();
    }
    
    //checkcode
    CTNChatManager* CTNChatManager::_instance = nullptr;
    
    CTNChatManager::CTNChatManager () {
        _currProcess = nullptr;
        _callback = nullptr;
    }
    
    CTNChatManager::~CTNChatManager () {
        _offMsgQueue.clear();
    }
    
    CTNChatManager* CTNChatManager::instance(){
        if (_instance == nullptr){
            _instance = new CTNChatManager();
        }
        
        return _instance;
    }
    
    void CTNChatManager::updateMyFeedList(vector<string>& feedList) {
        _clientInfo.feedList = feedList;
        this->printMyFeedIdList();
        //免打扰依赖于myfeedid信息，修改后需要重新加载
        ITnImDBSettings* setingsDB = getSettingsDB();
        if (setingsDB != nullptr){
            CTNDBSetting::instance()->loadSettingDisturbCache();
        }
    }
    
    void CTNChatManager::printMyFeedIdList() {
        if (_clientInfo.feedList.size() == 0) {
            TNMPLOG("myFeedIdlist is nil!");
        } else {
            std::string feedId;
            for (int i=0; i<_clientInfo.feedList.size(); i++) {
                feedId = feedId + _clientInfo.feedList.at(i) + ",";
            }
            TNMPLOG("myFeedIdlist is " << feedId);
        }
    }
    
  
    /////// ITNMPResponse ////////////
    //2、登录结果
    void CTNChatManager::loginResp(int32_t code, vector<int>& contentTypes, map<string, int> &forbiddenMap) {
        TNMPLOG("loginResp:"<<code);
        
        //process others
        switch (code) {
            case Toon::CONNECT_RESULT_SUCCESS:
            {
                _offMsgQueue.clear();
                CTNDBSetting* setingsDB = (CTNDBSetting*)getSettingsDB();
                if (setingsDB != nullptr){
//                    forbiddenMap[IM_SINGLECHAT_SEND_DISABLE] = 1;
//                    forbiddenMap[IM_GROUCHAT_SEND_DISABLE] = 1;
//                    forbiddenMap[IM_GROUPCHAT_CREATE_DISABLE] = 1;
//                    forbiddenMap[IM_GROUPCHAT_ADDMEMBER_DISABLE] = 1;
//
                    setingsDB->setForbiddenFeatureMap(forbiddenMap);
                }
                
                if (_callback != nullptr){
                    _callback->loginResp(0, contentTypes);
                    
                } else {
                    TNMPLOG("_callback is null loginResp CONNECT_RESULT_SUCCESS");
                }
                break;
            }
            case Toon::CONNECT_RESULT_SERVICE_UNAVAILABLE:
                break;
            case Toon::CONNECT_RESULT_ERROR_PROTOCOL:
            case Toon::CONNECT_RESULT_ERROR_INDICATE:
            case Toon::CONNECT_RESULT_ERROR_USERNAME_OR_PASSWORD:
            case Toon::CONNECT_RESULT_KICKOUT:
            case Toon::CONNECT_RESULT_OTHER:
            default:
                TNMPLOG("Kickout:"<< _clientInfo.clientId);
                this->kickOut();
                break;
        }
    }
    
    void CTNChatManager::kickOut() {
        _offMsgQueue.clear();
        
        if (_callback != nullptr){
            _callback->kickOut();
        } else {
            TNMPLOG("_callback is null kickOut");
        }
    }
    
    void CTNChatManager::offMsgResp(Toon::OffMsgResp* offMsg) {
        if (offMsg == nullptr){
            TNMPLOG("offMsgResp offMsg is null");
            return;
        }
        
        TNMPLOG("offMsgResp:" << offMsg->msgs.size()<<" reqId:"<<offMsg->req_id<<" code:"<<offMsg->code);
        // code 0 成功 code 1 成功了 但是没有拉完
        if (offMsg->code != 0 && offMsg->code != 1) {
            // 请求错误 不处理任何
            TNMPLOG("offMsgResp err, code:" << offMsg->code<<" reqId:"<<offMsg->req_id);
            //遗留在队列中需要处理
            return;
        }

        this->processHistoryMessages(offMsg->msgs, offMsg->req_id);
    }
    
    void CTNChatManager::hotSessionResp(Toon::HotSessionResp* hotSessions) {
        TNMPLOG("CTNChatManager::hotSessionResp");
        if (hotSessions == nullptr){
            TNMPLOG("hotSessions is nullptr hotSessionResp");
            return;
        }
        
        this->processHotSessionResp(hotSessions->vSessionInfo);
    }
    
    void CTNChatManager::syncSessionStatusResp(Toon::SyncSessionStatusResp* sessionStatus) {
        if (_callback != nullptr){
            string sessionId;
            _callback->syncSessionStatusResp(sessionId.c_str());
        } else {
            TNMPLOG("_callback is null syncSessionStatusResp");
        }
    }
    
    void CTNChatManager::syncSessionStatusReq(Toon::SyncSessionStatusReq* sessionStatus) {
        if (sessionStatus == nullptr) {
            return;
        }
        string sessionId = toonim::generateSessionId(sessionStatus->session_name.type, sessionStatus->session_name.from, sessionStatus->session_name.to, true);
        CTNSession session = toonim::getChatDB()->getSession(sessionId.c_str());
        toonim::getChatDB()->markSessionRead(sessionId.c_str());
        //标记为已读时需要判断该会话是否为重要消息，需要清除重要消息会话中的对应消息
        this->deleteImportantMessage(session);
        
        if (_callback != nullptr && sessionId.length() > 0){
            _callback->syncSessionStatusReq(sessionId.c_str());
        } else {
            TNMPLOG("_callback is null syncSessionStatusReq");
        }
    }
    
    void CTNChatManager::msgAck(string& msgId, int64_t seqId, int32_t type, string& from,string& to, int32_t result, int64_t timestamp) {
        TNMPLOG("msgAck msgId:"<<msgId.c_str()<<" seqId:"<<seqId<<" result:"<<result);
        
        string sessionId = generateSessionId(type, from, to, true);
        CTNMessage message = toonim::getChatDB()->getMessage(sessionId.c_str(), msgId.c_str());
        
        if (message.isEmpty()) {
            TNMPLOG("can't find message from database:" << msgId);
            return ;
        }
        
        //防止服务器返回seqId错误导致消息顺序紊乱
        if (seqId > 0){
            message.seqId = (int64_t)seqId;//服务端给序列号
        }
        
        //消息时间要更改为服务器时间
        if (timestamp > 0) {
            message.timestamp = timestamp;
        }
        string msgContent = message.genBodyJson();
        
        if (result == MESSAGE_ACK_MSG_SUCCESS) {
            TNMPLOG("seqId:" << seqId << "\tSEND\nOK\t" << message.msgId << "\t" << msgContent);//LOG_LEVEL_INFO
        } else {
            TNMPLOG("seqId:" << seqId << "\tSEND\tFAILED\t" << message.msgId << "\t" << msgContent);//LOG_LEVEL_INFO
        }
        
        //发送违禁词服务端返回错误码1，前端需要显示成发送成功，需要把错误码改成0
        if (result == MESSAGE_ACK_MSG_PROHIBITED) {
            result = MESSAGE_ACK_MSG_SUCCESS;
        }
        
        //NEED
        if (message.type == CTNIMMessageTypeMsgSingleOperate
            || message.type == CTNIMMessageTypeMsgGroupOperate) {
            
            CTNMessage operedMsg = processMessageOperate(message);
            toonim::getChatDB()->updateMessage(message);
            this->processMsgOperateAck(operedMsg, true);
            return;
        }
        
        this->processMessageAck(message, result);
        
//        if (_callback != nullptr){
//            _callback->msgAck(sessionId.c_str(), msgId.c_str(), seqId, result);
//        } else {
//            TNMPLOG("_callback is null msgAck");
//        }
    }
    
    //7、接收消息（未读数处理）
    void CTNChatManager::msgRecv(int32_t type, Toon::MsgReq * req) {
        Toon::BizMsg bizMsg;
        try {
            taf::JceInputStream<taf::BufferReader> is;
            
            is.setBuffer(req->content.data(), req->content.size());
            bizMsg.readFrom(is);
        } catch (...) {
        }
        
        if (isInvalid(type, req)) {
            TNMPLOG("invalid message msgRecv");
            return;
        }
        
        TNMPLOG("msgRecv type:"<<type<<" msg:"<<req->msg_id.c_str()<<" content:"<<bizMsg.content);
        CTNMessage message = msgReqToIMMessage(type, req);
        
        this->processRecvOnlineMessage(message);
    }
    
    void CTNChatManager::netStatusChanged(TNMPNetStatus status) {
        TNMPLOG("netStatusChanged:"<<status);
        if (_callback != nullptr){
            _callback->netStatusChanged(status);
        } else {
            TNMPLOG("_callback is null netStatusChanged");
        }
        
   }
    
    void CTNChatManager::userOlineStatus(Toon::NotifyPresenceStatusResp& userStatusResp) {
        std::map<string, int32_t> mapClientStatus;
        
        vector<Toon::ClientPresenceStatus>::iterator itTmp = userStatusResp.vecPresenceStatus.begin();
        while (itTmp != userStatusResp.vecPresenceStatus.end()){
            mapClientStatus[itTmp->client_id] = itTmp->nPresenceStatus;
            TNMPLOG("userOnlineStatus:"<<itTmp->client_id<<" STATUS:"<<(int)itTmp->nPresenceStatus);
            itTmp ++;
        }
        
        TNMPLOG("userOnlineStatus:"<<mapClientStatus.size());
        if (mapClientStatus.empty()){
            return;
        }
      
        if (_callback != nullptr){
            _callback->userOnlineStatus(mapClientStatus);
        } else {
            TNMPLOG("_callback is null userOlineStatus");
        }
    }
    
    void CTNChatManager::daInfo(string& atrName, map<string, string> & property) {
        if (_callback != nullptr) {
            _callback->daInfo(atrName.c_str(), property);
        }
    }
    
    /////// ITnImSdk ////////////
    void CTNChatManager::addNoticeFilter(int32_t catalogId, std::vector<int>& subCatalogId, const char* broadcast)
    {
        if (broadcast == NULL || strlen(broadcast) == 0){
            return;
        }
        
        CTNNoticeFilter filter;
        filter.catalogId = catalogId;
        
        std::set<int> subCatalogIdSet;
        subCatalogIdSet.insert(subCatalogId.begin(), subCatalogId.end());
        filter.subCatalogIdSet = subCatalogIdSet;
        filter.broadcast = broadcast;
        
        std::unique_lock<std::mutex> unilock(_noticeFileterMutex);
        _noticeFilterMap[catalogId] = filter;
    }
    
    
    int32_t CTNChatManager::getNetStatus()
    {
        if (_currProcess == nullptr){
            return TNMPNetNone;
        }
        
        return _currProcess->getNetStatus();
    }
    
    
    void CTNChatManager::addHostInfo(const char* host, int32_t port, bool isSSL)
    {
        if (host == NULL || strlen(host) == 0){
            return;
        }

        TMTPHostInfo hostInfo;
        hostInfo.host = host;
        hostInfo.port = port;
        hostInfo.isSSL = isSSL;
        
        vector<TMTPHostInfo>::iterator iter = find(_serverVector.begin(), _serverVector.end(), hostInfo);
        
        if (iter == _serverVector.end()) {
            _serverVector.push_back(hostInfo);
        }
    }
    
    //1、登录 外部接口
    int32_t CTNChatManager::login(const char* username, const char* password) {
        if (password == NULL || strlen(password) == 0){
            TNMPLOG("password can't be empty!!");
            return -1;
        }
        

        TNMPLOG("TNIMClientTNMP login ENTER  tk:" << password);
        if (_serverVector.size() == 0
            || _clientInfo.clientId.length() == 0) {
            TNMPLOG("IM Server is not init!");
            return -1;
        }
        
        //save the username password
        _clientInfo.setUsername(username);
        _clientInfo.setToken(password);
        
        return this->login();
     }
    
    int32_t CTNChatManager::login()
    {
        std::unique_lock<std::mutex> unilock(_loginMutex);
        if (this->getNetStatus() == TNMPNetConnecting
            || this->getNetStatus() == TNMPNetConnected
            || this->getNetStatus() == TNMPNetRecving){
            TNMPLOG("Netstatus is ok!"<<this->getNetStatus());
            return -1;
        }
        
        if (_clientInfo.token.length() == 0){
            TNMPLOG("CTNChatManager::login token is EMPTY FAILED!!!");
            return -1;
        }
        
        std::vector<TMTPHostInfo> vctHostInfo = _serverVector;
        
        TNMPLOG("Toon appType:"<<_clientInfo.toonType<<" version:"<<_clientInfo.version);
        this->createProcessThread();
        if (_currProcess == nullptr){
            TNMPLOG("createProcessThread FAILED!!!");
            return -1;
        }
        
        _currProcess->setClientInfo(vctHostInfo, _clientInfo.clientId.c_str(), _clientInfo.toonType,_clientInfo.apnsType, _clientInfo.version.c_str(), _clientInfo.deviceType, _clientInfo.pushServiceType);
        _currProcess->setUserInfo(_clientInfo.username.c_str(), _clientInfo.token.c_str(), _clientInfo.deviceId.c_str(), _clientInfo.pushToken.c_str());
        _currProcess->setAppPath(_clientInfo.appPath.c_str());
        _currProcess->start();
        
        return  0;
    }
    
    int32_t CTNChatManager::logout(bool notifyServer) {
        TNMPLOG("TNIMClientTNMP logout ENTER notifyServer:" << notifyServer);
        
        if (_currProcess == nullptr) {
            TNMPLOG("logout _process is nullptr");
            return -1;
        }
        
        try {
            _currProcess->logout(notifyServer);
            if (notifyServer){
                //退出登录后清空上一用户缓存
                toonim::resetDB();
                _arrRecvMsgId.clear();
            }
            TNMPLOG("after logout");
        } catch (...) {
            TNMPLOG("exception occur logout");
        }
        
        TNMPLOG("TNIMClientTNMP logout EXIT");
        
        return 0;
    }
    
    void CTNChatManager::reqSync(int32_t unreadCount, const char* pushToken){
        if (_currProcess == nullptr) {
            TNMPLOG("reqSync _currProcess is nullptr");
            return ;
        }
        
        try {
            Toon::SyncReq req;
            if (unreadCount >= 0) {
                req.apns_unreadnum = (taf::Int32)unreadCount;
            }
            
            //主动退出或者被踢不更新token
            if (pushToken != NULL && strlen(pushToken) > 0
                && this->getNetStatus() != TNMPNetLogout){
                req.device_token = pushToken;
                
                _clientInfo.pushToken = pushToken;
                _currProcess->setDeviceToken(pushToken);
            }
     
            _currProcess->syncReq(req);
            TNMPLOG("after reqSync");
        } catch (...) {
            TNMPLOG("exception occur reqSync");
        }
    }
    
    //6、发送消息
    int32_t CTNChatManager::sendMessage(CTNMessage* message) {
        if (message == nullptr){
            TNMPLOG("sendMessage message is nullptr failed!");
            return -1;
        }
        
        if (_currProcess == nullptr) {
            TNMPLOG("sendMessage _process is nullptr will login!");
            //修改无网重连后消息不能自动发出问题	创建currProcess
            this->login();
        }
        
        message->sessionId = generateSessionId(message->type, message->fromId, message->toId, true);
        message->sendStatus = CTNMessageSending;
        message->isMyself = CTNOwnerMyself;
        
        if(message->fromClientId.length() <= 0) {
            message->fromClientId = _clientInfo.clientId;
        }
        
        if (message->seqId <= 0) {
            int64_t localSeq = toonim::getChatDB()->getMaxSeqAllMessage(message->sessionId.c_str(), 2);
            
            if (localSeq <= 0) {
                message->seqId = 1;//wxy 本地无消息记录或者无发送成功的消息记录时，发送消息seqId默认从1开始计数，否则若消息从0开始计数，当出现连续发送超过一页消息记录时，消息拉取会出现问题，因为查询数据，seqID为0时，认为是第一次拉取数据，用户读取第一次拉取的消息得到最大的seqID为0时，继续拉消息，每次拉取的参数一样，底层只能从数据库中取出所有seqID为0的消息。
            } else {
                message->seqId = localSeq;
            }
        }
        
        if (message->timestamp <= 0) {
            message->timestamp = time(nullptr);
        }
        
        message->faultSeqId = -1;//发送消息默认为断层消息seqId为-1，表名无断层消息，底层做处理，wxy
        
        toonim::getChatDB()->replaceMessage(*message);
      
        //禁止群聊发送
        if (isDisableMessageSend(*message)){
            this->processMessageAck(*message, -1);
        }
        else{
            Toon::MsgReq *req = imMessageToMsgReq(message->type, *message);
            _currProcess->sendMsgReq(message->type, req, true);
        }
  
       
        bool isNewSession = false;
        CTNSession session = this->getSessionByMessage(*message, isNewSession);
        vector<toonim::CTNSession> sessionVector;
        sessionVector.push_back(session);
        toonim::getChatDB()->updateSession(sessionVector);
        if (_callback != nullptr) {
            std::string jsonStr = this->genSessionIdToJson(session.sessionId);
            _callback->notificationCenter(TNC_SESSION_CHANGE, jsonStr.c_str());
        }
        
        TNMPLOG("seqId:" << message->seqId << "\tSEND\tLOG\t" << message->msgId << "\t" << message->genBodyJson());//LOG_LEVEL_DEBUG 新接口没有定义topic参数
        
        return 0;
    }
    
    bool CTNChatManager::isDisableMessageSend(CTNMessage& message)
    {
        ITnImDBSettings* setingsDB = getSettingsDB();
        if (setingsDB == nullptr){
            return false;
        }
        
        //禁止单聊发送
        if (message.type == CTNIMMessageTypeChat && setingsDB->isForbiddenFeature(IM_SINGLECHAT_SEND_DISABLE)){
            return true;
        }
        
        //禁止群聊发送
        if (message.type == CTNIMMessageTypeGroupChat && setingsDB->isForbiddenFeature(IM_GROUCHAT_SEND_DISABLE)){
            return true;
        }
            
        return false;
    }
    
    void CTNChatManager::getLocalSessionBySessionItem(Toon::HotSessionItem &sessionItem, toonim::CTNSession &localSession){
        if (sessionItem.normal_top_msg.size() > 0) {
            localSession = getChatDB()->getSession(generateSessionId(sessionItem.normal_top_msg[0].type, sessionItem.normal_top_msg[0].item.from.c_str(), sessionItem.normal_top_msg[0].item.to.c_str(), this->isMySelfClientID(sessionItem.normal_top_msg[0].item.from_client_id)).c_str());
        }else if(sessionItem.priority_top_msg.size() > 0){
            localSession = getChatDB()->getSession(generateSessionId(sessionItem.priority_top_msg[0].type, sessionItem.priority_top_msg[0].item.from.c_str(), sessionItem.priority_top_msg[0].item.to.c_str(), this->isMySelfClientID(sessionItem.priority_top_msg[0].item.from_client_id)).c_str());
        }
    }
    
    /////// 功能接口 ////////////
    void CTNChatManager::setClientInfo(CTNClientInfo &clientInfo){
        TNMPLOG("setClientInfo clientId:" << clientInfo.clientId<<" appPath:"<<clientInfo.appPath);
        
//        if ((_clientInfo.clientId != "" && _clientInfo.clientId != clientInfo.clientId) || _clientInfo.clientId == "") {//新用户
//            for (int i = 0; i < _clientInfo.feedList.size(); ++i){
//                toonim::getChatDB()->getSessions(_clientInfo.feedList[i].c_str(), false);
//                toonim::getChatDB()->getSessions(_clientInfo.feedList[i].c_str(), true);
//            }
//        }
        
        //此处有多线程问题，@lll
        _clientInfo = clientInfo;
        this->printMyFeedIdList();
        
        toonim::initImDB(_clientInfo.clientId.c_str(), _clientInfo.appPath.c_str());
//        _dbGroup = toonim::initGroupChatDB(_clientInfo.clientId.c_str(), _clientInfo.appPath.c_str());
//        _dbSetting = toonim::initSettingsDB(_clientInfo.clientId.c_str(), _clientInfo.appPath.c_str());;
//
        this->loadOperateMessages();
    }
    
    void CTNChatManager::loadOperateMessages(){
        unique_lock<std::mutex> uniqueLock(_cacheOperateMutex);
        if (!_cacheOperateMsg.empty()){
            return;
        }
        
        vector<CTNMessageOperate> vctOperateMsgs = toonim::getChatDB()->getAllOperateMessages();
        vector<CTNMessageOperate>::iterator iter = vctOperateMsgs.begin();
        while (iter != vctOperateMsgs.end()){
            _cacheOperateMsg[iter->opMsgId] = *iter;
            iter ++;
        }
    }
    
    //////////////////////////////////////////////////
    bool CTNChatManager::isInvalid(int32_t type, Toon::MsgReq * req){
        if (req == nullptr) {
            TNMPLOG("req is nullptr!");
            return true;
        }
        
        if (req->msg_id.length() == 0 || req->from.length() == 0 || req->to.length() == 0 || req->content.size() == 0) {
            TNMPLOG("Message is empty, msgId:" << req->msg_id << " to:" << req->to << " from:" << req->from);
            
            return true;
        }
        
        string fromClientId = req->from_client_id;
        string toClientId = req->to_client_id;
        CTNIMMessageType imMessageType = (CTNIMMessageType)type;
        
        
        if (!(_clientInfo.clientId == fromClientId) && !(_clientInfo.clientId == toClientId)) {
            if (CTNIMMessageTypeBizNotice == imMessageType || CTNIMMessageTypeChat == imMessageType) {
                TNMPLOG("this message is not mine!");
                return true;
            }
        }
        
        if (type == CTNIMMessageTypeChat && !isMySelfFeed(req->from) && !isMySelfFeed(req->to)){
            TNMPLOG("Chat message is not mine! and from = " << req->from << " , to = " << req->to);
            
            return true;
        }
        
        
        return false;
    }
    
    CTNMessage CTNChatManager::msgReqToIMMessage(int32_t type, Toon::MsgReq * req){
        CTNMessage message;
        if (req == NULL || isInvalid(type, req)){
            return message;
        }
        
        if (this->checkMessageRepeat(req->msg_id)){
            TNMPLOG("checkMessageRepeat repeat:"<<req->msg_id);
            return message;
        }
        
        message.msgId = req->msg_id;
        message.seqId = req->seq_id;
        message.type = type;
        message.fromId = req->from;
        message.toId = req->to;
        message.pushInfo = req->pushinfo;
        message.timestamp = req->timestamp;
        message.priority = req->priority;
        message.fromClientId = req->from_client_id;
        message.toClientId = req->to_client_id;
        message.sessionId = toonim::generateSessionId(type, req->from, req->to, this->isMySelfClientID(req->from_client_id));

        if (message.fromClientId.length() > 0 && _clientInfo.clientId == message.fromClientId) {
            message.isMyself = CTNOwnerMyself;
        } else if (message.toClientId == _clientInfo.clientId){
            message.isMyself = CTNOwnerOther;
        } else {
            message.isMyself = CTNOwnerUnkown;
        }
        
        std::vector<std::string> arrToonType;
        
        for (int32_t i = 0; i < req->to_toon_type.size(); i++) {
            std::string toonType = req->to_toon_type[i];
            if (toonType.length() > 0){
                arrToonType.push_back(toonType);
            }
        }
        
        if (arrToonType.size() > 0) {
            message.toToonTypes = arrToonType;
        }
        //at feed
        
        message.sendStatus = CTNMessageSuccess;
        
        contentToJson(type, req->content, message);

        checkMessageFileStatus(message,CTNFileStatusNotDownload);

        checkMessageVoice(message);

        return message;
    }
    
    Toon::MsgReq * CTNChatManager::imMessageToMsgReq(int32_t type, CTNMessage& message){
        Toon::MsgReq *req = new Toon::MsgReq();
        
        req->msg_id = message.msgId;
        req->from = message.fromId;
        req->to = message.toId;
        req->timestamp = message.timestamp;
        req->priority = message.priority;
        req->flags = message.flags;
        req->to_client_id = message.toClientId;
        req->from_client_id = _clientInfo.clientId;
        req->seq_id = message.seqId;
        
        Toon::BizMsg bizChat;
        bizChat.catalogId =  message.catalogId;
        bizChat.contentType = (taf::Int32)message.contentType;
        std::string content = message.content;
        bizChat.content = content;
        
        if (message.senderName.length() > 0) {
            bizChat.senderName = message.senderName;
        }
        
        bizChat.atType = (int)message.atType;
        
#ifdef RAPIDJSONWRAPPER
        CTNJsonReader atFeeds(message.atFeeds);//测试通过 417-1
        
        for (int32_t i = 0; i < atFeeds.getSize(); ++i) {
            Toon::Feed feed;
            
            feed.feedId = atFeeds[i]["feedId"].getString();
            feed.userId = atFeeds[i]["userId"].getString();
            bizChat.atFeeds.push_back(feed);
        }
#else
        rapidjson::Document doc;
        doc.Parse<0>(message.atFeeds.c_str());
        
        rapidjson::Value &dataArray = doc;
        
        if (dataArray.IsArray())
        {
            for (rapidjson::SizeType i = 0; i < dataArray.Size(); i++)
            {
                Toon::Feed feed;
                
                const rapidjson::Value& feedId = dataArray[i]["feedId"];
                feed.feedId = feedId.GetString();
                const rapidjson::Value& userId = dataArray[i]["userId"];
                feed.userId = userId.GetString();
                bizChat.atFeeds.push_back(feed);
            }
        }
#endif
        taf::JceOutputStream<taf::BufferWriter> tos;
        bizChat.writeTo(tos);
        req->content = tos.getByteBuffer();
        if (message.toClientId.length() > 0
            && (message.type == TYPE_SINGLE_CHAT_MSGREQ || message.type == TYPE_MSG_SINGLE_OPERATE) ) {
            req->to_client_id = message.toClientId;
        }
        
        if (message.pushInfo.length() > 0) {
            req->pushinfo = message.pushInfo;
        }
        
        return req;
    }
    
    void CTNChatManager::contentToJson(int32_t type, vector<taf::Char> &vctContent,CTNMessage& imMessage)
    {
        if  (vctContent.size() == 0){
            return;
        }
        
        taf::JceInputStream<taf::BufferReader> is;
        
        is.setBuffer(vctContent.data(), vctContent.size());
        
        std::string json;
        switch (type) {
            case TYPE_NOTIFY_MSGREQ:
            case TYPE_SYNC_MSGREQ:
            case TYPE_GROUP_NOTIFY_REQ:
            case TYPE_SINGLE_CHAT_MSGREQ:
            case TYPE_GROUP_CHAT_MSGREQ:
            case TYPE_MOMENT_MSGREQ:
            {
                Toon::BizMsg bizMsg;
                try {
                    bizMsg.readFrom(is);
                } catch (...) {
                    TNMPLOG("bizMsg readFrom error:" << type);
                    json = vctContent.data();
                    break;
                }
//                TNMPLOG("bizMsg.expireTime :" << bizMsg.expireTime);
                imMessage.catalogId = bizMsg.catalogId;
                imMessage.subCatalogId = bizMsg.subCatalogId;
                imMessage.contentType = bizMsg.contentType;
                imMessage.expireTime = bizMsg.expireTime;
                imMessage.senderName = bizMsg.senderName.c_str();
                imMessage.atType = bizMsg.atType;
                if (bizMsg.bizNo.length() > 0) {
                    imMessage.bizNo = bizMsg.bizNo.c_str();
                }
                
#ifdef RAPIDJSONWRAPPER
                //测试通过 417-1
                CTNJsonArray feedArray;
                Toon::Feed feed;
                for (int32_t i = 0; i < bizMsg.atFeeds.size(); ++i) {
                    feed = bizMsg.atFeeds[i];
                    feedArray[i]["feedId"] = feed.feedId;
                    feedArray[i]["userId"] = feed.userId;
                }
                
                imMessage.atFeeds = feedArray.toString();
#else
                rapidjson::StringBuffer atFeeds;
                rapidjson::Writer<rapidjson::StringBuffer> feedWriter(atFeeds);
                feedWriter.StartArray();
                
                Toon::Feed feed;
                for (int32_t i = 0; i < bizMsg.atFeeds.size(); ++i) {
                    feed = bizMsg.atFeeds[i];
                    feedWriter.StartObject();
                    feedWriter.Key("feedId");
                    feedWriter.String(feed.feedId.c_str());
                    feedWriter.Key("userId");
                    feedWriter.String(feed.userId.c_str());
                    feedWriter.EndObject();
                }
                
                feedWriter.EndArray();
                
                imMessage.atFeeds = atFeeds.GetString();     
#endif
                
#ifdef RAPIDJSONWRAPPER
                CTNJsonWriter writer;//测试通过 417-1
                
                writer["catalogId"] = bizMsg.catalogId;
                writer["headFlag"] = bizMsg.headFlag;
                writer["finishFlag"] = bizMsg.finishFlag;
                writer["actionType"] = bizMsg.actionType;
                writer["showFlag"] = bizMsg.showFlag;
                writer["bubbleFlag"] = bizMsg.bubbleFlag;
                writer["subCatalogId"] = bizMsg.subCatalogId;
                writer["expireTime"] = bizMsg.expireTime;
                
                if (bizMsg.bizNo.length() > 0) {
                    writer["bizNo"] = bizMsg.bizNo;
                }
                
                if (bizMsg.subCatalog.length() > 0) {
                    writer["subCatalog"] = bizMsg.subCatalog;
                }
                if (bizMsg.headFeed.length() > 0) {
                    writer["headFeed"] = bizMsg.headFeed;
                }
                if (bizMsg.summary.length() > 0) {
                    writer["summary"] = bizMsg.summary;
                }
                
                json = writer.toString();
#else
                rapidjson::StringBuffer s;
                rapidjson::Writer<rapidjson::StringBuffer> writer(s);
                
                writer.StartObject();
                writer.Key("catalogId");
                writer.Int(bizMsg.catalogId);
                writer.Key("headFlag");
                writer.Int(bizMsg.headFlag);
                writer.Key("finishFlag");
                writer.Int(bizMsg.finishFlag);
                writer.Key("actionType");
                writer.Int(bizMsg.actionType);
                writer.Key("showFlag");
                writer.Int(bizMsg.showFlag);
                writer.Key("bubbleFlag");
                writer.Int(bizMsg.bubbleFlag);
                writer.Key("subCatalogId");
                writer.Int(bizMsg.subCatalogId);
                writer.Key("expireTime");
                writer.Int64(bizMsg.expireTime);
                
                if (bizMsg.bizNo.length() > 0) {
                    writer.Key("bizNo");
                    writer.String(bizMsg.bizNo.c_str());
                }
                
                if (bizMsg.subCatalog.length() > 0) {
                    writer.Key("subCatalog");
                    writer.String(bizMsg.subCatalog.c_str());
                }
                if (bizMsg.headFeed.length() > 0) {
                    writer.Key("headFeed");
                    writer.String(bizMsg.headFeed.c_str());
                }
                if (bizMsg.summary.length() > 0) {
                    writer.Key("summary");
                    writer.String(bizMsg.summary.c_str());
                }
                writer.EndObject();
                
                json = s.GetString();
#endif
                
                if (type == CTNIMMessageTypeBizNotice) {
                    //通知类消息可以打印消息详情，聊天消息没有意义都是默认值
                    TNMPLOG("the outside content json:" << json);
                }
                
                // 遗留点
                rapidjson::Document sDocument;
                sDocument.Parse<0>(json.c_str());
                
                try {
                    if (bizMsg.content.length() > 0) {
                        rapidjson::Document document;
                        document.Parse<0>(bizMsg.content.c_str());
                        
                        if (document.HasParseError() || !document.IsObject()) {
                            TNMPLOG("the bizMsg.content is not valid json string:" << bizMsg.content);
                            break;
                        }
                        
                        for (rapidjson::Value::MemberIterator itr = document.MemberBegin(); itr!=document.MemberEnd(); ++itr) {
                            
                            std::string key = "/";
                            key.append(itr->name.GetString());
                            switch (itr->value.GetType()) {
                                case rapidjson::kStringType:
                                    rapidjson::Pointer(key.c_str()).Set(sDocument, itr->value.GetString());
                                    break;
                                case rapidjson::kNumberType:
                                    if (itr->value.IsInt()) {
                                        rapidjson::Pointer(key.c_str()).Set(sDocument, itr->value.GetInt());
                                    }else if(itr->value.IsInt64()){
                                        rapidjson::Pointer(key.c_str()).Set(sDocument, itr->value.GetInt64());
                                    }else if(itr->value.IsFloat()){
                                        rapidjson::Pointer(key.c_str()).Set(sDocument, itr->value.GetFloat());
                                    }else if(itr->value.IsDouble()){
                                        rapidjson::Pointer(key.c_str()).Set(sDocument, itr->value.GetDouble());
                                    }else if(itr->value.IsUint()){
                                        rapidjson::Pointer(key.c_str()).Set(sDocument, itr->value.GetUint());
                                    }else if(itr->value.IsUint64()){
                                        rapidjson::Pointer(key.c_str()).Set(sDocument, itr->value.GetUint64());
                                    }
                                    break;
                                case rapidjson::kFalseType:
                                case rapidjson::kTrueType:
                                    rapidjson::Pointer(key.c_str()).Set(sDocument, itr->value.GetBool());
                                    break;
                                case rapidjson::kArrayType:
                                    rapidjson::Pointer(key.c_str()).Set(sDocument, itr->value.GetArray());
                                    break;
                                case rapidjson::kObjectType:
                                    rapidjson::Pointer(key.c_str()).Set(sDocument, itr->value.GetObject());
                                    break;
                                case rapidjson::kNullType:
                                {
                                    rapidjson::Value nullObject(rapidjson::kNullType);
                                    rapidjson::Pointer(key.c_str()).Set(sDocument, nullObject);
                                }
                                    break;
                                default:
                                    TNMPLOG("err type,name:" << itr->name.GetString() << ",type:" << itr->value.GetType() << ",content:" << bizMsg.content);
                                    break;
                            }
                        }
                        rapidjson::StringBuffer buffer;
                        rapidjson::Writer<rapidjson::StringBuffer> docWriter(buffer);
                        sDocument.Accept(docWriter);
                        json = buffer.GetString();
                    }
                } catch (...) {
                    json = json;
                    TNMPLOG("try catch log: analyzing inside content json failed");
                }
                
                break;
            }
            case TYPE_MSG_SINGLE_OPERATE:
            case TYPE_MSG_GROUP_OPERATE:
            {
                Toon::MsgOperate msgOperate;
                try {
                    msgOperate.readFrom(is);
                } catch (...) {
                    TNMPLOG("MsgOperate readFrom  error");
                    return;
                }
                imMessage.catalogId = msgOperate.catalogId;
                imMessage.contentType = CTNChatTypeRevoked;//操作消息默认为撤回消息，若有其他操作消息，该处根据catalogId判断进行赋值
                imMessage.status = CTNIMMessageDeleted;
                
                
#ifdef RAPIDJSONWRAPPER
                CTNJsonWriter writer;
                
                writer["catalogId"] = msgOperate.catalogId;
                
                if (msgOperate.operatorFeedId.length() > 0) {
                    writer["operatorFeedId"] = msgOperate.operatorFeedId;
                }
                
                if (msgOperate.operatorName.length() > 0) {
                    writer["operatorName"] = msgOperate.operatorName;
                }
                
                if (msgOperate.msgId.length() > 0) {
                    writer["msgId"] = msgOperate.msgId;
                }
                
                json = writer.toString();
#else
                rapidjson::StringBuffer s;
                rapidjson::Writer<rapidjson::StringBuffer> writer(s);
                
                writer.StartObject();
                writer.Key("catalogId");
                writer.Int(msgOperate.catalogId);
                
                if (msgOperate.operatorFeedId.length() > 0) {
                    writer.Key("operatorFeedId");
                    writer.String(msgOperate.operatorFeedId.c_str());
                }
                
                if (msgOperate.operatorName.length() > 0) {
                    writer.Key("operatorName");
                    writer.String(msgOperate.operatorName.c_str());
                }
                
                if (msgOperate.msgId.length() > 0) {
                    writer.Key("msgId");
                    writer.String(msgOperate.msgId.c_str());
                }
                
                writer.EndObject();
                
                json = s.GetString();
#endif
                
                
                break;
            }
            default:
            {
                json = vctContent.data();
                break;
            }
        }
        
        imMessage.content = json;
    }
    
    void CTNChatManager::createProcessThread () {
        try {
            if(_currProcess != nullptr) {
                TNMPLOG("createProcessThread Will logout process thread:" <<_currProcess->getId());
                _currProcess->logout(false);
                this->addToDiedArray(_currProcess);
                _currProcess = nullptr;
            }
            
            this->checkPorcessThread();
            
            _currProcess = new CTNProcessThread(this);
            if (_currProcess == nullptr){
                TNMPLOG("!!!!!!!_currProcess CAN'T NEW !!!!!!!!");
                return;
            }
            
            TNMPLOG("The current Process thread:"<< _currProcess->getId());
        } catch (exception e) {
            TNMPLOG("exception occur createTNMPThread :" << e.what());
        }
        TNMPLOG("createProcessThread ok:" << _currProcess->getId());
    }
    
    void CTNChatManager::addToDiedArray(CTNProcessThread* processThread){
        std::unique_lock<std::mutex> unilock(_diedArrayMutex);
        _diedArray.push_back(processThread);
    }
    
    void CTNChatManager::checkPorcessThread () {
        std::unique_lock<std::mutex> unilock(_diedArrayMutex);
        if (_diedArray.empty()){
            return;
        }
        
        TNMPLOG("checkPorcessThread:"<<_diedArray.size());
        for (int32_t i = _diedArray.size()-1; i >= 0; i--){
            CTNProcessThread* process = _diedArray.at(i);
            if (process == nullptr) {
                _diedArray.erase(_diedArray.begin()+i);
            }
            else if (process->isDied())
            {
                delete process;
                _diedArray.erase(_diedArray.begin()+i);
            }
            else{
                TNMPLOG("checkPorcessThread:"<<_diedArray.size()<<" thread:"<< process->getId());
                process->logout(false);
                process->stop();
            }
        }
    }
    
    CTNMessage  CTNChatManager::obtaionNoticeMessage(CTNMessage& message) {
        
#ifdef RAPIDJSONWRAPPER
        CTNJsonReader doc(message.content);
        
        if (strcmp(doc["bizNo"].getString().c_str(), "")) {
            message.msgId = doc["bizNo"].getString();
        }
#else
        rapidjson::Document jsonContent;
        jsonContent.Parse<0>(message.content.c_str());
        
        rapidjson::Value& bizNo = GetValueByPointerWithDefault(jsonContent, "/bizNo", "");
        
        if (strcmp(bizNo.GetString(), "")) {
            message.msgId = bizNo.GetString();
        }
#endif
        return message;
    }
    
    
    bool CTNChatManager::chatAndNoticeMessageIsValid(CTNMessage& message) {
        if (message.type != CTNIMMessageTypeChat
            && message.type != CTNIMMessageTypeGroupChat
            && message.type != CTNIMMessageTypeMsgGroupOperate
            && message.type != CTNIMMessageTypeMsgSingleOperate
            && message.type != CTNIMMessageTypeBizNotice
            && message.type != CTNIMMessageTypeGroupNotice) {
            return false;
        }
        return true;
    }
    
    CTNSession CTNChatManager::getSessionByMessage(CTNMessage& message, bool &isNewSession) {
        if ( message.isEmpty()) {
            TNMPLOG("getSessionByMessage:isRecved: error params");
            return CTNSession();
        }
        
        isNewSession = false;
        
        CTNSession session = toonim::getChatDB()->getSession(message.sessionId.c_str());
        // 更新留言
        if (!session.isValid()) {
            isNewSession = true;
            // 如果最后一条消息为操作消息 转换成单群聊消息
            if (message.type == CTNIMMessageTypeMsgSingleOperate) {
                session.type = CTNIMMessageTypeChat;
            }else if (message.type == CTNIMMessageTypeMsgGroupOperate) {
                session.type = CTNIMMessageTypeGroupChat;
            }else{
                session.type = message.type;
            }
            
            session.sessionId = message.sessionId;
            
            if (message.type == CTNIMMessageTypeChat || message.type == CTNIMMessageTypeMsgSingleOperate) {
                if (message.isMyself == CTNOwnerUnkown) {
                    //@todo 统一判断方向方法
                    if (isMySelfFeed(message.fromId)) {
                        message.isMyself = CTNOwnerMyself;
                    }
                    else{
                        message.isMyself = CTNOwnerOther;
                    }
                }
                
                if (message.isMyself == CTNOwnerMyself) {
                    session.topic = message.toId;
                    session.myFeedId = message.fromId;
                }else{
                    session.topic = message.fromId;
                    session.myFeedId = message.toId;
                }
            } else if (message.type == CTNIMMessageTypeBizNotice) {
                if (message.isMyself == CTNOwnerMyself) {
                    session.topic = message.toId;
                }
                else{
                    session.topic = message.fromId;
                }
            } else {
                session.topic = message.toId;
                session.myFeedId = "";
            }
            session.unreadCount = 0;
        }
        //session内容赋值不宜在此处
        
        //最后一条消息，缺省获取消息内容，群聊优先获取push内容，如果获取不到，再拼接
        string lastMsg = message.getAbstractText();
        session.lastMsgSendStatus = message.sendStatus;
        
        if (message.type == CTNIMMessageTypeGroupChat
            && lastMsg.length() > 0 && message.isMyself != CTNOwnerMyself && message.contentType != CTNChatTypeSystem && message.contentType != CTNChatTypeRevoked  && message.senderName.length() > 0) {
            lastMsg = message.senderName + ":" + lastMsg;
        }

        //只有正常需要显示的消息才需要更新lastMsg,lastMsgId,lastTime,sortTime
        if (message.status == CTNIMMessageNormal && session.lastMsgId != message.msgId) {
            session.lastMsg = lastMsg;
            session.lastMsgId = message.msgId;
            session.lastTime = message.timestamp;
            session.sortTime = message.timestamp;
        }
        
        return session;
    }
    
    bool CTNChatManager::isAtMeFromMsgIdWithMessage(CTNMessage& message) {
        //只有群聊才有@功能
        if (message.type != CTNIMMessageTypeGroupChat || message.status != CTNIMMessageNormal){
            return false;
        }
        
        //如果at消息被撤回，不标记
        if (message.contentType == CTNChatTypeRevoked){
            return false;
        }
        
        bool isAtMe = false;
        
        if (!isMySelfFeed(message.fromId)) {
            if (message.atType == CTNAtTypeAll) {
                isAtMe = true;
            } else if (message.atType == CTNAtTypeSome) {
                
#ifdef RAPIDJSONWRAPPER
                CTNJsonReader doc(message.atFeeds);//测试通过 417-1
                
                for (int i = 0; i < doc.getSize(); ++i) {
                    if (_clientInfo.clientId == doc[i]["userId"].getString()) {
                        isAtMe = true;
                    }
                }
#else
                rapidjson::Document doc;
                doc.Parse<0>(message.atFeeds.c_str());
                
                rapidjson::Value &dataArray = doc;
                
                if (dataArray.IsArray())
                {
                    for (rapidjson::SizeType i = 0; i < dataArray.Size(); i++)
                    {
                        if (_clientInfo.clientId == dataArray[i]["userId"].GetString()) {
                            isAtMe = true;
                        }
                    }
                }
#endif
            }
        }
        
        return isAtMe;
    }
    
    bool CTNChatManager::isFilterNotice(CTNMessage& message, string &broadcast) {
        if (message.type != CTNIMMessageTypeGroupNotice && message.type != CTNIMMessageTypeBizNotice) {
            return false;
        }
        
        std::unique_lock<std::mutex> unilock(_noticeFileterMutex);
        map<int, CTNNoticeFilter>::iterator iter = _noticeFilterMap.find(message.catalogId);
        if (iter == _noticeFilterMap.end()){
            return false;
        }
        
        broadcast = iter->second.broadcast;
        //没有subcatalogId 或者不过滤subCatalogId，只匹配catalogId
        if (iter->second.subCatalogIdSet.size() == 0){
            return true;
        }
        
        if (iter->second.subCatalogIdSet.find(message.subCatalogId) != iter->second.subCatalogIdSet.end()){
            return true;
        }
        
        return false;
    }
    
    
    void CTNChatManager::addSessionWithArray(std::vector<CTNSession>& sessionArray) {
        vector<CTNSession> newSessionArray;
        
        //此处循环 可以省略
        CTNSession session;
        for (int32_t i = 0; i < sessionArray.size(); ++i) {
            session = sessionArray[i];
            if (session.topic.length() == 0 || session.sessionId.length() == 0) {
                TNMPLOG("------------Error! add dialoginfo error:session key:" << session.sessionId << "topic:" << session.topic << "-------------");
                TNMPLOG("addSession: error params");
                continue;
            }
            
            if (session.type == CTNIMMessageTypeGroupChat) {
                CTNGroupInfo groupInfo = getGroupInfoWithTopic(session.topic);
                session.myFeedId = groupInfo.myFeedId;
            }
            newSessionArray.push_back(session);
        }
        
        toonim::getChatDB()->addSession(newSessionArray);
    }
    
    
   
    
    CTNOwner CTNChatManager::getMessageOwner(CTNMessage& message){
        CTNOwner owner = CTNOwnerUnkown;
        if (this->isMySelfClientID(message.fromClientId) && this->isMySelfFeed(message.fromId)){
            owner = CTNOwnerMyself;
        }
        else if (message.type == CTNIMMessageTypeGroupChat){
            owner = CTNOwnerOther;
        }
        else if (message.type == CTNIMMessageTypeChat && isMySelfClientID(message.toClientId)){
            owner = CTNOwnerOther;
        }
        
        return owner;
    }
    
    bool CTNChatManager::isMySelfFeed(std::string& feedId) {
        for (int32_t i = 0; i < _clientInfo.feedList.size(); i++){
            //            TNMPLOG("check myfeedid:"<<_clientInfo.feedList[i]<<" feedid:"<<feedId);
            if (feedId == _clientInfo.feedList[i]){
                return true;
            }
        }
        
        return false;
    }
    
    bool CTNChatManager::isMySelfFeed(std::set<std::string>& feedIdSet) {
        for (int32_t i = 0; i < _clientInfo.feedList.size(); ++i) {
            std::set<string>::iterator iterFind = feedIdSet.find(_clientInfo.feedList[i]);
            if (iterFind != feedIdSet.end()){
                return true;
            }
        }
        
        return false;
    }
    
    bool CTNChatManager::isMySelfClientID(const string& clientID) {
        
        if (_clientInfo.clientId == clientID) {
            return true;
        }
        
        return false;
    }
    
    void CTNChatManager::processMsgOperateAck(CTNMessage& message, bool success)
    {
        if  (message.isEmpty()){
            return;
        }
        
        if (_callback != nullptr){
            _callback->messageOperate(&message, success);
        }
    }


    int64_t getIdIntValueByTopic(string topic) {
        int64_t groupId;
        if(strncmp(topic.c_str(), "c_", 2) == 0 || strncmp(topic.c_str(), "g_", 2) == 0)
        {
            string strId = topic.substr(2, topic.length());
            sscanf(strId.c_str(),"%lld",&groupId);
            return  groupId;
        } else if (strncmp(topic.c_str(), "gc_", 3) == 0) {
            string strId = topic.substr(3, topic.length());
            sscanf(strId.c_str(),"%lld",&groupId);
            return  groupId;
        }
        sscanf(topic.c_str(),"%lld",&groupId);
        return  groupId;
    }
    
    void CTNChatManager::dissolveGroup(int64_t groupId){

        char buf[64] ={0};
        sprintf(buf,"gc_%lld", groupId);

        CTNSession session = toonim::getChatDB()->getSession(buf);
        if (session.topStatus == 1) {
            //取消置顶功能
            TNCBIZ_SETTINGS->setSessionSwitchTop(buf, "", CTNIMMessageTypeGroupChat, false, 0, nullptr, NULL);
        }
        
        toonim::getChatDB()->deleteSession(buf);
        toonim::getGroupChatDB()->deleteGroupInfo(groupId);
        toonim::getGroupChatDB()->deleteAllGroupMembers(groupId);

        std::ostringstream groupIdstr;
        toonim::ITnImDBSettings* settings = toonim::getSettingsDB();
        groupIdstr << "SESSION_TYPE_GROUPMEMBERVERSION_" << groupId;
        settings->deleteSessionSetting(groupIdstr.str().c_str(), toonim::SESSION_TYPE_GROUPMEMBERVERSION);

        if (_callback != nullptr){

#ifdef RAPIDJSONWRAPPER
            CTNJsonWriter writer;
            
            writer["isOut"] = 1;
            
            
            CTNJsonArray array(writer, "topics", false);

            array = buf;
            array.toString();
            
            std::string str = writer.toString();
            cout<<"dissolveGroup:"<<str;
            _callback->notificationCenter(TNC_GROUP_CHANGED, str.c_str());
#else
            rapidjson::StringBuffer buffer;
            rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
            writer.StartObject();
            writer.Key("isOut");
            writer.Int(1);
            writer.Key("topics");
            writer.StartArray();
            writer.String(buf);
            writer.EndArray();
            writer.EndObject();
            
            cout<<"dissolveGroup:"<<buffer.GetString();
            _callback->notificationCenter(TNC_GROUP_CHANGED, buffer.GetString());
#endif
            _callback->notificationCenter(TNC_UNREAD, "");
        }
    }
    
    void CTNChatManager::reqSyncSessionStatus(const char* sessionId) {
        if (sessionId == NULL) {
            vector<CTNSession> vecSession = toonim::getChatDB()->getSessions(nullptr, true);
            vector<CTNSession> updateSessions;
            for (int i = 0; i < vecSession.size(); ++i) {
                CTNSession session = vecSession[i];
                if (session.unreadCount > 0) {
                    int64_t maxSeqId = toonim::getChatDB()->getMaxSeqAllMessage(session.sessionId.c_str(), 2);
                    CTNSessionName sessionName;
                    
                    if (session.type == CTNIMMessageTypeChat || session.type == CTNIMMessageTypeGroupChat || session.type == CTNIMMessageTypeMsgSingleOperate || session.type == CTNIMMessageTypeMsgGroupOperate) {
                        sessionName.from = session.myFeedId;
                        sessionName.to = session.topic;
                        sessionName.type = session.type;
                    }else{
                        sessionName.to = "";
                        sessionName.from = session.sessionId;
                        sessionName.type = session.type;
                    }
                    
                    if (_currProcess == nullptr) {
                        TNMPLOG("reqSync network is not ready!");
                        return;
                    }
                    
                    Toon::SyncSessionStatusReq req;
                    req.session_name.type = sessionName.type;
                    req.read_seq_id = maxSeqId;
                    req.apns_unreadnum = 0;
                    if (sessionName.from.length() > 0){
                        req.session_name.from = sessionName.from ;
                    }
                    if (sessionName.to.length() > 0){
                        req.session_name.to = sessionName.to ;
                    }
                    _currProcess->reqSyncSessionStatus(req);
                }
            }
            
            toonim::getChatDB()->clearAllUnreadCount();
            //清除所有未读数时需要清除重要消息表
            toonim::getChatDB()->deleteAllImportantMessage(CTNIMMessageTypeAt);
            toonim::getChatDB()->deleteAllImportantMessage(CTNIMMessageTypeFollow);
            
            if (_callback != nullptr) {
                _callback->notificationCenter(TNC_UNREAD, "");
            }
            return;
        } else if(sessionId[0] != '\0') {
            toonim::getChatDB()->markSessionRead(sessionId);
            CTNSession session = toonim::getChatDB()->getSession(sessionId);
            
            //标记为已读时需要判断该会话是否为重要消息，需要清除重要消息会话中的对应消息
            this->deleteImportantMessage(session);
            int64_t maxSeqId = toonim::getChatDB()->getMaxSeqAllMessage(sessionId, 2);
            CTNSessionName sessionName;
            
            if (session.type == CTNIMMessageTypeChat || session.type == CTNIMMessageTypeGroupChat || session.type == CTNIMMessageTypeMsgSingleOperate || session.type == CTNIMMessageTypeMsgGroupOperate) {
                sessionName.from = session.myFeedId;
                sessionName.to = session.topic;
                sessionName.type = session.type;
            }else{
                sessionName.to = session.sessionId;
                sessionName.from = session.sessionId;
                sessionName.type = session.type;
            }
            
            if (_currProcess == nullptr) {
                TNMPLOG("reqSync network is not ready!");
                return;
            }
            Toon::SyncSessionStatusReq req;
            req.session_name.type = sessionName.type;
            req.read_seq_id = maxSeqId;
            if (sessionName.from.length() > 0){
                req.session_name.from = sessionName.from ;
            }
            if (sessionName.to.length() > 0){
                req.session_name.to = sessionName.to ;
            }
            
            int unreadCount = toonim::getChatDB()->getUnreadCount(nullptr, nullptr);
            if (unreadCount > 0){
                req.apns_unreadnum = unreadCount;
            }
            else {
                req.apns_unreadnum = 0;
            }
            
            _currProcess->reqSyncSessionStatus(req);
            session.readSeqId = maxSeqId;
            if (_callback != nullptr) {
                std::string jsonStr = this->genSessionIdToJson(session.sessionId);
                _callback->notificationCenter(TNC_UNREAD, jsonStr.c_str());
            }
        }
    }
    
    //标记会话为已读时，需要判断是否要删除重要消息
    void CTNChatManager::deleteImportantMessage(CTNSession session)
    {
        if (session.type != CTNIMMessageTypeGroupChat) {
            return;
        }
        //at开关状态判断
        if (CTNDBSetting().instance()->getAtMessaeSwitch()) {
            toonim::getChatDB()->deleteImportantMessageBySessionId(CTNIMMessageTypeAt, session.sessionId.c_str());
        }
        
        //关注的人
        if (toonim::getSettingsDB()->getMyFollowFeedList().size() > 0) {
            toonim::getChatDB()->deleteImportantMessageBySessionId(CTNIMMessageTypeFollow, session.sessionId.c_str());
        }
    }

    void CTNChatManager::clientReport(int32_t type, const char* content)
    {
        if (_currProcess == nullptr){
            TNMPLOG("clientReport _currProcess is null!");
            return ;
        }
        
        Toon::ClientReport report;
        report.type = type;
        if (content != nullptr && strlen(content) > 0){
            report.content = content;
        }
        
        _currProcess->clientReport(report);
    }
    
    void CTNChatManager::subOrganize(vector<string> &vctOrgId){
        if (_currProcess == nullptr || vctOrgId.empty()){
            TNMPLOG("subOrganize vctOrgId or _currProcess is null!");
            return ;
        }
        
        Toon::SubOrganizeReq req;
        req.vecOrganizeIDs = vctOrgId;
        _currProcess->subOrganizeReq(req);
    }
    
    
    std::string CTNChatManager::genRevokeMessageContent(toonim::CTNMessage& message, const std::string& operateName)
    {
        std::string content = "";
        std::string title = "";
        std::ostringstream s;
        
        if (message.fromClientId == _clientInfo.clientId || isMySelfFeed(message.fromId)) {
            title = "你撤回了一条消息";
        }
        else {
            if (operateName.length() > 0) {
                s << operateName << "撤回了一条消息";
            } else {
                s << "对方撤回了一条消息";
            }
            title = s.str();
        }
        
#ifdef RAPIDJSONWRAPPER
        CTNJsonWriter writer;
        
        writer["text"] = title;
        
        content = writer.toString();
#else
        rapidjson::StringBuffer jsonS;
        rapidjson::Writer<rapidjson::StringBuffer> writer(jsonS);
        writer.StartObject();
        writer.Key("text");
        writer.String(title.c_str());
        writer.EndObject();
        
        content = jsonS.GetString();
#endif
        return content;
    }
    
//    void CTNChatManager::updateSessionWithArray(vector<CTNSession>& sessionArray) {
//        toonim::getChatDB()->updateSession(sessionArray);
//        //发送通知
//        //    [[NSNotificationCenter defaultCenter] postNotificationName:TNC_UNREAD object:nil userInfo:nil];
//    }
    
//    bool CTNChatManager::messageIsValid(CTNMessage& message) {
//        if ( (message.type != CTNIMMessageTypeChat//message == nil ||
//              && message.type != CTNIMMessageTypeGroupChat
//              && message.type != CTNIMMessageTypeMsgGroupOperate
//              && message.type != CTNIMMessageTypeMsgSingleOperate)) {
//            return false;
//        }
//        
//        return true;
//    }
    
    void CTNChatManager::processMessageAck(CTNMessage& message, int32_t errorCode) {
        //@todo 私信或许有错误
        CTNMessageSendStatus sendStatus;
        CTNMessageFileStatus fileStatus;
        if (errorCode == 0) {
            sendStatus = CTNMessageSuccess;
            fileStatus = CTNFileStatusSended;
        } else {
            sendStatus = CTNMessageFailed;
            fileStatus = CTNFileStatusSendFailed;
            TNMPLOG("sendStatus_failed");
        }
        TNMPLOG("processMessageAck sendStatus:" << sendStatus<<" msgId:"<<message.msgId);
        
        if (!message.isEmpty()) {
            //数据库操作
            message.sendStatus = sendStatus;

            checkMessageFileStatus(message,fileStatus);
            toonim::getChatDB()->updateMessage(message);
        }
        
        if (message.status != CTNIMMessageDeleted) {
            bool isNewSession = false;
            CTNSession session = getSessionByMessage(message, isNewSession);
            session.lastMsgId = message.msgId;
            
            session.lastMsgSendStatus = message.sendStatus;
            TNMPLOG("sendStatus = " << message.sendStatus);
            TNMPLOG("messageSessionId = " << session.sessionId << ", messageID = " << message.msgId);
            
            //不需要调用unread，直接调用chatDB的方法
            vector<CTNSession> vecSession;
            vecSession.push_back(session);
            toonim::getChatDB()->updateSession(vecSession);
            if (_callback != nullptr) {
                std::string jsonStr = this->genSessionIdToJson(session.sessionId);
                _callback->notificationCenter(TNC_SESSION_CHANGE, jsonStr.c_str());
            }
        }
        
        if (_callback != nullptr){
            _callback->msgAck(message.sessionId.c_str(), message.msgId.c_str(), message.seqId, errorCode);
        }
        else {
            TNMPLOG("_callback is null msgAck");
        }
    }

    void CTNChatManager::checkMessageVoice(CTNMessage& message){

        if (message.contentType != CTNChatTypeVoice) {
            return;
        }


        if (this->_callback != nullptr){
            
#ifdef RAPIDJSONWRAPPER
            rapidjson::Document fileBody;
            fileBody.Parse(message.content.c_str());
            
            CTNJsonReader doc(message.content);
            
            
            CTNJsonWriter writer;
            
            writer["msgId"] = message.msgId;
            writer["url"] = doc["url"].getString();
            
            std::string buffer = writer.toString();
            
            cout<<"checkMessageVoice:"<<buffer;
            this->_callback->notificationCenter(TNC_DOWNLOAD_VOICE, buffer.c_str());
#else
            rapidjson::Document fileBody;
            fileBody.Parse(message.content.c_str());
            
            rapidjson::Value& url = fileBody["url"];
            
            rapidjson::StringBuffer buffer;
            rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
            writer.StartObject();
            writer.Key("msgId");
            writer.String(message.msgId.c_str());
            writer.Key("url");
            writer.String(url.GetString());
            writer.EndObject();
            
            cout<<"checkMessageVoice:"<<buffer.GetString();
            this->_callback->notificationCenter(TNC_DOWNLOAD_VOICE, buffer.GetString());
#endif

            
        }

    }

    void CTNChatManager::checkMessageFileStatus(CTNMessage& message,CTNMessageFileStatus status){

        if (message.contentType != CTNChatTypeFiles) {
            return;
        }

#ifdef RAPIDJSONWRAPPER
        //未封装
        rapidjson::Document fileBody;
        fileBody.Parse(message.content.c_str());
        
        rapidjson::Value& fileStatus = fileBody["status"];
        if (fileStatus.IsNull()) {
            fileBody.AddMember("status", status, fileBody.GetAllocator());
        }else{
            fileStatus.SetInt(status);
        }
        
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        fileBody.Accept(writer);
        rapidjson::Value& fileFormat = fileBody["format"];
        
        message.fileFormat = fileFormat.GetString();
        message.content = buffer.GetString();
#else
        rapidjson::Document fileBody;
        fileBody.Parse(message.content.c_str());
        
        rapidjson::Value& fileStatus = fileBody["status"];
        if (fileStatus.IsNull()) {
            fileBody.AddMember("status", status, fileBody.GetAllocator());
        }else{
            fileStatus.SetInt(status);
        }
        
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        fileBody.Accept(writer);
        rapidjson::Value& fileFormat = fileBody["format"];
        
        message.fileFormat = fileFormat.GetString();
        message.content = buffer.GetString();
#endif
        
//        TNMPLOG("buffer.GetString():"<<buffer.GetString())
    }

    bool CTNChatManager::checkMessageRepeat(const string& msgId) {
        if (msgId.length() == 0) {
            TNMPLOG("checkMessageRepeat: error params!");
            return true;
        }
        
        vector<string>::iterator iter = find(_arrRecvMsgId.begin(),_arrRecvMsgId.end(),msgId);
        
        if (iter!=_arrRecvMsgId.end())
        {
//            TNMPLOG("repeat message give up it:"<<msgId<<" find:"<<*iter);//LOG_LEVEL_NOTICE
            return true;
            
        }
        
        if (_arrRecvMsgId.size() > 100) {
            _arrRecvMsgId.pop_back();
        }
        
        //add to first position
        _arrRecvMsgId.insert(_arrRecvMsgId.begin(), msgId);
//        _arrRecvMsgId.push_back(msgId);
        
        return false;
    }
    

    //增量更新的方法
    void CTNChatManager::syncGroupMember(int64_t groupId) {
        if (groupId <= 0) {
            TNMPLOG("syncGroupMember:succeed: error params");
            return;
        }
        
        auto lambda = [this,groupId](int32_t code, const char *message, void *userData)->void{
            if (this->_callback != nullptr){
                if (message != nullptr) {
                    char buf[64] ={0};
                    sprintf(buf,"gc_%lld", groupId);
                    
#ifdef RAPIDJSONWRAPPER
                    CTNJsonWriter writer;//测试通过 417-1
                    
                    CTNJsonArray array(writer, "topics", false);
                    
                    array = buf;
                    array.toString();
                    
                    CTNJsonArray arrayMsg(writer, "message", false);
                    
                    arrayMsg = message;
                    arrayMsg.toString();
                    
                    std::string strMsg = message?message:"";
                    
                    CTNJsonReader doc(strMsg);
                    
                    CTNJsonValue arrayList = doc["data"]["memberList"];
                    
                    if (arrayList.getArraySize() > 0) {
                        std::string strGroupMem = writer.toString();
                        cout<<"syncGroupMember:"<<strGroupMem;
                        this->_callback->notificationCenter(TNC_GROUP_MEMBER_CHANGED, strGroupMem.c_str());
                    }
#else
                    rapidjson::StringBuffer buffer;
                    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
                    writer.StartObject();
                    
                    writer.Key("topics");
                    writer.StartArray();
                    writer.String(buf);
                    writer.EndArray();
                    
                    writer.Key("message");
                    writer.StartArray();
                    writer.String(message);
                    writer.EndArray();
                    
                    writer.EndObject();
                    
                    rapidjson::Document doc;
                    doc.Parse<0>(message);
                    rapidjson::Value &messageList = doc;
                    if (messageList.IsObject() && messageList.HasMember("data")) {
                        rapidjson::Value data = (messageList)["data"].GetObject();
                        if (data.IsObject() && data.HasMember("memberList") && data["memberList"].IsArray()) {
                            rapidjson::Document::Array memberList = data["memberList"].GetArray();
                            if (memberList.Size() > 0) {
                                cout<<"syncGroupMember:"<<buffer.GetString();
                                this->_callback->notificationCenter(TNC_GROUP_MEMBER_CHANGED, buffer.GetString());
                            }
                        }
                    }
#endif

                    
                }
            }
            
        };
//        string keyStr = "SESSION_TYPE_GROUPMEMBERVERSION_" + CTNDBUtils::stringFromInt64(groupId);
//        string version = getSettingsDB()->getSessionSetting(keyStr.c_str(), SESSION_TYPE_GROUPMEMBERVERSION).value;
//        if (version.length()  == 0) {
//            version = "0";
//        }
        char buf[64] ={0};
        sprintf(buf,"%lld", groupId);

        TNCBIZ_GROUPCHAT->obtainMembersByGroupChatId(buf, lambda, NULL);
   }
    
    void CTNChatManager::syncMyGroupFromServerSucceed()
    {

        auto lambda = [this](int32_t code, const char *message, void *userData)->void{
            TNMPLOG("synchronize update group chat finished");
            if (this->_callback != nullptr){

                cout<<"MESSAGE:"<<message<<endl;
                
                
#ifdef RAPIDJSONWRAPPER
                std::string strMsg = message?message:"";//测试通过 417-1
                CTNJsonReader doc(strMsg);
                
                CTNJsonWriter writer;
                
                CTNJsonValue topicArray = doc["data"]["groupChatList"];
                
                if (topicArray.getArraySize() > 0) {
                    CTNJsonArray topicArr(writer, "topics", false);
                    
                    for (int i = 0; i < topicArray.getArraySize(); ++i) {
                        std::string syncTopic = topicArray[i]["topic"].getString();
                        int32_t status = topicArray[i]["status"].getInt32();
                        
                        if (status == 1) {
                            topicArr = syncTopic;
                        }
                    }
                    
                    topicArr.toString();
                }
                
                std::string buffer = writer.toString();
                
                cout<<"syncMyGroupFromServerSucceed:"<<buffer;
                this->_callback->notificationCenter(TNC_GROUP_CHANGED, buffer.c_str());
#else
                rapidjson::Document jsonContent;
                jsonContent.Parse<0>(message);
                
                
                rapidjson::StringBuffer buffer;
                rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
                writer.StartObject();
                
                rapidjson::Value& topic = GetValueByPointerWithDefault(jsonContent, "/data/groupChatList", "");
                if (topic.IsArray()) {
                    writer.Key("topics");
                    writer.StartArray();
                    for (int i = 0; i < topic.Size(); ++i)
                    {
                        rapidjson::Value & value = topic[i];
                        if (value.HasMember("topic") && value["topic"].IsString()) {
                            std::string syncTopic = value["topic"].GetString();
                            int32_t status = value["status"].GetInt();
                            cout<<"syncTopic:"<<syncTopic;
                            if (status == 1) {
                                writer.String(syncTopic.c_str());
                            }
                        }
                    }
                    writer.EndArray();
                }
                
                writer.EndObject();
                
                cout<<"syncMyGroupFromServerSucceed:"<<buffer.GetString();
                this->_callback->notificationCenter(TNC_GROUP_CHANGED, buffer.GetString());
#endif
                
            }

        };

        TNCBIZ_GROUPCHAT->obtainAllGroupChat(_clientInfo.clientId.c_str() , lambda, NULL);
        
//        TNMPLOG("synchronize update group chat  timestamp:" << version);
        //发送通知 inputDict
        //群组逻辑为http接口该模块不负责群组功能
    }
    
    
    CTNGroupInfo CTNChatManager::getGroupInfoWithTopic(const string& topic) {
        if (topic.length() <= 0)
        {
            TNMPLOG("getGroupInfoWithTopic: error params");
            return CTNGroupInfo();
        }
        //通过群ID查询群组信息，session的topic字段去掉首部的"gc_"转换为整型数字即为群ID
        string strGroupId = topic.substr(3, topic.length());
        int64_t groupId;
        groupId = atoll(strGroupId.c_str());
        
        CTNGroupInfo groupInfo = toonim::getGroupChatDB()->getGroupInfo(groupId);
        return groupInfo;
    }
    
    int32_t CTNChatManager::revokeMessage(const char* sessionId, const char* msgId, const char* operatorFeedId, const char* operatorName) {
        if (msgId == NULL || strlen(msgId) == 0
            || operatorFeedId == NULL || strlen(operatorFeedId) == 0
            || sessionId == NULL || strlen(sessionId) == 0
            || operatorName == NULL || strlen(operatorName) == 0) {
            TNMPLOG("revokeMessage prarm is error");
            return -1;
        } else {
            TNMPLOG("revokeMessage failure msgId=" << msgId << ", operatorFeedId=" << operatorFeedId << ", operatorName=" << operatorName);
        }
        
        if (_currProcess == nullptr){
            TNMPLOG("_currProcess is nullptr!");
            return  -1;
        }
        
        toonim::CTNMessage message = toonim::getChatDB()->getMessage(sessionId, msgId);
        if (message.isEmpty()) {
            return -1;
        }
        
        if (message.type == CTNIMMessageTypeChat) {
            message.type = CTNIMMessageTypeMsgSingleOperate;
        } else {
            message.type = CTNIMMessageTypeMsgGroupOperate;
        }
        message.msgId = toonim::generateMsgId();
        message.contentType = CTNChatTypeRevoked;
        message.catalogId = CTNIMMessageRevoked;
        message.status = CTNIMMessageRevoked;
        string content;
        
        
#ifdef RAPIDJSONWRAPPER
        CTNJsonWriter writer;
        
        writer["msgId"] = msgId;
        writer["catalogId"] = CTNIMMessageRevoked;
        writer["operatorFeedId"] = operatorFeedId;
        writer["operatorName"] = operatorName;
        
        content = writer.toString();
#else
        rapidjson::StringBuffer jsonS;
        rapidjson::Writer<rapidjson::StringBuffer> writer(jsonS);
        writer.StartObject();
        writer.Key("msgId");
        writer.String(msgId);
        writer.Key("catalogId");
        writer.Int(CTNIMMessageRevoked);
        writer.Key("operatorFeedId");
        writer.String(operatorFeedId);
        writer.Key("operatorName");
        writer.String(operatorName);
        writer.EndObject();
        
        content = jsonS.GetString();
#endif
        
        message.content = content;
        message.status = ::CTNIMMessageRevoked;
        
        //save to message to db
        toonim::getChatDB()->addMessage(message);
        
        
        //send to server
        Toon::MsgReq *req = new Toon::MsgReq();
        req->msg_id = message.msgId;
        req->from = message.fromId;
        req->to = message.toId;
        req->timestamp = message.timestamp;
        req->from_client_id = _clientInfo.clientId;
        req->to_client_id = message.toClientId;
        req->priority = 1;
        
        Toon::MsgOperate msgOperate;
        msgOperate.catalogId = CTNIMMessageRevoked;
        msgOperate.msgId = msgId;
        
        if (operatorFeedId != NULL && strlen(operatorFeedId) > 0){
            msgOperate.operatorFeedId = operatorFeedId;
        }
        
        if (operatorName != NULL && strlen(operatorName) > 0){
            msgOperate.operatorName = operatorName;
        }
        
        taf::JceOutputStream<taf::BufferWriter> tos;
        msgOperate.writeTo(tos);
        req->content = tos.getByteBuffer();
        
        if (message.toClientId.length() > 0
            && (message.type == CTNIMMessageTypeChat || message.type == CTNIMMessageTypeMsgSingleOperate) ) {
            req->to_client_id = message.toClientId;
        }
        
        _currProcess->sendMsgReq(message.type, req, true);
        
        return 0;
    }
    
    void CTNChatManager::pullOffMessage(OffMsgMgr& offMsgInfo, int32_t requestNum, int32_t priority) {
        TNMPLOG("pullOffMessage=====sessiosnId:" << offMsgInfo.faultMsg.sessionId << " minSeqId:" << offMsgInfo.minSeqId << " maxSeqId:" << offMsgInfo.maxSeqId << " count:" << offMsgInfo.count << "  requestNum:" << requestNum << " priority:" << offMsgInfo.priority << " faultMsg.seqId:" << offMsgInfo.faultMsg.seqId << " reqId:" << offMsgInfo.reqId);
        if (_currProcess == nullptr) {
            TNMPLOG("reqSync network is not ready!");
            return;
        }
        
        if (requestNum <= 0) {
            TNMPLOG("need't to pull offmessage,give up.");
            return;
        }
        
        Toon::PullOffMsgReq req;
        
        if (offMsgInfo.type == CTNIMMessageTypeChat || offMsgInfo.type == CTNIMMessageTypeGroupChat || offMsgInfo.type == CTNIMMessageTypeMsgSingleOperate || offMsgInfo.type == CTNIMMessageTypeMsgGroupOperate || offMsgInfo.type == CTNIMMessageTypeGroupNotice) {
            // 单群聊和 群通知 fromId （群 可以不传）、 toId 和type
            req.session_name.type = offMsgInfo.type;
            req.session_name.from = offMsgInfo.from;
            req.session_name.to = offMsgInfo.to;
        }else if (offMsgInfo.type == CTNIMMessageTypeBizNotice) {// 通知
            req.session_name.type = offMsgInfo.type;
            req.session_name.from = offMsgInfo.faultMsg.sessionId;
            req.session_name.to = "";
            
        } else if (offMsgInfo.type== CTNIMMessageTypeSync){
            req.session_name.type = offMsgInfo.type;
        } else {
            TNMPLOG("pullOffMessage:error unrecognize type:" << offMsgInfo.type);//level:LOG_LEVEL_NOTICE
            return;
        }
        
        req.up_seq_id = offMsgInfo.minSeqId + 1;//本地消息已经存在，不需要再请求改seqID了
        req.down_seq_id = offMsgInfo.maxSeqId - 1;//热会话已经返回该消息，也不必请求了，否则重复消息无法入口要么就去重
        req.limit_count = requestNum;
        req.priority = offMsgInfo.priority;
//        req.timestamp = offMsgInfo.timestamp;
        req.req_id = offMsgInfo.reqId;
        _currProcess->reqPullOffMsg(req);
    }
    
   
    bool CTNChatManager::messageIsForbidden(CTNMessage& message) {
        if (message.isEmpty()){
            TNMPLOG("message is emtpy will give up:"<<message.msgId);
            return true;
        }
        
        //找不到toontype ，不是发给自己的消息丢体掉
        if (message.toToonTypes.size() > 0) {
            vector<string>::iterator iter = find(message.toToonTypes.begin(), message.toToonTypes.end(), CTNDBUtils::stringFromInt32(_clientInfo.toonType));
            if (iter == message.toToonTypes.end())
            {
                TNMPLOG("messageIsForbidden curr ToonType:<"<<_toonType << " msgId:" << message.msgId<<" toTypes:"<<message.getToToonTypeString());
                return true;
            }
        }
        
        return false;
    }
    
    std::string CTNChatManager::genSessionIdToJson(std::string &sessionId) {
        
#ifdef RAPIDJSONWRAPPER
        
        CTNJsonWriter writer;//测试通过 417-1
        
        writer["sessionId"] = sessionId;
        
        return writer.toString();
#else
        rapidjson::StringBuffer buffer;
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
        writer.StartObject();
        writer.Key("sessionId");
        writer.String(sessionId.c_str());
        writer.EndObject();
        
        return buffer.GetString();
#endif
    }



    ITnIMLog* getLogInstance(){
        return CTNLog::instance();
    }
    CTNLog* CTNLog::_instance = nullptr;
    
    CTNLog* CTNLog::instance(){
        if (_instance == nullptr){
            _instance = new CTNLog();
        }
        
        return _instance;
    }
    
    const char* CTNLog::getLogFileName(){
        
        std::string fileName = CLog::instance()->getFileName();
        return strdup(fileName.c_str());;
    }
    
    void CTNLog::writeLog(const char* logs)
    {
        if (logs == nullptr || strlen(logs) == 0){
            return;
        }
        
        TNMPLOG(logs);
    }
}






