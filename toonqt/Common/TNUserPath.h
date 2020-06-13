#ifndef TNUSERPATH_H
#define TNUSERPATH_H
#include <QString>
class TNUserPath
{
public:
	TNUserPath();
	~TNUserPath();
	void SetCurrentUser(const QString& user);
	const QString& GetCurrentDbPath();
	const QString& GetCurrentRecvFilePath();
	void SetCurrentRecvFilePath(const QString& path) { _userRecFile = path; }
	const QString& GetCurrentAvatar();
	const QString& GetScanCodePath();
	const QString& GetDocumentPath();
	const QString& GetCurrentDbMsgPath();
	const QString& GetCurrentConfigPath();
	QString GetUserPath();
    QString GetCurrentFaceModelPath();
private:
	QString _scanPath;
	QString _user;
	QString _userPath;
	QString _userDb;
	QString _msgDb;
	QString _userRecFile;
	QString _userAvatar;
	QString _documentPath;
	QString _userConfig;
    QString _userFaceModelPath;
};
#endif
