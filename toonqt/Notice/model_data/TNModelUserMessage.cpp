#include "TNModelUserMessage.h"

TNModelUserMessage::TNModelUserMessage() : _time(QDateTime::currentDateTime())
, _fileSize(-1)
, _picSize(100,100)
, _audioTime(0)
, _atType(0)
, _status(MSG_STATUS_UNSEND)
, _fileStatus(MSG_STATUS_FILE_UPLOADING)
{
	
}

TNModelUserMessage::~TNModelUserMessage()
{
}

void TNModelUserMessage::SetMessageType(MESSAGE_TYPE type)
{
	_messageType = type;
}

MESSAGE_TYPE TNModelUserMessage::GetMessageType()
{
	return _messageType;
}

void TNModelUserMessage::SetMsgID(const QString& msgID)
{
	_msgID = msgID;
}

QString TNModelUserMessage::GetMsgID()
{
	return _msgID;
}

void TNModelUserMessage::SetUserMessage(const QString & message)
{
	_strMessage = message;
}

QString TNModelUserMessage::GetUserMessage()
{
	return _strMessage;
}

QString TNModelUserMessage::GetPhotoIcon()
{
	return _photoIcon;
}

void TNModelUserMessage::SetPhotoIcon(const QString& photoIcon)
{
	_photoIcon = photoIcon;
}

void TNModelUserMessage::setMessageSendFrom(messageSendFrom from)
{
	_msgSendFrom = from;
}

messageSendFrom TNModelUserMessage::getMessageSendFrom()
{
	return _msgSendFrom;
}

void TNModelUserMessage::setTime(QDateTime time/* =QDateTime::currentDateTime() */)
{
	_time = time;
}

QDateTime TNModelUserMessage::getTime()
{
	return _time;
}

QSize TNModelUserMessage::getPicSize()
{
	return _picSize;
}

void TNModelUserMessage::setPicSize(const QSize& picSize)
{
	_picSize = picSize;
}

qint64 TNModelUserMessage::getFileSize()
{
	return _fileSize;
}

void TNModelUserMessage::setFileSize(qint64 size)
{
	_fileSize = size;
}

QString TNModelUserMessage::getFileName()
{
	return _fileName;
}

void TNModelUserMessage::setFileName(const QString& fileName)
{
	_fileName = fileName;
}

void TNModelUserMessage::setFileSuffix(const QString& suffix)
{
	_fileSuffix = suffix;
}

QString TNModelUserMessage::getFileSuffix()
{
	return _fileSuffix;
}
