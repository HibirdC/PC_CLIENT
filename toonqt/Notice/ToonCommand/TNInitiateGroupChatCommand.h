#ifndef TNINITIATEGROUPCHATCOMMAND_H
#define TNINITIATEGROUPCHATCOMMAND_H

#include "TNAbstractToonCommand.h"

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonDocument>

#include "TNHttpAddGroupChatMember.h"
#include "TNDbUtil.h"

class TNInitiateGroupChatCommand : public TNAbstractToonCommand
{
    Q_OBJECT

public:
    explicit TNInitiateGroupChatCommand(QObject *parent = Q_NULLPTR);
    ~TNInitiateGroupChatCommand();

    virtual QJsonObject executeToonCommand(const QJsonObject &inJsonData);

signals:
    void sigInitiateGroupChat(const QString &belongFeedId, const QString &groupChatId);

private:
    void activeJoinToGroupChat(const QList<TNFriend> &selectContacts, const QString &groupChatId);
    TNHttpAddGroupChatMember m_httpAddGroupChatMember;
    QString m_belongFeedId;
    QString m_groupChatId;
};


#endif // TNINITIATEGROUPCHATCOMMAND_H

