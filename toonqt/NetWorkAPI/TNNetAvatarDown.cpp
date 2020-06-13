#include "TNNetAvatarDown.h"
#include "TNPathUtil.h"
#include <QMutex>
#include <QFile>
#include "TNPathUtil.h"
#include "TNNameSpace.h"

TNNetAvatarDown::CGarbo TNNetAvatarDown::Garbo; //Never need to init
TNNetAvatarDown* TNNetAvatarDown::_instance = nullptr;
TNNetAvatarDown::TNNetAvatarDown():_downAvatarObject(nullptr)
{
	_downAvatarObject = new downAvatarClass();
	_downAvatarObject->moveToThread(&_threadDown);
	
	connect(this, SIGNAL(downAvatarSignals(QString, QString, bool, const QObject *, bool, QString)), _downAvatarObject, SLOT(downAvatarSlots(QString, QString, bool, const QObject *, bool, QString)),Qt::QueuedConnection);
	_threadDown.start();
}

TNNetAvatarDown::~TNNetAvatarDown()
{
	if (_downAvatarObject != nullptr)
	{
		delete _downAvatarObject;
		_downAvatarObject = nullptr;
	}
	_threadDown.quit();
    _threadDown.wait();
}
TNNetAvatarDown* TNNetAvatarDown::GetInstance()
{
	static QMutex s_mutex;
	if (_instance == nullptr)
	{
		QMutexLocker lock(&s_mutex);
		if (_instance == nullptr)
		{
			_instance = new TNNetAvatarDown();
		}
	}
	return _instance;
}
void TNNetAvatarDown::DownLoadFeedAvatar(QString feedId, QString url, bool tokenReady, const QObject * resultReceiver, bool isOriginal, QString appData)
{
	qInfo() << QThread::currentThreadId();
	if (_downAvatarObject == nullptr)
	{
		qInfo() << "[NetWorkAPI][TNNetAvatarDown]DownLoadFeedAvatar Down Avatar object invalid";
		return;
	}
	emit downAvatarSignals(feedId, url, tokenReady, resultReceiver, isOriginal, appData);
}

downAvatarClass::downAvatarClass()
{
	_ClousList.clear();
}
downAvatarClass::~downAvatarClass()
{
	foreach(TNHttpDownCloud* var,_ClousList){
		delete var;
	}
}
int downAvatarClass::getSpecialSubstringCount(const QString & feed, const QString &subString)
{
	int count = 0;
	QString tempFeed = feed;
	int pos = tempFeed.indexOf(subString);
	while (pos != -1)
	{
		count++;
		tempFeed = tempFeed.right(tempFeed.length() - pos-1);
		pos = tempFeed.indexOf(subString);
	}
	return count;
}
void downAvatarClass::releaseCouldRes(TNHttpDownCloud  *Cloud)
{
	for (QList<TNHttpDownCloud *>::iterator it = _ClousList.begin(); it != _ClousList.end(); it++)
	{
		if ((*it) == Cloud)
		{
			_ClousList.erase(it);
			Cloud->deleteLater();
			break;
		}
	}
}
void downAvatarClass::downAvatarSlots(QString avatarFeedId, QString url, bool tokenReady, const QObject * resultReceiver, bool isOriginal, QString appData)
{
	qInfo() << "[NetWorkAPI][TNNetAvatarDown]downAvatarSlots,thread:"<<QThread::currentThreadId();
	if (avatarFeedId == "" || url == "")
	{
		qInfo() << "[NetWorkAPI][TNNetAvatarDown]downAvatarSlots feed or url is invalid" << "feed:" << avatarFeedId << ",url:" << url;
		return;
	}
    /*
	if (getSpecialSubstringCount(feedId, "_") != 1)
	{
		qInfo() << "[NetWorkAPI][TNNetAvatarDown]downAvatarSlots feed is invalid" << "feed:" << feedId;
		return;
	}
    */
	if (_downList.contains(avatarFeedId))
	{
		qInfo() << "[NetWorkAPI][TNNetAvatarDown]downAvatarSlots the feed is downing" << "feed:" << avatarFeedId;
		return;
	}
	TNHttpDownCloud* cloudTemp = new TNHttpDownCloud();
	if (cloudTemp == nullptr)
	{
		qInfo() << "[NetWorkAPI][TNNetAvatarDown]downAvatarSlots New Cloud object failed";
		return;
	}
	_ClousList.append(cloudTemp);
	if (appData.isEmpty())
	{
		QObject::connect(cloudTemp, SIGNAL(downAvatarFinshed(bool, QString, QString)), resultReceiver, SLOT(onAvatarDownLoadFinish(bool, QString, QString)));
		QObject::connect(cloudTemp, SIGNAL(downAvatarFinshed(bool, QString, QString)), this, SLOT(downAvatarFinshedSlots(bool, QString, QString)));
	}
	else
	{
		QObject::connect(cloudTemp, SIGNAL(downAvatarFinshedEx(bool, QString, QString, QString)), resultReceiver, SLOT(onAvatarDownLoadFinishEx(bool, QString, QString, QString)));
		QObject::connect(cloudTemp, SIGNAL(downAvatarFinshedEx(bool, QString, QString, QString)), this, SLOT(downAvatarFinshedSlotsEx(bool, QString, QString, QString)));
	}

	QString newUrl, fileName;
	if (isOriginal)
	{
		fileName = TNPathUtil::getFeedAvatarPath(avatarFeedId) + "_org";
		newUrl = url;
	}
	else
	{
		fileName = TNPathUtil::getFeedAvatarPath(avatarFeedId);
		newUrl = TNHttpDownCloud::GetThumbUrl(TN::ThumbWidth, TN::ThumbHeight, url);
	}
	/*
	删除原始头像,下载原头像不删除旧图
	*/
	if (!isOriginal || avatarFeedId.startsWith("gc_"))
		TNPathUtil::removeAvatarFile(avatarFeedId);
	qInfo() << "[NetWorkAPI][TNNetAvatarDown]downAvatarSlots Down avatar :" << newUrl << " Feed:" << avatarFeedId << " AppData" << appData;
	QStringList appendData;
	appendData.append(avatarFeedId);
	if (!appData.isEmpty())
		appendData.append(appData);

	_downList.append(avatarFeedId);
	TNHttpCloudApi::GetInstance()->DownAvatorFromCloud([&](bool success,
		QString file, QStringList feedIdList, QString sessionId, TNHttpDownCloud* downThread){
		if (downThread){
			if (success){
				qInfo() << "[NetWorkAPI][TNNetAvatarDown]downAvatarSlots Success avatar :" << file << "Feed:" << feedIdList[0];
				if (feedIdList.size() > 1)
					downThread->setEmitAvatarFinishedSignalEx(success, file, feedIdList[0], feedIdList[1]);
				else
					downThread->setEmitAvatarFinishedSignal(success, file, feedIdList[0]);
			}
			else
				qInfo() << "[NetWorkAPI][TNNetAvatarDown]downAvatarSlots failed avatar :" << file << "Feed:" << feedIdList[0];
			this->releaseFeedList(feedIdList[0]);
			this->releaseCouldRes(downThread);
		}
	}, newUrl, appendData, fileName, cloudTemp, tokenReady);
}
void downAvatarClass::releaseFeedList(QString feedId)
{
	if (_downList.contains(feedId))
	{
		_downList.removeAll(feedId);
	}
}
