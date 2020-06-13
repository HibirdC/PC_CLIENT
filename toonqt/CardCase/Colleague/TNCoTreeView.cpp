#include "TNCoTreeView.h"
#include <QScrollBar>
#include <QMouseEvent>

TNCoTreeView::TNCoTreeView(QWidget *parent)
: QTreeView(parent)
{

}

TNCoTreeView::~TNCoTreeView()
{

}
void TNCoTreeView::updateGeometries()
{
	QTreeView::updateGeometries();
	this->verticalScrollBar()->setSingleStep(5);
}
void TNCoTreeView::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::RightButton)
	{
		return;
	}
	QTreeView::mousePressEvent(event);
}
void TNCoTreeView::keyPressEvent(QKeyEvent *event)
{
	return;
}