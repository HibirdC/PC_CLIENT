#include "TNHomePageTreeView.h"

#include <QScrollBar>
#include <QDebug>

TNHomePageTreeView::TNHomePageTreeView(QWidget *parent)
    : QTreeView(parent)
{

}

TNHomePageTreeView::~TNHomePageTreeView()
{

}

void TNHomePageTreeView::updateGeometries()
{
    QTreeView::updateGeometries();
    this->verticalScrollBar()->setSingleStep(5);
}

void TNHomePageTreeView::mouseDoubleClickEvent(QMouseEvent *event)
{
    return;
}

void TNHomePageTreeView::keyPressEvent(QKeyEvent *event)
{
    return;
}
