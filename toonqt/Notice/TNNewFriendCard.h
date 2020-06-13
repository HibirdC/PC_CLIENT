#ifndef TNNEWFRIENDCARD_H
#define TNNEWFRIENDCARD_H

#include "TNIMCoreClient.h"
#include "TNHttpCloudApi.h"
#include "TNHttpFriendRequest.h"
#include "TNHttpNewCardRequest.h"
#include "TNHttpOrgCardRequest.h"
#include "TNHttpGroupRequest.h"

#include <QWidget>

namespace Ui {
	class TNNewFriendCard;
}

class TNNewFriendCard : public QWidget
{
	Q_OBJECT

public:
	explicit TNNewFriendCard(TNPluginParamPtr param, const st_NoticeInfo &aNotice, QWidget *parent = 0);
	~TNNewFriendCard();

	bool isSameNotice(const st_NoticeInfo &aNotice) const;

protected:
	virtual void resizeEvent(QResizeEvent *event);

private slots:
	void slotAccept();
	void slotReject();
	void slotShowUrl();

    void slotShowHerFrame();
    void slotShowMineFrame();
	
private:
	void initialCard(const st_NoticeInfo &aNotice);
	bool isGroupAvatar(const st_NoticeInfo &aNotice);
	bool showCustomButton(const st_NoticeInfo &aNotice);
	bool showToonButton(const st_NoticeInfo &aNotice);
	bool showFinishedMarkLabel(const st_NoticeInfo &aNotice);
	bool showExpiredMarkLabel(const st_NoticeInfo &aNotice);
	void showMarkLabel();
	int  getXPosition() const;
	int  getYPosition() const;

	void acceptNewCard();
	void acceptOrgCard();
	void acceptNewFriend();
	void acceptJoinGroup();
	void inviteJoinGroup();
    void viewGroupInfo(const QString &groupId, const QString &belongFeedId);

	void rejectNewCard();
	void rejectOrgCard();
	void rejectNewFriend();	
	void rejectJoinGroup();

    void handleExchangeCard(bool accept);
    void handleNewCard(bool accept);
	void handleOrgCard(bool accept);
	void handleJoinGroupRequest(bool accept);

	bool alreadyJoinGroup() const;

private:
	Ui::TNNewFriendCard *ui;

	TNPluginParamPtr  m_pluginParam;
	st_NoticeInfo m_noticeInfo;

	TNHttpFriendRequestPtr  m_httpFriendRequest;

	TNHttpNewCardRequestPtr  m_httpNewCardRequest;
	TNHttpOrgCardRequestPtr  m_httpOrgCardRequest;
	TNHttpGroupRequestPtr    m_groupRequestPtr;

	// 异步更新下载头像
    void asynDownloadAvatar(const QString& url, const QString& sessionId, const QString& file_path);
	
private slots:
    void onAvatarDownLoadFinish(bool success, QString file_path, QString sessionId);
};

#endif // TNNEWFRIENDCARD_H
