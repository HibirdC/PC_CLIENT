#include "tnmessagebody.h"
#include <QLabel>
//摘要最大长度

const int TN_ABS_MAX_LEN = 20;

TNMessageBodyBase::TNMessageBodyBase()
{

}

TNMessageBodyBase::~TNMessageBodyBase()
{

}

TNMessageBodyBase* TNMessageBodyBase::instance(TNMessageContentType type)
{
	TNMessageBodyBase* bodyInstance = NULL;
	switch (type) {
	case TNChatTypeText:
		bodyInstance = new TNMessageBodyText();
		break;
	default:
		bodyInstance = new TNMessageBodyDefault();
		break;
	}

	return bodyInstance;
}

/**
TNMessageBodyDefault
*/

TNMessageBodyDefault::TNMessageBodyDefault()
{
	_text = QStringLiteral("暂不支持此类型，请在移动端查看");
}

TNMessageBodyDefault::~TNMessageBodyDefault()
{

}

QSize TNMessageBodyDefault::getViewSize()
{
	return QSize(130, 30);
}

QVariantMap TNMessageBodyDefault::pack()
{
	return QVariantMap();
}

void TNMessageBodyDefault::parse(QVariantMap &mapBody)
{
	Q_UNUSED(mapBody);
}


/**
TNMessageBodyText
*/

TNMessageBodyText::TNMessageBodyText()
{
}

TNMessageBodyText::~TNMessageBodyText()
{

}

void TNMessageBodyText::parse(QVariantMap &mapBody)
{
	_text = mapBody["text"].toString();
}

QVariantMap TNMessageBodyText::pack()
{
	QVariantMap mapBody;
	mapBody["text"] = _text;

	return mapBody;
}

QSize TNMessageBodyText::getViewSize()
{
	QSize size;
	/*QLabel lblMsg(_text);
	lblMsg.setTextFormat(Qt::RichText);

	QFont font;
	font.setPointSize(12);
	lblMsg.setFont(font);
	lblMsg.setWordWrap(true);
	int height = lblMsg.heightForWidth(380);

	size.setHeight(height);
	size.setWidth(lblMsg.width());*/

	return size;
}

QString TNMessageBodyText::getAbstractText()
{
	return _text;
}

bool TNMessageBodyText::isEmpty()
{
	if (_text.length() > 0){
		return false;
	}

	return true;
}

/**
TNMessageBodyNotification
*/

TNMessageBodyNotification::TNMessageBodyNotification()
{
}

TNMessageBodyNotification::~TNMessageBodyNotification()
{

}

void TNMessageBodyNotification::parse(QVariantMap &mapBody)
{
	_json = mapBody["text"].toString();
}

QVariantMap TNMessageBodyNotification::pack()
{
	QVariantMap mapBody;
	mapBody["text"] = _json;

	return mapBody;
}

QSize TNMessageBodyNotification::getViewSize()
{
	QSize size;
	QLabel lblMsg(_json);
	lblMsg.setTextFormat(Qt::RichText);

	QFont font;
	font.setPointSize(12);
	lblMsg.setFont(font);
	lblMsg.setWordWrap(true);
	int height = lblMsg.heightForWidth(380);

	size.setHeight(height);
	size.setWidth(lblMsg.width());

	return size;
}

QString TNMessageBodyNotification::getAbstractText()
{
	if (_json.length() > TN_ABS_MAX_LEN){
		return _json.left(TN_ABS_MAX_LEN);
	}

	return "";
}

bool TNMessageBodyNotification::isEmpty()
{
	if (_json.length() > 0){
		return false;
	}

	return true;
}

/**
TNMessageBodySystemText
*/

TNMessageBodySystemText::TNMessageBodySystemText()
{
}

TNMessageBodySystemText::~TNMessageBodySystemText()
{

}

void TNMessageBodySystemText::parse(QVariantMap &mapBody)
{
	_text = mapBody["text"].toString();
	_attributedText = mapBody["attribute"].toString();
}

QVariantMap TNMessageBodySystemText::pack()
{
	QVariantMap mapBody;
	mapBody["text"] = _text;
	mapBody["attribute"] = _attributedText;
	return mapBody;
}

QSize TNMessageBodySystemText::getViewSize()
{
	QSize size;
	QLabel lblMsg(_text);
	lblMsg.setTextFormat(Qt::RichText);

	QFont font;
	font.setPointSize(12);
	lblMsg.setFont(font);
	lblMsg.setWordWrap(true);
	int height = lblMsg.heightForWidth(380);

	size.setHeight(height);
	size.setWidth(lblMsg.width());

	return size;
}

QString TNMessageBodySystemText::getAbstractText()
{
	if (_text.length() > TN_ABS_MAX_LEN){
		return _text.left(TN_ABS_MAX_LEN);
	}

	return "";
}

bool TNMessageBodySystemText::isEmpty()
{
	if (_text.length() > 0){
		return false;
	}
	return true;
}

/**
TNMessageBodyFileBase
*/

TNMessageBodyFileBase::TNMessageBodyFileBase(): _size(0)
{
}

TNMessageBodyFileBase::~TNMessageBodyFileBase()
{

}

void TNMessageBodyFileBase::parse(QVariantMap &mapBody)
{
	_url = mapBody["url"].toString();
	_suffix = mapBody["suffix"].toString();
	_size = mapBody["size"].toInt();
}

QVariantMap TNMessageBodyFileBase::pack()
{
	QVariantMap mapBody;
	mapBody["url"] = _url;
	mapBody["suffix"] = _suffix;
	mapBody["size"] = _size;
	return mapBody;
}

QSize TNMessageBodyFileBase::getViewSize()
{
	QSize size;
	return size;
}

QString TNMessageBodyFileBase::getAbstractText()
{
	return QStringLiteral("[附件]");
}

bool TNMessageBodyFileBase::isEmpty()
{
	if (_url.length() > 0){
		return false;
	}
	return true;
}

/**
TNMessageBodyImage
*/

TNMessageBodyImage::TNMessageBodyImage() :_width(0), _height(0)
{
}

TNMessageBodyImage::~TNMessageBodyImage()
{

}

void TNMessageBodyImage::parse(QVariantMap &mapBody)
{
	TNMessageBodyFileBase::parse(mapBody);
	_width = mapBody["w"].toInt();
	_height = mapBody["h"].toInt();
}

QVariantMap TNMessageBodyImage::pack()
{
	QVariantMap mapBody = TNMessageBodyFileBase::pack();
	mapBody["w"] = _width;
	mapBody["h"] = _height;
	return mapBody;
}

QSize TNMessageBodyImage::getViewSize()
{
	QSize size(_width, _height);
	return size;
}

QString TNMessageBodyImage::getAbstractText()
{
	return QStringLiteral("[图片]");
}

/**
TNMessageBodyVoice
*/

TNMessageBodyVoice::TNMessageBodyVoice() :_time(0), _readed(false)
{
}

TNMessageBodyVoice::~TNMessageBodyVoice()
{

}

void TNMessageBodyVoice::parse(QVariantMap &mapBody)
{
	TNMessageBodyFileBase::parse(mapBody);
	_time = mapBody["time"].toInt();
	_readed = mapBody["readed"].toInt();
}

QVariantMap TNMessageBodyVoice::pack()
{
	QVariantMap mapBody = TNMessageBodyFileBase::pack();
	mapBody["time"] = _time;
	mapBody["readed"] = _readed;
	return mapBody;
}


QString TNMessageBodyVoice::getAbstractText()
{
	return QStringLiteral("[语音]");
}

/**
TNMessageBodyVideo
*/

TNMessageBodyVideo::TNMessageBodyVideo() :_width(0), _height(0), _time(0), _size(0)
{
}

TNMessageBodyVideo::~TNMessageBodyVideo()
{

}

void TNMessageBodyVideo::parse(QVariantMap &mapBody)
{
	_url = mapBody["url"].toString();
	_size = mapBody["size"].toInt();
	_time = mapBody["time"].toInt();
	_width = mapBody["w"].toInt();
	_height = mapBody["h"].toInt();
}

QVariantMap TNMessageBodyVideo::pack()
{
	QVariantMap mapBody;
	mapBody["time"] = _time;
	mapBody["size"] = _size;
	mapBody["w"] = _width;
	mapBody["h"] = _height;
	mapBody["url"] = _url;
	return mapBody;
}


QString TNMessageBodyVideo::getAbstractText()
{
	return QStringLiteral("[视频]");
}

/**
TNMessageBodyAttachment
*/

TNMessageBodyAttachment::TNMessageBodyAttachment()
{
}

TNMessageBodyAttachment::~TNMessageBodyAttachment()
{

}

void TNMessageBodyAttachment::parse(QVariantMap &mapBody)
{
	TNMessageBodyFileBase::parse(mapBody);
	_desc = mapBody["desc"].toInt();
	_format = mapBody["format"].toInt();
}

QVariantMap TNMessageBodyAttachment::pack()
{
	QVariantMap mapBody = TNMessageBodyFileBase::pack();
	mapBody["desc"] = _desc;
	mapBody["format"] = _format;
	return mapBody;
}


QString TNMessageBodyAttachment::getAbstractText()
{
	return QStringLiteral("[附件]");
}
