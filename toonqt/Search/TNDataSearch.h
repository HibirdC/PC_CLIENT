#pragma once

#include "localstorage_global.h"
#include "LocalStorageCommon.h"
#include "TNDbUtil.h"
#include "TNCHNHelper.h"

#include <QUrlQuery>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QMap>
#include <QEventLoop>
#include <QMargins>
#include <QMutex>

#include "search_global.h"

class SEARCH_EXPORT TNDataSearch
{
public:
	TNDataSearch();
	~TNDataSearch();
	static TNDataSearch* GetInstance();
	/*************************************************
	Function:       Search
	Description:    全局搜索 好友，同事，群聊，群组
	Input:          searchMode 搜索方式： 1： 精确搜索  0：泛型搜索（contain）
					type 搜索模块:  被搜索的模块为1 搜索，0 不搜索 。 如 1111 全部搜索 1000 仅搜索好友 ......以此类推
					key: 搜索的值
					searchResult 结果输出结果 
					ext 扩展参数
					2018.1.24 支持搜索消息通知
	Output:         QList<TNStructSearch>
	Return:			结果的数量
	Others:         
	*************************************************/
	int Search(int searchMode, const QString &type, const QString &key, QList<TNStructSearch> &searchResult, const QString &ext = "");

private:

	struct baseResult
	{
		bool hit;
		int hitIndex;
		QString hitString;
	};

	QMutex _mutex;
	static TNDataSearch* _Instance;
	void calculateSameRecord(QList<TNStructSearch> &result);
	int getSameCount(const QString & feedID, const QList<TNStructSearch> &result);
	int GetMinIndex(int pyIndex,int nameIndex);
	bool searchInFriendName(int searchMode, int type, const QString &key, TNStructFriend friendInfo, QMultiMap<int, TNStructSearch> &result);
	bool searchInReMark(int searchMode, int type, const QString &key,TNStructFriend friendInfo, QMultiMap<int, TNStructSearch> &result);
	bool searchInName(int searchMode, int type, const QString &key, st_FeedPtr feed, const QString &belongId, QMultiMap<int, TNStructSearch> &result);
	bool searchInGroupChatName(int searchMode, int type, const QString &key, st_GroupInfoPtr groupChat, QList<TNStructSearch> &result);
	bool searchInGroupChatMember(int searchMode, int type, const QString &key, TNStructGroupChat groupChatInfo, QList<TNStructSearch> &result);
	bool hitInGroupChatMember(int searchMode, int type, const QString &key, const QString &name,const QString &namePy, 
		TNStructGroupChat groupChatInfo, QList<TNStructSearch> &result);
	bool searchInNotifyMsg(int searchMode, int type, const QString &key,const QString &sessionId,
		const QString &avatorId,const QString &belongFeedId,const QString title, QMultiMap<int, TNStructSearch> &result);
	bool searchBasePyText(QString key, QString text, QString originalTextPy, baseResult &result);
	bool isMyStaffCard(const QString &feedId);
};
