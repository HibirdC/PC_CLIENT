#include <QMouseEvent>
#include <QDebug>
#include "TNScreenShotTextEdit.h"

TNScreenShotTextEdit::TNScreenShotTextEdit(int nFontPointSize, const QColor &fontColor, QWidget *parent)
    : QTextEdit(parent)
    , m_bIsMousePress(false)
    , m_nFontPointSize(nFontPointSize)
    , m_FontColor(fontColor)
{
    this->setObjectName("shotEditer");
    setLineWrapMode(QTextEdit::NoWrap);
    setContextMenuPolicy(Qt::NoContextMenu);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFontSize(nFontPointSize);
    setFontColor(fontColor);
    int nDefaultWidth = document()->size().width() + m_nFontPointSize * 1.5;
    int nDefaultHeight = document()->size().height() + m_nFontPointSize * 1.5;
    setFixedSize(QSize(nDefaultWidth, nDefaultHeight));
    //connect(document(), SIGNAL(contentsChanged()), this, SLOT(adjustSize()));
    connect(this, SIGNAL(textChanged()), this, SLOT(adjustSize()));
    viewport()->setMouseTracking(true);
}

TNScreenShotTextEdit::~TNScreenShotTextEdit()
{
}

void TNScreenShotTextEdit::adjustSize()
{
    int nWidth = document()->size().width() + m_nFontPointSize * 1.5;
    int nHeight = document()->size().height() + m_nFontPointSize * 1.5;
    setFixedSize(nWidth, nHeight);

    if (this->toPlainText().simplified().isEmpty())
    {
        qInfo()<<"[ScreenShot][TNScreenShotTextEdit] toPlainText is empty. m_nFontPointSize="<<m_nFontPointSize<<" m_FontColor="<<m_FontColor;
        setFontSize(m_nFontPointSize);
        setFontColor(m_FontColor);
    }
}

void TNScreenShotTextEdit::insertFromMimeData(const QMimeData *source)
{
    QTextEdit::insertFromMimeData(source);
    setFontSize(m_nFontPointSize);
    setFontColor(m_FontColor);
}

void TNScreenShotTextEdit::mousePressEvent(QMouseEvent *event)
{
    m_bIsMousePress = true;
    m_relativeCursorPosAtPress = event->pos();
    viewport()->setCursor(Qt::SizeAllCursor);
    QTextEdit::mousePressEvent(event);
}

void TNScreenShotTextEdit::mouseReleaseEvent(QMouseEvent *event)
{
    m_bIsMousePress = false;
    viewport()->setCursor(Qt::IBeamCursor);
    QTextEdit::mouseReleaseEvent(event);
}

void TNScreenShotTextEdit::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bIsMousePress)
    {
        QPoint posInParent = parentWidget()->mapFromGlobal(event->globalPos());
        move(posInParent - m_relativeCursorPosAtPress);
    }
    else
    {
        int x = event->pos().x();
        int y = event->pos().y();
        int w = width() - 5;
        int h = height() - 5;

        if (x < 5 || x > width() - 5 || y < 5 || y > height() - 5)
        {
            viewport()->setCursor(Qt::SizeAllCursor);
        }
        else
        {
            viewport()->setCursor(Qt::IBeamCursor);
        }
    }
    QTextEdit::mouseMoveEvent(event);
}

void TNScreenShotTextEdit::setFontSize(int pointSize)
{
    m_nFontPointSize = pointSize;
    qInfo()<<"[ScreenShot][TNScreenShotTextEdit] setFontSize="<<pointSize;
    QTextCharFormat fmt;
    fmt.setFontPointSize(pointSize);
    QTextCursor cursor = textCursor();
    cursor.select(QTextCursor::Document);
    cursor.mergeCharFormat(fmt);
    mergeCurrentCharFormat(fmt);
    this->update();
}

void TNScreenShotTextEdit::setFontColor(QColor color)
{
    m_FontColor = color;
    qInfo()<<"[ScreenShot][TNScreenShotTextEdit] setFontColor="<<color;
    QTextCharFormat fmt;
    fmt.setForeground(color);
    QTextCursor cursor = textCursor();
    cursor.select(QTextCursor::Document);
    cursor.mergeCharFormat(fmt);
    mergeCurrentCharFormat(fmt);
    this->update();
}
