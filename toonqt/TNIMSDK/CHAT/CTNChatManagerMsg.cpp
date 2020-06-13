//
//  CTNChatManagerMsg.cpp
//  tnimsdk
//
//  Created by lanhy on 2017/11/15.
//  Copyright © 2017年 syswin. All rights reserved.
//

#include "CTNChatManager.hpp"
#include "CTNDBUtils.hpp"
#include "pointer.h"
#include "document.h"
#include "CTNDBSettings.hpp"
#include "CTNBaseBean.h"
#include "CTNDBChat.hpp"

void CTNChatManager::processRecvOnlineMessage(CTNMessage& message){
    if (message.isEmpty()){
        TNMPLOG("processRecvOnlineMessage MESSAGE IS MEPTY!"<<message.msgId);
        return;
    }
    
    if (messageIsForbidden(message)) {
        return;
    }
    TNC_CHECK_RET(toonim::getChatDB(), void(0));
    
    try {
        //判断消息覆盖问题是否需要计数，默认计数，为false时不计数
        bool isAddUnreadCount = true;
        switch (message.type) {
            case CTNIMMessageTypeChat:{
                this->processMessageChat(message);
                toonim::getChatDB()->addMessage(message);
                break;
            }
            case CTNIMMessageTypeGroupChat:
            {
                set<int64_t> groupIdSet;
                if (this->processMessageGroupChat(message, groupIdSet)){
                    this->syncMyGroupFromServerSucceed();
                }
                
                if (!groupIdSet.empty()){
                     this->syncGroupMember(*groupIdSet.begin());
                }
                
                toonim::getChatDB()->addMessage(message);
                //处理关注的人消息
                this->processFollowMessage(message);
                break;
            }
            case CTNIMMessageTypeBizNotice:
            case CTNIMMessageTypeGroupNotice:
                isAddUnreadCount = this->processMessageNotice(message, true);
                toonim::getChatDB()->addMessage(message);
                
                break;
            case CTNIMMessageTypeMsgSingleOperate:
            case CTNIMMessageTypeMsgGroupOperate:
            {
                CTNMessage srcMessage = this->processMessageOperate(message);
                toonim::getChatDB()->addMessage(message);
         
                this->processMsgOperateAck(srcMessage, true);
                return;
            }
             case CTNIMMessageTypeSync:
                this->processMessageSync(message, true);
                toonim::getChatDB()->addMessage(message);
                return;
            default:
                TNMPLOG("type is error:" << message.type);
                return;
        }
        
        if (message.status != CTNIMMessageNormal) {
            return;
        }
        
        bool isNewSession = false;
        CTNSession session = getSessionByMessage(message, isNewSession);
        
        //收到自己消息，说明自己在另外一端正在登陆发送消息，未读数必然为0,同时消掉@提示
        if (message.isMyself == CTNOwnerMyself) {
            session.unreadCount = 0;
            session.atMeMsgId = "";
        }
        else if (message.isMyself == CTNOwnerOther && isAddUnreadCount) {
            session.unreadCount++;
        }
        
        //消息都已读不处理@消息，
        if (session.unreadCount > 0 && isAtMeFromMsgIdWithMessage(message)){
            session.atMeMsgId = message.msgId;
            //只有当该at消息未读时才需要存储at消息表
            this->processAtMeMessage(message);
        }
        
        vector<CTNSession> sessionArray;
        sessionArray.push_back(session);
        if (isNewSession){
            this->addSessionWithArray(sessionArray);//notifyRecvMessage 方法中的unread删除，此处可以调用
        }
        else{
            toonim::getChatDB()->updateSession(sessionArray);
        }
        
        if (_callback != nullptr){
            //在线消息回调，发送recv通知
            _callback->msgRecv(&message);
            //发送未读数变化通知
            std::string jsonStr = this->genSessionIdToJson(message.sessionId);
            _callback->notificationCenter(TNC_UNREAD, jsonStr.c_str());
        }
    } catch (...) {
        //                TNIM_INFO(([NSString stringWithFormat:@"exception occur registerCallbackServer:%@", exception.description]));
        TNMPLOG("exception occur processRecvOnlineMessage:");
    }
    
}


//处理热会话，不区分优先级，add by lanhuaiyu
//1.消息处理，2，会话处理，3，断层处理
void CTNChatManager::processHotSessionResp(vector<Toon::HotSessionItem> &vctSession){
    //由于安卓不能主动刷新问题，不管是否有热会话消息都要发送热会话回调
//    if (vctSession.size() == 0) {
//        TNMPLOG("processHotSessionResp vctSession isEmpty!");
//        return;
//    }
    
    vector<CTNSession> sessionArray;
    vector<CTNMessage> vctSaveMessage;
    bool needSyncGroup = false;
    set<int64_t> groupIdSet;
    set<CTNOffMessageResult> sessionSet;
    //判断是否有未读数变化
    bool isUnreadChange = false;
    
    for (int32_t i = 0; i < vctSession.size(); ++i) {
        
        Toon::HotSessionItem sessionItem = vctSession[i];
        
        int64_t maxSeqId = 0;
        vector<CTNMessage> vctMessage;
        //转换消息，顺便找出最大maxSeqId
        this->transOffmsgs(sessionItem.priority_top_msg, vctMessage, maxSeqId);
        this->transOffmsgs(sessionItem.normal_top_msg, vctMessage, maxSeqId);
        
        if (vctMessage.size() == 0){
            CTNSession tempSession;
            getLocalSessionBySessionItem(sessionItem, tempSession);
            
            if (tempSession.isValid() && tempSession.readSeqId < sessionItem.read_seq_id) {
                //已读seqID需要变更
                int64_t localMaxSeqId = toonim::getChatDB()->getMaxSeqAllMessage(tempSession.sessionId.c_str(), 2);
                if (localMaxSeqId <= sessionItem.read_seq_id) {
                    getChatDB()->markSessionRead(tempSession.sessionId.c_str());
                    isUnreadChange = true;
                }
            }
            continue;
        }
        
        TNMPLOG("processHotSessionResp sessionId:"<<vctMessage[0].sessionId<<" readSeqId:"<<sessionItem.read_seq_id);
        
        int64_t localMaxSeqId = toonim::getChatDB()->getMaxSeqAllMessage(vctMessage[0].sessionId.c_str(), 2);
        if (localMaxSeqId >= maxSeqId) {//没有新消息
            CTNSession tempSession;
            getLocalSessionBySessionItem(sessionItem, tempSession);
            
            if (tempSession.readSeqId == sessionItem.read_seq_id || !tempSession.isValid()) {//添加|| !tempSession.isValid()是由于该会话若被本地删除，则会获取不到tempSession，而本地消息最大seqId会大于等于热会话最大的seqID，因此会走到该分支 wxy
                continue;//无离线消息，continue
            }
            //已读seqID需要变更
        }
        
        int sessionUnread = 0;
        string atMeMsgId;
        CTNMessage lastMessage;//所有消息中最大消息
        CTNMessage maxDispayMessage;//最大显示消息中消息
        int64_t minSeqId = LLONG_MAX;
        for (vector<CTNMessage>::iterator itTmp = vctMessage.begin(); itTmp != vctMessage.end(); itTmp++){
            CTNMessage &message = *itTmp;
            minSeqId = min(minSeqId, message.seqId);
            if (messageIsForbidden(message)) {
                continue;
            }
            
            //判断消息覆盖问题是否需要计数，默认计数，为false时不计数
            bool addUnreadCount = true;
            
            switch (message.type) {
                case CTNIMMessageTypeChat:
                    processMessageChat(message);
                    break;
                case CTNIMMessageTypeGroupChat:
                {
                    bool temp = processMessageGroupChat(message,groupIdSet);
                    needSyncGroup = temp ? temp:needSyncGroup;
                    //处理关注的人消息，只有当message的seqid大于已读的readseqid时才需要处理重要消息
                    if (message.seqId > sessionItem.read_seq_id) {
                        this->processFollowMessage(message);
                    }
                    break;
                }
                case CTNIMMessageTypeMsgSingleOperate:
                case CTNIMMessageTypeMsgGroupOperate:
                    processMessageOperate(message);
                    break;
                case CTNIMMessageTypeBizNotice:
                case CTNIMMessageTypeGroupNotice:{
                    //返回是否计数
                    addUnreadCount = this->processMessageNotice(message, false);
                    break;
                }
                case CTNIMMessageTypeSync:
                    this->processMessageSync(message, false);
                    break;
                 default:
                    TNMPLOG("processHotSessionResp type is error:" << itTmp->type);
                    break;
            }
            
            this->checkMessageRevoked(message);
            
            //有离线消息 记录断层 并且获取最大消息，有可能是非正常消息
            if (maxSeqId == message.seqId){
                //如果新会话，本地没消息，如何处理,记录到已读位置，或者100条； 本地没断层，不需要记录
                if (localMaxSeqId > 0 && maxSeqId > localMaxSeqId +1){
                    message.faultSeqId = localMaxSeqId;
                }
                else if (localMaxSeqId <= 0){//本地没消息
                    //0表示特殊情况，本地没消息，拉取时根据情况来判断是否需要拉取100条，
                    //如果都已读，只拉取N条(一屏幕），否则拉取100条；
                    //是否已读判断：sessionItem.read_seq_id == message.seqId;
                    message.faultSeqId = 0;
                }
                
                lastMessage = message;
            }
            
            //获取最大可显示消息
            if (message.status == CTNIMMessageNormal && message.seqId > maxDispayMessage.seqId){
                maxDispayMessage = message;
            }

            //热会话只记录最后一条消息，防止历史消息拉取记录不到未读数
            vctSaveMessage.push_back(message);
            
            //2、判断是否有未读消息（a 对比seqId b 最近一条消息是否是自己的）
            //服务器返回的已读seqId == max（服务器返回的高优先级最大seqId，服务器返回的普通最大seqId），
            //有未读消息
            //1、获取该会话所有高优先级的消息
            //2、获取100条普通优先级的消息
            //俩条消息都可能为废弃的消息,不加未读
            //聊天都可能是已读 //撤回消息不计数
            if (message.seqId > sessionItem.read_seq_id && message.isMyself == CTNOwnerOther
                && message.status == CTNIMMessageNormal && addUnreadCount && message.seqId > localMaxSeqId){
                sessionUnread++;
            }
            
            if (message.seqId > sessionItem.read_seq_id && isAtMeFromMsgIdWithMessage(message) ){
                atMeMsgId = message.msgId;
                //只有当该at消息未读时才需要存储at消息表
                this->processAtMeMessage(message);
            }
        }
        
        if (!maxDispayMessage.isEmpty() && lastMessage.seqId != maxDispayMessage.seqId) {
            lastMessage = maxDispayMessage;
        }
       
        //抛出通知，直接处理掉，不生成会话
//        if (lastMessage.status == CTNIMMessageNoSession){
//            continue;
//        }
        
        bool isNewSession = false;
        CTNSession session = getSessionByMessage(lastMessage, isNewSession);
        if (!session.isValid()){
            TNMPLOG("processHotSessionResp session type is invalid:" << lastMessage.genBodyJson());
            continue;
        }
   
        if (session.readSeqId < sessionItem.read_seq_id) {
            session.readSeqId = sessionItem.read_seq_id;
        }
        
        //当服务端给的readsqid和最后一条消息的seqid相同时，说明该会话已读，需要把未读数置为0
        if (session.readSeqId == lastMessage.seqId) {
            sessionUnread = 0;
            session.unreadCount = 0;
            session.atMeMsgId = "";
            isUnreadChange = true;
            //清除未读数,需要删除该sessionId下的所有重要消息
            if (toonim::getChatDB() != nullptr) {
                toonim::getChatDB()->deleteImportantSessionBySessionId(session.sessionId.c_str());
            }
        }
        
        if (sessionUnread > 0){
            session.unreadCount += sessionUnread;
            isUnreadChange = true;
        }
        if (atMeMsgId.length() > 0){
            session.atMeMsgId = atMeMsgId;
        }
        
        sessionArray.push_back(session);
        CTNOffMessageResult offMessage;
        offMessage.sessionId = session.sessionId;
        offMessage.maxSeqId = maxSeqId;
        offMessage.minSeqId = minSeqId;
        sessionSet.insert(offMessage);
        TNMPLOG("processHotSessionResp maxSeqId:"<<maxSeqId);
    }
    
    //save to db;
    toonim::getChatDB()->addMessages(vctSaveMessage);
    addSessionWithArray(sessionArray);//notifyRecvMessage 方法中的unread删除，此处可以调用
    
    //此处去掉sessionSet为空判断，由于安卓业务问题需要主动发热会话回调
    if (_callback != nullptr) {
        //热会话回调,在聊天页面时处理完热会话需要刷新最有一条消息
        _callback->hotSessionResp(sessionSet);
        //session未读数变化，最后消息变化
        if (isUnreadChange) {
            _callback->notificationCenter(TNC_UNREAD, "");
        } else {
            _callback->notificationCenter(TNC_SESSION_CHANGE, "");
        }
    }
    
    //需要拉取混合断层
    fillSessionFaultMessage();
    
    //need sync group data
    //第一次必须同步群资料
//    if (needSyncGroup){
        this->syncMyGroupFromServerSucceed();
//    }
    
    //同步群成员
    for (set<int64_t>::iterator iter = groupIdSet.begin(); iter != groupIdSet.end(); iter++){
        this->syncGroupMember(*iter);
    }
}

//转换消息
//返回最小seqId
void CTNChatManager::transOffmsgs(vector<Toon::OffMsgItem> &vctSrc, vector<CTNMessage> &vctDest, int64_t &maxSeqId){
    int64_t minSeqId = LLONG_MAX;
    vector<Toon::OffMsgItem>::iterator itTmp = vctSrc.begin();
    while (itTmp != vctSrc.end())
    {
        CTNMessage imMessage = msgReqToIMMessage(itTmp->type,&(itTmp->item));
        if (!imMessage.isEmpty() && !messageIsForbidden(imMessage)){
            
            if (imMessage.priority == 1) {//高优先级消息放到前面处理
                vctDest.insert(vctDest.begin(), imMessage);
            }else{
                vctDest.push_back(imMessage);
            }
            
            maxSeqId = max(maxSeqId,itTmp->item.seq_id);
            
            minSeqId = min(minSeqId, itTmp->item.seq_id);
        }
        
        itTmp ++;
    }

}

//单聊处理
void CTNChatManager::processMessageChat(CTNMessage &message){
//    message.isMyself = this->getMessageOwner(message);
    
//    CTNIMMessageStatus status = checkSystemMessageStatus(message, true);
//    message.status = status;
//    _dbChat->addMessage(message);
}

//syncMemberGroupId:同步群成员 groupId
//返回值：是否同步群资料
bool CTNChatManager::processMessageGroupChat(CTNMessage &message, set<int64_t> &groupIdSet){
    message.isMyself = this->getMessageOwner(message);
    
    message.status = checkSystemMessageStatus(message);
    
//    if (message.status == CTNIMMessageDeleted){
//        return false;
//    }
    
#ifdef RAPIDJSONWRAPPER
    //需要处理是否保存消息
    CTNJsonReader bodyDict(message.content);
    
    if (bodyDict.hasParseErr()) {
        return false;
    }
    
    //45. 邀请入群，47,群资料变动，49，群成员加入，51，群成员退出，53，自己被踢，55，加入聊天室，57，退出聊天室,63群里有人被踢 140，141
    bool ret = false;
    if (message.catalogId == 45 || message.catalogId == 47 || message.catalogId == 53){
        ret = true;
    }
    
    if (message.catalogId == 45 || message.catalogId == 51 || message.catalogId == 63){
        string groupId = bodyDict["groupId"].getString();
        if (groupId.length() > 0){
            TNMPLOG("Need Sync groupMember:"<<groupId);
            groupIdSet.insert(CTNDBUtils::stringToInt64(groupId));
        }
    }
#else
    //需要处理是否保存消息
    rapidjson::Document bodyDict;
    bodyDict.Parse<0>(message.content.c_str());
    
    if(bodyDict.HasParseError()) {
        return false;
    }
    
    //45. 邀请入群，47,群资料变动，49，群成员加入，51，群成员退出，53，自己被踢，55，加入聊天室，57，退出聊天室,63群里有人被踢 140，141
    bool ret = false;
    if (message.catalogId == 45 || message.catalogId == 47 || message.catalogId == 53){
        ret = true;
    }
    
    if (message.catalogId == 45 || message.catalogId == 51 || message.catalogId == 63){
        string groupId = GetValueByPointerWithDefault(bodyDict, "/groupId", "").GetString();
        if (groupId.length() > 0){
            TNMPLOG("Need Sync groupMember:"<<groupId);
            groupIdSet.insert(CTNDBUtils::stringToInt64(groupId));
        }
    }
#endif
	_callback->syncGroupchat(&message);
    return ret;
}

//用户被踢出群聊后，不会收到离线消息！！
CTNIMMessageStatus CTNChatManager::checkSystemMessageStatus(CTNMessage& message, bool needSync) {
    if (message.isEmpty()) {
        return CTNIMMessageDeleted;
    }
    
    //只处理系统消息
    if (message.contentType != CTNChatTypeSystem) {
        return CTNIMMessageNormal;
    }
    
#ifdef RAPIDJSONWRAPPER
    CTNJsonReader content(message.content);
    
    CTNJsonValue feedIdList = content["showFeedIdList"];
    
    std::set<string> feedIdSet;
    
    for (int i = 0; i < feedIdList.getArraySize(); ++i) {
        feedIdSet.insert(feedIdList[i].getString());
    }
#else
    rapidjson::Document content;
    content.Parse<0>(message.content.c_str());
    
    rapidjson::Value& feedIdList = GetValueByPointerWithDefault(content, "/showFeedIdList", "");
    
    std::set<string> feedIdSet;
    if (feedIdList.IsArray()){
        for (rapidjson::SizeType i = 0; i < feedIdList.Size(); i++){
            if(feedIdList[i].IsString()) {
                feedIdSet.insert(feedIdList[i].GetString());
            }
        }
    }
#endif
    
    if (!isMySelfFeed(feedIdSet)) {
        return CTNIMMessageDeleted;
    }
    
    return CTNIMMessageNormal;
}


void CTNChatManager::checkMessageRevoked(CTNMessage &message){
    unique_lock<std::mutex> uniqueLock(_cacheOperateMutex);
    map<string, CTNMessageOperate>::iterator iterFind = _cacheOperateMsg.find(message.msgId);
    if (iterFind == _cacheOperateMsg.end()){
        return;
    }
    
    message.contentType = CTNChatTypeRevoked;
    message.content = genRevokeMessageContent(message, iterFind->second.opName);
    message.width = 0;
    message.height = 0;
    
    //程序crash 可能会有问题
    toonim::getChatDB()->deleteOperateMessage(iterFind->second.msgId.c_str());
}

bool CTNChatManager::processMessageNotice(CTNMessage &message, bool isOnline){
    if (message.isEmpty()){
        return false;
    }
    
    //判断是否为新朋友消息
    string broadcast;
    if (isFilterNotice(message, broadcast)) {
        if (_callback != nullptr){
            _callback->noticeMessage(&message, broadcast.c_str(), isOnline);
        }
        message.status = CTNIMMessageNoSession;
        return false;
    }
    
    if (message.contentType == CTNChatTypeNotification || message.contentType == 0 || message.contentType == CTNChatTypeCustomizedNotification) {
        
#ifdef RAPIDJSONWRAPPER
        CTNJsonReader noticeBody(message.content);
        
        if (noticeBody["msgStatus"]["content"].getString().length() > 0) {
            message.noticeStatusType = noticeBody["msgStatus"]["content"].getString();
        }
#else
        rapidjson::Document noticeBody;
        noticeBody.Parse<0>(message.content.c_str());
        
        rapidjson::Value& msgStatusType = GetValueByPointerWithDefault(noticeBody, "/msgStatus/content", "");
        if (strlen(msgStatusType.GetString()) > 0) {
            message.noticeStatusType = msgStatusType.GetString();
        }
#endif
        
    }
    
    //获取bizNo相同的seqid最大的消息，与新消息进行判断
    CTNMessage oldMessage = toonim::getChatDB()->getMaxNoticeMessage(message.sessionId.c_str(), message.bizNo.c_str());
    //没有相同的msgid消息
    if (oldMessage.isEmpty()) {
        return true;
    }
    
    if (message.seqId > oldMessage.seqId) {
        toonim::getChatDB()->deleteMessage(oldMessage.sessionId.c_str(), oldMessage.msgId.c_str());
    } else {
        message.status = CTNIMMessageDeleted;
    }
    
    CTNSession session = toonim::getChatDB()->getSession(message.sessionId.c_str());
    if (oldMessage.seqId > session.readSeqId) {
        return false;
    }
    
    return true;
}

void CTNChatManager::processMessageSync(CTNMessage &message, bool isOnline){
    if (message.isEmpty()){
        return;
    }
    
    if (messageIsForbidden(message)) {
        return;
    }
    
//    _dbChat->addMessage(message);

    if (_callback != nullptr){
        _callback->syncMessage(&message, isOnline);
    }
    
    message.status = CTNIMMessageNoSession;
}

//返回源消息
CTNMessage CTNChatManager::processMessageOperate(CTNMessage &message){
    unique_lock<std::mutex> uniqueLock(_cacheOperateMutex);
    if (message.isEmpty()){
        return CTNMessage();
    }
    
    if (messageIsForbidden(message)) {
        return CTNMessage();
    }
    
    //        1、    寻找被操作消息，是否找到
    //        2、    否，放入操作队列中，等待目标消息出现，终止
    //        3、    是，取出被操作消息，执行替换操作，被替换消息入库，操作消息出队列，终止
    if (message.catalogId != CTNIMMessageRevoked) {
        return CTNMessage();
    }
    
    message.status = ::CTNIMMessageRevoked;
    
#ifdef RAPIDJSONWRAPPER
    CTNJsonReader dictContent(message.content);
    
    string opMsgId = dictContent["msgId"].getString();
#else
    rapidjson::Document dictContent;
    dictContent.Parse<0>(message.content.c_str());
    
    string opMsgId = GetValueByPointerWithDefault(dictContent, "/msgId", "").GetString();
#endif
    
    
    //0、从缓存消息队列中寻找，离线消息列表中可能有该条消息要操作的消息对象，但是这些消息还没有存到数据库中，所以下面的getMessage操作不会查到这条消息，调用的地方将这些可能的目标消息放入到了vector中了。还没有解决这个问题，暂时在调用处又对消息vector重新遍历并处理一遍 wxy
    
    //1、寻找被操作消息，是否找到
    CTNMessage operedMsg = toonim::getChatDB()->getMessage(message.sessionId.c_str(), opMsgId.c_str());
    
    //撤回消息后需要删掉重要消息表中的数据
    bool deleteAtResult = toonim::getChatDB()->deleteImportantMessage(CTNIMMessageTypeAt, opMsgId.c_str());
    bool deleteFollow = toonim::getChatDB()->deleteImportantMessage(CTNIMMessageTypeFollow, opMsgId.c_str());
    if (deleteAtResult || deleteFollow) {
        //当删除成功时，需要刷新session页面，防止出现删除不实最后一条消息时不能刷新问题
        if (_callback != nullptr) {
            _callback->notificationCenter(TNC_SESSION_CHANGE, "");
        }
    }
    
    if (operedMsg.isEmpty()) {
        
        //        2、    否，放入操作队列中，等待目标消息出现，终止
        CTNMessageOperate operatMsg;
        operatMsg.content = message.content;
        operatMsg.mfrom = message.fromId;
        operatMsg.msgId = message.msgId;
        operatMsg.mto = message.toId;
        operatMsg.seqId =message.seqId;
        operatMsg.timestamp = message.timestamp;
        operatMsg.type = message.type;
        
#ifdef RAPIDJSONWRAPPER
        operatMsg.opFeedId = dictContent["operatorFeedId"].getString();
        operatMsg.opMsgId = opMsgId;
        operatMsg.opName = dictContent["operatorName"].getString();
        operatMsg.catalogId = dictContent["catalogId"].getInt32();
#else
        operatMsg.opFeedId = GetValueByPointerWithDefault(dictContent, "/operatorFeedId", "").GetString();
        operatMsg.opMsgId = opMsgId;
        operatMsg.opName = GetValueByPointerWithDefault(dictContent, "/operatorName", "").GetString();
        operatMsg.catalogId = GetValueByPointerWithDefault(dictContent, "/catalogId", 0).GetInt();
#endif
        
        _cacheOperateMsg[opMsgId] = operatMsg;
        
        vector<CTNMessageOperate> vecOperate;
        vecOperate.push_back(operatMsg);
        toonim::getChatDB()->addOperateMessage(vecOperate);
    }
    else {
        //        3、    是，取出被操作消息，执行替换操作，被替换消息入库，操作消息出队列，终止
        operedMsg.contentType = message.contentType;
#ifdef RAPIDJSONWRAPPER
        operedMsg.content = genRevokeMessageContent(message, dictContent["operatorName"].getString()) ;
#else
        operedMsg.content = genRevokeMessageContent(message, GetValueByPointerWithDefault(dictContent, "/operatorName", "").GetString());
#endif
        operedMsg.width = 0;
        operedMsg.height = 0;
        operedMsg.isMyself = message.isMyself;
        
        toonim::getChatDB()->updateMessage(operedMsg);
        
        toonim::getChatDB()->deleteOperateMessage(message.msgId.c_str());
        
        //如果撤回最后一条消息，更新session 最后一条消息
        CTNSession session = toonim::getChatDB()->getSession(operedMsg.sessionId.c_str());
        if (session.isValid() && (session.lastMsgId == opMsgId
                                  || session.atMeMsgId == opMsgId) && operedMsg.status != CTNIMMessageDeleted) {
            session.type = operedMsg.type;
            if (session.atMeMsgId == opMsgId) {
                session.atMeMsgId = "";

                CTNMessage lastMessage = toonim::getChatDB()->getLastMessage(session.sessionId.c_str());
                if (lastMessage.senderName.length() > 0) {
                    session.lastMsg = lastMessage.senderName + ":" + lastMessage.getAbstractText();
                } else {
                    session.lastMsg = lastMessage.getAbstractText();
                }
            }
            else {
                session.lastMsg = operedMsg.getAbstractText();
            }
            session.lastMsgSendStatus = CTNMessageSuccess;

            vector<CTNSession> sessionArray;
            sessionArray.push_back(session);
            toonim::getChatDB()->updateSession(sessionArray);
           
            if (_callback != nullptr) {
                std::string jsonStr = this->genSessionIdToJson(session.sessionId);
                _callback->notificationCenter(TNC_SESSION_CHANGE, jsonStr.c_str());
                
                //发送重要消息通知
                std::ostringstream strStream;
                strStream << TYPE_CLIENT_FOLLOWMESSAGE;
                string str = TNC_IMPORTANT_MESSAGE(strStream.str());
                _callback->notificationCenter(str.c_str());
                std::ostringstream otrStream;
                otrStream << TYPE_CLIENT_ATMESSAGE;
                string noticeStr = TNC_IMPORTANT_MESSAGE(otrStream.str());
                _callback->notificationCenter(noticeStr.c_str());
            }
        }
    }
    
    return operedMsg;
    
}

CTNIMMessageStatus CTNChatManager::checkSystemMessageStatus(CTNMessage& message){
    if (message.isEmpty()) {
        return CTNIMMessageDeleted;
    }
    
    //只处理系统消息
    if (message.contentType != CTNChatTypeSystem) {
        return CTNIMMessageNormal;
    }
    
#ifdef RAPIDJSONWRAPPER
    CTNJsonReader content(message.content);
    CTNJsonValue feedIdList = content["showFeedIdList"];
    
    std::set<string> feedIdSet;
    
    for (int i = 0; i < feedIdList.getArraySize(); ++i) {
        feedIdSet.insert(feedIdList[i].getString());
    }
#else
    rapidjson::Document content;
    content.Parse<0>(message.content.c_str());
    
    rapidjson::Value& feedIdList = GetValueByPointerWithDefault(content, "/showFeedIdList", "");
    
    std::set<string> feedIdSet;
    if (feedIdList.IsArray()){
        for (rapidjson::SizeType i = 0; i < feedIdList.Size(); i++){
            if(feedIdList[i].IsString()) {
                feedIdSet.insert(feedIdList[i].GetString());
            }
        }
    }
#endif
    
    
    
    if (!isMySelfFeed(feedIdSet)) {
        return CTNIMMessageDeleted;
    }
    
    return CTNIMMessageNormal;
}


void CTNChatManager::processHistoryMessages(vector<Toon::OffMsgItem> &historyMessages, string& reqId)
{
    int64_t maxSeqId = 0;
    vector<CTNMessage> msgCountArray;
    //转换消息，顺便找出最大maxSeqId
    this->transOffmsgs(historyMessages, msgCountArray, maxSeqId);
    
    OffMsgMgr offMsgMgr = _offMsgQueue[reqId];
    string sessionId = offMsgMgr.faultMsg.sessionId;
 
    TNMPLOG("processHistoryMessages reqId:"<<reqId<<" count:"<<offMsgMgr.count <<" real count:"<<msgCountArray.size());
    
    //此处可能有bug，消息为非法消息，被过滤了就会有问题
    if (msgCountArray.size() == 0){
        // 成功了 没有消息 视为 没有此断层消息可拉 删除断层
        TNMPLOG("processHistoryMessages msgCountArray is Empty!!");
        CTNMessage message = toonim::getChatDB()->getMessage(sessionId.c_str(), offMsgMgr.faultMsg.msgId.c_str());
        if (!message.isEmpty()){
            message.faultSeqId = -1;//清除断层消息
            toonim::getChatDB()->updateMessage(message);
        }
        
       _offMsgQueue.erase(reqId);
        return;
    }
    
    TNMPLOG("processOffMsgResp reqId:" << reqId << " offMsgMgr.reqId:" << offMsgMgr.reqId);
    
    //热会话时有可能不生成会话 删除会话时需要清除会话断层
    CTNSession session = toonim::getChatDB()->getSession(sessionId.c_str());

    CTNMessage minMessage;
    minMessage.seqId = LLONG_MAX;
    int unReadCount = 0;
    set<int64_t> groupIdSet;
    //找@我的未读消息
    string atMeMsgId;
    
    //存储通知消息的bizNo和message，做内存级判断比较
    map<string, CTNMessage*> noticemap;
    //同步消息判重用
    set<int32_t> syncCatalogIdSet;
    
    for (vector<CTNMessage>::iterator iterTmp = msgCountArray.begin(); iterTmp != msgCountArray.end(); iterTmp++){
        //有问题，函数中赋值没有带出来！！
        CTNMessage &message = *iterTmp;
        //判断消息覆盖问题是否需要计数，默认计数，为false时不计数
        bool addUnreadCount = true;
        
        switch (message.type) {
            case CTNIMMessageTypeChat:
                processMessageChat(message);
                break;
            case CTNIMMessageTypeGroupChat:
            {
                processMessageGroupChat(message, groupIdSet);
                //处理关注的人消息，只有当message的seqid大于已读的readseqid时才需要处理重要消息
                if (message.seqId > session.readSeqId) {
                    this->processFollowMessage(message);
                }
                break;
            }
            case CTNIMMessageTypeMsgSingleOperate:
            case CTNIMMessageTypeMsgGroupOperate:
                processMessageOperate(message);
                break;
            case CTNIMMessageTypeBizNotice:
            case CTNIMMessageTypeGroupNotice:
            {
                addUnreadCount =this->processMessageNotice(message, false);
                
                //在内存级别判断消息覆盖问题，有被覆盖的消息需要把状态改为delete状态
                if (message.bizNo.length() > 0) {
                    CTNMessage* oldMessage = noticemap[message.bizNo];
                    if (oldMessage == nullptr) {
                        noticemap[message.bizNo] = &message;
                    } else {
                        if (oldMessage->seqId > message.seqId) {
                            message.status = CTNIMMessageDeleted;
                        } else {
                            oldMessage->status = CTNIMMessageDeleted;
                            noticemap[message.bizNo] = &message;
                        }
                    }
                }
                break;
            }
            case CTNIMMessageTypeSync:
            {
                //离线同类型的同步只发一次
                if (syncCatalogIdSet.find(message.catalogId) == syncCatalogIdSet.end()){
                    syncCatalogIdSet.insert(message.catalogId);
                    this->processMessageSync(message, false);
                }
                else {
                    message.status = CTNIMMessageNoSession;
                }
                
                break;
            }
            default:
                TNMPLOG("processHotSessionResp type is error:" << message.type);
                break;
        }
        
        this->checkMessageRevoked(message);
        
        if (!isMySelfClientID(message.fromClientId)
            && message.status == CTNIMMessageNormal
            && message.seqId > session.readSeqId && addUnreadCount) {
                unReadCount++;
            
            if (isAtMeFromMsgIdWithMessage(message)){
                atMeMsgId = message.msgId;
                //只有当该at消息未读时才需要存储at消息表
                if (message.seqId > session.readSeqId) {
                    this->processAtMeMessage(message);
                }
            }
        }
        
        //获取最小messageId
        if (minMessage.seqId > message.seqId){
            minMessage = message;
        }
        
    }
   
    toonim::getChatDB()->addMessages(msgCountArray);
    
//    //保存
//    if (minMessage.status != CTNIMMessageNoSession){
        CTNMessage message = toonim::getChatDB()->getLastMessage(sessionId.c_str());
        if (!message.isEmpty()) {
            bool isNewSession = false;
            session = getSessionByMessage(message, isNewSession);
        }

        if (session.isValid()) {
            session.unreadCount += unReadCount;
            if (atMeMsgId.length() > 0 && session.atMeMsgId.length() == 0){
                session.atMeMsgId = atMeMsgId;
            }
            
            vector<CTNSession> vecSession;
            vecSession.push_back(session);
            toonim::getChatDB()->addSession(vecSession);
            if (_callback != nullptr){
                set<CTNOffMessageResult> sessionSet;
                CTNOffMessageResult offMessage;
                offMessage.sessionId = sessionId;
                offMessage.maxSeqId = maxSeqId;
                offMessage.minSeqId = minMessage.seqId;
                sessionSet.insert(offMessage);
                _callback->offMsgResp(sessionSet);
                if (unReadCount > 0 ) {
                    _callback->notificationCenter(TNC_UNREAD, "");
                } else {
                    std::string jsonStr = this->genSessionIdToJson(session.sessionId);
                    _callback->notificationCenter(TNC_SESSION_CHANGE, jsonStr.c_str());
                }
            }
        }
//    }
    
    //3、更新断层
    //出错时不记录断层
    int64_t faultSeqId = -1;//直接保存断层消息 localMsgId，缓存可能会有多线程同步问题
    if (offMsgMgr.faultMsg.msgId.length() > 0) {
        CTNMessage orgFault = toonim::getChatDB()->getMessage(sessionId.c_str(), offMsgMgr.faultMsg.msgId.c_str());
        //方便移动断层游标位置
        faultSeqId = orgFault.faultSeqId;;
        
        orgFault.faultSeqId = -1;//清除断层
        toonim::getChatDB()->updateMessage(orgFault);
    }
   
    
   if (offMsgMgr.minSeqId >= minMessage.seqId - 1 || faultSeqId <= 0) {
       TNMPLOG("offMsgMgr.seqId >= minSeqId ||  || faultSeqId <= 0 :"<<faultSeqId);
        //完成消息获取任务 continue
         //首次拉取没有写入数据库断层信息，因此不必清除原来的断层消息
        _offMsgQueue.erase(reqId);
    } else {
        //            增加新断层信息
        minMessage.faultSeqId = faultSeqId;
        toonim::getChatDB()->updateMessage(minMessage);
        
        //删除老历史请求，
        _offMsgQueue.erase(reqId);
        
        offMsgMgr.accumuCount += msgCountArray.size();
        //判断断层是否已经拉取够最大的消息，若达到，则不再进行拉取
        if (offMsgMgr.accumuCount < ACCUMUMAXLOADNUM) {
            //增加新历史请求，方便响应处理
            offMsgMgr.reqId = REQ_ID;
            offMsgMgr.maxSeqId = minMessage.seqId;
            offMsgMgr.faultMsg = minMessage;
            offMsgMgr.count = MAXLOADNUM;
            _offMsgQueue[offMsgMgr.reqId] = offMsgMgr;
            
            pullOffMessage(offMsgMgr, offMsgMgr.count, 2);
        }
    }
}

void CTNChatManager::fillSessionFaultMessage() {
    vector<CTNMessage> vecFaultMessage = toonim::getChatDB()->getAllFaultMessage();
    std::map<std::string, int64_t> mpSessionReadInfo;
    
    ((CTNDBChat*)toonim::getChatDB())->getSessionReadedId(mpSessionReadInfo);
    
    for (int i = 0; i < vecFaultMessage.size(); ++i) {
        CTNMessage faultMsg = vecFaultMessage[i];
        
        if (faultMsg.isEmpty()){
            continue;
        }        
        
        int32_t offMsgCount = (int32_t)(faultMsg.seqId - faultMsg.faultSeqId) - 1;//123
        
        if (offMsgCount > 0) {
            OffMsgMgr faltMsgMgr;
            faltMsgMgr.reqId = REQ_ID;
            faltMsgMgr.priority = 2;
            faltMsgMgr.from = faultMsg.fromId;
            faltMsgMgr.to = faultMsg.toId;
            faltMsgMgr.type = faultMsg.type;
            faltMsgMgr.faultMsg = faultMsg;
            
            //获取所有断层消息
            faltMsgMgr.maxSeqId = faultMsg.seqId;//+ 1 123
            faltMsgMgr.minSeqId = faultMsg.faultSeqId;

            if (faultMsg.faultSeqId == 0 && faultMsg.seqId == mpSessionReadInfo[faultMsg.sessionId]){
                //获取15条
                faltMsgMgr.count = 15;
            }
            else{
                faltMsgMgr.count = MAXLOADNUM;
            }
 
            _offMsgQueue[faltMsgMgr.reqId] = faltMsgMgr;
            pullOffMessage(faltMsgMgr, (int)faltMsgMgr.count, 2);
        } else {
            faultMsg.faultSeqId = -1;
            toonim::getChatDB()->updateMessage(faultMsg);
        }
        
    }
}

void CTNChatManager::processFollowMessage(CTNMessage &message) {
    //过滤非法、系统、撤回消息
    if (message.contentType == CTNChatTypeSystem || message.contentType == CTNChatTypeNone || message.contentType == CTNChatTypeRevoked){
        return;
    }
    if (((CTNDBSetting *)(toonim::getSettingsDB()))->isFollowMessage(message)) {
        toonim::getChatDB()->addImportantMessage(CTNIMMessageTypeFollow, message);
        if (_callback != nullptr) {
            _callback->notificationCenter(TNC_SESSION_CHANGE);
            std::ostringstream strStream;
            strStream << TYPE_CLIENT_FOLLOWMESSAGE;
            string str = TNC_IMPORTANT_MESSAGE(strStream.str());
            _callback->notificationCenter(str.c_str());
        }
    }
}

void CTNChatManager::processAtMeMessage(CTNMessage &message) {
    if (toonim::getSettingsDB() != nullptr && toonim::getSettingsDB()->getImportantStatus(CTNIMMessageTypeAt)) {
        if (toonim::getChatDB() != nullptr) {
            toonim::getChatDB()->addImportantMessage(CTNIMMessageTypeAt, message);
            if (_callback != nullptr) {
                _callback->notificationCenter(TNC_SESSION_CHANGE);
                std::ostringstream strStream;
                strStream << TYPE_CLIENT_ATMESSAGE;
                string str = TNC_IMPORTANT_MESSAGE(strStream.str());
                _callback->notificationCenter(str.c_str());
            }
        }
    }
}

