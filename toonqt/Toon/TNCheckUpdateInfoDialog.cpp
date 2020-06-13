#include "TNCheckUpdateInfoDialog.h"
#include "ui_TNCheckUpdateInfoDialog.h"

#include <QDebug>
#include <QProcess>
#include <QDesktopServices>

#include "TNUpgradePlatform.h"
#include "TNConfig.h"
#include "TNVersionInfo.h"
TNCheckUpdateInfoDialog::TNCheckUpdateInfoDialog(
        bool isForceUpgrade,
        QString downLoadURL,
        QString versionDesc,
        QWidget *parent)
    : DropShadowWidget(parent)
    , _downLoadURL(downLoadURL)
    , ui(new Ui::TNCheckUpdateInfoDialog)
{
    ui->setupUi(this);

    ui->textEdit->setPlainText(versionDesc);
    ui->nowButton->setObjectName("okButton");
    ui->quitButton->setObjectName("dialogCloseButton");
    ui->afterButton->setObjectName("dialogCloseButton");

    connect(ui->nowButton, SIGNAL(clicked()), this, SLOT(slotNowUpgrade()));
    connect(ui->quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(ui->afterButton, SIGNAL(clicked()), this, SLOT(slotRemindAfter()));

    if (isForceUpgrade)
    {
        //强制升级时, 将“退出软件”按钮显示, 隐藏掉“稍后提醒”按钮
        ui->quitButton->setVisible(true);
        ui->afterButton->setVisible(false);
    }
    else
    {
        ui->quitButton->setVisible(false);
        ui->afterButton->setVisible(true);
    }

    this->setWindowIcon(TOON_ICON);
    this->setWindowTitle(TOON_TITLE);
}

TNCheckUpdateInfoDialog::~TNCheckUpdateInfoDialog()
{
    delete ui;
}

void TNCheckUpdateInfoDialog::slotNowUpgrade()
{
    DropShadowWidget::accept();
    if ((TNUpgradePlatform::getPlatformName() == TNUpgradePlatform::win32PlatformName())
            || (TNUpgradePlatform::getPlatformName() == TNUpgradePlatform::win64PlatformName()))
    {
        TNConfig::instance()->setRemindLater(false);
        doUpgrade();
    }
    else //if (TNUpgradePlatform::getPlatformName() == TNUpgradePlatform::macPlatformName())
    {
        QDesktopServices::openUrl(QUrl(_downLoadURL));
        //qApp->quit();
    }
}

void TNCheckUpdateInfoDialog::slotRemindAfter()
{
    //稍后提醒保存到配置文件
    TNConfig::instance()->setRemindLater(true);
    DropShadowWidget::accept();
}

void TNCheckUpdateInfoDialog::closeEvent(QCloseEvent *event)
{
	qInfo() << "[Toon][TNCheckUpdateInfoDialog]closeEvent Recieve TNCheckUpdateInfoDialog close event";
    DropShadowWidget::closeEvent(event);
    qApp->quit();
}

void TNCheckUpdateInfoDialog::doUpgrade()
{
    QString exePath = qApp->applicationDirPath() + "/upgrade.exe";
    QStringList args;
    args << exePath << _downLoadURL;
    QProcess::startDetached(exePath, args);
    qApp->quit();
}
