#ifndef TNEXPANDITEM_H
#define TNEXPANDITEM_H

#include "TNCardCaseTreeItem.h"

#include <QList>
#include <QVariant>

class TNExpandItem : public TNCardCaseTreeItem
{
public:
	explicit TNExpandItem(const QString &nodeName, TNCardCaseTreeItem *parentItem = 0);
	~TNExpandItem();

    virtual ColleagueTreeItem getItemGrade() const;
};

#endif // TNEXPANDITEM_H
