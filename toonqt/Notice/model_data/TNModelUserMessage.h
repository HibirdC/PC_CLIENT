#ifndef TNMODELUSERMESSAGE_H
#define TNMODELUSERMESSAGE_H
#include <QString>
#include <QDateTime>
#include <QSize>
#include <QImage>

#include "NoticeEnum.h"
#include "TNTableModel.h"
#include "TNMessageListAdapter.h"
#include "TNIMCoreClient.h"
/*
消息具体信息
*/

class TNModelUserMessage : public TNModelItemBase
{
public:
	TNModelUserMessage();
	~TNModelUserMessage();

public:
	void SetAtType(int nType){ _atType = nType; }
	int  GetAtType(){ return _atType; }
	QList<QString> GetAtFeeds(){ return _atFeeds; }
	void SetAtFeeds(QList<QString> atFeeds){ _atFeeds = atFeeds; }

	void SetMessageType(MESSAGE_TYPE type);
	MESSAGE_TYPE GetMessageType();

	void setSessionType(TNBizType sessionType){ _sessionType = sessionType; }
	TNBizType getSessionType(){ return _sessionType; }
	

	void setMessageSendFrom(messageSendFrom from);
	messageSendFrom  getMessageSendFrom();

	void SetMsgID(const QString& msgID);
	QString GetMsgID();

	void SetUserMessage(const QString & message);
	QString GetUserMessage();

	QString GetPhotoIcon();
	void SetPhotoIcon(const QString& photoIcon);
	QString getAvatorUrl(){ return _photoUrl; }
	void setAvatorUrl(const QString& photoUrl){ _photoUrl = photoUrl; }
	QString GetFeedName(){ return _curFeedName; };
	void SetFeedName(const QString& feedName){ _curFeedName = feedName; }
	QDateTime getTime();
	void setTime(QDateTime time=QDateTime::currentDateTime());

	void setPicSize(const QSize& picSize);
	QSize getPicSize();

	void setFileSize(qint64 size);
	qint64 getFileSize();

	void setFileName(const QString& fileName);
	QString getFileName();

	void setFileSuffix(const QString& suffix);
	QString getFileSuffix();

	void setMyFeedId(const QString& myFeedId){ _myFeedId = myFeedId; }
	QString getMyFeedId(){ return _myFeedId; }

	void setSessionId(const QString &sessionId){ _sessionId = sessionId; }
	QString getSessionId(){ return _sessionId; }

	void setToFeedId(const QString& toFeedId){ _toFeedId = toFeedId; }
	QString getToFeedId(){ return _toFeedId; }

	void setUserId(const QString& userId){ _userId = userId; }
	QString getUserId(){ return _userId; }

	void setAudioTime(int audio_time){ _audioTime = audio_time; }
	int getAudioTime() { return _audioTime; }
	messageRecvSend getMsgSendOrRecv(){ return _msgSendRecv; }
	void setMsgSendOrRecv(messageRecvSend sendOrRecv){ _msgSendRecv = sendOrRecv; }
	//文件在本地的路径
	QString getFileLocalPath(){ return _fileLocalPath; }
	void setFileLocalPath(const QString& path){ _fileLocalPath = path; }
	void setFromId(const QString& fromId){ _fromId = fromId; }
	QString getFromId(){ return _fromId; }
    //消息状态
    void setMsgStatus(TNMsgStatus status){_status = status;}
    TNMsgStatus getMsgStatus(){return _status;}
    //文件上传/下载状态
    void setMsgFileStatus(TNMsgFileStatus status){_fileStatus = status;}
    TNMsgFileStatus getMsgFileStatus(){return _fileStatus;}
    //备注
    QString getRemark()const{return _reMark;}
    void setRemark(const QString& remark){_reMark = remark;}
private:
	QString			_msgID;
    MESSAGE_TYPE	_messageType = em_text;
	QString			_strMessage;
	QString			_photoIcon;
	QString			_curFeedName;//当前展示的feed名称
    QString			_photoUrl;//头像远程地址
	//多端多活区分该条消息是发送还是接收
    messageRecvSend _msgSendRecv = MESSAGE_SEND;
	//消息从哪儿发出,本人的消息,别人的消息
    messageSendFrom	_msgSendFrom = GROUP_MESSAGE_TYPE_CURRENT_ACCOUNT;
	//消息发送/接收的时间
	QDateTime		_time;
	//图片的size
	QSize			_picSize;
	//文件参数
	qint64			_fileSize;
	QString			_fileName;
	QString			_fileSuffix;
	QString			_fileLocalPath;//文件在本地的路径
	//群聊，单聊，通知
    TNBizType		_sessionType = MSG_BIZ_UNSHOW;
	QString         _sessionId;
	QString			_myFeedId;
	QString			_toFeedId;
	QString			_fromId;
	QString			_userId;
	QString			_topic;//群聊用
    //bool			_bReaded;//是否已读
	int				_audioTime;//音频时长
    TNMsgStatus     _status;//消息状态(发送三个状态,接受全为成功)
    TNMsgFileStatus _fileStatus;//图片,附件，语音,视频的上传下载状态
    int             _atType;//是否at了别人
	QList<QString>  _atFeeds;
    QString 		_reMark;//备注
};

#endif // TNMODELUSERMESSAGE_H
