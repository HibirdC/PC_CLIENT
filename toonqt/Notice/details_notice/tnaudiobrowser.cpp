#include "tnaudiobrowser.h"
#include "model_data/TNModelUserMessage.h"
#ifdef __APPLE__
#include "audio/macosx/playsound.h"
#else
#include "audio/tnplayaudio.h"
#endif
#include "TNIMCoreClient.h"
#include "emotion/TNEmojiSingleton.h"
#include <QPixmap>
#include <QMouseEvent>


TNAudioBrowser::TNAudioBrowser(bool isShowRevoke, TNModelUserMessage* data,
	TNMsgDetailModel* msgModel, QWidget *parent /* = 0 */)
	: QWidget(parent)
	, _playMovie(NULL)
	, _tnModelUserMsg(data)
	, _tnDetailModel(msgModel)
	, _isShowRevoke(isShowRevoke)
{
    ui.setupUi(this);
    Q_ASSERT(_tnDetailModel);
#ifdef __APPLE__
    _playSound = PlaySound::getInstance();
    _playSound->setMsgDetailModel(_tnDetailModel);
#else
    _tnPlayAudio = TNPlayAudio::getInstance();
    _tnPlayAudio->setMsgDetailModel(_tnDetailModel);
#endif
	init();
}

TNAudioBrowser::~TNAudioBrowser()
{
	_playMovie->stop();
	delete _playMovie;
	_playMovie = NULL;
}

void TNAudioBrowser::init()
{
	//初始化状态框
    ui.label_is_readed->setData(_tnModelUserMsg);
	ui.label_is_readed->setModel(_tnDetailModel);
	/////////////////////////////////////////////
	QPixmap pix;
	//时长
    int audio_time = _tnModelUserMsg->getAudioTime();
	QString s_audio_time = QString("%1\"").arg(audio_time);
    if (_tnModelUserMsg->getMessageSendFrom() == GROUP_MESSAGE_TYPE_CURRENT_ACCOUNT){
		ui.widget_audio_right->setCursor(QCursor(Qt::PointingHandCursor));
		ui.widget_audio_left->hide();
		_playMovie = new QMovie(":/Resources/audio_play_gray.gif");

		ui.label_audio_time_right->setText(s_audio_time);

		if (pix.load(":/Resources/audio_default_gray.png")){
			ui.label_audio_movie_right->setPixmap(pix);
		}
		ui.label_is_readed->setStatus(TNStatusLabel::em_readed);
	}
    else if (_tnModelUserMsg->getMessageSendFrom() == GROUP_MESSAGE_TYPE_OTHER){
		ui.widget_audio_left->setCursor(QCursor(Qt::PointingHandCursor));
		ui.widget_audio_right->hide();
		_playMovie = new QMovie(":/Resources/audio_play_blue.gif");
		ui.label_audio_time_left->setText(s_audio_time);

		if (pix.load(":/Resources/audio_default_blue.png")){
			ui.label_audio_movie_left->setPixmap(pix);
		}
	}
	_playMovie->setScaledSize(QSize(12, 17));
	this->setMaximumWidth(244);

	//是否下载
    switch(_tnModelUserMsg->getMsgFileStatus()){
    case MSG_STATUS_FILE_SUC:{
        //是否已读
        QString localPath = _tnModelUserMsg->getFileLocalPath();
        QFile  file(localPath);
        if(file.exists()){
            if(_tnModelUserMsg->getMyFeedId() == _tnModelUserMsg->getFromId()){
                ui.label_is_readed->setStatus(TNStatusLabel::em_readed);
            }else{
                ui.label_is_readed->setStatus(TNStatusLabel::em_unread);
            }
        }else{
            ui.label_is_readed->setStatus(TNStatusLabel::em_loading);
        }
        }
        break;
    case MSG_STATUS_FILE_READED:
        ui.label_is_readed->setStatus(TNStatusLabel::em_readed);
        break;
    case MSG_STATUS_FILE_DOWNLOADING:
    case MSG_STATUS_FILE_UNDOWN:
        ui.label_is_readed->setStatus(TNStatusLabel::em_loading);
        break;
    case MSG_STATUS_FILE_DOWN_FAIL:
        ui.label_is_readed->setStatus(TNStatusLabel::em_failed);
        break;
    default:
        break;
    }

	_pop_menu = new QMenu();
	QAction *revokeAction = new QAction(this);
	QAction *deleteMsg = new QAction(this);
	deleteMsg->setText(("删除"));
    revokeAction->setText(("撤回"));
	revokeAction->setVisible(_isShowRevoke);
	//清除原有菜单
	_pop_menu->addAction(deleteMsg);
	_pop_menu->addAction(revokeAction);

	connect(revokeAction, SIGNAL(triggered()), this, SIGNAL(actionRevote()));
	connect(deleteMsg, SIGNAL(triggered()), this, SIGNAL(actionDeleteMsg()));
}

void TNAudioBrowser::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton){
		//点击播放
        if (_tnModelUserMsg->getMsgStatus() == MSG_STATUS_SEND_SUC &&
                (_tnModelUserMsg->getMsgFileStatus() == MSG_STATUS_FILE_SUC ||
                 _tnModelUserMsg->getMsgFileStatus() == MSG_STATUS_FILE_READED)
           ){
			//已读
			ui.label_is_readed->setStatus(TNStatusLabel::em_readed);
			///////////////////////////////////////////////////////
            if (_tnModelUserMsg->getMessageSendFrom() == GROUP_MESSAGE_TYPE_CURRENT_ACCOUNT){
				ui.label_audio_movie_right->setMovie(_playMovie);
			}
            else if (_tnModelUserMsg->getMessageSendFrom() == GROUP_MESSAGE_TYPE_OTHER){
				ui.label_audio_movie_left->setMovie(_playMovie);
			}
			_playMovie->start();
#ifdef __APPLE__
            _playSound->Play(*_tnModelUserMsg);
#else
            _tnPlayAudio->playAudio(*_tnModelUserMsg);
#endif
            _tnModelUserMsg->setMsgFileStatus(MSG_STATUS_FILE_READED);
            //更新已读状态
			TNIMCoreClient* client = TNIMCoreClient::GetIMClient();
            client->SetMsgFileStatus(_tnModelUserMsg->GetMsgID(),_tnModelUserMsg->getSessionId(),MSG_STATUS_FILE_READED);
		}
	}
}

void TNAudioBrowser::stopPlay()
{
	_playMovie->stop();

	QPixmap pix;
    if (_tnModelUserMsg->getMessageSendFrom() == GROUP_MESSAGE_TYPE_CURRENT_ACCOUNT){
		if (pix.load(":/Resources/audio_default_gray.png")){
			ui.label_audio_movie_right->setPixmap(pix);
		}
	}
    else if (_tnModelUserMsg->getMessageSendFrom() == GROUP_MESSAGE_TYPE_OTHER){
		if (pix.load(":/Resources/audio_default_blue.png")){
			ui.label_audio_movie_left->setPixmap(pix);
		}
	}
}

void TNAudioBrowser::downloadFinished(const QString& fileUrl,bool success)
{
    _tnModelUserMsg->setMsgFileStatus(success ? MSG_STATUS_FILE_SUC :
                                                MSG_STATUS_FILE_DOWN_FAIL);
    if (success){
        if(_tnModelUserMsg->getMyFeedId() == _tnModelUserMsg->getFromId()){
            ui.label_is_readed->setStatus(TNStatusLabel::em_readed);
        }else{
            ui.label_is_readed->setStatus(TNStatusLabel::em_unread);
        }
    }else{
        ui.label_is_readed->setStatus(TNStatusLabel::em_failed);
    }
}

void TNAudioBrowser::contextMenuEvent(QContextMenuEvent *e)
{
	_pop_menu->exec(QCursor::pos());
}
