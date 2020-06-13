#include <QMediaContent>
#include "tnplayaudio.h"
#include "details_notice/TNMsgDetailModel.h"

TNPlayAudio::TNPlayAudio(QObject *parent /* = 0 */)
	: QObject(parent)
	, _player(new QMediaPlayer(this))
	, _currentPlayindex(0)
    , _tnDetailModel(NULL)
{
	connect(_player, SIGNAL(error(QMediaPlayer::Error)),
		this,SLOT(handleError(QMediaPlayer::Error)));
	connect(_player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),
		this, SLOT(onMediaStatusChanged(QMediaPlayer::MediaStatus)));
	connect(_player, SIGNAL(mediaChanged(const QMediaContent&)),
		this, SLOT(onMediaChanged(const QMediaContent&)));
}

TNPlayAudio* TNPlayAudio::getInstance()
{
    static TNPlayAudio pInsance;
    return &pInsance;
}

void TNPlayAudio::setMsgDetailModel(TNMsgDetailModel *msgModel)
{
    _tnDetailModel = msgModel;
}

TNPlayAudio::~TNPlayAudio()
{
	delete _player;
}

void TNPlayAudio::playAudio(TNModelUserMessage message)
{
	if (_oldUserMsg.GetMsgID() == message.GetMsgID()){
        if (_player->state() != QMediaPlayer::StoppedState){
			stopPlayCur(_oldUserMsg);
			return;
		}
	}
	
    if (_player->state() != QMediaPlayer::StoppedState){
        stopPlayCur(_oldUserMsg);
	}

	_oldUserMsg = message;
	QUrl url = QUrl::fromLocalFile(message.getFileLocalPath());
    QMediaContent content(url);
    _player->setMedia(content);
	_player->play();
}

void TNPlayAudio::stopPlayCur(TNModelUserMessage message)
{
	_player->stop();
	if (_tnDetailModel != NULL){
		_tnDetailModel->updateAudioDataReaded(message.GetMsgID());
	}
}

void TNPlayAudio::playNextAudio()
{

}

void TNPlayAudio::handleError(QMediaPlayer::Error error)
{
	if (_tnDetailModel != NULL){
		_tnDetailModel->updateAudioDataReaded(_oldUserMsg.GetMsgID());
	}
    QString qs_log = QString("[Notice] [TNPlayAudio] handleError:%1  %2").
            arg(error).arg(_player->errorString());
    qCritical() << qs_log;
}

void TNPlayAudio::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
	switch (status)
	{
	case QMediaPlayer::EndOfMedia:
		if (_tnDetailModel != NULL){
			_tnDetailModel->updateAudioDataReaded(_oldUserMsg.GetMsgID());
		}
		break;
	default:
		break;
	}
}

void TNPlayAudio::onMediaChanged(const QMediaContent &media)
{
    Q_UNUSED(media);
}

void TNPlayAudio::stopPalyAudio()
{
    if(_tnDetailModel == NULL){
        return;
    }
    if(_player->state() != QMediaPlayer::StoppedState){
        stopPlayCur(_oldUserMsg);
    }
}
