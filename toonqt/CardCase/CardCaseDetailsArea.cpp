#include <QJsonArray>
#include <qjsondocument.h>
#include <QJsonObject>
#include "CardCaseDetailsArea.h"
#include "Friend/TNCardCaseListAdapter.h"

#include "TNHttpApi.h"
#include "Colleague/TNStaffItem.h"
#include "TNDbUtil.h"
#include "TNIMCoreClient.h"
#include "TNSimpleBrowser.h"
#include "TNNameSpace.h"
#include "TNDataCache.h"
#include "TNIMCoreClient.h"
#include "tnnotifycenter.h"
#include "TNUserDataHelper.h"
#include "TNDataControlServer.h"
#include "TNNewFriendUtil.h"
#include "Group/TNCardCaseGroupAdapter.h"
#include "GroupChat/TNCardCaseGroupChatAdapter.h"

CardCaseDetailsArea::CardCaseDetailsArea(int id, TNPluginParamPtr pluginParam, QWidget *parent)
: TNWebViewDetailsArea(id, pluginParam, parent)
{
    setCurrentPage(2);

    TNNotifyCenter::instance()->connnectNotifyCreateToChat(this);
    TNNotifyCenter::instance()->connectNotifyReMarkUpdate(this);
    TNDataCache::GetInstance()->InstallCatcheFeedUpdateNotify(this);
}

CardCaseDetailsArea::~CardCaseDetailsArea()
{

}

void CardCaseDetailsArea::slotShowNewFriendNotice()
{
    setCurrentPage(0);

    QList<st_NewFriendPtr> newFriendList = TNNewFriendUtil::getNewFriendList();
    QJsonObject json;
    QJsonArray jsonArray;
    foreach (const st_NewFriendPtr &aNewFriend, newFriendList)
    {
        QString friendFeedId = aNewFriend->getFeedID();
        st_FeedPtr friendFeedInfo;
        QString friendUserId;
        QString friendFeedName;
        QString friendAvatarUrl;
        TNUserDataHelper::GetInstance()->GetFeedInfo(friendFeedId, friendFeedInfo);
        if (friendFeedInfo)
        {
            friendUserId = friendFeedInfo->GetUserID();
            friendFeedName = friendFeedInfo->GetTitle();
            friendAvatarUrl = friendFeedInfo->GetAvatarID();
        }

        Q_ASSERT(!friendFeedId.isEmpty());
        QJsonObject aNewFriendNotice;
        aNewFriendNotice.insert("friendUserId", friendUserId);
        aNewFriendNotice.insert("friendFeedId", friendFeedId);
        aNewFriendNotice.insert("friendFeedName", friendFeedName);
        aNewFriendNotice.insert("friendAvatarUrl", friendAvatarUrl);
        aNewFriendNotice.insert("friendApplyContent", aNewFriend->getAddComment());

        QString mineFeedId = aNewFriend->getMyFeedID();
        st_FeedPtr mineFeedInfo;
        QString mineFeedName;
        QString mineAvatarURL;
        TNUserDataHelper::GetInstance()->GetFeedInfo(mineFeedId, mineFeedInfo);
        if (mineFeedInfo)
        {
            mineFeedName  = mineFeedInfo->GetTitle();
            mineAvatarURL = mineFeedInfo->GetAvatarID();
        }
        aNewFriendNotice.insert("mineFeedId", mineFeedId);
        aNewFriendNotice.insert("mineFeedName", mineFeedName);
        aNewFriendNotice.insert("mineAvatarUrl", mineAvatarURL);
        aNewFriendNotice.insert("mobilePhone", aNewFriend->getMobilePhone());

        TN::NewFriendStatus newFriendStatus = TN::Accepting;
        if (aNewFriend->getStatus() == QStringLiteral("1"))
            newFriendStatus = TN::Exchanged;
        aNewFriendNotice.insert("newFriendStatus", newFriendStatus);

        aNewFriendNotice.insert("applyTime", aNewFriend->getApplyTime());
        aNewFriendNotice.insert("expireTime", aNewFriend->getExpireTime());

        jsonArray.append(aNewFriendNotice);
    }
    json.insert("newFriendList", jsonArray);

    showNewFriendH5(json);
}

void CardCaseDetailsArea::OnListAreaClickedSlot(const QModelIndex & index)
{
    setCurrentPage(1);

	TNCardCaseListAdapter *adapter = (TNCardCaseListAdapter*)index.data().toLongLong();
	if ((adapter == NULL) || (adapter->getType() == TNCardCaseListAdapter::FriendLetter))
		return ;

    m_currentFeedId = adapter->getDialogID();
	setTitleNameLabel(adapter->getName());

	const QString feedId = adapter->getDialogID();
	const QString belongFeedId = adapter->getBelongFeedId();        
    showFrameH5(feedId, belongFeedId);
}

void CardCaseDetailsArea::OnColleagueListAreaSlot(const QModelIndex & index)
{
    setCurrentPage(1);

	TNStaffItem *adapter = static_cast<TNStaffItem*>(index.internalPointer());
	if (adapter == NULL || adapter->getItemGrade() != TNStaffItem::Staff)
		return;

    m_currentFeedId = adapter->getDialogID();
	setTitleNameLabel(adapter->getTitle());   

    const QString feedId = adapter->getDialogID();
    const QString belongId = adapter->getBelongFeedId();
    showFrameH5(feedId, belongId);
}

void CardCaseDetailsArea::OnGroupListAreaSlot(const QModelIndex & index)
{
    setCurrentPage(1);

	TNCardCaseGroupAdapter * adapter = (TNCardCaseGroupAdapter*)index.data().toLongLong();
	if ((adapter == NULL))
		return;

    m_currentFeedId = adapter->getGroupId();
	setTitleNameLabel(adapter->getTitle());

	const QString feedId = adapter->getGroupId();
    const QString belongId = adapter->getBelongFeedId();
    showFrameH5(feedId, belongId);
}

void CardCaseDetailsArea::OnGroupChatListAreaSlot(const QModelIndex & index)
{
    setCurrentPage(1);

	TNCardCaseGroupChatAdapter * adapter = (TNCardCaseGroupChatAdapter*)index.data().toLongLong();
	if (adapter == NULL)
		return;

    m_currentFeedId = adapter->getGroupChatId();

    showGroupChatInfo(adapter);
}

void CardCaseDetailsArea::slotModifiedGroupChatInfos(const QModelIndex &index)
{
	TNCardCaseGroupChatAdapter * adapter = (TNCardCaseGroupChatAdapter*)index.data().toLongLong();
    if (adapter == NULL)
        return;

    if (m_currentFeedId == adapter->getGroupChatId())
    {
        showGroupChatInfo(adapter);
    }
}

void CardCaseDetailsArea::on_notifyReMarkUpdate(const QString &from, const QString &to, const QString &remark, int sources)
{
    if (m_currentFeedId == from)
    {
        if (!remark.isEmpty())
        {
            setTitleNameLabel(remark);
        }
        else
        {
            st_FeedPtr friendFeedInfo;
            TNUserDataHelper::GetInstance()->GetFeedInfo(m_currentFeedId, friendFeedInfo);
            if (friendFeedInfo)
            {
                setTitleNameLabel(friendFeedInfo->GetTitle());
            }
        }
    }
}

void CardCaseDetailsArea::feedCardUpdateFromCatche(const QString &feedId,
                                                   const QString &avatarId,
                                                   const QString &name,
                                                   const QString &subName,
                                                   const QString &userId,
                                                   const QString &namePy,
                                                   int sourceType)
{
    Q_UNUSED(avatarId);
    Q_UNUSED(subName);
    Q_UNUSED(userId);
    Q_UNUSED(namePy);
    Q_UNUSED(sourceType);
    if (m_currentFeedId == feedId)
        setTitleNameLabel(name);
}

void CardCaseDetailsArea::showGroupChatInfo(TNCardCaseGroupChatAdapter *adapter)
{
    setTitleNameLabel(adapter->getTitle());

    const QString feedId = adapter->getGroupChatId();
    const QString belongId = adapter->getBelongFeedId();
    showFrameH5(feedId, belongId);
}
