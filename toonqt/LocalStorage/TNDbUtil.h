#ifndef TNDBUTIL_H
#define TNDBUTIL_H

#include "localstorage_global.h"
#include "LocalStorageCommon.h"

#include <QMap>
#include <QPair>
#include <QList>
#include <QString>
#include <QStringList>
#include <QVariant>

struct LOCALSTORAGE_EXPORT TNStructSearch
{
	int m_hitType;
	int m_keyIndex; // 搜索关键字在搜索结果中的索引
	int m_count; //记录相同的个数
	int m_flag;
	QString m_extString; //好友：备注   群聊：包含的成员名 与m_hitType 配合使用
	QString m_hitString; //搜索hit 关键字
    QString m_belongFeedId;
    st_FeedPtr m_Feed;
};

struct LOCALSTORAGE_EXPORT TNStructCompany
{
    QString m_companyId;
    QString m_companyFeedId;
    QString m_companyName;
    QString m_companyUrl;
    QString m_companyLogoText;
    QString m_belongId;
    QString m_companyAddr;
    QString m_companyTel;
    QString m_companyEmail;
    QString m_currentMyStaff;
	QString m_orgCommunicationStatus;
    QMap<QString,st_FeedPtr> m_noGroupfeed;
    QMultiMap<int, QString> m_groupList; // Key: OrderValue Value: 部门Name
    QString m_photoRes;
    QMap<QString, QMultiMap<int, st_FeedPtr>> m_feed; //<部门名字，成员>
};

Q_DECLARE_METATYPE(TNStructCompany)

struct LOCALSTORAGE_EXPORT TNStructGroup
{
    int m_flag; //0 我创建的 1 我加入的
    int m_memberCount;
    QString m_belongId;
    st_FeedPtr m_groupFeed;
};

Q_DECLARE_METATYPE(TNStructGroup)
Q_DECLARE_METATYPE(QList<TNStructGroup>)

struct LOCALSTORAGE_EXPORT TNStructRemark
{
	QString remark;
	QString remarkPy;
};
Q_DECLARE_METATYPE(TNStructRemark)

struct LOCALSTORAGE_EXPORT TNFriend
{
    TNFriend() : m_age(-1) { }

    QString m_nickName;
    QString m_pinYin;
    QString m_avatarURL;
    QString m_avatarResourceFile;
    QString m_subTitle;
    QString m_gender;
    int m_age;
    QStringList m_tags;

    QString permissionType;

	QString m_remark;
	QString m_remarkPy;
    QString m_userId;
    QString m_belongFeedId; // 我的名片ID
    QString m_friendFeedId; // 好友的名片ID
};

Q_DECLARE_METATYPE(TNFriend)
Q_DECLARE_METATYPE(QList<TNFriend>)


struct LOCALSTORAGE_EXPORT TNStructGroupChat
{
    int m_flag;
    int m_memberCount;
    QList<TNFriend> m_groupMember;
    st_GroupInfoPtr m_groupChatFeed;
};

Q_DECLARE_METATYPE(TNStructGroupChat)
Q_DECLARE_METATYPE(QList<TNStructGroupChat>)

struct LOCALSTORAGE_EXPORT TNStructFriend
{
	int dupCount;
	QString remark;
	QString remarkpy;
    QString m_belongFeedId;
    st_FeedPtr m_Feed;
};

Q_DECLARE_METATYPE(TNStructFriend)

struct LOCALSTORAGE_EXPORT MineCard
{
    QString m_userId;
    QString m_feedId;
    QString m_nickName;
    QString m_avatarURL;
};

Q_DECLARE_METATYPE(MineCard)

class LOCALSTORAGE_EXPORT TNDbUtil
{
public:
    TNDbUtil();
    ~TNDbUtil();

    static QString getRecFilePathFromDB();

    static bool IsBootUp();
    static void SetBootUp(bool yes);

    static bool IsNoDisturbing();
    static void SetNoDisturbing(bool yes);

    static bool onceUsedPassWordLogin(const QString &strMobile);

    static TNFriend getFriend(const QString &feedId); // 不推荐再使用了， 而应该使用[TNUserDataHelper::GetFeedInfo()]

    // 关系
    static bool isFriendRelation(const QString &belongFeedId, const QString &feedId);
    static bool isColleageRelation(const QString &belongFeedId, const QString &feedId);
    static bool isInGroup(const QString &belongFeedId, const QString &feedId);

    static QString getMyBelongToFeedId(const QString &feedId);

    // 群组
    static QString findBelongToFeedIdInGroup(const QString &groupId);

    // 群聊
    static st_GroupInfoPtr getGroupChatInfo(const QString &groupChatId); // 不推荐再使用了， 而应该使用[TNUserDataHelper::GetGroupInfo()]
    static bool isInGroupChat(const QString &groupChatId, const QString &feedId);
    static QString findBelongToFeedIdInGroupChat(const QString &groupChatId);
    static QList<TNFriend> getAllGroupChatMemberCollectionSort(const QString &groupChatId);
    static void operateDBWhenExitGroupChat(const QString &groupChatId);

    static QString getCompanyFeedId(const QString &companyId);

private:
    static QList<MineCard> getMineCards(bool includeGroup = false);
    static TNFriend FeedPtrCastToFriend(const st_FeedPtr &feedInfo);
};

#endif // TNDBUTIL_H
