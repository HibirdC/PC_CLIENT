#ifndef TNCOMPANYTREEITEM_H
#define TNCOMPANYTREEITEM_H

#include "TNCardCaseTreeItem.h"

#include <QList>
#include <QVariant>

class TNCompanyItem : public TNCardCaseTreeItem
{
public:
    explicit TNCompanyItem(const QString &companyName, TNCardCaseTreeItem *parentItem = 0);
    ~TNCompanyItem();

    virtual ColleagueTreeItem getItemGrade() const;
};

#endif // TNCOMPANYTREEITEM_H
