#ifndef CTNUSERVERSIONINFO_H
#define CTNUSERVERSIONINFO_H
#include "qmap.h"
#include "imcore_global.h"
#include "common_global.h"

class QJsonObject;
enum UPDATE_TYPE
{
	UPDATE_TYPE_MYCARD = 0,			//我的名片
	UPDATE_TYPE_MYFRIEND,			//我的好友
	UPDATE_TYPE_GROUP,			   //我创建的群组
	UPDATE_TYPE_Colleague,			//我的同事
	UPDATE_TYPE_ColleagueRelation,	//我的同事组织关系组下面有哪些同事
	UPDATE_TYPE_OrgGroup,			//组织分组
	UPDATE_TYPE_GroupChat,			//我的群聊信息
	//UPDATE_TYPE_GroupMember,		//群聊成员信息
	UPDATE_TYPE_OrgCard,			//我的组织名片
	UPDATE_TYPE_StaffCard,          //我的员工名片
	UPDAET_TYPE_DisturbList,		//免打扰列表        
	UPDAET_TYPE_NEWFRIEND		    //新学员   
};
static QString s_types[11] = { "card", "friend", "group","colleague", "collRelation", "orgGroup", "groupChat", "orgCard", "staffCard", "disturbList","newFriend"};
class IMCORE_EXPORT TNUserVersionInfo
{
private:
	TNUserVersionInfo();
	~TNUserVersionInfo();
public:
	static TNUserVersionInfo* GetInstance();
	QString GetUpdateVersion(UPDATE_TYPE type);
	QString GetUpdateVersion(QString& groupId);
	void SetUpdateVersion(UPDATE_TYPE type, QJsonObject& object);
	void ResetUpdateVersion(UPDATE_TYPE type);
	void ResetUpdateVersion(QString& groupId);
	void SetUpdateVersion(QString& groupId, QJsonObject& object);
	void SetUpdateVersion(QMap<QString, QJsonObject> updateVersionMap);
public:
	void InitVesionMap();
	void ResetVersion();
private:
	void SetUpdateVersion(QString& typeName, QString& strVersion);
private:
	QMap<QString, QString>  _mapVersion;
};
#endif

