#ifndef TNNETAVATARDOWN_H
#define TNNETAVATARDOWN_H

#include <QObject>
#include <QThread>

#include "NetWorkAPI_global.h"
#include "TNHttpCloudApi.h"

class downAvatarClass;
class NETWORKAPI_EXPORT TNNetAvatarDown : public QObject
{
	Q_OBJECT

public:
	TNNetAvatarDown();
	~TNNetAvatarDown();
	static TNNetAvatarDown* GetInstance();
	void DownLoadFeedAvatar(QString feedId, QString url, bool tokenReady, const QObject * resultReceiver, bool isOriginal = false, QString appData = QString(""));
private:
	static TNNetAvatarDown * _instance;
	downAvatarClass        * _downAvatarObject;
	QThread				     _threadDown;

	class CGarbo // Explicit call ~TNNetAvatarDown()
	{
	public:
		~CGarbo()
		{
			if (TNNetAvatarDown::_instance)
				delete TNNetAvatarDown::_instance;
		}
	};
	static CGarbo Garbo;

Q_SIGNALS:
	void downAvatarSignals(QString, QString, bool, const QObject *, bool, QString);
};

class downAvatarClass : public QObject
{
	Q_OBJECT

public:
	downAvatarClass();
	~downAvatarClass();
private:
	QList<TNHttpDownCloud *> _ClousList;
	QList<QString>           _downList;
	void releaseCouldRes(TNHttpDownCloud *list);
	void releaseFeedList(QString feedId);
	int getSpecialSubstringCount(const QString & feed,const QString &subString);

public slots :
	void downAvatarSlots(QString,QString,bool,const QObject *,bool,QString);
};
#endif // TNNETAVATARDOWN_H
