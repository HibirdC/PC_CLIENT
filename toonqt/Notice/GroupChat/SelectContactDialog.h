#ifndef SELECTCONTACTDIALOG_H
#define SELECTCONTACTDIALOG_H

#include "DropShadowWidget.h"
#include "TNDbUtil.h"
#include "TNHttpCloudApi.h"
#include "TNContactModel.h"

#include <QMap>
#include <QDialog>
#include <QTableWidget>
#include <QTableWidgetItem>

namespace Ui {
class SelectContactDialog;
}

class TNDefaultPage;
class QSearchLineText;
class TNContactModel;
class SelectContactDialog : public /*QDialog*/DropShadowWidget
{
    Q_OBJECT

public:
    explicit SelectContactDialog(QWidget *parent = 0);
    void setData(const QString &belongMyFeedId, const QList<TNFriend> &excludeFriend);
    ~SelectContactDialog();

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

    bool isInGroupChat(const TNFriend& aFeed) const;
    void copyFriendCacheToMap();
    void copyColleagueCacheToMap();

private:
    Ui::SelectContactDialog *ui;
    QString m_belongToFeedId;
    QList<TNFriend> m_excludeFriend;
    QMap<QChar/*首字母*/, QMultiMap<QString/*拼音*/, ContactModelItem> > m_friendItems;
    QMap<QString/*feedID*/, TNFriend> m_feedIdToFriendMap;
    QSearchLineText *m_searchLineEdit;
    TNDefaultPage   *m_nullPage;
    TNContactModel *m_leftContactModel;
    TNContactModel *m_rightContactModel;
};

#endif // SELECTCONTACTDIALOG_H
