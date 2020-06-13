#ifndef MINELISTAREA_H
#define MINELISTAREA_H

#include <QWidget>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QStackedWidget>
#include <QListView>
#include <QTreeView>
#include <QPointer>
#include <QThread>
#include <QPushButton>

#include "ListAreaBase.h"
#include "Friend/TNCardCaseListAdapter.h"
#include "cardcase_global.h"
#include "common_global.h"
#include "Friend/TNCardCaseListFriendItemDelegate.h"
#include "TNHttpLoadAvatar.h"
#include "GroupChat/TNCardCaseGroupChatModel.h"
#include "TNHttpCloudApi.h"
#include "../LocalStorage/LocalStorageCommon.h"
#include "TNDbUtil.h"
#include "imcore_global.h"
#include "Colleague/TNStaffItem.h"
#include "Search/TNSearchAreaV2.h"
#include "TNQListView.h"
#include "GroupChat/TNCardCaseGroupChatDelegate.h"
#include "TNHttpObtainFeedList.h"
#include "TNHttpObtainGroupChatInfoByGroupChatId.h"
#include "TNHttpObtainGroupMembersByGroupId.h"
#include "TNDefaultPage.h"
#include "Colleague/TNCardCaseCOModel.h"
#include "Colleague/TNCardCaseCODelegate.h"
#include "Group/TNCardCaseGroupModel.h"
#include "Group/TNCardCaseGroupDelegate.h"
#include "Search/QSearchLineText.h"

class CardCaseListArea : public ListAreaBase
{
	Q_OBJECT

public:
	CardCaseListArea(int id, TNPluginParamPtr pluginParam, QWidget *parent = 0);
	~CardCaseListArea();

    enum
    {
		FriendCard,
		ColleagueCard,
		GroupCard,
		GroupChatCard
	};

	void LoadDefaultPage();
	void DownLoadAvatar(QString feedId, QString url,bool isOriginal);

    void updateNewFriendUnReadCount();

public slots :
	void OnButtonFriendSlot();
    void on_notifyRefresh(int type, QList<UINotifyData> dataList);
    void refreshNewFriendPage();
	void OnListAreaClickedSlot(const QModelIndex & index);
	void OnColleagueListAreaSlot(const QModelIndex & index);
	void OnGroupListAreaSlot(const QModelIndex & index);
	void OnGroupChatListAreaSlot(const QModelIndex & index);
	void on_notifyCurrentFeedChanged(const QString & feedID);
	void needToDownLoadAvatar(const QString &feedId,const QString &url,int type);
	void on_notifyReMarkUpdate(const QString &, const QString &, const QString &,int);
	void on_notifyKeyEventDis(int keyEvent);
	void feedCardUpdateFromCatche(const QString &feedId,
								  const QString &avatarId,
								  const QString &name,
								  const QString &subName,
								  const QString &userId,
								  const QString &namePy,
								  int sourceType);
private slots:
	void OnButtonColleagueSlot();
	void OnButtonGroupChatSlot();
	void OnButtonGroupSlot();

	void slotSearch(const QString &text);
	void onAvatarDownLoadFinish(bool success, QString url, QString feedId);
	void SearchClickedSlot(const QString &, const QString &, const QString &);
	void setCODepartItemExpanded(const QModelIndex & index);

private:
	void InitWidget();
	void InitSearchPage();
	void InitAvatarDir();
	void LoadFriend(QList<TNStructFriend> friendList);
	void LoadColleague(QList<TNStructCompany> companyInfoList);
	void LoadGroup(QList<TNStructGroup>& groupInfoList);
	void LoadGroupChat(QList<TNStructGroupChat> groupChatInfoList);
	void SearchContent(QString text);
	void UpdateGroupChatUI(QList<UINotifyData> dataList);
	void UpdateGroupChatMemberUI(QList<UINotifyData> dataList);
	void UpdateGroupUI(QList<UINotifyData> dataList);
	bool IsExistbyGroupChatId(QString feedId);
	bool IsExistbyFriendFeedId(const QString &feedId);
	bool IsExistbyGroupId(QString feedId, TNStructGroup &currentGroup);
	void ResetOldSelectedStatus(int type);
	void UpdateFriendUI(QList<UINotifyData> dataList);
	void UpdateColleagueUI(QList<UINotifyData> dataList);
	void BuildStaffItem(TNStructCompany company, st_FeedPtr feed, TNStaffItem ** Staff);
	void BuildGroupItem(TNStructGroup group,TNCardCaseGroupAdapter ** adapter);
	void UpdateFriendUIByChangeCard(const QString &feedID);
	void UpdateColleagueUIByChangeCard(const QString &feedID);
	void UpdateGroupUIByChangeCard(const QString &feedID);
	void UpdateGroupChatUIByChangeCard(const QString &feedID);
	void InitMyStuffAvatar();
	void DynamicUpdateFeedInfo(QString feedId, QString belongFeedId, QVector<QString>baseInfo, int iType);
	void DynamicUpdateFeedUI(st_FeedPtr feed,int type);
	void DynamicUpdateGroupChatInfo(QString feedId);
	void DynamicUpdateGroupChatUI(st_GroupInfoPtr group);
	void DynamicUpdateGroupMember(QString groupId);
	void DynamicUpdateGroupMemberUI(QString groupId,int count);
	void showNullPage(bool status,int type);
	void downSelected(int type);
	void upSelected(int type);
	void enterSelected(int type);
Q_SIGNALS:
    void clickedNewFriendItem();
    void updateNewFriendPage();
    void messageNumberChanged(int count);
	void ListAreaClicked(const QModelIndex &index);
	void ColleagueListAreaClicked(const QModelIndex &index);
	void GroupListAreaClicked(const QModelIndex &index);
	void GroupChatListAreaClicked(const QModelIndex &index);
	void ListAreaDoubleClicked(const QModelIndex &index);
	void ListFriendToDetailEvent(const QModelIndex &index);
	void ListColleagueToDetailEvent(const QModelIndex &index);
	void ListGroupToDetailEvent(const QModelIndex &index);
	void ListGroupChatToDetailEvent(const QModelIndex &index);
	void ListGroupChatModifyEvent(const QModelIndex &index);

	void CloseDetailPageEvent(const QString &feedId, const QString&belongId);
	void SearchClickedSignal(const QString & type, const QModelIndex &index);
	void UpdateColleagueCacheSignal();
	void UpdateOrgGroupAndRelationSignal();
	void RemoveSessionInSessionList(const QString &);
	void UpdateFriendReMark(const QString &, const QString &);
	/*
	isReady :true: 已经更新完毕，槽直接更新头像即可。
	         false:未更新，需要酌情更新。
	UINotifyData： ADD（0）：槽需要处理
	               DEL（0）：不需要处理
	*/
	void notifySessionList(QList<UINotifyData> dataList, bool isReady);

public Q_SLOTS:
	void hideSearchArea(bool status);
	void currentSelectedPage(int page);

private:
	TNSearchAreaV2 * _searchArea;

	TNPluginParamPtr _pluginParam;
	QStackedWidget *_stackedWidget;
	QWidget * _topWidget;
	QWidget * _searchWidget;
	TNQListView * _CardCaselistWidgt;
	TNCardCaseListModel * _listCardCaseModel;
	TNCardCaseListFriendItemDelegate *_CardCaseListDelegate;

	TNCoTreeView  * _ColleagueListWidgt;
	TNCardCaseCOModel *  _ColleagueModel;
	TNCardCaseCODelegate *_ColleagueDelegate;

	TNQListView  * _GroupListWidgt;
	TNCardCaseGroupModel * _GroupModel;
	TNCardCaseGroupDelegate *_GroupDelegate;

	TNQListView  * _GroupChatListWidgt;
	TNCardCaseGroupChatModel    * _GroupChatModel;
	TNCardCaseGroupChatDelegate *_GroupChatDelegate;

	QSearchLineText *_searchLineEdit;

	QPushButton * _buttonFriend;
	QPushButton * _buttonColleague;
	QPushButton * _buttonGroupChat;
	QPushButton * _buttonGroup;
	QString		  _strAvatarDir;
	int           _currentSelectedCard;
	int           _subCardStatus[4];
	bool          _searchMode;
	QMutex        _mutex;
	TNDefaultPage          *_nullPage;
	bool                    _nullPageStatus;

	TNHttpObtainFeedListPtr _httpObtainFeedList;
	TNHttpObtainGroupMembersByGroupIdPtr _httpObtainGroupMember;
	TNHttpObtainGroupChatInfoByGroupChatIdPtr _httpObtainGroupInfo;
	int           _currentSelectedPage;
protected:
	virtual bool eventFilter(QObject *watched, QEvent *event);
};

#endif // MINELISTAREA_H
