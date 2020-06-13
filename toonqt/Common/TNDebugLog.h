#ifndef TNDEBUGLOG_H
#define TNDEBUGLOG_H
#include <QObject>
#include <QString>
#include "common_global.h"
#include <QMutex>
#include <qfile.h>
#include <qtextstream.h>
#include "spdlog/spdlog.h"
class COMMON_EXPORT TNDebugLog : public QObject
{
	Q_OBJECT

public:
	TNDebugLog();
	~TNDebugLog();
	void CreateLogFile(const QString& filePath);
    std::shared_ptr<spdlog::logger> CreateLogFile(const QString& dirName,
                                                  const QString& fileName,
                                                  const QString& logger_name);
	void AppendLogInfo(QString logInfo);
	void AppendLogThread(QString logInfo);
	static void clearDebugOutput();
	static void setDebugOutput();
    static void PrintCurrentMSTime(QString loginfo);
private:
    void clearLastWeekLog();
private:
	QFile*			_logFile;
	QTextStream*	_textStream;
	QMutex          _textStreamMutex;
	std::shared_ptr<spdlog::logger>  _logger;
};
#endif

