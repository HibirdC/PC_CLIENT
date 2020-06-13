#ifndef TNRemoveGroupChatMemberDialog_H
#define TNRemoveGroupChatMemberDialog_H

#include "DropShadowWidget.h"
#include "TNContactModel.h"

#include <QMap>

namespace Ui {
class TNRemoveGroupChatMemberDialog;
}

class TNDefaultPage;
class QLineEdit;
class QTableView;
class QSearchLineText;
class TNContactModel;
class TNRemoveGroupChatMemberDialog : public /*QDialog*/DropShadowWidget
{
    Q_OBJECT

public:
    explicit TNRemoveGroupChatMemberDialog(QWidget *parent = 0);
    void setData(const QString &belongToFeedId, const QList<TNFriend> &groupChatMembers);
    ~TNRemoveGroupChatMemberDialog();

    TNFriend getGroupChatOwner() const;
    QList<TNFriend> getSelectedContact() const;

public slots :
    virtual void accept();

private slots:
    void slotSearch(const QString &text);
    void slotLeftItemClicked(const QModelIndex &index);
    void slotRightItemClicked(const QModelIndex &index);

private:
    void showNullPage(bool visible);
    void initialTableWidget();
    void initialTableViewSettings(QTableView *tableView);

    TNFriend getFriendEntity(const QString &feedId) const;

private:
    Ui::TNRemoveGroupChatMemberDialog *ui;
    QString m_belongToFeedId;
    QList<TNFriend> m_groupChatMembers;
    QSearchLineText *m_searchLineEdit;
    TNDefaultPage   *m_nullPage;
    TNContactModel *m_leftContactModel;
    TNContactModel *m_rightContactModel;
};

#endif // TNRemoveGroupChatMemberDialog_H
