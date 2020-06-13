#include "Toon.h"

#include <QtMultimedia/QSound>
#include <QtConcurrent/QtConcurrent>
#include <QDesktopWidget>
#include <qstyle.h>
#include <qstyleoption.h>
#include <QDebug>

#if defined(WINDOWS) || defined(WIN32) || defined(WIN64) 
#include <Windows.h>
#include <windowsx.h>
#endif 

#define DEFAULT_SCRREN_WIDTH 1600
#define DEFAULT_SCRREN_HEIGHT 900

#include "TNUtil.h"
#include "XmlSingleton.h"
#include "TNSettingData.h"
#include "TNUpgradeMangement.h"
#include "TNDataStatistics.h"
#include "tnnotifycenter.h"
#include "TNDataCache.h"
#include "TNVersionInfo.h"
#include "TNZoomFactor.h"
Toon::Toon(QWidget *parent)
    : QWidget(parent)
    , _CardCaseListArea(NULL)
    ,_CardCaseDetailArea(NULL)
    , _NoticeListArea(NULL)
    , _NoticeDetailArea(NULL)
    , _MineListArea(NULL)
    , _MineDetailArea(NULL)
    , _HomePageListArea(NULL)
    , _HomePageDetailArea(NULL)
    , _SetUpDetailArea(NULL)
    , _moveAble(false)
#ifdef Q_OS_WIN
    , _trayIco(nullptr)
#else
	,_settingNoDisturnStatusMac(TNDbUtil::IsNoDisturbing())
#endif
{
    TNUtil::setMainWidget(this);
    setWindowTitle(TOON_TITLE);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    setAttribute(Qt::WA_TranslucentBackground);
    QString wavFile = ":/media/Resources/media/messageReceived.wav";
#ifndef Q_OS_WIN
    _player = new QSound(wavFile,this);
#endif
}

Toon::~Toon()
{
#ifdef Q_OS_WIN
    if (_trayIco != nullptr)
    {
        delete _trayIco;
        _trayIco = nullptr;
    }
#endif
}

void Toon::init()
{
    this->setWindowIcon(TOON_ICON);
	//setAttribute(Qt::WA_QuitOnClose, true);
    this->setObjectName("BeaconfireIM");
    this->resize(1002, 652);
    int width = this->width();
    int height = this->height();
	QDesktopWidget* desktop = QApplication::desktop();
	QRect screenRect = desktop->availableGeometry();
	setMaximumWidth(screenRect.width());
	setMaximumHeight(screenRect.height());
#ifdef __linux__
    int re_width = screenRect.width() * this->width() / DEFAULT_SCRREN_WIDTH;
    int re_height = screenRect.height() * this->height() / DEFAULT_SCRREN_HEIGHT;
    this->resize(re_width,re_height);
    move((screenRect.width() - re_width)/2, (screenRect.height() - re_height)/2);
#else
    move((screenRect.width() - this->width()) / 2, (screenRect.height() - this->height()) / 2);
#endif

    menu_area = new MenuArea(TNUserDataHelper::GetInstance()->_pluginParam, this);
    list_area = new ListArea(TNUserDataHelper::GetInstance()->_pluginParam, this);
    details_area = new DetailsArea(this);

    tnLoadLibrary(DIMENSION_MENUTOP);
    tnLoadLibrary(DIMENSION_MENUCENTER);
    tnLoadLibrary(DIMENSION_MENUBOTTOM);

    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addWidget(menu_area);
    main_layout->addWidget(list_area);
	main_layout->addWidget(details_area);
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);

    setLayout(main_layout);

//#ifndef Q_OS_WIN
	title_widget = new TitleWidget(this);
	title_widget->setGeometry(0, 8, 60, 12);
	title_widget->show();
//#endif

    connect(menu_area, SIGNAL(doubleClickPage(int)), list_area, SLOT(doubleClickPage(int)));
    connect(menu_area, SIGNAL(turnPage(int)), list_area, SLOT(turnPage(int)));
    connect(menu_area, SIGNAL(turnPage(int)), details_area, SLOT(OnTurnPageSlot(int)));
    connect(menu_area, SIGNAL(maxMinSet(bool)), this, SLOT(windowsChangeSlot(bool)));
    connect(details_area, SIGNAL(maxMinSet(bool)), this, SLOT(windowsChangeSlot(bool)));
    connect(list_area, SIGNAL(maxMinSet(bool)), this, SLOT(windowsChangeSlot(bool)));

    if ((_CardCaseListArea != NULL) && (_CardCaseDetailArea != NULL) && (_NoticeListArea != NULL) && (_NoticeDetailArea != NULL))
    {
        connect(_CardCaseDetailArea, SIGNAL(MessageSignal(TNMessageListAdapter, bool)),
                _NoticeListArea, SLOT(OnMessageSlot(TNMessageListAdapter, bool)));

        connect(_NoticeDetailArea, SIGNAL(MessageSignal(TNMessageListAdapter, bool)),
                _NoticeListArea, SLOT(OnMessageSlot(TNMessageListAdapter, bool)));

        connect(menu_area, SIGNAL(turnPage(int)), _NoticeDetailArea, SLOT(onTurnPage(int)));

        connect(_NoticeDetailArea, SIGNAL(unReadCountSignal(const QString &, int, int)), menu_area, SLOT(unReadCountSlot(const QString &, int,int)));
        connect(_NoticeListArea, SIGNAL(activeMenu(int)), menu_area, SLOT(slotTurnPage(int)));
        connect(_NoticeListArea, SIGNAL(activeMenu(int)), list_area, SLOT(turnPage(int)));
        connect(_NoticeListArea, SIGNAL(activeMenu(int)), details_area, SLOT(OnTurnPageSlot(int)));

        connect(_NoticeDetailArea, SIGNAL(messageNotify(TNMessageListAdapter, bool)), this, SLOT(onReceivedMessage(TNMessageListAdapter, bool)));
        connect(_CardCaseDetailArea, SIGNAL(MessageSignal(int)), menu_area, SLOT(slotTurnPage(int)));
        connect(_CardCaseDetailArea, SIGNAL(MessageSignal(int)), list_area, SLOT(turnPage(int)));
        connect(_CardCaseDetailArea, SIGNAL(MessageSignal(int)), details_area, SLOT(OnTurnPageSlot(int)));
        connect(_CardCaseListArea, SIGNAL(RemoveSessionInSessionList(const QString&)),
                _NoticeListArea, SLOT(slotRemoveSession(const QString&)));
        connect(_CardCaseListArea, SIGNAL(notifySessionList(QList<UINotifyData>, bool)),
                _NoticeListArea, SLOT(onUpdateSessionListAvatar(QList<UINotifyData>,bool)));
        connect(this, SIGNAL(MessageSignal(int)), menu_area, SLOT(slotTurnPage(int)));

        connect(_MineDetailArea, SIGNAL(MessageSignal(TNMessageListAdapter, bool)),
                _NoticeListArea, SLOT(OnMessageSlot(TNMessageListAdapter, bool)));
        connect(_MineDetailArea, SIGNAL(MessageSignal(int)), menu_area, SLOT(slotTurnPage(int)));
        connect(_MineDetailArea, SIGNAL(MessageSignal(int)), list_area, SLOT(turnPage(int)));
        connect(_MineDetailArea, SIGNAL(MessageSignal(int)), details_area, SLOT(OnTurnPageSlot(int)));
        connect(_MineListArea, SIGNAL(CloseDetailPage(const QString &, const QString&)), _MineDetailArea, SLOT(CloseDetailPage(const QString &, const QString&)));
		connect(list_area, SIGNAL(sendCurrentSelectedPage(int)), _MineListArea, SLOT(currentSelectedPage(int)));

        connect(this, SIGNAL(windowsChange(bool)), _CardCaseListArea, SLOT(hideSearchArea(bool)));
        connect(title_widget, SIGNAL(showMax(bool)), _CardCaseListArea, SLOT(hideSearchArea(bool)));
        connect(list_area, SIGNAL(turnPageSignal(bool)), _CardCaseListArea, SLOT(hideSearchArea(bool)));
        connect(this, SIGNAL(windowsChange(bool)), _NoticeListArea, SLOT(hideSearchArea()));
        connect(title_widget, SIGNAL(showMax(bool)), _NoticeListArea, SLOT(hideSearchArea()));
        connect(list_area, SIGNAL(turnPageSignal(bool)), _NoticeListArea, SLOT(hideSearchArea()));
		connect(list_area, SIGNAL(sendCurrentSelectedPage(int)), _CardCaseListArea, SLOT(currentSelectedPage(int)));

        connect(this, SIGNAL(initNoticeLocalSession()), _NoticeListArea, SLOT(initLocalSession()));
    }

	Q_ASSERT(_SetUpDetailArea);

    connect(_SetUpDetailArea, SIGNAL(SendQuitSignal()), this, SIGNAL(SendQuitSignal()));
    connect(title_widget, SIGNAL(showMin()), this, SLOT(showMinimized()));
    connect(title_widget, SIGNAL(showMax(bool)), this, SLOT(showMax(bool)));
    connect(title_widget, SIGNAL(closeWidget()), this, SLOT(closeWidget()));
    connect(this, SIGNAL(windowsChange(bool)), title_widget, SLOT(updateMaxStatus(bool)));

    _VersionCheckTimer.setSingleShot(false);
    _VersionCheckTimer.setInterval(3600000); //一小时检查一次
    _VersionCheckTimer.start();
    connect(&_VersionCheckTimer, SIGNAL(timeout()), this, SLOT(onVerionCheckTimerOut()));
#ifdef Q_OS_WIN
    qApp->installNativeEventFilter(this);
	_trayIco = new TNWinTrayManger(this, getTrayIco(), screenRect);
    Q_ASSERT(_trayIco);
    connect(_trayIco, SIGNAL(showWidget()), this, SLOT(showWidget()));
    connect(_trayIco, SIGNAL(MessageSignal(int)), menu_area, SLOT(slotTurnPage(int)));
    connect(_trayIco, SIGNAL(quitAppSignal()), this, SLOT(quitAppSlot()));


    connect(_trayIco, SIGNAL(updateUnRead(const QString &, bool)), _NoticeListArea, SLOT(slotUpdateSession(const QString &, bool)));
    connect(_NoticeListArea, SIGNAL(updateTrayUnRead(const QString &)), _trayIco, SLOT(updateUnReadFromNotice(const QString &)));
	connect(_NoticeDetailArea, SIGNAL(updateTrayUnRead(const QString &)), _trayIco, SLOT(updateUnReadFromNotice(const QString &)));
    connect(_NoticeListArea, SIGNAL(outlineUpdateUnreadTray(TNMessageListAdapter, int)), _trayIco, SLOT(outlineUpdateUnreadTraySlot(TNMessageListAdapter, int)));
    connect(_NoticeListArea, SIGNAL(manualNoAlarmNotifyTray(const QString & ,bool ,int )), _trayIco, SLOT(manualNoAlarm(const QString &, bool , int )));
    connect(_NoticeListArea, SIGNAL(manualRemoveCurrentSession(const QString &, bool)), _trayIco, SLOT(manualDeleteSession(const QString &, bool)));
	connect(_NoticeListArea, SIGNAL(manualModifySessionNameToTray(const QString &, const QString &)), _trayIco, SLOT(manualModifySessionName(const QString &, const QString &)));
    connect(this, SIGNAL(trayDClicked()), _NoticeListArea, SLOT(trayDoubleClickMsg()));
    connect(_NoticeListArea, SIGNAL(reduceUnReadTray(const QString &,int)), _trayIco, SLOT(reduceUnReadFromNotice(const QString &,int)));
	connect(_SetUpDetailArea, SIGNAL(updateSettingStatus(QString, int)), _trayIco, SLOT(updateSettingNoDisturbStatus(QString,int)));
#else
    system_tray = new SystemTray(this);

    connect(system_tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconIsActived(QSystemTrayIcon::ActivationReason)));
    connect(system_tray, SIGNAL(showWidget()), this, SLOT(showWidget()));
    connect(system_tray, SIGNAL(MessageSignal(int)), menu_area, SLOT(slotTurnPage(int)));

    _TwinkleTimer.setSingleShot(false);
    _TwinkleTimer.setInterval(350);
    connect(&_TwinkleTimer, SIGNAL(timeout()), this, SLOT(twinkleTrayIcon()));
	connect(_SetUpDetailArea, SIGNAL(updateSettingStatus(QString, int)), this, SLOT(updateSettingNoDisturbStatusMac(QString,int)));
    system_tray->show();
#endif
    /*
    更新本地数据库中的未读消息
    */
    emit initNoticeLocalSession();
    TNNotifyCenter::instance()->connnectNotifyCurrentFeedChanged(this);

    title_widget->installEventFilter(this);
    menu_area->installEventFilter(this);
    list_area->installEventFilter(this);
}

void Toon::tnLoadLibrary(int dimension)
{
    XmlPluginStructVec pluginStructVec = XmlSingleton::GetInstance()->GetEnablePluginsByDimension(dimension);
    if (pluginStructVec.size() == 0)
    {
        return;
    }
    std::vector<std::shared_ptr<XmlPluginStruct> >::iterator iter = pluginStructVec.begin();
    for (; iter != pluginStructVec.end(); iter++)
    {
        qInfo() << "[Toon][Toon]Toon::LoadLibrary: " << (*iter)->strName;
        QString lib_path;
#ifdef Q_OS_WIN
        lib_path = (*iter)->strName;
#else
        lib_path = QCoreApplication::applicationDirPath();
        lib_path += "/";
        lib_path += (*iter)->strName;
#endif
        QLibrary menuLib(lib_path);   //声明所用到的dll文件
        //判断是否正确加载
        if (menuLib.load())
        {
            GetMyMenu getMenu = (GetMyMenu)menuLib.resolve("getMenu");
            if (getMenu)
            {
                PluginExportBase *tempMenu = getMenu(TNUserDataHelper::GetInstance()->_pluginParam, this);
                tempMenu->registerToonCommand();
                if (tempMenu->GetID() == MENU_CARDCASE_ID)
                {
                    _CardCaseListArea = tempMenu->GetList();
                    _CardCaseDetailArea = tempMenu->GetDetails();
                }
                else if (tempMenu->GetID() == MENU_NOTICE_ID)
                {
                    _NoticeListArea = tempMenu->GetList();
                    _NoticeDetailArea = tempMenu->GetDetails();
                }
                else if (tempMenu->GetID() == MENU_MINE_ID)
                {
                    _MineListArea = tempMenu->GetList();
                    _MineDetailArea = tempMenu->GetDetails();
                }
                else if (tempMenu->GetID() == MENU_HOMEPAGE_ID)
                {
                    _HomePageListArea   = tempMenu->GetList();
                    _HomePageDetailArea = tempMenu->GetDetails();
                }
                else if (tempMenu->GetID() == MENU_SETUP_ID)
                {
                    _SetUpDetailArea = tempMenu->GetDetails();
                }
                menu_area->LoadMenuLibrary(tempMenu, dimension);
                list_area->LoadListLibrary(tempMenu, dimension);
                details_area->LoadDetailsLibrary(tempMenu, dimension);
            }
        }
        else
        {	//加载失败
            QString err_string = "load library error:" + menuLib.errorString();
            qInfo() << "[Toon][Toon]Toon::LoadLibrary: " << err_string;
        }
    }
}

void Toon::showWidget()
{
    if (!isMaximized())
        this->showNormal();
    else
        this->showMaximized();
    this->raise();
    this->activateWindow();
}

void Toon::onVerionCheckTimerOut()
{
    QtConcurrent::run([&]()
    {
        TNUpgradeMangement::instance()->checkNewVersion(TNUserDataHelper::GetInstance()->_pluginParam, TNUpgradeMangement::ctTimed);
    });
}

void Toon::onReceivedMessage(TNMessageListAdapter adapter, bool isNotice)
{
#ifdef Q_OS_WIN
	_trayIco->recieveMessage(adapter);
	FlashWindow((HWND)winId(), true);
#else
	if (!isActiveWindow()){
		startTrayNotifyMac();
	}
	playMediaTraySoundMac();
#endif
}
void Toon::keyPressEvent(QKeyEvent * e)
{
    if (e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter
		|| e->key() == Qt::Key_Down || e->key() == Qt::Key_Up){
		/*
		全局键盘事件
		*/
		TNNotifyCenter::instance()->postNotifyKeyEventDis(e->key());
        return;
    }else if(e->key() == Qt::Key_W && e->modifiers() == Qt::ControlModifier){
        if(isMaximized() || isFullScreen()){
            title_widget->setEnabledMinBtn(true);
            showNormal();
            title_widget->updateMaxStatus(false);
        }
        hide();
    }else if(e->key() == Qt::Key_M && e->modifiers() == Qt::ControlModifier){
        if(!isMaximized() && !isFullScreen()){
            showMinimized();
        }
    }
    return QWidget::keyPressEvent(e);
}
void Toon::showMax(bool status)
{
    if (status) {
#ifdef Q_OS_MAC
        showFullScreen();
        title_widget->setEnabledMinBtn(false);
#else
        showMaximized();
#endif
    }else {
        showNormal();
        title_widget->setEnabledMinBtn(true);
    }
}
void Toon::windowsChangeSlot(bool status)
{
#ifdef Q_OS_MAC
    status = isFullScreen();
#else
    status = isMaximized();
#endif
    showMax(!status);
    emit windowsChange(!status);
}
void Toon::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        QPoint windowPos = this->pos();
        QPoint mousePos = event->globalPos();
        _dPos = mousePos - windowPos;
        _moveAble = true;
    }else{
        _moveAble = false;
    }
    return QWidget::mousePressEvent(event);
}

void Toon::mouseMoveEvent(QMouseEvent *event)
{
    if(_moveAble){
        if(isMaximized() || isFullScreen()){
            return;
        }
        this->move(event->globalPos() - this->_dPos);
    }
    return QWidget::mouseMoveEvent(event);
}

void Toon::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        _moveAble = false;
    }
}

void Toon::paintEvent(QPaintEvent * event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

bool Toon::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
#ifdef Q_OS_WIN
    MSG* native_message = static_cast<MSG*>(message);
    switch (native_message->message)
    {
    case WM_NCHITTEST:
        int xPos = GET_X_LPARAM(native_message->lParam) - this->frameGeometry().x();
        int yPos = GET_Y_LPARAM(native_message->lParam) - this->frameGeometry().y();
        if (xPos > 0 && xPos < 10 && yPos >(this->height() - 10) && yPos < (this->height()))
            *result = HTBOTTOMLEFT;
        else if (xPos >(this->width() - 10) && xPos < (this->width()) && yPos >(this->height() - 10) && yPos < (this->height()))
            *result = HTBOTTOMRIGHT;
        else if (xPos > 0 && xPos < 10 && yPos > 0 && yPos < 10)
            *result = HTTOPLEFT;
        else if (xPos >(this->width() - 10) && xPos < (this->width()) && yPos > 0 && yPos < 10)
            *result = HTTOPRIGHT;
        else if (xPos > -5 && xPos < 5)
            *result = HTLEFT;
        else if (xPos > (this->width() - 3) && xPos < (this->width() + 7))
            *result = HTRIGHT;
        else if (yPos > -5 && yPos < 5)
            *result = HTTOP;
        else if (yPos >(this->height() - 5) && yPos < (this->height() + 5))
            *result = HTBOTTOM;
        else
            return false;
        return true;
    }
#endif
    return false;
}

void Toon::closeEvent(QCloseEvent *event)
{
    qInfo() << "[Toon][Toon]Recieve close event";
    event->ignore();
    hide();
}


void Toon::closeWidget()
{
    hide();
}

void Toon::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
#ifdef Q_OS_WIN
	int x = this->width() - title_widget->width();
	int y = 1;
	int w = title_widget->width();
	int h = title_widget->height();
	title_widget->setGeometry(x, y, w, h);
#endif
}

void Toon::mouseDoubleClickEvent(QMouseEvent *event)
{
#ifdef Q_OS_MAC
    if (isMaximized() || isFullScreen()){
        title_widget->updateMaxStatus(false);
        showNormal();
        title_widget->setEnabledMinBtn(true);
    }
#endif
    return QWidget::mouseDoubleClickEvent(event);
}
const QString Toon::getTrayIco()
{
    return TNVersionInfo::GetSystemTrayRes();
}

bool Toon::nativeEventFilter(const QByteArray & eventType, void * message, long * result)
{
#ifdef Q_OS_WIN
    if (eventType == "windows_generic_MSG" || eventType == "windows_dispatcher_MSG")
    {
        if (_trayIco == nullptr)
            return false;
        MSG * pMsg = reinterpret_cast<MSG *>(message);
        if (pMsg->message == WM_TRAYNOTIFY)
        {
            switch (pMsg->lParam)
            {
            case WM_MOUSEMOVE:
                _trayIco->mouseMove();
                break;
            case WM_MOUSEHOVER:
                _trayIco->mouseHover();
                break;
            case WM_MOUSELEAVE:
                _trayIco->mouseLeave(cursor().pos());
                qDebug() << "Hover leave hit";
                break;
            case WM_LBUTTONDBLCLK:
                //_trayIco->trayHide();
                if (!isActiveWindow())
                {
                    showWidget();
                }
				emit MessageSignal(MENU_NOTICE_ID);
                emit trayDClicked();
                qDebug() << "WM_LBUTTONDBLCLK";
                break;
            case WM_LBUTTONDOWN:
                showWidget();
                break;
            case WM_RBUTTONDOWN:
                _trayIco->showMenu(QCursor::pos());
                break;
            }
        }
    }
#endif
    return false;
}

#ifdef Q_OS_WIN
void Toon::quitAppSlot()
{
    TNDataStatistics::RecordFuncStatisData(FUNC_TYPE_Tray_Logout, TNUserDataHelper::GetInstance()->_pluginParam);
    qApp->quit();
}
#endif

void Toon::on_notifyCurrentFeedChanged(const QString & feedID)
{
    qInfo() << "[Toon][Toon] on_notifyCurrentFeedChanged :" << feedID;
    if (feedID == AVATAR_ALL_FEED)
        return;
}
#ifndef Q_OS_WIN
void Toon::twinkleTrayIcon()
{
    if (system_tray->icon().isNull())
    {
        system_tray->setIcon(QIcon(getTrayIco()));
    }
    else
    {
        system_tray->setIcon(QIcon());
    }
}
bool Toon::event(QEvent *event)
{
    if (event->type() == QEvent::WindowActivate)
    {
		stopTrayNotifyMac();
    }
    return QWidget::event(event);
}
void Toon::iconIsActived(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    //点击托盘图标之后松开
    case QSystemTrayIcon::Trigger:
        showWidget();
        break;
        //双击托盘图标
    case QSystemTrayIcon::DoubleClick:
        showWidget();
        break;
    default:
        break;
    }
}
#endif

bool Toon::eventFilter(QObject *target, QEvent *event)
{
    if ((target == title_widget) || (target == menu_area) || (target == list_area))
    {
        if (event->type() == QEvent::FocusIn)
        {
            emit TNNotifyCenter::instance()->signalHideGroupChatMemberWidget();
        }
    }

    return QWidget::eventFilter(target, event);
}
#ifndef Q_OS_WIN
void Toon::updateSettingNoDisturbStatusMac(QString fun, int status)
{
	qInfo() << "[Toon]updateSettingNoDisturbStatusMac :" << status;
	if (fun == "NoDisturbing")
	{
		_settingNoDisturnStatusMac = status;
		/*
		停止闪烁
		*/
		if (_settingNoDisturnStatusMac)
			stopTrayNotifyMac();
	}
}
void Toon::startTrayNotifyMac()
{
	if(!_settingNoDisturnStatusMac){
		_TwinkleTimer.start();
	}
}
void Toon::stopTrayNotifyMac()
{
	_TwinkleTimer.stop();
	system_tray->setIcon(QIcon(getTrayIco()));
}
void Toon::playMediaTraySoundMac()
{
	if (!_settingNoDisturnStatusMac)
	{
		//收到消息
        if(_player->isFinished())
            _player->play();
	}
}
#endif
