#ifndef TOON_H
#define TOON_H

#include <QtWidgets/QMainWindow>
#include <QTranslator>
#include <QTimer>
#include <QEvent>
#include <QPainter>
#include <QtCore/QAbstractNativeEventFilter>
#include <QListView>
#include "common.h"
#include "TitleWidget.h"
#include "DropShadowWidget.h"
#include "MenuArea.h"
#include "ListArea.h"
#include "DetailsArea.h"
#include "TNDataStatistics.h"
#include "TNUserDataHelper.h"
#include "SystemTray.h"
#ifdef Q_OS_WIN
#include "unReadList\TNWinTrayManger.h"
#else
#include <QSound>
#endif

class Toon : public QWidget, QAbstractNativeEventFilter
{
    Q_OBJECT
public:
    Toon(QWidget *parent = 0);
    ~Toon();

    void init();

private:
    const QString getTrayIco();

Q_SIGNALS:
    void SendQuitSignal();
    void windowsChange(bool status);
    void MessageSignal(int);
    void initNoticeLocalSession();
    void trayDClicked();

private slots:
    void onVerionCheckTimerOut();
    void onReceivedMessage(TNMessageListAdapter adapter, bool isNotice);
    void showMax(bool status);
    void closeWidget();

#ifndef Q_OS_WIN
    void twinkleTrayIcon();
    void iconIsActived(QSystemTrayIcon::ActivationReason reason);
	void startTrayNotifyMac();
	void stopTrayNotifyMac();
	void playMediaTraySoundMac();
#endif

public slots:
    void showWidget();
    void windowsChangeSlot(bool status);
    void on_notifyCurrentFeedChanged(const QString & feedID);

#ifdef Q_OS_WIN
    void quitAppSlot();
#else
	void updateSettingNoDisturbStatusMac(QString fun, int status);
#endif

protected:
#ifndef Q_OS_WIN
    bool event(QEvent *event);
#endif
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
    virtual void closeEvent(QCloseEvent *event);
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    void resizeEvent(QResizeEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    virtual bool nativeEventFilter(const QByteArray &, void *, long *);
    virtual bool eventFilter(QObject *target, QEvent *event);

private:
    void tnLoadLibrary(int dimension);

private:
    /// <summary>	标题栏. </summary>
    TitleWidget *title_widget = NULL;
    /// <summary>	菜单区. </summary>
    MenuArea * menu_area = NULL;
    /// <summary>	列表区. </summary>
    ListArea * list_area = NULL;
    /// <summary>	详情区. </summary>
    DetailsArea * details_area = NULL;

    // 通讯录
    ListAreaBase * _CardCaseListArea;
    DetailsAreaBase * _CardCaseDetailArea;
    // 通知
    ListAreaBase * _NoticeListArea;
    DetailsAreaBase * _NoticeDetailArea;
    // 我的
    ListAreaBase * _MineListArea;
    DetailsAreaBase * _MineDetailArea;
    // 主页
    ListAreaBase *_HomePageListArea;
    DetailsAreaBase *_HomePageDetailArea;
    // 设置
    DetailsAreaBase *_SetUpDetailArea;

    // 检查更新用计时器
    QTimer _VersionCheckTimer;

    //pos
    QPoint   _dPos;
    bool     _moveAble;
#ifdef Q_OS_WIN
    TNWinTrayManger * _trayIco;
#else
    SystemTray      * system_tray = NULL;
    QTimer           _TwinkleTimer;
	bool             _settingNoDisturnStatusMac;
    QSound			*_player;
#endif
};

#endif // TOON_H
