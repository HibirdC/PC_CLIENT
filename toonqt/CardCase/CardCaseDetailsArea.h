#ifndef CARDCASEDETAILSAREA_H
#define CARDCASEDETAILSAREA_H

#include <QWidget>
#include <QWebChannel>
#include <QWebEngineView>

#include "Friend/TNCardCaseListAdapter.h"
#include "TNWebViewDetailsArea.h"
#include "Colleague/TNStaffItem.h"
#include "TNDbUtil.h"
#include "GroupChat/TNCardCaseGroupChatAdapter.h"

class CardCaseDetailsArea : public TNWebViewDetailsArea
{
    Q_OBJECT

public:
    CardCaseDetailsArea(int id, TNPluginParamPtr pluginParam, QWidget *parent = 0);
    ~CardCaseDetailsArea();

public slots:
    void slotShowNewFriendNotice();
    void OnListAreaClickedSlot(const QModelIndex & index);
    void OnColleagueListAreaSlot(const QModelIndex & index);
    void OnGroupListAreaSlot(const QModelIndex & index);
    void OnGroupChatListAreaSlot(const QModelIndex & index);
    void slotModifiedGroupChatInfos(const QModelIndex &index);

	void on_notifyReMarkUpdate(const QString &from, const QString &to, const QString &remark, int sources);

    void feedCardUpdateFromCatche(const QString &feedId,
                                  const QString &avatarId,
                                  const QString &name,
                                  const QString &subName,
                                  const QString &userId,
                                  const QString &namePy,
                                  int sourceType);

private:
    void showGroupChatInfo(TNCardCaseGroupChatAdapter *adapter);

private:
    QString m_currentFeedId;
};

#endif // CARDCASEDETAILSAREA_H
