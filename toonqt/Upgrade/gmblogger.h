#ifndef GMBLOGGER_H
#define GMBLOGGER_H

#include <QFile>
#include <QTextStream>

// 日志类
class GmbLogger
{
public:
    GmbLogger();
    ~GmbLogger();

    static GmbLogger &getInstance();

    void printLog(const QString &msg);

private:
    QFile*			m_logFile;
    QTextStream 	m_textStream;
};

#endif // GMBLOGGER_H
