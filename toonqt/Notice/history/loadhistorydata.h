#ifndef LOADHISTORYDATA_H
#define LOADHISTORYDATA_H
#include <QObject>

class TNMessageListAdapter;
class NoticeDetailsArea;
class TNModelUserMessage;
class TNMsgDetailModel;

namespace toonim{
struct CTNMessage;
}

#define	PAGE_NUM		10
class LoadHistoryData: public QObject
{
	Q_OBJECT

public:
    LoadHistoryData(TNMsgDetailModel* msgModel, NoticeDetailsArea* noticeDetail);
    ~LoadHistoryData();
public:
    void readCurrentSession(TNMessageListAdapter* currentAdapter,
                            unsigned int num = PAGE_NUM);
    int readCurrentSessionMore(unsigned int num = PAGE_NUM,
                                bool isJump = false);
    //添加一页数据,最后一个参数是否跳转,用于加载需要跳转到制定项的历史消息
    //返回实际的消息条数
    int AppandPageMsg(const QString& firstMsgId="",
                       unsigned int num = PAGE_NUM,
                       bool isJump = false);
	//当前显示是否最后一页
	bool CurrentIsLastPage();
    //获取未读的第一条消息的MsgId
    QString getFirstUnreadMsg(const QString& sessionId,int num);
    //向上跳转读取消息
    void readDataJump(int num);
    //读取firstMsgId到lastMsgId之间的数据,用于@跳转
    void readDataJump(const QString& firstUnreadMsgId);
Q_SIGNALS:
	void loadMsgFinsed(bool success, QString file, QString msgId);
    void AppandPageFinished(bool isLastPage,int num,bool isJump);
private:
	bool isFileDownloaded(const QString& msgId,QString& localPath);
	bool isAudioDownloaded(const QString& msgId, QString& localPath);
    //返回实际的显示的消息条数
    int produceHistoryData(const std::vector<toonim::CTNMessage>& messages);
    toonim::CTNMessage getSessionFirstUnreadMessage(const QString& msgId);
private:
	TNMsgDetailModel*		_msgModel;
	NoticeDetailsArea*		_noticeDetailArea;
	TNMessageListAdapter*	_currentAdapter;
	QString					_currentSessionId;
	bool					_bIsLastPageLocal;
    QList<TNModelUserMessage*> _list_msg;
    //从数据库读取当前会话的消息开始位置(消息id)
    QString 				_startMsgId;
};
#endif
