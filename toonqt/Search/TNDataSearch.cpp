#include "TNDataSearch.h"
#include "TNDbUtil.h"
#include "TNDataCache.h"
#include "TNIMCoreClient.h"
#include "CTNDBAPI.h"

#include <qdebug.h>

TNDataSearch* TNDataSearch::_Instance = new TNDataSearch();
TNDataSearch::TNDataSearch()
{

}

TNDataSearch::~TNDataSearch()
{

}
TNDataSearch* TNDataSearch::GetInstance()
{
	return _Instance;
}
bool TNDataSearch::searchBasePyText(QString key, QString text, QString originalTextPy, baseResult &result)
{
	bool isHit = false;
	int  hitIndex = -1;
	QString hitString;
	QString firstLetters;
	//3.8.3 title 和subtitle中间两个空格  需要处理
	QString textValidPy = originalTextPy.replace("  ",SPACE_STR);
	QStringList wordList = textValidPy.split(SPACE_STR);//最后一位空格会被格式化进去~
	for (int i = 0; i < wordList.size(); i++)
	{
		if (!wordList[i].isEmpty())
			firstLetters += wordList[i].at(0);
		QString combination = i == wordList.size() - 1 ? wordList[i] : wordList[i] + wordList[i + 1];
		if (wordList[i].contains(key, Qt::CaseInsensitive)){
			isHit = true;
			hitIndex = textValidPy.replace(SPACE_STR, "").indexOf(key, 0, Qt::CaseInsensitive);
			if (i<text.length())
				hitString = text.at(i);
			break;
		}
		else if (combination.contains(key, Qt::CaseInsensitive)){
			isHit = true;
			hitIndex = textValidPy.replace(SPACE_STR, "").indexOf(key, 0, Qt::CaseInsensitive);
			if (wordList[i + 1].contains(key, Qt::CaseInsensitive)){
				if (i<text.length()-1)
					hitString = QString(text.at(i + 1));
			}
			else{
				if (i<text.length() - 1)
					hitString = QString(text.at(i)) + QString(text.at(i + 1));
			}
			break;
		}
	}
	if (!isHit && (key.size() <= firstLetters.size()))
	{
		if (firstLetters.contains(key, Qt::CaseInsensitive))
		{
			isHit = true;
			int index = firstLetters.indexOf(key, 0, Qt::CaseInsensitive);
			hitIndex = index;
			int space = text.indexOf(SPACE_STR);
			if (space >= index && space <= index + key.size()){
				hitString = text.mid(index, space - index) +SPACE_STR+ text.mid(space+1, key.size()+index-space);
			}
			else if (space != -1 && index>space){
				//如果存在空格且hitstring在空格的左边，则需要+1去除空格。在firstLetters中不包含空格
				hitString = text.mid(index+1, key.size());
			}
			else{
				hitString = text.mid(index, key.size());
			}
		}
	}
	if (!isHit)
	{
		int flag = -1;
		QString hitText;
		for (int i = 0; i < wordList.size(); i++)
		{
			flag = i;
			if (key.isEmpty())
				break;
			if (wordList[i].isEmpty())
			{
				if (i != wordList.size()-1)
					hitText += SPACE_STR;
				continue;
			}
			if (key.contains(wordList[i]) && key.startsWith(wordList[i]))
			{
				if (i<text.length())
					hitText += text.at(i);
				int index = key.indexOf(wordList[i], 0, Qt::CaseInsensitive);
				key = key.mid(0, index) + key.mid(index + wordList[i].length(), key.length() - index - wordList[i].length());
			}
			else if (wordList[i].startsWith(key))
			{
				if (i<text.length())
					hitText += text.at(i);
				key.clear();
				break;
			}
			else if (!hitText.isEmpty())
			{
				break;
			}
		}
		if (key.isEmpty() && !hitText.isEmpty())
		{
			isHit = true;
			hitIndex = flag;
			hitString = hitText;
		}
	}
	if (isHit && hitIndex != -1 
		&& !hitString.isEmpty())
	{
		result.hit = isHit;
		result.hitIndex = hitIndex;
		result.hitString = hitString;
	}
	return isHit;
}
bool TNDataSearch::searchInReMark(int searchMode, int type, const QString &key, TNStructFriend friendInfo, QMultiMap<int, TNStructSearch> &result)
{
	bool isHit = false;
	QString remark = friendInfo.remark;
	QString remarkpy = friendInfo.remarkpy;
	if (remark.isEmpty() || remarkpy.isEmpty())
	{
		return isHit;
	}
	QString firstNamePY = remarkpy.left(remarkpy.indexOf(SPACE_STR));

	if (searchMode == 0)
	{
		baseResult searchResult;
		bool isHit = searchBasePyText(key,remark, remarkpy, searchResult);
		if (isHit && searchResult.hit)
		{
			TNStructSearch search;
			search.m_hitType = 0; //0 备注，1 昵称
			search.m_hitString = searchResult.hitString;
			search.m_flag = type;
			search.m_Feed = friendInfo.m_Feed;
			search.m_count = 2;
			search.m_keyIndex = searchResult.hitIndex;
			search.m_extString = remark;
			search.m_belongFeedId = friendInfo.m_belongFeedId;
			if (firstNamePY == key)
			{
				search.m_keyIndex--;
			}
			result.insert(search.m_keyIndex, search);
			return isHit;
		}
		if (remark.contains(key, Qt::CaseInsensitive))
		{
			isHit = true;
			int hitIndex = remark.indexOf(key, 0, Qt::CaseInsensitive);
			TNStructSearch search;
			search.m_hitType = 0; //0 备注，1 昵称
			search.m_hitString = remark.mid(hitIndex, key.size());;
			search.m_flag = type;
			search.m_Feed = friendInfo.m_Feed;
			search.m_count = 2;
			search.m_keyIndex = hitIndex;
			search.m_extString = remark;
			search.m_belongFeedId = friendInfo.m_belongFeedId;
			if (firstNamePY == key)
			{
				search.m_keyIndex--;
			}
			result.insert(search.m_keyIndex, search);
			return isHit;
		}
	}
	return isHit;
}
bool TNDataSearch::searchInFriendName(int searchMode, int type, const QString &key, TNStructFriend friendInfo, QMultiMap<int, TNStructSearch> &result)
{
	Q_ASSERT(friendInfo.m_Feed != nullptr);

	bool isHit = false;
	QString name = friendInfo.m_Feed->GetTitle();
	QString namePY = friendInfo.m_Feed->GetTitlePinYin();
	if (name.isEmpty() || namePY.isEmpty())
	{
		return isHit;
	}
	QString firstNamePY = namePY.left(namePY.indexOf(SPACE_STR));

	if (searchMode == 0)
	{
		baseResult searchResult;
		bool isHit = searchBasePyText(key,name, namePY,searchResult);
		if (isHit && searchResult.hit)
		{
			TNStructSearch search;
			search.m_hitType = 1; //0 备注，1 昵称
			search.m_hitString = searchResult.hitString;
			search.m_flag = type;
			search.m_Feed = friendInfo.m_Feed;
			search.m_count = 2;
			search.m_keyIndex = searchResult.hitIndex;
			search.m_belongFeedId = friendInfo.m_belongFeedId;
			search.m_extString = friendInfo.remark;
			if (firstNamePY == key)
			{
				search.m_keyIndex--;
			}
			result.insert(search.m_keyIndex, search);
			return isHit;
		}
		if (name.contains(key, Qt::CaseInsensitive))
		{
			isHit = true;
			int hitIndex = name.indexOf(key, 0, Qt::CaseInsensitive);
			TNStructSearch search;
			search.m_hitType = 1; //0 备注，1 昵称
			search.m_hitString = name.mid(hitIndex, key.size());;
			search.m_flag = type;
			search.m_Feed = friendInfo.m_Feed;
			search.m_count = 2;
			search.m_keyIndex = hitIndex;
			search.m_belongFeedId = friendInfo.m_belongFeedId;
			search.m_extString = friendInfo.remark;
			if (firstNamePY == key)
			{
				search.m_keyIndex--;
			}
			result.insert(search.m_keyIndex, search);
			return isHit;
		}
	}
	return isHit;
}
bool TNDataSearch::searchInName(int searchMode, int type, const QString &key, st_FeedPtr feed, const QString &belongId, QMultiMap<int, TNStructSearch> &result)
{
	Q_ASSERT(feed != nullptr);

	bool isHit = false;
	QString name = feed->GetTitle();
	QString namePY = feed->GetTitlePinYin();
	if (name.isEmpty() || namePY.isEmpty())
	{
		return isHit;
	}
	QString firstNamePY = namePY.left(namePY.indexOf(SPACE_STR));

	if (searchMode == 0)
	{
		baseResult searchResult;
		bool isHit = searchBasePyText(key,name, namePY, searchResult);
		if (isHit && searchResult.hit 
			&& !isMyStaffCard(feed->GetFeedID()))
		{
			TNStructSearch search;
			search.m_hitType = 1; //0 备注，1 昵称
			search.m_hitString = searchResult.hitString;
			search.m_flag = type;
			search.m_Feed = feed;
			search.m_count = 2;
			search.m_keyIndex = searchResult.hitIndex;
			search.m_belongFeedId = belongId;
			if (firstNamePY == key)
			{
				search.m_keyIndex--;
			}
			result.insert(search.m_keyIndex, search);
			return isHit;
		}
		if (name.contains(key, Qt::CaseInsensitive) 
			&& !isMyStaffCard(feed->GetFeedID()))
		{
			isHit = true;
			int hitIndex = name.indexOf(key, 0, Qt::CaseInsensitive);
			TNStructSearch search;
			search.m_hitType = 1; //0 备注，1 昵称
			search.m_hitString = name.mid(hitIndex, key.size());;
			search.m_flag = type;
			search.m_Feed = feed;
			search.m_count = 2;
			search.m_keyIndex = hitIndex;
			search.m_belongFeedId = belongId;
			if (firstNamePY == key)
			{
				search.m_keyIndex--;
			}
			result.insert(search.m_keyIndex, search);
			return isHit;
		}
	}
	return isHit;
}
bool TNDataSearch::searchInGroupChatName(int searchMode, int type, const QString &key, st_GroupInfoPtr groupChat, QList<TNStructSearch> &result)
{
	Q_ASSERT(groupChat != nullptr);

	bool isHit = false;
	QString name = groupChat->GetName();
	QString namePY = groupChat->GetNamePinyin();
	/*
	忽略名称和拼音是否为空
	*/
	QString firstNamePY = namePY.left(namePY.indexOf(SPACE_STR));

	if (searchMode == 0)
	{
		baseResult searchResult;
		bool isHit = searchBasePyText(key,name, namePY, searchResult);
		if (isHit && searchResult.hit)
		{
			st_FeedPtr feed = std::make_shared<st_Feed>();
			feed->SetTitle(groupChat->GetName());
			feed->SetTitlePinYin(groupChat->GetNamePinyin());
			feed->SetFeedID(groupChat->GetGroupId());
			feed->SetAvatarID(groupChat->GetHeaderImage());

			TNStructSearch search;
			search.m_hitType = 1; //0 备注，1 昵称, 2 成员
			search.m_hitString = searchResult.hitString;
			search.m_flag = type;
			search.m_Feed = feed;
			search.m_count = 2;
			search.m_keyIndex = searchResult.hitIndex;
			search.m_belongFeedId = groupChat->GetMyFeedId();
			if (firstNamePY == key)
			{
				search.m_keyIndex--;
			}
			result.insert(search.m_keyIndex, search);
			return isHit;
		}
		if (name.contains(key, Qt::CaseInsensitive))
		{
			st_FeedPtr feed = std::make_shared<st_Feed>();
			feed->SetTitle(groupChat->GetName());
			feed->SetTitlePinYin(groupChat->GetNamePinyin());
			feed->SetFeedID(groupChat->GetGroupId());
			feed->SetAvatarID(groupChat->GetHeaderImage());

			isHit = true;
			int hitIndex = name.indexOf(key, 0, Qt::CaseInsensitive);
			TNStructSearch search;
			search.m_hitType = 1; //0 备注，1 昵称, 2 成员
			search.m_hitString = name.mid(hitIndex, key.size());;
			search.m_flag = type;
			search.m_Feed = feed;
			search.m_count = 2;
			search.m_keyIndex = hitIndex;
			search.m_belongFeedId = groupChat->GetMyFeedId();
			if (firstNamePY == key)
			{
				search.m_keyIndex--;
			}
			result.insert(search.m_keyIndex, search);
			return isHit;
		}
	}
	return isHit;
}
bool TNDataSearch::hitInGroupChatMember(int searchMode, int type, const QString &key, const QString &name, const QString &namePy,
	TNStructGroupChat groupChatInfo, QList<TNStructSearch> &result)
{
	QString firstNamePY = namePy.left(namePy.indexOf(SPACE_STR));

	if (searchMode == 0)
	{
		baseResult searchResult;
		bool isHit = searchBasePyText(key, name, namePy, searchResult);
		if (isHit && searchResult.hit)
		{
			st_FeedPtr feed = std::make_shared<st_Feed>();
			feed->SetTitle(groupChatInfo.m_groupChatFeed->GetName());
			feed->SetTitlePinYin(groupChatInfo.m_groupChatFeed->GetNamePinyin());
			feed->SetFeedID(groupChatInfo.m_groupChatFeed->GetGroupId());
			feed->SetAvatarID(groupChatInfo.m_groupChatFeed->GetHeaderImage());

			TNStructSearch search;
			search.m_hitType = 2; //0 备注，1 昵称, 2 成员
			search.m_hitString = searchResult.hitString;
			search.m_extString = name;
			search.m_flag = type;
			search.m_Feed = feed;
			search.m_count = 2;
			search.m_keyIndex = searchResult.hitIndex;
			search.m_belongFeedId = groupChatInfo.m_groupChatFeed->GetMyFeedId();
			if (firstNamePY == key)
			{
				search.m_keyIndex--;
			}
			result.insert(search.m_keyIndex, search);
			return true;
		}
		if (name.contains(key, Qt::CaseInsensitive))
		{
			st_FeedPtr feed = std::make_shared<st_Feed>();
			feed->SetTitle(groupChatInfo.m_groupChatFeed->GetName());
			feed->SetTitlePinYin(groupChatInfo.m_groupChatFeed->GetNamePinyin());
			feed->SetFeedID(groupChatInfo.m_groupChatFeed->GetGroupId());
			feed->SetAvatarID(groupChatInfo.m_groupChatFeed->GetHeaderImage());

			isHit = true;
			int hitIndex = name.indexOf(key, 0, Qt::CaseInsensitive);
			TNStructSearch search;
			search.m_hitType = 2; //0 备注，1 昵称, 2 成员
			search.m_hitString = name.mid(hitIndex, key.size());
			search.m_extString = name;
			search.m_flag = type;
			search.m_Feed = feed;
			search.m_count = 2;
			search.m_keyIndex = hitIndex;
			search.m_belongFeedId = groupChatInfo.m_groupChatFeed->GetMyFeedId();
			if (firstNamePY == key)
			{
				search.m_keyIndex--;
			}
			result.insert(search.m_keyIndex, search);
			return true;
		}
	}
	return false;
}
bool TNDataSearch::searchInGroupChatMember(int searchMode, int type, const QString &key, 
	TNStructGroupChat groupChatInfo, QList<TNStructSearch> &result)
{
	Q_ASSERT(groupChatInfo.m_groupChatFeed!= nullptr);
	bool isHit = false;
	for (int i = 0; i < groupChatInfo.m_groupMember.size(); i++)
	{
		QString remark = groupChatInfo.m_groupMember[i].m_remark;
		QString remarkPY = groupChatInfo.m_groupMember[i].m_remarkPy;
		isHit = hitInGroupChatMember(searchMode, type, key, remark, remarkPY, groupChatInfo
			, result);
		/*
		备注优先
		*/
		if (!isHit)
		{
			QString name = groupChatInfo.m_groupMember[i].m_nickName;
			QString namePY = groupChatInfo.m_groupMember[i].m_pinYin;
			isHit = hitInGroupChatMember(searchMode, type, key, name, namePY, groupChatInfo
				, result);
		}
		if (isHit)
			break;
	}
	return  isHit;
}
int TNDataSearch::Search(int searchMode, const QString &type, const QString &key, QList<TNStructSearch> &searchResult, const QString &ext)
{
	if (type.isEmpty() || type.length() != 5 || type == "00000")
	{
		return 0;
	}
	QMultiMap<int, TNStructSearch> innerSearch;
	QList<TNStructSearch> innerSearchGroupChat;
	if (type[0] == '1')
	{
		QList<TNStructFriend> friendList;
		TNDataCache::GetInstance()->GetFriendCache(friendList);
		for (QList<TNStructFriend>::iterator feedIter = friendList.begin(); feedIter != friendList.end(); feedIter++)
		{
			if (!searchInReMark(searchMode, 0, key, (*feedIter), innerSearch))
			{
				searchInFriendName(searchMode, 0, key, (*feedIter), innerSearch);
			}
		}
	}
    if (type[1] == '1')
	{
		/*
		需要过滤自己的名片
		*/
		QList<TNStructCompany> companyList;
		TNDataCache::GetInstance()->GetColleagueCache(companyList);
		for (QList<TNStructCompany>::iterator it = companyList.begin(); it != companyList.end(); it++)
		{
			QMap<QString, QMultiMap<int, st_FeedPtr>> feedList = (*it).m_feed;
			for (QMap<QString, QMultiMap<int, st_FeedPtr>>::iterator feedIt = feedList.begin(); feedIt != feedList.end(); feedIt++)
			{
				foreach(st_FeedPtr staffFeed, feedIt.value())
				{
					st_FeedPtr feed = staffFeed;
					if (feed != nullptr)
						searchInName(searchMode, 1, key, feed, (*it).m_belongId, innerSearch);
				}
			}
			QMap<QString, st_FeedPtr> noGroupfeed = (*it).m_noGroupfeed;
			foreach(st_FeedPtr staffFeed, noGroupfeed)
			{
				st_FeedPtr feed = staffFeed;
				if (feed != nullptr)
					searchInName(searchMode, 1, key, feed, (*it).m_belongId, innerSearch);
			}
		}
	}
    if (type[2] == '1')
	{
		QList<TNStructGroup> groupList;
		TNDataCache::GetInstance()->GetGroupCache(groupList);
		for (QList<TNStructGroup>::iterator it = groupList.begin(); it != groupList.end(); it++)
		{
			st_FeedPtr feed = (*it).m_groupFeed;
			if (feed != nullptr)
				searchInName(searchMode, 2, key, feed, (*it).m_belongId, innerSearch);
		}
	}
    if (type[3] == '1')
	{
		QList<TNStructGroupChat> groupChatList;
		TNDataCache::GetInstance()->GetGroupChatCache(groupChatList);
		/*
		添加群聊成员搜索功能 2017.7.10
		*/
		for (QList<TNStructGroupChat>::iterator it = groupChatList.begin(); it != groupChatList.end(); it++)
		{
			st_GroupInfoPtr groupChat = (*it).m_groupChatFeed;
			Q_ASSERT(groupChat!= nullptr);

			if (!searchInGroupChatName(searchMode, 3, key, groupChat, innerSearchGroupChat))
			{
				searchInGroupChatMember(searchMode, 3, key, (*it), innerSearchGroupChat);
			}
		}
	}
	if (type[4] == '1')
	{
		QString myFeed;
		std::vector<toonim::CTNSession> ctn_sessions = TNIMCoreClient::GetDBChat()->getSessions(myFeed.toStdString().c_str(),true);
		for (std::vector<toonim::CTNSession>::iterator it = ctn_sessions.begin();
			it != ctn_sessions.end();it++)
		{
			if ((*it).type == 51)
			{
				searchInNotifyMsg(searchMode, 4, key, (*it).sessionId.c_str(), (*it).avatarId.c_str(), (*it).myFeedId.c_str(), (*it).title.c_str(), innerSearch);
			}
		}
	}
	searchResult.append(innerSearch.values());
	searchResult.append(innerSearchGroupChat);
	//Show all avatar
	return searchResult.size();
}
int TNDataSearch::getSameCount(const QString & feedID, const QList<TNStructSearch> &result)
{
	int count = 0;
	for (TNStructSearch info: result)
	{
		if (info.m_Feed->GetFeedID() == feedID)
			count++;
	}
	return count;
}
void TNDataSearch::calculateSameRecord(QList<TNStructSearch> &result)
{
	QList<TNStructSearch>::iterator it;
	for (it = result.begin(); it != result.end();it++)
	{
		if (it->m_flag == 0 || it->m_flag == 1)
			it->m_count = getSameCount(it->m_Feed->GetFeedID(), result);
	}
}
int TNDataSearch::GetMinIndex(int pyIndex, int nameIndex)
{
	int keyIndex = -1;
	if (pyIndex != -1 && nameIndex != -1)
	{
		keyIndex = pyIndex < nameIndex ? pyIndex : nameIndex;
	}
	else if (pyIndex != -1)
	{
		keyIndex = pyIndex;
	}
	else if (nameIndex != -1)
	{
		keyIndex = nameIndex;
	}
	return keyIndex;
}
bool TNDataSearch::searchInNotifyMsg(int searchMode, int type, const QString &key, const QString &sessionId,
	const QString &avatorId, const QString &belongFeedId, const QString title, QMultiMap<int, TNStructSearch> &result)
{
	bool isHit = false;
	QString name = title;
	QString namePY = TNCHNHelper::GetPinyins(name);
	if (name.isEmpty() || namePY.isEmpty())
	{
		return isHit;
	}
	QString firstNamePY = namePY.left(namePY.indexOf(SPACE_STR));

	if (searchMode == 0)
	{
		baseResult searchResult;
		bool isHit = searchBasePyText(key,name, namePY, searchResult);
		if (isHit && searchResult.hit)
		{
			st_FeedPtr feed = std::make_shared<st_Feed>();
			feed->SetTitle(name);
			feed->SetTitlePinYin(namePY);
			feed->SetFeedID(sessionId);
			feed->SetAvatarID(avatorId);

			TNStructSearch search;
			search.m_hitType = 1;
			search.m_hitString = searchResult.hitString;
			search.m_flag = type;
			search.m_Feed = feed;
			search.m_count = 2;
			search.m_keyIndex = searchResult.hitIndex;
			search.m_belongFeedId = belongFeedId;
			if (firstNamePY == key)
			{
				search.m_keyIndex--;
			}
			result.insert(search.m_keyIndex, search);
			return isHit;
		}
		if (name.contains(key, Qt::CaseInsensitive))
		{
			isHit = true;
			st_FeedPtr feed = std::make_shared<st_Feed>();
			feed->SetTitle(name);
			feed->SetTitlePinYin(namePY);
			feed->SetFeedID(sessionId);
			feed->SetAvatarID(avatorId);

			isHit = true;
			int hitIndex = name.indexOf(key, 0, Qt::CaseInsensitive);

			TNStructSearch search;
			search.m_hitType = 1;
			search.m_hitString = name.mid(hitIndex, key.size());
			search.m_flag = type;
			search.m_Feed = feed;
			search.m_count = 2;
			search.m_keyIndex = hitIndex;
			search.m_belongFeedId = belongFeedId;
			if (firstNamePY == key)
			{
				search.m_keyIndex--;
			}
			result.insert(search.m_keyIndex, search);
			return isHit;
		}
	}
	return isHit;
}
bool TNDataSearch::isMyStaffCard(const QString &feedId)
{
	if (!feedId.startsWith("s_"))
		return false;
	return TNDataCache::GetInstance()->IsInMyStuff(feedId);
}