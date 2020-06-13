#include "tnnotifycenter.h"
#include <QDebug>
#include <QThread>

TNNotifyCenter* TNNotifyCenter::_instance = NULL;

TNNotifyCenter::TNNotifyCenter(QObject *parent) :
    QObject(parent)
{
}

TNNotifyCenter* TNNotifyCenter::instance()
{
	if (_instance == NULL)
	{
		_instance = new TNNotifyCenter();
		qRegisterMetaType<TNMsgData>("TNMsgData");
		qRegisterMetaType<TNNoticeInfo>("TNNoticeInfo&");
		qRegisterMetaType<QList<UINotifyData>>("QList<UINotifyData>");
	}
	return _instance;
}

void TNNotifyCenter::connectNotifyRefreshRevert(const QObject * receiver)
{
	QObject::connect(this, SIGNAL(notifyRefeshRevert(int, int,qint64, const QString &, const QString &, const QString &)), receiver, SLOT(revokeProcess(int, int, qint64,const QString &, const QString &, const QString &)));
}
void TNNotifyCenter::connectNotifyNetStatus(const QObject * receiver)
{
    QObject::connect(this, SIGNAL(notifyNetStatus(int)), receiver, SLOT(on_notifyNetStatus(int)));
}

void TNNotifyCenter::connectNotifySendHotKeyChanged(const QObject *receiver)
{
    QObject::connect(this, SIGNAL(notifySendHotKeyChanged(const QString &)), receiver, SLOT(on_notifySendHotKeyChanged(const QString &)));
}

void TNNotifyCenter::connectScreenShotByShortCut(const QObject *receiver)
{
    QObject::connect(this, SIGNAL(notifyFinishedScreenShotByShortCut()), receiver, SLOT(slotFinishedScreenShotByShortCut()));
}

void TNNotifyCenter::connectNotifyCheckVersionFinished(const QObject * receiver)
{
    QObject::connect(this, SIGNAL(notifyCheckVersionFinished(bool, bool, QString, int, QString)),
        receiver, SLOT(on_notifyCheckVersionFinished(bool, bool, QString, int, QString)));
}

void TNNotifyCenter::connectNotifyOffMsg(const QObject * receiver)
{
	QObject::connect(this, SIGNAL(notifyOffMsg(int)), receiver, SLOT(on_notifyOffMsg(int)));
}

void TNNotifyCenter::connectNotifyRefreshSession(const QObject * receiver)
{
	QObject::connect(this, SIGNAL(notifyRefresh(QStringList)), receiver, SLOT(on_notifyRefresh(QStringList)));
}

void TNNotifyCenter::connectNotifyRemoveSession(const QObject * receiver)
{
	QObject::connect(this, SIGNAL(notifyRemoveSession(QString)), receiver, SLOT(on_notifyRemoveSession(QString)), Qt::QueuedConnection);
}

void TNNotifyCenter::connectNotifyReadSession(const QObject * receiver)
{
	QObject::connect(this, SIGNAL(notifyReadSession(QString)), receiver, SLOT(on_notifyReadSession(QString)), Qt::QueuedConnection);
}

void TNNotifyCenter::connectNotifyRefresh(const QObject * receiver)
{
	QObject::connect(this, SIGNAL(notifyRefresh(QString, int, const QString, TNMsgData)), receiver, SLOT(on_notifyRefresh(QString, int, const QString, TNMsgData)));
	QObject::connect(this, SIGNAL(notifyRefresh(QString, TNNoticeInfo&)), receiver, SLOT(on_notifyRefresh(QString, TNNoticeInfo&)));
}

void TNNotifyCenter::connectNotifyRefreshAddressList(const QObject * receiver)
{
	QObject::connect(this, SIGNAL(notifyRefresh(int, QList<UINotifyData>)), receiver, SLOT(on_notifyRefresh(int, QList<UINotifyData>)));
}

void TNNotifyCenter::connectNotifyResource(const QObject * receiver)
{
    QObject::connect(this, SIGNAL(notifyResource(const QString,int, QVariantMap)), receiver, SLOT(on_NotifyResource(const QString,int, QVariantMap)));
}

void TNNotifyCenter::connectNotifySendForward(const QObject * receiver)
{
    QObject::connect(this, SIGNAL(notifySendForward(QList<TNMessageListAdapter>)), receiver, SLOT(on_NotifySendForward(QList<TNMessageListAdapter>)));
}

void TNNotifyCenter::postNotifyCheckVersionFinished(
    bool isNeedUpgrade,
    bool isForceUpgrade,
    QString downLoadURL,
    int nCheckType,
    QString versionDesc
    )
{
    emit notifyCheckVersionFinished(isNeedUpgrade, isForceUpgrade, downLoadURL, nCheckType, versionDesc);
}
void TNNotifyCenter::postNotifyNetStatus(int netStatus)
{
    emit notifyNetStatus(netStatus);
}

void TNNotifyCenter::postNotifyRefresh(QString type, int statCode, const QString statDesc, TNMsgData& msgData)
{
//    if (NOTIFY_SHOW_DIALOG_DETAIL == type)
//    {
//        qDebug()<<"NOTIFY_SHOW_DIALOG_DETAIL SEND:"<<statDesc;
//    }

	emit notifyRefresh(type, statCode, statDesc, msgData);
}

void TNNotifyCenter::postNotifyRefresh(QString type, TNNoticeInfo& noticeData)
{

	emit notifyRefresh(type, noticeData);
}

void TNNotifyCenter::postNotifyRefreshRevert(int resultType, int msgType, qint64 msgTime, const QString &sessionId, const QString &msg, const QString &content)
{
	emit notifyRefeshRevert(resultType, msgType, msgTime, sessionId, msg, content);
}


void TNNotifyCenter::postNotifyRefresh(QStringList sessionIds)
{
	emit notifyRefresh(sessionIds);
}

void TNNotifyCenter::postNotifyResource(const QString resID,int statCode,QVariantMap mapData /*= QVariantMap()*/)
{
    emit notifyResource(resID, statCode, mapData);
}

void TNNotifyCenter::postNotifyOffMsg(int count)
{
	emit notifyOffMsg(count);
}

void TNNotifyCenter::postNotifyRefresh(int refreshType, QList<UINotifyData>& dataList)
{
	emit notifyRefresh(refreshType, dataList);
}

void TNNotifyCenter::postNotifyOnlineMsg(QString msgId, int bSuc)
{
	emit notifyOnlineMsg(msgId, bSuc);
}

void TNNotifyCenter::postNotifyRemoveSession(QString sessionId)
{
	emit notifyRemoveSession(sessionId);
}

void TNNotifyCenter::postNotifyReadSession(QString sessionId)
{
	emit notifyReadSession(sessionId);
}

void TNNotifyCenter::connnectNotifyMessageback(const QObject * receiver)
{
	QObject::connect(this, SIGNAL(notifyOnlineMsg(QString, int)),
		receiver, SLOT(on_notifyRefreshAck(QString, int)));
}

void TNNotifyCenter::postNotifySendHotKeyChanged(const QString &key)
{
    emit notifySendHotKeyChanged(key);
}

void TNNotifyCenter::postNotifyFinishedScreenShotByShortCut()
{
    emit notifyFinishedScreenShotByShortCut();
}
void TNNotifyCenter::postNotifySendForward(QList<TNMessageListAdapter> listAdapter)
{
    emit notifySendForward(listAdapter);
}

void TNNotifyCenter::postNotifyCurrentFeedChanged(const QString &feedID)
{
    emit notifyCurrentFeedChanged(feedID);
}

void TNNotifyCenter::postNotifyCreateGroupChatFinished(TNMessageListAdapter session)
{
    emit createGroupChatFinished(session);
}

void TNNotifyCenter::postNotifyCreateToChat(const QJsonObject &json)
{
    emit notifyCreateToChat(json);
}
void TNNotifyCenter::postNotifyReMarkUpdate(const QString &from, const QString &to, const QString &reMark,int sources)
{
	emit notifyReMarkUpdate(from, to, reMark, sources);
}

void TNNotifyCenter::connnectNotifyCurrentFeedChanged(const QObject * receiver)
{
    QObject::connect(this, SIGNAL(notifyCurrentFeedChanged(const QString &)), receiver, SLOT(on_notifyCurrentFeedChanged(const QString &)));
}

void TNNotifyCenter::connnectNotifyCreateGroupChatFinished(const QObject *receiver)
{
    QObject::connect(this, SIGNAL(createGroupChatFinished(TNMessageListAdapter)), receiver, SLOT(slotCreateGroupChatFromMenuArea(TNMessageListAdapter)));
}

void TNNotifyCenter::connnectNotifyCreateToChat(const QObject *receiver)
{
    QObject::connect(this, SIGNAL(notifyCreateToChat(const QJsonObject &)), receiver, SLOT(slotToChat(const QJsonObject &)));
}
void TNNotifyCenter::connectNotifyReMarkUpdate(const QObject * receiver)
{
	QObject::connect(this, SIGNAL(notifyReMarkUpdate(const QString &, const QString &, const QString &,int)), receiver, SLOT(on_notifyReMarkUpdate(const QString &, const QString &, const QString &,int)));
}
void TNNotifyCenter::connectNotifyOrgCommunicationStatus(const QObject * receiver)
{
	QObject::connect(this, SIGNAL(notifyOrgCommunicationStatus(const QString &, const QString &)), receiver, SLOT(on_notifyOrgCommunicationStatus(const QString &, const QString &)));
}
void TNNotifyCenter::postNotifyOrgCommunicationStatus(const QString &feedId, const QString &status)
{
	emit notifyOrgCommunicationStatus(feedId,status);
}
void TNNotifyCenter::connectNotifyKeyEventDis(const QObject * receiver)
{
	QObject::connect(this, SIGNAL(notifyKeyEventDis(int)), receiver, SLOT(on_notifyKeyEventDis(int)));
}
void TNNotifyCenter::postNotifyKeyEventDis(int keyEvent)
{
	emit notifyKeyEventDis(keyEvent);
}