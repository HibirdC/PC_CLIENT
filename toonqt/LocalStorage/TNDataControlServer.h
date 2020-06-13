#ifndef TNDATACONTROLSERVER_H
#define TNDATACONTROLSERVER_H

#include <QSqlDatabase>
#include <QMutex>

#include "localstorage_global.h"
#include "LocalStorageCommon.h"
#include "TNNoticeDetailTable.h"
#include "TNNoticelistTable.h"
#include "TNFeed.h"
#include "TNVersion.h"
#include "TNMyStuff.h"
#include "TNJoinStuff.h"
#include "TNLoginUser.h"
#include "TNBMessage0.h"
#include "TNMessageFault.h"
#include "TNMessageOperate.h"
#include "TNMessageAppInfo.h"
#include "TNChatAppList.h"
#include "TNChatSettings.h"
#include "TNGroupInfo.h"
#include "TNGroupMember.h"
#include "TNSession.h"
#include "TNSessionBackground.h"
#include "TNColleagueGroup.h"
#include "TNColleagueRelation.h"
#include "TNSetUp.h"
#include "TNBlackList.h"
#include "TNCompanyInfo.h"
#include "TNNewFriend.h"
#include "tnfaceid.h"
#include "TNReadSessionReq.h"
#include "TNOwnerData.h"

#define PAGE_MAX_NUM    15
class LOCALSTORAGE_EXPORT TNDataControlServer :public QObject
{
	Q_OBJECT

protected:
	TNDataControlServer();
public:
	~TNDataControlServer();
	static TNDataControlServer* GetInstance();
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Inserts the datas described by tableBase. </summary>
	///
	/// <remarks>	田恒, 2017/2/8. </remarks>
	///
	/// <param name="tableBase">	The table base. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

    bool InsertDatas(TableBasePtr tableBase,int dbType);
	int  InsertDatas(QList<TableBasePtr> tableBaseList, int dataType, int dbType);
	int  InsertDatas(QStringList list, int dataType, int dbType);
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Clears the table name described by tableBase. </summary>
	///
	/// <remarks>	田恒, 2017/2/8. </remarks>
	///
	/// <param name="tableBase">	The table base. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void ClearByTableName(const QString &tableName, int dbType);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets all fields by table name. </summary>
	///
	/// <remarks>	田恒, 2017/2/9. </remarks>
	///
	/// <param name="tableName">   	Name of the table. </param>
	/// <param name="tableBaseVec">	[in,out] The table base vector. </param>
	///
	/// <returns>	true if it succeeds, false if it fails. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	bool GetAllFieldsByTableName(const QString &tableName, TableBaseVec &tableBaseVec,int dbType);
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	delete fields of table name by field. </summary>
	///
	/// <remarks>	李涛, 2017/4/14. </remarks>
	///
	/// <param name="tableName">   	Name of the table. </param>
	/// <param name="fieldName">	The field name. </param>
	/// <param name="fieldValue">	The field value. </param>
	///
	/// <returns>	true if it succeeds, false if it fails. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	bool DeleteFromTableNameByField(const QString &tableName, const QString &fieldName, const QString &fieldValue, int dbType);
	bool DeleteFromTableNameByFieldEx(const QString &tableName, const QString &fieldName, const QString &fieldValue, const QString &fieldNameEx, const QString &fieldValueEx, int dbType);
	bool UpdateSetValueByField(const QString &tableName, const QString &fieldName, const QString &fieldValue, const QString &whereName, const QString &whereValue,int dbType);
	bool UpdateSetValueByFieldEx(const QString &tableName, const QString &fieldName, const QString &fieldValue, const QString &whereName, const QString &whereValue, const QString &fieldNameEx, const QString &fieldValueEx, int dbType);
	bool UpdateSetValueByFieldMap(const QString &tableName, QMap<QString, QString>& fieldMap, const QString &whereName, const QString &whereValue, int dbType);
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Query 支持分页查询 </summary>
	///
	/// <remarks>	李涛, 2017/4/18. </remarks>
	///
	/// <param name="tableName">   	Name of the table. </param>
	/// <param name="queryItem">	The field name.  </param>
	/// <param name="queryValue">	The field value. </param>
	///	<param name="fieldValue">	The field value. </param>
	/// <returns>	true if it succeeds, false if it fails. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
    bool Query(TableBaseVec &tableBaseVec, const QString &tableName, const QString &queryItem, const QString &queryValue, int dbType, int pageNum = -1, int pageIndex = 0, int newMsgNum = 0);


	bool BatchQuery(TableBaseVec &tableBaseVec, const QString &tableName, const QString &queryItem, const QStringList &queryValues, int dbType);

    /*
     * 查询历史记录从offset多少条开始,查询多少条num
    */
    bool queryHistoryMsg(TableBaseVec &tableBaseVec,const QString &sessionId,
                         const QString &msgId, int num);
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	MultiQuery 支持多条件分页查询 </summary>
	///
	/// <remarks>	王志永, 2017/5/17. </remarks>
	///
	/// <param name="tableName">   	Name of the table. </param>
	/// <param name="queryItem1">	The field name.  </param>
	/// <param name="queryItem2">	The field name.  </param>
	/// <param name="fieldValue1">	The field value. </param>
	///	<param name="fieldValue2">	The field value. </param>
	/// <returns>	true if it succeeds, false if it fails. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	bool MultiQuery(TableBaseVec &tableBaseVec, const QString &tableName, const QString &queryItem1, const QString &queryItem2, const QString queryValue1, const QString queryValue2,int dbType,int pageNum = PAGE_MAX_NUM, int pageIndex = 0);
	int  DeleteFromTableNameByField(const QString &tableName, const QString &fieldName, QList<QString> fieldValueList, int dbType);
	int  DeleteFromTableNameByFieldList(const QString &tableName, QList<QVector<QString>> delList, int dbType);
	int  FuzzyQuery(TableBaseVec &tableBaseVec, const QString &tableName, const QString &Value,QStringList keyList,const QString &type,int dbType);
	//退出或者切换用户，需要关闭数据库连接
	void CloseDb();
	//重置数据库连接，新用户登录时候
	bool ResetConnect();
	void GetLatestUserFromCommonDb(TableBaseVec &tableBaseVec);
	int  GetUserIsExist(const QString &mobile);
	void QueryCommonDB(TableBaseVec &tableBaseVec, const QString &tableName, const QString &queryItem, const QString &queryValue, int pageNum = PAGE_MAX_NUM, int pageIndex = 0);
	QSqlDatabase* GetConnectionDB(int dbType);

    void getAllGroupChatMemberCollectionSort(const QString &groupChatId, TableBaseVec &tableBaseVec);
	bool isMySelf(const QString &feedId);
	int  GetUNReadSeesionCount(const QString &feed);
    //获取会话未读的第一条消息msgId
    QString getSessionUnreadMsg(const QString& sessionId,int count);
    //获取未读消息
    bool getUnreadSessionMsg(TableBaseVec &tableBaseVec,
                                const QString& sessionId,
                                const QString& currentFristMsgId,
                                const QString& firstUnreadMsgId);

	//获取数据库校验状态
	bool getOwnerDataStatus(QSqlDatabase *db,int dbType);
	const QString getDBOwner(int dbType);
	//更新好友备注信息
	int updateFeedRemark(QString feedBelong,QString remark, QString remarkPY);
	bool updateSetValueByValueMap(const QString &tableName, const QString &fieldName,const QString &whereName, QMap<QString,QString> valueMap, int dbType);
private:
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Connects the given database name. </summary>
	///
	/// <remarks>	田恒, 2017/2/8. </remarks>
	///
	/// <param name="dbName">	The database name to connect. </param>
	///
	/// <returns>	true if it succeeds, false if it fails. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	bool Connect(const QString &dbName,int dbType);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	S this object. </summary>
	///
	/// <remarks>	田恒, 2017/2/8. </remarks>
	///
	/// <returns>	true if it succeeds, false if it fails. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	bool Init(int dbType);
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Init table. </summary>
	///
	/// <remarks>	田恒, 2017/2/8. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void InitTable(int dbType);
	bool initErrorFixed(int dbType);
	bool removeFileContext(const QString &folder);

private:
	static TNDataControlServer* _Instance;
	bool					_bInit;
	bool                    _bInitCommon;
	QSqlDatabase			_sqlDb;
	QSqlDatabase            _sqlCommonDb;
	QSqlDatabase			_sqlMsgDb;
	TNFeedPtr               _feedTable;
	TNVersionPtr            _versionTable;
	TNMyStuffPtr            _myStuffTable;
	TNJoinStuffPtr          _joinStuffTable;
	TNLoginUserPtr          _loginUser;
    TNFaceIdPtr				_faceId;
	TNBMessage0Ptr			_bmessage0;
	TNMessageOperatePtr		_messageOperate;
	TNMessageFaultPtr		_messageFault;
	TNMessageAppInfoPtr		_messageAppInfo;
	TNReadSessionReqPtr		_readSessionReq;
	TNChatAppListPtr		_chatAppList;
	TNChatSettingsPtr		_chatSettings;
	TNGroupInfoPtr			_groupInfo;
	TNGroupMemberPtr		_groupMember;
	TNSessionPtr			_session;
	TNSessionBackgroundPtr	_sessionBackGround;
	TNColleagueGroupPtr		_colleagueGroup;
	TNColleagueRelationPtr	_colleagueRelation;
	TNSetUpPtr				_setUp;
	TNBlackListPtr			_blackList;
	TNCompanyInfoPtr        _company;
    TNNewFriendPtr			_newFriend;
	TNOwnerDataPtr          _userOwner;
	TNOwnerDataPtr          _msgOwner;
	QMutex					_mutexMsg;
	QMutex					_mutexUser;

Q_SIGNALS:
	void dbOwnerError(int);
};

#endif

