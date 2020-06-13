#include <QHBoxLayout>
#include "videoplayer.h"
#include "videowidget.h"

VideoPlayer::VideoPlayer(int width,int height,QString video_path,QWidget *parent) :
    QWidget(parent),
    _video_player(new QMediaPlayer(this)),
    _video_width(width),
    _video_height(height),
    _mc_button_size(QSize(20,20)),
    _mc_button_space(6),
    _video_path(video_path){
    init();
}

VideoPlayer::~VideoPlayer(){
}

void VideoPlayer::init(){
    VideoWidget *video_widget = new VideoWidget;
    video_widget->setMinimumSize(_video_width,_video_height);

    QHBoxLayout* operate_layout = new QHBoxLayout();
    _btn_volumn = new QPushButton(this);
    _btn_volumn->setText(tr("volumn"));

    _btn_play_pause = new QPushButton(this);
    _btn_play_pause->setText(tr("play"));

    _lable_time_played = new QLabel(this);
    _lable_time_played->setText(tr("00:00:00"));

    _video_slider = new QSlider(Qt::Horizontal,this);

    _lable_time_last = new QLabel(this);
    _lable_time_last->setText(tr("00:00:00"));

    operate_layout->addWidget(_btn_volumn);
    operate_layout->addWidget(_btn_play_pause);
    operate_layout->addWidget(_lable_time_played);
    operate_layout->addWidget(_video_slider);
    operate_layout->addWidget(_lable_time_last);
    operate_layout->setContentsMargins(0,0,0,0);
    operate_layout->setSpacing(6);

    QVBoxLayout* v_layout = new QVBoxLayout();
    v_layout->addWidget(video_widget);
    v_layout->addLayout(operate_layout);
    v_layout->setMargin(0);

    this->setLayout(v_layout);

    _video_player->setMedia(QUrl::fromLocalFile(_video_path));

    _video_player->setVideoOutput(video_widget->videoSurface());
    connect(_video_player, SIGNAL(stateChanged(QMediaPlayer::State)),
            this, SLOT(mediaStateChanged(QMediaPlayer::State)));
    connect(_video_player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    connect(_video_player, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));

    connect(_video_slider, SIGNAL(sliderMoved(int)),this, SLOT(setPosition(int)));

    connect(_btn_play_pause,SIGNAL(clicked(bool)),this,SLOT(onPlay(bool)));
}

void VideoPlayer::onPlay(bool)
{
    switch(_video_player->state()) {
    case QMediaPlayer::PlayingState:
        _video_player->pause();
        break;
    default:
        _video_player->play();
        break;
    }
}

void VideoPlayer::onVolumnClicked(bool checked){
    Q_UNUSED(checked);
    //_volumn_slider->setGeometry();
}

void VideoPlayer::durationChanged(qint64 duration)
{
    _video_slider->setRange(0,duration);
}

void VideoPlayer::positionChanged(qint64 position)
{
    _video_slider->setValue(position);
}

void VideoPlayer::mediaStateChanged(QMediaPlayer::State state)
{
    switch(state) {
    case QMediaPlayer::PlayingState:
        _btn_play_pause->setText("pause");
        break;
    default:
        _btn_play_pause->setText("play");
        break;
    }
}

void VideoPlayer::setPosition(int position){
    _video_player->setPosition(position);
}
