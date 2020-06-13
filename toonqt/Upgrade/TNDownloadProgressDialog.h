#ifndef TNDOWNLOADPROGRESSDIALOG_H
#define TNDOWNLOADPROGRESSDIALOG_H

#include "DropShadowWidget.h"
#include "downloadmanager.h"

#include <QDialog>
#include <QNetworkReply>

namespace Ui {
class TNDownloadProgressDialog;
}

class TNDownloadProgressDialog: public /*QDialog*/DropShadowWidget
{
    Q_OBJECT

public:
    explicit  TNDownloadProgressDialog(QWidget *parent = 0);
    ~TNDownloadProgressDialog();
    
    void startDownLoad(const QString &url);

private slots:
    void slotDownLoaAgain();
    void slotFromDesktopBrownser();
    void onDownloadProcess(qint64 bytesReceived, qint64 bytesTotal);
    void onReplyFinished(int statusCode, const QString &zipFileName);
    void slotHandleError(QNetworkReply::NetworkError code);

private:
    Ui::TNDownloadProgressDialog *ui;

    DownLoadManager* m_downloadManager;
    QString m_url;
    QTime m_timeRecord;
    int m_lastTime;
    qint64 m_currentDownload;
    qint64 m_intervalDownload;
};

#endif // TNDOWNLOADPROGRESSDIALOG_H
