#include <QWidget>
#include <QEvent>
#include <QMouseEvent>
#include "TNResizerDecorator.h"
#include <QDebug>

#define SHADOW_WIDTH 20
#define RESIZEBORDERWIDTH 5 //调整窗体大小时，边界宽度

TNResizerDecorator::TNResizerDecorator(QWidget *parent)
    : QObject(parent)
    , m_pParentWidget(parent)
    , m_defaultShape(Qt::ArrowCursor)
    , m_isMoveable(true)
    , m_isResizalbe(true)
{
    init();
    m_pParentWidget->setMouseTracking(true);
    m_pParentWidget->installEventFilter(this);
}

TNResizerDecorator::~TNResizerDecorator()
{

}

void TNResizerDecorator::init()
{
    m_rectAtPressMouse = QRect();
    m_TopLeftAtPress = QPoint();
    m_curPosAtPressMouse = QPoint();
    m_bIsMousePress = false;
    m_CurrentResizeRegion = Default;
}

TNResizerDecorator::ResizeRegion TNResizerDecorator::getResizeRegion(QPoint clientPos)
{
    if (clientPos.y() <= RESIZEBORDERWIDTH)
    {
        if (clientPos.x() <= RESIZEBORDERWIDTH)
            return NorthWest;
        if (clientPos.x() >= m_pParentWidget->width() - RESIZEBORDERWIDTH)
            return NorthEast;
        return North;
    }

    else if (clientPos.y() >= m_pParentWidget->height() - RESIZEBORDERWIDTH)
    {
        if (clientPos.x() <= RESIZEBORDERWIDTH)
            return SouthWest;
        if (clientPos.x() >= m_pParentWidget->width() - RESIZEBORDERWIDTH)
            return SouthEast;
        return South;
    }
    else
    {
        if (clientPos.x() <= RESIZEBORDERWIDTH)
            return West;
        return East;
    }
}

bool TNResizerDecorator::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == m_pParentWidget)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *pMouseEvent = dynamic_cast<QMouseEvent *>(event);
			if (pMouseEvent)
				onMouseButtonPress(pMouseEvent);
        }
        if (event->type() == QEvent::MouseButtonRelease)
        {
            QMouseEvent *pMouseEvent = dynamic_cast<QMouseEvent *>(event);
			if (pMouseEvent)
				onMouseButtonRelease(pMouseEvent);
        }
        if (event->type() == QEvent::MouseMove)
        {
            QMouseEvent *pMouseEvent = dynamic_cast<QMouseEvent *>(event);
            //移动窗口
			if (pMouseEvent)
			{
				if (m_bIsMousePress)
					onMouseDrag(pMouseEvent);
				else
					onMouseMove(pMouseEvent);
			}
        }
    }
    return QObject::eventFilter(watched, event);
}


void TNResizerDecorator::setResizeCursor(ResizeRegion region)
{
    switch (region)
    {
    case North:
    case South:
        m_pParentWidget->setCursor(Qt::SizeVerCursor);
        break;
    case East:
    case West:
        m_pParentWidget->setCursor(Qt::SizeHorCursor);
        break;
    case NorthWest:
    case SouthEast:
        m_pParentWidget->setCursor(Qt::SizeFDiagCursor);
        break;
    default:
        m_pParentWidget->setCursor(Qt::SizeBDiagCursor);
        break;
    }
}

void TNResizerDecorator::handleResize(QPoint pos)
{
    int xdiff = pos.x() - m_curPosAtPressMouse.x();
    int ydiff = pos.y() - m_curPosAtPressMouse.y();
    if (m_rectInnerBoundary.width() != 0)
    {
        switch (m_CurrentResizeRegion)
        {
        case TNResizerDecorator::NorthEast:
        case TNResizerDecorator::East:
        case TNResizerDecorator::SouthEast:
            if (m_rectInnerBoundary.width() > 0)
            {
                xdiff = std::max<int>(m_rectInnerBoundary.right() - m_curPosAtPressMouse.x(), xdiff);
            }
            else
            {

                xdiff = std::max<int>(m_rectInnerBoundary.left() - m_curPosAtPressMouse.x(), xdiff);
            }
            break;
        case TNResizerDecorator::SouthWest:
        case TNResizerDecorator::West:
        case TNResizerDecorator::NorthWest:
            if (m_rectInnerBoundary.width() > 0)
            {
                xdiff = std::min<int>(m_rectInnerBoundary.left() - m_curPosAtPressMouse.x(), xdiff);
            }
            else
            {
                xdiff = std::min<int>(m_rectInnerBoundary.right() - m_curPosAtPressMouse.x(), xdiff);
            }
            break;
        default:
            break;
        }
    }
    if (m_rectInnerBoundary.height() != 0)
    {
        //内边界限制
        switch (m_CurrentResizeRegion)
        {
        case TNResizerDecorator::North:
        case TNResizerDecorator::NorthEast:
        case TNResizerDecorator::NorthWest:
            if (m_rectInnerBoundary.height() > 0)
            {
                ydiff = std::min<int>(m_rectInnerBoundary.top() - m_curPosAtPressMouse.y(), ydiff);
            }
            else
            {
                ydiff = std::min<int>(m_rectInnerBoundary.bottom() - m_curPosAtPressMouse.y(), ydiff);
            }
            break;
        case TNResizerDecorator::SouthEast:
        case TNResizerDecorator::South:
        case TNResizerDecorator::SouthWest:
            if (m_rectInnerBoundary.height() > 0)
            {
                ydiff = std::max<int>(m_rectInnerBoundary.bottom() - m_curPosAtPressMouse.y(), ydiff);
            }
            else
            {
                ydiff = std::max<int>(m_rectInnerBoundary.top() - m_curPosAtPressMouse.y(), ydiff);
            }
            break;
        default:
            break;
        }
    }

    double xNewPos = m_pParentWidget->x();
    double yNewPos = m_pParentWidget->y();
    switch (m_CurrentResizeRegion)
    {
    case East:
        m_pParentWidget->resize(m_rectAtPressMouse.width() + xdiff, m_pParentWidget->height());
        break;
    case West:
        m_pParentWidget->resize(m_rectAtPressMouse.width() - xdiff, m_pParentWidget->height());
        if (m_rectAtPressMouse.width() - xdiff > m_pParentWidget->minimumWidth())
        {
            m_pParentWidget->move(m_curPosAtPressMouse.x() + xdiff, m_pParentWidget->y());
        }
        break;
    case South:
        m_pParentWidget->resize(m_pParentWidget->width(), m_rectAtPressMouse.height() + ydiff);
        break;
    case North:
        m_pParentWidget->resize(m_pParentWidget->width(), m_rectAtPressMouse.height() - ydiff);
        if (m_rectAtPressMouse.height() - ydiff > m_pParentWidget->minimumHeight())
        {
            m_pParentWidget->move(m_pParentWidget->x(), m_curPosAtPressMouse.y() + ydiff);
        }
        break;
    case SouthEast:
        m_pParentWidget->resize(m_rectAtPressMouse.width() + xdiff, m_rectAtPressMouse.height() + ydiff);
        break;
    case NorthEast:
        m_pParentWidget->resize(m_rectAtPressMouse.width() + xdiff, m_rectAtPressMouse.height() - ydiff);
        if (m_rectAtPressMouse.height() - ydiff > m_pParentWidget->minimumHeight())
        {
            m_pParentWidget->move(m_pParentWidget->x(), m_curPosAtPressMouse.y() + ydiff);
        }
        break;
    case NorthWest:
        m_pParentWidget->resize(m_rectAtPressMouse.width() - xdiff, m_rectAtPressMouse.height() - ydiff);
        if (m_rectAtPressMouse.width() - xdiff > m_pParentWidget->minimumWidth())
        {
            xNewPos = m_curPosAtPressMouse.x() + xdiff;
        }
        if (m_rectAtPressMouse.height() - ydiff > m_pParentWidget->minimumHeight())
        {
            yNewPos = m_curPosAtPressMouse.y() + ydiff;
        }
        m_pParentWidget->move(xNewPos, yNewPos);
        break;
    case SouthWest:
        m_pParentWidget->resize(m_rectAtPressMouse.width() - xdiff, m_rectAtPressMouse.height() + ydiff);
        if (m_rectAtPressMouse.width() - xdiff > m_pParentWidget->minimumWidth())
        {
            m_pParentWidget->move(m_curPosAtPressMouse.x() + xdiff, m_pParentWidget->y());
        }
        break;
    default:
        break;
    }
}

void TNResizerDecorator::onMouseButtonPress(QMouseEvent *pMouseEvent)
{
    if (pMouseEvent->button() == Qt::LeftButton)
    {
        m_bIsMousePress = true;
        m_curPosAtPressMouse = pMouseEvent->globalPos();
        m_rectAtPressMouse = m_pParentWidget->rect();
    }
    m_TopLeftAtPress = m_pParentWidget->pos();
}

void TNResizerDecorator::onMouseButtonRelease(QMouseEvent *pMouseEvent)
{
    m_bIsMousePress = false;
    m_CurrentResizeRegion = Default;
    m_pParentWidget->setCursor(m_defaultShape);
}

void TNResizerDecorator::onMouseDrag(QMouseEvent *pMouseEvent)
{
    if (m_CurrentResizeRegion != Default)
    {
        if (!m_isResizalbe)
        {
            return;
        }
        handleResize(m_pParentWidget->mapToGlobal(pMouseEvent->pos()));
    }
    else
    {
        if (!m_isMoveable)
        {
            return;
        }
        if (m_pParentWidget->isMaximized())
        {
            //为减小鼠标拖动响应灵敏度，加如下判断
            int diffX = pMouseEvent->globalPos().x() - m_curPosAtPressMouse.x();
            int diffY = pMouseEvent->globalPos().y() - m_curPosAtPressMouse.y();
            if (abs(diffX) > 4 || abs(diffY) > 4)
            {
				/*
				当最大化时，拖动窗口，回到正常状态，并move屏幕中间
				*/
				m_bIsMousePress = false;
                m_pParentWidget->showNormal();
				//此处没必要移动
                //m_pParentWidget->move(pMouseEvent->globalPos() - QPoint(m_pParentWidget->width() / 2, 0));
                m_TopLeftAtPress = m_pParentWidget->pos();
            }
        }
        else
        {
            QPoint pos = pMouseEvent->globalPos() - m_curPosAtPressMouse + m_TopLeftAtPress;
            if (m_rectOuterBoundary.width() > 0)
            {
                double nMinX = m_rectOuterBoundary.left();
                double nMinY = m_rectOuterBoundary.top();
                double nMaxX = m_rectOuterBoundary.right() - m_pParentWidget->width();
                double nMaxY = m_rectOuterBoundary.bottom() - m_pParentWidget->height();
                double x = std::min<int>(pos.x(), nMaxX);
                x = std::max<int>(x, nMinX);
                double y = std::min<int>(pos.y(), nMaxY);
                y = std::max<int>(y, nMinY);
                m_pParentWidget->move(x, y);
            }
            else
            {
                m_pParentWidget->move(pos);
            }
        }
    }
}

void TNResizerDecorator::onMouseMove(QMouseEvent *pMouseEvent)
{
    if (!m_isResizalbe)
    {
        return;
    }
    //如果窗体可调整大小
    if (!m_pParentWidget->isMaximized())
    {
        QPoint cursorPos = pMouseEvent->pos();
        QRect windowRect = m_pParentWidget->rect();
        QRect clientRect(
            RESIZEBORDERWIDTH,
            RESIZEBORDERWIDTH,
            windowRect.width() - 2 * RESIZEBORDERWIDTH,
            windowRect.height() - 2 * RESIZEBORDERWIDTH
            );

        if (windowRect.contains(cursorPos) && !clientRect.contains(cursorPos))
        {
            m_CurrentResizeRegion = getResizeRegion(cursorPos);
            setResizeCursor(m_CurrentResizeRegion);
        }
        else
        {
            m_CurrentResizeRegion = Default;
            m_pParentWidget->setCursor(m_defaultShape);
        }
    }
}

void TNResizerDecorator::setDefaultCursor(Qt::CursorShape shape)
{
    m_defaultShape = shape;
}

void TNResizerDecorator::setOuterBoundary(const QRect &rect)
{
    m_rectOuterBoundary = rect;
}

void TNResizerDecorator::setInnerBoundary(const QRect &rect)
{
    m_rectInnerBoundary = rect;
}

void TNResizerDecorator::setMovable(bool bIsMoveable)
{
    m_isMoveable = bIsMoveable;
}

void TNResizerDecorator::setResizable(bool bIsResizable)
{
    m_isResizalbe = bIsResizable;
}
