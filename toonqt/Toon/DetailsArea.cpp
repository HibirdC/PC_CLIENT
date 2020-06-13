#include "DetailsArea.h"

#include <QPointer>
#include <QApplication>
#include <QDesktopWidget>

#include "tnnotifycenter.h"
#include "TNZoomFactor.h"
DetailsArea::DetailsArea(QWidget *parent)
    : QStackedWidget(parent)
{    
#ifdef Q_OS_WIN
    setMaximumWidth(TNZoomFactor::GetMaxFrameWidth() - MENU_AREA_WIDTH - LIST_AREA_WIDTH);
    setMaximumHeight(TNZoomFactor::GetMaxFrameHeight());
#endif
    connect(TNNotifyCenter::instance(), SIGNAL(signalListAreaVisible(bool)), this, SLOT(slotSetMaximumWidth(bool)));
#ifdef Q_OS_WIN
	this->setObjectName("detailWidget");
#else
	this->setObjectName("MacDetailWidget");
#endif
}

void DetailsArea::OnTurnPageSlot(int current_page)
{
    for (int i = 0; i < this->count(); i++)
    {
        DetailsAreaBase *detaiArea = qobject_cast<DetailsAreaBase *>(this->widget(i));
        if (detaiArea)
        {
            if (detaiArea->GetID() == current_page)
            {
                this->setCurrentIndex(i);
            }
        }
    }
}

void DetailsArea::slotSetMaximumWidth(bool visible)
{
#ifdef Q_OS_WIN
    if (visible)
		setMaximumWidth(TNZoomFactor::GetMaxFrameWidth() - MENU_AREA_WIDTH - LIST_AREA_WIDTH);
    else
		setMaximumWidth(TNZoomFactor::GetMaxFrameWidth() - MENU_AREA_WIDTH);
#endif
}

void DetailsArea::LoadDetailsLibrary(PluginExportBase *tempMenu, int dimension)
{
    Q_ASSERT(dimension);
    if (tempMenu->GetDetails() != NULL)
    {
        this->addWidget(tempMenu->GetDetails());
    }
}

void DetailsArea::mouseDoubleClickEvent(QMouseEvent*)
{
    emit maxMinSet(true);
}
