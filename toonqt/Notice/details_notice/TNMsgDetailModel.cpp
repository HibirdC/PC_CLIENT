#include "TNMsgDetailModel.h"
#include "TNMsgDetailItemWidget.h"
#include "TNDataCache.h"

TNMsgDetailModel::TNMsgDetailModel(QObject *parent) :
    TNTableModel(parent),
	_tableView(NULL),
	_chatDetailBase(NULL)
{
}

TNMsgDetailModel::~TNMsgDetailModel()
{
    
}

void TNMsgDetailModel::setChatDetailBase(TNChatDetailBase *chatDetailBase)
{
    _chatDetailBase = chatDetailBase;
}

TNModelUserMessage* TNMsgDetailModel::updateFileData(const QString& msgId, const QString& fileUrl,
	bool success /* = false */, int progress /* = 0 */)
{
	if (msgId.isEmpty())
		return NULL;
	TNModelUserMessage *itemData = NULL;
	int index = findItemData(msgId, &itemData);
    if (itemData != NULL && index != -1){
        switch (itemData->GetMessageType()){
        case em_image:
            switch (itemData->getMsgSendOrRecv()){
            case MESSAGE_SEND:
                itemData->setMsgFileStatus(success ? MSG_STATUS_FILE_SUC :
                                                     MSG_STATUS_FILE_UPLOAD_FAIL);
                if(!success)
                    itemData->setMsgStatus(MSG_STATUS_SEND_FAIL);
                itemData->SetUserMessage(fileUrl);
                break;
            case MESSAGE_RECV:
                //设置下载状态
                itemData->setMsgFileStatus(success ? MSG_STATUS_FILE_SUC:
                                                     MSG_STATUS_FILE_DOWN_FAIL);
                itemData->setFileLocalPath(fileUrl);
                break;
            default:
                break;
            }
            //更新
            if (_tableView != NULL){
                QModelIndex q_index = this->index(index, 0);
                TNMsgDetailItemWidget* item = static_cast<TNMsgDetailItemWidget*>(_tableView->indexWidget(q_index));
                if (item != NULL){
                    item->updateImage(success, fileUrl);
                }
            }else{
                //notice 日志
                QString qs_log = "[Notice] [TNMsgDetailModel] updateFileData image msgId:" + msgId +
                                " url:" + fileUrl + " failed";
                qInfo() << qs_log;
            }
            break;
        case em_file:
        case em_video:
            switch (itemData->getMsgSendOrRecv()){
            case MESSAGE_SEND://上传附件
                itemData->setMsgFileStatus(success ? MSG_STATUS_FILE_SUC :
                                                     MSG_STATUS_FILE_UPLOAD_FAIL);
                if(!success)
                    itemData->setMsgStatus(MSG_STATUS_SEND_FAIL);
                if (_tableView != NULL){
                    QModelIndex q_index = this->index(index, 0);
                    TNMsgDetailItemWidget* item = static_cast<TNMsgDetailItemWidget*>(_tableView->indexWidget(q_index));
                    if (item != NULL){
                        if (success){
                            itemData->SetUserMessage(fileUrl);
                        }
                        item->endProgressBar(success);
                    }
                }
                break;
            case MESSAGE_RECV://下载附件
            case MESSAGE_CONVERT:
                itemData->setMsgFileStatus(success ? MSG_STATUS_FILE_SUC :
                                                     MSG_STATUS_FILE_DOWN_FAIL);
                if (_tableView != NULL){
                    QModelIndex q_index = this->index(index, 0);
                    TNMsgDetailItemWidget* item = static_cast<TNMsgDetailItemWidget*>(_tableView->indexWidget(q_index));
                    if (item != NULL){
                        if (success){
                            itemData->setFileLocalPath(fileUrl);
                        }
                        item->onFileDownloadFinish(success, fileUrl, msgId);
                    }
                }
                break;
            default:
                break;
            }
        default:
            break;
        }
    }else{
        qInfo() << "[Notice] [TNMsgDetailModel] updateFileData fialed, can not find msgId:" << msgId;
    }
	return itemData;
}

TNModelUserMessage* TNMsgDetailModel::updateAudioDataReaded(const QString& msgId,
	bool isReaded /* = true */)
{
	if (msgId.isEmpty())
		return NULL;
	TNModelUserMessage *itemData = NULL;
	int index = findItemData(msgId, &itemData);

	if (itemData != NULL && index != -1){
		switch (itemData->GetMessageType()){
		case em_audio:
            itemData->setMsgFileStatus(MSG_STATUS_FILE_READED);
			if (_tableView != NULL){
				QModelIndex q_index = this->index(index, 0);
				TNMsgDetailItemWidget* item = static_cast<TNMsgDetailItemWidget*>(_tableView->indexWidget(q_index));
				if (item != NULL){
					item->stopPlay();
				}
			}
			break;
		default:
			break;
		}
	}
	return itemData;
}

TNModelUserMessage* TNMsgDetailModel::updateMsgFileProgress(const QString &msgId, int progress)
{
    if(msgId.isEmpty())
        return NULL;
    TNModelUserMessage *itemData = NULL;
    int index = findItemData(msgId, &itemData);
    if (itemData != NULL && index != -1){
        switch (itemData->GetMessageType()){
        case em_file:
        case em_image:
        case em_video:
            if (_tableView != NULL){
                QModelIndex q_index = this->index(index, 0);
                TNMsgDetailItemWidget* item = static_cast<TNMsgDetailItemWidget*>(_tableView->indexWidget(q_index));
                if (item != NULL){
                    item->updateProgressBar(itemData->GetMessageType(),progress);
                }
            }
            break;
        default:
            break;
        }
    }
    return itemData;
}

TNModelUserMessage* TNMsgDetailModel::updateMsgFeedback(const QString& msgId,
    int msg_status)
{
	if (msgId.isEmpty())
		return NULL;
	TNModelUserMessage *itemData = NULL;
	int index = findItemData(msgId, &itemData);

    if (itemData != NULL && index != -1){
        itemData->setMsgStatus((MSG_STATUS)msg_status);
        if (_tableView != NULL){
            QModelIndex q_index = this->index(index, 0);
            TNMsgDetailItemWidget* item = static_cast<TNMsgDetailItemWidget*>(_tableView->indexWidget(q_index));
            if (item != NULL){
                item->setStatusLabel(msg_status == MSG_STATUS_SEND_SUC);
            }
        }
        //如果名片不存在则在界面创建一条名片不存在的提示消息(在线)
        if(msg_status == MSG_STATUS_SEND_FAIL_Card){
            TNModelUserMessage *card_no_message = new TNModelUserMessage;
            card_no_message->SetUserMessage(("名片不存在"));
            card_no_message->SetMessageType(em_card_not_exist);
            card_no_message->setTime(itemData->getTime());
            if(!insertData(card_no_message)){
                delete card_no_message;
                card_no_message = NULL;
            }
        }else if(msg_status == MSG_STATUS_SEND_FAIL_CoCard){
            TNModelUserMessage *card_no_message = new TNModelUserMessage;
            card_no_message->SetUserMessage(("该名片未被使用，暂时无法沟通"));
            card_no_message->SetMessageType(em_card_not_exist);
            card_no_message->setTime(itemData->getTime());
            if(!insertData(card_no_message)){
                delete card_no_message;
                card_no_message = NULL;
            }
        }else if(msg_status == MSG_STATUS_SEND_FAIL_OrCard){
            TNModelUserMessage *card_no_message = new TNModelUserMessage;
            card_no_message->SetUserMessage(("该名片不支持聊天"));
            card_no_message->SetMessageType(em_card_not_exist);
            card_no_message->setTime(itemData->getTime());
            if(!insertData(card_no_message)){
                delete card_no_message;
                card_no_message = NULL;
            }
        }
    }else{
        qInfo() << "[Notice] [TNMsgDetailModel] updateMsgFeedback fialed, can not find msgId:" << msgId;
    }
	return itemData;
}

TNModelUserMessage* TNMsgDetailModel::updateAudioDataDownloaded(const QString& msgId,
	const QString& fileUrl,
	bool success /* = true */)
{
	if (msgId.isEmpty())
		return NULL;
	TNModelUserMessage *itemData = NULL;
	int index = findItemData(msgId, &itemData);

	if (itemData != NULL && index != -1){
		switch (itemData->GetMessageType()){
        case em_audio://语音只有下载
            itemData->setMsgFileStatus(success ? MSG_STATUS_FILE_SUC : MSG_STATUS_FILE_DOWN_FAIL);
            itemData->setFileLocalPath(fileUrl);
			if (_tableView != NULL){
				QModelIndex q_index = this->index(index, 0);
				TNMsgDetailItemWidget* item = static_cast<TNMsgDetailItemWidget*>(_tableView->indexWidget(q_index));
				if (item != NULL){
					item->audioDownloadFinish(success, fileUrl);
				}
			}
			break;
		default:
			break;
		}
	}
	return itemData;
}

bool TNMsgDetailModel::insertData(int index, TNModelUserMessage *userMsg)
{
	int size = _listItemData.size();
	if (index > 0){
		TNModelUserMessage* pre_itemData = static_cast<TNModelUserMessage*>
			(_listItemData.at(index - 1));
		if (userMsg->GetMsgID() == pre_itemData->GetMsgID()){
            qInfo() << "TNMsgDetailModel insertData pre_itemData has a same msgId";
            return false;
		}
	}
    if (index >= 0 && index <= size)
    {   
        beginInsertRows(QModelIndex(), index, index);
		_mutex.lock();
        _listItemData.insert(index, userMsg);
		_mutex.unlock();
        endInsertRows();
    }
    return true;
}

bool TNMsgDetailModel::insertData(TNModelUserMessage *userMsg)
{
    return insertData(this->rowCount(), userMsg);
}

void TNMsgDetailModel::insertData(int index, LIST_MESSAGE &listUserMsg)
{
	QMutexLocker locker(&_mutex);
	if (listUserMsg.size() == 0)
		return;
    if (index >= 0 && index <= _listItemData.size())
    {
        beginInsertRows(QModelIndex(), index, index + listUserMsg.size() - 1);
        for (LIST_MESSAGE::iterator it = listUserMsg.begin(); it != listUserMsg.end(); it++)
        {
            _listItemData.insert(index, *it);	
        }
        endInsertRows();
    }
}

void TNMsgDetailModel::removeData(int index, int count)
{
    if (index >= 0 && index < _listItemData.size() && count > 0 && index + count <= _listItemData.size())
    {
        beginRemoveRows(QModelIndex(), index, index + count - 1);
        for (int i = index + count - 1; i >= index; i--)
        {
			_mutex.lock();
            delete _listItemData.at(i);
            _listItemData.removeAt(i);
			_mutex.unlock();
        }
        endRemoveRows();
    }
}

void TNMsgDetailModel::removeData(TNModelUserMessage *userMsg)
{
    if (userMsg == NULL)
        return;
	
    for (int i = 0; i < _listItemData.size(); i++)
    {
        TNModelUserMessage *itemData = static_cast<TNModelUserMessage*>(_listItemData.at(i));
		if (itemData->GetMsgID() == userMsg->GetMsgID())
        {
            beginRemoveRows(QModelIndex(), i, i);
			_mutex.lock();
            delete itemData;
            _listItemData.removeAt(i);
			_mutex.unlock();
            endRemoveRows();
            break;
        }
    }
}

TNModelUserMessage* TNMsgDetailModel::lastData()
{
	QMutexLocker locker(&_mutex);
    if (!_listItemData.isEmpty())
        return static_cast<TNModelUserMessage*>(_listItemData.last());

    return NULL;
}

QVariant TNMsgDetailModel::data(const QModelIndex &index, qint32 role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::TextAlignmentRole)
    {
		TNModelUserMessage *userMessage = static_cast<TNModelUserMessage*>(_listItemData.at(index.row()));
        if (userMessage != NULL)
        {
            if (userMessage->getMessageSendFrom() == GROUP_MESSAGE_TYPE_CURRENT_ACCOUNT)
			{
				return qint32(Qt::AlignRight | Qt::AlignVCenter);
			}
			else
			{
				return qint32(Qt::AlignLeft | Qt::AlignVCenter);
			}
        }
        return qint32 (Qt::AlignLeft | Qt::AlignVCenter);
    }
    else if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
         if (index.row() > _listItemData.size())
            return QVariant();

        return (qint64)_listItemData.at(index.row());
    }

    return QVariant();
}

void TNMsgDetailModel::setTableView(QTableView* tableView)
{
	_tableView = tableView;
}

int TNMsgDetailModel::findItemData(const QString& msgId,TNModelUserMessage** itemData)
{
	int index = -1;
	if (msgId.isEmpty()){
		return index;
	}
	QMutexLocker locker(&_mutex);
	for (int i = 0; i < _listItemData.size(); i++)
	{
		TNModelUserMessage* tempItemData = static_cast<TNModelUserMessage*>(_listItemData.at(i));
		if (tempItemData->GetMsgID() == msgId)
		{
			index = i;
			*itemData = tempItemData;
			break;
		}
	}
	return index;
}

int TNMsgDetailModel::getModelSize()
{
	return _listItemData.size();
}

TNModelUserMessage* TNMsgDetailModel::updateAvatorIcon(const QString& msgId,
	const QString& file_path)
{
	//notice 日志
    QString qs_log = "[Notice] [TNMsgDetailModel] msgId:" + msgId + " updateAvatorIcon start filepath:" + file_path;
    qInfo() << qs_log;
	if (msgId.isEmpty())
		return NULL;
	TNModelUserMessage *itemData = NULL;
	int index = findItemData(msgId, &itemData);

	if (itemData != NULL && index != -1){
		itemData->SetPhotoIcon(file_path);//设置发送,接收状态
		if (_tableView != NULL){
			QModelIndex q_index = this->index(index, 0);
			TNMsgDetailItemWidget* item = static_cast<TNMsgDetailItemWidget*>(_tableView->indexWidget(q_index));
			if (item != NULL){
				item->setHeadpic(file_path);
			}
		}else{
			//Notice日志
            qs_log = "[Notice] [TNMsgDetailModel] msgId:" + msgId + " updateAvatorIcon filepath:" + file_path
				+ "failed _tableView=NULL";
            qInfo() << qs_log;
		}
	}else{
		//Notice日志
        qs_log = "[Notice] [TNMsgDetailModel] msgId:" + msgId + " updateAvatorIcon filepath:" + file_path
			+ "failed itemData=NULL";
        qInfo() << qs_log;
	}
	//Notice日志
    qs_log = "[Notice] [TNMsgDetailModel] msgId:" + msgId + " updateAvatorIcon filepath:" + file_path
		+ " end";
    qInfo() << qs_log;
	return itemData;
}

void TNMsgDetailModel::updateAvatorIconByFeedId(const QString &feedId, const QString &file_path)
{
    if(feedId.isEmpty()) {
        return;
    }
    int index = 0;
    _mutex.lock();
    for(TNModelItemBase *data : _listItemData){
        TNModelUserMessage* message = static_cast<TNModelUserMessage*> (data);
        if(message->getFromId() == feedId){
            if (_tableView != NULL){
                QModelIndex q_index = this->index(index, 0);
                TNMsgDetailItemWidget* item = static_cast<TNMsgDetailItemWidget*>(_tableView->indexWidget(q_index));
                if(item != NULL){
                    item->setHeadpic(file_path);
                }
            }
        }
        index++;
    }
    _mutex.unlock();
}

TNModelUserMessage* TNMsgDetailModel::updateMsgFileStatus(const QString &msgId, TNMsgFileStatus status)
{
    TNModelUserMessage* itemData = NULL;
    if(findItemData(msgId, &itemData) != -1 && itemData != NULL){
        itemData->setMsgFileStatus(status);
    }
    return itemData;
}

TNModelUserMessage* TNMsgDetailModel::updateMsgStatus(const QString& msgId,TNMsgStatus status)
{
    TNModelUserMessage* itemData = NULL;
    if(findItemData(msgId, &itemData) != -1 && itemData != NULL){
        itemData->setMsgStatus(status);
    }
    return itemData;
}

QModelIndex TNMsgDetailModel::getMsgIndex(const QString &msgId)
{
    TNModelUserMessage* temp = NULL;
    int index = findItemData(msgId,&temp);
    if(index != -1 && temp != NULL){
        return this->index(index,0);
    }
    return QModelIndex();
}

QStringList TNMsgDetailModel::mimeTypes() const
{
    return TNTableModel::mimeTypes();
}

Qt::DropActions TNMsgDetailModel::supportedDragActions() const
{
    return TNTableModel::supportedDragActions();
    //return Qt::CopyAction | Qt::MoveAction;
}

QMimeData* TNMsgDetailModel::mimeData(const QModelIndexList &indexes) const
{
    return TNTableModel::mimeData(indexes);
}

bool TNMsgDetailModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    return TNTableModel::dropMimeData(data,action,row,column,parent);
}

void TNMsgDetailModel::updateSendName(const QString& feedId,const QString& remark)
{
    int index = 0;
    _mutex.lock();
    for(TNModelItemBase* item: _listItemData){
        TNModelUserMessage* message = static_cast<TNModelUserMessage*> (item);
        if(message->getSessionType() == MSG_BIZ_GROUPCHAT){
            if(message->getFromId() == feedId){
                message->setRemark(remark);
                //界面更新
                QModelIndex q_index = this->index(index, 0);
                TNMsgDetailItemWidget* item = static_cast<TNMsgDetailItemWidget*>(_tableView->indexWidget(q_index));
                if (item != NULL){
                    item->updateSendName();
                }
            }
        }
        index++;
    }
    _mutex.unlock();
}
