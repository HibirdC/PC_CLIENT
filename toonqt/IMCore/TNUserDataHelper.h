#ifndef TNUSERDATAHELPER_H
#define TNUSERDATAHELPER_H
#include <qstring.h>
#include <qstringlist.h>
#include <QMutex>
#include "imcore_global.h"
#include "TNHttpObtainFeedList.h"
#include "TNHttpGetMessageAppInfo.h"
#include "LocalStorageCommon.h"
#include "TNHttpApi.h"
#include "TNHttpGetOrgCommunicationStatus.h"

class IMCORE_EXPORT TNUserDataHelper : public QObject
{
	Q_OBJECT

public:
	TNUserDataHelper();
	~TNUserDataHelper();
	static TNUserDataHelper* GetInstance();
    void GetFeedInfo(const QString& feedId, st_FeedPtr& feedInfo);
	void GetGroupInfo(QString& groupId, st_GroupInfo& groupInfo);
    void GetAppInfo(const QString& appId, st_MessageAppInfoPtr& appInfo);
	void Init(TNPluginParamPtr paramPlugin);
    TNHttpBaseApi * LoadFeeds(const QStringList& strFeedIDs, QList<UINotifyData> ext, int iType = -1, bool loadNow = true);
	void LoadFeedsSync(const QStringList& strFeedIDs);
	void ProcessDeleteStaff(const QStringList & strFeedIDs);
	bool IsEmptyUpdateList(){ return _feedUpdateList.isEmpty(); }

	int  GetCardStatus(const QString &feedId, const QString &belongId,bool &feedStaus,bool & belongFeedStatus);
	bool GetSingleCardStatus(const QString &feedId);
	bool GetOrgCommStatus(const QString &feedId);
	bool GetNativeCardStatus(const QString &feed);
	void updateCardStatus(const QString &feedId, const QString &belongId);
	void updateOrgCommStatus(const QString &feedId);
	void clearNativeCardStatus();
signals:
	void GetFeedFinishedOne();
	void GetFeedFinished(int type, QList<UINotifyData> notifyData);
	void GetAppFinished();
    void addNewFeedGetApi(TNHttpObtainFeedList *);
	
public:
	TNPluginParamPtr			_pluginParam;
private:
	void DeleteUnuseHttpFeed();
	void DestroyFeedThread(TNHttpObtainFeedList* feedThread);
private:
	QList<TNHttpObtainFeedList*>				_httpFeedList;
	QList<TNHttpObtainFeedList*>				_httpDeleteFeedList;
	QSet<QString>								_feedUpdateList;
	QMutex										_feedMutex;
	QMap<QString, bool>                         _feedStatusMap;
	TNHttpObtainFeedListPtr                     _httpObtainFeedList;
	TNHttpGetOrgCommunicationStatusPtr          _httpGetOrgCommunication;
};
#endif
