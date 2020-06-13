#include "TNUserVersionInfo.h"
#include "TNDataControlServer.h"
#include "qjsonobject.h"

#include <QDebug>

TNUserVersionInfo::TNUserVersionInfo()
{
	
}


TNUserVersionInfo::~TNUserVersionInfo()
{
}

QString TNUserVersionInfo::GetUpdateVersion(UPDATE_TYPE type)
{
	QString typeName = s_types[type];
	if (_mapVersion.find(typeName) != _mapVersion.end())
		return _mapVersion[typeName];
	return "0";
}

QString TNUserVersionInfo::GetUpdateVersion(QString& groupId)
{
	QString typeName = groupId;
	if (_mapVersion.find(typeName) != _mapVersion.end())
		return _mapVersion[typeName];
	return "0";
}

void TNUserVersionInfo::SetUpdateVersion(UPDATE_TYPE type, QJsonObject& object)
{
	QString typeName = s_types[type];
	SetUpdateVersion(typeName, object);
}

void TNUserVersionInfo::ResetUpdateVersion(UPDATE_TYPE type)
{
    qDebug()<<"TNUserVersionInfo::ResetUpdateVersion-enum begin...";
	QString typeName = s_types[type];
	QString version = "0";
	SetUpdateVersion(typeName, version);
    qDebug()<<"TNUserVersionInfo::ResetUpdateVersion-enum end.";
}

void TNUserVersionInfo::ResetUpdateVersion(QString& groupId)
{
    qDebug()<<"TNUserVersionInfo::ResetUpdateVersion-groupId begin...";
	QString version = "0";
	SetUpdateVersion(groupId, version);
    qDebug()<<"TNUserVersionInfo::ResetUpdateVersion-groupId end.";
}

void TNUserVersionInfo::SetUpdateVersion(QString& typeName, QString& strVersion)
{
	if (_mapVersion.find(typeName) != _mapVersion.end())
	{
		//update
		TNDataControlServer::GetInstance()->UpdateSetValueByField("Version", "version", strVersion, "name", typeName, DBTYPE_USER);
	}
	else
	{
		st_VersionPtr versionItem = std::make_shared<st_Version>();
		versionItem->SetName(typeName);
		versionItem->SetVersion(strVersion);
		TNDataControlServer::GetInstance()->InsertDatas(versionItem, DBTYPE_USER);
	}
	_mapVersion[typeName] = strVersion;
}

void TNUserVersionInfo::SetUpdateVersion(QString& groupId, QJsonObject& object)
{
	qlonglong version = object.value("data").toObject().value("version").toDouble();
	if (version == 0)
		return;
	QString strVersion = QString::number(version);
	QString typeName = groupId;
	SetUpdateVersion(typeName, strVersion);
}
void TNUserVersionInfo::SetUpdateVersion(QMap<QString, QJsonObject> updateVersionMap)
{
	foreach(const QString &groupId, updateVersionMap.keys())
	{
		QJsonObject object = updateVersionMap.value(groupId);
		qlonglong version = object.value("data").toObject().value("version").toDouble();
		if (version == 0)
			continue;
		QString strVersion = QString::number(version);
		QString typeName = groupId;
		SetUpdateVersion(typeName, strVersion);
	}
}
void TNUserVersionInfo::InitVesionMap()
{
	ResetVersion();
	TableBaseVec versionTable;
	TNDataControlServer::GetInstance()->GetAllFieldsByTableName("Version", versionTable, DBTYPE_USER);
	TableBaseVec::iterator iter = versionTable.begin();
	while (iter != versionTable.end())
	{
		st_VersionPtr version = std::dynamic_pointer_cast<st_Version>(*iter);
		_mapVersion.insert(version->GetName(), version->GetVersion());
		iter++;
	}
}

TNUserVersionInfo* TNUserVersionInfo::GetInstance()
{
	static TNUserVersionInfo* userVerson = NULL;
	if (userVerson == NULL)
		userVerson = new TNUserVersionInfo;
	return userVerson;
}
void TNUserVersionInfo::ResetVersion()
{
	_mapVersion.clear();
}
