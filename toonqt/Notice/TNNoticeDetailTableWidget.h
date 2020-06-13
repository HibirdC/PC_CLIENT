#ifndef TNNOTICEDETAILTABLEWIDGET_H
#define TNNOTICEDETAILTABLEWIDGET_H

#include <QStack>
#include <QTableWidget>

#include "TNIMCoreClient.h"
#include "details_notice/NoticeDetailsArea.h"

class NoticeDetailsArea;
class TNNoticeDetailTableWidget : public QTableWidget
{
    Q_OBJECT

public:
    explicit TNNoticeDetailTableWidget(QWidget *parent = Q_NULLPTR);

	void setNoticeDetailsArea(NoticeDetailsArea *noticeDetailsArea);

    void setSessionId(const QString &sessionId,TNMessageListAdapter* adapter);

	void appendNoticeCard(const st_NoticeInfo &noticeInfo);
	
	void setScrollToBottom(bool flag);
	
private slots:
	void VerticalScrollBaScrollToBottom(int, int);
	void VerticalScrollbarMoved(int);
    void onFocuseInTimeOut();
Q_SIGNALS:
    void readSessionUnreadNum(const QString& sessionId,int number);
	//通知Tray 未读列表状态
	void updateTrayUnRead(const QString & sessionId);
protected:
	virtual void updateGeometries();
	virtual void wheelEvent(QWheelEvent *event);
	virtual void resizeEvent(QResizeEvent *event);
    virtual void enterEvent(QEvent *event);
private:
    void noticeFocuseIn();
private:
	NoticeDetailsArea *m_noticeDetailsArea;
	QStack<st_NoticeInfo> m_noticeStack;
	bool m_isScrollToBottom; 

    QString m_sessionId;
    st_NoticeInfo m_currNotice;
    bool m_isLastPage;
    void readNoticeItemFromDB();

	void insertNoticeCard();
    //当前会话
    TNMessageListAdapter* _currentAdapter;
    //处理active状态,显示未读消息,并且3秒后消失
    //focuseIn timer定时器
    std::map<QTimer*,TNMessageListAdapter> _focuseInTimer;
};

#endif // TNNOTICEDETAILTABLEWIDGET_H
