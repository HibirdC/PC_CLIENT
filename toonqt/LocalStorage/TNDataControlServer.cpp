#include <QDebug>
#include <memory>
#include <QCoreApplication>
#include <QDir>

#include "TNDataControlServer.h"
#include "LocalStorageCommon.h"
#include "TNPathUtil.h"
#include "ConnectionPool.h"
#include "TNConfig.h"
#include "TNUserDataUtil.h"
#include "TNVersionInfo.h"


/*
#if !defined(__linux__)
#define SQLITE_CIPHER
#endif
*/

TNDataControlServer* TNDataControlServer::_Instance = NULL;
TNDataControlServer::TNDataControlServer() :_bInit(false), _bInitCommon(false)
{

}


TNDataControlServer::~TNDataControlServer()
{
	CloseDb();
	if (_sqlCommonDb.isOpen())
	{
		_sqlCommonDb.close();
		_bInitCommon = false;
	}
	//ConnectionPool::release();
}

bool TNDataControlServer::Init(int dbType)
{
	bool res = false;
	switch (dbType)
	{
	case DBTYPE_USER:
		if (Connect(TNPathUtil::getDbPath(), dbType))
		{
			qInfo() << "[LocalStorage][TNDataControlServer] User Database Create Sucessfully!";
			InitTable(dbType);
			res = true;
		}
		break;
	case DBTYPE_COMMON:
		if (Connect(TNPathUtil::getCommonDbPath(), dbType))
		{
			qInfo() << "[LocalStorage][TNDataControlServer] Common Database Create Sucessfully!";
			InitTable(dbType);
			_bInitCommon = true;
			res = true;
		}
		break;
	case DBTYPE_MSG:
		if (Connect(TNPathUtil::getDbMsgPath(), dbType))
		{
			qInfo() << "[LocalStorage][TNDataControlServer] msg Database Create Sucessfully!";
			InitTable(dbType);
			res = true;
		}
		break;
	default:
		break;
	}
	return res;
}

void TNDataControlServer::InitTable(int dbType)
{
	QList<TNBaseTablePtr> listTable;
	switch (dbType)
	{
	case DBTYPE_USER:
		_feedTable = std::make_shared<TNFeed>();
		listTable.append(_feedTable);
		_versionTable = std::make_shared<TNVersion>();
		listTable.append(_versionTable);
		_myStuffTable = std::make_shared<TNMyStuff>();
		listTable.append(_myStuffTable);
		_joinStuffTable = std::make_shared<TNJoinStuff>();
		listTable.append(_joinStuffTable);
		_chatSettings = std::make_shared<TNChatSettings>();
		listTable.append(_chatSettings);
		_chatAppList = std::make_shared<TNChatAppList>();
		listTable.append(_chatAppList);
		_groupInfo = std::make_shared<TNGroupInfo>();
		listTable.append(_groupInfo);
		_groupMember = std::make_shared<TNGroupMember>();
		listTable.append(_groupMember);
		_colleagueGroup = std::make_shared<TNColleagueGroup>();
		listTable.append(_colleagueGroup);
		_colleagueRelation = std::make_shared<TNColleagueRelation>();
		listTable.append(_colleagueRelation);
		_setUp = std::make_shared<TNSetUp>();
		listTable.append(_setUp);
		_blackList = std::make_shared<TNBlackList>();
		listTable.append(_blackList);
		_company = std::make_shared<TNCompanyInfo>();
		listTable.append(_company);
        _newFriend = std::make_shared<TNNewFriend>();
        listTable.append(_newFriend);
		break;
	case DBTYPE_COMMON:
		_loginUser = std::make_shared<TNLoginUser>();
        _faceId = std::make_shared<TNFaceId>();
		listTable.append(_loginUser);
        listTable.append(_faceId);
		break;
	case DBTYPE_MSG:
		_bmessage0 = std::make_shared<TNBMessage0>();
		listTable.append(_bmessage0);
		_messageOperate = std::make_shared<TNMessageOperate>();
		listTable.append(_messageOperate);
		_messageFault = std::make_shared<TNMessageFault>();
		listTable.append(_messageFault);
		_messageAppInfo = std::make_shared<TNMessageAppInfo>();
		listTable.append(_messageAppInfo);
		_session = std::make_shared<TNSession>();
		listTable.append(_session);
		_sessionBackGround = std::make_shared<TNSessionBackground>();
		listTable.append(_sessionBackGround);
		_readSessionReq = std::make_shared<TNReadSessionReq>();
		listTable.append(_readSessionReq);
	default:
		break;
	} 
    QList<TNBaseTablePtr>::const_iterator itera = listTable.begin();
    for(;itera != listTable.end();++itera){
        (*itera)->SetDBConnect(GetConnectionDB(dbType));
        (*itera)->createTable();
    }
}

bool TNDataControlServer::Connect(const QString &dbName,int dbType)
{
	bool res = false;
	QSqlDatabase tempDb;
	if (dbName.isEmpty())
	{
		return res;
	}
	if (!initErrorFixed(dbType))
	{
		TNConfig::instance()->setFixedFailed(true);
		return res;
	}
	//加密库
#ifdef SQLITE_CIPHER
    QStringList driverList = QSqlDatabase::drivers();
    if (!driverList.contains("SQLITECIPHER"))
    {
        qInfo() << "[LocalStorage][TNDataControlServer]Connect the driver is not valid,please add sqlitecipher";
        return false;
    }
	//对于1.2.1之前版本做toon.db清库处理。
	if (dbType == DBTYPE_USER)
	{
		if(!QFile::exists(TNPathUtil::getUserConfigFile()))
			QFile::remove(dbName);
	}
	tempDb = QSqlDatabase::addDatabase("SQLITECIPHER", dbName);
#else
	tempDb = QSqlDatabase::addDatabase("QSQLITE", dbName);
#endif
	tempDb.setDatabaseName(dbName);
#ifdef SQLITE_CIPHER
	tempDb.setPassword("tN8fL3YuD9");
	bool isEncode = TNConfig::instance()->getEncodeDB(dbType);
	if (!isEncode)
	{
		tempDb.setConnectOptions("QSQLITE_CREATE_KEY");
	}
#endif
 	if (tempDb.open()) {
		/*
		关闭SQL同步写
		*/
		QSqlQuery query(tempDb);
		query.exec("PRAGMA synchronous = OFF; ");
		switch (dbType)
		{
		case DBTYPE_USER:
			//验证数据库合法性
			if (!getOwnerDataStatus(&tempDb, dbType))
			{
				tempDb.close();
				QSqlDatabase::removeDatabase(dbName);
				return res;
			}
			_sqlDb = tempDb;
			break;
		case DBTYPE_COMMON:
			_sqlCommonDb = tempDb;
			break;
		case DBTYPE_MSG:
			//验证数据库合法性
			if (!getOwnerDataStatus(&tempDb, dbType))
			{
				tempDb.close();
				QSqlDatabase::removeDatabase(dbName);
				return res;
			}
			_sqlMsgDb = tempDb;
			break;
		default:
			break;
		}
#ifdef	SQLITE_CIPHER
		if (!isEncode)
		{
			TNConfig::instance()->setEncodeDB(true, dbType);
		}
#endif
		res = true;
	}
	else
	{
		QSqlDatabase::removeDatabase(dbName);
		qDebug() << "Database Init Error!";
	}
	return res;
}

bool TNDataControlServer::ResetConnect()
{
	if (_bInit)
		return true;
	bool resUser = Init(DBTYPE_USER);
	if (!resUser)
	{
		emit dbOwnerError(DBTYPE_USER);
		return false;
	}
	bool resMsg = Init(DBTYPE_MSG);
	if (!resMsg)
	{
		emit dbOwnerError(DBTYPE_MSG);
		return false;
	}
	_bInit = resUser && resMsg;
	return _bInit;
}
int  TNDataControlServer::InsertDatas(QStringList list, int dataType, int dbType)
{
	int resCount = 0;
	if (dbType == DBTYPE_USER)
	{
		QMutexLocker locker(&_mutexUser);
		switch (dataType)
		{
		case INSERT_COMPANY:
			if (_company != nullptr)
				_company->InsertDatas(list);
			break;
		}
	}
	return resCount;
}
int TNDataControlServer::InsertDatas(QList<TableBasePtr> tableBaseList, int dataType, int dbType)
{
	int resCount = 0;
	if (dbType == DBTYPE_USER)
	{
		QMutexLocker locker(&_mutexUser);
		switch (dataType)
		{
		case INSERT_FRINED:
			if (_joinStuffTable != nullptr)
				resCount = _joinStuffTable->InsertDatas(tableBaseList);
			break;
		case INSERT_GROUP:
			if (_joinStuffTable != nullptr)
				resCount = _joinStuffTable->InsertDatas(tableBaseList);
			break;
		case INSERT_FEED:
			if (_feedTable != nullptr)
				resCount = _feedTable->InsertDatas(tableBaseList);
			break;
		case INSERT_MYSTUFF:
			if (_myStuffTable != nullptr)
				resCount = _myStuffTable->InsertDatas(tableBaseList);
			break;
		case INSERT_COLLEAGUERELATION:
			if (_colleagueRelation != nullptr)
				resCount = _colleagueRelation->InsertDatas(tableBaseList);
			break;
		case INSERT_COLLEAGUEGROUP:
			if (_colleagueGroup != nullptr)
				resCount = _colleagueGroup->InsertDatas(tableBaseList);
			break;
		case INSERT_MYGROUP:
			if (_myStuffTable != nullptr)
				resCount = _myStuffTable->InsertDatas(tableBaseList);
			break;
		case INSERT_GROUPINFO:
			if (_groupInfo != nullptr)
				resCount = _groupInfo->InsertDatas(tableBaseList);
			break;
		case INSERT_GROUPMEMBER:
			if (_groupMember != nullptr)
				resCount = _groupMember->InsertDatas(tableBaseList);
			break;
		case INSERT_COMPANY:
			if (_company != nullptr)
				resCount = _company->InsertDatas(tableBaseList);
			break;
		case INSERT_NEWFRIEND:
			if (_newFriend != nullptr)
				resCount = _newFriend->InsertDatas(tableBaseList);
			break;
		default:
			break;
		}
    }else if(dbType == DBTYPE_COMMON){
        switch (dataType) {
        case INSERT_COMMON_FACEID:
            if(_faceId){
                resCount = _faceId->insertDatas(tableBaseList);
            }
            break;
        default:
            break;
        }
    }
	return resCount;
}
void TNDataControlServer::GetLatestUserFromCommonDb(TableBaseVec &tableBaseVec)
{
	if (!_bInitCommon)
	{
		if (!Init(DBTYPE_COMMON))
		{
			return;
		}
	}
	if (_loginUser != nullptr)	
		_loginUser->GetLatestUser(tableBaseVec);
}
int TNDataControlServer::GetUserIsExist(const QString &mobile)
{
	if (!_bInitCommon)
	{
		if (!Init(DBTYPE_COMMON))
		{
			emit dbOwnerError(DBTYPE_COMMON);
			return -1;
		}
	}
	if (_loginUser != nullptr)
		return _loginUser->GetUserIsExist(mobile);
	else
		return false;
}
void TNDataControlServer::QueryCommonDB(TableBaseVec &tableBaseVec, const QString &tableName, const QString &queryItem, const QString &queryValue, int pageNum, int pageIndex)
{
	if (!_bInitCommon)
	{
		if (!Init(DBTYPE_COMMON))
		{
			emit dbOwnerError(DBTYPE_COMMON);
			return;
		}
	}
	if (_loginUser != nullptr)
		_loginUser->Query(tableBaseVec, queryItem, queryValue);
}
bool TNDataControlServer::InsertDatas(TableBasePtr tableBase, int dbType)
{
    bool success = false;
	if (dbType == DBTYPE_USER)
	{
		QMutexLocker locker(&_mutexUser);
		if (st_FeedPtr feed = std::dynamic_pointer_cast<st_Feed>(tableBase))
		{
			if (_feedTable != nullptr)
				success = _feedTable->InsertDatas(feed);
		}
		else if (st_VersionPtr version = std::dynamic_pointer_cast<st_Version>(tableBase))
		{
			if (_versionTable != nullptr)
				success = _versionTable->InsertDatas(version);
		}
		else if (st_JoinStuffPtr JoinStuff = std::dynamic_pointer_cast<st_JoinStuff>(tableBase))
		{
			if (_joinStuffTable != nullptr)
				success = _joinStuffTable->InsertDatas(JoinStuff);
		}
		else if (st_MyStuffPtr myStuff = std::dynamic_pointer_cast<st_MyStuff>(tableBase))
		{
			if (_myStuffTable != nullptr)
				success = _myStuffTable->InsertDatas(myStuff);
		}
		else if (st_ChatAppListPtr chatAppList = std::dynamic_pointer_cast<st_ChatAppList>(tableBase))
		{
			if (_chatAppList != nullptr)
				success = _chatAppList->InsertDatas(chatAppList);
		}
		else if (st_ChatSettingsPtr chatSettings = std::dynamic_pointer_cast<st_ChatSettings>(tableBase))
		{
			if (_chatSettings != nullptr)
				success = _chatSettings->InsertDatas(chatSettings);
		}
		else if (st_GroupInfoPtr groupInfo = std::dynamic_pointer_cast<st_GroupInfo>(tableBase))
		{
			if (_groupInfo != nullptr)
				success = _groupInfo->InsertDatas(groupInfo);
		}
		else if (st_GroupMemberPtr groupMember = std::dynamic_pointer_cast<st_GroupMember>(tableBase))
		{
			if (_groupMember != nullptr)
				success = _groupMember->InsertDatas(groupMember);
		}
		else if (st_ColleagueGroupPtr group = std::dynamic_pointer_cast<st_ColleagueGroup>(tableBase))
		{
			if (_colleagueGroup != nullptr)
				 success = _colleagueGroup->InsertDatas(group);
		}
		else if (st_ColleagueRelationPtr relation = std::dynamic_pointer_cast<st_ColleagueRelation>(tableBase))
		{
			if (_colleagueRelation != nullptr)
				success = _colleagueRelation->InsertDatas(relation);
		}
		else if (st_SetUpPtr setup = std::dynamic_pointer_cast<st_SetUp>(tableBase))
		{
			if (_setUp != nullptr)
			 success = _setUp->InsertDatas(setup);
		}
		else if (st_BlackListPtr blackList = std::dynamic_pointer_cast<st_BlackList>(tableBase))
		{
			if (_blackList != nullptr)
				success = _blackList->InsertDatas(blackList);
		}
		else if (st_CompanyInfoPtr company = std::dynamic_pointer_cast<st_CompanyInfo>(tableBase))
		{
			if (_company != nullptr)
				success = _company->InsertDatas(company);
		}
        else if (st_NewFriendPtr newFriend = std::dynamic_pointer_cast<st_NewFriend>(tableBase))
        {
			if (_newFriend != nullptr)
				success = _newFriend->InsertDatas(newFriend);
        }
		else if (st_OwnerDataPtr userOwner = std::dynamic_pointer_cast<st_OwnerData>(tableBase))
		{
			if (_userOwner != nullptr)
				success = _userOwner->InsertDatas(userOwner);
		}
	}
	else if (dbType == DBTYPE_MSG)
	{
		QMutexLocker locker(&_mutexMsg);
		if (st_BMessage0Ptr message = std::dynamic_pointer_cast<st_BMessage0>(tableBase))
		{
			if (_bmessage0 != nullptr)
				 success = _bmessage0->InsertDatas(message);
		}
		else if (st_MessageFaultPtr messageFault = std::dynamic_pointer_cast<st_MessageFault>(tableBase))
		{
			if (_messageFault != nullptr)
				success = _messageFault->InsertDatas(messageFault);
		}
		else if (st_MessageOperatePtr messageOperate = std::dynamic_pointer_cast<st_MessageOperate>(tableBase))
		{
			if (_messageOperate != nullptr)
				success = _messageOperate->InsertDatas(messageOperate);
		}
		else if (st_MessageAppInfoPtr messageAppInfo = std::dynamic_pointer_cast<st_MessageAppInfo>(tableBase))
		{
			if (_messageAppInfo != nullptr)
				success = _messageAppInfo->InsertDatas(messageAppInfo);
		}
		else if (st_SessionBackgroundPtr sessionBackground = std::dynamic_pointer_cast<st_SessionBackground>(tableBase))
		{
			if (_sessionBackGround != nullptr)
				success = _sessionBackGround->InsertDatas(sessionBackground);
		}
		else if (st_SessionPtr session = std::dynamic_pointer_cast<st_Session>(tableBase))
		{
			if (_session != nullptr)
				success = _session->InsertDatas(session);
		}
		else if (st_ReadSessionReqPtr readSession = std::dynamic_pointer_cast<st_ReadSessionReq>(tableBase))
		{
			if (_readSessionReq != nullptr)
				success = _readSessionReq->InsertDatas(readSession);
		}
		else if (st_OwnerDataPtr msgOwner = std::dynamic_pointer_cast<st_OwnerData>(tableBase))
		{
			if (_msgOwner != nullptr)
				success = _msgOwner->InsertDatas(msgOwner);
		}
	}
	else if (dbType == DBTYPE_COMMON)
	{
		if (st_LoginUserPtr loginUser = std::dynamic_pointer_cast<st_LoginUser>(tableBase))
		{
			if (_loginUser != nullptr)
				success = _loginUser->InsertDatas(loginUser);
		}
	}
    return success;
}


bool TNDataControlServer::GetAllFieldsByTableName(const QString &tableName, TableBaseVec &tableBaseVec, int dbType)
{
	bool Ret = false;
	if (dbType == DBTYPE_USER)
	{
		QMutexLocker locker(&_mutexUser);
		if (tableName == "Feed")
		{
			if (_feedTable != nullptr)
				Ret = _feedTable->GetAllFields(tableBaseVec);
		}
		else if (tableName == "JoinStuff")
		{
			if (_joinStuffTable != nullptr)
				Ret = _joinStuffTable->GetAllFields(tableBaseVec);
		}
		else if (tableName == "MyStuff")
		{
			if (_myStuffTable != nullptr)
				Ret = _myStuffTable->GetAllFields(tableBaseVec);
		}
		else if (tableName == "Version")
		{
			if (_versionTable != nullptr)
				Ret = _versionTable->GetAllFields(tableBaseVec);
		}
		else if (tableName == "ChatAppList")
		{
			if (_chatAppList != nullptr)
				Ret = _chatAppList->GetAllFields(tableBaseVec);
		}
		else if (tableName == "ChatSettings")
		{
			if (_chatSettings != nullptr)
				Ret = _chatSettings->GetAllFields(tableBaseVec);
		}
		else if (tableName == "GroupInfo")
		{
			if (_groupInfo != nullptr)
				Ret = _groupInfo->GetAllFields(tableBaseVec);
		}
		else if (tableName == "GroupMember")
		{
			if (_groupMember != nullptr)
				Ret = _groupMember->GetAllFields(tableBaseVec);
		}
		else if (tableName == "ColleagueGroup")
		{
			if (_colleagueGroup != nullptr)
				Ret = _colleagueGroup->GetAllFields(tableBaseVec);
		}
		else if (tableName == "ColleagueRelation")
		{
			if (_colleagueRelation != nullptr)
				Ret = _colleagueRelation->GetAllFields(tableBaseVec);
		}
		else if (tableName == "SetUp")
		{
			if (_setUp != nullptr)
				Ret = _setUp->GetAllFields(tableBaseVec);
		}
		else if (tableName == "CompanyInfo")
		{
			if (_company != nullptr)
				Ret = _company->GetAllFields(tableBaseVec);
		}
		else if (tableName == "NewFriend")
		{
			if (_newFriend != nullptr)
				Ret = _newFriend->GetAllFields(tableBaseVec);
		}
	}
	else if (dbType == DBTYPE_MSG)
	{
		QMutexLocker locker(&_mutexMsg);
		if (tableName == "BMessage0")
		{
			if (_bmessage0 != nullptr)
				Ret = _bmessage0->GetAllFields(tableBaseVec);
		}
		else if (tableName == "MessageFault")
		{
			if (_messageFault != nullptr)
				Ret = _messageFault->GetAllFields(tableBaseVec);
		}
		else if (tableName == "MessageOperate")
		{
			if (_messageOperate != nullptr)
				Ret = _messageOperate->GetAllFields(tableBaseVec);
		}
		else if (tableName == "MessageAppInfo")
		{
			if (_messageAppInfo != nullptr)
				Ret = _messageAppInfo->GetAllFields(tableBaseVec);
		}
		else if (tableName == "Session")
		{
			if (_session != nullptr)
				Ret = _session->GetAllFields(tableBaseVec);
		}
		else if (tableName == "SessionBackground")
		{
			if (_sessionBackGround != nullptr)
				Ret = _sessionBackGround->GetAllFields(tableBaseVec);
		}
		else if (tableName == "ReadSession")
		{
			if (_readSessionReq != nullptr)
				Ret = _readSessionReq->GetAllFields(tableBaseVec);
		}
	}
	else if (dbType == DBTYPE_COMMON)
	{
		if (tableName == "LoginUser")
		{
			if (_loginUser != nullptr)
				Ret = _loginUser->GetAllFields(tableBaseVec);
		}
	}
	return Ret;
}
int  TNDataControlServer::FuzzyQuery(TableBaseVec &tableBaseVec, const QString &tableName, const QString &Value, QStringList keyList, const QString &type, int dbType)
{
	int Ret = -1;
	if (dbType == DBTYPE_USER)
	{
		QMutexLocker locker(&_mutexUser);
		if (tableName == "Feed")
		{
			if (_feedTable != nullptr)
				Ret = _feedTable->FuzzyQuery(tableBaseVec, Value, keyList, type);
		}
	}
	return Ret;
}
bool TNDataControlServer::MultiQuery(TableBaseVec &tableBaseVec, const QString &tableName, const QString &queryItem1, const QString &queryItem2, const QString queryValue1, const QString queryValue2, int dbType, int pageNum, int pageIndex)
{
	bool Ret = false;
	if (dbType == DBTYPE_USER)
	{
		QMutexLocker locker(&_mutexUser);
		if (tableName == "JoinStuff")
		{
			if (_joinStuffTable != nullptr)
				Ret = _joinStuffTable->MultiQuery(tableBaseVec, queryItem1, queryItem2, queryValue1, queryValue2);
		}
		else if (tableName == "MyStuff")
		{
			if (_myStuffTable != nullptr)
				Ret = _myStuffTable->MultiQuery(tableBaseVec, queryItem1, queryItem2, queryValue1, queryValue2);
		}
	}
	return Ret;
}

bool TNDataControlServer::queryHistoryMsg(TableBaseVec &tableBaseVec,
                                          const QString &sessionId,
                                          const QString &msgId,
                                          int num)
{
	QMutexLocker locker(&_mutexMsg);
	if (_bmessage0 != nullptr)
		return _bmessage0->queryHistoryMsg(tableBaseVec, sessionId, msgId, num);
	else
		return false;
}


bool TNDataControlServer::Query(TableBaseVec &tableBaseVec, const QString &tableName, const QString &queryItem, const QString &queryValue, int dbType, int pageNum, int pageIndex, int newMsgNum)
{
	bool Ret = false;
	if (dbType == DBTYPE_USER)
	{
		QMutexLocker locker(&_mutexUser);
		if (tableName == "Feed")
		{
			if (_feedTable != nullptr)
				Ret = _feedTable->Query(tableBaseVec, queryItem, queryValue);
		}
		else if (tableName == "JoinStuff")
		{
			if (_joinStuffTable != nullptr)
				Ret = _joinStuffTable->Query(tableBaseVec, queryItem, queryValue);
		}
		else if (tableName == "MyStuff")
		{
			if (_myStuffTable != nullptr)
				Ret = _myStuffTable->Query(tableBaseVec, queryItem, queryValue);
		}
		else if (tableName == "Version")
		{
			if (_versionTable != nullptr)
				Ret = _versionTable->Query(tableBaseVec, queryItem, queryValue);
		}
		else if (tableName == "ChatAppList")
		{
			if (_chatAppList != nullptr)
				Ret = _chatAppList->Query(tableBaseVec, queryItem, queryValue);
		}
		else if (tableName == "ChatSettings")
		{
			if (_chatSettings != nullptr)
				Ret = _chatSettings->Query(tableBaseVec, queryItem, queryValue);
		}
		else if (tableName == "GroupInfo")
		{
			if (_groupInfo != nullptr)
				Ret = _groupInfo->Query(tableBaseVec, queryItem, queryValue);
		}
		else if (tableName == "GroupMember")
		{
			if (_groupMember != nullptr)
				Ret = _groupMember->Query(tableBaseVec, queryItem, queryValue);
		}
		else if (tableName == "ColleagueGroup")
		{
			if (_colleagueGroup != nullptr)
				Ret = _colleagueGroup->Query(tableBaseVec, queryItem, queryValue);
		}
		else if (tableName == "ColleagueRelation")
		{
			if (_colleagueRelation != nullptr)
				Ret = _colleagueRelation->Query(tableBaseVec, queryItem, queryValue);
		}
		else if (tableName == "SetUp")
		{
			if (_setUp != nullptr)
				Ret = _setUp->Query(tableBaseVec, queryItem, queryValue);
		}
		else if (tableName == "BlackList")
		{
			if (_blackList != nullptr)
				Ret = _blackList->Query(tableBaseVec, queryItem, queryValue);
		}
		else if (tableName == "CompanyInfo")
		{
			if (_company != nullptr)
				Ret = _company->Query(tableBaseVec, queryItem, queryValue);
		}
		else if (tableName == "NewFriend")
		{
			if (_newFriend != nullptr)
				Ret = _newFriend->Query(tableBaseVec, queryItem, queryValue);
		}
	}
	else if (dbType == DBTYPE_MSG)
	{
		QMutexLocker locker(&_mutexMsg);
		if (tableName == "BMessage0")
		{
			if (_bmessage0 != nullptr)
                Ret = _bmessage0->Query(tableBaseVec, queryItem, queryValue, pageNum, pageIndex, newMsgNum);
		}
		else if (tableName == "MessageFault")
		{
			if (_messageFault != nullptr)
				Ret = _messageFault->Query(tableBaseVec, queryItem, queryValue);
		}
		else if (tableName == "MessageOperate")
		{
			if (_messageOperate != nullptr)
				Ret = _messageOperate->Query(tableBaseVec, queryItem, queryValue);
		}
		else if (tableName == "MessageAppInfo")
		{
			if (_messageAppInfo != nullptr)
				Ret = _messageAppInfo->Query(tableBaseVec, queryItem, queryValue);
		}
		else if (tableName == "Session")
		{
			if (_session != nullptr)
				Ret = _session->Query(tableBaseVec, queryItem, queryValue);
		}
		else if (tableName == "SessionBackground")
		{
			if (_sessionBackGround != nullptr)
				Ret = _sessionBackGround->Query(tableBaseVec, queryItem, queryValue);
		}
	}
	else if (dbType == DBTYPE_COMMON)
	{
		if (tableName == "LoginUser")
		{
			if (_loginUser != nullptr)
				Ret = _loginUser->Query(tableBaseVec, queryItem, queryValue);
		}
        if(tableName == "FaceId"){
            if (_faceId!= nullptr)
                Ret = _faceId->Query(tableBaseVec, queryItem, queryValue);
        }
	}
	return Ret;
}

bool TNDataControlServer::BatchQuery(TableBaseVec &tableBaseVec, const QString &tableName, const QString &queryItem, const QStringList &queryValues,int dbType)
{
    bool Ret = false;
	if (dbType == DBTYPE_USER)
	{
		QMutexLocker locker(&_mutexUser);
		if (tableName == "Feed")
		{
			if (_feedTable != nullptr)
				Ret = _feedTable->batchQuery(tableBaseVec, queryItem, queryValues);
		}
	}
    return Ret;
}

int TNDataControlServer::DeleteFromTableNameByField(const QString &tableName, const QString &fieldName, QList<QString> fieldValueList,int dbType)
{
	int result = -1;
	if (dbType == DBTYPE_MSG)
	{
		QMutexLocker locker(&_mutexMsg);
		if (tableName == "Session")
		{
			if (_session != nullptr)
				result = _session->Delete(fieldName, fieldValueList);
		}
		else if (tableName == "BMessage0")
		{
			if (_bmessage0 != nullptr)
				result = _bmessage0->Delete(fieldName, fieldValueList);
		}
	}
	else if (dbType == DBTYPE_USER)
	{
		QMutexLocker locker(&_mutexUser);
		if (tableName == "JoinStuff")
		{
			if (_joinStuffTable != nullptr)
				result = _joinStuffTable->Delete(fieldName, fieldValueList);
		}
		else if (tableName == "MyStuff")
		{
			if (_myStuffTable != nullptr)
				result = _myStuffTable->Delete(fieldName, fieldValueList);
		}
		else if (tableName == "ColleagueRelation")
		{
			if (_colleagueRelation != nullptr)
				result = _colleagueRelation->Delete(fieldName, fieldValueList);
		}
		else if (tableName == "ColleagueGroup")
		{
			if (_colleagueGroup != nullptr)
				result = _colleagueGroup->Delete(fieldName, fieldValueList);
		}
		else if (tableName == "GroupInfo")
		{
			if (_groupInfo != nullptr)
				result = _groupInfo->Delete(fieldName, fieldValueList);
		}
		else if (tableName == "GroupMember")
		{
			if (_groupMember != nullptr)
				result = _groupMember->Delete(fieldName, fieldValueList);
		}
		else if (tableName == "ComapnyInfo")
		{
			if (_company != nullptr)
				result = _company->Delete(fieldName, fieldValueList);
		}
		else if (tableName == "NewFriend")
		{
			if (_newFriend != nullptr)
				result = _newFriend->Delete(fieldName, fieldValueList);
		}
    }else if(dbType == DBTYPE_COMMON){
        if(tableName == "FaceId"){
            if(_faceId != NULL)
                result = _faceId->Delete(fieldName, fieldValueList);
        }
    }
	return result;
}
int  TNDataControlServer::DeleteFromTableNameByFieldList(const QString &tableName, QList<QVector<QString>> delList, int dbType)
{
	int result = -1;
	if (dbType == DBTYPE_USER)
	{
		QMutexLocker locker(&_mutexUser);
		if (tableName == "GroupMember")
		{
			if (_groupMember != nullptr)
				result = _groupMember->Delete(delList);
		}
	}
	return result;
}
bool TNDataControlServer::DeleteFromTableNameByField(const QString &tableName, const QString &fieldName, const QString &fieldValue,int dbType)
{
	bool result = false;
	if (dbType == DBTYPE_USER)
	{
		QMutexLocker locker(&_mutexUser);
		if (tableName == "GroupInfo")
		{
			if (_groupInfo != nullptr)
				result = _groupInfo->Delete(fieldName, fieldValue);
		}
		else if (tableName == "GroupMember")
		{
			if (_groupMember != nullptr)
				result = _groupMember->Delete(fieldName, fieldValue);
		}
		else if (tableName == "JoinStuff")
		{
			if (_joinStuffTable != nullptr)
				result = _joinStuffTable->Delete(fieldName, fieldValue);
		}
		else if (tableName == "MyStuff")
		{
			if (_myStuffTable != nullptr)
				result = _myStuffTable->Delete(fieldName, fieldValue);
		}
		else if (tableName == "ColleagueGroup")
		{
			if (_colleagueGroup != nullptr)
				result = _colleagueGroup->Delete(fieldName, fieldValue);
		}
		else if (tableName == "ColleagueRelation")
		{
			if (_colleagueRelation != nullptr)
				result = _colleagueRelation->Delete(fieldName, fieldValue);
		}	
		else if (tableName == "ComapnyInfo")
		{
			if (_company != nullptr)
				result = _company->Delete(fieldName, fieldValue);
		}
        else if (tableName == "NewFriend")
        {
			if (_newFriend != nullptr)
				result = _newFriend->Delete(fieldName, fieldValue);
        }
	}
	else if (dbType == DBTYPE_MSG)
	{
		QMutexLocker locker(&_mutexMsg);
		if (tableName == "Session")
		{
			if (_session != nullptr)
				result = _session->Delete(fieldName, fieldValue);
		}
		else if (tableName == "BMessage0")
		{
			if (_bmessage0 != nullptr)
				result = _bmessage0->Delete(fieldName, fieldValue);
		}
		else if (tableName == "ReadSession")
		{
			if (_readSessionReq != nullptr)
				result = _readSessionReq->Delete(fieldName, fieldValue);
		}
	}
	return result;
}

bool TNDataControlServer::DeleteFromTableNameByFieldEx(const QString &tableName, const QString &fieldName, const QString &fieldValue, const QString &fieldNameEx, const QString &fieldValueEx,int dbType)
{
	bool result = false;
	if (dbType == DBTYPE_USER)
	{
		QMutexLocker locker(&_mutexUser);
		if (tableName == "GroupMember")
		{
			if (_groupMember != nullptr)
				result = _groupMember->DeleteEx(fieldName, fieldValue, fieldNameEx, fieldValueEx);
		}
	}
	return result;
}


bool TNDataControlServer::UpdateSetValueByField(const QString &tableName, const QString &fieldName, const QString &fieldValue, const QString &whereName, const QString &whereValue, int dbType)
{
	bool result = false;
	if (dbType == DBTYPE_MSG)
	{
		QMutexLocker locker(&_mutexMsg);
		if (tableName == "Session")
		{
			if (_session != nullptr)
				result = _session->UpdateSetValueByField(fieldName, fieldValue, whereName, whereValue);
		}
		else if (tableName == "BMessage0")
		{
			if (_bmessage0 != nullptr)
				result = _bmessage0->UpdateSetValueByField(fieldName, fieldValue, whereName, whereValue);
		}
	}
	else if (dbType == DBTYPE_USER)
	{
		QMutexLocker locker(&_mutexUser);
		if (tableName == "GroupInfo")
		{
			if (_groupInfo != nullptr)
				result = _groupInfo->UpdateSetValueByField(fieldName, fieldValue, whereName, whereValue);
		}
		else if (tableName == "Version")
		{
			if (_versionTable != nullptr)
				result = _versionTable->UpdateSetValueByField(fieldName, fieldValue, whereName, whereValue);
        }
        else if (tableName == "BlackList")
        {
			if (_blackList != nullptr)
				result = _blackList->UpdateSetValueByField(fieldName, fieldValue, whereName, whereValue);
        }
        else if (tableName == "NewFriend")
        {
			if (_newFriend != nullptr)
				result = _newFriend->UpdateSetValueByField(fieldName, fieldValue, whereName, whereValue);
        }
		else if (tableName == "MyStuff")
		{
			if (_myStuffTable != nullptr)
				result = _myStuffTable->UpdateSetValueByField(fieldName, fieldValue, whereName, whereValue);
        }else if(tableName == "Feed"){
            if(_feedTable)
                result = _feedTable->updateSetValueByField(fieldName,fieldValue,whereName,whereValue);
        }
	}
	return result;
}

bool TNDataControlServer::UpdateSetValueByFieldEx(const QString &tableName, const QString &fieldName, const QString &fieldValue, const QString &whereName, const QString &whereValue, const QString &fieldNameEx, const QString &fieldValueEx, int dbType)
{
	bool result = false;
	if (dbType == DBTYPE_MSG)
	{
		QMutexLocker locker(&_mutexMsg);
		if (tableName == "BMessage0")
		{
			if (_bmessage0 != nullptr)
				result = _bmessage0->UpdateSetValueByFieldEx(fieldName, fieldValue, whereName, whereValue, fieldNameEx, fieldValueEx);
		}
		else if (tableName == "Session")
		{
			if (_session != nullptr)
				result = _session->UpdateSetValueByFieldEx(fieldName, fieldValue, whereName, whereValue, fieldNameEx, fieldValueEx);
		}
	}
	else if (dbType == DBTYPE_USER)
	{
		QMutexLocker locker(&_mutexUser);
		if (tableName == "GroupInfo")
		{
			if (_groupInfo != nullptr)
				result = _groupInfo->UpdateSetValueByFieldEx(fieldName, fieldValue, fieldNameEx, fieldValueEx, whereName, whereValue);
		}
	}
	return result;
}

bool TNDataControlServer::UpdateSetValueByFieldMap(const QString &tableName, QMap<QString, QString>& fieldMap, const QString &whereName, const QString &whereValue, int dbType)
{
	bool result = false;
	if (dbType == DBTYPE_MSG)
	{
		QMutexLocker locker(&_mutexMsg);
		if (tableName == "BMessage0")
		{
			if (_bmessage0 != nullptr)
				result = _bmessage0->UpdateSetValueByFieldMap(fieldMap, whereName, whereValue);
		}
	}
	else if (dbType == DBTYPE_USER)
	{
		QMutexLocker locker(&_mutexUser);
		if (tableName == "Feed")
		{
			if (_feedTable != nullptr)
				result = _feedTable->UpdateSetValueByFieldMap(fieldMap, whereName, whereValue);
		}
	}
	return result;
}


void TNDataControlServer::ClearByTableName(const QString &tableName,int dbType)
{
	if (dbType == DBTYPE_MSG)
	{
		QMutexLocker locker(&_mutexMsg);
		if (tableName == "BMessage0")
		{
			if (_bmessage0 != nullptr)
				_bmessage0->ClearAll();
		}
		else if (tableName == "MessageFault")
		{
			if (_messageFault != nullptr)
				_messageFault->ClearAll();
		}
		else if (tableName == "MessageOperate")
		{
			if (_messageOperate != nullptr)
				_messageOperate->ClearAll();
		}
		else if (tableName == "MessageAppInfo")
		{
			if (_messageAppInfo != nullptr)
				_messageAppInfo->ClearAll();
		}
		else if (tableName == "Session")
		{
			if (_session != nullptr)
				_session->ClearAll();
		}
		else if (tableName == "SessionBackground")
		{
			if (_sessionBackGround != nullptr)
				_sessionBackGround->ClearAll();
		}
		else if (tableName == "ReadSession")
		{
			if (_readSessionReq != nullptr)
				_readSessionReq->ClearAll();
		}
	}
	else if (dbType == DBTYPE_USER)
	{
		QMutexLocker locker(&_mutexUser);
		if (tableName == "ChatAppList")
		{
			if (_chatAppList != nullptr)
				_chatAppList->ClearAll();
		}
		else if (tableName == "ChatSettings")
		{
			if (_chatSettings != nullptr)
				_chatSettings->ClearAll();
		}
		else if (tableName == "GroupInfo")
		{
			if (_groupInfo != nullptr)
				_groupInfo->ClearAll();
		}
		else if (tableName == "GroupMember")
		{
			if (_groupMember != nullptr)
				_groupMember->ClearAll();
		}
		else if (tableName == "ColleagueGroup")
		{
			if (_colleagueGroup != nullptr)
				_colleagueGroup->ClearAll();
		}
		else if (tableName == "ColleagueRelation")
		{
			if (_colleagueRelation != nullptr)
				_colleagueRelation->ClearAll();
		}
		else if (tableName == "SetUp")
		{
			if (_setUp != nullptr)
				_setUp->ClearAll();
		}
		else if (tableName == "NewFriend")
		{
			if (_newFriend != nullptr)
				_newFriend->ClearAll();
		}
	}
	else if (dbType == DBTYPE_COMMON)
	{
		if (tableName == "LoginUser")
		{
			if (_loginUser != nullptr)
				_loginUser->ClearAll();
		}
	}
}
void TNDataControlServer::CloseDb()
{
	if (_sqlDb.isOpen())
		_sqlDb.close();
	if (_sqlMsgDb.isOpen())
		_sqlMsgDb.close();
	_bInit = false;
}

TNDataControlServer* TNDataControlServer::GetInstance()
{
	static QMutex	s_mutex;
	if (_Instance == NULL)
	{
		QMutexLocker locker(&s_mutex);
		if (_Instance == NULL)
		{
			_Instance = new TNDataControlServer();
		}
	}
	return _Instance;
}

QSqlDatabase* TNDataControlServer::GetConnectionDB(int dbType)
{
	if (dbType == DBTYPE_COMMON)
		return &_sqlCommonDb;
	else if (dbType == DBTYPE_USER)
		return &_sqlDb;
	else if (dbType == DBTYPE_MSG)
		return &_sqlMsgDb;
	return nullptr;
}

void TNDataControlServer::getAllGroupChatMemberCollectionSort(const QString &groupChatId, TableBaseVec &tableBaseVec)
{
	QMutexLocker locker(&_mutexUser);
    QSqlQuery query(_sqlDb);
    bool ret = query.exec(QString("Select * From groupmember,feed where groupmember.FeedId = feed.FeedId and groupid = '%1'").arg(groupChatId));
    if (ret)
    {
        while (query.next())
        {
            st_FeedPtr FeedTable = std::make_shared<st_Feed>();
            FeedTable->SetFeedID(query.value("feedId").toString());
            FeedTable->SetAvatarID(query.value("avatarId").toString());
            FeedTable->SetTitle(query.value("title").toString());
            FeedTable->SetTitlePinYin(query.value("titlePinYin").toString());
            FeedTable->SetSubTile(query.value("subtitle").toString());
            FeedTable->SetUserID(query.value("userId").toString());
            FeedTable->SetTag(query.value("tag").toString());
            FeedTable->SetSocialLevel(query.value("socialLevel").toString());
            FeedTable->SetConsumeLevel(query.value("consumeLevel").toString());
            FeedTable->SetServiceLevel(query.value("serviceLevel").toString());
            FeedTable->SetKeyWord(query.value("keyword").toString());
            FeedTable->SetSex(query.value("sex").toString());
            FeedTable->SetBirthday(query.value("birthday").toString());
            FeedTable->SetVersion(query.value("version").toString());
            FeedTable->SetComID(query.value("comId").toString());
            TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(FeedTable);
            tableBaseVec.push_back(tempTableBase);
        }
    }
    return;
}
bool TNDataControlServer::isMySelf(const QString &feedId)
{
	QMutexLocker locker(&_mutexUser);
	if (_myStuffTable != nullptr)
		return _myStuffTable->isMySelf(feedId);
	else
		return false;
}
int  TNDataControlServer::GetUNReadSeesionCount(const QString &feed)
{
	/*
	IM会话表模式更新后， 此接口已经废弃 2018.3.5
	*/
	QMutexLocker locker(&_mutexMsg);
	if (_session != nullptr)
		return _session->GetUNReadCount(feed);
	else
		return -1;
}

QString TNDataControlServer::getSessionUnreadMsg(const QString &sessionId, int count)
{
	QMutexLocker locker(&_mutexMsg);
    st_BMessage0Ptr message;
	if (_bmessage0 != nullptr && _bmessage0->getUnreadFirstMsg(sessionId, count, message)){
        return message->GetMsgId();
    }else{
        return "";
    }
}

bool TNDataControlServer::getUnreadSessionMsg(TableBaseVec &tableBaseVec,
                                              const QString &sessionId,
                                              const QString &currentFristMsgId,
                                              const QString &firstUnreadMsgId)
{
	QMutexLocker locker(&_mutexMsg);
	if (_bmessage0 != nullptr)
		return _bmessage0->getUnreadMsg(tableBaseVec, sessionId, currentFristMsgId, firstUnreadMsgId);
	else
		return false;
}
bool TNDataControlServer::getOwnerDataStatus(QSqlDatabase *db,int dbType)
{
	bool ret = false;
	QString userId = TNUserDataUtil::GetInstance()->getUserPluginParam()->strTnUserID;
	QString mobile = TNUserDataUtil::GetInstance()->getUserPluginParam()->strMobile;

	switch (dbType)
	{
	case DBTYPE_USER:
		_userOwner = std::make_shared<TNOwnerData>();
		if (_userOwner != nullptr)
		{
			_userOwner->SetDBConnect(db);
			_userOwner->createTable();

			QString dbOwner = getDBOwner(dbType);
			if (dbOwner.isEmpty())
			{
				st_OwnerDataPtr ownerData = std::make_shared<st_OwnerData>();
				ownerData->setUserId(userId);
				ownerData->setMobileId(mobile);
				ownerData->setExt(TNVersionInfo::appVersion());
				InsertDatas(std::dynamic_pointer_cast<TableBase>(ownerData), DBTYPE_USER);
				ret = true;
			}
			else if (dbOwner == TNUserDataUtil::GetInstance()->getUserPluginParam()->strTnUserID)
			{
				ret = true;
			}
			else
			{
				qInfo() << "[LocalStorage][TNDataControlServer]getOwnerDataStatus ,the toon db is not current user's";
				ret = false;
			}
		}
		break;
	case DBTYPE_MSG:
		_msgOwner = std::make_shared<TNOwnerData>();
		if (_msgOwner != nullptr)
		{
			_msgOwner->SetDBConnect(db);
			_msgOwner->createTable();

			QString dbOwner = getDBOwner(dbType);
			if (dbOwner.isEmpty())
			{
				st_OwnerDataPtr ownerData = std::make_shared<st_OwnerData>();
				ownerData->setUserId(userId);
				ownerData->setMobileId(mobile);
				ownerData->setExt(TNVersionInfo::appVersion());
				InsertDatas(std::dynamic_pointer_cast<TableBase>(ownerData), DBTYPE_MSG);
				ret = true;
			}
			else if (dbOwner == TNUserDataUtil::GetInstance()->getUserPluginParam()->strTnUserID)
			{
				ret = true;
			}
			else
			{
				qInfo() << "[LocalStorage][TNDataControlServer]getOwnerDataStatus ,the msg db is not current user's";
				ret = false;
			}
		}
		break;
	default:
		break;
	}
	return ret;
}
const QString TNDataControlServer::getDBOwner(int dbType)
{
	QString ownerUserId;
	switch (dbType)
	{
	case DBTYPE_USER:
		if (_userOwner != nullptr)
		{
			TableBaseVec owner;
			_userOwner->GetAllFields(owner);
			if (owner.size() > 0)
			{
				st_OwnerDataPtr data = std::dynamic_pointer_cast<st_OwnerData>(owner[0]);
				return data->getUserId();
			}
		}
		break;
	case DBTYPE_MSG:
		if (_msgOwner != nullptr)
		{
			TableBaseVec owner;
			_msgOwner->GetAllFields(owner);
			if (owner.size() > 0)
			{
				st_OwnerDataPtr data = std::dynamic_pointer_cast<st_OwnerData>(owner[0]);
				return data->getUserId();
			}
		}
		break;
	default:
		break;
	}
	return ownerUserId;
}
int TNDataControlServer::updateFeedRemark(QString feedBelong, QString remark, QString remarkPY)
{
	QMutexLocker locker(&_mutexUser);
	int ret = 0;
	if (_joinStuffTable != nullptr)
		ret = _joinStuffTable->updateFeedRemark(feedBelong, remark, remarkPY);
	else
		qInfo() <<"[LocalStorage][TNDataControlServer]updateFeedRemark Err: _feedTable is is null";
	return ret;
}
bool TNDataControlServer::updateSetValueByValueMap(const QString &tableName, const QString &fieldName, const QString &whereName, QMap<QString, QString> valueMap, int dbType)
{
	bool result = false;
	if (dbType == DBTYPE_USER)
	{
		QMutexLocker locker(&_mutexUser);
		if (tableName == "CompanyInfo")
		{
			if (_company != nullptr)
				result = _company->UpdateSetValueByValueMap(valueMap, fieldName, whereName);
		}
		else if (tableName == "Feed")
		{
			if (_feedTable != nullptr)
				result = _feedTable->UpdateSetValueByValueMap(valueMap, fieldName,whereName);
		}
	}
	return result;
}
bool TNDataControlServer::initErrorFixed(int dbType)
{
	bool res = true;
	int status = TNConfig::instance()->getFixedErrStatus();
	if (status == 0)
		return res;
	switch (dbType)
	{
	case DBTYPE_COMMON:
		if (status == 1) //common level,common数据块一块删除
		{
			QList<QString> fileList;
			fileList.append(TNPathUtil::getCommonDbPath());
			fileList.append(TNPathUtil::getConfigFile());
			for (int i = 0; i < fileList.size(); i++)
			{
				if (!res)
				{
					return res;
				}
				QFile fileTemp(fileList[i]);
				if (fileTemp.exists())
					res = fileTemp.remove();
			}
			TNConfig::instance()->setFixedErrStatus(0);
			TNConfig::instance()->setFixedFailed(false);
		}
		break;
	case DBTYPE_USER:
	case DBTYPE_MSG:
		if (status == 2 || status == 3)
		{
			QString userPath = TNPathUtil::getUserPath();
			if (userPath.isEmpty() || !removeFileContext(userPath))
			{
				res =  false;
			}
			if (res)
			{
				TNConfig::instance()->setFixedFailed(false);
				TNConfig::instance()->setFixedErrStatus(0);
			}
		}
		break;
	}
	return res;
}
bool TNDataControlServer::removeFileContext(const QString &folder)
{
	QDir dir(folder);
	QString errorFile;
	QFileInfoList fileList;
	QFileInfo curFile;
	if (!dir.exists()){
		return false;
	}
	fileList = dir.entryInfoList(QDir::Files
		| QDir::Readable | QDir::Writable
		| QDir::Hidden | QDir::NoDotAndDotDot
		, QDir::Name);

	int infoNum = fileList.size();
	for (int i = infoNum - 1; i >= 0; i--)
	{
		curFile = fileList[i];
		if (curFile.isFile())//如果是文件，删除文件
		{
			QFile fileTemp(curFile.filePath());
			fileTemp.remove();
			fileList.removeAt(i);
		}
	}
	/*
	确保删除干净
	*/
	fileList.clear();
	fileList = dir.entryInfoList(QDir::Files
		| QDir::Readable | QDir::Writable
		| QDir::Hidden | QDir::NoDotAndDotDot
		, QDir::Name);
	return fileList.size() > 0 ? false : true;
}
