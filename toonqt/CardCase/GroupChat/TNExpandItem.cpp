#include "TNExpandItem.h"
#include <QStringList>

TNExpandItem::TNExpandItem(const QString &nodeName, TNCardCaseTreeItem *parent) :
TNCardCaseTreeItem(QList<QVariant>() << nodeName, parent)
{

}

TNExpandItem::~TNExpandItem()
{
}

TNCardCaseTreeItem::ColleagueTreeItem TNExpandItem::getItemGrade() const
{
	return TNCardCaseTreeItem::Expand;
}
