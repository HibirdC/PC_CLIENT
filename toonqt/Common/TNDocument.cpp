#include "TNDocument.h"

#include <QDebug>
#include <QJsonObject>

void TNDocument::setSendTextText(const QJsonObject &text)
{
	emit sendText(text);
}

/*!
    This slot is invoked from the HTML client side and the text displayed on the server side.
*/
void TNDocument::receiveText(const QString &r_text)
{
    qDebug()<<"***********receiveText*********** this="<<this;
	emit sendReceiveText(r_text);
}

