/*******************************************************************
*  Copyright(c) 2000-2018 syswin
*  All rights reserved.
*
*  文件名称: TNScreenshotEditToolBar.h
*  说明:    截屏编辑工具栏管理类
******************************************************************/
#ifndef TNSCREENSHOTEDITTOOLBAR_H
#define TNSCREENSHOTEDITTOOLBAR_H

#include <QMenu>
#include <QObject>
#include <QToolBar>
#include "TNScreenshotEditOptionData.h"
class QAction;
class QActionGroup;
class QComboBox;
class QToolBar;
class QPushButton;
class QSignalMapper;
class QToolButton;

class SSToolBar : public QToolBar
{
    Q_OBJECT

public:
    explicit SSToolBar(QWidget *parent = Q_NULLPTR) : QToolBar(parent)
    {

    }

protected:
    virtual void enterEvent(QEvent *event)
    {
        this->setCursor(Qt::ArrowCursor);
        QWidget::enterEvent(event);
    }
};


class TNScreenshotEditToolBarManager : public QObject
{
    Q_OBJECT

public:
    TNScreenshotEditToolBarManager(TNScreenshotEditOptionData *pData, QWidget *parent);
    ~TNScreenshotEditToolBarManager();

    void showToolBar();
    void hideToolBar();
    void relocateToolBar(const QRect &refRect, const QRect &screenRect);
    QMenu *getContextMenu();

private:
    void initToolBar();
    void changeLineWidth(LineWidthSize type);
    void setUncheckedOtherDrawAction(QAction *pCurrentAction);

private slots:
    void onRectangleAction();
    void onRectangleActionMenu();
    void onEllipseAction();
    void onEllipseActionMenu();
    void onArrowAction();
    void onArrowActionMenu();
    void onBrushAction();
    void onBrushActionMenu();
    void onTextAction();
    void onTextActionMenu();
    void onUndoAction();
    void onSaveAction();
    void onCancelAction();
    void onOKAction();
    void onLineWidth_SmallAction();
    void onLineWidth_MiddleAction();
    void onLineWidth_LargeAction();
    void onEditGroupTrigger();
    void onColorSelected(int nColorIndex);
    void onTextSizeChanged(const QString &text);
signals:
    void undo();
    void save();
    void ok();
    void cancel();
    void drawActionChanged(CommandType type);
    void textColorChange();
private:
    QMenu *m_contextMenu;
    SSToolBar *m_pCommandBar;               //命令工具栏

    QActionGroup *m_pDrawCommandGroup;     //绘制命令action组
    QAction *m_pRectangle, *m_pRectangleMenu;               //矩形
    QAction *m_pEllipse, *m_pEllipseMenu;                   //椭圆
    QAction *m_pArrow, *m_pArrowMenu;                       //箭头
    QAction *m_pBrush, *m_pBrushMenu;                       //画刷
    QAction *m_pText, *m_pTextMenu;                         //文本

    QActionGroup *m_pEditCommandGroup;     //编辑命令action组
    QAction *m_pUndo, *m_pUndoMenu;        //撤销
    QAction *m_pSave, *m_pSaveMenu;        //保存
    QAction *m_pCancel, *m_pCancelMenu;    //保存
    QAction *m_pOK, *m_pOKMenu;            //完成

    QToolBar *m_pOptionBar;                //选项工具栏
    QAction *m_pLineWidth_Small;           //线宽-细
    QAction *m_pLineWidth_Middle;          //线宽-中
    QAction *m_pLineWidth_Large;           //线宽-粗
    QActionGroup *m_pLineWidthGroup;       //线宽action组

    QActionGroup *m_pColorGroup;           //颜色数组
	QSignalMapper *m_pColorSignalMap;

    QAction *m_pTextSizeAction;            //文字大小选择控件
    QComboBox *m_pTextSizeComboBox;        //文字大社区合框

    TNScreenshotEditOptionData *m_pData;
    QWidget *m_pParent;
};

#endif // TNSCREENSHOTEDITTOOLBAR_H
