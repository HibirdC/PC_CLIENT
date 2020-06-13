#include "TNUnReadView.h"
#include <QMouseEvent>

TNUnReadView::TNUnReadView()
	: QListView()
{

}

TNUnReadView::~TNUnReadView()
{

}
bool TNUnReadView::event(QEvent *event)
{
	if (event->type() == QEvent::Leave)
	{
		this->hide();
	}
	return QListView::event(event);
}
void TNUnReadView::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::RightButton)
	{
		return;
	}
	QListView::mousePressEvent(event);
}