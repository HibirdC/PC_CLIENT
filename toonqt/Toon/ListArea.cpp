#include "ListArea.h"

#include <QPointer>
#include <QStyleOption>
#include <QApplication>
#include <QDesktopWidget>

#include "tnnotifycenter.h"
#include "TNDataStatistics.h"
#include "TNZoomFactor.h"
ListArea::ListArea(TNPluginParamPtr pluginParam, QWidget *parent)
    : QStackedWidget(parent)
    , _pluginParam(pluginParam)
    , _latestSelectedPage(MENU_NOTICE_ID)
{
    init();
}

void ListArea::init()
{
#ifdef Q_OS_WIN
    setObjectName("ListArea");
    setMaximumHeight(TNZoomFactor::GetMaxFrameHeight());
#else
    setObjectName("MacListArea");
#endif

    this->setFocusPolicy(Qt::ClickFocus);
}

void ListArea::LoadListLibrary(PluginExportBase *tempMenu, int dimension)
{
    Q_ASSERT(dimension);
    if (tempMenu->GetList() != NULL)
    {
        this->addWidget(tempMenu->GetList());
    }
}

void ListArea::doubleClickPage(int current_page)
{
    if (current_page == MENU_NOTICE_ID)
    {
        emit turnPageSignal(true);
        ListAreaBase *listArea = qobject_cast<ListAreaBase *>(this->widget(0));
        if (listArea)
            listArea->LoadScropUnRead(true);
    }
}

void ListArea::turnPage(int current_page)
{
    for (int i = 0; i < this->count(); i++)
    {
        ListAreaBase *listArea = qobject_cast<ListAreaBase *>(this->widget(i));
        if (listArea)
        {
            if (listArea->GetID() == current_page)
            {
                this->setCurrentIndex(i);
                break;
            }
        }
    }

    if (current_page == MENU_AVATAR_ID)
    {
        emit turnPageSignal(true);
    }
    else if (current_page == MENU_CARDCASE_ID)
    {
        this->show();
        emit TNNotifyCenter::instance()->signalListAreaVisible(true);
        emit turnPageSignal(true);
		emit sendCurrentSelectedPage(current_page);
        ListAreaBase *listArea = qobject_cast<ListAreaBase *>(this->widget(1));
        if (listArea)
            listArea->LoadDefaultPage();
    }
    else if (current_page == MENU_NOTICE_ID)
    {
        this->show();
        emit TNNotifyCenter::instance()->signalListAreaVisible(true);
        emit turnPageSignal(true);
        if (_latestSelectedPage == MENU_NOTICE_ID)
        {
            ListAreaBase *listArea = qobject_cast<ListAreaBase *>(this->widget(0));
            if (listArea)
                listArea->LoadScropUnRead(false);
        }
    }
    else if (current_page == MENU_MINE_ID)
    {
        this->show();
        emit TNNotifyCenter::instance()->signalListAreaVisible(true);
        emit turnPageSignal(true);
		emit sendCurrentSelectedPage(current_page);
    }
    else if (current_page == MENU_HOMEPAGE_ID)
    {
        this->show();
        emit TNNotifyCenter::instance()->signalListAreaVisible(false);
        emit turnPageSignal(true);
    }
    else
    {
        this->show();
        emit TNNotifyCenter::instance()->signalListAreaVisible(true);
        emit turnPageSignal(true);
    }
    _latestSelectedPage = current_page;
}

bool ListArea::eventFilter(QObject *obj, QEvent *event)
{
    return QStackedWidget::eventFilter(obj, event);
}

void ListArea::paintEvent(QPaintEvent * event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void ListArea::mouseDoubleClickEvent(QMouseEvent*)
{
    emit maxMinSet(true);
}
