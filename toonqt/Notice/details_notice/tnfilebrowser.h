#ifndef TNFILEBROWSER_H
#define TNFILEBROWSER_H

#include <QWidget>
#include <QFileInfo>
#include "ui_tnfilebrowser.h"
#include "model_data/TNModelUserMessage.h"

class TNMsgDetailModel;
class TNSendIMsg;

class TNFileBrowser : public QWidget
{
	Q_OBJECT

public:
	/*
	参数说明:
	send_from 文件从哪里发出，别人发送和自己发送
	down_up 文件上传或者下载,上传和下载的样式不一样
	isFinshed 上传下载是否完成,界面样式不一样
	*/
    TNFileBrowser(bool isShowRevoke, TNModelUserMessage* data,
		TNMsgDetailModel* msgModel,
		QWidget *parent = 0);
	~TNFileBrowser();

	
	void setFileData();
	void setProgressBarValue(int value);
	void contextMenuEvent(QContextMenuEvent *e);
    void startProgressBar(int pos);
    void updateProgressBar(int pos);
    void endProgressBar(bool success);
	void onDownloadFinish(bool success, QString file, QString msgId);
	void startToDown(QString filePath);
protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void dragMoveEvent(QDragMoveEvent *event);
    virtual void dropEvent(QDropEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void dragEnterEvent(QDragEnterEvent *event);
private slots:
	void onClickedOpenfile();
	void onClickedOpendir();
    void onCancelUploading();
private:
	void setFileIcon(const QString& file_suffix);
	void InitMenu();
    void initStatus();
private:
	Ui::TNFileBrowser	ui;
    TNModelUserMessage	*_data;//消息内容

	TNMsgDetailModel	*_msgModel;
	TNSendIMsg*			_imClient;//发送接收文件类
    QMenu				*_pop_menu;
    bool            	_isShowRevoke;
    bool				_isShowSaveAs;
    static QString		_oldSelectPath;//上次另存为的路径
    bool 				_isCreatedDrag;
    QPoint 				_startPos;
    QString 			_currentMsgId;//当前消息的msgid
signals:
	void actionRevote();
	void actionSendForward();
    void delFileMsg();
    void cancelFileDownOrUploading(bool upload = true);
};

#endif // TNFILEBROWSER_H
