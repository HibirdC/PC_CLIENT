#ifndef TNCMESSAGE_H
#define TNCMESSAGE_H
#include "imcore_global.h"
#include <QString>
#include <QVariantMap>
#include <QList>
#include <tmtp_type.h>
#include <QSize>

#include "tnmessagebody.h"
#include "imcore_global.h"
namespace Toon {
class MsgReq;
}
#define ADDTION_LOCALPATH	"local"
#define ADDTION_URL			"url"
#define ADDTION_FILE_STATUS	"filestatus"
class TNCMessage
{
public:
    TNCMessage();
    virtual ~TNCMessage();
    Toon_TMTP_TYPE type;
    QString msgId;
	QString msgOpId;
    qlonglong timestamp;
    int catalogId;
    QString catalog;
   
    QString from;
	QString fromUserId;
    QString to;
	QString toUserId;
	QString localPath;
    QString pushInfo;
	QString toToonType;
    TNMessageContentType contentType;
    int atType;
    QList<QString>  atFeeds;
    QString senderName;
    qlonglong flags;
    int priority;
    qlonglong expireTime;
	qlonglong seqId;
	int		  bubbleFlag;			//是否冒泡，冒泡为加入未读，不冒泡为不加入未读，默认为0，
    QSize size;
    bool isMyself;
    TNIMMessageSendStatus sendStatus;
	int	 fileStatus;
    void setContent(const QString& content){
        _content = content;
    }

    void setBody(TNMessageBodyBase* body){
        _body = body;
    }

    QString getSesssionId();
    void SetSessionId(const QString& sessionId){ _sessionId = sessionId; }
	QString getTopic();
    QString getContent();

    QString packBody();
    TNMessageBodyBase* getBody();

    void parseBody(QString &jsonBody);

//    void parseBodyByDict(QVariantMap &dictBody);

    QString getAbstractText();

    bool isEmpty();

    QString pack();
	QString GetAtFeedlist();
	bool    IsContaionMeAtFeeds(QString userId);
    //- (void) generateRevokedMessage:(NSString*) operatorName;

    static QString genSessionId(Toon_TMTP_TYPE type,const QString& from,const QString& to);
	static QString genTopic(Toon_TMTP_TYPE type, QString& from, QString& to);
	static bool IsContainMeAtFeedsFromMsgData(QString userId, const TNMsgData& message);
    static TNCMessage* instanceFromMsgReq(int type,Toon::MsgReq* req);  
private:

private:
    QString _sessionId;
	QString _topic;
    TNMessageBodyBase *_body;
    QString _content;


};

#endif // TNCMESSAGE_H
