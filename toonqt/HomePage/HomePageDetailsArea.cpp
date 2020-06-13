#include "HomePageDetailsArea.h"
#include "ui_HomePageDetailsArea.h"

#include <QUrl>
#include <QLabel>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QWebEngineView>

#include "TNWebEnginePage.h"

HomePageDetailsArea::HomePageDetailsArea(int id, TNPluginParamPtr pluginParam, QWidget *parent)
    : DetailsAreaBase(id, parent)
    , ui(new Ui::HomePageDetailsArea)
    , m_pluginParam(pluginParam)
{
    ui->setupUi(this);

    m_stackedWidget = new QStackedWidget(this);
    m_stackedWidget->setObjectName("stackedWidget");
    m_stackedWidget->setContentsMargins(0, 0, 0, 0);

    initHomePageWidget();
    initDefaultPageWidget();

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(m_stackedWidget);

    this->setLayout(mainLayout);

    setCurrentPage(1);
}

void HomePageDetailsArea::initHomePageWidget()
{
    QWidget *homePageWidget = new QWidget;
    homePageWidget->setContentsMargins(0, 0, 0, 0);

    QWidget *titleWidget = new QWidget();
    titleWidget->setObjectName("homepageWidget");
    m_titleLabel = new QLabel("");
    //m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setObjectName("homepageTitle");
    QHBoxLayout *titleLayout = new QHBoxLayout();
    titleLayout->setSpacing(0);
    titleLayout->setContentsMargins(0, 0, 0, 0);
    titleLayout->addWidget(m_titleLabel);
    titleWidget->setLayout(titleLayout);

    m_webEngineView = new QWebEngineView();
    TNWebEnginePage *webPage = new TNWebEnginePage(this);
    m_webEngineView->setPage(webPage);
    connect(m_webEngineView, SIGNAL(loadFinished(bool)), this, SLOT(slotLoadUrlFinished(bool)));

    QVBoxLayout *homePageLayout = new QVBoxLayout(this);
    homePageLayout->setSpacing(0);
    homePageLayout->setContentsMargins(0, 0, 0, 0);
    homePageLayout->addWidget(titleWidget);
    homePageLayout->addWidget(m_webEngineView);

    homePageWidget->setLayout(homePageLayout);

    m_stackedWidget->addWidget(homePageWidget);
}

void HomePageDetailsArea::initDefaultPageWidget()
{
    QWidget *defaultPageWidget = new QWidget;
    defaultPageWidget->setContentsMargins(0, 0, 0, 0);

    QGridLayout *defaultPageLayout = new QGridLayout(this);
    QLabel *label_default_backpic = new QLabel(this);
    label_default_backpic->setFixedSize(200, 124);
    label_default_backpic->setObjectName("label_default_backpic");
    defaultPageLayout->addWidget(new QLabel(this), 0, 0);
    defaultPageLayout->addWidget(new QLabel(this), 0, 1);
    defaultPageLayout->addWidget(new QLabel(this), 0, 2);
    defaultPageLayout->addWidget(new QLabel(this), 1, 0);
    defaultPageLayout->addWidget(label_default_backpic, 1, 1);
    defaultPageLayout->addWidget(new QLabel(this), 1, 2);
    defaultPageLayout->addWidget(new QLabel(this), 2, 0);
    defaultPageLayout->addWidget(new QLabel(this), 2, 1);
    defaultPageLayout->addWidget(new QLabel(this), 2, 2);
    defaultPageWidget->setLayout(defaultPageLayout);

    m_stackedWidget->addWidget(defaultPageWidget);
}

HomePageDetailsArea::~HomePageDetailsArea()
{
    delete ui;
}

void HomePageDetailsArea::setCurrentPage(int pageIndex)
{
    m_stackedWidget->setCurrentIndex(pageIndex);
}

void HomePageDetailsArea::setUrl(const QString &title, const QString &url)
{
    setCurrentPage(0);
    qInfo()<<"HomePageDetailsArea-title="<<title<<" url="<<url;
    m_titleLabel->setText(title);
    if (m_webEngineView->url() == QUrl(url))
        return;
    m_webEngineView->setUrl(QUrl(url));
}

void HomePageDetailsArea::slotShowHome(const QString &title, const QString &url)
{
    setUrl(title, url);
}

void HomePageDetailsArea::slotLoadUrlFinished(bool ok)
{
    if (ok)
    {
        //m_titleLabel->setText(m_webEngineView->title());
    }
    else
    {
        qInfo() << "[HomePage][HomePageDetailsArea]slotLoadUrlFinished load web failed.";
    }
}
