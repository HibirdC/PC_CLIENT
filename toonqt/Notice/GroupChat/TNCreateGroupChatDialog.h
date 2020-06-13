#ifndef TNCREATEGROUPCHATCONTACTDIALOG_H
#define TNCREATEGROUPCHATCONTACTDIALOG_H

#include "DropShadowWidget.h"
#include "TNDbUtil.h"
#include "TNHttpCloudApi.h"
#include "TNContactModel.h"

#include <QMap>
#include <QDialog>
#include <QTableWidget>
#include <QTableWidgetItem>

namespace Ui {
class TNCreateGroupChatDialog;
}

class TNDefaultPage;
class QSearchLineText;
class QListWidgetItem;
class TNContactModel;
class TNCreateGroupChatDialog : public /*QDialog*/DropShadowWidget
{
    Q_OBJECT

public:
    explicit TNCreateGroupChatDialog(QWidget *parent = 0);
    ~TNCreateGroupChatDialog();

    QString getBelongFeedId() const;
    QList<TNFriend> getSelectedContact() const;

public slots :
    virtual void accept();

private slots:
    void slotCardItemClicked(const QModelIndex &index);
    void slotSearch(const QString &text);
    void slotLeftItemClicked(const QModelIndex &index);
    void slotRightItemClicked(const QModelIndex &index);

private:
    void showNullPage(bool visible);
    void initialStuffTableView();
    void initialTableWidget();
    void initialTableViewSettings(QTableView *tableView);

    void copyFriendCacheToMap();
    void copyColleagueCacheToMap();

    bool isInHistory(const QString &feedId);

private:
    Ui::TNCreateGroupChatDialog *ui;
    QSearchLineText *m_searchLineEdit;
    TNDefaultPage   *m_nullPage;

    QString m_belongToFeedId;
    TNContactModel *m_stuffContactModel;

    QMap<QChar/*首字母*/, QMultiMap<QString/*拼音*/, ContactModelItem> > m_friendItems;
    QMap<QString/*belongToFeedId*/, QList<ContactModelItem> > m_cacheSelectedFriendItems;

    QMap<QString/*feedID*/, TNFriend> m_feedIdToFriendMap;

    TNContactModel *m_leftContactModel;
    TNContactModel *m_rightContactModel;
};

#endif // TNCREATEGROUPCHATCONTACTDIALOG_H
