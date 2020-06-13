#include "TNDbUtil.h"

#include "../Common/common_global.h"
#include "TNDataControlServer.h"
#include "TNDataCache.h"

#include <QDate>
#include <QDebug>

TNDbUtil::TNDbUtil()
{
}


TNDbUtil::~TNDbUtil()
{
}

QString TNDbUtil::getRecFilePathFromDB()
{
    TableBaseVec setTables;
    TNDataControlServer::GetInstance()->Query(setTables, "SetUp", "Key", "LocalPath", DBTYPE_USER);
    if (setTables.size() > 0)
    {
        st_SetUpPtr loginItem = std::dynamic_pointer_cast<st_SetUp>(setTables[0]);
        return loginItem->GetValue();
    }

    return QString::null;
}

bool TNDbUtil::IsBootUp()
{
    TableBaseVec setTables;
    TNDataControlServer::GetInstance()->Query(setTables, "SetUp", "Key", "BootUp", DBTYPE_USER);
    if (setTables.size() > 0)
    {
        st_SetUpPtr loginItem = std::dynamic_pointer_cast<st_SetUp>(setTables[0]);
        return loginItem->GetValue() == QString("1");
    }

    return false;
}

void TNDbUtil::SetBootUp(bool yes)
{
    st_SetUpPtr loginItem = std::make_shared<st_SetUp>();
    loginItem->SetKey("BootUp");
    loginItem->SetValue(yes ? QString("1") : QString("0"));
    TNDataControlServer::GetInstance()->InsertDatas(loginItem, DBTYPE_USER);
}

bool TNDbUtil::IsNoDisturbing()
{
    TableBaseVec setTables;
    TNDataControlServer::GetInstance()->Query(setTables, "SetUp", "Key", "NoDisturbing", DBTYPE_USER);
    if (setTables.size() > 0)
    {
        st_SetUpPtr loginItem = std::dynamic_pointer_cast<st_SetUp>(setTables[0]);
        return loginItem->GetValue() == QString("1");
    }

    return false;
}

void TNDbUtil::SetNoDisturbing(bool yes)
{
    st_SetUpPtr loginItem = std::make_shared<st_SetUp>();
    loginItem->SetKey("NoDisturbing");
    loginItem->SetValue(yes ? QString("1") : QString("0"));
    TNDataControlServer::GetInstance()->InsertDatas(loginItem, DBTYPE_USER);
}

bool TNDbUtil::onceUsedPassWordLogin(const QString &strMobile)
{
    TableBaseVec tableBaseVec;
    TNDataControlServer::GetInstance()->GetAllFieldsByTableName("LoginUser", tableBaseVec, DBTYPE_COMMON);
    for (TableBaseVec::iterator iter = tableBaseVec.begin(); iter != tableBaseVec.end(); iter++)
    {
        st_LoginUserPtr record = std::dynamic_pointer_cast<st_LoginUser>(*iter);
        if (record->GetMobile().endsWith(strMobile))
            return true;
    }

    return false;
}

TNFriend TNDbUtil::getFriend(const QString &feedId)
{
    TNFriend aFriend;

    TableBaseVec feedTableBaseVec;
	TNDataControlServer::GetInstance()->Query(feedTableBaseVec, "Feed", "feedId", feedId, DBTYPE_USER);
    Q_ASSERT(feedTableBaseVec.size() == 1);
    for (TableBaseVec::iterator feedIter = feedTableBaseVec.begin(); feedIter != feedTableBaseVec.end(); feedIter++)
    {
        st_FeedPtr feed = std::dynamic_pointer_cast<st_Feed>(*feedIter);
        aFriend = FeedPtrCastToFriend(feed);
    }

    qInfo()<<"TNDbUtil::getFriend result is null. feedId="<<feedId;
    return aFriend;
}

QString TNDbUtil::findBelongToFeedIdInGroup(const QString &groupId)
{
    TableBaseVec tempJoinTableBaseVec;
	TNDataControlServer::GetInstance()->Query(tempJoinTableBaseVec, "JoinStuff", "feedId", groupId, DBTYPE_USER);
    if (tempJoinTableBaseVec.size()>=1)
    {
        st_JoinStuffPtr joinStuff = std::dynamic_pointer_cast<st_JoinStuff>(*tempJoinTableBaseVec.begin());
        return joinStuff->GetBelongTo();
    }

    return QString::null;
}

QList<TNFriend> TNDbUtil::getAllGroupChatMemberCollectionSort(const QString &groupChatId)
{
    QMultiMap<qint64, TNFriend> chatMemberMap; // 目的用于排序，时间戳可能相同
    TableBaseVec tempMyTableBaseVec;
    QMap<QString, QPair<qint64, QString> > allFeedIdToTimeMap;
    TNDataControlServer::GetInstance()->Query(tempMyTableBaseVec, "GroupInfo", "groupId", groupChatId, DBTYPE_USER, DBTYPE_USER);
    if (tempMyTableBaseVec.size() > 0)
    {
        st_GroupInfoPtr groupInfo = std::dynamic_pointer_cast<st_GroupInfo>(tempMyTableBaseVec[0]);
        QString groupId = groupInfo->GetGroupId();
        TableBaseVec groupMemberTableBaseVec;
        TNDataControlServer::GetInstance()->Query(groupMemberTableBaseVec, "GroupMember", "groupId", groupId, DBTYPE_USER);
        for (TableBaseVec::iterator memberIter = groupMemberTableBaseVec.begin(); memberIter != groupMemberTableBaseVec.end(); memberIter++)
        {
            st_GroupMemberPtr groupMember = std::dynamic_pointer_cast<st_GroupMember>(*memberIter);
            allFeedIdToTimeMap.insert(groupMember->GetFeedId(), QPair<qint64, QString>(groupMember->GetTimestamp(), groupMember->GetPermissionType()));
        }

        for (QString feedId : allFeedIdToTimeMap.keys())
        {
            TableBaseVec feedTableBaseVec;
            TNDataControlServer::GetInstance()->Query(feedTableBaseVec, "Feed", "FeedId", feedId, DBTYPE_USER);
            for (TableBaseVec::iterator feedIter = feedTableBaseVec.begin(); feedIter != feedTableBaseVec.end(); feedIter++)
            {
                st_FeedPtr feed = std::dynamic_pointer_cast<st_Feed>(*feedIter);
                if (feed == nullptr)
                    continue;

                TNFriend aFriend = FeedPtrCastToFriend(feed);
                aFriend.m_belongFeedId = groupInfo->GetMyFeedId();

                /*
                获取备注并写入到内存
                */
                TNStructRemark sMark = TNDataCache::GetInstance()->getFriendFeedReMarkWithPY(aFriend.m_friendFeedId, aFriend.m_belongFeedId);
                aFriend.m_remark = sMark.remark;
                aFriend.m_remarkPy = sMark.remarkPy;

                aFriend.permissionType = allFeedIdToTimeMap[aFriend.m_friendFeedId].second;
                if ((aFriend.permissionType == "1") || (aFriend.permissionType == "2"))
                {
                    chatMemberMap.insert(qint64(0), aFriend); // 如果是群主，则时间戳用0，保证其插入在第一位
                }
                else
                {
                    chatMemberMap.insert(allFeedIdToTimeMap[aFriend.m_friendFeedId].first, aFriend);
                }
            }
        }
    }
    //qDebug()<<"chatMemberMap.keys="<<chatMemberMap.keys();
    QList<TNFriend> chatMembers = chatMemberMap.values();
    return chatMembers;
}

void TNDbUtil::operateDBWhenExitGroupChat(const QString &groupChatId)
{
    // 删除并退出群聊
    qDebug()<<"TNDbUtil::operateDBWhenExitGroupChat begin...";
	TNDataControlServer::GetInstance()->DeleteFromTableNameByField("GroupInfo", "groupId", groupChatId, DBTYPE_USER);
    qDebug()<<"TNDbUtil::operateDBWhenExitGroupChat-001...";
	TNDataControlServer::GetInstance()->DeleteFromTableNameByField("GroupMember", "groupId", groupChatId, DBTYPE_USER);
    qDebug()<<"TNDbUtil::operateDBWhenExitGroupChat-002...";
	//消息表需要单独删除处理。
}

bool TNDbUtil::isFriendRelation(const QString &belongFeedId, const QString &feedId)
{
    qDebug() << "TNDbUtil::isFriendRelation-belongFeedId=" << belongFeedId << "-feedId=" << feedId;
    TableBaseVec resTableBaseVec;
    TNDataControlServer::GetInstance()->MultiQuery(resTableBaseVec, "JoinStuff", "belongTo", "feedId", belongFeedId, feedId, DBTYPE_USER);
    if (resTableBaseVec.size()>=1)
    {
        st_JoinStuffPtr joinStuff = std::dynamic_pointer_cast<st_JoinStuff>(*resTableBaseVec.begin());
        if (joinStuff->GetFeedType() == FeedTypeContact)
            return true;
    }

    return false;
}

bool TNDbUtil::isColleageRelation(const QString &belongFeedId, const QString &feedId)
{
    qDebug() << "TNDbUtil::isColleageRelation-belongFeedId=" << belongFeedId << "-feedId=" << feedId;
    TableBaseVec resTableBaseVec;
    TNDataControlServer::GetInstance()->MultiQuery(resTableBaseVec, "JoinStuff", "belongTo", "feedId", belongFeedId, feedId, DBTYPE_USER);
    if (resTableBaseVec.size()>=1)
    {
        st_JoinStuffPtr joinStuff = std::dynamic_pointer_cast<st_JoinStuff>(*resTableBaseVec.begin());
        if (joinStuff->GetFeedType() == FeedTypeOrgStaff)
            return true;
    }

    return false;
}

bool TNDbUtil::isInGroup(const QString &belongFeedId, const QString &feedId)
{
    qDebug() << "TNDbUtil::isInGroup-belongFeedId=" << belongFeedId << "-feedId=" << feedId;
    TableBaseVec resTableBaseVec;
    TNDataControlServer::GetInstance()->MultiQuery(resTableBaseVec, "JoinStuff", "belongTo", "feedId", belongFeedId, feedId, DBTYPE_USER);
    if (resTableBaseVec.size()>=1)
    {
        st_JoinStuffPtr joinStuff = std::dynamic_pointer_cast<st_JoinStuff>(*resTableBaseVec.begin());
        if (joinStuff->GetFeedType() == FeedTypeGroup)
            return true;
    }

    return false;
}

QString TNDbUtil::getMyBelongToFeedId(const QString &feedId)
{
    QString currentBelongFeedId = TNDataCache::GetInstance()->GetCurrentMyFeed();
    if (currentBelongFeedId == AVATAR_ALL_FEED)
    {
        QString belongFeedId;

        // 先从数据库查与 feedId 建立关系的我的 belongFeedId
        TableBaseVec myStuffTableBaseVec;
        TNDataControlServer::GetInstance()->Query(myStuffTableBaseVec, "JoinStuff", "feedId", feedId, DBTYPE_USER);
        if (myStuffTableBaseVec.size()==1)
        {
            // 如果数据库查到只有一张，则用之
            TableBaseVec::iterator iter = myStuffTableBaseVec.begin();
            st_JoinStuffPtr myStuff = std::dynamic_pointer_cast<st_JoinStuff>(*iter);
            belongFeedId = myStuff->GetBelongTo();
        }
        else if (myStuffTableBaseVec.size()>1)
        {
            // 如果有多于一张，则用个人名片的第一张
            for (TableBaseVec::iterator iter = myStuffTableBaseVec.begin(); iter != myStuffTableBaseVec.end(); iter++)
            {
                st_JoinStuffPtr myStuff = std::dynamic_pointer_cast<st_JoinStuff>(*iter);
                if (myStuff->GetBelongTo().startsWith("c_"))
                {
                    belongFeedId = myStuff->GetBelongTo();
                    break;
                }
            }
            // 如果建立关系的多张名片中没有个人名片，则使用第一张
            if (belongFeedId.isEmpty())
            {
                st_JoinStuffPtr myStuff = std::dynamic_pointer_cast<st_JoinStuff>(*(myStuffTableBaseVec.begin()));
                if (myStuff)
                    belongFeedId = myStuff->GetBelongTo();
            }
        }

        // 如果数据库查不到 belongFeedId 则使用个人名片的第一张
        if (belongFeedId.isEmpty())
        {
            st_FeedPtr selfFeed = TNDataCache::GetInstance()->getMyFirstPersonalCard();
            if (selfFeed)
                belongFeedId = selfFeed->GetFeedID();
        }

        qDebug()<<"getMyBelongToFeedId-belongFeedId="<<belongFeedId;
        Q_ASSERT(!belongFeedId.isEmpty());
        return belongFeedId;
    }
    else
    {
        return currentBelongFeedId;
    }
}

st_GroupInfoPtr TNDbUtil::getGroupChatInfo(const QString &groupChatId)
{
    TableBaseVec groupTableBaseVec;
	TNDataControlServer::GetInstance()->Query(groupTableBaseVec, "GroupInfo", "groupId", groupChatId, DBTYPE_USER);
    if (groupTableBaseVec.size() != 0)
    {
        st_GroupInfoPtr groupInfo = std::dynamic_pointer_cast<st_GroupInfo>(*groupTableBaseVec.begin());
        return groupInfo;
    }

    // 如果是新加入的群聊并立即调用（发起群聊会话时）该函数，则可能出现还没有更新数据的情况，则返回空
    return st_GroupInfoPtr();
}

bool TNDbUtil::isInGroupChat(const QString &groupChatId, const QString &feedId)
{
    QList<TNFriend> results = TNDataCache::GetInstance()->GetGroupChatMemberCache(groupChatId);
    foreach (const TNFriend &var, results)
    {
        if (var.m_friendFeedId == feedId)
            return true;
    }

    return false;
}

QString TNDbUtil::findBelongToFeedIdInGroupChat(const QString &groupChatId)
{
    QList<TNFriend> members = TNDataCache::GetInstance()->GetGroupChatMemberCache(groupChatId);
    QStringList memberFeeds;
    foreach(const TNFriend &member, members)
    {
        memberFeeds.append(member.m_friendFeedId);
    }

    QList<MineCard> cards = TNDbUtil::getMineCards();
    foreach(const MineCard &card, cards)
    {
        if (memberFeeds.contains(card.m_feedId))
            return card.m_feedId;
    }

    return QString::null;
}

QList<MineCard> TNDbUtil::getMineCards(bool includeGroup)
{
    QList<MineCard> results;

    TableBaseVec myStuffTableBaseVec;
	TNDataControlServer::GetInstance()->GetAllFieldsByTableName("MyStuff", myStuffTableBaseVec, DBTYPE_USER);
    for (TableBaseVec::iterator iter = myStuffTableBaseVec.begin(); iter != myStuffTableBaseVec.end(); iter++)
    {
        st_MyStuffPtr myStuffRecord = std::dynamic_pointer_cast<st_MyStuff>(*iter);
        // TODO: 这里应该要将 FeedType==3 剔除
        if (!includeGroup && (myStuffRecord->GetFeedType() == FeedTypeGroup))
            continue;

        TableBaseVec feedTableBaseVec;
		TNDataControlServer::GetInstance()->Query(feedTableBaseVec, "Feed", "feedId", myStuffRecord->GetFeedID(),DBTYPE_USER);
        if (feedTableBaseVec.size() != 1)
        {
            //Q_ASSERT(!"never come to here"); // 线上服务器数据 企通科技 有问题
            continue;
        }
        st_FeedPtr feedRecord = std::dynamic_pointer_cast<st_Feed>(*feedTableBaseVec.begin());
        MineCard aMineCard;

        aMineCard.m_userId = feedRecord->GetUserID();
        aMineCard.m_feedId = feedRecord->GetFeedID();
        aMineCard.m_nickName = feedRecord->GetTitle();
        aMineCard.m_avatarURL = feedRecord->GetAvatarID();

        results.append(aMineCard);
    }

    return results;
}

QString TNDbUtil::getCompanyFeedId(const QString &companyId)
{
    TableBaseVec companyInfoVec;
    TNDataControlServer::GetInstance()->Query(companyInfoVec, "CompanyInfo", "comId", companyId, DBTYPE_USER);
    if (companyInfoVec.size() == 0)
    {
        return QString::null;
    }
    st_CompanyInfoPtr cominfo = std::dynamic_pointer_cast<st_CompanyInfo>(companyInfoVec[0]);
    QString companyFeedId = cominfo->getComFeedId();

    return companyFeedId;
}

TNFriend TNDbUtil::FeedPtrCastToFriend(const st_FeedPtr &feedInfo)
{
    TNFriend aFriend;

    aFriend.m_pinYin = feedInfo->GetTitlePinYin();
    aFriend.m_gender = feedInfo->GetSex();
    //aFriend.m_belongFeedId = belongFeedId;
    aFriend.m_userId = feedInfo->GetUserID();
    const QString birthStr(feedInfo->GetBirthday());
    if (birthStr.isNull() || birthStr.isEmpty())
    {
        aFriend.m_age = -1;
    }
    else
    {
        QDate birthDate(QDate::fromString(birthStr, Qt::ISODate));
        int mouth = QDate::currentDate().month() - birthDate.month();
        if (mouth<0)
            aFriend.m_age = QDate::currentDate().year() - birthDate.year() - 1;
        else
            aFriend.m_age = QDate::currentDate().year() - birthDate.year();
    }

    QString tag = feedInfo->GetTag();
    if (!tag.isEmpty())
    {
        QStringList friendTags = tag.split(",");
        aFriend.m_tags = friendTags;
    }

    aFriend.m_nickName = feedInfo->GetTitle();
    aFriend.m_subTitle = feedInfo->GetSubTile();
    aFriend.m_friendFeedId = feedInfo->GetFeedID();

    aFriend.m_avatarURL = feedInfo->GetAvatarID();
    //aFriend.m_avatarResourceFile = ;

    return aFriend;
}
