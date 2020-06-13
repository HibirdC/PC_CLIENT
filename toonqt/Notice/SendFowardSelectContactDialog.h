#ifndef SENDFOWARDSELECTCONTACTDIALOG_H
#define SENDFOWARDSELECTCONTACTDIALOG_H

#include "DropShadowWidget.h"
#include "TNDbUtil.h"
#include "TNHttpCloudApi.h"
#include "TNMessageListAdapter.h"
#include "TNContactModel.h"

#include <QMap>
#include <QDialog>
#include <QTableWidget>
#include <QTableWidgetItem>

namespace Ui {
    class SendFowardSelectContactDialog;
}

class TNDefaultPage;
class TNContactModel;
class SendFowardSelectContactDialog : public /*QDialog*/DropShadowWidget
{
	Q_OBJECT

public:
    static SendFowardSelectContactDialog *getInstance();
    void setData(const QString &belongMyFeedId);
    ~SendFowardSelectContactDialog();

private:
    SendFowardSelectContactDialog(QWidget *parent = 0);
    QList<TNMessageListAdapter> getSelectedSessions() const;
	QList<TNFriend> getSelectedContact() const;
    QList<TNStructGroupChat> getSelectedGroupChats() const;

signals:
    void selectFinished(QList<TNMessageListAdapter> selectSessions, QList<TNFriend> selectFriends, QList<TNStructGroupChat> selectGroupChats);

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

    bool shouldExclude(const QString& feedId, int *sessionIndex) const;

    void copySessionCacheToMap();
	void copyFriendCacheToMap();
	void copyColleagueCacheToMap();
	void copyGroupChatCacheToMap();

    void resetLeftViewRowHidden();

private:
    static SendFowardSelectContactDialog *s_pInstance;
    Ui::SendFowardSelectContactDialog *ui;
    QString m_belongToFeedId;

    QList<ContactModelItem> m_sessionItems;
    QMultiMap<QString/*拼音*/, ContactModelItem> m_friendItems;
    QMultiMap<QString/*拼音*/, ContactModelItem> m_GroupChatItems;
    QMap<QString/*feedID*/, TNMessageListAdapter> m_feedIdToSessionMap;
    QMap<QString/*feedID*/, TNStructGroupChat> m_feedIdToGroupChatMap;
	QMap<QString/*feedID*/, TNFriend> m_feedIdToFriendMap;
	QLineEdit *_searchLineEdit;
    TNDefaultPage   *m_nullPage;
	TNContactModel *m_leftContactModel;
	TNContactModel *m_rightContactModel;
    int m_maxSelectedNum;
};

#endif // SENDFOWARDSELECTCONTACTDIALOG_H
