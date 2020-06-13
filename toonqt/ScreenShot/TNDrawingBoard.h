/*******************************************************************
*  Copyright(c) 2000-2018 syswin
*  All rights reserved.
*
*  文件名称: TNDrawingBoard.h
*  说明:    画板控件
******************************************************************/

#ifndef TNDRAWINGBOARD_H
#define TNDRAWINGBOARD_H

#include <QWidget>
#include <QPixmap>
#include <QList>
#include <QStack>
#include "TNScreenshotEditOptionData.h"
#include "TNScreenshotEditToolBarManager.h"

class TNScreenShotTextEdit;
class TNResizerDecorator;

class TNDrawingBoard : public QWidget
{
    Q_OBJECT

public:
    TNDrawingBoard(QWidget *parent);
    ~TNDrawingBoard();

    void setEditToolBarManager(TNScreenshotEditToolBarManager *pMgr)
    {
        m_pMgr = pMgr;
    }
    void setOptionData(TNScreenshotEditOptionData *pData)
    {
        m_pData = pData;
    }
    //撤销, 返回是否已经撤销到头
    bool undo();

    const QPixmap &getComplatedPixmap();

public slots:
    void onCurrentTextColorChanged();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);
    void enterEvent(QEvent *event);
    void paintEvent(QPaintEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
signals:
    void hasDrawn();//当画板上第一次绘制时，释放此信号
    void doubleClick();
private slots:
    void onDrawActionChanged(CommandType type);
private:
    inline void createShowBufferPixmap();
    void doDraw(const QPoint &globalPos);
    void drawRect(const QRect &rect);
    void drawEllipse(const QRect &rect);
    void drawArrow(QPoint start, QPoint end);
    void drawBrush(QPoint globalPos);
    void onMouseButtonPress(QPoint globalPos);
    void onMouseButtonRelease(QPoint globalPos);
    void changeTextEditVisible(QPoint globalPos);
    void recordHistory();
private:
    TNResizerDecorator *m_pDrawingBoardResizer;
    TNScreenshotEditToolBarManager *m_pMgr;
    TNScreenshotEditOptionData *m_pData;
    bool m_bIsMousePress;
    QPoint m_pointAtPress;
    
    QPixmap m_pmCompletedShowBuffer;   //已经释放鼠标，完成的绘制
    QPixmap m_pmInDrawingShowBuffer;   //鼠标拖动过程中，未完成的绘制
    QPoint m_oldPos;                   //用于画刷使用
    QRect m_minGeometryRect;           //用于在绘制之后再重新调整窗体大小时，限制窗体最小尺寸

    QStack<CommandType> m_CommandHistoryList;//命令历史记录
    QStack<QPixmap> m_PixmapHistoryList;
    QStack<TNScreenShotTextEdit *> m_TextHistoryList;
    QStack<QRect> m_minGeometryRectHistoryList;
};

#endif // TNDRAWINGBOARD_H
