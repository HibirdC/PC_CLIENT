#include "TNDownloadProgressDialog.h"
#include "ui_TNDownloadProgressDialog.h"

#include "TNPathUtil.h"
#include "TNZipCommon.h"
#include <QProcess>
#include <QClipboard>
#include <QDesktopServices>

#define UNIT_KB	1024			//KB
#define UNIT_MB 1024*1024		//MB
#define UNIT_GB 1024*1024*1024	//GB

#define TIME_INTERVAL 500		//0.5s

// 转换单位;
static QString transformUnit(qint64 bytes , bool isSpeed = false)
{
    QString strUnit = " B";
    if (bytes <= 0)
    {
        bytes = 0;
    }
    else if (bytes < UNIT_KB)
    {
    }
    else if (bytes < UNIT_MB)
    {
        bytes /= UNIT_KB;
        strUnit = " KB";
    }
    else if (bytes < UNIT_GB)
    {
        bytes /= UNIT_MB;
        strUnit = " MB";
    }
    else if (bytes > UNIT_GB)
    {
        bytes /= UNIT_GB;
        strUnit = " GB";
    }

    if (isSpeed)
    {
        strUnit += "/S";
    }
    return QString("%1%2").arg(bytes).arg(strUnit);
}

static QString transformTime(qint64 seconds)
{
    QString strValue;
    QString strSpacing(" ");
    if (seconds <= 0)
    {
        strValue = QString("%1s").arg(0);
    }
    else if (seconds < 60)
    {
        strValue = QString("%1s").arg(seconds);
    }
    else if (seconds < 60 * 60)
    {
        int nMinute = seconds / 60;
        int nSecond = seconds - nMinute * 60;

        strValue = QString("%1m").arg(nMinute);

        if (nSecond > 0)
            strValue += strSpacing + QString("%1s").arg(nSecond);
    }
    else if (seconds < 60 * 60 * 24)
    {
        int nHour = seconds / (60 * 60);
        int nMinute = (seconds - nHour * 60 * 60) / 60;
        int nSecond = seconds - nHour * 60 * 60 - nMinute * 60;

        strValue = QString("%1h").arg(nHour);

        if (nMinute > 0)
            strValue += strSpacing + QString("%1m").arg(nMinute);

        if (nSecond > 0)
            strValue += strSpacing + QString("%1s").arg(nSecond);
    }
    else
    {
        int nDay = seconds / (60 * 60 * 24);
        int nHour = (seconds - nDay * 60 * 60 * 24) / (60 * 60);
        int nMinute = (seconds - nDay * 60 * 60 * 24 - nHour * 60 * 60) / 60;
        int nSecond = seconds - nDay * 60 * 60 * 24 - nHour * 60 * 60 - nMinute * 60;

        strValue = QString("%1d").arg(nDay);

        if (nHour > 0)
            strValue += strSpacing + QString("%1h").arg(nHour);

        if (nMinute > 0)
            strValue += strSpacing + QString("%1m").arg(nMinute);

        if (nSecond > 0)
            strValue += strSpacing + QString("%1s").arg(nSecond);
    }

    return strValue;
}

TNDownloadProgressDialog::TNDownloadProgressDialog(QWidget *parent) :
    /*QDialog*/DropShadowWidget(parent)
  , ui(new Ui::TNDownloadProgressDialog)
  , m_lastTime(0)
  , m_currentDownload(0)
  , m_intervalDownload(0)
{
    ui->setupUi(this);

    m_downloadManager = new DownLoadManager(this);
    m_downloadManager->setDownInto(true);
    connect(m_downloadManager , SIGNAL(signalDownloadProcess(qint64, qint64)), this, SLOT(onDownloadProcess(qint64, qint64)));
    connect(m_downloadManager, SIGNAL(signalReplyFinished(int, QString)), this, SLOT(onReplyFinished(int, QString)));
    connect(m_downloadManager, SIGNAL(signalDownloadError(QNetworkReply::NetworkError)), this, SLOT(slotHandleError(QNetworkReply::NetworkError)));

    connect(ui->reDownLoadButton, SIGNAL(clicked()), this, SLOT(slotDownLoaAgain()));
    connect(ui->fromBrownserButton, SIGNAL(clicked()), this, SLOT(slotFromDesktopBrownser()));
    connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(close()));

    ui->reDownLoadButton->hide();
    ui->fromBrownserButton->hide();
    ui->closeButton->setText(QString::null);
    ui->progressBar->setRange(0, 0);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowIcon(QIcon(":/sysIcon/Resources/img/sysIcon//windowsicon.png"));
    this->setWindowTitle(tr(QStringLiteral("升级程序").toUtf8().data()));
}

TNDownloadProgressDialog::~TNDownloadProgressDialog()
{
    delete ui;
}

void TNDownloadProgressDialog::startDownLoad(const QString &url)
{
    m_url = url;
    m_downloadManager->reset();
    m_timeRecord.restart();
    m_lastTime = 0;
    m_currentDownload = 0;
    m_downloadManager->downloadFile(url);
    ui->confirmTitleLabel->setText(tr(QStringLiteral("升级程序正在运行......").toUtf8().data()));
    ui->reDownLoadButton->hide();
    ui->fromBrownserButton->hide();
    this->setFixedSize(350, 168);
}

void TNDownloadProgressDialog::slotDownLoaAgain()
{
    qDebug()<<"slotDownLoaAgain-m_url="<<m_url;
    startDownLoad(m_url);
}

void TNDownloadProgressDialog::slotFromDesktopBrownser()
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(m_url);
    qDebug()<<"slotFromDesktopBrownser-m_url="<<m_url;
    QDesktopServices::openUrl(QUrl(m_url));
}

void TNDownloadProgressDialog::onDownloadProcess(qint64 bytesReceived, qint64 bytesTotal)
{
    qDebug()<<"bytesReceived="<<bytesReceived<<" bytesTotal="<<bytesTotal<<" percent="<<QString("%1").arg(bytesReceived * 100 / bytesTotal);

    // 超过0.5s更新一次速度;
    m_intervalDownload += bytesReceived - m_currentDownload;
    m_currentDownload = bytesReceived;
    int timeNow = m_timeRecord.elapsed();
    if (timeNow - m_lastTime > TIME_INTERVAL)
    {
        // 当前速度
        qint64 ispeed = m_intervalDownload * 1000 / (timeNow - m_lastTime);
        QString strSpeed = transformUnit(ispeed, true);
        ui->speedLabel->setText(strSpeed);

        if (bytesTotal == -1)
        {
            // 如果不知道总大小，则显示当前已经下载的文件大小
            ui->downloadedLabel->setText(transformUnit(m_currentDownload));
        }
        else
        {
            // 显示文件总大小
            ui->downloadedLabel->setText(transformUnit(bytesTotal));
        }

        m_intervalDownload = 0;
        m_lastTime = timeNow;
    }

    if (bytesReceived == bytesTotal)
    {
        ui->downloadedLabel->setText(transformUnit(bytesTotal));
        ui->unknownSizeLabel->setIndent(250);
        ui->unknownSizeLabel->setText("100%");
    }

    // 更新进度条
    ui->progressBar->setMaximum(bytesTotal);
    ui->progressBar->setValue(bytesReceived);
    ui->progressBar->update();

    if (bytesTotal == -1)
    {
        ui->unknownSizeLabel->hide();
    }
    else
    {
        int x = double(bytesReceived)/(bytesTotal)*290;
        if (x>250)
            x = 250;
        ui->unknownSizeLabel->setIndent(x);
        ui->unknownSizeLabel->setText(ui->progressBar->text());
    }
}

void TNDownloadProgressDialog::onReplyFinished(int statusCode, const QString &zipFileName)
{
    qDebug()<<"downloadFile-time="<<m_timeRecord.elapsed();
    qDebug()<<"statusCode="<<statusCode;
    if (statusCode >= 200 && statusCode < 400)
    {
        qDebug()<<"==========================upgradeStart-zipFileName="<<zipFileName;
        qDebug()<<"==========================upgradeStart-zipFolder="<<TNPathUtil::getInstallPackageFile();
        QTime time;
        time.start();
        bool zipOk = TNZipCommon::unZlibFile(zipFileName, TNPathUtil::getInstallPackageFile());
        qDebug()<<"==========================upgradeStart-zip-time="<<time.elapsed();
        if (zipOk)
        {
            ui->confirmTitleLabel->setText(tr(QStringLiteral("文件解压成功.正在启动安装文件，请稍候...").toUtf8().data()));
            qDebug() << "unZlibFile ok!";
        }
        else
        {
            ui->confirmTitleLabel->setText(tr(QStringLiteral("文件解压失败").toUtf8().data()));
            qDebug() << "unZlibFile failed!";
        }

        QString setupFile = TNPathUtil::getInstallPackageFile() + "setup.exe";
        time.restart();
        bool setupOk = QProcess::startDetached(setupFile, QStringList());
        qDebug()<<"==========================upgradeStart-setup-time="<<time.elapsed();
        if (setupOk)
        {
            QDialog::accept();
            qDebug() << "setup ok! ";
        }
        else
        {
            ui->confirmTitleLabel->setText(tr(QStringLiteral("安装文件启动失败").toUtf8().data()));
            qDebug() << "setup error!";
        }
        qDebug()<<"Upgrade Success!";
    }
    else
    {
        qDebug() << "Download Failed!";
    }
}

void TNDownloadProgressDialog::slotHandleError(QNetworkReply::NetworkError code)
{
    qDebug()<<"TNDownloadProgressDialog::slotHandleError-error="<<code;

    ui->confirmTitleLabel->setText(tr(QStringLiteral("安装文件下载失败").toUtf8().data()));
    ui->reDownLoadButton->show();
    ui->fromBrownserButton->show();
    this->setFixedSize(350, 194);
}
