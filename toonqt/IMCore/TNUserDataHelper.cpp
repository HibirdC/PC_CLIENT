#include "TNUserDataHelper.h"
#include "qjsonobject.h"
#include "qjsondocument.h"
#include "TNDataControlServer.h"
#include "qjsonarray.h"
#include "qeventloop.h"
#include "TNHttpObtainGroupChatInfoByGroupChatIdSyn.h"
#include "tnnotifycenter.h"
#include "TNPathUtil.h"

#include <QTimer>
#include <QFile>
#include <QMutexLocker>
#define TIME_OUT  1000*5
TNUserDataHelper::TNUserDataHelper()
{
	_httpObtainFeedList = nullptr;
	_httpGetOrgCommunication = nullptr;
}

TNUserDataHelper* TNUserDataHelper::GetInstance()
{
	static TNUserDataHelper* userHelper;
	static QMutex s_mutex;
	if (userHelper == NULL)
	{
		QMutexLocker locker(&s_mutex);
		if (userHelper == NULL)
			userHelper = new TNUserDataHelper;
	}
	return userHelper;
}

TNUserDataHelper::~TNUserDataHelper()
{
	for (int index = 0; index < _httpFeedList.size(); index++)
	{
		TNHttpObtainFeedList* httpFeed = _httpDeleteFeedList[index];
		if (httpFeed)
			delete httpFeed;
	}
	_httpDeleteFeedList.clear();
}

void TNUserDataHelper::GetFeedInfo(const QString &feedId, st_FeedPtr& feedInfo)
{
	
	if (feedId.isEmpty())
		return;
	//优先查库
	bool isRead = false;
	TableBaseVec tableFeed;
	TNDataControlServer::GetInstance()->Query(tableFeed, "Feed", "feedId", feedId, DBTYPE_USER);
	if (tableFeed.size() > 0)
    {
        //从数据库去取
        qInfo() << "[IMCore][TNUserDataHelper]:GetFeedInfo from database";
		feedInfo = std::dynamic_pointer_cast<st_Feed>(tableFeed[0]);
		if (!feedInfo->GetTitle().isEmpty())
		{
			isRead = true;
		}
        qInfo() << "[IMCore][TNUserDataHelper]:GetFeedInfo from database end";
    }
	if (!isRead)
	{
		//从服务器去取
		qInfo() << "[IMCore][TNUserDataHelper]:GetFeedInfo from server";
		QStringList feedlist;
		feedlist.append(feedId);
		QList<UINotifyData> extData;
		TNHttpBaseApi *pApi = LoadFeeds(feedlist, extData);
        if (nullptr == pApi)
        {
            return;
        }
		QEventLoop eventLoop;
		connect(pApi, SIGNAL(SuccessfulReturn(TNHttpBaseApi *)), &eventLoop, SLOT(quit()));
		QTimer::singleShot(TIME_OUT, &eventLoop, SLOT(quit()));
		eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
		TableBaseVec tableFeed;
		TNDataControlServer::GetInstance()->Query(tableFeed, "Feed", "feedId", feedId, DBTYPE_USER);
		if (tableFeed.size() > 0)
			feedInfo = std::dynamic_pointer_cast<st_Feed>(tableFeed[0]);
        else
            qInfo() << "[IMCore][TNUserDataHelper]:GetFeedInfo return feedInfo is null.";
		qInfo() << "[IMCore][TNUserDataHelper]:GetFeedInfo from server end";
	}
}

void TNUserDataHelper::GetAppInfo(const QString& appId, st_MessageAppInfoPtr& appInfo)
{
	if (appId.isEmpty())
		return;
	TableBaseVec tableFeed;
	TNDataControlServer::GetInstance()->Query(tableFeed, "MessageAppInfo", "appId", appId,DBTYPE_MSG);
	if (tableFeed.size() > 0)
		appInfo = std::dynamic_pointer_cast<st_MessageAppInfo>(tableFeed[0]);
	else
	{
		TNHttpGetMessageAppInfoPtr httpGetAppInfo = std::make_shared<TNHttpGetMessageAppInfo>();
		httpGetAppInfo->GetAppNoticeById([&](bool success, QJsonObject jsonObject)
		{
			if (success)
			{
				st_MessageAppInfoPtr stAppinfo = std::make_shared<st_MessageAppInfo>();
				stAppinfo->SetAppId(jsonObject.value("data").toObject().value("appId").toString());
				if (stAppinfo->GetAppId().isEmpty())
				{
					int appId = jsonObject.value("data").toObject().value("appId").toInt();
					QString strAppId = QString::number(appId);
					stAppinfo->SetAppId(strAppId);
				}
				stAppinfo->SetAppTitle(jsonObject.value("data").toObject().value("appTitle").toString());
				stAppinfo->SetAppLittleIcon(jsonObject.value("data").toObject().value("appLittleIcon").toString()); 
				stAppinfo->SetIsDelete(jsonObject.value("data").toObject().value("isDelete").toInt());
				stAppinfo->SetAppCode(jsonObject.value("data").toObject().value("appCode").toString());
				stAppinfo->SetChatFlag(jsonObject.value("data").toObject().value("chatFlag").toInt());
				stAppinfo->SetBtnNumber(jsonObject.value("data").toObject().value("btnNumber").toInt());
				TNDataControlServer::GetInstance()->InsertDatas(std::dynamic_pointer_cast<TableBase>(stAppinfo), DBTYPE_MSG);
			}
			emit GetAppFinished();
			
		}, _pluginParam, appId);
		QEventLoop eventLoop;
		QObject::connect(httpGetAppInfo.get(), SIGNAL(SuccessfulReturn(TNHttpBaseApi *)), &eventLoop, SLOT(quit()));
		QTimer::singleShot(TIME_OUT, &eventLoop, SLOT(quit()));
		eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
		TableBaseVec tableFeed;
		TNDataControlServer::GetInstance()->Query(tableFeed, "MessageAppInfo", "appId", appId,DBTYPE_MSG);
		if (tableFeed.size() > 0)
			appInfo = std::dynamic_pointer_cast<st_MessageAppInfo>(tableFeed[0]);
 	}

}

TNHttpBaseApi * TNUserDataHelper::LoadFeeds(const QStringList &strFeedIDs, QList<UINotifyData> ext, int iType, bool loadNow)
{
	qInfo() << "[IMCore][TNUserDataHelper]LoadFeeds start";
	DeleteUnuseHttpFeed();
	if (_feedUpdateList.size() == 0 && strFeedIDs.size() == 0)
		return nullptr;
	_feedUpdateList += strFeedIDs.toSet();
	if (!loadNow)
		return nullptr;
	if (_feedUpdateList.size() != 0)
	{
		TNHttpObtainFeedList* httpGetFeed = new TNHttpObtainFeedList;
        emit addNewFeedGetApi(httpGetFeed);
		_httpFeedList.append(httpGetFeed);

		std::vector<QVariant> extern_params;
		extern_params.push_back(iType);
		httpGetFeed->GetJson([&](bool success, QJsonObject jsonObject, QList<UINotifyData> extData, TNHttpObtainFeedList* httpFeed,std::vector<QVariant> params)
		{
			if (success)
			{
				QList<TableBasePtr> stFeedList;
				QJsonArray feeds = jsonObject.value("data").toArray();
				//qDebug() << "httpGetFeed: " << QString(QJsonDocument(jsonObject).toJson());
				for (int m = 0; m < feeds.size(); m++)
				{
					st_FeedPtr stFeed = std::make_shared<st_Feed>();
					stFeed->SetBirthday(feeds.at(m).toObject().value("birthday").toString());
					stFeed->SetComID(feeds.at(m).toObject().value("comId").toString());
					stFeed->SetConsumeLevel(feeds.at(m).toObject().value("consumeLevel").toString());
					stFeed->SetKeyWord(feeds.at(m).toObject().value("keyword").toString());
					stFeed->SetFeedID(feeds.at(m).toObject().value("feedId").toString());
					stFeed->SetServiceLevel(feeds.at(m).toObject().value("serviceLevel").toString());
					stFeed->SetSex(feeds.at(m).toObject().value("sex").toString());
					stFeed->SetSocialLevel(feeds.at(m).toObject().value("socialLevel").toString());
					stFeed->SetTitle(feeds.at(m).toObject().value("title").toString());
					stFeed->SetSubTile(feeds.at(m).toObject().value("subtitle").toString());
					stFeed->SetTitlePinYin(feeds.at(m).toObject().value("titlePinYin").toString());
					stFeed->SetUserID(feeds.at(m).toObject().value("userId").toString());
					stFeed->SetVersion(feeds.at(m).toObject().value("version").toString());
					stFeed->SetTag(feeds.at(m).toObject().value("tag").toString());
					stFeed->SetAvatarID(feeds.at(m).toObject().value("avatarId").toString());
					stFeedList.append(std::dynamic_pointer_cast<TableBase>(stFeed));
					qInfo() << "[IMCore][TNUserDataHelper]httpGetFeed Insert feed name : " << stFeed->GetTitle() << "Insert feed ID : " << stFeed->GetFeedID();
				}
				if (stFeedList.size() > 0)
				{
					qInfo() << "[IMCore][TNUserDataHelper]httpGetFeed: " << "Insert feed list: " << stFeedList.size();
					TNDataControlServer::GetInstance()->InsertDatas(stFeedList, INSERT_FEED, DBTYPE_USER);
				}

				if (params[0].toInt() != -1)
				{
					qInfo() << "[IMCore][TNUserDataHelper]httpGetFeed GetFeedFinished";
					emit GetFeedFinished(params[0].toInt(), extData);
				}
				else
				{
					qInfo() << "[IMCore][TNUserDataHelper]httpGetFeed GetFeedFinishedOne";
					emit GetFeedFinishedOne();
				}
				qInfo() << "[IMCore][TNUserDataHelper]httpGetFeed LoadFeeds end";
				DestroyFeedThread(httpFeed);
				return;
			}
			if (params[0].toInt() == -1)
			{
				emit GetFeedFinishedOne();
			}
			DestroyFeedThread(httpFeed);
		}, _pluginParam, _feedUpdateList.toList(), ext, extern_params);
		_feedUpdateList.clear();
        return httpGetFeed;
	}
	qInfo() << "[IMCore][TNUserDataHelper]httpGetFeed LoadFeeds end(failed)";
	return nullptr;
}

void TNUserDataHelper::LoadFeedsSync(const QStringList& strFeedIDs)
{
	QList<UINotifyData> notifyData;
	LoadFeeds(strFeedIDs, notifyData);
	QEventLoop eventLoop;
	connect(this, &TNUserDataHelper::GetFeedFinishedOne, &eventLoop, &QEventLoop::quit);
	eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
}


void TNUserDataHelper::Init(TNPluginParamPtr paramPlugin)
{
	this->_pluginParam = paramPlugin;
}

void TNUserDataHelper::DeleteUnuseHttpFeed()
{
	QMutexLocker locker(&_feedMutex);
	for (int index = 0; index < _httpDeleteFeedList.size(); index++)
	{
		TNHttpObtainFeedList* httpFeed = _httpDeleteFeedList[index];
		if (httpFeed)
			httpFeed->deleteLater();
	}
	_httpDeleteFeedList.clear();

}

void TNUserDataHelper::DestroyFeedThread(TNHttpObtainFeedList* feedThread)
{
	QMutexLocker locker(&_feedMutex);
	if (_httpFeedList.size() > 0)
	{
		_httpFeedList.removeOne(feedThread);
	}
	_httpDeleteFeedList.append(feedThread);

}

void TNUserDataHelper::GetGroupInfo(QString& groupId, st_GroupInfo& groupInfo)
{
	TableBaseVec groupTableBaseVec;
	TNDataControlServer::GetInstance()->Query(groupTableBaseVec, "GroupInfo", "groupId", groupId, DBTYPE_USER);
	if (groupTableBaseVec.size() > 0)
		groupInfo = *std::dynamic_pointer_cast<st_GroupInfo>(*groupTableBaseVec.begin()).get();
	else
	{
		TNHttpObtainGroupChatInfoByGroupChatIdSyn obtainGroupChatInfoByGroupChatIdSyn;
		if (obtainGroupChatInfoByGroupChatIdSyn.obtainGroupChatInfo(_pluginParam, groupId.mid(3)))
		{
			QString groupChatName = obtainGroupChatInfoByGroupChatIdSyn.getGroupChatName();
			QString myFeedId = obtainGroupChatInfoByGroupChatIdSyn.getMyFeedId();
			QString groupChatHeadImage = obtainGroupChatInfoByGroupChatIdSyn.getGroupChatHeadImage();
            int currNum = obtainGroupChatInfoByGroupChatIdSyn.getCurrNum();
            groupInfo.SetGroupId(groupId);
			groupInfo.SetMyFeedId(myFeedId);
			groupInfo.SetName(groupChatName);
			groupInfo.SetHeaderImage(groupChatHeadImage);
            groupInfo.SetCurrNum(currNum);
		}
	}

}
void TNUserDataHelper::ProcessDeleteStaff(const QStringList & strFeedIDs)
{
	int ret = false;
	QList<UINotifyData> notifyData;
	qInfo() << "[IMCORE][TNUserDataHelper] ProcessDeleteStaff start : " << strFeedIDs.size();
	for (QString staffId : strFeedIDs)
	{
		QString comId;
		TableBaseVec tableMyStuff;
		TNDataControlServer::GetInstance()->Query(tableMyStuff, "MyStuff", "feedId", staffId, DBTYPE_USER);
		if (tableMyStuff.size() == 0)
		{
			qInfo() << "[IMCORE][TNUserDataHelper] ProcessDeleteStaff failed, beacuse the feed is not in MyStuff: " << staffId;
			continue;
		}
		st_MyStuffPtr myStuff = std::dynamic_pointer_cast<st_MyStuff>(tableMyStuff[0]);
		if (myStuff == nullptr)
		{
			qInfo() << "[IMCORE][TNUserDataHelper] ProcessDeleteStaff failed, beacuse the feed is not in MyStuff: " << staffId;
			continue;
		}
		comId = myStuff->GetExt();
		ret = TNDataControlServer::GetInstance()->DeleteFromTableNameByField("ColleagueRelation", "comId", comId, DBTYPE_USER);
		if (!ret)
			qInfo() << "[IMCORE][TNUserDataHelper] ProcessDeleteStaff failed, beacuse the ColleagueRelation can't delete";
		ret = TNDataControlServer::GetInstance()->DeleteFromTableNameByField("ColleagueGroup", "comId", comId, DBTYPE_USER);
		if (!ret)
			qInfo() << "[IMCORE][TNUserDataHelper] ProcessDeleteStaff failed, beacuse the ColleagueGroup can't delete";
		/*
		获取当前名片所有的好友： 
		*/
		TableBaseVec tableFriendList;
		TNDataControlServer::GetInstance()->MultiQuery(tableFriendList, "JoinStuff", "feedType", "belongTo", FeedTypeContact, staffId, DBTYPE_USER);
		for (TableBaseVec::iterator iter = tableFriendList.begin(); iter != tableFriendList.end(); iter++)
		{
			UINotifyData data;
			st_JoinStuffPtr joinStuff = std::dynamic_pointer_cast<st_JoinStuff>(*iter);
			data.feedId = joinStuff->GetFeedBelong();
			data.operateType = UI_OPERATE_DEL;
			notifyData.append(data);
		}
		if (tableFriendList.size() > 0)
		{
			ret = TNDataControlServer::GetInstance()->DeleteFromTableNameByField("JoinStuff", "belongTo", staffId, DBTYPE_USER);
			if (!ret)
				qInfo() << "[IMCORE][TNUserDataHelper] ProcessDeleteStaff failed, beacuse the friend can't delete";
		}
		/*
		删除头像
		*/
		TNPathUtil::removeAvatarFile(staffId);
	}
	if (notifyData.size() > 0)
	{
		//更新UI
		TNNotifyCenter::instance()->postNotifyRefresh(RefreshTypeUI_Myfriend, notifyData);
	}
	ret = TNDataControlServer::GetInstance()->DeleteFromTableNameByField("MyStuff", "feedId", strFeedIDs, DBTYPE_USER);
	if (!ret)
	{
		qInfo() << "[IMCORE][TNUserDataHelper] ProcessDeleteStaff failed, beacuse the MyStuff can't delete ";
	}
	qInfo() << "[IMCORE][TNUserDataHelper] ProcessDeleteStaff end ";
}
int TNUserDataHelper::GetCardStatus(const QString &feedId, const QString &belongId, bool &feedStaus, bool & belongStatus)
{
	QStringList list;
	list.append(belongId);
	list.append(feedId);

	feedStaus  = false;
	belongStatus = false;

	TNHttpApi _httpApi;
	QJsonObject cardJson;
	int nRet = _httpApi.GetFeedList(_pluginParam, list, cardJson);
	if (nRet == 0)
	{
		QString debugText = QString(QJsonDocument(cardJson).toJson());
		qInfo() << "[IMCORE][TNUserDataHelper]GetCardStatus=" << debugText;
		QJsonArray feedArray = cardJson.value("data").toArray();
        for (int i = 0; i < feedArray.size(); i++)
		{
			QString feed = cardJson.value("data").toArray().at(i).toObject().value("feedId").toString();
			QString userId = cardJson.value("data").toArray().at(i).toObject().value("userId").toString();
            if ((feed == feedId) && (userId != QString("0")))
			{
				feedStaus = true;
			}
            else if ((feed == belongId) && (userId != QString("0")))
			{
				belongStatus = true;
			}
		}
	}
	return nRet;
}
bool TNUserDataHelper::GetSingleCardStatus(const QString &feedId)
{
	QStringList list;
	list.append(feedId);

	bool result = false;
	TNHttpApi _httpApi;
	QJsonObject cardJson;
	int nRet = _httpApi.GetFeedList(_pluginParam, list, cardJson);
	if (nRet == 0)
	{
		QString debugText = QString(QJsonDocument(cardJson).toJson());
		qInfo() << "[IMCORE][TNUserDataHelper]GetSingleCardStatus=" << debugText;
		QJsonArray feedArray = cardJson.value("data").toArray();
		for (int i = 0; i < feedArray.size(); i++)
		{
			QString feed = cardJson.value("data").toArray().at(i).toObject().value("feedId").toString();
			QString userId = cardJson.value("data").toArray().at(i).toObject().value("userId").toString();
			if ((feed == feedId) && (userId != QString("0")))
			{
				result = true;
			}
		}
	}
	else
		result = true;
	return result;
}
bool TNUserDataHelper::GetOrgCommStatus(const QString &feedId)
{
	Q_ASSERT(!feedId.isEmpty()
		&& feedId.startsWith("o_"));

	bool result = false;
	TNHttpApi _httpApi;
	QJsonObject objectJson;
	int nRet = _httpApi.GetOCSStatus(_pluginParam, feedId, objectJson);
	if (nRet == 0)
	{
		QString debugText = QString(QJsonDocument(objectJson).toJson());
		qInfo() << "[IMCORE][TNUserDataHelper]GetOrgCommStatus=" << debugText;
		QJsonArray myListOrgArray = objectJson.value("data").toArray();
		for (int p = 0; p < myListOrgArray.size(); p++)
		{
			QMap<QString, QString> statusMap;
			QString oFeed = objectJson.value("data").toArray().at(p).toObject().value("feedId").toString();
			QString status = objectJson.value("data").toArray().at(p).toObject().value("communicateStatus").toString();
			if (oFeed == feedId)
			{
				result = status == "1" ? true : false;
				break;
			}
		}
	}
	return result;
}
void TNUserDataHelper::updateCardStatus(const QString &feedId, const QString &belongId)
{
	Q_ASSERT(!feedId.isEmpty());
	qInfo() << "[IMCORE][TNUserDataHelper]updateCardStatus feedId:" << feedId << " belong:" << belongId;
	if (_httpObtainFeedList.get() == nullptr)
	{
		_httpObtainFeedList = std::make_shared<TNHttpObtainFeedList>();
	}

	std::vector<QVariant> extern_params;
	extern_params.push_back(feedId);

	QSet<QString> feedList;
	feedList.insert(feedId);
	if (!belongId.isEmpty() && !belongId.startsWith("gc_")){
		extern_params.push_back(belongId);
		feedList.insert(belongId);
	}

	QList<UINotifyData> extData;
	_httpObtainFeedList->GetJson([&](bool success, QJsonObject jsonObject, QList<UINotifyData> extData, TNHttpObtainFeedList* httpFeed,
		std::vector<QVariant> params)
	{
		if (success)
		{
			QList<QString> srcFeed;
			for (int i = 0; i < params.size(); i++)
			{
				srcFeed.append(params[i].toString());
			}
			QList<TableBasePtr> stFeedList;
			QJsonArray feeds = jsonObject.value("data").toArray();
			for (int m = 0; m < feeds.size(); m++)
			{
				QString tempFeedId = feeds.at(m).toObject().value("feedId").toString();
				QString tempUserId = feeds.at(m).toObject().value("userId").toString();
				if (!tempFeedId.isEmpty())
				{
					if (_feedStatusMap.contains(tempFeedId))
					{
						_feedStatusMap.remove(tempFeedId);
					}
					srcFeed.removeOne(tempFeedId);
					_feedStatusMap.insert(tempFeedId, tempUserId != QString("0"));
					qInfo() << "[IMCORE][TNUserDataHelper]updateCardStatus return,feedId :" << tempFeedId << " userId:" << tempUserId;
				}
			}
			//个人名片被删除后，不会返回状态
			for (int i = 0; i < srcFeed.size(); i++)
			{
				qInfo() << "[IMCORE][TNUserDataHelper]updateCardStatus return,feedId :" << srcFeed[i] << " status : delete";
				_feedStatusMap.insert(srcFeed[i], false);
			}
		}
	}, _pluginParam, feedList.toList(), extData, extern_params);
}
void TNUserDataHelper::updateOrgCommStatus(const QString &feedId)
{
	Q_ASSERT(!feedId.isEmpty()
		&& feedId.startsWith("o_"));

	qInfo() << "[IMCORE][TNUserDataHelper]updateOrgCommStatus feed: " << feedId;
	if (_httpGetOrgCommunication.get() == nullptr)
	{
		_httpGetOrgCommunication = std::make_shared<TNHttpGetOrgCommunicationStatus>();
	}

	QSet<QString> feedList;
	feedList.insert(feedId);

	_httpGetOrgCommunication->GetJson([&](bool success, bool needRefreshUI, QJsonObject JsonObject)
	{
		if (success)
		{
			QJsonArray myListOrgArray = JsonObject.value("data").toArray();
			for (int p = 0; p < myListOrgArray.size(); p++)
			{
				QString oFeed = JsonObject.value("data").toArray().at(p).toObject().value("feedId").toString();
				QString status = JsonObject.value("data").toArray().at(p).toObject().value("communicateStatus").toString();
				if (!oFeed.isEmpty() && !status.isEmpty())
				{
					if (_feedStatusMap.contains(oFeed))
					{
						_feedStatusMap.remove(oFeed);
					}
					_feedStatusMap.insert(oFeed, status == QString("1"));
					qInfo() << "[IMCORE][TNUserDataHelper]updateOrgCommStatus return ,feed: " << oFeed << " status:" << status;
				}
			}
		}
	}, _pluginParam, feedList, false);
}
bool TNUserDataHelper::GetNativeCardStatus(const QString &feedId)
{
	Q_ASSERT(!feedId.isEmpty());

	bool result = true;
	QMap<QString, bool>::iterator it = _feedStatusMap.find(feedId);
	if (it != _feedStatusMap.end())
	{
		result = it.value();
	}
	return result;
}
void TNUserDataHelper::clearNativeCardStatus()
{
	QMutexLocker locker(&_feedMutex);
	_feedStatusMap.clear();
}