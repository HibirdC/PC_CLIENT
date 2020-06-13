#include <QApplication>
#include <QDesktopWidget>
#include <QMoveEvent>
#include <QPainter>
#include <QScreen>
#include <QMenu>
#include <QMessageBox>

#include "TNUtil.h"
#include "TNResizerDecorator.h"
#include "TNDrawingBoard.h"
#include "TNArrowDrawTool.h"
#include "TNScreenShotTextEdit.h"

TNDrawingBoard::TNDrawingBoard(QWidget *parent)
    : QWidget(parent)
    , m_pDrawingBoardResizer(nullptr)
    , m_pMgr(nullptr)
    , m_pData(nullptr)
    , m_bIsMousePress(false)
{
    setMinimumSize(QSize(10, 10));
    m_pDrawingBoardResizer = new TNResizerDecorator(this);
    installEventFilter(this);
    m_pDrawingBoardResizer->setOuterBoundary(parent->rect());
    m_pDrawingBoardResizer->setDefaultCursor(Qt::SizeAllCursor);
}

TNDrawingBoard::~TNDrawingBoard()
{
    delete m_pDrawingBoardResizer;
    m_pData->currentTextEdit = nullptr;
}

void TNDrawingBoard::enterEvent(QEvent *event)
{
    if (nullptr != m_pData)
    {
        if (m_pData->currentCommand != ctNull)
        {
            m_pDrawingBoardResizer->setDefaultCursor(Qt::CrossCursor);
            m_pDrawingBoardResizer->setMovable(false);
        }
        else
        {
            m_pDrawingBoardResizer->setDefaultCursor(Qt::SizeAllCursor);
            m_pDrawingBoardResizer->setMovable(true);
        }
    }
    QWidget::enterEvent(event);
}

bool TNDrawingBoard::eventFilter(QObject *watched, QEvent *event)
{
    do 
    {
        if (watched != this)
        {
            TNScreenShotTextEdit *pTextEdit = dynamic_cast<TNScreenShotTextEdit *>(watched);
            if (nullptr != pTextEdit)
            {
                if (event->type() == QEvent::FocusIn)
                {
                    m_pData->currentTextEdit = pTextEdit;
                }
            }

            break;
        }
        if (nullptr == m_pData)
        {
            break;
        }

        if (m_pData->currentCommand == ctNull)
        {
            break;
        }

        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *pMouseEvent = dynamic_cast<QMouseEvent *>(event);
			if (pMouseEvent)
				onMouseButtonPress(pMouseEvent->globalPos());
        }

        if (event->type() == QEvent::MouseButtonRelease)
        {
            if (m_bIsMousePress)
            {
                m_bIsMousePress = false;
                if (cursor().shape() == Qt::CrossCursor)
                {
                    QMouseEvent *pMouseEvent = dynamic_cast<QMouseEvent *>(event);
					if (pMouseEvent)
						onMouseButtonRelease(pMouseEvent->globalPos());
                }
            }
        }

        if (event->type() == QEvent::MouseMove)
        {
            if (m_bIsMousePress && cursor().shape() == Qt::CrossCursor)
            {
                QMouseEvent *pMouseEvent = dynamic_cast<QMouseEvent *>(event);
				if (pMouseEvent)
					doDraw(pMouseEvent->globalPos());
            }
        }

        break;
    } while (false);
    return QWidget::eventFilter(watched, event);
}

void TNDrawingBoard::onMouseButtonPress(QPoint globalPos)
{
    m_bIsMousePress = true;
    m_pointAtPress = globalPos;
    m_oldPos = m_pointAtPress;
}

void TNDrawingBoard::onMouseButtonRelease(QPoint globalPos)
{
    if (m_pData->currentCommand == ctNull)
    {
        return;
    }
    if (m_pData->currentCommand == ctText)
    {
        changeTextEditVisible(globalPos);
    }
    else
    {
        //其他绘制命令要保存历史记录
        QPoint pt1 = m_pointAtPress;
        QPoint pt2 = globalPos;
        QRect rect = QRect(pt1.x(), pt1.y(), pt2.x() - pt1.x(), pt2.y() - pt1.y());
        rect = rect.intersected(this->geometry());
        m_minGeometryRect = m_minGeometryRect.united(rect);
        m_pDrawingBoardResizer->setInnerBoundary(m_minGeometryRect);
        recordHistory();
    }
}

void TNDrawingBoard::onCurrentTextColorChanged()
{
    if (nullptr != m_pData->currentTextEdit)
    {
        m_pData->currentTextEdit->setFontColor(m_pData->getColor(ctText));
    }
}

void TNDrawingBoard::mousePressEvent(QMouseEvent *event)
{
#ifdef Q_OS_WIN
    if (event->button() == Qt::RightButton)
    {
        QAction *action = m_pMgr->getContextMenu()->exec(event->globalPos());
        if (action)
            m_bIsMousePress = false;
    }
#endif

#ifdef Q_OS_MAC
    QWidget::mousePressEvent(event);
#endif
}

void TNDrawingBoard::changeTextEditVisible(QPoint globalPos)
{
    if (nullptr == m_pData->currentTextEdit)
    {
        //如果当前编辑框为空，则创建并显示
        m_pData->currentTextEdit = new TNScreenShotTextEdit(m_pData->textAttribute.nFontSize, m_pData->getColor(ctText), this);
        m_pData->currentTextEdit->setTextColor(m_pData->getColor(ctText));
        //connect(m_pData->currentTextEdit, SIGNAL(editFinished()), this, SLOT(onTextEditFinished()));
        m_pData->currentTextEdit->move(mapFromGlobal(globalPos));
        m_pData->currentTextEdit->show();
        m_pData->currentTextEdit->installEventFilter(this);
        m_pData->currentTextEdit->viewport()->setFocus();
    }
    else
    {
        //如果当前编辑框非空，则如果文本为空则释放
        m_pData->currentTextEdit->clearFocus();
        if (m_pData->currentTextEdit->toPlainText().simplified().isEmpty())
        {
            delete m_pData->currentTextEdit;
        }
        else
        {
            QRect rect(mapToGlobal(m_pData->currentTextEdit->pos()), m_pData->currentTextEdit->size());
            m_minGeometryRect = m_minGeometryRect.united(rect);
            m_pDrawingBoardResizer->setInnerBoundary(m_minGeometryRect);
            recordHistory();
        }
        m_pData->currentTextEdit = nullptr;
    }
}

void TNDrawingBoard::doDraw(const QPoint &pos)
{
    createShowBufferPixmap();
    QRect rect = QRect(m_pointAtPress, pos).intersected(this->geometry());
    switch (m_pData->currentCommand)
    {
    case ctRectangle:
        drawRect(rect);
        break;
    case ctEllipse:
        drawEllipse(rect);
        break;
    case ctArrow:
        if (rect.topLeft() == m_pointAtPress)
        {
            drawArrow(rect.topLeft(), rect.bottomRight());
        }
        else if (rect.topRight() == m_pointAtPress)
        {
            drawArrow(rect.topRight(), rect.bottomLeft());
        }
        else if (rect.bottomLeft() == m_pointAtPress)
        {
            drawArrow(rect.bottomLeft(), rect.topRight());
        }
        else
        {
            drawArrow(rect.bottomRight(), rect.topLeft());
        }
        break;
    case ctText:
        break;
    case ctBrush:
        drawBrush(pos);
        break;
    default:
        break;
    }
}

void TNDrawingBoard::drawBrush(QPoint pos)
{
    if (m_pmInDrawingShowBuffer.isNull())
    {
        m_pmInDrawingShowBuffer = m_pmCompletedShowBuffer;
    }
    QPainter painter(&m_pmInDrawingShowBuffer);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPen pen;
    switch (m_pData->brushAttribute.lineWidthSize)
    {
    case lwsMiddle:
        pen.setWidth(3);
        break;
        break;
    case lwsLarge:
        pen.setWidth(6);
        break;
    default:
        pen.setWidth(1);
        break;
    }
    pen.setColor(m_pData->getColor(ctBrush));
    painter.setPen(pen);
    painter.drawLine(m_oldPos, pos);
    m_oldPos = pos;
}

void TNDrawingBoard::drawRect(const QRect &rect)
{
    m_pmInDrawingShowBuffer = m_pmCompletedShowBuffer;
    QPainter painter(&m_pmInDrawingShowBuffer);
    QPen pen;
    switch (m_pData->rectangleAttribute.lineWidthSize)
    {
    case lwsMiddle:
        pen.setWidth(3);
        break;
        break;
    case lwsLarge:
        pen.setWidth(6);
        break;
    default:
        pen.setWidth(1);
        break;
    }
    pen.setColor(m_pData->getColor(ctRectangle));
    painter.setPen(pen);
    painter.drawRect(rect);
    this->update();
}

void TNDrawingBoard::drawEllipse(const QRect &rect)
{
    m_pmInDrawingShowBuffer = m_pmCompletedShowBuffer;
    QPainter painter(&m_pmInDrawingShowBuffer);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPen pen;
    switch (m_pData->ellipseAttribute.lineWidthSize)
    {
    case lwsMiddle:
        pen.setWidth(3);
        break;
        break;
    case lwsLarge:
        pen.setWidth(6);
        break;
    default:
        pen.setWidth(1);
        break;
    }
    pen.setColor(m_pData->getColor(ctEllipse));
    painter.setPen(pen);
    painter.drawEllipse(rect);
    this->update();
}

void TNDrawingBoard::drawArrow(QPoint start, QPoint end)
{
    m_pmInDrawingShowBuffer = m_pmCompletedShowBuffer;
    QPainter painter(&m_pmInDrawingShowBuffer);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPainterPath path;
    TNArrowDrawTool().getArrowPath(m_pData->arrowAttribute.lineWidthSize, path, start, end);
    QColor color = m_pData->getColor(ctArrow);
    painter.fillPath(path, color);
    QPen pen;
    pen.setColor(color);
    painter.setPen(pen);
    painter.drawPath(path);
    this->update();
}

void TNDrawingBoard::createShowBufferPixmap()
{
    if (m_pmCompletedShowBuffer.isNull())
    {
        m_pmCompletedShowBuffer = QPixmap(TNUtil::getScreenWindowRect().size());
        m_pmCompletedShowBuffer.fill(QColor(0, 0, 0, 0));
        m_PixmapHistoryList.push_back(m_pmCompletedShowBuffer);
    }
}

void TNDrawingBoard::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect screenRect = TNUtil::getScreenWindowRect();
    QRect rect(this->mapFromGlobal(screenRect.topLeft()), this->mapFromGlobal(screenRect.bottomRight()));
    painter.drawPixmap(rect, m_pmInDrawingShowBuffer);
}

void TNDrawingBoard::recordHistory()
{
    if (m_pData->currentCommand == ctText)
    {
        m_TextHistoryList.push(m_pData->currentTextEdit);
    }
    else
    {
        m_pmCompletedShowBuffer = m_pmInDrawingShowBuffer;
        m_PixmapHistoryList.push_back(m_pmCompletedShowBuffer);
    }
    m_CommandHistoryList.push(m_pData->currentCommand);
    if (m_CommandHistoryList.size() == 1)
    {
        emit hasDrawn();
    }
    m_minGeometryRectHistoryList.push(m_minGeometryRect);
}

bool TNDrawingBoard::undo()
{
    if (nullptr != m_pData->currentTextEdit)
    {
        delete m_pData->currentTextEdit;
        m_pData->currentTextEdit = nullptr;
        if (m_CommandHistoryList.isEmpty())
        {
            m_pData->currentCommand = ctNull;
        }
        return false;
    }

    if (m_CommandHistoryList.isEmpty())
    {
        return true;
    }
    if (m_CommandHistoryList.top() == ctText)
    {
        TNScreenShotTextEdit *pEdit = m_TextHistoryList.pop();
        delete pEdit;
    }
    else
    {
        m_PixmapHistoryList.pop();
        m_pmInDrawingShowBuffer = m_PixmapHistoryList.top();
        m_pmCompletedShowBuffer = m_pmInDrawingShowBuffer;
        update();
    }
    m_CommandHistoryList.pop();
    m_minGeometryRectHistoryList.pop();
    if (m_CommandHistoryList.isEmpty())
    {
        m_pData->currentCommand = ctNull;
    }
    if (m_minGeometryRectHistoryList.isEmpty())
    {
        m_minGeometryRect = QRect();
    }
    else
    {
        m_minGeometryRect = m_minGeometryRectHistoryList.top();
    }
    m_pDrawingBoardResizer->setInnerBoundary(m_minGeometryRect);
    return false;
}

void TNDrawingBoard::onDrawActionChanged(CommandType type)
{
    if (type != ctText)
    {
        if (m_pData->currentTextEdit != nullptr)
        {
            m_pData->currentTextEdit->clearFocus();
            if (m_pData->currentTextEdit->toPlainText().isEmpty())
            {
                delete m_pData->currentTextEdit;
            }
            else
            {
                QRect rect(mapToGlobal(m_pData->currentTextEdit->pos()), m_pData->currentTextEdit->size());
                m_minGeometryRect = m_minGeometryRect.united(rect);
                m_pDrawingBoardResizer->setInnerBoundary(m_minGeometryRect);
                recordHistory();
            }
            m_pData->currentTextEdit = nullptr;
        }
    }
}

const QPixmap &TNDrawingBoard::getComplatedPixmap()
{
    if (nullptr != m_pData->currentTextEdit)
    {
        //如果当前处于编辑文字状态，则需要去掉编辑框的border
        changeTextEditVisible(QCursor::pos());
        repaint();
    }

    createShowBufferPixmap();
    QPainter painter(&m_pmCompletedShowBuffer);
    for (int i = 0; i < m_TextHistoryList.size(); i++)
    {
        TNScreenShotTextEdit *pEdit = m_TextHistoryList[i];
        QRect globalRect(mapToGlobal(pEdit->pos()), QSize(pEdit->width(), pEdit->height()));
        QPixmap textPixmap = pEdit->grab();
        painter.drawPixmap(globalRect, textPixmap);
    }

    return m_pmCompletedShowBuffer;
}

void TNDrawingBoard::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit doubleClick();
}

void TNDrawingBoard::contextMenuEvent(QContextMenuEvent *event)
{
    //QMenu *menu = new QMenu();
    //menu->addAction();
    //menu->addSeparator();
}
