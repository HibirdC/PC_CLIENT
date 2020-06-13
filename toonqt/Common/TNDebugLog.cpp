#include "TNDebugLog.h"
#include <qdatetime.h>
#include <qfileinfo.h>
#include <qdir.h>
#include <qdebug.h>
#include <iostream>
#include <string>
#include <climits>
#include "TNPathUtil.h"
#include "QtConcurrent/QtConcurrent"
#include "tnwinconvert.h"

#define MAX_LOGFILE_SIZE 10
#define MAX_LOGFILES 100
#define MAX_LOG_EX_DAYS 7

TNDebugLog::TNDebugLog(): _logFile(NULL)
  ,_textStream(NULL)
{
    clearLastWeekLog();
}


TNDebugLog::~TNDebugLog()
{
	if (_textStream)
	{
		delete _textStream;
		_textStream = NULL;
	}
	if (_logFile)
	{
		_logFile->close();
		delete _logFile;
	}
}

void TNDebugLog::clearDebugOutput()
{
	qInstallMessageHandler(0);
}

void TNDebugLog::setDebugOutput()
{
	static TNDebugLog debugLog;
	debugLog.CreateLogFile(TNPathUtil::getLogPath());
	class HelperClass
	{
	public:
		static void messageHandler(QtMsgType type, const QMessageLogContext &, const QString &message_)
		{
			QString message;
#ifdef WIN32
			DWORD threadId = GetCurrentThreadId();
			message = QString("[%1]:  ").arg(threadId);
#endif 
			switch (type)
			{
			case QtDebugMsg:
			{
				message.append(message_);
				return;
			}
			case QtWarningMsg:
			{
				//painter warning ignore
				if (message_.indexOf("QPainter") >= 0 || message_.indexOf("QWidget") >= 0)
				{
					return;
				}
				message.append("[Warning:] ");
				message.append(message_);
				break;
			}
			case QtCriticalMsg:
			{
				message.append("[Critical:] ");
				message.append(message_);
				break;
			}
			case QtFatalMsg:
			{
				message.append("[Fatal:] ");
				message.append(message_);
				break;
			}
			case QtInfoMsg:
			{
				message.append(message_);
			}
			default: { break; }
			}
			debugLog.AppendLogThread(message.toStdString().c_str());
		}
	};
	qInstallMessageHandler(HelperClass::messageHandler);
}

void TNDebugLog::PrintCurrentMSTime(QString loginfo)
{
	QDateTime time = QDateTime::currentDateTime();
	qlonglong nowTime = time.toMSecsSinceEpoch();
	QString strTime = QString::number(nowTime);
	qInfo() << loginfo << strTime;
}

void TNDebugLog::CreateLogFile(const QString& filePath)
{
	//使用loger库
	QString logPath = filePath;
	if (!QFileInfo::exists(logPath))
	{
		QDir().mkpath(QFileInfo(logPath).path());
	}
	QString fileName = QString("%1_toon.log").arg(QDateTime::currentDateTime().toString("yyyy_MM_dd"));
	logPath.append(fileName);
	try
	{
		std::string log_path;
#ifdef Q_OS_WIN
		log_path = tnwinconvert::UnicodeToAscii(tnwinconvert::Utf8ToUnicode(logPath.toStdString()));
#endif
        _logger = spdlog::rotating_logger_mt("toon_daily_log", log_path.c_str(), 1048576 * MAX_LOGFILE_SIZE, MAX_LOGFILES);
		_logger->set_level(spdlog::level::info);
		_logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] %v");
		_logger->flush_on(spdlog::level::info);
	}
	catch (...)
	{
		_logFile = new QFile(logPath);
		if (_logFile)
			_logFile->open(QIODevice::WriteOnly | QIODevice::Append);
	}
	
}
void TNDebugLog::AppendLogInfo(QString logInfo)
{
	if (_logFile)
	{
		_textStreamMutex.lock();
		if (_textStream == NULL)
			_textStream = new QTextStream(_logFile);
		*_textStream << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz") << ": " << logInfo << "\r\n" << endl;
		_textStreamMutex.unlock();
	}
	else
	{
		try
		{
			_logger->info(logInfo.toStdString().c_str());
		}
		catch (...)
		{
			
		}
	}
}

void TNDebugLog::AppendLogThread(QString logInfo)
{
	QtConcurrent::run(this, &TNDebugLog::AppendLogInfo, logInfo);
}


std::shared_ptr<spdlog::logger> TNDebugLog::CreateLogFile(const QString &dirName,
                                                          const QString &fileName,
                                                          const QString &logger_name)
{
    QDir dir(dirName);
    if(!dir.exists()){
        dir.mkdir(dirName);
    }
    QString log_fileName = QString("%1_%2.log").
                    arg(QDateTime::currentDateTime().toString("yyyy_MM_dd"),
                        fileName);
    QString log_path = dirName + "/" + log_fileName;
    std::string s_log_path;
#ifdef Q_OS_WIN
    s_log_path = tnwinconvert::UnicodeToAscii(tnwinconvert::Utf8ToUnicode(log_path.toStdString()));
#else
    s_log_path = log_path.toStdString();
#endif
    std::shared_ptr<spdlog::logger> daily_logger;
    try
    {
        daily_logger = spdlog::rotating_logger_mt(logger_name.toStdString().c_str(),
            s_log_path.c_str(),1048576 * MAX_LOGFILE_SIZE, MAX_LOGFILES);
        daily_logger->set_pattern("[%H:%M:%S.%e %z] [thread %t]: %v");
        daily_logger->flush_on(spdlog::level::info);
    }catch(const spdlog::spdlog_ex& ex){
        std::cout << "Log init failed: " << ex.what() << std::endl;
        daily_logger.reset();
    }
    return daily_logger;
}

void TNDebugLog::clearLastWeekLog()
{
    QDateTime curDateTime = QDateTime::currentDateTime();
    QDate curDate = curDateTime.date();
    QDir directory(TNPathUtil::getLogPath());
    QStringList logs = directory.entryList(QStringList() << "*.txt" << "*.log*",QDir::Files);
    foreach (QString log, logs) {
        QString log_path = TNPathUtil::getLogPath() + log;
        if(log.contains("toon.log")){
            int index = log.indexOf("toon.log");
            if(index == -1) continue;
            QString tmp = log.mid(0,index - 1);
            QDate logDate = QDate::fromString(tmp,"yyyy_MM_dd");
            if(!logDate.isValid()) continue;
            int days = qAbs(curDate.daysTo(logDate));
            if(days > MAX_LOG_EX_DAYS){
                directory.remove(log_path);
            }
        }else if(log.contains("notice.log")){
            int index = log.indexOf("notice.log");
            if(index == -1) continue;
            QString tmp = log.mid(0,index - 1);
            QDate logDate = QDate::fromString(tmp,"yyyy_MM_dd");
            if(!logDate.isValid()) continue;
            int days = qAbs(curDate.daysTo(logDate));
            if(days > MAX_LOG_EX_DAYS){
                directory.remove(log_path);
            }
        }else if(log.endsWith(".txt")){
            int index = log.indexOf("imlog");
            int endIndex = log.indexOf(".txt");
            if(index == -1 || endIndex == -1) continue;
            int start = index + sizeof("imlog") - 1;
            QString tmp = log.mid(start, endIndex - start);
            QDate logDate = QDate::fromString(tmp,"yyyy-MM-dd");
            if(!logDate.isValid()) continue;
            int days = qAbs(curDate.daysTo(logDate));
            if(days > MAX_LOG_EX_DAYS){
                directory.remove(log_path);
            }
        }
    }
}
