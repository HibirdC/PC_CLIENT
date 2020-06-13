#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QPushButton>
#include <QSlider>
#include <QLabel>


class VideoPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit VideoPlayer(int width,int height,QString video_path,QWidget *parent = 0);
    ~VideoPlayer();

    void init();
private slots:
    void onVolumnClicked(bool);
    void mediaStateChanged(QMediaPlayer::State);
    void positionChanged(qint64);
    void durationChanged(qint64);
    void setPosition(int);
    void onPlay(bool);
private:
    QMediaPlayer*	_video_player;
    int 			_video_width;
    int 			_video_height;
    QPushButton*	_min_button;
    QPushButton*	_max_button;
    QPushButton*	_close_button;
    QSize			_mc_button_size;
    int				_mc_button_space;
    QSlider*		_volumn_slider;
    QString 		_video_path;

    QPushButton* 	_btn_volumn;
    QPushButton*	_btn_play_pause;
    QSlider*		_video_slider;
    QLabel*			_lable_time_played;
    QLabel*			_lable_time_last;
};

#endif // VIDEOPLAYER_H
