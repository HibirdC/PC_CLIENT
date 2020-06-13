#include "tntextobject.h"
#include <QDebug>

TNTextObject::TNTextObject(QObject *parent)
	: QObject(parent)
{

}

TNTextObject::~TNTextObject()
{
	qDebug() << "Del TNTextObject Object";
}

