#ifndef TNPATHUTIL_H
#define TNPATHUTIL_H
#include <QString>
#include "common_global.h"
class TNUserPath;
#define TOON_FILE_ONLINE	"/toon files/"
#define TOON_FILE_TEST		"/toon-test files/"
#define TOON_FILE_DEV		"/toon-dev files/"
#define TOON_FILE_UCLOUD		"/toon-ucloud files/"
#define CRASH_FILE			"crash.dmp"

class COMMON_EXPORT TNPathUtil
{
public:
	TNPathUtil();
	~TNPathUtil();
public:
	static void SetCurrentUser(const QString& user);
	static bool isDownloadedAvatarPhoto(const QString &feedID, QString &filePath);
	static bool isDownloadedOriginalAvatarPhoto(const QString &feedID, QString &originalFilePath);
	static QString getFeedAvatarPath(const QString& feedId);
	static QString getFeedAvatarPath();
	static void removeAvatarFile(const QString& feedId);
	static QString getDbPath();
	static QString getDbMsgPath();
	static QString getCommonDbPath();
	static QString getScanCodePath();
	static QString getLogPath();
	static QString getUserRecFile();
	static QString getGlocalConfigFile();
	static QString getConfigFile();
	static QString getUserConfigFile();
	static QString getUserPath();
	static void SetUserRecFile(const QString& user);
	static QString getInstallPackageFile();
	//创建文件目录，有则不创建，没有则创建
	static bool CreateFilePath(QString& path);
	static void SetToonFile(const QString& toonFile);
	static QString GetToonFile();
	static QString getFileIcon(const QString &fileSuffix);
    static QString getFaceModelPath();
	//定制版本配置路径
	static QString getVersionPath();
private:
	static TNUserPath s_userPath;
	static QString s_toonFile;
};
#define TOON_FILE TNPathUtil::GetToonFile()
#endif
