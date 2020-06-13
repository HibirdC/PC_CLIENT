#include "TNGCTreeView.h"
#include <QScrollBar>
#include <QMouseEvent>

TNGCTreeView::TNGCTreeView(QWidget *parent)
: QTreeView(parent)
{

}

TNGCTreeView::~TNGCTreeView()
{

}

void TNGCTreeView::updateGeometries()
{
	QTreeView::updateGeometries();
	this->verticalScrollBar()->setSingleStep(5);
}
void TNGCTreeView::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::RightButton)
	{
		return;
	}
	QTreeView::mousePressEvent(event);
}