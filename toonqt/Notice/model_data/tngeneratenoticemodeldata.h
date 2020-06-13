#ifndef TNGENERATENOTICEMODELDATA_H
#define TNGENERATENOTICEMODELDATA_H

#include <QObject>

#include "NoticeEnum.h"
#include "TNIMCoreClient.h"

class TNModelUserMessage;
class TNMessageListAdapter;

class TNGenerateNoticeModelData : public QObject
{
	Q_OBJECT

public:
	TNGenerateNoticeModelData(QObject *parent = 0);
	~TNGenerateNoticeModelData();

    TNModelUserMessage* generateSendMsg(MESSAGE_TYPE type, QString content,
        bool bSended, TNMessageListAdapter* curSession,int atType,QList<QString> atFeeds);
	TNModelUserMessage* generateRecvMsg(const TNMsgData& msgData, MESSAGE_TYPE type,
		const QString& myFeedId, bool bDownloaded);
    TNModelUserMessage* generateRevokeMsg(MESSAGE_TYPE type, QString content,TNMessageListAdapter* curSession);
    TNModelUserMessage generateHistoryMsgFromDataBase(const toonim::CTNMessage& messageDataBase);
Q_SIGNALS:
    void maxFileSize(QString content);
};

#endif // TNGENERATENOTICEMODELDATA_H
