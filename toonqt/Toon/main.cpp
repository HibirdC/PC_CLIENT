#include "login.h"
#include "Toon.h"
#include <QObject>
#include <QTextCodec>
#include <QProcess>
#include <QUrl>
#include "TNHttpBasicRouterApi.h"
#include "TNHttpBaseApi.h"
#include "StateMachine.h"
#include "TNDebugLog.h"
#include "TNZoomFactor.h"
#include "TNSettingData.h"
#include "TNConfig.h"
#include "TNVersionInfo.h"
#include "TNPathUtil.h"
#include <QMessageBox>
#ifdef WIN32
#include <Windows.h>
//#include <vld.h>
#include "DbgHelp.h"
#pragma comment(lib, "Dbghelp.lib")
#endif
#ifdef Q_OS_MAC
#include "macqapplication.h"
#else
#include "toonapplication.h"
#endif
#if !defined(_DEBUG ) && !defined(QT_DEBUG)
#define TOON_SIGNAL
#endif


#ifdef WIN32
static LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException)
{
	//And output crash information
	EXCEPTION_RECORD *record = pException->ExceptionRecord;
	QString errCode(QString::number(record->ExceptionCode, 16));
	QString errAddr(QString::number((uint)record->ExceptionAddress, 16));
	QString errFlag(QString::number(record->ExceptionFlags, 16));
	QString errPara(QString::number(record->NumberParameters, 16));
	qInfo() << "[Toon][ToonApplication]ApplicationCrashHandler errCode: " << errCode;
	qInfo() << "[Toon][ToonApplication]ApplicationCrashHandler errAddr: " << errAddr;
	qInfo() << "[Toon][ToonApplication]ApplicationCrashHandler errFlag: " << errFlag;
	qInfo() << "[Toon][ToonApplication]ApplicationCrashHandler errPara: " << errPara;
	//Create the dump file，fail try three times
	QString crashPath = CRASH_FILE;
	for (int times = 0; times < 3; times++)
	{
		HANDLE hDumpFile = CreateFile((LPCWSTR)crashPath.utf16(),
			GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hDumpFile != INVALID_HANDLE_VALUE) {
			MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
			dumpInfo.ExceptionPointers = pException;
			dumpInfo.ThreadId = GetCurrentThreadId();
			dumpInfo.ClientPointers = TRUE;
			MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);
			CloseHandle(hDumpFile);
			break;
		}
		else
		{
			qInfo() << "[Toon][ToonApplication]CrashHandler: file handle invalid";
			DeleteFile((LPCWSTR)QString("crash.dmp").utf16());
			crashPath = TNPathUtil::getUserPath() + CRASH_FILE;
		}
	}
    qApp->quit();
#ifdef DAOTOON
	return EXCEPTION_EXECUTE_HANDLER;
#endif
#ifndef QT_DEBUG
    QProcess::startDetached(qApp->applicationFilePath(), QStringList());
#endif
	return EXCEPTION_EXECUTE_HANDLER;
}
#endif


int main(int argc, char *argv[])
{
#ifdef WIN32
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);
#endif
	QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
	QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#ifndef QT_DEBUG
    TNDebugLog::setDebugOutput();
#endif

#ifndef Q_OS_MAC
    ToonApplication app(argc, argv);
#else 
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    macQApplication app(argc, argv);
#endif

#ifdef TOON_SIGNAL
    if(app.isRunning()){
        qInfo() << "toon has an instance running";
        return 0;
    }
#endif
#ifdef DAOTOON
	QString appPath = QCoreApplication::applicationDirPath();
	SetCurrentDirectory(appPath.toStdWString().c_str());
	bool bIsWebStartup = false;
	if (argc == 2)
	{
		QString urlProtocal = argv[1];
		if (urlProtocal.startsWith("toonpc") )
			bIsWebStartup = true;
	}
	if (!bIsWebStartup)
	{
		qDebug() << "[login]:非网页登录";
		QMessageBox::information(NULL, "toon", ("请在oa系统登录！"));
		return 0;
	}
#endif // DAOTOON
	TNConfig::instance()->ApplyCurrentLangueSet();
    QList<QString> listStyle;
	listStyle.append(":/qss/Resources/toon.qss");
	listStyle.append(":/qss/Resources/systool.qss");
	listStyle.append(":/qss/Resources/emoji.qss");
    listStyle.append(TNVersionInfo::GetDefaultQss());
    TNSettingData::SetToonStyle(listStyle);
	//初始化环境
	NetWorkAPI::InitNetEnv();

    //此处必须加上，否则消息循环可能受到closeevent，而退出应用程序，即使重写closeevent事件。
    app.setQuitOnLastWindowClosed(false);
    StateMachine stateMachine(&app);
    stateMachine.Init(true);
    app.exec();
#ifndef QT_DEBUG
	TNDebugLog::clearDebugOutput();
#endif
	return 0;
}
