#include <QIcon>
#include "TNResizerDecorator.h"
#include "DropShadowWidget.h"
#include "TNVersionInfo.h"
#define SHADOW_WIDTH 20
#define RESIZEBORDERWIDTH 5 //调整窗体大小时，边界宽度
DropShadowWidget::DropShadowWidget(QWidget *parent)
	: QDialog(parent)
    , m_pResizerDecorator(nullptr)
{
    init();
	//初始化为未按下鼠标左键
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
	setAttribute(Qt::WA_NoSystemBackground, false);
    setMouseTracking(true);
    setWindowIcon(TOON_ICON);
    setWindowTitle(TOON_TITLE);
    m_pResizerDecorator = new TNResizerDecorator(this);
    m_pResizerDecorator->setMovable(true);
    m_pResizerDecorator->setResizable(false);
}

DropShadowWidget::~DropShadowWidget()
{

}

void DropShadowWidget::init()
{ 
}

void DropShadowWidget::setResizable(bool bValue)
{
    m_pResizerDecorator->setResizable(bValue);
}

void DropShadowWidget::setMoveable(bool bIsMoveable)
{
    m_pResizerDecorator->setMovable(bIsMoveable);
}