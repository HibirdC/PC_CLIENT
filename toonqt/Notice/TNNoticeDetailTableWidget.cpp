#include "TNNoticeDetailTableWidget.h"

#include "TNNewFriendCard.h"

#include <QHeaderView>
#include <QScrollBar>

static bool messageGreaterThan(const st_NoticeInfo &p1, const st_NoticeInfo &p2)
{
	return (p1.timestmp_s < p2.timestmp_s);
}

TNNoticeDetailTableWidget::TNNoticeDetailTableWidget(QWidget *parent) : QTableWidget(parent)
  ,m_noticeDetailsArea(NULL)
  ,_currentAdapter(NULL)
{
	m_isScrollToBottom = true;
    m_isLastPage = false;
	this->setColumnCount(1);
	this->setShowGrid(false);
	this->horizontalHeader()->setVisible(false);
	this->verticalHeader()->setVisible(false);
    this->setColumnWidth(0, 660);
	this->setSelectionBehavior(QAbstractItemView::SelectRows);
	this->setSelectionMode(QAbstractItemView::NoSelection);
	this->setEditTriggers(QAbstractItemView::NoEditTriggers);
	this->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setFocusPolicy(Qt::NoFocus);

	connect(verticalScrollBar(), SIGNAL(rangeChanged(int, int)), this, SLOT(VerticalScrollBaScrollToBottom(int, int)));
	connect(verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(VerticalScrollbarMoved(int)));
}

void TNNoticeDetailTableWidget::setNoticeDetailsArea(NoticeDetailsArea *noticeDetailsArea)
{
	m_noticeDetailsArea = noticeDetailsArea;
}

void TNNoticeDetailTableWidget::setSessionId(const QString &sessionId,TNMessageListAdapter* adapter)
{
    QTime time;
    time.start();
    qInfo()<<"[Notice][TNNoticeDetailTableWidget] setSessionId begin. sessionId="<<sessionId;
    Q_ASSERT(adapter);
    _currentAdapter = adapter;

    m_sessionId = sessionId;
    m_isLastPage = false;
	QList<st_NoticeInfo> m_noticeList;
    TNIMCoreClient::GetIMClient()->GetNoticeListFromSessionId(m_noticeList, m_sessionId);
	qSort(m_noticeList.begin(), m_noticeList.end(), messageGreaterThan);

	m_noticeStack.clear();
	for (int i = 0; i < m_noticeList.size(); ++i)
	{
		m_noticeStack.push(m_noticeList.at(i));
	}

	this->clearContents();
	this->setRowCount(0);
	for (int iRow = 0; iRow < this->rowCount(); ++iRow)
	{
		this->setRowHidden(iRow, false);
	}

	for (int i = 0; i < 3; ++i)
	{
		insertNoticeCard();
	}
	this->setScrollToBottom(true);
    qInfo()<<"[Notice][TNNoticeDetailTableWidget] setSessionId end. Time="<<time.elapsed();
}

void TNNoticeDetailTableWidget::readNoticeItemFromDB()
{
    if (m_isLastPage)
        return;

    qInfo()<<"[Notice][TNNoticeDetailTableWidget] readNoticeItemFromDB. m_currNotice.seqId="<<m_currNotice.seqId;
    QList<st_NoticeInfo> noticeList;
    TNIMCoreClient::GetIMClient()->GetNoticeListFromSessionId(noticeList, m_sessionId, m_currNotice.seqId);
    qSort(noticeList.begin(), noticeList.end(), messageGreaterThan);
    if (noticeList.isEmpty())
    {
        qInfo()<<"[Notice][TNNoticeDetailTableWidget] readNoticeItemFromDB arrived last page";
        m_isLastPage = true;
        return;
    }

    for (int i = 0; i < noticeList.size(); ++i)
    {
        m_noticeStack.push(noticeList.at(i));
    }
    qInfo()<<"[Notice][TNNoticeDetailTableWidget] readNoticeItemFromDB. m_noticeStack.size="<<m_noticeStack.size();
}

void TNNoticeDetailTableWidget::appendNoticeCard(const st_NoticeInfo &noticeInfo)
{
    if (m_noticeDetailsArea == nullptr)
        return;

    QTime time;
    time.start();
    qInfo()<<"[Notice][TNNoticeDetailTableWidget] appendNoticeCard begin...";
	for (int iRow = 0; iRow < this->rowCount(); ++iRow)
	{
		TNNewFriendCard *card = static_cast<TNNewFriendCard*>(this->cellWidget(iRow, 0));
		if (card->isSameNotice(noticeInfo))
		{
			// 可能有多个重的，所以需要多次循环排重隐藏，不能break;
			this->setRowHidden(iRow, true);
			//break; 
		}
	}

	int rowNum = this->rowCount();
	this->setRowCount(rowNum + 1);
	TNNewFriendCard *card = new TNNewFriendCard(m_noticeDetailsArea->_pluginParam, noticeInfo);

    this->setRowHeight(rowNum, card->height() + 10);
	this->setCellWidget(rowNum, 0, card);
	this->setScrollToBottom(true);

    qInfo()<<"[Notice][TNNoticeDetailTableWidget] appendNoticeCard end. Time="<<time.elapsed();
}

void TNNoticeDetailTableWidget::updateGeometries()
{
	QTableWidget::updateGeometries();
	this->verticalScrollBar()->setSingleStep(10);
}

void TNNoticeDetailTableWidget::wheelEvent(QWheelEvent *event)
{
	QTableWidget::wheelEvent(event);

	if (this->verticalScrollBar()->value() == 0)
	{
		insertNoticeCard();
	}
}

void TNNoticeDetailTableWidget::VerticalScrollBaScrollToBottom(int min, int max)
{
	if (m_isScrollToBottom)
		verticalScrollBar()->setValue(max);
}

void TNNoticeDetailTableWidget::VerticalScrollbarMoved(int value)
{
	if (value != verticalScrollBar()->maximum())
	{
		m_isScrollToBottom = false;
	}
	else
	{
		m_isScrollToBottom = true;
	}
}

void TNNoticeDetailTableWidget::setScrollToBottom(bool flag)
{
	m_isScrollToBottom = flag;
}

void TNNoticeDetailTableWidget::insertNoticeCard()
{
    QTime time;
    time.start();

    if (m_noticeStack.isEmpty())
        readNoticeItemFromDB();

    if (m_noticeStack.isEmpty())
        return;

    if (m_noticeDetailsArea == nullptr)
        return;

    qInfo()<<"[Notice][TNNoticeDetailTableWidget] insertNoticeCard begin...";
    m_currNotice = m_noticeStack.pop();
    TNNewFriendCard *card = new TNNewFriendCard(m_noticeDetailsArea->_pluginParam, m_currNotice);
	this->insertRow(0);
    this->setRowHeight(0, card->height() + 10);
	this->setCellWidget(0, 0, card);
    qInfo()<<"[Notice][TNNoticeDetailTableWidget] insertNoticeCard end. Time="<<time.elapsed();
}

void TNNoticeDetailTableWidget::resizeEvent(QResizeEvent *event)
{
	int w = this->width();
	this->setColumnWidth(0, w - 10); //  减10是给两边和滚动条预留空间

	QTableWidget::resizeEvent(event);
}

void TNNoticeDetailTableWidget::enterEvent(QEvent *event)
{
    noticeFocuseIn();
    return QTableWidget::enterEvent(event);
}

void TNNoticeDetailTableWidget::noticeFocuseIn()
{
    QTime time;
    time.start();
    qInfo()<<"[Notice][TNNoticeDetailTableWidget] noticeFocuseIn begin...";
    if(_currentAdapter != NULL){
        if(!_currentAdapter->getActive()){
            std::map<QTimer*,TNMessageListAdapter>::const_iterator itera
                    = _focuseInTimer.begin();
            for(;itera != _focuseInTimer.end();++itera){
                if(itera->second.getSessionId() == _currentAdapter->getSessionId()){
                    return;
                }
            }
            _currentAdapter->setActive(true);
            QTimer* tempTimer = new QTimer(this);
            connect(tempTimer,SIGNAL(timeout()),this,SLOT(onFocuseInTimeOut()));
            _focuseInTimer[tempTimer] = *_currentAdapter;
            tempTimer->start(3000);
        }
    }
    qInfo()<<"[Notice][TNNoticeDetailTableWidget] noticeFocuseIn end. Time="<<time.elapsed();
}

void TNNoticeDetailTableWidget::onFocuseInTimeOut()
{
    QTime time;
    time.start();
    qInfo()<<"[Notice][TNNoticeDetailTableWidget] onFocuseInTimeOut begin...";
    QTimer* tempTimer = qobject_cast<QTimer*>(sender());
    std::map<QTimer*,TNMessageListAdapter>::const_iterator itera =
            _focuseInTimer.find(tempTimer);
    if(itera != _focuseInTimer.end()){
        TNMessageListAdapter adapter = itera->second;
        if(adapter.getUnreadCount() > 0){
			//同时通知托盘停止闪烁
			emit updateTrayUnRead(adapter.getSessionId());
            emit readSessionUnreadNum(adapter.getSessionId(),0);
        }
        TNIMCoreClient::GetIMClient()->ReadSession(adapter.getSessionId());
        _focuseInTimer.erase(itera);
    }
    tempTimer->stop();
    delete tempTimer;
    qInfo()<<"[Notice][TNNoticeDetailTableWidget] onFocuseInTimeOut end. Time="<<time.elapsed();
}
