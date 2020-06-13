#include <QAction>
#include <QActionGroup>
#include <QComboBox>
#include <QToolBar>
#include <QToolButton>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSignalMapper>
#include <QEvent>
#include <QDebug>
#include "TNScreenshotEditToolBarManager.h"
#include "TNScreenShotTextEdit.h"

TNScreenshotEditToolBarManager::TNScreenshotEditToolBarManager(TNScreenshotEditOptionData *pData, QWidget*parent)
: QObject(parent)
, m_pData(pData)
, m_pParent(parent)
, m_contextMenu(nullptr)
, m_pCommandBar(nullptr)
, m_pRectangle(nullptr), m_pRectangleMenu(nullptr)
, m_pEllipse(nullptr), m_pEllipseMenu(nullptr)
, m_pArrow(nullptr), m_pArrowMenu(nullptr)
, m_pBrush(nullptr), m_pBrushMenu(nullptr)
, m_pText(nullptr), m_pTextMenu(nullptr)
, m_pUndo(nullptr), m_pUndoMenu(nullptr)
, m_pSave(nullptr), m_pSaveMenu(nullptr)
, m_pCancel(nullptr), m_pCancelMenu(nullptr)
, m_pOK(nullptr), m_pOKMenu(nullptr)
, m_pOptionBar(nullptr)
, m_pLineWidth_Small(nullptr)
, m_pLineWidth_Middle(nullptr)
, m_pLineWidth_Large(nullptr)
, m_pTextSizeComboBox(nullptr)
{
    initToolBar();
}

TNScreenshotEditToolBarManager::~TNScreenshotEditToolBarManager()
{

}

void TNScreenshotEditToolBarManager::showToolBar()
{
    m_pCommandBar->show();
}

void TNScreenshotEditToolBarManager::hideToolBar()
{
    m_pCommandBar->hide();
    m_pOptionBar->hide();
}

void TNScreenshotEditToolBarManager::initToolBar()
{
    m_contextMenu = new QMenu();
    m_contextMenu->setObjectName("shotContextMenu");

    m_pCommandBar = new SSToolBar(m_pParent);
    m_pCommandBar->setAutoFillBackground(true);
    m_pCommandBar->setObjectName("shotToolBar");
	m_pCommandBar->setFixedSize(404, 40);
    m_pDrawCommandGroup = new QActionGroup(this);

    //矩形工具
    QToolButton *pBtnRegangle = new QToolButton();
    m_pRectangle = m_pCommandBar->addWidget(pBtnRegangle);
    m_pRectangle->setToolTip(tr(QStringLiteral("矩形工具").toUtf8().data()));
    pBtnRegangle->setDefaultAction(m_pRectangle);
    pBtnRegangle->setObjectName("shotSquare");
	pBtnRegangle->setFixedSize(20,20);
    m_pDrawCommandGroup->setExclusive(false);
    m_pRectangle->setCheckable(true);
    m_pDrawCommandGroup->addAction(m_pRectangle);
	m_pRectangleMenu = new QAction(QIcon(":/screenShot/Resources/img/screenShot/menu/square.png"), tr(QStringLiteral("矩形工具").toUtf8().data()), m_contextMenu);
    m_contextMenu->addAction(m_pRectangleMenu);

    //椭圆工具
    QToolButton *pBtnEllipse = new QToolButton();
    m_pEllipse = m_pCommandBar->addWidget(pBtnEllipse);
	m_pEllipse->setToolTip(tr(QStringLiteral("椭圆工具").toUtf8().data()));
    pBtnEllipse->setDefaultAction(m_pEllipse);
    pBtnEllipse->setObjectName("shotCircle");
	pBtnEllipse->setFixedSize(20, 20);
	pBtnRegangle->setContentsMargins(10, 0, 10, 0);
    m_pEllipse->setCheckable(true);
    m_pDrawCommandGroup->addAction(m_pEllipse);

	m_pEllipseMenu = new QAction(QIcon(":/screenShot/Resources/img/screenShot/menu/circle.png"), tr(QStringLiteral("椭圆工具").toUtf8().data()), m_contextMenu);
    m_contextMenu->addAction(m_pEllipseMenu);

    //箭头工具
    QToolButton *pBtnArrow = new QToolButton();
    m_pArrow = m_pCommandBar->addWidget(pBtnArrow);
    m_pArrow->setToolTip(tr(QStringLiteral("箭头工具").toUtf8().data()));
    pBtnArrow->setDefaultAction(m_pArrow);
    pBtnArrow->setObjectName("shotArrow");
	pBtnArrow->setFixedSize(20, 20);
	pBtnArrow->setContentsMargins(10, 0, 10, 0);
    m_pArrow->setCheckable(true);
    m_pDrawCommandGroup->addAction(m_pArrow);

	m_pArrowMenu = new QAction(QIcon(":/screenShot/Resources/img/screenShot/menu/arrow.png"), tr(QStringLiteral("箭头工具").toUtf8().data()), m_contextMenu);
    m_contextMenu->addAction(m_pArrowMenu);

    //画刷工具
    QToolButton *pBtnBrush = new QToolButton();
    m_pBrush = m_pCommandBar->addWidget(pBtnBrush);
	m_pBrush->setToolTip(tr(QStringLiteral("画刷工具").toUtf8().data()));
    pBtnBrush->setDefaultAction(m_pBrush);
    pBtnBrush->setObjectName("shotPen");
	pBtnBrush->setFixedSize(20, 20);
    m_pBrush->setCheckable(true);
    m_pDrawCommandGroup->addAction(m_pBrush);

	m_pBrushMenu = new QAction(QIcon(":/screenShot/Resources/img/screenShot/menu/pen.png"), tr(QStringLiteral("画刷工具").toUtf8().data()), m_contextMenu);
    m_contextMenu->addAction(m_pBrushMenu);

    //文字工具
    QToolButton *pBtnText = new QToolButton();
    m_pText = m_pCommandBar->addWidget(pBtnText);
    m_pText->setToolTip(tr(QStringLiteral("文字工具").toUtf8().data()));
    pBtnText->setDefaultAction(m_pText);
    pBtnText->setObjectName("shotWord");
	pBtnText->setFixedSize(20, 20);
    m_pText->setCheckable(true);
    m_pDrawCommandGroup->addAction(m_pText);

	m_pTextMenu = new QAction(QIcon(":/screenShot/Resources/img/screenShot/menu/word.png"), tr(QStringLiteral("文字工具").toUtf8().data()), m_contextMenu);
    m_contextMenu->addAction(m_pTextMenu);

    m_pCommandBar->addSeparator();

    //撤销编辑
    m_pEditCommandGroup = new QActionGroup(this);
    QToolButton *pBtnUndo = new QToolButton();
    m_pUndo = m_pCommandBar->addWidget(pBtnUndo);
    m_pUndo->setShortcut(QString("Ctrl+Z"));
    m_pUndo->setToolTip(tr(QStringLiteral("撤销编辑").toUtf8().data()));
    pBtnUndo->setDefaultAction(m_pUndo);
    pBtnUndo->setObjectName("shotRotate");
	pBtnUndo->setFixedSize(20, 20);
    m_pEditCommandGroup->addAction(m_pUndo);

    m_contextMenu->addSeparator();
	m_pUndoMenu = new QAction(QIcon(":/screenShot/Resources/img/screenShot/menu/rotate.png"), tr(QStringLiteral("撤销编辑").toUtf8().data()), m_contextMenu);
    m_contextMenu->addAction(m_pUndoMenu);

    //保存
    QToolButton *pBtnSave = new QToolButton();
    m_pSave = m_pCommandBar->addWidget(pBtnSave);
    m_pSave->setShortcut(QString("Ctrl+S"));
	m_pSave->setToolTip(tr(QStringLiteral("保存").toUtf8().data()));
    pBtnSave->setDefaultAction(m_pSave);
    pBtnSave->setObjectName("shotSave");
	pBtnSave->setFixedSize(20, 20);
    m_pEditCommandGroup->addAction(m_pSave);

	m_pSaveMenu = new QAction(QIcon(":/screenShot/Resources/img/screenShot/menu/download.png"), tr(QStringLiteral("保存").toUtf8().data()), m_contextMenu);
    m_contextMenu->addAction(m_pSaveMenu);

    //退出截图
    QToolButton *pBtnCancle= new QToolButton();
    m_pCancel = m_pCommandBar->addWidget(pBtnCancle);
    m_pCancel->setToolTip(tr(QStringLiteral("退出截图").toUtf8().data()));
    pBtnCancle->setDefaultAction(m_pCancel);
    pBtnCancle->setObjectName("shotExit");
	pBtnCancle->setFixedSize(20, 20);
    m_pEditCommandGroup->addAction(m_pCancel);

	m_pCancelMenu = new QAction(QIcon(":/screenShot/Resources/img/screenShot/menu/cross.png"), tr(QStringLiteral("退出截图").toUtf8().data()), m_contextMenu);
    m_contextMenu->addAction(m_pCancelMenu);

    //完成截图
    QToolButton *pBtnOK = new QToolButton();
    m_pOK = m_pCommandBar->addWidget(pBtnOK);
    m_pOK->setToolTip(tr(QStringLiteral("完成截图").toUtf8().data()));
    pBtnOK->setDefaultAction(m_pOK);
    pBtnOK->setObjectName("shotOk");
	pBtnOK->setFixedSize(20, 20);
    m_pEditCommandGroup->addAction(m_pOK);

	m_pOKMenu = new QAction(QIcon(":/screenShot/Resources/img/screenShot/menu/ok.png"), tr(QStringLiteral("完成截图").toUtf8().data()), m_contextMenu);
    m_contextMenu->addAction(m_pOKMenu);

    //选项工具栏
    m_pOptionBar = new QToolBar(m_pParent);
	m_pOptionBar->setObjectName("shotOptionBar");
	m_pOptionBar->setContentsMargins(0, 0, 0, 0);
	m_pOptionBar->setFixedSize(404, 40);
    m_pOptionBar->setAutoFillBackground(true);

    //细线
    m_pLineWidthGroup = new QActionGroup(this);
    QToolButton *pBtnLineWidth_Small = new QToolButton();
    m_pLineWidth_Small = m_pOptionBar->addWidget(pBtnLineWidth_Small);
    pBtnLineWidth_Small->setDefaultAction(m_pLineWidth_Small);
	pBtnLineWidth_Small->setFixedSize(32, 40);
	pBtnLineWidth_Small->setObjectName("lineSmall");
    pBtnLineWidth_Small->setToolTip(tr(QStringLiteral("细线").toUtf8().data()));
    m_pLineWidth_Small->setCheckable(true);
    m_pLineWidthGroup->addAction(m_pLineWidth_Small);

    //中线
    QToolButton *pBtnLineWidth_Middle = new QToolButton();
    m_pLineWidth_Middle = m_pOptionBar->addWidget(pBtnLineWidth_Middle);
    pBtnLineWidth_Middle->setDefaultAction(m_pLineWidth_Middle);
    m_pLineWidth_Middle->setCheckable(true);
	pBtnLineWidth_Middle->setFixedSize(32, 40);
	pBtnLineWidth_Middle->setObjectName("lineMiddle");
    pBtnLineWidth_Middle->setToolTip(tr(QStringLiteral("中线").toUtf8().data()));
    m_pLineWidthGroup->addAction(m_pLineWidth_Middle);

    //粗线
    QToolButton *pBtnLineWidth_Large = new QToolButton();
    m_pLineWidth_Large = m_pOptionBar->addWidget(pBtnLineWidth_Large);
    pBtnLineWidth_Large->setDefaultAction(m_pLineWidth_Large);
    m_pLineWidth_Large->setCheckable(true);
	pBtnLineWidth_Large->setFixedSize(32, 40);
	pBtnLineWidth_Large->setObjectName("lineLarge");
    pBtnLineWidth_Large->setToolTip(tr(QStringLiteral("粗线").toUtf8().data()));
    m_pLineWidthGroup->addAction(m_pLineWidth_Large);

    //字体选择控件
    QWidget * pTextSizeWidget = new QWidget(m_pParent);
    m_pTextSizeAction = m_pOptionBar->addWidget(pTextSizeWidget);
    QHBoxLayout *pLayout = new QHBoxLayout();
    pLayout->setContentsMargins(2, 0, 10, 0);
    pLayout->setSpacing(0);
    pTextSizeWidget->setLayout(pLayout);
    QLabel *pLabel = new QLabel();
	pLabel->setObjectName("shotWord");
	pLabel->setFixedSize(40, 40);
    pLabel->setContentsMargins(0, 0, 0, 0);
    pLayout->addWidget(pLabel);
    m_pTextSizeComboBox = new QComboBox(m_pParent);
	m_pTextSizeComboBox->setObjectName("shotCombobox");
    m_pTextSizeComboBox->setContentsMargins(0, 0, 0, 0);
    m_pTextSizeComboBox->setMaximumWidth(50);
    //m_pTextSizeComboBox->setFocusPolicy(Qt::NoFocus);
    for (int i = 8; i <= 12; i++)
    {
        m_pTextSizeComboBox->addItem(QString("%1").arg(i));
    }

    for (int i = 14; i <= 22; i+=2)
    {
        m_pTextSizeComboBox->addItem(QString("%1").arg(i));
    }
    pLayout->addWidget(m_pTextSizeComboBox);

    m_pOptionBar->addSeparator();
    //颜色选项
    m_pColorSignalMap = new QSignalMapper(this);
    m_pColorGroup = new QActionGroup(this);
    for (int i = 0; i < 8; i++)
    {
        QToolButton *pBtnColor = new QToolButton();
        QAction *pColorAction = m_pOptionBar->addWidget(pBtnColor);
        QString colorBtnName = QString("colorButton_%1").arg(i+1);
        pBtnColor->setObjectName(colorBtnName);
		pBtnColor->setFixedSize(32, 40);
        pBtnColor->setDefaultAction(pColorAction);
        pColorAction->setCheckable(true);
        m_pColorGroup->addAction(pColorAction);
        connect(pColorAction, SIGNAL(triggered()), m_pColorSignalMap, SLOT(map()));
        m_pColorSignalMap->setMapping(pColorAction, i);
    }
    connect(m_pColorSignalMap, SIGNAL(mapped(int)), this, SLOT(onColorSelected(int)));

    connect(m_pRectangle, SIGNAL(triggered()), this, SLOT(onRectangleAction()));
    connect(m_pRectangleMenu, SIGNAL(triggered()), this, SLOT(onRectangleActionMenu()));
    connect(m_pEllipse, SIGNAL(triggered()), this, SLOT(onEllipseAction()));
    connect(m_pEllipseMenu, SIGNAL(triggered()), this, SLOT(onEllipseActionMenu()));
    connect(m_pArrow, SIGNAL(triggered()), this, SLOT(onArrowAction()));
    connect(m_pArrowMenu, SIGNAL(triggered()), this, SLOT(onArrowActionMenu()));
    connect(m_pBrush, SIGNAL(triggered()), this, SLOT(onBrushAction()));
    connect(m_pBrushMenu, SIGNAL(triggered()), this, SLOT(onBrushActionMenu()));
    connect(m_pText, SIGNAL(triggered()), this, SLOT(onTextAction()));
    connect(m_pTextMenu, SIGNAL(triggered()), this, SLOT(onTextActionMenu()));
    connect(m_pOK, SIGNAL(triggered()), this, SLOT(onOKAction()));
    connect(m_pOKMenu, SIGNAL(triggered()), this, SLOT(onOKAction()));
    connect(m_pCancel, SIGNAL(triggered()), this, SLOT(onCancelAction()));
    connect(m_pCancelMenu, SIGNAL(triggered()), this, SLOT(onCancelAction()));
    connect(m_pSave, SIGNAL(triggered()), this, SLOT(onSaveAction()));
    connect(m_pSaveMenu, SIGNAL(triggered()), this, SLOT(onSaveAction()));
    connect(m_pUndo, SIGNAL(triggered()), this, SLOT(onUndoAction()));
    connect(m_pUndoMenu, SIGNAL(triggered()), this, SLOT(onUndoAction()));
    connect(m_pEditCommandGroup, SIGNAL(triggered(QAction *)), this, SLOT(onEditGroupTrigger()));
    connect(m_pLineWidth_Small, SIGNAL(triggered()), this, SLOT(onLineWidth_SmallAction()));
    connect(m_pLineWidth_Middle, SIGNAL(triggered()), this, SLOT(onLineWidth_MiddleAction()));
    connect(m_pLineWidth_Large, SIGNAL(triggered()), this, SLOT(onLineWidth_LargeAction()));
    connect(m_pTextSizeComboBox, SIGNAL(currentTextChanged(const QString &)), this, SLOT(onTextSizeChanged(const QString &)));
}

void TNScreenshotEditToolBarManager::relocateToolBar(const QRect &refRect, const QRect &screenRect)
{
    int nCommandBarWidth = m_pCommandBar->width();
    int nCommandBarHeight = m_pCommandBar->height();
    int nOptionBarWidth = m_pOptionBar->width();
    int nOptionBarHeight = m_pOptionBar->height();

    //y值
    int nCommandBarDefaultY = refRect.bottomRight().y() + 5;
    int nOptionBarDefaultY = nCommandBarDefaultY + nCommandBarHeight + 5;
    //如果工具栏底部超过屏幕，则重定位到上边
    if (nOptionBarDefaultY + nOptionBarHeight > screenRect.height())
    {
        nCommandBarDefaultY = refRect.topRight().y() -nCommandBarHeight - 5;
        nOptionBarDefaultY = nCommandBarDefaultY - nOptionBarHeight - 5;
    }
    //工具栏顶部超过屏幕，则重定位到上边
    if (nOptionBarDefaultY < 0)
    {
        nCommandBarDefaultY = refRect.topRight().y() + 5;
        nOptionBarDefaultY = nCommandBarDefaultY + nCommandBarHeight + 5;
    }

    //x值
    int nCommandBarDefaultX = refRect.bottomRight().x() - nCommandBarWidth;
    nCommandBarDefaultX = std::max<int>(nCommandBarDefaultX, 0);
    int nOptionBarDefaultX = nCommandBarDefaultX;

    m_pCommandBar->move(nCommandBarDefaultX, nCommandBarDefaultY);
    m_pOptionBar->move(nOptionBarDefaultX, nOptionBarDefaultY);
}

QMenu *TNScreenshotEditToolBarManager::getContextMenu()
{
    return m_contextMenu;
}

void TNScreenshotEditToolBarManager::onRectangleAction()
{
    if (m_pRectangle->isChecked())
    {
        m_pLineWidthGroup->setVisible(true);
        m_pTextSizeAction->setVisible(false);
        m_pData->currentCommand = ctRectangle;
        m_pLineWidthGroup->actions().at(m_pData->rectangleAttribute.lineWidthSize)->setChecked(true);
        m_pColorGroup->actions().at(m_pData->rectangleAttribute.nColorIndex)->setChecked(true);
        m_pOptionBar->show();
        setUncheckedOtherDrawAction(m_pRectangle);
        emit drawActionChanged(ctRectangle);
    }
    else
    {
        m_pOptionBar->hide();
    }
}

void TNScreenshotEditToolBarManager::onRectangleActionMenu()
{
    m_pRectangle->setChecked(true);
    onRectangleAction();
}

void TNScreenshotEditToolBarManager::onEllipseAction()
{
    if (m_pEllipse->isChecked())
    {
        m_pLineWidthGroup->setVisible(true);
        m_pTextSizeAction->setVisible(false);
        m_pData->currentCommand = ctEllipse;
        m_pLineWidthGroup->actions().at(m_pData->ellipseAttribute.lineWidthSize)->setChecked(true);
        m_pColorGroup->actions().at(m_pData->ellipseAttribute.nColorIndex)->setChecked(true);
        m_pOptionBar->show();
        setUncheckedOtherDrawAction(m_pEllipse);
        emit drawActionChanged(ctEllipse);
    }
    else
    {
        m_pOptionBar->hide();
    }
}

void TNScreenshotEditToolBarManager::onEllipseActionMenu()
{
    m_pEllipse->setChecked(true);
    onEllipseAction();
}

void TNScreenshotEditToolBarManager::onArrowAction()
{
    if (m_pArrow->isChecked())
    {
        m_pLineWidthGroup->setVisible(true);
        m_pTextSizeAction->setVisible(false);
        m_pData->currentCommand = ctArrow;
        m_pLineWidthGroup->actions().at(m_pData->arrowAttribute.lineWidthSize)->setChecked(true);
        m_pColorGroup->actions().at(m_pData->arrowAttribute.nColorIndex)->setChecked(true);
        m_pOptionBar->show();
        setUncheckedOtherDrawAction(m_pArrow);
        emit drawActionChanged(ctArrow);
    }
    else
    {
        m_pOptionBar->hide();
    }
}

void TNScreenshotEditToolBarManager::onArrowActionMenu()
{
    m_pArrow->setChecked(true);
    onArrowAction();
}

void TNScreenshotEditToolBarManager::onBrushAction()
{
    if (m_pBrush->isChecked())
    {
        m_pLineWidthGroup->setVisible(true);
        m_pTextSizeAction->setVisible(false);
        m_pData->currentCommand = ctBrush;
        m_pLineWidthGroup->actions().at(m_pData->brushAttribute.lineWidthSize)->setChecked(true);
        m_pColorGroup->actions().at(m_pData->brushAttribute.nColorIndex)->setChecked(true);
        m_pOptionBar->show();
        setUncheckedOtherDrawAction(m_pBrush);
        emit drawActionChanged(ctBrush);
    }
    else
    {
        m_pOptionBar->hide();
    }
}

void TNScreenshotEditToolBarManager::onBrushActionMenu()
{
    m_pBrush->setChecked(true);
    onBrushAction();
}

void TNScreenshotEditToolBarManager::onTextAction()
{
    if (m_pText->isChecked())
    {
        m_pLineWidthGroup->setVisible(false);
        m_pTextSizeAction->setVisible(true);
        m_pData->currentCommand = ctText;
        m_pTextSizeComboBox->setCurrentText(QString("%1").arg(m_pData->textAttribute.nFontSize));
        m_pColorGroup->actions().at(m_pData->textAttribute.nColorIndex)->setChecked(true);
        m_pOptionBar->show();
        setUncheckedOtherDrawAction(m_pText);
        emit drawActionChanged(ctText);
    }
    else
    {
        m_pOptionBar->hide();
    }
}

void TNScreenshotEditToolBarManager::onTextActionMenu()
{
    m_pText->setChecked(true);
    onTextAction();
}

void TNScreenshotEditToolBarManager::onUndoAction()
{
    QList<QAction*> actionList = m_pDrawCommandGroup->actions();
    for (int i = 0; i < actionList.size(); i++)
    {
        actionList[i]->setChecked(false);
    }

    emit undo();
}
void TNScreenshotEditToolBarManager::onSaveAction()
{
    emit save();
}

void TNScreenshotEditToolBarManager::onCancelAction()
{
    emit cancel();
}

void TNScreenshotEditToolBarManager::onOKAction()
{
    emit ok();
}

void TNScreenshotEditToolBarManager::changeLineWidth(LineWidthSize type)
{
    switch (m_pData->currentCommand)
    {
    case ctRectangle:
        m_pData->rectangleAttribute.lineWidthSize = type;
        break;
    case ctEllipse:
        m_pData->ellipseAttribute.lineWidthSize = type;
        break;
    case ctArrow:
        m_pData->arrowAttribute.lineWidthSize = type;
        break;
    case ctBrush:
        m_pData->brushAttribute.lineWidthSize = type;
        break;
    default:
        break;
    }
}

void TNScreenshotEditToolBarManager::onLineWidth_SmallAction()
{
    changeLineWidth(lwsSmall);
}

void TNScreenshotEditToolBarManager::onLineWidth_MiddleAction()
{
    changeLineWidth(lwsMiddle);
}

void TNScreenshotEditToolBarManager::onLineWidth_LargeAction()
{
    changeLineWidth(lwsLarge);
}

void TNScreenshotEditToolBarManager::setUncheckedOtherDrawAction(QAction *pCurrentAction)
{
    QList<QAction*> actionList = m_pDrawCommandGroup->actions();
    for (int i = 0; i < actionList.size(); i++)
    {
        QAction *pAction = actionList[i];
        if (pAction != pCurrentAction)
        {
            pAction->setChecked(false);
        }
    }
}

void TNScreenshotEditToolBarManager::onEditGroupTrigger()
{
    QAction *pCheckedAction = m_pDrawCommandGroup->checkedAction();
    if (nullptr != pCheckedAction)
    {
        pCheckedAction->setChecked(false);
    }
    m_pOptionBar->hide();
}

void TNScreenshotEditToolBarManager::onColorSelected(int index)
{
    switch (m_pData->currentCommand)
    {
    case ctRectangle:
        m_pData->rectangleAttribute.nColorIndex = index;
        break;
    case ctEllipse:
        m_pData->ellipseAttribute.nColorIndex = index;
        break;
    case ctArrow:
        m_pData->arrowAttribute.nColorIndex = index;
        break;
    case ctBrush:
        m_pData->brushAttribute.nColorIndex = index;
        break;
    case ctText:
        m_pData->textAttribute.nColorIndex = index;
        emit textColorChange();
        break;
    default:
        break;
    }
}

void TNScreenshotEditToolBarManager::onTextSizeChanged(const QString &text)
{
    m_pData->textAttribute.nFontSize = text.toInt();
    if (nullptr != m_pData->currentTextEdit)
    {
        m_pData->currentTextEdit->setFontSize(m_pData->textAttribute.nFontSize);
    }
}
