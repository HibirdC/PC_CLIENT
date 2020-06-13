#include "CSeachClearLabel.h"
#include <QMouseEvent>
#include <QCursor>

CSeachClearLabel::CSeachClearLabel(QWidget *parent)
	: QLabel(parent)
{
	installEventFilter(this);
}

CSeachClearLabel::~CSeachClearLabel()
{

}
void CSeachClearLabel::mousePressEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::LeftButton)
	{
		emit sigClicked();
	}
	QLabel::mousePressEvent(event);
}
bool CSeachClearLabel::eventFilter(QObject *target, QEvent *event)
{
	if (event->type() == QEvent::Enter)
	{
		this->setCursor(QCursor(Qt::PointingHandCursor));
	}
	return QWidget::eventFilter(target, event);
}
