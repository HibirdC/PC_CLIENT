#include "TNSearchViewV2.h"
#include <QScrollBar>
#include <QDebug>

TNSearchViewV2::TNSearchViewV2(QWidget *parent)
: QTreeView(parent)
{

}
TNSearchViewV2::~TNSearchViewV2()
{

}
void TNSearchViewV2::setItemExpanded(const QModelIndex &index, bool expanded)
{
	qInfo() << "[TNMVD][TNSearchViewV2]setItemExpanded Tree second node Click(setItemExpanded): " << expanded;
	this->setExpanded(index, expanded);
}
void TNSearchViewV2::updateGeometries()
{
	QTreeView::updateGeometries();
	this->verticalScrollBar()->setSingleStep(5);
}
void TNSearchViewV2::mouseDoubleClickEvent(QMouseEvent *event)
{
	return;
}
void TNSearchViewV2::keyPressEvent(QKeyEvent *event)
{
	return;
}