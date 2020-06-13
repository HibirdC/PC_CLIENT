#include "TNDataCache.h"
#include "common_global.h"
#include "TNDataControlServer.h"
#include "TNDbUtil.h"
#include "TNPathUtil.h"
#include <QDebug>
#include <QThread>
#include "TNDebugLog.h"
#include "TNCHNHelper.h"

TNDataCache* TNDataCache::_Instance = nullptr;
TNDataCache::TNDataCache(QObject *parent) :
	QObject(parent)
	,_isUpdateAllCache(false)
	, _currentMyfeedId(AVATAR_ALL_FEED)
{
	QObject::connect(this, SIGNAL(ResetSignal()), this, SLOT(reSetCacheSlot()));
}


TNDataCache::~TNDataCache()
{
}
TNDataCache* TNDataCache::GetInstance()
{
	static QMutex s_mutex;
	if (_Instance == nullptr)
	{
		QMutexLocker lock(&s_mutex);
		if (_Instance == nullptr)
			_Instance = new TNDataCache();
	}
	return _Instance;
}

void TNDataCache::UpdateMyStuffCache()
{
	QMutexLocker lock(&_mutex);
	qInfo() << "[LocalStorage][TNDataCache]UpdateMyStuffCache is using the lock,thread ID" << QString("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0'));
	_myStuff.clear();
	QList<QString> org_list;
	QList<QString> stuff_list;
	QList<QString> card_list;
	QMap<QString, st_FeedPtr> tempMap;
	TableBaseVec myStuffTableBaseVec;
	TNDataControlServer::GetInstance()->GetAllFieldsByTableName("MyStuff", myStuffTableBaseVec, DBTYPE_USER);
	for (TableBaseVec::iterator iter = myStuffTableBaseVec.begin(); iter != myStuffTableBaseVec.end(); iter++)
	{
		st_MyStuffPtr myStuffRecord = std::dynamic_pointer_cast<st_MyStuff>(*iter);
		if (myStuffRecord->GetFeedType() == FeedTypeGroup)
			continue;

		TableBaseVec feedTableBaseVec;
		TNDataControlServer::GetInstance()->Query(feedTableBaseVec, "Feed", "feedId", myStuffRecord->GetFeedID(), DBTYPE_USER);
		if (feedTableBaseVec.size() != 1)
			continue;
		QString feedId = myStuffRecord->GetFeedID();
		if (feedId.startsWith("o_"))
		{
			org_list.append(feedId);
		}
		else if (feedId.startsWith("s_"))
		{
			stuff_list.append(feedId);
		}
		else if (feedId.startsWith("c_"))
		{
			card_list.append(feedId);
		}
		st_FeedPtr feedRecord = std::dynamic_pointer_cast<st_Feed>(*feedTableBaseVec.begin());
		tempMap.insert(feedId, feedRecord);
	}
	for (QString feed: org_list)
	{
		_myStuff.append(tempMap.value(feed));
	}
	for (QString feed : stuff_list)
	{
		_myStuff.append(tempMap.value(feed));
	}
	for (QString feed : card_list)
	{
		_myStuff.append(tempMap.value(feed));
	}
	qInfo() << "[LocalStorage][TNDataCache]UpdateMyStuffCache release the lock,data size: " << _myStuff.size();
}
bool TNDataCache::IsInMyStuff(const QString &feedId)
{
	QMutexLocker lock(&_mutex);
	bool result = false;
	for (st_FeedPtr feed : _myStuff)
	{
		if (feed->GetFeedID() == feedId)
		{
			result = true;
			break;
		}
	}
	return result;
}
bool TNDataCache::IsInMyStuffFromDB(const QString &feed)
{
	QMutexLocker lock(&_mutex);
	TableBaseVec tableBaseVec;
	TNDataControlServer::GetInstance()->Query(tableBaseVec, "MyStuff", "feedId", feed, DBTYPE_USER);
	return tableBaseVec.size() > 0 ? true : false;
}
void TNDataCache::UpdateFriendCache()
{
	QMutexLocker lock(&_mutex);
	_FriendList.clear();
	qInfo() << "[LocalStorage][TNDataCache]UpdateFriendCache is using the lock,thread ID" << QString("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0'));
	TableBaseVec tempTableBaseVec;
	QList<QString> tempFeedList;
	TNDataControlServer::GetInstance()->Query(tempTableBaseVec, "JoinStuff", "feedType", FeedTypeContact, DBTYPE_USER);
	for (TableBaseVec::iterator iter = tempTableBaseVec.begin(); iter != tempTableBaseVec.end(); iter++)
	{
		TNStructFriend friendInfo;
		st_JoinStuffPtr joinStuff = std::dynamic_pointer_cast<st_JoinStuff>(*iter);
		const QString feedID = joinStuff->GetFeedID();
		QString belongFeedId = joinStuff->GetBelongTo();
		tempFeedList.append(feedID);

		friendInfo.remark = joinStuff->GetReMark();
		friendInfo.remarkpy = joinStuff->GetReMarkPY();

		TableBaseVec feedTableBaseVec;
		TNDataControlServer::GetInstance()->Query(feedTableBaseVec, "Feed", "feedId", feedID, DBTYPE_USER);
		for (TableBaseVec::iterator feedIter = feedTableBaseVec.begin(); feedIter != feedTableBaseVec.end(); feedIter++)
		{
			friendInfo.dupCount = 1;
			friendInfo.m_belongFeedId = belongFeedId;
			friendInfo.m_Feed = std::dynamic_pointer_cast<st_Feed>(*feedIter);
			_FriendList.insert(belongFeedId, friendInfo);
		}
	}
	for (QMultiMap<QString, TNStructFriend>::iterator it = _FriendList.begin(); it != _FriendList.end(); it++)
	{
		it->dupCount = tempFeedList.count(it->m_Feed->GetFeedID());
	}
	qInfo() << "[LocalStorage][TNDataCache]UpdateFriendCache release the lock,data size: " << _FriendList.size();
	return;
}
void TNDataCache::UpdateColleagueCache()
{
	QMutexLocker lock(&_mutex);
	_CompanyList.clear();
	qInfo() << "[LocalStorage][TNDataCache]UpdateColleagueCache is using the lock,thread ID" << QString("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0'));
	TableBaseVec companyTableBaseVec;
	TNDataControlServer::GetInstance()->Query(companyTableBaseVec, "MyStuff", "feedType", FeedTypeStaff, DBTYPE_USER);
	for (TableBaseVec::iterator iter = companyTableBaseVec.begin(); iter != companyTableBaseVec.end(); iter++)
	{
		TNStructCompany companyInfo;
		QMap<QString, st_FeedPtr> noGroupList;
		QMap<QString, QMultiMap<int, st_FeedPtr>> feedMapList;
		QMultiMap<int, QString> departmentList;
		st_MyStuffPtr myStuff = std::dynamic_pointer_cast<st_MyStuff>(*iter);
		const QString comId = myStuff->GetExt();
		/*
		应该是 comId
		*/
		if (comId.isEmpty())
			continue;

		TableBaseVec companyInfoVec;
		TNDataControlServer::GetInstance()->Query(companyInfoVec, "CompanyInfo", "comId", comId, DBTYPE_USER);
		if (companyInfoVec.size() == 0)
		{
			continue;
		}
		st_CompanyInfoPtr cominfo = std::dynamic_pointer_cast<st_CompanyInfo>(companyInfoVec[0]);
		companyInfo.m_companyId = cominfo->getComId();
		companyInfo.m_companyFeedId = cominfo->getComFeedId();
		companyInfo.m_companyName = cominfo->getComName();
		companyInfo.m_companyUrl = cominfo->getLogo();
		companyInfo.m_companyLogoText = cominfo->getIntroduction();
		companyInfo.m_companyAddr = cominfo->getComAddress();
		companyInfo.m_companyTel = cominfo->getPhone();
		companyInfo.m_companyEmail = cominfo->getEmail();
		companyInfo.m_orgCommunicationStatus = cominfo->getOrgCommunication();

		companyInfo.m_currentMyStaff = myStuff->GetFeedID();

		QString avatarFileName = TNPathUtil::getFeedAvatarPath(companyInfo.m_companyFeedId);
		if (!QFile::exists(avatarFileName))
		{
			avatarFileName = (":/Resources/toolWidget/defaultAvatar.png");
		}
		companyInfo.m_photoRes = avatarFileName;

		/*
		注意，以JoinStuff 表中的关系关系为主
		*/
		/*
		要显示没有组织目录的员工， 需要启用 m_noGroupfeed map， 在此处，将joinstuff 表中 的feed 和 colleaguerelation 里面的比对 ， 不在colleaguerelation中的即是要找的 。
		*/
		///*
		//The first to get the data that it's no group .
		//*/
		TableBaseVec noGroupTableBaseVec;
		TNDataControlServer::GetInstance()->MultiQuery(noGroupTableBaseVec, "JoinStuff", "belongTo", "feedType", myStuff->GetFeedID(), FeedTypeOrgStaff, DBTYPE_USER);
		for (TableBaseVec::iterator iter = noGroupTableBaseVec.begin(); iter != noGroupTableBaseVec.end(); iter++)
		{
			st_JoinStuffPtr joinStuffNoGroup = std::dynamic_pointer_cast<st_JoinStuff>(*iter);
			QString feedId = joinStuffNoGroup->GetFeedID();
			if (joinStuffNoGroup->GetBelongTo() != companyInfo.m_currentMyStaff)
			{
				continue;
			}
			companyInfo.m_belongId = joinStuffNoGroup->GetBelongTo();
			TableBaseVec feedTableBaseVec;
			TNDataControlServer::GetInstance()->Query(feedTableBaseVec, "Feed", "feedId", feedId, DBTYPE_USER);
			if (feedTableBaseVec.size()>0)
			{
				st_FeedPtr feed = std::dynamic_pointer_cast<st_Feed>(feedTableBaseVec[0]);
				Q_ASSERT(feed != NULL);
				noGroupList[feed->GetFeedID()] = feed;
			}
		}

		/*
		The second to get department data
		*/
		TableBaseVec departmentTableBaseVec;
		TNDataControlServer::GetInstance()->Query(departmentTableBaseVec, "ColleagueGroup", "comId", companyInfo.m_companyId, DBTYPE_USER);
		for (TableBaseVec::iterator iter = departmentTableBaseVec.begin(); iter != departmentTableBaseVec.end(); iter++)
		{
			st_ColleagueGroupPtr colleagueGroup = std::dynamic_pointer_cast<st_ColleagueGroup>(*iter);
			Q_ASSERT(colleagueGroup != NULL);
			if (colleagueGroup->GetGroupName() == ("思源总部"))//在组织结构服务器数据错误时， 把思源总部排在第一个
				departmentList.insert(colleagueGroup->GetOrderValue().toInt()-1, colleagueGroup->GetGroupName());
			else
				departmentList.insert(colleagueGroup->GetOrderValue().toInt(), colleagueGroup->GetGroupName());

			QMultiMap<int, st_FeedPtr> departStaffMap;
			TableBaseVec memberTableBaseVec;
			TNDataControlServer::GetInstance()->Query(memberTableBaseVec, "ColleagueRelation", "groupId", colleagueGroup->GetGroupId(), DBTYPE_USER);
			for (TableBaseVec::iterator iter = memberTableBaseVec.begin(); iter != memberTableBaseVec.end(); iter++)
			{
				st_ColleagueRelationPtr colleagueRelation = std::dynamic_pointer_cast<st_ColleagueRelation>(*iter);
				Q_ASSERT(colleagueRelation != NULL);
				if (colleagueRelation->GetBelongTo() != companyInfo.m_currentMyStaff)
				{
					continue;
				}
				companyInfo.m_belongId = colleagueRelation->GetBelongTo();
				TableBaseVec feedTableBaseVec;
				QMap<QString, st_FeedPtr>::iterator it;
				if ((it = noGroupList.find(colleagueRelation->GetFeedId())) != noGroupList.end())
				{
					noGroupList.erase(it);
				}
				else
				{
					//此关系无效，删掉关系
					qInfo() << "[LocalStorage][TNDataCache]UpdateColleagueCache Invalid colleagueRelation, so delete it . feed_belongTo_group: " << colleagueRelation->GetFeedBelongToGroup();
					TNDataControlServer::GetInstance()->DeleteFromTableNameByField("ColleagueRelation", "feed_belongTo_group", colleagueRelation->GetFeedBelongToGroup(), DBTYPE_USER);
					continue;
				}
				TNDataControlServer::GetInstance()->Query(feedTableBaseVec, "Feed", "feedId", colleagueRelation->GetFeedId(), DBTYPE_USER);
				for (TableBaseVec::iterator feedIter = feedTableBaseVec.begin(); feedIter != feedTableBaseVec.end(); feedIter++) //应该是唯一的
				{
					st_FeedPtr feed = std::dynamic_pointer_cast<st_Feed>(*feedIter);
					departStaffMap.insert(colleagueRelation->GetOrderValue().toInt(), feed);
				}
			}
			if (departStaffMap.size()>0)
				feedMapList.insert(colleagueGroup->GetGroupName(), departStaffMap);
		}

		companyInfo.m_feed = feedMapList;
		companyInfo.m_groupList = departmentList;
		companyInfo.m_noGroupfeed = noGroupList;
		_CompanyList.insert(companyInfo.m_currentMyStaff, companyInfo);
	}
	qInfo() << "[LocalStorage][TNDataCache]UpdateColleagueCache release the lock,data size: " << _CompanyList.size();
	return;
}
void TNDataCache::UpdateGroupChatCache()
{
	QMutexLocker lock(&_mutex);
	_GroupChatList.clear();
	qInfo() << "[LocalStorage][TNDataCache]UpdateGroupChatCache is using the lock,thread ID" << QString("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0'));
	TableBaseVec tempMyTableBaseVec;
	TNDataControlServer::GetInstance()->GetAllFieldsByTableName("GroupInfo", tempMyTableBaseVec, DBTYPE_USER);
	for (TableBaseVec::iterator iter = tempMyTableBaseVec.begin(); iter != tempMyTableBaseVec.end(); iter++)
	{
		TNStructGroupChat groupChatInfo;
		st_GroupInfoPtr groupInfo = std::dynamic_pointer_cast<st_GroupInfo>(*iter);

		if (groupInfo->GetGroupId().isEmpty() || groupInfo->GetMyFeedId().isEmpty()
			|| groupInfo->GetName().isEmpty() || groupInfo->GetMaxNum() == 0
			|| groupInfo->GetCreatorFeedId().isEmpty() || groupInfo->GetTopic().isEmpty()
			|| groupInfo->GetCurrNum() == 0)
		{
			qInfo() << "[LocalStorage][TNDataCache]UpdateGroupChatCache Invalid GroupChat,so delete it";
			TNDataControlServer::GetInstance()->DeleteFromTableNameByField("GroupInfo", "GroupId", groupInfo->GetGroupId(), DBTYPE_USER);
			continue;
		}
		TableBaseVec myStuffTableBaseVec;
		TNDataControlServer::GetInstance()->Query(myStuffTableBaseVec, "MyStuff", "feedId", groupInfo->GetCreatorFeedId(), DBTYPE_USER);
		/*
		Need to check if it is in my stuff .
		*/
		groupChatInfo.m_flag = myStuffTableBaseVec.size() > 0 ? 0 : 1;
		groupChatInfo.m_memberCount = groupInfo->GetCurrNum();
		groupChatInfo.m_groupChatFeed = groupInfo;

		/*
		Update GroupChat member
		*/
		groupChatInfo.m_groupMember = TNDbUtil::getAllGroupChatMemberCollectionSort(groupInfo->GetGroupId());
		_GroupChatList.insert(groupInfo->GetMyFeedId(), groupChatInfo);
	}
	qInfo() << "[LocalStorage][TNDataCache]UpdateGroupChatCache release the lock,data size: " << _GroupChatList.size();
	return;
}
void TNDataCache::UpdateGroupCache()
{
	QMutexLocker lock(&_mutex);
	_GroupList.clear();
	qInfo() << "[LocalStorage][TNDataCache]UpdateGroupCache is using the lock,thread ID" << QString("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0'));
	TableBaseVec tempMyTableBaseVec;
	TNDataControlServer::GetInstance()->Query(tempMyTableBaseVec, "MyStuff", "feedType", FeedTypeGroup, DBTYPE_USER);
	for (TableBaseVec::iterator iter = tempMyTableBaseVec.begin(); iter != tempMyTableBaseVec.end(); iter++)
	{
		TNStructGroup groupInfo;
		st_MyStuffPtr myStuff = std::dynamic_pointer_cast<st_MyStuff>(*iter);
		QString feedId = myStuff->GetFeedID();
		int memberNumber = myStuff->GetExt().toInt();
		TableBaseVec feedTableBaseVec;
		TNDataControlServer::GetInstance()->Query(feedTableBaseVec, "Feed", "feedId", feedId, DBTYPE_USER);
		if (feedTableBaseVec.size() > 0)
		{
			st_FeedPtr feed = std::dynamic_pointer_cast<st_Feed>(feedTableBaseVec[0]);
			groupInfo.m_flag = 1;
			groupInfo.m_memberCount = memberNumber;
			groupInfo.m_belongId = myStuff->GetBelongTo();
			groupInfo.m_groupFeed = feed;
			_GroupList.insert(groupInfo.m_belongId, groupInfo);
		}
	}

	TableBaseVec tempJoinTableBaseVec;
	TNDataControlServer::GetInstance()->Query(tempJoinTableBaseVec, "JoinStuff", "feedType", FeedTypeGroup, DBTYPE_USER);
	for (TableBaseVec::iterator iter = tempJoinTableBaseVec.begin(); iter != tempJoinTableBaseVec.end(); iter++)
	{
		TNStructGroup groupInfo;
		st_JoinStuffPtr joinStuff = std::dynamic_pointer_cast<st_JoinStuff>(*iter);
		QString feedId = joinStuff->GetFeedID();
		int memberNumber = joinStuff->GetExt1().toInt();
		int permisson = joinStuff->GetExt2().toInt();
		TableBaseVec feedTableBaseVec;
		TNDataControlServer::GetInstance()->Query(feedTableBaseVec, "Feed", "feedId", feedId, DBTYPE_USER);
		if (feedTableBaseVec.size() > 0)
		{
			st_FeedPtr feed = std::dynamic_pointer_cast<st_Feed>(feedTableBaseVec[0]);
			groupInfo.m_flag = permisson;
			groupInfo.m_memberCount = memberNumber;
			groupInfo.m_groupFeed = feed;
			groupInfo.m_belongId = joinStuff->GetBelongTo();
			_GroupList.insert(groupInfo.m_belongId, groupInfo);
		}
	}
	qInfo() << "[LocalStorage][TNDataCache]UpdateGroupCache release the lock,data size: " << _GroupList.size();
	return;
}
void TNDataCache::UpdateGroupChatCachebyId(QList<TNStructGroupChat> &groupChatInfoList, QString feedId, CacheGCOp type)
{
	QMutexLocker lock(&_mutex);
	qInfo() << "[LocalStorage][TNDataCache]UpdateGroupChatCachebyId is using the lock,thread ID" << QString("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0'));
	if (feedId.isEmpty() || !_isUpdateAllCache)
		return;
	if (type == CacheGCOp::gcAdd) //new
	{
		TableBaseVec tempMyTableBaseVec;
		TNDataControlServer::GetInstance()->Query(tempMyTableBaseVec, "GroupInfo", "groupId", feedId, DBTYPE_USER);
		if (tempMyTableBaseVec.size() >0)
		{
			TNStructGroupChat groupChatInfo;
			st_GroupInfoPtr myStuff = std::dynamic_pointer_cast<st_GroupInfo>(tempMyTableBaseVec[0]);

			TableBaseVec myStuffTableBaseVec;
			TNDataControlServer::GetInstance()->Query(myStuffTableBaseVec, "MyStuff", "feedId", myStuff->GetCreatorFeedId(), DBTYPE_USER);
			/*
			Need to check if it is in my stuff .
			*/
			groupChatInfo.m_flag = myStuffTableBaseVec.size() > 0 ? 0 : 1;
			groupChatInfo.m_memberCount = myStuff->GetCurrNum();
			groupChatInfo.m_groupChatFeed = myStuff;

			//更新成员
			QList<TNFriend> members = TNDbUtil::getAllGroupChatMemberCollectionSort(myStuff->GetGroupId());
			groupChatInfo.m_groupMember = members;
			_GroupChatList.insert(myStuff->GetMyFeedId(), groupChatInfo);
			groupChatInfoList = _GroupChatList.values();
			qInfo() << "[LocalStorage][TNDataCache]UpdateGroupChatCachebyId add : " << feedId << " members:" << members.size();
		}
	}
	else if (type == CacheGCOp::gcModify)
	{
		TableBaseVec tempMyTableBaseVec;
		TNDataControlServer::GetInstance()->Query(tempMyTableBaseVec, "GroupInfo", "groupId", feedId, DBTYPE_USER);
		if (tempMyTableBaseVec.size() >0)
		{
			TNStructGroupChat groupChatInfo;
			st_GroupInfoPtr myStuff = std::dynamic_pointer_cast<st_GroupInfo>(tempMyTableBaseVec[0]);

			TableBaseVec myStuffTableBaseVec;
			TNDataControlServer::GetInstance()->Query(myStuffTableBaseVec, "MyStuff", "feedId", myStuff->GetCreatorFeedId(), DBTYPE_USER);
			//更新成员
			QList<TNFriend> members = TNDbUtil::getAllGroupChatMemberCollectionSort(myStuff->GetGroupId());
			/*
			Need to check if it is in my stuff .
			*/
			groupChatInfo.m_flag = myStuffTableBaseVec.size() > 0 ? 0 : 1;
			groupChatInfo.m_memberCount = myStuff->GetCurrNum();
			groupChatInfo.m_groupChatFeed = myStuff;
			groupChatInfo.m_groupMember = members;
			for (QMultiMap<QString, TNStructGroupChat>::iterator it = _GroupChatList.begin();
				it != _GroupChatList.end(); it++)
			{
				st_GroupInfoPtr subStuff = it.value().m_groupChatFeed;
				if (subStuff->GetGroupId() == feedId)
				{
					*it = groupChatInfo;
					break;
				}
			}
			groupChatInfoList = _GroupChatList.values();
			qInfo() << "[LocalStorage][TNDataCache]UpdateGroupChatCachebyId modify : " << feedId << " members:" << members.size();
		}
	}
	else if (type == CacheGCOp::gcDel)
	{
		for (QMultiMap<QString, TNStructGroupChat>::iterator it = _GroupChatList.begin();
			it != _GroupChatList.end();)
		{
			st_GroupInfoPtr subStuff = it.value().m_groupChatFeed;
			if (subStuff->GetGroupId() == feedId)
			{
				it = _GroupChatList.erase(it);
				break;
			}
			it++;
		}
		groupChatInfoList = _GroupChatList.values();
		qInfo() << "[LocalStorage][TNDataCache]UpdateGroupChatCachebyId del : " << feedId;
	}
	qInfo() << "[LocalStorage][TNDataCache]UpdateGroupChatCachebyId release the lock,thread ID" << QString("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0'));
}
void TNDataCache::UpdateGroupChatCachebyId(QList<TNStructGroupChat> &groupChatInfoList, QString feedId, CacheGCOp type, TNStructGroupChat &groupChat)
{
	QMutexLocker lock(&_mutex);
	qInfo() << "[LocalStorage][TNDataCache]UpdateGroupChatCachebyId is using the lock,thread ID" << QString("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0'));
	if (feedId.isEmpty() || !_isUpdateAllCache)
		return;
	if (type == CacheGCOp::gcAdd) //new
	{
		TableBaseVec tempMyTableBaseVec;
		TNDataControlServer::GetInstance()->Query(tempMyTableBaseVec, "GroupInfo", "groupId", feedId, DBTYPE_USER);
		if (tempMyTableBaseVec.size() >0)
		{
			TNStructGroupChat groupChatInfo;
			st_GroupInfoPtr myStuff = std::dynamic_pointer_cast<st_GroupInfo>(tempMyTableBaseVec[0]);

			TableBaseVec myStuffTableBaseVec;
			TNDataControlServer::GetInstance()->Query(myStuffTableBaseVec, "MyStuff", "feedId", myStuff->GetCreatorFeedId(), DBTYPE_USER);
			/*
			Need to check if it is in my stuff .
			*/
			groupChatInfo.m_flag = myStuffTableBaseVec.size() > 0 ? 0 : 1;
			groupChatInfo.m_memberCount = myStuff->GetCurrNum();
			groupChatInfo.m_groupChatFeed = myStuff;

			//更新成员
			QList<TNFriend> members = TNDbUtil::getAllGroupChatMemberCollectionSort(myStuff->GetGroupId());
			groupChatInfo.m_groupMember = members;
			_GroupChatList.insert(myStuff->GetMyFeedId(), groupChatInfo);
			groupChat = groupChatInfo;
			groupChatInfoList = _GroupChatList.values();
			qInfo() << "[LocalStorage][TNDataCache]UpdateGroupChatCachebyId add : " << feedId;
		}
	}
	else if (type == CacheGCOp::gcModify)
	{
		TableBaseVec tempMyTableBaseVec;
		TNDataControlServer::GetInstance()->Query(tempMyTableBaseVec, "GroupInfo", "groupId", feedId, DBTYPE_USER);
		if (tempMyTableBaseVec.size() >0)
		{
			TNStructGroupChat groupChatInfo;
			st_GroupInfoPtr myStuff = std::dynamic_pointer_cast<st_GroupInfo>(tempMyTableBaseVec[0]);

			TableBaseVec myStuffTableBaseVec;
			TNDataControlServer::GetInstance()->Query(myStuffTableBaseVec, "MyStuff", "feedId", myStuff->GetCreatorFeedId(), DBTYPE_USER);
			//更新成员
			QList<TNFriend> members = TNDbUtil::getAllGroupChatMemberCollectionSort(myStuff->GetGroupId());
			/*
			Need to check if it is in my stuff .
			*/
			groupChatInfo.m_flag = myStuffTableBaseVec.size() > 0 ? 0 : 1;
			groupChatInfo.m_memberCount = myStuff->GetCurrNum();
			groupChatInfo.m_groupChatFeed = myStuff;
			groupChatInfo.m_groupMember = members;
			for (QMultiMap<QString, TNStructGroupChat>::iterator it = _GroupChatList.begin();
				it != _GroupChatList.end(); it++)
			{
				st_GroupInfoPtr subStuff = it.value().m_groupChatFeed;
				if (subStuff->GetGroupId() == feedId)
				{
					*it = groupChatInfo;
					break;
				}
			}
			groupChat = groupChatInfo;
			groupChatInfoList = _GroupChatList.values();
			qInfo() << "[LocalStorage][TNDataCache]UpdateGroupChatCachebyId modify : " << feedId;
		}
	}
	else if (type == CacheGCOp::gcDel)
	{
		for (QMultiMap<QString, TNStructGroupChat>::iterator it = _GroupChatList.begin();
			it != _GroupChatList.end();)
		{
			st_GroupInfoPtr subStuff = it.value().m_groupChatFeed;
			if (subStuff->GetGroupId() == feedId)
			{
				groupChat = (*it);
				it = _GroupChatList.erase(it);
				break;
			}
			it++;
		}
		groupChatInfoList = _GroupChatList.values();
		qInfo() << "[LocalStorage][TNDataCache]UpdateGroupChatCachebyId del : " << feedId;
	}
	qInfo() << "[LocalStorage][TNDataCache]UpdateGroupChatCachebyId release the lock,thread ID" << QString("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0'));
}
void TNDataCache::UpdateFriendCachebyId(QString feedId, QString belongId, CacheFOp type, TNStructFriend &myFrind)
{
	/*
	feedId feed_belongId
	*/
	QMutexLocker lock(&_mutex);
	qInfo() << "[LocalStorage][TNDataCache]UpdateFriendCachebyId is using the lock,thread ID" << QString("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0'));
	if (feedId.isEmpty() || !_isUpdateAllCache)
		return;
	if (type == CacheFOp::frAdd) //new
	{
		TNStructFriend friendInfo;
		TableBaseVec tempMyTableBaseVec;
		friendInfo.m_belongFeedId = belongId;
		TNDataControlServer::GetInstance()->Query(tempMyTableBaseVec, "Feed", "feedId", feedId, DBTYPE_USER);
		if (tempMyTableBaseVec.size() > 0)
		{
			st_FeedPtr feed = std::dynamic_pointer_cast<st_Feed>(tempMyTableBaseVec[0]);
			friendInfo.m_Feed = feed;
			int dupCount = updateFriendListDupCount(feedId, type);
			friendInfo.dupCount = dupCount == 0 ? 1 : dupCount;
			TNStructRemark remark = getRemarkFromRelation(feedId, belongId);
			friendInfo.remark = remark.remark;
			friendInfo.remarkpy = remark.remarkPy;
			_FriendList.insert(belongId, friendInfo);
			myFrind = friendInfo;
			qInfo() << "[LocalStorage][TNDataCache]UpdateFriendCachebyId add: " << feedId;
		}
		else
			qInfo() << "[LocalStorage][TNDataCache]UpdateFriendCachebyId Failed: When Update the friend ,but the feed don't insert database";
	}
	else if (type == CacheFOp::frDel)
	{
		updateFriendListDupCount(feedId, type);
		for (QMultiMap<QString, TNStructFriend>::iterator it = _FriendList.begin();
			it != _FriendList.end();)
		{
			st_FeedPtr feed = it.value().m_Feed;
			if (feed->GetFeedID() == feedId && it.key() == belongId)
			{
				it = _FriendList.erase(it);
				break;
			}
			it++;
		}
		qInfo() << "[LocalStorage][TNDataCache]UpdateFriendCachebyId del: " << feedId;
	}
	else if (type == CacheFOp::frModify)
	{
		for (QMultiMap<QString, TNStructFriend>::iterator it = _FriendList.begin();
			it != _FriendList.end();)
		{
			st_FeedPtr feed = it.value().m_Feed;
			if (feed->GetFeedID() == feedId && it.key() == belongId)
			{
				//构造新的数据
				TNStructFriend friendInfo;
				TableBaseVec tempMyTableBaseVec;
				friendInfo.m_belongFeedId = belongId;
				TNDataControlServer::GetInstance()->Query(tempMyTableBaseVec, "Feed", "feedId", feedId, DBTYPE_USER);
				if (tempMyTableBaseVec.size() > 0)
				{
					st_FeedPtr feed = std::dynamic_pointer_cast<st_Feed>(tempMyTableBaseVec[0]);
					friendInfo.m_Feed = feed;
					int dupCount = updateFriendListDupCount(feedId, type);
					friendInfo.dupCount = dupCount == 0 ? 1 : dupCount;
					TNStructRemark remark = getRemarkFromRelation(feedId, belongId);
					friendInfo.remark = remark.remark;
					friendInfo.remarkpy = remark.remarkPy;
					myFrind = friendInfo;
					*it = friendInfo;
					qInfo() << "[LocalStorage][TNDataCache]UpdateFriendCachebyId modify: " << feedId;
				}
				break;
			}
			it++;
		}
	}
	qInfo() << "[LocalStorage][TNDataCache]UpdateFriendCachebyId release the lock,thread ID" << QString("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0'));
}
int TNDataCache::updateFriendListDupCount(const QString &feedId, CacheFOp op)
{
	int count = 0;
	QList<TNStructFriend> list = _FriendList.values();
	for (QMultiMap<QString, TNStructFriend>::iterator it = _FriendList.begin();
		it != _FriendList.end(); it++)
	{
		if (it->m_Feed != nullptr &&
			it->m_Feed->GetFeedID() == feedId)
		{
			count = it->dupCount;
			if (op == CacheFOp::frAdd)
			{
				it->dupCount++;
			}
			else if (op == CacheFOp::frDel)
			{
				it->dupCount--;
			}
			count = it->dupCount;
		}
	}
	return count;
}
void TNDataCache::UpdateGroupCachebyId(QList<TNStructGroup> &groupInfoList, QString feedId, CacheGOp type)
{
	QMutexLocker lock(&_mutex);
	qInfo() << "[LocalStorage][TNDataCache]UpdateGroupCachebyId is using the lock,thread ID" << QString("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0'));
	if (feedId.isEmpty() || !_isUpdateAllCache)
		return;
	if (type == CacheGOp::grAdd) //new
	{
		TNStructGroup group;
		if (GetGroupInfobyId(group, feedId))
		{
			_GroupList.insert(group.m_belongId, group);
			groupInfoList = _GroupList.values();
			qInfo() << "[LocalStorage][TNDataCache]UpdateGroupCachebyId add : " << feedId;
		}
	}
	else if (type == CacheGOp::grModify)
	{
		TNStructGroup group;
		if (GetGroupInfobyId(group, feedId))
		{
			for (QMultiMap<QString, TNStructGroup>::iterator it = _GroupList.begin();
				it != _GroupList.end(); it++)
			{
				st_FeedPtr feed = it.value().m_groupFeed;
				if (feed->GetFeedID() == feedId)
				{
					*it = group;
					break;
				}
			}
			groupInfoList = _GroupList.values();
			qInfo() << "[LocalStorage][TNDataCache]UpdateGroupCachebyId modify : " << feedId;
		}
	}
	else if (type == CacheGOp::grDel)
	{
		for (QMultiMap<QString, TNStructGroup>::iterator it = _GroupList.begin();
			it != _GroupList.end();)
		{
			st_FeedPtr feed = it.value().m_groupFeed;
			if (feed->GetFeedID() == feedId)
			{
				it = _GroupList.erase(it);
				break;
			}
			it++;
		}
		groupInfoList = _GroupList.values();
		qInfo() << "[LocalStorage][TNDataCache]UpdateGroupCachebyId del : " << feedId;
	}
	qInfo() << "[LocalStorage][TNDataCache]UpdateGroupCachebyId release the lock,thread ID" << QString("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0'));
}
void TNDataCache::UpdateGroupCachebyId(QList<TNStructGroup> &groupInfoList, QString feedId, CacheGOp type,
	TNStructGroup &outGroup)
{
	QMutexLocker lock(&_mutex);
	qInfo() << "[LocalStorage][TNDataCache]UpdateGroupCachebyId is using the lock,thread ID" << QString("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0'));
	if (feedId.isEmpty() || !_isUpdateAllCache)
		return;
	if (type == CacheGOp::grAdd) //new
	{
		TNStructGroup group;
		if (GetGroupInfobyId(group, feedId))
		{
			outGroup = group;
			_GroupList.insert(group.m_belongId, group);
			groupInfoList = _GroupList.values();
			qInfo() << "[LocalStorage][TNDataCache]UpdateGroupCachebyId add : " << feedId;
		}
	}
	else if (type == CacheGOp::grModify)
	{
		TNStructGroup group;
		if (GetGroupInfobyId(group, feedId))
		{
			for (QMultiMap<QString, TNStructGroup>::iterator it = _GroupList.begin();
				it != _GroupList.end(); it++)
			{
				st_FeedPtr feed = it.value().m_groupFeed;
				if (feed->GetFeedID() == feedId)
				{
					*it = group;
					outGroup = group;
					break;
				}
			}
			groupInfoList = _GroupList.values();
			qInfo() << "[LocalStorage][TNDataCache]UpdateGroupCachebyId modify : " << feedId;
		}
	}
	else if (type == CacheGOp::grDel)
	{
		for (QMultiMap<QString, TNStructGroup>::iterator it = _GroupList.begin();
			it != _GroupList.end();)
		{
			st_FeedPtr feed = it.value().m_groupFeed;
			if (feed->GetFeedID() == feedId)
			{
				it = _GroupList.erase(it);
				break;
			}
			it++;
		}
		groupInfoList = _GroupList.values();
		qInfo() << "[LocalStorage][TNDataCache]UpdateGroupCachebyId del : " << feedId;
	}
	qInfo() << "[LocalStorage][TNDataCache]UpdateGroupCachebyId release the lock,thread ID" << QString("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0'));
}
bool TNDataCache::GetGroupInfobyId(TNStructGroup &group, QString groupId)
{
	/*
	需要在 我创建的 和我加入的 里查找
	*/
	/* 
	权限类型：1 版主 2 管理员 3 普通成员,
	*/

	qInfo() << "[LocalStorage][TNDataCache]GetGroupInfobyId start ";
	bool result = false;
	if (groupId.isEmpty())
		return result;

	TableBaseVec tempMyTableBaseVec;
	TNDataControlServer::GetInstance()->MultiQuery(tempMyTableBaseVec, "MyStuff", "feedType", "feedId", FeedTypeGroup, groupId, DBTYPE_USER);
	if (tempMyTableBaseVec.size() > 0)
	{
		TNStructGroup groupInfo;
		st_MyStuffPtr myStuff = std::dynamic_pointer_cast<st_MyStuff>(tempMyTableBaseVec[0]);
		if (myStuff != nullptr){
			QString feedId = myStuff->GetFeedID();
			int memberNumber = myStuff->GetExt().toInt();
			TableBaseVec feedTableBaseVec;
			TNDataControlServer::GetInstance()->Query(feedTableBaseVec, "Feed", "feedId", feedId, DBTYPE_USER);
			if (feedTableBaseVec.size() > 0){
				result = true;
				st_FeedPtr feed = std::dynamic_pointer_cast<st_Feed>(feedTableBaseVec[0]);
				groupInfo.m_flag = 1;
				groupInfo.m_memberCount = memberNumber;
				groupInfo.m_belongId = myStuff->GetBelongTo();
				groupInfo.m_groupFeed = feed;
				group = groupInfo;
				qInfo() << "[LocalStorage][TNDataCache]GetGroupInfobyId froup member: " << memberNumber;
			}
		}
	}
	else
	{
		tempMyTableBaseVec.clear();
		TNDataControlServer::GetInstance()->MultiQuery(tempMyTableBaseVec, "JoinStuff", "feedType", "feedId", FeedTypeGroup, groupId, DBTYPE_USER);
		if (tempMyTableBaseVec.size() > 0)
		{
			TNStructGroup groupInfo;
			st_JoinStuffPtr joinStuff = std::dynamic_pointer_cast<st_JoinStuff>(tempMyTableBaseVec[0]);
			if (joinStuff != nullptr){
				QString feedId = joinStuff->GetFeedID();
				int memberNumber = joinStuff->GetExt1().toInt();
				int permission = joinStuff->GetExt2().toInt();
				TableBaseVec feedTableBaseVec;
				TNDataControlServer::GetInstance()->Query(feedTableBaseVec, "Feed", "feedId", feedId, DBTYPE_USER);
				if (feedTableBaseVec.size() > 0)
				{
					result = true;
					st_FeedPtr feed = std::dynamic_pointer_cast<st_Feed>(feedTableBaseVec[0]);
					groupInfo.m_flag = permission;
					groupInfo.m_memberCount = memberNumber;
					groupInfo.m_belongId = joinStuff->GetBelongTo();
					groupInfo.m_groupFeed = feed;
					group = groupInfo;
					qInfo() << "[LocalStorage][TNDataCache]GetGroupInfobyId froup member: " << memberNumber;
				}
			}
		}
	}
	qInfo() << "[LocalStorage][TNDataCache]GetGroupInfobyId end ";
	return result;
}

void TNDataCache::getMyStuff(QList<st_FeedPtr>& mystuff, const QString &feedId)
{
	qInfo() << "[LocalStorage][TNDataCache]getMyStuff start ";
	if (feedId.isEmpty())
	{
		mystuff = _myStuff;
	}
	else
	{
		for (st_FeedPtr feed:_myStuff)
		{
			if (feed->GetFeedID() == feedId)
				mystuff.append(feed);
		}
	}
	qInfo() << "[LocalStorage][TNDataCache]getMyStuff end ,data size: " << mystuff.size();
}
st_FeedPtr TNDataCache::getMyFirstPersonalCard()
{
	for (st_FeedPtr feed : _myStuff)
	{
		if (feed->GetFeedID().startsWith("c_"))
			return feed;
	}

	Q_ASSERT(!"error! no exist personal card");
	return st_FeedPtr();
}
QList<TNFriend> TNDataCache::GetGroupChatMemberCache(const QString &groupId)
{
	QMutexLocker lock(&_mutex);
	qInfo() << "[LocalStorage][TNDataCache]GetGroupChatMemberCache is using the lock,thread ID" << QString("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0'));
	QList<TNFriend> result;
	for (TNStructGroupChat gchat: _GroupChatList)
	{
		if (gchat.m_groupChatFeed->GetGroupId() == groupId)
		{
			for (TNFriend info : gchat.m_groupMember)
			{
				result.append(info);
			}
			break;
		}
	}
	qInfo() << "[LocalStorage][TNDataCache]GetGroupChatMemberCache release the lock,data size: " << result.size();
	return result;
}
void TNDataCache::UpdateInStepCache(QList<UINotifyData> dataList, int type)
{
	if (!_isUpdateAllCache)
	{
		return;
	}
	if (type == 2)
	{
		for (UINotifyData uiMsg : dataList)
		{
			QList<TNStructGroup> InfoList;
			switch (uiMsg.operateType)
			{
			case UI_OPERATE_ADD:
				UpdateGroupCachebyId(InfoList, uiMsg.feedId, CacheGOp::grAdd);
				break;
			case UI_OPERATE_DEL:
				UpdateGroupCachebyId(InfoList, uiMsg.feedId, CacheGOp::grDel);
				break;
			}
		}
	}
	else if (type == 1)
	{
		for (UINotifyData uiMsg : dataList)
		{
			QList<TNStructGroupChat> InfoList;
			switch (uiMsg.operateType)
			{
			case UI_OPERATE_ADD:
				if (IsExistbyGroupChatId(uiMsg.feedId))
				{
					UpdateGroupChatCachebyId(InfoList, uiMsg.feedId, CacheGCOp::gcModify);
				}
				else
				{
					UpdateGroupChatCachebyId(InfoList, uiMsg.feedId, CacheGCOp::gcAdd);
				}
				break;
			case UI_OPERATE_DEL:
				UpdateGroupChatCachebyId(InfoList, uiMsg.feedId, CacheGCOp::gcDel);
				break;
			}
		}
	}
	else if (type == 0)
	{
		for (UINotifyData uiMsg : dataList)
		{
			QString feedId, belongId;
			TableBaseVec tempMyTableBaseVec;
			int pos = uiMsg.feedId.indexOf("_", 2);
			if (pos == -1)
			{
				continue;
			}
			TNStructFriend myFriend;
			feedId = uiMsg.feedId.mid(0, pos);
			belongId = uiMsg.feedId.mid(pos + 1, uiMsg.feedId.length() - pos - 1);
			switch (uiMsg.operateType)
			{
			case UI_OPERATE_ADD:
				if (!IsExistbyFriendFeedId(feedId))
				{
					UpdateFriendCachebyId(feedId, belongId, CacheFOp::frAdd, myFriend);
				}
				else
				{
					UpdateFriendCachebyId(feedId, belongId, CacheFOp::frModify, myFriend);
				}
				break;
			case UI_OPERATE_DEL:
				UpdateFriendCachebyId(feedId, belongId, CacheFOp::frDel, myFriend);
				break;
			}
		}
	}
}
bool TNDataCache::IsExistbyFriendFeedId(QString feedId)
{
	QMutexLocker lock(&_mutex);
	qInfo() << "[LocalStorage][TNDataCache]IsExistbyFriendFeedId is using the lock,thread ID" << QString("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0'));
	bool result = false;
	for (QMultiMap<QString, TNStructFriend>::iterator iter = _FriendList.begin(); iter != _FriendList.end(); iter++)
	{
		TNStructFriend Info = iter.value();
		st_FeedPtr feed = Info.m_Feed;
		if (feed->GetFeedID() == feedId)
		{
			result = true;
			break;
		}
	}
	qInfo() << "[LocalStorage][TNDataCache]IsExistbyFriendFeedId release the lock,thread ID" << QString("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0'));
	return result;
}
bool TNDataCache::IsExistbyGroupChatId(QString feedId)
{
	QMutexLocker lock(&_mutex);
	qInfo() << "[LocalStorage][TNDataCache]IsExistbyGroupChatId is using the lock,thread ID" << QString("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0'));
	bool result = false;
	for (QMultiMap<QString, TNStructGroupChat>::iterator iter = _GroupChatList.begin(); iter != _GroupChatList.end(); iter++)
	{
		TNStructGroupChat groupChatInfo = iter.value();
		st_GroupInfoPtr myStuff = groupChatInfo.m_groupChatFeed;
		if (myStuff->GetGroupId() == feedId)
		{
			result = true;
			break;
		}
	}
	qInfo() << "[LocalStorage][TNDataCache]IsExistbyGroupChatId release the lock,thread ID" << QString("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0'));
	return result;
}
void  TNDataCache::GetColleagueCache(QList<TNStructCompany>& companyList, QString myFeedId)
{
	QMutexLocker lock(&_mutex);
	QString selectMyFeedId = myFeedId.isEmpty() ? _currentMyfeedId : myFeedId;
	qInfo() << "[LocalStorage][TNDataCache]GetColleagueCache is is ok ,size: " << _CompanyList.size();
	if (selectMyFeedId.isEmpty() || selectMyFeedId == AVATAR_ALL_FEED)
		companyList.append(_CompanyList.values());
	else
		companyList.append(_CompanyList.values(selectMyFeedId));
}
void TNDataCache::GetGroupCache(QList<TNStructGroup>& groupList, QString myFeedId)
{
	QMutexLocker lock(&_mutex);
	qInfo() << "[LocalStorage][TNDataCache]GetGroupCache is is ok ,size: " << _GroupList.size();
	QString selectMyFeedId = myFeedId.isEmpty() ? _currentMyfeedId : myFeedId;
	if (selectMyFeedId.isEmpty() || selectMyFeedId == AVATAR_ALL_FEED)
		groupList.append(_GroupList.values());
	else
		groupList.append(_GroupList.values(_currentMyfeedId));
}
void TNDataCache::GetGroupChatCache(QList<TNStructGroupChat>& groupChatList, QString myFeedId)
{
	QMutexLocker lock(&_mutex);
	qInfo() << "[LocalStorage][TNDataCache]GetGroupChatCache is is ok ,size: " << _GroupChatList.size();
	QString selectMyFeedId = myFeedId.isEmpty() ? _currentMyfeedId : myFeedId;
	if (selectMyFeedId.isEmpty() || selectMyFeedId == AVATAR_ALL_FEED)
		groupChatList.append(_GroupChatList.values());
	else
		groupChatList.append(_GroupChatList.values(selectMyFeedId));
}
void TNDataCache::GetFriendCache(QList<TNStructFriend>& friendList, QString myFeedId)
{
	QMutexLocker lock(&_mutex);
	QString selectMyFeedId = myFeedId.isEmpty() ? _currentMyfeedId : myFeedId;
	if (selectMyFeedId.isEmpty() || selectMyFeedId == AVATAR_ALL_FEED)
		friendList.append(_FriendList.values());
	else
		friendList.append(_FriendList.values(selectMyFeedId));
	qInfo() << "[LocalStorage][TNDataCache]GetFriendCache is ok ,size: " << friendList.size();
}
void TNDataCache::ReSetCache()
{
	emit ResetSignal();
}
void TNDataCache::updateAllCacheSlot()
{
	qInfo() << "[LocalStorage][TNDataCache]updateAllCacheSlot start,thread ID" << QString("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0'));
	_isUpdateAllCache = false;
	UpdateMyStuffCache();
	UpdateFriendCache();
	qInfo() << "[LocalStorage][TNDataCache]updateAllCacheSlot _FriendList: " << _FriendList.size();
	UpdateColleagueCache();
	qInfo() << "[LocalStorage][TNDataCache]updateAllCacheSlot _CompanyList: " << _CompanyList.size();
	UpdateGroupCache();
	qInfo() << "[LocalStorage][TNDataCache]updateAllCacheSlot _GroupList: " << _GroupList.size();
	UpdateGroupChatCache();
	qInfo() << "[LocalStorage][TNDataCache]updateAllCacheSlot _GroupChatList: " << _GroupChatList.size();
	_isUpdateAllCache = true;
	emit HasUpdateAllCache();
	qInfo() << "[LocalStorage][TNDataCache]updateAllCacheSlot end";
}
void TNDataCache::reSetCacheSlot()
{
	qInfo() << "[LocalStorage][TNDataCache]ReSetCacheSlot start,thread ID" << QString("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0'));
	_myStuff.clear();
	_FriendList.clear();
	_CompanyList.clear();
	_GroupList.clear();
	_GroupChatList.clear();
	_currentMyfeedId = AVATAR_ALL_FEED;
	qInfo() << "[LocalStorage][TNDataCache]ReSetCacheSlot end";
}
void TNDataCache::UpdateColleagueSlot()
{
	qInfo() << "[LocalStorage][TNDataCache]UpdateColleagueSlot start,old size:" << _CompanyList.size();
	UpdateColleagueCache();
	qInfo() << "[LocalStorage][TNDataCache]UpdateColleagueSlot end, new size:" << _CompanyList.size();
}
bool TNDataCache::IsCurrentCardCache(const QString &feedId)
{
	qInfo() << "[LocalStorage][TNDataCache]Current card: " << _currentMyfeedId;
    return feedId == _currentMyfeedId || _currentMyfeedId == AVATAR_ALL_FEED;
}

void TNDataCache::SynUpdateFeedCache(st_FeedPtr  feed, int type, int sources)
{
	if (feed == nullptr || feed->GetFeedID().isEmpty())
	{
		return;
	}
	qInfo() << "[LocalStorage][TNDataCache]SynUpdateFeedCache feed is changed, feed: " 
		<< feed->GetFeedID() <<",type :"<<type <<" sources:"<<sources;

	QString name, namePY, subName, avatarURL, feedId,userId;
	feedId = feed->GetFeedID();
	name = feed->GetTitle();
	subName = feed->GetSubTile();
	avatarURL = feed->GetAvatarID();
	namePY = feed->GetTitlePinYin();
	userId = feed->GetUserID();

	if (type == 0 || type == 1)//好友,同事
	{
		emit guysUpdateCard(feedId, avatarURL, name, subName, userId, namePY, sources);
		//更新缓存
		QMutexLocker lock(&_mutex);
		if (feedId.startsWith("c_"))
		{
			for (QMultiMap<QString, TNStructFriend> ::iterator it = _FriendList.begin();
				it != _FriendList.end(); it++)
			{
				if ((*it).m_Feed->GetFeedID() == feedId)
				{
					(*it).m_Feed->SetAvatarID(avatarURL);
					(*it).m_Feed->SetTitle(name);
					(*it).m_Feed->SetSubTile(subName);
					(*it).m_Feed->SetTitlePinYin(namePY);
					(*it).m_Feed->SetUserID(userId);
				}
			}
		}
		else if (feedId.startsWith("s_"))
		{
			for (QMultiMap<QString, TNStructCompany> ::iterator it = _CompanyList.begin();
				it != _CompanyList.end(); it++)
			{
				for (QMap<QString, st_FeedPtr>::iterator noGroupId = (*it).m_noGroupfeed.begin();
					noGroupId != (*it).m_noGroupfeed.end(); noGroupId++)
				{
					if (noGroupId.key() == feedId)
					{
						(*noGroupId)->SetAvatarID(avatarURL);
						(*noGroupId)->SetTitle(name);
						(*noGroupId)->SetSubTile(subName);
						(*noGroupId)->SetTitlePinYin(namePY);
						(*noGroupId)->SetUserID(userId);
						break;
					}
				}
				QMap<QString, QMultiMap<int, st_FeedPtr>>::iterator departIt;
				for (departIt = (*it).m_feed.begin(); departIt != (*it).m_feed.end(); departIt++)
				{
					QMultiMap<int, st_FeedPtr>::iterator memberIt;
					for (memberIt = (*departIt).begin(); memberIt != (*departIt).end(); memberIt++)
					{
						if (memberIt.value()->GetFeedID() == feedId)
						{
							(*memberIt)->SetAvatarID(avatarURL);
							(*memberIt)->SetTitle(name);
							(*memberIt)->SetSubTile(subName);
							(*memberIt)->SetTitlePinYin(namePY);
							(*memberIt)->SetUserID(userId);
							break;
						}
					}
				}
			}
		}
		for (QMultiMap<QString, TNStructGroupChat>::iterator it = _GroupChatList.begin();
			it != _GroupChatList.end(); it++)
		{
			for (QList<TNFriend>::iterator gcIt = (*it).m_groupMember.begin();
				gcIt != (*it).m_groupMember.end(); gcIt++)
			{
				if ((*gcIt).m_friendFeedId == feedId)
				{
					(*gcIt).m_avatarURL = avatarURL;
					(*gcIt).m_nickName = name;
					(*gcIt).m_subTitle = subName;
					(*gcIt).m_pinYin = namePY;
					break;
				}
			}
		}
		/*
		更新我的信息
		*/
		for (QList<st_FeedPtr>::iterator it = _myStuff.begin(); it != _myStuff.end(); it++)
		{
			if ((*it)->GetFeedID() == feedId)
			{
				(*it)->SetAvatarID(avatarURL);
				(*it)->SetTitle(name);
				(*it)->SetSubTile(subName);
				(*it)->SetTitlePinYin(namePY);
				break;
			}
		}
	}
	else if (type == 2)
	{
		/*
		目前未对社区成员做处理
		*/
		for (QMultiMap<QString, TNStructGroup>::iterator it = _GroupList.begin();
			it != _GroupList.end(); it++)
		{
			if (it->m_groupFeed->GetFeedID() == feedId)
			{
				(*it).m_groupFeed->SetAvatarID(avatarURL);
				(*it).m_groupFeed->SetTitle(name);
				(*it).m_groupFeed->SetSubTile(subName);
				(*it).m_groupFeed->SetTag(feed->GetTag());
				(*it).m_groupFeed->SetTitlePinYin(namePY);
				break;
			}
		}
	}
}
void TNDataCache::InstallCatcheFeedUpdateNotify(const QObject * resultReceiver) 
{
	QObject::connect(this, SIGNAL(guysUpdateCard(const QString &, const QString &, const QString &, const QString &, const QString &, const QString &, int)),
		resultReceiver, SLOT(feedCardUpdateFromCatche(const QString &, const QString &, const QString &, const QString &, const QString &, const QString &, int)));
}

void TNDataCache::InstallCatcheGroupChatUpdateNotify(const QObject * resultReceiver)
{
	QObject::connect(this, SIGNAL(guysUpdateGroupChat(const QString &)), resultReceiver, SLOT(GroupChatUpdateFromCatche(const QString &)));
}

int TNDataCache::GetSpecialFriendCount(const QString & feedID)
{
	QMutexLocker lock(&_mutex);
	QList<TNStructFriend> currentAllFriend;
	if (_currentMyfeedId.isEmpty() || _currentMyfeedId == AVATAR_ALL_FEED)
		currentAllFriend = _FriendList.values();
	else
		currentAllFriend = _FriendList.values(_currentMyfeedId);
	int count = 0;
	foreach(TNStructFriend info, currentAllFriend)
	{
		if (info.m_Feed->GetFeedID() == feedID)
		{
			count = info.dupCount;
			break;
		}
	}
	return count;
}
st_FeedPtr TNDataCache::getSpecialFriendFeed(const QString & feedID, const QString &belongFeed)
{
	QMutexLocker lock(&_mutex);
	st_FeedPtr result;
	QList<TNStructFriend> currentAllFriend;
	if (_currentMyfeedId.isEmpty() || _currentMyfeedId == AVATAR_ALL_FEED)
		currentAllFriend = _FriendList.values();
	else
		currentAllFriend = _FriendList.values(_currentMyfeedId);
	foreach(TNStructFriend info, currentAllFriend)
	{
		if (info.m_Feed->GetFeedID() == feedID
			&&info.m_belongFeedId == belongFeed)
		{
			result = info.m_Feed;
			break;
		}
	}
	return result;
}
QString TNDataCache::GetMyTitle(const QString &myFeed)
{
	QString myTitle;
	for (st_FeedPtr feed : _myStuff)
	{
		if (feed->GetFeedID() == myFeed)
		{
			myTitle = feed->GetTitle();
		}
	}
	return myTitle;
}

void TNDataCache::setPhoneNum(const QString &phone_num)
{
    _currentPhoneNum = phone_num;
}
void TNDataCache::SynUpdateGroupChatCache(st_GroupInfoPtr group)
{
	if (group == nullptr || group->GetGroupId().isEmpty())
	{
		return;
	}
	qInfo() << "[LocalStorage][TNDataCache]SynUpdateGroupCache group is changed, feed: " << group->GetGroupId();

	emit guysUpdateGroupChat(group->GetGroupId());

	for (QMultiMap<QString, TNStructGroupChat>::iterator it = _GroupChatList.begin();
		it != _GroupChatList.end(); it++)
	{
		if (it->m_groupChatFeed->GetGroupId() == group->GetGroupId())
		{
			(*it).m_groupChatFeed = group;
			break;
		}
	}
}
int TNDataCache::getGroupStatusByID(const QString &groupId)
{
	int res = -1;
	for (QMultiMap<QString, TNStructGroup>::iterator it = _GroupList.begin();
		it != _GroupList.end(); it++)
	{
		if (it->m_groupFeed->GetFeedID() == groupId)
		{
			res = it->m_flag;
			break;
		}
	}
	return res;
}
void TNDataCache::updateGroupMemberCount(const QString &groupId, int count)
{
	Q_ASSERT(!groupId.isEmpty());

	QMutexLocker lock(&_mutex);
	qInfo() << "[LocalStorage][TNDataCache]updateGroupMemberCount groupId:" << groupId;
	for (QMultiMap<QString, TNStructGroup>::iterator it = _GroupList.begin();
		it != _GroupList.end(); it++)
	{
		if (it->m_groupFeed->GetFeedID() == groupId)
		{
			(*it).m_memberCount = count;
			break;
		}
	}
}
const QString TNDataCache::getFriendFeedReMark(const QString &feedId, const QString &belongFeed)
{
	QString remark;
	for (QMultiMap<QString, TNStructFriend> ::iterator it = _FriendList.begin();
		it != _FriendList.end(); it++)
	{
		if ((*it).m_Feed->GetFeedID() == feedId && (*it).m_belongFeedId == belongFeed)
		{
			remark = (*it).remark;
			break;
		}
	}
    qDebug() << "[LocalStorage][TNDataCache]getFriendFeedReMark result:" << remark;
	return remark;
}
const TNStructRemark TNDataCache::getFriendFeedReMarkWithPY(const QString &feedId, const QString &belongFeed)
{
	TNStructRemark result;
	for (QMultiMap<QString, TNStructFriend> ::iterator it = _FriendList.begin();
		it != _FriendList.end(); it++)
	{
		if ((*it).m_Feed->GetFeedID() == feedId && (*it).m_belongFeedId == belongFeed)
		{
			result.remark = (*it).remark;
			result.remarkPy = (*it).remarkpy;
			break;
		}
	}
	qInfo() << "[LocalStorage][TNDataCache]getFriendFeedReMark result:" << result.remark;
	return result;
}
bool TNDataCache::updateFriendFeedReMark(const QString &feedId, const QString &belongFeed, const QString &remark)
{
	Q_ASSERT(!feedId.isEmpty());

	QMutexLocker lock(&_mutex);
	qInfo() << "[LocalStorage][TNDataCache]updateFriendFeedReMark feedId:" << feedId << " Remark:" << remark;
	bool res = false;
	/*
	更新好友备注
	*/
	for (QMultiMap<QString, TNStructFriend> ::iterator it = _FriendList.begin();
		it != _FriendList.end(); it++)
	{
		if ((*it).m_Feed->GetFeedID() == feedId && (*it).m_belongFeedId == belongFeed)
		{
			if ((*it).remark != remark)
			{
				(*it).remark = remark;
				(*it).remarkpy = TNCHNHelper::GetPinyins(remark);
			}
			res = true;
			break;
		}
	}
	/*
	更新所有群聊成员备注
	*/
	for (QMultiMap<QString, TNStructGroupChat>::iterator it = _GroupChatList.begin();
		it != _GroupChatList.end(); it++)
	{
		for (QList<TNFriend>::iterator gcIt = (*it).m_groupMember.begin();
			gcIt != (*it).m_groupMember.end(); gcIt++)
		{
			if ((*gcIt).m_friendFeedId == feedId && 
				(*gcIt).m_belongFeedId == belongFeed)
			{
				(*gcIt).m_remark = remark;
				(*gcIt).m_remarkPy = TNCHNHelper::GetPinyins(remark);
				break;
			}
		}
	}
	return res;
}
int TNDataCache::getNotifyMsgCache(QList<st_SessionPtr> &notifyList)
{
	TableBaseVec feedTableBaseVec;
	TNDataControlServer::GetInstance()->Query(feedTableBaseVec, "Session", "type",NOTIFYSESSION_TYPE, DBTYPE_MSG);
	for (int i = 0; i < feedTableBaseVec.size(); i++)
	{
		notifyList.append(std::dynamic_pointer_cast<st_Session>(feedTableBaseVec[i]));
	}
	qInfo() << "[LocalStorage][TNDataCache]getNotifyMsgCache size:" << notifyList.size();
	return notifyList.size();
}
void TNDataCache::updateOrgCommunicationStatus(const QString &feedId, const QString & status)
{
	Q_ASSERT(!feedId.isEmpty() && !status.isEmpty());

	QMutexLocker lock(&_mutex);
	bool ret = false;
	qInfo() << "[LocalStorage][TNDataCache]updateOrgCommunicationStatus feed:" << feedId << " status:" << status;
	for (QList<st_FeedPtr>::iterator it = _myStuff.begin();
		it != _myStuff.end(); it++)
	{
		if ((*it)->GetFeedID() == feedId)
		{
			ret = true;
			(*it)->SetExt1(status);
			break;
		}
	}
	//如果不是我的
	if (!ret)
	{
		for (QMultiMap<QString, TNStructFriend> ::iterator it = _FriendList.begin();
			it != _FriendList.end(); it++)
		{
			if ((*it).m_Feed->GetFeedID() == feedId)
			{
				(*it).m_Feed->SetExt1(status);
			}
		}
	}
}
QString TNDataCache::innerGetOrgCommunicationStatus(const QString &feedId)
{
	Q_ASSERT(!feedId.isEmpty());

	/*
	先从我的组织名片里找,其次在我的好友里找
	*/
	QString result;
	for (QList<st_FeedPtr>::iterator it = _myStuff.begin();
		it != _myStuff.end(); it++)
	{
		if ((*it)->GetFeedID() == feedId)
		{
			result = (*it)->GetExt1();
			qInfo() << "[LocalStorage][TNDataCache]innerGetOrgCommunicationStatus feed:" << feedId << " status:" << (*it)->GetExt1();
			break;
		}
	}
	if (result.isEmpty())
	{
		for (QMultiMap<QString, TNStructFriend>::iterator it = _FriendList.begin();
			it != _FriendList.end();it++)
		{
			if (it->m_Feed->GetFeedID() == feedId)
			{
				result = it->m_Feed->GetExt1();
				qInfo() << "[LocalStorage][TNDataCache]innerGetOrgCommunicationStatus feed:" << feedId << " status:" << it->m_Feed->GetExt1();
				break;
			}
		}
	}
	return result;
}
bool TNDataCache::getOrgCommunicationStatus(const QString &feedId)
{
    Q_ASSERT(!feedId.isEmpty() && feedId.startsWith("o_"));
	/*
	默认可沟通
	*/
	bool ret = true;
	if (innerGetOrgCommunicationStatus(feedId) == QString("0"))
	{
		ret = false;
	}
	return ret;
}
bool TNDataCache::isChangedOfBaseInfo(QString feedId, QString name, QString subtitle, QString headImage,int type)
{
	Q_ASSERT(!feedId.isEmpty());
	qInfo() << "[LocalStorage][TNDataCache]isChangedOfBaseInfo feed:" << feedId;
	QMutexLocker lock(&_mutex);
	bool ret = true;
	bool isMySelf = false;
	if (type == 0 || type == 1)
	{
		for (st_FeedPtr feed : _myStuff)
		{
			if (feed->GetFeedID() == feedId)
			{
				isMySelf = true;
				if (feed->GetTitle() == name && feed->GetSubTile() == subtitle &&
					feed->GetAvatarID() == headImage)
				{
					ret = false;
					break;
				}
			}
		}
	}
	if (!isMySelf)
	{
		switch (type)
		{
		case 0:
			//好友
			for (QMultiMap<QString, TNStructFriend> ::iterator it = _FriendList.begin();
				it != _FriendList.end(); it++)
			{
				if (it->m_Feed->GetFeedID() == feedId&& it->m_Feed->GetSubTile() == subtitle &&
					it->m_Feed->GetAvatarID() == headImage &&it->m_Feed->GetTitle() == name)
				{
					ret = false;
					break;
				}
			}
			break;
		case 1:
			//同事
			for (QMultiMap<QString, TNStructCompany> ::iterator it = _CompanyList.begin();
				it != _CompanyList.end(); it++)
			{
				bool isFind = false;
				for (QMap<QString, st_FeedPtr>::iterator noGroupId = (*it).m_noGroupfeed.begin();
					noGroupId != (*it).m_noGroupfeed.end(); noGroupId++)
				{
					if (noGroupId.key() == feedId && (*noGroupId)->GetSubTile() == subtitle &&
						(*noGroupId)->GetAvatarID() == headImage && (*noGroupId)->GetTitle() == name)
					{
						ret = false;
						isFind = true;
						break;
					}
				}
				if (!isFind)
				{
					QMap<QString, QMultiMap<int, st_FeedPtr>>::iterator departIt;
					for (departIt = (*it).m_feed.begin(); departIt != (*it).m_feed.end(); departIt++)
					{
						QMultiMap<int, st_FeedPtr>::iterator memberIt;
						for (memberIt = (*departIt).begin(); memberIt != (*departIt).end(); memberIt++)
						{
							if (memberIt.value()->GetFeedID() == feedId && (*memberIt)->GetSubTile() == subtitle &&
								(*memberIt)->GetAvatarID() == headImage && (*memberIt)->GetTitle() == name)
							{
								ret = false;
								isFind = true;
								break;
							}
						}
					}
				}
				if (isFind)
					break;
			}
			break;
		case 2:
			for (QMultiMap<QString, TNStructGroup>::iterator it = _GroupList.begin();
				it != _GroupList.end(); it++)
			{
				/*
				仅判断头像
				*/
				if (it->m_groupFeed->GetFeedID() == feedId &&it->m_groupFeed->GetAvatarID() == headImage)
				{
					ret = false;
					break;
				}
			}
			break;
		case 3:
			break;
		default:
			break;
		}
	}
	qInfo() << "[LocalStorage][TNDataCache]isChangedOfBaseInfo return :" << ret;
	return ret;
}
bool TNDataCache::isChangedOfGroupInfo(QString feedId, QString name, QString headImage, int memberCount)
{
	Q_ASSERT(!feedId.isEmpty());
	QMutexLocker lock(&_mutex);
	qInfo() << "[LocalStorage][TNDataCache]isChangedOfGroupInfo feed:" << feedId;
	bool ret = true;
	for (QMultiMap<QString, TNStructGroupChat>::iterator it = _GroupChatList.begin();
		it != _GroupChatList.end(); it++)
	{
		if (it->m_groupChatFeed->GetGroupId() == feedId &&it->m_groupChatFeed->GetHeaderImage() == headImage
			&&it->m_groupChatFeed->GetName() == name && it->m_groupChatFeed->GetCurrNum() == memberCount)
		{
			ret = false;
			break;
		}
	}
	qInfo() << "[LocalStorage][TNDataCache]isChangedOfGroupInfo return:" << ret;
	return ret;
}
const TNStructRemark TNDataCache::getRemarkFromRelation(const QString &feedId, const QString &belongFeed)
{
	Q_ASSERT(!feedId.isEmpty());
	Q_ASSERT(!belongFeed.isEmpty());

	TNStructRemark result;
	QString key = feedId + "_" + belongFeed;
	TableBaseVec tempTableBaseVec;
	TNDataControlServer::GetInstance()->MultiQuery(tempTableBaseVec, "JoinStuff", "feed_belong", "feedType", key, FeedTypeContact, DBTYPE_USER);
	if (tempTableBaseVec.size() > 0){
		st_JoinStuffPtr joinStuff = std::dynamic_pointer_cast<st_JoinStuff>(tempTableBaseVec[0]);
		result.remark = joinStuff->GetReMark();
		result.remarkPy = joinStuff->GetReMarkPY();
	}
	qInfo() << "[LocalStorage][TNDataCache]getRemarkFromRelation key:" << key << " result:" << result.remark;
	return result;
}