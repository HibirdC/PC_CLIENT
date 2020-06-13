#ifndef TNAUDIOBROWSER_H
#define TNAUDIOBROWSER_H

#include <QWidget>
#include <QMovie>
#include <QMenu>

#include "model_data/TNModelUserMessage.h"
#include "ui_tnaudiobrowser.h"

#ifdef __APPLE__
class PlaySound;
#else
class TNPlayAudio;
#endif
class TNMsgDetailModel;

class TNAudioBrowser : public QWidget
{
	Q_OBJECT

public:
    TNAudioBrowser(bool isShowRevoke,TNModelUserMessage* data,
		TNMsgDetailModel* msgModel,
		QWidget *parent = 0);
	void contextMenuEvent(QContextMenuEvent *e);
	~TNAudioBrowser();

	void stopPlay();
	void downloadFinished(const QString& fileUrl,bool success);
protected:
	void mousePressEvent(QMouseEvent *event);
private:
	void init();
private:
	Ui::TNAudioBrowser	ui;
	QMovie*				_playMovie;
    TNModelUserMessage  *_tnModelUserMsg;
	TNMsgDetailModel*	_tnDetailModel;
	QMenu			*_pop_menu;
	bool            _isShowRevoke;
#ifdef __APPLE__
    PlaySound*			_playSound;
#else
    TNPlayAudio*		_tnPlayAudio;
#endif
signals:
	void actionRevote();
	void actionDeleteMsg();
};

#endif // TNAUDIOBROWSER_H
