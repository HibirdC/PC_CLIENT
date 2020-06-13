#include "tngeneratenoticemodeldata.h"
#include "TNModelUserMessage.h"
#include "TNIMCoreClient.h"
#include "TNMessageListAdapter.h"
#include "TNPathUtil.h"
#include "TNDataControlServer.h"
#include "TNUserDataHelper.h"
#include "tnimagectr.h"
#include "TNDataCache.h"
#include "CTNDBHeader.h"
#include <QFileInfo>
#include <QApplication>
#include <QImageReader>
#include <QUuid>

#define  MAX_FILE_SIZE    60 * 1024 * 1024

TNGenerateNoticeModelData::TNGenerateNoticeModelData(
	QObject *parent /* = 0 */)
	: QObject(parent)
{

}

TNGenerateNoticeModelData::~TNGenerateNoticeModelData()
{

}

TNModelUserMessage* TNGenerateNoticeModelData::generateSendMsg(MESSAGE_TYPE type, 
    QString content, bool bSended, TNMessageListAdapter* curSession, int atType, QList<QString> atFeeds
    )
{
    //notice 日志
    qInfo() << "[Notice] [TNGenerateNoticeModelData] generateSendMsg start ";

	TNModelUserMessage *message = new TNModelUserMessage;
	message->SetMessageType(type);
	message->setSessionId(curSession->getSessionId());
	message->setMsgSendOrRecv(MESSAGE_SEND);
	message->SetMsgID(TNIMCoreClient::GetMsgId());
	QString myFeedId = curSession->getMyFeedId();
	message->setMyFeedId(myFeedId);
	message->setFromId(myFeedId);
	QString toFeedId = curSession->getToFeed();
	message->setToFeedId(toFeedId);
	message->setSessionType((TNBizType)curSession->getType());
	if (curSession->getType() == MSG_BIZ_SINGLECHAT || curSession->getType() == MSG_BIZ_SINGLECHAT_REVERT){//单聊
        QString usrId = curSession->getUserId();
        message->setUserId(usrId);
	}

	switch (type)
	{
	case em_text:
		message->SetUserMessage(content);
		break;
	case em_image:
	{
        qInfo() << "[Notice] [generateSendMsg] content:" << content;
		QFileInfo file_info(content);
        message->setFileName(file_info.fileName());
        message->setFileSuffix(TNImageCtr::getImageTypeRetString(content));
        //图片发送先拷贝到程序存储图片的位置,拷贝一张原图,然后生成一张缩略图
        QFile file(content);
        QString uuid = QUuid::createUuid().toString();
        QString savePath = TNPathUtil::getUserRecFile() + uuid;
        QString savePath_org = savePath + "_org";
        if(file.copy(savePath_org))
            content = savePath_org;
        //生成缩略图
        bool is_scale = false;
        if(message->getFileSuffix() != ".gif"){
            QImage image;
            QSize image_size(200,200);
            if(TNImageCtr::speedLoadImage(content,true,image,image_size,message->getFileSuffix())){
                QString suffix = message->getFileSuffix();
                Q_ASSERT(suffix.size() > 1);
                suffix = suffix.mid(1);
                if(image.save(savePath,suffix.toStdString().c_str())){
                    content = savePath;
                    message->setFileLocalPath(content);
                    message->setPicSize(image_size);
                    is_scale = true;
                }
            }
        }else{
            QImageReader file_image(content,message->getFileSuffix().toStdString().c_str());
            if (file_image.canRead()){
                message->setPicSize(QSize(file_image.size().width(), file_image.size().height()));
                message->setFileLocalPath(content);
                is_scale = true;
            }
        }
        qInfo() << "[Notice] [generateSendMsg] content:" << content;
        if(!is_scale){
            //notice 日志
            QString qs_log = "[Notice] [TNGenerateNoticeModelData] load image failed, msgId:" + message->GetMsgID();
            qCritical() << qs_log;
            delete message;
            return NULL;
        }
	}
	break;
	case em_file:
	{
		message->setFileLocalPath(content);
		QFileInfo file_info(content);
		QString file_name = file_info.fileName();
		QString file_suffix = file_info.suffix();
		qint64  file_size = file_info.size();

        if (file_size > MAX_FILE_SIZE || file_size <= 0){
            //notice 日志
            QString qs_log = "[Notice] [TNGenerateNoticeModelData] TNModelUserMessage::generateSendMsg file size > 60MB, msgId:" + message->GetMsgID();
            qInfo() << qs_log;
            QString content = ("发送的文件大小不能大于60MB且不能为0");
            emit maxFileSize(content);
            delete message;
			return NULL;
        }
		message->setFileName(file_name);
		message->setFileSuffix(file_suffix);
		message->setFileSize(file_size);
	}
		break;
	default:
		break;
	}

	message->setMessageSendFrom(GROUP_MESSAGE_TYPE_CURRENT_ACCOUNT);
	Q_ASSERT(curSession != NULL);
	//我的头像
	QString avatarFileName = TNPathUtil::getFeedAvatarPath(myFeedId);
	message->SetPhotoIcon(avatarFileName);

	st_FeedPtr feedInfo;
	TNUserDataHelper::GetInstance()->GetFeedInfo(myFeedId, feedInfo);
	if (feedInfo)
	{
		message->setAvatorUrl(feedInfo->GetAvatarID());
		message->SetFeedName(feedInfo->GetTitle());
	}

	if (atType != -1)
	{
		message->SetAtType(atType);
		message->SetAtFeeds(atFeeds);
	}
    //备注
    if(curSession->getType() == MSG_BIZ_GROUPCHAT){
        QString remark = TNDataCache::GetInstance()->getFriendFeedReMark(message->getFromId(), message->getMyFeedId());
        message->setRemark(remark);
    }
    ///////////////////////////////
    //notice 日志
    QString qs_log = "[Notice] [TNGenerateNoticeModelData] generateSendMsg end,msgId:" + message->GetMsgID();
    qInfo() << qs_log;
    return message;
}

TNModelUserMessage* TNGenerateNoticeModelData::generateRecvMsg(const TNMsgData& msgData, MESSAGE_TYPE type,
	const QString& myFeedId, bool bDownloaded)
{
    Q_UNUSED(bDownloaded);
    //notice 日志
    QString qs_log = "[Notice] [TNGenerateNoticeModelData] generateRecvMsg start";
    qInfo() << qs_log;
    TNModelUserMessage* message = new TNModelUserMessage();
	message->SetMsgID(msgData.msgId);
	message->SetMessageType(type);
	message->setMsgSendOrRecv(MESSAGE_RECV);
	message->setPicSize(QSize(msgData.w, msgData.h));
	message->setFileName(msgData.desc);
	message->setFileSuffix(msgData.format);
	message->setFileSize(msgData.size);
	message->setSessionId(msgData.sessionId);
	message->setSessionType(msgData.bizType);
	message->setMyFeedId(myFeedId);
    message->setMsgStatus(msgData.status);
    message->setMsgFileStatus(msgData.fileStatus);
    message->setMsgFileStatus(MSG_STATUS_FILE_UNDOWN);

	//多端多活判断是否自己发来的消息
	bool flag = msgData.bIsMyself;
	if (!flag){
		message->setMessageSendFrom(GROUP_MESSAGE_TYPE_OTHER);
	}
	else{
		message->setMessageSendFrom(GROUP_MESSAGE_TYPE_CURRENT_ACCOUNT);
	}
    //格式化收到的信息,替换一些特殊字符
    QString t = msgData.data;
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
    message->SetUserMessage(t);
	message->setAudioTime(msgData.time);
	QDateTime time_temp = QDateTime::fromMSecsSinceEpoch(msgData.timestmp * 1000);
	message->setTime(time_temp);

	//头像
	QString feedId = msgData.from;
	message->setFromId(feedId);
	message->setToFeedId(msgData.to);
	QString avatarFileName = TNPathUtil::getFeedAvatarPath(feedId);
	message->SetPhotoIcon(avatarFileName);

	st_FeedPtr feedInfo;
	TNUserDataHelper::GetInstance()->GetFeedInfo(feedId, feedInfo);
	if (feedInfo){
		message->setAvatorUrl(feedInfo->GetAvatarID());
		message->SetFeedName(feedInfo->GetTitle());
	}
    //备注
    if(msgData.bizType == MSG_BIZ_GROUPCHAT){
        QString remark = TNDataCache::GetInstance()->getFriendFeedReMark(message->getFromId(), message->getMyFeedId());
        message->setRemark(remark);
    }
    //notice 日志
    qs_log = "[Notice] [TNGenerateNoticeModelData] generateRecvMsg end,msgId:" + message->GetMsgID();
    qInfo() << qs_log;
    return message;
}

TNModelUserMessage* TNGenerateNoticeModelData::generateRevokeMsg(MESSAGE_TYPE type, QString content, TNMessageListAdapter* curSession)
{
    //notice 日志
    QString qs_log = "[Notice] [TNGenerateNoticeModelData] generateRevokeMsg start";
    qInfo() << qs_log;
    TNModelUserMessage *message = new TNModelUserMessage;
	message->SetMessageType(type);
	message->SetUserMessage(content);
	message->setSessionId(curSession->getSessionId());
	message->setMsgSendOrRecv(MESSAGE_SEND);
	message->SetMsgID(TNIMCoreClient::GetMsgId());
	QString myFeedId = curSession->getMyFeedId();
	message->setMyFeedId(myFeedId);
	message->setFromId(myFeedId);
	QString toFeedId = curSession->getToFeed();
	message->setToFeedId(toFeedId);
	message->setSessionType((TNBizType)curSession->getType());
    //notice 日志
    qs_log = "[Notice] [TNGenerateNoticeModelData] generateRevokeMsg end, msgId:" + message->GetMsgID();
    qInfo() << qs_log;
    return message;
}

TNModelUserMessage TNGenerateNoticeModelData::generateHistoryMsgFromDataBase(const toonim::CTNMessage& messageDataBase)
{
    TNModelUserMessage message;
    TNMsgData data;//解析后得到数据
    TNIMCoreClient::IMMessageCastToData(messageDataBase, data);
    if (!data.bShow){
        return message;
    }
    message.setSessionId(data.sessionId);
    //判断消息是否自己发送
    message.setSessionType((MSG_BIZ_TYPE)data.bizType);
    if (!data.bIsMyself){
        message.setMessageSendFrom(GROUP_MESSAGE_TYPE_OTHER);
    }else{
        message.setMessageSendFrom(GROUP_MESSAGE_TYPE_CURRENT_ACCOUNT);
    }
    if (data.bizType == MSG_BIZ_SINGLECHAT || data.bizType == MSG_BIZ_SINGLECHAT_REVERT){
        if (!data.bIsMyself){
            message.setMyFeedId(data.to);
        }else{
            message.setMyFeedId(data.from);
        }
        message.setToFeedId(data.to);
        message.setFromId(data.from);
    }else if (data.bizType == MSG_BIZ_GROUPCHAT || data.bizType == MSG_BIZ_GROUPCHAT_REVERT){
        TableBaseVec groupTableBaseVec;
        QString groupId = data.sessionId;
		TNDataControlServer::GetInstance()->Query(groupTableBaseVec, "GroupInfo", "groupId", groupId, DBTYPE_USER);
        if (groupTableBaseVec.size() != 0){
            st_GroupInfoPtr groupInfo = std::dynamic_pointer_cast<st_GroupInfo>(*groupTableBaseVec.begin());
            message.setMyFeedId(groupInfo->GetMyFeedId());
            message.setToFeedId(groupId);
            message.setFromId(data.from);
        }
    }
    message.setUserId(data.toUserId);
    // 获取头像
    QString feedId = data.from;
    QString avatarFileName = TNPathUtil::getFeedAvatarPath(feedId);
    message.SetPhotoIcon(avatarFileName);
    st_FeedPtr feedInfo;
    TNUserDataHelper::GetInstance()->GetFeedInfo(feedId, feedInfo);
    if (feedInfo){
        message.setAvatorUrl(feedInfo->GetAvatarID());
        message.SetFeedName(feedInfo->GetTitle());
    }
    qlonglong timeLong = (qlonglong)data.timestmp * 1000;
    QDateTime date_time = QDateTime::fromMSecsSinceEpoch(timeLong);
    message.setTime(date_time);
    message.SetMsgID(data.msgId);
    message.setMsgStatus(data.status);
    message.setMsgFileStatus(data.fileStatus);
    //历史记录全为已经发送的数据或者接收的数据
    message.SetUserMessage(data.data);
    QString localPath = data.localPath;
    switch (data.type)
    {
    case MSG_TYPE_TEXT:
        message.SetMessageType(em_text);
        if (message.getMsgStatus() != MSG_STATUS_SEND_SUC){//对于不成功的文字数据只存在发送不成功
            message.setMsgSendOrRecv(MESSAGE_SEND);
        }
        break;
    case MSG_TYPE_IMG:
        message.SetMessageType(em_image);
        message.setPicSize(QSize(data.w, data.h));
        message.SetUserMessage(data.url);
        //图片对于加载历史记录来说全是接收,从服务器下载
        if(message.getMsgStatus() != MSG_STATUS_SEND_SUC){
            message.setMsgSendOrRecv(MESSAGE_SEND);
        }else{
            switch(message.getMsgFileStatus()){
            case MSG_STATUS_FILE_DOWNLOADING:
            case MSG_STATUS_FILE_DOWN_FAIL:
            case MSG_STATUS_FILE_UNDOWN:
            case MSG_STATUS_FILE_SUC:
                message.setMsgSendOrRecv(MESSAGE_RECV);
                break;
            case MSG_STATUS_FILE_UPLOADING:
            case MSG_STATUS_FILE_UPLOAD_FAIL:
                message.setMsgSendOrRecv(MESSAGE_SEND);
                break;
            default:
                break;
            }
        }
        message.setFileSuffix(data.format);
        if(QFile::exists(localPath)){
            message.setFileLocalPath(localPath);
        }
        break;
    case MSG_TYPE_ATTACHMENT:
        message.SetUserMessage(data.url);
        message.SetMessageType(em_file);
        if(message.getMsgStatus() != MSG_STATUS_SEND_SUC){
            message.setMsgSendOrRecv(MESSAGE_SEND);
            message.setFileLocalPath(localPath);
        }else{
            switch(message.getMsgFileStatus()){
            case MSG_STATUS_FILE_DOWNLOADING:
            case MSG_STATUS_FILE_DOWN_FAIL:
            case MSG_STATUS_FILE_UNDOWN:
                message.setMsgSendOrRecv(MESSAGE_RECV);
                break;
            case MSG_STATUS_FILE_UPLOADING:
            case MSG_STATUS_FILE_UPLOAD_FAIL:
                message.setMsgSendOrRecv(MESSAGE_SEND);
                break;
            case MSG_STATUS_FILE_SUC:
                if (localPath.isEmpty() || !QFile::exists(localPath)){//本地没有
                    message.setMsgSendOrRecv(MESSAGE_RECV);//该条文件需要下载
                }else{
                    message.setMsgSendOrRecv(MESSAGE_SEND);
                    message.setFileLocalPath(localPath);
                }
                break;
            default:
                break;
            }
        }
        message.setFileName(data.desc);
        message.setFileSuffix(data.format);
        message.setFileSize(data.size);
        break;
    case MSG_TYPE_VOICE://音频
        //音频只能接收
        message.setMsgSendOrRecv(MESSAGE_RECV);
        message.SetMessageType(em_audio);
        message.setAudioTime(data.time);//音频时长
        if(QFile::exists(localPath))
            message.setFileLocalPath(localPath);
        break;
    case MSG_TYPE_NOTICE://通知(群聊)
        message.SetMessageType(em_groupchat_notice);
        break;
    case MSG_TYPE_OTHER:
        message.SetMessageType(em_notsupport);
        break;
    default:
        break;
    }
    //备注
    if(data.bizType == MSG_BIZ_GROUPCHAT){
        QString remark = TNDataCache::GetInstance()->getFriendFeedReMark(message.getFromId(), message.getMyFeedId());
        message.setRemark(remark);
    }
    return message;
}
