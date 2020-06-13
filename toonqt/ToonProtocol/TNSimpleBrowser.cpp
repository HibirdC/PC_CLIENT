#include "TNSimpleBrowser.h"
#include "ui_TNSimpleBrowser.h"

#include "TNUtil.h"
#include "TNNameSpace.h"
#include "TNWebEnginePage.h"
#include "TNWebEngineUrlRequestInterceptor.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QWebEngineHistory>
#include <QMessageBox>
#include <QMutex>
#include "TNToonCommandManager.h"
#include "TNUploadPhotoCommand.h"
#include "TNZoomFactor.h"
#include "NetWorkAPI_global.h"
#include "TNDataCache.h"
#include "TNVersionInfo.h"
#include "TNConfig.h"
#ifdef Q_OS_WIN
#include <Windows.h>
#endif

TNSimpleBrowser *TNSimpleBrowser::m_instance = 0;

TNSimpleBrowser *TNSimpleBrowser::getInstance()
{
    static QMutex mutex;

    if (m_instance == 0)
    {
        mutex.lock();
        m_instance = new TNSimpleBrowser();
        TNUtil::moveCenterInMainWidget(m_instance);
        mutex.unlock();
    }

    return m_instance;
}

TNSimpleBrowser::TNSimpleBrowser(QWidget *parent) :
    /*QDialog*/DropShadowWidget(parent),
    ui(new Ui::TNSimpleBrowser)
{
    ui->setupUi(this);
	setAttribute(Qt::WA_QuitOnClose, false);
    QWidget *titltWidget = new QWidget(this);
    titltWidget->setObjectName("browserTitle");

    m_backButton = new QPushButton(QStringLiteral(""));
    m_forwardButton = new QPushButton(QStringLiteral(""));
    m_freshButton = new QPushButton(QStringLiteral(""));
    m_minButton   = new QPushButton(QStringLiteral(""));
    m_maxButton   = new QPushButton(QStringLiteral(""));
    m_closeButton = new QPushButton(QStringLiteral(""));
    m_backButton->setObjectName("bs_backButton");
    m_forwardButton->setObjectName("bs_forwardButton");
    m_freshButton->setObjectName("bs_freshButton");

#ifdef Q_OS_WIN
    m_minButton->setObjectName("bs_minButton");
    m_maxButton->setObjectName("bs_maxButton");
    m_closeButton->setObjectName("bs_closeButton");
#else
    m_minButton->setObjectName("mac_bs_minButton");
    m_maxButton->setObjectName("mac_bs_maxButton");
    m_closeButton->setObjectName("mac_bs_closeButton");
#endif


    m_maxButton->setCheckable(true);
    m_maxButton->setChecked(false);

    connect(m_backButton, SIGNAL(clicked()), this, SLOT(slotBack()));
    connect(m_forwardButton, SIGNAL(clicked()), this, SLOT(slotForward()));
    connect(m_freshButton, SIGNAL(clicked()), this, SLOT(slotFresh()));
    connect(m_minButton, SIGNAL(clicked()), this, SLOT(slotMinimum()));
    connect(m_maxButton, SIGNAL(clicked(bool)), this, SLOT(slotMaximum(bool)));
    connect(m_closeButton, SIGNAL(clicked()), this, SLOT(slotClose()));

    QHBoxLayout *buttonLayOut = new QHBoxLayout();
#ifdef Q_OS_WIN
    buttonLayOut->setSpacing(15);
    buttonLayOut->setContentsMargins(20, 5, 20, 5);
    buttonLayOut->addWidget(m_backButton);
    buttonLayOut->addWidget(m_forwardButton);
    buttonLayOut->addWidget(m_freshButton);
    buttonLayOut->addSpacerItem(new QSpacerItem(40, 20));
    buttonLayOut->addWidget(m_minButton);
    buttonLayOut->addWidget(m_maxButton);
    buttonLayOut->addWidget(m_closeButton);
    buttonLayOut->setStretch(3, 1);
#else
    buttonLayOut->setSpacing(20);
    buttonLayOut->setContentsMargins(20, 5, 20, 5);
    buttonLayOut->addWidget(m_closeButton);
    buttonLayOut->addWidget(m_minButton);
    buttonLayOut->addWidget(m_maxButton);
    buttonLayOut->addSpacerItem(new QSpacerItem(40, 20));
    buttonLayOut->addWidget(m_backButton);
    buttonLayOut->addWidget(m_forwardButton);
    buttonLayOut->addWidget(m_freshButton);
    buttonLayOut->setStretch(3, 1);
#endif


    titltWidget->setLayout(buttonLayOut);

    m_webEngineView = new QWebEngineView();
    //m_webEngineView->setZoomFactor(TNZoomFactor::GetAppFactor());
    m_webEngineView->setContextMenuPolicy(Qt::NoContextMenu);
    m_webChannel = new QWebChannel();

    m_webChannel->registerObject(QStringLiteral("TNBrowserContent"), &m_content);
    TNWebEnginePage *webPage = new TNWebEnginePage(this);
    m_webEngineView->setPage(webPage);
    m_webEngineView->page()->setWebChannel(m_webChannel);
    m_webEngineView->page()->profile()->setHttpUserAgent(HttpUserAgent_H5);
    m_webEngineView->page()->profile()->setRequestInterceptor(TNWebEngineUrlRequestInterceptor::getInstance());
    connect(m_webEngineView, SIGNAL(loadFinished(bool)), this, SLOT(slotSendDataToH5(bool)));
    connect(&m_content, SIGNAL(sendReceiveText(const QString &)), this, SIGNAL(sendReceivedTextFromH5(const QString &)));

    QVBoxLayout *mainLayOut = new QVBoxLayout(this);
    mainLayOut->setSpacing(0);
    mainLayOut->setContentsMargins(0, 0, 0, 0);
    mainLayOut->addWidget(titltWidget);
    mainLayOut->addWidget(m_webEngineView);

    this->setLayout(mainLayOut);
#ifdef Q_OS_WIN
    this->setObjectName("browserWidget");
    this->setContentsMargins(1, 1, 1, 1);
#else
    this->setObjectName("MacBrowserWidget");
    this->setContentsMargins(0, 0, 0, 0);
#endif
    this->resize(440, 630);
    this->setWindowFlags(Qt::FramelessWindowHint);

    this->setWindowIcon(TOON_ICON);
    this->setWindowTitle(TOON_TITLE);

    TNToonCommandManager::instance()->registerToonCommand(QString("mwap/window"), TNAbstractToonCommandPtr(new CloseH5WindowCommand()));
    TNToonCommandManager::instance()->registerToonCommand(QString("mwap/network"), TNAbstractToonCommandPtr(new CheckNetwokCommand()));
    TNToonCommandManager::instance()->registerToonCommand(QString("mwap/photo"), TNAbstractToonCommandPtr(new TNUploadPhotoCommand()));
}

TNSimpleBrowser::~TNSimpleBrowser()
{
    delete ui;
}

void TNSimpleBrowser::setPluginParam(const TNPluginParamPtr &pluginParam)
{
    m_pluginParam = pluginParam;
}

void TNSimpleBrowser::freeInstance()
{
    if (m_instance)
    {
        m_instance->close();
        delete m_instance;
        m_instance = 0;
    }
}

void TNSimpleBrowser::setUrl(const QString &url)
{
    m_time.restart();

    if (QUrl(url) == m_webEngineView->page()->url())
        return;

    m_webEngineView->page()->setUrl(QUrl(url));
}

void TNSimpleBrowser::showOnTop()
{
    if (this->isMinimized())
    {
        this->showNormal();
    }
    //设置窗口置顶
#ifdef Q_OS_WIN
    ::SetWindowPos(HWND(this->winId()), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
    ::SetWindowPos(HWND(this->winId()), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
#endif

#ifdef Q_OS_MAC
    this->raise();
#endif

    this->show();
    this->activateWindow();
}

void TNSimpleBrowser::slotBack()
{
    m_webEngineView->page()->triggerAction(QWebEnginePage::Back);
}

void TNSimpleBrowser::slotForward()
{
    m_webEngineView->page()->triggerAction(QWebEnginePage::Forward);
}

void TNSimpleBrowser::slotFresh()
{
    m_webEngineView->page()->triggerAction(QWebEnginePage::Reload);
}

void TNSimpleBrowser::slotMinimum()
{
    this->showMinimized();
}

void TNSimpleBrowser::slotMaximum(bool checked)
{
    if (checked)
    {
        //this->setContentsMargins(0, 0, 0, 0);
        this->showMaximized();
    }
    else
    {
        //this->setContentsMargins(20, 20, 20, 20);
        this->showNormal();
    }
}

void TNSimpleBrowser::slotClose()
{
    this->close();
    freeInstance();
}

void TNSimpleBrowser::slotSendDataToH5(bool ok)
{
    if (ok)
    {
        QString url = m_webEngineView->page()->url().toString();
        qDebug() << "slotSendDataToH5-url=" << url;
        if (m_pluginParam)
        {
            QJsonObject text;
            int languageIndex = int(TNConfig::instance()->GetCurrentLangueSet());
            text.insert("language", languageIndex);
            text.insert("toonType", APPTYPE);
            text.insert("userId", m_pluginParam->strTnUserID);
            text.insert("userToken", m_pluginParam->strTnUserToken);
            text.insert("userAgent", m_pluginParam->strTnUserAgent);

            QJsonArray cardArray;
            QList<st_FeedPtr> myAllStuff;
            TNDataCache::GetInstance()->getMyStuff(myAllStuff);
            for (st_FeedPtr card : myAllStuff)
            {
                QJsonObject aCardJson;
                aCardJson.insert("feedId", card->GetFeedID());
                aCardJson.insert("feedName", card->GetTitle());
                aCardJson.insert("feedAvatar", card->GetAvatarID());
                cardArray.append(aCardJson);
            }
            text.insert("feedList", cardArray);

            m_content.setSendTextText(text);
            qInfo() << "[ToonProtocol][TNSimpleBrowser]User info data json to web.";
        }
    }
    else
    {
        qInfo()  << "[ToonProtocol][TNSimpleBrowser]slotSendDataToH5 load web failed.";
    }

    qInfo() << "[ToonProtocol][TNSimpleBrowser]webtime=" << m_time.elapsed();
}

void TNSimpleBrowser::resizeEvent(QResizeEvent *event)
{
#ifdef Q_OS_MAC
    if (isMaximized())
    {
        m_minButton->setEnabled(false);
    }
    else
    {
        m_minButton->setEnabled(true);
    }
#endif // Q_OS_MAC
    DropShadowWidget::resizeEvent(event);
}
