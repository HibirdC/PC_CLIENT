#include "TNHttpDownFile.h"

#include "TNPathUtil.h"

TNHttpDownFile::TNHttpDownFile() :m_reply(NULL)
{
}

TNHttpDownFile::~TNHttpDownFile()
{
}

void TNHttpDownFile::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
{
    if (statusCode == 200)
    {
        QString installPath = getFileName();
        m_output.close();
        this->downLoadCallBack(true, installPath);
    }
    else
    {
        this->downLoadCallBack(false, "");
    }
}

void TNHttpDownFile::DownLoadNewVersion(std::function<void(bool, QString)> callback, const QString& url, QObject *receiver)
{
    QString installPath = getFileName();
    m_output.setFileName(installPath);
    if (!m_output.open(QIODevice::WriteOnly))
    {
        qDebug()<<"error! open file failed. FileName="<<installPath;
        return;
    }

    this->downLoadCallBack = callback;

    QNetworkRequest _httpRequest;
    m_reply = get(_httpRequest, url);
    connect(m_reply, SIGNAL(readyRead()), this, SLOT(downloadReadyRead()));
    connect(m_reply, SIGNAL(downloadProgress(qint64, qint64)), receiver, SLOT(On_DownLoadProgress(qint64, qint64)));
    connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), receiver, SLOT(slotHandleError(QNetworkReply::NetworkError)));
}

void TNHttpDownFile::downloadReadyRead()
{
    m_output.write(m_reply->readAll());
}

QString TNHttpDownFile::getFileName()
{
    QString installPath = TNPathUtil::getInstallPackageFile() + "toon.zip";
    return installPath;
}
