#include "TNPathUtil.h"
#include "TNUserPath.h"
#include <QCoreApplication>
#include <qdir.h>
#include <QStandardPaths>
#include <QDebug>

#define LOG							"log/"
#define INSTALL						"install/"
#define COMMON_DB_FILE				"common.db"
#define CONFIG_FILE					"toon.ini"
#define GLOBAL_CONFIG_FILE			"global.ini"
#define VERSION_CONFIG_FILE			"version.ini"
TNUserPath TNPathUtil::s_userPath;
QString TNPathUtil::s_toonFile = TOON_FILE_ONLINE;
TNPathUtil::TNPathUtil()
{
}


TNPathUtil::~TNPathUtil()
{ }


void TNPathUtil::SetCurrentUser(const QString& user)
{
	s_userPath.SetCurrentUser(user);
}

bool TNPathUtil::isDownloadedAvatarPhoto(const QString &feedID, QString &filePath)
{
	if (feedID.isEmpty())
	{
		return false;
	}

    QString avatarFileName = TNPathUtil::getFeedAvatarPath(feedID);
    if(feedID.startsWith("gc_")){//群聊头像为原图
        avatarFileName += "_org";
    }
	filePath = avatarFileName;
	if (QFile::exists(avatarFileName))
	{
		return true;
	}

	return false;
}
bool TNPathUtil::isDownloadedOriginalAvatarPhoto(const QString &feedID, QString &filePath)
{
	if (feedID.isEmpty())
	{
		return false;
	}
	QString sFeedId = feedID;
	QString avatarFileName = TNPathUtil::getFeedAvatarPath(sFeedId)+"_org";
	filePath = avatarFileName;
	if (QFile::exists(avatarFileName))
	{
		return true;
	}
	return false;
}
QString TNPathUtil::getFeedAvatarPath()
{
	return s_userPath.GetCurrentAvatar();
}

QString TNPathUtil::getFeedAvatarPath(const QString& feedId)
{
    return s_userPath.GetCurrentAvatar() + feedId;
}
void TNPathUtil::removeAvatarFile(const QString& feedId)
{
	qInfo() << "[COMMON][TNPathUtil]removeAvatarFile start,feed:" << feedId;
	bool ret = false;
	QString avatar = TNPathUtil::getFeedAvatarPath(feedId);
	QString avatarOrg = TNPathUtil::getFeedAvatarPath(feedId) + "_org";
	if (QFile::exists(avatar))	{
		ret = QFile::remove(avatar);
		qInfo() << "[COMMON][TNPathUtil]remove a avatar, feed:" << feedId << " result:" << ret;
	}
	if (QFile::exists(avatarOrg)){
		ret = QFile::remove(avatarOrg);
		qInfo() << "[COMMON][TNPathUtil]remove a org avatar, feed:" << feedId << " result:" << ret;
	}
}
bool TNPathUtil::CreateFilePath(QString& path)
{
	QDir dir(path);
	if (!dir.exists())
		return dir.mkpath(path);
	return true;
}

QString TNPathUtil::getDbPath()
{
	return s_userPath.GetCurrentDbPath();
}

QString  TNPathUtil::getDbMsgPath()
{
	return s_userPath.GetCurrentDbMsgPath();
}

QString TNPathUtil::getCommonDbPath()
{
	return s_userPath.GetDocumentPath() + COMMON_DB_FILE;
}

QString TNPathUtil::getUserRecFile()
{
	return s_userPath.GetCurrentRecvFilePath();
}

QString TNPathUtil::getScanCodePath()
{
	return s_userPath.GetScanCodePath();
}
QString TNPathUtil::getUserConfigFile()
{
	return s_userPath.GetCurrentConfigPath();
}

QString TNPathUtil::getUserPath()
{
	return s_userPath.GetUserPath();
}

QString TNPathUtil::getLogPath()
{
	QString logPath = s_userPath.GetDocumentPath() + LOG;
	CreateFilePath(logPath);
	return logPath;
}

QString TNPathUtil::getGlocalConfigFile()
{
    QString globaConfig = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/" + GLOBAL_CONFIG_FILE;
	return globaConfig;
}

QString TNPathUtil::getConfigFile()
{
	QString configPath = s_userPath.GetDocumentPath() + CONFIG_FILE;
	return configPath;
}

QString TNPathUtil::getInstallPackageFile()
{
	QString installPath = s_userPath.GetDocumentPath() + INSTALL;
	CreateFilePath(installPath);
	return installPath;
}

void TNPathUtil::SetUserRecFile(const QString& user)
{
	s_userPath.SetCurrentRecvFilePath(user);
}

void TNPathUtil::SetToonFile(const QString& toonFile)
{
	s_toonFile = toonFile;
}

QString TNPathUtil::GetToonFile()
{
	return s_toonFile;
}

QString TNPathUtil::getFileIcon(const QString &fileSuffix)
{
    enum FileTpye
    {
        ftPdf = 0,
        ftDoc,
        ftXls,
        ftTxt,
        ftPPT,
        ftAndroid,
        ftZip,
        ftVideo
    };
    static QHash<QString, FileTpye> s_FileIconHash;
    if (s_FileIconHash.isEmpty())
    {
        s_FileIconHash["pdf"] = ftPdf;
        s_FileIconHash["doc"] = ftDoc;
        s_FileIconHash["docx"] = ftDoc;
        s_FileIconHash["xlsx"] = ftXls;
        s_FileIconHash["xls"] = ftXls;
        s_FileIconHash["txt"] = ftTxt;
        s_FileIconHash["ppt"] = ftPPT;
        s_FileIconHash["pptx"] = ftPPT;
        s_FileIconHash["apk"] = ftAndroid;

        s_FileIconHash["zip"] = ftZip;
        s_FileIconHash["rar"] = ftZip;
        s_FileIconHash["tar.gz"] = ftZip;
        s_FileIconHash["tar"] = ftZip;
        s_FileIconHash["gzip"] = ftZip;
        s_FileIconHash["7-zip"] = ftZip;
        s_FileIconHash["bz2"] = ftZip;
        s_FileIconHash["iso"] = ftZip;
        s_FileIconHash["z"] = ftZip;
        s_FileIconHash["lzh"] = ftZip;
        s_FileIconHash["ace"] = ftZip;
        s_FileIconHash["uue"] = ftZip;
        s_FileIconHash["cab"] = ftZip;
        s_FileIconHash["arj"] = ftZip;

        s_FileIconHash["avi"] = ftVideo;
        s_FileIconHash["wmv"] = ftVideo;
        s_FileIconHash["mpeg"] = ftVideo;
        s_FileIconHash["mp4"] = ftVideo;
        s_FileIconHash["mov"] = ftVideo;
        s_FileIconHash["mkv"] = ftVideo;
        s_FileIconHash["flv"] = ftVideo;
        s_FileIconHash["f4v"] = ftVideo;
        s_FileIconHash["m4v"] = ftVideo;
        s_FileIconHash["rmvb"] = ftVideo;
        s_FileIconHash["rm"] = ftVideo;
        s_FileIconHash["3gp"] = ftVideo;
        s_FileIconHash["ts"] = ftVideo;
        s_FileIconHash["mts"] = ftVideo;
        s_FileIconHash["vob"] = ftVideo;
    }
    QHash<QString, FileTpye>::Iterator iter = s_FileIconHash.find(fileSuffix.toLower());
    if (iter == s_FileIconHash.end())
    {
        return ":/Resources/default.png";
    }
    switch (iter.value())
    {
    case ftPdf:
        return ":/Resources/PDF.png";
    case ftDoc:
        return ":/Resources/docx.png";
    case ftXls:
        return ":/Resources/xls.png";
    case ftTxt:
        return ":/Resources/text.png";
        break;
    case ftPPT:
        return ":/Resources/PDF.png";
        break;
    case ftAndroid:
        return ":/Resources/android.png";
    case ftZip:
        return ":/Resources/zip.png";
    case ftVideo:
        return ":/Resources/video.png";
    default:
        return ":/Resources/default.png";
    }
}

QString TNPathUtil::getFaceModelPath()
{
    return  s_userPath.GetCurrentFaceModelPath();
}

QString TNPathUtil::getVersionPath()
{
	QString versionConfig = QCoreApplication::applicationDirPath() + "/" + VERSION_CONFIG_FILE;
	return versionConfig;
}
