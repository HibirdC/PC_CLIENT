#include "TNElidedLabel.h"

#include <QDebug>
#include <QPainter>
#include <QResizeEvent>
#include <QStyleOption>

TNElidedLabel::TNElidedLabel(QWidget* parent, Qt::WindowFlags f)
: QLabel(parent, f)
, _elideMode(Qt::ElideRight)
{
}

TNElidedLabel::TNElidedLabel(const QString& txt, QWidget* parent, Qt::WindowFlags f)
: QLabel(txt, parent, f)
, _elideMode(Qt::ElideRight)
{
}

TNElidedLabel::TNElidedLabel(const QString& txt, Qt::TextElideMode elideMode,
	QWidget *parent, Qt::WindowFlags f)
	: QLabel(txt, parent, f)
	, _elideMode(elideMode)
{
}

TNElidedLabel::~TNElidedLabel()
{

}

void TNElidedLabel::setText(const QString& txt)
{
    _orignalText = txt;
    QLabel::setText(_orignalText);
    cacheElidedText(geometry().width(),txt);
}

void TNElidedLabel::cacheElidedText(int w,const QString& text)
{
    _cachedElidedText = fontMetrics().elidedText(text, _elideMode, w, Qt::TextShowMnemonic);
}

void TNElidedLabel::resizeEvent(QResizeEvent* e)
{
	QLabel::resizeEvent(e);
    cacheElidedText(e->size().width(),_orignalText);
}

void TNElidedLabel::paintEvent(QPaintEvent* e)
{
    QPainter p(this);
    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    if(_elideMode == Qt::ElideNone){
        QLabel::paintEvent(e);
    }else{
        p.drawText(0, 0,
                   geometry().width(),
                   geometry().height(),
                   alignment(),
                   _cachedElidedText
                   );

    }
}

void TNElidedLabel::setToolTip(const QString &tip)
{
    int w = 300;
    QString toolTip = fontMetrics().elidedText(tip, _elideMode, w, Qt::TextShowMnemonic);
    return QLabel::setToolTip(toolTip);
}
