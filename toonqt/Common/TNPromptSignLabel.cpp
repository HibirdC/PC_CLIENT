#include <QEvent>
#include "TNPromptSignLabel.h"


TNPromptSignLabel::TNPromptSignLabel(QWidget * attchWidget, TNPromptSignLabel::PosType type)
    : _attachWidget(attchWidget)
    , _posType(type)
{
    setParent(_attachWidget->parentWidget());
	setObjectName("upgradePromptLabel");//todo 暂时使用这个样式
    setMaximumSize(10, 10);
    attchWidget->installEventFilter(this);
}


TNPromptSignLabel::~TNPromptSignLabel()
{
}

void TNPromptSignLabel::relocate()
{
    QPoint pos;
    if (_posType == TopRight)
    {
        pos.setX(_attachWidget->pos().x() + _attachWidget->width() - width() * 2 / 3);
        pos.setY(_attachWidget->pos().y() - height() / 3);
        move(pos);
    }
    else if (_posType == CenterRight)
    {
        pos.setX(_attachWidget->pos().x() + _attachWidget->width() - 40);
        pos.setY(_attachWidget->pos().y() + _attachWidget->height() * 0.5 - height() * 0.5);
        move(pos);
    }
    show();
}

bool TNPromptSignLabel::eventFilter(QObject *target, QEvent *event)
{
    if (target == _attachWidget)
	{
		if (event->type() == QEvent::Resize || event->type() == QEvent::Move)
		{
            relocate();
		}
	}
    return QWidget::eventFilter(target, event);
}
