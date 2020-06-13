#include "tnsendimsg.h"
#include "TNIMCoreClient.h"
#include "TNMessageListAdapter.h"
#include "tnnotifycenter.h"
#include "details_notice/TNMsgDetailModel.h"
#include "audio/wav/tnconvertamr.h"
#include "model_data/tngeneratenoticemodeldata.h"
#include "TNDataControlServer.h"
#include "TNPathUtil.h"
#include "TNUserDataHelper.h"
#include "TNNetAvatarDown.h"
#include "noticelistmodel.h"
#include "tnsessionnetwork.h"
#include "CTNDBAPI.h"
#include <QApplication>
#include <QDir>

TNSendIMsg* TNSendIMsg::_instance = NULL;
TNSendIMsg::TNSendIMsg(QObject *parent /* = 0 */)
	: QObject(parent)
	, _msgModel(NULL)
    , _listMsgModel(NULL)
{
    _httpCloudApi = TNHttpCloudApi::GetInstance();
    connect(this, SIGNAL(upLoadFinishSign(bool, QString, QString, QString)),
        this, SLOT(onUpLoadFinish(bool, QString, QString, QString)));
    connect(this, SIGNAL(downloadFinishSign(bool, QString, QString, QString, int, bool)),
        this, SLOT(onDownLoadFinish(bool, QString, QString, QString, int, bool)));
    connect(_httpCloudApi,SIGNAL(DownLoadProgressCloud(qint64, qint64, QStringList)),
            this,SLOT(onDownLoadProgress(qint64,qint64,QStringList)));
    connect(_httpCloudApi,SIGNAL(UpLoadProgressCloud(qint64, qint64, QString)),
            this,SLOT(onUpLoadProgress(qint64,qint64,QString)));

    _sessionNetWork = TNSessionNetWork::getInstance();
    //接收消息
	TNNotifyCenter::instance()->connectNotifyRefresh(this);
	TNNotifyCenter::instance()->connnectNotifyMessageback(this);
	TNNotifyCenter::instance()->connectNotifyRefreshAddressList(this);
}

TNSendIMsg::~TNSendIMsg()
{
}

void TNSendIMsg::releaseInstance()
{
    delete _instance;
    _instance = NULL;
}

TNSendIMsg* TNSendIMsg::getInstance()
{
    if (_instance == NULL){
        _instance = new TNSendIMsg();
	}
    return _instance;
}

void TNSendIMsg::setDetailModel(TNMsgDetailModel* msgModel)
{
	_msgModel = msgModel;
}

void TNSendIMsg::setListMsgModel(NoticeListModel* listModel)
{
	_listMsgModel = listModel;
    _sessionNetWork->setSessionModel(_listMsgModel);
}

NoticeListModel* TNSendIMsg::getListMsgModel()
{
    return _listMsgModel;
}

void TNSendIMsg::setTNPluginParamPtr(const TNPluginParamPtr& param)
{
	_pluginParam = param;
}

void TNSendIMsg::ProcessIMMSG(TNModelUserMessage message)
{
    //正在发送的状态
    message.setMsgStatus(MSG_STATUS_SENDING);
    _msgModel->updateMsgStatus(message.GetMsgID(),MSG_STATUS_SENDING);
    switch (message.GetMessageType()){
		case em_audio:
		case em_file:
        case em_image:
            //上传文件成功了,但没有发送
            if(message.getMsgFileStatus() == MSG_STATUS_FILE_SUC){
                SendMsgToIMServer(&message);
                return;
            }
            //预存
            if(message.getMsgFileStatus() != MSG_STATUS_FILE_UPLOAD_FAIL){
                message.setMsgFileStatus(MSG_STATUS_FILE_UPLOADING);
                TNMsgData data = convertMsgData(&message);
                TNIMCoreClient::GetIMClient()->PreSaveIMMessage(&data,
                message.getSessionType() == MSG_BIZ_SINGLECHAT);
            }else{
                message.setMsgFileStatus(MSG_STATUS_FILE_UPLOADING);
            }
			//上传成功发送
            UploadCloud(&message);
            break;
		case em_text:
			//直接发送
            SendMsgToIMServer(&message);
			break;
		default:
			break;
	}
}

void TNSendIMsg::SendMsgToIMServer(const QString& sessionId, const QString &msgId)
{
    CTNMessage message = TNIMCoreClient::GetDBChat()->getMessage(sessionId.toStdString().c_str(),msgId.toStdString().c_str());
    TNGenerateNoticeModelData generateModelData;
    TNModelUserMessage userMessage = generateModelData.generateHistoryMsgFromDataBase(message);
    if(!userMessage.GetMsgID().isEmpty()){
        SendMsgToIMServer(&userMessage);
    }
}

void TNSendIMsg::SendMsgToIMServer(TNModelUserMessage* message)
{
    TNMsgData IMdata = convertMsgData(message);
    bool isSingleChat = true;
    if (message->getSessionType() == MSG_BIZ_GROUPCHAT)
    {
        isSingleChat = false;
    }
	TNIMCoreClient::GetIMClient()->SendIMMessage(&IMdata, isSingleChat);
}

TNMsgData TNSendIMsg::convertMsgData(TNModelUserMessage *message)
{
    TNMsgData IMdata;
    MSG_TYPE type;
    switch(message->GetMessageType()){
    case em_text:
        type = MSG_TYPE_TEXT;
        break;
    case em_image:
        if(message->getFileSuffix() == ".gif"){
            type = MSG_TYPE_GIFIMG;
        }else{
            type = MSG_TYPE_IMG;
        }
        break;
    case em_file:
        type = MSG_TYPE_ATTACHMENT;
        break;
    case em_audio:
        type = MSG_TYPE_VOICE;
        break;
    case em_video:
        type = MSG_TYPE_VIDEO;
        break;
    case em_red_card:
        type = MSG_TYPE_RED_CARD;
        break;
    case em_groupchat_notice:
        type = MSG_TYPE_NOTICE;
        break;
    case em_notsupport:
        type = MSG_TYPE_OTHER;
        break;
    case em_card_not_exist:
        type = MSG_TYPE_CARD_FAILED;
        break;
    default:
        break;
    }
    IMdata.type = type;
    IMdata.from = message->getMyFeedId();

    IMdata.to = message->getToFeedId();
    IMdata.data = message->GetUserMessage();
    IMdata.toUserId = message->getUserId();
    IMdata.desc = message->getFileName();
    IMdata.size = message->getFileSize();
    IMdata.w = message->getPicSize().width();
    IMdata.h = message->getPicSize().height();
    IMdata.msgId = message->GetMsgID();
    IMdata.localPath = message->getFileLocalPath();
    IMdata.atType = message->GetAtType();
    IMdata.atFeeds = message->GetAtFeeds();
    IMdata.format = message->getFileSuffix();
    IMdata.status = message->getMsgStatus();
    IMdata.fileStatus = message->getMsgFileStatus();
    return  IMdata;
}

void TNSendIMsg::UploadCloud(TNModelUserMessage* message)
{
    //避免重复上传
    if(!pushBackUpload(message->GetMsgID())){
        return;
    }
    if(message->GetMessageType() == em_file || message->GetMessageType() == em_image){
        appendProgress(down_mark(message->GetMsgID()));
    }
    QString local_path = message->getFileLocalPath();
    qInfo() << "[Notice] [UploadCloud] file local path:" << local_path << " msgId:" << message->GetMsgID();
    if(message->GetMessageType() == em_image){
        Q_ASSERT(local_path.size() > 4);
        if(local_path.right(4) != "_org")
            local_path += "_org";
    }
    QVector<QVariant> extern_params;
    extern_params.push_back(message->GetMsgID());
    extern_params.push_back(message->getSessionId());
    _httpCloudApi->UploadFileToCloud([&](bool success, QString file_path, QVector<QVariant> params){
        QString msgId = params[0].toString();
        QString sessionId = params[1].toString();
        emit upLoadFinishSign(success,file_path,msgId,sessionId);
    }, _pluginParam, local_path, extern_params);
}

void TNSendIMsg::onUpLoadFinish(bool success, QString url, QString msgId, QString sessionId)
{
    //删除队列中上传
    popUpUpload(msgId);
    ///////////////
    TNModelUserMessage* itemData = _msgModel->updateFileData(msgId, url, success);
    //删除上传进度
    removeProgress(down_mark(msgId));
    if(itemData == NULL){
        //notice 日志
        qInfo() << "[Notice] [TNSendIMsg] onUpLoadFinish updateFileData failed msgId:" << msgId << " sessionId:" << sessionId;
    }
    if(success){
        TNIMCoreClient::GetIMClient()->SetMsgFileStatus(
                    msgId,
                    sessionId,
                    MSG_STATUS_FILE_SUC,
                    url);
        if(itemData != NULL)
            SendMsgToIMServer(itemData);
        else
            SendMsgToIMServer(sessionId,msgId);
    }else{
        TNIMCoreClient::GetIMClient()->SetMsgFileStatus(
                    msgId,
                    sessionId,
                    MSG_STATUS_FILE_UPLOAD_FAIL);
        TNIMCoreClient::GetIMClient()->SetMsgSendStatus(
                    msgId,
                    sessionId,
                    MSG_STATUS_SEND_FAIL);

        //notice 日志
        qInfo() << "[Notice] [TNSendIMsg] onUpLoadFinish updateFileData failed msgId:" << msgId << " sessionId:" << sessionId;
    }
}

void TNSendIMsg::onDownLoadFinish(bool success, QString url, QString msgId, QString sessionId, int type, bool is_org)
{
	switch (type){
	case download_image:
	case download_file:
        if(!is_org){
            onFileDownLoadFinish(success, url, msgId, sessionId);
        }else{
            emit orig_image_finished(success,msgId,url);
        }
		break;
	case download_audio:
        onAudioDownLoadFinish(success, url, msgId, sessionId);
		break;
	default:
		break;
	}
    //删除下载进度
    removeProgress(down_mark(msgId,is_org));
}

void TNSendIMsg::onFileDownLoadFinish(bool success, QString url, QString msgId, QString sessionId, bool is_org_image)
{
    //从下载队列中移除
    popUpDownload(down_mark(msgId,is_org_image));
    //notice 日志
    QString qs_log = "[Notice] [TNSendIMsg] onFileDownLoadFinish msgId:" + msgId
            + " url:" + url + " success: " + QString("%1").arg(success);
    qInfo() << qs_log;
    //更新数据库
    TNIMCoreClient* client = TNIMCoreClient::GetIMClient();
    client->SetMsgFileStatus(msgId, sessionId, success ? MSG_STATUS_FILE_SUC : MSG_STATUS_FILE_DOWN_FAIL,url,false);
    //更新界面
    _msgModel->updateFileData(msgId, url, success);
}

void TNSendIMsg::on_notifyRefresh(QString type, int statCode, const QString statDesc, TNMsgData msgData)
{
	qDebug() << "[noticedetail]on_notifyRefresh begin";
	emit notifyRefresh(type, statCode, statDesc, msgData);
	qDebug() << "[noticedetail]on_notifyRefresh end";
}

void TNSendIMsg::on_notifyRefresh(QString type, TNNoticeInfo &noticeInfo)
{
	emit notifyRefresh(type, noticeInfo);
}

void TNSendIMsg::DownloadImage(TNModelUserMessage message)
{
	switch (message.GetMessageType()){
    case em_image:{
        QString format = message.getFileSuffix();
        if(!format.isEmpty()){
            format = format.mid(1);
        }
        QString url = message.GetUserMessage();
        QString messageId = message.GetMsgID();

        QString org_file_path = TNPathUtil::getUserRecFile() + messageId + "_org";

        //下载缩略图
        QString new_url = TNHttpDownCloud::GetThumbUrl(message.getPicSize().width(),
                message.getPicSize().height(), url, format);
        qDebug() << new_url;
        //下载唯一
        if(!pushBackDownload(down_mark(messageId))){
            return;
        }
        //notice 日志
        QString qs_log = "[Notice] [TNSendIMsg] DownloadImage __small__ msgId:" + messageId
                + " start download url:" + new_url;
        qInfo() << qs_log;

        appendProgress(down_mark(messageId));

        QVector<QVariant> extern_params;
        extern_params.push_back(message.GetMsgID());
        extern_params.push_back(message.getSessionId());
        extern_params.push_back(download_image);

        _httpCloudApi->DownFileFromCloudEx(
            TNSendIMsg::download_file_callback,
            _pluginParam, new_url, "",
            message.GetMsgID(), extern_params, false);

        //下载原图
        if(!pushBackDownload(down_mark(messageId,true))){
            return;
        }
        //notice 日志
        qs_log = "[Notice] [TNSendIMsg] DownloadImage __big__ msgId:" + messageId
                + " start download url:" + url;
        qInfo() << qs_log;
        //加入下载progress
        appendProgress(down_mark(messageId,true));
        _httpCloudApi->DownFileFromCloudEx(
            TNSendIMsg::download_file_callback,
            _pluginParam,url,org_file_path,
            message.GetMsgID(),extern_params,true);
        break;
    }
    default:
        break;
    }
}

void TNSendIMsg::downLoadOrgImage(TNModelUserMessage message)
{
    //下载原图
    if(!pushBackDownload(down_mark(message.GetMsgID(),true))){
        return;
    }
    QString url = message.GetUserMessage();
    QString org_file_path = TNPathUtil::getUserRecFile() + message.GetMsgID() + "_org";
    QVector<QVariant> extern_params;
    extern_params.push_back(message.GetMsgID());
    extern_params.push_back(message.getSessionId());
    extern_params.push_back(download_image);
    //notice 日志
    qInfo() << "[Notice] [TNSendIMsg] DownloadImage __big__ msgId:" << message.GetMsgID()
        << " start download url:" << url;
    //加入下载progress
    appendProgress(down_mark(message.GetMsgID(), true));
    _httpCloudApi->DownFileFromCloudEx(
        TNSendIMsg::download_file_callback,
        _pluginParam,url,org_file_path,
        message.GetMsgID(),extern_params,true);
}

void TNSendIMsg::DownloadFile(const QString& url, const QString& msgId, const QString& sessionId, const QString& file_path)
{
    //下载唯一
    down_mark down;
    down._msg_id = msgId;
    if(!pushBackDownload(down)){
        return;
    }
    //notice 日志
    QString qs_log = "[Notice] [TNSendIMsg] DownloadFile msgId:" + msgId + " start download url:" + url + " local_file:" + file_path;
    qInfo() << qs_log;
    //下载进度加入
    appendProgress(down_mark(msgId,false));
    QVector<QVariant> extern_params;
    extern_params.push_back(msgId);
    extern_params.push_back(sessionId);
    extern_params.push_back(download_file);
    _httpCloudApi->DownFileFromCloudEx([&](bool success, QString file_path, QVector<QVariant> params){
		//notice 日志
        QString msgId = params[0].toString();
        QString sessionId = params[1].toString();
        int type = params[2].toInt();
        QString qs_log = "[Notice] [TNSendIMsg] DownloadFile msgId:" + msgId + " callback";
        qInfo() << qs_log;
        emit downloadFinishSign(success, file_path, msgId, sessionId, (int)type);
    }, _pluginParam, url, file_path, msgId,extern_params);
}

void TNSendIMsg::DownloadAudio(TNModelUserMessage data)
{
    switch (data.GetMessageType()){
    case em_audio:{
        //下载唯一
        down_mark down;
        down._msg_id = data.GetMsgID();
        if(!pushBackDownload(down)){
            return;
        }
        //notice 日志
        QString qs_log = "[Notice] [TNSendIMsg] DownloadAudio msgId:" + data.GetMsgID() + " start download url:" + data.GetUserMessage();
        qInfo() << qs_log;

        QVector<QVariant> extern_params;
        extern_params.push_back(data.GetMsgID());
        extern_params.push_back(data.getSessionId());
        extern_params.push_back(download_audio);
        _httpCloudApi->DownFileFromCloudEx([&](bool success,QString file_path,QVector<QVariant> params){
            //notice 日志
            QString msgId = params[0].toString();
            QString sessionId = params[1].toString();
            int type = params[2].toInt();
            QString qs_log = "[Notice] [TNSendIMsg] DownloadImage msgId:" + msgId + " callback";
            qInfo() << qs_log;
            emit downloadFinishSign(success, file_path, msgId, sessionId, (int)type);
        }, _pluginParam, data.GetUserMessage(), "", data.GetMsgID(),extern_params);
        break;
    }
    default:
        break;
    }
}

void TNSendIMsg::onAudioDownLoadFinish(bool success, QString url, QString msgId,QString sessionId)
{
    //从下载队列中移除
    down_mark down;
    down._msg_id = msgId;
    down._is_org = false;
    popUpDownload(down);
    //notice 日志
    QString qs_log = "[Notice] [TNSendIMsg] onAudioDownLoadFinish msgId:" + msgId
            + " url:" + url + " success " + QString("").arg(success);
    qInfo() << qs_log;
    TNIMCoreClient* client = TNIMCoreClient::GetIMClient();
    if (!success){
        _msgModel->updateAudioDataDownloaded(msgId, sessionId, false);
        client->SetMsgFileStatus(msgId, sessionId, MSG_STATUS_FILE_DOWN_FAIL);
        return;
	}
	
	//将amr转换成wav
	QString dstWavFile = url + ".wav";
	if (TNConvertAmr::convertAmrToWav(url, dstWavFile)){
		//删除源文件
		QDir dir;
		dir.remove(url);
		////////////////
        //notice 日志
        qs_log = "[Notice] [TNSendIMsg] onAudioDownLoadFinish convertAmrToWav:" + msgId
            + " url:" + dstWavFile + " success";
        qInfo() << qs_log;
        _msgModel->updateAudioDataDownloaded(msgId, dstWavFile, true);
		//更新数据库localpath
        client->SetMsgFileStatus(msgId, sessionId, MSG_STATUS_FILE_SUC, dstWavFile, false);
    }else{
        //notice 日志
        qs_log = "[Notice] [TNSendIMsg] onAudioDownLoadFinish convertAmrToWav:" + msgId + " failed";
        qCritical() << qs_log;
        _msgModel->updateAudioDataDownloaded(msgId, "", false);
        client->SetMsgFileStatus(msgId,sessionId,MSG_STATUS_FILE_DOWN_FAIL);
    }
}

void TNSendIMsg::DownloadAvatar(const QString& url,
                                const QString& feedId,
                                const QString& msgId,
                                const QString& file_path)
{
	bool isDownloading = false;
	_mutexAvator.lock();
	list<QString>::const_iterator itera = _listAvator.begin();
	for (; itera != _listAvator.end(); ++itera){
		if (msgId == *itera){
			isDownloading = true;
			break;
		}
	}
	_mutexAvator.unlock();
	if (isDownloading){
		return;
	}else{
		_mutexAvator.lock();
		_listAvator.push_back(msgId);
		_mutexAvator.unlock();
	}
	/////////////////////////
    //notice 日志
    QString qs_log = "[Notice] [TNSendIMsg] DownloadAvator msgId:" + msgId + " start download url:" + url;
    qInfo() << qs_log;
    TNNetAvatarDown::GetInstance()->DownLoadFeedAvatar(feedId, url,
    TNHttpCloudApi::GetInstance()->GetCloudStoken(_pluginParam),
        this,false,msgId);
    Q_UNUSED(file_path);
}

void TNSendIMsg::onAvatarDownLoadFinishEx(bool success,QString file_path,
                                              QString feedId,QString msgId)
{
    onAvatarDownLoadFinishSign(success,file_path,feedId,msgId);
}


void TNSendIMsg::onAvatarDownLoadFinishSign(bool success,
    QString url, QString feedId, QString msgId)
{
	_mutexAvator.lock();
    _listAvator.remove(msgId);
	_mutexAvator.unlock();
	if (success){
		//notice 日志
        QString qs_log = "[Notice] [TNSendIMsg] msgId:" + msgId + " feedId:" + feedId + " onAvatarDownLoadFinishSign success url:" + url;
        qInfo() << qs_log;
        //_msgModel->updateAvatorIcon(msgId, url);
        _msgModel->updateAvatorIconByFeedId(feedId,url);
	}else{
        QString qs_log = "[Notice] [TNSendIMsg] msgId:" + msgId + " feedId:" + feedId + " onAvatarDownLoadFinishSign failed url:" + url;
        qInfo() << qs_log;
	}
}

void TNSendIMsg::on_notifyRefreshAck(QString msgId, int bSuc)
{
    //notice 日志
    QString qs_log = "[Notice] [TNSendIMsg] on_notifyRefreshAck msgId:" + msgId + " bSuc:" + QString("%1").arg(bSuc);
    qInfo() << qs_log;
    _msgModel->updateMsgFeedback(msgId, bSuc);
}

void TNSendIMsg::on_notifyRefresh(int type, QList<UINotifyData> data)
{
	if (type == RefreshTypeUI_SwitchSingle){
		for (int i = 0; i < data.size(); i++){
			switch (data[i].operateType)
			{
			case UI_OPERATE_ADD://开启消息免打扰
				_listMsgModel->manulSetSessionAlarm(data[i].feedId, true);
				break;
			case UI_OPERATE_DEL://关闭消息免打扰
				_listMsgModel->manulSetSessionAlarm(data[i].feedId, false);
				break;
			default:
				break;
			}
		}
	}
}

bool TNSendIMsg::isFileDownloaded(const QString& msgId, QString& localPath)
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

bool TNSendIMsg::isAudioDownloaded(const QString& msgId, QString& localPath)
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

bool TNSendIMsg::updateProgress(const down_mark& mark,int progress)
{
    QMutexLocker lock(&_mutex_progress);
    if(_up_down_progress.find(mark) != _up_down_progress.end()){
        _up_down_progress[mark] = progress;
        return true;
    }
    return false;
}

bool TNSendIMsg::removeProgress(const down_mark& mark)
{
    QMutexLocker lock(&_mutex_progress);
    map<down_mark,int>::const_iterator itera = _up_down_progress.find(mark);
    if(itera != _up_down_progress.end()){
        _up_down_progress.erase(itera);
        return true;
    }
    return false;
}

bool TNSendIMsg::getProgress(const down_mark &mark, int *progress)
{
    QMutexLocker lock(&_mutex_progress);
    map<down_mark,int>::const_iterator itera = _up_down_progress.find(mark);
    if(itera != _up_down_progress.end()){
        *progress = _up_down_progress[mark];
        return true;
    }
    return false;
}

void TNSendIMsg::appendProgress(const down_mark& mark)
{
    QMutexLocker lock(&_mutex_progress);
    if(_up_down_progress.find(mark) == _up_down_progress.end())
        _up_down_progress[mark] = 0;
}

void TNSendIMsg::onUpLoadProgress(qint64 per,qint64 total,QString msgId)
{
    if(per <= 0 || total <= 0){
        return;
    }
    int progress = per * 100 / total;
    updateProgress(down_mark(msgId,false),progress);
    _msgModel->updateMsgFileProgress(msgId,progress);
}

void TNSendIMsg::onDownLoadProgress(qint64 per, qint64 total, QStringList info)
{
    if(per <= 0 || total <= 0){
        return;
    }
    int progress = per * 100 / total;
    QString msg_id = info[0];
    QString local_path = info[1];
    if(local_path.right(4) == "_org"){
        updateProgress(down_mark(msg_id,true),progress);
        //发送大图progress信号
        emit org_image_progress(msg_id,progress);
    }else{
        //如果是图片则为缩略图进度
        updateProgress(down_mark(msg_id,false),progress);
        _msgModel->updateMsgFileProgress(msg_id,progress);
    }
}

bool TNSendIMsg::pushBackDownload(const down_mark& mark)
{
    bool flag = false;
    _mutexDown.lock();
    if(!isDownloading(mark)){
        _listDown.push_back(mark);
        flag = true;
    }
    _mutexDown.unlock();
    return flag;
}

void TNSendIMsg::popUpDownload(const down_mark& mark)
{
    _mutexDown.lock();
    _listDown.remove(mark);
    _mutexDown.unlock();
}

bool TNSendIMsg::isDownloading(const down_mark &mark)
{
    bool flag = false;
    list<down_mark>::const_iterator itera = _listDown.begin();
    for(;itera!=_listDown.end();++itera){
        if(mark == *itera){
            flag = true;
            break;
        }
    }
    return flag;
}

bool TNSendIMsg::pushBackUpload(const QString &msgId)
{
    bool flag = false;
    _mutexUp.lock();
    if(!isUploading(msgId)){
        flag = true;
        _listUp.push_back(msgId);
    }
    _mutexUp.unlock();
    return flag;
}

void TNSendIMsg::popUpUpload(const QString &msgId)
{
    _mutexUp.lock();
    _listUp.remove(msgId);
    _mutexUp.unlock();
}

bool TNSendIMsg::isUploading(const QString &msgId)
{
    bool flag = false;
    list<QString>::const_iterator itera = _listUp.begin();
    for(;itera != _listUp.end();++itera){
        if(msgId == *itera){
            flag = true;
            break;
        }
    }
    return flag;
}

void TNSendIMsg::download_file_callback(bool success, QString file_path, QVector<QVariant> params)
{
    //notice 日志
    QString msgId = params[0].toString();
    QString sessionId = params[1].toString();
    int type = params[2].toInt();
    QString qs_log;
    bool is_org = false;
    if(file_path.right(4) == "_org"){
        qs_log = "[Notice] [TNSendIMsg] DownloadImage __big__ msgId:" + msgId + " callback";
        is_org = true;
    }else{
        qs_log = "[Notice] [TNSendIMsg] DownloadImage __small__ msgId:" + msgId + " callback";
    }
    qInfo() << qs_log;
    emit TNSendIMsg::getInstance()->downloadFinishSign(success, file_path, msgId, sessionId, (int)(type), is_org);
}

void TNSendIMsg::downLoadAvator(TNMessageListAdapter itemData)
{
    QString sessionId = itemData.getSessionId();
    QStringList sessionList = sessionId.split("_");
    QString mark_feed_id;
    switch (itemData.getType()){
    case MSG_BIZ_SINGLECHAT:
    case MSG_BIZ_SINGLECHAT_REVERT:
        if (sessionList.size() == 4){
            QString one = sessionList[0] + "_" + sessionList[1];
            QString two = sessionList[2] + "_" + sessionList[3];
            if (one == itemData.getMyFeedId()){
                mark_feed_id = two;
            }else{
                mark_feed_id = one;
            }
        }
        break;
    case MSG_BIZ_GROUPCHAT_REVERT:
    case MSG_BIZ_GROUPCHAT:
    case MSG_BIZ_NOTIFY:
        mark_feed_id = sessionId;
        break;
    default:
        break;
    }
    Q_ASSERT(!mark_feed_id.isEmpty());
    Q_ASSERT(!sessionId.isEmpty());

    _sessionNetWork->downloadAvatar(itemData.getAvatarPhotoUrl(),
        mark_feed_id,sessionId,itemData.getType());
    //notice 日志
    QString qs_log = "[Notice] [TNMessageListModel] session list: " + mark_feed_id + " downLoadAvator url:" + itemData.getAvatarPhotoUrl();
    qInfo() << qs_log;
}

void TNSendIMsg::cancelDownLoad(const QString &msgId,const QString& sessionId)
{
    _httpCloudApi->CancelRequest(msgId,false);
    TNIMCoreClient::GetIMClient()->SetMsgFileStatus(msgId, sessionId, MSG_STATUS_FILE_DOWN_FAIL);
}

void TNSendIMsg::cancelUpLoad(const QString &msgId)
{
    _httpCloudApi->CancelRequest(msgId);
}
