#include "TNIMReadSessionManager.h"
#include "common_global.h"
#include "tmtp.h"
TNIMReadSessionManager::TNIMReadSessionManager(QObject *parent)
	: QObject(parent)
{

}

TNIMReadSessionManager::~TNIMReadSessionManager()
{

}

void TNIMReadSessionManager::SaveReadSessionReq(const QString& sessionId, const Toon::SyncSessionStatusReq& readSessionReq)
{
	st_ReadSessionReqPtr readSession = std::make_shared<st_ReadSessionReq>();
	readSession->SetReqId(readSessionReq.req_id.c_str());
	readSession->SetSessionId(sessionId);
	readSession->SetFrom(readSessionReq.session_name.from.c_str());
	readSession->SetTo(readSessionReq.session_name.to.c_str());
	readSession->SetReadSeqId(readSessionReq.read_seq_id);
	readSession->SetType(readSessionReq.session_name.type);
	TNDataControlServer::GetInstance()->InsertDatas(std::dynamic_pointer_cast<TableBase>(readSession), DBTYPE_MSG);
}
void TNIMReadSessionManager::DeleteReadSessionReq(QString sessionId)
{
	//sessionid 无效
	TNDataControlServer::GetInstance()->ClearByTableName("ReadSession", DBTYPE_MSG);
	//TNDataControlServer::GetInstance()->DeleteFromTableNameByField("ReadSession", "sessionId", sessionId, DBTYPE_MSG);
}
void TNIMReadSessionManager::GetAllReadSessionReq(TableBaseVec& readSessoins)
{
	TNDataControlServer::GetInstance()->GetAllFieldsByTableName("ReadSession", readSessoins, DBTYPE_MSG);
}

void TNIMReadSessionManager::GetSyncSessionStatusReq(st_ReadSessionReqPtr stSessionReq, Toon::SyncSessionStatusReq& readReq)
{
	if (stSessionReq != NULL)
	{
		readReq.req_id = stSessionReq->GetReqId().toUtf8().data();
		readReq.read_seq_id = stSessionReq->GetReadSeqId();
		Toon::SessionName sessionItem;
		sessionItem.from = stSessionReq->GetFrom().toUtf8().data();
		sessionItem.to = stSessionReq->GetTo().toUtf8().data();
		sessionItem.type = stSessionReq->GetType();
		readReq.session_name = sessionItem;
	}
}
