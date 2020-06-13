#include "TNStaffItem.h"
#include "TNDepartmentItem.h"
#include <QStringList>

TNDepartmentItem::TNDepartmentItem(const QString &departmentName, TNCardCaseTreeItem *parent) :
    TNCardCaseTreeItem(QList<QVariant>()<<departmentName, parent)
{

}

TNDepartmentItem::~TNDepartmentItem()
{
}

TNCardCaseTreeItem::ColleagueTreeItem TNDepartmentItem::getItemGrade() const
{
    return TNCardCaseTreeItem::Department;
}
