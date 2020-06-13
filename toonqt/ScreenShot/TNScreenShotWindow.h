/*******************************************************************
*  Copyright(c) 2000-2018 syswin
*  All rights reserved.
*
*  文件名称: TNScreenShotWindow.h
*  说明:    截屏窗体
******************************************************************/
#ifndef TNSCREENSHOTWINDOW_H
#define TNSCREENSHOTWINDOW_H

#include <QDialog>
#include <QPen>

#include "TNNameSpace.h"

class QRubberBand;
class QLabel;

class TNDrawingBoard;
class TNResizerDecorator;
class TNMagnifierWidget;
class TNScreenshotEditToolBarManager;
class TNScreenshotEditOptionData;
class TNScreenShotWindow : public QDialog
{
    Q_OBJECT

public:
    TNScreenShotWindow(QWidget *parent = 0);
    ~TNScreenShotWindow();

    TN::ScreenShotExitFlag exitFlag() const;
public Q_SLOTS:
    virtual void accept();
protected slots:
    void onUndo();
    void onOk();
    void onCancel();
    void onSave();
    void onFirstDrawn();
    void onApplicationStateChanged(Qt::ApplicationState state);

protected:
    virtual void showEvent(QShowEvent *event);
    virtual void paintEvent(QPaintEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual bool eventFilter(QObject *watched, QEvent *event);
private:
    void initWindowRectList();                              //初始化桌面上窗口区域列表
    void drawAdsorptionWindow(QPoint curPos);               //绘制吸附窗体
    void drawRubberBandOrDrawingBoard(QRect rect);          //绘制橡皮筋或者画板
    void drawBackground(QRect transparent);                 //绘制背景区，参数是透明区域的rect
    void getResultPixmap();                              //取得最终截图

    inline void creatRubberBand();                          //创建橡皮筋控件
    inline void creatDrawingBoard();                        //创建画板
    inline void createDimensionalLabel();                   //创建尺寸标签
    inline void showMagnifier();                            //创建放大镜
    inline void relocateDimensionalLabel(QPoint refPoint);  //定位尺寸显示标签的位置,参照点是画板或者橡皮筋的左上角
    inline void setDimensionalPrompt(int width, int height);//设置尺寸提示

    inline void showToolBar();                              //显示工具栏
    inline void hideToolBar();                              //隐藏工具栏

private:
    enum EditMode
    {
        emWindowsAdsorption = 0,         //窗体吸附模式
        emMousePressAtAdsorption,        //吸附窗体时按下鼠标模式
        emRubberBandResize,              //橡皮筋大小调整模式
        emDrawingBoardMove,              //画板移动模式
        emDrawingBoardResize,            //画板调整尺寸模式
        emDrawingEdit                    //绘图编辑模式
    };                                   
    QRubberBand *m_pRubberBand;          //橡皮筋控件
    TNDrawingBoard *m_pDrawingBorad;     //画板控件
    TNMagnifierWidget *m_pMagnifierWidget;//放大镜控件
    QLabel *m_pDimensionalLabel;         //尺寸显示label

    EditMode m_CurrentMode;              //当前编辑模式
    QList<QRect> m_windowRectList;       //屏幕上所有窗口的rect,用来实现鼠标自动吸附效果
    QPixmap m_pmFullScreenShot;          //整个屏幕的截屏pixmap
    QPixmap m_pmShowBuffer;              //屏幕显示用pixmap
    QPixmap m_pmResult;                  //输出结果pixmap
    QPen    m_WindowBorderPen;           //用来绘制选中窗口的边界的画笔
    QPen    m_RubberBandPen;             //用来绘制橡皮筋控件边界的画笔
    QRect   m_AdsorptionWindowRect;      //当前吸附窗体的区域

    QPoint  m_posAtMousePress;           //光标按下时的位置

    TNScreenshotEditToolBarManager *m_EditToolBarManager;
    TNScreenshotEditOptionData *m_pEditOptionData;
    bool m_isCloseWhenInactive;//程序市区焦点时是否关闭,在弹出另存为对话框时设为false，其他设为ture
    TN::ScreenShotExitFlag m_exitFlag;
};

#endif // TNSCREENSHOTWINDOW_H
