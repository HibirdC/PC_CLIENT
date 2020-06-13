#ifndef TNHTTPDOMNFILE_H
#define TNHTTPDOMNFILE_H

#include <functional>
#include <QList>
#include <QPair>
#include <QFile>

#include "common_global.h"
#include "TNHttpBaseApi.h"


class NETWORKAPI_EXPORT TNHttpDownFile : public TNHttpBaseApi
{
    Q_OBJECT

public:
    TNHttpDownFile();
    ~TNHttpDownFile();

    //receiver 用于连接下载进度信号
    void DownLoadNewVersion(std::function<void(bool, QString)> callback, const QString& url, QObject *receiver);

protected:
    void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);

protected slots:
    void downloadReadyRead();

private:
    std::function<void(bool, QString)> downLoadCallBack;

    QFile m_output;
    QNetworkReply *m_reply;

    QString getFileName();
};

typedef std::shared_ptr<TNHttpDownFile>  TNHttpDownFilePtr;

#endif // TNHTTPDOMNFILE_H
