#include <QLabel>
#include <QVBoxLayout>
#include <QApplication>
#include <QDesktopWidget>
#include <QEvent>
#include <QPainter>

#include "TNUtil.h"
#include "TNMagnifierWidget.h"

TNMagnifierWidget::TNMagnifierWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *pMainLaytou = new QVBoxLayout(this);
    pMainLaytou->setSpacing(0);
    pMainLaytou->setContentsMargins(2, 2, 2, 2);
    pMainLaytou->setAlignment(Qt::AlignHCenter);

    //放大图片显示区
    m_pPicViewer = new QWidget(this);
    m_pPicViewer->setContentsMargins(0, 0, 0, 0);
    m_pPicViewer->installEventFilter(this);
    m_pPicViewer->setFixedSize(120, 90);
    pMainLaytou->addWidget(m_pPicViewer);

    //尺寸、颜色值提示区
    m_pPromptLabel = new QLabel(this);
    m_pPromptLabel->setContentsMargins(6, 0, 0, 0);
    m_pPromptLabel->setFixedSize(120, 40);
    m_pPromptLabel->setObjectName("MagnifierPromptLabel");
    m_pPromptLabel->setStyleSheet("#MagnifierPromptLabel{background:rgba(0,0,0,0.5);color:#ffffff;}");
    m_pPromptLabel->setAutoFillBackground(false);
    pMainLaytou->addWidget(m_pPromptLabel);
    this->setFixedSize(124, 134);
}

TNMagnifierWidget::~TNMagnifierWidget()
{

}

void TNMagnifierWidget::paintEvent(QPaintEvent *event)
{
    //绘制边框
    QPainter painter(this);
    QRect borderRect = this->rect();
    borderRect.adjust(0, 0, -1, -1);
    painter.drawRect(borderRect);
    borderRect.adjust(1, 1, -1, -1);
    QPen pen;
    pen.setColor(QColor(255, 255, 255));
    painter.setPen(pen);
    painter.drawRect(borderRect);
}

bool TNMagnifierWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == m_pPicViewer)
    {
        if (event->type() == QEvent::Paint)
        {
            QPainter painter(m_pPicViewer);
            painter.drawPixmap(m_pPicViewer->rect(), m_pixmap);
            double height = m_pPicViewer->height();
            double width = m_pPicViewer->width();
            QPen pen;
            pen.setColor(QColor(0, 174, 255));
            pen.setWidth(3);
            painter.setPen(pen);
            painter.drawLine(QPoint(1, height / 2), QPoint(width - 1, height / 2));
            painter.drawLine(QPoint(width / 2, 1), QPoint(width / 2, height - 1));
        }
    }

    return QWidget::eventFilter(watched, event);
}

void TNMagnifierWidget::updatePixmap(QPixmap pixmap, int width, int height)
{
    m_pixmap = pixmap;
    QColor color = QColor(pixmap.toImage().pixel(QPoint(pixmap.width() / 2, pixmap.height() / 2)));
    QString strPrompt = QString("%1%2%3\nRGB:(%4,%5,%6)").arg(width).arg(tr(QStringLiteral("×").toUtf8().data()))
        .arg(height).arg(color.red()).arg(color.green()).arg(color.blue());
    m_pPromptLabel->setText(strPrompt);
}

void TNMagnifierWidget::relocate(QPoint refPoint)
{
    QRect screenRect = TNUtil::getScreenWindowRect();
    double width = this->width();
    double height = this->height();

    double xOffSet = 5;//放大镜距离光标的x方向5
    if (refPoint.x() + xOffSet + width > screenRect.width())
    {
        xOffSet = - (xOffSet + width);
    }

    double yOffSet = 28;//放大镜距离光标的y方向28
    if (refPoint.y() + yOffSet + height > screenRect.height())
    {
        yOffSet = - (yOffSet + height);
    }

    move(QPoint(refPoint.x() + xOffSet, refPoint.y() + yOffSet));
}
