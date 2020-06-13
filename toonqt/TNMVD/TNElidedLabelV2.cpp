#include "TNElidedLabelV2.h"

#include <QDebug>
#include <QPainter>
#include <QResizeEvent>
#include <QStyleOption>

TNElidedLabelV2::TNElidedLabelV2(QWidget* parent, Qt::WindowFlags f)
: QLabel(parent, f)
, _elideMode(Qt::ElideRight)
{
}

TNElidedLabelV2::TNElidedLabelV2(const QString& txt, QWidget* parent, Qt::WindowFlags f)
: QLabel(txt, parent, f)
, _elideMode(Qt::ElideRight)
{
}

TNElidedLabelV2::TNElidedLabelV2(const QString& txt, Qt::TextElideMode elideMode,
	QWidget *parent, Qt::WindowFlags f)
	: QLabel(txt, parent, f)
	, _elideMode(elideMode)
{
}

TNElidedLabelV2::~TNElidedLabelV2()
{

}

void TNElidedLabelV2::setText(const QString& txt)
{
	QLabel::setText(txt);
	cacheElidedText(geometry().width());
}

void TNElidedLabelV2::cacheElidedText(int w)
{
    _cachedElidedText = fontMetrics().elidedText(text(), _elideMode, w, Qt::TextShowMnemonic);
}

void TNElidedLabelV2::resizeEvent(QResizeEvent* e)
{
	QLabel::resizeEvent(e);
	cacheElidedText(e->size().width());
}

void TNElidedLabelV2::paintEvent(QPaintEvent* e)
{
    QPainter p(this);
    if (_elideMode == Qt::ElideNone) {
		QLabel::paintEvent(e);
	}
	else {
		p.drawText(0, 0,
			geometry().width(),
			geometry().height(),
			alignment(),
			_cachedElidedText
			);
	}
	QStyleOption opt;
	opt.init(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void TNElidedLabelV2::setToolTip(const QString &tip)
{
    int w = 300;
    QString toolTip = fontMetrics().elidedText(tip, _elideMode, w, Qt::TextShowMnemonic);
    return QLabel::setToolTip(toolTip);
}
