#ifndef TNIMREADSESSIONMANAGER_H
#define TNIMREADSESSIONMANAGER_H

#include <QObject>
#include "TNDataControlServer.h"
//namespace Toon
//{
//	class SyncSessionStatusReq;
//}
class TNIMReadSessionManager : public QObject
{
	Q_OBJECT

public:
	TNIMReadSessionManager(QObject *parent);
	~TNIMReadSessionManager();
	//void SaveReadSessionReq(const QString& sessionId, const Toon::SyncSessionStatusReq& readSessionReq);
	void DeleteReadSessionReq(QString reqId);
	void GetAllReadSessionReq(TableBaseVec& readSessoins);
	//void GetSyncSessionStatusReq(st_ReadSessionReqPtr stSessionReq, Toon::SyncSessionStatusReq& readReq);
private:
	
};

#endif // TNIMREADSESSIONMANAGER_H
