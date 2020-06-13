#ifndef TNNOTICEMESSAGEOPERATE_H
#define TNNOTICEMESSAGEOPERATE_H
#include <QObject>
class TNModelUserMessage;
class TNNoticeMessageOperate : public QObject
{
	Q_OBJECT

private:
    TNNoticeMessageOperate();
public:
    static TNNoticeMessageOperate* GetInstance();
    ~TNNoticeMessageOperate();
	void ProcessMsgRevokeAction(TNModelUserMessage* userMessage);
    void ProcessMsgForwordAction(TNModelUserMessage* userMessage, QMap<QString, QString>& feedList);
};
#endif
