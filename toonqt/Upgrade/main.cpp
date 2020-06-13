#include <QtWidgets/QApplication>
#include <QSharedMemory>

#ifdef  Q_OS_WIN32
#include <Windows.h>
#endif

#include "TNDownloadProgressDialog.h"
#include "gmblogger.h"
#include "TNConfig.h"

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    switch (type) {
    case QtDebugMsg:
        //fprintf(stderr, "Debug: %s\n", msg);
        GmbLogger::getInstance().printLog(msg);
        break;
    case QtInfoMsg:
        //fprintf(stderr, "Debug: %s\n", msg);
        GmbLogger::getInstance().printLog(msg);
        break;
    case QtWarningMsg:
        //fprintf(stderr, "Warning: %s\n", msg);
        GmbLogger::getInstance().printLog(msg);
        break;
    case QtCriticalMsg:
        //fprintf(stderr, "Critical: %s\n", msg);
        GmbLogger::getInstance().printLog(msg);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s\n", msg);
        abort();
    }
}

void SetToonStyle(QList<QString>& styleList)
{
    QString strQss;
    for (int index = 0; index < styleList.size(); index++)
    {
        QString moduleStyle = styleList[index];
        QFile qss(moduleStyle);
        if (qss.open(QFile::ReadOnly))
        {
            strQss += QString::fromUtf8(qss.readAll());
            qss.close();
        }
    }
    qApp->setStyleSheet(strQss);
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication a(argc, argv);

    QSharedMemory shared_memory;
    shared_memory.setKey(QString("toonUpgrade"));

    qInstallMessageHandler(myMessageOutput);

    qDebug()<<"==========================upgradeStart==========================";
    if (shared_memory.attach())
    {
        return 0;
    }
    if (shared_memory.create(1))
    {
        LANGUE_TYPE langType = TNConfig::instance()->GetCurrentLangueSet();
        qDebug()<<"==========================GetCurrentLangueSet="<<langType;
        TNConfig::instance()->ApplyCurrentLangueSet();
        QList<QString> listStyle;
        listStyle.append(":/Upgrade/Resources/upgrade.qss");
        SetToonStyle(listStyle);

        QString downLoadURL = QString(argv[2]);
        qDebug()<<"==========================upgradeStart-downLoadURL="<<downLoadURL;
        TNDownloadProgressDialog progressDialog;
        progressDialog.startDownLoad(downLoadURL);

#ifdef Q_OS_WIN32
        ::SetWindowPos(HWND(progressDialog.winId()), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
        ::SetWindowPos(HWND(progressDialog.winId()), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
#endif

        progressDialog.exec();
    }
    return 0;
}
