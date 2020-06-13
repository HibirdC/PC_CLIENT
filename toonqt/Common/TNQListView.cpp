#include "TNQListView.h"
#include <QMouseEvent>
#include <QScrollBar>
#include <QToolTip>
#include <QDebug>

TNQListView::TNQListView(QWidget *parent)
: QListView(parent)
{
	setMouseTracking(true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}
TNQListView::~TNQListView()
{

}
void TNQListView::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::RightButton)
	{
		return;
	}
	QListView::mousePressEvent(event);
}
void TNQListView::keyPressEvent(QKeyEvent *event)
{
	return;
}
void TNQListView::updateGeometries()
{
	QListView::updateGeometries();
	this->verticalScrollBar()->setSingleStep(8);
}
