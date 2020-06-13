#ifndef TNGROUPCHATCREATOR_H
#define TNGROUPCHATCREATOR_H

#include "TNDbUtil.h"
#include "TNMessageListAdapter.h"
#include "TNHttpCreateGroupChat.h"
#include <QObject>

class TNProgressLoading;
class TNGroupChatCreator : public QObject
{
    Q_OBJECT
public:
    explicit TNGroupChatCreator(QObject *parent = 0);

    void createGroupChat(const QString &belongFeedId, QList<TNFriend> selectContacts);

private:
    void stopLoading(const QString& groupId);
    void doStopLoading();

private:
    QStringList m_finishedGroupMemberDBGroupIds;
    QString m_newCreateGroupId;
    TNHttpCreateGroupChat m_httpCreateGroupChat;

    TNProgressLoading *m_progressLoading;
};

#endif // TNGROUPCHATCREATOR_H
