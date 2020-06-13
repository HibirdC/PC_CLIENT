#include "TNNoticeUpdater.h"
#include "qjsonobject.h"
#include "qjsonarray.h"
#include "TNDataControlServer.h"
#include "TNUserDataHelper.h"
#include "tnnotifycenter.h"
#include "qeventloop.h"
#include "TNHttpApi.h"
#include "qjsondocument.h"
#include "TNHttpDownCloud.h"
#include "CTNChatAPI.h"
#include <time.h>
#include <qnetworkconfigmanager.h>
#ifdef WIN32
#include <windows.h>
#elif __linux__
#endif
#include "TNDbUtil.h"
#include "TNDataCache.h"
#include "TNCHNHelper.h"
#include "CTNDBAPI.h"
#include "TNIMCoreClient.h"
#include "TNConfig.h"
#include "TNPathUtil.h"
#include <QSettings>

TNNoticeUpdater::TNNoticeUpdater(bool isIncreamentUpdate)
: _isIncreamentUpdate(isIncreamentUpdate), _hasStartedUpdating(false), _needEmitCompanyFinished(false), _outTimer(NULL),
_latestUpdateCompanyTime(QDateTime::currentDateTime()), _isChangedOfCompanyInfo(false), _netWorkManager(NULL)
{
    _userDataHelper = TNUserDataHelper::GetInstance();
	connect(_userDataHelper, SIGNAL(GetFeedFinished(int, QList<UINotifyData>)), this, SLOT(OnFinishLoadSlots(int, QList<UINotifyData>)));
    connect(_userDataHelper, SIGNAL(addNewFeedGetApi(TNHttpObtainFeedList *)), this, SLOT(onNewFeedGetApi(TNHttpObtainFeedList *)));
	connect(this, SIGNAL(UpdateRefreshUI(int, QString)), this, SLOT(OnUpdateRefreshUI(int, QString)));
	connect(this, SIGNAL(StartUpdateDb()), this, SLOT(StartUpdateThread()));
	connect(this, SIGNAL(StartUpdateCompany()), this, SLOT(StartUpdateCompanySlot()));
	connect(this, SIGNAL(companyUpdateFinished()), this, SLOT(companyUpdateFinishedSlot()));
	connect(this, SIGNAL(startUpdateReMark(const QString&, const QString &)), this, SLOT(startUpdateReMarkSlot(const QString&, const QString &)));
	//connect(this, SIGNAL(AllUpdateFinished()), TNDataCache::GetInstance(), SLOT(updateAllCacheSlot()));
	_netWorkManager = new QNetworkAccessManager(this);
	QNetworkConfigurationManager manager;
	_netWorkManager->setConfiguration(manager.defaultConfiguration());
	_netWorkManager->setNetworkAccessible(QNetworkAccessManager::Accessible);
}


TNNoticeUpdater::~TNNoticeUpdater()
{
	if (_outTimer)
	{
		_outTimer->stop();
		delete _outTimer;
		_outTimer = NULL;
	}
	if (_netWorkManager)
		_netWorkManager->disconnect();
}
void TNNoticeUpdater::appendUINotifyData(QString feedId,QString belongId, UIOperateType operateType, QList<UINotifyData> &dataList)
{
	foreach(UINotifyData notify, dataList)
	{
		if (notify.belongId == belongId &&notify.feedId == feedId && notify.operateType == operateType)
		{
			return;
		}
	}
	UINotifyData data;
	data.feedId = feedId;
	data.belongId = belongId;
	data.operateType = operateType;
	dataList.append(data);
}
void TNNoticeUpdater::updateGroupChat()
{
	qInfo() << "[IMCORE][TNNoticeUpdater]updateGroupChat start  ";
    if (_httpObtainGroupChatsByUserId.get() == NULL)
    {
		_httpObtainGroupChatsByUserId = std::make_shared<TNHttpObtainGroupChatsByUserId>();
        monitorHttpApi(_httpObtainGroupChatsByUserId.get());
    }
    QString versionChat = "0";
    if (_isIncreamentUpdate)
    {
        versionChat = TNUserVersionInfo::GetInstance()->GetUpdateVersion(UPDATE_TYPE_GroupChat);
    }
	_httpObtainGroupChatsByUserId->GetJson([&](bool success, QJsonObject jsonObject)
	{
		if (success)
		{
			QList<TableBasePtr> inGroupInfoList;
			QList<QString> outGroupInfoList;
			QList<UINotifyData> notifyOutData;
			QList<UINotifyData> notifyInData;
			qInfo() << "[IMCORE][TNNoticeUpdater]updateGroupChat _httpObtainGroupChatsByUserId :  " << QString(QJsonDocument(jsonObject).toJson());
			QJsonArray groupChatArray = jsonObject.value("data").toObject().value("groupChatList").toArray();
			for (int i = 0; i < groupChatArray.size(); i++)
			{
				st_GroupInfoPtr stGroupInfo = std::make_shared<st_GroupInfo>();
                QString groupId = groupChatArray.at(i).toObject().value("topic").toString();
				QString groupChatName = groupChatArray.at(i).toObject().value("groupChatName").toString();
				QString myFeedId = groupChatArray.at(i).toObject().value("myFeedId").toString();
				stGroupInfo->SetMyFeedId(myFeedId);
				int status = groupChatArray.at(i).toObject().value("status").toInt();
				if (status)
				{
					QString groupNamePY = TNCHNHelper::GetPinyins(groupChatName);
					QString groupChatHeadImage = groupChatArray.at(i).toObject().value("groupChatHeadImage").toString();
					QString creatorFeedId = groupChatArray.at(i).toObject().value("creatorFeedId").toString();
					QString topic = groupChatArray.at(i).toObject().value("topic").toString();
					int currNum = groupChatArray.at(i).toObject().value("currNum").toInt();
					int maxNum = groupChatArray.at(i).toObject().value("maxNum").toInt();
					int disturbStatus = groupChatArray.at(i).toObject().value("disturbStatus").toInt();
					int status = groupChatArray.at(i).toObject().value("status").toInt();
					updateGroupChatMember(groupId);
					stGroupInfo->SetCreatorFeedId(creatorFeedId);
					stGroupInfo->SetCurrNum(currNum);
					stGroupInfo->SetDisturbStatus(disturbStatus);
					stGroupInfo->SetGroupId(groupId);
					stGroupInfo->SetHeaderImage(groupChatHeadImage);
					stGroupInfo->SetMaxNum(maxNum);
					stGroupInfo->SetName(groupChatName);
					stGroupInfo->SetTopic(topic);
					stGroupInfo->SetNamePinyin(groupNamePY);
					inGroupInfoList.append(std::dynamic_pointer_cast<TableBase>(stGroupInfo));
					toonim::getChatDB()->updateSessionTitleAndImage(groupId.toUtf8().data(), groupChatName.toUtf8().data(), NULL);
					appendUINotifyData(groupId, stGroupInfo->GetMyFeedId(), UI_OPERATE_ADD, notifyInData);
					qInfo() << "[IMCORE][TNNoticeUpdater]updateGroupChat _httpObtainGroupChatsByUserId add group:  " << groupId;
				}
				else
				{
					outGroupInfoList.append(groupId);
					appendUINotifyData(groupId, stGroupInfo->GetMyFeedId(), UI_OPERATE_DEL, notifyOutData);
					qInfo() << "[IMCORE][TNNoticeUpdater]updateGroupChat _httpObtainGroupChatsByUserId delete group:  " << groupId;
				}
			}
			if (inGroupInfoList.size() > 0)
			{
				qInfo() << "[IMCORE][TNNoticeUpdater]updateGroupChat _httpObtainGroupChatsByUserId insert groupinfo:  " << inGroupInfoList.size();
				TNDataControlServer::GetInstance()->InsertDatas(inGroupInfoList, INSERT_GROUPINFO, DBTYPE_USER);
				if (notifyInData.size() > 0 && _isIncreamentUpdate)
				{
					qInfo() << "[IMCORE][TNNoticeUpdater]updateGroupChat _httpObtainGroupChatsByUserId add(update) groupinfo,postNotifyRefresh RefreshTypeUI_GroupChat:  " << notifyInData.size();
					TNNotifyCenter::instance()->postNotifyRefresh(RefreshTypeUI_GroupChat, notifyInData);
				}
			}
			if (outGroupInfoList.size()> 0)
			{
				// 删除并退出群聊
				qInfo() << "[IMCORE][TNNoticeUpdater]updateGroupChat _httpObtainGroupChatsByUserId delete groupinfo:  " << outGroupInfoList.size();
				foreach(const QString &sessionId, outGroupInfoList) // 实际上只会有一个
				{
					TNDbUtil::operateDBWhenExitGroupChat(sessionId);
					TNIMCoreClient::GetIMClient()->GetDBChat()->deleteSession(sessionId.toUtf8().data());
					//请勿reset version
					//TNUserVersionInfo::GetInstance()->ResetUpdateVersion(UPDATE_TYPE_GroupChat);
                    //gcc error:
                    QString qs_sessionId = sessionId;
                    TNUserVersionInfo::GetInstance()->ResetUpdateVersion(qs_sessionId);

					TNNotifyCenter::instance()->postNotifyRemoveSession(sessionId);
				}
				if (notifyOutData.size() > 0 && _isIncreamentUpdate)
				{
					qInfo() << "[IMCORE][TNNoticeUpdater]updateGroupChat _httpObtainGroupChatsByUserId delete groupinfo,postNotifyRefresh RefreshTypeUI_GroupChat:  " << notifyOutData.size();
					TNNotifyCenter::instance()->postNotifyRefresh(RefreshTypeUI_GroupChat, notifyOutData);
				}
			}
			TNUserVersionInfo::GetInstance()->SetUpdateVersion(UPDATE_TYPE_GroupChat, jsonObject);
			qInfo() << "[IMCORE][TNNoticeUpdater]updateGroupChat end  ";
		}
	}, _userDataHelper->_pluginParam, versionChat);
}
void TNNoticeUpdater::updateNewFriend()
{
	qInfo() << "[IMCORE][TNNoticeUpdater]updateNewFriend start  ";
	if (_httpGetUnConfirmFriendFeed.get() == NULL)
	{
		_httpGetUnConfirmFriendFeed = std::make_shared<TNHttpGetUnConfirmFriendFeed>();
		monitorHttpApi(_httpGetUnConfirmFriendFeed.get());
	}
	QString versionNewFriend = "0";
	if (_isIncreamentUpdate)
	{
		versionNewFriend = TNUserVersionInfo::GetInstance()->GetUpdateVersion(UPDAET_TYPE_NEWFRIEND);
	}
	_httpGetUnConfirmFriendFeed->GetJson([&](bool success, QJsonObject jsonObject)
	{
		if (success)
		{
			QStringList strFeedIDs;
			qInfo() << "[IMCORE][TNNoticeUpdater]updateNewFriend _httpGetUnConfirmFriendFeed :  " << QString(QJsonDocument(jsonObject).toJson());
			QJsonArray friendArray = jsonObject.value("data").toObject().value("contactList").toArray();
			for (int i = 0; i < friendArray.size(); i++)
			{
				st_NewFriendPtr stFriendInfo = std::make_shared<st_NewFriend>();
				QString myFeedId =   friendArray.at(i).toObject().value("myFeedId").toString();
				QString feedId = friendArray.at(i).toObject().value("feedId").toString();
				QString feedBelong = feedId + "_" + myFeedId;
				int status = friendArray.at(i).toObject().value("status").toInt();
				//status(integer) : 状态， 0 : 删除; 1:好友; 2:待确认
				if (status)
				{
					QString addComment = friendArray.at(i).toObject().value("addComment").toString();
					QString mobile = friendArray.at(i).toObject().value("mobile").toString();
					QString applyTime = QString("%1").arg(static_cast<qlonglong>(friendArray.at(i).toObject().value("applyTime").toDouble()));
					QString expireTime = QString("%1").arg(static_cast<qlonglong>(friendArray.at(i).toObject().value("expireTime").toDouble()));
					QString  fromWhere = QString("%1").arg(friendArray.at(i).toObject().value("fromWhere").toInt());
					stFriendInfo->setApplyTime(applyTime);
					stFriendInfo->setExpireTime(expireTime);
					stFriendInfo->setAddComment(addComment);
					stFriendInfo->setMobilePhone(mobile);
					stFriendInfo->setFromWhere(fromWhere);
					stFriendInfo->setFeedID(feedId);
					stFriendInfo->setMyFeedID(myFeedId);
					stFriendInfo->setIsRead("1");
					stFriendInfo->setFeedBelong(feedBelong);
					stFriendInfo->setStatus(QString("%1").arg(status));
					strFeedIDs.append(feedId);
					TNDataControlServer::GetInstance()->InsertDatas(stFriendInfo, DBTYPE_USER);
					qInfo() << "[IMCORE][TNNoticeUpdater]updateNewFriend _httpGetUnConfirmFriendFeed add request:  " << feedBelong;
				}
				else
				{
					TNDataControlServer::GetInstance()->DeleteFromTableNameByField("NewFriend", "feed_belong", feedBelong, DBTYPE_USER);
					qInfo() << "[IMCORE][TNNoticeUpdater]updateNewFriend _httpGetUnConfirmFriendFeed delete request:  " << feedBelong;
				}
			}
			if (strFeedIDs.size() > 0)
			{
				QList<UINotifyData> notifyData;
				_userDataHelper->LoadFeeds(strFeedIDs, notifyData, RefreshTypeUI_NoFresh);
			}
			TNUserVersionInfo::GetInstance()->SetUpdateVersion(UPDAET_TYPE_NEWFRIEND, jsonObject);
            QList<UINotifyData> notifyDatas;
            TNNotifyCenter::instance()->postNotifyRefresh(RefreshTypeUI_Newfriend, notifyDatas);
			qInfo() << "[IMCORE][TNNoticeUpdater]updateNewFriend end  ";
		}
	}, _userDataHelper->_pluginParam, versionNewFriend);
}
QString TNNoticeUpdater::GetBelongId(const QString &feedId)
{
	/*
	Need get belong ID
	*/
	QString belongId;
	QList<TNStructGroupChat> list;
	TNDataCache::GetInstance()->GetGroupChatCache(list, AVATAR_ALL_FEED);
	for (TNStructGroupChat groupChat : list)
	{
		if (groupChat.m_groupChatFeed != nullptr && groupChat.m_groupChatFeed->GetGroupId() == feedId)
		{
			belongId = groupChat.m_groupChatFeed->GetMyFeedId();
			break;
		}
	}
	return belongId;
}
void TNNoticeUpdater::updateGroupChatMember(QString groupId)
{
	qInfo() << "[IMCORE][TNNoticeUpdater]updateGroupChatMember start  ";
    if (_httpObtainGroupChatMembersByGroupChatId.get() == NULL)
    {
		_httpObtainGroupChatMembersByGroupChatId = std::make_shared<TNHttpObtainGroupChatMembersByGroupChatId>();
        monitorHttpApi(_httpObtainGroupChatMembersByGroupChatId.get());
    }
	QString groupChatId = groupId;
	if (groupId.startsWith("gc_"))
		groupChatId = groupId.mid(3);
	QString	groupIdType = "gc_" + groupChatId;
    QString groupMemberVersion = "0";
    if (_isIncreamentUpdate)
    {
        groupMemberVersion = TNUserVersionInfo::GetInstance()->GetUpdateVersion(groupIdType);
    }
    _httpObtainGroupChatMembersByGroupChatId->GetJson([&](bool success, QString retGroupChatId, QJsonObject jsonObject)
	{
		if (success)
		{
            if (!retGroupChatId.startsWith("gc_"))
                retGroupChatId = QString("gc_")+ retGroupChatId;
			QStringList strINFeeds,strOutFeeds;
			QList<TableBasePtr> inGroupMemberList;
			QList<QVector<QString>> outGroupMemberList;
			QMap<QString, QJsonObject> groupChatVersionMap;
			qInfo() << "[IMCORE][TNNoticeUpdater]updateGroupChatMember _httpObtainGroupChatMembersByGroupChatId :  " << QString(QJsonDocument(jsonObject).toJson());
			QJsonArray groupChatMembersArray = jsonObject.value("data").toObject().value("memberList").toArray();
			for (int m = 0; m < groupChatMembersArray.size(); m++)
			{
				QString feedId = groupChatMembersArray.at(m).toObject().value("feedId").toString();
				QString userId = QString("%1").arg(groupChatMembersArray.at(m).toObject().value("userId").toInt());
				int status = groupChatMembersArray.at(m).toObject().value("status").toInt();
				QString disturbStatus = QString("%1").arg(groupChatMembersArray.at(m).toObject().value("disturbStatus").toInt());
				QString permissionType = QString("%1").arg(groupChatMembersArray.at(m).toObject().value("permissionType").toInt());
				quint64 timestamp = groupChatMembersArray.at(m).toObject().value("timestamp").toDouble();

                st_GroupMemberPtr stGroupMember = std::make_shared<st_GroupMember>();
                stGroupMember->SetGroupId(retGroupChatId);
				stGroupMember->SetFeedId(feedId);
				stGroupMember->SetStatus(status);
				stGroupMember->SetTimestamp(timestamp);
				stGroupMember->SetPermissionType(permissionType);
				//2018.2.1 接口3.8需求， status 22作为回收名片状态标志，也会同步
				if (status == 1)
				{
					strINFeeds.append(feedId);
					inGroupMemberList.append(std::dynamic_pointer_cast<TableBase>(stGroupMember));
					qInfo() << "[IMCORE][TNNoticeUpdater]updateGroupChatMember _httpObtainGroupChatMembersByGroupChatId  add member: retGroupChatId=" << retGroupChatId << " feedId=" << feedId;
				}
				else
				{
					QVector<QString> deleteTable;
					deleteTable.append("groupId");
                    deleteTable.append(retGroupChatId);
					deleteTable.append("feedId");
					deleteTable.append(feedId);
					outGroupMemberList.append(deleteTable);
					strOutFeeds.append(feedId);
					qInfo() << "[IMCORE][TNNoticeUpdater]updateGroupChatMember _httpObtainGroupChatMembersByGroupChatId  delete member:  " << feedId;
				}
				if (m == 0)
                    groupChatVersionMap[retGroupChatId] = jsonObject;
			}
			/*
			Need to optimize
			*/
			if (outGroupMemberList.size() > 0)
			{
				qInfo() << "[IMCORE][TNNoticeUpdater]updateGroupChatMember _httpObtainGroupChatMembersByGroupChatId  delete member list: " << outGroupMemberList.size();
				TNDataControlServer::GetInstance()->DeleteFromTableNameByFieldList("GroupMember", outGroupMemberList,DBTYPE_USER);
			}
			if (inGroupMemberList.size() > 0)
			{
				qInfo() << "[IMCORE][TNNoticeUpdater]updateGroupChatMember _httpObtainGroupChatMembersByGroupChatId  add member list: " << inGroupMemberList.size();
				TNDataControlServer::GetInstance()->InsertDatas(inGroupMemberList, INSERT_GROUPMEMBER, DBTYPE_USER);
			}
			if (groupChatVersionMap.size() > 0)
				TNUserVersionInfo::GetInstance()->SetUpdateVersion(groupChatVersionMap);
			if (strINFeeds.size() > 0)
			{
				QList<UINotifyData> notifyData;
                appendUINotifyData(retGroupChatId, GetBelongId(retGroupChatId), UI_OPERATE_ADD, notifyData);
				_userDataHelper->LoadFeeds(strINFeeds, notifyData, RefreshTypeUI_GroupMember, !_hasStartedUpdating);
				qInfo() << "[IMCORE][TNNoticeUpdater]updateGroupChatMember _httpObtainGroupChatMembersByGroupChatId LoadFeeds (add):  " << strINFeeds.size();
			}	
			if (strOutFeeds.size() > 0)
			{
				QList<UINotifyData> notifyData;
				/*
				仅仅是更新成员,不需要执行LoadFeed
				*/
                appendUINotifyData(retGroupChatId, GetBelongId(retGroupChatId), UI_OPERATE_DEL, notifyData);
				TNNotifyCenter::instance()->postNotifyRefresh(RefreshTypeUI_GroupMember, notifyData);
				qInfo() << "[IMCORE][TNNoticeUpdater]updateGroupChatMember _httpObtainGroupChatMembersByGroupChatId postNotifyRefresh RefreshTypeUI_GroupChat:  " << strOutFeeds.size();
			}
			qInfo() << "[IMCORE][TNNoticeUpdater]updateGroupChatMember end ";
		}
	}, _userDataHelper->_pluginParam, groupChatId, groupMemberVersion);
}

void TNNoticeUpdater::updateDisturibData()
{
	if (_httpQuerySwitchInfo == NULL)
	{
		_httpQuerySwitchInfo = std::make_shared<TNHttpQuertySwitchInfo>();
		monitorHttpApi(_httpQuerySwitchInfo.get());
	}
	QString disturbVersion = "0";
	if (_isIncreamentUpdate)
		disturbVersion = TNUserVersionInfo::GetInstance()->GetUpdateVersion(UPDAET_TYPE_DisturbList);
	_httpQuerySwitchInfo->GetJson([&](bool success, QJsonObject jsonObject)
	{
		if (success)
		{
			QJsonArray switchArray = jsonObject.value("data").toObject().value("userSwitches").toArray();
			QList<UINotifyData> switchNotify;
			for (int i = 0; i < switchArray.size(); i++)
			{
				UINotifyData switchItem;
				int status = switchArray.at(i).toObject().value("status").toInt();
				QString feedId = switchArray.at(i).toObject().value("feedId").toString();
				QString passiveFeedId = switchArray.at(i).toObject().value("passiveFeedId").toString();
				QString sessionId = TNIMCoreClient::GetIMClient()->GetSessionId(feedId, passiveFeedId, MSG_BIZ_SINGLECHAT);
				switchItem.feedId = sessionId;
				if (status)
				{
					st_BlackListPtr stBlackInfo = std::make_shared<st_BlackList>();
					stBlackInfo->SetFeedId(feedId);
					stBlackInfo->SetPassiveFeedId(passiveFeedId);
					stBlackInfo->SetStatus(status);
					TNDataControlServer::GetInstance()->InsertDatas(stBlackInfo, DBTYPE_USER);
					switchItem.operateType = UI_OPERATE_ADD;
				}
				else
				{
					TNDataControlServer::GetInstance()->DeleteFromTableNameByField("BlackList", "feedId_passiveFeedId", feedId + passiveFeedId, DBTYPE_USER);
					switchItem.operateType = UI_OPERATE_DEL;
				}
				switchNotify.append(switchItem);
			}
			TNUserVersionInfo::GetInstance()->SetUpdateVersion(UPDAET_TYPE_DisturbList, jsonObject);
			TNNotifyCenter::instance()->postNotifyRefresh(RefreshTypeUI_SwitchSingle, switchNotify);
		}

	}, _userDataHelper->_pluginParam, disturbVersion);
}

/*
如果先增加好友，再删除好友。 离线更新时， 收到的数据中有2条： 1增1 减 ， 这个函数就会有问题。 目前只有一条减的 （和服务器确认， 设计如此）。
*/
void TNNoticeUpdater::updateMyFriend()
{
	//好友
	qInfo() << "[IMCORE][TNNoticeUpdater]updateMyFriend start ";
    if (_httpGetContactFriendFeed.get() == NULL)
    {
		_httpGetContactFriendFeed = std::make_shared<TNHttpGetContactFriendFeed>();
        monitorHttpApi(_httpGetContactFriendFeed.get());
    }
    QString friendVersion = "0";
    if (_isIncreamentUpdate)
    {
        friendVersion = TNUserVersionInfo::GetInstance()->GetUpdateVersion(UPDATE_TYPE_MYFRIEND);
    }
	_httpGetContactFriendFeed->GetJson([&](bool success, QJsonObject jsonObject)
	{
		if (success)
		{
			qInfo() << "[IMCORE][TNNoticeUpdater]updateMyFriend _httpGetContactFriendFeed: " << QString(QJsonDocument(jsonObject).toJson());
			QStringList strFeedIDs;
			QStringList strOrgFeedIDs;
			QList<UINotifyData> notifyDelData;
			QList<UINotifyData> notifyAddData;
			QList<TableBasePtr> inJoinList;
			QList<QString> outJoinList;
			QJsonArray feedArray = jsonObject.value("data").toObject().value("contactList").toArray();
			for (int i = 0; i < feedArray.size(); i++)
			{
				int cardStatus = feedArray.at(i).toObject().value("cardStatus").toInt();
				int status = feedArray.at(i).toObject().value("status").toInt();
				QString feedId = feedArray.at(i).toObject().value("feedId").toString();
				QString belongto = feedArray.at(i).toObject().value("myFeedId").toString();
				QString reMark = feedArray.at(i).toObject().value("remarkName").toString();
				QString reMarkPY = feedArray.at(i).toObject().value("remarkNamePinyin").toString();
				QString feedBelong = feedId + "_" + belongto;
				//cardStatus (integer): 名片状态：0删除，1正常；2回收；4禁用 ,
				if (status == 1 && cardStatus == 1)
				{
					st_JoinStuffPtr stJoinStuff = std::make_shared<st_JoinStuff>();
					strFeedIDs.append(feedId);
					stJoinStuff->SetFeedID(feedId);
					stJoinStuff->SetBelongTo(belongto);
					QString strType(FeedTypeContact);
					stJoinStuff->SetFeedType(strType);
					stJoinStuff->SetFeedBelong(feedBelong);
					stJoinStuff->SetReMark(reMark);
					stJoinStuff->SetReMarkPY(reMarkPY);
					inJoinList.append(std::dynamic_pointer_cast<TableBase>(stJoinStuff));
					appendUINotifyData(feedBelong, belongto, UI_OPERATE_ADD, notifyAddData);
					/*
					如果是组织名片需要知道，是否可沟通
					*/
					if (feedId.startsWith("o_"))
						strOrgFeedIDs.append(feedId);
					qInfo() << "[IMCORE][TNNoticeUpdater]updateMyFriend _httpGetContactFriendFeed: " << "insert feed :" << feedId;
				}
				else
				{
					outJoinList.append(feedBelong);
					appendUINotifyData(feedBelong, belongto, UI_OPERATE_DEL, notifyDelData);
					qInfo() << "[IMCORE][TNNoticeUpdater]updateMyFriend _httpGetContactFriendFeed: " << "delete feed :" << feedId;
				}
			}
			/*
			Notice: feed_belong is the primary key .
			*/
			if (outJoinList.size() > 0)
			{
				qInfo() << "[IMCORE][TNNoticeUpdater]updateMyFriend _httpGetContactFriendFeed: " << "delete join list size :" << outJoinList.size();
				TNDataControlServer::GetInstance()->DeleteFromTableNameByField("JoinStuff", "feed_belong", outJoinList, DBTYPE_USER);
			}
			if (notifyDelData.size() > 0 && _isIncreamentUpdate) //会更新 两遍？
			{
				qInfo() << "[IMCORE][TNNoticeUpdater]updateMyFriend _httpGetContactFriendFeed: " << "postNotifyRefresh RefreshTypeUI_Myfriend";
				TNNotifyCenter::instance()->postNotifyRefresh(RefreshTypeUI_Myfriend, notifyDelData);
			}
			if (inJoinList.size() > 0)
			{
				qInfo() << "[IMCORE][TNNoticeUpdater]updateMyFriend _httpGetContactFriendFeed: " << "insert join list size :" << inJoinList.size();
				TNDataControlServer::GetInstance()->InsertDatas(inJoinList, INSERT_FRINED, DBTYPE_USER);
			}
			TNUserVersionInfo::GetInstance()->SetUpdateVersion(UPDATE_TYPE_MYFRIEND, jsonObject);
			if (strFeedIDs.size() > 0)
			{
				qInfo() << "[IMCORE][TNNoticeUpdater]updateMyFriend _httpGetContactFriendFeed: " << "LoadFeeds (insert feed) ,type :RefreshTypeUI_Myfriend : " << strFeedIDs.size();
				_userDataHelper->LoadFeeds(strFeedIDs, notifyAddData, RefreshTypeUI_Myfriend);
			}
			if (strOrgFeedIDs.size() > 0)
			{
				qInfo() << "[IMCORE][TNNoticeUpdater]updateMyFriend _httpGetContactFriendFeed:update org communication,size " << strOrgFeedIDs.size();
				updateOrgCommunicationStatus(strOrgFeedIDs.toSet(),false);
			}
			qInfo() << "[IMCORE][TNNoticeUpdater]updateMyFriend end ";
		}
	}, _userDataHelper->_pluginParam, friendVersion);
}
void TNNoticeUpdater::updateFriendReMarkSingle(QString from, QStringList tos)
{
	qInfo() << "[IMCORE][TNNoticeUpdater]updateFriendReMarkSingle start ";
	if (_httpGetFeedReMark.get() == NULL)
	{
		_httpGetFeedReMark = std::make_shared<TNHttpGetFeedRemark>();
		monitorHttpApi(_httpGetFeedReMark.get());
	}
	_httpGetFeedReMark->GetJson([&](bool success, QJsonObject reMarkJsonObject)
	{
		if (success)
		{
			qInfo() << "[IMCORE][TNNoticeUpdater]updateFriendReMarkSingle _httpGetFeedReMark: " << QString(QJsonDocument(reMarkJsonObject).toJson());
			QString to,remark;
			QString from = reMarkJsonObject.value("data").toObject().value("from").toString();
			QJsonArray feedArray = reMarkJsonObject.value("data").toObject().value("list").toArray();
			for (int i = 0; i < feedArray.size(); i++)
			{
				remark = feedArray.at(i).toObject().value("remark").toString();
				to = feedArray.at(i).toObject().value("to").toString();
				if (!remark.isEmpty() && !from.isEmpty())
				{
					break;
				}
			}
			if (!remark.isEmpty())
			{
				QString feedBelong = from + "_" + to;
				TNDataControlServer::GetInstance()->updateFeedRemark(feedBelong, remark, TNCHNHelper::GetPinyins(remark));
				TNNotifyCenter::instance()->postNotifyReMarkUpdate(from, to, remark,true);
			}
			qInfo() << "[IMCORE][TNNoticeUpdater]updateFriendReMarkSingle update remark :" << remark << " from:" << from;
		}
	}, _userDataHelper->_pluginParam, from, tos); //获取备注
}
//void TNNoticeUpdater::updateFriendReMark()
//{
//	qInfo() << "[IMCORE][TNNoticeUpdater]updateFriendReMark start ";
//	if (_httpGetFeedReMark.get() == NULL)
//	{
//		_httpGetFeedReMark = std::make_shared<TNHttpGetFeedRemark>();
//		monitorHttpApi(_httpGetFeedReMark.get());
//	}
//	if (_httpGetAllFriendFeed.get() == NULL)
//	{
//		_httpGetAllFriendFeed = std::make_shared<TNHttpGetContactFriendFeed>();
//		monitorHttpApi(_httpGetAllFriendFeed.get());
//	}
//	_httpGetAllFriendFeed->GetJson([&](bool success, QJsonObject jsonObject)
//	{
//		if (success)
//		{
//			qInfo() << "[IMCORE][TNNoticeUpdater]updateFriendReMark _httpGetAllFriendFeed: " << QString(QJsonDocument(jsonObject).toJson());
//			QJsonArray feedArray = jsonObject.value("data").toObject().value("contactList").toArray();
//			for (int i = 0; i < feedArray.size(); i++)
//			{
//				int cardStatus = feedArray.at(i).toObject().value("cardStatus").toInt();
//				int status = feedArray.at(i).toObject().value("status").toInt();
//				QString feedId = feedArray.at(i).toObject().value("feedId").toString();
//				QString belongto = feedArray.at(i).toObject().value("myFeedId").toString();
//				//cardStatus (integer): 名片状态：0删除，1正常；2回收；4禁用 ,
//				if (status == 1 && cardStatus == 1)
//				{
//					_httpGetFeedReMark->GetJson([&](bool success, QJsonObject reMarkJsonObject)
//					{
//						if (success)
//						{
//							QMap<QString, QString> reMarkMap;
//							qInfo() << "[IMCORE][TNNoticeUpdater]updateFriendReMark _httpGetFeedReMark: " << QString(QJsonDocument(reMarkJsonObject).toJson());
//							QString to;
//							QString from = reMarkJsonObject.value("data").toObject().value("from").toString();
//							QJsonArray feedArray = reMarkJsonObject.value("data").toObject().value("list").toArray();
//							for (int i = 0; i < feedArray.size(); i++)
//							{
//								QString remark = feedArray.at(i).toObject().value("remark").toString();
//								to = feedArray.at(i).toObject().value("to").toString();
//								if (!remark.isEmpty() && !from.isEmpty())
//									reMarkMap.insert(from, remark);
//							}
//							if (reMarkMap.size()>0)
//								TNDataControlServer::GetInstance()->updateFeedRemark(to, reMarkMap);
//							qInfo() << "[IMCORE][TNNoticeUpdater]update remark size :" << reMarkMap.size() << " from:" << from;
//						}
//					}, _userDataHelper->_pluginParam, feedId, QStringList(belongto)); //获取备注
//				}
//			}
//		}
//	}, _userDataHelper->_pluginParam, "0"); /*全量拉取所有好友*/
//}
void TNNoticeUpdater::updateGroup()
{
	// 自己创建的群组
	qInfo() << "[IMCORE][TNNoticeUpdater]updateGroup start";
	if (_httpGetMyGroup.get() == NULL)
    {
		_httpGetMyGroup = std::make_shared<TNHttpGetMyGroup>();
		monitorHttpApi(_httpGetMyGroup.get());
    }
	QString version = "0";
	if (_isIncreamentUpdate)
	{
		version = TNUserVersionInfo::GetInstance()->GetUpdateVersion(UPDATE_TYPE_GROUP);
	}

	_httpGetMyGroup->GetJson([&](bool success, QJsonObject jsonObject)
	{
		if (success)
		{
			QStringList strFeedIDs;
			QList<TableBasePtr> inMyStuffList;
			QList<TableBasePtr> inJoinStuffList;
			QList<QString> outMyStuffList;
			QList<QString> outJoinStuffList;
			QList<UINotifyData> notifyDelData;
			QList<UINotifyData> notifyAddData;
			qInfo() << "[IMCORE][TNNoticeUpdater]updateGroup _httpGetMyGroup: " << QString(QJsonDocument(jsonObject).toJson());
			QJsonArray myItems = jsonObject.value("data").toObject().value("myGroupList").toArray();
			for (int p = 0; p < myItems.size(); p++)
			{
				// 权限类型：1 版主 2 管理员 3 普通成员,
				int permission= myItems.at(p).toObject().value("permissionType").toInt();
				if (permission == 3 || permission == 2) //我加入的
				{
					st_JoinStuffPtr stJoinStuff = std::make_shared<st_JoinStuff>();
					int status = myItems.at(p).toObject().value("status").toInt();
					QString myFeed = myItems.at(p).toObject().value("cardFeedId").toString();
					QString joinGroupFeed = myItems.at(p).toObject().value("groupFeedId").toString();
					QString feedBelong = joinGroupFeed + "_" + myFeed;
					if (status == 1)
					{
						/*
						我将社区转移给别人， 会收到 permission 为3 的通知。客户端需要将在我加入的社区删除 。
						*/
						if (TNDataCache::GetInstance()->getGroupStatusByID(joinGroupFeed) == 1) //原先状态是我的
						{
							outMyStuffList.append(joinGroupFeed);
							appendUINotifyData(joinGroupFeed, myFeed, UI_OPERATE_DEL, notifyDelData);
						}

						QString groupMemberCount = QString("%1").arg(myItems.at(p).toObject().value("groupMemberCount").toInt());
						QString groupPermission = QString("%1").arg(permission);
						strFeedIDs.append(joinGroupFeed);
						stJoinStuff->SetFeedID(joinGroupFeed);
						stJoinStuff->SetBelongTo(myFeed);
						QString strType(FeedTypeGroup);
						stJoinStuff->SetFeedType(strType);
						stJoinStuff->SetFeedBelong(feedBelong);
						stJoinStuff->SetExt1(groupMemberCount);
						stJoinStuff->SetExt2(groupPermission);
						appendUINotifyData(joinGroupFeed, myFeed, UI_OPERATE_ADD, notifyAddData);
						inJoinStuffList.append(std::dynamic_pointer_cast<TableBase>(stJoinStuff));
						qInfo() << "[IMCORE][TNNoticeUpdater]updateGroup _httpGetMyGroup: " << "insert join group :" << joinGroupFeed << " member: " << groupMemberCount;
					}
					else if (status == 0 || status == 11)
					{
						appendUINotifyData(joinGroupFeed, myFeed, UI_OPERATE_DEL, notifyDelData);
						outJoinStuffList.append(feedBelong);
						qInfo() << "[IMCORE][TNNoticeUpdater]updateGroup _httpGetMyGroup: " << "delete join group :" << outJoinStuffList.size();
					}
				}
				else  //我创建的
				{
					st_MyStuffPtr myStuff = std::make_shared<st_MyStuff>();
					int status = myItems.at(p).toObject().value("status").toInt();
					QString myFeed = myItems.at(p).toObject().value("cardFeedId").toString();
					myStuff->SetBelongTo(myFeed);

					/*
					状态 status (integer, optional): 状态: 0 删除 1 正常 2 待审核 10 被举报 11 群组解散 ,
					*/
					QString myGroupFeed = myItems.at(p).toObject().value("groupFeedId").toString();
					if (status == 1)
					{
						/*
						别人将社区转移给我时， 会收到 permission 为1 的通知。客户端需要将在我加入的社区删除 。
						*/
						if (TNDataCache::GetInstance()->getGroupStatusByID(myGroupFeed) == 2 ||
							TNDataCache::GetInstance()->getGroupStatusByID(myGroupFeed) == 3) 
						{
							QString feedBelongTemp = myGroupFeed + "_" + myFeed;
							appendUINotifyData(myGroupFeed, myFeed, UI_OPERATE_DEL, notifyDelData);
							outJoinStuffList.append(feedBelongTemp);
						}

						QString groupMemberCount = QString("%1").arg(myItems.at(p).toObject().value("groupMemberCount").toInt());
						strFeedIDs.append(myGroupFeed);
						myStuff->SetFeedID(myGroupFeed);
						myStuff->SetFeedType(QString(FeedTypeGroup));
						myStuff->SetExt(groupMemberCount);
						appendUINotifyData(myGroupFeed, myFeed, UI_OPERATE_ADD, notifyAddData);
						inMyStuffList.append(std::dynamic_pointer_cast<TableBase>(myStuff));
						qInfo() << "[IMCORE][TNNoticeUpdater]updateGroup _httpGetMyGroup: " << "insert my group :" << myGroupFeed << " member: " << groupMemberCount;
					}
					else if (status == 0 || status == 11)
					{
						outMyStuffList.append(myGroupFeed);
						appendUINotifyData(myGroupFeed, myStuff->GetBelongTo(), UI_OPERATE_DEL, notifyDelData);
						qInfo() << "[IMCORE][TNNoticeUpdater]updateGroup _httpGetMyGroup: " << "delete my group :" << myGroupFeed;
					}
				}
			}
			if (inMyStuffList.size() > 0)
			{
				TNDataControlServer::GetInstance()->InsertDatas(inMyStuffList, INSERT_MYGROUP, DBTYPE_USER);
				qInfo() << "[IMCORE][TNNoticeUpdater]updateGroup _httpGetMyGroup:  " << "insert group list :" << inMyStuffList.size();
			}
			if (outMyStuffList.size() > 0)
			{
				TNDataControlServer::GetInstance()->DeleteFromTableNameByField("MyStuff", "feedId", outMyStuffList, DBTYPE_USER);
				if (_isIncreamentUpdate)
				{
					TNNotifyCenter::instance()->postNotifyRefresh(RefreshTypeUI_Group, notifyDelData);
				}
				qInfo() << "[IMCORE][TNNoticeUpdater]updateGroup _httpGetMyGroup:  " << "delete group list :" << outMyStuffList.size();
			}
			if (inJoinStuffList.size() > 0)
			{
				qInfo() << "[IMCORE][TNNoticeUpdater]updateGroup _httpGetMyGroup:  " << "insert group list :" << inJoinStuffList.size();
				TNDataControlServer::GetInstance()->InsertDatas(inJoinStuffList, INSERT_GROUP, DBTYPE_USER);
			}
			if (outJoinStuffList.size() > 0)
			{
				TNDataControlServer::GetInstance()->DeleteFromTableNameByField("JoinStuff", "feed_belong", outJoinStuffList, DBTYPE_USER);
				if (_isIncreamentUpdate)
				{
					TNNotifyCenter::instance()->postNotifyRefresh(RefreshTypeUI_Group, notifyDelData);
				}
				qInfo() << "[IMCORE][TNNoticeUpdater]updateGroup _httpGetMyGroup:  " << "delete group list :" << outJoinStuffList.size();
			}
			TNUserVersionInfo::GetInstance()->SetUpdateVersion(UPDATE_TYPE_GROUP, jsonObject);
			if (strFeedIDs.size() > 0)
			{
				qInfo() << "[IMCORE][TNNoticeUpdater]updateGroup _httpGetMyGroup LoadFeeds,type:  " << RefreshTypeUI_Group;
				_userDataHelper->LoadFeeds(strFeedIDs, notifyAddData, RefreshTypeUI_Group);
			}
		}
	}, _userDataHelper->_pluginParam, version,""); //feed 为空
}

void TNNoticeUpdater::updateGroupMember(QString groupId)
{
	qInfo() << "[IMCORE][TNNoticeUpdater]updateGroupMember start ";
    if (_httpObtainGroupMembersByGroupId.get() == NULL)
    {
        _httpObtainGroupMembersByGroupId = std::make_shared<TNHttpObtainGroupMembersByGroupId>();
        monitorHttpApi(_httpObtainGroupMembersByGroupId.get());
    }
    QString groupMemberVersion = "0";
    if (_isIncreamentUpdate)
    {
        groupMemberVersion = TNUserVersionInfo::GetInstance()->GetUpdateVersion(groupId);
    }
    _httpObtainGroupMembersByGroupId->GetJson([&](bool success, QString retFeedId, QJsonObject jsonObject)
    {
        if (success)
        {
            QStringList strFeeds;
            QList<TableBasePtr> inGroupMemberList;
            QList<QVector<QString>> outGroupMemberList;
            QMap<QString, QJsonObject> groupVersionMap;
            QString data = QString(QJsonDocument(jsonObject).toJson());
            QJsonArray groupChatArray = jsonObject.value("data").toObject().value("list").toArray();
            for (int m = 0; m < groupChatArray.size(); m++)
            {
                QString feedId = groupChatArray.at(m).toObject().value("cardFeedId").toString();
                QString userId = QString("%1").arg(groupChatArray.at(m).toObject().value("userId").toInt());
                int status = groupChatArray.at(m).toObject().value("status").toInt();
                QString permissionType = QString("%1").arg(groupChatArray.at(m).toObject().value("permissionType").toInt());
                QString groupId = QString("%1").arg(static_cast<qlonglong>(groupChatArray.at(m).toObject().value("groupId").toDouble()));
                st_GroupMemberPtr stGroupMember = std::make_shared<st_GroupMember>();
                groupId = "g_" + groupId;
                stGroupMember->SetGroupId(groupId);
                stGroupMember->SetFeedId(feedId);
                stGroupMember->SetStatus(status);
                strFeeds.append(feedId);
                if (status)
                    inGroupMemberList.append(std::dynamic_pointer_cast<TableBase>(stGroupMember));
                else
                {
                    QVector<QString> deleteTable;
                    deleteTable.append("groupId");
                    deleteTable.append(groupId);
                    deleteTable.append("feedId");
                    deleteTable.append(feedId);
                    outGroupMemberList.append(deleteTable);
                }
                if (m == 0)
                    groupVersionMap[groupId] = jsonObject;
            }
            if (inGroupMemberList.size() > 0)
				TNDataControlServer::GetInstance()->InsertDatas(inGroupMemberList, INSERT_GROUPMEMBER, DBTYPE_USER);
            if (groupVersionMap.size() > 0)
                TNUserVersionInfo::GetInstance()->SetUpdateVersion(groupVersionMap);
            if (outGroupMemberList.size() > 0)
				TNDataControlServer::GetInstance()->DeleteFromTableNameByFieldList("GroupMember", outGroupMemberList, DBTYPE_USER);
            if (strFeeds.size() > 0)
            {
                QList<UINotifyData> notifyData;
                _userDataHelper->LoadFeeds(strFeeds, notifyData, -100);
            }
			qInfo() << "[IMCORE][TNNoticeUpdater]updateGroupMember end ";
        }
    }, _userDataHelper->_pluginParam, groupId, groupMemberVersion);
}

void TNNoticeUpdater::updateMyCard()
{
    if (_httpGetListRelationItem.get() == NULL)
    {
		_httpGetListRelationItem = std::make_shared<TNHttpGetListRelationItem>();
        monitorHttpApi(_httpGetListRelationItem.get());
    }
    QString myCardVersion = "0";

	//2018.1.25 服务器取消增量
	//2018.3.9  服务器变回增量
    if (_isIncreamentUpdate)
    {
        myCardVersion = TNUserVersionInfo::GetInstance()->GetUpdateVersion(UPDATE_TYPE_MYCARD);
    }

	qInfo() << "myCardVersion :"<<myCardVersion;
	_httpGetListRelationItem->GetJson([&](bool success, QJsonObject jsonObject)
	{
		if (success)
		{
			QStringList strFeedIDs;
			QList<UINotifyData> notifyDelData;
			QList<UINotifyData> notifyAddData;
			QList<TableBasePtr> inMyStuffList;
			QList<QString> outMyStuffList;
			qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCard _httpGetListRelationItem: " << QString(QJsonDocument(jsonObject).toJson());
			QJsonArray myItems = jsonObject.value("data").toObject().value("relationItemList").toArray();
			for (int p = 0; p < myItems.size(); p++)
			{
				//userStatus： //使用状态 0 停用 1 启用 2 转让中
				//status ： 状态  0 删除 1 正常
				int status = myItems.at(p).toObject().value("status").toInt();
				QString myFeed = myItems.at(p).toObject().value("feedId").toString();
				if (status)
				{
					st_MyStuffPtr myStuff = std::make_shared<st_MyStuff>();
					myStuff->SetFeedID(myFeed);
					myStuff->SetFeedType(QString(FeedTypeCard));
					strFeedIDs.append(myFeed);
					inMyStuffList.append(std::dynamic_pointer_cast<TableBase>(myStuff));
					appendUINotifyData(myFeed, myFeed, UI_OPERATE_ADD, notifyAddData);
				}
				else
				{
					outMyStuffList.append(myFeed);
					appendUINotifyData(myFeed, myFeed, UI_OPERATE_DEL, notifyDelData);
				}
			}
			if (inMyStuffList.size()> 0)
				TNDataControlServer::GetInstance()->InsertDatas(inMyStuffList, INSERT_MYSTUFF, DBTYPE_USER);
			if (outMyStuffList.size()> 0)
				TNDataControlServer::GetInstance()->DeleteFromTableNameByField("MyStuff", "feedId", outMyStuffList, DBTYPE_USER);
			
			if (notifyDelData.size() > 0 && _isIncreamentUpdate) //会更新 两遍？
			{
				qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCard _httpGetListRelationItem: " << "postNotifyRefresh RefreshTypeUI_MyCard";
				TNNotifyCenter::instance()->postNotifyRefresh(RefreshTypeUI_MyCard, notifyDelData);
			}

			//更新版本时间戳
			TNUserVersionInfo::GetInstance()->SetUpdateVersion(UPDATE_TYPE_MYCARD, jsonObject);
            if (strFeedIDs.size() > 0)
            {
				_userDataHelper->LoadFeeds(strFeedIDs, notifyAddData, RefreshTypeUI_MyCard);
            }
		}
	}, _userDataHelper->_pluginParam, myCardVersion);
}

void TNNoticeUpdater::updateMyCompany()
{
	qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany start ";
    if (_httpGetListStaffContactByUserId.get() == NULL)
    {
		_httpGetListStaffContactByUserId = std::make_shared<TNHttpGetListStaffContactByUserId>();
        monitorHttpApi(_httpGetListStaffContactByUserId.get());
    }
    if (_httpGetListStaffCard.get() == NULL)
    {
		_httpGetListStaffCard = std::make_shared<TNHttpGetListStaffCard>();
        monitorHttpApi(_httpGetListStaffCard.get());
    }
    if (_httpGetListStaffCardByUserId.get() == NULL)
    {
        _httpGetListStaffCardByUserId = std::make_shared<TNHttpGetListStaffCardByUserId>();
        monitorHttpApi(_httpGetListStaffCardByUserId.get());
    }
	if (_httpGetCompanyInfobyComIdList.get() == NULL)
	{
		_httpGetCompanyInfobyComIdList = std::make_shared<TNHttpGetCompanyInfoByComIdList>();
		monitorHttpApi(_httpGetCompanyInfobyComIdList.get());
	}

	if (_httpGetCompanyFeedIdByComId.get() == NULL)
	{
		_httpGetCompanyFeedIdByComId = std::make_shared<TNHttpGetCompanyFeedIdByComId>();
		monitorHttpApi(_httpGetCompanyFeedIdByComId.get());
	}
	if (_httpGetListOrgCardByFeeds.get() == NULL)
	{
		_httpGetListOrgCardByFeeds = std::make_shared<TNHttpGetListOrgCard>();
		monitorHttpApi(_httpGetListOrgCardByFeeds.get());
	}

	if (_httpGetListOrgCardByUserId.get() == NULL)
	{
		_httpGetListOrgCardByUserId = std::make_shared<TNHttpGetListOrgCardByUserId>();
		monitorHttpApi(_httpGetListOrgCardByUserId.get());
	}

	if (_httpGetListOrgCardByFeedForOrg.get() == NULL)
	{
		_httpGetListOrgCardByFeedForOrg = std::make_shared<TNHttpGetListOrgCard>();
		monitorHttpApi(_httpGetListOrgCardByFeedForOrg.get());
	}

	if (_httpGetListGroupContactByUserId.get() == NULL)
	{
		_httpGetListGroupContactByUserId = std::make_shared<TNHttpGetListGroupContactByUserId>();
		monitorHttpApi(_httpGetListGroupContactByUserId.get());
	}

	if (_httpGetOrgGroupList.get() == NULL)
	{
		_httpGetOrgGroupList = std::make_shared<TNHttpGetOrgGroupList>();
		monitorHttpApi(_httpGetOrgGroupList.get());
	}

    if (_httpApi.get() == NULL)
    {
		_httpApi = std::make_shared<TNHttpApi>();
    }
    QString colleagueVersion = "0";
    if (_isIncreamentUpdate)
    {
        colleagueVersion = TNUserVersionInfo::GetInstance()->GetUpdateVersion(UPDATE_TYPE_Colleague);
    }
	//接口与文档不一致
	_httpGetListStaffContactByUserId->GetJson([&](bool success, QJsonObject jsonStaffContactObject)
	{
		qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany _httpGetListStaffContactByUserId :" << QString(QJsonDocument(jsonStaffContactObject).toJson());
		if (success)
		{
			QStringList strFeedIDs;
			QList<TableBasePtr> inJoinList;
			QList<QString> outJoinList;
			QJsonArray myfeedArray = jsonStaffContactObject.value("data").toObject().value("list").toArray();
			for (int n = 0; n < myfeedArray.size(); n++)
			{
				QString myFeed = myfeedArray.at(n).toObject().value("myFeedId").toString();
				strFeedIDs.append(myFeed);

				QJsonArray stuffFeeds = myfeedArray.at(n).toObject().value("colleagueList").toArray();
				for (int m = 0; m < stuffFeeds.size(); m++)
				{
					_isChangedOfCompanyInfo = true;
					st_JoinStuffPtr stJoinStuff = std::make_shared<st_JoinStuff>();
					int status = stuffFeeds.at(m).toObject().value("useStatus").toInt();
					QString tempFeed = stuffFeeds.at(m).toObject().value("feedId").toString();
					QString feedBelong = tempFeed + "_" + myFeed;
					if (status ==1)
					{
						strFeedIDs.append(tempFeed);
						stJoinStuff->SetFeedID(tempFeed);
						stJoinStuff->SetBelongTo(myFeed);
						QString strFeedType(FeedTypeOrgStaff);
						stJoinStuff->SetFeedType(strFeedType);
						stJoinStuff->SetFeedBelong(feedBelong);
						inJoinList.append(std::dynamic_pointer_cast<TableBase>(stJoinStuff));
					}
					else if (status == 0)
					{
						qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany _httpGetListStaffContactByUserId: delete staff contact: " << feedBelong;
						outJoinList.append(feedBelong);
					}
					//同步将其头像删除
					TNPathUtil::removeAvatarFile(tempFeed);
				}
			}
			if (inJoinList.size()> 0)
				TNDataControlServer::GetInstance()->InsertDatas(inJoinList, INSERT_FRINED, DBTYPE_USER);
			if (strFeedIDs.size() > 0)
			{
                QList<UINotifyData> notifyData;
				_userDataHelper->LoadFeeds(strFeedIDs, notifyData, RefreshTypeUI_NoFresh);
			}
			/*
			Notice: feed_belong is the primary key .
			*/
			if (outJoinList.size() > 0)
			{
				qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany _httpGetListStaffContactByUserId: delete staff contact list: " << outJoinList.size();
				TNDataControlServer::GetInstance()->DeleteFromTableNameByField("JoinStuff", "feed_belong", outJoinList, DBTYPE_USER);
			}
			TNUserVersionInfo::GetInstance()->SetUpdateVersion(UPDATE_TYPE_Colleague, jsonStaffContactObject);
		}
	}, _userDataHelper->_pluginParam, colleagueVersion);

	/*
	All colleague staff， 为了支持组织名称修改， 员工名片全量拉取。 
	*/
	QString StaffCardVersion = "0";
	//if (_isIncreamentUpdate)
	//{
	//	StaffCardVersion = TNUserVersionInfo::GetInstance()->GetUpdateVersion(UPDATE_TYPE_StaffCard);
	//}
	_httpGetListStaffCardByUserId->GetJson([&](bool success, QJsonObject jsonStaffCardObject)
	{
		qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany _httpGetListStaffCardByUserId :" << QString(QJsonDocument(jsonStaffCardObject).toJson());
		if (success)
		{
			QString strFeeds;
			QStringList inStaffFeedIDs;
			QStringList outStaffList;
			QString data = QString(QJsonDocument(jsonStaffCardObject).toJson());
			QJsonArray myStaffCard = jsonStaffCardObject.value("data").toObject().value("list").toArray();
			for (int n = 0; n < myStaffCard.size(); n++)
			{
				_isChangedOfCompanyInfo = true;
				QString myFeed = myStaffCard.at(n).toObject().value("feedId").toString();
				int status = myStaffCard.at(n).toObject().value("useStatus").toInt();
				if (status == 1)
				{
					inStaffFeedIDs.push_back(myFeed);
					strFeeds = ((n == 0) ? myFeed : (strFeeds + "," + myFeed));
				}
				else if (status == 0)
				{
					qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany _httpGetListStaffCardByUserId: delete my staff: " << myFeed;
					outStaffList.append(myFeed);
				}
			}

			if (!strFeeds.isEmpty())
			{
				_httpGetListStaffCard->GetJson([&](bool success, QJsonObject jsonListStaffObject)
				{
					qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany _httpGetListStaffCard :" << QString(QJsonDocument(jsonListStaffObject).toJson());
					if (success)
					{
						QList<TableBasePtr> inMyStuffList;
						QStringList outMyStuffList;
						QStringList outCompanyList;
						QStringList inCompanyList;
						QJsonArray myListStaffArray = jsonListStaffObject.value("data").toArray();
						for (int p = 0; p < myListStaffArray.size(); p++)
						{
							_isChangedOfCompanyInfo = true;
							st_MyStuffPtr myStuff = std::make_shared<st_MyStuff>();
							QString myFeedID = myListStaffArray.at(p).toObject().value("feedId").toString();
							QString strComID = QString("%1").arg(myListStaffArray.at(p).toObject().value("comId").toInt());
							int status = myListStaffArray.at(p).toObject().value("status").toInt();
							if (status == 1)
							{
								myStuff->SetFeedID(myFeedID);
								myStuff->SetFeedType(QString(FeedTypeStaff));
								myStuff->SetExt(strComID);
								/*
								新增加员工名片
								*/
								qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany _httpGetListStaffCard: new staff Card & comany: " << myFeedID << " Com:" + strComID;
								inMyStuffList.append(std::dynamic_pointer_cast<TableBase>(myStuff));
								inCompanyList.append(strComID);
								//查看本地是否存在头像
								TNPathUtil::removeAvatarFile(myFeedID);
							}
							else
							{
								/*
								这里是员工名片详细参数，不应该进来。
								*/
								qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany _httpGetListStaffCard: delete staff Card & comany: " << myFeedID << " Com:" + strComID;
								outMyStuffList.append(myFeedID);
								outCompanyList.append(strComID);
							}
						}
						if (inMyStuffList.size() > 0)
						{
							qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany _httpGetListStaffCard Colleague staff over,total :" << inMyStuffList.size();
							TNDataControlServer::GetInstance()->InsertDatas(inMyStuffList, INSERT_MYSTUFF, DBTYPE_USER);
						}
						if (outMyStuffList.size() > 0)
						{
							qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany _httpGetListStaffCard: delete staff card list: " << outMyStuffList.size();
							TNDataControlServer::GetInstance()->DeleteFromTableNameByField("MyStuff", "feedId", outMyStuffList, DBTYPE_USER);
						}
						if (inCompanyList.size() > 0)
						{
							/*
							先入库公司ID
							*/
							qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany _httpGetListStaffCard New Company add over,total :" << inMyStuffList.size();
							TNDataControlServer::GetInstance()->InsertDatas(inCompanyList, INSERT_COMPANY, DBTYPE_USER);
						}
						if (outCompanyList.size() >0)
						{
							/*
							删除公司信息
							*/
							qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany _httpGetListStaffCard Delete Company over,total :" << inMyStuffList.size();
							TNDataControlServer::GetInstance()->DeleteFromTableNameByField("CompanyInfo", "comId", outCompanyList, DBTYPE_USER);
						}
						/*
						获得公司详情并入库
						*/
						if (inCompanyList.size() > 0)
						{
							_httpGetCompanyInfobyComIdList->GetJson([&](bool success, QJsonObject jsonComInfoListObject)
							{
								qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany _httpGetCompanyInfobyComIdList :" << QString(QJsonDocument(jsonComInfoListObject).toJson());
								if (success)
								{
									QMap<QString, QString> companyNameList;
									QJsonArray myDataArray = jsonComInfoListObject.value("data").toObject().value("companyList").toArray();
									for (int p = 0; p < myDataArray.size(); p++)
									{
										_isChangedOfCompanyInfo = true;
										QString comID = QString("%1").arg(myDataArray.at(p).toObject().value("comId").toInt());
										QString comName = myDataArray.at(p).toObject().value("comName").toString();
										companyNameList.insert(comID, comName);
										qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany _httpGetCompanyInfobyComIdList Company Info : " << comID << "-" + comName;;
									}
									if (companyNameList.size() >0)
									{
										/*
										更新公司名称
										*/
										qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany _httpGetCompanyInfobyComIdList Update Company Name :" << companyNameList.size();
										TNDataControlServer::GetInstance()->updateSetValueByValueMap("CompanyInfo","comName","comId",companyNameList,DBTYPE_USER);
									}
								}
							},_userDataHelper->_pluginParam, inCompanyList.toSet());

							/*
							更新公司 Feed
							*/
							for (QString comId:inCompanyList)
							{
                                _httpGetCompanyFeedIdByComId->GetJson([&](bool success, QString, QJsonObject jsonComFeedObject)
								{
									qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany _httpGetCompanyFeedIdByComId :" << QString(QJsonDocument(jsonComFeedObject).toJson());
									if (success)
									{
										/*
										实际只有一个
										*/
										QStringList feeds;
										QString comFeedId = jsonComFeedObject.value("data").toArray().at(0).toObject().value("feedId").toString();
										qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany _httpGetCompanyFeedIdByComId company feed: " << comFeedId;
										feeds.append(comFeedId);
                                        _httpGetListOrgCardByFeeds->GetJson([&](bool success, QString, QJsonObject jsonComFeedCardObject)
										{
											if (success)
											{
												QList<TableBasePtr> inOrgCardStaffCompanyList;
												QStringList outOrgCardStaffCompanyList;
												qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany _httpGetListOrgCardByFeedForOrg :" << QString(QJsonDocument(jsonComFeedCardObject).toJson());
												QJsonArray myListOrgArray = jsonComFeedCardObject.value("data").toArray();
												for (int p = 0; p < myListOrgArray.size(); p++)
												{
													_isChangedOfCompanyInfo = true;
													st_CompanyInfoPtr company = std::make_shared<st_CompanyInfo>();
													company->setComId(QString("%1").arg(jsonComFeedCardObject.value("data").toArray().at(p).toObject().value("comId").toInt()));
													company->setComFeedId(jsonComFeedCardObject.value("data").toArray().at(p).toObject().value("feedId").toString());
													company->setComAddress(jsonComFeedCardObject.value("data").toArray().at(p).toObject().value("address").toString());
													company->setCardNo(jsonComFeedCardObject.value("data").toArray().at(p).toObject().value("cardNo").toString());
                                                    qint64 tempCreateTime = jsonComFeedCardObject.value("data").toArray().at(p).toObject().value("createTime").toDouble();
													company->setCreateTime(QString("%1").arg(tempCreateTime));
													company->setCreatorId(QString("%1").arg(jsonComFeedCardObject.value("data").toArray().at(p).toObject().value("creatorId").toInt()));
													company->setDisplayName(jsonComFeedCardObject.value("data").toArray().at(p).toObject().value("displayName").toString());
													company->setDisplayNamePinyin(jsonComFeedCardObject.value("data").toArray().at(p).toObject().value("displayNamePinyin").toString());
													company->setExchangeMode(QString("%1").arg(jsonComFeedCardObject.value("data").toArray().at(p).toObject().value("exchangeMode").toInt()));
													company->setIndustry(jsonComFeedCardObject.value("data").toArray().at(p).toObject().value("industry").toString());
													company->setIntroduction(jsonComFeedCardObject.value("data").toArray().at(p).toObject().value("introduction").toString());
													company->setLogo(jsonComFeedCardObject.value("data").toArray().at(p).toObject().value("logo").toString());
                                                    qint64 tempUpdateTime = jsonComFeedCardObject.value("data").toArray().at(p).toObject().value("updateTime").toDouble();
													company->setUpdateTime(QString("%1").arg(tempUpdateTime));
													company->setOwnerId(QString("%1").arg(jsonComFeedCardObject.value("data").toArray().at(p).toObject().value("ownerId").toInt()));
													company->setOrgCommunication(jsonComFeedCardObject.value("data").toArray().at(p).toObject().value("communicateStatus").toString());
													QJsonArray subItems = jsonComFeedCardObject.value("data").toArray().at(p).toObject().value("fieldList").toArray();
													for (int i = 0; i < subItems.size(); i++)
													{
														QString fieldId = QString("%1").arg(subItems.at(i).toObject().value("fieldId").toInt());
														if (fieldId == COMPANYINFO_FIELDID_EMAIL)
														{
															company->setEmail(subItems.at(i).toObject().value("fieldValue").toString());
														}
														else if (fieldId == COMPANYINFO_FIELDID_TEL)
														{
															company->setPhone(subItems.at(i).toObject().value("fieldValue").toString());
														}
													}
													int status = jsonComFeedCardObject.value("data").toArray().at(p).toObject().value("useStatus").toInt();
													if (status)
													{
														qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany _httpGetListOrgCardByFeedForOrg: update company info";
														inOrgCardStaffCompanyList.append(std::dynamic_pointer_cast<TableBase>(company));
													}
													else
													{
														qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany _httpGetListOrgCardByFeedForOrg: delete company info: " << company->getComId();
														/*
														删除一个组织时，组织名片头像删除
														*/
														TNPathUtil::removeAvatarFile(company->getComFeedId());
														outOrgCardStaffCompanyList.append(company->getComId());
													}
												}
												if (inOrgCardStaffCompanyList.size() > 0)
												{
													qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany _httpGetListOrgCardByFeedForOrg: update company info list :" << inOrgCardStaffCompanyList.size();
													TNDataControlServer::GetInstance()->InsertDatas(inOrgCardStaffCompanyList, INSERT_COMPANY, DBTYPE_USER);
												}
												if (outOrgCardStaffCompanyList.size()>0)
												{
													qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany _httpGetListOrgCardByFeedForOrg: delete company info list: " << outOrgCardStaffCompanyList.size();
													TNDataControlServer::GetInstance()->DeleteFromTableNameByField("CompanyInfo", "comId", outOrgCardStaffCompanyList, DBTYPE_USER);
												}
											}
                                        }, _userDataHelper->_pluginParam, QString(),feeds);
									}
                                }, _userDataHelper->_pluginParam, QString(), comId);
							}
						}
					}
				}, _userDataHelper->_pluginParam, strFeeds);
			}
			if (outStaffList.size() > 0)
			{
				/*
				目前名片收回，仅仅发此消息
				*/
				//1. 通过名片删掉所有的部门 ColleagueGroup
				//2. 通过名片Groupid删除所有的 ColleagueReltaion
				//3. 删除名片
				//4. 删除名片对应的好友
				//5. 删除头像
				qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany _httpGetListStaffCardByUserId: delete my staff list: " << outStaffList.size();
				_userDataHelper->ProcessDeleteStaff(outStaffList);
			}
			TNUserVersionInfo::GetInstance()->SetUpdateVersion(UPDATE_TYPE_StaffCard, jsonStaffCardObject);
			if (!inStaffFeedIDs.isEmpty())
			{
				QList<UINotifyData> notifyData;
				_userDataHelper->LoadFeeds(inStaffFeedIDs, notifyData, RefreshTypeUI_NoFresh);
			}
		}
	}, _userDataHelper->_pluginParam, StaffCardVersion);

    QString orgCardUpdateVersion = "0";
    if (_isIncreamentUpdate)
    {
        orgCardUpdateVersion = TNUserVersionInfo::GetInstance()->GetUpdateVersion(UPDATE_TYPE_OrgCard);
    }
	/*
	注意，此API 文档与实际不符，应该是未更新文档
	*/
	_httpGetListOrgCardByUserId->GetJson([&](bool success, QJsonObject jsonOrgCardObject)
	{
		if (success)
		{
			QList<TableBasePtr> inMyStuffList;
			QStringList outMyStuffList;
            QStringList orgFeedIDs;
			QJsonArray myListOrgArray = jsonOrgCardObject.value("data").toObject().value("list").toArray();
			qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany _httpGetListOrgCardByUserId :" << QString(QJsonDocument(jsonOrgCardObject).toJson());
			for (int p = 0; p < myListOrgArray.size(); p++)
			{
				_isChangedOfCompanyInfo = true;
				st_MyStuffPtr myStuff = std::make_shared<st_MyStuff>();
				QString orgFeedID = myListOrgArray.at(p).toObject().value("feedId").toString();
				QString orgComID = QString("%1").arg(myListOrgArray.at(p).toObject().value("comId").toInt());
				int status = myListOrgArray.at(p).toObject().value("useStatus").toInt();
				if (status == 1)
				{
					orgFeedIDs.append(orgFeedID);
					myStuff->SetFeedID(orgFeedID);
					myStuff->SetFeedType(QString(FeedTypeOrg));
					myStuff->SetExt(orgComID);
					inMyStuffList.append(std::dynamic_pointer_cast<TableBase>(myStuff));
				}
				else if (status == 0)
				{
					qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany _httpGetListOrgCardByUserId: delete OrgCard: " << orgFeedID;
					outMyStuffList.append(orgFeedID);
				}
			}
			if (inMyStuffList.size() > 0)
			{
				qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany Colleague staff over,total :" << inMyStuffList.size();
				TNDataControlServer::GetInstance()->InsertDatas(inMyStuffList, INSERT_MYSTUFF, DBTYPE_USER);
			}
			if (outMyStuffList.size() > 0)
			{
				qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany _httpGetListOrgCardByUserId: delete OrgCard list: " << outMyStuffList.size();
				TNDataControlServer::GetInstance()->DeleteFromTableNameByField("MyStuff", "feedId", outMyStuffList, DBTYPE_USER);
			}
			QList<UINotifyData> notifyData;
            if (orgFeedIDs.size() > 0)
            {
				_userDataHelper->LoadFeeds(orgFeedIDs, notifyData, RefreshTypeUI_NoFresh);
				updateOrgCommunicationStatus(orgFeedIDs.toSet(), false);
				/*
				我的组织名片对应的公司信息
				*/
                _httpGetListOrgCardByFeedForOrg->GetJson([&](bool success, QString,QJsonObject jsonOrgCardByFeedObject)
				{
					if (success)
					{
						QList<TableBasePtr> inOrgCardCompanyList;
						QStringList outOrgCardCompanyList;
						qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany _httpGetListOrgCardByFeedForOrg :" << QString(QJsonDocument(jsonOrgCardByFeedObject).toJson());
						QJsonArray myListOrgArray = jsonOrgCardByFeedObject.value("data").toArray();
						for (int p = 0; p < myListOrgArray.size(); p++)
						{
							_isChangedOfCompanyInfo = true;
							st_CompanyInfoPtr company = std::make_shared<st_CompanyInfo>();
							company->setComId(QString("%1").arg(jsonOrgCardByFeedObject.value("data").toArray().at(p).toObject().value("comId").toInt()));
							company->setComFeedId(jsonOrgCardByFeedObject.value("data").toArray().at(p).toObject().value("feedId").toString());
							company->setComAddress(jsonOrgCardByFeedObject.value("data").toArray().at(p).toObject().value("address").toString());
							company->setCardNo(jsonOrgCardByFeedObject.value("data").toArray().at(p).toObject().value("cardNo").toString());
							qint64 tempCreateTime = jsonOrgCardByFeedObject.value("data").toArray().at(p).toObject().value("createTime").toDouble();
							company->setCreateTime(QString("%1").arg(tempCreateTime));
							company->setCreatorId(QString("%1").arg(jsonOrgCardByFeedObject.value("data").toArray().at(p).toObject().value("creatorId").toInt()));
							company->setDisplayName(jsonOrgCardByFeedObject.value("data").toArray().at(p).toObject().value("displayName").toString());
							company->setComName(jsonOrgCardByFeedObject.value("data").toArray().at(p).toObject().value("displayName").toString());
							company->setDisplayNamePinyin(jsonOrgCardByFeedObject.value("data").toArray().at(p).toObject().value("displayNamePinyin").toString());
							company->setExchangeMode(QString("%1").arg(jsonOrgCardByFeedObject.value("data").toArray().at(p).toObject().value("exchangeMode").toInt()));
							company->setIndustry(jsonOrgCardByFeedObject.value("data").toArray().at(p).toObject().value("industry").toString());
							company->setIntroduction(jsonOrgCardByFeedObject.value("data").toArray().at(p).toObject().value("introduction").toString());
							company->setLogo(jsonOrgCardByFeedObject.value("data").toArray().at(p).toObject().value("logo").toString());
							qint64 tempUpdateTime = jsonOrgCardByFeedObject.value("data").toArray().at(p).toObject().value("updateTime").toDouble();
							company->setUpdateTime(QString("%1").arg(tempUpdateTime));
							company->setOwnerId(QString("%1").arg(jsonOrgCardByFeedObject.value("data").toArray().at(p).toObject().value("ownerId").toInt()));
							company->setOrgCommunication(jsonOrgCardByFeedObject.value("data").toArray().at(p).toObject().value("communicateStatus").toString());
							QJsonArray subItems = jsonOrgCardByFeedObject.value("data").toArray().at(p).toObject().value("fieldList").toArray();
							for (int i = 0; i < subItems.size(); i++)
							{
								QString fieldId = QString("%1").arg(subItems.at(i).toObject().value("fieldId").toInt());
								if (fieldId == COMPANYINFO_FIELDID_EMAIL)
								{
									company->setEmail(subItems.at(i).toObject().value("fieldValue").toString());
								}
								else if (fieldId == COMPANYINFO_FIELDID_TEL)
								{
									company->setPhone(subItems.at(i).toObject().value("fieldValue").toString());
								}
							}
							int status = jsonOrgCardByFeedObject.value("data").toArray().at(p).toObject().value("useStatus").toInt();
							if (status)
							{
								qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany _httpGetListOrgCardByFeedForOrg: update company info";
								inOrgCardCompanyList.append(std::dynamic_pointer_cast<TableBase>(company));
							}
							else
							{
								qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany _httpGetListOrgCardByFeedForOrg: delete company info: " << company->getComId();
								outOrgCardCompanyList.append(company->getComId());
							}
						}
						if (inOrgCardCompanyList.size() > 0)
						{
							qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany _httpGetListOrgCardByFeedForOrg: update company info list :" << inOrgCardCompanyList.size();
							TNDataControlServer::GetInstance()->InsertDatas(inOrgCardCompanyList, INSERT_COMPANY, DBTYPE_USER);
						}
						if (outOrgCardCompanyList.size()>0)
						{
							qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany _httpGetListOrgCardByFeedForOrg: delete company info list: " << outOrgCardCompanyList.size();
							TNDataControlServer::GetInstance()->DeleteFromTableNameByField("CompanyInfo", "comId", outOrgCardCompanyList, DBTYPE_USER);
						}
					}
                }, _userDataHelper->_pluginParam, QString(),orgFeedIDs);
            }
		}
		TNUserVersionInfo::GetInstance()->SetUpdateVersion(UPDATE_TYPE_OrgCard, jsonOrgCardObject);
	}, _userDataHelper->_pluginParam, orgCardUpdateVersion);

	//增量查询同事通讯录分组关系
    QString versionColleagueRelation = "0";
    if (_isIncreamentUpdate)
    {
        versionColleagueRelation = TNUserVersionInfo::GetInstance()->GetUpdateVersion(UPDATE_TYPE_ColleagueRelation);
    }
	_httpGetListGroupContactByUserId->GetJson([&](bool success, QJsonObject jsonObject)
	{
		qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany _httpGetListGroupContactByUserId :" << QString(QJsonDocument(jsonObject).toJson());
		if (success)
		{
			QList<TableBasePtr> inColleagueRelationList;
			QList<QString> outColleagueRelationList;
			QStringList strFeedIDs;
			QJsonArray feedArray = jsonObject.value("data").toObject().value("list").toArray();
			for (int i = 0; i < feedArray.size(); i++)
			{
				QString myFeed = feedArray.at(i).toObject().value("myFeedId").toString();
				QJsonArray colleagueListArray = feedArray.at(i).toObject().value("colleagueList").toArray();
				for (int j = 0; j < colleagueListArray.size(); j++)
				{
					_isChangedOfCompanyInfo = true;
					st_ColleagueRelationPtr stColleagueRelation = std::make_shared<st_ColleagueRelation>();
					int status = colleagueListArray.at(j).toObject().value("status").toInt();
					QString feedId = colleagueListArray.at(j).toObject().value("feedId").toString();
					QString groupId = QString("%1").arg(colleagueListArray.at(j).toObject().value("groupId").toInt());
					QString feedBelongGroup = feedId + "_" + myFeed + "_" + groupId;
					if (status)
					{
						strFeedIDs.append(feedId);
						QString relationId = QString("%1").arg(colleagueListArray.at(j).toObject().value("relationId").toInt());
						QString groupId = QString("%1").arg(colleagueListArray.at(j).toObject().value("groupId").toInt());
						QString comId = QString("%1").arg(colleagueListArray.at(j).toObject().value("comId").toInt());
						QString staffId = QString("%1").arg(static_cast<qlonglong>(colleagueListArray.at(j).toObject().value("staffId").toDouble()));
						QString status = QString("%1").arg(colleagueListArray.at(j).toObject().value("status").toInt());
						QString orderValue = QString("%1").arg(colleagueListArray.at(j).toObject().value("orderValue").toInt());
						QString createTime = QString("%1").arg(static_cast<qlonglong>(colleagueListArray.at(j).toObject().value("createTime").toDouble()));
						QString updateTime = QString("%1").arg(static_cast<qlonglong>(colleagueListArray.at(j).toObject().value("updateTime").toDouble()));

						stColleagueRelation->SetFeedId(feedId);
						stColleagueRelation->SetRelationId(relationId);
						stColleagueRelation->SetGroupId(groupId);
						stColleagueRelation->SetComId(comId);
						stColleagueRelation->SetStaffId(staffId);
						stColleagueRelation->SetOrderValue(orderValue);
						stColleagueRelation->SetCreateTime(createTime);
						stColleagueRelation->SetUpdateTime(updateTime);
						stColleagueRelation->SetBelongTo(myFeed);
						stColleagueRelation->SetFeedBelongToGroup(feedBelongGroup);
						inColleagueRelationList.append(std::dynamic_pointer_cast<TableBase>(stColleagueRelation));
					}
					else
					{
						qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany _httpGetListGroupContactByUserId: delete ColleagueRelation: " << feedBelongGroup;
						outColleagueRelationList.append(feedBelongGroup);
					}
				}
			}
			if (inColleagueRelationList.size() > 0)
			{
				qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany _httpGetListGroupContactByUserId: add ColleagueRelation list: " << inColleagueRelationList.size();
				TNDataControlServer::GetInstance()->InsertDatas(inColleagueRelationList, INSERT_COLLEAGUERELATION, DBTYPE_USER);
			}
			if (outColleagueRelationList.size() > 0)
			{
				qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany _httpGetListGroupContactByUserId: delete ColleagueRelation list: " << outColleagueRelationList.size();
				TNDataControlServer::GetInstance()->DeleteFromTableNameByField("ColleagueRelation", "feed_belongTo_group", outColleagueRelationList, DBTYPE_USER);
			}
			if (TNUserVersionInfo::GetInstance()->GetUpdateVersion(UPDATE_TYPE_ColleagueRelation) != "0" 
				&& strFeedIDs.size() > 0) //全量的时候跳过
			{
				QList<UINotifyData> notifyData;
				_userDataHelper->LoadFeeds(strFeedIDs, notifyData, RefreshTypeUI_NoFresh);
			}
			TNUserVersionInfo::GetInstance()->SetUpdateVersion(UPDATE_TYPE_ColleagueRelation, jsonObject);
		}
	}, _userDataHelper->_pluginParam, versionColleagueRelation);

	//查询组织分组
    QString versionOrgGroup = "0";
    if (_isIncreamentUpdate)
    {
        versionOrgGroup = TNUserVersionInfo::GetInstance()->GetUpdateVersion(UPDATE_TYPE_OrgGroup);
    }
	_httpGetOrgGroupList->GetJson([&](bool success, QJsonObject jsonObject)
	{
		qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany _httpGetOrgGroupList :" << QString(QJsonDocument(jsonObject).toJson());
		if (success)
		{
			QList<TableBasePtr> inColleagueGroupList;
			QList<QString> outColleagueGroupList;
			QJsonArray groupArray = jsonObject.value("data").toObject().value("list").toArray();
			for (int i = 0; i < groupArray.size(); i++)
			{
				_isChangedOfCompanyInfo = true;
				st_ColleagueGroupPtr stColleagueGroup = std::make_shared<st_ColleagueGroup>();
				int status = groupArray.at(i).toObject().value("status").toInt();
				QString groupId = QString("%1").arg(groupArray.at(i).toObject().value("groupId").toInt());
				if (status)
				{
					QString comId = QString("%1").arg(groupArray.at(i).toObject().value("comId").toInt());
					QString groupName = groupArray.at(i).toObject().value("groupName").toString();
					QString orderValue = QString("%1").arg(groupArray.at(i).toObject().value("orderValue").toInt());
					QString createTime = QString("%1").arg(static_cast<qlonglong>(groupArray.at(i).toObject().value("createTime").toDouble()));
					QString updateTime = QString("%1").arg(static_cast<qlonglong>(groupArray.at(i).toObject().value("updateTime").toDouble()));
					stColleagueGroup->SetGroupId(groupId);
					stColleagueGroup->SetComId(comId);
					stColleagueGroup->SetGroupName(groupName);
					stColleagueGroup->SetOrderValue(orderValue);
					stColleagueGroup->SetCreateTime(createTime);
					stColleagueGroup->SetUpdateTime(updateTime);
					inColleagueGroupList.append(std::dynamic_pointer_cast<TableBase>(stColleagueGroup));
				}
				else
				{
					qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany _httpGetOrgGroupList: delete department: " << groupId;
					outColleagueGroupList.append(groupId);
				}
			}
			if (inColleagueGroupList.size() >0)
				TNDataControlServer::GetInstance()->InsertDatas(inColleagueGroupList, INSERT_COLLEAGUEGROUP, DBTYPE_USER);
			if (outColleagueGroupList.size() > 0)
			{
				qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany _httpGetOrgGroupList: delete department list: " << outColleagueGroupList.size();
				TNDataControlServer::GetInstance()->DeleteFromTableNameByField("ColleagueGroup", "groupId", outColleagueGroupList, DBTYPE_USER);
			}
			TNUserVersionInfo::GetInstance()->SetUpdateVersion(UPDATE_TYPE_OrgGroup, jsonObject);
			qInfo() << "[IMCORE][TNNoticeUpdater]updateMyCompany end ";
		}
	}, _userDataHelper->_pluginParam, versionOrgGroup);
}
void TNNoticeUpdater::StartUpdateCompanySlot()
{
	qint64 time = abs(QDateTime::currentDateTime().secsTo(_latestUpdateCompanyTime));
	if (time > 30 && !_hasStartedUpdating)
	{
		_latestUpdateCompanyTime = QDateTime::currentDateTime();
		init(true);
		updateMyCompany();
	}
	else
		qInfo() << "[IMCORE][TNNoticeUpdater]ProcessUpdateCompany not update,time ：" << time << " _hasStartedUpdating: " << _hasStartedUpdating;
}
void TNNoticeUpdater::ProcessUpdateCompany()
{
	emit StartUpdateCompany();
	qInfo() << "[IMCORE][TNNoticeUpdater]ProcessUpdateCompany";
}
/*
已弃用
*/
void TNNoticeUpdater::ProcessUpdateGroupAndRelation()
{
	if (_httpGetListGroupContactByUserId.get() == NULL)
	{
		_httpGetListGroupContactByUserId = std::make_shared<TNHttpGetListGroupContactByUserId>();
	}
	QString versionColleagueRelation = "0";
	if (_isIncreamentUpdate)
	{
		versionColleagueRelation = TNUserVersionInfo::GetInstance()->GetUpdateVersion(UPDATE_TYPE_ColleagueRelation);
	}
	_httpGetListGroupContactByUserId->GetJson([&](bool success, QJsonObject jsonObject)
	{
		qDebug() << "_httpGetListGroupContactByUserId :" << QString(QJsonDocument(jsonObject).toJson());
		if (success)
		{
			QList<TableBasePtr> inColleagueRelationList;
			QList<QString> outColleagueRelationList;
			QJsonArray feedArray = jsonObject.value("data").toObject().value("list").toArray();
			for (int i = 0; i < feedArray.size(); i++)
			{
				QString myFeed = feedArray.at(i).toObject().value("myFeedId").toString();
				QJsonArray colleagueListArray = feedArray.at(i).toObject().value("colleagueList").toArray();
				for (int j = 0; j < colleagueListArray.size(); j++)
				{
					st_ColleagueRelationPtr stColleagueRelation = std::make_shared<st_ColleagueRelation>();
					int status = colleagueListArray.at(j).toObject().value("status").toInt();
					QString feedId = colleagueListArray.at(j).toObject().value("feedId").toString();
					QString groupId = QString("%1").arg(colleagueListArray.at(j).toObject().value("groupId").toInt());
					QString feedBelongGroup = feedId + "_" + myFeed + "_" + groupId;
					if (status)
					{
						QString feedId = colleagueListArray.at(j).toObject().value("feedId").toString();
						QString relationId = QString("%1").arg(colleagueListArray.at(j).toObject().value("relationId").toInt());
						QString groupId = QString("%1").arg(colleagueListArray.at(j).toObject().value("groupId").toInt());
						QString comId = QString("%1").arg(colleagueListArray.at(j).toObject().value("comId").toInt());
						QString staffId = QString("%1").arg(static_cast<qlonglong>(colleagueListArray.at(j).toObject().value("staffId").toDouble()));
						QString status = QString("%1").arg(colleagueListArray.at(j).toObject().value("status").toInt());
						QString orderValue = QString("%1").arg(colleagueListArray.at(j).toObject().value("orderValue").toInt());
						QString createTime = QString("%1").arg(static_cast<qlonglong>(colleagueListArray.at(j).toObject().value("createTime").toDouble()));
						QString updateTime = QString("%1").arg(static_cast<qlonglong>(colleagueListArray.at(j).toObject().value("updateTime").toDouble()));

						stColleagueRelation->SetFeedId(feedId);
						stColleagueRelation->SetRelationId(relationId);
						stColleagueRelation->SetGroupId(groupId);
						stColleagueRelation->SetComId(comId);
						stColleagueRelation->SetStaffId(staffId);
						stColleagueRelation->SetOrderValue(orderValue);
						stColleagueRelation->SetCreateTime(createTime);
						stColleagueRelation->SetUpdateTime(updateTime);
						stColleagueRelation->SetBelongTo(myFeed);
						stColleagueRelation->SetFeedBelongToGroup(feedBelongGroup);
						inColleagueRelationList.append(std::dynamic_pointer_cast<TableBase>(stColleagueRelation));
					}
					else
					{
						qDebug() << "_httpGetListGroupContactByUserId: delete ColleagueRelation: " << feedBelongGroup;
						outColleagueRelationList.append(feedBelongGroup);
					}
				}
			}
			if (inColleagueRelationList.size() >0)
				TNDataControlServer::GetInstance()->InsertDatas(inColleagueRelationList, INSERT_COLLEAGUERELATION, DBTYPE_USER);
			if (outColleagueRelationList.size() > 0)
			{
				qDebug() << "_httpGetListGroupContactByUserId: delete ColleagueRelation list: " << outColleagueRelationList.size();
				TNDataControlServer::GetInstance()->DeleteFromTableNameByField("ColleagueRelation", "feed_belongTo_group", outColleagueRelationList, DBTYPE_USER);
			}
			TNUserVersionInfo::GetInstance()->SetUpdateVersion(UPDATE_TYPE_ColleagueRelation, jsonObject);
		}
	}, _userDataHelper->_pluginParam, versionColleagueRelation);

	//查询组织分组
	if (_httpGetOrgGroupList.get() == NULL)
	{
		_httpGetOrgGroupList = std::make_shared<TNHttpGetOrgGroupList>();
	}
	QString versionOrgGroup = "0";
	if (_isIncreamentUpdate)
	{
		versionOrgGroup = TNUserVersionInfo::GetInstance()->GetUpdateVersion(UPDATE_TYPE_OrgGroup);
	}
	_httpGetOrgGroupList->GetJson([&](bool success, QJsonObject jsonObject)
	{
		qDebug() << "_httpGetOrgGroupList :" << QString(QJsonDocument(jsonObject).toJson());
		if (success)
		{
			QList<UINotifyData> notifyData;
			QList<TableBasePtr> inColleagueGroupList;
			QList<QString> outColleagueGroupList;
			QJsonArray groupArray = jsonObject.value("data").toObject().value("list").toArray();
			for (int i = 0; i < groupArray.size(); i++)
			{
				st_ColleagueGroupPtr stColleagueGroup = std::make_shared<st_ColleagueGroup>();
				int status = groupArray.at(i).toObject().value("status").toInt();
				QString groupId = QString("%1").arg(groupArray.at(i).toObject().value("groupId").toInt());
				if (status)
				{
					QString comId = QString("%1").arg(groupArray.at(i).toObject().value("comId").toInt());
					QString groupName = groupArray.at(i).toObject().value("groupName").toString();
					QString orderValue = QString("%1").arg(groupArray.at(i).toObject().value("orderValue").toInt());
					QString createTime = QString("%1").arg(static_cast<qlonglong>(groupArray.at(i).toObject().value("createTime").toDouble()));
					QString updateTime = QString("%1").arg(static_cast<qlonglong>(groupArray.at(i).toObject().value("updateTime").toDouble()));
					stColleagueGroup->SetGroupId(groupId);
					stColleagueGroup->SetComId(comId);
					stColleagueGroup->SetGroupName(groupName);
					stColleagueGroup->SetOrderValue(orderValue);
					stColleagueGroup->SetCreateTime(createTime);
					stColleagueGroup->SetUpdateTime(updateTime);
					inColleagueGroupList.append(std::dynamic_pointer_cast<TableBase>(stColleagueGroup));
					appendUINotifyData(groupId, groupId, UI_OPERATE_ADD, notifyData);
				}
				else
				{
					qDebug() << "_httpGetOrgGroupList: delete department: " << groupId;
					outColleagueGroupList.append(groupId);
					appendUINotifyData(groupId, groupId, UI_OPERATE_DEL, notifyData);
				}
			}
			if (inColleagueGroupList.size() >0)
				TNDataControlServer::GetInstance()->InsertDatas(inColleagueGroupList, INSERT_COLLEAGUEGROUP, DBTYPE_USER);
			if (outColleagueGroupList.size() > 0)
			{
				qDebug() << "_httpGetOrgGroupList: delete department list: " << outColleagueGroupList.size();
				TNDataControlServer::GetInstance()->DeleteFromTableNameByField("ColleagueGroup", "groupId", outColleagueGroupList, DBTYPE_USER);
			}
			if (notifyData.size() > 0)
			{
				TNNotifyCenter::instance()->postNotifyRefresh(RefreshTypeUI_Colleague, notifyData);
			}
			TNUserVersionInfo::GetInstance()->SetUpdateVersion(UPDATE_TYPE_OrgGroup, jsonObject);
			qDebug() << "updateMyCompany end ";
		}
	}, _userDataHelper->_pluginParam, versionOrgGroup);
}
void TNNoticeUpdater::OnFinishLoadSlots(int type, QList<UINotifyData> dataList)
{
	qInfo() << "OnFinishLoadSlots start";
    if (_isIncreamentUpdate)
    {
		qDebug() << "OnFinishLoadSlots postNotifyRefresh info,type : " << type << " data: " << dataList.size();
		if (type == RefreshTypeUI_MyCard)
		{
			//更新imsdk myfeed数据
			QList<st_FeedPtr> myAllStuff;
			TNDataCache::GetInstance()->UpdateMyStuffCache();
			TNDataCache::GetInstance()->getMyStuff(myAllStuff);
			vector<std::string> feedList;
			for (st_FeedPtr feed : myAllStuff)
			{
				feedList.push_back(feed->GetFeedID().toUtf8().data());
			}
			toonim::getImSDK()->updateMyFeedList(feedList);
		}
		TNNotifyCenter::instance()->postNotifyRefresh(type, dataList);
		//更新缓存
    }
	qDebug() << "OnFinishLoadSlots end";
}

void TNNoticeUpdater::OnUpdateRefreshUI(int type, QString info)
{
	qInfo() << "[IMCORE][TNNoticeUpdater]OnUpdateRefreshUI start type: " << type;
	if (type == CATALOG_SYNC_MYFRIEND)
	{
		updateMyFriend();
	}
	else if (type == CATALOG_SYNC_GROUP)
		updateGroup();
	else if (type == CATALOG_SYNC_MYCARD)
	{
		init(true);
		/*
		个人名片通知也会走这里
		*/
		updateMyCard();
		updateMyCompany();
	}
	else if (type == CATALOG_SYNC_GROUPCHAT)
		updateGroupChat();
	else if (type == CATALOG_SYNC_GROUPMEMBER && !info.isEmpty())
	{
		if (!info.startsWith("gc_"))
		{
			info = "gc_" + info;
		}
		updateGroupChatMember(info);
	}
	else if (type == CATALOG_SYNC_SWITCH)
		updateDisturibData();
	else if (type == CATALOG_FRIEND_REQ)
		updateNewFriend();
	else if (type == CATALOG_STNC_ORGCOMMUNICATION)
	{
		QSet<QString> list;
		list.insert(info);
		updateOrgCommunicationStatus(list,true);
	}
	qInfo() << "[IMCORE][TNNoticeUpdater]OnUpdateRefreshUI end type: " << type;
}

void TNNoticeUpdater::ProcessUpdateUI(int type, QString info)
{
	emit UpdateRefreshUI(type, info);
	qDebug() << "emit UpdateRefreshUI ,type: " << type;
}

void TNNoticeUpdater::ProcessStartUpdateDb()
{
	emit StartUpdateDb();
	qInfo() << "[IMCORE][TNNoticeUpdater]ProcessStartUpdateDb emit StartUpdateDb ";
}

void TNNoticeUpdater::init(bool needUpdateCompany)
{
	_hasStartedUpdating = true;
	_needEmitCompanyFinished = needUpdateCompany;
}

void TNNoticeUpdater::StartUpdateThread()
{
	//转换数据库表
	castDBTable();

	qInfo() << "[IMCORE][TNNoticeUpdater]StartUpdateThread start";
	if (_outTimer == NULL)
		_outTimer = new QTimer;
	connect(_outTimer, SIGNAL(timeout()), this, SLOT(onTimerout()));
	_outTimer->setSingleShot(true);
	_outTimer->setInterval(1000*10); 
	_outTimer->start();
	init(false);
	/*
	非常重要
	//我的名片
	updateMyCard();
	//好友
	updateMyFriend();
	//同事
	updateMyCompany();
	// 自己创建的群组
	updateGroup();
	//群聊
	updateGroupChat();
	//免打扰数据
	updateDisturibData();
	//新学员
	updateNewFriend();
	*/
	qInfo() << "[IMCORE][TNNoticeUpdater]StartUpdateThread end";
   
}
void TNNoticeUpdater::companyUpdateFinishedSlot()
{
	QList<UINotifyData> notifyData;
	//仅仅标识有数据，无实际意义
	appendUINotifyData(AVATAR_ALL_FEED, AVATAR_ALL_FEED, UI_OPERATE_ADD, notifyData);
	TNNotifyCenter::instance()->postNotifyRefresh(RefreshTypeUI_Colleague, notifyData);
	/*
	仍旧需要通知myCard,否则【我的】不更新。
	*/
	//组织名片更新，imsdk更新myfeed数据
	QList<st_FeedPtr> myAllStuff;
	TNDataCache::GetInstance()->UpdateMyStuffCache();
	TNDataCache::GetInstance()->getMyStuff(myAllStuff);
	vector<std::string> feedList;
	for (st_FeedPtr feed : myAllStuff)
	{
		feedList.push_back(feed->GetFeedID().toUtf8().data());
	}
	toonim::getImSDK()->updateMyFeedList(feedList);
	TNNotifyCenter::instance()->postNotifyRefresh(RefreshTypeUI_MyCard, notifyData);

	qInfo() << "[IMCORE][TNNoticeUpdater]companyUpdateFinishedSlot :" << "send RefreshTypeUI_Colleague and RefreshTypeUI_MyCard to UI";
}
void TNNoticeUpdater::monitorHttpApi(TNHttpBaseApi * httpApi)
{
	httpApi->SetNetWorkManager(_netWorkManager);
	if (_hasStartedUpdating)
	{
		_ConnectingHttpApis.insert(httpApi);
		connect(httpApi, SIGNAL(SuccessfulReturn(TNHttpBaseApi *)), this, SLOT(onHttpApiReturn(TNHttpBaseApi *)));
	}
}

void TNNoticeUpdater::onHttpApiReturn(TNHttpBaseApi * httpApi)
{
	//qDebug() << "BaseAPI...onHttpApiReturn...statusCode:";
    if (!_hasStartedUpdating)
    {
        return;
    }
	if (!_needEmitCompanyFinished)
	{
		//重置超时时间
		qInfo() << "[IMCORE][TNNoticeUpdater]onHttpApiReturn:time reset";
		_outTimer->stop();
		_outTimer->setInterval(1000*10);
		_outTimer->start();
	}
    if (!httpApi->isNullConnection())
    {
        return;
    }
	_ConnectingHttpApis.erase(httpApi);

	std::set<TNHttpBaseApi *>::const_iterator iter = _ConnectingHttpApis.begin();
	while (iter != _ConnectingHttpApis.end())
	{
		TNHttpBaseApi *api = *iter;
		if (!api->isNullConnection())
		{
			return;
		}
		iter++;
	}
	qInfo() << "[IMCORE][TNNoticeUpdater]onHttpApiReturn Load Feed monitor finished";

    if (_needEmitCompanyFinished)
    {
        if (_httpGetListStaffContactByUserId->isNullConnection()
            && _httpGetListStaffCard->isNullConnection()
            && _httpGetListOrgCardByUserId->isNullConnection()
            && _httpGetListGroupContactByUserId->isNullConnection()
            && _httpGetListStaffCardByUserId->isNullConnection()
			&& _httpGetCompanyInfobyComIdList->isNullConnection()
			&& _httpGetListOrgCardByFeeds->isNullConnection()
			&& _httpGetCompanyFeedIdByComId->isNullConnection()
			&& _httpGetListOrgCardByFeedForOrg->isNullConnection()
			&& _httpGetOrgGroupList->isNullConnection())
        {
            _needEmitCompanyFinished = false;
			if (_isChangedOfCompanyInfo)
			{
				_isChangedOfCompanyInfo = false;
				emit companyUpdateFinished();
				qInfo() << "[IMCORE][TNNoticeUpdater]onHttpApiReturn Send companyUpdateFinished signal";
			}
			else
				qInfo() << "[IMCORE][TNNoticeUpdater]onHttpApiReturn Not Send companyUpdateFinished signal";
        }
        else
        {
            return;
        }
		_hasStartedUpdating = false;
    }
	else
	{
		if (!_userDataHelper->IsEmptyUpdateList())
		{
			QList<UINotifyData> notifyData;
			QStringList strFeedIDs;
			//群聊成员详情，合并请求一次
			_userDataHelper->LoadFeeds(strFeedIDs, notifyData, -1);
		}
		else
		{
			//群聊成员详情请求结果返回后，发送更新缓存信号
			_outTimer->stop();
			qInfo() << "[IMCORE][TNNoticeUpdater]onHttpApiReturn Send update all cache signal,thread ID:" << QString("@0x%1").arg(quintptr(QThread::currentThreadId()), 16, 16, QLatin1Char('0'));
			TNDataCache::GetInstance()->updateAllCacheSlot();
			//emit AllUpdateFinished();
			_hasStartedUpdating = false;
		}
	}
}

void TNNoticeUpdater::onNewFeedGetApi(TNHttpObtainFeedList * api)
{
	Q_ASSERT(api);
	if (_hasStartedUpdating && api)
	{
		_ConnectingHttpApis.insert(api);
		connect(api, SIGNAL(SuccessfulReturn(TNHttpBaseApi *)), this, SLOT(onHttpApiReturn(TNHttpBaseApi *)));
	}
}

void TNNoticeUpdater::onTimerout()
{
	qInfo() << "[IMCORE][TNNoticeUpdater]onTimerout TNNoticeUpdater:time out 10s";
	_outTimer->stop();
	TNDataCache::GetInstance()->updateAllCacheSlot();
	//emit AllUpdateFinished();
	_hasStartedUpdating = false;
}
void TNNoticeUpdater::ProcessUpdateRemark(const QString&from, const QString &to)
{
	emit startUpdateReMark(from,to);
	qInfo() << "[IMCORE][TNNoticeUpdater]ProcessUpdateRemark";
}
void TNNoticeUpdater::startUpdateReMarkSlot(const QString&from, const QString &to)
{
	qInfo() << "[IMCORE][TNNoticeUpdater]startUpdateReMarkSlot";
	updateFriendReMarkSingle(from, QStringList(to));
}
/*
1. 仅仅名片所有者会收到通知
2. 调用获取时，会异步同步
*/
void TNNoticeUpdater::updateOrgCommunicationStatus(QSet<QString> oFeeds, bool needRefreshUI)
{
	Q_ASSERT(oFeeds.size());

	qInfo() << "[IMCORE][TNNoticeUpdater]updateOrgCommunicationStatus start ,ofeeds size:" << oFeeds.size();
	if (_httpGetOrgCommunication.get() == NULL)
	{
		_httpGetOrgCommunication = std::make_shared<TNHttpGetOrgCommunicationStatus>();
		monitorHttpApi(_httpGetOrgCommunication.get());
	}

	_httpGetOrgCommunication->GetJson([&](bool success,bool needRefreshUI, QJsonObject JsonObject)
	{
		if (success)
		{
			QMap<QString, QString> statusMap;
			qInfo() << "[IMCORE][TNNoticeUpdater]updateOrgCommunicationStatus _httpGetOrgCommunication: " << QString(QJsonDocument(JsonObject).toJson());
			QJsonArray myListOrgArray = JsonObject.value("data").toArray();
			for (int p = 0; p < myListOrgArray.size(); p++)
			{
				QString oFeed = JsonObject.value("data").toArray().at(p).toObject().value("feedId").toString();
				QString status = JsonObject.value("data").toArray().at(p).toObject().value("communicateStatus").toString();
				if (!oFeed.isEmpty() && !status.isEmpty())
				{
					statusMap.insert(oFeed,status);
					if (needRefreshUI)
					{
						//更新缓存
						TNDataCache::GetInstance()->updateOrgCommunicationStatus(oFeed, status);
						//发送通知
						TNNotifyCenter::instance()->postNotifyOrgCommunicationStatus(oFeed, status);
					}
				}
			}
			if (statusMap.size() > 0)
			{
				//更新数据库,feed表
				TNDataControlServer::GetInstance()->updateSetValueByValueMap("Feed", "ext1", "feedId", statusMap, DBTYPE_USER);
			}
		}
	}, _userDataHelper->_pluginParam, oFeeds, needRefreshUI);
}

void TNNoticeUpdater::castDBTable()
{
	TNConfig* pconfig = TNConfig::instance();
	int nStatus = 0;
	nStatus = pconfig->GetCastStatus();
	if (nStatus > 0)
	{
		return;
	}

	bool bRetCast = castBmssageToCTNMessage();
	if (bRetCast)
	{
		pconfig->SetCastStatus(1);
	}
	else
	{
		pconfig->SetCastStatus(0);
	}

	castSession();
}

bool TNNoticeUpdater::castBmssageToCTNMessage()
{
	TableBaseVec tableBaseVec;
	vector<CTNMessage> messages;

	bool bRetRDB = TNDataControlServer::GetInstance()->GetAllFieldsByTableName("BMessage0", tableBaseVec, DBTYPE_MSG);
	if (!bRetRDB)
	{
		qInfo() << "[IMCORE][TNNoticeUpdater]castBmssageToCTNMessage";
	}

	for (TableBaseVec::iterator iter = tableBaseVec.begin(); iter != tableBaseVec.end(); iter++)
	{
		st_BMessage0Ptr record = std::dynamic_pointer_cast<st_BMessage0>(*iter);
		CTNMessage imMessage;
		TNIMCoreClient::GetIMClient()->BMessageCastToIMMessage(record, imMessage);

		messages.push_back(imMessage);
	}

	bool bRetWDB = toonim::getChatDB()->addMessages(messages);
	return bRetWDB;
}

bool TNNoticeUpdater::castSession()
{
	TableBaseVec tableBaseVec;
	vector<CTNSession> sessions;

	bool bRetRDB = TNDataControlServer::GetInstance()->GetAllFieldsByTableName("Session", tableBaseVec, DBTYPE_MSG);
	if (!bRetRDB)
	{
		qInfo() << "[IMCORE][TNNoticeUpdater]castSession";
	}

	for (TableBaseVec::iterator iter = tableBaseVec.begin(); iter != tableBaseVec.end(); iter++)
	{
		st_SessionPtr record = std::dynamic_pointer_cast<st_Session>(*iter);
		CTNSession imSession;
		TNIMCoreClient::GetIMClient()->BSessionCastToIMSession(record, imSession);

		sessions.push_back(imSession);
	}

	bool bRetWDB = toonim::getChatDB()->addSession(sessions);
	return bRetWDB;
}