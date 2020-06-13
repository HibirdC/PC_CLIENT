#include "gmblogger.h"

#include <QDir>
#include <QDebug>
#include <QFileInfo>
#include <QDateTime>

#include "TNPathUtil.h"

GmbLogger::GmbLogger()
{
    QString logPath = TNPathUtil::getLogPath();
    if (!QFileInfo::exists(logPath))
    {
        QDir().mkpath(QFileInfo(logPath).path());
    }
    QString fileName = QString("%1_upgrade.log").arg(QDateTime::currentDateTime().toString("yyyy_MM_dd"));
    logPath.append(fileName);
    m_logFile = new QFile(logPath);
    bool ok = m_logFile->open(QIODevice::WriteOnly | QIODevice::Append);
    if (ok)
        m_textStream.setDevice(m_logFile);
}

GmbLogger::~GmbLogger()
{
    if (m_logFile)
    {
        m_logFile->close();
        delete m_logFile;
    }
}

GmbLogger &GmbLogger::getInstance()
{
    static GmbLogger loggerObj;

    return loggerObj;
}

void GmbLogger::printLog(const QString &msg)
{
    m_textStream << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz") << ": " << msg << "\r\n" << endl;
}
