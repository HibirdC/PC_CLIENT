#include "TNGroupChatCreator.h"

#include "TNUtil.h"
#include "tnnotifycenter.h"
#include "TNIMCoreClient.h"
#include "TNUserDataHelper.h"
#include "TNMessageBox.h"
#include "TNProgressLoading.h"
#include "SelectContactDialog.h"
#include "TNInputGroupChatNameDialog.h"
#include "TNDataCache.h"
#include "common_global.h"
#include "TNChooseCardDialog.h"
#include "TNDataControlServer.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QApplication>

TNGroupChatCreator::TNGroupChatCreator(QObject *parent) : QObject(parent)
{
    m_progressLoading = new TNProgressLoading(TNUtil::getMainWidget());
}

void TNGroupChatCreator::stopLoading(const QString& groupId)
{
    if (groupId.startsWith("gc_"))
    {
        m_finishedGroupMemberDBGroupIds.append(groupId);
        doStopLoading();
    }
}

void TNGroupChatCreator::doStopLoading()
{
    if (m_finishedGroupMemberDBGroupIds.contains(m_newCreateGroupId))
    {
        m_progressLoading->stop();
        m_finishedGroupMemberDBGroupIds.clear();
        m_newCreateGroupId = QString::null;
    }
}

void TNGroupChatCreator::createGroupChat(const QString &belongFeedId, QList<TNFriend> selectContacts)
{
    qInfo()<<"[TNMVD][TNGroupChatCreator]createGroupChat begin...";

    // 加入我
    TNFriend mySelf = TNDbUtil::getFriend(belongFeedId);
    selectContacts.prepend(mySelf);

    QString feedId = mySelf.m_friendFeedId;
    QString feedAvatartId = mySelf.m_avatarURL;
    QString feedTitle = mySelf.m_nickName;
    m_httpCreateGroupChat.SetCreateFeed(feedAvatartId, feedId, feedTitle);

    for (int i = 0; i < selectContacts.size(); i++)
    {
        QString memberAvatartId = selectContacts.at(i).m_avatarURL;
        QString memberFeedId = selectContacts.at(i).m_friendFeedId;
        QString memberFeedTitle = selectContacts.at(i).m_nickName;
        QString userId = selectContacts.at(i).m_userId;
        m_httpCreateGroupChat.AddGroupMember(memberAvatartId, memberFeedId, memberFeedTitle, userId);
    }

    auto writeGroupChatInfoDB = [&](bool success, QString cBelongFeedId, QJsonObject jsonObject)
    {
        qInfo()<<"[TNMVD][TNGroupChatCreator]createGroupChat-callback begin...";
        if (success)
        {
            QString debugText = QJsonDocument(jsonObject).toJson();
            qInfo()<<"[TNMVD][TNGroupChatCreator]createGroupChat-debugText="<<debugText;
            int retCode = jsonObject["meta"].toObject().value("code").toInt();
            if (retCode == 0)
            {
                QVariantMap mapResp = jsonObject.toVariantMap();
                QVariant metaInfo = mapResp["meta"];
                QVariantMap metaInfoMap = metaInfo.toMap();

                QVariant groupInfo = mapResp["data"];
                QVariantMap mapGroup = groupInfo.toMap();
                int maxNum = mapGroup["maxNum"].toInt();
                int currNum = mapGroup["currNum"].toInt();
                int disturbStatus = mapGroup["disturbStatus"].toInt();
                int groupType = mapGroup["groupType"].toInt();
                QString topic = mapGroup["topic"].toString();
                QString groupchatId = topic; // 使用topic
                QString groupChatName = mapGroup["groupChatName"].toString();
                QString createFeedId = mapGroup["creatorFeedId"].toString();
                QString myFeedId = mapGroup["myFeedId"].toString();
                QString groupChatHeadImage = mapGroup["groupChatHeadImage"].toString();

                Q_ASSERT(groupchatId.startsWith("gc_"));

                st_GroupInfoPtr stGroupInfo = std::make_shared<st_GroupInfo>();
                stGroupInfo->SetCreatorFeedId(createFeedId);
                stGroupInfo->SetCurrNum(currNum);
                stGroupInfo->SetDisturbStatus(disturbStatus);
                stGroupInfo->SetGroupId(groupchatId);
                stGroupInfo->SetHeaderImage(groupChatHeadImage);
                stGroupInfo->SetMaxNum(maxNum);
                stGroupInfo->SetMyFeedId(myFeedId);
                stGroupInfo->SetName(groupChatName);
                stGroupInfo->SetTopic(topic);
                TNDataControlServer::GetInstance()->InsertDatas(stGroupInfo, DBTYPE_USER);

                // 通知左侧会话列表新建session
                QString from = cBelongFeedId;
                QString to   = groupchatId;
                QString sessionId = TNIMCoreClient::GetSessionId(from, to, MSG_BIZ_GROUPCHAT);
                TNMessageListAdapter session(sessionId, MSG_BIZ_GROUPCHAT);
                session.setAvatarPhotoUrl(groupChatHeadImage);
                session.setMyFeedId(from);
                session.setToFeed(to);
                session.setName(groupChatName);
                session.setTime(QDateTime::currentDateTime().toTime_t());

                TNNotifyCenter::instance()->postNotifyCreateGroupChatFinished(session);

                m_newCreateGroupId = groupchatId;
                doStopLoading();
            }
            else
            {
                QString content = jsonObject.value("meta").toObject().value("message").toString();
                qInfo() << "[TNMVD][TNGroupChatCreator]createGroupChat failed. retCode=" << retCode << " content=" << content;
                TNMessageBox messageBox(QApplication::activeWindow());
                messageBox.setMsg(content);
                messageBox.exec();
            }
        }
        else
        {
            TNMessageBox messageBox(QApplication::activeWindow());
            messageBox.setMsg(("操作失败，请检查您的网络状态"));
            messageBox.exec();
        }
        qInfo()<<"[TNMVD][TNGroupChatCreator]createGroupChat-callback end.";
    };

    m_httpCreateGroupChat.requestCreateGroupChat(writeGroupChatInfoDB, TNUserDataHelper::GetInstance()->_pluginParam, belongFeedId);
    m_progressLoading->start();
    qInfo()<<"[TNMVD][TNGroupChatCreator]createGroupChat end.";
}
