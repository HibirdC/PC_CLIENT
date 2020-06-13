#include <QApplication>
#include <QRubberBand>
#include <QDesktopWidget>
#include <QKeyEvent>
#include <QClipboard>
#include <QPainter>
#include <QLabel>
#include <QScreen>
#include <QStyleOption>
#include <QFileDialog>
#include <QDateTime>
#include <QDebug>

#include "TNUtil.h"
#include "TNScreenShotWindow.h"
#include "TNResizerDecorator.h"
#include "TNDrawingBoard.h"
#include "TNMagnifierWidget.h"
#include "TNScreenshotEditOptionData.h"
#include "TNScreenshotEditToolBarManager.h"
#include "TNPathUtil.h"
#ifdef Q_OS_MAC
#include "CoreGraphics/CoreGraphics.h"
#include "mac/mac_getwindowrects.h"
#endif
#ifdef Q_OS_WIN
//window下，取得所有可见顶层窗口的句柄
#include <Windows.h>
std::vector<HWND> g_AllWindow;
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    if (GetParent(hwnd) == NULL && IsWindowVisible(hwnd))
    {
        g_AllWindow.push_back(hwnd);
    }
    return TRUE;
}
void GetAllWindow()
{
    EnumWindows(&EnumWindowsProc, 0);
}
#endif //Q_OS_WIN 

TNScreenShotWindow::TNScreenShotWindow(QWidget *parent)
    : QDialog(parent)
    , m_pRubberBand(nullptr)
    , m_pDrawingBorad(nullptr)
    , m_pMagnifierWidget(nullptr)
    , m_pDimensionalLabel(nullptr)
    , m_CurrentMode(emWindowsAdsorption)
    , m_EditToolBarManager(nullptr)
    , m_pEditOptionData(nullptr)
    , m_isCloseWhenInactive(true)
    , m_exitFlag(TN::ClosedExit)
{
    setMouseTracking(true);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    m_WindowBorderPen.setColor(QColor(0, 174, 255));
    m_WindowBorderPen.setWidth(4);
    m_RubberBandPen.setColor(QColor(0, 174, 255));
    initWindowRectList();
    setAttribute(Qt::WA_QuitOnClose, false);
    connect(qApp, SIGNAL(applicationStateChanged(Qt::ApplicationState)),
        this, SLOT(onApplicationStateChanged(Qt::ApplicationState)));
}

TNScreenShotWindow::~TNScreenShotWindow()
{
}

TN::ScreenShotExitFlag TNScreenShotWindow::exitFlag() const
{
    return m_exitFlag;
}

void TNScreenShotWindow::showEvent(QShowEvent *event)
{
    QScreen *pCurrentScreen = QGuiApplication::primaryScreen();
    if (pCurrentScreen)
    {
        QRect screenRect = pCurrentScreen->geometry();
        m_pmFullScreenShot = pCurrentScreen->grabWindow(QApplication::desktop()->screen()->winId(), 0, 0, screenRect.width(), screenRect.height());
        m_pmFullScreenShot.setDevicePixelRatio(TNUtil::getDevicePixelRatioF());
        m_pmShowBuffer = m_pmFullScreenShot;
        drawAdsorptionWindow(QCursor::pos());
    }
    QWidget::showEvent(event);
}

void TNScreenShotWindow::initWindowRectList()
{
#ifdef Q_OS_WIN
    //windows系统下，遍历所有顶层窗口，取得每个窗口的矩形区域
    GetAllWindow();
    LPRECT lpRect = new tagRECT();
    for (size_t i = 0; i < g_AllWindow.size(); i++)
    {
        GetWindowRect(g_AllWindow[i], lpRect);
        QRect rect(QPoint(lpRect->left, lpRect->top), QPoint(lpRect->right, lpRect->bottom));
        m_windowRectList.push_back(TNUtil::adjustWin32RectByRatio(rect));
    }
    delete lpRect;
    g_AllWindow.clear();
    g_AllWindow.swap(std::vector<HWND>());
#elif __linux__
    QWidget *pWidget = QApplication::activeWindow();
    if (nullptr != pWidget)
        m_windowRectList.push_back(pWidget->geometry());
#else
    m_windowRectList = Mac_getWindowRects::getWindowList();
    qDebug() << "screenshot windowRectList:" << m_windowRectList;
#endif // Q_OS_WIN

    //和整屏幕的rect求交
    QRect fullScreenRect = TNUtil::getScreenWindowRect();
    for (int i = 0; i < m_windowRectList.size(); i++)
    {
        m_windowRectList[i] = m_windowRectList[i].intersected(fullScreenRect);
    }
    qInfo()<<"[ScreenShot][TNScreenShotWindow]-m_windowRectList="<<m_windowRectList;
}

void TNScreenShotWindow::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	QStyleOption opt;
	opt.init(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
	painter.drawPixmap(this->rect(), m_pmShowBuffer);
}

void TNScreenShotWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        accept();
    }
}

void TNScreenShotWindow::mouseMoveEvent(QMouseEvent *event)
{
    switch (m_CurrentMode)
    {
    case emWindowsAdsorption://吸附窗体模式时，移动光标，自动绘制所在窗体边界
        drawAdsorptionWindow(QCursor::pos());
        showMagnifier();
        break;
    case emMousePressAtAdsorption://吸附窗体模式时，如果鼠标处于按下状态, 并且光标有移动，则进入橡皮筋大小调整模式
        if (abs(event->pos().x() - m_posAtMousePress.x()) > 1
            && abs(event->pos().y() - m_posAtMousePress.y()) > 1){
            Q_ASSERT(nullptr == m_pRubberBand);
            creatRubberBand();
            m_pRubberBand->setGeometry(QRect(m_posAtMousePress, QSize()));
            QRect rubber_rect = m_pRubberBand->geometry();
            drawRubberBandOrDrawingBoard(rubber_rect);
            m_CurrentMode = emRubberBandResize;
        }
        break;
    case emRubberBandResize:{
        showMagnifier();
        m_pRubberBand->setGeometry(QRect(m_posAtMousePress, event->pos()).normalized());
        /*
        */
    }
        break;
    default:
        break;
    }
    QWidget::mouseMoveEvent(event);
}

void TNScreenShotWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        if (m_CurrentMode == emDrawingEdit)
        {
            //todo 右键菜单
        }
        else
        {
            accept();
        }
    }
    if (event->button() == Qt::LeftButton)
    {
        m_posAtMousePress = event->pos();
        switch (m_CurrentMode)
        {
        case TNScreenShotWindow::emWindowsAdsorption:
            m_CurrentMode = emMousePressAtAdsorption;
            break;
        default:
            break;
        }
    }
}

void TNScreenShotWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        switch (m_CurrentMode)
        {
        case emWindowsAdsorption:
            Q_ASSERT(false);
            break;
        case emMousePressAtAdsorption:{//吸附窗体模式时，释放光标,进入"画板模式"
            creatDrawingBoard();
            m_pDrawingBorad->setGeometry(m_AdsorptionWindowRect);
            m_CurrentMode = emDrawingBoardMove;
            m_pMagnifierWidget->hide();
            showToolBar();
        }
            break;
        case emRubberBandResize:{//调整橡皮筋窗体大小模式时，释放光标,也进入"画板模式"
            creatDrawingBoard();
            m_pDrawingBorad->setGeometry(m_pRubberBand->geometry());
            delete m_pRubberBand;
            m_pRubberBand = nullptr;
            m_CurrentMode = emDrawingBoardMove;
            m_pMagnifierWidget->hide();
            showToolBar();
        }
            break;
        case emDrawingBoardResize:
            m_pMagnifierWidget->hide();
            showToolBar();
            break;
        default:
            break;
        }
    }
}

bool TNScreenShotWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == m_pRubberBand)
    {
        if (event->type() == QEvent::Paint)
        {
            drawRubberBandOrDrawingBoard(m_pRubberBand->geometry());
            return true;
        }
        if (event->type() == QEvent::Move)
        {
            //还原坐标
            relocateDimensionalLabel(m_pRubberBand->pos());
        }
        if (event->type() == QEvent::Resize)
        {
            setDimensionalPrompt(m_pRubberBand->width(), m_pRubberBand->height());
        }
    }

    if (watched == m_pDrawingBorad)
    {
        if (event->type() == QEvent::Paint)
        {
            drawRubberBandOrDrawingBoard(m_pDrawingBorad->geometry());
        }
        if (event->type() == QEvent::Move)
        {
            //显示时,将坐标还原
            relocateDimensionalLabel(m_pDrawingBorad->pos());
            showToolBar();
        }
        if (event->type() == QEvent::Resize)
        {
            if (m_CurrentMode != emDrawingBoardResize)
            {
                m_CurrentMode = emDrawingBoardResize;
            }
            setDimensionalPrompt(m_pDrawingBorad->width(), m_pDrawingBorad->height());
            showMagnifier();
            hideToolBar();
        }
    }
    return QWidget::eventFilter(watched, event);
} 

void TNScreenShotWindow::creatRubberBand()
{
    Q_ASSERT(nullptr == m_pRubberBand);
    m_pRubberBand = new QRubberBand(QRubberBand::Line, this);
    m_pRubberBand->installEventFilter(this);
    m_pRubberBand->show();
    createDimensionalLabel();
}

void TNScreenShotWindow::creatDrawingBoard()
{
    Q_ASSERT(nullptr == m_pDrawingBorad);
    m_pDrawingBorad = new TNDrawingBoard(this);
    m_pDrawingBorad->installEventFilter(this);
    m_pDrawingBorad->show();
    if (nullptr != m_pMagnifierWidget)
    {
        //保证放大镜在画板的上方
        m_pMagnifierWidget->raise();
    }
    createDimensionalLabel();
    connect(m_pDrawingBorad, SIGNAL(hasDrawn()), this, SLOT(onFirstDrawn()));
    connect(m_pDrawingBorad, SIGNAL(doubleClick()), this, SLOT(onOk()));
}

void TNScreenShotWindow::createDimensionalLabel()
{
    if (nullptr == m_pDimensionalLabel)
    {
        m_pDimensionalLabel = new QLabel(this);
        m_pDimensionalLabel->setObjectName("DimensionalDisplayLabel");
        m_pDimensionalLabel->setFixedSize(70, 22);
        m_pDimensionalLabel->setAlignment(Qt::AlignCenter);
        m_pDimensionalLabel->setAutoFillBackground(true);
        m_pDimensionalLabel->show();
    }
}

void TNScreenShotWindow::setDimensionalPrompt(int width, int height)
{
    if (nullptr != m_pDimensionalLabel)
    {
        m_pDimensionalLabel->setText(QString("%1%2%3").arg(width).arg(tr(QStringLiteral("×").toUtf8().data())).arg(height));
    }
}

void TNScreenShotWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    getResultPixmap();
    QApplication::clipboard()->setPixmap(m_pmResult);
    m_exitFlag = TN::FinishedExit;
    accept();
}

void TNScreenShotWindow::getResultPixmap()
{
    switch (m_CurrentMode)
    {
    case TNScreenShotWindow::emMousePressAtAdsorption:
        break;
    case TNScreenShotWindow::emRubberBandResize:
        break;
    case TNScreenShotWindow::emWindowsAdsorption:
    {
        QRect rect = m_AdsorptionWindowRect;
        m_pmResult = m_pmFullScreenShot.copy(TNUtil::adjustRectByRatio(rect));
        break;
    }
    case TNScreenShotWindow::emDrawingBoardResize:
    case TNScreenShotWindow::emDrawingBoardMove:
    case TNScreenShotWindow::emDrawingEdit:
    {
        QRect rect = m_pDrawingBorad->geometry();
        QPainter painter(&m_pmFullScreenShot);
        painter.drawPixmap(this->rect(), m_pDrawingBorad->getComplatedPixmap());
        m_pmResult = m_pmFullScreenShot.copy(TNUtil::adjustRectByRatio(rect));
        break;
    }
    default:
        break;
    }
    Q_ASSERT(!m_pmResult.isNull());
}

void TNScreenShotWindow::drawBackground(QRect transparent)
{
    m_pmShowBuffer = m_pmFullScreenShot;
    QPainter painter(&m_pmShowBuffer);
    //画其他区域的半透明效果
    QRegion backgroundRegion;
    backgroundRegion += TNUtil::getScreenWindowRect();
    backgroundRegion -= transparent;
    QPainterPath path;
    path.addRegion(backgroundRegion);
    painter.fillPath(path, QBrush(QColor(0, 0, 0, 150)));
}

void TNScreenShotWindow::drawRubberBandOrDrawingBoard(QRect orinRect)
{
    drawBackground(orinRect);
    QPainter painter(&m_pmShowBuffer);
    //绘制边框
    m_RubberBandPen.setWidth(1);
    painter.setPen(m_RubberBandPen);
    QRect borderRect = orinRect;
    borderRect.adjust(0, 0, -1, -1);
    painter.drawRect(borderRect);

    //绘制顶点
    m_RubberBandPen.setWidth(5);
    painter.setPen(m_RubberBandPen);
    painter.drawPoint(orinRect.topLeft());
    painter.drawPoint(orinRect.topRight());
    painter.drawPoint(orinRect.bottomLeft());
    painter.drawPoint(orinRect.bottomRight());
    painter.drawPoint((orinRect.topLeft() + orinRect.topRight()) / 2);
    painter.drawPoint((orinRect.topLeft() + orinRect.bottomLeft()) / 2);
    painter.drawPoint((orinRect.topRight() + orinRect.bottomRight()) / 2);
    painter.drawPoint((orinRect.bottomLeft() + orinRect.bottomRight()) / 2);
    update();
}

void TNScreenShotWindow::drawAdsorptionWindow(QPoint curPos)
{
    m_AdsorptionWindowRect = TNUtil::getScreenWindowRect();
    for (int i = 0; i < m_windowRectList.size(); i++)
    {
        if (m_windowRectList[i].contains(curPos))
        {
            m_AdsorptionWindowRect = m_windowRectList[i];
            break;
        }
    }
    drawBackground(m_AdsorptionWindowRect);
    QPainter painter(&m_pmShowBuffer);
    //画边框
    painter.setPen(m_WindowBorderPen);
    QRect borderRect = m_AdsorptionWindowRect;
    painter.drawRect(borderRect);
    update();
}

void TNScreenShotWindow::relocateDimensionalLabel(QPoint refPoint)
{
    if (nullptr != m_pDimensionalLabel)
    {
        double y = refPoint.y() - m_pDimensionalLabel->height() - 1;
        if (y < 0)
        {
            y = refPoint.y();
        }
        m_pDimensionalLabel->move(QPoint(refPoint.x(), y));
    }
}

void TNScreenShotWindow::showMagnifier()
{
    if (nullptr == m_pMagnifierWidget)
    {
        m_pMagnifierWidget = new TNMagnifierWidget(this);
    }
    QPoint curPos = QCursor::pos();
    QRect rect(curPos + QPoint(-15, -11), curPos + QPoint(15, 11));
    QPixmap pixmap = m_pmFullScreenShot.copy(TNUtil::adjustRectByRatio(rect));
    int width = m_AdsorptionWindowRect.width();
    int height = m_AdsorptionWindowRect.height();
    if (m_pRubberBand != nullptr)
    {
        width = m_pRubberBand->width();
        height = m_pRubberBand->height();
    }
    else if (m_pDrawingBorad != nullptr)
    {
        width = m_pDrawingBorad->width();
        height = m_pDrawingBorad->height();
    }
    m_pMagnifierWidget->updatePixmap(pixmap, width, height);
    m_pMagnifierWidget->relocate(curPos);
    m_pMagnifierWidget->show();
}

void TNScreenShotWindow::showToolBar()
{
    TNScreenshotEditOptionData *pEditOptionData = TNScreenshotEditOptionData::instance();
    if (nullptr == m_EditToolBarManager)
    {
        TNScreenshotEditOptionData::instance()->currentCommand = ctNull;
        m_EditToolBarManager = new TNScreenshotEditToolBarManager(pEditOptionData, this);
        connect(m_EditToolBarManager, SIGNAL(undo()), this, SLOT(onUndo()));
        connect(m_EditToolBarManager, SIGNAL(ok()), this, SLOT(onOk()));
        connect(m_EditToolBarManager, SIGNAL(cancel()), this, SLOT(onCancel()));
        connect(m_EditToolBarManager, SIGNAL(save()), this, SLOT(onSave()));
        connect(m_EditToolBarManager, SIGNAL(drawActionChanged(CommandType)), m_pDrawingBorad, SLOT(onDrawActionChanged(CommandType)));
        connect(m_EditToolBarManager, SIGNAL(textColorChange()), m_pDrawingBorad, SLOT(onCurrentTextColorChanged()));
    }
    m_pDrawingBorad->setEditToolBarManager(m_EditToolBarManager);
    m_pDrawingBorad->setOptionData(pEditOptionData);
    m_EditToolBarManager->showToolBar();
    m_EditToolBarManager->relocateToolBar(m_pDrawingBorad->geometry(), this->geometry());
}

void TNScreenShotWindow::hideToolBar()
{
    if (nullptr != m_EditToolBarManager)
    {
        m_EditToolBarManager->hideToolBar();
    }
}

void TNScreenShotWindow::onUndo()
{
    if (m_pDrawingBorad->undo())
    {
        delete m_pDrawingBorad;
        m_pDrawingBorad = nullptr;
        m_CurrentMode = emWindowsAdsorption;
        drawAdsorptionWindow(QCursor::pos());
        m_EditToolBarManager->hideToolBar();
    }
}

void TNScreenShotWindow::onSave()
{
    getResultPixmap();
    QString defaltPath = TNPathUtil::getUserRecFile();
    QString defaltName = tr(QString(QStringLiteral("通toon截图")).toUtf8().data()) + QDateTime::currentDateTime().toString("yyyyMMddhhmmss");;
    m_isCloseWhenInactive = false;
    QString fileName = QFileDialog::getSaveFileName(
        this,
        tr(QStringLiteral("文件另存为").toUtf8().data()),
        defaltPath + defaltName, 
        QString("Config Files (*.png)")
        );
    m_isCloseWhenInactive = true;
    if (!fileName.isEmpty())
    {
        m_pmResult.save(fileName);
        accept();
    }
}

void TNScreenShotWindow::onOk()
{
    getResultPixmap();
    QApplication::clipboard()->setPixmap(m_pmResult);
    m_exitFlag = TN::FinishedExit;
    accept();
}

void TNScreenShotWindow::accept()
{
#ifdef Q_OS_MAC
    showNormal();
#endif
    return QDialog::accept();
}

void TNScreenShotWindow::onCancel()
{
    accept();
}

void TNScreenShotWindow::onFirstDrawn()
{
    m_CurrentMode = emDrawingEdit;
}

void TNScreenShotWindow::onApplicationStateChanged(Qt::ApplicationState state)
{
    if (m_isCloseWhenInactive && state != Qt::ApplicationActive)
    {
        accept();
    }
}
