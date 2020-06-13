#include "TNInitiateGroupChatCommand.h"

#include <QDebug>
#include <QFileDialog>
#include <QApplication>

#include "TNDbUtil.h"
#include "TNDataCache.h"
#include "TNUserDataHelper.h"
#include "TNJoinGroupChatConfirmDialog.h"

TNInitiateGroupChatCommand::TNInitiateGroupChatCommand(QObject *parent) : TNAbstractToonCommand(parent)
{

}

TNInitiateGroupChatCommand::~TNInitiateGroupChatCommand()
{

}

QJsonObject TNInitiateGroupChatCommand::executeToonCommand(const QJsonObject &inJsonData)
{
    QJsonObject outJsonResult;

    if (inJsonData.contains("myFeedId") && inJsonData.contains("groupChatId")  && inJsonData.contains("groupId"))
    {
        QString creatorFeedId = inJsonData["myFeedId"].toString();
        QString groupChatId  = inJsonData["groupChatId"].toString();
        if (!groupChatId.startsWith("gc_"))
            groupChatId = QString("gc_") + groupChatId;

        QString belongFeedId = TNDbUtil::findBelongToFeedIdInGroupChat(groupChatId);
        if (!belongFeedId.isEmpty())
        { // 说明我在该群聊里
            emit sigInitiateGroupChat(belongFeedId, groupChatId);
        }
        else
        { // 我所有名片都不在群聊里
            const QString groupId = inJsonData["groupId"].toString();
            st_FeedPtr selfFeed;
            QString belongFeedIdInGroup = TNDbUtil::findBelongToFeedIdInGroup(groupId);
            if (!belongFeedIdInGroup.isEmpty())
            {
                QList<st_FeedPtr> myStuff;
                TNDataCache::GetInstance()->getMyStuff(myStuff, belongFeedIdInGroup);
                if (myStuff.size() > 0)
                    selfFeed = myStuff.first();
            }
            else
            {
                selfFeed = TNDataCache::GetInstance()->getMyFirstPersonalCard();
            }
            if (!selfFeed)
            {
                qInfo()<<"[Notice][TNInitiateGroupChatCommand]error! selfFeed is null?";
                Q_ASSERT(!"error! selfFeed is null?");
                return outJsonResult;
            }

            st_GroupInfo groupChatInfo;
            TNUserDataHelper::GetInstance()->GetGroupInfo(groupChatId, groupChatInfo);

            TNJoinGroupChatConfirmDialog dialog(selfFeed, groupChatInfo, QApplication::activeWindow());
            if (dialog.exec() == QDialog::Accepted)
            {
                // 加入群聊
                QList<TNFriend> selectContacts;
                TNFriend aFriend;
                aFriend.m_userId = selfFeed->GetUserID();
                aFriend.m_friendFeedId = selfFeed->GetFeedID();
                aFriend.m_nickName = selfFeed->GetTitle();
                aFriend.m_avatarURL = selfFeed->GetAvatarID();
                selectContacts.append(aFriend);

                activeJoinToGroupChat(selectContacts, groupChatId);
            }
            else
            {
                return outJsonResult;
            }
        }
    }
    else
    {
        DefaultToonCommand::defaultToonProtocolTipBox();
    }

    return outJsonResult;
}

void TNInitiateGroupChatCommand::activeJoinToGroupChat(const QList<TNFriend> &selectContacts, const QString &groupChatId)
{
    if (selectContacts.isEmpty())
        return;

    // 主动加入
    qInfo()<<"[Notice][TNInitiateGroupChatCommand]activeJoinToGroupChat begin...";
    m_belongFeedId = selectContacts.first().m_friendFeedId;
    m_groupChatId  = groupChatId;
    INVIT_SOURCE type = SOUCE_TYPE_ACTICE;
    QString title = selectContacts.first().m_nickName;
    m_httpAddGroupChatMember.setAddGroupChatInfo(m_belongFeedId, title, m_groupChatId, type);

    for (int i = 0; i < selectContacts.size(); i++)
    {
        QString memberAvatartId = selectContacts.at(i).m_avatarURL;
        QString memberFeedId = selectContacts.at(i).m_friendFeedId;
        QString memberFeedTitle = selectContacts.at(i).m_nickName;
        QString userId = selectContacts.at(i).m_userId;
        m_httpAddGroupChatMember.addGroupMember(userId, memberFeedId, memberFeedTitle, memberAvatartId);
    }

    auto writeGroupChatMemberDB = [&](bool success, QJsonObject jsonObject, QStringList memberNames)
    {
        qInfo()<<"[Notice][TNInitiateGroupChatCommand]activeJoinToGroupChat-callback begin...";
        if (success)
        {
            QString debugText = QJsonDocument(jsonObject).toJson();
            qInfo()<<"[Notice][TNInitiateGroupChatCommand]writeGroupChatMemberDB-debugText="<<debugText;
            int retCode = jsonObject["meta"].toObject().value("code").toInt();
            if (retCode == 0)
            {
                qInfo() << "activeJoinToGroupChat success.";
                emit sigInitiateGroupChat(m_belongFeedId, m_groupChatId);
            }
            else
            {
                //QString content = jsonObject.value("meta").toObject().value("message").toString();
                QString content(("操作失败"));
                if (retCode == 118006)
                {
                    content = ("超过群聊最大人数限制");
                }
                if (retCode == 118007)
                {
                    Q_ASSERT(!"因多名片规则限制,无法加入群聊-此情况在此应该不存在！");
                }

                qInfo() << "activeJoinToGroupChat failed. retCode=" << retCode << " content=" << content;
                TNMessageBox messageBox(QApplication::activeWindow());
                messageBox.setMsg(content);
                messageBox.exec();
            }
        }
        qInfo()<<"[Notice][TNInitiateGroupChatCommand]activeJoinToGroupChat-callback end.";
    };

    QStringList contactNames;
    foreach (const TNFriend &aContact, selectContacts)
    {
        contactNames.append(aContact.m_nickName);
    }
    m_httpAddGroupChatMember.requestAddGroupChatMember(writeGroupChatMemberDB, TNUserDataHelper::GetInstance()->_pluginParam, contactNames);
    qInfo()<<"[Notice][TNInitiateGroupChatCommand]activeJoinToGroupChat end.";
}
