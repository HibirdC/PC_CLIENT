#include "tnstatuslabel.h"
#include "TNMsgDetailModel.h"
#include "network/tnsendimsg.h"
#include <QFile>

TNStatusLabel::TNStatusLabel( QWidget *parent /* = 0 */)
	: QLabel(parent)
	, _loadingMovie(NULL)
	, _detailModel(NULL)
    , _data(NULL)
    , _tnSendIMsg(TNSendIMsg::getInstance())
{
}

TNStatusLabel::~TNStatusLabel()
{
	if (_loadingMovie != NULL){
		delete _loadingMovie;
		_loadingMovie = NULL;
	}
}

void TNStatusLabel::mousePressEvent(QMouseEvent *ev)
{
	switch (_status)
	{
	case TNStatusLabel::em_failed://重新发送/下载
        switch (_data->getMsgSendOrRecv())
		{
		case MESSAGE_RECV:
			reRecv();
			break;
		case MESSAGE_SEND:
			reSend();
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void TNStatusLabel::setStatus(MESSAGE_STATUS status)
{
	switch (status)
	{
	case TNStatusLabel::em_readed:
		setReaded();
		break;
	case TNStatusLabel::em_unread:
		setUnRead();
		break;
	case TNStatusLabel::em_loading:
		setLoading();
		break;
	case TNStatusLabel::em_loaded:
		setLoaded();
		break;
	case TNStatusLabel::em_failed:
		setFailed();
		break;
	case TNStatusLabel::em_successed:
		setSuccessed();
		break;
	default:
		break;
	}
	_status = status;
}

void TNStatusLabel::setUnRead()
{
	setCursor(Qt::ArrowCursor);
	QPixmap pix;
	if (pix.load(":/Resources/unread.png")){
		setPixmap(pix);
	}
	show();
}

void TNStatusLabel::setReaded()
{
	setCursor(Qt::ArrowCursor);
	hide();
}

void TNStatusLabel::setLoading()
{
	setCursor(Qt::ArrowCursor);
	if (_loadingMovie == NULL){
		_loadingMovie = new QMovie(":/Resources/toolWidget/loading_spinner.gif");
	}
	Q_ASSERT(_loadingMovie);
	_loadingMovie->setScaledSize(size());
	setAttribute(Qt::WA_NoSystemBackground);
	setMovie(_loadingMovie);
	_loadingMovie->start();
	show();
}

void TNStatusLabel::setLoaded()
{
	setCursor(Qt::ArrowCursor);
	if (_loadingMovie != NULL){
		_loadingMovie->stop();
		delete _loadingMovie;
		_loadingMovie = NULL;
	}
	hide();
}

void TNStatusLabel::setFailed()
{
	setCursor(Qt::PointingHandCursor);
	if (_loadingMovie != NULL){
		_loadingMovie->stop();
		delete _loadingMovie;
		_loadingMovie = NULL;
	}
	QPixmap pix;
	if (pix.load(":/Resources/prompt_fill.png")){
		setPixmap(pix);
	}
	show();
}

void TNStatusLabel::setSuccessed()
{
	if (_loadingMovie != NULL){
		_loadingMovie->stop();
		delete _loadingMovie;
		_loadingMovie = NULL;
	}
	setCursor(Qt::ArrowCursor);
	hide();
}

void TNStatusLabel::reSend()
{
	TNModelUserMessage* itemData = NULL;
    int index = _detailModel->findItemData(_data->GetMsgID(), &itemData);
	if (itemData != NULL && index != -1){
        TNModelUserMessage* newItemData = new TNModelUserMessage(*itemData);
        //删除消息
        _detailModel->removeData(itemData);
        itemData = NULL;
        ///////////////////////////////////
        newItemData->setTime();
        newItemData->setMsgStatus(MSG_STATUS_RESEND);
        TNIMCoreClient::GetIMClient()->SetMsgSendStatus(newItemData->GetMsgID(),
            newItemData->getSessionId(),
            MSG_STATUS_SENDING);
        switch (newItemData->GetMessageType()) {
        case em_file:
        case em_image:
            if((newItemData->getMsgFileStatus() != MSG_STATUS_FILE_SUC
                    && QFile::exists(newItemData->getFileLocalPath()))
                    || newItemData->GetUserMessage().isEmpty()){
                newItemData->setMsgFileStatus(MSG_STATUS_FILE_UPLOADING);
                TNIMCoreClient::GetIMClient()->SetMsgFileStatus(newItemData->GetMsgID(),
                    newItemData->getSessionId(),
                    MSG_STATUS_FILE_UPLOADING);
            }
            break;
        default:
            break;
        }
        if(!_detailModel->insertData(newItemData)){
            delete newItemData;
            return;
        }
        emit reSend(*newItemData);
	}
}

void TNStatusLabel::reRecv()
{
    if(_data == NULL)
        return;
    switch (_data->GetMessageType()){
    case em_image:
        _data->setMsgFileStatus(MSG_STATUS_FILE_DOWNLOADING);
        _tnSendIMsg->DownloadImage(*_data);
        setLoading();
        break;
    case em_audio:
        _data->setMsgFileStatus(MSG_STATUS_FILE_DOWNLOADING);
        _tnSendIMsg->DownloadAudio(*_data);
        setLoading();
        break;
    default:
        break;
    }
}

void TNStatusLabel::setData(TNModelUserMessage* data)
{
	_data = data;
}

void TNStatusLabel::setModel(TNMsgDetailModel* detailModel)
{
	_detailModel = detailModel;
    connect(this,SIGNAL(reSend(TNModelUserMessage)),
        _detailModel,SIGNAL(reSendData(TNModelUserMessage)));
}
