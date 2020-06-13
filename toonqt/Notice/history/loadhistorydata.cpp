#include "loadhistorydata.h"
#include "details_notice/TNMsgDetailModel.h"
#include "TNDataControlServer.h"
#include "TNIMCoreClient.h"
#include "TNMessageListAdapter.h"
#include "TNPathUtil.h"
#include "details_notice/NoticeDetailsArea.h"
#include "TNUserDataHelper.h"
#include "TNMsgDetailModel.h"
#include "TNDataCache.h"
#include "CTNDBHeader.h"
#include "CTNDBAPI.h"
#include <QApplication>
#include <QDir>

LoadHistoryData::LoadHistoryData(TNMsgDetailModel* msgModel,
                                         NoticeDetailsArea* noticeDetail) : _msgModel(msgModel)
, _noticeDetailArea(noticeDetail)
, _currentAdapter(NULL)
, _bIsLastPageLocal(false)
{

}


LoadHistoryData::~LoadHistoryData()
{
}

void LoadHistoryData::readCurrentSession(TNMessageListAdapter* currentAdapter, unsigned int num)
{
    Q_ASSERT(currentAdapter);
	if (_msgModel == NULL || _noticeDetailArea == NULL)
		return;
	_bIsLastPageLocal = false;
	_currentAdapter = currentAdapter;
	_currentSessionId = currentAdapter->getSessionId();
    _startMsgId = "";//每次切换会话后开始位置质空
    //展示数据,第一次读取数据
    AppandPageMsg("",num);
}

int LoadHistoryData::readCurrentSessionMore(unsigned int num,
                                                 bool isJump)
{
    Q_ASSERT(_msgModel);
    Q_ASSERT(_noticeDetailArea);
    Q_ASSERT(_currentAdapter);
    //展示数据
    return AppandPageMsg(_startMsgId,num,isJump);
}

int LoadHistoryData::AppandPageMsg(const QString& firstMsgId,
                                        unsigned int num,
                                        bool isJump)
{
    Q_ASSERT(_msgModel);
    Q_ASSERT(_noticeDetailArea);
    Q_ASSERT(_currentAdapter);

    toonim::CTNMessage first_message;
    if(!firstMsgId.isEmpty()){
        first_message = TNIMCoreClient::GetDBChat()->getMessage(
                _currentSessionId.toStdString().c_str(),
                firstMsgId.toStdString().c_str());
    }
    vector<toonim::CTNMessage> messages = TNIMCoreClient::GetDBChat()->getMessages(
                _currentSessionId.toStdString().c_str(),first_message.seqId,num);
    //当前最后一页
    if (messages.size() < num)
        _bIsLastPageLocal = true;
    else
        _bIsLastPageLocal = false;
    int show_num = produceHistoryData(messages);
    emit AppandPageFinished(CurrentIsLastPage(),show_num,isJump);
    return show_num;
}

int LoadHistoryData::produceHistoryData(const std::vector<toonim::CTNMessage>& messages)
{
    if(messages.size() > 0){
        _startMsgId = QString(messages[0].msgId.c_str());
    }
    for(toonim::CTNMessage ctn_message : messages){
        TNModelUserMessage *message = new TNModelUserMessage;

        TNMsgData data;//解析后得到数据
        TNIMCoreClient::IMMessageCastToData(ctn_message, data);
        //消息数据过滤
        if (!data.bShow || ((data.bizType == MSG_BIZ_GROUPCHAT_REVERT ||
            data.bizType  == MSG_BIZ_SINGLECHAT_REVERT) && data.data.isEmpty())){
            delete message;
            continue;
        }
        message->setSessionId(_currentSessionId);
        //判断消息是否自己发送
        message->setSessionType((MSG_BIZ_TYPE)_currentAdapter->getType());
        if (!data.bIsMyself){
            message->setMessageSendFrom(GROUP_MESSAGE_TYPE_OTHER);
        }else{
            message->setMessageSendFrom(GROUP_MESSAGE_TYPE_CURRENT_ACCOUNT);
        }
        if (_currentAdapter->getType() == MSG_BIZ_SINGLECHAT ||
                _currentAdapter->getType() ==MSG_BIZ_SINGLECHAT_REVERT){
            if (!data.bIsMyself){
                message->setMyFeedId(data.to);
            }else{
                message->setMyFeedId(data.from);
            }
            message->setToFeedId(data.to);
            message->setFromId(data.from);
        }else if (_currentAdapter->getType() == MSG_BIZ_GROUPCHAT ||
                  _currentAdapter->getType() == MSG_BIZ_GROUPCHAT_REVERT){
            TableBaseVec groupTableBaseVec;
            QString groupId = _currentAdapter->getSessionId();
			TNDataControlServer::GetInstance()->Query(groupTableBaseVec, "GroupInfo", "groupId", groupId, DBTYPE_USER);
            if (groupTableBaseVec.size() != 0){
                st_GroupInfoPtr groupInfo = std::dynamic_pointer_cast<st_GroupInfo>(*groupTableBaseVec.begin());
                message->setMyFeedId(groupInfo->GetMyFeedId());
                message->setToFeedId(groupId);
                message->setFromId(data.from);
            }
        }
        message->setUserId(data.toUserId);
        // 获取头像
        QString feedId = data.from;
        QString avatarFileName = TNPathUtil::getFeedAvatarPath(feedId);
        message->SetPhotoIcon(avatarFileName);
        st_FeedPtr feedInfo;
        TNUserDataHelper::GetInstance()->GetFeedInfo(feedId, feedInfo);
        if (feedInfo){
            message->setAvatorUrl(feedInfo->GetAvatarID());
            message->SetFeedName(feedInfo->GetTitle());
        }
        qlonglong timeLong = (qlonglong)data.timestmp * 1000;
        QDateTime date_time = QDateTime::fromMSecsSinceEpoch(timeLong);
        message->setTime(date_time);
        message->SetMsgID(data.msgId);
        message->setMsgStatus(data.status);
        message->setMsgFileStatus(data.fileStatus);
        //格式化收到的信息,替换一些特殊字符
        QString t = data.data;
        QChar *ub = t.data(), *uc = ub, *ue = uc + t.size();
        for (; uc != ue; ++uc) {
            switch (uc->unicode()) {
            case 0xfdd0: // QTextBeginningOfFrame
            case 0xfdd1: // QTextEndOfFrame
            case QChar::ParagraphSeparator:
            case QChar::LineSeparator: {
                *uc = QLatin1Char('\n');
            } break;
            case QChar::Nbsp:
            case QChar::Null:{
                *uc = QLatin1Char(' ');
            } break;
            case QChar::LineFeed:
                break;
            case QChar::ObjectReplacementCharacter:
                *uc = QLatin1Char(' ');
                break;
            }
        }
        //历史记录全为已经发送的数据或者接收的数据
        message->SetUserMessage(t);
        QString localPath(data.localPath);
        switch (data.type){
        case MSG_TYPE_TEXT:
            message->SetMessageType(em_text);
            if (message->getMsgStatus() != MSG_STATUS_SEND_SUC){//对于不成功的文字数据只存在发送不成功
                message->setMsgSendOrRecv(MESSAGE_SEND);
            }
            break;
        case MSG_TYPE_IMG:
            message->SetMessageType(em_image);
            message->setPicSize(QSize(data.w, data.h));
            //图片对于加载历史记录来说全是接收,从服务器下载
            if(message->getMsgStatus() != MSG_STATUS_SEND_SUC){
                message->setMsgSendOrRecv(MESSAGE_SEND);
            }else{
                switch(message->getMsgFileStatus()){
                case MSG_STATUS_FILE_DOWNLOADING:
                case MSG_STATUS_FILE_DOWN_FAIL:
                case MSG_STATUS_FILE_UNDOWN:
                case MSG_STATUS_FILE_SUC:
                    message->setMsgSendOrRecv(MESSAGE_RECV);
                    break;
                case MSG_STATUS_FILE_UPLOADING:
                case MSG_STATUS_FILE_UPLOAD_FAIL:
                    message->setMsgSendOrRecv(MESSAGE_SEND);
                    break;
                default:
                    break;
                }
            }
            message->setFileSuffix(data.format);
            isFileDownloaded(data.msgId,localPath);
            message->setFileLocalPath(localPath);
            break;
        case MSG_TYPE_ATTACHMENT:
            message->SetMessageType(em_file);
            if(message->getMsgStatus() != MSG_STATUS_SEND_SUC){
                message->setMsgSendOrRecv(MESSAGE_SEND);
                message->setFileLocalPath(localPath);
            }else{
                switch(message->getMsgFileStatus()){
                case MSG_STATUS_FILE_DOWNLOADING:
                case MSG_STATUS_FILE_DOWN_FAIL:
                case MSG_STATUS_FILE_UNDOWN:
                    message->setMsgSendOrRecv(MESSAGE_RECV);
                    break;
                case MSG_STATUS_FILE_UPLOADING:
                case MSG_STATUS_FILE_UPLOAD_FAIL:
                    message->setMsgSendOrRecv(MESSAGE_SEND);
                    break;
                case MSG_STATUS_FILE_SUC:
                    if (localPath.isEmpty() || !QFile::exists(localPath)){//本地没有
                        message->setMsgSendOrRecv(MESSAGE_RECV);//该条文件需要下载
                    }else{
                        message->setMsgSendOrRecv(MESSAGE_RECV);//该条文件需要下载
                        message->setFileLocalPath(localPath);
                    }
                    break;
                default:
                    break;
                }
            }
            message->setFileName(data.desc);
            message->setFileSuffix(data.format);
            message->setFileSize(data.size);
            break;
        case MSG_TYPE_VIDEO://视屏
            message->SetMessageType(em_video);
            if(message->getMsgStatus() != MSG_STATUS_SEND_SUC){
                message->setMsgSendOrRecv(MESSAGE_SEND);
                message->setFileLocalPath(localPath);
            }else{
                switch(message->getMsgFileStatus()){
                case MSG_STATUS_FILE_DOWNLOADING:
                case MSG_STATUS_FILE_DOWN_FAIL:
                case MSG_STATUS_FILE_UNDOWN:
                    message->setMsgSendOrRecv(MESSAGE_RECV);
                    break;
                case MSG_STATUS_FILE_UPLOADING:
                case MSG_STATUS_FILE_UPLOAD_FAIL:
                    message->setMsgSendOrRecv(MESSAGE_SEND);
                    break;
                case MSG_STATUS_FILE_SUC:
                    if (localPath.isEmpty() || !QFile::exists(localPath)){//本地没有
                        message->setMsgSendOrRecv(MESSAGE_RECV);//该条文件需要下载
                    }else{
                        message->setMsgSendOrRecv(MESSAGE_RECV);//该条文件需要下载
                        message->setFileLocalPath(localPath);
                    }
                    break;
                default:
                    break;
                }
            }
            message->setFileName(data.desc);
            message->setFileSuffix(data.format);
            message->setFileSize(data.size);
            break;
        case MSG_TYPE_VOICE://音频
            //音频只能接收
            message->setMsgSendOrRecv(MESSAGE_RECV);
            message->SetMessageType(em_audio);
            message->setAudioTime(data.time);//音频时长
            if (isAudioDownloaded(data.msgId, localPath)){
                message->setFileLocalPath(localPath);
            }
            break;
        case MSG_TYPE_NOTICE://通知(群聊)
            message->SetMessageType(em_groupchat_notice);
            break;
        case MSG_TYPE_OTHER:
            message->SetMessageType(em_notsupport);
            break;
        case MSG_TYPE_RED_CARD:
            message->SetMessageType(em_red_card);
            break;
        default:
            break;
        }
        //备注
        if(_currentAdapter->getType() == MSG_BIZ_GROUPCHAT){
            QString remark = TNDataCache::GetInstance()->getFriendFeedReMark(message->getFromId(), message->getMyFeedId());
            message->setRemark(remark);
        }
        //先插model创建界面
        _list_msg.push_front(message);
        //如果这条消息名片不存在则在界面创建一条名片不存在的提示消息(离线)
        if(message->getMsgStatus() == MSG_STATUS_SEND_FAIL_Card){
            TNModelUserMessage *card_no_message = new TNModelUserMessage;
            card_no_message->SetUserMessage(("名片不存在"));
            card_no_message->SetMessageType(em_card_not_exist);
            card_no_message->setTime(message->getTime());
            _list_msg.push_front(card_no_message);
        }else if(message->getMsgStatus() == MSG_STATUS_SEND_FAIL_CoCard){
            TNModelUserMessage *card_no_message = new TNModelUserMessage;
            card_no_message->SetUserMessage(("该名片未被使用，暂时无法沟通"));
            card_no_message->SetMessageType(em_card_not_exist);
            card_no_message->setTime(message->getTime());
            _list_msg.push_front(card_no_message);
        }else if(message->getMsgStatus() == MSG_STATUS_SEND_FAIL_OrCard){
            TNModelUserMessage *card_no_message = new TNModelUserMessage;
            card_no_message->SetUserMessage(("该名片不支持聊天"));
            card_no_message->SetMessageType(em_card_not_exist);
            card_no_message->setTime(message->getTime());
            _list_msg.push_front(card_no_message);
        }
    }
    _msgModel->insertData(0, _list_msg);
    int show_num = _list_msg.size();
    _list_msg.clear();
    return show_num;
}

bool LoadHistoryData::isFileDownloaded(const QString& msgId,QString& localPath)
{
	if (msgId.isEmpty())
		return false;
	QString picPath = TNPathUtil::getUserRecFile() + msgId;
	picPath.replace("//", "/");
	QDir dir;
	if (dir.exists(picPath)){
		localPath = picPath;
		return true;
	}
	return false;
}

bool LoadHistoryData::isAudioDownloaded(const QString& msgId, QString& localPath)
{
	if (msgId.isEmpty())
		return false;
	QString picPath = TNPathUtil::getUserRecFile() + msgId + ".wav";
	picPath.replace("//", "/");
	QDir dir;
	if (dir.exists(picPath)){
		localPath = picPath;
		return true;
	}
	return false;
}

bool LoadHistoryData::CurrentIsLastPage()
{
	return _bIsLastPageLocal;
}

void LoadHistoryData::readDataJump(int num)
{
    if (_msgModel == NULL || _noticeDetailArea == NULL)
        return;
    Q_ASSERT(num > 0);
    toonim::CTNMessage last_message = TNIMCoreClient::GetDBChat()->getLastMessage(_currentSessionId.toStdString().c_str());
    std::vector<toonim::CTNMessage> messages = TNIMCoreClient::GetDBChat()->getMessages(_currentSessionId.toStdString().c_str(),
                last_message.seqId,num);

    messages.push_back(last_message);
    int show_num = produceHistoryData(messages);
    emit AppandPageFinished(false,show_num,true);
}

void LoadHistoryData::readDataJump(const QString &firstUnreadMsgId)
{
    if (_msgModel == NULL || _noticeDetailArea == NULL)
        return;
    TNModelUserMessage* itemData = (TNModelUserMessage*)_msgModel->data(_msgModel->index(0,0)).toLongLong();
    Q_ASSERT(itemData);
    toonim::CTNMessage last_message = TNIMCoreClient::GetDBChat()->getMessage(_currentSessionId.toStdString().c_str(),itemData->GetMsgID().toStdString().c_str());
    toonim::CTNMessage end_message = TNIMCoreClient::GetDBChat()->getMessage(
                _currentSessionId.toStdString().c_str(),
                firstUnreadMsgId.toStdString().c_str());
    Q_ASSERT(!last_message.isEmpty() && !end_message.isEmpty());
    std::vector<toonim::CTNMessage> messages;
    int num = qAbs(last_message.seqId - end_message.seqId);
    messages = TNIMCoreClient::GetDBChat()->getMessages(_currentSessionId.toStdString().c_str(),
                last_message.seqId,num);
    int show_num = produceHistoryData(messages);
    emit AppandPageFinished(false,show_num,true);
}

QString LoadHistoryData::getFirstUnreadMsg(const QString &sessionId, int num)
{
    Q_ASSERT(!sessionId.isEmpty());
    if(num <= 0){
        return "";
    }
    std::vector<toonim::CTNMessage> messages = TNIMCoreClient::GetDBChat()->getMessages(sessionId.toStdString().c_str(),0,num);
    if(messages.size() <= 0){
        return "";
    }else{
        return QString(messages[0].msgId.c_str());
    }
}
