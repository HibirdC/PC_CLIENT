#ifndef TNPLAYAUDIO_H
#define TNPLAYAUDIO_H

#include <QObject>
#include <QMediaPlayer>
#include <list>
#include "model_data/TNModelUserMessage.h"
using namespace std;

class TNMsgDetailModel;

class TNPlayAudio : public QObject
{
	Q_OBJECT
public:
	~TNPlayAudio();
	void playAudio(TNModelUserMessage message);
    void stopPalyAudio();
    static TNPlayAudio* getInstance();
    void setMsgDetailModel(TNMsgDetailModel* msgModel);
signals:
	void playFinished(QMediaPlayer::MediaStatus status);
private:
    TNPlayAudio(QObject *parent = 0);
	void playNextAudio();
	void stopPlayCur(TNModelUserMessage message);
private slots:
	void handleError(QMediaPlayer::Error);
	void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
	void onMediaChanged(const QMediaContent &media);
private:
	QMediaPlayer*				_player;
    int							_currentPlayindex;
	TNModelUserMessage			_oldUserMsg;
	TNMsgDetailModel*			_tnDetailModel;
};

#endif // TNPLAYAUDIO_H
