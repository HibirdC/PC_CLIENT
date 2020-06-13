#include "tnavatorbutton.h"
#include <QPainter>
#include <QTime>
#include <QDebug>
#include "TNDebugLog.h"
TNAvatorButton::TNAvatorButton(QWidget *parent /* = 0 */, Cust_Type cust_type /* = cust_radius */)
	: QPushButton(parent)
	, _cust_type(cust_type)
	, _sizeType(TN::Normal)
{
	_avatorImagePath = ":/Resources/DefaltAvarta.png";
}

TNAvatorButton::~TNAvatorButton()
{

}

void TNAvatorButton::setSmallMask(TN::AvatarType flag)
{
	_sizeType = flag;
}

void TNAvatorButton::setCustType(Cust_Type cust_type)
{
	_cust_type = cust_type;
	QPixmap drawImage = TNCommonDealAvator::getTypeQPixmap(_avatorImagePath, QSize(80,80), _cust_type, _sizeType);
	setIcon(drawImage);
	setIconSize(size());
	update();
}

void TNAvatorButton::setAvatorImagePath(const QString& file_path)
{
	_avatorImagePath = file_path;
	QPixmap drawImage = TNCommonDealAvator::getTypeQPixmap(_avatorImagePath, QSize(80, 80), _cust_type, _sizeType);
	setIcon(drawImage);
	setIconSize(size());
	update();
}

void TNAvatorButton::paintEvent(QPaintEvent * e)
{
	/*
	QPainter p(this);
	p.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::HighQualityAntialiasing, true);
	QPixmap drawImage = TNCommonDealAvator::getTypeQPixmap(_avatorImagePath, QSize(80, 80), _cust_type, _sizeType);
	QRect rectTarget(0, 0, 40, 40);
	QRect rectSource(0, 0, 80, 80);
	p.drawPixmap(rectTarget, drawImage, rectSource);*/
	QPushButton::paintEvent(e);
}