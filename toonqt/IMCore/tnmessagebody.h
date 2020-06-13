#ifndef TNMESSAGEBODY_H
#define TNMESSAGEBODY_H

#include <QString>
#include <QVariantMap>
#include <QList>
#include <QSize>

typedef enum tnimMessageStatus{
	TNIMMessageDraft = 0,
	TNIMMessageSending = 1,
	TNIMMessageSuccess = 2,
	TNIMMessageFailed = 3,
	TNIMMessageFailedCard = 4,				//个人名片，只可以删除
	TNIMMessageFailedCoCard = 5,			//同事名片，只可以回收
	TNIMMessageFailedOrCard = 6				//组织名片不可沟通	
}TNIMMessageSendStatus;

//消息类型：1：文本， 2：语音，3：图片，4：名片，5：位置，6:表情(暂时没用),7：常用信息(暂时没用)，8：收藏,9:常用地址(暂时没用), 10:视频, 11:礼物, 12:gif表情图片, 15:分享
typedef enum msgType{
	TNChatTypeText = 1,
	TNChatTypeVoice = 2,
	TNChatTypeImage = 3,
	TNChatTypeVcard = 4,
	TNChatTypeLocation = 5,
	TNChatTypeNotification = 6,  // 通知
	TNChatTypeSystem = 7,//系统消息，类似纯文本
	TNChatTypeCollect = 8,
	TNChatTypeAddress = 9,  // 没用
	TNChatTypeVedio = 10,
	TNChatTypeGift = 11,
	TNChatTypeGifImage = 12,
	TNChatTypeFiles = 14, //发文件
	TNChatTypeShare = 15,
	TNChatTypeRedCard = 16,
	TNChatTypeVRImage = 18,
	TNChatTypeVRVideo = 19,
	TNChatTypeTime = 1001,
	TNChatTypeGameIntroduce = 1002, //游戏展示
	TNChatTypeAlert = 1003,         //游戏Alert框
	TNChatTypeGPrompt = 1004,       //游戏提醒系统消息
	TNChatTypeGImage = 1005,         //游戏提醒系统消息
	TNChatTypeGResult = 1006,         //游戏结果展示页
	TNChatTypeSeparate = 1007,

	TNChatTypeRevoked = 2000

}TNMessageContentType;


class TNMessageBodyBase {
public:

	TNMessageBodyBase();
    virtual ~TNMessageBodyBase();

	static TNMessageBodyBase* instance(TNMessageContentType type);

	virtual void parse(QVariantMap &mapBody) = 0;
	virtual QVariantMap pack() = 0;

	QSize getViewSize(){
		return QSize(0, 0);
	}

	virtual QString getAbstractText()
	{
		return "";
	}

	bool isEmpty(){
		return true;
	}
};


//default
class TNMessageBodyDefault : public TNMessageBodyBase
{
public:
	TNMessageBodyDefault();
	~TNMessageBodyDefault();

	void parse(QVariantMap &mapBody);
	QVariantMap pack();
	QSize getViewSize();

private:
	QString _text;
};

class TNMessageBodyText : public TNMessageBodyBase
{
public:
	TNMessageBodyText();
	~TNMessageBodyText();

	virtual void parse(QVariantMap &mapBody);
	QVariantMap pack();
	QSize getViewSize();
	QString getAbstractText();
	bool isEmpty();

	void setText(QString text){
		_text = text;
	}

private:
	QString _text;
};

class TNMessageBodyNotification : public TNMessageBodyBase
{
public:
	TNMessageBodyNotification();
	~TNMessageBodyNotification();

	virtual void parse(QVariantMap &mapBody);
	QVariantMap pack();
	QSize getViewSize();
	QString getAbstractText();
	bool isEmpty();

	void setNotification(QString _json){
		_json = _json;
	}

private:
	QString _json;
};

class TNMessageBodySystemText : public TNMessageBodyBase
{
public:
	TNMessageBodySystemText();
	~TNMessageBodySystemText();

	virtual void parse(QVariantMap &mapBody);
	QVariantMap pack();
	QSize getViewSize();
	QString getAbstractText();
	bool isEmpty();

	void setText(QString text){
		_text = text;
	}
	void setAttributeText(QString& attribute){
		_attributedText = attribute;
	}

private:
	QString _text;
	QString _attributedText;
};

class TNMessageBodyFileBase : public TNMessageBodyBase
{
public:
	TNMessageBodyFileBase();
	~TNMessageBodyFileBase();

	virtual void parse(QVariantMap &mapBody);
	QVariantMap pack();
	QSize getViewSize();
	QString getAbstractText();
	bool isEmpty();

	void setUrl(QString url){
		_url = url;
	}

	void setSuffix(QString suffix)
	{
		_suffix = suffix;
	}
	void setSize(int size)
	{
		_size = size;
	}

private:
	QString _url;
	QString _suffix;
	int     _size;
};

class TNMessageBodyImage : public TNMessageBodyFileBase
{
public:
	TNMessageBodyImage();
	~TNMessageBodyImage();

	virtual void parse(QVariantMap &mapBody);
	QVariantMap pack();
	QString getAbstractText();
	QSize getViewSize();
	void setWdith(int w){
		_width = w;
	}

	void setHeight(int height)
	{
		_height = height;
	}

private:
	int  _width;
	int  _height;
};

class TNMessageBodyAttachment : public TNMessageBodyFileBase
{
public:
	TNMessageBodyAttachment();
	~TNMessageBodyAttachment();

	virtual void parse(QVariantMap &mapBody);
	QVariantMap pack();
	QString getAbstractText();
    void setFormat(const QString& format){
		_format = format;
	}

    void setDesc(const QString& desc)
	{
		_desc = desc;
	}

private:
	QString  _format;
	QString  _desc;
};


class TNMessageBodyVoice : public TNMessageBodyFileBase
{
public:
	TNMessageBodyVoice();
	~TNMessageBodyVoice();

	virtual void parse(QVariantMap &mapBody);
	QVariantMap pack();
	QString getAbstractText();
	void setTime(int time){
		_time = time;
	}

	void setReaded(int readed)
	{
		_readed = readed;
	}

private:
	int  _time;
	int  _readed;
};

class TNMessageBodyVideo : public TNMessageBodyBase
{
public:
	TNMessageBodyVideo();
	~TNMessageBodyVideo();

	virtual void parse(QVariantMap &mapBody);
	QVariantMap pack();
	QString getAbstractText();
	void setTime(int time)
	{
		_time = time;
	}
	void setWidth(int width)
	{
		_width = width;
	}
	void setHeight(int height)
	{
		_height = height;
	}
	void setUrl(QString url)
	{
		_url = url;
	}
	void setSize(int size)
	{
		_size = size;
	}
private:
	int			_width;
	int			_height;
	int			_time;
	QString		_url;
	int			_size;
};
#endif // TNMESSAGEBODY_H
