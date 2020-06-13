#include "TNUserPath.h"
#include "TNPathUtil.h"
#include <QStandardPaths>

#define AVATART		"/UserAvatar/"
#define RECV_FILE	"/FileRecv/"
#define SCAN_CODE	"/ScanCode/"
#define DB_FILE		"/toon.db"
#define DB_FILE_MSG "/message.db"
#define CONFIG_FILE "/config.ini"
#define FACE_MODEL_FILE "/faceid/"

TNUserPath::TNUserPath()
{
}


TNUserPath::~TNUserPath()
{
}

const QString& TNUserPath::GetCurrentDbPath()
{

	return _userDb;
}

const QString& TNUserPath::GetCurrentRecvFilePath()
{
    TNPathUtil::CreateFilePath(_userRecFile);
	return _userRecFile;
}

const QString& TNUserPath::GetCurrentAvatar()
{
	return _userAvatar;
}

const QString& TNUserPath::GetCurrentDbMsgPath()
{
	return _msgDb;
}
const QString& TNUserPath::GetCurrentConfigPath()
{
	return _userConfig;
}
void TNUserPath::SetCurrentUser(const QString& user)
{
	_user = user;
	QString documentPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
	documentPath += TOON_FILE;
	documentPath += "/" + _user + "/";
	TNPathUtil::CreateFilePath(documentPath);
	_userPath = documentPath;
	_userConfig = documentPath+CONFIG_FILE;
	_userConfig = _userConfig.replace("//", "/");

	_userDb = documentPath + DB_FILE;
	_userDb = _userDb.replace("//", "/");
	_msgDb = documentPath + DB_FILE_MSG;
	_msgDb = _msgDb.replace("//", "/");
	_userRecFile = documentPath + RECV_FILE;
	_userRecFile = _userRecFile.replace("//", "/");
	TNPathUtil::CreateFilePath(_userRecFile);

	_userAvatar = documentPath + AVATART;
	_userAvatar = _userAvatar.replace("//", "/");

	TNPathUtil::CreateFilePath(_userAvatar);

}

const QString& TNUserPath::GetScanCodePath()
{
	if (_scanPath.isEmpty())
	{
		QString documentPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
		documentPath += TOON_FILE;
		_documentPath = documentPath;
		_scanPath = documentPath + SCAN_CODE;
		TNPathUtil::CreateFilePath(_scanPath);
	}
	return _scanPath;
}

const QString& TNUserPath::GetDocumentPath()
{
	if (_documentPath.isEmpty())
	{
		QString documentPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
		documentPath += TOON_FILE;
		_documentPath = documentPath;
		TNPathUtil::CreateFilePath(_documentPath);
	}
	return _documentPath;
}

QString TNUserPath::GetUserPath()
{
	return _userPath;
}

QString TNUserPath::GetCurrentFaceModelPath()
{
    if(_userFaceModelPath.isEmpty()){
        QString documentPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
        documentPath += TOON_FILE;
        _userFaceModelPath = documentPath + FACE_MODEL_FILE;
        _userFaceModelPath = _userFaceModelPath.replace("//","/");
        TNPathUtil::CreateFilePath(_userFaceModelPath);
    }
    return _userFaceModelPath;
}
