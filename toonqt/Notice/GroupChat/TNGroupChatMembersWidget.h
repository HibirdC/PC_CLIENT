#ifndef TNGROUPCHATMEMBERSWIDGET_H
#define TNGROUPCHATMEMBERSWIDGET_H

#include <QWidget>
#include <QToolButton>
#include <QLineEdit>

#include "TNDbUtil.h"
#include "TNHttpApi.h"
#include "TNHttpCloudApi.h"
#include "TNHttpCreateGroupChat.h"
#include "TNHttpAddGroupChatMember.h"
#include "TNHttpRemoveGroupChatMember.h"
#include "TNHttpQuitGroupChat.h"
#include "TNMessageListAdapter.h"
#include "TNHttpObtainGroupChatInfoByGroupChatIdSyn.h"

namespace Ui {
class TNGroupChatMembersWidget;
}

class TNDefaultPage;
class QSearchLineText;
class TNContactModel;
class TNProgressLoading;
class TNGroupChatMembersWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TNGroupChatMembersWidget(QWidget *parent = 0);
    ~TNGroupChatMembersWidget();

    void resetSession(TNMessageListAdapter *currentAdpter);
    void updateTableWidget();
    void stopLoading(const QString& groupChatId);

signals:
    void createGroupChatFinished(TNMessageListAdapter session);
    void exitGroupChatFinished(TNMessageListAdapter messageListAdapter);
    void widgetHided();

private slots:
    void slotSearch(const QString &text);
    void slotSelectContactDialog();
    void slotRemoveGroupChatMemberDialog();
    void slotSelectFinished(QList<TNFriend> selectFriends);
    void slotExitGroupChat();
    void slotMemberFrame(const QModelIndex &index);
    //更新备注
	void on_notifyReMarkUpdate(const QString &from, const QString &to, const QString &remark, int sources);

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    void showNullPage(bool visible);
    void initialTableViewSettings();
    void initialTableWidget();

    QString wrapTitleLabelName(const QString& oldName);
    bool shouldShowAddButton() const;
    bool shouldShowRemoveButton() const;
    bool isSingleChat() const;
    bool isGroupChat() const;
    void createGroupChat(const QList<TNFriend> &selectContacts);
    void addMemberToGroupChat(const QList<TNFriend> &selectContacts);
    void removeMemberFromGroupChat(const TNFriend &groupChatOwner, const QList<TNFriend> &selectContacts);
    void exitGroupChat();

    st_GroupInfoPtr getGroupChatInfoFromHttp(const QString &groupChatId);

    QString getCurrentGroupChatId() const;
    QString getCurrentGroupChatName() const;
    QString getMyFeedId() const;
    QString getToFeedId() const;
    QString getUserId() const;

    void doStopLoading();

private:
    Ui::TNGroupChatMembersWidget *ui;
    TNPluginParamPtr  m_pluginParam;
    TNMessageListAdapter m_currentAdpter;
    QList<TNFriend> m_groupChatMembers;
    QSearchLineText *m_searchLineEdit;
    TNDefaultPage   *m_nullPage;
    TNContactModel *m_groupChatMemberModel;

    TNHttpCreateGroupChat m_httpCreateGroupChat;
    TNHttpAddGroupChatMember m_httpAddGroupChatMember;
    TNHttpRemoveGroupChatMember m_httpRemoveGroupChatMember;
    TNHttpQuitGroupChat m_httpQuitGroupChat;

    QStringList m_finishedGroupMemberDBGroupIds;
    QString m_newCreateGroupChatIdCallback;

    TNProgressLoading *m_progressLoading;

    bool m_occurredException;
};

#endif // TNGROUPCHATMEMBERSWIDGET_H
