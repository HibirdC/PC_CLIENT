#ifndef TNWINTRAYMANGER_H
#define TNWINTRAYMANGER_H

#include <QObject>
#include <QTimer>

#include "TNCMsgTray.h"
#include "TNSysTray.h"
#include "TNUnReadMsgAdapter.h"
#include "TNUnReadListDelegate.h"
#include "TNUnReadView.h"
#include "TNMessageListAdapter.h"
#include "TNUnReadMsgListW.h"

class TNWinTrayManger : public QObject
{
	Q_OBJECT

public:
	TNWinTrayManger(QWidget *parent,QString icoFile, QRect validScreenRect);
	~TNWinTrayManger();

	void recieveMessage(TNMessageListAdapter adapter);
	void showMenu(QPoint pos);
	void mouseMove();
	void mouseHover();
	void mouseLeave(QPoint curPoint);
Q_SIGNALS:
	void updateUnRead(const QString & sessionId, bool isAll);
	void showWidget();
	void MessageSignal(int);
	void quitAppSignal();

private:
	void initTrayIco(QWidget *parent);
	void initUnReadList();
	void buildUnReadWidget();
	void stopTrayNotify();
	int  getExistSession(const QString sessionID);
	void startTrayNotify();
	void playMediaTraySound();

public slots:
	void unReadListAreaClicked(const QModelIndex &index);
	void updateUnReadFromNotice(const QString &sessionId);
	void outlineUpdateUnreadTraySlot(TNMessageListAdapter, int);
	void reduceUnReadFromNotice(const QString &sessionId,int currentCount);
	void unReadListIgnoreAll(bool);
	void twinkleTrayIcon();
	void manualNoAlarm(const QString &sessionId, bool noAlarm, int unRead);
	void manualDeleteSession(const QString &sessionId,bool);
	void manualModifySessionName(const QString &sessionId, const QString & newName);
	void manualModifySessionRemark(const QString &sessionId, const QString & remark);
	void on_notifyReadSession(QString sessionId);
	void on_notifyCurrentFeedChanged(const QString & feedID);
	void updateSettingNoDisturbStatus(QString, int);
	void on_notifyReMarkUpdate(const QString &from, const QString &to, const QString &remark,int sources);
private:
	//自定义托盘
	NOTIFYICONDATA  m_nid;
	TNCMsgTray      m_traypos;
	QLabel          *m_pSysIcon;
	TNSysTray       *system_tray;
	HICON           m_Hico;
	//未读消息列表
	QList<TNMessageListAdapter> _unReadList; //sessionID,unReadStruct
	TNUnReadMsgListW * _unReadMsgList;
	TNUnReadMsgModel * _unReadMsgModel;
	TNUnReadListDelegate *_unReadMsgDelegate;
	QRect _unReadMsgListRect;
	/// <summary>	托盘图标闪烁用timer. </summary>
	QTimer _TwinkleTimer;
	bool _settingNoDisturnStatus;
};

#endif // TNWINTRAYMANGER_H
