#include <QApplication>
#include "noticelistmodel.h"
#include "TNDataControlServer.h"
#include "TNIMCoreClient.h"
#include "TNDataCache.h"
#include "TNUserDataHelper.h"
#include "TNPathUtil.h"
#include "out_line_message/tnoutlinemessagethread.h"
#include "network/tnsessionnetwork.h"
#include "tnnotifycenter.h"
#include "CTNDBHeader.h"
#include "CTNDBAPI.h"

NoticeListModel::NoticeListModel(QObject* parent) : TNTableModel(parent)
  ,_outLineThread(NULL)
{
    connect(this, SIGNAL(updateTotalUnread()),
        this, SLOT(onUpdateTotalUnread()),Qt::QueuedConnection);
    TNNotifyCenter::instance()->connnectNotifyCurrentFeedChanged(this);
    TNNotifyCenter::instance()->connectNotifyReMarkUpdate(this);
    TNNotifyCenter::instance()->connectNotifyOrgCommunicationStatus(this);
}

NoticeListModel::~NoticeListModel()
{

}

void NoticeListModel::init_data(QString feedId)
{
    this->clearData();
    if(feedId == AVATAR_ALL_FEED){
        feedId = "";
    }else{
        //屏蔽不可沟通的会话
        if(feedId.startsWith("o_")){
            if(!TNDataCache::GetInstance()->getOrgCommunicationStatus(feedId)){
                //显示notice_list默认背景
                emit showDefaultBack();
                return;
            }
        }
    }
    ////////////////////////
    std::vector<toonim::CTNSession> ctn_sessions = TNIMCoreClient::GetDBChat()->getSessions(feedId.toStdString().c_str(), true);
    for(int i = ctn_sessions.size() - 1; i >= 0; i--){
        CTNSession ctn_session = ctn_sessions[i];
        QString myFeedId(ctn_session.myFeedId.c_str());
        //屏蔽不可沟通的会话
        if(myFeedId.startsWith("o_")){
            if(!TNDataCache::GetInstance()->getOrgCommunicationStatus(myFeedId)){
                continue;
            }
        }
        /////////////////
        TNMessageListAdapter* session = createNewSession(&ctn_session);
        if(!session) continue;
        insertData(0,session);
        //通知Tray 未读消息列表
        if (session->getUnreadCount() > 0){
            if (!session->getNoAlarm() || session->getIsAtMe()){
                emit outlineUpdateUnreadTray(*session, session->getUnreadCount());
            }
        }
    }

    //更新总条数
    emit updateTotalUnread();
    //显示notice_list默认背景
    emit showDefaultBack();
}

TNMessageListAdapter* NoticeListModel::createNewSession(const toonim::CTNSession *ctn_session)
{
    QString sessionId = QString(ctn_session->sessionId.c_str());//sessionPtr->GetSessionId();
    //第一期不支持小秘书聊天功能
    QList<st_FeedPtr> myStuff;
    TNDataCache::GetInstance()->getMyStuff(myStuff, sessionId);
    if (myStuff.size() > 0)
        return NULL;
    if (sessionId == TNUserDataHelper::GetInstance()->_pluginParam->strTnUserID){
        return NULL;
    }

    QString myFeedId = QString(ctn_session->myFeedId.c_str());
    QString sessionTitle = QString(ctn_session->title.c_str());
    QString strAvatarURL = QString(ctn_session->avatarId.c_str());
    QString toFeedId,remark;
    MSG_BIZ_TYPE type = TNIMCoreClient::GetIMClient()->GetSessionType(ctn_session);
    bool bNoAlarm = false;//免打扰
    if (type == MSG_BIZ_GROUPCHAT){//群聊查群聊info
        toFeedId = sessionId;
        TableBaseVec tempTableBaseVec;
        TNDataControlServer::GetInstance()->Query(tempTableBaseVec, "GroupInfo",
            "groupId", sessionId, DBTYPE_USER);
        if (!tempTableBaseVec.empty()){
            st_GroupInfoPtr groupInfo = std::dynamic_pointer_cast<st_GroupInfo>
                (tempTableBaseVec[0]);
            bNoAlarm = groupInfo->GetDisturbStatus();
            sessionTitle = groupInfo->GetName();
        }
    }else if(type == MSG_BIZ_SINGLECHAT){//单聊
        QStringList sessionList = sessionId.split("_");
        if (sessionList.size() == 4){
            QString one = sessionList[0] + "_" + sessionList[1];
            QString two = sessionList[2] + "_" + sessionList[3];
            if (one == myFeedId){
                toFeedId = two;
            }else{
                toFeedId = one;
            }
        }
        st_FeedPtr feedPtr;
        TNUserDataHelper::GetInstance()->GetFeedInfo(toFeedId,feedPtr);
        if(feedPtr.get())
            sessionTitle = feedPtr->GetTitle();
        //单聊需要备注
        remark = TNDataCache::GetInstance()->getFriendFeedReMark(toFeedId,myFeedId);
    }else if (type == MSG_BIZ_UNSHOW){
        return NULL;
    }else if(type == MSG_BIZ_NOTIFY){
        sessionTitle = QString(ctn_session->title.c_str());
        strAvatarURL = QString(ctn_session->avatarId.c_str());
    }

    TNMessageListAdapter * tempAdapter = new TNMessageListAdapter(sessionId, type);
    tempAdapter->setName(sessionTitle);
    tempAdapter->setAvatarPhotoUrl(strAvatarURL);
    tempAdapter->setType(type);
    tempAdapter->setIsAtMe(!ctn_session->atMeMsgId.empty());
    tempAdapter->setTime(ctn_session->lastTime);
    int unReadNum = ctn_session->unreadCount;
    tempAdapter->setUnreadCount(unReadNum > 0 ? unReadNum : 0);
    if(tempAdapter->getUnreadCount() == 0){
        tempAdapter->setIsAtMe(false);
    }
    //手动置顶,状态
    tempAdapter->setTopSatus(ctn_session->topStatus);

    if (type == MSG_BIZ_SINGLECHAT){
        //单聊免打扰
        TableBaseVec tempTableBaseVec;
        QString feedId_passiveFeedId = myFeedId + toFeedId;
        TNDataControlServer::GetInstance()->Query(tempTableBaseVec, "BlackList",
            "feedId_passiveFeedId", feedId_passiveFeedId, DBTYPE_USER);
        if (!tempTableBaseVec.empty()){
            st_BlackListPtr blackList_ptr = std::dynamic_pointer_cast<st_BlackList>
                (tempTableBaseVec[0]);
            bNoAlarm = blackList_ptr->GetStatus();
        }
    }
    tempAdapter->setNoAlarm(bNoAlarm);
    tempAdapter->setToFeed(toFeedId);
    tempAdapter->setMyFeedId(myFeedId);
    //备注
    tempAdapter->setRemark(remark);
    //设置最后一条数据
    QString lastMsgId = QString(ctn_session->lastMsgId.c_str());
    setLastMsg(lastMsgId,tempAdapter);
    //////////////////////////////////
    readFeedUserId(toFeedId, tempAdapter);
    //从数据库读出会话的草稿
    tempAdapter->setDraft(QString(ctn_session->draft.c_str()));
    QString avatarFilePath;
    setAvatarPhoto(tempAdapter, avatarFilePath);
    if(!tempAdapter->isValid()){
        qInfo() << "[Notice] [NoticeListArea] slotAppendSessionTop adapter is not valid";
        qInfo() << "[Notice] [NoticeListArea] slotAppendSessionTop adapter sessionId:" <<
                tempAdapter->getSessionId() << " myFeedId:" << tempAdapter->getMyFeedId()
                << " toFeedId:" << tempAdapter->getToFeed() << " type:" << tempAdapter->getType();
    }
    return tempAdapter;
}

void NoticeListModel::setLastMsg(const QString &lastMsgId, TNMessageListAdapter *itemData)
{
    CTNMessage ctn_message = TNIMCoreClient::GetDBChat()->getMessage(itemData->getSessionId().toStdString().c_str(),lastMsgId.toStdString().c_str());
    if(!ctn_message.isEmpty() && ctn_message.status != 2){
        //1.5.0版本不能使用lastMsg的time是因为底层Im数据库处理xxxx退出群聊的消息有bug,会话表时间更新了,lastMsgId不更新.
        //itemData->setTime(ctn_message.timestamp);
        st_NoticeInfo notice_data;
        TNMsgData msg_data;//解析后得到数据
        switch (ctn_message.type){
        case MSG_BIZ_GROUPNOTIFY://社区通知
        case MSG_BIZ_NOTIFY://企业通知,小秘书
            TNIMNoticeProcessor::IMMessageCastToNotice(&ctn_message, notice_data);
            setSessionLastMsg(itemData, notice_data);
            break;
        case MSG_BIZ_SINGLECHAT:
        case MSG_BIZ_GROUPCHAT:
        case MSG_BIZ_SINGLECHAT_REVERT:
        case MSG_BIZ_GROUPCHAT_REVERT:
            TNIMCoreClient::IMMessageCastToData(ctn_message, msg_data);
            setSessionLastMsg((MESSAGE_TYPE)msg_data.type, itemData, msg_data);
            break;
        default:
            break;
        }
    }else{
        itemData->setLastMessage("");
    }
}


void NoticeListModel::readFeedUserId(const QString& feedID, TNMessageListAdapter* tempAdapter)
{
    TableBaseVec feedTableBaseVec;
    TNDataControlServer::GetInstance()->Query(feedTableBaseVec, "Feed", "feedId", feedID, DBTYPE_USER);
    for (TableBaseVec::iterator feedIter = feedTableBaseVec.begin();
        feedIter != feedTableBaseVec.end(); ++feedIter){
        st_FeedPtr feed = std::dynamic_pointer_cast<st_Feed>(*feedIter);
        tempAdapter->setUserId(feed->GetUserID());
    }
}

bool NoticeListModel::setAvatarPhoto(TNMessageListAdapter* itemData, QString& file_path)
{
    QString sessionId = itemData->getSessionId();
    QStringList sessionList = sessionId.split("_");
    QString sessionAvatarId;
    int type = itemData->getType();
    switch (type){
    case MSG_BIZ_SINGLECHAT:
    case MSG_BIZ_SINGLECHAT_REVERT:
        if (sessionList.size() == 4){
            QString one = sessionList[0] + "_" + sessionList[1];
            QString two = sessionList[2] + "_" + sessionList[3];
            if (one == itemData->getMyFeedId()){
                sessionAvatarId = two;
            }else{
                sessionAvatarId = one;
            }
        }
        break;
    case MSG_BIZ_GROUPCHAT:
    case MSG_BIZ_GROUPCHAT_REVERT:
    case MSG_BIZ_NOTIFY:
        sessionAvatarId = sessionId;
        break;
        default:
            break;
    }
	QString avatarFileName = TNPathUtil::getFeedAvatarPath(sessionAvatarId);
	if (sessionAvatarId.startsWith("gc_")){//群聊头像为原图
		avatarFileName += "_org";
	}
	itemData->setPhotoResID(avatarFileName);
	file_path = avatarFileName;
    return true;
}

void NoticeListModel::setSessionLastMsg(TNMessageListAdapter *adapter, const st_NoticeInfo &noticeInfo)
{
    adapter->setLastMessage(noticeInfo.summary);
}

void NoticeListModel::setSessionLastMsg(MESSAGE_TYPE type, TNMessageListAdapter* adapter,const TNMsgData &msgData)
{
    QString sender_name;
    bool isMySelf = msgData.bIsMyself;
    if(!isMySelf){
        //获取备注
        QString remark;
        if(adapter->getType() == MSG_BIZ_GROUPCHAT){
            remark = TNDataCache::GetInstance()->getFriendFeedReMark(msgData.from,adapter->getMyFeedId());
            sender_name = msgData.senderName;
            if(!remark.isEmpty()){
                sender_name = remark;
            }
        }
    }
    //////////////////////
    QString preMsg;
    if (!sender_name.isEmpty()){
        preMsg = sender_name + ":";
    }

    switch (type){
    case em_image:
        adapter->setLastMessage(preMsg + tr(DEFAULT_IMAGE_LAST_MESSAGE));
        break;
    case em_file:
        adapter->setLastMessage(preMsg + tr(DEFAULT_FILE_LAST_MESSAGE));
        break;
    case em_audio:
        adapter->setLastMessage(preMsg + tr(DEFAULT_AUDIO_LAST_MESSAGE));
        break;
    case em_video:
        adapter->setLastMessage(preMsg + tr(DEFAULT_VIDEO_LAST_MESSAGE));
        break;
    case em_text:
        adapter->setLastMessage(preMsg + msgData.data);
        break;
    case em_notsupport:
        adapter->setLastMessage(tr(NOTSUPPORT_TEXT));
        break;
    case em_red_card:
        adapter->setLastMessage(tr(RED_ENVELOPES));
        break;
    default:
        adapter->setLastMessage(msgData.data);
        break;
    }
}

Qt::ItemFlags NoticeListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;
    return TNTableModel::flags(index);
}

int NoticeListModel::prependData(TNMessageListAdapter adapter,
    TNMessageListAdapter **destData,
    bool isSelected,
    bool autoAddUnread,
    bool isSend,
    bool isBubble)
{
    Q_ASSERT(adapter.isValid());
    bool isManualOnTop = adapter.getTopStatus() > 0;
    if(isManualOnTop && adapter.getActive()) autoAddUnread = false;
    int index = 0;
    bool newSession = true;
    int insert_index = 0;//插入的位置
    int last_manualtop_index = 0;//最后一个手动选择置顶的位置
    TNMessageListAdapter *itemData = NULL;
    _mutex.lock();
    QList<TNModelItemBase*>::iterator itera = _listItemData.begin();
    for (; itera != _listItemData.end(); ++itera){
        itemData = static_cast<TNMessageListAdapter*>(*itera);
        if (itemData->getSessionId() == adapter.getSessionId()){
            newSession = false;
            itemData->setIsAtMe(adapter.getIsAtMe());
            if(!adapter.getLastMessage().isEmpty())
                itemData->setLastMessage(adapter.getLastMessage());
            itemData->setTime(adapter.getTime());
            if(isSelected){
                adapter.setBackStatus(TNMessageListAdapter::em_notice_list_select);
            }

            set_unread_active_status(adapter,itemData,isSelected,autoAddUnread,isSend,isBubble);
            _listItemData.erase(itera);
            //没有人工置顶的置顶
            if (itemData->getTopStatus() == 0 && index > 0){
                insert_index = last_manualtop_index;
            }
            break;
        }
        index++;
        if(itemData->getTopStatus() > 0){
            last_manualtop_index = index;
        }
    }
    _mutex.unlock();

    if (newSession){
        insert_index = last_manualtop_index;
        TNMessageListAdapter* newAdapter = new TNMessageListAdapter(adapter);
        bool bNoAlarm = getNoAlarm(newAdapter->getSessionId(),newAdapter->getMyFeedId(),
                                   newAdapter->getToFeed(),(TNBizType)newAdapter->getType());
        newAdapter->setNoAlarm(bNoAlarm);
        if(isSelected){
            newAdapter->setBackStatus(TNMessageListAdapter::em_notice_list_select);
        }
        //设置usrId
        if(newAdapter->getType() == MSG_BIZ_SINGLECHAT ||
                newAdapter->getType() == MSG_BIZ_SINGLECHAT_REVERT){
            QString toFeedId = newAdapter->getToFeed();
            st_FeedPtr tofeedInfo;
            TNUserDataHelper::GetInstance()->GetFeedInfo(toFeedId, tofeedInfo);
            if(tofeedInfo){
                newAdapter->setUserId(tofeedInfo->GetUserID());
            }
        }
        set_unread_active_status(adapter,newAdapter,isSelected,autoAddUnread,isSend,isBubble);
        //新的会话如果已经下载了头像设置头像
        QString file_path;
        setAvatarPhoto(newAdapter, file_path);
        beginInsertRows(QModelIndex(), insert_index, insert_index);
        insertAt(newAdapter, insert_index);
        endInsertRows();
        *destData = newAdapter;
    }else{
        //更新头像的机制,如果上次头像下载失败,当置顶时如果下载成功了重新设置
        QString file_path;
        setAvatarPhoto(itemData, file_path);
        if (isManualOnTop){//手动置顶
            itemData->setTopSatus(1);
            /*更新数据库将数据库topstatus赋值*/
            CTNSession ctn_session = TNIMCoreClient::GetDBChat()->getSession(itemData->getSessionId().toStdString().c_str());
            ctn_session.topStatus = itemData->getTopStatus();
            std::vector<CTNSession> ctn_sessions;
            ctn_sessions.push_back(ctn_session);
            if(!TNIMCoreClient::GetDBChat()->updateSession(ctn_sessions)){
                qInfo() << "[Notice][NoticeListModel] prependdata updateSession failed";
            }
            insert_index = 0;
            pushFront(itemData);
            if(index != 0){
                qInfo() << "[Notice] [NoticeListModel] prependdata beginmove src_index:" << index << "dst_index:0 line:" << __LINE__;
                beginMoveRows(QModelIndex(), index, index, QModelIndex(), 0);
                endMoveRows();
                qInfo() << "[Notice] [NoticeListModel] prependdata endmove line:" << __LINE__;
            }
        }else{
            insertAt(itemData, insert_index);
            if(index != insert_index){
                int model_move_index = insert_index;
                if(insert_index > index){
                    model_move_index += 1;
                }
                qInfo() << "[Notice] [NoticeListModel] prependdata beginmove src_index:" << index << "dst_index:" << model_move_index << "line:" << __LINE__;
                beginMoveRows(QModelIndex(),index,index,QModelIndex(),model_move_index);
                endMoveRows();
                qInfo() << "[Notice] [NoticeListModel] prependdata endmove line:" << __LINE__;
            }else{
                emit dataChanged(this->index(index,0),this->index(index,0));
            }
        }
        *destData = itemData;
    }
    //隐藏默认ListNotice背景
    emit showDefaultBack();
    ///////////////////////
    return insert_index;
}

void NoticeListModel::set_unread_active_status(const TNMessageListAdapter &adapter,
    TNMessageListAdapter *itemData,
    bool isSelected,
    bool autoAddUnread,
    bool isSend,
    bool isBubble)
{
    if(!isBubble){
        return;
    }
    bool isActive = adapter.getActive();
    //autoAddUnread为真则表示在线数据,且isSelected=false
    if (!isSelected && autoAddUnread && !isSend){
        //用于在线消息更新,会话未选中
        //如果不选中则total加1
        itemData->setUnreadCount(itemData->getUnreadCount() + 1);
        if (!itemData->getNoAlarm()){
            emit updateTotalUnread();
        }
    }else if(isSelected && autoAddUnread && !isSend && !isActive){
        //会话选中,在线消息且窗口处于未激活(即没有在消息界面)
        itemData->setActive(isActive);
        itemData->setUnreadCount(itemData->getUnreadCount() + 1);
        if (!itemData->getNoAlarm()){
            emit updateTotalUnread();
        }
    }else if(isSelected && !autoAddUnread && !isSend){
        //离线消息,选中会话,默认设置为未激活,会话未读条数过几秒后消失
        itemData->setActive(false);
        itemData->setUnreadCount(adapter.getUnreadCount());
        if (!itemData->getNoAlarm()){
            emit updateTotalUnread();
        }
    }else if (!autoAddUnread && !isSelected && !isSend){
        //离线消息,未选中，且不是自己发送的消息
        itemData->setUnreadCount(adapter.getUnreadCount());
    }
}

bool NoticeListModel::removeRowBySessionId(const QString &sessionId)
{
    if(sessionId.isEmpty()){
        return false;
    }
    TNMessageListAdapter* itemData = NULL;
    int index = findItemDataBySessionId(sessionId,&itemData);
    if(index == -1 || !itemData){
        return false;
    }
    //删除会话更新未读总条数
    if(itemData->getUnreadCount() > 0)
        emit updateTotalUnread();
    TNIMCoreClient::GetIMClient()->RemoveAndReadSession(sessionId);

    beginRemoveRows(QModelIndex(), index, index);
    _mutex.lock();
    delete _listItemData.at(index);
    _listItemData.removeAt(index);
    _mutex.unlock();
    endRemoveRows();
    return true;
}

int NoticeListModel::findItemDataBySessionId(const QString &sessionId,
                                                TNMessageListAdapter **itemData)
{
    int index = -1;
    _mutex.lock();
    for (int j = 0; j < _listItemData.size(); ++j){
        TNMessageListAdapter *findItemData = static_cast<TNMessageListAdapter*>(_listItemData.at(j));
        if (findItemData->getSessionId() == sessionId){
            //该条session会有更新
            index = j;
            *itemData = findItemData;
            break;
        }
    }
    _mutex.unlock();
    return index;
}

bool NoticeListModel::isTop(const TNMessageListAdapter &adapter,
    TNMessageListAdapter **topItemData,
    int &index,
    bool isSelected,
    bool autoAddUnread,
    bool isSend,
    bool isBubble)
{
    Q_ASSERT(adapter.isValid());
    bool isManualOnTop = adapter.getTopStatus() > 0;
    if(isManualOnTop && adapter.getActive())
        autoAddUnread = false;
    QMutexLocker locker(&_mutex);
    //置顶的会话
    if (isManualOnTop){
        int i = 0;
        QList<TNModelItemBase*>::const_iterator itera = _listItemData.begin();
        for (; itera != _listItemData.end(); ++itera){
            TNMessageListAdapter* itemData = static_cast<TNMessageListAdapter*>(*itera);
            if (adapter.getSessionId() == itemData->getSessionId()){
                itemData->setLastMessage(adapter.getLastMessage());
                itemData->setTime(adapter.getTime());
                itemData->setIsAtMe(adapter.getIsAtMe());
                if(isSelected) itemData->setBackStatus(TNMessageListAdapter::em_notice_list_select);
                set_unread_active_status(adapter,itemData,isSelected,autoAddUnread,isSend,isBubble);
                *topItemData = itemData;
                index = i;
                emit dataChanged(this->index(index,0),this->index(index,0));
                if(index  == 0){
                    return true;
                }else{
                    return false;
                }
            }
            i++;
        }
    }else{
        //没有置顶的会话
        for (int i = 0; i < _listItemData.size(); i++){
            TNMessageListAdapter* itemData = static_cast<TNMessageListAdapter*>
                (_listItemData.at(i));
            if (itemData->getTopStatus() == 0 &&
                itemData->getSessionId() == adapter.getSessionId()){
                if (!adapter.getLastMessage().isEmpty())
                    itemData->setLastMessage(adapter.getLastMessage());
                itemData->setTime(adapter.getTime());
                itemData->setIsAtMe(adapter.getIsAtMe());
                index = i;
                emit dataChanged(this->index(index,0),this->index(index,0));
                if (i > 0){
                    TNMessageListAdapter* pre_itemData = static_cast<TNMessageListAdapter*>
                        (_listItemData.at(i - 1));
                    if (pre_itemData->getTopStatus() > 0){
                        set_unread_active_status(adapter,itemData,isSelected,autoAddUnread,isSend,isBubble);
                        if(isSelected) itemData->setBackStatus(TNMessageListAdapter::em_notice_list_select);
                        *topItemData = itemData;
                        return true;
                    }
                }else if (i == 0){
                    set_unread_active_status(adapter,itemData,isSelected,autoAddUnread,isSend,isBubble);
                    if(isSelected) itemData->setBackStatus(TNMessageListAdapter::em_notice_list_select);
                    *topItemData = itemData;
                    return true;
                }
                return false;
            }
        }
    }
    return false;
}

void NoticeListModel::insertAt(TNMessageListAdapter* itemData, int index)
{
    _mutex.lock();
    _listItemData.insert(index, itemData);
    _mutex.unlock();
}

void NoticeListModel::pushFront(TNMessageListAdapter * itemData)
{
    _mutex.lock();
    _listItemData.push_front(itemData);
    _mutex.unlock();
}

bool NoticeListModel::getNoAlarm(const QString &sessionId,
    const QString &myFeedId, const QString &toFeedId, TNBizType type)
{
    bool bNoAlarm = false;//免打扰
    if (type == MSG_BIZ_GROUPCHAT){//群聊查群聊info
        TableBaseVec tempTableBaseVec;
        TNDataControlServer::GetInstance()->Query(tempTableBaseVec, "GroupInfo",
            "groupId", sessionId, DBTYPE_USER);
        if (!tempTableBaseVec.empty()){
            st_GroupInfoPtr groupInfo = std::dynamic_pointer_cast<st_GroupInfo>
                (tempTableBaseVec[0]);
            bNoAlarm = groupInfo->GetDisturbStatus();
        }
    }else if(type == MSG_BIZ_SINGLECHAT){
        //单聊免打扰
        TableBaseVec tempTableBaseVec;
        QString feedId_passiveFeedId = myFeedId + toFeedId;
        TNDataControlServer::GetInstance()->Query(tempTableBaseVec, "BlackList",
            "feedId_passiveFeedId", feedId_passiveFeedId, DBTYPE_USER);
        if (!tempTableBaseVec.empty()){
            st_BlackListPtr blackList_ptr = std::dynamic_pointer_cast<st_BlackList>
                (tempTableBaseVec[0]);
            bNoAlarm = blackList_ptr->GetStatus();
        }
    }
    return bNoAlarm;
}

void NoticeListModel::pushBack(TNMessageListAdapter* itemData)
{
    _mutex.lock();
    _listItemData.push_back(itemData);
    _mutex.unlock();
}

bool NoticeListModel::removeSession(const QString& sessionId, bool isSelect)
{
    bool flag = removeRowBySessionId(sessionId);
    if (flag){
        emit manualRemoveCurSession(sessionId, isSelect);
    }
    return flag;
}

void NoticeListModel::incrementUnreadCount(const QString &sessionId)
{
    QMutexLocker locker(&_mutex);
    for(int i=0; i < _listItemData.size(); i++){
        TNMessageListAdapter *itemData = static_cast<TNMessageListAdapter*>(_listItemData.at(i));
        if (itemData->getSessionId() == sessionId){
            int newCount = itemData->getUnreadCount() + 1;
            itemData->setUnreadCount(newCount);
            emit dataChanged(this->index(i,0),this->index(i,0));
            break;
        }
    }
}

void NoticeListModel::incrementalSession(const QString &sessionId)
{
    for (int j = 0; j < _listItemData.size(); ++j){
        TNMessageListAdapter *itemData = static_cast<TNMessageListAdapter*>(_listItemData.at(j));
        if (itemData->getSessionId() == sessionId){
            //该条session会有更新
            break;
        }
    }
    if(_outLineThread == NULL){
        _outLineThread = new TNOutLineMessageThread(this);
        qRegisterMetaType<TNMessageListAdapter>("TNMessageListAdapter");
        connect(_outLineThread,SIGNAL(main_view_operate(TNMessageListAdapter)),
                this,SLOT(onOutLineOperate(TNMessageListAdapter)));
        _outLineThread->start();
    }
    _outLineThread->push_outline_session(sessionId);
}

void NoticeListModel::setUnreadCount(const QModelIndex &index, int count)
{
    QMutexLocker locker(&_mutex);
    int row = index.row();
    if (row >= 0 && row < _listItemData.size())
    {
        TNMessageListAdapter *itemData = static_cast<TNMessageListAdapter*>(_listItemData.at(row));
        Q_ASSERT(itemData);
        itemData->setUnreadCount(count);
        emit dataChanged(index,index);
    }
}

int NoticeListModel::setSomeoneAtYou(const QString &sessionId, bool isAt)
{
    TNMessageListAdapter* itemData = NULL;
    int index = findItemDataBySessionId(sessionId,&itemData);
    if(index != -1 && itemData != NULL){
        itemData->setIsAtMe(isAt);
        emit dataChanged(this->index(index,0),this->index(index,0));
    }
    return index;
}

int NoticeListModel::setUnreadCount(const QString &sessionId, int count)
{
    int index = -1;
    QMutexLocker locker(&_mutex);
    for(int i=0; i < _listItemData.size();i++){
        TNMessageListAdapter *itemData = static_cast<TNMessageListAdapter*>
                (_listItemData.at(i));
        Q_ASSERT(itemData);
        if(itemData->getSessionId() == sessionId){
            itemData->setUnreadCount(count);
            index = i;
            emit dataChanged(this->index(index,0),this->index(index,0));
            break;
        }
    }
    return index;
}

int NoticeListModel::getUnreadCount(const QModelIndex &index)
{
    QMutexLocker locker(&_mutex);
    int row = index.row();
    if (row >= 0 && row < _listItemData.size())
    {
        TNMessageListAdapter *itemData = static_cast<TNMessageListAdapter*>(_listItemData.at(row));
        Q_ASSERT(itemData);
        return itemData->getUnreadCount();
    }
    return 0;
}

int NoticeListModel::getUnreadCount(const QString& sessionId)
{
    QMutexLocker locker(&_mutex);
    for(int i=0; i < _listItemData.size();i++){
        TNMessageListAdapter *itemData = static_cast<TNMessageListAdapter*>
                (_listItemData.at(i));
        Q_ASSERT(itemData);
        if(itemData->getSessionId() == sessionId){
            return itemData->getUnreadCount();
        }
    }
    return 0;
}

void NoticeListModel::incrementalSession(QStringList listSession)
{
    QTime time;
    time.start();
    int size = listSession.size();
    for (int i = 0; i < size; ++i){
        QString sessionId = listSession[i];
        incrementalSession(sessionId);
    }
    //notice 日志
    QString qs_log(QString("[Notice] [TNMessageListModel] incrementalSession take time:%1").arg(time.elapsed()));
    qInfo() << qs_log;
}

QList<TNMessageListAdapter> NoticeListModel::getSessionList() const
{
    QList<TNMessageListAdapter> results;
    foreach (TNModelItemBase *item, _listItemData){
        TNMessageListAdapter *adapter = static_cast<TNMessageListAdapter*>(item);
        results.append(*adapter);
    }
    return results;
}

TNMessageListAdapter* NoticeListModel::createNewSession(const QString& sessionId)
{
    CTNSession ctn_session = TNIMCoreClient::GetDBChat()->getSession(sessionId.toStdString().c_str());
    if(!ctn_session.isValid()){
        return NULL;
    }else{
        return createNewSession(&ctn_session);
    }
}

void NoticeListModel::updateAvatarPhoto(const QString& sessionId, const QString& file_path)
{
    if(!QFile::exists(file_path)){
        return;
    }
    TNMessageListAdapter *itemData = NULL;
    int index = -1;
    index = findItemDataBySessionId(sessionId,&itemData);
    if (index != -1 && itemData != NULL){
        itemData->setPhotoResID(file_path);
        emit dataChanged(this->index(index,0),this->index(index,0));
        QString qs_log = "[Notice] [TNMessageListModel] session list updateAvatarPhoto sessionId:" + sessionId + " file_path:" + file_path + " end";
        qInfo() << qs_log;
    }
}

TNMessageListAdapter* NoticeListModel::updateSessionName(const QString& sessionId, const QString& name)
{
    int index = -1;
    TNMessageListAdapter* itemData = NULL;
    index = findItemDataBySessionId(sessionId,&itemData);
    if(index != -1 && itemData != NULL){
        itemData->setName(name);
        emit dataChanged(this->index(index,0),this->index(index,0));
    }
    return itemData;
}

void NoticeListModel::onUpdateTotalUnread()
{
    int totalUnreaded = 0;
    for (int j = 0; j < _listItemData.size(); ++j){
        TNMessageListAdapter *itemData = static_cast<TNMessageListAdapter*>(_listItemData.at(j));
        if (!itemData->getNoAlarm()){
            totalUnreaded += itemData->getUnreadCount();
        }
    }
    //Notice日志
    QString qs_log = "[Notice] [TNMessageListModel] onUpdateTotalUnread \
        totalUnreaded:" + QString("%1").arg(totalUnreaded);
    qInfo() << qs_log;
    //通知menu界面更新未读条数
    emit messageNumberChanged(totalUnreaded);
}

void NoticeListModel::manulOnTopSession(QModelIndex q_index)
{
    TNMessageListAdapter* itemData = (TNMessageListAdapter*)data(q_index).toLongLong();
    if(itemData){
        itemData->setTopSatus(1);
        emit dataChanged(q_index,q_index);
    }
}

int NoticeListModel::manulCancelTopSession(QModelIndex q_index)
{
    TNMessageListAdapter *itemData = (TNMessageListAdapter*)this->data(q_index).toLongLong();
    Q_ASSERT(itemData);
    int index = q_index.row();
    int insert_index = -1;
    if (itemData != NULL && index != -1){
        itemData->setTopSatus(0);
        /*更新数据库将数据库topstatus赋值*/
        CTNSession ctn_session = TNIMCoreClient::GetDBChat()->getSession(itemData->getSessionId().toStdString().c_str());
        if(!ctn_session.isValid()){
            return insert_index;
        }
        ctn_session.topStatus = itemData->getTopStatus();
        std::vector<CTNSession> sessions;
        sessions.push_back(ctn_session);
        if(!TNIMCoreClient::GetDBChat()->updateSession(sessions)){
            qInfo() << "[Notice][NoticeListModel] manulCancelTopSession updateSession failed";
            return insert_index;
        }
        ///////////////////////////////////
        //插入正确的位置
        _mutex.lock();
        for (int j = 0; j < _listItemData.size(); ++j){
            TNMessageListAdapter *tempData = static_cast<TNMessageListAdapter*>
                (_listItemData.at(j));
            if(itemData->getSessionId() == tempData->getSessionId()){
                _listItemData.removeAt(j);
                break;
            }
        }
        for(int j=0; j < _listItemData.size();++j){
            TNMessageListAdapter *tempData = static_cast<TNMessageListAdapter*>
                (_listItemData.at(j));
            if (tempData->getTopStatus() == 0){
                if (itemData->getTime() > tempData->getTime() && itemData->getSessionId() != tempData->getSessionId()){
                    insert_index = j;
                    break;
                }
            }
        }
        _mutex.unlock();
        if(insert_index == index){
            insertAt(itemData, insert_index);
            return insert_index;
        }
        //插入中间
        if (insert_index != -1){
            int model_move_index = insert_index;
            if(insert_index > index){
                model_move_index += 1;
            }
            qInfo() << "[Notice] [NoticeListModel] manualcancel beginmove src_index:" << index << "dst_index:" << model_move_index << "line:" << __LINE__;
            beginMoveRows(QModelIndex(),index,index,QModelIndex(),model_move_index);
            insertAt(itemData, insert_index);
            endMoveRows();
            qInfo() << "[Notice] [NoticeListModel] manualcancel endmove line:" << __LINE__;
        }else{
            int model_move_index = _listItemData.size();
            if(model_move_index == index){
                pushBack(itemData);
            }else{
                if(model_move_index > index){
                    model_move_index += 1;
                }
                qInfo() << "[Notice] [NoticeListModel] manualcancel beginmove src_index:" << index << "dst_index:" << model_move_index << "line:" << __LINE__;
                beginMoveRows(QModelIndex(),index,index,QModelIndex(),model_move_index);
                pushBack(itemData);
                endMoveRows();
                qInfo() << "[Notice] [NoticeListModel] manualcancel endmove line:" << __LINE__;
            }
            insert_index = _listItemData.size() - 1;
        }
    }
    return insert_index;
}

void NoticeListModel::removeSession(QModelIndex q_index)
{
    TNMessageListAdapter *itemData = (TNMessageListAdapter*)this->data(q_index).toLongLong();
    Q_ASSERT(itemData);
    removeSession(itemData->getSessionId(),itemData->getBackStatus() == TNMessageListAdapter::em_notice_list_select);
}

void NoticeListModel::manulModifySessionName(const QString& session_id,const QString& name)
{
    TNMessageListAdapter* session = updateSessionName(session_id,name);
    Q_ASSERT(session);
    if(session->getBackStatus() == TNMessageListAdapter::em_notice_list_select){
        emit manualModifySessionName(session->getSessionId(), name);
    }
}

void NoticeListModel::manulSetSessionAlarm(QModelIndex q_index, bool noAlarm)
{
    TNMessageListAdapter* session = (TNMessageListAdapter*)this->data(q_index).toLongLong();
    Q_ASSERT(session);
    manulSetSessionAlarm(session->getSessionId(),noAlarm);
}

void NoticeListModel::manulSetSessionAlarm(const QString& sessionId, bool noAlarm)
{
    TNMessageListAdapter *itemData = NULL;
    int index = -1;
    _mutex.lock();
    for (int j = 0; j < _listItemData.size(); ++j){
        itemData = static_cast<TNMessageListAdapter*>(_listItemData.at(j));
        if (itemData->getSessionId() == sessionId){
            //该条session会有更新
            index = j;
            itemData->setNoAlarm(noAlarm);
            if (!noAlarm){
                //开启消息提醒总条数增加
                emit updateTotalUnread();
            }else{
                //开启消息免打扰总条数减少
                emit updateTotalUnread();
            }
            break;
        }
    }
    _mutex.unlock();
    if (index != -1 && itemData != NULL){
        emit manualNoAlarmNotifyTray(itemData->getSessionId(), noAlarm, itemData->getUnreadCount());
        emit dataChanged(this->index(index,0),this->index(index,0));
    }
}

bool NoticeListModel::updateActive(const QString &sessionId, bool isActive)
{
    TNMessageListAdapter* findItemData = NULL;
    int index = findItemDataBySessionId(sessionId,&findItemData);
    if(index != -1 && findItemData != NULL){
        findItemData->setActive(isActive);
        emit dataChanged(this->index(index,0),this->index(index,0));
    }
    return index != -1;
}

bool NoticeListModel::updateSessionByFeedId(const QString &feedId, const QString &avatorUrl, const QString &name)
{
    std::map<int,TNMessageListAdapter*> map_itemData;
    if(!findItemDataByFeedId(feedId,map_itemData)){
        return false;
    }
    for(std::map<int,TNMessageListAdapter*>::const_iterator itera = map_itemData.begin();
        itera != map_itemData.end();++itera){
        TNMessageListAdapter* findItemData = itera->second;
        int index = itera->first;
        Q_ASSERT(findItemData);
        findItemData->setAvatarPhotoUrl(avatorUrl);
        findItemData->setName(name);
        //更新数据库
        TNIMCoreClient::GetDBChat()->updateSessionTitleAndImage(
            findItemData->getSessionId().toStdString().c_str(),
            name.toStdString().c_str(),avatorUrl.toStdString().c_str());
        QString localPath;
        if(TNPathUtil::isDownloadedAvatarPhoto(feedId,localPath)){
            findItemData->setPhotoResID(localPath);
            emit dataChanged(this->index(index,0),this->index(index,0));
        }
    }
    return true;
}

void NoticeListModel::updateSessionUserIdByFeedId(const QString &feedId, const QString &userId)
{
    std::map<int,TNMessageListAdapter*> map_itemData;
    if(!findItemDataByFeedId(feedId,map_itemData)){
        return;
    }
    for(std::map<int,TNMessageListAdapter*>::const_iterator itera = map_itemData.begin();
        itera != map_itemData.end();++itera){
        TNMessageListAdapter* findItemData = itera->second;
        if(findItemData->getUserId() == userId){
            continue;
        }
        findItemData->setUserId(userId);
    }
}

void NoticeListModel::updateSessionAvatarByFeedId(const QString &feedId, const QString &avatorUrl)
{
    std::map<int,TNMessageListAdapter*> map_itemData;
    if(!findItemDataByFeedId(feedId,map_itemData)){
        return;
    }
    for(std::map<int,TNMessageListAdapter*>::const_iterator itera = map_itemData.begin();
        itera != map_itemData.end();++itera){
        int index = itera->first;
        TNMessageListAdapter* findItemData = itera->second;
        if(findItemData->getAvatarPhotoUrl() == avatorUrl){
            continue;
        }
        findItemData->setAvatarPhotoUrl(avatorUrl);
        findItemData->setPhotoResID("");
        emit dataChanged(this->index(index,0),this->index(index,0));
    }
}

void NoticeListModel::updateSessionAvatarBySessionId(const QString &sessionId, const QString &avatorUrl)
{
    TNMessageListAdapter* findItemData = NULL;
    int index = findItemDataBySessionId(sessionId, &findItemData);
    if(index != -1 && findItemData != NULL){
        if(findItemData->getAvatarPhotoUrl() == avatorUrl){
            return;
        }
        findItemData->setAvatarPhotoUrl(avatorUrl);
        findItemData->setPhotoResID("");
        emit dataChanged(this->index(index,0),this->index(index,0));
    }
}

void NoticeListModel::onOutLineOperate(TNMessageListAdapter session)
{
    //根据当前选择的名片判断离线会话是否显示
    QString currentFeedid = TNDataCache::GetInstance()->GetCurrentMyFeed();
    if(currentFeedid != AVATAR_ALL_FEED && currentFeedid != session.getMyFeedId()){
        return;
    }
    TNMessageListAdapter* findItemData = NULL;
    int index  = findItemDataBySessionId(session.getSessionId(),&findItemData);
    int insert_index = -1;
    if(index == -1 && !findItemData){
        TNMessageListAdapter* destData = NULL;
        insertSort(session, &destData, insert_index);
        if (destData != NULL){
            emit outlineUpdateUnread(destData->getMyFeedId(), 1, session.getType());
            if (session.getNoAlarm() && !session.getIsAtMe()){
                return;
            }
            emit outlineUpdateUnreadTray(session, session.getUnreadCount());
        }
    }else{
        if(index == -1 || findItemData == NULL){
            return;
        }
        bool bSelected = false;
        findItemData->setIsAtMe(session.getIsAtMe());
        bSelected = (findItemData->getBackStatus() == TNMessageListAdapter::em_notice_list_select);
        if(bSelected){
            *findItemData = session;
            emit reSelectOutLine(*findItemData, bSelected, false, false, false,true);
            emit reLoadDetailsModel(findItemData);
        }else{
            *findItemData = session;
            moveSort(findItemData,index,insert_index);
            //更新最外层的名片红点信号,根据当前用户会话更新
            emit outlineUpdateUnread(session.getMyFeedId(), 1, session.getType());
            if (session.getNoAlarm() && !session.getIsAtMe()){
                return;
            }
            emit outlineUpdateUnreadTray(session, session.getUnreadCount());
        }
    }
    //更新总会话
    emit updateTotalUnread();
    //隐藏默认背景信号
    emit showDefaultBack();
}

void NoticeListModel::setAllSessionReaded()
{
    _mutex.lock();
    for (int j = 0; j < _listItemData.size(); ++j){
        TNMessageListAdapter *findItemData = static_cast<TNMessageListAdapter*>(_listItemData.at(j));
        findItemData->setUnreadCount(0);
        emit dataChanged(this->index(j,0),this->index(j,0));
    }
    _mutex.unlock();
    QTime cur_time;
    cur_time.start();
    for (int j = 0; j < _listItemData.size(); ++j){
        TNMessageListAdapter *findItemData = static_cast<TNMessageListAdapter*>(_listItemData.at(j));
        TNIMCoreClient::GetIMClient()->ReadSession(findItemData->getSessionId());
    }
    qInfo() << "[Notice] [TNMessageListModel] setAllSessionReaded take time:" << cur_time.elapsed();
}

int NoticeListModel::getScropUnReadItem(int latestItem)
{
    QMutexLocker locker(&_mutex);
    int index = -1;
    for (int j = latestItem+1; j < _listItemData.size(); ++j){
        TNMessageListAdapter *findItemData = static_cast<TNMessageListAdapter*>(_listItemData.at(j));
        if (findItemData->getUnreadCount() >0 && !findItemData->getNoAlarm()){
            index = j;
            break;
        }
    }
    return index;
}

void NoticeListModel::moveSort(TNMessageListAdapter *itemData,int src_index, int &dst_index)
{
    Q_ASSERT(itemData->isValid());
    //插入正确的位置
    dst_index = -1;
    _mutex.lock();
    _listItemData.removeAt(src_index);
    for (int j = 0; j < _listItemData.size(); ++j){
        TNMessageListAdapter *tempData = static_cast<TNMessageListAdapter*>
                        (_listItemData.at(j));
        if(tempData->getSessionId() == itemData->getSessionId()){
            continue;
        }
        if(itemData->getTopStatus() > 0){//置顶
            if(itemData->getTime() > tempData->getTime() &&
                    tempData->getTopStatus() > 0){
                dst_index = j;
                break;
            }else if(itemData->getTime() <= tempData->getTime()
                     && tempData->getTopStatus() > 0){
                continue;
            }else{
                dst_index = j;
                break;
            }
        }else{
            if (itemData->getTime() > tempData->getTime()
                    && tempData->getTopStatus() == 0){
                dst_index = j;
                break;
            }
        }
    }
    _mutex.unlock();
    if(dst_index == src_index){
        insertAt(itemData, dst_index);
        emit dataChanged(this->index(dst_index,0),this->index(dst_index,0));
        return;
    }
    //插入中间
    if (dst_index != -1){
        int model_move_index = dst_index;
        if(dst_index > src_index){
            model_move_index += 1;
        }
        qInfo() << "[Notice] [NoticeListModel] movesort beginmove src_index:" << src_index << "dst_index:" << model_move_index << "line:" << __LINE__;
        beginMoveRows(QModelIndex(),src_index,src_index,QModelIndex(),model_move_index);
        insertAt(itemData, dst_index);
        endMoveRows();
        qInfo() << "[Notice] [NoticeListModel] movesor endmove line:" << __LINE__;
    }else{
        int model_move_index = _listItemData.size();
        if(model_move_index == src_index){
            pushBack(itemData);
            emit dataChanged(this->index(model_move_index,0),this->index(model_move_index,0));
        }else{
            if(model_move_index > src_index)
                model_move_index += 1;
            qInfo() << "[Notice] [NoticeListModel] movesort beginmove src_index:" << src_index << "dst_index:" << model_move_index << "line:" << __LINE__;
            beginMoveRows(QModelIndex(),src_index,src_index,QModelIndex(),model_move_index);
            pushBack(itemData);
            endMoveRows();
            qInfo() << "[Notice] [NoticeListModel] movesort endmove line:" << __LINE__;
        }
        dst_index = _listItemData.size() - 1;
    }
}

void NoticeListModel::insertSort(const TNMessageListAdapter &session,
                                    TNMessageListAdapter** itemData,
                                    int &insert_index)
{
    Q_ASSERT(session.isValid());
    *itemData = new TNMessageListAdapter(session);
    //插入正确的位置
    insert_index = -1;
    _mutex.lock();
    for (int j = 0; j < _listItemData.size(); ++j){
        TNMessageListAdapter *tempData = static_cast<TNMessageListAdapter*>
                        (_listItemData.at(j));
        if((*itemData)->getTopStatus() > 0){//置顶
            if((*itemData)->getTime() > tempData->getTime() &&
                    tempData->getTopStatus() > 0){
                insert_index = j;
                break;
            }else if((*itemData)->getTime() <= tempData->getTime()
                     && tempData->getTopStatus() > 0){
                continue;
            }else{
                insert_index = j;
                break;
            }
        }else{
            if ((*itemData)->getTime() > tempData->getTime()
                    && tempData->getTopStatus() == 0){
                insert_index = j;
                break;
            }
        }
    }
    _mutex.unlock();
    //插入中间
    if (insert_index != -1){
        beginInsertRows(QModelIndex(), insert_index, insert_index);
        insertAt(*itemData, insert_index);
        endInsertRows();
    }else{
        beginInsertRows(QModelIndex(), _listItemData.size(), _listItemData.size());
        pushBack(*itemData);
        endInsertRows();
        insert_index = _listItemData.size() - 1;
    }
}

void NoticeListModel::on_notifyCurrentFeedChanged(const QString &feedId)
{
    init_data(feedId);
}

void NoticeListModel::setBackStatus(const QString &session_id, TNMessageListAdapter::Back_Status status)
{
    TNMessageListAdapter* itemData = NULL;
    int index = findItemDataBySessionId(session_id,&itemData);
    if(index != -1 && itemData != NULL){
        itemData->setBackStatus(status);
        emit dataChanged(this->index(index,0),this->index(index,0));
    }
}

void NoticeListModel::setSessionUnSelected(const QString &session_id)
{
    setBackStatus(session_id,TNMessageListAdapter::em_notice_list_normal);
}

void NoticeListModel::updateRemark(const QString &sessionId, const QString &remark)
{
    TNMessageListAdapter* item_data = NULL;
    int index = findItemDataBySessionId(sessionId,&item_data);
    if(index != -1 && item_data != NULL){
        item_data->setRemark(remark);
        emit dataChanged(this->index(index,0),this->index(index,0));
    }
}

void NoticeListModel::on_notifyReMarkUpdate(const QString &from, const QString &to, const QString &remark, int sources)
{
    QString session_id = TNIMCoreClient::GetSessionId(from,to,MSG_BIZ_SINGLECHAT);
    updateRemark(session_id,remark);
}

void NoticeListModel::on_notifyOrgCommunicationStatus(const QString &feedId, const QString &status)
{
    if(status == "0"){//不可沟通
        std::map<int,TNMessageListAdapter*> map_itemData;
        if(!findItemDataByFeedId(feedId,map_itemData)){
            return;
        }
        for(std::map<int,TNMessageListAdapter*>::const_iterator itera = map_itemData.begin();
            itera != map_itemData.end();++itera){
            TNMessageListAdapter* itemData = itera->second;
            Q_ASSERT(itemData);
            removeSession(itemData->getSessionId(),itemData->getBackStatus() == TNMessageListAdapter::em_notice_list_select);
        }
    }
}

void NoticeListModel::updateLastMsg(const QString &sessionId)
{
    TNMessageListAdapter* itemData = NULL;
    int index = findItemDataBySessionId(sessionId, &itemData);
    if(index == -1 || itemData == NULL){
        return;
    }
    CTNSession ctn_session = TNIMCoreClient::GetDBChat()->getSession(sessionId.toStdString().c_str());
    if(ctn_session.isValid()){
        //最后一条消息更新
        QString lastMsgId = QString(ctn_session.lastMsgId.c_str());
        //最后一条时间更新
        setLastMsg(lastMsgId, itemData);
        emit dataChanged(this->index(index,0), this->index(index,0));
    }
}

bool NoticeListModel::findItemDataByFeedId(const QString &feedId, std::map<int, TNMessageListAdapter *> &map_itemData)
{
    int index = -1;
    _mutex.lock();
    for (int j = 0; j < _listItemData.size(); ++j){
        TNMessageListAdapter *findItemData = static_cast<TNMessageListAdapter*>(_listItemData.at(j));
        if (findItemData->getToFeed() == feedId){
            //该条session会有更新
            index = j;
            map_itemData[index] = findItemData;
        }
    }
    _mutex.unlock();
    return index != -1;
}
