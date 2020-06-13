#include "TNMessageListAdapter.h"
#include <QDebug>

TNMessageListAdapter::TNMessageListAdapter()
    : _type(52/*MSG_BIZ_SINGLECHAT*/)
    , _time(0)
    , _unreadCount(0)
    , _topStatus(0)
    , _bNoAlarm(false)
    , _active(true)
	, _bAtMe(false)
    , _back_status(em_notice_list_normal)
{

}

TNMessageListAdapter::TNMessageListAdapter(const QString &sessionId, int type)
    : _type(type)
, _sessionId(sessionId)
, _time(0)
, _unreadCount(0)
, _topStatus(0)
, _bNoAlarm(false)
, _active(true)
, _bAtMe(false)
, _back_status(em_notice_list_normal)
{
}

TNMessageListAdapter::~TNMessageListAdapter()
{
}

void TNMessageListAdapter::setName(const QString &name)
{
	_name = name;
}

QString TNMessageListAdapter::getName() const
{
    return _name;
}

void TNMessageListAdapter::setLastMessage(const QString &lastMessage)
{
	_lastMessage = lastMessage;
}

QString TNMessageListAdapter::getLastMessage() const
{
    return _lastMessage;
}

QString TNMessageListAdapter::getPhotoResID() const
{
	return _photoResID;
}

void TNMessageListAdapter::setPhotoResID(const QString &resID)
{
	_photoResID = resID;
}
