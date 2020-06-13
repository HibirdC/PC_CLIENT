#include "TNWinTrayManger.h"
#include "TNDataCache.h"
#include "TNVersionInfo.h"
#include "TNNotifyCenter.h"
#include "TNNetAvatarDown.h"
#include "TNUserDataHelper.h"
#include "TNDataStatistics.h"
#include "TNDataControlServer.h"
#include "TNPathUtil.h"

#include <QtMultimedia/QSound>
#include <QDesktopWidget>

Q_GUI_EXPORT HICON qt_pixmapToWinHICON(const QPixmap &);

TNWinTrayManger::TNWinTrayManger(QWidget *parent, QString ico, QRect validScreenRect)
	: QObject(parent)
	, _settingNoDisturnStatus(TNDbUtil::IsNoDisturbing())
{
	m_Hico = qt_pixmapToWinHICON(QIcon(ico).pixmap(16, 16));
	initTrayIco(parent);
	initUnReadList();

	_TwinkleTimer.setSingleShot(false);
	_TwinkleTimer.setInterval(350);
	connect(&_TwinkleTimer, SIGNAL(timeout()), this, SLOT(twinkleTrayIcon()));
	TNNotifyCenter::instance()->connectNotifyReadSession(this);
	TNNotifyCenter::instance()->connnectNotifyCurrentFeedChanged(this);
	TNNotifyCenter::instance()->connectNotifyReMarkUpdate(this);
}

TNWinTrayManger::~TNWinTrayManger()
{
	if (system_tray != nullptr)
	{
		delete system_tray;
		system_tray = nullptr;
	}
	Shell_NotifyIcon(NIM_DELETE, &m_nid);
}
void TNWinTrayManger::twinkleTrayIcon()
{
	if (m_nid.hIcon == nullptr)
	{
		m_nid.hIcon = m_Hico;
	}
	else
	{
		m_nid.hIcon = nullptr;
	}
	Shell_NotifyIcon(NIM_MODIFY, &m_nid);
}
int TNWinTrayManger::getExistSession(const QString sessionID)
{
	int result = -1;
	for (int i = 0; i < _unReadList.size(); i++)
	{
		if (_unReadList[i].getSessionId() == sessionID)
		{
			result = i;
			break;
		}
	}
	return result;
}
void TNWinTrayManger::recieveMessage(TNMessageListAdapter adapter)
{
	qInfo() << "[Toon][TNWinTrayManger]recieveMessage session name: " << adapter.getName() << " unRead:" << adapter.getUnreadCount();
	if (adapter.getUnreadCount() <= 0)
		return;

	startTrayNotify();
	playMediaTraySound();
	int index = getExistSession(adapter.getSessionId());
	if (index >= 0) //存在
	{
		//需要更新到头部
		_unReadList.removeAt(index);
	}
	_unReadList.push_front(adapter); //头部插入
}
void TNWinTrayManger::initTrayIco(QWidget *parent)
{
	//创建托盘图标
	m_pSysIcon = new QLabel;
	m_nid.cbSize = sizeof m_nid;
	m_nid.hIcon = m_Hico;
	m_nid.hWnd = HWND(m_pSysIcon->winId());
	m_nid.uCallbackMessage = WM_TRAYNOTIFY;
	m_nid.uID = 1;
	m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	QString toolTip = TOON_TITLE;
	wcscpy_s(m_nid.szTip, reinterpret_cast<const wchar_t *>(toolTip.utf16()));
	Shell_NotifyIcon(NIM_ADD, &m_nid);
	m_traypos.SetNotifyIconInfo(HWND(parent->winId()), 1, WM_TRAYNOTIFY);
	system_tray = new TNSysTray(parent);
	Q_ASSERT(system_tray);
	connect(system_tray, SIGNAL(showWidget()), this, SIGNAL(showWidget()));
	connect(system_tray, SIGNAL(MessageSignal(int)), this, SIGNAL(MessageSignal(int)));
	connect(system_tray, SIGNAL(quitAppSignal()), this, SIGNAL(quitAppSignal()));
}
void TNWinTrayManger::initUnReadList()
{
	_unReadMsgList = new  TNUnReadMsgListW();
    _unReadMsgList->setFixedWidth(LIST_UNREAD_WIDTH);
	_unReadMsgList->setObjectName("UNReadMsgWidgt");
    _unReadMsgList->setContentsMargins(0,0,0,0);
	_unReadMsgList->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::SubWindow);
	_unReadMsgDelegate = new TNUnReadListDelegate();
	_unReadMsgList->setDelegate(_unReadMsgDelegate);
	_unReadMsgModel = new TNUnReadMsgModel(this);
	_unReadMsgList->setModel(_unReadMsgModel);
	_unReadMsgList->hide();

	connect(_unReadMsgList, SIGNAL(unReadListAreaClicked(const QModelIndex &)), this, SLOT(unReadListAreaClicked(const QModelIndex &)));
	connect(_unReadMsgList, SIGNAL(ignoreAll(bool)), this, SLOT(unReadListIgnoreAll(bool)));
}
void TNWinTrayManger::buildUnReadWidget()
{
	qDebug() << "buildUnReadWidget";
	if (_unReadList.size() == 0 || _settingNoDisturnStatus)
		return;
	int total = 0;
	QList<TNUnReadMsgAdapter*> buildList;
	for (QList<TNMessageListAdapter>::iterator it = _unReadList.begin();
		it != _unReadList.end(); it++)
	{
		TNUnReadMsgAdapter *item = new TNUnReadMsgAdapter(TNUnReadMsgAdapter::normal);
		QString photosId = (*it).getPhotoResID();
		QString sessionId = (*it).getSessionId();
		QString toFeed = (*it).getToFeed();
		if (toFeed.isEmpty())
			toFeed = sessionId;
		if (photosId.isEmpty())
		{
			qInfo() << "[Toon][TNWinTrayManger]buildUnReadWidget warning the photosId is invalid,sessionId:" << sessionId;
			if (toFeed.startsWith("gc_"))
				photosId = TNPathUtil::getFeedAvatarPath(toFeed) + "_org";
			else
				photosId = TNPathUtil::getFeedAvatarPath(toFeed);
		}
		item->setFromAvator(photosId);
		item->setFromFeedId(toFeed);
		item->setFromName((*it).getName());
		item->setUnReadCount((*it).getUnreadCount());
		item->setSessionId(sessionId);
		item->setRemark((*it).getRemark());

		/*
		目前只有免打扰开启时，会把未读设为0
		*/
		if ((*it).getUnreadCount() <= 0 && !(*it).getNoAlarm())
		{
			qInfo() << "[Toon][TNWinTrayManger]buildUnReadWidget error unRead count";
			continue;
		}
		if ((*it).getNoAlarm())
		{
			item->setNoShowCount(true);
		}
		else
		{
			item->setNoShowCount(false);
			total += (*it).getUnreadCount();
		}
		buildList.append(item);
	}

	if (buildList.size() == 0)
	{
		stopTrayNotify();
		return;
	}
	_unReadMsgList->setTotalCount(total);
	if (_unReadMsgModel != nullptr)
	{
		_unReadMsgModel->resetModel();
		_unReadMsgModel->appendData(buildList);
	}
	int widgetH = 0,viewH = 0;
	if (buildList.size() > 5)
        viewH = (LIST_UNREAD_HEIGHT) * 5;
	else
        viewH = (LIST_UNREAD_HEIGHT) * buildList.size();

    widgetH = viewH + LIST_UNREAD_TITLE_HEIGHT + LIST_UNREAD_BUTTOM_HEIGHT;
	_unReadMsgList->setFixedHeight(widgetH);
	_unReadMsgList->setViewHeight(viewH);

	if (_unReadMsgList != nullptr)
	{
		QDesktopWidget* desktop = QApplication::desktop();
		QRect screenRect = desktop->screenGeometry();
		QRect validScreenRect = desktop->availableGeometry();
		QPoint cur = QCursor::pos();
		int x = 0, y = 0;
		//上下任务栏
		if (screenRect.width() == validScreenRect.width() && screenRect.height() != validScreenRect.height())
		{
			if (validScreenRect.x() == 0 && validScreenRect.y() == 0) //下任务栏
			{
				x = cur.rx() - LIST_UNREAD_WIDTH / 2;
				y = validScreenRect.height() - widgetH;
			}
			else if (validScreenRect.x() == 0 && validScreenRect.y() != 0) //上任务栏
			{
				x = cur.rx() - LIST_UNREAD_WIDTH / 2;
				y = validScreenRect.y();
			}
		}//左右任务栏
		else if (screenRect.width() != validScreenRect.width() && screenRect.height() == validScreenRect.height())
		{
			//左任务栏
			if (validScreenRect.x() != 0 && validScreenRect.y() == 0)
			{
				x = validScreenRect.x();
				y = cur.ry() - widgetH / 2;
			}
			//右任务栏
			else if (validScreenRect.x() == 0 && validScreenRect.y() == 0)
			{
				x = validScreenRect.width() - LIST_UNREAD_WIDTH;
				y = cur.ry() - widgetH / 2;
			}
		}
		else //任务栏开启自动隐藏
		{
#ifdef Q_OS_WIN
			int taskBarHeight = 0;
			int cx = GetSystemMetrics(SM_CXSCREEN);
			int cy = GetSystemMetrics(SM_CYSCREEN);
			HWND tooBarWnd = FindWindow(L"shell_traywnd", NULL);  //获得任务栏的句柄
			if (tooBarWnd != nullptr)
			{
				RECT toolBarRect;
				GetWindowRect(tooBarWnd, &toolBarRect); //任务栏的尺寸
				if (toolBarRect.top > 0&& toolBarRect.left == 0 
					&& toolBarRect.bottom == cy) //下任务栏
				{
					taskBarHeight = toolBarRect.bottom - toolBarRect.top;
					x = cur.rx() - LIST_UNREAD_WIDTH / 2;
					y = cy - taskBarHeight - widgetH;
				}
				else if (toolBarRect.top <=0 && toolBarRect.right == cx 
					&& toolBarRect.bottom < cy) //上任务栏
				{
					taskBarHeight = toolBarRect.bottom - toolBarRect.top;
					x = cur.rx() - LIST_UNREAD_WIDTH / 2;
					y = taskBarHeight;
				}
				else if (toolBarRect.left <=0 &&toolBarRect.bottom == cy 
					&& toolBarRect.right < cx) //左任务栏
				{
					taskBarHeight = toolBarRect.right - toolBarRect.left;
					x = taskBarHeight;
					y = cur.ry() - widgetH / 2;
				}
				else if (toolBarRect.left>0 &&toolBarRect.bottom == cy 
					&& toolBarRect.right == cx)//右任务栏
				{
					taskBarHeight = toolBarRect.right - toolBarRect.left;
					x = cx - taskBarHeight - LIST_UNREAD_WIDTH;
					y = cur.ry() - widgetH / 2;
				}
			}
		}
#endif
		if (x > 0 && y > 0)
		{
			_unReadMsgListRect.setRect(x, y, LIST_UNREAD_WIDTH, widgetH);
			_unReadMsgList->move(x, y);
			_unReadMsgList->showWindow();
		}
	}
}
void TNWinTrayManger::stopTrayNotify()
{
	qInfo() << "[Toon][TNWinTrayManger]stopTrayNotify ";
	_TwinkleTimer.stop();
	m_nid.hIcon = m_Hico;
	Shell_NotifyIcon(NIM_MODIFY, &m_nid);
}
void TNWinTrayManger::unReadListAreaClicked(const QModelIndex &index)
{
	TNUnReadMsgAdapter *adapter = (TNUnReadMsgAdapter*)index.data().toLongLong();
	if (adapter != NULL && adapter->getType() == TNUnReadMsgAdapter::normal)
	{
		qDebug() << "[Toon]unReadListAreaClicked: name: " << adapter->getFromName();
		//隐藏当前窗口
		if (_unReadMsgList != nullptr)
			_unReadMsgList->hide();
		int index = getExistSession(adapter->getSessionId());
		if (index >= 0)
		{
			_unReadList.removeAt(index);
		}
		if (_unReadList.size() == 0)
			stopTrayNotify();
		emit showWidget();
		emit MessageSignal(MENU_NOTICE_ID);
		if (adapter->getType() == TNUnReadMsgAdapter::normal)
		{
			emit updateUnRead(adapter->getSessionId(), false);
		}
	}
}
void TNWinTrayManger::updateUnReadFromNotice(const QString &sessionId)
{
	qInfo() << "[Toon][TNWinTrayManger]updateUnReadFromNotice ,sessionId:" << sessionId;
	int index = getExistSession(sessionId);
	if (index >= 0)
	{
		_unReadList.removeAt(index);
		if (!_unReadMsgList->isHidden())
		{
			_unReadMsgList->hide();
			buildUnReadWidget();
		}
	}
	if (_unReadList.size() == 0)
		stopTrayNotify();
}
void TNWinTrayManger::unReadListIgnoreAll(bool status)
{
	qDebug() << "[Toon] unReadListIgnoreAll";
	//隐藏当前窗口
	if (_unReadMsgList != nullptr)
	{
		_unReadMsgList->hide();
		_unReadList.clear();
		stopTrayNotify();
	}
	emit updateUnRead((""), true);
	TNDataStatistics::RecordFuncStatisData(FUNC_TYPE_Msgtip_IgnoreAll, TNUserDataHelper::GetInstance()->_pluginParam);
}
void TNWinTrayManger::on_notifyCurrentFeedChanged(const QString & feedID)
{
	for (QList<TNMessageListAdapter>::iterator it = _unReadList.begin(); it != _unReadList.end();)
	{
		if (feedID != AVATAR_ALL_FEED && it->getMyFeedId() != feedID)
		{
			it = _unReadList.erase(it);
		}
		else
			it++;
	}
	if (_unReadList.size() == 0)
		stopTrayNotify();
}
void TNWinTrayManger::outlineUpdateUnreadTraySlot(TNMessageListAdapter adapter, int unRead)
{
	qInfo() << "[Toon][TNWinTrayManger] outlineUpdateUnreadTraySlot :" << unRead;
	if (adapter.getNoAlarm()&&!adapter.getIsAtMe())
		return;
	if (adapter.getUnreadCount() == 0)
	{
		int index = getExistSession(adapter.getSessionId());
		if (index >= 0) //存在
		{
			_unReadList.removeAt(index);
		}
		if (_unReadList.size() == 0)
			stopTrayNotify();
		return;
	}
	QString currentFeed = TNDataCache::GetInstance()->GetCurrentMyFeed();
	if (currentFeed == AVATAR_ALL_FEED ||
		adapter.getMyFeedId() == currentFeed)
	{
		/*
		2018.3.19托盘不需要下载头像
		*/
		//if (!QFile::exists(adapter.getPhotoResID()))
		//{
		//	QString toFeed = adapter.getToFeed();
		//	if (toFeed.isEmpty())
		//	{
		//		toFeed = adapter.getSessionId();
		//	}
		//	bool isOriginal = false;
		//	if (toFeed.startsWith("gc_"))
		//	{
		//		isOriginal = true;
		//	}
		//	qInfo() << "[Toon][TNWinTrayManger] DownLoadAvatar, url: " << adapter.getAvatarPhotoUrl() << " feedId:" << toFeed;
		//	TNNetAvatarDown::GetInstance()->DownLoadFeedAvatar(toFeed, adapter.getAvatarPhotoUrl(), TNHttpCloudApi::GetInstance()->GetCloudStoken(TNUserDataHelper::GetInstance()->_pluginParam), this, isOriginal);
		//}
		startTrayNotify();

		/*
		离线数据可能未排序， 需要插入排序
		*/
		int index = getExistSession(adapter.getSessionId());
		if (index >= 0) //存在
		{
			//需要更新到头部
			_unReadList.removeAt(index);
		}
		int expectIndex = -1;
		for (int i = 0; i < _unReadList.size();i++)
		{
			if (adapter.getTime()>= _unReadList[i].getTime())
			{
				expectIndex = i;
				break;
			}
		}
		if (expectIndex == -1)
			expectIndex = _unReadList.size(); 
		_unReadList.insert(expectIndex, adapter); 
	}
}
void TNWinTrayManger::showMenu(QPoint pos)
{
	if (system_tray!= nullptr)
	{
		system_tray->showMenu(QCursor::pos());
	}
}
void TNWinTrayManger::mouseMove()
{
	m_traypos.OnMouseMove();
}
void TNWinTrayManger::mouseHover()
{
	if (_unReadMsgList == nullptr)
	{
		qInfo() << "[Toon][TNWinTrayManger]_unReadMsgList is exception to NULL";
		return;
	}

	_unReadMsgList->showWindowStatus(true);
	if (_unReadMsgList->isHidden())
	{
		buildUnReadWidget();
	}
}
void TNWinTrayManger::mouseLeave(QPoint point)
{
	if (_unReadMsgList != nullptr &&!_unReadMsgList->isHidden())
	{
		if (!_unReadMsgListRect.contains(point))
		{
			_unReadMsgList->delayHide();
		}
	}
}
void TNWinTrayManger::manualNoAlarm(const QString &sessionId, bool noAlarm, int unReadCount)
{
	qInfo() << "[Toon][TNWinTrayManger]manualNoAlarm :" << sessionId << " unRead:" << unReadCount;
	int index = getExistSession(sessionId);
	if (index>= 0) 
	{
		if (noAlarm)
		{
			//设置消息免打扰
			_unReadList[index].setUnreadCount(0);
			_unReadList[index].setNoAlarm(true);
		}
		else
		{
			if (unReadCount>0)
			{
				//取消设置免打扰
				_unReadList[index].setNoAlarm(false);
				_unReadList[index].setUnreadCount(unReadCount);
			}
			else
			{
				qInfo() << "[Toon][TNWinTrayManger]manualNoAlarm unReadCount is invalid";
				_unReadList.removeAt(index);
				if (_unReadList.size() == 0)
					stopTrayNotify();
			}
		}
	}
}
void TNWinTrayManger::manualDeleteSession(const QString &sessionId, bool isSelected)
{
	Q_UNUSED(isSelected);
	qInfo() << "[Toon][TNWinTrayManger]manualDeleteSession :" << sessionId;
	int index = getExistSession(sessionId);
	if (index >= 0)
	{
		_unReadList.removeAt(index);
	}
	if (_unReadList.size() == 0)
		stopTrayNotify();
}
void TNWinTrayManger::manualModifySessionName(const QString &sessionId, const QString &newName)
{
	qInfo() << "[Toon][TNWinTrayManger]manualModifySessionName :" << sessionId;
	int index = getExistSession(sessionId);
	if (index >= 0)
	{
		_unReadList[index].setName(newName);
	}
}
void TNWinTrayManger::manualModifySessionRemark(const QString &sessionId, const QString & remark)
{
	qInfo() << "[Toon][TNWinTrayManger]manualModifySessionRemark :" << sessionId;
	int index = getExistSession(sessionId);
	if (index >= 0)
	{
		_unReadList[index].setRemark(remark);
	}
}
void TNWinTrayManger::on_notifyReadSession(QString sessionId)
{
	//手机端已读
	manualDeleteSession(sessionId,true);
}
void TNWinTrayManger::reduceUnReadFromNotice(const QString &sessionId, int currentCount)
{
	qInfo() << "[Toon][TNWinTrayManger]reduceUnReadFromNotice :" << sessionId;
	int index = getExistSession(sessionId);
	if (index >= 0)
	{
		if (currentCount == 0)
			_unReadList.removeAt(index);
		else
			_unReadList[index].setUnreadCount(currentCount);
		if (!_unReadMsgList->isHidden())
		{
			_unReadMsgList->hide();
			buildUnReadWidget();
		}
	}
	if (_unReadList.size() == 0)
		stopTrayNotify();
}
void TNWinTrayManger::updateSettingNoDisturbStatus(QString fun, int status)
{
	qInfo() << "[Toon][TNWinTrayManger]updateSettingNoDisturbStatus :" << status;
	if (fun == "NoDisturbing")
	{
		_settingNoDisturnStatus = status;
		/*
		恢复闪烁
		*/
		if (!_settingNoDisturnStatus &&_unReadList.size() > 0)
			startTrayNotify();
		else
			stopTrayNotify();
	}
}
void TNWinTrayManger::startTrayNotify()
{
	if (!_settingNoDisturnStatus)
	{
		qInfo() << "[Toon][TNWinTrayManger]startTrayNotify ";
		_TwinkleTimer.start();
	}
}
void TNWinTrayManger::on_notifyReMarkUpdate(const QString &from, const QString &to, const QString &remark,int sources)
{
	QString session_id = TNIMCoreClient::GetSessionId(from, to, MSG_BIZ_SINGLECHAT);
	manualModifySessionRemark(session_id, remark);
}
void TNWinTrayManger::playMediaTraySound()
{
	if (!_settingNoDisturnStatus)
	{
		qInfo() << "[Toon][TNWinTrayManger]playMediaTraySound ";
		QString wavFile = ":/media/Resources/media/messageReceived.wav";
		QSound::play(wavFile);
	}
}