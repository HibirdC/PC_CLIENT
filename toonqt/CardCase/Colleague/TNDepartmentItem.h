#ifndef TNDEPARTMENTTREEITEM_H
#define TNDEPARTMENTTREEITEM_H

#include "TNCardCaseTreeItem.h"

#include <QList>
#include <QVariant>

class TNDepartmentItem : public TNCardCaseTreeItem
{
public:
    explicit TNDepartmentItem(const QString &departmentName, TNCardCaseTreeItem *parentItem = 0);
    ~TNDepartmentItem();

    virtual ColleagueTreeItem getItemGrade() const;
};

#endif // TNDEPARTMENTTREEITEM_H
